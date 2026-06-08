import SwiftUI

struct EffectRackView: View {
    @EnvironmentObject var vm: GuitarixViewModel
    @State private var showingEffectPicker = false

    // Commonly used effects — the bridge exposes all available plugin ids,
    // here we show a curated palette for quick access.
    private let palette: [(group: String, ids: [String])] = [
        ("Dynamics",   ["compressor", "noise_gate"]),
        ("Drive",      ["tube_screamer", "distortion", "fuzz", "overdrive"]),
        ("Modulation", ["chorus", "flanger", "phaser", "tremolo"]),
        ("Time",       ["delay", "digital_delay", "reverb"]),
        ("EQ / Filter",["graphic_eq", "parametric_eq", "tone_control", "wah"]),
    ]

    var body: some View {
        VStack(spacing: 0) {
            // ── Mono chain ────────────────────────────────────────────────
            chainSection(title: "Mono Chain (pre-amp)", ids: vm.monoChain, isMono: true)

            Divider().background(.white.opacity(0.1))

            // ── Stereo chain ──────────────────────────────────────────────
            chainSection(title: "Stereo Chain (post-amp)", ids: vm.stereoChain, isMono: false)

            Spacer()

            // ── Add effects bar ───────────────────────────────────────────
            HStack {
                Spacer()
                Button {
                    showingEffectPicker = true
                } label: {
                    Label("Add Effect", systemImage: "plus.circle.fill")
                        .font(.callout)
                }
                .buttonStyle(.borderedProminent)
                .tint(.orange)
                .padding()
            }
        }
        .popover(isPresented: $showingEffectPicker) {
            EffectPickerView { id in
                vm.addEffect(id)
                showingEffectPicker = false
            }
        }
    }

    @ViewBuilder
    private func chainSection(title: String, ids: [String], isMono: Bool) -> some View {
        VStack(alignment: .leading, spacing: 8) {
            Text(title)
                .font(.caption)
                .foregroundStyle(.secondary)
                .padding(.horizontal, 16)
                .padding(.top, 12)

            if ids.isEmpty {
                Text("No effects — tap Add Effect to insert one")
                    .font(.caption)
                    .foregroundStyle(.tertiary)
                    .padding(.horizontal, 16)
                    .padding(.bottom, 12)
            } else {
                ScrollView(.horizontal, showsIndicators: false) {
                    HStack(spacing: 12) {
                        ForEach(ids, id: \.self) { id in
                            EffectModuleView(
                                pluginId: id,
                                onRemove: { vm.removeEffect(id) }
                            )
                        }
                    }
                    .padding(.horizontal, 16)
                    .padding(.bottom, 12)
                }
            }
        }
        .frame(minHeight: 160)
    }
}

// ── Effect module tile ────────────────────────────────────────────────────────

struct EffectModuleView: View {
    @EnvironmentObject var vm: GuitarixViewModel
    let pluginId: String
    let onRemove: () -> Void
    @State private var isExpanded = false

    var body: some View {
        VStack(spacing: 0) {
            // Header
            HStack {
                Text(pluginId.replacingOccurrences(of: "_", with: " ").capitalized)
                    .font(.caption.bold())
                    .foregroundStyle(.white)
                Spacer()
                Button(action: { isExpanded.toggle() }) {
                    Image(systemName: isExpanded ? "chevron.up" : "chevron.down")
                        .font(.caption2)
                }
                .buttonStyle(.plain)
                .foregroundStyle(.secondary)
                Button(action: onRemove) {
                    Image(systemName: "xmark")
                        .font(.caption2)
                }
                .buttonStyle(.plain)
                .foregroundStyle(.red.opacity(0.7))
            }
            .padding(.horizontal, 10)
            .padding(.vertical, 8)
            .background(Color.orange.opacity(0.2))

            if isExpanded {
                // Show knobs for the first few float parameters matching this plugin
                let params = effectParams(for: pluginId)
                if params.isEmpty {
                    Text("No parameters")
                        .font(.caption2)
                        .foregroundStyle(.secondary)
                        .padding(10)
                } else {
                    HStack(spacing: 14) {
                        ForEach(params.prefix(4), id: \.self) { paramId in
                            KnobView(paramId: paramId)
                        }
                    }
                    .padding(10)
                }
            }
        }
        .frame(width: isExpanded ? 280 : 140)
        .background(Color.white.opacity(0.06))
        .clipShape(RoundedRectangle(cornerRadius: 10))
        .overlay(
            RoundedRectangle(cornerRadius: 10)
                .stroke(Color.white.opacity(0.1), lineWidth: 1)
        )
        .animation(.spring(response: 0.25), value: isExpanded)
    }

