// CoreAudioDriver.cpp
// Low-latency guitar input → Guitarix DSP → stereo output via CoreAudio AUHAL.

#include "CoreAudioDriver.h"
#include <CoreAudio/CoreAudio.h>
#include <AudioUnit/AudioUnit.h>
#include <AudioToolbox/AudioToolbox.h>
#include <cstring>
#include <cmath>
#include <stdexcept>
#include <algorithm>

// ── helpers ───────────────────────────────────────────────────────────────────

static void throwIfErr(OSStatus s, const char* msg) {
    if (s != noErr) throw std::runtime_error(std::string(msg) + " (" + std::to_string(s) + ")");
}

static AudioDeviceID defaultDevice(bool input) {
    AudioDeviceID dev = kAudioObjectUnknown;
    UInt32 size = sizeof(dev);
    AudioObjectPropertyAddress addr {
        input ? kAudioHardwarePropertyDefaultInputDevice
              : kAudioHardwarePropertyDefaultOutputDevice,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMain
    };
    AudioObjectGetPropertyData(kAudioObjectSystemObject, &addr, 0, nullptr, &size, &dev);
    return dev;
}

// ── CoreAudioDriver ───────────────────────────────────────────────────────────

CoreAudioDriver::CoreAudioDriver() = default;

CoreAudioDriver::~CoreAudioDriver() {
    close();
}

bool CoreAudioDriver::open(AudioProcessCallback cb,
                           double requestedSampleRate,
                           uint32_t requestedBufferSize)
{
    callback_ = std::move(cb);

    if (!setupIOUnit(requestedSampleRate, requestedBufferSize))
        return false;

    OSStatus err = AudioUnitInitialize(ioUnit_);
    if (err != noErr) return false;

    err = AudioOutputUnitStart(ioUnit_);
    if (err != noErr) return false;

    running_.store(true);
    return true;
}

void CoreAudioDriver::close() {
    if (!running_.load()) return;
    running_.store(false);
    if (ioUnit_) {
        AudioOutputUnitStop(ioUnit_);
        AudioUnitUninitialize(ioUnit_);
        AudioComponentInstanceDispose(ioUnit_);
        ioUnit_ = nullptr;
    }
}

// ── setupIOUnit ───────────────────────────────────────────────────────────────

