import SwiftUI

struct AmpSelectorView: View {
    @EnvironmentObject var vm: GuitarixViewModel

    // Well-known amp categories (mapped from guitarix plugin id prefixes)
    private let categories: [(name: String, prefix: String)] = [
        ("Tube Amp",     "amp"),
        ("Preamp",       "pre"),
        ("Neural (NAM)", "nam"),
        ("AIDA-X",       "aida"),
        ("Clean",        "clean"),
        ("Fuzz",         "fuzz"),
    ]

    private var filteredModels: [String] {
        guard !selectedCategory.isEmpty else { return vm.ampModels }
        return vm.ampModels.filter { $0.hasPrefix(selectedCategory) }
    }

    @State private var selectedCategory = ""
    @State private var search = ""

    var body: some View {
        VSplitView {
            // ── Amp model grid ────────────────────────────────────────────
            VStack(alignment: .leading, spacing: 0) {
                // Category pills + search
                HStack {
                    categoryPills
                    Spacer()
                    TextField("Search…", text: $search)
                        .textFieldStyle(.roundedBorder)
                        .frame(width: 180)
                }
                .padding(.horizontal, 16)
                .padding(.vertical, 10)

                ScrollView {
                    LazyVGrid(columns: [GridItem(.adaptive(minimum: 140))], spacing: 12) {
                        ForEach(displayedModels, id: \.self) { id in
                            AmpModelCard(id: id, isSelected: vm.selectedAmpModel == id) {
                                vm.selectedAmpModel = id
                            }
                        }
                    }
                    .padding(16)
                }
            }
            .frame(minHeight: 220)

            // ── Cabinet selector ──────────────────────────────────────────
            VStack(alignment: .leading, spacing: 8) {
                Text("Cabinet")
                    .font(.caption)
                    .foregroundStyle(.secondary)
                    .padding(.horizontal, 16)
                    .padding(.top, 12)

                ScrollView(.horizontal, showsIndicators: false) {
                    HStack(spacing: 10) {
                        ForEach(vm.cabinetModels, id: \.self) { cab in
                            CabinetCard(id: cab, isSelected: vm.selectedCabinet == cab) {
                                vm.selectedCabinet = cab
                            }
                        }
                    }
                    .padding(.horizontal, 16)
                    .padding(.bottom, 12)
                }
            }
            .frame(height: 110)
            .background(.black.opacity(0.3))
        }
    }

    private var displayedModels: [String] {
        let base = filteredModels
        if search.isEmpty { return base }
        return base.filter { $0.localizedCaseInsensitiveContains(search) }
    }

    private var categoryPills: some View {
        ScrollView(.horizontal, showsIndicators: false) {
            HStack(spacing: 6) {
                CategoryPill(label: "All", isSelected: selectedCategory.isEmpty) {
                    selectedCategory = ""
                }
                ForEach(categories, id: \.name) { cat in
                    CategoryPill(label: cat.name, isSelected: selectedCategory == cat.prefix) {
                        selectedCategory = selectedCategory == cat.prefix ? "" : cat.prefix
                    }
                }
            }
        }
    }
}

// ── Sub-views ─────────────────────────────────────────────────────────────────

struct AmpModelCard: View {
    let id: String
    let isSelected: Bool
    let onTap: () -> Void

    var body: some View {
        Button(action: onTap) {
            VStack(spacing: 6) {
                Image(systemName: "speaker.wave.3")
                    .font(.title)
                    .foregroundStyle(isSelected ? .black : .orange)
                Text(displayName)
                    .font(.caption2)
                    .lineLimit(2)
                    .multilineTextAlignment(.center)
                    .foregroundStyle(isSelected ? .black : .white)
            }
            .frame(maxWidth: .infinity)
            .padding(.vertical, 12)
            .background(isSelected ? Color.orange : Color.white.opacity(0.07))
            .clipShape(RoundedRectangle(cornerRadius: 10))
            .overlay(
                RoundedRectangle(cornerRadius: 10)
                    .stroke(isSelected ? Color.clear : Color.white.opacity(0.12), lineWidth: 1)
            )
        }
        .buttonStyle(.plain)
    }

    private var displayName: String {
        id.replacingOccurrences(of: "_", with: " ")
          .capitalized
    }
}

struct CabinetCard: View {
    let id: String
    let isSelected: Bool
    let onTap: () -> Void

    var body: some View {
        Button(action: onTap) {
            Text(id.replacingOccurrences(of: "_", with: " ").uppercased())
                .font(.caption.bold())
                .padding(.horizontal, 14)
                .padding(.vertical, 8)
                .background(isSelected ? Color.orange : Color.white.opacity(0.1))
                .foregroundStyle(isSelected ? .black : .white)
                .clipShape(RoundedRectangle(cornerRadius: 8))
        }
        .buttonStyle(.plain)
    }
}

struct CategoryPill: View {
    let label: String
    let isSelected: Bool
    let onTap: () -> Void

    var body: some View {
        Button(action: onTap) {
            Text(label)
                .font(.caption.bold())
                .padding(.horizontal, 10)
                .padding(.vertical, 5)
                .background(isSelected ? Color.orange : Color.white.opacity(0.1))
                .foregroundStyle(isSelected ? .black : .secondary)
                .clipShape(Capsule())
        }
        .buttonStyle(.plain)
    }
}
