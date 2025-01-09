#ifndef SCLINUX_H
    #define SCLINUX_H

    #include "getch.h"
    #include <strings.h>

    #define stricmp(a,b) strcasecmp(a,b)
    #define strnicmp(a,b,c) strncasecmp(a,b,c)

    #define DIRECTORY_SEP_CHAR '/'
    #define DIRECTORY_SEP_STR "/"

    #ifdef HAVE_ENDIAN_H
        #include <endian.h>
    #endif

    #ifndef __BYTE_ORDER
        #include <stdlib.h>
    #endif

    #if defined(__OpenBSD__) || defined(__FreeBSD__)
        #define __BYTE_ORDER BYTE_ORDER
        #define __LITTLE_ENDIAN LITTLE_ENDIAN
        #define __BIG_ENDIAN BIG_ENDIAN
    #endif

    #if defined(__APPLE__)
        #define __BYTE_ORDER BYTE_ORDER
        #define __LITTLE_ENDIAN __DARWIN_LITTLE_ENDIAN
        #define __BIG_ENDIAN __DARWIN_BIG_ENDIAN
    #endif

    #ifndef __BYTE_ORDER
        #error "Cannot determine system byte order (__BYTE_ORDER undefined)"
    #endif
#endif