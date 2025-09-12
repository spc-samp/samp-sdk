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

#if defined(__cplusplus)

#if (defined(_MSC_VER) && _MSVC_LANG >= 201402L) || __cplusplus >= 201402L
    #define SAMP_SDK_CXX14
#endif

#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_SDK_CXX_MODERN
#endif

#endif