bool CoreAudioDriver::setupIOUnit(double sampleRate, uint32_t bufferSize) {
    // 1. Find the AUHAL (RemoteIO on macOS is "DefaultOutputUnit" concept;
    //    we use kAudioUnitSubType_HALOutput which handles both I/O).
    AudioComponentDescription desc{};
    desc.componentType         = kAudioUnitType_Output;
    desc.componentSubType      = kAudioUnitSubType_HALOutput;
    desc.componentManufacturer = kAudioUnitManufacturer_Apple;

    AudioComponent comp = AudioComponentFindNext(nullptr, &desc);
    if (!comp) return false;

    OSStatus err = AudioComponentInstanceNew(comp, &ioUnit_);
    if (err != noErr) return false;

    // 2. Enable input bus (bus 1) and output bus (bus 0).
    UInt32 enableIO = 1;
    err = AudioUnitSetProperty(ioUnit_, kAudioOutputUnitProperty_EnableIO,
                               kAudioUnitScope_Input, 1, &enableIO, sizeof(enableIO));
    throwIfErr(err, "Enable input");

    enableIO = 1;
    err = AudioUnitSetProperty(ioUnit_, kAudioOutputUnitProperty_EnableIO,
                               kAudioUnitScope_Output, 0, &enableIO, sizeof(enableIO));
    throwIfErr(err, "Enable output");

    // 3. Set devices.
    AudioDeviceID inDev  = inputDeviceId_  ? inputDeviceId_  : defaultDevice(true);
    AudioDeviceID outDev = outputDeviceId_ ? outputDeviceId_ : defaultDevice(false);

    err = AudioUnitSetProperty(ioUnit_, kAudioOutputUnitProperty_CurrentDevice,
                               kAudioUnitScope_Global, 1, &inDev, sizeof(inDev));
    throwIfErr(err, "Set input device");

    err = AudioUnitSetProperty(ioUnit_, kAudioOutputUnitProperty_CurrentDevice,
                               kAudioUnitScope_Global, 0, &outDev, sizeof(outDev));
    throwIfErr(err, "Set output device");

    // 4. Set stream format: non-interleaved 32-bit float.
    AudioStreamBasicDescription fmt{};
    fmt.mSampleRate       = sampleRate;
    fmt.mFormatID         = kAudioFormatLinearPCM;
    fmt.mFormatFlags      = kAudioFormatFlagIsFloat | kAudioFormatFlagIsNonInterleaved;
    fmt.mBitsPerChannel   = 32;
    fmt.mChannelsPerFrame = 2;
    fmt.mBytesPerFrame    = 4;
    fmt.mFramesPerPacket  = 1;
    fmt.mBytesPerPacket   = 4;

    // Input stream (mono from guitar interface → we read ch0 as mono)
    AudioStreamBasicDescription fmtMono = fmt;
    fmtMono.mChannelsPerFrame = 1;

    err = AudioUnitSetProperty(ioUnit_, kAudioUnitProperty_StreamFormat,
                               kAudioUnitScope_Output, 1, &fmtMono, sizeof(fmtMono));
    // Non-fatal if the device doesn't accept mono; we'll de-interleave manually.

    // Output stream (stereo)
    err = AudioUnitSetProperty(ioUnit_, kAudioUnitProperty_StreamFormat,
                               kAudioUnitScope_Input, 0, &fmt, sizeof(fmt));
    throwIfErr(err, "Set output stream format");

    // 5. Buffer size.
    UInt32 bs = static_cast<UInt32>(bufferSize);
    AudioObjectPropertyAddress bsAddr {
        kAudioDevicePropertyBufferFrameSize,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMain
    };
    AudioObjectSetPropertyData(outDev, &bsAddr, 0, nullptr, sizeof(bs), &bs);

    actualSampleRate_ = sampleRate;
    actualBufferSize_ = bufferSize;

    // Pre-allocate float buffers.
    inBufL_.assign(bufferSize * 4, 0.f);
    inBufR_.assign(bufferSize * 4, 0.f);
    outBufL_.assign(bufferSize * 4, 0.f);
    outBufR_.assign(bufferSize * 4, 0.f);

    // 6. Register render callback.
    AURenderCallbackStruct cb{ renderCallback, this };
    err = AudioUnitSetProperty(ioUnit_, kAudioUnitProperty_SetRenderCallback,
                               kAudioUnitScope_Input, 0, &cb, sizeof(cb));
    throwIfErr(err, "Set render callback");

    return true;
}

// ── render callback (real-time thread) ───────────────────────────────────────

OSStatus CoreAudioDriver::renderCallback(void*                       inRefCon,
                                         AudioUnitRenderActionFlags* ioActionFlags,
                                         const AudioTimeStamp*       inTimeStamp,
                                         UInt32                      inBusNumber,
                                         UInt32                      inNumberFrames,
                                         AudioBufferList*            ioData)
{
    auto* self = static_cast<CoreAudioDriver*>(inRefCon);
    if (!self->running_.load()) return noErr;

    const uint32_t n = inNumberFrames;

    // Pull input from bus 1.
    // We allocate a temporary ABL on the stack for the input render.
    AudioBufferList* inABL = nullptr;
    // Use a small stack allocation for 1-channel case.
    constexpr int maxCh = 2;
    char abl_storage[sizeof(AudioBufferList) + (maxCh - 1) * sizeof(AudioBuffer)];
    inABL = reinterpret_cast<AudioBufferList*>(abl_storage);
    inABL->mNumberBuffers = 1;
    inABL->mBuffers[0].mNumberChannels = 1;
    inABL->mBuffers[0].mDataByteSize   = n * sizeof(float);
    inABL->mBuffers[0].mData           = self->inBufL_.data();

    // Pull captured audio from input bus.
    AudioUnitRender(self->ioUnit_, ioActionFlags, inTimeStamp, 1, n, inABL);

    const float* inL = static_cast<float*>(inABL->mBuffers[0].mData);
    const float* inR = nullptr; // mono guitar in

    float* outL = self->outBufL_.data();
    float* outR = self->outBufR_.data();

    // Call the DSP callback (GuitarixBridge sets this up to call the engine chains).
    if (self->callback_) {
        self->callback_(inL, inR, outL, outR, n);
    } else {
        std::memset(outL, 0, n * sizeof(float));
        std::memset(outR, 0, n * sizeof(float));
    }

    // Write output to CoreAudio buffers (non-interleaved stereo).
    if (ioData->mNumberBuffers >= 2) {
        std::memcpy(ioData->mBuffers[0].mData, outL, n * sizeof(float));
        std::memcpy(ioData->mBuffers[1].mData, outR, n * sizeof(float));
    } else if (ioData->mNumberBuffers == 1) {
        // Interleaved fallback: mix to stereo interleaved.
        float* dst = static_cast<float*>(ioData->mBuffers[0].mData);
        for (uint32_t i = 0; i < n; ++i) {
            dst[i*2]   = outL[i];
            dst[i*2+1] = outR[i];
        }
    }

    self->updateMeters(outL, outR, inL, n);
    return noErr;
}

