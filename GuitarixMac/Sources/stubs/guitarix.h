// guitarix.h — macOS stub for GUITARIX_AS_PLUGIN builds.
// Replaces the GTK-laden original. machine.cpp includes this via the
// stubs/ directory which is ordered before the real headers/ directory.
// We pull in everything machine.cpp actually needs, skipping GTK/curl/NSM.

#pragma once

#define GUITARIX_AS_PLUGIN 1

// engine.h brings in glibmm, giomm, sigc++, boost, lilv, lv2, and all
// guitarix engine types (GxEngine, GxSettings, TunerAdapter, etc.)
#include "engine.h"

// jsonrpc.h declares GxService (used by GxMachine::start_socket)
#include "jsonrpc.h"

// machine.h declares GxMachineBase, GxMachine, GxMachineRemote.
// It needs ext/stdio_filebuf.h for GxMachineRemote — we provide a
// Clang-compatible stub at stubs/ext/stdio_filebuf.h.
#include "machine.h"

// Forward-declare the GTK UI builder type used as a parameter in
// GxMachine::load_unit(). The function body returns false under
// GUITARIX_AS_PLUGIN, so only the declaration needs to compile.
namespace gx_gui {
    class UiBuilderImpl;
}
