// RTNeural.h — stub for the RTNeural inference library.
// The real library lives in trunk/src/RTNeural/RTNeural (uninitialised submodule).
// gx_neural_plugins.h only needs RTNeural::Model<T> as an opaque pointer type.
// gx_neural_plugins.cpp is excluded from the macOS build, so no methods are called.

#pragma once

namespace RTNeural {
    // Forward-declare the Model template used as an opaque pointer.
    template <typename T>
    class Model {};
} // namespace RTNeural
