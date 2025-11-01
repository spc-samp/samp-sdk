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
 * This file contains an advanced macro for automatically exporting plugin        *
 * functions on the Windows platform without needing a .def file or manual        *
 * linker directives. It simplifies the process of making functions available     *
 * to the SA-MP server.                                                           *
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