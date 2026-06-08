#!/usr/bin/env bash
# build.sh — Full macOS build for GuitarixMac
# Usage:  cd GuitarixMac && ./build.sh [clean]
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# ── 0. Optional clean ──────────────────────────────────────────────────────────
if [[ "${1:-}" == "clean" ]]; then
    echo "==> Cleaning build directory…"
    rm -rf "$BUILD_DIR"
    echo "Done."
    exit 0
fi

echo "==> GuitarixMac build script"
echo "    Repo root : $REPO_ROOT"
echo "    Build dir : $BUILD_DIR"
echo ""

# ── 1. Homebrew dependencies ───────────────────────────────────────────────────
echo "==> Checking / installing Homebrew dependencies…"
brew_pkgs=(
    cmake
    ninja
    pkg-config
    glibmm@2.66
    libsigc++@2
    boost
    libsndfile
    fftw
    lv2
    lilv
    gperf
    intltool
    xcodegen
)

missing=()
for pkg in "${brew_pkgs[@]}"; do
    brew list --formula "$pkg" &>/dev/null || missing+=("$pkg")
done

if [[ ${#missing[@]} -gt 0 ]]; then
    echo "    Installing: ${missing[*]}"
    brew install "${missing[@]}"
else
    echo "    All dependencies present."
fi
echo ""

# ── 2. Generate faust DSP sources (if waf is available) ──────────────────────
FAUST_GENERATED="$REPO_ROOT/trunk/src/gx_head/engine/gx_preamp_data.cc"
if [[ ! -f "$FAUST_GENERATED" ]]; then
    echo "==> Generating Faust DSP sources via waf…"
    pushd "$REPO_ROOT/trunk" >/dev/null
    python3 waf configure --prefix=/tmp/gx_tmp --optimization \
        --includeresampler --includeconvolver 2>&1 | tail -5
    python3 waf build --targets=gx_preamp_data,gx_cabinet_data 2>&1 | tail -5
    popd >/dev/null
    echo ""
fi

# ── 3. Build C++ engine static libraries via CMake ───────────────────────────
echo "==> Building Guitarix C++ engine…"
mkdir -p "$BUILD_DIR"
cmake -B "$BUILD_DIR/cmake" \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX="$BUILD_DIR" \
      -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
      "$SCRIPT_DIR" \
      2>&1 | tail -10

cmake --build "$BUILD_DIR/cmake" --parallel 2>&1 | tail -15
cmake --install "$BUILD_DIR/cmake"

echo "    Engine built → $BUILD_DIR/lib/"
echo ""

# ── 4. Generate Xcode project ─────────────────────────────────────────────────
echo "==> Generating Xcode project with XcodeGen…"
pushd "$SCRIPT_DIR" >/dev/null
xcodegen generate
popd >/dev/null
echo ""

# ── 5. Build the app ──────────────────────────────────────────────────────────
echo "==> Building GuitarixMac.app…"
xcodebuild \
    -project "$SCRIPT_DIR/GuitarixMac.xcodeproj" \
    -scheme   GuitarixMac \
    -configuration Release \
    -derivedDataPath "$BUILD_DIR/xcode" \
    SYMROOT="$BUILD_DIR/products" \
    build \
    2>&1 | xcbeautify 2>/dev/null || \
xcodebuild \
    -project "$SCRIPT_DIR/GuitarixMac.xcodeproj" \
    -scheme   GuitarixMac \
    -configuration Release \
    -derivedDataPath "$BUILD_DIR/xcode" \
    SYMROOT="$BUILD_DIR/products" \
    build

APP_PATH="$BUILD_DIR/products/Release/GuitarixMac.app"

if [[ -d "$APP_PATH" ]]; then
    echo ""
    echo "✅  Build succeeded!"
    echo "    App: $APP_PATH"
    echo ""
    echo "    Open with:  open \"$APP_PATH\""
    echo "    Or copy to: /Applications/"
else
    echo "❌  Build failed — check output above." >&2
    exit 1
fi
