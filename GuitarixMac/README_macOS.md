# GuitarixMac — Native macOS App

A native macOS port of [Guitarix](https://guitarix.org), the modular virtual guitar amplifier.  
The C++ DSP engine is kept intact; GTK and JACK are replaced with SwiftUI and CoreAudio.

## Architecture

```
┌─────────────────────────────────────────────────────┐
│  SwiftUI (Sources/App/)                             │
│  AmpSelectorView · EffectRackView · TunerView …     │
└────────────────┬───────────────────────────────────┘
                 │  Swift ↔ Obj-C via bridging header
┌────────────────▼───────────────────────────────────┐
│  GuitarixBridge.mm  (Obj-C++)                       │
│  Wraps GxMachine — preset/parameter/rack API        │
└────────────────┬───────────────────────────────────┘
                 │  C++
┌────────────────▼───────────────────────────────────┐
│  Guitarix C++ engine  (trunk/src/gx_head/engine/)   │
│  GUITARIX_AS_PLUGIN=1  (JACK stripped out)          │
│  MonoModuleChain · StereoModuleChain · GxMachine    │
└────────────────┬───────────────────────────────────┘
                 │  CoreAudio callbacks
┌────────────────▼───────────────────────────────────┐
│  CoreAudioDriver.cpp                                │
│  AUHAL AudioUnit · 32-bit float non-interleaved     │
│  Guitar input → DSP → stereo output                 │
└─────────────────────────────────────────────────────┘
```

## Requirements

- macOS 13 Ventura or later (Apple Silicon or Intel)
- Xcode 15+
- Homebrew

## Build

```bash
cd GuitarixMac
./build.sh
```

The script will:
1. Install Homebrew dependencies (glibmm, sigc++, boost, fftw, sndfile, xcodegen, cmake)
2. Build the Guitarix C++ engine as a static library (`build/lib/libguitarix_engine.a`)
3. Build the CoreAudio driver (`build/lib/libguitarix_coreaudio.a`)
4. Run XcodeGen to produce `GuitarixMac.xcodeproj`
5. Build the macOS app → `build/products/Release/GuitarixMac.app`

```bash
# Clean and rebuild
./build.sh clean && ./build.sh

# Open the app
open build/products/Release/GuitarixMac.app
```

## Project layout

```
GuitarixMac/
├── CMakeLists.txt              # Builds C++ engine static libs
├── project.yml                 # XcodeGen project spec
├── build.sh                    # One-shot build script
├── Sources/
│   ├── Bridge/
│   │   ├── GuitarixBridge.h    # Obj-C interface (imported by Swift)
│   │   ├── GuitarixBridge.mm   # Obj-C++ implementation
│   │   ├── CoreAudioDriver.h   # AUHAL CoreAudio driver header
│   │   ├── CoreAudioDriver.cpp # AUHAL CoreAudio driver implementation
│   │   └── GuitarixMac-Bridging-Header.h
│   └── App/
│       ├── GuitarixApp.swift
│       ├── ContentView.swift
│       ├── GuitarixViewModel.swift
│       ├── AmpSelectorView.swift
│       ├── EffectRackView.swift
│       ├── PresetBrowserView.swift
│       ├── TunerView.swift
│       ├── LevelMeterView.swift
│       └── AudioSettingsView.swift
└── Resources/
    └── Info.plist
```

## Known adaptation points

The bridge (`GuitarixBridge.mm`) wraps `GxMachine` which is compiled with
`GUITARIX_AS_PLUGIN=1`. A few engine APIs are exposed by name in the bridge;
if the upstream engine renames them, update the bridge to match.

**Faust-generated sources** — `gx_preamp_data.cc` and `gx_cabinet_data.cc` are
generated at configure time by the waf build system. The `build.sh` script runs
`waf build` to produce them before the CMake step. If you have them already
(from a prior Linux build), copy them into `trunk/src/gx_head/engine/`.

**LV2 / LADSPA plugins** — the engine can load external LV2 and LADSPA plugins
at runtime. On macOS these won't be present by default; the engine gracefully
skips them. You can install LV2 bundles under `~/Library/Audio/Plug-Ins/LV2/`.

## iOS port (future)

The CoreAudio driver works on iOS with minor changes:
- Replace `kAudioUnitSubType_HALOutput` with `kAudioUnitSubType_RemoteIO`
- Remove device-selection code (iOS has no device picker)
- The SwiftUI layer needs iPhone layout adjustments

The engine C++ compiles for iOS arm64 without modification.
