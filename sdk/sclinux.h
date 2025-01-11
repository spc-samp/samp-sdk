#ifndef SCLINUX_H
    #define SCLINUX_H

    #include "getch.h"
    #include <strings.h>

    #define stricmp(a,b) strcasecmp(a,b)
    #define strnicmp(a,b,c) strncasecmp(a,b,c)

    #define DIRECTORY_SEP_CHAR '/'
    #define DIRECTORY_SEP_STR "/"

    // Modern endianness detection
    #if defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)
        #include <endian.h>
    #elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
        #include <sys/endian.h>
    #elif defined(__APPLE__)
        #include <machine/endian.h>
        #include <libkern/OSByteOrder.h>
    #endif

    #ifndef __BYTE_ORDER
        #if defined(__BYTE_ORDER__)
            #define __BYTE_ORDER __BYTE_ORDER__
            #define __LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
            #define __BIG_ENDIAN __ORDER_BIG_ENDIAN__
        #else
            #if defined(__linux__) || defined(__CYGWIN__) || defined(__GNUC__) || \
                defined(__GNU_LIBRARY__) || defined(__ANDROID__)
                #include <endian.h>
            #endif
        #endif
    #endif

    #ifndef __BYTE_ORDER
        #if defined(__hppa__) || defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
            (defined(__MIPS__) && defined(__MIPSEB__)) || defined(__ppc__) || defined(__POWERPC__) || \
            defined(__powerpc__) || defined(__PPC__) || defined(__sparc__)
            #define __BYTE_ORDER __BIG_ENDIAN
        #else
            #define __BYTE_ORDER __LITTLE_ENDIAN
        #endif
    #endif

    #if !defined(__LITTLE_ENDIAN)
        #define __LITTLE_ENDIAN 1234
    #endif

    #if !defined(__BIG_ENDIAN)
        #define __BIG_ENDIAN 4321
    #endif

#endif