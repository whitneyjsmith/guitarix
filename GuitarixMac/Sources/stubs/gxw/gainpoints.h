// gxw/gainpoints.h — macOS stub.
// The real header uses G_BEGIN_DECLS/G_END_DECLS (GLib macros).
// We provide a plain C++ version so gxwmm/gainline.h compiles without GTK.

#pragma once

struct gain_points {
    int    i;
    double g;
};
