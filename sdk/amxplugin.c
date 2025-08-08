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

void *pAMXFunctions = NULL;

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
    uint16_t* AMXAPI amx_Align16(uint16_t* v) {
        typedef uint16_t* (AMXAPI *func_t)(uint16_t*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align16](v);
    }

    uint32_t* AMXAPI amx_Align32(uint32_t* v) {
        typedef uint32_t* (AMXAPI *func_t)(uint32_t*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align32](v);
    }
    
#if defined _I64_MAX || defined HAVE_I64
    uint64_t* AMXAPI amx_Align64(uint64_t* v) {
        typedef uint64_t* (AMXAPI *func_t)(uint64_t*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align64](v);
    }
#endif

    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr) {
        typedef int (AMXAPI *func_t)(AMX*, int, cell*, cell**);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Allot](amx, cells, amx_addr, phys_addr);
    }

    int AMXAPI amx_Callback(AMX* amx, cell index, cell* result, const cell* params) {
        typedef int (AMXAPI *func_t)(AMX*, cell, cell*, const cell*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Callback](amx, index, result, params);
    }

    int AMXAPI amx_Cleanup(AMX* amx) {
        typedef int (AMXAPI *func_t)(AMX*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Cleanup](amx);
    }

    int AMXAPI amx_Clone(AMX* amxClone, AMX* amxSource, void* data) {
        typedef int (AMXAPI *func_t)(AMX*, AMX*, void*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Clone](amxClone, amxSource, data);
    }

    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index) {
        typedef int (AMXAPI *func_t)(AMX*, cell*, int);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Exec](amx, retval, index);
    }

    int AMXAPI amx_FindNative(AMX* amx, const char* name, int* index) {
        typedef int (AMXAPI *func_t)(AMX*, const char*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindNative](amx, name, index);
    }

    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index) {
        typedef int (AMXAPI *func_t)(AMX*, const char*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindPublic](amx, funcname, index);
    }

    int AMXAPI amx_FindPubVar(AMX* amx, const char* varname, cell* amx_addr) {
        typedef int (AMXAPI *func_t)(AMX*, const char*, cell*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindPubVar](amx, varname, amx_addr);
    }

    int AMXAPI amx_FindTagId(AMX* amx, cell tag_id, char* tagname) {
        typedef int (AMXAPI *func_t)(AMX*, cell, char*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindTagId](amx, tag_id, tagname);
    }

    int AMXAPI amx_Flags(AMX* amx, uint16_t* flags) {
        typedef int (AMXAPI *func_t)(AMX*, uint16_t*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Flags](amx, flags);
    }

    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr) {
        typedef int (AMXAPI *func_t)(AMX*, cell, cell**);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetAddr](amx, amx_addr, phys_addr);
    }

    int AMXAPI amx_GetNative(AMX* amx, int index, char* funcname) {
        typedef int (AMXAPI *func_t)(AMX*, int, char*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetNative](amx, index, funcname);
    }

    int AMXAPI amx_GetPublic(AMX* amx, int index, char* funcname) {
        typedef int (AMXAPI *func_t)(AMX*, int, char*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetPublic](amx, index, funcname);
    }

    int AMXAPI amx_GetPubVar(AMX* amx, int index, char* varname, cell* amx_addr) {
        typedef int (AMXAPI *func_t)(AMX*, int, char*, cell*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetPubVar](amx, index, varname, amx_addr);
    }

    int AMXAPI amx_GetString(char* dest, const cell* source, int use_wchar, size_t size) {
        typedef int (AMXAPI *func_t)(char*, const cell*, int, size_t);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetString](dest, source, use_wchar, size);
    }

    int AMXAPI amx_GetTag(AMX* amx, int index, char* tagname, cell* tag_id) {
        typedef int (AMXAPI *func_t)(AMX*, int, char*, cell*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetTag](amx, index, tagname, tag_id);
    }

    int AMXAPI amx_GetUserData(AMX* amx, long tag, void** ptr) {
        typedef int (AMXAPI *func_t)(AMX*, long, void**);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetUserData](amx, tag, ptr);
    }

    int AMXAPI amx_Init(AMX* amx, void* program) {
        typedef int (AMXAPI *func_t)(AMX*, void*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Init](amx, program);
    }

    int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code) {
        typedef int (AMXAPI *func_t)(AMX*, void*, void*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_InitJIT](amx, reloc_table, native_code);
    }
    
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap) {
        typedef int (AMXAPI *func_t)(AMX*, long*, long*, long*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_MemInfo](amx, codesize, datasize, stackheap);
    }

    int AMXAPI amx_NameLength(AMX* amx, int* length) {
        typedef int (AMXAPI *func_t)(AMX*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NameLength](amx, length);
    }

    AMX_NATIVE_INFO* AMXAPI amx_NativeInfo(const char* name, AMX_NATIVE func) {
        typedef AMX_NATIVE_INFO* (AMXAPI *func_t)(const char*, AMX_NATIVE);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NativeInfo](name, func);
    }

    int AMXAPI amx_NumNatives(AMX* amx, int* number) {
        typedef int (AMXAPI *func_t)(AMX*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NumNatives](amx, number);
    }

    int AMXAPI amx_NumPublics(AMX* amx, int* number) {
        typedef int (AMXAPI *func_t)(AMX*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NumPublics](amx, number);
    }

    int AMXAPI amx_NumPubVars(AMX* amx, int* number) {
        typedef int (AMXAPI *func_t)(AMX*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NumPubVars](amx, number);
    }

    int AMXAPI amx_NumTags(AMX* amx, int* number) {
        typedef int (AMXAPI *func_t)(AMX*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_NumTags](amx, number);
    }

    int AMXAPI amx_Push(AMX* amx, cell value) {
        typedef int (AMXAPI *func_t)(AMX*, cell);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Push](amx, value);
    }
    
    int AMXAPI amx_PushArray(AMX* amx, cell* amx_addr, cell** phys_addr, const cell array[], int numcells) {
        typedef int (AMXAPI *func_t)(AMX*, cell*, cell**, const cell*, int);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_PushArray](amx, amx_addr, phys_addr, array, numcells);
    }

    int AMXAPI amx_PushString(AMX* amx, cell* amx_addr, cell** phys_addr, const char* string, int pack, int use_wchar) {
        typedef int (AMXAPI *func_t)(AMX*, cell*, cell**, const char*, int, int);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_PushString](amx, amx_addr, phys_addr, string, pack, use_wchar);
    }

    int AMXAPI amx_RaiseError(AMX* amx, int error) {
        typedef int (AMXAPI *func_t)(AMX*, int);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_RaiseError](amx, error);
    }

    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number) {
        typedef int (AMXAPI *func_t)(AMX*, const AMX_NATIVE_INFO*, int);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Register](amx, nativelist, number);
    }

    int AMXAPI amx_Release(AMX* amx, cell amx_addr) {
        typedef int (AMXAPI *func_t)(AMX*, cell);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_Release](amx, amx_addr);
    }

    int AMXAPI amx_SetCallback(AMX* amx, AMX_CALLBACK callback) {
        typedef int (AMXAPI *func_t)(AMX*, AMX_CALLBACK);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_SetCallback](amx, callback);
    }

    int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug) {
        typedef int (AMXAPI *func_t)(AMX*, AMX_DEBUG);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_SetDebugHook](amx, debug);
    }

    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size) {
        typedef int (AMXAPI *func_t)(cell*, const char*, int, int, size_t);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_SetString](dest, source, pack, use_wchar, size);
    }

    int AMXAPI amx_SetUserData(AMX* amx, long tag, void* ptr) {
        typedef int (AMXAPI *func_t)(AMX*, long, void*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_SetUserData](amx, tag, ptr);
    }

    int AMXAPI amx_StrLen(const cell* cstring, int* length) {
        typedef int (AMXAPI *func_t)(const cell*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_StrLen](cstring, length);
    }

    int AMXAPI amx_UTF8Check(const char* string, int* length) {
        typedef int (AMXAPI *func_t)(const char*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_UTF8Check](string, length);
    }

    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value) {
        typedef int (AMXAPI *func_t)(const char*, const char**, cell*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_UTF8Get](string, endptr, value);
    }

    int AMXAPI amx_UTF8Len(const cell* cstr, int* length) {
        typedef int (AMXAPI *func_t)(const cell*, int*);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_UTF8Len](cstr, length);
    }

    int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value) {
        typedef int (AMXAPI *func_t)(char*, char**, int, cell);

        return ((func_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_UTF8Put](string, endptr, maxchars, value);
    }
#endif