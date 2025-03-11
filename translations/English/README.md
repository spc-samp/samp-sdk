# samp-sdk

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Language](https://img.shields.io/badge/Language-C-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![SDK](https://img.shields.io/badge/SA--MP-SDK-orange.svg)](https://github.com/spc-samp/samp-sdk)
[![Platform Windows](https://img.shields.io/badge/Windows-0078D6?style=flat&logo=windows&logoColor=white)](https://github.com/spc-samp/samp-sdk)
[![Platform Linux](https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black)](https://github.com/spc-samp/samp-sdk)
[![Platform FreeBSD](https://img.shields.io/badge/FreeBSD-AB2B28?style=flat&logo=freebsd&logoColor=white)](https://github.com/spc-samp/samp-sdk)
[![AMX](https://img.shields.io/badge/AMX-Powered-yellow.svg)](https://github.com/spc-samp/samp-sdk)
[![Native Support](https://img.shields.io/badge/Natives-Supported-success.svg)](https://github.com/spc-samp/samp-sdk)
[![Memory Safe](https://img.shields.io/badge/Memory-Safe-red.svg)](https://github.com/spc-samp/samp-sdk)

The SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) is a comprehensive collection of C files, headers, and components that enable developers to create plugins for the SA-MP server. This SDK provides a foundation for extending the functionality of the SA-MP server through native functions, allowing developers to implement features beyond what is available in Pawn scripts.

## Languages

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Index

- [samp-sdk](#samp-sdk)
  - [Languages](#languages)
  - [Index](#index)
  - [Core Components](#core-components)
    - [AMX System](#amx-system)
      - [Core AMX Headers](#core-amx-headers)
    - [Platform Support](#platform-support)
    - [Plugin System](#plugin-system)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [AMX Native Functions](#amx-native-functions)
  - [Technical Details](#technical-details)
    - [Memory Management](#memory-management)
    - [Memory Operations](#memory-operations)
    - [Error Handling](#error-handling)
    - [String Handling](#string-handling)
    - [String Operations](#string-operations)
  - [Unicode Support](#unicode-support)
    - [Unicode Operations](#unicode-operations)
  - [Cross-Platform Compatibility](#cross-platform-compatibility)
  - [System Requirements](#system-requirements)
    - [Compiler Support](#compiler-support)
  - [Best Practices](#best-practices)
  - [Internal Structures](#internal-structures)
    - [AMX Header Structure](#amx-header-structure)
  - [Advanced Features](#advanced-features)
    - [JIT Compilation Support](#jit-compilation-support)
    - [Debug Interface](#debug-interface)
    - [Public Function Interface](#public-function-interface)
  - [Version Information](#version-information)
    - [Version Compatibility](#version-compatibility)
  - [License](#license)
    - [Terms and Conditions of Use](#terms-and-conditions-of-use)
      - [1. Granted Permissions](#1-granted-permissions)
      - [2. Mandatory Conditions](#2-mandatory-conditions)
      - [3. Copyright](#3-copyright)
      - [4. Disclaimer of Warranty and Limitation of Liability](#4-disclaimer-of-warranty-and-limitation-of-liability)

## Core Components

### AMX System

The AMX (Abstract Machine eXecutor) is the virtual machine that executes Pawn scripts in SA-MP. The SDK provides extensive support for interacting with the AMX system through various C files and headers.

#### Core AMX Headers

1. **amx.h**

    The primary header that consolidates all AMX-related functionality:
    - Core AMX functions for script execution
    - Memory management
    - Native function registration
    - String handling
    - UTF-8 support

    Key functions include:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);         // Initializes an AMX instance
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index); // Executes a public function
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number); // Registers native functions
    ```

2. **amx_platform.h**

    Responsible for platform detection and configuration:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```
    - Detects systems such as Linux, FreeBSD, OpenBSD, and macOS.
    - Includes `sclinux.h` for Unix-like systems.
    - Identifies 64-bit architectures:
      ```c
      #if defined _LP64 || defined WIN64 || defined _WIN64
          #define __64BIT__
      #endif
      ```
    - Calculates GCC version if applicable:
      ```c
      #if defined __GNUC__
          #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #endif
      ```

3. **amx_constants.h**

    Defines essential constants for AMX operation:
    - **Versions**:
      ```c
      #define CUR_FILE_VERSION  9   // Current file format version
      #define MIN_FILE_VERSION  6   // Minimum supported version
      #define MIN_AMX_VERSION   10  // Minimum AMX version
      #define MAX_FILE_VER_JIT  8   // Maximum version with JIT support
      #define MIN_AMX_VER_JIT   8   // Minimum version with JIT support
      ```
    - **Magic Codes**:
      ```c
      #define AMX_MAGIC_16    0xf1e2  // For 16-bit cells
      #define AMX_MAGIC_32    0xf1e0  // For 32-bit cells
      #define AMX_MAGIC_64    0xf1e1  // For 64-bit cells
      ```
    - **Error Codes**:
      ```c
      enum {
          AMX_ERR_NONE,         // No error
          AMX_ERR_EXIT,         // Script terminated
          AMX_ERR_ASSERT,       // Assertion failed
          AMX_ERR_STACKERR,     // Stack error
          AMX_ERR_BOUNDS,       // Out-of-bounds access
          AMX_ERR_MEMACCESS,    // Invalid memory access
          AMX_ERR_INVINSTR,     // Invalid instruction
          AMX_ERR_STACKLOW,     // Stack too low
          AMX_ERR_HEAPLOW,      // Heap too low
          AMX_ERR_CALLBACK,     // Callback error
          AMX_ERR_NATIVE,       // Native function error
          AMX_ERR_DIVIDE,       // Division by zero
          AMX_ERR_SLEEP,        // Sleep mode activated
          AMX_ERR_INVSTATE,     // Invalid state
          AMX_ERR_MEMORY = 16,  // Insufficient memory
          AMX_ERR_FORMAT,       // Invalid format
          AMX_ERR_VERSION,      // Incompatible version
          AMX_ERR_NOTFOUND,     // Resource not found
          AMX_ERR_INDEX,        // Invalid index
          AMX_ERR_DEBUG,        // Debugging error
          AMX_ERR_INIT,         // Initialization failure
          AMX_ERR_USERDATA,     // User data error
          AMX_ERR_INIT_JIT,     // JIT initialization failure
          AMX_ERR_PARAMS,       // Invalid parameters
          AMX_ERR_DOMAIN,       // Domain error
          AMX_ERR_GENERAL,      // General error
      };
      ```
    - **Flags**:
      ```c
      #define AMX_FLAG_DEBUG      0x02   // Debug mode
      #define AMX_FLAG_COMPACT    0x04   // Compact encoding
      #define AMX_FLAG_SLEEP      0x08   // Sleep support
      #define AMX_FLAG_NOCHECKS   0x10   // No safety checks
      #define AMX_FLAG_NO_RELOC   0x200  // No relocation
      #define AMX_FLAG_NO_SYSREQD 0x400  // No sysreq.d
      #define AMX_FLAG_SYSREQN    0x800  // sysreq.n support
      #define AMX_FLAG_NTVREG     0x1000 // Native registration
      #define AMX_FLAG_JITC       0x2000 // JIT compilation
      #define AMX_FLAG_BROWSE     0x4000 // Browse mode
      #define AMX_FLAG_RELOC      0x8000 // Relocation enabled
      ```
    - **Execution Codes**:
      ```c
      #define AMX_EXEC_MAIN   (-1)  // Execute main function
      #define AMX_EXEC_CONT   (-2)  // Continue execution
      ```

4. **amx_memory.h**

    Manages memory allocation:
    - Support for `alloca`:
      ```c
      #if defined HAVE_ALLOCA_H
          #include <alloca.h>
      #elif defined __BORLANDC__
          #include <malloc.h>
      #endif
      #if defined __WIN32__ || defined _WIN32 || defined WIN32
          #define alloca(n)   _alloca(n)
      #endif
      ```
    - Defines compression margin:
      ```c
      #if !defined AMX_COMPACTMARGIN
          #define AMX_COMPACTMARGIN 64
      #endif
      ```

5. **amx_calling.h**

    Defines calling conventions:
    - For native functions and APIs:
      ```c
      #if defined PAWN_DLL
          #define AMX_NATIVE_CALL __stdcall
          #define AMXAPI          __stdcall
      #endif
      #if !defined AMX_NATIVE_CALL
          #define AMX_NATIVE_CALL
      #endif
      #if defined STDECL
          #define AMXAPI __stdcall
      #elif defined CDECL
          #define AMXAPI __cdecl
      #elif defined GCC_HASCLASSVISIBILITY
          #define AMXAPI __attribute__((visibility("default")))
      #else
          #define AMXAPI
      #endif
      ```

6. **amx_types.h**

    Defines standard integer types:
    - Support for `stdint.h` or manual definitions:
      ```c
      #if defined HAVE_STDINT_H
          #include <stdint.h>
      #elif defined HAVE_INTTYPES_H
          #include <inttypes.h>
      #else
          typedef short int           int16_t;
          typedef unsigned short int  uint16_t;
          typedef long int            int32_t;
          typedef unsigned long int   uint32_t;
          #if defined __WIN32__ || defined _WIN32 || defined WIN32
              typedef __int64           int64_t;
              typedef unsigned __int64  uint64_t;
          #endif
      #endif
      ```

7. **amx_macros.h**

    Provides utility macros:
    - **Address Calculation**:
      ```c
      #define amx_Address(amx,addr) \
          (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))
      ```
    - **String Handling**:
      ```c
      #define amx_StrParam(amx,param,result) \
          do { \
              int result##_length_; \
              amx_StrLen(amx_Address(amx,param),&result##_length_); \
              if (result##_length_>0 && \
                  ((result)=(void*)alloca((result##_length_+1)*sizeof(*(result))))!=NULL) \
              amx_GetString((char*)(result),amx_Address(amx,param), \
                              sizeof(*(result))>1,result##_length_+1); \
              else (result)=NULL; \
          } while(0)
      ```
    - **Parameter Count**:
      ```c
      #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))
      ```
    - **Function Registration**:
      ```c
      #define amx_RegisterFunc(amx, name, func) \
          amx_Register((amx), amx_NativeInfo((name),(func)), 1)
      ```

8. **amx_cell.h**

    Defines cell types:
    - Configures `PAWN_CELL_SIZE` (default: 32):
      ```c
      #if PAWN_CELL_SIZE==16
          typedef uint16_t  ucell;
          typedef int16_t   cell;
      #elif PAWN_CELL_SIZE==32
          typedef uint32_t  ucell;
          typedef int32_t   cell;
      #elif PAWN_CELL_SIZE==64
          typedef uint64_t  ucell;
          typedef int64_t   cell;
      #endif
      ```
    - Floating-point support:
      ```c
      #if PAWN_CELL_SIZE==32
          #define amx_ftoc(f)   (*(cell*)&(f))  // Float to cell
          #define amx_ctof(c)   (*(float*)&(c))  // Cell to float
      #elif PAWN_CELL_SIZE==64
          #define amx_ftoc(f)   (*(cell*)&(f))  // Double to cell
          #define amx_ctof(c)   (*(double*)&(c)) // Cell to double
      #endif
      ```
    - Character manipulation:
      ```c
      #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))  // For 32-bit
      ```

9. **amx_structures.h**

    Defines core structures:
    - **AMX**:
      ```c
      typedef struct tagAMX {
          unsigned char _FAR *base;    // Base address
          unsigned char _FAR *data;    // Data segment
          AMX_CALLBACK callback;       // Callback function
          AMX_DEBUG debug;            // Debug callback
          cell cip;                   // Code instruction pointer
          cell frm;                   // Frame base
          cell hea;                   // Heap base
          cell hlw;                   // Heap lower bound
          cell stk;                   // Stack pointer
          cell stp;                   // Stack top
          int flags;                  // Flags
          long usertags[AMX_USERNUM]; // User tags
          void _FAR *userdata[AMX_USERNUM]; // User data
          int error;                  // Error code
          int paramcount;             // Parameter count
          cell pri;                   // Primary register
          cell alt;                   // Alternate register
          cell reset_stk;             // Reset stack
          cell reset_hea;             // Reset heap
          cell sysreq_d;              // sysreq.d address
          #if defined JIT
              int reloc_size;         // Relocation size
              long code_size;         // Code size
          #endif
      } AMX;
      ```
    - **AMX_HEADER**:
      ```c
      typedef struct tagAMX_HEADER {
          int32_t size;          // File size
          uint16_t magic;        // Signature
          char    file_version;  // File version
          char    amx_version;   // AMX version
          int16_t flags;         // Flags
          int16_t defsize;       // Definition size
          int32_t cod;           // Code start
          int32_t dat;           // Data start
          int32_t hea;           // Heap start
          int32_t stp;           // Stack top
          int32_t cip;           // Initial instruction pointer
          int32_t publics;       // Publics offset
          int32_t natives;       // Natives offset
          int32_t libraries;     // Libraries offset
          int32_t pubvars;       // Public variables offset
          int32_t tags;          // Tags offset
          int32_t nametable;     // Name table offset
      } AMX_HEADER;
      ```

### Platform Support

The SDK includes robust platform-specific handling through various headers:

1. **amx_platform.h**

    Provides platform detection and configuration:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Handles operating system-specific definitions:
    ```c
    #if defined(__WATCOMC__)
        #if defined(__WINDOWS__) || defined(__NT__)
            #define _Windows 1
        #endif
        #ifdef __386__
            #define __32BIT__ 1
        #endif
    #endif
    ```

### Plugin System

#### plugincommon.h

Defines the main plugin interface and supporting structures:
```c
#define SAMP_PLUGIN_VERSION 0x0200

enum SUPPORTS_FLAGS {
    SUPPORTS_VERSION = SAMP_PLUGIN_VERSION,
    SUPPORTS_VERSION_MASK = 0xffff,
    SUPPORTS_AMX_NATIVES = 0x10000
};

enum PLUGIN_DATA_TYPE {
    PLUGIN_DATA_LOGPRINTF = 0x00,
    PLUGIN_DATA_AMX_EXPORTS = 0x10,
    PLUGIN_DATA_CALLPUBLIC_FS = 0x11,
    PLUGIN_DATA_CALLPUBLIC_GM = 0x12
};
```

#### amxplugin.c

The `amxplugin.c` file is a key component of the SA-MP SDK, providing platform-specific implementations for AMX functions. It implements two approaches based on platform and compiler:

1. **Windows MSVC Implementation (32-bit)**
    - Uses naked functions with assembly for direct function table access:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Cross-Platform Implementation**
    - Uses function pointers for platform independence:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

**Key Features**:

3. **Function Table Management**
    - Uses a static pointer `pAMXFunctions` to store the AMX function table.
    - Provides access to all core AMX functions.
    - Handles runtime function resolution.

4. **Platform-Specific Optimizations**
    - Windows 32-bit: Direct assembly implementation using naked functions.
    - Other platforms: Function pointer indirection.
    - Special handling for 64-bit systems.

5. **Implemented Function Categories**

    a. **Memory Management Functions**:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. **Execution Functions**:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. **Symbol Management**:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. **String Handling**:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - UTF-8 support functions
    
    e. **Debug and Information**:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Conditional Compilation**
    - Handles different platforms via preprocessor directives.
    - Special handling for 64-bit systems.
    - Optional JIT support:
      ```c
      #if defined _I64_MAX || defined HAVE_I64
          DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
              PLUGIN_AMX_EXPORT_Align64)
      #endif
      ```

7. **Error Handling Integration**
    - Implements `amx_RaiseError` for error reporting.
    - Preserves error codes across function calls.
    - Integrates with the AMX debug system.

### AMX Native Functions

The SDK provides comprehensive support for creating and managing native functions:
```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

**Key Native Function Operations**:
- Registration via `amx_Register`.
- Parameter access and validation via `amx_NumParams`.
- Return value handling.
- Error reporting with `amx_RaiseError`.

## Technical Details

### Memory Management

The SDK provides extensive memory management facilities:

1. **amx_memory.h**

    Handles memory allocation and platform-specific operations:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```
    - Defines `AMX_COMPACTMARGIN` as 64 by default for memory compression.

2. **amx_alignment.h**

    Manages memory alignment requirements:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Memory Operations

The SDK includes several functions for memory manipulation:

1. **Memory Allocation**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Allocates memory in the AMX heap.
    - Returns both AMX and physical addresses.
    - Handles alignment requirements.

2. **Memory Access**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Converts AMX addresses to physical addresses.
    - Validates memory access.
    - Handles memory boundaries.

3. **Memory Information**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Retrieves memory layout information.
    - Reports segment sizes.
    - Useful for debugging and optimization.

### Error Handling

The SDK includes a comprehensive error handling system defined in `amx_constants.h`:
```c
enum {
    AMX_ERR_NONE,
    AMX_ERR_EXIT,
    AMX_ERR_ASSERT,
    AMX_ERR_STACKERR,
    AMX_ERR_BOUNDS,
    AMX_ERR_MEMACCESS,
    AMX_ERR_INVINSTR,
    AMX_ERR_STACKLOW,
    AMX_ERR_HEAPLOW,
    AMX_ERR_CALLBACK,
    AMX_ERR_NATIVE,
    AMX_ERR_DIVIDE,
    AMX_ERR_SLEEP,
    AMX_ERR_INVSTATE,
    AMX_ERR_MEMORY = 16,
    AMX_ERR_FORMAT,
    AMX_ERR_VERSION,
    AMX_ERR_NOTFOUND,
    AMX_ERR_INDEX,
    AMX_ERR_DEBUG,
    AMX_ERR_INIT,
    AMX_ERR_USERDATA,
    AMX_ERR_INIT_JIT,
    AMX_ERR_PARAMS,
    AMX_ERR_DOMAIN,
    AMX_ERR_GENERAL,
};
```

### String Handling

The SDK provides robust string handling capabilities through various macros and functions:
```c
#define amx_StrParam(amx,param,result) \
    do { \
        int result##_length_; \
        amx_StrLen(amx_Address(amx,param),&result##_length_); \
        if (result##_length_>0 && \
            ((result)=(void*)alloca((result##_length_+1)*sizeof(*(result))))!=NULL) \
        amx_GetString((char*)(result),amx_Address(amx,param), \
                            sizeof(*(result))>1,result##_length_+1); \
        else (result)=NULL; \
    } while(0)
```
- Alternative for `char*`:
  ```c
  #define amx_StrParamChar(amx, param, result) \
      do { \
          cell* amx_cstr_; \
          int amx_length_; \
          amx_GetAddr((amx), (param), &amx_cstr_); \
          amx_StrLen(amx_cstr_, &amx_length_); \
          if (amx_length_ > 0 && ((result) = (char*)alloca((amx_length_ + 1) * sizeof(*(result)))) != NULL) \
              amx_GetString((char*)(result), amx_cstr_, sizeof(*(result)) > 1, amx_length_ + 1); \
          else \
              (result) = ""; \
      } while(0)
  ```

### String Operations

1. **String Length**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Calculates string length.
    - Handles packed and unpacked strings.
    - Returns length in characters.

2. **String Conversion**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Converts C strings to AMX strings.
    - Supports packed and unpacked formats.
    - Handles Unicode conversion.

## Unicode Support

The SDK provides comprehensive Unicode support through UTF-8 handling functions:
```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Unicode Operations

1. **UTF-8 Validation**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - Validates UTF-8 encoded strings.
    - Reports string length in characters.
    - Detects encoding errors.

2. **Character Conversion**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extracts Unicode characters.
    - Handles multi-byte sequences.
    - Reports parsing errors.

## Cross-Platform Compatibility

The SDK ensures cross-platform compatibility through:

1. **Endianness Handling**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Path Handling**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

3. **Platform-Independent Types**
    - Defined in `amx_types.h` for consistency.

## System Requirements

The SDK supports multiple platforms and compilers:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Compiler Support

1. **Microsoft Visual C++**
    - Pragma handling.
    - Warning suppression.
    - Calling conventions via `amx_calling.h`.

2. **GCC**
    - Diagnostic controls.
    - Attribute specifications.
    - Platform-specific optimizations.

3. **Clang**
    - Warning configurations.
    - Cross-platform compatibility.
    - Modern C++ features.

## Best Practices

When using the SA-MP SDK, consider the following best practices:

1. **Memory Management**
    - Always clean up allocated resources.
    - Use appropriate memory alignment.
    - Handle memory errors gracefully.
    - Monitor heap usage.
    - Implement proper memory bounds checking.
    - Use memory pools for frequent allocations.
    - Clean up resources in reverse order of allocation.

2. **Error Handling**
    - Check return values from AMX functions.
    - Implement proper error handling in native functions.
    - Use provided error constants.
    - Log errors appropriately.
    - Implement error recovery mechanisms.
    - Provide meaningful error messages.
    - Handle system-specific errors.

3. **Cross-Platform Development**
    - Use platform-independent types.
    - Utilize provided macros for platform-specific code.
    - Test on multiple platforms.
    - Handle endianness differences.
    - Use appropriate path separators.
    - Consider file system differences.
    - Implement platform-specific optimizations.

4. **Performance Considerations**
    - Use appropriate cell sizes.
    - Implement efficient string handling.
    - Optimize native function calls.
    - Minimize memory allocations.
    - Use suitable data structures.
    - Implement caching where appropriate.
    - Profile critical code paths.

When working with `amxplugin.c` functionality:

1. **Platform-Specific Development**
    - Consider platform differences in function implementations.
    - Test on both 32-bit and 64-bit systems.
    - Handle platform-specific alignment requirements.
    - Validate function table pointer before use.
    - Implement appropriate error checking for each platform.
    - Consider performance implications of different implementations.

2. **Function Table Management**
    - Initialize function table before use.
    - Verify function availability.
    - Handle missing functions gracefully.
    - Implement proper cleanup procedures.
    - Cache frequently used function pointers.
    - Validate function table integrity.

3. **Error Handling**
    - Implement proper error checking for platform-specific code.
    - Handle alignment errors appropriately.
    - Validate function table entries.
    - Provide meaningful error messages.
    - Implement recovery mechanisms.
    - Log platform-specific errors.

## Internal Structures

### AMX Header Structure

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Size of the "file"
    uint16_t magic;        // Signature
    char    file_version;  // File format version
    char    amx_version;   // Required AMX version
    int16_t flags;         // Flags
    int16_t defsize;       // Size of a definition record
    int32_t cod;           // Initial value of COD - code block
    int32_t dat;           // Initial value of DAT - data block
    int32_t hea;           // Initial value of HEA - start of heap
    int32_t stp;           // Initial value of STP - stack top
    int32_t cip;           // Initial value of CIP - code instruction pointer
    int32_t publics;       // Offset to public functions
    int32_t natives;       // Offset to native function table
    int32_t libraries;     // Offset to libraries
    int32_t pubvars;       // Offset to public variables
    int32_t tags;          // Offset to tags
    int32_t nametable;     // Offset to name table
} AMX_HEADER;
```

This structure is critical for understanding the AMX file format and how the virtual machine loads and executes scripts.

## Advanced Features

### JIT Compilation Support

The SDK includes support for Just-In-Time compilation:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Debug Interface

Debugging support is provided through:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Public Function Interface

The SDK provides comprehensive support for working with public functions:

1. **Finding Public Functions**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Locates public functions by name.
    - Returns the function index.
    - Validates function existence.

2. **Executing Public Functions**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Executes public functions.
    - Handles return values.
    - Manages execution context.

## Version Information

The SDK includes version constants for compatibility checking:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Version Compatibility

The SDK maintains compatibility through:
1. File version checking.
2. AMX version validation.
3. JIT compatibility verification.
4. Feature detection.
5. Platform-specific version handling.

## License

Copyright © **SA-MP Programming Community**

This software is licensed under the terms of the MIT License ("License"); you may use this software according to the License terms. A copy of the License can be obtained at: [MIT License](https://opensource.org/licenses/MIT)

### Terms and Conditions of Use

#### 1. Granted Permissions

This license grants, free of charge, to any person obtaining a copy of this software and associated documentation files, the following rights:
- To use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the software without restriction.
- To permit persons to whom the software is furnished to do so, subject to the following conditions.

#### 2. Mandatory Conditions

All copies or substantial portions of the software must include:
- The above copyright notice.
- This permission notice.
- The disclaimer notice below.

#### 3. Copyright

The software and all associated documentation are protected by copyright laws. The **SA-MP Programming Community** retains the original copyright of the software.

#### 4. Disclaimer of Warranty and Limitation of Liability

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.

IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

---

For detailed information about the MIT License, visit: https://opensource.org/licenses/MIT