    private func effectParams(for id: String) -> [String] {
        vm.parameterIds(for: id)
    }
}

// ── Knob ──────────────────────────────────────────────────────────────────────

struct KnobView: View {
    @EnvironmentObject var vm: GuitarixViewModel
    let paramId: String

    @State private var dragStart: CGFloat = 0
    @State private var valueAtDragStart: Float = 0

    var body: some View {
        VStack(spacing: 4) {
            ZStack {
                Circle()
                    .stroke(Color.white.opacity(0.15), lineWidth: 3)
                    .frame(width: 44, height: 44)
                Circle()
                    .trim(from: 0.1, to: normalised * 0.8 + 0.1)
                    .stroke(Color.orange, style: StrokeStyle(lineWidth: 3, lineCap: .round))
                    .frame(width: 44, height: 44)
                    .rotationEffect(.degrees(-90))
                Text(String(format: "%.1f", value))
                    .font(.system(size: 9, design: .monospaced))
                    .foregroundStyle(.white)
            }
            .gesture(DragGesture(minimumDistance: 0)
                .onChanged { g in
                    if g.translation.height == 0 { // first event
                        dragStart = g.location.y
                        valueAtDragStart = value
                    }
                    let delta = Float(dragStart - g.location.y) / 120.0
                    let range = vm.range(for: paramId)
                    let newVal = (valueAtDragStart + delta * (range.upperBound - range.lowerBound))
                        .clamped(to: range)
                    vm.setFloat(newVal, for: paramId)
                }
            )

            Text(vm.label(for: paramId).components(separatedBy: ".").last ?? paramId)
                .font(.system(size: 9))
                .foregroundStyle(.secondary)
                .lineLimit(1)
        }
    }

    private var value: Float      { vm.floatValue(for: paramId) }
    private var normalised: Double {
        let r = vm.range(for: paramId)
        guard r.upperBound > r.lowerBound else { return 0 }
        return Double((value - r.lowerBound) / (r.upperBound - r.lowerBound))
    }
}

// ── Effect picker popover ─────────────────────────────────────────────────────

struct EffectPickerView: View {
    let onSelect: (String) -> Void

    private let categories: [(group: String, ids: [String])] = [
        ("Dynamics",   ["compressor", "noise_gate"]),
        ("Drive",      ["tube_screamer", "distortion", "fuzz", "overdrive"]),
        ("Modulation", ["chorus", "flanger", "phaser", "tremolo"]),
        ("Time",       ["delay", "digital_delay", "reverb"]),
        ("EQ",         ["graphic_eq", "parametric_eq", "tone_control"]),
    ]

    var body: some View {
        VStack(alignment: .leading, spacing: 0) {
            Text("Add Effect")
                .font(.headline)
                .padding()

            Divider()

            ScrollView {
                ForEach(categories, id: \.group) { cat in
                    Section {
                        ForEach(cat.ids, id: \.self) { id in
                            Button {
                                onSelect(id)
                            } label: {
                                HStack {
                                    Text(id.replacingOccurrences(of: "_", with: " ").capitalized)
                                    Spacer()
                                    Image(systemName: "plus")
                                }
                                .contentShape(Rectangle())
                                .padding(.horizontal)
                                .padding(.vertical, 8)
                            }
                            .buttonStyle(.plain)
                        }
                    } header: {
                        Text(cat.group)
                            .font(.caption.bold())
                            .foregroundStyle(.secondary)
                            .padding(.horizontal)
                            .padding(.top, 10)
                    }
                }
            }
        }
        .frame(width: 260, height: 380)
    }
}

// ── GuitarixViewModel extension ───────────────────────────────────────────────

extension GuitarixViewModel {
    /// Returns parameter ids that belong to a specific plugin, by prefix matching.
    func parameterIds(for pluginId: String) -> [String] {
        // Guitarix parameter ids use the pattern "pluginId.paramName"
        guard let b = Mirror(reflecting: self).children
            .first(where: { $0.label == "bridge" })?.value as? GuitarixBridge
        else { return [] }
        return (b.parameterIds() as! [String]).filter { $0.hasPrefix(pluginId + ".") }
    }
}

// ── Clamp helper ──────────────────────────────────────────────────────────────

extension Comparable {
    func clamped(to range: ClosedRange<Self>) -> Self {
        min(max(self, range.lowerBound), range.upperBound)
    }
}
