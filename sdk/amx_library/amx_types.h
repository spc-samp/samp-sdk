/*  Pawn Abstract Machine (for the Pawn language)
 *
 *  Copyright (c) ITB CompuPhase, 1997-2006
 *
 *  This software is provided "as-is", without any express or implied warranty.
 *  In no event will the authors be held liable for any damages arising from
 *  the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1.  The origin of this software must not be misrepresented; you must not
 *      claim that you wrote the original software. If you use this software in
 *      a product, an acknowledgment in the product documentation would be
 *      appreciated but is not required.
 *  2.  Altered source versions must be plainly marked as such, and must not be
 *      misrepresented as being the original software.
 *  3.  This notice may not be removed or altered from any source distribution.
 *
 *  Version: $Id: amx.h 3648 2006-10-12 11:24:50Z thiadmer $
 *
 *  Copyright (c) SPC (SA-MP Programming Community)
 *  The SA-MP Programming Community holds copyright solely for the improvements
 *  made to this file and does not claim any rights to the original content.
 *  SPC improvements are licensed under the MIT License, available at:
 *  https://opensource.org/licenses/MIT
 *
 *  - Separate file for better organization of 'amx.h'. By: SPC
 */

#ifndef AMX_TYPES_H_INCLUDED
    #define AMX_TYPES_H_INCLUDED

    #include <stdlib.h>
    #include <limits.h>

    // Modern C detection and stdint inclusion
    #if !defined HAVE_STDINT_H
        #if (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L) || \
            defined __GNUC__ || defined __LCC__ || defined __DMC__ || \
            (defined __WATCOMC__ && __WATCOMC__ >= 1200)
            #define HAVE_STDINT_H 1
        #endif
    #endif

    #if !defined HAVE_INTTYPES_H
        #if defined __FreeBSD__ || defined __APPLE__
            #define HAVE_INTTYPES_H 1
        #endif
    #endif

    // Include appropriate integer type headers
    #if defined HAVE_STDINT_H
        #include <stdint.h>
    #elif defined HAVE_INTTYPES_H
        #include <inttypes.h>
    #else
        #if defined __MACH__
            #include <ppc/types.h>
        #endif
        
        // Define standard integer types if not available
        typedef short int           int16_t;
        typedef unsigned short int  uint16_t;
        
        #if defined SN_TARGET_PS2
            typedef int               int32_t;
            typedef unsigned int      uint32_t;
        #else
            typedef long int          int32_t;
            typedef unsigned long int uint32_t;
        #endif
        
        #if defined __WIN32__ || defined _WIN32 || defined WIN32
            typedef __int64           int64_t;
            typedef unsigned __int64  uint64_t;
            #define HAVE_I64
        #endif
        
        #if !defined _INTPTR_T_DEFINED
            #if defined _LP64 || defined WIN64 || defined _WIN64
                typedef __int64         intptr_t;
            #else
                typedef int32_t         intptr_t;
            #endif
        #endif
    #endif
#endif