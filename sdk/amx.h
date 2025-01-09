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
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    int AMXAPI amx_Callback(AMX* amx, cell index, cell* result, const cell* params);
    int AMXAPI amx_Cleanup(AMX* amx);
    int AMXAPI amx_Clone(AMX* amxClone, AMX* amxSource, void* data);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_FindNative(AMX* amx, const char* name, int* index);
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    int AMXAPI amx_FindPubVar(AMX* amx, const char* varname, cell* amx_addr);
    int AMXAPI amx_FindTagId(AMX* amx, cell tag_id, char* tagname);
    int AMXAPI amx_Flags(AMX* amx, uint16_t* flags);
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    int AMXAPI amx_GetNative(AMX* amx, int index, char* funcname);
    int AMXAPI amx_GetPublic(AMX* amx, int index, char* funcname);
    int AMXAPI amx_GetPubVar(AMX* amx, int index, char* varname, cell* amx_addr);
    int AMXAPI amx_GetString(char* dest, const cell* source, int use_wchar, size_t size);
    int AMXAPI amx_GetTag(AMX* amx, int index, char* tagname, cell* tag_id);
    int AMXAPI amx_GetUserData(AMX* amx, long tag, void** ptr);
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    int AMXAPI amx_NameLength(AMX* amx, int* length);
    AMX_NATIVE_INFO* AMXAPI amx_NativeInfo(const char* name, AMX_NATIVE func);
    int AMXAPI amx_NumNatives(AMX* amx, int* number);
    int AMXAPI amx_NumPublics(AMX* amx, int* number);
    int AMXAPI amx_NumPubVars(AMX* amx, int* number);
    int AMXAPI amx_NumTags(AMX* amx, int* number);
    int AMXAPI amx_Push(AMX* amx, cell value);
    int AMXAPI amx_PushArray(AMX* amx, cell* amx_addr, cell** phys_addr, const cell array[], int numcells);
    int AMXAPI amx_PushString(AMX* amx, cell* amx_addr, cell** phys_addr, const char* string, int pack, int use_wchar);
    int AMXAPI amx_PushStringLen(AMX* amx, cell* amx_addr, cell** phys_addr, const char* string, int length, int pack, int use_wchar);
    int AMXAPI amx_RaiseError(AMX* amx, int error);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    int AMXAPI amx_Release(AMX* amx, cell amx_addr);
    int AMXAPI amx_SetCallback(AMX* amx, AMX_CALLBACK callback);
    int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    int AMXAPI amx_SetStringLen(cell* dest, const char* source, int length, int pack, int use_wchar, size_t size);
    int AMXAPI amx_SetUserData(AMX* amx, long tag, void* ptr);
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
    int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);

    // NPC AMX functions 
    int AMXAPI npcamx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    int AMXAPI npcamx_Callback(AMX* amx, cell index, cell* result, const cell* params);
    int AMXAPI npcamx_Cleanup(AMX* amx);
    int AMXAPI npcamx_Clone(AMX* amxClone, AMX* amxSource, void* data);
    int AMXAPI npcamx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI npcamx_FindNative(AMX* amx, const char* name, int* index);
    int AMXAPI npcamx_FindPublic(AMX* amx, const char* funcname, int* index);
    int AMXAPI npcamx_FindPubVar(AMX* amx, const char* varname, cell* amx_addr);
    int AMXAPI npcamx_FindTagId(AMX* amx, cell tag_id, char* tagname);
    int AMXAPI npcamx_Flags(AMX* amx, uint16_t* flags);
    int AMXAPI npcamx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    int AMXAPI npcamx_GetNative(AMX* amx, int index, char* funcname);
    int AMXAPI npcamx_GetPublic(AMX* amx, int index, char* funcname);
    int AMXAPI npcamx_GetPubVar(AMX* amx, int index, char* varname, cell* amx_addr);
    int AMXAPI npcamx_GetString(char* dest, const cell* source, int use_wchar, size_t size);
    int AMXAPI npcamx_GetTag(AMX* amx, int index, char* tagname, cell* tag_id);
    int AMXAPI npcamx_GetUserData(AMX* amx, long tag, void** ptr);
    int AMXAPI npcamx_Init(AMX* amx, void* program);
    int AMXAPI npcamx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
    int AMXAPI npcamx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    int AMXAPI npcamx_NameLength(AMX* amx, int* length);
    AMX_NATIVE_INFO* AMXAPI npcamx_NativeInfo(const char* name, AMX_NATIVE func);
    int AMXAPI npcamx_NumNatives(AMX* amx, int* number);
    int AMXAPI npcamx_NumPublics(AMX* amx, int* number);
    int AMXAPI npcamx_NumPubVars(AMX* amx, int* number);
    int AMXAPI npcamx_NumTags(AMX* amx, int* number);
    int AMXAPI npcamx_Push(AMX* amx, cell value);
    int AMXAPI npcamx_PushArray(AMX* amx, cell* amx_addr, cell** phys_addr, const cell array[], int numcells);
    int AMXAPI npcamx_PushString(AMX* amx, cell* amx_addr, cell** phys_addr, const char* string, int pack, int use_wchar);
    int AMXAPI npcamx_PushStringLen(AMX* amx, cell* amx_addr, cell** phys_addr, const char* string, int length, int pack, int use_wchar);
    int AMXAPI npcamx_RaiseError(AMX* amx, int error);
    int AMXAPI npcamx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    int AMXAPI npcamx_Release(AMX* amx, cell amx_addr);
    int AMXAPI npcamx_SetCallback(AMX* amx, AMX_CALLBACK callback);
    int AMXAPI npcamx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
    int AMXAPI npcamx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    int AMXAPI npcamx_SetStringLen(cell* dest, const char* source, int length, int pack, int use_wchar, size_t size);
    int AMXAPI npcamx_SetUserData(AMX* amx, long tag, void* ptr);
    int AMXAPI npcamx_StrLen(const cell* cstring, int* length);
    int AMXAPI npcamx_UTF8Check(const char* string, int* length);
    int AMXAPI npcamx_UTF8Get(const char* string, const char** endptr, cell* value);
    int AMXAPI npcamx_UTF8Len(const cell* cstr, int* length);
    int AMXAPI npcamx_UTF8Put(char* string, char** endptr, int maxchars, cell value);

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