// macos_compat.h — force-included for every engine translation unit.
// Provides Linux-only symbols that Guitarix's engine headers assume exist.

#pragma once

#ifdef __APPLE__
#include <pthread.h>
#include <time.h>

// pthread_condattr_setclock is a Linux extension (POSIX 2008 option).
// On macOS, condition variables always use the system monotonic clock,
// so skipping this call is correct and safe.
#ifndef CLOCK_MONOTONIC
#  define CLOCK_MONOTONIC 1
#endif

static inline int pthread_condattr_setclock(pthread_condattr_t* /*attr*/,
                                             clockid_t /*clock_id*/) {
    return 0;   // no-op: macOS cond vars are already monotonic
}

// GetPrefsPath: used in gx_system.cpp under GUITARIX_AS_PLUGIN + __APPLE__.
// Fills buf with the macOS user config directory (~/Library/Application Support).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static inline void GetPrefsPath(char* buf, size_t n) {
    const char* home = getenv("HOME");
    if (home) {
        snprintf(buf, n, "%s/Library/Application Support", home);
    } else {
        strncpy(buf, "/tmp", n);
        buf[n - 1] = '\0';
    }
}

#endif // __APPLE__
