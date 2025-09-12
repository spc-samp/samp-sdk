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

#include <string>
#include <atomic>
#include <mutex>
#include <unordered_map>
#include <memory>
//
#include "amx_api.hpp"
#include "amx_defs.h"
#include "amx_manager.hpp"
#include "core.hpp"
#include "function_hook.hpp"
#include "hash.hpp"
#include "public_dispatcher.hpp"
#include "version.hpp"
//
#if defined(SAMP_SDK_CXX_MODERN)
    #include <shared_mutex>
#endif

constexpr int PLUGIN_EXEC_GHOST_PUBLIC = -10;

namespace Samp_SDK {
    namespace Detail {
        int SAMP_SDK_AMX_API Amx_Register_Detour(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
        int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index);
        int SAMP_SDK_AMX_API Amx_Init_Detour(AMX *amx, void *program);
        int SAMP_SDK_AMX_API Amx_Cleanup_Detour(AMX *amx);
        int SAMP_SDK_AMX_API Amx_Find_Public_Detour(AMX* amx, const char* name, int* index);
        
#if defined(_M_IX86) || defined(__i386__)
        inline Function_Hook<amx::Register_t>& Get_Amx_Register_Hook() {
            static Function_Hook<amx::Register_t> hook;

            return hook;
        }
        inline Function_Hook<amx::Exec_t>& Get_Amx_Exec_Hook() {
            static Function_Hook<amx::Exec_t> hook;
            
            return hook;
        }
        inline Function_Hook<amx::Init_t>& Get_Amx_Init_Hook() {
            static Function_Hook<amx::Init_t> hook;

            return hook;
        }
        inline Function_Hook<amx::Cleanup_t>& Get_Amx_Cleanup_Hook() {
            static Function_Hook<amx::Cleanup_t> hook;

            return hook;
        }
        inline Function_Hook<amx::Find_Public_t>& Get_Amx_Find_Public_Hook() {
            static Function_Hook<amx::Find_Public_t> hook;
            
            return hook;
        }
#endif

        static thread_local std::unique_ptr<std::string> tl_public_name;

        SAMP_SDK_FORCE_INLINE const char* Get_Public_Name_By_Index(AMX* amx, int index) {
            if (!amx || !amx->base || index < 0)
                return nullptr;

            AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);

            if (hdr->magic != AMX_MAGIC)
                return nullptr;

            int num_publics = (hdr->natives - hdr->publics) / sizeof(AMX_FUNCSTUBNT);

            if (index >= num_publics)
                return nullptr;

            AMX_FUNCSTUBNT* public_tbl = reinterpret_cast<AMX_FUNCSTUBNT*>(amx->base + hdr->publics);

            return reinterpret_cast<const char*>(amx->base + public_tbl[index].nameofs);
        }

        class Interceptor_Manager {
            public:
                static Interceptor_Manager& Instance() {
                    static Interceptor_Manager instance;

                    return instance;
                }

                void Activate() {
#if defined(_M_IX86) || defined(__i386__)
                    void* register_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Register);
                    void* exec_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec);
                    void* init_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Init);
                    void* cleanup_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Cleanup);
                    void* find_public_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_FindPublic);
                    
                    if (register_func && exec_func && init_func && cleanup_func && find_public_func) {
                        Get_Amx_Init_Hook().Install(init_func, reinterpret_cast<void*>(Amx_Init_Detour));
                        Get_Amx_Cleanup_Hook().Install(cleanup_func, reinterpret_cast<void*>(Amx_Cleanup_Detour));
                        Get_Amx_Register_Hook().Install(register_func, reinterpret_cast<void*>(Amx_Register_Detour));
                        Get_Amx_Find_Public_Hook().Install(find_public_func, reinterpret_cast<void*>(Amx_Find_Public_Detour));
                        Get_Amx_Exec_Hook().Install(exec_func, reinterpret_cast<void*>(Amx_Exec_Detour));
                    }
                    else
                        Core::Instance().Log("[SAMP SDK] Fatal: Failed to activate core interceptors, pAMXFunctions not available.");
#else
                    Core::Instance().Log("[SAMP SDK] Warning: Core AMX interception is not supported on this architecture.");