// ── metering ─────────────────────────────────────────────────────────────────

static float peakOf(const float* buf, uint32_t n) {
    float pk = 0.f;
    for (uint32_t i = 0; i < n; ++i) pk = std::max(pk, std::abs(buf[i]));
    return pk;
}

void CoreAudioDriver::updateMeters(const float* outL, const float* outR,
                                   const float* inL,  uint32_t frames)
{
    constexpr float kRelease = 0.9f;
    auto smooth = [&](std::atomic<float>& meter, float newPeak) {
        float old = meter.load(std::memory_order_relaxed);
        meter.store(std::max(newPeak, old * kRelease), std::memory_order_relaxed);
    };
    smooth(inputLevel_,   peakOf(inL,  frames));
    smooth(outputLevelL_, peakOf(outL, frames));
    smooth(outputLevelR_, peakOf(outR, frames));
}

// ── device enumeration ────────────────────────────────────────────────────────

static std::vector<CoreAudioDriver::DeviceInfo> enumerateDevices(bool input) {
    std::vector<CoreAudioDriver::DeviceInfo> result;

    AudioObjectPropertyAddress addr {
        kAudioHardwarePropertyDevices,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMain
    };
    UInt32 size = 0;
    if (AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &addr, 0, nullptr, &size) != noErr)
        return result;

    int count = size / sizeof(AudioDeviceID);
    std::vector<AudioDeviceID> ids(count);
    AudioObjectGetPropertyData(kAudioObjectSystemObject, &addr, 0, nullptr, &size, ids.data());

    AudioObjectPropertyAddress nameAddr {
        kAudioDevicePropertyDeviceNameCFString,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMain
    };
    AudioObjectPropertyAddress streamAddr {
        kAudioDevicePropertyStreamConfiguration,
        input ? kAudioObjectPropertyScopeInput : kAudioObjectPropertyScopeOutput,
        kAudioObjectPropertyElementMain
    };

    for (auto dev : ids) {
        // Check that this device has streams in the requested direction.
        UInt32 sz = 0;
        if (AudioObjectGetPropertyDataSize(dev, &streamAddr, 0, nullptr, &sz) != noErr) continue;
        if (sz == 0) continue;

        CFStringRef cfName = nullptr;
        UInt32 nameSize = sizeof(cfName);
        if (AudioObjectGetPropertyData(dev, &nameAddr, 0, nullptr, &nameSize, &cfName) != noErr)
            continue;

        char buf[256] = {};
        if (cfName) {
            CFStringGetCString(cfName, buf, sizeof(buf), kCFStringEncodingUTF8);
            CFRelease(cfName);
        }
        result.push_back({ std::string(buf), static_cast<uint32_t>(dev) });
    }
    return result;
}

std::vector<CoreAudioDriver::DeviceInfo> CoreAudioDriver::listInputDevices()  {
    return enumerateDevices(true);
}
std::vector<CoreAudioDriver::DeviceInfo> CoreAudioDriver::listOutputDevices() {
    return enumerateDevices(false);
}
