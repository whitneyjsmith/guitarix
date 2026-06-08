// GuitarixBridge.mm
// Objective-C++ implementation — calls into GxMachine (C++) and CoreAudioDriver.

#define GUITARIX_AS_PLUGIN 1

#import "GuitarixBridge.h"
#include "CoreAudioDriver.h"

// Guitarix engine headers
#include "engine.h"
#include "machine.h"
#include "gx_system.h"

#include <memory>
#include <string>
#include <vector>

// Bring the entire gx_engine namespace into scope so GxMachine, GxEngine,
// GxEngineState, kEngineOff/On/Bypass, PluginListBase etc. are unqualified.
using namespace gx_engine;

// ── Helpers ───────────────────────────────────────────────────────────────────

static NSString *ns(const std::string& s) {
    return [NSString stringWithUTF8String:s.c_str()];
}
static NSString *ns(const Glib::ustring& s) {
    return [NSString stringWithUTF8String:s.c_str()];
}
static std::string cpp(NSString *s) {
    return s ? std::string(s.UTF8String) : "";
}

// ── GXPreset ──────────────────────────────────────────────────────────────────

@implementation GXPreset
@end

@implementation GXAudioDevice
@end

// ── GuitarixBridge ────────────────────────────────────────────────────────────

@implementation GuitarixBridge {
    std::unique_ptr<gx_system::CmdlineOptions> _options;
    std::unique_ptr<GxMachine>                 _machine;
    std::unique_ptr<CoreAudioDriver>           _driver;
    NSString *_currentAmpModelId;
    NSString *_currentCabinetModelId;
    BOOL      _tunerEnabled;
}

@synthesize engineState    = _engineState;
@synthesize tunerEnabled   = _tunerEnabled;

// ── Init ──────────────────────────────────────────────────────────────────────

- (nullable instancetype)initWithError:(NSError **)error {
    self = [super init];
    if (!self) return nil;

    _currentAmpModelId     = @"";
    _currentCabinetModelId = @"";
    _tunerEnabled          = NO;

    try {
        NSString *bundlePath = [[NSBundle mainBundle] bundlePath];
        _options = std::make_unique<gx_system::CmdlineOptions>(bundlePath.UTF8String);

        NSString *appSupport = [NSSearchPathForDirectoriesInDomains(
            NSApplicationSupportDirectory, NSUserDomainMask, YES) firstObject];
        NSString *gxDir = [appSupport stringByAppendingPathComponent:@"Guitarix/"];
        [[NSFileManager defaultManager] createDirectoryAtPath:gxDir
                                  withIntermediateDirectories:YES
                                                   attributes:nil
                                                        error:nil];
        _options->set_user_dir(std::string(gxDir.UTF8String));

        _machine = std::make_unique<GxMachine>(*_options);
        _driver  = std::make_unique<CoreAudioDriver>();

    } catch (const std::exception& e) {
        if (error) {
            *error = [NSError errorWithDomain:@"GuitarixBridge"
                                         code:1
                                     userInfo:@{NSLocalizedDescriptionKey:
                                         [NSString stringWithUTF8String:e.what()]}];
        }
        return nil;
    }
    return self;
}

// ── Audio I/O ─────────────────────────────────────────────────────────────────

- (BOOL)startAudioWithSampleRate:(double)sampleRate
                      bufferSize:(uint32_t)bufferSize
                           error:(NSError **)error
{
    // Use __weak to avoid a retain cycle in the C++ lambda.
    __weak GuitarixBridge *weakSelf = self;

    auto cb = [weakSelf](const float* inL, const float* /*inR*/,
                         float* outL, float* outR, uint32_t n)
    {
        GuitarixBridge *s = weakSelf;
        if (!s || !s->_machine) {
            memset(outL, 0, n * sizeof(float));
            memset(outR, 0, n * sizeof(float));
            return;
        }

        // Use a heap buffer — VLAs are non-standard in C++17.
        std::vector<float> monoOut(n, 0.0f);

        // mono_chain: guitar input → amp/pre-amp chain → mono out
        s->_machine->get_engine().mono_chain.process(
            static_cast<int>(n),
            inL ? inL : outL,
            monoOut.data()
        );

        // stereo_chain: mono fed to both inputs → stereo effect chain → L+R out
        s->_machine->get_engine().stereo_chain.process(
            static_cast<int>(n),
            monoOut.data(), monoOut.data(),
            outL, outR
        );
    };

    bool ok = _driver->open(cb, sampleRate, bufferSize);
    if (!ok) {
        if (error) {
            *error = [NSError errorWithDomain:@"GuitarixBridge"
                                         code:2
                                     userInfo:@{NSLocalizedDescriptionKey:
                                         @"Failed to open CoreAudio unit"}];
        }
        return NO;
    }

    // Tell the engine what sample rate we're running at.
    _machine->get_engine().set_samplerate(static_cast<unsigned int>(sampleRate));

    return YES;
}

