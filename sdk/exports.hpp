/* ============================================================================== *
 * SA-MP SDK - A Modern C++ SDK for San Andreas Multiplayer Plugin Development    *
 * ============================================================================== *
 *                                                                                *
 * Copyright (c) 2025, SPC (SA-MP Programming Community)                          *
 *                                                                                *
 * Developed by: Calasans                                                         *
 * Provided by: SA-MP Programming Community                                       *
 * License: MIT License                                                           *
 * Repository: https://github.com/spc-samp/samp-sdk                               *
 *                                                                                *
 * ============================================================================== *
 *                                                                                *
 * This SDK provides a modern, high-level C++ abstraction layer over the native   *
 * SA-MP Plugin SDK. It is designed to simplify plugin development by offering    *
 * type-safe, object-oriented, and robust interfaces for interacting with the     *
 * SA-MP server and the Pawn scripting environment.                               *
 *                                                                                *
 * --- Core Architecture & Features ---                                           *
 *                                                                                *
 *  - Type-Safe C++ Interface:                                                    *
 *      > Write SA-MP natives and public callbacks as standard C++ functions.     *
 *      > Use C++ types like `int`, `float`, and `std::string` directly.          *
 *                                                                                *
 *  - Automatic Marshalling:                                                      *
 *      > The SDK automatically handles the complex conversion of data types      *
 *        (marshalling) between the C++ environment and the Pawn virtual          *
 *        machine.                                                                *
 *      > Transparently manages memory for strings and reference parameters.      *
 *                                                                                *
 *  - Powerful Hooking Engine:                                                    *
 *      > Seamlessly intercepts both Pawn public callbacks (with `Plugin_Public`) *
 *        and natives (with `Plugin_Native_Hook`).                                *
 *      > Allows multiple plugins built with the SDK to coexist and chain         *
 *        callbacks/hooks correctly without interfering with each other.          *
 *      > Supports "Ghost Callbacks" for hooking publics not present in the       *
 *        script.                                                                 *
 *                                                                                *
 *  - Simplified Pawn Interaction:                                                *
 *      > Call any Pawn native or public function from C++ with `Pawn(...)`.      *
 *      > The SDK automatically finds the target function (native or public).     *
 *      > Built-in utilities like `Pawn_Format` for easy string formatting.       *
 *                                                                                *
 *  - Dynamic Module System:                                                      *
 *      > Load and unload other plugins/modules dynamically from a host plugin    *
 *        using `Plugin_Module` and `Plugin_Unload_Module`.                       *
 *      > Enables building scalable and maintainable plugin architectures.        *
 *                                                                                *
 *  - Modern C++ Compatibility:                                                   *
 *      > Requires C++14 and automatically utilizes features up to C++20.         *
 *      > Encourages modern C++ practices for safer and more expressive code.     *
 *                                                                                *
 * ============================================================================== *
 *                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to       *
 * deal in the Software without restriction, including without limitation the     *
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or    *
 * sell copies of the Software, and to permit persons to whom the Software is     *
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in     *
 * all copies or substantial portions of the Software.                            *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING        *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS   *
 * IN THE SOFTWARE.                                                               *
 *                                                                                *
 * ============================================================================== */

#pragma once

#include "platform.hpp"

#if defined(SAMP_SDK_WINDOWS)
    #if defined(SAMP_SDK_COMPILER_MSVC)
        // This macro tells the Microsoft Visual C++ linker to export a function
        // from the DLL. It takes the function's name as a string literal
        // and the stack size of its arguments (in bytes) as a string literal.
        // The linker will automatically handle the name decoration (e.g., _MyFunction@StackSize)
        // and export it with the clean name provided.
        //
        // Example: Export_Plugin("MyFunction", "4") becomes #pragma comment(linker, "/EXPORT:MyFunction=_MyFunction@4")
        #define SAMP_SDK_EXPORT_PLUGIN(function_name_str, stack_size_str) \
            __pragma(comment(linker, "/EXPORT:" function_name_str "=_" function_name_str "@" stack_size_str))
    #else
        // For compilers other than MSVC (like GCC/Clang on Windows via MinGW),
        // function exports are handled by the SAMP_SDK_EXPORT macro in platform.hpp
        // using __attribute__((dllexport)). This macro does nothing for them.
        #define SAMP_SDK_EXPORT_PLUGIN(function_name_str, stack_size_str)
    #endif
#else
    // On non-Windows platforms (Linux), function visibility is handled differently
    // (e.g., with __attribute__((visibility("default")))), so this macro is not needed.
    #define SAMP_SDK_EXPORT_PLUGIN(function_name_str, stack_size_str)
#endif

// User-friendly alias for the SDK's export macro.
// Note: This macro is primarily for MSVC users. For GCC/Clang on Windows,
// use SAMP_SDK_EXPORT directly on the function declaration.
#define Export_Plugin(function_name_str, stack_size_str) SAMP_SDK_EXPORT_PLUGIN(function_name_str, stack_size_str)