#endif
                }

                void Deactivate() {
#if defined(_M_IX86) || defined(__i386__)
                    Get_Amx_Register_Hook().Uninstall();
                    Get_Amx_Exec_Hook().Uninstall();
                    Get_Amx_Init_Hook().Uninstall();
                    Get_Amx_Cleanup_Hook().Uninstall();
                    Get_Amx_Find_Public_Hook().Uninstall();
#endif
                }
                
                void Cache_Natives(const AMX_NATIVE_INFO* nativelist, int number) {
                    auto& cache_data = Get_Cache_Data();
                    std::lock_guard<std::mutex> lock(cache_data.mtx);

                    for (int i = 0; (number == -1 || i < number) && nativelist[i].name != nullptr; ++i)
                        cache_data.native_cache[FNV1a_Hash(nativelist[i].name)] = nativelist[i].func;
                }

                AMX_NATIVE Find_Cached_Native(uint32_t hash) {
                    auto& cache_data = Get_Cache_Data();
                    std::lock_guard<std::mutex> lock(cache_data.mtx);
                    auto it = cache_data.native_cache.find(hash);

                    return (it != cache_data.native_cache.end()) ? it->second : nullptr;
                }

                void Set_Gamemode_Amx(AMX* amx) {
                    gamemode_amx_ = amx;
                }

                bool Is_Gamemode_Amx(AMX* amx) const {
                    return amx == gamemode_amx_;
                }
            private:
                Interceptor_Manager() : gamemode_amx_(nullptr) {}
                ~Interceptor_Manager() = default;

                struct Cache_Data {
                    std::unordered_map<uint32_t, AMX_NATIVE> native_cache;
                    std::mutex mtx;
                };

                static Cache_Data& Get_Cache_Data() {
                    static Cache_Data data;

                    return data;
                }

                AMX* gamemode_amx_;
        };

        inline int SAMP_SDK_AMX_API Amx_Init_Detour(AMX *amx, void *program) {
            int result = Get_Amx_Init_Hook().Call_Original(amx, program);
            
            if (result == static_cast<int>(AmxError::None))
                Amx_Manager::Instance().Add_Amx(amx);

            return result;
        }

        inline int SAMP_SDK_AMX_API Amx_Cleanup_Detour(AMX *amx) {
            return (Amx_Manager::Instance().Remove_Amx(amx), Get_Amx_Cleanup_Hook().Call_Original(amx));
        }

        inline int SAMP_SDK_AMX_API Amx_Register_Detour(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number) {
            return (Interceptor_Manager::Instance().Cache_Natives(nativelist, number), Get_Amx_Register_Hook().Call_Original(amx, nativelist, number));
        }

        inline int SAMP_SDK_AMX_API Amx_Find_Public_Detour(AMX* amx, const char* name, int* index) {
            int error = Get_Amx_Find_Public_Hook().Call_Original(amx, name, index);

            if (Interceptor_Manager::Instance().Is_Gamemode_Amx(amx)) {
                tl_public_name = std::make_unique<std::string>(name);

                if (error != static_cast<int>(AmxError::None)) {
                    if (Public_Dispatcher::Instance().Has_Handler(FNV1a_Hash(name)))
                        return (*index = PLUGIN_EXEC_GHOST_PUBLIC, static_cast<int>(AmxError::None));
                }
            }

            return error;
        }
        
        inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
            auto& manager = Interceptor_Manager::Instance();
            std::unique_ptr<std::string> public_name_ptr;

            if (index == AMX_EXEC_MAIN) {
                manager.Set_Gamemode_Amx(amx);
                public_name_ptr = std::make_unique<std::string>("OnGameModeInit");
            }
            else if (manager.Is_Gamemode_Amx(amx) && index != AMX_EXEC_CONT) {
                if (tl_public_name)
                    public_name_ptr = std::move(tl_public_name);
            }

            if (public_name_ptr) {
                cell result = 1;
                bool should_continue = Public_Dispatcher::Instance().Dispatch(FNV1a_Hash(public_name_ptr->c_str()), amx, result);
                
                if (!should_continue) {
                    if (retval)
                        *retval = result;

                    if (*public_name_ptr == "OnPlayerCommandText") {
                        if (retval)
                            *retval = 1;
                    }

                    amx->stk += amx->paramcount * sizeof(cell);
                    amx->paramcount = 0;
                    
                    return static_cast<int>(AmxError::None);
                }
            }
            
            return Get_Amx_Exec_Hook().Call_Original(amx, retval, index);
        }
    }
}