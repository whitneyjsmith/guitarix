// GuitarixBridge.h
// Pure Objective-C interface — importable from Swift without any C++ headers.
// The .mm implementation calls into GxMachine and CoreAudioDriver.

#pragma once
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// ── Preset ────────────────────────────────────────────────────────────────────

@interface GXPreset : NSObject
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *bank;
@end

// ── Audio device info ─────────────────────────────────────────────────────────

@interface GXAudioDevice : NSObject
@property (nonatomic, copy)   NSString *name;
@property (nonatomic, assign) uint32_t  deviceId;
@end

// ── Engine state ──────────────────────────────────────────────────────────────

typedef NS_ENUM(NSInteger, GXEngineState) {
    GXEngineStateOff    = 0,
    GXEngineStateBypassed,
    GXEngineStateOn,
};

// ── Main bridge ───────────────────────────────────────────────────────────────

@interface GuitarixBridge : NSObject

/// Initialise engine + CoreAudio. Returns nil and sets error on failure.
- (nullable instancetype)initWithError:(NSError **)error;

// ── Audio I/O ─────────────────────────────────────────────────────────────────

- (BOOL)startAudioWithSampleRate:(double)sampleRate
                      bufferSize:(uint32_t)bufferSize
                           error:(NSError **)error;
- (void)stopAudio;

- (NSArray<GXAudioDevice *> *)availableInputDevices;
- (NSArray<GXAudioDevice *> *)availableOutputDevices;
- (void)setInputDeviceId:(uint32_t)deviceId;
- (void)setOutputDeviceId:(uint32_t)deviceId;

/// Live metering — call from a display-link / timer on the main thread.
@property (nonatomic, readonly) float inputLevel;     // 0..1
@property (nonatomic, readonly) float outputLevelL;
@property (nonatomic, readonly) float outputLevelR;

// ── Engine state ──────────────────────────────────────────────────────────────

@property (nonatomic, assign) GXEngineState engineState;

// ── Amp & cabinet models ──────────────────────────────────────────────────────

/// All amp model ids registered in the engine.
- (NSArray<NSString *> *)ampModelIds;

/// Currently active amp model (empty string = none).
@property (nonatomic, copy) NSString *currentAmpModelId;

/// All cabinet model ids.
- (NSArray<NSString *> *)cabinetModelIds;
@property (nonatomic, copy) NSString *currentCabinetModelId;

// ── Parameters ────────────────────────────────────────────────────────────────

/// All parameter ids (e.g. "amp.gain", "tube.bias").
- (NSArray<NSString *> *)parameterIds;

- (float)floatValueForParameterId:(NSString *)paramId;
- (void)setFloatValue:(float)value forParameterId:(NSString *)paramId;

- (BOOL)boolValueForParameterId:(NSString *)paramId;
- (void)setBoolValue:(BOOL)value forParameterId:(NSString *)paramId;

/// Min/max range for a float parameter.
- (void)rangeForParameterId:(NSString *)paramId min:(float *)outMin max:(float *)outMax;

/// Human-readable label for a parameter id.
- (NSString *)labelForParameterId:(NSString *)paramId;

// ── Presets ───────────────────────────────────────────────────────────────────

- (NSArray<NSString *> *)presetBanks;
- (NSArray<GXPreset *> *)presetsInBank:(NSString *)bank;
- (void)loadPreset:(GXPreset *)preset;
- (void)saveCurrentPresetAs:(NSString *)name inBank:(NSString *)bank;
- (void)deletePreset:(GXPreset *)preset;

// ── Active effect rack ────────────────────────────────────────────────────────

/// Ordered list of active plugin ids in the mono chain.
- (NSArray<NSString *> *)monoChainPluginIds;
/// Ordered list in the stereo chain.
- (NSArray<NSString *> *)stereoChainPluginIds;

- (void)insertPlugin:(NSString *)pluginId beforePlugin:(nullable NSString *)beforeId;
- (void)removePlugin:(NSString *)pluginId;
- (void)movePlugin:(NSString *)pluginId beforePlugin:(nullable NSString *)beforeId;

// ── Tuner ─────────────────────────────────────────────────────────────────────

@property (nonatomic, assign) BOOL tunerEnabled;
/// Current detected frequency in Hz. 0 if not tracking.
@property (nonatomic, readonly) float tunerFrequency;
/// Detected note name (e.g. "E2"). Empty if not tracking.
@property (nonatomic, readonly) NSString *tunerNoteName;
/// Cents deviation from the detected note (-50..+50).
@property (nonatomic, readonly) float tunerCents;

@end

NS_ASSUME_NONNULL_END
