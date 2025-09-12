/* ============================================================================ *
 * SA-MP SDK - A Modern C++ SDK for San Andreas Multiplayer Plugin Development  *
 * ============================================================================ *
 *                                                                              *
 * Copyright (c) 2025, SPC (SA-MP Programming Community)                        *
 *                                                                              *
 * Developed by: Calasans                                                       *
 * Provided by: SA-MP Programming Community                                     *
 * License: MIT License                                                         *
 * Repository: https://github.com/spc-samp/samp-sdk                             *
 *                                                                              *
 * ============================================================================ *
 *                                                                              *
 * This SDK provides a modern, high-level C++ abstraction layer over the native *
 * SA-MP Plugin SDK. It is designed to simplify plugin development by offering  *
 * type-safe, object-oriented, and robust interfaces for interacting with the   *
 * SA-MP server and the Pawn scripting environment.                             *
 *                                                                              *
 * --- Core Architecture & Features ---                                         *
 *                                                                              *
 *  - Type-Safe C++ Interface:                                                  *
 *      > Write SA-MP natives and public callbacks as standard C++ functions.   *
 *      > Use C++ types like `int`, `float`, and `std::string` directly.        *
 *                                                                              *
 *  - Automatic Marshalling:                                                    *
 *      > The SDK automatically handles the complex conversion of data types    *
 *        (marshalling) between the C++ environment and the Pawn virtual        *
 *        machine.                                                              *
 *      > Transparently manages memory for strings and reference parameters.    *
 *                                                                              *
 *  - Powerful Hooking Engine:                                                  *
 *      > Seamlessly intercepts Pawn public callbacks using `Plugin_Public`.    *
 *      > Allows multiple plugins built with the SDK to coexist and chain       *
 *        callbacks correctly without interfering with each other.              *
 *      > Supports "Ghost Callbacks" for hooking publics not present in the     *
 *        script.                                                               *
 *                                                                              *
 *  - Simplified Pawn Interaction:                                              *
 *      > Call any Pawn native or public function from C++ with `Pawn(...)`.    *
 *      > The SDK automatically finds the target function (native or public).   *
 *      > Built-in utilities like `Pawn_Format` for easy string formatting.     *
 *                                                                              *
 *  - Dynamic Module System:                                                    *
 *      > Load and unload other plugins/modules dynamically from a host plugin  *
 *        using `Plugin_Module` and `Plugin_Unload_Module`.                     *
 *      > Enables building scalable and maintainable plugin architectures.      *
 *                                                                              *
 *  - Modern C++ Compatibility:                                                 *
 *      > Automatically detects and utilizes features from C++11 to C++20.      *
 *      > Encourages modern C++ practices for safer and more expressive code.   *
 *                                                                              *
 * ============================================================================ *
 *                                                                              *
 * Permission is hereby granted, free of charge, to any person obtaining a copy *
 * of this software and associated documentation files (the "Software"), to     *
 * deal in the Software without restriction, including without limitation the   *
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or  *
 * sell copies of the Software, and to permit persons to whom the Software is   *
 * furnished to do so, subject to the following conditions:                     *
 *                                                                              *
 * The above copyright notice and this permission notice shall be included in   *
 * all copies or substantial portions of the Software.                          *
 *                                                                              *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR   *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,     *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER       *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS *
 * IN THE SOFTWARE.                                                             *
 *                                                                              *
 * ============================================================================ */

#pragma once

#include "amx_api.hpp"
#include "amx_defs.h"
#include "amx_helpers.hpp"
#include "amx_manager.hpp"
#include "amx_memory.hpp"
#include "callbacks.hpp"
#include "core.hpp"
#include "interceptor_manager.hpp"
#include "logger.hpp"
#include "native.hpp"
#include "platform.hpp"
#include "plugin_defs.h"
#include "public_dispatcher.hpp"
#include "samp_defs.hpp"
#include "module_manager.hpp"
#include "dynamic_library.hpp"

bool OnLoad();
void OnUnload();
unsigned int GetSupportFlags();

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxLoad(AMX* amx);
void OnAmxUnload(AMX* amx);
#endif

#if defined(SAMP_SDK_WANT_PROCESS_TICK)
void OnProcessTick();
#endif

#if defined(SAMP_SDK_IMPLEMENTATION)

#if defined(SAMP_SDK_WINDOWS)
    #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
    #pragma comment(linker, "/EXPORT:Load=_Load@4")
    #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
