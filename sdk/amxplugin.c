/*  SA:MP Multiplayer Modification For GTA:SA
 *
 *  Copyright (c) SA:MP Team, 2004-2007
 *
 *  Copyright (c) SPC (SA-MP Programming Community)
 *  The SA-MP Programming Community holds copyright solely for the improvements
 *  made to this file and does not claim any rights to the original content.
 *  SPC improvements are licensed under the MIT License, available at:
 *  https://opensource.org/licenses/MIT
 */

#include "plugin.h"

static void *pAMXFunctions = NULL;

#if (defined(WIN32) || defined(_WIN32)) && defined(_MSC_VER) && !defined(__64BIT__)
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { _asm { mov eax, pAMXFunctions } _asm { jmp dword ptr[eax + index * 4] } }

    // Unified macro to reduce code duplication for naked functions
    #define DEFINE_AMX_NAKED_FN(name, index) \
        NUDE name { AMX_JUMP_HELPER(index) }

    // Function definitions using the macro
    DEFINE_AMX_NAKED_FN(uint16_t* AMXAPI amx_Align16(uint16_t* v), PLUGIN_AMX_EXPORT_Align16)
    DEFINE_AMX_NAKED_FN(uint32_t* AMXAPI amx_Align32(uint32_t* v), PLUGIN_AMX_EXPORT_Align32)

    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), PLUGIN_AMX_EXPORT_Align64)
    #endif

    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr), PLUGIN_AMX_EXPORT_Allot)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Callback(AMX* amx, cell index, cell* result, const cell* params), PLUGIN_AMX_EXPORT_Callback)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Cleanup(AMX* amx), PLUGIN_AMX_EXPORT_Cleanup)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Clone(AMX* amxClone, AMX* amxSource, void* data), PLUGIN_AMX_EXPORT_Clone)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Exec(AMX* amx, cell* retval, int index), PLUGIN_AMX_EXPORT_Exec)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_FindNative(AMX* amx, const char* name, int* index), PLUGIN_AMX_EXPORT_FindNative)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index), PLUGIN_AMX_EXPORT_FindPublic)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_FindPubVar(AMX* amx, const char* varname, cell* amx_addr), PLUGIN_AMX_EXPORT_FindPubVar)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_FindTagId(AMX* amx, cell tag_id, char* tagname), PLUGIN_AMX_EXPORT_FindTagId)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Flags(AMX* amx, uint16_t* flags), PLUGIN_AMX_EXPORT_Flags)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr), PLUGIN_AMX_EXPORT_GetAddr)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_GetNative(AMX* amx, int index, char* funcname), PLUGIN_AMX_EXPORT_GetNative)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_GetPublic(AMX* amx, int index, char* funcname), PLUGIN_AMX_EXPORT_GetPublic)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_GetPubVar(AMX* amx, int index, char* varname, cell* amx_addr), PLUGIN_AMX_EXPORT_GetPubVar)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_GetString(char* dest, const cell* source, int use_wchar, size_t size), PLUGIN_AMX_EXPORT_GetString)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_GetTag(AMX* amx, int index, char* tagname, cell* tag_id), PLUGIN_AMX_EXPORT_GetTag)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_GetUserData(AMX* amx, long tag, void** ptr), PLUGIN_AMX_EXPORT_GetUserData)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Init(AMX* amx, void* program), PLUGIN_AMX_EXPORT_Init)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code), PLUGIN_AMX_EXPORT_InitJIT)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap), PLUGIN_AMX_EXPORT_MemInfo)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_NameLength(AMX* amx, int* length), PLUGIN_AMX_EXPORT_NameLength)
    DEFINE_AMX_NAKED_FN(AMX_NATIVE_INFO* AMXAPI amx_NativeInfo(const char* name, AMX_NATIVE func), PLUGIN_AMX_EXPORT_NativeInfo)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_NumNatives(AMX* amx, int* number), PLUGIN_AMX_EXPORT_NumNatives)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_NumPublics(AMX* amx, int* number), PLUGIN_AMX_EXPORT_NumPublics)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_NumPubVars(AMX* amx, int* number), PLUGIN_AMX_EXPORT_NumPubVars)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_NumTags(AMX* amx, int* number), PLUGIN_AMX_EXPORT_NumTags)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Push(AMX* amx, cell value), PLUGIN_AMX_EXPORT_Push)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_PushArray(AMX* amx, cell* amx_addr, cell** phys_addr, const cell array[], int numcells), PLUGIN_AMX_EXPORT_PushArray)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_PushString(AMX* amx, cell* amx_addr, cell** phys_addr, const char* string, int pack, int use_wchar), PLUGIN_AMX_EXPORT_PushString)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_RaiseError(AMX* amx, int error), PLUGIN_AMX_EXPORT_RaiseError)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number), PLUGIN_AMX_EXPORT_Register)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_Release(AMX* amx, cell amx_addr), PLUGIN_AMX_EXPORT_Release)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_SetCallback(AMX* amx, AMX_CALLBACK callback), PLUGIN_AMX_EXPORT_SetCallback)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug), PLUGIN_AMX_EXPORT_SetDebugHook)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size), PLUGIN_AMX_EXPORT_SetString)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_SetUserData(AMX* amx, long tag, void* ptr), PLUGIN_AMX_EXPORT_SetUserData)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_StrLen(const cell* cstring, int* length), PLUGIN_AMX_EXPORT_StrLen)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_UTF8Check(const char* string, int* length), PLUGIN_AMX_EXPORT_UTF8Check)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value), PLUGIN_AMX_EXPORT_UTF8Get)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_UTF8Len(const cell* cstr, int* length), PLUGIN_AMX_EXPORT_UTF8Len)
    DEFINE_AMX_NAKED_FN(int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value), PLUGIN_AMX_EXPORT_UTF8Put)
