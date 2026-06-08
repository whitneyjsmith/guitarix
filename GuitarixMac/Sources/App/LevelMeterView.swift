import SwiftUI

struct LevelMeterView: View {
    @Binding var level: Float
    let label: String
    let color: Color

    var body: some View {
        VStack(spacing: 2) {
            // Vertical bar
            GeometryReader { geo in
                ZStack(alignment: .bottom) {
                    Capsule()
                        .fill(Color.white.opacity(0.07))
                    Capsule()
                        .fill(barGradient)
                        .frame(height: geo.size.height * CGFloat(clampedLevel))
                        .animation(.linear(duration: 0.03), value: level)
                }
            }
            .frame(width: 8, height: 32)

            Text(label)
                .font(.system(size: 8, design: .monospaced))
                .foregroundStyle(.secondary)
        }
    }

    private var clampedLevel: Float { max(0, min(1, level)) }

    private var barGradient: LinearGradient {
        LinearGradient(
            stops: [
                .init(color: color.opacity(0.6), location: 0),
                .init(color: color,              location: 0.7),
                .init(color: .red,               location: 1.0),
            ],
            startPoint: .bottom,
            endPoint: .top
        )
    }
}

// ── Stereo pair convenience ───────────────────────────────────────────────────

struct StereoMeterView: View {
    @Binding var levelL: Float
    @Binding var levelR: Float

    var body: some View {
        HStack(spacing: 3) {
            LevelMeterView(level: $levelL, label: "L", color: .green)
            LevelMeterView(level: $levelR, label: "R", color: .green)
        }
    }
}
