# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Ein modernes, Header-Only und High-Level C++ SDK für die Entwicklung von Plugins und Modulen für SA-MP.**

</div>

## Sprachen

- Português: [README](../../)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Inhaltsverzeichnis

- [SA-MP SDK](#sa-mp-sdk)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [1. Einführung und Designphilosophie](#1-einführung-und-designphilosophie)
    - [Das Problem mit der Standard C API von SA-MP](#das-problem-mit-der-standard-c-api-von-sa-mp)
    - [Die Lösung des SA-MP SDK: Abstraktion mit Sicherheit und Performance](#die-lösung-des-sa-mp-sdk-abstraktion-mit-sicherheit-und-performance)
    - [Header-Only Modell: Vorteile und Implikationen](#header-only-modell-vorteile-und-implikationen)
  - [2. Konfiguration und Umgebung](#2-konfiguration-und-umgebung)
    - [Kompilierungsanforderungen](#kompilierungsanforderungen)
    - [Empfohlene Dateistruktur](#empfohlene-dateistruktur)
    - [Wesentliche Konfigurationsmakros](#wesentliche-konfigurationsmakros)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP Definitionen und Konstanten (`samp_defs.hpp`)](#sa-mp-definitionen-und-konstanten-samp_defshpp)
  - [3. Umfassende API-Nutzungsanleitung](#3-umfassende-api-nutzungsanleitung)
    - [3.1. Der Plugin-Lebenszyklus](#31-der-plugin-lebenszyklus)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Abfangen von Pawn-Events](#32-plugin_public-abfangen-von-pawn-events)
      - [Syntax und Deklaration](#syntax-und-deklaration)
      - [Automatische Parameter-Marshalling](#automatische-parameter-marshalling)
      - [Flusskontrolle: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#flusskontrolle-plugin_public_continue-vs-plugin_public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.3. `Plugin_Native`: Erstellen von nativen C++-Funktionen](#33-plugin_native-erstellen-von-nativen-c-funktionen)
      - [Syntax und feste Signatur](#syntax-und-feste-signatur)
      - [Automatische Native-Registrierung](#automatische-native-registrierung)
      - [Parameter-Extraktion: `Register_Parameters` vs. `Native_Params`](#parameter-extraktion-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Vollständige API: `Get`, `Get_REF`, `Set_REF`)](#native_params-vollständige-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Rückgabewerte](#rückgabewerte)
    - [3.4. `Plugin_Native_Hook`: Abfangen von vorhandenen SA-MP-Natives](#34-plugin_native_hook-abfangen-von-vorhandenen-sa-mp-natives)
      - [Syntax und feste Signatur](#syntax-und-feste-signatur-1)
      - [Hook-Registrierung und -Aktivierung](#hook-registrierung-und--aktivierung)
      - [Aufruf der originalen Native (Hook-Kette): `Call_Original_Native`](#aufruf-der-originalen-native-hook-kette-call_original_native)
      - [Vollständiges Beispiel für `Plugin_Native_Hook`](#vollständiges-beispiel-für-plugin_native_hook)
    - [3.5. `Pawn_*` Makros: Aufrufen von Pawn-Funktionen aus C++](#35-pawn_-makros-aufrufen-von-pawn-funktionen-aus-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Syntax und Konventionen](#syntax-und-konventionen)
      - [Marshalling von Eingabeparametern](#marshalling-von-eingabeparametern)
      - [Marshalling von Ausgabeparametern (Referenzen: `int&`, `float&`, `std::string&`)](#marshalling-von-ausgabeparametern-referenzen-int-float-stdstring)
      - [Das `Callback_Result`-Objekt: Vollständige Analyse](#das-callback_result-objekt-vollständige-analyse)
    - [3.6. `Plugin_Module`: Dynamische Modulverwaltung](#36-plugin_module-dynamische-modulverwaltung)
      - [Syntax und Zweck](#syntax-und-zweck)
      - [Lebenszyklus eines Moduls](#lebenszyklus-eines-moduls)
      - [Vorteile der Modularisierung](#vorteile-der-modularisierung)
    - [3.7. `Plugin_Call`: Aufrufen interner Plugin-Natives](#37-plugin_call-aufrufen-interner-plugin-natives)
      - [Syntax und Performance-Vorteile](#syntax-und-performance-vorteile)
    - [3.8. SDK-Utility-Funktionen](#38-sdk-utility-funktionen)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Empfohlen)](#stdstring-plugin_formatconst-char-format--empfohlen)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Implementierungsdetail)](#stdstring-samp_sdkformatconst-char-format--implementierungsdetail)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Interne Anatomie und Architektur des SDK](#4-interne-anatomie-und-architektur-des-sdk)
    - [4.1. `core.hpp`: Das minimalistische Fundament](#41-corehpp-das-minimalistische-fundament)
    - [4.2. `platform.hpp` und `version.hpp`: Kompatibilität und Metadaten](#42-platformhpp-und-versionhpp-kompatibilität-und-metadaten)
    - [4.3. `function_hook.hpp`: Der x86-Abfangmotor](#43-function_hookhpp-der-x86-abfangmotor)
    - [4.4. `interceptor_manager.hpp`: Der AMX-Hook-Controller](#44-interceptor_managerhpp-der-amx-hook-controller)
    - [4.5. `amx_manager.hpp`: Verwalten von `AMX*`-Instanzen](#45-amx_managerhpp-verwalten-von-amx-instanzen)
    - [4.6. `public_dispatcher.hpp`: Der `Plugin_Public`-Callback-Router](#46-public_dispatcherhpp-der-plugin_public-callback-router)
    - [4.7. `native.hpp`: Verwalten und Aufrufen von Plugin-Natives](#47-nativehpp-verwalten-und-aufrufen-von-plugin-natives)
    - [4.8. `native_hook_manager.hpp`: Der Hook-Motor für Natives](#48-native_hook_managerhpp-der-hook-motor-für-natives)
    - [4.9. `callbacks.hpp` \& `amx_memory.hpp`: C++ -\> Pawn-Aufrufe und RAII](#49-callbackshpp--amx_memoryhpp-c---pawn-aufrufe-und-raii)
    - [4.10. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Abstrahierter AMX-Zugriff](#410-amx_apihpp--amx_helpershpp--amx_defsh-abstrahierter-amx-zugriff)
  - [5. Kompilierung und Bereitstellung](#5-kompilierung-und-bereitstellung)
    - [Architektur- und Plattformanforderungen](#architektur--und-plattformanforderungen)
    - [Beispiele für Kompilierungsbefehle](#beispiele-für-kompilierungsbefehle)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW unter Windows)**](#gcc--clang-mingw-unter-windows)
    - [Überlegungen zur Verteilung](#überlegungen-zur-verteilung)
  - [Lizenz](#lizenz)
    - [Nutzungsbedingungen](#nutzungsbedingungen)
      - [1. Gewährte Berechtigungen](#1-gewährte-berechtigungen)
      - [2. Verpflichtende Bedingungen](#2-verpflichtende-bedingungen)
      - [3. Urheberrecht](#3-urheberrecht)
      - [4. Gewährleistungsausschluss und Haftungsbeschränkung](#4-gewährleistungsausschluss-und-haftungsbeschränkung)

## 1. Einführung und Designphilosophie

### Das Problem mit der Standard C API von SA-MP

Die SA-MP Plugin API ist eine C-Programmierschnittstelle. Obwohl funktional und fundamental, stellt sie die Herausforderungen der Low-Level-Programmierung dar:
- **Manuelle Speicherverwaltung:** Funktionen wie `amx_Allot` und `amx_Release` erfordern, dass der Entwickler den Speicher im AMX-Heap explizit zuweist und freigibt. Dies ist eine häufige Ursache für Speicherlecks und Laufzeitfehler.
- **Schwache Typisierung und manuelle Konvertierungen:** Parameter werden als `cell`-Array übergeben, was explizite (und oft unsichere) Konvertierungen zwischen `cell`, `int`, `float` und `char*` erzwingt.
- **Redundanz und Boilerplate:** Das Extrahieren mehrerer Parameter aus einem `cell* params`-Array, das Verwalten von Stringlängen und das Verwalten des AMX-Stacks für C++ zu Pawn-Rückrufen erfordert sich wiederholenden Code.
- **Fragilität der Schnittstelle:** Das Fehlen einer Kompilierzeitprüfung (Typsicherheit) bedeutet, dass Fehler bei der Parameterübergabe oder bei Typen bis zur Ausführung unbemerkt bleiben können, was zu Abstürzen oder undefiniertem Verhalten führt.

### Die Lösung des SA-MP SDK: Abstraktion mit Sicherheit und Performance

Das SA-MP SDK begegnet diesen Problemen, indem es eine leistungsstarke Abstraktionsebene in C++ bereitstellt:
- **RAII (Resource Acquisition Is Initialization):** Automatische Speicherverwaltung in der AMX. `Amx_Scoped_Memory` stellt sicher, dass der zugewiesene Speicher freigegeben wird.
- **Typsicherheit:** Automatische und sichere Konvertierung von Parametern zwischen C++ und Pawn. Sie arbeiten direkt mit `int`, `float`, `std::string`.
- **Prägnante und idiomatisches Syntax:** Makros und Templates bieten eine saubere API, die dem modernen C++ ähnlicher ist als der traditionellen C-API.
- **Robuste Abfangung:** Ein fortschrittlicher Hooking-Engine ermöglicht das transparente Abfangen von Pawn-Rückrufen (`Plugin_Public`), die Erstellung neuer Natives (`Plugin_Native`) und **das Hooking und Verkettung von vorhandenen SA-MP Natives (`Plugin_Native_Hook`)**.
- **Hohe Performance:** Umfangreiche Nutzung von Kompilierzeit-Hashing (FNV1a), Funktions-Caching und `thread_local`-Optimierungen, um den Overhead der Abstraktionen zu minimieren.

### Header-Only Modell: Vorteile und Implikationen

Das SDK besteht ausschließlich aus Header-Dateien (`.hpp`, `.h`).
- **Vorteile:**
   - **Vereinfachte Integration:** Es gibt keine Bibliotheken zum Erstellen, Verknüpfen oder Verteilen. Einfach die Header einbinden.
   - **Compileroptimierungen:** Der Compiler hat vollständigen Einblick in den SDK-Code und Ihr Plugin, was aggressives Inlining und Link-Time-Optimierungen ermöglicht, was zu schnelleren Binärdateien führen kann.
- **Implikationen:**
   - **Kompilierzeit:** Bei sehr großen Projekten kann die Kompilierung aufgrund der wiederholten Einbindung des SDK-Codes länger dauern. Dies wird durch Include-Guards und die "include nur das, was nötig ist"-Natur von C++ gemildert.
   - **Implementierungsmakros:** Die Notwendigkeit des Makros `SAMP_SDK_IMPLEMENTATION` ist eine Folge des Header-Only-Modells, um Symbol-Neudefinitionen zu vermeiden.

## 2. Konfiguration und Umgebung

### Kompilierungsanforderungen

- **C++-Compiler:** Kompatibel mit C++14 oder höher (das SDK verwendet Funktionen von C++14, C++17 und C++20 für spezifische Optimierungen, aber C++14 ist das Minimum).
   - GCC (Version 7+)
   - Clang (Version 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Architektur:** **x86 (32-bit)**. SA-MP läuft ausschließlich auf dieser Architektur. Das SDK enthält Überprüfungen in `platform.hpp`, die Kompilierungsfehler auslösen, wenn die falsche Architektur erkannt wird.
- **Betriebssystem:** Windows oder Linux.

### Empfohlene Dateistruktur

Zur Klarheit und Organisation ist es üblich, das SDK in einem Unterordner `samp-sdk` zu organisieren.

```
my_plugin/
├── samp-sdk/
│   ├── // Other SDK files
│   └── samp_sdk.hpp             // The main header to include
│
├── src/
│   ├── main.cpp                  // Where SAMP_SDK_IMPLEMENTATION is defined
│   └── my_custom_logic.cpp       // Optional, to organize code
│
└── CMakeLists.txt (or .vcxproj, Makefile)
```

### Wesentliche Konfigurationsmakros

Definieren Sie diese Makros immer *bevor* Sie `samp_sdk.hpp` inkludieren.

#### `SAMP_SDK_IMPLEMENTATION`

- **Zweck:** Signalisiert dem Compiler, dass diese `.cpp`-Datei die Implementierungen der Plugin-Exportfunktionen (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`) generieren soll. **Das SDK übernimmt das automatische Exportieren dieser Funktionen, wodurch die Notwendigkeit von `.def`-Dateien (unter Windows) oder `__attribute__((visibility("default")))`-Deklarationen (unter Linux) für diese Funktionen entfällt.**
- **Technischer Einfluss:** Ohne dieses Makro findet der Linker die erforderlichen Exporte nicht, und der SA-MP-Server kann Ihr Plugin nicht laden.
- **Grundregel:** **Definieren Sie dieses Makro in NUR EINER `.cpp`-Datei in Ihrem gesamten Projekt.** Das Definieren in mehreren Dateien führt zu einem "duplizierten Symbol"-Linkerfehler.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // The macro makes the SDK export the necessary functions automatically.
#include "samp-sdk/samp_sdk.hpp"

// ... your plugin code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Zweck:** Aktiviert die Pawn-Script-Lebenszyklus-Callbacks (`OnAmxLoad`, `OnAmxUnload`) und die Funktionalität, neue Natives in C++ zu erstellen (`Plugin_Native`).
- **Aktivierte Funktionalitäten:**
   - Callbacks `OnAmxLoad(AMX* amx)` und `OnAmxUnload(AMX* amx)`.
   - Deklaration und Registrierung neuer C++-Natives mit `Plugin_Native`.
   - Das Makro `Plugin_Call` zum Aufrufen von mit `Plugin_Native` erstellten Natives innerhalb Ihres eigenen Plugins.
- **Technischer Einfluss:** Wenn dieses Makro definiert ist, sammelt das SDK automatisch alle Ihre `Plugin_Native`s. In der Funktion `Supports()` wird das Flag `SUPPORTS_AMX_NATIVES` automatisch hinzugefügt, wenn in Ihrem Projekt `Plugin_Native`s vorhanden sind.
- **Flexibilität:** **Sie können dieses Makro in mehreren `.cpp`-Dateien definieren.** Das statische Registrierungssystem des SDK konsolidiert alle Natives aus verschiedenen Kompilierungseinheiten in einer einzigen globalen Liste.

```cpp
// my_natives.cpp (can be a separate file from main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Only to enable Plugin_Native and the OnAmxLoad/OnAmxUnload callbacks
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Zweck:** Aktiviert den Callback `OnProcessTick()`, der regelmäßig vom Server aufgerufen wird.
- **Technischer Einfluss:** Fügt das Flag `SUPPORTS_PROCESS_TICK` automatisch der Funktion `Supports()` hinzu.

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

### SA-MP Definitionen und Konstanten (`samp_defs.hpp`)

Diese Datei stellt alle bekannten SA-MP-Konstanten und -Grenzwerte bereit, wie z.B. `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST` usw. Sie wird automatisch von `samp_sdk.hpp` eingebunden und sollte verwendet werden, um die Kompatibilität und Lesbarkeit des Codes zu gewährleisten.

## 3. Umfassende API-Nutzungsanleitung

### 3.1. Der Plugin-Lebenszyklus

Die folgenden Funktionen sind die Einstiegs- und Ausstiegspunkte Ihres Plugins, die vom SDK automatisch exportiert werden.

#### `bool OnLoad()`

- **Beschreibung:** Erste Funktion, die vom SA-MP-Server nach erfolgreichem Laden Ihres Plugins in den Speicher aufgerufen wird.
- **Verwendung:** Ideal zum Initialisieren von Systemen, Laden von Konfigurationen, Öffnen von Datenbankverbindungen oder Laden von Modulen (`Plugin_Module`).
- **Rückgabe:**
   - `true`: Das Plugin wurde erfolgreich initialisiert und der Ladevorgang wird fortgesetzt.
   - `false`: Das Plugin konnte nicht initialisiert werden. Der Ladevorgang wird abgebrochen und das Plugin entladen.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Example: Load a module (more details in section 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database Module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load database module!");

        return false; // Aborts the main plugin loading
    }

    return true;
}
```

#### `void OnUnload()`

- **Beschreibung:** Letzte Funktion, die vom SA-MP-Server vor dem Entladen Ihres Plugins aus dem Speicher aufgerufen wird.
- **Verwendung:** Ideal zum Bereinigen von Ressourcen, Schließen von Verbindungen, Speichern von Zuständen und Sicherstellen, dass keine Ressourcen verloren gehen. Das SDK verwaltet das Entladen von Modulen (`Plugin_Module`) automatisch.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // No manual action is needed for modules loaded via Plugin_Module;
    // the SDK handles this.
}
```

#### `unsigned int GetSupportFlags()`

- **Beschreibung:** Informiert den SA-MP-Server, welche Funktionen Ihr Plugin unterstützt und verwenden möchte.
- **Verwendung:** **Geben Sie immer `SUPPORTS_VERSION` (oder `SAMP_PLUGIN_VERSION`) zurück.** Die Flags `SUPPORTS_AMX_NATIVES` und `SUPPORTS_PROCESS_TICK` werden vom SDK automatisch hinzugefügt, wenn `Plugin_Native`s vorhanden sind und/oder wenn das Makro `SAMP_SDK_WANT_PROCESS_TICK` definiert ist. Dies vereinfacht die Wartung und vermeidet Fehler.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // The SDK adds the necessary flags automatically.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Erfordert:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beschreibung:** Wird immer aufgerufen, wenn ein neues Pawn-Skript (ein Gamemode oder Filterscript) auf dem Server geladen und initialisiert wird.
- **Verwendung:** Wenn Sie spezifische Logik für jedes AMX-Skript benötigen oder skriptspezifische Daten initialisieren möchten.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxLoad(AMX* amx) {
    // amx represents the new loaded script instance.
    Samp_SDK::Log("AMX script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Erfordert:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beschreibung:** Wird aufgerufen, wenn ein Pawn-Skript vom Server entladen wird.
- **Verwendung:** Zum Bereinigen von spezifischen Ressourcen, die Sie diesem bestimmten `AMX*` zugewiesen oder zugeordnet haben.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Erfordert:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Beschreibung:** Wird wiederholt bei jedem "Tick" des Servers aufgerufen (normalerweise 20 Mal pro Sekunde, oder alle 50 ms).
- **Verwendung:** Für kontinuierliche Hintergrundlogik, Timer, Statusaktualisierungen, die nicht von Spielerereignissen abhängen, oder Datensynchronisation.
- **Vorsicht:** Vermeiden Sie hier blockierende oder rechenintensive Operationen, da diese den Server verlangsamen können.

```cpp
// main.cpp (with SAMP_SDK_WANT_PROCESS_TICK defined)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Every 10 seconds (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Abfangen von Pawn-Events

Das Makro `Plugin_Public` ist die primäre Brücke, um Pawn-Callbacks in Ihrem C++-Code zu empfangen.

#### Syntax und Deklaration

- `Plugin_Public(PublicName, Type1 Param1, Type2 Param2, ...)`
- Der Name der von Ihnen deklarierten C++-Funktion **muss identisch sein** mit dem Pawn-Callback (z.B. `OnPlayerConnect`).
- Die C++-Parametertypen (`int`, `float`, `std::string`) werden vom SDK automatisch konvertiert.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Player %d said: %s", playerid, text.c_str());

    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Automatische Parameter-Marshalling

Das SDK übernimmt automatisch das Lesen des `cell stack` der AMX und die Konvertierung in die angegebenen C++-Typen:
- `int`: Direkt von `cell` konvertiert.
- `float`: Von `cell` mit `amx::AMX_CTOF` konvertiert.
- `std::string`: Das SDK liest die Stringadresse in der AMX, weist einen `std::string` in C++ zu und kopiert den Inhalt.

#### Flusskontrolle: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

Der von Ihrer `Plugin_Public`-Funktion zurückgegebene Wert ist entscheidend und bestimmt den Ausführungsfluss des Callbacks:
- `return PLUGIN_PUBLIC_CONTINUE;` (Wert `1`): Zeigt an, dass die Ausführung des Callbacks **fortgesetzt** werden soll. Wenn andere Plugins diesen Callback ebenfalls abfangen, werden sie aufgerufen (in umgekehrter Ladereihenfolge). Anschließend wird die ursprüngliche `public` im Pawn-Skript aufgerufen.
- `return PLUGIN_PUBLIC_STOP;` (Wert `0`): Zeigt an, dass die Ausführung des Callbacks **unterbrochen** werden soll. Kein weiteres Plugin (mit geringerer Priorität) oder die ursprüngliche `public` im Pawn-Skript wird für dieses Ereignis aufgerufen. Dies ist ideal, um ein System zu implementieren, das ein Standardverhalten von SA-MP "überschreibt" oder "blockiert".

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

#### Ghost Callbacks

Eine erweiterte Funktion von `Plugin_Public` ist die Unterstützung von "Ghost Callbacks". Dies bedeutet, dass Sie einen Pawn-Callback abfangen können, selbst wenn er **nicht** im `.amx`-Skript des Gamemodes oder Filterscripts vorhanden ist. Das SDK "täuscht" den Server, damit er Ihren C++-Hook trotzdem aufruft. Dies ist nützlich für interne Callbacks oder um neue Funktionen zu erstellen, ohne von der Anwesenheit einer `public` im Pawn-Skript abzuhängen.

```cpp
// You can define a callback that the Pawn script doesn't have, but your plugin will hear it.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Custom internal event received: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// To "trigger" this event from another point in your C++ code:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// The call will go to your Plugin_Public above, even if there is no OnMyCustomInternalEvent in Pawn.
```

### 3.3. `Plugin_Native`: Erstellen von nativen C++-Funktionen

`Plugin_Native` ermöglicht es Ihnen, die Funktionalität von Pawn mit hochperformantem C++-Code zu erweitern.

#### Syntax und feste Signatur

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- Die C++-Funktion muss genau diese Signatur haben: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` ist der Name, den die Pawn-Skripte verwenden werden.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementation ...
    return 0;
}
```

#### Automatische Native-Registrierung

> [!NOTE]
> Sie müssen `amx_Register` **nicht** manuell aufrufen. Das SDK erkennt alle Ihre `Plugin_Native`s (in jeder `.cpp`-Datei, die `samp_sdk.hpp` eingebunden und `SAMP_SDK_WANT_AMX_EVENTS` definiert hat) und registriert sie automatisch in jedem geladenen AMX-Skript (`OnAmxLoad`).

#### Parameter-Extraktion: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Beschreibung:** Einfacherer Helfer zum sequenziellen Extrahieren mehrerer Parameter.
- **Verwendung:** `Register_Parameters(variable1, variable2, ...)`
- **Einschränkungen:** Für Eingabeparameter. Behandelt keine optionalen Parameter oder den Zugriff per Index.
- **Unterstützte Typen:** `int`, `float`, `std::string`.

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

##### `Native_Params` (Vollständige API: `Get`, `Get_REF`, `Set_REF`)

- **Beschreibung:** Eine Wrapper-Klasse, die eine objektorientierte Schnittstelle für den Zugriff auf die Parameter einer Native bereitstellt. Leistungsfähiger für komplexe Szenarien.
- **Konstruktion:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Beschreibung:** Gibt die Anzahl der an die Native übergebenen Parameter zurück.
- **Verwendung:** Wesentlich für den Umgang mit optionalen Parametern.

###### `p.Get<T>(size_t index)`

- **Beschreibung:** Extrahiert einen Eingabeparameter per Index und konvertiert ihn in den Typ `T`.
- **Unterstützte Typen:** `int`, `float`, `std::string`.

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

- **Beschreibung:** Ruft den Wert eines **Referenzparameters** (Pawn-Zeiger) ab und speichert ihn in `out_value`.
- **Verwendung:** Zum Lesen von Werten, die als Referenz von Pawn übergeben wurden.
- **Rückgabe:** `true`, wenn die AMX-Adresse gültig ist, `false` sonst.

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
    
    // And writes them back to Pawn's memory
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Beschreibung:** Gibt ein `std::optional<T>` zurück, um einen Referenzparameter zu lesen. Sicherer für C++17 und höher.

###### `p.Set_REF<T>(size_t index, T value)`

- **Beschreibung:** Schreibt einen Wert `T` in einen Pawn-**Referenzparameter** (die Adresse, die Pawn übergeben hat).
- **Verwendung:** Zum Ändern von Werten, die als Referenz übergeben wurden, sodass Pawn die Änderung sieht.
- **Rückgabe:** `true`, wenn das Schreiben erfolgreich war, `false` sonst.

#### Rückgabewerte

- Ihre `Plugin_Native`-Funktion muss eine `cell` zurückgeben.
- Um einen `int` oder `bool` zurückzugeben, verwenden Sie einen Cast zu `cell`.
- Um einen `float` zurückzugeben, verwenden Sie `amx::AMX_FTOC(my_float)`.

```cpp
// Returns a bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Returns a float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Returns 100.0f
}
```

### 3.4. `Plugin_Native_Hook`: Abfangen von vorhandenen SA-MP-Natives

Das Makro `Plugin_Native_Hook` ermöglicht es Ihnen, das Verhalten jeder vorhandenen SA-MP-Native-Funktion oder von Natives anderer Plugins abzufangen und zu modifizieren. Dies ist ein leistungsstarker Mechanismus, um die Standardlogik des Servers zu erweitern oder zu ändern.

#### Syntax und feste Signatur

- `Plugin_Native_Hook(NativeName, AMX* amx, cell* params)`
- Die C++-Funktion muss genau diese Signatur haben: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` muss der genaue Name der Native sein, die Sie hooken möchten (z.B. `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepts the SendClientMessage native
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Important to call the original
}
```

#### Hook-Registrierung und -Aktivierung

> [!NOTE]
> Sie müssen `amx_Register` **nicht** manuell aufrufen oder `SAMP_SDK_WANT_AMX_EVENTS` speziell für `Plugin_Native_Hook` definieren. Das SDK erkennt und registriert Ihre Hooks automatisch. Bei der ersten Ausführung eines AMX-Skripts ersetzt das SDK den Native-Zeiger in der Tabelle durch ein "Trampolin", das zu Ihrer `Plugin_Native_Hook`-Funktion umleitet. Dieser Prozess gewährleistet die sichere Verkettung von Hooks mehrerer Plugins.

#### Aufruf der originalen Native (Hook-Kette): `Call_Original_Native`

Innerhalb Ihrer `Plugin_Native_Hook`-Funktion **MÜSSEN** Sie das Makro `Call_Original_Native(NativeName)` verwenden, um die Originalfunktion (oder den nächsten Hook in der Kette) aufzurufen. Dies ist entscheidend, um:
- **Funktionalität zu bewahren:** Wenn Sie die Originalfunktion nicht aufrufen, funktioniert die gehookte Native einfach nicht mehr für andere Plugins oder den Server.
- **Hook-Kettung:** Ermöglicht es mehreren Plugins, dieselbe Native zu hooken, und stellt sicher, dass alle Hooks in einer Sequenz ausgeführt werden.
- **Rückgabewertmanipulation:** Sie können den Rückgabewert von `Call_Original_Native` überprüfen und sogar ändern, bevor Sie ihn aus Ihrer Hook-Funktion zurückgeben.

```cpp
// Example: Blocking SendClientMessage if it contains a specific word
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extracts the parameters for analysis
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // We don't need the color for this logic
    std::string message = p.Get_String(2); // Gets the message string

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGE BLOCKED for playerid %d: %s", playerid, message.c_str());

        return 0; // Returns 0 (false) to Pawn, indicating the message was not sent.
                  // And more importantly, we DO NOT call Call_Original_Native, blocking the message.
    }

    // If the message does not contain the forbidden word, we call the original native
    // and return its value, ensuring the message is sent normally
    // and that other hooks (if any) are executed.
    return Call_Original_Native(SendClientMessage);
}
```

#### Vollständiges Beispiel für `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS is not strictly necessary for hooks, but common for OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook for the CreateVehicle native
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extracts the CreateVehicle native parameters for inspection
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

    // Example of how to *modify* an input parameter
    // If the model is 400 (Landstalker), we change it to 401 (Bravura)
    if (modelid == 400) {
        // We directly modify the 'params' array for the original call
        params[1] = static_cast<cell>(401); // The model is at position 0 in the parameter array (params[1])
        Samp_SDK::Log("  -> Model 400 changed to 401 before creation.");
    }
    
    // We call the original native (or the next hook in the chain) with the possibly modified parameters
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle returned: %d (Vehicle ID)", (int)original_retval);

    // You can modify the return value here before returning it to Pawn.
    // Example: if vehicle creation failed, return a custom invalid ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Vehicle creation failed in original native.");

        return -1; // Returns a different value to Pawn.
    }

    return original_retval; // Returns the value that the original native returned (or the modified one above).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Minimal implementations for the lifecycle
bool OnLoad() {
    Samp_SDK::Log("Native Hook Example Plugin loaded!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Native Hook Example Plugin unloaded!");
}

// These callbacks will only be present if SAMP_SDK_WANT_AMX_EVENTS is defined
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detected: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detected: %p", (void*)amx);
}*/
```
> [!WARNING]
> Die direkte Manipulation des `cell* params`-Arrays zur Änderung von Eingabeparametern erfordert Vorsicht. Stellen Sie sicher, dass Sie die Reihenfolge und den Typ der Parameter verstehen. Für die meisten Anwendungsfälle reicht `p.Get(...)` zur Inspektion und `Call_Original_Native(...)` zur Fortsetzung der Kette aus. Die direkte Änderung von `params` sollte nur erfolgen, wenn Sie wissen, dass der Parameter ein Wert ist und für den ursprünglichen Aufruf geändert werden muss. Bei Strings und Arrays ist die Änderung komplexer und beinhaltet in der Regel `amx::Set_String`, um in die vorhandene Adresse zu schreiben oder neu zuzuweisen, was einfacher zu handhaben sein kann, indem die Native über `Pawn_Native` mit den neuen Werten aufgerufen und `0` von Ihrem Hook zurückgegeben wird, um den ursprünglichen Aufruf abzubrechen.

### 3.5. `Pawn_*` Makros: Aufrufen von Pawn-Funktionen aus C++

Diese Makros sind das Gegenteil von `Plugin_Public` und `Plugin_Native`: Sie ermöglichen es Ihrem C++-Code, Pawn-Funktionen aufzurufen.

#### `Pawn_Native(NativeName, ...)`

- **Zweck:** Die empfohlene Methode, SA-MP Native-Funktionen (oder die anderer Plugins) aus C++ aufzurufen.
- **Mechanismus:** Sucht den Zeiger der Native im internen Cache des SDK (gefüllt durch `Amx_Register_Detour`). Falls gefunden, führt es die Native in einer `Amx_Sandbox`-Umgebung (einer gefälschten und isolierten AMX-Instanz) aus.
- **Performance:** Am effizientesten, da es die teure Suche nach `publics` vermeidet und direkt mit dem Native-Zeiger interagiert.

#### `Pawn_Public(PublicName, ...)`

- **Zweck:** Ruft eine bestimmte öffentliche Funktion in einem Pawn-Skript auf.
- **Mechanismus:** Durchläuft die vom `Amx_Manager` verwalteten `AMX*`-Instanzen, sucht die `public` nach Namen und führt sie aus.
- **Performance:** Weniger effizient als `Pawn_Native` aufgrund der Suche und des tatsächlichen `amx_Exec`. Im Allgemeinen sind `publics` langsamer als `natives`.
- **Verwendung:** Ideal zum Aufrufen benutzerdefinierter Ereignisse in Ihren Gamemodes/Filterscripts, die keine Natives sind.

#### `Pawn(FunctionName, ...)`

- **Zweck:** Ein Komfortmakro, das versucht zu erraten, ob die Funktion eine Native oder eine Public ist.
- **Mechanismus:** Versucht zunächst, als `Pawn_Native` aufzurufen. Wenn dies fehlschlägt (die Native wird nicht gefunden), versucht es, als `Pawn_Public` aufzurufen.
- **Performance:** Kann etwas langsamer sein als `Pawn_Native`, wenn die Funktion eine Native ist, aufgrund des doppelten Suchversuchs. Für `publics` ist die Leistung die gleiche wie bei `Pawn_Public`.
- **Verwendung:** Für Funktionen, bei denen Sie nicht sicher sind, ob sie Natives oder Publics sind, oder um den Boilerplate-Code zu vermeiden, zuerst eine und dann die andere zu versuchen.

#### Syntax und Konventionen

- **Funktionsname:** Verwenden Sie immer den Pawn-Funktionsnamen **direkt, ohne Anführungszeichen**. Das SDK konvertiert ihn intern in einen String.
- **Parameter:** Übergeben Sie die C++-Parameter direkt.

```cpp
// Correct:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Wrong (but would technically work due to hashing, avoid):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling von Eingabeparametern

Das SDK konvertiert Ihre C++-Typen in das `cell`-Format der AMX und verwaltet dabei den Speicher nach Bedarf:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (mittels `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (weist Speicher in der AMX zu, kopiert den String und übergibt die Adresse `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling von Ausgabeparametern (Referenzen: `int&`, `float&`, `std::string&`)

Dies ist eine Schlüsselfunktionalität für Bequemlichkeit und Sicherheit. Für Pawn-Funktionen, die einen Zeiger (Referenz) erwarten, automatisiert das SDK den gesamten Prozess der Speicherzuweisung/-freigabe und Datenkopie.

- **Verwendung:** Übergeben Sie Ihre Variable einfach als Referenz (`&`).
- **Mechanismus:** Das SDK weist Speicher im AMX-Heap zu, übergibt die AMX-Adresse an die Pawn-Funktion, wartet darauf, dass die Pawn-Funktion diese Adresse füllt, liest den Wert zurück und gibt den AMX-Speicher frei. Alles transparent.
- **Mit `std::string&`:** Das SDK weist einen Standardpuffer (256 Zellen) in der AMX für den String zu.

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

#### Das `Callback_Result`-Objekt: Vollständige Analyse

Alle `Pawn_*`-Aufrufe geben ein `Callback_Result`-Objekt zurück. Dieses Objekt ist ein sicherer Wrapper für das Ergebnis des Pawn-Aufrufs.

- `Callback_Result() noexcept`: Standardkonstruktor, zeigt Fehlschlag an (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Konstruktor für Erfolg oder Fehlschlag mit Wert.
- `explicit operator bool() const`: Ermöglicht die Verwendung von `if (result)`, um zu überprüfen, ob der Aufruf erfolgreich war.
- `operator cell() const`: Ermöglicht die Konvertierung des Ergebnisses in `cell`, um den Wert zu erhalten.
- `float As_Float() const`: Bequemlichkeit, um das Ergebnis als `float` zu erhalten.
- `cell Value() const`: Gibt den Rohwert `cell` zurück.
- `bool Success() const`: Gibt `true` zurück, wenn der Pawn-Aufruf erfolgreich war.
- `int Get_Amx_Error() const`: Gibt den AMX-Fehlercode zurück, wenn der Aufruf fehlgeschlagen ist (0 für Erfolg).

```cpp
// Example: Getting a player's health.
// The native GetPlayerHealth(playerid, &Float:health) expects a playerid and a reference to health.
int playerid = 0; // Example player ID
float player_health = 0.0f;

// We call GetPlayerHealth, passing playerid and player_health by reference.
// The SDK will handle the marshalling for the 'health' output parameter.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Checks if the call was successful (operator bool)
    // The value returned by result.As_Float() or result (operator cell)
    // would be the return value of the *native*, not the output parameter.
    // The health value has already been updated in 'player_health' due to output parameter marshalling.
    Samp_SDK::Log("Player %d has %.1f health.", playerid, player_health);
}
else {
    // The call failed, perhaps the player does not exist or the native was not found.
    Samp_SDK::Log("Error getting player %d health. AMX code: %d", playerid, result.Get_Amx_Error());
}

// For natives that return a value and use output parameters (less common, but possible),
// you would use both:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param is already updated
// }
```

### 3.6. `Plugin_Module`: Dynamische Modulverwaltung

Das Makro `Plugin_Module` ermöglicht es Ihrem Plugin, als "Lader" für andere Plugins zu fungieren, wodurch eine modulare und erweiterbare Architektur entsteht. Ein auf diese Weise geladenes Modul wird als erstklassiges Plugin behandelt, mit einem eigenen Ereignislebenszyklus, der vom Host-Plugin verwaltet wird.

#### Syntax und Zweck

- `Plugin_Module(const char* base_filename, const char* module_directory, const char* optional_success_message)`
- `base_filename`: Der *Basisname* der Moduldatei **ohne Dateierweiterung** (z.B. für `my_module.dll` oder `my_module.so` verwenden Sie `"my_module"`). Das SDK fügt automatisch die entsprechende `.dll`- oder `.so`-Erweiterung hinzu.
- `module_directory`: Der Pfad des Verzeichnisses, in dem sich die Moduldatei befindet (z.B. `"plugins/my_custom_modules"`). **Fügen Sie den Dateinamen hier nicht ein.** Das SDK erstellt den vollständigen Pfad (`module_directory/base_filename.ext`).
- `optional_success_message`: Eine optionale Nachricht, die in der Serverkonsole protokolliert wird, wenn das Modul erfolgreich geladen wurde.

```cpp
// main.cpp, inside OnLoad()

// Loads the 'core_logic.dll' (or 'core_logic.so') module
// which is located in the 'modules/custom/' folder of the server.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic Module loaded successfully!"))
    return (Samp_SDK::Log("FATAL ERROR: Failed to load 'core_logic' module!"), false);

// Loads the 'admin_system.dll' (or 'admin_system.so') module
// which is located directly in the 'plugins/' folder of the server.
if (!Plugin_Module("admin_system", "plugins", "Administration Module activated."))
    Samp_SDK::Log("WARNING: Administration Module could not be loaded.");
```

#### Lebenszyklus eines Moduls

Ein Modul muss die Funktionen `Load`, `Unload` und `Supports` exportieren, genau wie ein normales Plugin. Das SDK verwaltet den Lebenszyklus des Moduls wie folgt:

- **Laden:** Wenn `Plugin_Module` aufgerufen wird, führt das SDK Folgendes aus:
   1. Erstellt den vollständigen Dateipfad (z.B. `modules/custom/core_logic.dll`).
   2. Verwendet `Dynamic_Library` (`LoadLibrary`/`dlopen`), um die Binärdatei zu laden.
   3. **Ruft die Zeiger für ALLE Lebenszyklusfunktionen des Moduls ab:**
      - **Erforderlich:** `Load`, `Unload`, `Supports`. Wenn eine fehlt, schlägt das Laden des Moduls fehl.
      - **Optional:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Ruft die `Load`-Funktion des Moduls auf und übergibt `ppData` des Hauptplugins.
   5. Wenn `Load` `true` zurückgibt, wird das Modul zur internen Liste der geladenen Module hinzugefügt.

- **Ereignisweiterleitung:** Das Host-Plugin **leitet Ereignisse automatisch** an alle geladenen Module weiter.
 > [!IMPORTANT]
 > Damit die Ereignisse korrekt weitergeleitet werden, muss das **Host-Plugin** (das `Plugin_Module` aufruft) für den Empfang dieser Ereignisse konfiguriert sein.
 > - Damit `AmxLoad` und `AmxUnload` in den Modulen funktionieren, muss das Host-Plugin das Makro `SAMP_SDK_WANT_AMX_EVENTS` definieren.
 > - Damit `ProcessTick` in den Modulen funktioniert, muss das Host-Plugin das Makro `SAMP_SDK_WANT_PROCESS_TICK` definieren.

- **Entladen:** Während des `OnUnload` Ihres Hauptplugins entlädt das SDK alle Module, die über `Plugin_Module` geladen wurden. Dies geschieht in **umgekehrter Reihenfolge** zum Laden (das zuletzt geladene wird zuerst entladen), was entscheidend ist, um Abhängigkeiten zu verwalten und die korrekte Freigabe von Ressourcen zu gewährleisten.

#### Vorteile der Modularisierung

- **Code-Organisation:** Teilen Sie große Plugins in kleinere, überschaubare Komponenten auf, jede in einer eigenen Moduldatei.
- **Wiederverwendbarkeit:** Erstellen Sie generische Module (z.B. ein Datenbankmodul, ein erweitertes Protokollsystemmodul), die von verschiedenen Plugins verwendet werden können, und fördern Sie so die Code-Wiederverwendung.
- **Unabhängige Komponenten:** Erstellen Sie Module, die **vollständig ereignisgesteuert und unabhängig sind**. Ein Modul kann eigene `Plugin_Native`s haben, `Plugin_Public`s abfangen und eine eigene `OnProcessTick`-Logik haben, die wie ein eigenständiges Plugin funktioniert, aber von einem Host geladen wird.
- **Dynamische Updates:** In kontrollierten Szenarien ermöglicht dies die Aktualisierung von Teilen Ihres Systems (Ersetzen einer `.dll`- oder `.so`-Moduldatei), ohne das Hauptplugin oder den gesamten Server neu kompilieren und neu starten zu müssen (obwohl dies ein strenges Versions- und Kompatibilitätsmanagement erfordert).

### 3.7. `Plugin_Call`: Aufrufen interner Plugin-Natives

Verwenden Sie `Plugin_Call`, um eine `Plugin_Native` aufzurufen, die **innerhalb Ihres eigenen Plugins** definiert ist.

#### Syntax und Performance-Vorteile

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Vorteil:** Vermeidet den Overhead, die Native im AMX-Native-Array zu suchen. Das SDK verwaltet eine direkte Zuordnung von Namens-Hashes zu Funktionszeigern für Ihre eigenen Natives, was dies zur schnellsten Methode macht, sie intern aufzurufen.
- **Erfordert:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logic to check the level
    return (playerid % 2 == 0) ? 1 : 0; // Example: even level for even IDs
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Calls your own native
                Samp_SDK::Log("Player %d is at a high level!", i);
        }
    }
}
```

### 3.8. SDK-Utility-Funktionen

#### `Samp_SDK::Log(const char* format, ...)`

- **Beschreibung:** Gibt Meldungen in der Serverkonsole und in der Datei `server_log.txt` aus. Ein sicherer Wrapper für `logprintf`.
- **Verwendung:** Zum Debuggen, für Statusmeldungen und Fehler.
- **Mechanismus:** Intern ruft das SDK den Zeiger auf `logprintf` über `ppData[PLUGIN_DATA_LOGPRINTF]` ab. Die Funktion handhabt die Formatierung des Strings auf sichere Weise.

```cpp
// Anywhere in your plugin
Samp_SDK::Log("The plugin was initialized with a value %d and a string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Empfohlen)

- **Beschreibung:** Formatiert einen String sicher (ähnlich wie `sprintf`) und gibt einen `std::string` zurück. Dies ist die **empfohlene und idiomatischste** Methode, Strings zur Verwendung innerhalb Ihres Plugins zu formatieren.
- **Verwendung:** Ideal zum Erstellen formatierter Nachrichten, bevor sie an `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, oder für andere String-Anforderungen in Ihrem C++-Code übergeben werden.
- **Mechanismus:** Intern ist `Plugin_Format` ein Makro, das `Samp_SDK::Format` aufruft. Es verwendet `vsnprintf`, um die genaue Größe des formatierten Strings zu bestimmen und weist einen `std::string` mit ausreichender Kapazität zu, wodurch Pufferüberläufe vermieden werden.

```cpp
int playerid = 0; // Example ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Player %d, your current health is %d.", playerid, health));

// Can also be used for internal logs
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Implementierungsdetail)

- **Beschreibung:** Die zugrunde liegende Implementierungsfunktion für die Stringformatierung, die sich im `Samp_SDK`-Namespace befindet.
- **Verwendung:** Wird in der Regel nicht direkt vom Benutzer aufgerufen. Das Makro `Plugin_Format` wird als Komfort für diese Funktion bereitgestellt, um sich an die Namenskonventionen anderer SDK-Makros (`Plugin_Public`, `Plugin_Native`) anzupassen. Sie würden es nur direkt aufrufen, wenn Sie das Makro `Plugin_Format` aus einem bestimmten Grund vermeiden möchten.

```cpp
// Example of how Samp_SDK::Format works, but prefer Plugin_Format
std::string raw_status = Samp_SDK::Format("For internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Beschreibung:** Konvertiert eine AMX-String-Adresse (`cell amx_addr`) in einen C++-`std::string`.
- **Verwendung:** Hauptsächlich innerhalb von `Plugin_Native` und `Plugin_Native_Hook`, wenn Sie auf Strings zugreifen müssen, die nicht automatisch von `Register_Parameters` oder `Native_Params` konvertiert werden (z.B. wenn der Pawn-Parameter ein `const` `string` ist und nicht als `std::string` in Ihrer `Plugin_Native` oder `Plugin_Public` für das automatische Marshalling deklariert wurde).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Gets the string address in AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String from AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Interne Anatomie und Architektur des SDK

Dieser Abschnitt enthüllt die zugrunde liegenden Mechanismen des SA-MP SDK, indem er seine Architektur, die Schlüsselkomponenten und deren Zusammenspiel zur Bereitstellung der High-Level-Abstraktion untersucht. Ein tiefes Verständnis dieser Interna ermöglicht es dem Entwickler, die Nutzung des SDK zu optimieren, komplexe Probleme zu debuggen und sogar dessen Funktionalitäten zu erweitern.

### 4.1. `core.hpp`: Das minimalistische Fundament

Die `Samp_SDK::Core` ist ein `Singleton`, das als anfänglicher und zentraler Zugriffspunkt zu den Low-Level-Daten dient, die von der SA-MP Plugin-Umgebung bereitgestellt werden. Ihre Hauptaufgabe ist es, die wesentlichen Funktionalitäten zu kapseln und offenzulegen.

- **`Samp_SDK::Core::Instance()`**:
   - **Beschreibung:** Gibt die einzige globale Instanz der `Core`-Klasse zurück. Dies ist ein `Singleton`-Entwurfsmuster, um sicherzustellen, dass der Zugriff auf die Plugin-Daten (`ppData`) konsistent und zentralisiert ist.
   - **Mechanismus:** Die Instanz wird einmalig initialisiert, wenn `Core::Instance().Load(ppData)` in der `Load()`-Funktion Ihres Plugins aufgerufen wird.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Beschreibung:** Ermöglicht sicheren und indizierten Zugriff auf die Funktionszeiger der AMX-API. Das Array `pAMXFunctions` (erhalten über `ppData[PLUGIN_DATA_AMX_EXPORTS]`) enthält die Adressen kritischer Funktionen wie `amx_Exec`, `amx_Register` usw.
   - **Impact:** Anstatt `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)` zu verwenden, bietet das SDK typsichere Wrapper im `amx::`-Namespace (z.B. `amx::Exec(...)`), wodurch der Code lesbarer und weniger fehleranfällig wird.
   - **Internes Beispiel (`amx_api.hpp`):**
      ```cpp
      // Simplified snippet from amx_api.hpp
      namespace amx {
          template <typename Func, int Index, typename... Args>
          inline auto Call(Args... args) -> decltype(std::declval<Func>()(args...)) {
              using Return_Type = decltype(std::declval<Func>()(args...));
              auto func_ptr = reinterpret_cast<Func>(Core::Instance().Get_AMX_Export(Index));

              if (SAMP_SDK_UNLIKELY(!func_ptr)) {
                  Log("[SA-MP SDK] Fatal: Attempted to call AMX export at index %d, but pAMXFunctions was not loaded!", Index);
                
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
   - **Beschreibung:** Ein Zeiger auf die SA-MP-Funktion `logprintf`, die die Standard-Schnittstelle zum Drucken von Nachrichten in der Serverkonsole und in `server_log.txt` ist.
   - **Mechanismus:** `Samp_SDK::Log` ist ein sicherer Wrapper, der diesen Zeiger verwendet und sicherstellt, dass Ihre Nachrichten in der SA-MP-Umgebung korrekt angezeigt werden.

### 4.2. `platform.hpp` und `version.hpp`: Kompatibilität und Metadaten

Diese Header sind die Grundlage für die Portabilität und Optimierung des SDK, indem sie es an verschiedene Kompilierungsumgebungen anpassen und spezifische Merkmale des modernen C++ nutzen.

- **Plattform- und Architekturerkennung:**
   - **Mechanismus:** Verwendet Präprozessor-Makros (`#if defined(WIN32)`, `#if defined(__linux__)` usw.), um das Betriebssystem zu identifizieren.
   - **Architekturprüfung:** Enthält `static_assert` oder `#error`, um sicherzustellen, dass das Plugin für x86 (32-Bit) kompiliert wird, eine kritische Anforderung für die Kompatibilität mit SA-MP und dem Hooking-Mechanismus.
   - **Verwaltung des Symbol-Exports:**
      - `SAMP_SDK_EXPORT`: Ein in `platform.hpp` definiertes Makro, das sich zu `extern "C"` erweitert und unter Linux `__attribute__((visibility("default")))` hinzufügt. Unter Windows stellt es lediglich `extern "C"` sicher, da das SDK `pragma comment(linker, "/EXPORT:...")` (für MSVC) oder den MinGW-Standard zum Exportieren der Hauptfunktionen verwendet.
      - Dies stellt sicher, dass die Lebenszyklusfunktionen des Plugins (`Supports`, `Load`, `Unload` usw.) unabhängig von der Kompilierungsumgebung korrekt aus Ihrer DLL/SO exportiert werden, **ohne dass `.def`-Dateien oder das manuelle Hinzufügen von `__attribute__((visibility("default")))`** in Ihrer Implementierung erforderlich sind.
   - **Beispiel (`platform.hpp` - relevanter Ausschnitt):**
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
   - **Beispiel (`samp_sdk.hpp` - relevanter Ausschnitt der Implementierung):**
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

      // Implementation of the exported functions
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... other functions ...
      #endif
      ```

- **Optimierungs- und Branch-Vorhersage-Makros:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mechanismus:** `__forceinline` (MSVC) oder `__attribute__((always_inline)) inline` (GCC/Clang). Schlägt dem Compiler dringend vor, den Funktionsrumpf direkt an der Aufrufstelle einzufügen, wodurch der Overhead eines tatsächlichen Funktionsaufrufs entfällt.
      - **Verwendung:** Wird auf kleine, performanzkritische Funktionen innerhalb des SDK angewendet.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mechanismus:** `[[likely]]` / `[[unlikely]]` (C++20) oder `__builtin_expect` (GCC/Clang). Hinweise an den Compiler, welcher Pfad eines `if/else` am wahrscheinlichsten genommen wird.
      - **Auswirkung:** Hilft dem Compiler, effizienteren Code für die Branch Prediction zu generieren, wodurch die CPU-Latenz reduziert wird.
      - **Beispiel (`platform.hpp`):**
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
   - **`SAMP_SDK_USED_BY_ASM`**:
      - **Mechanismus:** `__attribute__((used))` (GCC/Clang). Informiert den Compiler, dass ein Symbol (in diesem Fall eine Funktion) verwendet wird, auch wenn es keine Referenzen darauf im C++-Code gibt.
      - **Auswirkung:** Entscheidend für C++-Funktionen, die von eingebetteten Assembly-Blöcken (`asm volatile`) aufgerufen werden. Ohne dieses Attribut kann der Compiler-Optimierer die Funktion fälschlicherweise entfernen, was zu einem "undefined symbol"-Fehler im Linker führt.
      - **Beispiel (`platform.hpp`):**
         ```cpp
         #if defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
             #define SAMP_SDK_USED_BY_ASM __attribute__((used))
         #else
             #define SAMP_SDK_USED_BY_ASM
         #endif
         ```

- **Standard C++-Definitionen (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mechanismus:** Makros, die basierend auf dem Wert von `__cplusplus` und `_MSVC_LANG` definiert werden.
   - **Verwendung:** Ermöglichen es dem SDK, neuere C++-Funktionen (wie `std::apply` und `if constexpr` von C++17 oder `std::is_same_v` von C++17) zu verwenden, wenn verfügbar, während die Kompatibilität mit älteren Standards erhalten bleibt.
   - **Beispiel (`version.hpp` - Verwendung von `if constexpr`):**
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
                  // C++14 compatibility: use the helper function Assign_Parameter_By_Type
                  Assign_Parameter_By_Type(amx, &value, first); 
      #endif
          }

          Get_Public_Params_Recursive(amx, index + 1, rest...);
      }
      ```

### 4.3. `function_hook.hpp`: Der x86-Abfangmotor

Dieser Header definiert den Low-Level-Mechanismus zur Durchführung von Funktions-Hooks (Abfangen), der für den Betrieb des SDK von grundlegender Bedeutung ist. Er ist streng von der x86 (32-Bit)-Architektur abhängig.

- **`X86_Detour`**:
   - **Beschreibung:** Eine Klasse, die die Logik kapselt, den Anfang einer Funktion im Speicher mit einer Sprunganweisung zu einer Umleitungsfunktion zu überschreiben.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mechanismus:** Bei x86 hat die relative Sprunganweisung (`JMP`) typischerweise 5 Bytes: `0xE9` (Opcode für JMP near, relative), gefolgt von 4 Bytes, die den Offset der Zieladresse relativ zur nächsten Anweisung darstellen.
      - **Anweisungsbeispiel:** `E9 XX XX XX XX` (wobei `XX` die Offset-Bytes sind).
   - **`Apply(void* target, void* detour)`**:
      - **Aktion:** Installiert den Hook. Zuerst werden die `JUMP_INSTRUCTION_SIZE` Originalbytes der `target`-Funktion (`original_bytes_`) gespeichert. Anschließend wird die relative Adresse des `detour` in Bezug auf das `target` berechnet und der Anfang von `target` mit der `JMP`-Anweisung überschrieben.
      - **Beispiel für die Berechnung der relativen Adresse:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Address of detour - (Address of target + Size of JMP instruction)
         ```
   - **`Revert()`**:
      - **Aktion:** Deinstalliert den Hook und stellt die `original_bytes_` in der `target`-Funktion wieder her.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mechanismus:** Unter Windows wird `VirtualProtect` verwendet; unter Linux `mprotect`. Diese Systemaufrufe ändern die Berechtigungen der Speicherseite, auf der sich die Funktion befindet, auf `EXECUTE_READWRITE` (Windows) oder `PROT_WRITE | PROT_EXEC` (Linux), um die Codeänderung zur Laufzeit zu ermöglichen.
      - **Beispiel (`Unprotect_Memory`):**
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
   - **Beschreibung:** Ein C++ `type-safe` Wrapper für `X86_Detour`, der sicherstellt, dass die Funktionszeigertypen korrekt sind.
   - `Install(void* target, void* detour)`: Kapselt den Aufruf `X86_Detour::Apply`.
   - `Uninstall()`: Kapselt den Aufruf `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Sicherheitsmechanismus (Rekursionsschutz):** Diese Funktion ist entscheidend, um Endlosschleifen zu vermeiden, wenn der Detour die Originalfunktion aufrufen muss. Sie **deinstalliert den Hook temporär (`detour_.Revert()`)**, ruft die Originalfunktion auf (`Get_Original()(args...)`) und **installiert den Hook dann wieder (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Ein Zähler, der sicherstellt, dass der Hook nur dann wieder installiert wird, wenn der oberste Originalaufruf abgeschlossen ist, was sichere rekursive Aufrufe der Originalfunktion ermöglicht (z.B. wenn die Originalfunktion rekursiv ist). Das `thread_local` stellt sicher, dass der `recursion_guard` für jeden Thread isoliert ist, was in Multithread-Umgebungen wichtig ist.
      - **Beispiel (`Call_Original` mit Scope_Guard):**
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

### 4.4. `interceptor_manager.hpp`: Der AMX-Hook-Controller

Dieser `Singleton` ist das Nervenzentrum der Interaktion des SDK mit der SA-MP AMX Virtual Machine. Er koordiniert die Installation der von `function_hook.hpp` bereitgestellten Hooks in den vom Server bereitgestellten AMX-API-Funktionen und leitet den Ausführungsfluss an die SDK-Logik um.

- **`Activate()` / `Deactivate()`**:
   - **Beschreibung:** Öffentliche Methoden zum Installieren und Deinstallieren aller erforderlichen Hooks. Werden in `OnLoad()` bzw. `OnUnload()` Ihres Plugins aufgerufen.
   - **Mechanismus:** Ruft die AMX-Funktionszeiger (wie `amx_Register`, `amx_Exec` usw.) mit `Core::Instance().Get_AMX_Export(...)` ab und installiert die Detours.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Gehookte Funktion:** `amx_Register`
   - **Zweck:** Fängt die Registrierung *aller* Natives ab (durch SA-MP, andere Plugins oder Gamemode).
   - **Aktion:** Für jede registrierte Native fügt der `Interceptor_Manager` sie einem internen Cache (`Cache_Data::native_cache`) hinzu.
   - **Auswirkung:** Dieser Cache ist entscheidend für die Performance von `Pawn_Native` und ermöglicht eine extrem schnelle Suche des Native-Zeigers anstelle einer teuren Suche in der AMX.
   - **Zusätzliche Funktion für `Plugin_Native_Hook`:** Dieser Detour ist *auch* dafür verantwortlich, die Liste der Natives zu modifizieren, bevor sie registriert werden. Wenn eine Native einen zugeordneten `Plugin_Native_Hook` hat, wird der Funktionszeiger in der Registrierungsliste durch das vom `Native_Hook_Manager` generierte Trampolin ersetzt. Dies ermöglicht, dass Ihr Hook zuerst aufgerufen wird.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Gehookte Funktion:** `amx_Exec`
   - **Zweck:** **Dies ist der kritischste Hook.** Er fängt *jede* Codeausführung in der AMX ab, einschließlich des Aufrufs von Pawn-`publics`.
   - **`Plugin_Public`-Abfangmechanismus:**
      1. Wenn `amx_Exec` für eine `public` (oder `AMX_EXEC_MAIN`) aufgerufen wird, wird der `Amx_Exec_Detour` ausgeführt.
      2. Er ruft den Namen der `public` ab (mit `tl_public_name`, der durch `Amx_Find_Public_Detour` gefüllt wurde).
      3. Fragt den `Public_Dispatcher::Instance().Dispatch()` ab, um zu prüfen, ob C++-Handler für diesen Namen registriert sind.
      4. Falls Handler vorhanden sind, führt er diese aus. Der `Public_Dispatcher` übernimmt das `Marshalling` der Parameter von der AMX zu den korrekten C++-Typen.
      5. Basierend auf dem Rückgabewert des `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`) entscheidet er, ob er die ursprüngliche `amx_Exec` aufruft (`Get_Amx_Exec_Hook().Call_Original(...)`) oder die Ausführung der Pawn-`public` beendet.
      6. **Stack-Manipulation:** Wenn die Ausführung der Pawn-`public` unterbrochen wird (`PLUGIN_PUBLIC_STOP`), korrigiert der `Amx_Exec_Detour` den AMX-Stack (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`), um Inkonsistenzen zu vermeiden.
   - **Aktivierung von `Plugin_Native_Hook` (AMX-Patching):**
      - Bei der ersten Ausführung einer `AMX*` überprüft dieser Detour, ob die AMX bereits "gepatcht" wurde (`!manager.Is_Amx_Patched(amx)`).
      - Wenn nicht, durchläuft er die Native-Tabelle **dieser spezifischen AMX-Instanz im Speicher**.
      - Für jede Native, die einen im `Native_Hook_Manager` registrierten `Plugin_Native_Hook` hat, ersetzt er die Adresse der Native in der Tabelle durch ein vom `Native_Hook_Manager` generiertes Trampolin. Die Originaladresse (oder die des vorherigen Hooks) wird im `Native_Hook`-Objekt gespeichert.
      - Die AMX wird dann als "gepatcht" markiert, um unnötige Neuverarbeitung zu vermeiden.
   - **Beispiel (`Amx_Exec_Detour` - mit Details zu `Plugin_Native_Hook`):**
      ```cpp
      // Simplified snippet from interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          auto& manager = Interceptor_Manager::Instance();

          std::unique_ptr<std::string> public_name_ptr;

          // Plugin_Public interception logic (as described above)
          // ...

          int exec_result = Get_Amx_Exec_Hook().Call_Original(amx, retval, index);

          // Patching logic for Plugin_Native_Hook
          if (SAMP_SDK_UNLIKELY(!manager.Is_Amx_Patched(amx))) {
              auto& hook_manager = Native_Hook_Manager::Instance();
              auto& hooks_to_apply = hook_manager.Get_All_Hooks();

              if (!hooks_to_apply.empty()) {
                  AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
                  AMX_FUNCSTUBNT* natives = reinterpret_cast<AMX_FUNCSTUBNT*>(reinterpret_cast<unsigned char*>(hdr) + hdr->natives);

                  int num_natives;

                  amx::Num_Natives(amx, &num_natives);

                  for (auto& hook_to_apply : hooks_to_apply) { // Iterates through all registered Plugin_Native_Hooks
                      uint32_t hook_hash = hook_to_apply.Get_Hash();

                      for (int i = 0; i < num_natives; ++i) { // Iterates through the AMX natives
                          const char* native_name = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(hdr) + natives[i].nameofs);

                          if (FNV1a_Hash(native_name) == hook_hash) { // If the AMX native name matches a hook
                              AMX_NATIVE current_func = reinterpret_cast<AMX_NATIVE>(natives[i].address);

                              hook_to_apply.Set_Next_In_Chain(current_func); // Saves the pointer to the original/previous function

                              AMX_NATIVE trampoline = hook_manager.Get_Trampoline(hook_hash); // Gets the trampoline for this hook

                              if (trampoline)
                                  natives[i].address = reinterpret_cast<ucell>(trampoline); // Replaces in the AMX table
                              
                              break;
                          }
                      }
                  }
              }
              
              manager.On_Amx_Patched(amx); // Marks the AMX as patched
          }
          
          return exec_result;
      }
      ```
- **`int SAMP_SDK_AMX_API Amx_Find_Public_Detour(...)`**:
   - **Gehookte Funktion:** `amx_FindPublic`
   - **Zweck:** Fängt die Suche nach `publics` nach Namen ab.
   - **"Ghost Publics"-Mechanismus:** Wenn `amx_FindPublic` die ursprüngliche `public` in Pawn nicht findet, der `Public_Dispatcher` aber einen registrierten C++-Handler für diesen Namen hat, gibt dieser Hook `AMX_ERR_NONE` und einen speziellen `index` (`PLUGIN_EXEC_GHOST_PUBLIC`) zurück. Dies lässt die SA-MP-API "denken", dass die `public` existiert, und ermöglicht es, dass der nachfolgende `amx_Exec`-Aufruf (für diesen speziellen Index) vom `Amx_Exec_Detour` abgefangen wird, der dann zum C++-Handler umleitet.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Wird verwendet, um den Namen der `public` an den `Amx_Exec_Detour` zu übergeben, wenn ein "Ghost Public" erkannt wird, da `amx_Exec` nur den Index, nicht den Namen, empfängt.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Gehookte Funktionen:** `amx_Init` / `amx_Cleanup`
   - **Zweck:** Verwalten der Liste der aktiven `AMX*`-Instanzen.
   - **Aktion:** `Amx_Init_Detour` ruft `Amx_Manager::Instance().Add_Amx()` auf, und `Amx_Cleanup_Detour` ruft `Amx_Manager::Instance().Remove_Amx()` auf.

### 4.5. `amx_manager.hpp`: Verwalten von `AMX*`-Instanzen

Dieser `Singleton` führt ein dynamisches Register aller aktuell auf dem Server geladenen AMX-Virtual-Machines. Er ist unerlässlich für Funktionen, die mit "allen Skripten" interagieren oder ein bestimmtes Skript finden müssen.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Beschreibung:** Eine Liste von Zeigern auf alle initialisierten `AMX*`-Instanzen (Gamemode und Filterscripts).
   - **Verwaltung:** Wird durch die Hooks `Amx_Init_Detour` gefüllt und durch `Amx_Cleanup_Detour` geleert.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Zweck:** Schützt `loaded_amx_` vor gleichzeitigem Zugriff in Multithread-Umgebungen (obwohl SA-MP größtenteils Single-Thread ist, ist dies eine gute Sicherheitspraxis). `std::shared_mutex` ermöglicht mehrere gleichzeitige Leser, aber nur einen Schreiber.
- **`std::atomic<uint32_t> generation_`**:
   - **Zweck:** Ein Zähler, der bei jedem Hinzufügen oder Entfernen einer AMX inkrementiert wird.
   - **Verwendung:** Wird vom `Caller_Cache` in `callbacks.hpp` verwendet, um zu erkennen, wann sich die Liste der AMXs geändert hat, wodurch Caches für `publics`-Suchen ungültig werden und sichergestellt wird, dass `Pawn_Public`-Aufrufe immer mit aktuellen Informationen ausgeführt werden. Dies optimiert die Leistung, indem wiederholte Suchen in einem unveränderten Zustand vermieden werden.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Beschreibung:** Durchläuft `loaded_amx_` (vom neuesten zum ältesten, was in der Regel den relevantesten Gamemode oder Filterscript zuerst platziert), um die `public` mit dem angegebenen Namen zu finden.
   - **Mechanismus:** Verwendet `amx::Find_Public` für jede `AMX*`-Instanz.
   - **Auswirkung:** Ist die Grundlage für `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: Der `Plugin_Public`-Callback-Router

Dieser `Singleton` ist die Komponente, die Pawn-`public`-Namen ihren C++-`Plugin_Public`-Funktionen zuordnet.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Schlüssel:** Der FNV1a-Hash des `public`-Namens (z.B. `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Wert:** Ein `std::vector` von `std::function<cell(AMX*)>`, wobei jede `std::function` ein C++-Handler ist, der für diese `public` registriert wurde.
   - **Mechanismus:** Der `std::vector` ermöglicht die Registrierung mehrerer `Plugin_Public`s für denselben Callback (z.B. mehrere Plugins, die `OnPlayerCommandText` abfangen möchten). Die Handler werden in umgekehrter Registrierungsreihenfolge ausgeführt.
- **`Public_Register`**:
   - **Mechanismus:** Dies ist eine Template-Klasse, deren Makro `PLUGIN_PUBLIC_REGISTRATION` eine globale statische Instanz erstellt. Im statischen Konstruktor (`static bool registered = [...]`) registriert sie ihren `Plugin_Public`-Handler beim `Public_Dispatcher`. Dies ist ein Muster der "statischen Kompilier-/Initialisierungszeitregistrierung".
   - **Beispiel (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Register<decltype(&name), &name, hash_##name> register_##name;
      ```

- **`Public_Traits` und `Wrapper()`**:
   - **Mechanismus:** `Public_Traits` ist eine Trait-Vorlage, die mittels Metaprogrammierung eine Funktion `static cell Wrapper(AMX* amx)` generiert.
   - **Zweck:** Dieser `Wrapper` ist die `Amx_Handler_Func`, die der `Public_Dispatcher` tatsächlich speichert und aufruft. Er ist verantwortlich für:
      1. Aufruf von `Public_Param_Reader::Get_Public_Params(amx, args...)`, um die Parameter aus dem AMX-Stack zu extrahieren.
      2. Aufruf Ihrer tatsächlichen C++-`Plugin_Public`-Funktion (`func_ptr`) mit den bereits in die korrekten C++-Typen konvertierten Parametern.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Beschreibung:** Eine Reihe von rekursiven Template-Funktionen, die die Werte aus dem AMX-Stack lesen und in die in der `Plugin_Public`-Deklaration angegebenen C++-Typen konvertieren.
   - **Mechanismus:** Verwendet `Get_Stack_Cell()` für den Zugriff auf die `cell`s im Stack. Nutzt `if constexpr` (C++17+) oder `std::is_same<T>::value` (C++14), um die korrekte Konvertierung anzuwenden (`amx::AMX_CTOF` für float, `Samp_SDK::Get_String` für string, direkter Cast für int).

### 4.7. `native.hpp`: Verwalten und Aufrufen von Plugin-Natives

Dieser Header ist der Erstellung und Verwaltung von C++-Natives gewidmet, die Ihr Plugin für Pawn bereitstellt.

- **`Native_List_Holder`**:
   - **Beschreibung:** Ein globaler `Singleton`, der alle in Ihrem Plugin deklarierten `Plugin_Native`s speichert (aus allen `.cpp`-Dateien, die `SAMP_SDK_WANT_AMX_EVENTS` verwenden).
   - **`std::vector<Native> natives_`**: Enthält `Native`-Objekte (die den Namen der Native und den Zeiger auf die C++-Funktion `Native_Handler` speichern).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Eine Hash-optimierte Map für schnelle Suchen von internen `Plugin_Native`s (wird von `Plugin_Call` verwendet).
- **`Native_Register`**:
   - **Mechanismus:** Ähnlich wie `Public_Register` ist dies eine Template-Klasse, deren Makro `Plugin_Native` eine globale statische Instanz erstellt. In ihrem Konstruktor fügt sie die Native dem `Native_List_Holder` hinzu.
   - **Auswirkung:** Ermöglicht es Ihnen, `Plugin_Native`s in mehreren `.cpp`-Dateien zu deklarieren, ohne sich um die manuelle Registrierung kümmern zu müssen. Alle werden automatisch gesammelt.
- **`Native_Registry`**:
   - **Beschreibung:** Eine Hilfsklasse, die in `OnAmxLoad` die vollständige Liste der `Native`s vom `Native_List_Holder` nimmt und sie in ein `AMX_NATIVE_INFO`-Array formatiert.
   - **Mechanismus:** Ruft `amx::Register(amx, amx_natives_info_.data(), -1)` auf, um alle Ihre Natives in der gerade geladenen AMX-Instanz zu registrieren.
- **`Plugin_Call_Impl(...)`**:
   - **Beschreibung:** Die zugrunde liegende Implementierung des Makros `Plugin_Call`.
   - **Mechanismus:** Verwendet `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)`, um den C++-Funktionszeiger direkt abzurufen.
   - **Umgebung:** Führt die Native in einer `Amx_Sandbox`-Umgebung (isoliert) aus, um den temporären Stack und Heap zu verwalten, ähnlich wie `Pawn_Native` funktioniert.

### 4.8. `native_hook_manager.hpp`: Der Hook-Motor für Natives

Dies ist das robuste Hooking-System für Natives, das entwickelt wurde, um die Verkettung von Hooks mehrerer Plugins für dieselbe Native zu verwalten.

- **`Native_Hook`**:
   - **Beschreibung:** Eine Klasse, die einen einzelnen Native-Hook repräsentiert. Speichert den Hash des Native-Namens, die vom Benutzer bereitgestellte C++-Handler-Funktion (`user_handler_`) und einen `std::atomic<AMX_NATIVE> next_in_chain_`.
   - **`user_handler_`**: Ihre `Plugin_Native_Hook` C++-Funktion.
   - **`next_in_chain_`**: Der Pointer zur ursprünglichen Native oder zum Hook eines Plugins mit niedrigerer Priorität. Es ist ein `std::atomic`, um Thread-Safety beim Lesen/Schreiben zu gewährleisten.
   - **`Dispatch(AMX* amx, cell* params)`**: Wird vom Trampolin aufgerufen, um Ihren `user_handler_` auszuführen.
   - **`Call_Original(AMX* amx, cell* params)`**: Entscheidende Methode, die `next_in_chain_` aufruft, sodass Ihr Hook die ursprüngliche Funktionalität oder den nächsten Hook in der Kette aufrufen kann.
- **`Trampoline_Allocator`**:
   - **Beschreibung:** Eine Klasse, die für die Allokation von ausführbaren Speicherblöcken und die Generierung des Assembly-"Trampolin"-Codes in diesen Blöcken verantwortlich ist.
   - **`Generate_Trampoline_Code(unsigned char* memory, int hook_id)`**: Schreibt 10 Bytes Assembly:
      1. `B8 XX XX XX XX`: `MOV EAX, hook_id` (platziert die eindeutige ID des Hooks im EAX-Register).
      2. `E9 XX XX XX XX`: `JMP relative_address_to_Dispatch_Wrapper_Asm` (springt zur generischen Dispatch-Funktion des SDK).
   - **`Allocation_Size = 4096`**: Allokiert Speicher in Seiten für Effizienz und Cache-Ausrichtung.
   - **Speicherberechtigungen:** Verwendet `VirtualAlloc` (Windows) oder `mmap` (Linux) mit `EXECUTE_READWRITE`-Berechtigungen, um sicherzustellen, dass der generierte Code ausgeführt werden kann.
- **`Dispatch_Wrapper_Asm()`**:
   - **Beschreibung:** Eine kleine Assembly-Funktion (definiert mit `__declspec(naked)` oder `asm volatile`), die als Ziel aller Trampoline dient.
   - **Aktion:** Speichert die Register, verschiebt `EAX` (das die `hook_id` enthält) auf den Stack und ruft die C++-Funktion `Dispatch_Hook` auf. Nach der Rückkehr von `Dispatch_Hook` werden die Register wiederhergestellt und die Funktion kehrt zurück.
- **`cell SAMP_SDK_CDECL Dispatch_Hook(int hook_id, AMX* amx, cell* params)`**:
   - **Beschreibung:** Die generische C++-Funktion, die von `Dispatch_Wrapper_Asm` aufgerufen wird.
   - **Aktion:** Verwendet `hook_id`, um den entsprechenden `Native_Hook` im `Native_Hook_Manager` zu finden und ruft dessen `Dispatch()`-Methode auf, die wiederum den `Plugin_Native_Hook`-Handler des Benutzers aufruft.
   - **Linker-Überlegungen:** Diese Funktion ist ein kritischer Punkt der Interoperabilität zwischen C++ und Assembly. Um sicherzustellen, dass sie unter Linux (GCC/Clang) korrekt exportiert und vom Linker gefunden wird, ist sie mit drei wichtigen Eigenschaften definiert:
      1. **`extern "C"`**: Verhindert das C++ Name Mangling und stellt sicher, dass das Symbol den reinen C-Namen `Dispatch_Hook` hat, wonach der Assembly-Code sucht.
      2. **`inline`**: Ermöglicht es, dass die Funktionsdefinition in der Header-Datei enthalten ist (erforderlich für eine Header-only-Bibliothek), ohne "multiple definition"-Fehler (ODR - One Definition Rule) zu verursachen.
      3. **`SAMP_SDK_USED_BY_ASM` (`__attribute__((used))` in GCC/Clang)**: Zwingt den Compiler, den Code für die Funktion zu emittieren, selbst wenn er keine Aufrufe dazu von anderem C++-Code findet. Dies verhindert, dass der Optimierer sie fälschlicherweise entfernt.
- **`Native_Hook_Manager`**:
   - **Beschreibung:** Der zentrale `singleton`, der alle registrierten `Native_Hook`s und deren Trampoline verwaltet.
   - **`std::list<Native_Hook> hooks_`**: Speichert die Liste der Hooks in der Reihenfolge.
   - **`std::unordered_map<uint32_t, Trampoline_Func> hash_to_trampoline_`**: Ordnet den Hash des Native-Namens dem Zeiger des generierten Trampolins zu.
   - **`std::vector<uint32_t> hook_id_to_hash_`**: Ordnet die ganzzahlige ID des Hooks (im Trampolin verwendet) zurück zum Hash des Native-Namens.
   - **`Get_Trampoline(uint32_t hash)`**: Gibt einen Trampolin-Zeiger für einen bestimmten Native-Hash zurück (oder erstellt und allokiert ihn).
- **`PLUGIN_NATIVE_HOOK_REGISTRATION`**:
   - **Mechanismus:** Ein Makro, das für jeden `Plugin_Native_Hook` eine globale statische Klasse (`Native_Hook_Register_##name`) erstellt. Im statischen Konstruktor dieser Klasse registriert es den Benutzer-`handler` beim `Native_Hook_Manager`.

### 4.9. `callbacks.hpp` & `amx_memory.hpp`: C++ -> Pawn-Aufrufe und RAII

Diese Header bilden das Rückgrat für das Aufrufen von Pawn-Funktionen aus C++ (`Pawn_*`-Makros) und gewährleisten die Speichersicherheit.

- **`Amx_Sandbox`**:
   - **Beschreibung:** Eine `thread_local`-Struktur, die eine minimalistische und isolierte `AMX`-Umgebung für `Pawn_Native`- und `Plugin_Call`-Aufrufe simuliert.
   - **Mechanismus:** Besitzt eine eigene `AMX`-Struktur, `AMX_HEADER` und einen `std::vector<unsigned char> heap`, um den Speicher eines Skripts zu simulieren. Dies ermöglicht, dass `amx::Push`, `amx::Allot` usw. aufgerufen werden, ohne den Zustand realer, laufender Pawn-Skripte zu beeinträchtigen.
   - **`thread_local`:** Stellt sicher, dass jeder Thread seine eigene `Amx_Sandbox` hat, wodurch Race Conditions verhindert werden, wenn das SDK in einem Multithread-Kontext verwendet wird (z.B. ein zukünftiger Thread-Pool für Nicht-Pawn-Operationen).
   - **Beispiel (`Amx_Sandbox`):**
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
   - **Beschreibung:** Eine Reihe überladener Template-Funktionen, die das `Marshalling` *jedes* C++-Parameters in das von der AMX erwartete `cell`-Format verwalten und umgekehrt für Ausgabeparameter.
   - **Eingabeverarbeitung:**
       - Für `int`, `float`, `bool`: Konvertiert direkt in `cell`.
       - Für `const char*`, `std::string`: Weist Speicher im Heap der `Amx_Sandbox` (oder echtem AMX für `Pawn_Public`) zu, kopiert den String und legt die AMX-Adresse auf den Stack.
   - **Ausgabeverarbeitung (`is_output_arg`):**
       - **Mechanismus:** Wenn ein Argument eine nicht-konstante Lvalue-Referenz ist (erkannt durch das Trait `is_output_arg`), legt der `Parameter_Processor` nicht den Wert ab, sondern eine *AMX-Adresse* für eine temporär im Heap zugewiesene `cell`.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Nach dem Aufruf der Pawn-Native wird eine Liste von Lambdas (`post_call_updaters`) ausgeführt. Jedes Lambda ist dafür verantwortlich, den endgültigen Wert der im AMX zugewiesenen `cell` zu lesen und ihn zurück der ursprünglichen C++-Variable zuzuweisen (z.B. `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mechanismus:** Ein `std::integral_constant` (Typmerkmal), das zur Kompilierzeit bewertet, ob ein C++-Parametertyp eine modifizierbare Referenz ist (z.B. `int&`, `float&`, `std::string&`). Dies ermöglicht es dem `Parameter_Processor`, Eingabe- von Ausgabeparametern zu unterscheiden.
   - **Beispiel (`is_output_arg`):**
      ```cpp
      // Simplified snippet from callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Beschreibung:** Eine RAII-Klasse (`Resource Acquisition Is Initialization`), die die Speicherzuweisung und -freigabe in der AMX kapselt.
   - **Mechanismus:** Im Konstruktor ruft sie `amx::Allot` auf, um eine `amx_addr` und eine `phys_addr` zu erhalten. Im Destruktor ruft sie `amx::Release` auf, um diesen Speicher freizugeben.
   - **Auswirkung:** **Entscheidend, um Speicherlecks im AMX-Heap zu verhindern.** Stellt sicher, dass der temporäre Speicher, der für Strings oder Ausgabeparameter verwendet wird, immer freigegeben wird, selbst wenn Ausnahmen auftreten oder frühzeitig zurückgekehrt wird.

### 4.10. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Abstrahierter AMX-Zugriff

Diese Header bieten die grundlegenden Definitionen und High-Level-Tools für die Interaktion mit Pawn.

- **`amx_defs.h`**:
   - **Inhalt:** Enthält die rohen Definitionen der AMX-Strukturen (`AMX`, `AMX_HEADER`), Typen (`cell`, `ucell`) und Fehler-Enums (`AmxError`). Definiert auch `AMX_NATIVE` und `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Verwendet Packing-Attribute (`#pragma pack(push, 1)` / `__attribute__((packed))`), um sicherzustellen, dass die AMX-Strukturen das korrekte Speicherlayout haben, was für die Interoperabilität von grundlegender Bedeutung ist.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Beschreibung:** Die Haupt-Template-Funktion zum Aufrufen der vom Server bereitgestellten AMX-API-Funktionen.
   - **Mechanismus:** Ruft den Funktionszeiger über `Core::Instance().Get_AMX_Export(Index)` ab und ruft ihn auf. Zentralisiert die Fehlerbehandlung, falls der Funktionszeiger nicht verfügbar ist.
   - **Auswirkung:** Konvertiert Low-Level-Aufrufe (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) in idiomatisches und typsicheres C++ (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Beschreibung:** Wesentliche Funktionen zum Konvertieren von `cell`-Werten in `float` und umgekehrt, wobei eine bitweise Neuinterpretation des Speichers durchgeführt wird.
   - **`static_assert`:** Enthält `static_assert`, um sicherzustellen, dass `sizeof(cell) == sizeof(float)` zur Kompilierzeit gilt, wodurch Fehler auf Plattformen mit unterschiedlichen Typgrößen verhindert werden.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Beschreibung:** Hilfsprogramm zum Konvertieren einer AMX-String-Adresse in `std::string`.
   - **Mechanismus:** Zuerst wird die physische Adresse (`cell* phys_addr`) des Strings in der AMX mit `amx::Get_Addr` abgerufen. Anschließend werden `amx::STR_Len` zur Bestimmung der Länge und `amx::Get_String` zum Kopieren der Bytes in einen `std::string` verwendet.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Beschreibung:** Die Basis-Stringformatierungsfunktion (`printf`-ähnlich) für das SDK.
   - **Mechanismus:** Verwendet `vsnprintf` in zwei Durchgängen: zuerst zur Bestimmung der erforderlichen Stringgröße und dann zur Formatierung des Strings in den dynamisch zugewiesenen `std::string`. Dies verhindert Pufferüberläufe.

## 5. Kompilierung und Bereitstellung

### Architektur- und Plattformanforderungen

- Ihr Plugin **MUSS** für die Architektur **x86 (32-Bit)** kompiliert werden.
- Unterstützte Plattformen: Windows (.dll) und Linux (.so).

### Beispiele für Kompilierungsbefehle

#### **MSVC (Visual Studio)**

1. Erstellen Sie ein neues Projekt für eine "Dynamic-Link Library (DLL)".
2. Legen Sie in den Projekteinstellungen die "Lösungsplattform" auf **x86** fest.
3. Stellen Sie sicher, dass der C++ Language Standard mindestens C++14 ist.

#### **GCC / Clang (Linux)**

```bash
# For a plugin named 'my_plugin.so' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Kompiliert für 32-Bit.
- `-shared`: Erstellt eine gemeinsam genutzte Bibliothek (`.so`).
- `-std=c++17`: Setzt den C++-Standard auf C++17 (kann `c++14` oder `c++20` sein).
- `-O2`: Optimierungsstufe 2.
- `-fPIC`: Generiert positionsunabhängigen Code, erforderlich für gemeinsam genutzte Bibliotheken.
- `-Wall -Wextra`: Aktiviert zusätzliche Warnungen, um Fehler zu erkennen.
- `-Wl,--no-undefined`: Verhindert das Erstellen der Bibliothek, wenn undefinierte Symbole vorhanden sind.

#### **GCC / Clang (MinGW unter Windows)**

```bash
# For a plugin named 'my_plugin.dll' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Linkt die C++-Standardbibliothek statisch. Dies ist unerlässlich, um zu verhindern, dass Ihr Plugin von compilerspezifischen Laufzeit-DLLs abhängt, die auf dem System des Benutzers möglicherweise nicht vorhanden sind.
- `-static-libgcc`: Linkt die GCC-Bibliothek statisch.

### Überlegungen zur Verteilung

- **Dateiname:** Ihr Plugin muss die Erweiterung `.dll` (Windows) oder `.so` (Linux) haben. Beispiel: `my_plugin.dll`.
- **Speicherort:** Legen Sie die kompilierte Datei in den Ordner `plugins/` Ihres SA-MP-Servers.
- **server.cfg:** Fügen Sie den Namen Ihres Plugins (unter Windows ohne Erweiterung) zur Zeile `plugins` in der `server.cfg` hinzu.
   ```
   plugins my_plugin (if Linux, my_plugin.so)
   ```

## Lizenz

Copyright © **SA-MP Programming Community**

Diese Software ist unter den Bedingungen der MIT-Lizenz ("Lizenz") lizenziert; Sie dürfen diese Software gemäß den Lizenzbedingungen nutzen. Eine Kopie der Lizenz finden Sie unter: [MIT License](https://opensource.org/licenses/MIT)

### Nutzungsbedingungen

#### 1. Gewährte Berechtigungen

Diese Lizenz gewährt jeder Person, die eine Kopie dieser Software und der zugehörigen Dokumentationsdateien erhält, kostenlos folgende Rechte:
* Die Software ohne Einschränkungen zu nutzen, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, zu unterlizenzieren und/oder zu verkaufen
* Personen, denen die Software zur Verfügung gestellt wird, dies unter den folgenden Bedingungen zu gestatten

#### 2. Verpflichtende Bedingungen

Alle Kopien oder wesentliche Teile der Software müssen enthalten:
* Den obigen Urheberrechtshinweis
* Diesen Erlaubnishinweis
* Den nachstehenden Haftungsausschluss

#### 3. Urheberrecht

Die Software und alle zugehörige Dokumentation sind durch Urheberrechtsgesetze geschützt. Die **SA-MP Programming Community** behält die ursprünglichen Urheberrechte an der Software.

#### 4. Gewährleistungsausschluss und Haftungsbeschränkung

DIE SOFTWARE WIRD "WIE BESEHEN" ZUR VERFÜGUNG GESTELLT, OHNE JEGLICHE AUSDRÜCKLICHE ODER IMPLIZITE GEWÄHRLEISTUNG, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT, DER EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND DER NICHTVERLETZUNG VON RECHTEN DRITTER.

DIE AUTOREN ODER URHEBERRECHTSINHABER SIND IN KEINEM FALL HAFTBAR FÜR ANSPRÜCHE, SCHÄDEN ODER ANDERE VERPFLICHTUNGEN, OB IN EINER VERTRAGS- ODER DELIKTKLAGE, DIE AUS ODER IN VERBINDUNG MIT DER SOFTWARE ODER DER NUTZUNG ODER ANDEREN GESCHÄFTEN MIT DER SOFTWARE ENTSTEHEN.

---

For detailed information about the MIT License, visit: https://opensource.org/licenses/MIT