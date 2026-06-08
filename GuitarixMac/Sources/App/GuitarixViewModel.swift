import Foundation
import Combine

// GuitarixViewModel owns the bridge and drives the SwiftUI layer.
// All published properties are updated on the main thread.

@MainActor
final class GuitarixViewModel: ObservableObject {

    // ── Engine & audio ────────────────────────────────────────────────────────
    @Published var isRunning    = false
    @Published var bypassed     = false { didSet { applyBypass() } }
    @Published var errorMessage: String? = nil

    // ── Tuner ─────────────────────────────────────────────────────────────────
    @Published var tunerEnabled  = false { didSet { bridge?.tunerEnabled = tunerEnabled } }
    @Published var tunerFreq: Float     = 0
    @Published var tunerNote: String    = ""
    @Published var tunerCents: Float    = 0

    // ── Level meters ──────────────────────────────────────────────────────────
    @Published var inputLevel:   Float  = 0
    @Published var outputLevelL: Float  = 0
    @Published var outputLevelR: Float  = 0

    // ── Amp / cabinet ─────────────────────────────────────────────────────────
    @Published var ampModels: [String]     = []
    @Published var selectedAmpModel        = "" { didSet { bridge?.currentAmpModelId = selectedAmpModel } }
    @Published var cabinetModels: [String] = []
    @Published var selectedCabinet         = "" { didSet { bridge?.currentCabinetModelId = selectedCabinet } }

    // ── Effect rack ───────────────────────────────────────────────────────────
    @Published var monoChain:   [String] = []
    @Published var stereoChain: [String] = []

    // ── Presets ───────────────────────────────────────────────────────────────
    @Published var presetBanks:     [String]    = []
    @Published var presetsInBank:   [GXPreset]  = []
    @Published var selectedBank     = "" { didSet { loadBankPresets() } }

    // ── Audio device selection ────────────────────────────────────────────────
    @Published var inputDevices:  [GXAudioDevice] = []
    @Published var outputDevices: [GXAudioDevice] = []
    @Published var selectedInputDeviceId:  UInt32 = 0
    @Published var selectedOutputDeviceId: UInt32 = 0

    // ── Private ───────────────────────────────────────────────────────────────
    private var bridge: GuitarixBridge?
    private var meterTimer: Timer?
    private var sampleRate: Double = 44100
    private var bufferSize: UInt32 = 256

    // ── Lifecycle ─────────────────────────────────────────────────────────────

    init() {
        var err: NSError?
        guard let b = GuitarixBridge(error: &err) else {
            errorMessage = err?.localizedDescription ?? "Failed to initialise engine"
            return
        }
        bridge = b

        ampModels     = (b.ampModelIds()     as! [String])
        cabinetModels = (b.cabinetModelIds() as! [String])
        presetBanks   = (b.presetBanks()     as! [String])
        inputDevices  = (b.availableInputDevices()  as! [GXAudioDevice])
        outputDevices = (b.availableOutputDevices() as! [GXAudioDevice])

        if let first = presetBanks.first { selectedBank = first }
        reloadChains()
    }

    // ── Audio control ─────────────────────────────────────────────────────────

    func startAudio() {
        guard let b = bridge else { return }
        b.setInputDeviceId(selectedInputDeviceId)
        b.setOutputDeviceId(selectedOutputDeviceId)

        var err: NSError?
        guard b.startAudio(withSampleRate: sampleRate, bufferSize: bufferSize, error: &err) else {
            errorMessage = err?.localizedDescription ?? "Audio start failed"
            return
        }
        b.engineState = .on
        isRunning = true
        startMeterTimer()
    }

    func stopAudio() {
        bridge?.stopAudio()
        isRunning = false
        stopMeterTimer()
    }

    private func applyBypass() {
        bridge?.engineState = bypassed ? .bypassed : .on
    }

    // ── Meter polling (30 fps) ────────────────────────────────────────────────

    private func startMeterTimer() {
        meterTimer = Timer.scheduledTimer(withTimeInterval: 1.0/30, repeats: true) { [weak self] _ in
            Task { @MainActor [weak self] in self?.pollMeters() }
        }
    }

    private func stopMeterTimer() {
        meterTimer?.invalidate()
        meterTimer = nil
    }

    private func pollMeters() {
        guard let b = bridge else { return }
        inputLevel   = b.inputLevel
        outputLevelL = b.outputLevelL
        outputLevelR = b.outputLevelR
        if tunerEnabled {
            tunerFreq  = b.tunerFrequency
            tunerNote  = b.tunerNoteName
            tunerCents = b.tunerCents
        }
    }

    // ── Presets ───────────────────────────────────────────────────────────────

    private func loadBankPresets() {
        guard let b = bridge else { return }
        presetsInBank = (b.presets(inBank: selectedBank) as! [GXPreset])
    }

    func loadPreset(_ preset: GXPreset) {
        bridge?.load(preset)
        reloadChains()
    }

    func saveCurrentPreset(name: String) {
        bridge?.saveCurrentPreset(as: name, inBank: selectedBank)
        loadBankPresets()
    }

    // ── Effect rack ───────────────────────────────────────────────────────────

    func reloadChains() {
        guard let b = bridge else { return }
        monoChain   = (b.monoChainPluginIds()   as! [String])
        stereoChain = (b.stereoChainPluginIds() as! [String])
    }

    func addEffect(_ id: String) {
        bridge?.insertPlugin(id, beforePlugin: nil)
        reloadChains()
    }

    func removeEffect(_ id: String) {
        bridge?.removePlugin(id)
        reloadChains()
    }

    // ── Parameter access (passthrough to bridge) ──────────────────────────────

    func floatValue(for paramId: String) -> Float {
        bridge?.floatValue(forParameterId: paramId) ?? 0
    }

    func setFloat(_ value: Float, for paramId: String) {
        bridge?.setFloatValue(value, forParameterId: paramId)
    }

    func range(for paramId: String) -> ClosedRange<Float> {
        var lo: Float = 0, hi: Float = 1
        bridge?.range(forParameterId: paramId, min: &lo, max: &hi)
        return lo...hi
    }

    func label(for paramId: String) -> String {
        (bridge?.label(forParameterId: paramId) ?? paramId) as String
    }
}
