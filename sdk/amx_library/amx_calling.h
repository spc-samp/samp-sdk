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