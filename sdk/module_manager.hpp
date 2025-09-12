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
#include <vector>
#include <memory>
#include <algorithm>
//
#include "dynamic_library.hpp"
#include "logger.hpp"

namespace Samp_SDK {
    namespace Detail {
        using Module_Load_t = bool (SAMP_SDK_CALL *)(void** ppPluginData);
        using Module_Unload_t = void (SAMP_SDK_CALL *)();
        using Module_Supports_t = unsigned int (SAMP_SDK_CALL *)();

        class Module {
            public:
                Module(const std::string& name) : name_(name) {}

                const std::string& Get_Name() const {
                    return name_;
                }

                bool Load(const std::string& path, void** ppData) {
                    if (!library_.Load(path))
                        return false;

                    auto load_func = library_.Get_Function<Module_Load_t>("Load");
                    auto unload_func = library_.Get_Function<Module_Unload_t>("Unload");

                    if (!load_func || !unload_func) {
                        Log("[SAMP-SDK] Error: Module '%s' does not export required 'Load' and 'Unload' functions.", name_.c_str());
                        library_.Unload();

                        return false;
                    }

                    unload_func_ = unload_func;
                    
                    if (!load_func(ppData)) {
                        Log("[SAMP-SDK] Error: Module '%s' failed to initialize (Load function returned false).", name_.c_str());
                        library_.Unload();

                        return false;
                    }

                    return true;
                }

                void Unload() {
                    if (library_.Is_Loaded() && unload_func_) {
                        unload_func_();
                        library_.Unload();
                    }
                }

            private:
                std::string name_;
                Dynamic_Library library_;
                Module_Unload_t unload_func_ = nullptr;
        };

        class Module_Manager {
            public:
                static Module_Manager& Instance() {
                    static Module_Manager instance;

                    return instance;
                }

                bool Load_Module(const std::string& name, const std::string& path, const std::string& success_msg, void** ppData) {
                    auto it = std::find_if(loaded_modules_.begin(), loaded_modules_.end(), [&](const auto& module_ptr) {
                        return module_ptr->Get_Name() == name;
                    });

                    if (it != loaded_modules_.end())
                        return (Log("[SAMP-SDK] Error: A module with the name '%s' is already loaded.", name.c_str()), false);
                    
                    std::string full_path = path;

                    if (!path.empty() && path.back() != '/' && path.back() != '\\')
                        full_path += '/';

                    full_path += name;

#if defined(SAMP_SDK_WINDOWS)
                    full_path += ".dll";
#elif defined(SAMP_SDK_LINUX)
                    full_path += ".so";
#endif

                    auto module = std::make_unique<Module>(name);

                    if (module->Load(full_path, ppData)) {
                        if (!success_msg.empty())
                            Log(success_msg.c_str());

                        loaded_modules_.push_back(std::move(module));

                        return true;
                    }
                    
                    return false;
                }

                void Unload_All_Modules() {
                    for (auto it = loaded_modules_.rbegin(); it != loaded_modules_.rend(); ++it)
                        (*it)->Unload();

                    loaded_modules_.clear();
                }
            private:
                Module_Manager() = default;
                std::vector<std::unique_ptr<Module>> loaded_modules_;
        };
    }
}