- (void)stopAudio {
    _driver->close();
}

- (NSArray<GXAudioDevice *> *)availableInputDevices {
    NSMutableArray *arr = [NSMutableArray array];
    for (auto& d : CoreAudioDriver::listInputDevices()) {
        GXAudioDevice *dev = [[GXAudioDevice alloc] init];
        dev.name     = ns(d.name);
        dev.deviceId = d.deviceId;
        [arr addObject:dev];
    }
    return arr;
}

- (NSArray<GXAudioDevice *> *)availableOutputDevices {
    NSMutableArray *arr = [NSMutableArray array];
    for (auto& d : CoreAudioDriver::listOutputDevices()) {
        GXAudioDevice *dev = [[GXAudioDevice alloc] init];
        dev.name     = ns(d.name);
        dev.deviceId = d.deviceId;
        [arr addObject:dev];
    }
    return arr;
}

- (void)setInputDeviceId:(uint32_t)deviceId  { _driver->setInputDevice(deviceId);  }
- (void)setOutputDeviceId:(uint32_t)deviceId { _driver->setOutputDevice(deviceId); }

- (float)inputLevel    { return _driver->inputLevel();   }
- (float)outputLevelL  { return _driver->outputLevelL(); }
- (float)outputLevelR  { return _driver->outputLevelR(); }

// ── Engine state ──────────────────────────────────────────────────────────────

- (GXEngineState)engineState { return _engineState; }
- (void)setEngineState:(GXEngineState)state {
    _engineState = state;
    // GxEngineState is a plain enum in namespace gx_engine (not a scoped enum),
    // so values are unqualified after 'using namespace gx_engine'.
    switch (state) {
        case GXEngineStateOff:      _machine->set_state(kEngineOff);     break;
        case GXEngineStateBypassed: _machine->set_state(kEngineBypass);  break;
        case GXEngineStateOn:       _machine->set_state(kEngineOn);      break;
    }
}

// ── Amp / cabinet models ──────────────────────────────────────────────────────

- (NSArray<NSString *> *)ampModelIds {
    // Iterate the engine's plugin list — returns all registered DSP plugins.
    NSMutableArray *ids = [NSMutableArray array];
    PluginListBase& pl = _machine->get_pluginlist();
    for (auto it = pl.begin(); it != pl.end(); ++it) {
        Plugin *p = it->second;
        if (p && p->pdef) {
            [ids addObject:ns(p->pdef->id)];
        }
    }
    return ids;
}

- (NSString *)currentAmpModelId { return _currentAmpModelId; }
- (void)setCurrentAmpModelId:(NSString *)modelId {
    _currentAmpModelId = modelId;
    if (modelId.length > 0) {
        [self insertPlugin:modelId beforePlugin:nil];
    }
}

- (NSArray<NSString *> *)cabinetModelIds {
    return @[@"cabinet", @"cab_4x12", @"cab_2x12", @"cab_1x12", @"cab_1x8"];
}

- (NSString *)currentCabinetModelId { return _currentCabinetModelId; }
- (void)setCurrentCabinetModelId:(NSString *)modelId {
    _currentCabinetModelId = modelId;
}

// ── Parameters ────────────────────────────────────────────────────────────────

- (NSArray<NSString *> *)parameterIds {
    NSMutableArray *ids = [NSMutableArray array];
    ParamMap& pmap = _machine->get_parammap();
    for (auto it = pmap.begin(); it != pmap.end(); ++it) {
        [ids addObject:ns(it->first)];
    }
    return ids;
}

- (float)floatValueForParameterId:(NSString *)paramId {
    // Use the public template specialisation on GxMachineBase.
    return _machine->get_parameter_value<float>(cpp(paramId));
}

- (void)setFloatValue:(float)value forParameterId:(NSString *)paramId {
    _machine->set_parameter_value(cpp(paramId), value);
}

- (BOOL)boolValueForParameterId:(NSString *)paramId {
    return _machine->get_parameter_value<bool>(cpp(paramId)) ? YES : NO;
}

- (void)setBoolValue:(BOOL)value forParameterId:(NSString *)paramId {
    _machine->set_parameter_value(cpp(paramId), (bool)value);
}

- (void)rangeForParameterId:(NSString *)paramId min:(float *)outMin max:(float *)outMax {
    ParamMap& pmap = _machine->get_parammap();
    std::string cid = cpp(paramId);
    if (pmap.hasId(cid)) {
        Parameter& p = pmap[cid];
        if (p.isFloat()) {
            FloatParameter& fp = p.getFloat();
            if (outMin) *outMin = fp.get_lower();
            if (outMax) *outMax = fp.get_upper();
            return;
        }
    }
    if (outMin) *outMin = 0.f;
    if (outMax) *outMax = 1.f;
}

- (NSString *)labelForParameterId:(NSString *)paramId {
    ParamMap& pmap = _machine->get_parammap();
    std::string cid = cpp(paramId);
    if (pmap.hasId(cid)) return ns(pmap[cid].l_name());
    return paramId;
}

