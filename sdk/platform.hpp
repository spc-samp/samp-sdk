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

#include <cstdint>
#include <cstddef>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define SAMP_SDK_WINDOWS
#elif defined(LINUX) || defined(__linux__)
    #define SAMP_SDK_LINUX
#else
    #error "Platform not supported. Only Windows and Linux are supported."
#endif

#if defined(SAMP_SDK_WINDOWS) && !defined(_M_IX86)
    #error "This plugin must be compiled for the x86 (32-bit) architecture on Windows. Please check your compiler settings."
#elif (defined(__GNUC__) || defined(__clang__)) && !defined(__i386__)
    #error "This plugin must be compiled for the i386 (32-bit) architecture on Linux. Use the -m32 compiler flag."
#endif

#if defined (__cplusplus)
    #define SAMP_SDK_EXTERN_C extern "C"
#else
    #define SAMP_SDK_EXTERN_C
#endif

#if defined(SAMP_SDK_WINDOWS)
    #define SAMP_SDK_AMX_API
    #define SAMP_SDK_NATIVE_CALL
    #define SAMP_SDK_CALL __stdcall
    #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
    #define SAMP_SDK_FORCE_INLINE __forceinline
#else
    #define SAMP_SDK_AMX_API
    #define SAMP_SDK_NATIVE_CALL
    #define SAMP_SDK_CALL
    #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
    #define SAMP_SDK_FORCE_INLINE __attribute__((always_inline)) inline
#endif

#if defined(__cplusplus) && __cplusplus >= 202002L
    #define SAMP_SDK_LIKELY(x) (x) [[likely]]
    #define SAMP_SDK_UNLIKELY(x) (x) [[unlikely]]
#elif defined(__GNUC__) || defined(__clang__)
    #define SAMP_SDK_LIKELY(x) __builtin_expect(!!(x), 1)
    #define SAMP_SDK_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define SAMP_SDK_LIKELY(x) (x)
    #define SAMP_SDK_UNLIKELY(x) (x)
#endif