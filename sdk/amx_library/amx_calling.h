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

#ifndef AMX_CALLING_H_INCLUDED
    #define AMX_CALLING_H_INCLUDED

    // Calling conventions
    #if defined PAWN_DLL
        #if !defined AMX_NATIVE_CALL
            #define AMX_NATIVE_CALL __stdcall
        #endif
        #if !defined AMXAPI
            #define AMXAPI __stdcall
        #endif
    #endif

    #if !defined AMX_NATIVE_CALL
        #define AMX_NATIVE_CALL
    #endif

    #if !defined AMXAPI
        #if defined STDECL
            #define AMXAPI __stdcall
        #elif defined CDECL
            #define AMXAPI __cdecl
        #elif defined GCC_HASCLASSVISIBILITY
            #define AMXAPI __attribute__((visibility("default")))
        #else
            #define AMXAPI
        #endif
    #endif

    #if !defined AMXEXPORT
        #define AMXEXPORT
    #endif
#endif