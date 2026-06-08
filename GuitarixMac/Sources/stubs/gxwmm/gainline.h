// gxwmm/gainline.h — macOS stub.
// Provides Gainline (a std::vector<gain_points>) without any GTK/gxw dependency.
// Used by gx_convolver.h for IR gain envelope points.

#pragma once

#include <gxw/gainpoints.h>
#include <vector>
#include <cmath>

inline bool operator==(const gain_points& p1, const gain_points& p2) {
    return p1.i == p2.i && std::abs(p1.g - p2.g) < 1e-4 * (p1.g + p2.g);
}
inline bool operator!=(const gain_points& p1, const gain_points& p2) {
    return !(p1 == p2);
}

class Gainline : public std::vector<gain_points> {
public:
    Gainline(gain_points* p, int n) { while (n-- > 0) push_back(*p++); }
    Gainline() {}
    const gain_points* points() const { return &(*begin()); }
};

inline bool operator==(const Gainline& g1, const Gainline& g2) {
    if (g1.size() != g2.size()) return false;
    for (unsigned int i = 0; i < g1.size(); ++i)
        if (g1.points()[i] != g2.points()[i]) return false;
    return true;
}
inline bool operator!=(const Gainline& g1, const Gainline& g2) { return !(g1 == g2); }
