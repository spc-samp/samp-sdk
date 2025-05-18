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

#ifndef AMX_CONSTANTS_H_INCLUDED
    #define AMX_CONSTANTS_H_INCLUDED

    // Version constants
    #define CUR_FILE_VERSION  9
    #define MIN_FILE_VERSION  6
    #define MIN_AMX_VERSION   10
    #define MAX_FILE_VER_JIT  8
    #define MIN_AMX_VER_JIT   8

    // Magic numbers for different cell sizes
    #define AMX_MAGIC_16    0xf1e2
    #define AMX_MAGIC_32    0xf1e0
    #define AMX_MAGIC_64    0xf1e1

    #if PAWN_CELL_SIZE==16
        #define AMX_MAGIC     AMX_MAGIC_16
    #elif PAWN_CELL_SIZE==32
        #define AMX_MAGIC     AMX_MAGIC_32
    #elif PAWN_CELL_SIZE==64
        #define AMX_MAGIC     AMX_MAGIC_64
    #endif

    // Error codes
    enum {
        AMX_ERR_NONE,
        AMX_ERR_EXIT,
        AMX_ERR_ASSERT,
        AMX_ERR_STACKERR,
        AMX_ERR_BOUNDS,
        AMX_ERR_MEMACCESS,
        AMX_ERR_INVINSTR,
        AMX_ERR_STACKLOW,
        AMX_ERR_HEAPLOW,
        AMX_ERR_CALLBACK,
        AMX_ERR_NATIVE,
        AMX_ERR_DIVIDE,
        AMX_ERR_SLEEP,
        AMX_ERR_INVSTATE,
        
        AMX_ERR_MEMORY = 16,
        AMX_ERR_FORMAT,
        AMX_ERR_VERSION,
        AMX_ERR_NOTFOUND,
        AMX_ERR_INDEX,
        AMX_ERR_DEBUG,
        AMX_ERR_INIT,
        AMX_ERR_USERDATA,
        AMX_ERR_INIT_JIT,
        AMX_ERR_PARAMS,
        AMX_ERR_DOMAIN,
        AMX_ERR_GENERAL,
    };

    // Flags
    #define AMX_FLAG_DEBUG      0x02
    #define AMX_FLAG_COMPACT    0x04
    #define AMX_FLAG_SLEEP      0x08
    #define AMX_FLAG_NOCHECKS   0x10
    #define AMX_FLAG_NO_RELOC   0x200
    #define AMX_FLAG_NO_SYSREQD 0x400
    #define AMX_FLAG_SYSREQN    0x800 
    #define AMX_FLAG_NTVREG     0x1000
    #define AMX_FLAG_JITC       0x2000
    #define AMX_FLAG_BROWSE     0x4000
    #define AMX_FLAG_RELOC      0x8000

    // Execution codes
    #define AMX_EXEC_MAIN   (-1)
    #define AMX_EXEC_CONT   (-2)

    // User tags
    #define AMX_USERTAG(a,b,c,d) ((a) | ((b)<<8) | ((long)(c)<<16) | ((long)(d)<<24))
#endif