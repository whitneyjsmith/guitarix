// malloc.h — macOS shim.
// Linux and GCC provide <malloc.h> as a top-level header.
// macOS/Clang puts it at <malloc/malloc.h>. This shim bridges the gap.

#pragma once
#include <stdlib.h>
#ifdef __APPLE__
#  include <malloc/malloc.h>
#endif
