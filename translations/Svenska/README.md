# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Ett modernt, header-only och högnivå C++ SDK för utveckling av plugins och moduler för SA-MP.**

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

- [SA-MP SDK](#sa-mp-sdk)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [1. Introduktion och Designfilosofi](#1-introduktion-och-designfilosofi)
    - [Problemet med SA-MPs Standard C API](#problemet-med-sa-mps-standard-c-api)
    - [SA-MP SDKs Lösning: Abstraktion med Säkerhet och Prestanda](#sa-mp-sdks-lösning-abstraktion-med-säkerhet-och-prestanda)
    - [Header-Only Modell: Fördelar och Implikationer](#header-only-modell-fördelar-och-implikationer)
  - [2. Konfiguration och Miljö](#2-konfiguration-och-miljö)
    - [Kompileringskrav](#kompileringskrav)
    - [Rekommenderad Filstruktur](#rekommenderad-filstruktur)
    - [Viktiga Konfigurationsmakron](#viktiga-konfigurationsmakron)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP Definitioner och Konstanter (`samp_defs.hpp`)](#sa-mp-definitioner-och-konstanter-samp_defshpp)
  - [3. Omfattande API Användarguide](#3-omfattande-api-användarguide)
    - [3.1. Pluginets Livscykel](#31-pluginets-livscykel)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Intercepting Pawn Events](#32-plugin_public-intercepting-pawn-events)
      - [Syntax och Deklaration](#syntax-och-deklaration)
      - [Automatisk Parameter-Marshalling](#automatisk-parameter-marshalling)
      - [Flödeskontroll: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#flödeskontroll-plugin_public_continue-vs-plugin_public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.3. `Plugin_Native`: Skapa Native-funktioner i C++](#33-plugin_native-skapa-native-funktioner-i-c)
      - [Syntax och Fast Signatur](#syntax-och-fast-signatur)
      - [Automatisk Registrering av Natives](#automatisk-registrering-av-natives)
      - [Parameterutvinning: `Register_Parameters` vs. `Native_Params`](#parameterutvinning-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Full API: `Get`, `Get_REF`, `Set_REF`)](#native_params-full-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Returvärden](#returvärden)
    - [3.4. `Plugin_Native_Hook`: Intercepting Existing SA-MP Natives](#34-plugin_native_hook-intercepting-existing-sa-mp-natives)
      - [Syntax och Fast Signatur](#syntax-och-fast-signatur-1)
      - [Registrering och Aktivering av Hook](#registrering-och-aktivering-av-hook)
      - [Anropa Original Native (Hook-kedja): `Call_Original_Native`](#anropa-original-native-hook-kedja-call_original_native)
      - [Fullständigt Exempel på `Plugin_Native_Hook`](#fullständigt-exempel-på-plugin_native_hook)
    - [3.5. `Pawn_*` Makron: Anropa Pawn-funktioner från C++](#35-pawn_-makron-anropa-pawn-funktioner-från-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Syntax och Konventioner](#syntax-och-konventioner)
      - [Marshalling av Input-parametrar](#marshalling-av-input-parametrar)
      - [Marshalling av Output-parametrar (Referenser: `int&`, `float&`, `std::string&`)](#marshalling-av-output-parametrar-referenser-int-float-stdstring)
      - [Objektet `Callback_Result`: Fullständig Analys](#objektet-callback_result-fullständig-analys)
    - [3.6. `Plugin_Module`: Hantering av Dynamiska Moduler](#36-plugin_module-hantering-av-dynamiska-moduler)
      - [Syntax och Syfte](#syntax-och-syfte)
      - [En Moduls Livscykel](#en-moduls-livscykel)
      - [Fördelar med Modularisering](#fördelar-med-modularisering)
    - [3.7. `Plugin_Call`: Anropa Pluginets Interna Natives](#37-plugin_call-anropa-pluginets-interna-natives)
      - [Syntax och Prestandafördelar](#syntax-och-prestandafördelar)
    - [3.8. SDK Verktygsfunktioner](#38-sdk-verktygsfunktioner)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Rekommenderas)](#stdstring-plugin_formatconst-char-format--rekommenderas)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Implementeringsdetalj)](#stdstring-samp_sdkformatconst-char-format--implementeringsdetalj)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. SDKs Interna Anatomi och Arkitektur](#4-sdks-interna-anatomi-och-arkitektur)
    - [4.1. `core.hpp`: Den Minimalistiska Grunden](#41-corehpp-den-minimalistiska-grunden)
    - [4.2. `platform.hpp` och `version.hpp`: Kompatibilitet och Metadata](#42-platformhpp-och-versionhpp-kompatibilitet-och-metadata)
    - [4.3. `function_hook.hpp`: x86 Intercept-motorn](#43-function_hookhpp-x86-intercept-motorn)
    - [4.4. `interceptor_manager.hpp`: AMX Hook-kontrollern](#44-interceptor_managerhpp-amx-hook-kontrollern)
    - [4.5. `amx_manager.hpp`: Hantera `AMX*` Instanser](#45-amx_managerhpp-hantera-amx-instanser)
    - [4.6. `public_dispatcher.hpp`: `Plugin_Public` Callback-routern](#46-public_dispatcherhpp-plugin_public-callback-routern)
    - [4.7. `native.hpp`: Hantera och Anropa Plugin Natives](#47-nativehpp-hantera-och-anropa-plugin-natives)
    - [4.8. `native_hook_manager.hpp`: Natives Hook-motorn](#48-native_hook_managerhpp-natives-hook-motorn)
    - [4.9. `callbacks.hpp` \& `amx_memory.hpp`: C++ -\> Pawn Anrop och RAII](#49-callbackshpp--amx_memoryhpp-c---pawn-anrop-och-raii)
    - [4.10. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Abstraherad AMX-åtkomst](#410-amx_apihpp--amx_helpershpp--amx_defsh-abstraherad-amx-åtkomst)
  - [5. Kompilering och Deploy](#5-kompilering-och-deploy)
    - [Krav på Arkitektur och Plattform](#krav-på-arkitektur-och-plattform)
    - [Exempel på Kompileringskommandon](#exempel-på-kompileringskommandon)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW på Windows)**](#gcc--clang-mingw-på-windows)
    - [Överväganden för Distribution](#överväganden-för-distribution)
  - [Licens](#licens)
    - [Användarvillkor](#användarvillkor)
      - [1. Beviljade rättigheter](#1-beviljade-rättigheter)
      - [2. Obligatoriska villkor](#2-obligatoriska-villkor)
      - [3. Upphovsrätt](#3-upphovsrätt)
      - [4. Garantifriskrivning och ansvarsbegränsning](#4-garantifriskrivning-och-ansvarsbegränsning)

## 1. Introduktion och Designfilosofi

### Problemet med SA-MPs Standard C API

SA-MP plugin API är ett C-programmeringsgränssnitt. Även om det är funktionellt och grundläggande, presenterar det utmaningarna som är inneboende i lågnivåprogrammering:
- **Manuell Minneshantering:** Funktioner som `amx_Allot` och `amx_Release` kräver att utvecklaren explicit allokerar och frigör minne på AMX-heapen. Detta är en vanlig källa till minnesläckor och körtidsfel.
- **Svag Typning och Manuella Konverteringar:** Parametrar skickas som en array av `cell`s, vilket tvingar fram explicita (och ofta osäkra) konverteringar mellan `cell`, `int`, `float` och `char*`.
- **Verbositet och Boilerplate:** Att extrahera flera parametrar från en `cell* params`-array, hantera strängstorlekar och hantera AMX-stacken för C++ till Pawn-återanrop kräver repetitiv kod.
- **Gränssnittets Bräcklighet:** Bristen på kompileringstidsverifiering (type safety) innebär att fel i parameteröverföring eller typer kan gå obemärkta förbi fram till exekvering, vilket orsakar krascher eller odefinierade beteenden.

### SA-MP SDKs Lösning: Abstraktion med Säkerhet och Prestanda

SA-MP SDK tacklar dessa problem genom att tillhandahålla ett kraftfullt abstraktionslager i C++:
- **RAII (Resource Acquisition Is Initialization):** Automatisk minneshantering i AMX. `Amx_Scoped_Memory` säkerställer att allokerat minne frigörs.
- **Typsäkerhet:** Automatisk och säker konvertering av parametrar mellan C++ och Pawn. Du hanterar `int`, `float`, `std::string` direkt.
- **Koncis och Idiomatisk Syntax:** Makron och templates tillhandahåller ett rent API som mer liknar modern C++ än det traditionella C-API:et.
- **Robust Intercepting:** En avancerad hooking-motor möjliggör transparent intercepting av Pawn callbacks (`Plugin_Public`), skapande av nya natives (`Plugin_Native`), och **hooking och kedjning av befintliga SA-MP native-funktioner (`Plugin_Native_Hook`)**.
- **Hög Prestanda:** Omfattande användning av kompileringstids-hashing (FNV1a), funktionscaching och `thread_local`-optimeringar för att minimera overheaden av abstraktionerna.

### Header-Only Modell: Fördelar och Implikationer

SDK:n består uteslutande av header-filer (`.hpp`, `.h`).
- **Fördelar:**
   - **Förenklad Integration:** Inga bibliotek att bygga, länka eller distribuera. Inkludera bara headrarna.
   - **Kompileringsoptimeringar:** Kompilatorn har fullständig insyn i SDK:s kod och ditt plugins kod, vilket möjliggör aggressiv inlining och länkningstidsoptimeringar, vilket kan resultera i snabbare binärfiler.
- **Implikationer:**
   - **Kompileringstid:** För mycket stora projekt kan kompileringen ta längre tid på grund av upprepad inkludering av SDK-koden. Detta minskas genom inklusions-guards och C++:s "inkludera bara det som behövs"-natur.
   - **Implementeringsmakron:** Behovet av makrot `SAMP_SDK_IMPLEMENTATION` är en konsekvens av header-only-modellen för att undvika omdefinitioner av symboler.

## 2. Konfiguration och Miljö

### Kompileringskrav

- **C++ Kompilator:** Kompatibel med C++14 eller senare (SDK:n använder funktioner från C++14, C++17 och C++20 för specifika optimeringar, men C++14 är minimum).
   - GCC (version 7+)
   - Clang (version 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Arkitektur:** **x86 (32-bit)**. SA-MP fungerar uteslutande på denna arkitektur. SDK:n innehåller kontroller i `platform.hpp` som kommer att utfärda kompileringsfel om fel arkitektur upptäcks.
- **Operativsystem:** Windows eller Linux.

### Rekommenderad Filstruktur

För tydlighet och organisation är det vanligt att organisera SDK:n i en undermapp `samp-sdk`.

```
my_plugin/
├── samp-sdk/
│   ├── // Andra SDK-filer
│   └── samp_sdk.hpp             // Den huvudsakliga headern som ska inkluderas
│
├── src/
│   ├── main.cpp                  // Där SAMP_SDK_IMPLEMENTATION definieras
│   └── my_custom_logic.cpp       // Valfritt, för att organisera kod
│
└── CMakeLists.txt (eller .vcxproj, Makefile)
```

### Viktiga Konfigurationsmakron

Definiera alltid dessa makron *innan* du inkluderar `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Syfte:** Signalera till kompilatorn att den här `.cpp`-filen ska generera implementeringarna av pluginets exportfunktioner (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **SDK:n hanterar exporteringen av dessa funktioner automatiskt, vilket eliminerar behovet av `.def`-filer (på Windows) eller `__attribute__((visibility("default")))`-deklarationer (på Linux) för dessa funktioner.**
- **Teknisk påverkan:** Utan detta makro kommer länkaren inte att hitta de nödvändiga exporteringarna, och SA-MP-servern kommer inte att kunna ladda ditt plugin.
- **Grundläggande regel:** **Definiera detta makro i ENDAST EN `.cpp`-fil i hela ditt projekt.** Att definiera det i mer än en fil kommer att orsaka ett länkfel av typen "dubbel symbol".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // Makrot gör att SDK:n exporterar de nödvändiga funktionerna automatiskt.
#include "samp-sdk/samp_sdk.hpp"

// ... din plugin-kod ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Syfte:** Aktiverar Pawn-skriptets livscykel-callbacks (`OnAmxLoad`, `OnAmxUnload`) och funktionaliteten att skapa nya C++-natives (`Plugin_Native`).
- **Aktiverade Funktioner:**
   - Callbacks `OnAmxLoad(AMX* amx)` och `OnAmxUnload(AMX* amx)`.
   - Deklaration och registrering av nya C++ natives med `Plugin_Native`.
   - Makrot `Plugin_Call` för att anropa natives skapade med `Plugin_Native` inom ditt eget plugin.
- **Teknisk påverkan:** När detta makro är definierat samlar SDK:n automatiskt in alla dina `Plugin_Native`s. I funktionen `Supports()` läggs flaggan `SUPPORTS_AMX_NATIVES` automatiskt till om det finns några `Plugin_Native`s i ditt projekt.
- **Flexibilitet:** **Du kan definiera detta makro i flera `.cpp`-filer.** SDK:ns statiska registreringssystem kommer att konsolidera alla natives från olika kompileringsenheter till en enda global lista.

```cpp
// my_natives.cpp (kan vara en separat fil från main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Endast för att aktivera Plugin_Native och OnAmxLoad/OnAmxUnload callbacks
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Syfte:** Aktiverar `OnProcessTick()` callback, som anropas regelbundet av servern.
- **Teknisk påverkan:** Lägger automatiskt till flaggan `SUPPORTS_PROCESS_TICK` i funktionen `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logik som körs vid varje "tick" på servern (t.ex. 20ms)
    // Var försiktig med tunga operationer här!
}
```

### SA-MP Definitioner och Konstanter (`samp_defs.hpp`)

Denna fil tillhandahåller alla kända SA-MP konstanter och gränser, som `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. Den inkluderas automatiskt av `samp_sdk.hpp` och bör användas för att säkerställa kompatibilitet och läsbarhet i koden.

## 3. Omfattande API Användarguide

### 3.1. Pluginets Livscykel

Följande funktioner är ingångs- och utgångspunkterna för ditt plugin, automatiskt exporterade av SDK:n.

#### `bool OnLoad()`

- **Beskrivning:** Första funktionen som anropas av SA-MP-servern efter att ditt plugin har laddats in i minnet.
- **Användning:** Idealisk för att initialisera system, ladda konfigurationer, öppna databasanslutningar eller ladda moduler (`Plugin_Module`).
- **Returvärde:**
   - `true`: Pluginet har initialiserats framgångsrikt och laddningen fortsätter.
   - `false`: Pluginet misslyckades med att initialisera. Laddningen avbryts och pluginet laddas ur.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initialiserar MyPlugin v1.0...");

    // Exempel: Ladda en modul (mer detaljer i avsnitt 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Databasmodulen laddad.")) {
        Samp_SDK::Log("FEL: Kunde inte ladda databasmodulen!");

        return false; // Avbryter laddningen av huvudpluginet
    }

    return true;
}
```

#### `void OnUnload()`

- **Beskrivning:** Sista funktionen som anropas av SA-MP-servern innan ditt plugin avlastas från minnet.
- **Användning:** Idealisk för att rensa upp resurser, stänga anslutningar, spara tillstånd och säkerställa att inga resurser läcker. SDK:n hanterar avlastning av moduler (`Plugin_Module`) automatiskt.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin avlastat. Frigör resurser...");
    // Ingen manuell åtgärd behövs för moduler laddade via Plugin_Module;
    // SDK:n hanterar detta.
}
```

#### `unsigned int GetSupportFlags()`

- **Beskrivning:** Informerar SA-MP-servern vilka funktioner ditt plugin stöder och vill använda.
- **Användning:** **Returnera alltid `SUPPORTS_VERSION` (eller `SAMP_PLUGIN_VERSION`).** Flaggorna `SUPPORTS_AMX_NATIVES` och `SUPPORTS_PROCESS_TICK` läggs till automatiskt av SDK:n om det finns `Plugin_Native`s, och/eller om makrot `SAMP_SDK_WANT_PROCESS_TICK` är definierat, respektive. Detta förenklar underhåll och förhindrar fel.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // SDK:n lägger automatiskt till de nödvändiga flaggorna.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Kräver:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beskrivning:** Anropas varje gång ett nytt Pawn-skript (ett Gamemode eller Filterscript) laddas och initialiseras på servern.
- **Användning:** Om du behöver specifik logik för varje AMX-skript, eller initialisera specifika data per skript.

```cpp
// main.cpp (med SAMP_SDK_WANT_AMX_EVENTS definierat)
void OnAmxLoad(AMX* amx) {
    // amx representerar den nya laddade skriptinstansen.
    Samp_SDK::Log("AMX-skript laddat: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Kräver:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beskrivning:** Anropas när ett Pawn-skript avlastas från servern.
- **Användning:** För att rensa upp eventuella specifika resurser som du allokerade eller associerade med den specifika `AMX*`.

```cpp
// main.cpp (med SAMP_SDK_WANT_AMX_EVENTS definierat)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX-skript avlastat: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Kräver:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Beskrivning:** Anropas upprepade gånger vid varje "tick" på servern (vanligtvis 20 gånger per sekund, eller var 50:e ms).
- **Användning:** För kontinuerlig bakgrundslogik, timers, tillståndsuppdateringar som inte är beroende av spelarhändelser, eller datasynkronisering.
- **Varning:** Undvik blockerande eller beräkningsmässigt tunga operationer här, eftersom de kan orsaka lagg på servern.

```cpp
// main.cpp (med SAMP_SDK_WANT_PROCESS_TICK definierat)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Var 10:e sekund (20 ticks/sek * 10 sek = 200 ticks)
        Samp_SDK::Log("Server aktiv i %d sekunder.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Intercepting Pawn Events

Makrot `Plugin_Public` är den primära bryggan för att ta emot Pawn callbacks i din C++-kod.

#### Syntax och Deklaration

- `Plugin_Public(PublicName, Type1 Param1, Type2 Param2, ...)`
- C++-funktionens namn som du deklarerar **måste vara detsamma** som Pawn-callbackens (t.ex. `OnPlayerConnect`).
- C++-parametertyperna (`int`, `float`, `std::string`) konverteras automatiskt av SDK:n.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Spelare %d sade: %s", playerid, text.c_str());

    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Automatisk Parameter-Marshalling

SDK:n hanterar automatiskt läsning från AMX `cell stack` och konvertering till de angivna C++-typerna:
- `int`: Konverteras direkt från `cell`.
- `float`: Konverteras från `cell` med `amx::AMX_CTOF`.
- `std::string`: SDK:n läser strängens adress i AMX, allokerar en `std::string` i C++ och kopierar innehållet.

#### Flödeskontroll: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

Värdet som returneras av din `Plugin_Public`-funktion är avgörande och bestämmer flödet av callback-exekveringen:
- `return PLUGIN_PUBLIC_CONTINUE;` (värde `1`): Indikerar att callback-exekveringen ska **fortsätta**. Om det finns andra plugins som också interceptar denna callback, kommer de att anropas (i omvänd laddningsordning). Därefter kommer den ursprungliga `public`-funktionen i Pawn-skriptet att anropas.
- `return PLUGIN_PUBLIC_STOP;` (värde `0`): Indikerar att callback-exekveringen ska **avbrytas**. Inga andra plugins (med lägre prioritet) eller den ursprungliga `public`-funktionen i Pawn-skriptet kommer att anropas för denna händelse. Detta är idealiskt för att implementera ett system som "skriver över" eller "blockerar" ett standardbeteende i SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Fryser spelaren
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Spelare %d frusen.", playerid));

        return PLUGIN_PUBLIC_STOP; // Förhindrar att kommandot bearbetas av andra skript.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Tillåter att andra kommandon bearbetas.
}
```

#### Ghost Callbacks

En avancerad funktion i `Plugin_Public` är stödet för "Ghost Callbacks". Detta innebär att du kan intercepta en Pawn callback även om den **inte finns** i gamemodets eller filterscriptets `.amx`-skript. SDK:n "lurar" servern att anropa din C++-hook ändå. Detta är användbart för interna callbacks eller för att skapa ny funktionalitet utan att vara beroende av att en `public` finns i Pawn-skriptet.

```cpp
// Du kan definiera en callback som Pawn-skriptet inte har, men ditt plugin kommer att lyssna på den.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Anpassad intern händelse mottagen: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// För att "trigga" denna händelse från en annan del av din C++-kod:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// Anropet går till din Plugin_Public ovan, även om det inte finns någon OnMyCustomInternalEvent i Pawn.
```

### 3.3. `Plugin_Native`: Skapa Native-funktioner i C++

`Plugin_Native` låter dig utöka Pawn-funktionaliteten med högpresterande C++-kod.

#### Syntax och Fast Signatur

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- C++-funktionen måste ha exakt denna signatur: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` är namnet som Pawn-skripten kommer att använda.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementering ...
    return 0;
}
```

#### Automatisk Registrering av Natives

> [!NOTE]
> Du **behöver inte** anropa `amx_Register` manuellt. SDK:n upptäcker alla dina `Plugin_Native`s (i vilken `.cpp`-fil som helst som har inkluderat `samp_sdk.hpp` och definierat `SAMP_SDK_WANT_AMX_EVENTS`) och registrerar dem automatiskt i varje laddat AMX-skript (`OnAmxLoad`).

#### Parameterutvinning: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Beskrivning:** Enklare hjälpfunktion för att extrahera flera parametrar sekventiellt.
- **Användning:** `Register_Parameters(variable1, variable2, ...)`
- **Begränsningar:** För input-parametrar. Hanterar inte valfria parametrar eller indexerad åtkomst.
- **Typer som stöds:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extraherar de 3 parametrarna
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (Full API: `Get`, `Get_REF`, `Set_REF`)

- **Beskrivning:** En wrapper-klass som tillhandahåller ett objektorienterat gränssnitt för att komma åt parametrarna för en native. Kraftfullare för komplexa scenarier.
- **Konstruktion:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Beskrivning:** Returnerar antalet parametrar som skickats till nativen.
- **Användning:** Viktigt för att hantera valfria parametrar.

###### `p.Get<T>(size_t index)`

- **Beskrivning:** Extraherar en input-parameter via index och konverterar den till typen `T`.
- **Typer som stöds:** `int`, `float`, `std::string`.

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
- **Returvärde:** `true` om AMX-adressen är giltig, `false` annars.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Hämtar värden från referenserna (Pawn skickade adresser)
    p.Get_REF(1, health); // Läser värdet av Float:health
    p.Get_REF(2, money);   // Läser värdet av money
    
    Samp_SDK::Log("Spelare %d, Hälsa: %.1f, Pengar: %d", playerid, health, money);
    
    // Nu, modifiera dem
    health = 50.0f;
    money += 100;
    
    // Och skriv tillbaka dem till Pawn-minnet
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Beskrivning:** Returnerar en `std::optional<T>` för att läsa en referensparameter. Säkrare för C++17 och senare.

###### `p.Set_REF<T>(size_t index, T value)`

- **Beskrivning:** Skriver ett värde `T` till en Pawn **referensparameter** (adressen som Pawn skickade).
- **Användning:** För att modifiera värden som skickats via referens, så att Pawn ser ändringen.
- **Returvärde:** `true` om skrivningen lyckades, `false` annars.

#### Returvärden

- Din `Plugin_Native`-funktion måste returnera en `cell`.
- För att returnera en `int` eller `bool`, använd en cast till `cell`.
- För att returnera en `float`, använd `amx::AMX_FTOC(my_float)`.

```cpp
// Returnerar en bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Returnerar en float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Returnerar 100.0f
}
```

### 3.4. `Plugin_Native_Hook`: Intercepting Existing SA-MP Natives

Makrot `Plugin_Native_Hook` låter dig intercepta och modifiera beteendet hos vilken befintlig SA-MP native-funktion som helst, eller från andra plugins. Detta är en kraftfull mekanism för att utöka eller ändra serverns standardlogik.

#### Syntax och Fast Signatur

- `Plugin_Native_Hook(NativeName, AMX* amx, cell* params)`
- C++-funktionen måste ha exakt denna signatur: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` måste vara det exakta namnet på nativen som du vill hooka (t.ex. `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepts the SendClientMessage native
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Viktigt att anropa originalet
}
```

#### Registrering och Aktivering av Hook

> [!NOTE]
> Du **behöver inte** anropa `amx_Register` manuellt eller definiera `SAMP_SDK_WANT_AMX_EVENTS` specifikt för `Plugin_Native_Hook`. SDK:n upptäcker och registrerar automatiskt dina hooks. Vid den första exekveringen av ett AMX-skript ersätter SDK:n native-pekaren i tabellen med en "trampoline" som omdirigerar till din `Plugin_Native_Hook`-funktion. Denna process säkerställer säker kedjning av hooks från flera plugins.

#### Anropa Original Native (Hook-kedja): `Call_Original_Native`

Inom din `Plugin_Native_Hook`-funktion **MÅSTE** du använda makrot `Call_Original_Native(NativeName)` för att anropa den ursprungliga funktionen (eller nästa hook i kedjan). Detta är avgörande för att:
- **Bevara Funktionaliteten:** Om du inte anropar originalet kommer den hookade nativen helt enkelt att sluta fungera för andra plugins eller för servern.
- **Hook-kedjning:** Tillåter att flera plugins hookar samma native och att alla hooks exekveras i en sekvens.
- **Returvärdeshantering:** Du kan inspektera och till och med modifiera returvärdet från `Call_Original_Native` innan du returnerar det från din hook-funktion.

```cpp
// Exempel: Blockera SendClientMessage om det innehåller ett specifikt ord
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extraherar parametrarna för analys
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // Vi behöver inte färgen för denna logik
    std::string message = p.Get_String(2); // Hämtar meddelandesträngen

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MEDDELANDE BLOCKERAT för playerid %d: %s", playerid, message.c_str());

        return 0; // Returnerar 0 (false) till Pawn, vilket indikerar att meddelandet inte skickades.
                  // Och viktigast av allt, vi anropar INTE Call_Original_Native, vilket blockerar meddelandet.
    }

    // Om meddelandet inte innehåller det förbjudna ordet, anropar vi original native-funktionen
    // och returnerar dess värde, vilket säkerställer att meddelandet skickas normalt
    // och att andra hooks (om de finns) exekveras.
    return Call_Original_Native(SendClientMessage);
}
```

#### Fullständigt Exempel på `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS är inte strikt nödvändigt för hooks, men är vanligt för att ha OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook för CreateVehicle native
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extraherar parametrarna från CreateVehicle native för inspektion
    int modelid = p.Get<int>(0);
    float x = p.Get<float>(1);
    float y = p.Get<float>(2);
    float z = p.Get<float>(3);
    float angle = p.Get<float>(4);
    int color1 = p.Get<int>(5);
    int color2 = p.Get<int>(6);
    int respawn_delay = p.Get<int>(7);
    bool addsiren = p.Get<bool>(8);

    Samp_SDK::Log("HOOK: CreateVehicle called! Model: %d, Pos: (%.2f, %.2f, %.2f)", modelid, x, y, z);

    // Exempel på hur man *modifierar* en input-parameter
    // Om modellen är 400 (Landstalker), ändrar vi den till 401 (Bravura)
    if (modelid == 400) {
        // Vi modifierar direkt 'params'-arrayen för det ursprungliga anropet
        params[1] = static_cast<cell>(401); // Modellen är på position 0 i parameterarrayen (params[1])
        Samp_SDK::Log("  -> Modell 400 ändrad till 401 före skapandet.");
    }
    
    // Vi anropar den ursprungliga nativen (eller nästa hook i kedjan) med de eventuellt modifierade parametrarna
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle returned: %d (fordons-ID)", (int)original_retval);

    // Du kan modifiera returvärdet här innan du returnerar det till Pawn.
    // Exempel: om fordonet misslyckades med att skapas, returnera ett anpassat ogiltigt ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Fordonskapande misslyckades i den ursprungliga nativen.");

        return -1; // Returnerar ett annat värde till Pawn.
    }

    return original_retval; // Returnerar det värde som original nativen returnerade (eller det ovan modifierade).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Minimala implementeringar för livscykeln
bool OnLoad() {
    Samp_SDK::Log("Exempelplugin för Native Hook laddat!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Exempelplugin för Native Hook avlastat!");
}

// Dessa callbacks finns endast om SAMP_SDK_WANT_AMX_EVENTS är definierat
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detected: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detected: %p", (void*)amx);
}*/
```
> [!WARNING]
> Direkt manipulation av `cell* params`-arrayen för att ändra input-parametrar kräver försiktighet. Se till att du förstår ordningen och typen av parametrar. För de flesta användningsfall är `p.Get(...)` för att inspektera och `Call_Original_Native(...)` för att fortsätta kedjan tillräckligt. Direkt ändring av `params` bör endast göras om du vet att parametern är ett värde och behöver modifieras för det ursprungliga anropet. För strängar och arrayer är modifieringen mer komplex och involverar vanligtvis `amx::Set_String` för att skriva till den befintliga adressen eller omallokera, vilket kan vara lättare att hantera genom att anropa nativen via `Pawn_Native` med de nya värdena och returnera `0` från din hook för att avbryta det ursprungliga anropet.

### 3.5. `Pawn_*` Makron: Anropa Pawn-funktioner från C++

Dessa makron är motsatsen till `Plugin_Public` och `Plugin_Native`: de låter din C++-kod anropa Pawn-funktioner.

#### `Pawn_Native(NativeName, ...)`

- **Syfte:** Det rekommenderade sättet att anropa SA-MP native-funktioner (eller från andra plugins) från C++.
- **Mekanism:** Söker efter native-pekaren i SDK:ns interna cache (fylld av `Amx_Register_Detour`). Om den hittas, exekverar den nativen i en `Amx_Sandbox`-miljö (en falsk och isolerad AMX-instans).
- **Prestanda:** Den mest effektiva, eftersom den undviker den dyra sökningen efter `publics` och interagerar direkt med native-pekaren.

#### `Pawn_Public(PublicName, ...)`

- **Syfte:** Anropar en specifik public-funktion i ett Pawn-skript.
- **Mekanism:** Går igenom de `AMX*`-instanser som hanteras av `Amx_Manager`, söker efter `public`-funktionen med namnet och exekverar den.
- **Prestanda:** Mindre effektiv än `Pawn_Native` på grund av sökningen och det faktiska `amx_Exec`. Generellt sett är `publics` långsammare än `natives`.
- **Användning:** Idealisk för att anropa anpassade händelser i dina Gamemode/Filterscripts som inte är natives.

#### `Pawn(FunctionName, ...)`

- **Syfte:** Ett bekvämlighetsmakro som försöker gissa om funktionen är en native eller en public.
- **Mekanism:** Försöker först anropa som `Pawn_Native`. Om det misslyckas (nativen hittas inte), försöker den anropa som `Pawn_Public`.
- **Prestanda:** Kan vara något långsammare än `Pawn_Native` om funktionen är en native, på grund av det dubbla sökförsöket. För `publics` är prestandan densamma som `Pawn_Public`.
- **Användning:** För funktioner där du inte är säker på om de är natives eller publics, eller för att undvika det upprepande kodandet med att försöka den ena och sedan den andra.

#### Syntax och Konventioner

- **Funktionsnamn:** Använd alltid Pawn-funktionens namn **direkt, utan citattecken**. SDK:n konverterar det till en sträng internt.
- **Parametrar:** Skicka C++-parametrarna direkt.

```cpp
// Rätt:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Fel (men skulle tekniskt sett fungera på grund av hashen, undvik):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling av Input-parametrar

SDK:n konverterar dina C++-typer till AMX:s `cell`-format och hanterar minnet efter behov:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (med `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (allokerar minne i AMX, kopierar strängen och skickar `amx_addr`-adressen)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling av Output-parametrar (Referenser: `int&`, `float&`, `std::string&`)

Detta är en nyckelfunktion för bekvämlighet och säkerhet. För Pawn-funktioner som förväntar sig en pekare (referens), automatiserar SDK:n hela processen med minnesallokering/-frisättning och datakopiering.

- **Hur man använder:** Skicka helt enkelt din variabel med referens (`&`).
- **Mekanism:** SDK:n allokerar minne på AMX-heapen, skickar AMX-adressen till Pawn-funktionen, väntar på att Pawn-funktionen fyller denna adress, läser tillbaka värdet och frigör AMX-minnet. Allt transparent.
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

    Samp_SDK::Log("Plats för %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interiör:%d Värld:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### Objektet `Callback_Result`: Fullständig Analys

Alla `Pawn_*`-anrop returnerar ett `Callback_Result`-objekt. Detta objekt är en säker wrapper för resultatet av Pawn-anropet.

- `Callback_Result() noexcept`: Standardkonstruktor, indikerar misslyckande (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Konstruktor för framgång eller misslyckande med värde.
- `explicit operator bool() const`: Tillåter att använda `if (result)` för att kontrollera om anropet lyckades.
- `operator cell() const`: Tillåter att konvertera resultatet till `cell` för att få värdet.
- `float As_Float() const`: Bekvämlighetsfunktion för att få resultatet som `float`.
- `cell Value() const`: Returnerar det råa `cell`-värdet.
- `bool Success() const`: Returnerar `true` om Pawn-anropet lyckades.
- `int Get_Amx_Error() const`: Returnerar AMX-felkoden om anropet misslyckades (0 för framgång).

```cpp
// Exempel: Hämta en spelares hälsa.
// Nativen GetPlayerHealth(playerid, &Float:health) förväntar sig ett playerid och en referens till hälsan.
int playerid = 0; // Exempel på spelar-ID
float player_health = 0.0f;

// Vi anropar GetPlayerHealth och skickar playerid och player_health via referens.
// SDK:n tar hand om marshalling för output-parametern 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Kontrollerar om anropet lyckades (operator bool)
    // Värdet som returneras av result.As_Float() eller result (operator cell)
    // skulle vara native-funktionens *returvärde*, inte output-parametern.
    // Hälsovärdet har redan uppdaterats i 'player_health' på grund av marshalling av output-parametern.
    Samp_SDK::Log("Spelare %d har %.1f hälsa.", playerid, player_health);
}
else {
    // Anropet misslyckades, kanske spelaren inte finns eller nativen hittades inte.
    Samp_SDK::Log("Fel vid hämtning av spelare %d:s hälsa. AMX-kod: %d", playerid, result.Get_Amx_Error());
}

// För natives som returnerar ett värde och använder output-parametrar (mindre vanligt, men möjligt),
// skulle du använda båda:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param är redan uppdaterad
// }
```

### 3.6. `Plugin_Module`: Hantering av Dynamiska Moduler

Makrot `Plugin_Module` tillåter ditt plugin att fungera som en "laddare" för andra plugins, vilket skapar en modulär och utbyggbar arkitektur. En modul som laddas på detta sätt behandlas som ett förstklassigt plugin, med sin egen livscykel av händelser som hanteras av värd-pluginet.

#### Syntax och Syfte

- `Plugin_Module(const char* base_filename, const char* module_directory, const char* optional_success_message)`
- `base_filename`: Basnamnet på modulfilen, **utan filändelse** (t.ex. för `my_module.dll` eller `my_module.so`, använd `"my_module"`). SDK:n lägger automatiskt till lämplig filändelse (`.dll` eller `.so`).
- `module_directory`: Sökvägen till katalogen där modulfilen finns (t.ex. `"plugins/my_custom_modules"`). **Inkludera inte filnamnet här.** SDK:n kommer att sammanfoga hela sökvägen (`module_directory/base_filename.ext`).
- `optional_success_message`: Ett valfritt meddelande som ska loggas i serverkonsolen om modulen laddas framgångsrikt.

```cpp
// main.cpp, inom OnLoad()

// Laddar modulen 'core_logic.dll' (eller 'core_logic.so')
// som finns i serverns 'modules/custom/'-mapp.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic-modulen laddad framgångsrikt!"))
    return (Samp_SDK::Log("FATALT FEL: Kunde inte ladda modulen 'core_logic'!"), false);

// Laddar modulen 'admin_system.dll' (eller 'admin_system.so')
// som finns direkt i serverns 'plugins/'-mapp.
if (!Plugin_Module("admin_system", "plugins", "Administrationsmodulen aktiverad."))
    Samp_SDK::Log("VARNING: Administrationsmodulen kunde inte laddas.");
```

#### En Moduls Livscykel

En modul måste exportera funktionerna `Load`, `Unload` och `Supports`, precis som ett vanligt plugin. SDK:n hanterar modulens livscykel på följande sätt:

- **Laddning:** När `Plugin_Module` anropas, gör SDK:n följande:
   1. Konstruerar den fullständiga filsökvägen (t.ex. `modules/custom/core_logic.dll`).
   2. Använder `Dynamic_Library` (`LoadLibrary`/`dlopen`) för att ladda binärfilen.
   3. **Hämtar pekare till ALLA modulens livscykelfunktioner:**
      - **Obligatoriska:** `Load`, `Unload`, `Supports`. Om någon saknas, misslyckas modulladdningen.
      - **Valfria:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Anropar modulens `Load`-funktion och skickar `ppData` från huvudpluginet.
   5. Om `Load` returnerar `true`, läggs modulen till den interna listan över laddade moduler.

- **Vidarebefordran av händelser:** Värd-pluginet **vidarebefordrar automatiskt** händelserna till alla laddade moduler.
 > [!IMPORTANT]
 > För att händelserna ska vidarebefordras korrekt måste **värd-pluginet** (det som anropar `Plugin_Module`) vara konfigurerat för att ta emot dessa händelser.
 > - För att `AmxLoad` och `AmxUnload` ska fungera i modulerna måste värd-pluginet definiera makrot `SAMP_SDK_WANT_AMX_EVENTS`.
 > - För att `ProcessTick` ska fungera i modulerna måste värd-pluginet definiera makrot `SAMP_SDK_WANT_PROCESS_TICK`.

- **Avlastning:** Under `OnUnload` av ditt huvudplugin, avlastar SDK:n alla moduler som laddats via `Plugin_Module`. Detta görs i **omvänd ordning** från laddningen (den sist laddade avlastas först), vilket är avgörande för att hantera beroenden och säkerställa korrekt frigörande av resurser.

#### Fördelar med Modularisering

- **Kodorganisation:** Dela upp stora plugins i mindre, hanterbara komponenter, var och en i sin egen modulfil.
- **Återanvändbarhet:** Skapa generiska moduler (t.ex. en databasmodul, en avancerad loggsystemmodul) som kan användas av olika plugins, vilket främjar kodåteranvändning.
- **Oberoende Komponenter:** Skapa moduler som är **helt händelsestyrda och oberoende**. En modul kan ha sina egna `Plugin_Native`s, intercepta `Plugin_Public`s och ha sin egen `OnProcessTick`-logik, som fungerar som ett autonomt plugin men laddas av en värd.
- **Dynamiska Uppdateringar:** I kontrollerade scenarier möjliggör det uppdatering av delar av ditt system (genom att ersätta en modul `.dll` eller `.so`) utan att behöva kompilera om och starta om huvudpluginet eller hela servern (även om detta kräver noggrann versions- och kompatibilitetshantering).

### 3.7. `Plugin_Call`: Anropa Pluginets Interna Natives

Använd `Plugin_Call` för att anropa en `Plugin_Native` definierad **inom ditt eget plugin**.

#### Syntax och Prestandafördelar

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Fördel:** Undviker överhänget med att söka efter nativen i AMX:s native-array. SDK:n upprätthåller en direkt mappning från namn-hashes till funktionspekare för sina egna natives, vilket gör detta till det snabbaste sättet att anropa dem internt.
- **Kräver:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logik för att kontrollera nivån
    return (playerid % 2 == 0) ? 1 : 0; // Exempel: jämn nivå för jämna ID:n
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Anropar din egen native
                Samp_SDK::Log("Spelare %d har en hög nivå!", i);
        }
    }
}
```

### 3.8. SDK Verktygsfunktioner

#### `Samp_SDK::Log(const char* format, ...)`

- **Beskrivning:** Skriver ut meddelanden till serverkonsolen och till filen `server_log.txt`. En säker wrapper för `logprintf`.
- **Användning:** För felsökning, statusmeddelanden och fel.
- **Mekanism:** Internt hämtar SDK:n pekaren till `logprintf` via `ppData[PLUGIN_DATA_LOGPRINTF]`. Funktionen hanterar strängformateringen på ett säkert sätt.

```cpp
// Var som helst i ditt plugin
Samp_SDK::Log("Pluginet har initialiserats med värde %d och strängen '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Rekommenderas)

- **Beskrivning:** Formaterar en sträng på ett säkert sätt (liknande `sprintf`) och returnerar en `std::string`. Detta är det **rekommenderade och mest idiomatiska** sättet att formatera strängar för användning inom ditt plugin.
- **Användning:** Idealisk för att konstruera formaterade meddelanden innan de skickas till `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, eller för något annat strängbehov inom din C++-kod.
- **Mekanism:** Internt är `Plugin_Format` ett makro som anropar `Samp_SDK::Format`. Den använder `vsnprintf` för att bestämma den exakta storleken på den formaterade strängen och allokerar en `std::string` med tillräcklig kapacitet, vilket förhindrar buffertöverskridanden.

```cpp
int playerid = 0; // Exempel på ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Spelare %d, din nuvarande hälsa är %d.", playerid, health));

// Kan även användas för interna loggar
Samp_SDK::Log(Plugin_Format("DEBUG: Bearbetar status för ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Implementeringsdetalj)

- **Beskrivning:** Den underliggande implementeringsfunktionen för strängformatering, belägen inom `Samp_SDK`-namnrymden.
- **Användning:** Kallas vanligtvis inte direkt av användaren. Makrot `Plugin_Format` tillhandahålls som en bekvämlighet för denna funktion, i linje med namngivningskonventionen för andra SDK-makron (`Plugin_Public`, `Plugin_Native`). Du skulle endast anropa den direkt om du ville undvika makrot `Plugin_Format` av någon specifik anledning.

```cpp
// Exempel på hur Samp_SDK::Format fungerar, men föredra Plugin_Format
std::string raw_status = Samp_SDK::Format("Endast för internt bruk: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Beskrivning:** Konverterar en AMX-strängadress (`cell amx_addr`) till en C++ `std::string`.
- **Användning:** Främst inom `Plugin_Native` och `Plugin_Native_Hook` när du behöver komma åt strängar som inte automatiskt konverteras av `Register_Parameters` eller `Native_Params` (t.ex. om Pawn-parametern är en `const` `string` och inte har deklarerats som `std::string` i din `Plugin_Native` eller `Plugin_Public` för automatisk Marshalling).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Hämtar strängadressen i AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("Sträng från AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. SDKs Interna Anatomi och Arkitektur

Detta avsnitt avslöjar de underliggande mekanismerna i SA-MP SDK, utforskar dess arkitektur, nyckelkomponenter och hur de interagerar för att tillhandahålla abstraktion på hög nivå. En djup förståelse för dessa interna delar gör det möjligt för utvecklaren att optimera användningen av SDK:n, felsöka komplexa problem och till och med utöka dess funktionalitet.

### 4.1. `core.hpp`: Den Minimalistiska Grunden

`Samp_SDK::Core` är en `singleton` som fungerar som den initiala och centraliserade åtkomstpunkten till de lågnivådata som tillhandahålls av SA-MP plugin-miljön. Dess huvudansvar är att kapsla in och exponera de väsentliga funktionerna.

- **`Samp_SDK::Core::Instance()`**:
   - **Beskrivning:** Returnerar den enda globala instansen av klassen `Core`. Detta är ett `singleton`-designmönster för att säkerställa att åtkomsten till pluginets data (`ppData`) är konsekvent och centraliserad.
   - **Mekanism:** Instansen initialiseras en enda gång när `Core::Instance().Load(ppData)` anropas i ditt plugins `Load()`-funktion.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Beskrivning:** Möjliggör säker och indexerad åtkomst till funktionspekare för AMX API:n. `pAMXFunctions`-arrayen (mottagen via `ppData[PLUGIN_DATA_AMX_EXPORTS]`) innehåller adresserna till kritiska funktioner som `amx_Exec`, `amx_Register`, etc.
   - **Påverkan:** Istället för att använda `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, erbjuder SDK:n typsäkra wrappers i `amx::`-namnrymden (t.ex. `amx::Exec(...)`), vilket gör koden mer läsbar och mindre benägen att drabbas av typkonverteringsfel.
   - **Internt exempel (`amx_api.hpp`):**
      ```cpp
      // Förenklad utdrag från amx_api.hpp
      namespace amx {
          template <typename Func, int Index, typename... Args>
          inline auto Call(Args... args) -> decltype(std::declval<Func>()(args...)) {
              using Return_Type = decltype(std::declval<Func>()(args...));
              auto func_ptr = reinterpret_cast<Func>(Core::Instance().Get_AMX_Export(Index));

              if (SAMP_SDK_UNLIKELY(!func_ptr)) {
                  Log("[SA-MP SDK] Fatal: Försök att anropa AMX-export på index %d, men pAMXFunctions var inte laddat!", Index);
                
      #if defined(SAMP_SDK_CXX_MODERN)
                  return Samp_SDK::amx::Detail::Amx_Call_Error_Handler<Return_Type>();
      #elif defined(SAMP_SDK_CXX14)
                  return Samp_SDK::amx::Detail::Amx_Call_Error_Handler<Return_Type>(typename std::is_pointer<Return_Type>::type{});
      #endif
              }

              return func_ptr(args...);
          }

          inline int Exec(AMX* amx, cell* retval, int index) {
              return Call<Exec_t, PLUGIN_AMX_EXPORT_Exec>(amx, retval, index);
          }
      } // namespace amx
      ```

- **`logprintf_ptr`**:
   - **Beskrivning:** En pekare till SA-MP:s `logprintf`-funktion, som är standardgränssnittet för att skriva ut meddelanden till serverkonsolen och `server_log.txt`.
   - **Mekanism:** `Samp_SDK::Log` är en säker wrapper som använder denna pekare och säkerställer att dina meddelanden visas korrekt i SA-MP-miljön.

### 4.2. `platform.hpp` och `version.hpp`: Kompatibilitet och Metadata

Dessa headrar är grunden för SDK:ns portabilitet och optimering, anpassar den till olika kompileringsmiljöer och utnyttjar specifika funktioner i modern C++.

- **Plattforms- och Arkitekturdetektering:**
   - **Mekanism:** Använder förprocessor-makron (`#if defined(WIN32)`, `#if defined(__linux__)`, etc.) för att identifiera operativsystemet.
   - **Arkitekturverifiering:** Innehåller `static_assert` eller `#error` för att säkerställa att pluginet kompileras för x86 (32-bit), ett kritiskt krav för kompatibilitet med SA-MP och hooking-mekanismen.
   - **Hantering av Exportsymboler:**
      - `SAMP_SDK_EXPORT`: Ett makro definierat i `platform.hpp` som expanderar till `extern "C"` och, på Linux, lägger till `__attribute__((visibility("default")))`. På Windows säkerställer det bara `extern "C"` eftersom SDK:n använder `pragma comment(linker, "/EXPORT:...")` (för MSVC) eller MinGW-standarden för att exportera huvudfunktionerna.
      - Detta säkerställer att pluginets livscykelfunktioner (`Supports`, `Load`, `Unload`, etc.) exporteras korrekt från din DLL/SO, oavsett kompileringsmiljö, **utan behov av `.def`-filer eller att lägga till `__attribute__((visibility("default")))` manuellt** i din implementering.
   - **Exempel (`platform.hpp` - relevant fragment):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // För MSVC hanteras exporten av pragma linker commands
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // För GCC/Clang på Linux använder vi synlighetsattributet
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... andra definitioner ...
      ```
   - **Exempel (`samp_sdk.hpp` - relevant fragment av implementeringen):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // På Windows (MSVC) använder vi pragma comment för att exportera funktionerna.
          // Detta eliminerar behovet av en .def-fil.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... andra exports ...
      #endif

      // Implementering av de exporterade funktionerna
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... andra funktioner ...
      #endif
      ```

- **Makron för optimering och Branch Prediction:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mekanism:** `__forceinline` (MSVC) eller `__attribute__((always_inline)) inline` (GCC/Clang). Föreslår starkt för kompilatorn att infoga funktionens kropp direkt vid anropet, vilket eliminerar överhänget av ett faktiskt funktionsanrop.
      - **Användning:** Används för små och prestandakritiska funktioner inom SDK:n.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mekanism:** `[[likely]]` / `[[unlikely]]` (C++20) eller `__builtin_expect` (GCC/Clang). Tips till kompilatorn om vilken väg i en `if/else`-sats som är mest sannolik att tas.
      - **Påverkan:** Hjälper kompilatorn att generera effektivare kod för grenprognoser (branch prediction), vilket minskar CPU-latensen.
      - **Exempel (`platform.hpp`):**
         ```cpp
         #if (defined(SAMP_SDK_COMPILER_MSVC) && _MSVC_LANG >= 202002L) || (defined(__cplusplus) && __cplusplus >= 202002L)
             #define SAMP_SDK_LIKELY(x) (x) [[likely]]
             #define SAMP_SDK_UNLIKELY(x) (x) [[unlikely]]
         #elif defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
             #define SAMP_SDK_LIKELY(x) __builtin_expect(!!(x), 1)
             #define SAMP_SDK_UNLIKELY(x) __builtin_expect(!!(x), 0)
         #else
             #define SAMP_SDK_LIKELY(x) (x)
             #define SAMP_SDK_UNLIKELY(x) (x)
         #endif
         ```

- **C++ Standard Definitioner (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mekanism:** Makron definierade baserat på värdet av `__cplusplus` och `_MSVC_LANG`.
   - **Användning:** Tillåter SDK:n att använda nyare C++-funktioner (som `std::apply` och `if constexpr` från C++17, eller `std::is_same_v` från C++17) när de är tillgängliga, samtidigt som kompatibiliteten med äldre standarder bibehålls.
   - **Exempel (`version.hpp` - användning av `if constexpr`):**
      ```cpp
      // Förenklad utdrag från public_dispatcher.hpp
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
                  // C++14-kompatibilitet: använd hjälpfunktionen Assign_Parameter_By_Type
                  Assign_Parameter_By_Type(amx, &value, first); 
      #endif
          }

          Get_Public_Params_Recursive(amx, index + 1, rest...);
      }
      ```

### 4.3. `function_hook.hpp`: x86 Intercept-motorn

Denna header definierar lågnivåmekanismen för att utföra funktion-hooks (intercept), vilket är grundläggande för SDK:ns funktion. Den är strikt beroende av x86-arkitekturen (32-bit).

- **`X86_Detour`**:
   - **Beskrivning:** En klass som kapslar in logiken för att skriva över början av en funktion i minnet med en hoppinstruktion till en detour-funktion.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mekanism:** I x86 har en relativ hoppinstruktion (`JMP`) vanligtvis 5 byte: `0xE9` (opcode för JMP near, relative) följt av 4 byte som representerar förskjutningen (offset) av måladdressen i förhållande till nästa instruktion.
      - **Instruktionsexempel:** `E9 XX XX XX XX` (där `XX` är förskjutningens byte).
   - **`Apply(void* target, void* detour)`**:
      - **Åtgärd:** Installerar hooken. Först lagras de `JUMP_INSTRUCTION_SIZE` ursprungliga bytena från `target`-funktionen (`original_bytes_`). Sedan beräknas den relativa adressen för `detour` i förhållande till `target` och början av `target` skrivs över med `JMP`-instruktionen.
      - **Exempel på beräkning av relativ adress:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Detour-funktionens adress - (Målfunktionens adress + storlek på JMP-instruktionen)
         ```
   - **`Revert()`**:
      - **Åtgärd:** Avinstallerar hooken och återställer de `original_bytes_` i `target`-funktionen.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mekanism:** På Windows används `VirtualProtect`; på Linux `mprotect`. Dessa systemanrop ändrar behörigheterna för minnessidan där funktionen finns till `EXECUTE_READWRITE` (Windows) eller `PROT_WRITE | PROT_EXEC` (Linux), vilket tillåter att koden modifieras vid körtid.
      - **Exempel (`Unprotect_Memory`):**
         ```cpp
         // Förenklad utdrag från function_hook.hpp
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
   - **Beskrivning:** En C++ `type-safe` wrapper för `X86_Detour`, som säkerställer att funktionspekartyperna är korrekta.
   - `Install(void* target, void* detour)`: Kapslar in anropet `X86_Detour::Apply`.
   - `Uninstall()`: Kapslar in anropet `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Säkerhetsmekanism (Recursion Guard):** Denna funktion är kritisk för att undvika oändliga loopar när detektivåtgärden behöver anropa originalfunktionen. Den **avinstallerar tillfälligt hooken (`detour_.Revert()`)**, anropar originalfunktionen (`Get_Original()(args...)`) och **installerar sedan om hooken (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: En räknare som säkerställer att hooken endast återinstalleras när det högsta ursprungliga anropet är slutfört, vilket möjliggör säkra rekursiva anrop till originalfunktionen (om originalfunktionen till exempel är rekursiv). `thread_local` garanterar att `recursion_guard` är isolerad för varje tråd, viktigt i flertrådiga miljöer.
      - **Exempel (`Call_Original` med Scope_Guard):**
         ```cpp
         // Förenklad utdrag från function_hook.hpp
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

### 4.4. `interceptor_manager.hpp`: AMX Hook-kontrollern

Denna `singleton` är nervcentrumet för SDK:ns interaktion med SA-MP:s AMX virtuella maskin. Den koordinerar installationen av hooks som tillhandahålls av `function_hook.hpp` i de AMX API-funktioner som exponeras av servern, och omdirigerar exekveringsflödet till SDK:ns logik.

- **`Activate()` / `Deactivate()`**:
   - **Beskrivning:** Offentliga metoder för att installera och avinstallera alla nödvändiga hooks. Anropas i ditt plugins `OnLoad()` och `OnUnload()`, respektive.
   - **Mekanism:** Hämtar pekarna till AMX-funktionerna (som `amx_Register`, `amx_Exec`, etc.) med `Core::Instance().Get_AMX_Export(...)` och installerar avvikelserna.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Hookad Funktion:** `amx_Register`
   - **Syfte:** Interceptar registreringen av *alla* natives (av SA-MP, andra plugins eller gamemode).
   - **Åtgärd:** För varje registrerad native lägger `Interceptor_Manager` till den i en intern cache (`Cache_Data::native_cache`).
   - **Påverkan:** Denna cache är grundläggande för prestandan hos `Pawn_Native`, vilket möjliggör en extremt snabb sökning efter native-pekaren istället för en dyrbar sökning i AMX.
   - **Ytterligare funktion för `Plugin_Native_Hook`:** Denna detour *är också* ansvarig för att modifiera listan över natives innan de registreras. Om en native har en associerad `Plugin_Native_Hook`, ersätts funktionens pekare i registreringslistan med den trampoline som genereras av `Native_Hook_Manager`. Detta gör att din hook kan anropas först.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Hooked Funktion:** `amx_Exec`
   - **Syfte:** **Detta är den mest kritiska hooken.** Den interceptar *alla* kodexekveringar i AMX, inklusive anrop av Pawn `publics`.
   - **Mekanism för att Intercepta `Plugin_Public`:**
      1. När `amx_Exec` anropas för en `public` (eller `AMX_EXEC_MAIN`), exekveras `Amx_Exec_Detour`.
      2. Den hämtar namnet på `public`-funktionen (med `tl_public_name` som fyllts i av `Amx_Find_Public_Detour`).
      3. Konsulterar `Public_Dispatcher::Instance().Dispatch()` för att kontrollera om det finns C++-handlers registrerade för detta namn.
      4. Om det finns handlers, exekverar den dem. `Public_Dispatcher` hanterar `marshalling` av parametrarna från AMX till de korrekta C++-typerna.
      5. Baserat på returvärdet från `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), bestämmer den om den ska anropa den ursprungliga `amx_Exec` (`Get_Amx_Exec_Hook().Call_Original(...)`) eller avsluta exekveringen av Pawn `public`.
      6. **Stackhantering:** Om exekveringen av Pawn `public` avbryts (`PLUGIN_PUBLIC_STOP`), korrigerar `Amx_Exec_Detour` AMX-stacken (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) för att undvika inkonsekvenser.
   - **Aktivering av `Plugin_Native_Hook` (Patching AMX):**
      - Första gången en `AMX*` exekveras, kontrollerar denna detour om AMX redan har "patchats" (`!manager.Is_Amx_Patched(amx)`).
      - Om inte, går den igenom native-tabellen **för den specifika AMX-instansen i minnet**.
      - För varje native som har en `Plugin_Native_Hook` registrerad i `Native_Hook_Manager`, ersätter den native-adressen i tabellen med en trampoline genererad av `Native_Hook_Manager`. Den ursprungliga adressen (eller från den tidigare hooken) sparas i `Native_Hook`-objektet.
      - AMX markeras sedan som "patchad" för att undvika onödig ombearbetning.
   - **Exempel (`Amx_Exec_Detour` - med detaljer om `Plugin_Native_Hook`):**
      ```cpp
      // Förenklad utdrag från interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          auto& manager = Interceptor_Manager::Instance();

          std::unique_ptr<std::string> public_name_ptr;

          // Plugin_Public intercepting logic (as described above)
          // ...

          int exec_result = Get_Amx_Exec_Hook().Call_Original(amx, retval, index);

          // Patching Logic for Plugin_Native_Hook
          if (SAMP_SDK_UNLIKELY(!manager.Is_Amx_Patched(amx))) {
              auto& hook_manager = Native_Hook_Manager::Instance();
              auto& hooks_to_apply = hook_manager.Get_All_Hooks();

              if (!hooks_to_apply.empty()) {
                  AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
                  AMX_FUNCSTUBNT* natives = reinterpret_cast<AMX_FUNCSTUBNT*>(reinterpret_cast<unsigned char*>(hdr) + hdr->natives);

                  int num_natives;

                  amx::Num_Natives(amx, &num_natives);

                  for (auto& hook_to_apply : hooks_to_apply) { // Itererar genom alla registrerade Plugin_Native_Hooks
                      uint32_t hook_hash = hook_to_apply.Get_Hash();

                      for (int i = 0; i < num_natives; ++i) { // Itererar genom AMX-natives
                          const char* native_name = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(hdr) + natives[i].nameofs);

                          if (FNV1a_Hash(native_name) == hook_hash) { // Om AMX-native-namnet matchar en hook
                              AMX_NATIVE current_func = reinterpret_cast<AMX_NATIVE>(natives[i].address);

                              hook_to_apply.Set_Next_In_Chain(current_func); // Sparar pekaren till original/föregående funktion

                              AMX_NATIVE trampoline = hook_manager.Get_Trampoline(hook_hash); // Hämtar trampolinen för denna hook

                              if (trampoline)
                                  natives[i].address = reinterpret_cast<ucell>(trampoline); // Ersätter i AMX-tabellen
                              
                              break;
                          }
                      }
                  }
              }
              
              manager.On_Amx_Patched(amx); // Marker AMX as patched
          }
          
          return exec_result;
      }
      ```
- **`int SAMP_SDK_AMX_API Amx_Find_Public_Detour(...)`**:
   - **Hookad Funktion:** `amx_FindPublic`
   - **Syfte:** Interceptar sökningen efter `publics` efter namn.
   - **Mekanism för "Ghost Publics":** Om den ursprungliga `amx_FindPublic` inte hittar en `public` i Pawn, men `Public_Dispatcher` har en C++-handler registrerad för det namnet, returnerar denna hook `AMX_ERR_NONE` och ett speciellt `index` (`PLUGIN_EXEC_GHOST_PUBLIC`). Detta får SA-MP API att "tro" att `public`-funktionen existerar, vilket tillåter att det efterföljande `amx_Exec`-anropet (för detta speciella index) interceptas av `Amx_Exec_Detour`, som sedan omdirigerar till C++-handlern.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Används för att skicka namnet på `public`-funktionen till `Amx_Exec_Detour` när en "ghost public" upptäcks, eftersom `amx_Exec` endast tar emot indexet, inte namnet.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Hookade Funktioner:** `amx_Init` / `amx_Cleanup`
   - **Syfte:** Hantera listan över aktiva `AMX*`-instanser.
   - **Åtgärd:** `Amx_Init_Detour` anropar `Amx_Manager::Instance().Add_Amx()`, och `Amx_Cleanup_Detour` anropar `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Hantera `AMX*` Instanser

Denna `singleton` upprätthåller ett dynamiskt register över alla AMX virtuella maskiner som för närvarande är laddade på servern. Det är viktigt för funktioner som behöver interagera med "alla skript" eller hitta ett specifikt skript.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Beskrivning:** En lista med pekare till alla `AMX*`-instanser som har initialiserats (gamemode och filterscripts).
   - **Hantering:** Fylls av hooks `Amx_Init_Detour` och töms av `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Syfte:** Skyddar `loaded_amx_` mot samtidig åtkomst i flertrådiga miljöer (även om SA-MP i huvudsak är en tråd, är detta en bra säkerhetspraxis). `std::shared_mutex` tillåter flera läsare samtidigt, men bara en skrivare.
- **`std::atomic<uint32_t> generation_`**:
   - **Syfte:** En räknare som ökar varje gång en AMX läggs till eller tas bort.
   - **Användning:** Används av `Caller_Cache` i `callbacks.hpp` för att upptäcka när listan över AMX:er har ändrats, vilket ogiltigförklarar cachelagringar av `public`-sökningar och säkerställer att `Pawn_Public`-anrop alltid fungerar med uppdaterad information. Detta optimerar prestanda genom att undvika upprepade sökningar i ett tillstånd som inte har ändrats.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Beskrivning:** Itererar genom `loaded_amx_` (från senaste till äldsta, vilket vanligtvis placerar den mest relevanta gamemoden eller filterscriptet först) för att hitta `public`-funktionen med det angivna namnet.
   - **Mekanism:** Använder `amx::Find_Public` för varje `AMX*`-instans.
   - **Påverkan:** Är grunden för `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: `Plugin_Public` Callback-routern

Denna `singleton` är den komponent som mappar namn på Pawn `publics` till dina C++ `Plugin_Public`-funktioner.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Nyckel:** FNV1a-hash av `public`-funktionens namn (t.ex. `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Värde:** En `std::vector` av `std::function<cell(AMX*)>`, där varje `std::function` är en C++-handler registrerad för den `public`-funktionen.
   - **Mekanism:** `std::vector` tillåter att flera `Plugin_Public`s registreras för samma callback (t.ex. flera plugins som vill intercepta `OnPlayerCommandText`). Handlarna exekveras i omvänd registreringsordning.
- **`Public_Register`**:
   - **Mekanism:** Detta är en template-klass vars makro `PLUGIN_PUBLIC_REGISTRATION` skapar en statisk global instans. I den statiska konstruktorn (`static bool registered = [...]`) registrerar den sin `Plugin_Public`-handler i `Public_Dispatcher`. Detta är ett mönster för "statisk registrering vid kompilering/initialisering".
   - **Exempel (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Register<decltype(&name), &name, hash_##name> register_##name;
      ```

- **`Public_Traits` och `Wrapper()`**:
   - **Mekanism:** `Public_Traits` är en trait-template som, med metaprogrammering, genererar en funktion `static cell Wrapper(AMX* amx)`.
   - **Syfte:** Denna `Wrapper` är den `Amx_Handler_Func` som `Public_Dispatcher` faktiskt lagrar och anropar. Den är ansvarig för att:
      1. Anropa `Public_Param_Reader::Get_Public_Params(amx, args...)` för att extrahera parametrarna från AMX-stacken.
      2. Anropa din faktiska C++ `Plugin_Public`-funktion (`func_ptr`) med parametrarna redan konverterade till de korrekta C++-typerna.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Beskrivning:** En uppsättning rekursiva template-funktioner som läser värden från AMX-stacken och konverterar dem till de C++-typer som specificerats i `Plugin_Public`-deklarationen.
   - **Mekanism:** Använder `Get_Stack_Cell()` för att komma åt `cell`s på stacken. Använder `if constexpr` (C++17+) eller `std::is_same<T>::value` (C++14) för att tillämpa rätt konvertering (`amx::AMX_CTOF` för float, `Samp_SDK::Get_String` för string, direkt cast till int).

### 4.7. `native.hpp`: Hantera och Anropa Plugin Natives

Denna header är dedikerad till att skapa och hantera C++ natives som ditt plugin exponerar för Pawn.

- **`Native_List_Holder`**:
   - **Beskrivning:** En global `singleton` som lagrar alla `Plugin_Native`s deklarerade i ditt plugin (från alla `.cpp`-filer som använder `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Innehåller `Native`-objekt (som lagrar namnet på nativen och pekaren till C++ `Native_Handler`-funktionen).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: En hash-optimerad mapp för snabba sökningar av interna `Plugin_Native`s (används av `Plugin_Call`).
- **`Native_Register`**:
   - **Mekanism:** Precis som `Public_Register` är detta en template-klass vars makro `Plugin_Native` skapar en statisk global instans. I dess konstruktor lägger den till nativen i `Native_List_Holder`.
   - **Påverkan:** Låter dig deklarera `Plugin_Native`s i flera `.cpp`-filer utan att oroa dig för manuell registrering. Alla kommer att samlas in automatiskt.
- **`Native_Registry`**:
   - **Beskrivning:** En hjälpklass som, i `OnAmxLoad`, hämtar den fullständiga listan över `Native`s från `Native_List_Holder` och formaterar dem till en `AMX_NATIVE_INFO`-array.
   - **Mekanism:** Anropar `amx::Register(amx, amx_natives_info_.data(), -1)` för att registrera alla dina natives i den AMX-instans som just laddades.
- **`Plugin_Call_Impl(...)`**:
   - **Beskrivning:** Den underliggande implementeringen av makrot `Plugin_Call`.
   - **Mekanism:** Använder `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` för att direkt hämta C++-funktionens pekare.
   - **Miljö:** Exekverar nativen i en `Amx_Sandbox`-miljö (isolerad) för att hantera temporär stack och heap, på ett liknande sätt som `Pawn_Native` fungerar.

### 4.8. `native_hook_manager.hpp`: Natives Hook-motorn

Detta är det robusta native hooking-systemet, designat för att hantera kedjning av hooks från flera plugins för samma native.

- **`Native_Hook`**:
   - **Beskrivning:** En klass som representerar en enskild native hook. Lagrar hashen av native-namnet, den användarlevererade C++-handlerfunktionen (`user_handler_`) och en `std::atomic<AMX_NATIVE> next_in_chain_`.
   - **`user_handler_`**: Din C++ `Plugin_Native_Hook`-funktion.
   - **`next_in_chain_`**: Pekaren till den ursprungliga nativen eller till en hook från ett plugin med lägre prioritet. Det är en `std::atomic` för att säkerställa trådsäkerhet vid läsning/skrivning.
   - **`Dispatch(AMX* amx, cell* params)`**: Anropas av trampolinen för att exekvera din `user_handler_`.
   - **`Call_Original(AMX* amx, cell* params)`**: Viktig metod som anropar `next_in_chain_`, vilket tillåter din hook att anropa den ursprungliga funktionaliteten eller nästa hook i kedjan.
- **`Trampoline_Allocator`**:
   - **Beskrivning:** En klass som ansvarar för att allokera exekverbara minnesblock och generera assembler-koden "trampoline" i dessa block.
   - **`Generate_Trampoline_Code(unsigned char* memory, int hook_id)`**: Skriver 10 byte assembler:
      1. `B8 XX XX XX XX`: `MOV EAX, hook_id` (placerar den unika hook-ID:t i EAX-registret).
      2. `E9 XX XX XX XX`: `JMP relative_address_to_Dispatch_Wrapper_Asm` (hoppar till SDK:ns generiska Dispatch_Wrapper_Asm-funktion).
   - **`Allocation_Size = 4096`**: Allokerar minne i sidor för effektivitet och cache-justering.
   - **Minnesbehörigheter:** Använder `VirtualAlloc` (Windows) eller `mmap` (Linux) med behörigheter `EXECUTE_READWRITE` för att säkerställa att den genererade koden kan exekveras.
- **`Dispatch_Wrapper_Asm()`**:
   - **Beskrivning:** En liten assembler-funktion (definierad med `__declspec(naked)` eller `asm volatile`) som fungerar som målet för alla trampoliner.
   - **Åtgärd:** Sparar register, flyttar `EAX` (som innehåller `hook_id`) till stacken och anropar `Dispatch_Hook`-funktionen i C++. Efter återkomst från `Dispatch_Hook` återställs register och återvänder.
- **`cell SAMP_SDK_CDECL Dispatch_Hook(int hook_id, AMX* amx, cell* params)`**:
   - **Beskrivning:** Den generiska C++-funktionen som anropas av `Dispatch_Wrapper_Asm`.
   - **Åtgärd:** Använder `hook_id` för att hitta motsvarande `Native_Hook` i `Native_Hook_Manager` och anropar dess `Dispatch()`-metod, som i sin tur anropar användarens `Plugin_Native_Hook`-handler.
- **`Native_Hook_Manager`**:
   - **Beskrivning:** Den centrala `singleton` som hanterar alla registrerade `Native_Hook`s och deras trampoliner.
   - **`std::list<Native_Hook> hooks_`**: Lagrar listan över hooks i ordning.
   - **`std::unordered_map<uint32_t, Trampoline_Func> hash_to_trampoline_`**: Mappar hashen av native-namnet till pekaren för den genererade trampolinen.
   - **`std::vector<uint32_t> hook_id_to_hash_`**: Mappar det heltaliga ID:t för hooken (används i trampolinen) tillbaka till hashen av native-namnet.
   - **`Get_Trampoline(uint32_t hash)`**: Returnerar (eller skapar och allokerar) en trampolinepekare för en given native-hash.
- **`PLUGIN_NATIVE_HOOK_REGISTRATION`**:
   - **Mekanism:** Ett makro som skapar en statisk global klass (`Native_Hook_Register_##name`) för varje `Plugin_Native_Hook`. I den statiska konstruktorn för denna klass registrerar den användarens `handler` i `Native_Hook_Manager`.

### 4.9. `callbacks.hpp` & `amx_memory.hpp`: C++ -> Pawn Anrop och RAII

Dessa headrar utgör ryggraden för att anropa Pawn-funktioner från C++ (`Pawn_*`-makron) och säkerställer minnesäkerhet.

- **`Amx_Sandbox`**:
   - **Beskrivning:** En `thread_local` struktur som simulerar en minimalistisk och isolerad `AMX`-miljö för `Pawn_Native`- och `Plugin_Call`-anrop.
   - **Mekanism:** Har sin egen `AMX`-struct, `AMX_HEADER` och en `std::vector<unsigned char> heap` för att simulera ett skripts minne. Detta gör att `amx::Push`, `amx::Allot`, etc., kan anropas utan att interferera med tillståndet för verkliga Pawn-skript som körs.
   - **`thread_local`:** Säkerställer att varje tråd har sin egen `Amx_Sandbox`, vilket förhindrar kapplöpningsförhållanden om SDK:n används i ett flertrådat sammanhang (t.ex. en framtida trådpool för icke-Pawn-operationer).
   - **Exempel (`Amx_Sandbox`):**
      ```cpp
      // Förenklad utdrag från callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Simulerat minne för stack/heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Initialiserar AMX och headern
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
   - **Beskrivning:** En uppsättning överbelastade template-funktioner som hanterar `marshalling` av *varje* C++-parameter till det `cell`-format som AMX förväntar sig, och vice versa för utdataparametrar.
   - **Input-bearbetning:**
       - För `int`, `float`, `bool`: Konverterar direkt till `cell`.
       - För `const char*`, `std::string`: Allokerar minne på `Amx_Sandbox`-heapen (eller verklig AMX för `Pawn_Public`), kopierar strängen och lägger AMX-adressen på stacken.
   - **Output-bearbetning (`is_output_arg`):**
       - **Mekanism:** När ett argument är en icke-konstant lvalue-referens (upptäcks av trait `is_output_arg`), skjuter `Parameter_Processor` inte värdet, utan snarare en *AMX-adress* till en tillfälligt allokerad `cell` på heapen.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Efter anropet till Pawn native-funktionen exekveras en lista med lambdas (`post_call_updaters`). Varje lambda ansvarar för att läsa det slutliga värdet från den allokerade `cell`en i AMX och tilldela det tillbaka till den ursprungliga C++-variabeln (t.ex. `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mekanism:** En `std::integral_constant` (type trait) som vid kompileringstiden utvärderar om en C++-parametertyp är en modifierbar referens (t.ex. `int&`, `float&`, `std::string&`). Detta gör att `Parameter_Processor` kan skilja på in- och utparametrar.
   - **Exempel (`is_output_arg`):**
      ```cpp
      // Förenklad utdrag från callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Beskrivning:** En RAII-klass (`Resource Acquisition Is Initialization`) som kapslar in allokering och frigörande av minne i AMX.
   - **Mekanism:** I konstruktorn anropar den `amx::Allot` för att få en `amx_addr` och en `phys_addr`. I destruktorn anropar den `amx::Release` för att frigöra detta minne.
   - **Påverkan:** **Viktigt för att förhindra minnesläckor på AMX-heapen.** Säkerställer att temporärt minne som används för strängar eller utdataparametrar alltid frigörs, även om undantag uppstår eller tidiga returer görs.

### 4.10. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Abstraherad AMX-åtkomst

Dessa headrar tillhandahåller de grundläggande definitionerna och högnivåverktygen för att interagera med Pawn.

- **`amx_defs.h`**:
   - **Innehåll:** Innehåller de råa definitionerna av AMX-strukturerna (`AMX`, `AMX_HEADER`), typer (`cell`, `ucell`) och fel-enums (`AmxError`). Definierar även `AMX_NATIVE` och `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Använder packningsattribut (`#pragma pack(push, 1)` / `__attribute__((packed))`) för att säkerställa att AMX-strukturerna har rätt minneslayout, vilket är avgörande för interoperabilitet.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Beskrivning:** Den huvudsakliga template-funktionen för att anropa AMX API-funktioner som exponeras av servern.
   - **Mekanism:** Hämtar funktionens pekare via `Core::Instance().Get_AMX_Export(Index)` och anropar den. Centraliserar felhantering om funktionens pekare inte är tillgänglig.
   - **Påverkan:** Konverterar lågnivåanrop (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) till idiomatiska och typsäkra C++-anrop (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Beskrivning:** Viktiga funktioner för att konvertera `cell`-värden till `float` och vice versa, genom att utföra en bitvis ominterpretation av minnet.
   - **`static_assert`:** Innehåller `static_assert` för att säkerställa att `sizeof(cell) == sizeof(float)` vid kompileringstid, vilket förhindrar fel på plattformar med olika typstorlekar.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Beskrivning:** Hjälpfunktion för att konvertera en AMX-strängadress till `std::string`.
   - **Mekanism:** Först hämtas den fysiska adressen (`cell* phys_addr`) för strängen i AMX med `amx::Get_Addr`. Sedan används `amx::STR_Len` för att bestämma längden och `amx::Get_String` för att kopiera byten till en `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Beskrivning:** Basfunktionen för strängformatering (`printf`-liknande) för SDK:n.
   - **Mekanism:** Använder `vsnprintf` i två pass: först för att bestämma den nödvändiga strängstorleken, och sedan för att formatera strängen till den dynamiskt allokerade `std::string`. Detta förhindrar buffertöverskridanden.

## 5. Kompilering och Deploy

### Krav på Arkitektur och Plattform

- Ditt plugin **MÅSTE** kompileras för arkitekturen **x86 (32-bit)**.
- Plattformar som stöds: Windows (.dll) och Linux (.so).

### Exempel på Kompileringskommandon

#### **MSVC (Visual Studio)**

1. Skapa ett nytt projekt av typen "Dynamic-Link Library (DLL)".
2. I projektinställningarna, ställ in "Lösningsplattform" till **x86**.
3. Se till att C++ Language Standard är minst C++14.

#### **GCC / Clang (Linux)**

```bash
# För ett plugin som heter 'my_plugin.so' från 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Kompilerar för 32-bit.
- `-shared`: Skapar ett delat bibliotek (`.so`).
- `-std=c++17`: Sätter C++-standarden till C++17 (kan vara `c++14` eller `c++20`).
- `-O2`: Optimeringsnivå 2.
- `-fPIC`: Genererar positionsberoende kod, nödvändigt för delade bibliotek.
- `-Wall -Wextra`: Aktiverar ytterligare varningar för att hjälpa till att hitta fel.
- `-Wl,--no-undefined`: Förhindrar att biblioteket skapas om det finns odefinierade symboler.

#### **GCC / Clang (MinGW på Windows)**

```bash
# För ett plugin som heter 'my_plugin.dll' från 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Länkar standard C++-biblioteket statiskt. Viktigt för att undvika att ditt plugin är beroende av specifika kompilator-runtime DLL:er som kanske inte finns på användarens system.
- `-static-libgcc`: Länkar GCC-biblioteket statiskt.

### Överväganden för Distribution

- **Filnamn:** Ditt plugin ska ha filändelsen `.dll` (Windows) eller `.so` (Linux). Ex: `my_plugin.dll`.
- **Plats:** Placera den kompilerade filen i din SA-MP-servers `plugins/`-mapp.
- **server.cfg:** Lägg till namnet på ditt plugin (om Windows, utan filändelsen) till raden `plugins` i `server.cfg`.
   ```
   plugins my_plugin (om Linux, my_plugin.so)
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