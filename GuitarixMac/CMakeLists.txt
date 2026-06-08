cmake_minimum_required(VERSION 3.22)
project(GuitarixEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Dependencies (installed via Homebrew) ──────────────────────────────────────
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIBMM   REQUIRED IMPORTED_TARGET glibmm-2.4)
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
    ${ENGINE_ROOT}/gx_head/engine/gx_neural_plugins.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_paramtable.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_pitch_tracker.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_pluginloader.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_preset.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_resampler.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_system.cpp
    ${ENGINE_ROOT}/gx_head/engine/gx_convolver.cpp
    ${ENGINE_ROOT}/gx_head/engine/jsonrpc.cpp
    ${ENGINE_ROOT}/gx_head/engine/jsonrpc_methods-generated.cc
    ${ENGINE_ROOT}/gx_head/engine/ladspaback.cpp
    ${ENGINE_ROOT}/gx_head/engine/ladspaplugin.cpp
    # faust-generated DSP
    ${ENGINE_ROOT}/gx_head/engine/gx_cabinet_data.cc
    ${ENGINE_ROOT}/gx_head/engine/gx_preamp_data.cc
    # machine layer
    ${ENGINE_ROOT}/gx_head/gui/machine.cpp
)

add_library(guitarix_engine STATIC ${ENGINE_SOURCES})

target_compile_definitions(guitarix_engine PUBLIC
    GUITARIX_AS_PLUGIN=1
    HAVE_LADSPA=1
)

target_include_directories(guitarix_engine PUBLIC
    ${ENGINE_ROOT}/headers
    ${ENGINE_ROOT}/gx_head/engine
    ${ENGINE_ROOT}/zita-convolver
    ${ENGINE_ROOT}/zita-resampler-1.1.0/libs
)

target_link_libraries(guitarix_engine PUBLIC
    PkgConfig::GLIBMM
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
    -msse -msse2 -msse3 -mfpmath=sse
    -Wno-deprecated-declarations
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