// ── Presets ───────────────────────────────────────────────────────────────────

- (NSArray<NSString *> *)presetBanks {
    NSMutableArray *banks = [NSMutableArray array];
    // Use GxMachine's bank_size() / get_bank_name() API — no need to reach
    // into settings.banks directly.
    int n = _machine->bank_size();
    for (int i = 0; i < n; ++i) {
        [banks addObject:ns(_machine->get_bank_name(i))];
    }
    return banks;
}

- (NSArray<GXPreset *> *)presetsInBank:(NSString *)bank {
    NSMutableArray *presets = [NSMutableArray array];
    gx_system::PresetFileGui *pf =
        _machine->get_bank_file(Glib::ustring(cpp(bank)));
    if (!pf) return presets;

    for (int i = 0; i < pf->size(); ++i) {
        GXPreset *p = [[GXPreset alloc] init];
        p.name = ns(pf->get_name(i));
        p.bank = bank;
        [presets addObject:p];
    }
    return presets;
}

- (void)loadPreset:(GXPreset *)preset {
    // GxMachineBase::load_preset takes a PresetFileGui* and a preset name.
    gx_system::PresetFileGui *pf =
        _machine->get_bank_file(Glib::ustring(cpp(preset.bank)));
    if (pf) {
        _machine->load_preset(pf, Glib::ustring(cpp(preset.name)));
    }
}

- (void)saveCurrentPresetAs:(NSString *)name inBank:(NSString *)bank {
    // GxSettingsBase::save takes PresetFile& (not PresetFileGui&).
    // settings.banks.get_file() returns PresetFile* so no private-inheritance
    // cast is needed. GxSettings makes banks public via 'using GxSettingsBase::banks'.
    gx_preset::GxSettings& settings = _machine->get_settings();
    gx_system::PresetFile *pf = settings.banks.get_file(Glib::ustring(cpp(bank)));
    if (pf) {
        settings.save(*pf, Glib::ustring(cpp(name)));
    }
}

- (void)deletePreset:(GXPreset *)preset {
    gx_system::PresetFileGui *pf =
        _machine->get_bank_file(Glib::ustring(cpp(preset.bank)));
    if (pf) {
        // GxMachineBase::erase_preset takes a PresetFileGui& (not pointer).
        _machine->erase_preset(*pf, Glib::ustring(cpp(preset.name)));
    }
}

// ── Effect rack ───────────────────────────────────────────────────────────────

- (NSArray<NSString *> *)monoChainPluginIds {
    NSMutableArray *ids = [NSMutableArray array];
    const std::vector<std::string>& order =
        _machine->get_rack_unit_order(PLUGIN_TYPE_MONO);
    for (auto& s : order) [ids addObject:ns(s)];
    return ids;
}

- (NSArray<NSString *> *)stereoChainPluginIds {
    NSMutableArray *ids = [NSMutableArray array];
    const std::vector<std::string>& order =
        _machine->get_rack_unit_order(PLUGIN_TYPE_STEREO);
    for (auto& s : order) [ids addObject:ns(s)];
    return ids;
}

- (void)insertPlugin:(NSString *)pluginId beforePlugin:(nullable NSString *)beforeId {
    _machine->insert_rack_unit(cpp(pluginId), cpp(beforeId), PLUGIN_TYPE_MONO);
}

- (void)removePlugin:(NSString *)pluginId {
    _machine->remove_rack_unit(cpp(pluginId), PLUGIN_TYPE_MONO);
}

- (void)movePlugin:(NSString *)pluginId beforePlugin:(nullable NSString *)beforeId {
    _machine->remove_rack_unit(cpp(pluginId), PLUGIN_TYPE_MONO);
    _machine->insert_rack_unit(cpp(pluginId), cpp(beforeId), PLUGIN_TYPE_MONO);
}

// ── Tuner ─────────────────────────────────────────────────────────────────────

- (BOOL)tunerEnabled { return _tunerEnabled; }
- (void)setTunerEnabled:(BOOL)on {
    _tunerEnabled = on;
    _machine->tuner_used_for_display(on);
    _machine->tuner_switch(on);
}

- (float)tunerFrequency {
    return _machine->get_tuner_freq();
}

- (NSString *)tunerNoteName {
    float note = _machine->get_tuner_note();
    if (note <= 0.f) return @"";
    static const char* names[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    int midi   = static_cast<int>(std::round(note));
    int octave = (midi / 12) - 1;
    return [NSString stringWithFormat:@"%s%d", names[midi % 12], octave];
}

- (float)tunerCents {
    float freq = _machine->get_tuner_freq();
    if (freq <= 0.f) return 0.f;
    float note = _machine->get_tuner_note();
    if (note <= 0.f) return 0.f;
    float refFreq = 440.f * std::pow(2.f, (note - 69.f) / 12.f);
    return 1200.f * std::log2f(freq / refFreq);
}

@end
