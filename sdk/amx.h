#ifndef AMX_H_INCLUDED
    #define AMX_H_INCLUDED

    #include "amx_library/amx_platform.h"
    #include "amx_library/amx_types.h"
    #include "amx_library/amx_memory.h"
    #include "amx_library/amx_calling.h"
    #include "amx_library/amx_cell.h"
    #include "amx_library/amx_structures.h"
    #include "amx_library/amx_constants.h"
    #include "amx_library/amx_macros.h"
    #include "amx_library/amx_alignment.h"

    #ifdef __cplusplus
        extern "C" {
    #endif

    // Compiler-specific pragma handling
    #if defined _MSC_VER
        #pragma warning(disable:4103)
        #pragma warning(disable:4100)
        #pragma warning(disable:4127)
        #pragma warning(disable:4996)
    #elif defined __clang__
        #pragma GCC diagnostic ignored "-Wlogical-op-parentheses"
        #pragma GCC diagnostic ignored "-Wbitwise-op-parentheses"
    #endif

    // Core AMX functions
    extern int AMXAPI (*amx_Allot)(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    extern int AMXAPI (*amx_Callback)(AMX* amx, cell index, cell* result, const cell* params);
    extern int AMXAPI (*amx_Cleanup)(AMX* amx);
    extern int AMXAPI (*amx_Clone)(AMX* amxClone, AMX* amxSource, void* data);
    extern int AMXAPI (*amx_Exec)(AMX* amx, cell* retval, int index);
    extern int AMXAPI (*amx_FindNative)(AMX* amx, const char* name, int* index);
    extern int AMXAPI (*amx_FindPublic)(AMX* amx, const char* funcname, int* index);
    extern int AMXAPI (*amx_FindPubVar)(AMX* amx, const char* varname, cell* amx_addr);
    extern int AMXAPI (*amx_FindTagId)(AMX* amx, cell tag_id, char* tagname);
    extern int AMXAPI (*amx_Flags)(AMX* amx, uint16_t* flags);
    extern int AMXAPI (*amx_GetAddr)(AMX* amx, cell amx_addr, cell** phys_addr);
    extern int AMXAPI (*amx_GetNative)(AMX* amx, int index, char* funcname);
    extern int AMXAPI (*amx_GetPublic)(AMX* amx, int index, char* funcname);
    extern int AMXAPI (*amx_GetPubVar)(AMX* amx, int index, char* varname, cell* amx_addr);
    extern int AMXAPI (*amx_GetString)(char* dest, const cell* source, int use_wchar, size_t size);
    extern int AMXAPI (*amx_GetTag)(AMX* amx, int index, char* tagname, cell* tag_id);
    extern int AMXAPI (*amx_GetUserData)(AMX* amx, long tag, void** ptr);
    extern int AMXAPI (*amx_Init)(AMX* amx, void* program);
    extern int AMXAPI (*amx_InitJIT)(AMX* amx, void* reloc_table, void* native_code);
    extern int AMXAPI (*amx_MemInfo)(AMX* amx, long* codesize, long* datasize, long* stackheap);
    extern int AMXAPI (*amx_NameLength)(AMX* amx, int* length);
    extern AMX_NATIVE_INFO* AMXAPI (*amx_NativeInfo)(const char* name, AMX_NATIVE func);
    extern int AMXAPI (*amx_NumNatives)(AMX* amx, int* number);
    extern int AMXAPI (*amx_NumPublics)(AMX* amx, int* number);
    extern int AMXAPI (*amx_NumPubVars)(AMX* amx, int* number);
    extern int AMXAPI (*amx_NumTags)(AMX* amx, int* number);
    extern int AMXAPI (*amx_Push)(AMX* amx, cell value);
    extern int AMXAPI (*amx_PushArray)(AMX* amx, cell* amx_addr, cell** phys_addr, const cell array[], int numcells);
    extern int AMXAPI (*amx_PushString)(AMX* amx, cell* amx_addr, cell** phys_addr, const char* string, int pack, int use_wchar);
    extern int AMXAPI (*amx_RaiseError)(AMX* amx, int error);
    extern int AMXAPI (*amx_Register)(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    extern int AMXAPI (*amx_Release)(AMX* amx, cell amx_addr);
    extern int AMXAPI (*amx_SetCallback)(AMX* amx, AMX_CALLBACK callback);
    extern int AMXAPI (*amx_SetDebugHook)(AMX* amx, AMX_DEBUG debug);
    extern int AMXAPI (*amx_SetString)(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    extern int AMXAPI (*amx_SetUserData)(AMX* amx, long tag, void* ptr);
    extern int AMXAPI (*amx_StrLen)(const cell* cstring, int* length);
    extern int AMXAPI (*amx_UTF8Check)(const char* string, int* length);
    extern int AMXAPI (*amx_UTF8Get)(const char* string, const char** endptr, cell* value);
    extern int AMXAPI (*amx_UTF8Len)(const cell* cstr, int* length);
    extern int AMXAPI (*amx_UTF8Put)(char* string, char** endptr, int maxchars, cell value);

    // Restore packing
    #if !defined AMX_NO_ALIGN
        #if defined __LINUX__ || defined __FreeBSD__ || defined __APPLE__
            #pragma pack()
        #elif defined MACOS && defined __MWERKS__
            #pragma options align=reset
        #else
            #pragma pack(pop)
        #endif
    #endif

    #ifdef __cplusplus
        }
    #endif
#endif