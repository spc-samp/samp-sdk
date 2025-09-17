# SAMP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Ett modernt, endast-header, högnivå C++ SDK för utveckling av SA-MP-plugins och moduler.**

</div>

## Språk

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Türkçe: [README](../Turkce/README.md)

## Innehållsförteckning

- [SAMP SDK](#samp-sdk)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [1. Introduktion och designfilosofi](#1-introduktion-och-designfilosofi)
    - [Problemet med standard SA-MP C API](#problemet-med-standard-sa-mp-c-api)
    - [SAMP SDK-lösningen: Abstraktion med säkerhet och prestanda](#samp-sdk-lösningen-abstraktion-med-säkerhet-och-prestanda)
    - [Endast-header-modell: Fördelar och implikationer](#endast-header-modell-fördelar-och-implikationer)
  - [2. Konfiguration och miljö](#2-konfiguration-och-miljö)
    - [Kompileringskrav](#kompileringskrav)
    - [Rekommenderad filstruktur](#rekommenderad-filstruktur)
    - [Viktiga konfigurationsmakron\*\*](#viktiga-konfigurationsmakron)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP-definitioner och konstanter (`samp_defs.hpp`)](#sa-mp-definitioner-och-konstanter-samp_defshpp)
  - [3. Omfattande API-användarhandbok](#3-omfattande-api-användarhandbok)
    - [3.1. Plugin-livscykeln](#31-plugin-livscykeln)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Avlyssning av Pawn-händelser](#32-plugin_public-avlyssning-av-pawn-händelser)
      - [Syntax och deklaration](#syntax-och-deklaration)
      - [Automatisk parameteröverföring](#automatisk-parameteröverföring)
      - [Flödeskontroll: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#flödeskontroll-plugin_public_continue-vs-plugin_public_stop)
    - [3.3. `Plugin_Native`: Skapa native-funktioner i C++](#33-plugin_native-skapa-native-funktioner-i-c)
      - [Syntax och fast signatur](#syntax-och-fast-signatur)
      - [Automatisk registrering av natives](#automatisk-registrering-av-natives)
      - [Parameterutvinning: `Register_Parameters` vs. `Native_Params`](#parameterutvinning-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Fullständig API: `Get`, `Get_REF`, `Set_REF`)](#native_params-fullständig-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Returvärden](#returvärden)
    - [3.4. `Pawn_*` Makron: Anropa Pawn-funktioner från C++](#34-pawn_-makron-anropa-pawn-funktioner-från-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Syntax och konventioner](#syntax-och-konventioner)
      - [Marshaling av inparametrar](#marshaling-av-inparametrar)
      - [Marshaling av utparametrar (referenser: `int&`, `float&`, `std::string&`)](#marshaling-av-utparametrar-referenser-int-float-stdstring)
      - [Objektet `Callback_Result`: Fullständig analys](#objektet-callback_result-fullständig-analys)
      - [**3.5. `Plugin_Module`: Hantering av dynamiska moduler**](#35-plugin_module-hantering-av-dynamiska-moduler)
      - [Syntax och syfte](#syntax-och-syfte)
      - [Modulens livscykel](#modulens-livscykel)
      - [Fördelar med modularisering](#fördelar-med-modularisering)
    - [3.6. `Plugin_Call`: Anropa interna plugin-natives](#36-plugin_call-anropa-interna-plugin-natives)
      - [Syntax och prestandafördelar](#syntax-och-prestandafördelar)
    - [**3.7. SDK-verktygsfunktioner**](#37-sdk-verktygsfunktioner)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Rekommenderas)](#stdstring-plugin_formatconst-char-format--rekommenderas)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Implementeringsdetalj)](#stdstring-samp_sdkformatconst-char-format--implementeringsdetalj)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. **SDK:s interna anatomi och arkitektur**](#4-sdks-interna-anatomi-och-arkitektur)
    - [4.1. `core.hpp`: Den minimalistiska grunden](#41-corehpp-den-minimalistiska-grunden)
    - [**4.2. `platform.hpp` och `version.hpp`: Kompatibilitet och metadata**](#42-platformhpp-och-versionhpp-kompatibilitet-och-metadata)
    - [4.3. `function_hook.hpp`: x86-avlyssningsmotorn](#43-function_hookhpp-x86-avlyssningsmotorn)
    - [4.4. `interceptor_manager.hpp`: AMX-hook-kontrollern](#44-interceptor_managerhpp-amx-hook-kontrollern)
    - [4.5. `amx_manager.hpp`: Hantering av `AMX*`-instanser](#45-amx_managerhpp-hantering-av-amx-instanser)
    - [4.6. `public_dispatcher.hpp`: `Plugin_Public`-callback-routern](#46-public_dispatcherhpp-plugin_public-callback-routern)
    - [4.7. `native.hpp`: Hantering och anrop av plugin-natives](#47-nativehpp-hantering-och-anrop-av-plugin-natives)
    - [4.8. `callbacks.hpp` \& `amx_memory.hpp`: C++ -\> Pawn-anrop och RAII](#48-callbackshpp--amx_memoryhpp-c---pawn-anrop-och-raii)
    - [4.9. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Abstraherad AMX-åtkomst](#49-amx_apihpp--amx_helpershpp--amx_defsh-abstraherad-amx-åtkomst)
  - [5. Kompilering och distribution](#5-kompilering-och-distribution)
    - [Arkitektur- och plattformskrav](#arkitektur--och-plattformskrav)
    - [Exempel på kompileringskommandon](#exempel-på-kompileringskommandon)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW på Windows)**](#gcc--clang-mingw-på-windows)
    - [Överväganden för distribution](#överväganden-för-distribution)
  - [Licens](#licens)
    - [Användarvillkor](#användarvillkor)
      - [1. Beviljade rättigheter](#1-beviljade-rättigheter)
      - [2. Obligatoriska villkor](#2-obligatoriska-villkor)
      - [3. Upphovsrätt](#3-upphovsrätt)
      - [4. Garantifriskrivning och ansvarsbegränsning](#4-garantifriskrivning-och-ansvarsbegränsning)

## 1. Introduktion och designfilosofi

### Problemet med standard SA-MP C API

SA-MP:s plugin-API är ett programmeringsgränssnitt i C. Även om det är funktionellt och grundläggande, presenterar det de utmaningar som är inneboende i lågnivåprogrammering:
- **Manuell minneshantering:** Funktioner som `amx_Allot` och `amx_Release` kräver att utvecklaren explicit allokerar och frigör minne på AMX-heapen. Detta är en vanlig källa till minnesläckor och runtime-fel.
- **Svag typning och manuella konverteringar:** Parametrar skickas som en array av `cell`s, vilket tvingar fram explicita (och ofta osäkra) konverteringar mellan `cell`, `int`, `float` och `char*`.
- **Verbositet och boilerplate:** Att extrahera flera parametrar från en `cell* params`-array, hantera strängstorlekar och hantera AMX-stacken för C++ till Pawn-callback-anrop kräver repetitiv kod.
- **Gränssnittets bräcklighet:** Bristen på kompileringstidsverifiering (typsäkerhet) innebär att fel vid parameteröverföring eller typer kan gå obemärkta förbi fram till exekvering, vilket orsakar krascher eller odefinierat beteende.

### SAMP SDK-lösningen: Abstraktion med säkerhet och prestanda

SAMP SDK tacklar dessa problem genom att tillhandahålla ett kraftfullt abstraktionslager i C++:
- **RAII (Resource Acquisition Is Initialization):** Automatisk minneshantering i AMX. `Amx_Scoped_Memory` säkerställer att allokerat minne frigörs.
- **Typsäkerhet:** Automatisk och säker parameterkonvertering mellan C++ och Pawn. Du hanterar `int`, `float`, `std::string` direkt.
- **Koncis och idiomatisk syntax:** Makron och mallar tillhandahåller ett rent API som liknar modern C++ mer än det traditionella C-API:et.
- **Robust avlyssning:** En avancerad hooking-motor möjliggör transparent avlyssning av Pawn-callbacks (`Plugin_Public`) och dynamisk registrering av natives.
- **Hög prestanda:** Omfattande användning av kompileringstids-hashing (FNV1a), funktionscaching och `thread_local`-optimeringar för att minimera overheaden av abstraktionerna.

### Endast-header-modell: Fördelar och implikationer

SDK:n består uteslutande av header-filer (`.hpp`, `.h`).
- **Fördelar:**
   - **Förenklad integration:** Inga bibliotek att bygga, länka eller distribuera. Inkludera bara headrarna.
   - **Kompileringsoptimeringar:** Kompilatorn har fullständig insyn i SDK:s och ditt plugins kod, vilket möjliggör aggressiv inlining och länkningstidsoptimeringar, vilket kan resultera i snabbare binärer.
- **Implikationer:**
   - **Kompileringstid:** För mycket stora projekt kan kompileringen ta längre tid på grund av upprepad inkludering av SDK-koden. Detta mildras av inklusionsskydd och C++:s "inkludera bara det som behövs"-karaktär.
   - **Implementeringsmakron:** Behovet av makrot `SAMP_SDK_IMPLEMENTATION` är en konsekvens av endast-header-modellen för att undvika omdefinitioner av symboler.

## 2. Konfiguration och miljö

### Kompileringskrav

- **C++-kompilator:** Kompatibel med C++14 eller högre (SDK:n använder funktioner från C++14, C++17 och C++20 för specifika optimeringar, men C++14 är minimum).
   - GCC (version 7+)
   - Clang (version 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Arkitektur:** **x86 (32-bit)**. SA-MP fungerar uteslutande på denna arkitektur. SDK:n innehåller kontroller i `platform.hpp` som kommer att utfärda kompileringsfel om felaktig arkitektur upptäcks.
- **Operativsystem:** Windows eller Linux.

### Rekommenderad filstruktur

För tydlighet och organisation är det vanligt att organisera SDK:n i en undermapp `samp-sdk`.

```
my_plugin/
├── samp-sdk/
│   ├── // Other SDK files
│   └── samp_sdk.hpp             // The main header to include
│
├── src/
│   ├── main.cpp                  // Where SAMP_SDK_IMPLEMENTATION is defined
│   └── my_custom_logic.cpp       // Optional, for organizing code
│
└── CMakeLists.txt (or .vcxproj, Makefile)
```

### Viktiga konfigurationsmakron**

Definiera alltid dessa makron *innan* du inkluderar `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Syfte:** Signalerar till kompilatorn att denna `.cpp`-fil ska generera implementationerna av pluginets exportfunktioner (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **SDK:n sköter exporten av dessa funktioner automatiskt, vilket eliminerar behovet av `.def`-filer (på Windows) eller `__attribute__((visibility("default")))`-deklarationer (på Linux) för dessa funktioner.**
- **Teknisk inverkan:** Utan detta makro kommer länkaren inte att hitta de nödvändiga exportfunktionerna, och SA-MP-servern kommer inte att kunna ladda ditt plugin.
- **Grundläggande regel:** **Definiera detta makro i ENDAST EN `.cpp`-fil i hela ditt projekt.** Att definiera det i mer än en fil kommer att orsaka ett länkningsfel med "dubbel symbol".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // The macro makes the SDK export the necessary functions automatically.
#include "samp-sdk/samp_sdk.hpp"

// ... your plugin code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Syfte:** Aktiverar SDK:ns funktioner relaterade till interaktion med AMX-miljön (Pawn virtual machine).
- **Aktiverade funktioner:**
   - Deklaration och registrering av C++ natives med `Plugin_Native`.
   - Callbacks `OnAmxLoad(AMX* amx)` och `OnAmxUnload(AMX* amx)`.
   - Makrot `Plugin_Call` för att anropa pluginets egna natives.
- **Teknisk inverkan:** När detta makro är definierat samlar SDK:n automatiskt in alla dina `Plugin_Native`:er. I funktionen `Supports()` läggs flaggan `SUPPORTS_AMX_NATIVES` automatiskt till.
- **Flexibilitet:** **Du kan definiera detta makro i flera `.cpp`-filer.** SDK:ns statiska registreringssystem (`Native_Registrar`) kommer att konsolidera alla natives från olika kompilatorer till en enda global lista.

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

- **Syfte:** Aktiverar callbacken `OnProcessTick()`, som regelbundet anropas av servern.
- **Teknisk inverkan:** Lägger automatiskt till flaggan `SUPPORTS_PROCESS_TICK` i funktionen `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logic executed at each server "tick" (e.g., 20ms)
    // Be careful with heavy operations here!
}
```

### SA-MP-definitioner och konstanter (`samp_defs.hpp`)

Denna fil tillhandahåller alla kända SA-MP-konstanter och gränser, såsom `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. Den inkluderas automatiskt av `samp_sdk.hpp` och bör användas för att säkerställa kodkompatibilitet och läsbarhet.

## 3. Omfattande API-användarhandbok

### 3.1. Plugin-livscykeln

Följande funktioner är start- och stopppunkterna för ditt plugin, automatiskt exporterade av SDK:n.

#### `bool OnLoad()`

- **Beskrivning:** Första funktionen som anropas av SA-MP-servern efter att ditt plugin har laddats in i minnet.
- **Användning:** Idealisk för att initiera system, ladda konfigurationer, öppna databasanslutningar eller ladda moduler (`Plugin_Module`).
- **Retur:**
   - `true`: Pluginet har initierats framgångsrikt och laddningen fortsätter.
   - `false`: Pluginet misslyckades med att initieras. Laddningen kommer att avbrytas och pluginet kommer att avlastas.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Example: Load a module (more details in section 3.5)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database Module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load the database module!");

        return false; // Aborts the loading of the main plugin
    }

    return true;
}
```

#### `void OnUnload()`

- **Beskrivning:** Sista funktionen som anropas av SA-MP-servern innan den avlastar ditt plugin från minnet.
- **Användning:** Idealisk för att rensa resurser, stänga anslutningar, spara tillstånd och säkerställa att inga resurser läcker ut. SDK:n hanterar avlastning av moduler (`Plugin_Module`) automatiskt.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // No manual action is needed for modules loaded via Plugin_Module;
    // the SDK handles it.
}
```

#### `unsigned int GetSupportFlags()`

- **Beskrivning:** Informerar SA-MP-servern om vilka funktioner ditt plugin stöder och vill använda.
- **Användning:** **Returnera alltid `SUPPORTS_VERSION` (eller `SAMP_PLUGIN_VERSION`).** De andra flaggorna (`SUPPORTS_AMX_NATIVES`, `SUPPORTS_PROCESS_TICK`) läggs automatiskt till av SDK:n om makrona `SAMP_SDK_WANT_AMX_EVENTS` och `SAMP_SDK_WANT_PROCESS_TICK` är definierade. Detta förenklar underhållet och förhindrar fel.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // The SDK adds the necessary flags automatically.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Kräver:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beskrivning:** Anropas varje gång ett nytt Pawn-skript (ett Gamemode eller Filterscript) laddas och initieras på servern.
- **Användning:** Om du behöver specifik logik för varje AMX-skript, som att registrera anpassade natives (även om `Plugin_Native` gör detta automatiskt), eller initiera skriptspecifik data.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxLoad(AMX* amx) {
    // amx represents the new loaded script instance.
    // You can, for example, call a specific public in this script:
    // Pawn_Public_OnAmx("OnMyPluginLoaded", amx); // Hypothetical example of a more advanced API.
    Samp_SDK::Log("AMX script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Kräver:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beskrivning:** Anropas när ett Pawn-skript avlastas från servern.
- **Användning:** För att rensa eventuella specifika resurser som du allokerade eller associerade med den specifika `AMX*`.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Kräver:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Beskrivning:** Anropas upprepade gånger vid varje "tick" av servern (vanligtvis 20 gånger per sekund, eller var 50:e ms).
- **Användning:** För kontinuerlig bakgrundslogik, timers, tillståndsuppdateringar som inte är beroende av spelarhändelser, eller datasynkronisering.
- **Varning:** Undvik blockering eller beräkningsmässigt tunga operationer här, eftersom de kan orsaka lagg på servern.

```cpp
// main.cpp (with SAMP_SDK_WANT_PROCESS_TICK defined)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Every 10 seconds (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Avlyssning av Pawn-händelser

Makrot `Plugin_Public` är den primära bryggan för att ta emot Pawn-callbacks i din C++-kod.

#### Syntax och deklaration

- `Plugin_Public(PublicName, Type1 Param1, Type2 Param2, ...)`
- C++-funktionsnamnet du deklarerar **måste vara detsamma** som Pawn-callback-namnet (t.ex. `OnPlayerConnect`).
- C++-parametertyperna (`int`, `float`, `std::string`) konverteras automatiskt av SDK:n.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    // ...
}
```

#### Automatisk parameteröverföring

SDK:n hanterar automatiskt läsning från AMX:s `cell stack` och konvertering till de specificerade C++-typerna:
- `int`: Konverteras direkt från `cell`.
- `float`: Konverteras från `cell` med `amx::AMX_CTOF`.
- `std::string`: SDK:n läser strängadressen i AMX, allokerar en `std::string` i C++ och kopierar innehållet.

#### Flödeskontroll: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

Returvärdet från din `Plugin_Public`-funktion är avgörande och bestämmer callbackens exekveringsflöde:
- `return PLUGIN_PUBLIC_CONTINUE;` (värde `1`): Indikerar att callbackens exekvering ska **fortsätta**. Om det finns andra plugins som också fångar denna callback, kommer de att anropas. Därefter kommer den ursprungliga `public`-funktionen i Pawn-skriptet att anropas.
- `return PLUGIN_PUBLIC_STOP;` (värde `0`): Indikerar att callbackens exekvering ska **avbrytas**. Inga andra plugins eller den ursprungliga `public`-funktionen i Pawn-skriptet kommer att anropas för denna händelse. Detta är idealiskt för att implementera ett system som "skriver över" eller "blockerar" ett standardbeteende i SA-MP.

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

### 3.3. `Plugin_Native`: Skapa native-funktioner i C++

`Plugin_Native` låter dig utöka Pawn-funktionaliteten med högpresterande C++-kod.

#### Syntax och fast signatur

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- C++-funktionen måste ha exakt denna signatur: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` är det namn som Pawn-skripten kommer att använda.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementation ...
    return 0;
}
```

#### Automatisk registrering av natives

> [!NOTE]
> Du behöver **inte** anropa `amx_Register` manuellt. SDK:n detekterar alla dina `Plugin_Native`:er (i vilken `.cpp`-fil som helst med `SAMP_SDK_WANT_AMX_EVENTS`) och registrerar dem automatiskt i varje laddat AMX-skript (`OnAmxLoad`).

#### Parameterutvinning: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Beskrivning:** Enklare hjälpfunktion för att extrahera flera parametrar sekventiellt.
- **Användning:** `Register_Parameters(variable1, variable2, ...)`
- **Begränsningar:** Endast för inparametrar. Hanterar inte valfria parametrar eller åtkomst via index.
- **Stödda typer:** `int`, `float`, `std::string`.

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

##### `Native_Params` (Fullständig API: `Get`, `Get_REF`, `Set_REF`)

- **Beskrivning:** En wrapper-klass som tillhandahåller ett objektorienterat gränssnitt för att komma åt parametrarna i en native. Kraftfullare för komplexa scenarier.
- **Konstruktion:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Beskrivning:** Returnerar antalet parametrar som skickats till native-funktionen.
- **Användning:** Väsentligt för att hantera valfria parametrar.

###### `p.Get<T>(size_t index)`

- **Beskrivning:** Extraherar en inparameter efter index och konverterar den till typen `T`.
- **Stödda typer:** `int`, `float`, `std::string`.

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

- **Beskrivning:** Hämtar värdet av en **referensparameter** (Pawn-pekare) och lagrar det i `out_value`.
- **Användning:** För att läsa värden som har skickats med referens från Pawn.
- **Retur:** `true` om AMX-adressen är giltig, `false` annars.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Get the values of the references (Pawn passed addresses)
    p.Get_REF(1, health); // Reads the value of Float:health
    p.Get_REF(2, money);   // Reads the value of money
    
    Samp_SDK::Log("Player %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Now, modify them
    health = 50.0f;
    money += 100;
    
    // And write them back to Pawn's memory
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Beskrivning:** Returnerar en `std::optional<T>` för att läsa en referensparameter. Säkrare för C++17 och senare.

###### `p.Set_REF<T>(size_t index, T value)`

- **Beskrivning:** Skriver ett värde `T` till en Pawn **referensparameter** (adressen som Pawn skickade).
- **Användning:** För att ändra värden som skickades med referens, så att Pawn ser ändringen.
- **Retur:** `true` om skrivningen lyckades, `false` annars.

#### Returvärden

- Din `Plugin_Native`-funktion måste returnera en `cell`.
- För att returnera en `int` eller `bool`, använd en cast till `cell`.
- För att returnera en `float`, använd `amx::AMX_FTOC(my_float)`.

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

### 3.4. `Pawn_*` Makron: Anropa Pawn-funktioner från C++

Dessa makron är motsatsen till `Plugin_Public` och `Plugin_Native`: de låter din C++-kod anropa Pawn-funktioner.

#### `Pawn_Native(NativeName, ...)`

- **Syfte:** Det rekommenderade sättet att anropa SA-MP-natives (eller från andra plugins) från C++.
- **Mekanism:** Letar upp native-pekaren i SDK:ns interna cache (fylld av `Amx_Register_Detour`). Om den hittas, exekverar den native-funktionen i en `Amx_Sandbox`-miljö (en falsk, isolerad AMX-instans).
- **Prestanda:** Den mest effektiva, eftersom den undviker den dyra sökningen efter `publics` och interagerar direkt med native-pekaren.

#### `Pawn_Public(PublicName, ...)`

- **Syfte:** Anropar en specifik public-funktion i ett Pawn-skript.
- **Mekanism:** Går igenom `AMX*`-instanserna som hanteras av `Amx_Manager`, letar upp `public`-funktionen med namnet och exekverar den.
- **Prestanda:** Mindre effektiv än `Pawn_Native` på grund av sökningen och den faktiska `amx_Exec`. Generellt är `publics` långsammare än `natives`.
- **Användning:** Idealisk för att anropa anpassade händelser i din Gamemode/Filterscripts som inte är natives.

#### `Pawn(FunctionName, ...)`

- **Syfte:** Ett bekvämlighetsmakro som försöker gissa om funktionen är en native eller en public.
- **Mekanism:** Först försöker den anropa som `Pawn_Native`. Om det misslyckas (native-funktionen hittas inte), försöker den anropa som `Pawn_Public`.
- **Prestanda:** Kan vara något långsammare än `Pawn_Native` om funktionen är en native, på grund av det dubbla sökförsöket. För `publics` är prestandan densamma som `Pawn_Public`.
- **Användning:** För funktioner där du inte är säker på om de är natives eller publics, eller för att undvika boilerplate för att prova den ena och sedan den andra.

#### Syntax och konventioner

- **Funktionsnamn:** Använd alltid Pawn-funktionens namn **direkt, utan citationstecken**. SDK:n konverterar det internt till en sträng.
- **Parametrar:** Skicka C++-parametrarna direkt.

```cpp
// Correct:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Incorrect (but would technically work due to hashing, avoid):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshaling av inparametrar

SDK:n konverterar dina C++-typer till AMX:s `cell`-format och hanterar minnet vid behov:
-   `int`, `bool`, `long`, `enum` -> `cell`
-   `float`, `double` -> `cell` (med `amx::AMX_FTOC`)
-   `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (allokerar minne i AMX, kopierar strängen och skickar `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshaling av utparametrar (referenser: `int&`, `float&`, `std::string&`)

Detta är en viktig funktion för bekvämlighet och säkerhet. För Pawn-funktioner som förväntar sig en pekare (referens), automatiserar SDK:n hela processen med minnesallokering/frigörning och datakopiering.

- **Hur man använder:** Skicka helt enkelt din variabel med referens (`&`).
- **Mekanism:** SDK:n allokerar minne på AMX-heapen, skickar AMX-adressen till Pawn-funktionen, väntar på att Pawn-funktionen ska fylla den adressen, läser tillbaka värdet och frigör AMX-minnet. Allt transparent.
- **Med `std::string&`:** SDK:n allokerar en standardbuffer (256 celler) i AMX för strängen.

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

#### Objektet `Callback_Result`: Fullständig analys

Alla `Pawn_*`-anrop returnerar ett `Callback_Result`-objekt. Detta objekt är en säker wrapper för resultatet av Pawn-anropet.

- `Callback_Result() noexcept`: Standardkonstruktor, indikerar fel (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Konstruktor för framgång eller fel med värde.
- `explicit operator bool() const`: Tillåter att använda `if (result)` för att kontrollera om anropet lyckades.
- `operator cell() const`: Tillåter att konvertera resultatet till `cell` för att få värdet.
- `float As_Float() const`: Bekvämlighet för att få resultatet som `float`.
- `cell Value() const`: Returnerar råvärdet `cell`.
- `bool Success() const`: Returnerar `true` om Pawn-anropet lyckades.
- `int Get_Amx_Error() const`: Returnerar AMX-felkoden om anropet misslyckades (0 för framgång).

```cpp
// Example: Getting a player's health.
// The native GetPlayerHealth(playerid, &Float:health) expects a playerid and a reference to health.
int playerid = 0; // Example player ID
float player_health = 0.0f;

// We call GetPlayerHealth, passing playerid and player_health by reference.
// The SDK will handle the marshalling for the output parameter 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Checks if the call was successful (operator bool)
    // The value returned by result.As_Float() or result (operator cell)
    // would be the return value of the *native*, not the output parameter.
    // The health value has already been updated in 'player_health' due to output parameter marshalling.
    Samp_SDK::Log("Player %d has %.1f health.", playerid, player_health);
} else {
    // The call failed, perhaps the player does not exist or the native was not found.
    Samp_SDK::Log("Error getting player %d health. AMX Code: %d", playerid, result.Get_Amx_Error());
}

// For natives that return a value and use output parameters (less common, but possible),
// you would use both:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param is already updated
// }
```

#### **3.5. `Plugin_Module`: Hantering av dynamiska moduler**

Makrot `Plugin_Module` gör det möjligt för ditt plugin att fungera som en "laddare" för andra plugins, vilket skapar en modulär och utbyggbar arkitektur. En modul som laddas på detta sätt behandlas som ett förstklassigt plugin, med sin egen livscykel för händelser som hanteras av värd-pluginet.

#### Syntax och syfte

- `Plugin_Module(const char* nome_do_arquivo_base, const char* diretorio_do_modulo, const char* mensagem_sucesso_opcional)`
- `nome_do_arquivo_base`: Basnamnet på modulfilen, **utan tillägget** (t.ex. för `my_module.dll` eller `my_module.so`, använd `"my_module"`). SDK:n lägger automatiskt till tillägget `.dll` eller `.so` som är lämpligt.
- `diretorio_do_modulo`: Sökvägen till katalogen där modulfilen finns (t.ex. `"plugins/my_custom_modules"`). **Inkludera inte filnamnet här.** SDK:n kommer att sammanfoga den fullständiga sökvägen (`diretorio_do_modulo/nome_do_arquivo_base.ext`).
- `mensagem_sucesso_opcional`: Ett valfritt meddelande som loggas till serverkonsolen om modulen laddas framgångsrikt.

```cpp
// main.cpp, inuti OnLoad()

// Laddar modulen 'core_logic.dll' (eller 'core_logic.so')
// som finns i mappen 'modules/custom/' på servern.
if (!Plugin_Module("core_logic", "modules/custom", "Kärnlogikmodul laddades framgångsrikt!"))
    return (Samp_SDK::Log("KRITISKT FEL: Misslyckades med att ladda modulen 'core_logic'!"), false);

// Laddar modulen 'admin_system.dll' (eller 'admin_system.so')
// som finns direkt i mappen 'plugins/' på servern.
if (!Plugin_Module("admin_system", "plugins", "Administrationsmodul aktiverad."))
    Samp_SDK::Log("VARNING: Administrationsmodulen kunde inte laddas.");
```

#### Modulens livscykel

En modul måste exportera funktionerna `Load`, `Unload` och `Supports`, precis som ett vanligt plugin. SDK:n hanterar modulens livscykel på följande sätt:

- **Laddning:** När `Plugin_Module` anropas, gör SDK:n följande:
   1. Bygger den fullständiga sökvägen till filen (t.ex. `modules/custom/core_logic.dll`).
   2. Använder `Dynamic_Library` (`LoadLibrary`/`dlopen`) för att ladda binärfilen.
   3. **Hämtar pekare till ALLA livscykelfunktioner för modulen:**
      - **Obligatoriska:** `Load`, `Unload`, `Supports`. Om någon saknas misslyckas laddningen av modulen.
      - **Valfria:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Anropar modulens `Load`-funktion och skickar med `ppData` från huvudpluginet.
   5. Om `Load` returnerar `true`, läggs modulen till i den interna listan över laddade moduler.

- **Vidarebefordran av händelser:** Värd-pluginet **vidarebefordrar automatiskt** händelser till alla laddade moduler.
 > [!IMPORTANT]
 > För att händelser ska vidarebefordras korrekt måste **värd-pluginet** (det som anropar `Plugin_Module`) vara konfigurerat för att ta emot dessa händelser.
 > - För att `AmxLoad` och `AmxUnload` ska fungera i moduler måste värd-pluginet definiera makrot `SAMP_SDK_WANT_AMX_EVENTS`.
 > - För att `ProcessTick` ska fungera i moduler måste värd-pluginet definiera makrot `SAMP_SDK_WANT_PROCESS_TICK`.

- **Avladdning:** Under `OnUnload` för ditt huvudplugin avladdar SDK:n alla moduler som laddats via `Plugin_Module`. Detta sker i **omvänd ordning** jämfört med laddningen (den senast laddade modulen avladdas först), vilket är avgörande för att hantera beroenden och säkerställa korrekt frigöring av resurser.

#### Fördelar med modularisering

- **Kodorganisation:** Dela upp stora plugins i mindre, hanterbara komponenter, var och en i sin egen modulfils.
- **Återanvändbarhet:** Skapa generiska moduler (t.ex. en databasmodul, en avancerad loggningsmodul) som kan användas av olika plugins, vilket främjar kodåteranvändning.
- **Oberoende komponenter:** Skapa moduler som är **helt händelsestyrda och oberoende**. En modul kan ha sina egna `Plugin_Native`s, fånga upp `Plugin_Public`s och ha sin egen `OnProcessTick`-logik, och fungerar som ett självständigt plugin men laddas av en värd.
- **Dynamiska uppdateringar:** I kontrollerade scenarier möjliggör det uppdatering av delar av systemet (genom att ersätta en `.dll` eller `.so` för en modul) utan att behöva kompilera om och starta om huvudpluginet eller hela servern (även om detta kräver strikt hantering av versioner och kompatibilitet).

### 3.6. `Plugin_Call`: Anropa interna plugin-natives

Använd `Plugin_Call` för att anropa en `Plugin_Native` definierad **inom ditt eget plugin**.

#### Syntax och prestandafördelar

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Fördel:** Undviker överhuvudet med att söka efter native-funktionen i AMX:s native-array. SDK:n upprätthåller en direkt mappning av namn-hashingar till funktionspekare för sina egna natives, vilket gör detta till det snabbaste sättet att anropa dem internt.
- **Kräver:** `SAMP_SDK_WANT_AMX_EVENTS`.

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
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Calls your own native
                Samp_SDK::Log("Player %d is at a high level!", i);
        }
    }
}
```

### **3.7. SDK-verktygsfunktioner**

#### `Samp_SDK::Log(const char* format, ...)`

- **Beskrivning:** Skriver ut meddelanden till serverkonsolen och `server_log.txt`. En säker wrapper för `logprintf`.
- **Användning:** För felsökning, statusmeddelanden och fel.
- **Mekanism:** Internt hämtar SDK:n pekaren till `logprintf` via `ppData[PLUGIN_DATA_LOGPRINTF]`. Funktionen hanterar strängformatering på ett säkert sätt.

```cpp
// Anywhere in your plugin
Samp_SDK::Log("The plugin was initialized with a value %d and a string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Rekommenderas)

- **Beskrivning:** Formaterar en sträng på ett säkert sätt (liknar `sprintf`) och returnerar en `std::string`. Detta är det **rekommenderade och mest idiomatiska** sättet att formatera strängar för användning inom ditt plugin.
- **Användning:** Idealisk för att konstruera formaterade meddelanden innan du skickar dem till `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, eller för något annat strängbehov inom din C++-kod.
- **Mekanism:** Internt är `Plugin_Format` ett makro som anropar `Samp_SDK::Format`. Det använder `vsnprintf` för att bestämma den exakta storleken på den formaterade strängen och allokerar en `std::string` med tillräcklig kapacitet, vilket förhindrar buffertöverskridanden.

```cpp
int playerid = 0; // Example ID
int health = 50;
std::string status_message = Plugin_Format("Player %d, your current health is %d.", playerid, health); // Using the Plugin_Format macro
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, status_message);

// Can also be used for internal logs
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid).c_str());
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Implementeringsdetalj)

- **Beskrivning:** Den underliggande implementeringsfunktionen för strängformatering, belägen inom `Samp_SDK`-namnrymden.
- **Användning:** Kallas vanligtvis inte direkt av användaren. Makrot `Plugin_Format` tillhandahålls som en bekvämlighet för denna funktion, i linje med namngivningskonventionen för andra SDK-makron (`Plugin_Public`, `Plugin_Native`). Du skulle bara anropa den direkt om du ville undvika makrot `Plugin_Format` av någon specifik anledning.

```cpp
// Example of how Samp_SDK::Format works, but prefer Plugin_Format
std::string raw_status = Samp_SDK::Format("For internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Beskrivning:** Konverterar en AMX-strängadress (`cell amx_addr`) till en C++ `std::string`.
- **Användning:** Huvudsakligen inom `Plugin_Native` när du behöver komma åt strängar som inte konverteras automatiskt av `Register_Parameters` eller `Native_Params` (t.ex. om Pawn-parametern är en `const` `string` och inte deklarerades som `std::string` i din `Plugin_Native` eller `Plugin_Public` för automatisk marshaling).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Gets the AMX string address

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("AMX String: %s", cpp_string.c_str());

    return 1;
}
```

## 4. **SDK:s interna anatomi och arkitektur**

Detta avsnitt avslöjar de underliggande mekanismerna i SAMP SDK, utforskar dess arkitektur, nyckelkomponenter och hur de interagerar för att tillhandahålla abstraktion på hög nivå. En djup förståelse för dessa inre delar ger utvecklaren möjlighet att optimera användningen av SDK:n, felsöka komplexa problem och till och med utöka dess funktionalitet.

### 4.1. `core.hpp`: Den minimalistiska grunden

`Samp_SDK::Core` är en `singleton` som fungerar som den initiala och centraliserade åtkomstpunkten till lågnivådata som tillhandahålls av SA-MP plugin-miljön. Dess huvudsakliga ansvar är att kapsla in och exponera de väsentliga funktionerna.

- **`Samp_SDK::Core::Instance()`**:
   - **Beskrivning:** Returnerar den enda globala instansen av klassen `Core`. Detta är ett `singleton`-designmönster för att säkerställa att åtkomsten till plugin-data (`ppData`) är konsekvent och centraliserad.
   - **Mekanism:** Instansen initieras en gång när `Core::Instance().Load(ppData)` anropas i pluginets `Load()`-funktion.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Beskrivning:** Tillåter säker och indexerad åtkomst till funktionspekarna i AMX API. Arrayen `pAMXFunctions` (mottagen via `ppData[PLUGIN_DATA_AMX_EXPORTS]`) innehåller adresserna till kritiska funktioner som `amx_Exec`, `amx_Register`, etc.
   - **Inverkan:** Istället för att använda `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, erbjuder SDK:n typsäkra wrappers i `amx::`-namnrymden (t.ex. `amx::Exec(...)`), vilket gör koden mer läsbar och mindre benägen för cast-fel.
   - **Internt exempel (`amx_api.hpp`):**
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
   - **Beskrivning:** En pekare till SA-MP:s `logprintf`-funktion, som är standardgränssnittet för att skriva ut meddelanden till serverkonsolen och `server_log.txt`.
   - **Mekanism:** `Samp_SDK::Log` är en säker wrapper som använder denna pekare, vilket säkerställer att dina meddelanden visas korrekt i SA-MP-miljön.

### **4.2. `platform.hpp` och `version.hpp`: Kompatibilitet och metadata**

Dessa header-filer utgör grunden för SDK:ns portabilitet och optimering, anpassar den till olika kompileringsmiljöer och utnyttjar specifika funktioner i modern C++.

- **Plattforms- och arkitekturdetektering:**
   - **Mekanism:** Använder förprocessor-makron (`#if defined(WIN32)`, `#if defined(__linux__)`, etc.) för att identifiera operativsystemet.
   - **Arkitekturverifiering:** Innehåller `static_assert` eller `#error` för att säkerställa att pluginet kompileras för x86 (32-bit), ett kritiskt krav för kompatibilitet med SA-MP och hooking-mekanismen.
   - **Hantering av symboleksport:**
      - `SAMP_SDK_EXPORT`: Ett makro definierat i `platform.hpp` som expanderar till `extern "C"` och, på Linux, lägger till `__attribute__((visibility("default")))`. På Windows säkerställer det bara `extern "C"` eftersom SDK:n använder `pragma comment(linker, "/EXPORT:...")` (för MSVC) eller MinGW-standarden för att exportera huvudfunktionerna.
      - Detta säkerställer att pluginets livscykelfunktioner (`Supports`, `Load`, `Unload`, etc.) korrekt exporteras från din DLL/SO, oavsett kompileringsmiljö, **utan behov av `.def`-filer eller att manuellt lägga till `__attribute__((visibility("default")))`** i din implementering.
   - **Exempel (`platform.hpp` - relevant fragment):**
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
   - **Exempel (`samp_sdk.hpp` - relevant implementeringsfragment):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // On Windows (MSVC), we use pragma comment to export the functions.
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

- **Optimerings- och branch-förutsägelsemakron:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mekanism:** `__forceinline` (MSVC) eller `__attribute__((always_inline)) inline` (GCC/Clang). Föreslår starkt för kompilatorn att infoga funktionens kropp direkt på anropsplatsen, vilket eliminerar overheaden av ett faktiskt funktionsanrop.
      - **Användning:** Tillämpas på små och prestandakritiska funktioner inom SDK:n.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mekanism:** `[[likely]]` / `[[unlikely]]` (C++20) eller `__builtin_expect` (GCC/Clang). Tips till kompilatorn om vilken väg en `if/else` är mest sannolik att tas.
      - **Inverkan:** Hjälper kompilatorn att generera effektivare kod för branch prediction, vilket minskar CPU-latensen.
      - **Exempel (`platform.hpp`):**
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

- **Standard C++-definitioner (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mekanism:** Makron definierade baserat på värdet av `__cplusplus` och `_MSVC_LANG`.
   - **Användning:** Tillåter SDK:n att använda nyare C++-funktioner (som `std::apply` och `if constexpr` från C++17, eller `std::is_same_v` från C++17) när de är tillgängliga, samtidigt som kompatibiliteten med äldre standarder bibehålls.
   - **Exempel (`version.hpp` - användning av `if constexpr`):**
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

### 4.3. `function_hook.hpp`: x86-avlyssningsmotorn

Denna header definierar lågnivåmekanismen för att utföra hooks (avlyssningar) av funktioner, vilket är grundläggande för SDK:ns funktion. Den är strikt beroende av x86 (32-bit)-arkitekturen.

- **`X86_Detour`**:
   - **Beskrivning:** En klass som kapslar in logiken för att skriva över början av en funktion i minnet med en hoppinstruktion till en detour-funktion.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mekanism:** I x86 har den relativa hoppinstruktionen (`JMP`) vanligtvis 5 byte: `0xE9` (opcode för JMP near, relative) följt av 4 byte som representerar förskjutningen (offset) av måladdressen i förhållande till nästa instruktion.
      - **Exempel på instruktion:** `E9 XX XX XX XX` (där `XX` är förskjutningsbyten).
   - **`Apply(void* target, void* detour)`**:
      - **Åtgärd:** Installerar hooken. Först lagras de `JUMP_INSTRUCTION_SIZE` originalbyten från `target`-funktionen (`original_bytes_`). Sedan beräknas den relativa adressen för `detour` i förhållande till `target` och början av `target` skrivs över med `JMP`-instruktionen.
      - **Exempel på beräkning av relativ adress:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Address of the detour - (Address of the target + Size of the JMP instruction)
         ```
   - **`Revert()`**:
      - **Åtgärd:** Avinstallerar hooken, återställer de `original_bytes_` i `target`-funktionen.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mekanism:** På Windows används `VirtualProtect`; på Linux, `mprotect`. Dessa systemanrop ändrar behörigheterna för minnessidan där funktionen finns till `EXECUTE_READWRITE` (Windows) eller `PROT_WRITE | PROT_EXEC` (Linux), vilket tillåter att koden modifieras under exekvering.
      - **Exempel (`Unprotect_Memory`):**
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
   - **Beskrivning:** En C++ `type-safe` wrapper för `X86_Detour`, som säkerställer att funktionens pekartyper är korrekta.
   - `Install(void* target, void* detour)`: Inkapslar anropet `X86_Detour::Apply`.
   - `Uninstall()`: Inkapslar anropet `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Säkerhetsmekanism (rekursionsskydd):** Denna funktion är kritisk för att undvika oändliga loopar när detektorn behöver anropa den ursprungliga funktionen. Den **avinstallerar temporärt hooken (`detour_.Revert()`)**, anropar den ursprungliga funktionen (`Get_Original()(args...)`), och **återinstallerar sedan hooken (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: En räknare som säkerställer att hooken endast återinstalleras när den högsta nivån av ursprunglig anrop har slutförts, vilket tillåter säkra rekursiva anrop av den ursprungliga funktionen (om den ursprungliga funktionen är rekursiv, till exempel). `thread_local` säkerställer att `recursion_guard` är isolerad för varje tråd, viktigt i flertrådade miljöer.
      - **Exempel (`Call_Original` med Scope_Guard):**
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

### 4.4. `interceptor_manager.hpp`: AMX-hook-kontrollern

Denna `singleton` är nervcentrumet för SDK:ns interaktion med SA-MP:s AMX virtual machine. Den koordinerar installationen av hooks som tillhandahålls av `function_hook.hpp` i AMX API-funktionerna som exponeras av servern, och omdirigerar exekveringsflödet till SDK:ns logik.

- **`Activate()` / `Deactivate()`**:
   - **Beskrivning:** Offentliga metoder för att installera och avinstallera alla nödvändiga hooks. Anropas i ditt plugins `OnLoad()` respektive `OnUnload()`.
   - **Mekanism:** Hämtar pekarna till AMX-funktionerna (som `amx_Register`, `amx_Exec`, etc.) med `Core::Instance().Get_AMX_Export(...)` och installerar detours.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Hooked-funktion:** `amx_Register`
   - **Syfte:** Avlyssnar registreringen av *alla* natives (av SA-MP, andra plugins eller gamemode).
   - **Åtgärd:** Anropar `Interceptor_Manager::Instance().Cache_Natives()` för att lagra pekarna och namnen på natives i en intern cache.
   - **Inverkan:** Denna cache är grundläggande för `Pawn_Native`s prestanda, vilket möjliggör en extremt snabb sökning efter native-pekaren istället för en kostsam sökning i AMX.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Hooked-funktion:** `amx_Exec`
   - **Syfte:** **Detta är den mest kritiska hooken.** Den avlyssnar *alla* kodexekveringar i AMX, inklusive anrop av Pawn `publics`.
   - **Mekanism för att avlyssna `Plugin_Public`:**
      1. När `amx_Exec` anropas för en `public` (eller `AMX_EXEC_MAIN`), exekveras `Amx_Exec_Detour`.
      2. Den hämtar namnet på `public`-funktionen (med `Get_Public_Name_By_Index` eller `tl_public_name`).
      3. Frågar `Public_Dispatcher::Instance().Dispatch()` för att kontrollera om det finns C++-hanterare registrerade för detta namn.
      4. Om det finns hanterare, exekverar den dem. `Public_Dispatcher` hanterar `marshalling` av parametrarna från AMX till de korrekta C++-typerna.
      5. Baserat på returvärdet från `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), bestämmer den om den ska anropa den ursprungliga `amx_Exec` (`Get_Amx_Exec_Hook().Call_Original(...)`) eller avsluta exekveringen av Pawn `public`.
      6. **Stackhantering:** Om exekveringen av Pawn `public` avbryts (`PLUGIN_PUBLIC_STOP`), korrigerar `Amx_Exec_Detour` AMX-stacken (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) för att undvika inkonsekvenser.
   - **Exempel (`Amx_Exec_Detour`):**
      ```cpp
      // Simplified snippet from interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          // ... logic to determine the public name ...
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
   - **Hooked-funktion:** `amx_FindPublic`
   - **Syfte:** Avlyssnar sökningen efter `publics` med namn.
   - **"Ghost Publics"-mekanism:** Om den ursprungliga `amx_FindPublic` inte hittar en `public` i Pawn, men `Public_Dispatcher` har en C++-hanterare registrerad för det namnet, returnerar denna hook `AMX_ERR_NONE` och ett speciellt `index` (`PLUGIN_EXEC_GHOST_PUBLIC`). Detta får SA-MP:s API att "tro" att `public`-funktionen existerar, vilket tillåter att det efterföljande `amx_Exec`-anropet (för detta speciella index) avlyssnas av `Amx_Exec_Detour`, som sedan omdirigerar till C++-hanteraren.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Används för att skicka namnet på `public`-funktionen till `Amx_Exec_Detour` när en "ghost public" upptäcks, eftersom `amx_Exec` endast tar emot indexet, inte namnet.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Hooked-funktioner:** `amx_Init` / `amx_Cleanup`
   - **Syfte:** Hantera listan över aktiva `AMX*`-instanser.
   - **Åtgärd:** `Amx_Init_Detour` anropar `Amx_Manager::Instance().Add_Amx()`, och `Amx_Cleanup_Detour` anropar `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Hantering av `AMX*`-instanser

Denna `singleton` upprätthåller ett dynamiskt register över alla AMX virtuella maskiner som för närvarande är laddade på servern. Det är viktigt för funktioner som behöver interagera med "alla skript" eller hitta ett specifikt skript.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Beskrivning:** En lista med pekare till alla `AMX*`-instanser som har initierats (gamemode och filterscripts).
   - **Hantering:** Fylls av `Amx_Init_Detour`-hooks och töms av `Amx_Cleanup_Detour`-hooks.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Syfte:** Skyddar `loaded_amx_` mot samtidig åtkomst i flertrådade miljöer (även om SA-MP i huvudsak är en enkeltrådad, är detta en god säkerhetsvana). `std::shared_mutex` tillåter flera läsare samtidigt, men endast en skrivare.
- **`std::atomic<uint32_t> generation_`**:
   - **Syfte:** En räknare som ökar varje gång en AMX läggs till eller tas bort.
   - **Användning:** Används av `Caller_Cache` i `callbacks.hpp` för att detektera när listan över AMX:er har ändrats, ogiltigförklarar cachelagrade sökningar efter `publics` och säkerställer att `Pawn_Public`-anrop alltid fungerar med uppdaterad information. Detta optimerar prestandan genom att undvika repetitiva sökningar i ett tillstånd som inte har ändrats.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Beskrivning:** Går igenom `loaded_amx_` (från senast till äldst, vilket oftast placerar gamemode eller den mest relevanta filterscripten först) för att hitta `public`-funktionen med det angivna namnet.
   - **Mekanism:** Använder `amx::Find_Public` för varje `AMX*`-instans.
   - **Inverkan:** Är grunden för `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: `Plugin_Public`-callback-routern

Denna `singleton` är den komponent som mappar Pawn `public`-namn till dina C++ `Plugin_Public`-funktioner.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Nyckel:** FNV1a-hashen av `public`-funktionens namn (t.ex. `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Värde:** En `std::vector` av `std::function<cell(AMX*)>`, där varje `std::function` är en C++-hanterare registrerad för den `public`-funktionen.
   - **Mekanism:** `std::vector` tillåter att flera `Plugin_Public`:er registreras för samma callback (t.ex. flera plugins som vill avlyssna `OnPlayerCommandText`). Hanterarna exekveras i omvänd registreringsordning.
- **`Public_Registrar`**:
   - **Mekanism:** Detta är en mallklass vars makro `PLUGIN_PUBLIC_REGISTRATION` skapar en statisk global instans. I den statiska konstruktorn (`static bool registered = [...]`) registrerar den sin `Plugin_Public`-hanterare i `Public_Dispatcher`. Detta är ett mönster för "statisk registrering vid kompileringstid/initialisering".
   - **Exempel (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Registrar<decltype(&name), &name, hash_##name> registrar_##name;
      ```

- **`Public_Traits` och `Wrapper()`**:
   - **Mekanism:** `Public_Traits` är en trait-mall som, med hjälp av metaprogrammering, genererar en funktion `static cell Wrapper(AMX* amx)`.
   - **Syfte:** Denna `Wrapper` är den `Amx_Handler_Func` som `Public_Dispatcher` faktiskt lagrar och anropar. Den ansvarar för att:
      1. Anropa `Public_Param_Reader::Get_Public_Params(amx, args...)` för att extrahera parametrarna från AMX-stacken.
      2. Anropa din faktiska C++ `Plugin_Public`-funktion (`func_ptr`) med parametrarna som redan konverterats till korrekta C++-typer.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Beskrivning:** En uppsättning rekursiva mallfunktioner som läser värden från AMX-stacken och konverterar dem till de C++-typer som specificerats i `Plugin_Public`-deklarationen.
   - **Mekanism:** Använder `Get_Stack_Cell()` för att komma åt `cell`:erna på stacken. Använder `if constexpr` (C++17+) eller `std::is_same<T>::value` (C++14) för att tillämpa korrekt konvertering (`amx::AMX_CTOF` för float, `Samp_SDK::Get_String` för sträng, direkt cast för int).

### 4.7. `native.hpp`: Hantering och anrop av plugin-natives

Denna header är dedikerad till skapande och hantering av C++-natives som ditt plugin exponerar för Pawn.

- **`Native_List_Holder`**:
   - **Beskrivning:** En global `singleton` som lagrar alla `Plugin_Native`:er som deklarerats i ditt plugin (från alla `.cpp`-filer som använder `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Innehåller `Native`-objekt (som lagrar native-namnet och pekaren till C++-funktionen `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: En hashmapsoptimerad mapp för snabba sökningar efter interna `Plugin_Native`:er (används av `Plugin_Call`).
- **`Native_Registrar`**:
   - **Mekanism:** Precis som `Public_Registrar` är detta en mallklass vars makro `Plugin_Native` skapar en statisk global instans. I dess konstruktor lägger den till native-funktionen till `Native_List_Holder`.
   - **Inverkan:** Tillåter dig att deklarera `Plugin_Native`:er i flera `.cpp`-filer utan att oroa dig för manuell registrering. Alla kommer att samlas in automatiskt.
- **`Native_Registry`**:
   - **Beskrivning:** En hjälpklass som, i `OnAmxLoad`, hämtar hela listan över `Native`:er från `Native_List_Holder` och formaterar dem i en `AMX_NATIVE_INFO`-array.
   - **Mekanism:** Anropar `amx::Register(amx, amx_natives_info_.data(), -1)` för att registrera alla dina natives i den just laddade AMX-instansen.
- **`Plugin_Call_Impl(...)`**:
   - **Beskrivning:** Den underliggande implementeringen av makrot `Plugin_Call`.
   - **Mekanism:** Använder `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` för att direkt få C++-funktionspekaren.
   - **Miljö:** Exekverar native-funktionen i en `Amx_Sandbox`-miljö (isolerad) för att hantera temporär stack och heap, på ett liknande sätt som `Pawn_Native` fungerar.

### 4.8. `callbacks.hpp` & `amx_memory.hpp`: C++ -> Pawn-anrop och RAII

Dessa headers utgör ryggraden för att anropa Pawn-funktioner från C++ (`Pawn_*`-makron) och säkerställer minnessäkerhet.

- **`Amx_Sandbox`**:
   - **Beskrivning:** En `thread_local`-struktur som simulerar en minimalistisk och isolerad `AMX`-miljö för `Pawn_Native` och `Plugin_Call`-anrop.
   - **Mekanism:** Har sin egen `AMX`-struktur, `AMX_HEADER` och en `std::vector<unsigned char> heap` för att simulera ett skripts minne. Detta gör att `amx::Push`, `amx::Allot`, etc. kan anropas utan att störa tillståndet för verkliga körande Pawn-skript.
   - **`thread_local`:** Säkerställer att varje tråd har sin egen `Amx_Sandbox`, vilket förhindrar race conditions om SDK:n används i en flertrådad kontext (t.ex. en framtida trådpool för icke-Pawn-operationer).
   - **Exempel (`Amx_Sandbox`):**
      ```cpp
      // Simplified snippet from callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Simulated memory for stack/heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Initializes the AMX and the header
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
   - **Beskrivning:** En uppsättning överbelastade mallfunktioner som hanterar `marshalling` av *varje* C++-parameter till det `cell`-format som förväntas av AMX, och vice versa för utparametrar.
   - **Inmatningsbearbetning:**
       - För `int`, `float`, `bool`: Konverteras direkt till `cell`.
       - För `const char*`, `std::string`: Allokerar minne på `Amx_Sandbox`s heap (eller verklig AMX för `Pawn_Public`), kopierar strängen och lägger till AMX-adressen på stacken.
   - **Utmatningsbearbetning (`is_output_arg`):**
       - **Mekanism:** När ett argument är en icke-const lvalue-referens (detekteras av trait `is_output_arg`), skjuter `Parameter_Processor` inte in värdet, utan en *AMX-adress* till en temporärt allokerad `cell` på heapen.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Efter anropet till Pawn-native exekveras en lista med lambdas (`post_call_updaters`). Varje lambda ansvarar för att läsa det slutliga värdet från den allokerade `cell`:en i AMX och tilldela det tillbaka till den ursprungliga C++-variabeln (t.ex. `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mekanism:** En `std::integral_constant` (typtrait) som vid kompileringstid utvärderar om en C++-parametertyp är en modifierbar referens (t.ex. `int&`, `float&`, `std::string&`). Detta gör att `Parameter_Processor` kan skilja på in- och utparametrar.
   - **Exempel (`is_output_arg`):**
      ```cpp
      // Simplified snippet from callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Beskrivning:** En RAII-klass (`Resource Acquisition Is Initialization`) som kapslar in allokering och deallokering av minne i AMX.
   - **Mekanism:** I konstruktorn anropar den `amx::Allot` för att få en `amx_addr` och en `phys_addr`. I destruktorn anropar den `amx::Release` för att frigöra detta minne.
   - **Inverkan:** **Avgörande för att förhindra minnesläckor på AMX-heapen.** Säkerställer att tillfälligt minne som används för strängar eller utparametrar alltid frigörs, även om undantag uppstår eller tidiga returer görs.

### 4.9. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Abstraherad AMX-åtkomst

Dessa headrar tillhandahåller de grundläggande definitionerna och högnivåverktygen för att interagera med Pawn.

- **`amx_defs.h`**:
   - **Innehåll:** Innehåller råa definitioner av AMX-strukturer (`AMX`, `AMX_HEADER`), typer (`cell`, `ucell`) och fel-enums (`AmxError`). Definierar också `AMX_NATIVE` och `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Använder packningsattribut (`#pragma pack(push, 1)` / `__attribute__((packed))`) för att säkerställa att AMX-strukturerna har korrekt minneslayout, vilket är avgörande för interoperabilitet.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Beskrivning:** Den huvudsakliga mallfunktionen för att anropa AMX API-funktionerna som exponeras av servern.
   - **Mekanism:** Hämtar funktionspekaren via `Core::Instance().Get_AMX_Export(Index)` och anropar den. Centraliserar felhantering om funktionspekaren inte är tillgänglig.
   - **Inverkan:** Konverterar lågnivåanrop (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) till idiomatiska och typsäkra C++-anrop (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Beskrivning:** Viktiga funktioner för att konvertera `cell`-värden till `float` och vice versa, genom att utföra en bitvis ominterpretation av minnet.
   - **`static_assert`:** Inkluderar `static_assert` för att säkerställa att `sizeof(cell) == sizeof(float)` vid kompileringstid, vilket förhindrar fel på plattformar med olika typstorlekar.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Beskrivning:** Hjälpfunktion för att konvertera en AMX-strängadress till `std::string`.
   - **Mekanism:** Först hämtas den fysiska adressen (`cell* phys_addr`) för strängen i AMX med `amx::Get_Addr`. Därefter används `amx::STR_Len` för att bestämma längden och `amx::Get_String` för att kopiera byten till en `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Beskrivning:** Den grundläggande strängformateringsfunktionen (`printf`-liknande) för SDK:n.
   - **Mekanism:** Använder `vsnprintf` i två pass: först för att bestämma strängens nödvändiga storlek, och sedan för att formatera strängen i den dynamiskt allokerade `std::string`. Detta förhindrar buffertöverskridanden.

## 5. Kompilering och distribution

### Arkitektur- och plattformskrav

- Ditt plugin **MÅSTE** kompileras för **x86 (32-bit)**-arkitekturen. SDK:ns hooking-mekanism är specifik för denna arkitektur.
- Stödda plattformar: Windows (.dll) och Linux (.so).

### Exempel på kompileringskommandon

#### **MSVC (Visual Studio)**

1. Skapa ett nytt projekt för "Dynamic-Link Library (DLL)".
2. I projektinställningarna, ställ in "Lösningsplattform" till **x86**.
3. Säkerställ att C++ Language Standard är minst C++14.

#### **GCC / Clang (Linux)**

```bash
# For a plugin named 'my_plugin.so' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Kompilerar för 32-bit.
- `-shared`: Skapar ett delat bibliotek (`.so`).
- `-std=c++17`: Sätter C++-standarden till C++17 (kan vara `c++14` eller `c++20`).
- `-O2`: Optimeringsnivå 2.
- `-fPIC`: Genererar positionsberoende kod, nödvändigt för delade bibliotek.
- `-Wall -Wextra`: Aktiverar ytterligare varningar för att hjälpa till att fånga fel.
- `-Wl,--no-undefined`: Förhindrar att biblioteket skapas om det finns odefinierade symboler.

#### **GCC / Clang (MinGW på Windows)**

```bash
# For a plugin named 'my_plugin.dll' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Länkar C++-standardbiblioteket statiskt. Väsentligt för att förhindra att ditt plugin är beroende av specifika kompilator-runtime-DLL:er som kanske inte finns på användarens system.
- `-static-libgcc`: Länkar GCC-biblioteket statiskt.

### Överväganden för distribution

- **Filnamn:** Ditt plugin ska ha filändelsen `.dll` (Windows) eller `.so` (Linux). Ex: `my_plugin.dll`.
- **Plats:** Placera den kompilerade filen i `plugins/`-mappen på din SA-MP-server.
- **server.cfg:** Lägg till namnet på ditt plugin (om det är Windows, utan filändelse) till `plugins`-raden i `server.cfg`.
   ```
   plugins my_plugin (if Linux, my_plugin.so)
   ```

## Licens

Copyright © **SA-MP Programming Community**

Denna programvara är licensierad under villkoren i MIT-licensen ("Licensen"); du får använda denna programvara i enlighet med Licensens villkor. En kopia av Licensen kan erhållas på: [MIT License](https://opensource.org/licenses/MIT)

### Användarvillkor

#### 1. Beviljade rättigheter

Denna licens ger kostnadsfritt följande rättigheter till alla som erhåller en kopia av denna programvara och tillhörande dokumentationsfiler:
* Att använda, kopiera, modifiera, slå samman, publicera, distribuera, underlicensiera och/eller sälja kopior av programvaran utan begränsningar
* Att tillåta personer som programvaran tillhandahålls till att göra detsamma, under förutsättning att de följer nedanstående villkor

#### 2. Obligatoriska villkor

Alla kopior eller väsentliga delar av programvaran måste innehålla:
* Ovanstående upphovsrättsmeddelande
* Detta tillståndsmeddelande
* Nedanstående ansvarsfriskrivning

#### 3. Upphovsrätt

Programvaran och all tillhörande dokumentation skyddas av upphovsrättslagar. **SA-MP Programming Community** behåller den ursprungliga upphovsrätten till programvaran.

#### 4. Garantifriskrivning och ansvarsbegränsning

PROGRAMVARAN TILLHANDAHÅLLS "I BEFINTLIGT SKICK", UTAN NÅGON GARANTI AV NÅGOT SLAG, UTTRYCKLIG ELLER UNDERFÖRSTÅDD, INKLUSIVE MEN INTE BEGRÄNSAT TILL GARANTIER FÖR SÄLJBARHET, LÄMPLIGHET FÖR ETT SÄRSKILT SYFTE OCH ICKE-INTRÅNG.

UNDER INGA OMSTÄNDIGHETER SKA FÖRFATTARNA ELLER UPPHOVSRÄTTSINNEHAVARNA VARA ANSVARIGA FÖR NÅGRA ANSPRÅK, SKADOR ELLER ANNAT ANSVAR, VARE SIG I EN AVTALSHANDLING, SKADESTÅNDSANSPRÅK ELLER PÅ ANNAT SÄTT, SOM UPPSTÅR FRÅN, UT ELLER I SAMBAND MED PROGRAMVARAN ELLER ANVÄNDNINGEN ELLER ANNAT HANDHAVANDE AV PROGRAMVARAN.

---

För detaljerad information om MIT-licensen, besök: https://opensource.org/licenses/MIT