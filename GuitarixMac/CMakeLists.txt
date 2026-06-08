cmake_minimum_required(VERSION 3.22)
project(GuitarixEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Dependencies (installed via Homebrew) ──────────────────────────────────────
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIBMM   REQUIRED IMPORTED_TARGET glibmm-2.4)
pkg_check_modules(GIOMM    REQUIRED IMPORTED_TARGET giomm-2.4)
pkg_check_modules(LILV     REQUIRED IMPORTED_TARGET lilv-0)
pkg_check_modules(SIGCPP   REQUIRED IMPORTED_TARGET sigc++-2.0)
pkg_check_modules(SNDFILE  REQUIRED IMPORTED_TARGET sndfile)
pkg_check_modules(FFTW3    REQUIRED IMPORTED_TARGET fftw3f)
find_package(Boost REQUIRED COMPONENTS thread iostreams)

# ── Engine source root ─────────────────────────────────────────────────────────
set(ENGINE_ROOT "${CMAKE_SOURCE_DIR}/../trunk/src")

set(ENGINE_SOURCES
    ${ENGINE_ROOT}/gx_head/engine/gx_engine.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_engine_audio.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_faust_plugins.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_internal_plugins.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_internal_ui_plugins.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_jack_wrapper.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_json.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_logging.cpp
    # gx_neural_plugins.cpp excluded: requires RTNeural + NAM submodules (not initialised)
    ${ENGINE_ROOT}/gx_head/engine/gx_paramtable.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_pitch_tracker.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_pluginloader.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_preset.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_resampler.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_system.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_convolver.cpp
    ${ENGINE_ROOT}/gx_head/engine/jsonrpc.cpp
    # jsonrpc_methods-generated.cc is #included inside jsonrpc.cpp — not a separate TU
    ${ENGINE_ROOT}/gx_head/engine/ladspaback.cpp
    ${ENGINE_ROOT}/gx_head/engine/ladspaplugin.cpp
    # gx_cabinet_data.cc and gx_preamp_data.cc are #included inside gx_internal_plugins.cpp
    # (CabDesc_imp/PreDesc_imp templates are defined there) — not separate TUs
    # machine layer
    ${ENGINE_ROOT}/gx_head/gui/machine.cpp
)

add_library(guitarix_engine STATIC ${ENGINE_SOURCES})

target_compile_definitions(guitarix_engine PUBLIC
    GUITARIX_AS_PLUGIN=1
    HAVE_LADSPA=1
)

target_include_directories(guitarix_engine PUBLIC
    # stubs/ MUST come first: our guitarix.h, ext/stdio_filebuf.h, and malloc.h
    # intercept includes before the GTK-laden originals are reached.
    ${CMAKE_SOURCE_DIR}/Sources/stubs
    ${ENGINE_ROOT}/headers
    ${ENGINE_ROOT}/gx_head/engine
    ${ENGINE_ROOT}/zita-convolver
    ${ENGINE_ROOT}/zita-resampler-1.1.0
    ${ENGINE_ROOT}/gx_head/engine/tabels    # valve.h and other lookup tables
    ${ENGINE_ROOT}/faust-generated          # low_high_cut.h, jconv_post.h, etc.
    ${ENGINE_ROOT}/plugins                  # pluginlib.h (bare include in gx_engine.cpp)
)

target_link_libraries(guitarix_engine PUBLIC
    PkgConfig::GLIBMM
    PkgConfig::GIOMM
    PkgConfig::LILV
    PkgConfig::SIGCPP
    PkgConfig::SNDFILE
    PkgConfig::FFTW3
    Boost::thread
    Boost::iostreams
    dl
)

target_compile_options(guitarix_engine PRIVATE
    -O2
    -ffast-math
    -Wno-deprecated-declarations
    # Force-include the macOS compatibility shims before any engine header
    -include ${CMAKE_SOURCE_DIR}/Sources/stubs/macos_compat.h
)

# ── CoreAudio driver (built alongside the engine) ─────────────────────────────
add_library(guitarix_coreaudio STATIC
    ${CMAKE_SOURCE_DIR}/Sources/Bridge/CoreAudioDriver.cpp
)

target_include_directories(guitarix_coreaudio PUBLIC
    ${CMAKE_SOURCE_DIR}/Sources/Bridge
    ${ENGINE_ROOT}/headers
)

target_link_libraries(guitarix_coreaudio PUBLIC
    guitarix_engine
    "-framework CoreAudio"
    "-framework AudioToolbox"
    "-framework AudioUnit"
)

# ── Install both static libs for Xcode to link ────────────────────────────────
install(TARGETS guitarix_engine guitarix_coreaudio
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY ${ENGINE_ROOT}/headers/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/guitarix)
