import SwiftUI

struct AudioSettingsView: View {
    @EnvironmentObject var vm: GuitarixViewModel

    private let sampleRates: [Double] = [44100, 48000, 88200, 96000]
    private let bufferSizes: [UInt32] = [64, 128, 256, 512]

    @State private var sampleRate: Double = 44100
    @State private var bufferSize: UInt32 = 256

    var body: some View {
        Form {
            Section("Audio Input") {
                Picker("Input Device", selection: $vm.selectedInputDeviceId) {
                    Text("System Default").tag(UInt32(0))
                    ForEach(vm.inputDevices, id: \.deviceId) { dev in
                        Text(dev.name).tag(dev.deviceId)
                    }
                }

                Picker("Sample Rate", selection: $sampleRate) {
                    ForEach(sampleRates, id: \.self) { sr in
                        Text("\(Int(sr)) Hz").tag(sr)
                    }
                }

                Picker("Buffer Size", selection: $bufferSize) {
                    ForEach(bufferSizes, id: \.self) { bs in
                        Text("\(bs) frames  (~\(latencyMs(bs, sampleRate)) ms)").tag(bs)
                    }
                }
            }

            Section("Audio Output") {
                Picker("Output Device", selection: $vm.selectedOutputDeviceId) {
                    Text("System Default").tag(UInt32(0))
                    ForEach(vm.outputDevices, id: \.deviceId) { dev in
                        Text(dev.name).tag(dev.deviceId)
                    }
                }
            }

            Section("Engine") {
                LabeledContent("Status") {
                    HStack(spacing: 6) {
                        Circle()
                            .fill(vm.isRunning ? Color.green : Color.red)
                            .frame(width: 8, height: 8)
                        Text(vm.isRunning ? "Running" : "Stopped")
                            .foregroundStyle(.secondary)
                    }
                }

                if vm.isRunning {
                    LabeledContent("Sample Rate") {
                        Text("\(Int(vm.activeSampleRate)) Hz")
                    }
                    LabeledContent("Buffer Size") {
                        Text("\(vm.activeBufferSize) frames")
                    }
                    LabeledContent("Latency") {
                        Text(latencyMs(vm.activeBufferSize, vm.activeSampleRate))
                    }
                }
            }

            Section {
                HStack {
                    Spacer()
                    if vm.isRunning {
                        Button("Restart Audio") {
                            vm.stopAudio()
                            vm.startAudio()
                        }
                        .buttonStyle(.borderedProminent)
                        .tint(.orange)
                    } else {
                        Button("Start Audio") {
                            vm.startAudio()
                        }
                        .buttonStyle(.borderedProminent)
                        .tint(.green)
                    }
                    Spacer()
                }
            }
        }
        .formStyle(.grouped)
        .frame(maxWidth: 560)
        .padding()
    }

    private func latencyMs(_ bufSize: UInt32, _ sr: Double) -> String {
        String(format: "%.1f ms", Double(bufSize) / sr * 1000.0)
    }
}

// ── GuitarixViewModel extension ───────────────────────────────────────────────

extension GuitarixViewModel {
    var activeSampleRate: Double { bridge?.value(forKey: "sampleRate") as? Double ?? 44100 }
    var activeBufferSize: UInt32 { 256 }   // TODO: expose from bridge if needed
}
