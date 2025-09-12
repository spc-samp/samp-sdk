# SAMP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**A modern, header-only, high-level C++ SDK for developing SA-MP plugins and modules.**

</div>

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

## Table of Contents

- [SAMP SDK](#samp-sdk)
  - [Languages](#languages)
  - [Table of Contents](#table-of-contents)
  - [1. Introduction and Design Philosophy](#1-introduction-and-design-philosophy)
    - [The Problem with the Standard SA-MP C API](#the-problem-with-the-standard-sa-mp-c-api)
    - [The SAMP SDK Solution: Abstraction with Safety and Performance](#the-samp-sdk-solution-abstraction-with-safety-and-performance)
    - [Header-Only Model: Advantages and Implications](#header-only-model-advantages-and-implications)
  - [2. Setup and Environment](#2-setup-and-environment)
    - [Compilation Requirements](#compilation-requirements)
    - [Recommended File Structure](#recommended-file-structure)
    - [Essential Configuration Macros\*\*](#essential-configuration-macros)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP Definitions and Constants (`samp_defs.hpp`)](#sa-mp-definitions-and-constants-samp_defshpp)
  - [3. Comprehensive API Usage Guide](#3-comprehensive-api-usage-guide)
    - [3.1. The Plugin Lifecycle](#31-the-plugin-lifecycle)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Intercepting Pawn Events](#32-plugin_public-intercepting-pawn-events)
      - [Syntax and Declaration](#syntax-and-declaration)
      - [Automatic Parameter Marshalling](#automatic-parameter-marshalling)
      - [Flow Control: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#flow-control-plugin_public_continue-vs-plugin_public_stop)
    - [3.3. `Plugin_Native`: Creating Native Functions in C++](#33-plugin_native-creating-native-functions-in-c)
      - [Syntax and Fixed Signature](#syntax-and-fixed-signature)
      - [Automatic Native Registration](#automatic-native-registration)
      - [Parameter Extraction: `Register_Parameters` vs. `Native_Params`](#parameter-extraction-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Full API: `Get`, `Get_REF`, `Set_REF`)](#native_params-full-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Return Values](#return-values)
    - [3.4. `Pawn_*` Macros: Calling Pawn Functions from C++](#34-pawn_-macros-calling-pawn-functions-from-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Syntax and Conventions](#syntax-and-conventions)
      - [Input Parameter Marshalling](#input-parameter-marshalling)
      - [Output Parameter Marshalling (References: `int&`, `float&`, `std::string&`)](#output-parameter-marshalling-references-int-float-stdstring)
      - [The `Callback_Result` Object: Complete Analysis](#the-callback_result-object-complete-analysis)
    - [3.5. `Plugin_Module`: Dynamic Module Management](#35-plugin_module-dynamic-module-management)
      - [Syntax and Purpose](#syntax-and-purpose)
      - [Module Lifecycle](#module-lifecycle)
      - [Benefits of Modularization](#benefits-of-modularization)
    - [3.6. `Plugin_Call`: Calling Internal Plugin Natives](#36-plugin_call-calling-internal-plugin-natives)
      - [Syntax and Performance Advantages](#syntax-and-performance-advantages)
    - [**3.7. SDK Utility Functions**](#37-sdk-utility-functions)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Recommended)](#stdstring-plugin_formatconst-char-format--recommended)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Implementation Detail)](#stdstring-samp_sdkformatconst-char-format--implementation-detail)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. **Internal Anatomy and SDK Architecture**](#4-internal-anatomy-and-sdk-architecture)
    - [4.1. `core.hpp`: The Minimalist Foundation](#41-corehpp-the-minimalist-foundation)
    - [**4.2. `platform.hpp` and `version.hpp`: Compatibility and Metadata**](#42-platformhpp-and-versionhpp-compatibility-and-metadata)
    - [4.3. `function_hook.hpp`: The x86 Interception Engine](#43-function_hookhpp-the-x86-interception-engine)
    - [4.4. `interceptor_manager.hpp`: The AMX Hook Controller](#44-interceptor_managerhpp-the-amx-hook-controller)
    - [4.5. `amx_manager.hpp`: Managing `AMX*` Instances](#45-amx_managerhpp-managing-amx-instances)
    - [4.6. `public_dispatcher.hpp`: The `Plugin_Public` Callback Router](#46-public_dispatcherhpp-the-plugin_public-callback-router)
    - [4.7. `native.hpp`: Managing and Calling Plugin Natives](#47-nativehpp-managing-and-calling-plugin-natives)
    - [4.8. `callbacks.hpp` \& `amx_memory.hpp`: C++ -\> Pawn Calls and RAII](#48-callbackshpp--amx_memoryhpp-c---pawn-calls-and-raii)
    - [4.9. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Abstracted AMX Access](#49-amx_apihpp--amx_helpershpp--amx_defsh-abstracted-amx-access)
  - [5. Compilation and Deployment](#5-compilation-and-deployment)
    - [Architecture and Platform Requirements](#architecture-and-platform-requirements)
    - [Examples of Compilation Commands](#examples-of-compilation-commands)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW on Windows)**](#gcc--clang-mingw-on-windows)
    - [Considerations for Distribution](#considerations-for-distribution)
  - [License](#license)
    - [Terms and Conditions of Use](#terms-and-conditions-of-use)
      - [1. Granted Permissions](#1-granted-permissions)
      - [2. Mandatory Conditions](#2-mandatory-conditions)
      - [3. Copyright](#3-copyright)
      - [4. Disclaimer of Warranty and Limitation of Liability](#4-disclaimer-of-warranty-and-limitation-of-liability)

## 1. Introduction and Design Philosophy

### The Problem with the Standard SA-MP C API

The SA-MP plugin API is a C programming interface. While functional and fundamental, it presents the inherent challenges of low-level programming:
- **Manual Memory Management:** Functions like `amx_Allot` and `amx_Release` require the developer to explicitly allocate and deallocate memory on the AMX heap. This is a common source of memory leaks and runtime failures.
- **Weak Typing and Manual Conversions:** Parameters are passed as an array of `cell`s, forcing explicit (and often unsafe) conversions between `cell`, `int`, `float`, and `char*`.
- **Verbosity and Boilerplate:** Extracting multiple parameters from a `cell* params` array, handling string lengths, and managing the AMX stack for C++ to Pawn callbacks requires repetitive code.
- **Fragile Interface:** The lack of compile-time verification (type safety) means that errors in parameter passing or types can go unnoticed until execution, causing crashes or undefined behavior.

### The SAMP SDK Solution: Abstraction with Safety and Performance

The SAMP SDK addresses these issues by providing a powerful C++ abstraction layer:
- **RAII (Resource Acquisition Is Initialization):** Automatic memory management on the AMX. `Amx_Scoped_Memory` ensures that allocated memory is freed.
- **Type Safety:** Automatic and safe parameter conversion between C++ and Pawn. You deal with `int`, `float`, `std::string` directly.
- **Concise and Idiomatic Syntax:** Macros and templates provide a clean API that more closely resembles modern C++ than the traditional C API.
- **Robust Interception:** An advanced hooking engine allows transparent interception of Pawn callbacks (`Plugin_Public`) and dynamic registration of natives.
- **High Performance:** Extensive use of compile-time hashing (FNV1a), function caching, and `thread_local` optimizations to minimize the overhead of abstractions.

### Header-Only Model: Advantages and Implications

The SDK is composed exclusively of header files (`.hpp`, `.h`).
- **Advantages:**
   - **Simplified Integration:** No libraries to build, link, or distribute. Just include the headers.
   - **Compiler Optimizations:** The compiler has full visibility of the SDK and your plugin code, allowing aggressive inlining and link-time optimizations, which can result in faster binaries.
- **Implications:**
   - **Compilation Time:** For very large projects, compilation may take longer due to repeated inclusion of SDK code. This is mitigated by include guards and the "include only what's necessary" nature of C++.
   - **Implementation Macros:** The need for the `SAMP_SDK_IMPLEMENTATION` macro is a consequence of the header-only model to avoid symbol redefinitions.

## 2. Setup and Environment

### Compilation Requirements

- **C++ Compiler:** Compatible with C++14 or higher (the SDK uses C++14, C++17, and C++20 features for specific optimizations, but C++14 is the minimum).
   - GCC (version 7+)
   - Clang (version 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Architecture:** **x86 (32-bit)**. SA-MP operates exclusively on this architecture. The SDK includes checks in `platform.hpp` that will emit compilation errors if the incorrect architecture is detected.
- **Operating System:** Windows or Linux.

### Recommended File Structure

For clarity and organization, it is common to organize the SDK in a `samp-sdk` subfolder.

```
my_plugin/
├── samp-sdk/
│   ├── // Other SDK files
│   └── samp_sdk.hpp             // The main header to be included
│
├── src/
│   ├── main.cpp                  // Where SAMP_SDK_IMPLEMENTATION is defined
│   └── my_custom_logic.cpp       // Optional, to organize code
│
└── CMakeLists.txt (or .vcxproj, Makefile)
```

### Essential Configuration Macros**

Always define these macros *before* including `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Purpose:** Signals to the compiler that this `.cpp` file should generate the implementations of the plugin's export functions (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **The SDK handles the export of these functions automatically, eliminating the need for `.def` files (on Windows) or `__attribute__((visibility("default")))` declarations (on Linux) for these functions.**
- **Technical Impact:** Without this macro, the linker will not find the necessary exports, and the SA-MP server will not be able to load your plugin.
- **Fundamental Rule:** **Define this macro in ONLY ONE `.cpp` file in your entire project.** Defining it in more than one file will cause a "duplicate symbol" linkage error.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // The macro makes the SDK export the necessary functions automatically.
#include "samp-sdk/samp_sdk.hpp"

// ... your plugin code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Purpose:** Enables SDK functionalities related to interaction with the AMX (Pawn virtual machine) environment.
- **Enabled Functionalities:**
   - Declaration and registration of C++ natives using `Plugin_Native`.
   - Callbacks `OnAmxLoad(AMX* amx)` and `OnAmxUnload(AMX* amx)`.
   - The `Plugin_Call` macro to invoke the plugin's own natives.
- **Technical Impact:** When this macro is defined, the SDK automatically collects all your `Plugin_Native`s. In the `Supports()` function, the `SUPPORTS_AMX_NATIVES` flag is automatically added.
- **Flexibility:** **You can define this macro in multiple `.cpp` files.** The SDK's static registration system (`Native_Registrar`) will consolidate all natives from different compilation units into a single global list.

```cpp
// my_natives.cpp (can be a separate file from main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Only to enable Plugin_Native
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Purpose:** Enables the `OnProcessTick()` callback, which is regularly invoked by the server.
- **Technical Impact:** Automatically adds the `SUPPORTS_PROCESS_TICK` flag to the `Supports()` function.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logic executed every server "tick" (e.g., 20ms)
    // Be careful with heavy operations here!
}
```

### SA-MP Definitions and Constants (`samp_defs.hpp`)

This file provides all known SA-MP constants and limits, such as `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. It is automatically included by `samp_sdk.hpp` and should be used to ensure code compatibility and readability.

## 3. Comprehensive API Usage Guide

### 3.1. The Plugin Lifecycle

The following functions are the entry and exit points of your plugin, automatically exported by the SDK.

#### `bool OnLoad()`

- **Description:** First function called by the SA-MP server after your plugin is successfully loaded into memory.
- **Usage:** Ideal for initializing any systems, loading configurations, opening database connections, or loading modules (`Plugin_Module`).
- **Return:**
   - `true`: The plugin initialized successfully and loading continues.
   - `false`: The plugin failed to initialize. Loading will be aborted and the plugin will be unloaded.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Example: Load a module (more details in section 3.5)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load database module!");

        return false; // Aborts main plugin loading
    }

    return true;
}
```

#### `void OnUnload()`

- **Description:** Last function called by the SA-MP server before unloading your plugin from memory.
- **Usage:** Ideal for cleaning up resources, closing connections, saving states, and ensuring no resources are leaked. The SDK automatically manages the unloading of modules (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // No manual action is needed for modules loaded via Plugin_Module;
    // the SDK handles it.
}
```

#### `unsigned int GetSupportFlags()`

- **Description:** Informs the SA-MP server which features your plugin supports and wants to use.
- **Usage:** **Always return `SUPPORTS_VERSION` (or `SAMP_PLUGIN_VERSION`).** The other flags (`SUPPORTS_AMX_NATIVES`, `SUPPORTS_PROCESS_TICK`) are automatically added by the SDK if the `SAMP_SDK_WANT_AMX_EVENTS` and `SAMP_SDK_WANT_PROCESS_TICK` macros are defined. This simplifies maintenance and prevents errors.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // The SDK adds the necessary flags automatically.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requires:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description:** Called whenever a new Pawn script (a Gamemode or Filterscript) is loaded and initialized on the server.
- **Usage:** If you need specific logic for each AMX script, such as registering custom natives (although `Plugin_Native` does this automatically), or initializing script-specific data.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxLoad(AMX* amx) {
    // amx represents the new instance of the loaded script.
    // You can, for example, call a specific public in this script:
    // Pawn_Public_OnAmx("OnMyPluginLoaded", amx); // Hypothetical example of a more advanced API.
    Samp_SDK::Log("AMX script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Requires:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description:** Called when a Pawn script is unloaded from the server.
- **Usage:** To clean up any specific resources you allocated or associated with that particular `AMX*`.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requires:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Description:** Called repeatedly every server "tick" (usually 20 times per second, or every 50ms).
- **Usage:** For continuous background logic, timers, state updates that don't depend on player events, or data synchronization.
- **Caution:** Avoid blocking or computationally heavy operations here, as they can cause server lag.

```cpp
// main.cpp (with SAMP_SDK_WANT_PROCESS_TICK defined)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Every 10 seconds (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Intercepting Pawn Events

The `Plugin_Public` macro is the primary bridge for receiving Pawn callbacks in your C++ code.

#### Syntax and Declaration

- `Plugin_Public(PublicName, Type1 Param1, Type2 Param2, ...)`
- The C++ function name you declare **must be the same** as the Pawn callback (e.g., `OnPlayerConnect`).
- C++ parameter types (`int`, `float`, `std::string`) are automatically converted by the SDK.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    // ...
}
```

#### Automatic Parameter Marshalling

The SDK automatically handles reading the AMX `cell stack` and converting to the specified C++ types:
- `int`: Converted directly from `cell`.
- `float`: Converted from `cell` using `amx::AMX_CTOF`.
- `std::string`: The SDK reads the string address in the AMX, allocates a C++ `std::string`, and copies the content.

#### Flow Control: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

The return value of your `Plugin_Public` function is crucial and determines the callback's execution flow:
- `return PLUGIN_PUBLIC_CONTINUE;` (value `1`): Indicates that the callback execution should **continue**. If there are other plugins that also intercept this callback, they will be called. Then, the original `public` in the Pawn script will be invoked.
- `return PLUGIN_PUBLIC_STOP;` (value `0`): Indicates that the callback execution should be **stopped**. No other plugin or the original `public` in the Pawn script will be invoked for this event. This is ideal for implementing a system that "overrides" or "blocks" a default SA-MP behavior.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Freezes the player
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Player %d frozen.", playerid));

        return PLUGIN_PUBLIC_STOP; // Prevents the command from being processed by other scripts.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Allows other commands to be processed.
}
```

### 3.3. `Plugin_Native`: Creating Native Functions in C++

`Plugin_Native` allows you to extend Pawn functionality with high-performance C++ code.

#### Syntax and Fixed Signature

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- The C++ function must have exactly this signature: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` is the name Pawn scripts will use.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementation ...
    return 0;
}
```

#### Automatic Native Registration

> [!NOTE]
> You **do not need** to call `amx_Register` manually. The SDK detects all your `Plugin_Native`s (in any `.cpp` file with `SAMP_SDK_WANT_AMX_EVENTS`) and automatically registers them with each loaded AMX script (`OnAmxLoad`).

#### Parameter Extraction: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Description:** Simpler helper to extract multiple parameters sequentially.
- **Usage:** `Register_Parameters(variable1, variable2, ...)`
- **Limitations:** For input parameters. Does not handle optional parameters or indexed access.
- **Supported Types:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extracts the 3 parameters
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (Full API: `Get`, `Get_REF`, `Set_REF`)

- **Description:** A wrapper class that provides an object-oriented interface to access a native's parameters. More powerful for complex scenarios.
- **Construction:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Description:** Returns the number of parameters passed to the native.
- **Usage:** Essential for handling optional parameters.

###### `p.Get<T>(size_t index)`

- **Description:** Extracts an input parameter by index and converts it to type `T`.
- **Supported Types:** `int`, `float`, `std::string`.

```cpp
// Pawn: native GetPlayerWeaponAmmo(playerid, weaponid = -1);
Plugin_Native(GetPlayerWeaponAmmo, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    int weaponid = (p.Count() > 1) ? p.Get<int>(1) : Pawn_Native(GetPlayerWeapon, playerid);
    
    return Pawn_Native(GetPlayerAmmo, playerid, weaponid);
}
```

###### `p.Get_REF<T>(size_t index, T& out_value)`

- **Description:** Gets the value of a **reference** parameter (Pawn pointer) and stores it in `out_value`.
- **Usage:** To read values that were passed by reference from Pawn.
- **Return:** `true` if the AMX address is valid, `false` otherwise.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Gets the values of the references (Pawn passed addresses)
    p.Get_REF(1, health); // Reads the value of Float:health
    p.Get_REF(2, money);   // Reads the value of money
    
    Samp_SDK::Log("Player %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Now, modify them
    health = 50.0f;
    money += 100;
    
    // And writes them back to Pawn memory
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Description:** Returns an `std::optional<T>` to read a reference parameter. Safer for C++17 and above.

###### `p.Set_REF<T>(size_t index, T value)`

- **Description:** Writes a `T` value to a Pawn **reference** parameter (the address Pawn passed).
- **Usage:** To modify values that were passed by reference, making Pawn see the change.
- **Return:** `true` if the write was successful, `false` otherwise.

#### Return Values

- Your `Plugin_Native` function must return a `cell`.
- To return an `int` or `bool`, use a cast to `cell`.
- To return a `float`, use `amx::AMX_FTOC(my_float)`.

```cpp
// Returns a bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    int playerid = p.Get<int>(0);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Returns a float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Returns 100.0f
}
```

### 3.4. `Pawn_*` Macros: Calling Pawn Functions from C++

These macros are the inverse of `Plugin_Public` and `Plugin_Native`: they allow your C++ code to invoke Pawn functions.

#### `Pawn_Native(NativeName, ...)`

- **Purpose:** The recommended way to call SA-MP native functions (or from other plugins) from C++.
- **Mechanism:** Searches for the native's pointer in the SDK's internal cache (populated by `Amx_Register_Detour`). If found, executes the native in an `Amx_Sandbox` environment (a fake, isolated AMX instance).
- **Performance:** The most efficient, as it avoids expensive `public` lookups and interacts directly with the native's pointer.

#### `Pawn_Public(PublicName, ...)`

- **Purpose:** Calls a specific public function in a Pawn script.
- **Mechanism:** Iterates through the `AMX*` instances managed by `Amx_Manager`, searches for the `public` by name, and executes it.
- **Performance:** Less efficient than `Pawn_Native` due to the lookup and actual `amx_Exec`. Generally, `publics` are slower than `natives`.
- **Usage:** Ideal for invoking custom events in your Gamemode/Filterscripts that are not natives.

#### `Pawn(FunctionName, ...)`

- **Purpose:** A convenience macro that tries to guess if the function is a native or a public.
- **Mechanism:** First, tries to call as `Pawn_Native`. If it fails (the native is not found), it tries to call as `Pawn_Public`.
- **Performance:** Can be slightly slower than `Pawn_Native` if the function is native, due to the double lookup attempt. For `publics`, the performance is the same as `Pawn_Public`.
- **Usage:** For functions where you are unsure if they are native or public, or to avoid the boilerplate of trying one and then the other.

#### Syntax and Conventions

- **Function Name:** Always use the Pawn function name **directly, without quotes**. The SDK will convert it to a string internally.
- **Parameters:** Pass C++ parameters directly.

```cpp
// Correct:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Incorrect (but would technically work due to hashing, avoid):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Input Parameter Marshalling

The SDK converts your C++ types to the AMX `cell` format, managing memory as needed:
-   `int`, `bool`, `long`, `enum` -> `cell`
-   `float`, `double` -> `cell` (using `amx::AMX_FTOC`)
-   `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (allocates memory on the AMX, copies the string, and passes the `amx_addr` address)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Output Parameter Marshalling (References: `int&`, `float&`, `std::string&`)

This is a key feature for convenience and safety. For Pawn functions that expect a pointer (reference), the SDK automates the entire process of memory allocation/deallocation and data copying.

- **How to use:** Just pass your variable by reference (`&`).
- **Mechanism:** The SDK allocates memory on the AMX heap, passes the AMX address to the Pawn function, waits for the Pawn function to fill that address, reads the value back, and frees the AMX memory. All transparently.
- **With `std::string&`:** The SDK allocates a default buffer (256 cells) on the AMX for the string.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Location of %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interior:%d World:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### The `Callback_Result` Object: Complete Analysis

All `Pawn_*` calls return a `Callback_Result` object. This object is a safe wrapper for the Pawn call result.

- `Callback_Result() noexcept`: Default constructor, indicates failure (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Constructor for success or failure with value.
- `explicit operator bool() const`: Allows using `if (result)` to check if the call was successful.
- `operator cell() const`: Allows converting the result to `cell` to get the value.
- `float As_Float() const`: Convenience to get the result as `float`.
- `cell Value() const`: Returns the raw `cell` value.
- `bool Success() const`: Returns `true` if the Pawn call was successful.
- `int Get_Amx_Error() const`: Returns the AMX error code if the call failed (0 for success).

```cpp
// Example: Getting a player's health.
// The native GetPlayerHealth(playerid, &Float:health) expects a playerid and a reference to health.
int playerid = 0; // Example Player ID
float player_health = 0.0f;

// We call GetPlayerHealth, passing playerid and player_health by reference.
// The SDK will handle marshalling for the 'health' output parameter.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Checks if the call was successful (operator bool)
    // The value returned by result.As_Float() or result (operator cell)
    // would be the native's *return value*, not the output parameter.
    // The health value has already been updated in 'player_health' due to output parameter marshalling.
    Samp_SDK::Log("Player %d has %.1f health.", playerid, player_health);
} else {
    // The call failed, perhaps the player doesn't exist or the native was not found.
    Samp_SDK::Log("Error getting player %d's health. AMX Code: %d", playerid, result.Get_Amx_Error());
}

// For natives that return a value and use output parameters (less common, but possible),
// you would use both:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param is already updated
// }
```

### 3.5. `Plugin_Module`: Dynamic Module Management

The `Plugin_Module` macro allows your plugin to act as a "loader" for other plugins, creating a modular and extensible architecture.

#### Syntax and Purpose

- `Plugin_Module(const char* base_filename, const char* module_directory, const char* optional_success_message)`
- `base_filename`: The *base* name of the module file, **without the extension** (e.g., for `my_module.dll` or `my_module.so`, use `"my_module"`). The SDK will automatically add the appropriate `.dll` or `.so` extension.
- `module_directory`: The path to the directory where the module file is located (e.g., `"plugins/my_custom_modules"`). **Do not include the filename here.** The SDK will concatenate the full path (`module_directory/base_filename.ext`).
- `optional_success_message`: An optional message to be logged to the server console if the module loads successfully.

```cpp
// main.cpp, inside OnLoad()

// Loads the module 'core_logic.dll' (or 'core_logic.so')
// which is located in the server's 'modules/custom/' folder.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic Module loaded successfully!"))
    return (Samp_SDK::Log("FATAL ERROR: Failed to load module 'core_logic'!"), false);

// Loads the module 'admin_system.dll' (or 'admin_system.so')
// which is located directly in the server's 'plugins/' folder.
if (!Plugin_Module("admin_system", "plugins", "Admin Module activated."))
    Samp_SDK::Log("WARNING: Admin Module could not be loaded.");
```

#### Module Lifecycle

- **Loading:** When `Plugin_Module` is called, the SDK:
   1. Constructs the full file path (e.g., `plugins/custom/core_logic.dll`).
   2. Uses `Dynamic_Library` (`LoadLibrary`/`dlopen`) to load the binary.
   3. Gets pointers to the module's lifecycle functions: `Load`, `Unload`, and `Supports`.
   4. Calls the module's `Load` function, passing the main plugin's `ppData`.
   5. If `Load` returns `true`, the module is added to the internal list of loaded modules.
- **Unloading:** During `OnUnload` of your main plugin, the SDK unloads all modules that were loaded via `Plugin_Module`. This is done in **reverse order** of loading (the last one loaded is the first one unloaded), which is crucial for managing dependencies and ensuring correct resource release.

#### Benefits of Modularization

- **Code Organization:** Divide large plugins into smaller, manageable components, each in its own module file.
- **Reusability:** Create generic modules (e.g., a database module, an advanced logging system module) that can be used by different plugins, promoting code reuse.
- **Dynamic Updates:** In controlled scenarios, allows updating parts of your system (by replacing a module `.dll` or `.so`) without needing to recompile and restart the main plugin or the entire server (although this requires rigorous version and compatibility management).

### 3.6. `Plugin_Call`: Calling Internal Plugin Natives

Use `Plugin_Call` to invoke a `Plugin_Native` defined **within your own plugin**.

#### Syntax and Performance Advantages

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Advantage:** Avoids the overhead of looking up the native in the AMX native array. The SDK maintains a direct map of name hashes to function pointers for its own natives, making this the fastest way to call them internally.
- **Requires:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logic to check level
    return (playerid % 2 == 0) ? 1 : 0; // Example: even level for even IDs
}

void CheckAllPlayersLevel() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Calls its own native
                Samp_SDK::Log("Player %d is high level!", i);
        }
    }
}
```

### **3.7. SDK Utility Functions**

#### `Samp_SDK::Log(const char* format, ...)`

- **Description:** Prints messages to the server console and the `server_log.txt` file. A safe wrapper for `logprintf`.
- **Usage:** For debugging, status messages, and errors.
- **Mechanism:** Internally, the SDK obtains the `logprintf` pointer through `ppData[PLUGIN_DATA_LOGPRINTF]`. The function handles string formatting safely.

```cpp
// Anywhere in your plugin
Samp_SDK::Log("The plugin was initialized with a value %d and a string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Recommended)

- **Description:** Safely formats a string (similar to `sprintf`) and returns an `std::string`. This is the **recommended and most idiomatic** way to format strings for use within your plugin.
- **Usage:** Ideal for building formatted messages before passing them to `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, or any other string need within your C++ code.
- **Mechanism:** Internally, `Plugin_Format` is a macro that calls `Samp_SDK::Format`. It uses `vsnprintf` to determine the exact size of the formatted string and allocates an `std::string` with sufficient capacity, preventing buffer overflows.

```cpp
int playerid = 0; // Example ID
int health = 50;
std::string status_message = Plugin_Format("Player %d, your current health is %d.", playerid, health); // Using the Plugin_Format macro
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, status_message);

// Can also be used for internal logs
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid).c_str());
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Implementation Detail)

- **Description:** The underlying implementation function for string formatting, located within the `Samp_SDK` namespace.
- **Usage:** Generally not called directly by the user. The `Plugin_Format` macro is provided as a convenience for this function, aligning with the naming convention of other SDK macros (`Plugin_Public`, `Plugin_Native`). You would only call it directly if you wanted to avoid the `Plugin_Format` macro for some specific reason.

```cpp
// Example of how Samp_SDK::Format works, but prefer Plugin_Format
std::string raw_status = Samp_SDK::Format("For internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Description:** Converts an AMX string address (`cell amx_addr`) into a C++ `std::string`.
- **Usage:** Primarily within `Plugin_Native` when you need to access strings that are not automatically converted by `Register_Parameters` or `Native_Params` (e.g., if the Pawn parameter is a `const` `string` and was not declared as `std::string` in your `Plugin_Native` or `Plugin_Public` for automatic Marshalling).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Gets the string address in AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("AMX String: %s", cpp_string.c_str());

    return 1;
}
```

## 4. **Internal Anatomy and SDK Architecture**

This section reveals the underlying mechanisms of the SAMP SDK, exploring its architecture, key components, and how they interact to provide high-level abstraction. A deep understanding of these internals empowers the developer to optimize SDK usage, debug complex problems, and even extend its functionalities.

### 4.1. `core.hpp`: The Minimalist Foundation

`Samp_SDK::Core` is a `singleton` that serves as the initial and centralized access point to low-level data provided by the SA-MP plugin environment. Its main responsibility is to encapsulate and expose essential functionalities.

- **`Samp_SDK::Core::Instance()`**:
   - **Description:** Returns the single global instance of the `Core` class. This is a `singleton` design pattern to ensure consistent and centralized access to plugin data (`ppData`).
   - **Mechanism:** The instance is initialized once when `Core::Instance().Load(ppData)` is called in your plugin's `Load()` function.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Description:** Allows safe and indexed access to AMX API function pointers. The `pAMXFunctions` array (received via `ppData[PLUGIN_DATA_AMX_EXPORTS]`) contains the addresses of critical functions like `amx_Exec`, `amx_Register`, etc.
   - **Impact:** Instead of using `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, the SDK offers type-safe wrappers in the `amx::` namespace (e.g., `amx::Exec(...)`), making the code more readable and less prone to casting errors.
   - **Internal Example (`amx_api.hpp`):**
      ```cpp
      // Simplified snippet from amx_api.hpp
      namespace amx {
          template <typename Func, int Index, typename... Args>
          inline auto Call(Args... args) -> decltype(std::declval<Func>()(args...)) {
              using Return_Type = decltype(std::declval<Func>()(args...));
              auto func_ptr = reinterpret_cast<Func>(Core::Instance().Get_AMX_Export(Index));

              if (SAMP_SDK_UNLIKELY(!func_ptr))
                  return (Samp_SDK::Log("[SAMP SDK] Fatal: Attempted to call AMX export at index %d, but pAMXFunctions was not loaded!", Index),
                  Samp_SDK::amx::Detail::Amx_Call_Error_Handler<Return_Type>(typename std::is_pointer<Return_Type>::type{}));

              return func_ptr(args...);
          }

          inline int Exec(AMX* amx, cell* retval, int index) {
              return Call<Exec_t, PLUGIN_AMX_EXPORT_Exec>(amx, retval, index);
          }
      } // namespace amx
      ```

- **`logprintf_ptr`**:
   - **Description:** A pointer to the SA-MP `logprintf` function, which is the standard interface for printing messages to the server console and `server_log.txt`.
   - **Mechanism:** `Samp_SDK::Log` is a safe wrapper that uses this pointer, ensuring your messages are correctly displayed in the SA-MP environment.

### **4.2. `platform.hpp` and `version.hpp`: Compatibility and Metadata**

These headers are the foundation for SDK portability and optimization, adapting it to different compilation environments and leveraging modern C++ features.

- **Platform and Architecture Detection:**
   - **Mechanism:** Uses preprocessor macros (`#if defined(WIN32)`, `#if defined(__linux__)`, etc.) to identify the operating system.
   - **Architecture Check:** Contains `static_assert` or `#error` to ensure the plugin is being compiled for x86 (32-bit), a critical requirement for SA-MP compatibility and the hooking mechanism.
   - **Symbol Export Management:**
      - `SAMP_SDK_EXPORT`: A macro defined in `platform.hpp` that expands to `extern "C"` and, on Linux, adds `__attribute__((visibility("default")))`. On Windows, it just ensures `extern "C"` because the SDK uses `pragma comment(linker, "/EXPORT:...")` (for MSVC) or the MinGW standard to export the main functions.
      - This ensures that the plugin lifecycle functions (`Supports`, `Load`, `Unload`, etc.) are correctly exported from your DLL/SO, regardless of the compilation environment, **without the need for `.def` files or manually adding `__attribute__((visibility("default")))`** in your implementation.
   - **Example (`platform.hpp` - relevant fragment):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // For MSVC, export is managed by pragma linker commands
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // For GCC/Clang on Linux, we use the visibility attribute
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... other definitions ...
      ```
   - **Example (`samp_sdk.hpp` - relevant fragment of the implementation):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // On Windows (MSVC), we use pragma comment to export functions.
          // This eliminates the need for a .def file.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... other exports ...
      #endif

      // Implementation of exported functions
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... other functions ...
      #endif
      ```

- **Optimization and Branch Prediction Macros:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mechanism:** `__forceinline` (MSVC) or `__attribute__((always_inline)) inline` (GCC/Clang). Strongly suggests to the compiler to insert the function body directly at the call site, eliminating the overhead of an actual function call.
      - **Usage:** Applied to small, performance-critical functions within the SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mechanism:** `[[likely]]` / `[[unlikely]]` (C++20) or `__builtin_expect` (GCC/Clang). Hints to the compiler about which path of an `if/else` is more likely to be taken.
      - **Impact:** Helps the compiler generate more efficient code for branch prediction, reducing CPU latency.
      - **Example (`platform.hpp`):**
         ```cpp
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
         ```

- **Standard C++ Definitions (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mechanism:** Macros defined based on the value of `__cplusplus` and `_MSVC_LANG`.
   - **Usage:** Allow the SDK to utilize newer C++ features (like `std::apply` and `if constexpr` from C++17, or `std::is_same_v` from C++17) when available, while maintaining compatibility with older standards.
   - **Example (`version.hpp` - `if constexpr` usage):**
      ```cpp
      // Simplified snippet from public_dispatcher.hpp
      template<typename First, typename... Rest>
      inline void Get_Public_Params_Recursive(AMX* amx, int index, First& first, Rest&... rest) {
          cell value;

          if (Get_Stack_Cell(amx, index, value)) {
      #if defined(SAMP_SDK_CXX_MODERN)
                  if constexpr (std::is_same_v<decay_t<First>, std::string>)
                      first = Samp_SDK::Get_String(amx, value);
                  else if constexpr (std::is_floating_point_v<decay_t<First>>)
                      first = amx::AMX_CTOF(value);
                  else
                      first = static_cast<decay_t<First>>(value);
      #elif defined(SAMP_SDK_CXX14)
                  Assign_Parameter_By_Type(amx, &value, -1, first);
      #endif
          }

          Get_Public_Params_Recursive(amx, index + 1, rest...);
      }
      ```

### 4.3. `function_hook.hpp`: The x86 Interception Engine

This header defines the low-level mechanism for performing function hooks (interceptions), which is fundamental to the SDK's operation. It is strictly dependent on the x86 (32-bit) architecture.

- **`X86_Detour`**:
   - **Description:** A class that encapsulates the logic of overwriting the beginning of a function in memory with a jump instruction to a detour function.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mechanism:** On x86, the relative jump (`JMP`) instruction generally has 5 bytes: `0xE9` (opcode for JMP near, relative) followed by 4 bytes representing the offset of the target address relative to the next instruction.
      - **Instruction Example:** `E9 XX XX XX XX` (where `XX` are the offset bytes).
   - **`Apply(void* target, void* detour)`**:
      - **Action:** Installs the hook. First, it stores the `JUMP_INSTRUCTION_SIZE` original bytes of the `target` function (`original_bytes_`). Then, it calculates the relative address of the `detour` with respect to the `target` and overwrites the beginning of `target` with the `JMP` instruction.
      - **Relative Address Calculation Example:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Detour address - (Target address + JMP instruction size)
         ```
   - **`Revert()`**:
      - **Action:** Uninstalls the hook, restoring the `original_bytes_` to the `target` function.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mechanism:** On Windows, it uses `VirtualProtect`; on Linux, `mprotect`. These system calls change the permissions of the memory page where the function resides to `EXECUTE_READWRITE` (Windows) or `PROT_WRITE | PROT_EXEC` (Linux), allowing the code to be modified at runtime.
      - **Example (`Unprotect_Memory`):**
         ```cpp
         // Simplified snippet from function_hook.hpp
         #if defined(SAMP_SDK_WINDOWS)
             DWORD old_protect;
             VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &old_protect);
         #elif defined(SAMP_SDK_LINUX)
             long pagesize = sysconf(_SC_PAGESIZE);
             uintptr_t page_start = reinterpret_cast<uintptr_t>(address) & -pagesize;
             mprotect(reinterpret_cast<void*>(page_start), size + (reinterpret_cast<uintptr_t>(address) - page_start), PROT_READ | PROT_WRITE | PROT_EXEC);
         #endif
         ```

- **`Function_Hook<FuncPtr>`**:
   - **Description:** A type-safe C++ wrapper for `X86_Detour`, ensuring correct function pointer types.
   - `Install(void* target, void* detour)`: Encapsulates the `X86_Detour::Apply` call.
   - `Uninstall()`: Encapsulates the `X86_Detour::Revert` call.
   - **`Call_Original(Args... args)`**:
      - **Safety Mechanism (Recursion Guard):** This function is critical to prevent infinite loops when the detour needs to call the original function. It **temporarily uninstalls the hook (`detour_.Revert()`)**, calls the original function (`Get_Original()(args...)`), and then **reinstalls the hook (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: A counter that ensures the hook is only reinstalled when the highest-level original call is complete, allowing safe recursive calls to the original function (if the original function is recursive, for example). `thread_local` ensures that `recursion_guard` is isolated for each thread, important in multi-threaded environments.
      - **Example (`Call_Original` with Scope_Guard):**
         ```cpp
         // Simplified snippet from function_hook.hpp
         template<typename... Args>
         auto Call_Original(Args... args) -> decltype(Get_Original()(args...)) {
             static thread_local int recursion_guard = 0;

             if (recursion_guard == 0)
                 detour_.Revert();

             recursion_guard++;

             struct Scope_Guard {
                 int& guard_ref;
                 X86_Detour& detour_ref;

                 ~Scope_Guard() {
                     guard_ref--;

                     if (guard_ref == 0)
                         detour_ref.Reapply();
                 }
             };

             Scope_Guard guard{recursion_guard, detour_};
             
             return Get_Original()(args...);
         }
         ```

### 4.4. `interceptor_manager.hpp`: The AMX Hook Controller

This `singleton` is the nerve center of the SDK's interaction with the SA-MP AMX virtual machine. It coordinates the installation of hooks provided by `function_hook.hpp` into the AMX API functions exposed by the server, redirecting the execution flow to the SDK's logic.

- **`Activate()` / `Deactivate()`**:
   - **Description:** Public methods to install and uninstall all necessary hooks. Called in your plugin's `OnLoad()` and `OnUnload()` functions, respectively.
   - **Mechanism:** Obtains the AMX function pointers (like `amx_Register`, `amx_Exec`, etc.) using `Core::Instance().Get_AMX_Export(...)` and installs the detours.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Hooked Function:** `amx_Register`
   - **Purpose:** Intercepts the registration of *all* natives (by SA-MP, other plugins, or gamemode).
   - **Action:** Calls `Interceptor_Manager::Instance().Cache_Natives()` to store the native pointers and names in an internal cache.
   - **Impact:** This cache is fundamental for `Pawn_Native`'s performance, allowing extremely fast native pointer lookup instead of an expensive AMX lookup.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Hooked Function:** `amx_Exec`
   - **Purpose:** **This is the most critical hook.** It intercepts *any* code execution in the AMX, including calling Pawn `publics`.
   - **`Plugin_Public` Interception Mechanism:**
      1. When `amx_Exec` is called for a `public` (or `AMX_EXEC_MAIN`), `Amx_Exec_Detour` is executed.
      2. It gets the `public`'s name (using `Get_Public_Name_By_Index` or `tl_public_name`).
      3. Queries `Public_Dispatcher::Instance().Dispatch()` to check if there are C++ handlers registered for this name.
      4. If there are handlers, it executes them. The `Public_Dispatcher` handles marshalling AMX parameters to the correct C++ types.
      5. Based on the return value from `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), it decides whether to call the original `amx_Exec` (`Get_Amx_Exec_Hook().Call_Original(...)`) or terminate the Pawn `public`'s execution.
      6. **Stack Manipulation:** If the Pawn `public`'s execution is stopped (`PLUGIN_PUBLIC_STOP`), `Amx_Exec_Detour` fixes the AMX stack (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) to avoid inconsistencies.
   - **Example (`Amx_Exec_Detour`):**
      ```cpp
      // Simplified snippet from interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          // ... logic to determine public name ...
          std::unique_ptr<std::string> public_name_ptr;

          if (index == AMX_EXEC_MAIN) {
              Interceptor_Manager::Instance().Set_Gamemode_Amx(amx);
              public_name_ptr = std::make_unique<std::string>("OnGameModeInit");
          }
          else if (Interceptor_Manager::Instance().Is_Gamemode_Amx(amx) && index != AMX_EXEC_CONT) {
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
      ```

- **`int SAMP_SDK_AMX_API Amx_Find_Public_Detour(...)`**:
   - **Hooked Function:** `amx_FindPublic`
   - **Purpose:** Intercepts the lookup for `publics` by name.
   - **"Ghost Publics" Mechanism:** If the original `amx_FindPublic` does not find a `public` in Pawn, but the `Public_Dispatcher` has a C++ handler registered for that name, this hook returns `AMX_ERR_NONE` and a special `index` (`PLUGIN_EXEC_GHOST_PUBLIC`). This makes the SA-MP API "think" the `public` exists, allowing the subsequent `amx_Exec` call (for this special index) to be intercepted by `Amx_Exec_Detour`, which then redirects to the C++ handler.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Used to pass the `public`'s name to `Amx_Exec_Detour` when a "ghost public" is detected, as `amx_Exec` only receives the index, not the name.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Hooked Functions:** `amx_Init` / `amx_Cleanup`
   - **Purpose:** Manage the list of active `AMX*` instances.
   - **Action:** `Amx_Init_Detour` calls `Amx_Manager::Instance().Add_Amx()`, and `Amx_Cleanup_Detour` calls `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Managing `AMX*` Instances

This `singleton` maintains a dynamic record of all AMX virtual machines currently loaded on the server. It is essential for functions that need to interact with "all scripts" or find a specific script.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Description:** A list of pointers to all `AMX*` instances that have been initialized (gamemode and filterscripts).
   - **Management:** Populated by `Amx_Init_Detour` hooks and emptied by `Amx_Cleanup_Detour` hooks.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Purpose:** Protects `loaded_amx_` against concurrent access in multi-threaded environments (although SA-MP is mostly single-threaded, this is good safety practice). `std::shared_mutex` allows multiple readers simultaneously, but only one writer.
- **`std::atomic<uint32_t> generation_`**:
   - **Purpose:** A counter that increments each time an AMX is added or removed.
   - **Usage:** Used by `Caller_Cache` in `callbacks.hpp` to detect when the list of AMXs has changed, invalidating `public` lookup caches and ensuring that `Pawn_Public` calls always operate with updated information. This optimizes performance by avoiding repetitive lookups in an unchanged state.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Description:** Iterates through `loaded_amx_` (from newest to oldest, which usually puts the gamemode or most relevant filterscript first) to find the `public` with the specified name.
   - **Mechanism:** Uses `amx::Find_Public` for each `AMX*` instance.
   - **Impact:** It is the basis for `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: The `Plugin_Public` Callback Router

This `singleton` is the component that maps Pawn `public` names to your C++ `Plugin_Public` functions.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Key:** The FNV1a hash of the `public`'s name (e.g., `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Value:** An `std::vector` of `std::function<cell(AMX*)>`, where each `std::function` is a C++ handler registered for that `public`.
   - **Mechanism:** The `std::vector` allows multiple `Plugin_Public`s to be registered for the same callback (e.g., several plugins wanting to intercept `OnPlayerCommandText`). Handlers are executed in reverse order of registration.
- **`Public_Registrar`**:
   - **Mechanism:** This is a template class whose `PLUGIN_PUBLIC_REGISTRATION` macro creates a global static instance. In the static constructor (`static bool registered = [...]`), it registers its `Plugin_Public` handler with the `Public_Dispatcher`. This is a "static compile-time/initialization registration" pattern.
   - **Example (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Registrar<decltype(&name), &name, hash_##name> registrar_##name;
      ```

- **`Public_Traits` and `Wrapper()`**:
   - **Mechanism:** `Public_Traits` is a trait template that, using metaprogramming, generates a `static cell Wrapper(AMX* amx)` function.
   - **Purpose:** This `Wrapper` is the `Amx_Handler_Func` that the `Public_Dispatcher` actually stores and calls. It is responsible for:
      1. Calling `Public_Param_Reader::Get_Public_Params(amx, args...)` to extract parameters from the AMX stack.
      2. Calling your actual C++ `Plugin_Public` function (`func_ptr`) with parameters already converted to the correct C++ types.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Description:** A set of recursive template functions that read values from the AMX stack and convert them to the C++ types specified in the `Plugin_Public` declaration.
   - **Mechanism:** Uses `Get_Stack_Cell()` to access `cell`s on the stack. Uses `if constexpr` (C++17+) or `std::is_same<T>::value` (C++14) to apply the correct conversion (`amx::AMX_CTOF` for float, `Samp_SDK::Get_String` for string, direct cast for int).

### 4.7. `native.hpp`: Managing and Calling Plugin Natives

This header is dedicated to the creation and management of C++ natives that your plugin exposes to Pawn.

- **`Native_List_Holder`**:
   - **Description:** A global `singleton` that stores all `Plugin_Native`s declared in your plugin (from all `.cpp` files that use `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Contains `Native` objects (which store the native's name and the pointer to the C++ `Native_Handler` function).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: An optimized hash map for fast lookups of internal `Plugin_Native`s (used by `Plugin_Call`).
- **`Native_Registrar`**:
   - **Mechanism:** Similar to `Public_Registrar`, this is a template class whose `Plugin_Native` macro creates a global static instance. In its constructor, it adds the native to `Native_List_Holder`.
   - **Impact:** Allows you to declare `Plugin_Native`s in multiple `.cpp` files without worrying about manual registration. All will be collected automatically.
- **`Native_Registry`**:
   - **Description:** A helper class that, in `OnAmxLoad`, takes the complete list of `Native`s from `Native_List_Holder` and formats them into an `AMX_NATIVE_INFO` array.
   - **Mechanism:** Calls `amx::Register(amx, amx_natives_info_.data(), -1)` to register all your natives with the newly loaded AMX instance.
- **`Plugin_Call_Impl(...)`**:
   - **Description:** The underlying implementation of the `Plugin_Call` macro.
   - **Mechanism:** Uses `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` to directly get the C++ function pointer.
   - **Environment:** Executes the native in an `Amx_Sandbox` (isolated) environment to manage temporary stack and heap, similar to how `Pawn_Native` works.

### 4.8. `callbacks.hpp` & `amx_memory.hpp`: C++ -> Pawn Calls and RAII

These headers form the backbone for calling Pawn functions from C++ (`Pawn_*` macros) and ensure memory safety.

- **`Amx_Sandbox`**:
   - **Description:** A `thread_local` structure that simulates a minimalist, isolated `AMX` environment for `Pawn_Native` and `Plugin_Call` calls.
   - **Mechanism:** Has its own `AMX` struct, `AMX_HEADER`, and a `std::vector<unsigned char> heap` to simulate a script's memory. This allows `amx::Push`, `amx::Allot`, etc., to be called without interfering with the state of real running Pawn scripts.
   - **`thread_local`:** Ensures that each thread has its own `Amx_Sandbox`, preventing race conditions if the SDK is used in a multi-threaded context (e.g., a future thread pool for non-Pawn operations).
   - **Example (`Amx_Sandbox`):**
      ```cpp
      // Simplified snippet from callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Simulated memory for stack/heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Initializes the AMX and header
          }

          void Reset() {
              memset(&amx, 0, sizeof(amx));
              memset(&amx_header, 0, sizeof(amx_header));
              amx_header.magic = AMX_MAGIC;
              amx_header.file_version = MIN_FILE_VERSION;
              amx_header.amx_version = MIN_AMX_VERSION;
              amx_header.dat = reinterpret_cast<ucell>(heap.data()) - reinterpret_cast<ucell>(&amx_header);
              amx.base = reinterpret_cast<unsigned char*>(&amx_header);
              amx.data = heap.data();
              amx.callback = amx::Callback;
              amx.stp = heap.size();
              amx.stk = heap.size();
              amx.hea = 0;
              amx.flags = AMX_FLAG_NTVREG | AMX_FLAG_RELOC;
          }
      };
      ```

- **`Parameter_Processor`**:
   - **Description:** A set of overloaded template functions that manage the `marshalling` of *each* C++ parameter to the `cell` format expected by the AMX, and vice versa for output parameters.
   - **Input Processing:**
       - For `int`, `float`, `bool`: Converts directly to `cell`.
       - For `const char*`, `std::string`: Allocates memory on the `Amx_Sandbox` heap (or real AMX for `Pawn_Public`), copies the string, and pushes the AMX address onto the stack.
   - **Output Processing (`is_output_arg`):**
       - **Mechanism:** When an argument is a non-const lvalue reference (detected by the `is_output_arg` trait), `Parameter_Processor` does not push the value, but rather an *AMX address* to a `cell` temporarily allocated on the heap.
       - **`std::vector<std::function<void()>> post_call_updaters`**: After the Pawn native call, a list of lambdas (`post_call_updaters`) is executed. Each lambda is responsible for reading the final value from the `cell` allocated in the AMX and assigning it back to the original C++ variable (e.g., `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mechanism:** An `std::integral_constant` (type trait) that, at compile time, evaluates whether a C++ parameter type is a modifiable reference (e.g., `int&`, `float&`, `std::string&`). This allows `Parameter_Processor` to differentiate input from output parameters.
   - **Example (`is_output_arg`):**
      ```cpp
      // Simplified snippet from callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Description:** An RAII (`Resource Acquisition Is Initialization`) class that encapsulates AMX memory allocation and deallocation.
   - **Mechanism:** In the constructor, it calls `amx::Allot` to get an `amx_addr` and a `phys_addr`. In the destructor, it calls `amx::Release` to free that memory.
   - **Impact:** **Crucial for preventing memory leaks on the AMX heap.** Ensures that temporary memory used for strings or output parameters is always freed, even if exceptions or early returns occur.

### 4.9. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Abstracted AMX Access

These headers provide the fundamental definitions and high-level tools for interacting with Pawn.

- **`amx_defs.h`**:
   - **Content:** Contains the raw definitions of AMX structures (`AMX`, `AMX_HEADER`), types (`cell`, `ucell`), and error enums (`AmxError`). Also defines `AMX_NATIVE` and `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Uses packing attributes (`#pragma pack(push, 1)` / `__attribute__((packed))`) to ensure AMX structures have the correct memory layout, fundamental for interoperability.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Description:** The main template function for invoking AMX API functions exposed by the server.
   - **Mechanism:** Gets the function pointer through `Core::Instance().Get_AMX_Export(Index)` and calls it. Centralizes error handling if the function pointer is not available.
   - **Impact:** Converts low-level calls (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) into idiomatic and type-safe C++ calls (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Description:** Essential functions for converting `cell` values to `float` and vice versa, performing a bitwise reinterpretation of memory.
   - **`static_assert`:** Includes `static_assert` to ensure `sizeof(cell) == sizeof(float)` at compile time, preventing errors on platforms with different type sizes.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Description:** Helper to convert an AMX string address into `std::string`.
   - **Mechanism:** First, gets the physical address (`cell* phys_addr`) of the string in the AMX using `amx::Get_Addr`. Then, uses `amx::STR_Len` to determine the length and `amx::Get_String` to copy the bytes into an `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Description:** The base string formatting function (`printf`-like) for the SDK.
   - **Mechanism:** Uses `vsnprintf` in two passes: first to determine the necessary string size, and then to format the string into the dynamically allocated `std::string`. This prevents buffer overflows.

## 5. Compilation and Deployment

### Architecture and Platform Requirements

- Your plugin **MUST** be compiled for the **x86 (32-bit)** architecture. The SDK's hooking mechanism is specific to this architecture.
- Supported Platforms: Windows (.dll) and Linux (.so).

### Examples of Compilation Commands

#### **MSVC (Visual Studio)**

1. Create a new "Dynamic-Link Library (DLL)" project.
2. In project settings, set the "Solution Platform" to **x86**.
3. Ensure the C++ Language Standard is at least C++14.

#### **GCC / Clang (Linux)**

```bash
# For a plugin named 'my_plugin.so' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compiles for 32-bit.
- `-shared`: Creates a shared library (`.so`).
- `-std=c++17`: Sets the C++ standard to C++17 (can be `c++14` or `c++20`).
- `-O2`: Optimization level 2.
- `-fPIC`: Generates position-independent code, necessary for shared libraries.
- `-Wall -Wextra`: Activates additional warnings to help catch errors.
- `-Wl,--no-undefined`: Prevents library creation if there are undefined symbols.

#### **GCC / Clang (MinGW on Windows)**

```bash
# For a plugin named 'my_plugin.dll' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Statically links the C++ standard library. Essential to prevent your plugin from depending on specific compiler runtime DLLs that may not be present on the user's system.
- `-static-libgcc`: Statically links the GCC library.

### Considerations for Distribution

- **File Name:** Your plugin must have the `.dll` (Windows) or `.so` (Linux) extension. E.g., `my_plugin.dll`.
- **Location:** Place the compiled file in your SA-MP server's `plugins/` folder.
- **server.cfg:** Add your plugin's name (if Windows, without the extension) to the `plugins` line in `server.cfg`.
   ```
   plugins my_plugin (if Linux, my_plugin.so)
   ``

## License

Copyright © **SA-MP Programming Community**

This software is licensed under the terms of the MIT License ("License"); you may use this software according to the License terms. A copy of the License can be obtained at: [MIT License](https://opensource.org/licenses/MIT)

### Terms and Conditions of Use

#### 1. Granted Permissions

This license grants, free of charge, to any person obtaining a copy of this software and associated documentation files, the following rights:
* To use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the software without restriction
* To permit persons to whom the software is furnished to do so, subject to the following conditions

#### 2. Mandatory Conditions

All copies or substantial portions of the software must include:
* The above copyright notice
* This permission notice
* The disclaimer notice below

#### 3. Copyright

The software and all associated documentation are protected by copyright laws. The **SA-MP Programming Community** retains the original copyright of the software.

#### 4. Disclaimer of Warranty and Limitation of Liability

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.

IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

---

For detailed information about the MIT License, visit: https://opensource.org/licenses/MIT