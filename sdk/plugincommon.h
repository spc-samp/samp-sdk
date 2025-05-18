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

#ifndef _PLUGINCOMMON_H_INCLUDED
    #define _PLUGINCOMMON_H_INCLUDED

    #define SAMP_PLUGIN_VERSION 0x0200

    #ifdef __cplusplus
        #define PLUGIN_EXTERN_C extern "C"
    #else
        #define PLUGIN_EXTERN_C
    #endif

    #if defined(LINUX) || defined(FREEBSD) || defined(__FreeBSD__) || defined(__OpenBSD__)
        #ifdef __GNUC__
            #define PLUGIN_CALL __attribute__((cdecl))
            #ifndef SAMPSVR
                #define PLUGIN_EXPORT PLUGIN_EXTERN_C __attribute__((visibility("default")))
            #else
                #define PLUGIN_EXPORT PLUGIN_EXTERN_C
            #endif
        #else
            #define PLUGIN_CALL
            #define PLUGIN_EXPORT PLUGIN_EXTERN_C
        #endif
    #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
        #define PLUGIN_CALL __stdcall
        #define PLUGIN_EXPORT PLUGIN_EXTERN_C __declspec(dllexport)
    #else
        #error "Unsupported platform: Define either WIN32, LINUX, or FREEBSD"
    #endif

    enum SUPPORTS_FLAGS {
        SUPPORTS_VERSION = SAMP_PLUGIN_VERSION,
        SUPPORTS_VERSION_MASK = 0xffff,
        SUPPORTS_AMX_NATIVES = 0x10000,
        SUPPORTS_PROCESS_TICK = 0x20000
    };

    enum PLUGIN_DATA_TYPE {
        PLUGIN_DATA_LOGPRINTF = 0x00,
        PLUGIN_DATA_AMX_EXPORTS = 0x10,
        PLUGIN_DATA_CALLPUBLIC_FS = 0x11,
        PLUGIN_DATA_CALLPUBLIC_GM = 0x12
    };

    enum PLUGIN_AMX_EXPORT {
        PLUGIN_AMX_EXPORT_Align16,
        PLUGIN_AMX_EXPORT_Align32,
        PLUGIN_AMX_EXPORT_Align64,
        PLUGIN_AMX_EXPORT_Allot,
        PLUGIN_AMX_EXPORT_Callback,
        PLUGIN_AMX_EXPORT_Cleanup,
        PLUGIN_AMX_EXPORT_Clone,
        PLUGIN_AMX_EXPORT_Exec,
        PLUGIN_AMX_EXPORT_FindNative,
        PLUGIN_AMX_EXPORT_FindPublic,
        PLUGIN_AMX_EXPORT_FindPubVar,
        PLUGIN_AMX_EXPORT_FindTagId,
        PLUGIN_AMX_EXPORT_Flags,
        PLUGIN_AMX_EXPORT_GetAddr,
        PLUGIN_AMX_EXPORT_GetNative,
        PLUGIN_AMX_EXPORT_GetPublic,
        PLUGIN_AMX_EXPORT_GetPubVar,
        PLUGIN_AMX_EXPORT_GetString,
        PLUGIN_AMX_EXPORT_GetTag,
        PLUGIN_AMX_EXPORT_GetUserData,
        PLUGIN_AMX_EXPORT_Init,
        PLUGIN_AMX_EXPORT_InitJIT,
        PLUGIN_AMX_EXPORT_MemInfo,
        PLUGIN_AMX_EXPORT_NameLength,
        PLUGIN_AMX_EXPORT_NativeInfo,
        PLUGIN_AMX_EXPORT_NumNatives,
        PLUGIN_AMX_EXPORT_NumPublics,
        PLUGIN_AMX_EXPORT_NumPubVars,
        PLUGIN_AMX_EXPORT_NumTags,
        PLUGIN_AMX_EXPORT_Push,
        PLUGIN_AMX_EXPORT_PushArray,
        PLUGIN_AMX_EXPORT_PushString,
        PLUGIN_AMX_EXPORT_RaiseError,
        PLUGIN_AMX_EXPORT_Register,
        PLUGIN_AMX_EXPORT_Release,
        PLUGIN_AMX_EXPORT_SetCallback,
        PLUGIN_AMX_EXPORT_SetDebugHook,
        PLUGIN_AMX_EXPORT_SetString,
        PLUGIN_AMX_EXPORT_SetUserData,
        PLUGIN_AMX_EXPORT_StrLen,
        PLUGIN_AMX_EXPORT_UTF8Check,
        PLUGIN_AMX_EXPORT_UTF8Get,
        PLUGIN_AMX_EXPORT_UTF8Len,
        PLUGIN_AMX_EXPORT_UTF8Put
    };
#endif