import SwiftUI

@main
struct GuitarixApp: App {

    @StateObject private var vm = GuitarixViewModel()

    var body: some Scene {
        WindowGroup {
            ContentView()
                .environmentObject(vm)
                .frame(minWidth: 900, minHeight: 600)
        }
        .windowStyle(.hiddenTitleBar)
        .commands {
            CommandGroup(replacing: .newItem) {}   // no "New" menu item needed
            CommandMenu("Engine") {
                Button("Start Audio") { vm.startAudio() }
                    .keyboardShortcut("r", modifiers: [.command])
                Button("Stop Audio")  { vm.stopAudio()  }
                    .keyboardShortcut(".", modifiers: [.command])
                Divider()
                Toggle("Bypass", isOn: $vm.bypassed)
                    .keyboardShortcut("b", modifiers: [.command])
                Toggle("Tuner",  isOn: $vm.tunerEnabled)
                    .keyboardShortcut("t", modifiers: [.command])
            }
        }
    }
}
