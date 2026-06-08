#pragma once
// CoreAudioDriver.h — replaces GxJack for the macOS app.
// Opens the default audio input (guitar interface) and output using
// CoreAudio's AudioUnit HAL, then drives the Guitarix DSP engine chains
// from a real-time render callback.

#include <AudioUnit/AudioUnit.h>
#include <AudioToolbox/AudioToolbox.h>
#include <functional>
#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

namespace gx_engine {
class MonoModuleChain;
class StereoModuleChain;
}

// Callback signature: called from the RT thread with de-interleaved float buffers.
// inL/inR: input (inR == nullptr for mono-in devices).
// outL/outR: output (always stereo out).
using AudioProcessCallback =
    std::function<void(const float* inL, const float* inR,
                       float* outL,       float* outR,
                       uint32_t frameCount)>;

class CoreAudioDriver {
public:
    CoreAudioDriver();
    ~CoreAudioDriver();

    // Initialize with a user-supplied DSP callback.
    // sampleRate and bufferSize are requested values; actual values are set
    // after open() and readable via getSampleRate() / getBufferSize().
    bool open(AudioProcessCallback cb,
              double requestedSampleRate = 44100.0,
              uint32_t requestedBufferSize = 256);

    void close();
    bool isRunning() const { return running_.load(); }

    double   getSampleRate()  const { return actualSampleRate_; }
    uint32_t getBufferSize()  const { return actualBufferSize_; }

    // Level metering (peak, smoothed, updated from RT thread)
    float inputLevel()  const { return inputLevel_.load();  }
    float outputLevelL() const { return outputLevelL_.load(); }
    float outputLevelR() const { return outputLevelR_.load(); }

    // List available audio devices (display names + AudioDeviceID)
    struct DeviceInfo { std::string name; uint32_t deviceId; };
    static std::vector<DeviceInfo> listInputDevices();
    static std::vector<DeviceInfo> listOutputDevices();

    // Select specific device before open()
    void setInputDevice(uint32_t deviceId)  { inputDeviceId_  = deviceId; }
    void setOutputDevice(uint32_t deviceId) { outputDeviceId_ = deviceId; }

private:
    // CoreAudio IO AudioUnit (AUHAL)
    AudioUnit ioUnit_  = nullptr;
    AudioUnit mixUnit_ = nullptr;       // optional mixer for metering

    uint32_t inputDeviceId_  = 0;       // 0 = default
    uint32_t outputDeviceId_ = 0;

    double   actualSampleRate_ = 44100.0;
    uint32_t actualBufferSize_ = 256;

    std::atomic<bool>  running_{false};
    AudioProcessCallback callback_;

    // Intermediate buffers (allocated in open(), used in RT callback)
    std::vector<float> inBufL_, inBufR_;
    std::vector<float> outBufL_, outBufR_;

    // Metering (lock-free, updated from RT thread)
    std::atomic<float> inputLevel_{0.f};
    std::atomic<float> outputLevelL_{0.f};
    std::atomic<float> outputLevelR_{0.f};

    // CoreAudio render callback (called by the OS on a real-time thread)
    static OSStatus renderCallback(void*                       inRefCon,
                                   AudioUnitRenderActionFlags* ioActionFlags,
                                   const AudioTimeStamp*       inTimeStamp,
                                   UInt32                      inBusNumber,
                                   UInt32                      inNumberFrames,
                                   AudioBufferList*            ioData);

    bool setupIOUnit(double sampleRate, uint32_t bufferSize);
    void updateMeters(const float* outL, const float* outR,
                      const float* inL,  uint32_t frames);
};
