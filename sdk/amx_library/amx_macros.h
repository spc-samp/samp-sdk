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