// dsp.h — stub for NAM (NeuralAmpModelerCore) DSP class.
// The real header lives in trunk/src/NAM/NeuralAmpModelerCore (uninitialised submodule).
// gx_neural_plugins.h only needs the pointer type; a forward declaration suffices.
// gx_neural_plugins.cpp is excluded from the macOS build, so no methods are called.

#pragma once

namespace nam {
    // Forward-declare the base DSP class used as an opaque pointer.
    class DSP {};
} // namespace nam
