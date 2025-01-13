#ifndef AMX_PLATFORM_H_INCLUDED
    #define AMX_PLATFORM_H_INCLUDED

    // Platform detection
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif

    // Unix-like systems header
    #if defined __LINUX__ || defined __FreeBSD__ || defined __OpenBSD__ || defined __APPLE__
        #include "../sclinux.h"
    #endif

    // GCC version detection
    #if defined __GNUC__
        #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
    #endif

    // 64-bit detection
    #if defined _LP64 || defined WIN64 || defined _WIN64
        #if !defined __64BIT__
            #define __64BIT__
        #endif
    #endif
#endif