#else
    // Template for function pointer types to reduce code duplication
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }

    DEFINE_AMX_FN_TYPE(amx_Align16, uint16_t*, uint16_t* v)
    DEFINE_AMX_FN_TYPE(amx_Align32, uint32_t*, uint32_t* v)

    #if defined _I64_MAX || defined HAVE_I64
    	DEFINE_AMX_FN_TYPE(amx_Align64, uint64_t*, uint64_t* v)
    #endif

    DEFINE_AMX_FN_TYPE(amx_Allot, int, AMX* amx, int cells, cell* amx_addr, cell** phys_addr)
    DEFINE_AMX_FN_TYPE(amx_Callback, int, AMX* amx, cell index, cell* result, const cell* params)
    DEFINE_AMX_FN_TYPE(amx_Cleanup, int, AMX* amx)
    DEFINE_AMX_FN_TYPE(amx_Clone, int, AMX* amxClone, AMX* amxSource, void* data)
    DEFINE_AMX_FN_TYPE(amx_Exec, int, AMX* amx, cell* retval, int index)
    DEFINE_AMX_FN_TYPE(amx_FindNative, int, AMX* amx, const char* name, int* index)
    DEFINE_AMX_FN_TYPE(amx_FindPublic, int, AMX* amx, const char* funcname, int* index)
    DEFINE_AMX_FN_TYPE(amx_FindPubVar, int, AMX* amx, const char* varname, cell* amx_addr)
    DEFINE_AMX_FN_TYPE(amx_FindTagId, int, AMX* amx, cell tag_id, char* tagname)
    DEFINE_AMX_FN_TYPE(amx_Flags, int, AMX* amx, uint16_t* flags)
    DEFINE_AMX_FN_TYPE(amx_GetAddr, int, AMX* amx, cell amx_addr, cell** phys_addr)
    DEFINE_AMX_FN_TYPE(amx_GetNative, int, AMX* amx, int index, char* funcname)
    DEFINE_AMX_FN_TYPE(amx_GetPublic, int, AMX* amx, int index, char* funcname)
    DEFINE_AMX_FN_TYPE(amx_GetPubVar, int, AMX* amx, int index, char* varname, cell* amx_addr)
    DEFINE_AMX_FN_TYPE(amx_GetString, int, char* dest, const cell* source, int use_wchar, size_t size)
    DEFINE_AMX_FN_TYPE(amx_GetTag, int, AMX* amx, int index, char* tagname, cell* tag_id)
    DEFINE_AMX_FN_TYPE(amx_GetUserData, int, AMX* amx, long tag, void** ptr)
    DEFINE_AMX_FN_TYPE(amx_Init, int, AMX* amx, void* program)
    DEFINE_AMX_FN_TYPE(amx_InitJIT, int, AMX* amx, void* reloc_table, void* native_code)
    DEFINE_AMX_FN_TYPE(amx_MemInfo, int, AMX* amx, long* codesize, long* datasize, long* stackheap)
    DEFINE_AMX_FN_TYPE(amx_NameLength, int, AMX* amx, int* length)
    DEFINE_AMX_FN_TYPE(amx_NativeInfo, AMX_NATIVE_INFO*, const char* name, AMX_NATIVE func)
    DEFINE_AMX_FN_TYPE(amx_NumNatives, int, AMX* amx, int* number)
    DEFINE_AMX_FN_TYPE(amx_NumPublics, int, AMX* amx, int* number)
    DEFINE_AMX_FN_TYPE(amx_NumPubVars, int, AMX* amx, int* number)
    DEFINE_AMX_FN_TYPE(amx_NumTags, int, AMX* amx, int* number)
    DEFINE_AMX_FN_TYPE(amx_Push, int, AMX* amx, cell value)
    DEFINE_AMX_FN_TYPE(amx_PushArray, int, AMX* amx, cell* amx_addr, cell** phys_addr, const cell array[], int numcells)
    DEFINE_AMX_FN_TYPE(amx_PushString, int, AMX* amx, cell* amx_addr, cell** phys_addr, const char* string, int pack, int use_wchar)
    DEFINE_AMX_FN_TYPE(amx_RaiseError, int, AMX* amx, int error)
    DEFINE_AMX_FN_TYPE(amx_Register, int, AMX* amx, const AMX_NATIVE_INFO* nativelist, int number)
    DEFINE_AMX_FN_TYPE(amx_Release, int, AMX* amx, cell amx_addr)
    DEFINE_AMX_FN_TYPE(amx_SetCallback, int, AMX* amx, AMX_CALLBACK callback)
    DEFINE_AMX_FN_TYPE(amx_SetDebugHook, int, AMX* amx, AMX_DEBUG debug)
    DEFINE_AMX_FN_TYPE(amx_SetString, int, cell* dest, const char* source, int pack, int use_wchar, size_t size)
    DEFINE_AMX_FN_TYPE(amx_SetUserData, int, AMX* amx, long tag, void* ptr)
    DEFINE_AMX_FN_TYPE(amx_StrLen, int, const cell* cstring, int* length)
    DEFINE_AMX_FN_TYPE(amx_UTF8Check, int, const char* string, int* length)
    DEFINE_AMX_FN_TYPE(amx_UTF8Get, int, const char* string, const char** endptr, cell* value)
    DEFINE_AMX_FN_TYPE(amx_UTF8Len, int, const cell* cstr, int* length)
    DEFINE_AMX_FN_TYPE(amx_UTF8Put, int, char* string, char** endptr, int maxchars, cell value)
#endif