#if defined(SAMP_SDK_WANT_AMX_EVENTS)
    #pragma comment(linker, "/EXPORT:AmxLoad=_AmxLoad@4")
    #pragma comment(linker, "/EXPORT:AmxUnload=_AmxUnload@4")
#endif
#if defined(SAMP_SDK_WANT_PROCESS_TICK)
    #pragma comment(linker, "/EXPORT:ProcessTick=_ProcessTick@0")
#endif
#endif

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
namespace Samp_SDK {
    namespace Detail {
        inline Native_Registry Get_Registered_Natives() {
            return Native_Registry(Native_List_Holder::Instance().Get_Natives());
        }
    }
}
#else
void OnAmxLoad(AMX* amx) { (void)amx; }
void OnAmxUnload(AMX* amx) { (void)amx; }
#endif

#if !defined(SAMP_SDK_WANT_PROCESS_TICK)
void OnProcessTick() {}
#endif

SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() {
    unsigned int flags = GetSupportFlags();

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
    if (!Samp_SDK::Detail::Native_List_Holder::Instance().Get_Natives().empty())
        flags |= SUPPORTS_AMX_NATIVES;
#endif
#if defined(SAMP_SDK_WANT_PROCESS_TICK)
        flags |= SUPPORTS_PROCESS_TICK;
#endif

    return flags;
}

SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) {
    Samp_SDK::Core::Instance().Load(ppData);
    Samp_SDK::Detail::Interceptor_Manager::Instance().Activate();

    return OnLoad();
}

SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() {
    OnUnload();

    Samp_SDK::Detail::Module_Manager::Instance().Unload_All_Modules();
    Samp_SDK::Detail::Interceptor_Manager::Instance().Deactivate();
}

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
SAMP_SDK_EXPORT void SAMP_SDK_CALL AmxLoad(AMX* amx) {
    Samp_SDK::Detail::Get_Registered_Natives().Register_All(amx);

    OnAmxLoad(amx);
}

SAMP_SDK_EXPORT void SAMP_SDK_CALL AmxUnload(AMX* amx) {
    OnAmxUnload(amx);
}
#endif

#if defined(SAMP_SDK_WANT_PROCESS_TICK)
SAMP_SDK_EXPORT void SAMP_SDK_CALL ProcessTick() {
    OnProcessTick();
}
#endif

#endif

#define Plugin_Module(name, path, ...) \
    Samp_SDK::Detail::Module_Manager::Instance().Load_Module(name, path, ##__VA_ARGS__, Samp_SDK::Core::Instance().Get_Plugin_Data())

#define Plugin_Public(name, ...) \
    static cell SAMP_SDK_CALL name(__VA_ARGS__); \
    namespace { \
        PLUGIN_PUBLIC_REGISTRATION(name) \
    } \
    static cell SAMP_SDK_CALL name(__VA_ARGS__)

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
    #define Plugin_Native(name, ...) \
        cell SAMP_SDK_NATIVE_CALL name(__VA_ARGS__); \
        namespace { \
            ::Samp_SDK::Detail::Native_Registrar registrar_##name(#name, name); \
        } \
        cell SAMP_SDK_NATIVE_CALL name(__VA_ARGS__)
    #define Plugin_Call(name, ...) \
        Samp_SDK::Detail::Plugin_Call_Impl(Samp_SDK::Detail::FNV1a_Hash_Const(#name), ##__VA_ARGS__)
#endif

#define Pawn(name, ...)         Samp_SDK::Detail::Caller<Samp_SDK::Pawn_Call_Type::Automatic>::Call(Samp_SDK::Detail::FNV1a_Hash_Const(#name), #name, ##__VA_ARGS__)
#define Pawn_Native(name, ...)  Samp_SDK::Detail::Caller<Samp_SDK::Pawn_Call_Type::Native>::Call(Samp_SDK::Detail::FNV1a_Hash_Const(#name), #name, ##__VA_ARGS__)
#define Pawn_Public(name, ...)  Samp_SDK::Detail::Caller<Samp_SDK::Pawn_Call_Type::Public>::Call(Samp_SDK::Detail::FNV1a_Hash_Const(#name), #name, ##__VA_ARGS__)

#define Plugin_Format(...) Samp_SDK::Format(__VA_ARGS__)
#define Register_Parameters(...) \
    Samp_SDK::Detail::Register_Parameters_Impl(amx, params, __VA_ARGS__)
