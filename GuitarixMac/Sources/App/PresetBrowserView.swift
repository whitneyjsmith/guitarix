import SwiftUI

struct PresetBrowserView: View {
    @EnvironmentObject var vm: GuitarixViewModel
    @State private var savePresetName = ""
    @State private var showingSaveSheet = false
    @State private var searchText = ""

    var body: some View {
        VStack(spacing: 0) {
            // ── Bank picker ───────────────────────────────────────────────
            Picker("Bank", selection: $vm.selectedBank) {
                ForEach(vm.presetBanks, id: \.self) { bank in
                    Text(bank).tag(bank)
                }
            }
            .labelsHidden()
            .padding(8)

            // ── Search ────────────────────────────────────────────────────
            TextField("Search presets…", text: $searchText)
                .textFieldStyle(.roundedBorder)
                .padding(.horizontal, 8)
                .padding(.bottom, 6)

            Divider()

            // ── Preset list ───────────────────────────────────────────────
            List(filteredPresets, id: \.name) { preset in
                PresetRow(preset: preset)
                    .onTapGesture { vm.loadPreset(preset) }
                    .contextMenu {
                        Button("Delete", role: .destructive) {
                            // TODO: call vm.deletePreset(preset)
                        }
                    }
            }
            .listStyle(.sidebar)

            Divider()

            // ── Save button ───────────────────────────────────────────────
            Button {
                showingSaveSheet = true
            } label: {
                Label("Save Preset", systemImage: "square.and.arrow.down")
                    .font(.callout)
                    .frame(maxWidth: .infinity)
            }
            .buttonStyle(.borderedProminent)
            .tint(.orange)
            .padding(10)
        }
        .navigationTitle("Presets")
        .sheet(isPresented: $showingSaveSheet) {
            SavePresetSheet(isPresented: $showingSaveSheet)
        }
    }

    private var filteredPresets: [GXPreset] {
        if searchText.isEmpty { return vm.presetsInBank }
        return vm.presetsInBank.filter {
            $0.name.localizedCaseInsensitiveContains(searchText)
        }
    }
}

struct PresetRow: View {
    let preset: GXPreset

    var body: some View {
        HStack {
            Image(systemName: "music.note.list")
                .foregroundStyle(.orange)
                .font(.callout)
            Text(preset.name)
                .font(.callout)
        }
        .padding(.vertical, 2)
    }
}

struct SavePresetSheet: View {
    @EnvironmentObject var vm: GuitarixViewModel
    @Binding var isPresented: Bool
    @State private var name = ""

    var body: some View {
        VStack(spacing: 16) {
            Text("Save Preset")
                .font(.headline)
            TextField("Preset name", text: $name)
                .textFieldStyle(.roundedBorder)
                .frame(width: 250)
            HStack {
                Button("Cancel") { isPresented = false }
                    .keyboardShortcut(.cancelAction)
                Button("Save") {
                    if !name.isEmpty {
                        vm.saveCurrentPreset(name: name)
                        isPresented = false
                    }
                }
                .keyboardShortcut(.defaultAction)
                .buttonStyle(.borderedProminent)
                .tint(.orange)
            }
        }
        .padding(24)
        .frame(width: 320)
    }
}
