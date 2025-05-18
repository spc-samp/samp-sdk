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

#ifndef AMX_MACROS_H_INCLUDED
    #define AMX_MACROS_H_INCLUDED

    #include "amx_structures.h"

    // Utility macros
    #if !defined arraysize
        #define arraysize(array)  (sizeof(array) / sizeof((array)[0]))
    #endif

    // Address calculation
    #define amx_Address(amx,addr) \
        (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))

    // String parameter handling
    #if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
        #define amx_StrParam_Type(amx,param,result,type) \
            do { \
                int result##_length_; \
                amx_StrLen(amx_Address(amx,param),&result##_length_); \
                char result##_vla_[(result##_length_+1)*sizeof(*(result))]; \
                (result)=(type)result##_vla_; \
                amx_GetString((char*)(result),amx_Address(amx,param), \
                            sizeof(*(result))>1,result##_length_+1); \
            } while(0)
        #define amx_StrParam(amx,param,result) amx_StrParam_Type(amx,param,result,void*)
    #else
        #define amx_StrParam_Type(amx,param,result,type) \
            do { \
                int result##_length_; \
                amx_StrLen(amx_Address(amx,param),&result##_length_); \
                if (result##_length_>0 && \
                    ((result)=(type)alloca((result##_length_+1)*sizeof(*(result))))!=NULL) \
                amx_GetString((char*)(result),amx_Address(amx,param), \
                                sizeof(*(result))>1,result##_length_+1); \
                else (result)=NULL; \
            } while(0)
        #define amx_StrParam(amx,param,result) amx_StrParam_Type(amx,param,result,void*)
    #endif

    // Enhanced string parameter handling for char*
    #define amx_StrParamChar(amx, param, result) \
        do { \
            cell* amx_cstr_; \
            int amx_length_; \
            amx_GetAddr((amx), (param), &amx_cstr_); \
            amx_StrLen(amx_cstr_, &amx_length_); \
            if (amx_length_ > 0 && ((result) = (char*)alloca((amx_length_ + 1) * sizeof(*(result)))) != NULL) \
                amx_GetString((char*)(result), amx_cstr_, sizeof(*(result)) > 1, amx_length_ + 1); \
            else \
                (result) = ""; \
        } while(0)

    // Parameter count utility
    #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))

    // Function registration helper
    #define amx_RegisterFunc(amx, name, func) \
        amx_Register((amx), amx_NativeInfo((name),(func)), 1)
#endif