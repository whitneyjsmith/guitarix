import SwiftUI

struct ContentView: View {
    @EnvironmentObject var vm: GuitarixViewModel
    @State private var selectedTab: AppTab = .amp

    enum AppTab: String, CaseIterable {
        case amp      = "Amp"
        case effects  = "Effects"
        case tuner    = "Tuner"
        case settings = "Settings"

        var icon: String {
            switch self {
            case .amp:      return "speaker.wave.3.fill"
            case .effects:  return "slider.horizontal.3"
            case .tuner:    return "music.note"
            case .settings: return "gearshape.fill"
            }
        }
    }

    var body: some View {
        NavigationSplitView {
            // ── Left sidebar: preset browser ──────────────────────────────
            PresetBrowserView()
                .navigationSplitViewColumnWidth(min: 200, ideal: 220)
        } detail: {
            VStack(spacing: 0) {
                // ── Header bar ─────────────────────────────────────────────
                headerBar

                // ── Main content tabs ──────────────────────────────────────
                TabView(selection: $selectedTab) {
                    AmpSelectorView()
                        .tabItem { Label(AppTab.amp.rawValue, systemImage: AppTab.amp.icon) }
                        .tag(AppTab.amp)

                    EffectRackView()
                        .tabItem { Label(AppTab.effects.rawValue, systemImage: AppTab.effects.icon) }
                        .tag(AppTab.effects)

                    TunerView()
                        .tabItem { Label(AppTab.tuner.rawValue, systemImage: AppTab.tuner.icon) }
                        .tag(AppTab.tuner)

                    AudioSettingsView()
                        .tabItem { Label(AppTab.settings.rawValue, systemImage: AppTab.settings.icon) }
                        .tag(AppTab.settings)
                }
            }
            .background(Color(red: 0.12, green: 0.12, blue: 0.14))
        }
        .alert("Engine Error", isPresented: .constant(vm.errorMessage != nil)) {
            Button("OK") { vm.errorMessage = nil }
        } message: {
            Text(vm.errorMessage ?? "")
        }
    }

    // ── Header bar ────────────────────────────────────────────────────────────

    private var headerBar: some View {
        HStack(spacing: 16) {
            // Logo / title
            HStack(spacing: 6) {
                Image(systemName: "waveform.circle.fill")
                    .font(.title2)
                    .foregroundStyle(.orange)
                Text("Guitarix")
                    .font(.headline)
                    .foregroundStyle(.white)
            }

            Spacer()

            // Transport
            Button {
                vm.isRunning ? vm.stopAudio() : vm.startAudio()
            } label: {
                Label(vm.isRunning ? "Stop" : "Start",
                      systemImage: vm.isRunning ? "stop.circle.fill" : "play.circle.fill")
                    .foregroundStyle(vm.isRunning ? .red : .green)
            }
            .buttonStyle(.plain)

            // Bypass toggle
            Toggle(isOn: $vm.bypassed) {
                Label("Bypass", systemImage: "bolt.slash")
            }
            .toggleStyle(.button)
            .tint(.orange)
            .controlSize(.small)

            // Level meters
            HStack(spacing: 4) {
                LevelMeterView(level: $vm.inputLevel,   label: "IN",  color: .cyan)
                LevelMeterView(level: $vm.outputLevelL, label: "L",   color: .green)
                LevelMeterView(level: $vm.outputLevelR, label: "R",   color: .green)
            }
        }
        .padding(.horizontal, 16)
        .padding(.vertical, 10)
        .background(.ultraThinMaterial)
    }
}

// ── Preview ───────────────────────────────────────────────────────────────────

#Preview {
    ContentView()
        .environmentObject(GuitarixViewModel())
}
