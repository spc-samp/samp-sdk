#ifndef _OSDEFS_H
    #define _OSDEFS_H

    // Compiler detection and platform-specific definitions
    #if defined(__WATCOMC__)
        #if defined(__WINDOWS__) || defined(__NT__)
            #define _Windows 1
        #endif
        #ifdef __386__
            #define __32BIT__ 1
        #endif
        #if defined(_Windows) && defined(__32BIT__)
            #define __WIN32__ 1
        #endif
    #elif defined(_MSC_VER)
        #if defined(_WINDOWS) || defined(_WIN32)
            #define _Windows 1
        #endif
        #ifdef _WIN32
            #define __WIN32__ 1
            #define __32BIT__ 1
        #endif
    #endif

    // Endianness detection
    #if defined(__FreeBSD__)
        #include <sys/endian.h>
    #elif defined(__APPLE__)
        #include <machine/endian.h>
    #elif defined(LINUX)
        #include <endian.h>
    #endif

    #ifndef BIG_ENDIAN
        #define BIG_ENDIAN 4321
    #endif
    #ifndef LITTLE_ENDIAN
        #define LITTLE_ENDIAN 1234
    #endif

    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif

    // Directory separator
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif

    // Path length definitions
    #ifndef _MAX_PATH
        #if defined(PATH_MAX)
            #define _MAX_PATH PATH_MAX
        #elif defined(_POSIX_PATH_MAX)
            #define _MAX_PATH _POSIX_PATH_MAX
        #else
            #define _MAX_PATH 4096
        #endif
    #endif
#endif