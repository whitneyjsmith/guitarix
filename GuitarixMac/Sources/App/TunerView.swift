import SwiftUI

struct TunerView: View {
    @EnvironmentObject var vm: GuitarixViewModel

    var body: some View {
        VStack(spacing: 24) {
            Spacer()

            // ── Enable toggle ─────────────────────────────────────────────
            Toggle("Enable Tuner", isOn: $vm.tunerEnabled)
                .toggleStyle(.switch)
                .tint(.orange)

            if vm.tunerEnabled {
                // ── Note display ──────────────────────────────────────────
                VStack(spacing: 8) {
                    Text(vm.tunerNote.isEmpty ? "–" : vm.tunerNote)
                        .font(.system(size: 72, weight: .bold, design: .monospaced))
                        .foregroundStyle(noteColor)
                        .animation(.easeInOut(duration: 0.1), value: vm.tunerNote)

                    Text(vm.tunerFreq > 0
                         ? String(format: "%.1f Hz", vm.tunerFreq)
                         : "")
                        .font(.caption)
                        .foregroundStyle(.secondary)
                }

                // ── Cents deviation needle ────────────────────────────────
                CentsNeedleView(cents: vm.tunerCents)
                    .frame(width: 320, height: 80)
            } else {
                Text("Enable the tuner to detect pitch.")
                    .foregroundStyle(.secondary)
            }

            Spacer()
        }
        .frame(maxWidth: .infinity)
    }

    private var noteColor: Color {
        let c = abs(vm.tunerCents)
        if c < 5   { return .green  }
        if c < 15  { return .yellow }
        return .red
    }
}

struct CentsNeedleView: View {
    let cents: Float    // -50 … +50

    var body: some View {
        GeometryReader { geo in
            let w = geo.size.width
            let h = geo.size.height
            let mid = w / 2
            let clamped = Double(max(-50, min(50, cents)))
            let x = mid + clamped / 50.0 * (w * 0.45)

            ZStack(alignment: .leading) {
                // Scale markings
                ForEach([-50, -25, 0, 25, 50], id: \.self) { c in
                    let xPos = mid + Double(c) / 50.0 * (w * 0.45)
                    Rectangle()
                        .frame(width: 2, height: c == 0 ? h * 0.6 : h * 0.35)
                        .foregroundStyle(c == 0 ? Color.white.opacity(0.6) : Color.white.opacity(0.25))
                        .position(x: xPos, y: h * 0.5)
                }

                // Needle
                Rectangle()
                    .frame(width: 3, height: h * 0.8)
                    .foregroundStyle(needleColor)
                    .cornerRadius(2)
                    .shadow(color: needleColor.opacity(0.7), radius: 6)
                    .position(x: x, y: h * 0.5)
                    .animation(.spring(response: 0.12, dampingFraction: 0.6), value: cents)
            }
            .background(Color.white.opacity(0.05))
            .clipShape(RoundedRectangle(cornerRadius: 8))
        }
    }

    private var needleColor: Color {
        let c = abs(cents)
        if c < 5  { return .green  }
        if c < 15 { return .yellow }
        return .red
    }
}
