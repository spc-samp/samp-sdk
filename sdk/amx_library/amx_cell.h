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

#ifndef AMX_CELL_H_INCLUDED
    #define AMX_CELL_H_INCLUDED

    // Cell size configuration
    #if !defined PAWN_CELL_SIZE
        #define PAWN_CELL_SIZE 32
    #endif

    #if PAWN_CELL_SIZE==16
        typedef uint16_t  ucell;
        typedef int16_t   cell;
    #elif PAWN_CELL_SIZE==32
        typedef uint32_t  ucell;
        typedef int32_t   cell;
    #elif PAWN_CELL_SIZE==64
        typedef uint64_t  ucell;
        typedef int64_t   cell;
    #else
        #error Unsupported cell size (PAWN_CELL_SIZE)
    #endif

    // Pointer width handling
    #if defined _LP64 || defined __LP64__ || defined WIN64 || defined _WIN64
        #define __64BIT__
    #endif

    #if defined __64BIT__ && PAWN_CELL_SIZE < 64
        #define AMX_DONT_RELOCATE
        #define AMX_WIDE_POINTERS
    #elif !defined __64BIT__ && PAWN_CELL_SIZE < 32
        #define AMX_DONT_RELOCATE
        #define AMX_WIDE_POINTERS
    #endif

    #define UNPACKEDMAX   (((ucell)1 << (sizeof(ucell)-1)*8) - 1)
    #define UNLIMITED     (~1u >> 1)

    // Character handling
    #define CHARBITS (8*sizeof(char))
    #if PAWN_CELL_SIZE==16
        #define CHARMASK (0xffffu << 8*(2-sizeof(char)))
    #elif PAWN_CELL_SIZE==32
        #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))
    #elif PAWN_CELL_SIZE==64
        #define CHARMASK (0xffffffffffffffffuLL << 8*(8-sizeof(char)))
    #else
        #error Unsupported cell size
    #endif

    // Floating point support
    #if PAWN_CELL_SIZE==32
        #define amx_ftoc(f)   (*(cell*)&(f))
        #define amx_ctof(c)   (*(float*)&(c))
    #elif PAWN_CELL_SIZE==64
        #define amx_ftoc(f)   (*(cell*)&(f))
        #define amx_ctof(c)   (*(double*)&(c))
    #endif

#endif