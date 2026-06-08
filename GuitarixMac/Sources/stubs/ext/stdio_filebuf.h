// ext/stdio_filebuf.h — Clang/libc++ stub.
// GCC ships __gnu_cxx::stdio_filebuf as a libstdc++ extension.
// Clang with libc++ (macOS default) doesn't have it.
// GxMachineRemote uses it to wrap a socket fd in an ostream.
// We won't instantiate GxMachineRemote in the macOS app, so a minimal
// compile-time stub is sufficient.

#pragma once
#include <streambuf>
#include <ios>

namespace __gnu_cxx {

template <typename CharT, typename Traits = std::char_traits<CharT>>
class stdio_filebuf : public std::basic_streambuf<CharT, Traits> {
public:
    stdio_filebuf() = default;

    // Construct from an existing file descriptor (fd) and open mode.
    // The real GCC version mmaps the fd; we just store it.
    explicit stdio_filebuf(int /*fd*/, std::ios_base::openmode /*mode*/,
                           std::size_t /*bufsize*/ = static_cast<std::size_t>(BUFSIZ)) {}

    int fd() const { return -1; }
    // GxMachineRemote calls close() on the buf before deleting it.
    stdio_filebuf* close() { return this; }
};

} // namespace __gnu_cxx
