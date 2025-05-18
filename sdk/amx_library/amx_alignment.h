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

#ifndef AMX_ALIGNMENT_H_INCLUDED
    #define AMX_ALIGNMENT_H_INCLUDED

    // Alignment handling
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 

    // Packing directives
    #if defined __GNUC__
        #define PACKED __attribute__((packed))
    #else
        #define PACKED
    #endif

    #if !defined AMX_NO_ALIGN
        #if defined LINUX || defined __FreeBSD__
            #pragma pack(1)
        #elif defined MACOS && defined __MWERKS__
            #pragma options align=mac68k
        #else
            #pragma pack(push)
            #pragma pack(1)
            #if defined __TURBOC__
                #pragma option -a-
            #endif
        #endif
    #endif

    // Utility macros for header processing
    #define USENAMETABLE(hdr) ((hdr)->defsize==sizeof(AMX_FUNCSTUBNT))
    #define NUMENTRIES(hdr,field,nextfield) ((unsigned)(((hdr)->nextfield - (hdr)->field) / (hdr)->defsize))
    #define GETENTRY(hdr,table,index) ((AMX_FUNCPART *)((unsigned char*)(hdr) + (unsigned)(hdr)->table + (unsigned)index*(hdr)->defsize))
    #define GETENTRYNAME(hdr,entry) (USENAMETABLE(hdr) ? (char *)((unsigned char*)(hdr) + (unsigned)((AMX_FUNCSTUBNT*)(entry))->nameofs) : ((AMX_FUNCSTUB*)(entry))->name)

    // Cell swap operations
    #if PAWN_CELL_SIZE==16
        void amx_Swap16(uint16_t *v);
    #endif
    #if PAWN_CELL_SIZE==32
        void amx_Swap32(uint32_t *v);
    #endif
    #if PAWN_CELL_SIZE==64 && (defined _I64_MAX || defined INT64_MAX || defined HAVE_I64)
        void amx_Swap64(uint64_t *v);
    #endif

    // Cell alignment and swap macros
    #if PAWN_CELL_SIZE==16
        #define amx_AlignCell(v) amx_Align16((uint16_t*)(v))
        #define amx_SwapCell(v)  amx_Swap16((uint16_t*)(v))
    #elif PAWN_CELL_SIZE==32
        #define amx_AlignCell(v) amx_Align32((uint32_t*)(v))
        #define amx_SwapCell(v)  amx_Swap32((uint32_t*)(v))
    #elif PAWN_CELL_SIZE==64 && (defined _I64_MAX || defined INT64_MAX || defined HAVE_I64)
        #define amx_AlignCell(v) amx_Align64((uint64_t*)(v))
        #define amx_SwapCell(v)  amx_Swap64((uint64_t*)(v))
    #else
        #error Unsupported cell size
    #endif
#endif