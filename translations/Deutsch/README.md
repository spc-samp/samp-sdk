# SAMP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Ein modernes, header-only und hochleveliges C++ SDK für die Entwicklung von SA-MP Plugins und Modulen.**

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

- [SAMP SDK](#samp-sdk)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [1. Einführung und Designphilosophie](#1-einführung-und-designphilosophie)
    - [Das Problem mit der Standard-C-API von SA-MP](#das-problem-mit-der-standard-c-api-von-sa-mp)
    - [Die Lösung des SAMP SDK: Abstraktion mit Sicherheit und Performance](#die-lösung-des-samp-sdk-abstraktion-mit-sicherheit-und-performance)
    - [Header-Only-Modell: Vorteile und Implikationen](#header-only-modell-vorteile-und-implikationen)
  - [2. Konfiguration und Umgebung](#2-konfiguration-und-umgebung)
    - [Kompilierungsanforderungen](#kompilierungsanforderungen)
    - [Empfohlene Dateistruktur](#empfohlene-dateistruktur)
    - [Essentielle Konfigurationsmakros\*\*](#essentielle-konfigurationsmakros)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP Definitionen und Konstanten (`samp_defs.hpp`)](#sa-mp-definitionen-und-konstanten-samp_defshpp)
  - [3. Umfassende API-Nutzungsanleitung](#3-umfassende-api-nutzungsanleitung)
    - [3.1. Der Lebenszyklus des Plugins](#31-der-lebenszyklus-des-plugins)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Abfangen von Pawn-Events](#32-plugin_public-abfangen-von-pawn-events)
      - [Syntax und Deklaration](#syntax-und-deklaration)
      - [Automatisches Marshalling von Parametern](#automatisches-marshalling-von-parametern)
      - [Kontrolle des Ablaufs: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#kontrolle-des-ablaufs-plugin_public_continue-vs-plugin_public_stop)
    - [3.3. `Plugin_Native`: Erstellen von nativen C++-Funktionen](#33-plugin_native-erstellen-von-nativen-c-funktionen)
      - [Syntax und feste Signatur](#syntax-und-feste-signatur)
      - [Automatische Registrierung von Natives](#automatische-registrierung-von-natives)
      - [Extraktion von Parametern: `Register_Parameters` vs. `Native_Params`](#extraktion-von-parametern-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Vollständige API: `Get`, `Get_REF`, `Set_REF`)](#native_params-vollständige-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Rückgabe von Werten](#rückgabe-von-werten)
    - [3.4. `Pawn_*` Makros: Aufrufen von Pawn-Funktionen aus C++](#34-pawn_-makros-aufrufen-von-pawn-funktionen-aus-c)
      - [`Pawn_Native(NameDerNative, ...)`](#pawn_nativenamedernative-)
      - [`Pawn_Public(NameDerPublic, ...)`](#pawn_publicnamederpublic-)
      - [`Pawn(NameDerFunktion, ...)`](#pawnnamederfunktion-)
      - [Syntax und Konventionen](#syntax-und-konventionen)
      - [Marshalling von Eingabeparametern](#marshalling-von-eingabeparametern)
      - [Marshalling von Ausgabeparametern (Referenzen: `int&`, `float&`, `std::string&`)](#marshalling-von-ausgabeparametern-referenzen-int-float-stdstring)
      - [Das `Callback_Result`-Objekt: Vollständige Analyse](#das-callback_result-objekt-vollständige-analyse)
    - [3.5. `Plugin_Module`: Verwaltung dynamischer Module](#35-plugin_module-verwaltung-dynamischer-module)
      - [Syntax und Zweck](#syntax-und-zweck)
      - [Lebenszyklus eines Moduls](#lebenszyklus-eines-moduls)
      - [Vorteile der Modularisierung](#vorteile-der-modularisierung)
    - [3.6. `Plugin_Call`: Aufrufen interner Plugin-Natives](#36-plugin_call-aufrufen-interner-plugin-natives)
      - [Syntax und Performancevorteile](#syntax-und-performancevorteile)
    - [**3.7. SDK-Dienstprogrammfunktionen**](#37-sdk-dienstprogrammfunktionen)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Empfohlen)](#stdstring-plugin_formatconst-char-format--empfohlen)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Implementierungsdetail)](#stdstring-samp_sdkformatconst-char-format--implementierungsdetail)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. **Interne Anatomie und Architektur des SDK**](#4-interne-anatomie-und-architektur-des-sdk)
    - [4.1. `core.hpp`: Die minimalistische Grundlage](#41-corehpp-die-minimalistische-grundlage)
    - [**4.2. `platform.hpp` und `version.hpp`: Kompatibilität und Metadaten**](#42-platformhpp-und-versionhpp-kompatibilität-und-metadaten)
    - [4.3. `function_hook.hpp`: Der x86 Intercept-Engine](#43-function_hookhpp-der-x86-intercept-engine)
    - [4.4. `interceptor_manager.hpp`: Der AMX-Hook-Controller](#44-interceptor_managerhpp-der-amx-hook-controller)
    - [4.5. `amx_manager.hpp`: Verwalten von `AMX*`-Instanzen](#45-amx_managerhpp-verwalten-von-amx-instanzen)
    - [4.6. `public_dispatcher.hpp`: Der `Plugin_Public`-Callback-Router](#46-public_dispatcherhpp-der-plugin_public-callback-router)
    - [4.7. `native.hpp`: Verwalten und Aufrufen von Plugin-Natives](#47-nativehpp-verwalten-und-aufrufen-von-plugin-natives)
    - [4.8. `callbacks.hpp` \& `amx_memory.hpp`: C++ -\> Pawn-Aufrufe und RAII](#48-callbackshpp--amx_memoryhpp-c---pawn-aufrufe-und-raii)
    - [4.9. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Abstrahierter AMX-Zugriff](#49-amx_apihpp--amx_helpershpp--amx_defsh-abstrahierter-amx-zugriff)
  - [5. Kompilierung und Bereitstellung](#5-kompilierung-und-bereitstellung)
    - [Anforderungen an Architektur und Plattform](#anforderungen-an-architektur-und-plattform)
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

### Das Problem mit der Standard-C-API von SA-MP

Die SA-MP Plugin-API ist eine C-Programmierschnittstelle. Obwohl funktional und grundlegend, bringt sie die Herausforderungen der Low-Level-Programmierung mit sich:
- **Manuelle Speicherverwaltung:** Funktionen wie `amx_Allot` und `amx_Release` erfordern, dass der Entwickler Speicher im AMX-Heap explizit allokiert und freigibt. Dies ist eine häufige Ursache für Speicherlecks und Laufzeitfehler.
- **Schwache Typisierung und manuelle Konvertierungen:** Parameter werden als Array von `cell`s übergeben, was explizite (und oft unsichere) Konvertierungen zwischen `cell`, `int`, `float` und `char*` erzwingt.
- **Ausführlichkeit und Boilerplate:** Das Extrahieren mehrerer Parameter aus einem `cell* params`-Array, der Umgang mit Stringlängen und die Verwaltung des AMX-Stacks für C++ zu Pawn-Rückrufe erfordert sich wiederholenden Code.
- **Zerbrechlichkeit der Schnittstelle:** Das Fehlen einer Kompilierungszeitprüfung (Typ-Sicherheit) bedeutet, dass Fehler bei der Parameterübergabe oder den Typen bis zur Ausführung unbemerkt bleiben können, was zu Abstürzen oder undefiniertem Verhalten führt.

### Die Lösung des SAMP SDK: Abstraktion mit Sicherheit und Performance

Das SAMP SDK begegnet diesen Problemen durch eine leistungsstarke Abstraktionsebene in C++:
- **RAII (Resource Acquisition Is Initialization):** Automatische Speicherverwaltung im AMX. `Amx_Scoped_Memory` stellt sicher, dass der zugewiesene Speicher freigegeben wird.
- **Typensicherheit:** Automatische und sichere Konvertierung von Parametern zwischen C++ und Pawn. Sie arbeiten direkt mit `int`, `float`, `std::string`.
- **Prägnante und idiomische Syntax:** Makros und Templates bieten eine saubere API, die sich modernerem C++ als der traditionellen C-API ähnelt.
- **Robuste Interception:** Eine fortschrittliche Hooking-Engine ermöglicht die transparente Interception von Pawn-Callbacks (`Plugin_Public`) und die dynamische Registrierung von Natives.
- **Hohe Performance:** Umfassender Einsatz von Kompilierungszeit-Hashing (FNV1a), Funktions-Caching und `thread_local`-Optimierungen, um den Overhead der Abstraktionen zu minimieren.

### Header-Only-Modell: Vorteile und Implikationen

Das SDK besteht ausschließlich aus Header-Dateien (`.hpp`, `.h`).
- **Vorteile:**
   - **Vereinfachte Integration:** Es müssen keine Bibliotheken gebaut, verknüpft oder verteilt werden. Einfach die Header einbinden.
   - **Compiler-Optimierungen:** Der Compiler hat vollständige Sichtbarkeit auf den SDK-Code und Ihr Plugin, was aggressives Inlining und Link-Time-Optimierungen ermöglicht, was zu schnelleren Binärdateien führen kann.
- **Implikationen:**
   - **Kompilierungszeit:** Bei sehr großen Projekten kann die Kompilierung aufgrund der wiederholten Einbindung des SDK-Codes länger dauern. Dies wird durch Include-Guards und die "nur das Nötigste einbinden"-Natur von C++ gemildert.
   - **Implementierungsmakros:** Die Notwendigkeit des Makros `SAMP_SDK_IMPLEMENTATION` ist eine Konsequenz des Header-Only-Modells, um Neudefinitionen von Symbolen zu vermeiden.

## 2. Konfiguration und Umgebung

### Kompilierungsanforderungen

- **C++-Compiler:** Kompatibel mit C++14 oder höher (das SDK verwendet Funktionen von C++14, C++17 und C++20 für spezifische Optimierungen, C++14 ist jedoch das Minimum).
   - GCC (Version 7+)
   - Clang (Version 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Architektur:** **x86 (32-Bit)**. SA-MP läuft ausschließlich auf dieser Architektur. Das SDK enthält Überprüfungen in `platform.hpp`, die Kompilierungsfehler ausgeben, wenn die falsche Architektur erkannt wird.
- **Betriebssystem:** Windows oder Linux.

### Empfohlene Dateistruktur

Zur Übersichtlichkeit und Organisation ist es üblich, das SDK in einem Unterordner `samp-sdk` zu organisieren.

```
mein_plugin/
├── samp-sdk/
│   ├── // Andere SDK-Dateien
│   └── samp_sdk.hpp             // Der Haupt-Header, der inkludiert werden muss
│
├── src/
│   ├── main.cpp                  // Wo SAMP_SDK_IMPLEMENTATION definiert ist
│   └── my_custom_logic.cpp       // Optional, um Code zu organisieren
│
└── CMakeLists.txt (oder .vcxproj, Makefile)
```

### Essentielle Konfigurationsmakros**

Definieren Sie diese Makros immer *bevor* Sie `samp_sdk.hpp` einbinden.

#### `SAMP_SDK_IMPLEMENTATION`

- **Zweck:** Signalisiert dem Compiler, dass diese `.cpp`-Datei die Implementierungen der Plugin-Exportfunktionen (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`) generieren soll. **Das SDK übernimmt die automatische Exportierung dieser Funktionen und eliminiert die Notwendigkeit von `.def`-Dateien (unter Windows) oder `__attribute__((visibility("default")))`-Deklarationen (unter Linux) für diese Funktionen.**
- **Technische Auswirkungen:** Ohne dieses Makro findet der Linker die erforderlichen Exporte nicht, und der SA-MP-Server kann Ihr Plugin nicht laden.
- **Grundregel:** **Definieren Sie dieses Makro in NUR EINER `.cpp`-Datei in Ihrem gesamten Projekt.** Das Definieren in mehreren Dateien führt zu einem Linkerfehler "doppeltes Symbol".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // Das Makro veranlasst das SDK, die erforderlichen Funktionen automatisch zu exportieren.
#include "samp-sdk/samp_sdk.hpp"

// ... Ihr Plugin-Code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Zweck:** Aktiviert die SDK-Funktionen, die mit der Interaktion mit der AMX-Umgebung (Pawn Virtual Machine) zusammenhängen.
- **Aktivierte Funktionen:**
   - Deklaration und Registrierung von C++-Natives mit `Plugin_Native`.
   - Callbacks `OnAmxLoad(AMX* amx)` und `OnAmxUnload(AMX* amx)`.
   - Das Makro `Plugin_Call` zum Aufrufen eigener Plugin-Natives.
- **Technische Auswirkungen:** Wenn dieses Makro definiert ist, sammelt das SDK automatisch alle Ihre `Plugin_Native`s. In der Funktion `Supports()` wird das Flag `SUPPORTS_AMX_NATIVES` automatisch hinzugefügt.
- **Flexibilität:** **Sie können dieses Makro in mehreren `.cpp`-Dateien definieren.** Das statische Registrierungssystem des SDK (`Native_Registrar`) konsolidiert alle Natives aus verschiedenen Kompilierungseinheiten in einer einzigen globalen Liste.

```cpp
// my_natives.cpp (kann eine separate Datei von main.cpp sein)
#define SAMP_SDK_WANT_AMX_EVENTS // Nur zum Aktivieren von Plugin_Native
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Zweck:** Aktiviert den `OnProcessTick()`-Callback, der regelmäßig vom Server aufgerufen wird.
- **Technische Auswirkungen:** Fügt automatisch das Flag `SUPPORTS_PROCESS_TICK` in der Funktion `Supports()` hinzu.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logik, die bei jedem "Tick" des Servers ausgeführt wird (z.B. 20ms)
    // Vorsicht bei rechenintensiven Operationen hier!
}
```

### SA-MP Definitionen und Konstanten (`samp_defs.hpp`)

Diese Datei stellt alle bekannten SA-MP-Konstanten und -Grenzen zur Verfügung, wie z.B. `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST` usw. Sie wird automatisch von `samp_sdk.hpp` eingebunden und sollte verwendet werden, um die Kompatibilität und Lesbarkeit des Codes zu gewährleisten.

## 3. Umfassende API-Nutzungsanleitung

### 3.1. Der Lebenszyklus des Plugins

Die folgenden Funktionen sind die Eingangs- und Ausgangspunkte Ihres Plugins, die automatisch vom SDK exportiert werden.

#### `bool OnLoad()`

- **Beschreibung:** Erste Funktion, die vom SA-MP-Server nach dem erfolgreichen Laden Ihres Plugins in den Speicher aufgerufen wird.
- **Verwendung:** Ideal zum Initialisieren von Systemen, Laden von Konfigurationen, Öffnen von Datenbankverbindungen oder Laden von Modulen (`Plugin_Module`).
- **Rückgabe:**
   - `true`: Das Plugin wurde erfolgreich initialisiert und das Laden wird fortgesetzt.
   - `false`: Das Plugin konnte nicht initialisiert werden. Das Laden wird abgebrochen und das Plugin wird entladen.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initialisiere MeinPlugin v1.0...");

    // Beispiel: Laden eines Moduls (weitere Details in Abschnitt 3.5)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Datenbankmodul geladen.")) {
        Samp_SDK::Log("FEHLER: Datenbankmodul konnte nicht geladen werden!");

        return false; // Bricht das Laden des Hauptplugins ab
    }

    return true;
}
```

#### `void OnUnload()`

- **Beschreibung:** Letzte Funktion, die vom SA-MP-Server aufgerufen wird, bevor Ihr Plugin aus dem Speicher entladen wird.
- **Verwendung:** Ideal zum Bereinigen von Ressourcen, Schließen von Verbindungen, Speichern von Zuständen und Sicherstellen, dass keine Ressourcen verloren gehen. Das SDK verwaltet das Entladen von Modulen (`Plugin_Module`) automatisch.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MeinPlugin entladen. Gebe Ressourcen frei...");
    // Für über Plugin_Module geladene Module ist keine manuelle Aktion erforderlich;
    // das SDK kümmert sich darum.
}
```

#### `unsigned int GetSupportFlags()`

- **Beschreibung:** Informiert den SA-MP-Server, welche Funktionen Ihr Plugin unterstützt und nutzen möchte.
- **Verwendung:** **Geben Sie immer `SUPPORTS_VERSION` (oder `SAMP_PLUGIN_VERSION`) zurück.** Die anderen Flags (`SUPPORTS_AMX_NATIVES`, `SUPPORTS_PROCESS_TICK`) werden automatisch vom SDK hinzugefügt, wenn die Makros `SAMP_SDK_WANT_AMX_EVENTS` und `SAMP_SDK_WANT_PROCESS_TICK` definiert sind. Dies vereinfacht die Wartung und vermeidet Fehler.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // Das SDK fügt die notwendigen Flags automatisch hinzu.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Erfordert:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beschreibung:** Wird immer dann aufgerufen, wenn ein neues Pawn-Skript (ein Gamemode oder Filterscript) auf dem Server geladen und initialisiert wird.
- **Verwendung:** Wenn Sie eine spezifische Logik für jedes AMX-Skript benötigen, z.B. benutzerdefinierte Natives registrieren (obwohl `Plugin_Native` dies automatisch tut) oder skriptspezifische Daten initialisieren.

```cpp
// main.cpp (mit definiertem SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxLoad(AMX* amx) {
    // amx repräsentiert die neu geladene Skriptinstanz.
    // Sie könnten zum Beispiel eine spezifische Public in diesem Skript aufrufen:
    // Pawn_Public_OnAmx("OnMyPluginLoaded", amx); // Hypothetisches Beispiel einer fortgeschritteneren API.
    Samp_SDK::Log("AMX-Skript geladen: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Erfordert:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beschreibung:** Wird aufgerufen, wenn ein Pawn-Skript vom Server entladen wird.
- **Verwendung:** Zum Bereinigen von spezifischen Ressourcen, die Sie diesem `AMX*` zugeordnet oder dafür allokiert haben.

```cpp
// main.cpp (mit definiertem SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX-Skript entladen: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Erfordert:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Beschreibung:** Wird wiederholt bei jedem "Tick" des Servers aufgerufen (normalerweise 20 Mal pro Sekunde oder alle 50 ms).
- **Verwendung:** Für kontinuierliche Hintergrundlogik, Timer, Zustandsaktualisierungen, die nicht von Spielerereignissen abhängen, oder Daten synchronisieren.
- **Vorsicht:** Vermeiden Sie hier blockierende oder rechenintensive Operationen, da diese zu Server-Lag führen können.

```cpp
// main.cpp (mit definiertem SAMP_SDK_WANT_PROCESS_TICK)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Alle 10 Sekunden (20 Ticks/Sek * 10 Sek = 200 Ticks)
        Samp_SDK::Log("Server aktiv seit %d Sekunden.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Abfangen von Pawn-Events

Das Makro `Plugin_Public` ist die primäre Brücke, um Pawn-Callbacks in Ihrem C++-Code zu empfangen.

#### Syntax und Deklaration

- `Plugin_Public(NameDerPublic, Typ1 Param1, Typ2 Param2, ...)`
- Der Name der C++-Funktion, die Sie deklarieren, **muss derselbe sein** wie der Pawn-Callback (z.B. `OnPlayerConnect`).
- Die C++-Parametertypen (`int`, `float`, `std::string`) werden vom SDK automatisch konvertiert.

```cpp
// Fängt OnPlayerText(playerid, text[]) ab
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    // ...
}
```

#### Automatisches Marshalling von Parametern

Das SDK kümmert sich automatisch um das Lesen des `cell stack` der AMX und die Konvertierung in die angegebenen C++-Typen:
- `int`: Direkt von `cell` konvertiert.
- `float`: Von `cell` unter Verwendung von `amx::AMX_CTOF` konvertiert.
- `std::string`: Das SDK liest die Adresse des Strings in der AMX, allokiert einen `std::string` in C++ und kopiert den Inhalt.

#### Kontrolle des Ablaufs: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

Der Rückgabewert Ihrer `Plugin_Public`-Funktion ist entscheidend und bestimmt den Ausführungsfluss des Callbacks:
- `return PLUGIN_PUBLIC_CONTINUE;` (Wert `1`): Zeigt an, dass die Ausführung des Callbacks **fortgesetzt** werden soll. Wenn andere Plugins diesen Callback ebenfalls abfangen, werden sie aufgerufen. Anschließend wird die ursprüngliche `public` im Pawn-Skript aufgerufen.
- `return PLUGIN_PUBLIC_STOP;` (Wert `0`): Zeigt an, dass die Ausführung des Callbacks **unterbrochen** werden soll. Weder andere Plugins noch die ursprüngliche `public` im Pawn-Skript werden für dieses Ereignis aufgerufen. Dies ist ideal, um ein System zu implementieren, das ein Standardverhalten von SA-MP "überschreibt" oder "blockiert".

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Friert den Spieler ein
        Pawn_Native(SendClientMessage, playerid, -1, Pawn_Format("Spieler %d eingefroren.", playerid));

        return PLUGIN_PUBLIC_STOP; // Verhindert, dass der Befehl von anderen Skripten verarbeitet wird.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Ermöglicht die Verarbeitung anderer Befehle.
}
```

### 3.3. `Plugin_Native`: Erstellen von nativen C++-Funktionen

`Plugin_Native` ermöglicht es Ihnen, die Funktionalität von Pawn mit hochperformantem C++-Code zu erweitern.

#### Syntax und feste Signatur

- `Plugin_Native(NameDerNative, AMX* amx, cell* params)`
- Die C++-Funktion muss genau diese Signatur haben: `cell NameDerNative(AMX* amx, cell* params)`.
- `NameDerNative` ist der Name, den die Pawn-Skripte verwenden werden.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementierung ...
    return 0;
}
```

#### Automatische Registrierung von Natives

> [!NOTE]
> Sie müssen `amx_Register` **nicht** manuell aufrufen. Das SDK erkennt alle Ihre `Plugin_Native`s (in jeder `.cpp`-Datei mit `SAMP_SDK_WANT_AMX_EVENTS`) und registriert sie automatisch in jedem geladenen AMX-Skript (`OnAmxLoad`).

#### Extraktion von Parametern: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Beschreibung:** Einfacherer Helfer zum sequentiellen Extrahieren mehrerer Parameter.
- **Verwendung:** `Register_Parameters(variable1, variable2, ...)`
- **Einschränkungen:** Für Eingabeparameter. Behandelt keine optionalen Parameter oder den Zugriff nach Index.
- **Unterstützte Typen:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extrahiert die 3 Parameter
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (Vollständige API: `Get`, `Get_REF`, `Set_REF`)

- **Beschreibung:** Eine Wrapper-Klasse, die eine objektorientierte Schnittstelle zum Zugriff auf die Parameter einer Native bietet. Leistungsstärker für komplexe Szenarien.
- **Konstruktion:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Beschreibung:** Gibt die Anzahl der an die Native übergebenen Parameter zurück.
- **Verwendung:** Wesentlich für den Umgang mit optionalen Parametern.

###### `p.Get<T>(size_t index)`

- **Beschreibung:** Extrahiert einen Eingabeparameter nach Index und konvertiert ihn in den Typ `T`.
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

- **Beschreibung:** Ruft den Wert eines **Referenzparameters** (Pawn-Pointer) ab und speichert ihn in `out_value`.
- **Verwendung:** Zum Lesen von Werten, die als Referenz von Pawn übergeben wurden.
- **Rückgabe:** `true`, wenn die AMX-Adresse gültig ist, `false` sonst.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Erhält die Werte der Referenzen (Pawn hat Adressen übergeben)
    p.Get_REF(1, health); // Liest den Wert von Float:health
    p.Get_REF(2, money);   // Liest den Wert von money
    
    Samp_SDK::Log("Spieler %d, Gesundheit: %.1f, Geld: %d", playerid, health, money);
    
    // Jetzt ändern
    health = 50.0f;
    money += 100;
    
    // Und in den Pawn-Speicher zurückschreiben
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

#### Rückgabe von Werten

- Ihre `Plugin_Native`-Funktion muss eine `cell` zurückgeben.
- Um einen `int` oder `bool` zurückzugeben, verwenden Sie einen Cast zu `cell`.
- Um einen `float` zurückzugeben, verwenden Sie `amx::AMX_FTOC(mein_float)`.

```cpp
// Gibt einen Bool zurück
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    int playerid = p.Get<int>(0);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Gibt einen Float zurück
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Gibt 100.0f zurück
}
```

### 3.4. `Pawn_*` Makros: Aufrufen von Pawn-Funktionen aus C++

Diese Makros sind das Gegenteil von `Plugin_Public` und `Plugin_Native`: Sie ermöglichen es Ihrem C++-Code, Pawn-Funktionen aufzurufen.

#### `Pawn_Native(NameDerNative, ...)`

- **Zweck:** Die empfohlene Methode, um SA-MP-Natives (oder Natives anderer Plugins) aus C++ aufzurufen.
- **Mechanismus:** Sucht den Pointer der Native im internen Cache des SDK (gefüllt durch `Amx_Register_Detour`). Wenn gefunden, wird die Native in einer `Amx_Sandbox`-Umgebung (einer gefälschten und isolierten AMX-Instanz) ausgeführt.
- **Performance:** Am effizientesten, da die teure Suche nach `publics` vermieden und direkt mit dem Native-Pointer interagiert wird.

#### `Pawn_Public(NameDerPublic, ...)`

- **Zweck:** Ruft eine spezifische öffentliche Funktion in einem Pawn-Skript auf.
- **Mechanismus:** Durchläuft die vom `Amx_Manager` verwalteten `AMX*`-Instanzen, sucht die `public` nach Namen und führt sie aus.
- **Performance:** Weniger effizient als `Pawn_Native` aufgrund der Suche und des tatsächlichen `amx_Exec`. `publics` sind im Allgemeinen langsamer als `natives`.
- **Verwendung:** Ideal zum Aufrufen benutzerdefinierter Ereignisse in Ihrem Gamemode/Filterscripts, die keine Natives sind.

#### `Pawn(NameDerFunktion, ...)`

- **Zweck:** Ein Komfortmakro, das versucht, zu erraten, ob die Funktion eine Native oder eine Public ist.
- **Mechanismus:** Versucht zuerst, als `Pawn_Native` aufzurufen. Wenn dies fehlschlägt (die Native wird nicht gefunden), versucht es, als `Pawn_Public` aufzurufen.
- **Performance:** Kann etwas langsamer sein als `Pawn_Native`, wenn die Funktion nativ ist, aufgrund des doppelten Suchversuchs. Für `publics` ist die Leistung dieselbe wie bei `Pawn_Public`.
- **Verwendung:** Für Funktionen, bei denen Sie nicht sicher sind, ob sie nativ oder öffentlich sind, oder um den Boilerplate-Code zu vermeiden, eine nach der anderen zu versuchen.

#### Syntax und Konventionen

- **Funktionsname:** Verwenden Sie immer den Pawn-Funktionsnamen **direkt, ohne Anführungszeichen**. Das SDK konvertiert ihn intern in einen String.
- **Parameter:** Übergeben Sie die C++-Parameter direkt.

```cpp
// Richtig:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Falsch (würde aber technisch aufgrund des Hashings funktionieren, vermeiden Sie dies):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling von Eingabeparametern

Das SDK konvertiert Ihre C++-Typen in das `cell`-Format der AMX und verwaltet den Speicher nach Bedarf:
-   `int`, `bool`, `long`, `enum` -> `cell`
-   `float`, `double` -> `cell` (mittels `amx::AMX_FTOC`)
-   `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (allokiert Speicher in der AMX, kopiert den String und übergibt die Adresse `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling von Ausgabeparametern (Referenzen: `int&`, `float&`, `std::string&`)

Dies ist eine Schlüsselfunktion für Komfort und Sicherheit. Bei Pawn-Funktionen, die einen Zeiger (Referenz) erwarten, automatisiert das SDK den gesamten Prozess der Speicherzuweisung/-freigabe und Datenkopie.

- **Anwendung:** Übergeben Sie Ihre Variable einfach als Referenz (`&`).
- **Mechanismus:** Das SDK allokiert Speicher im AMX-Heap, übergibt die AMX-Adresse an die Pawn-Funktion, erwartet, dass die Pawn-Funktion diese Adresse füllt, liest den Wert zurück und gibt den AMX-Speicher frei. Alles transparent.
- **Mit `std::string&`:** Das SDK allokiert einen Standardpuffer (256 Zellen) in der AMX für den String.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Standort von %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interieur:%d Welt:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### Das `Callback_Result`-Objekt: Vollständige Analyse

Alle `Pawn_*`-Aufrufe geben ein `Callback_Result`-Objekt zurück. Dieses Objekt ist ein sicherer Wrapper für das Ergebnis des Pawn-Aufrufs.

- `Callback_Result() noexcept`: Standardkonstruktor, zeigt Fehler an (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Konstruktor für Erfolg oder Fehler mit Wert.
- `explicit operator bool() const`: Ermöglicht die Verwendung von `if (result)`, um zu überprüfen, ob der Aufruf erfolgreich war.
- `operator cell() const`: Ermöglicht die Konvertierung des Ergebnisses in `cell`, um den Wert zu erhalten.
- `float As_Float() const`: Komfortfunktion, um das Ergebnis als `float` zu erhalten.
- `cell Value() const`: Gibt den Rohwert `cell` zurück.
- `bool Success() const`: Gibt `true` zurück, wenn der Pawn-Aufruf erfolgreich war.
- `int Get_Amx_Error() const`: Gibt den AMX-Fehlercode zurück, wenn der Aufruf fehlgeschlagen ist (0 für Erfolg).

```cpp
// Beispiel: Abrufen der Gesundheit eines Spielers.
// Die Native GetPlayerHealth(playerid, &Float:health) erwartet eine playerid und eine Referenz für die Gesundheit.
int playerid = 0; // Beispiel Spieler-ID
float player_health = 0.0f;

// Wir rufen GetPlayerHealth auf und übergeben playerid und player_health als Referenz.
// Das SDK kümmert sich um das Marshalling für den Ausgabeparameter 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Überprüft, ob der Aufruf erfolgreich war (Operator bool)
    // Der von result.As_Float() oder result (Operator cell) zurückgegebene Wert
    // wäre der Rückgabewert der *Native*, nicht der Ausgabeparameter.
    // Der Gesundheitswert wurde bereits in 'player_health' aktualisiert, aufgrund des Marshallings des Ausgabeparameters.
    Samp_SDK::Log("Spieler %d hat %.1f Gesundheit.", playerid, player_health);
} else {
    // Der Aufruf ist fehlgeschlagen, vielleicht existiert der Spieler nicht oder die Native wurde nicht gefunden.
    Samp_SDK::Log("Fehler beim Abrufen der Gesundheit von Spieler %d. AMX-Code: %d", playerid, result.Get_Amx_Error());
}

// Für Natives, die einen Wert zurückgeben und Ausgabeparameter verwenden (seltener, aber möglich),
// würden Sie beides verwenden:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param ist bereits aktualisiert
// }
```

### 3.5. `Plugin_Module`: Verwaltung dynamischer Module

Das Makro `Plugin_Module` ermöglicht es Ihrem Plugin, als "Loader" für andere Plugins zu fungieren und so eine modulare und erweiterbare Architektur zu schaffen.

#### Syntax und Zweck

- `Plugin_Module(const char* basis_dateiname, const char* modul_verzeichnis, const char* optionale_erfolgsmeldung)`
- `basis_dateiname`: Der **Basisname** der Moduldatei, **ohne Erweiterung** (z.B. für `my_module.dll` oder `my_module.so`, verwenden Sie `"my_module"`). Das SDK fügt automatisch die passende `.dll`- oder `.so`-Erweiterung hinzu.
- `modul_verzeichnis`: Der Pfad des Verzeichnisses, in dem sich die Moduldatei befindet (z.B. `"plugins/my_custom_modules"`). **Fügen Sie hier nicht den Dateinamen ein.** Das SDK erstellt den vollständigen Pfad (`modul_verzeichnis/basis_dateiname.ext`).
- `optionale_erfolgsmeldung`: Eine optionale Nachricht, die in der Serverkonsole protokolliert wird, wenn das Modul erfolgreich geladen wurde.

```cpp
// main.cpp, innerhalb von OnLoad()

// Lädt das Modul 'core_logic.dll' (oder 'core_logic.so'),
// das sich im Ordner 'modules/custom/' des Servers befindet.
if (!Plugin_Module("core_logic", "modules/custom", "Kernlogik-Modul erfolgreich geladen!"))
    return (Samp_SDK::Log("FATALER FEHLER: Das Modul 'core_logic' konnte nicht geladen werden!"), false);

// Lädt das Modul 'admin_system.dll' (oder 'admin_system.so'),
// das sich direkt im Ordner 'plugins/' des Servers befindet.
if (!Plugin_Module("admin_system", "plugins", "Administrationsmodul aktiviert."))
    Samp_SDK::Log("WARNUNG: Administrationsmodul konnte nicht geladen werden.");
```

#### Lebenszyklus eines Moduls

- **Laden:** Wenn `Plugin_Module` aufgerufen wird, führt das SDK Folgendes aus:
   1. Erstellt den vollständigen Dateipfad (z.B. `plugins/custom/core_logic.dll`).
   2. Verwendet `Dynamic_Library` (`LoadLibrary`/`dlopen`), um die Binärdatei zu laden.
   3. Ruft die Zeiger für die Lebenszyklusfunktionen des Moduls ab: `Load`, `Unload` und `Supports`.
   4. Ruft die `Load`-Funktion des Moduls auf und übergibt `ppData` des Hauptplugins.
   5. Wenn `Load` `true` zurückgibt, wird das Modul zur internen Liste der geladenen Module hinzugefügt.
- **Entladen:** Während `OnUnload` Ihres Hauptplugins entlädt das SDK alle Module, die über `Plugin_Module` geladen wurden. Dies geschieht in **umgekehrter Reihenfolge** zum Laden (das zuletzt geladene wird zuerst entladen), was entscheidend ist, um Abhängigkeiten zu verwalten und die korrekte Freigabe von Ressourcen sicherzustellen.

#### Vorteile der Modularisierung

- **Code-Organisation:** Teilen Sie große Plugins in kleinere, überschaubare Komponenten auf, jede in ihrer eigenen Moduldatei.
- **Wiederverwendbarkeit:** Erstellen Sie generische Module (z. B. ein Datenbankmodul, ein erweitertes Logsystemmodul), die von verschiedenen Plugins verwendet werden können, und fördern Sie so die Code-Wiederverwendung.
- **Dynamische Updates:** In kontrollierten Szenarien ermöglicht dies die Aktualisierung von Teilen Ihres Systems (durch Ersetzen einer `.dll` oder `.so` eines Moduls), ohne das gesamte Hauptplugin oder den gesamten Server neu kompilieren und neu starten zu müssen (obwohl dies ein strenges Versions- und Kompatibilitätsmanagement erfordert).

### 3.6. `Plugin_Call`: Aufrufen interner Plugin-Natives

Verwenden Sie `Plugin_Call`, um eine `Plugin_Native` aufzurufen, die **innerhalb Ihres eigenen Plugins** definiert ist.

#### Syntax und Performancevorteile

- `Plugin_Call(NameDerNative, Param1, Param2, ...)`
- **Vorteil:** Vermeidet den Overhead, die Native im AMX-Native-Array zu suchen. Das SDK verwaltet eine direkte Zuordnung von Namen-Hashes zu Funktionspointern für Ihre eigenen Natives, was dies zur schnellsten Methode macht, sie intern aufzurufen.
- **Erfordert:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logik zur Überprüfung des Levels
    return (playerid % 2 == 0) ? 1 : 0; // Beispiel: gerades Level für gerade IDs
}

void CheckAllPlayersLevel() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Ruft Ihre eigene Native auf
                Samp_SDK::Log("Spieler %d ist auf einem hohen Level!", i);
        }
    }
}
```

### **3.7. SDK-Dienstprogrammfunktionen**

#### `Samp_SDK::Log(const char* format, ...)`

- **Beschreibung:** Gibt Nachrichten in der Serverkonsole und in der Datei `server_log.txt` aus. Ein sicherer Wrapper für `logprintf`.
- **Verwendung:** Zum Debuggen, für Statusmeldungen und Fehler.
- **Mechanismus:** Intern ruft das SDK den Pointer für `logprintf` über `ppData[PLUGIN_DATA_LOGPRINTF]` ab. Die Funktion kümmert sich um die sichere Formatierung des Strings.

```cpp
// Überall in Ihrem Plugin
Samp_SDK::Log("Das Plugin wurde mit dem Wert %d und dem String '%s' initialisiert.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Empfohlen)

- **Beschreibung:** Formatiert einen String sicher (ähnlich `sprintf`) und gibt einen `std::string` zurück. Dies ist die **empfohlene und idiomatischste** Methode, Strings für die Verwendung in Ihrem Plugin zu formatieren.
- **Verwendung:** Ideal zum Erstellen formatierter Nachrichten, bevor sie an `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)` oder für andere String-Bedürfnisse in Ihrem C++-Code übergeben werden.
- **Mechanismus:** Intern ist `Plugin_Format` ein Makro, das `Samp_SDK::Format` aufruft. Es verwendet `vsnprintf`, um die exakte Länge des formatierten Strings zu bestimmen, und allokiert einen `std::string` mit ausreichender Kapazität, wodurch Pufferüberläufe vermieden werden.

```cpp
int playerid = 0; // Beispiel-ID
int health = 50;
std::string status_message = Plugin_Format("Spieler %d, Ihre aktuelle Gesundheit beträgt %d.", playerid, health); // Verwendung des Makros Plugin_Format
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, status_message);

// Kann auch für interne Logs verwendet werden
Samp_SDK::Log(Plugin_Format("DEBUG: Verarbeite Status für ID %d", playerid).c_str());
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Implementierungsdetail)

- **Beschreibung:** Die zugrunde liegende Implementierungsfunktion für die Stringformatierung, die sich im `Samp_SDK`-Namespace befindet.
- **Verwendung:** Wird normalerweise nicht direkt vom Benutzer aufgerufen. Das Makro `Plugin_Format` wird als Komfortfunktion für diese Funktion bereitgestellt, um die Namenskonventionen anderer SDK-Makros (`Plugin_Public`, `Plugin_Native`) zu wahren. Sie würden sie nur direkt aufrufen, wenn Sie das Makro `Plugin_Format` aus einem bestimmten Grund vermeiden wollten.

```cpp
// Beispiel, wie Samp_SDK::Format funktioniert, aber bevorzugen Sie Plugin_Format
std::string raw_status = Samp_SDK::Format("Nur für interne Verwendung: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Beschreibung:** Konvertiert eine AMX-String-Adresse (`cell amx_addr`) in einen C++ `std::string`.
- **Verwendung:** Hauptsächlich innerhalb von `Plugin_Native`, wenn Sie auf Strings zugreifen müssen, die nicht automatisch von `Register_Parameters` oder `Native_Params` konvertiert werden (z.B. wenn der Pawn-Parameter ein `const` `string` ist und nicht als `std::string` in Ihrer `Plugin_Native` oder `Plugin_Public` für automatisches Marshalling deklariert wurde).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Ruft die String-Adresse in der AMX ab

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("AMX-String: %s", cpp_string.c_str());

    return 1;
}
```

## 4. **Interne Anatomie und Architektur des SDK**

Dieser Abschnitt enthüllt die zugrunde liegenden Mechanismen des SAMP SDK und erforscht seine Architektur, die Schlüsselkomponenten und wie sie interagieren, um die High-Level-Abstraktion bereitzustellen. Ein tiefes Verständnis dieser Interna befähigt den Entwickler, die Nutzung des SDK zu optimieren, komplexe Probleme zu debuggen und sogar seine Funktionen zu erweitern.

### 4.1. `core.hpp`: Die minimalistische Grundlage

Der `Samp_SDK::Core` ist ein `Singleton`, der als initialer und zentralisierter Zugriffspunkt auf die Low-Level-Daten dient, die von der SA-MP Plugin-Umgebung bereitgestellt werden. Seine Hauptverantwortung ist es, die essentiellen Funktionen zu kapseln und offenzulegen.

- **`Samp_SDK::Core::Instance()`**:
   - **Beschreibung:** Gibt die einzige globale Instanz der `Core`-Klasse zurück. Dies ist ein `Singleton`-Designmuster, um sicherzustellen, dass der Zugriff auf die Plugin-Daten (`ppData`) konsistent und zentralisiert ist.
   - **Mechanismus:** Die Instanz wird einmalig initialisiert, wenn `Core::Instance().Load(ppData)` in der `Load()`-Funktion Ihres Plugins aufgerufen wird.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Beschreibung:** Ermöglicht sicheren, indexierten Zugriff auf die Funktionszeiger der AMX-API. Das Array `pAMXFunctions` (erhalten über `ppData[PLUGIN_DATA_AMX_EXPORTS]`) enthält die Adressen kritischer Funktionen wie `amx_Exec`, `amx_Register` usw.
   - **Auswirkung:** Anstatt `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)` zu verwenden, bietet das SDK typsichere Wrapper im `amx::` Namespace (z.B. `amx::Exec(...)`), wodurch der Code lesbarer und weniger fehleranfällig wird.
   - **Internes Beispiel (`amx_api.hpp`):**
      ```cpp
      // Vereinfachter Ausschnitt aus amx_api.hpp
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
   - **Beschreibung:** Ein Zeiger auf die SA-MP-Funktion `logprintf`, die die Standardschnittstelle zum Drucken von Nachrichten in der Serverkonsole und in `server_log.txt` ist.
   - **Mechanismus:** `Samp_SDK::Log` ist ein sicherer Wrapper, der diesen Zeiger verwendet, um sicherzustellen, dass Ihre Nachrichten in der SA-MP-Umgebung korrekt angezeigt werden.

### **4.2. `platform.hpp` und `version.hpp`: Kompatibilität und Metadaten**

Diese Header sind die Basis für die Portabilität und Optimierung des SDK, passen es an verschiedene Kompilierungsumgebungen an und nutzen spezifische Funktionen des modernen C++ aus.

- **Plattform- und Architekturerkennung:**
   - **Mechanismus:** Verwendet Präprozessor-Makros (`#if defined(WIN32)`, `#if defined(__linux__)` usw.), um das Betriebssystem zu identifizieren.
   - **Architekturprüfung:** Enthält `static_assert` oder `#error`, um sicherzustellen, dass das Plugin für x86 (32-Bit) kompiliert wird, eine kritische Anforderung für die Kompatibilität mit SA-MP und den Hooking-Mechanismus.
   - **Verwaltung des Symbol-Exports:**
      - `SAMP_SDK_EXPORT`: Ein in `platform.hpp` definiertes Makro, das sich zu `extern "C"` erweitert und unter Linux `__attribute__((visibility("default")))` hinzufügt. Unter Windows stellt es nur `extern "C"` sicher, da das SDK `pragma comment(linker, "/EXPORT:...")` (für MSVC) oder den MinGW-Standard verwendet, um die Hauptfunktionen zu exportieren.
      - Dies stellt sicher, dass die Lebenszyklusfunktionen des Plugins (`Supports`, `Load`, `Unload` usw.) korrekt aus Ihrer DLL/SO exportiert werden, unabhängig von der Kompilierungsumgebung, **ohne dass `.def`-Dateien oder das manuelle Hinzufügen von `__attribute__((visibility("default")))`** in Ihrer Implementierung erforderlich sind.
   - **Beispiel (`platform.hpp` - relevanter Ausschnitt):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // Für MSVC wird der Export durch Pragma-Linker-Befehle verwaltet
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // Für GCC/Clang unter Linux verwenden wir das Sichtbarkeitsattribut
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... andere Definitionen ...
      ```
   - **Beispiel (`samp_sdk.hpp` - relevanter Implementierungsausschnitt):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // Unter Windows (MSVC) verwenden wir pragma comment, um die Funktionen zu exportieren.
          // Dies eliminiert die Notwendigkeit einer .def-Datei.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... andere Exporte ...
      #endif

      // Implementierung der exportierten Funktionen
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... andere Funktionen ...
      #endif
      ```

- **Optimierungs- und Branch-Vorhersage-Makros:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mechanismus:** `__forceinline` (MSVC) oder `__attribute__((always_inline)) inline` (GCC/Clang). Schlägt dem Compiler dringend vor, den Funktionsrumpf direkt an der Aufrufstelle einzufügen, wodurch der Overhead eines tatsächlichen Funktionsaufrufs entfällt.
      - **Verwendung:** Wird auf kleine und performanzkritische Funktionen innerhalb des SDK angewendet.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mechanismus:** `[[likely]]` / `[[unlikely]]` (C++20) oder `__builtin_expect` (GCC/Clang). Hinweise an den Compiler, welcher Pfad eines `if/else` wahrscheinlicher genommen wird.
      - **Auswirkung:** Hilft dem Compiler, effizienteren Code für die Branch-Vorhersage zu generieren, wodurch die CPU-Latenz reduziert wird.
      - **Beispiel (`platform.hpp`):**
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

- **Standard C++-Definitionen (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mechanismus:** Makros, die auf dem Wert von `__cplusplus` und `_MSVC_LANG` basieren.
   - **Verwendung:** Ermöglichen es dem SDK, neuere C++-Funktionen (wie `std::apply` und `if constexpr` aus C++17 oder `std::is_same_v` aus C++17) zu verwenden, wenn verfügbar, während die Kompatibilität mit älteren Standards erhalten bleibt.
   - **Beispiel (`version.hpp` - Verwendung von `if constexpr`):**
      ```cpp
      // Vereinfachter Ausschnitt aus public_dispatcher.hpp
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

### 4.3. `function_hook.hpp`: Der x86 Intercept-Engine

Dieser Header definiert den Low-Level-Mechanismus zum Durchführen von Funktionshooks (Interzeptionen), der für den Betrieb des SDK grundlegend ist. Er ist streng von der x86 (32-Bit)-Architektur abhängig.

- **`X86_Detour`**:
   - **Beschreibung:** Eine Klasse, die die Logik zur Überschreibung des Anfangs einer Funktion im Speicher mit einer Sprunganweisung zu einer Umleitungsfunktion kapselt.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mechanismus:** Auf x86 hat die relative Sprunganweisung (`JMP`) normalerweise 5 Bytes: `0xE9` (Opcode für JMP near, relative), gefolgt von 4 Bytes, die den Offset (Verschiebung) der Zieladresse relativ zur nächsten Anweisung darstellen.
      - **Beispiel einer Anweisung:** `E9 XX XX XX XX` (wobei `XX` die Bytes der Verschiebung sind).
   - **`Apply(void* target, void* detour)`**:
      - **Aktion:** Installiert den Hook. Zuerst werden die `JUMP_INSTRUCTION_SIZE` Originalbytes der `target`-Funktion (`original_bytes_`) gespeichert. Anschließend wird die relative Adresse des `detour` in Bezug auf `target` berechnet und der Anfang von `target` mit der `JMP`-Anweisung überschrieben.
      - **Beispiel der relativen Adressberechnung:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Adresse der Umleitung - (Adresse des Ziels + Größe der JMP-Anweisung)
         ```
   - **`Revert()`**:
      - **Aktion:** Deinstalliert den Hook, indem die `original_bytes_` in der `target`-Funktion wiederhergestellt werden.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mechanismus:** Unter Windows wird `VirtualProtect` verwendet; unter Linux `mprotect`. Diese Systemaufrufe ändern die Berechtigungen der Speicherseite, auf der sich die Funktion befindet, auf `EXECUTE_READWRITE` (Windows) oder `PROT_WRITE | PROT_EXEC` (Linux), wodurch der Code zur Laufzeit geändert werden kann.
      - **Beispiel (`Unprotect_Memory`):**
         ```cpp
         // Vereinfachter Ausschnitt aus function_hook.hpp
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
      - **Sicherheitsmechanismus (Rekursionsschutz):** Diese Funktion ist entscheidend, um Endlosschleifen zu vermeiden, wenn der Detour die Originalfunktion aufrufen muss. Sie **deinstalliert den Hook (`detour_.Revert()`) vorübergehend**, ruft die Originalfunktion auf (`Get_Original()(args...)`) und **installiert den Hook dann erneut (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Ein Zähler, der sicherstellt, dass der Hook nur dann erneut installiert wird, wenn der oberste Originalaufruf abgeschlossen ist, wodurch sichere rekursive Aufrufe der Originalfunktion (wenn die Originalfunktion beispielsweise rekursiv ist) ermöglicht werden. `thread_local` stellt sicher, dass der `recursion_guard` für jeden Thread isoliert ist, was in Multi-Thread-Umgebungen wichtig ist.
      - **Beispiel (`Call_Original` mit Scope_Guard):**
         ```cpp
         // Vereinfachter Ausschnitt aus function_hook.hpp
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

Dieser `Singleton` ist das Nervenzentrum der SDK-Interaktion mit der SA-MP AMX Virtual Machine. Er koordiniert die Installation der von `function_hook.hpp` bereitgestellten Hooks in den vom Server exponierten AMX API-Funktionen und leitet den Ausführungsfluss an die SDK-Logik um.

- **`Activate()` / `Deactivate()`**:
   - **Beschreibung:** Öffentliche Methoden zum Installieren und Deinstallieren aller erforderlichen Hooks. Werden in `OnLoad()` bzw. `OnUnload()` Ihres Plugins aufgerufen.
   - **Mechanismus:** Ruft die AMX-Funktionszeiger (wie `amx_Register`, `amx_Exec` usw.) mit `Core::Instance().Get_AMX_Export(...)` ab und installiert die Detours.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Gehookte Funktion:** `amx_Register`
   - **Zweck:** Fängt die Registrierung *aller* Natives (durch SA-MP, andere Plugins oder Gamemode) ab.
   - **Aktion:** Ruft `Interceptor_Manager::Instance().Cache_Natives()` auf, um die Zeiger und Namen der Natives in einem internen Cache zu speichern.
   - **Auswirkung:** Dieser Cache ist entscheidend für die Performance von `Pawn_Native`, da er eine extrem schnelle Suche des Native-Zeigers ermöglicht, anstatt einer teuren Suche im AMX.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Gehookte Funktion:** `amx_Exec`
   - **Zweck:** **Dies ist der kritischste Hook.** Er fängt *jede* Codeausführung in der AMX ab, einschließlich des Aufrufs von Pawn-`publics`.
   - **Interceptionsmechanismus für `Plugin_Public`:**
      1. Wenn `amx_Exec` für eine `public` (oder `AMX_EXEC_MAIN`) aufgerufen wird, wird der `Amx_Exec_Detour` ausgeführt.
      2. Er ruft den Namen der `public` ab (mit `Get_Public_Name_By_Index` oder `tl_public_name`).
      3. Fragt den `Public_Dispatcher::Instance().Dispatch()` ab, um zu prüfen, ob C++-Handler für diesen Namen registriert sind.
      4. Wenn Handler vorhanden sind, führt er sie aus. Der `Public_Dispatcher` kümmert sich um das `marshalling` der Parameter von der AMX in die korrekten C++-Typen.
      5. Basierend auf dem Rückgabewert des `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`) entscheidet er, ob er die ursprüngliche `amx_Exec` aufruft (`Get_Amx_Exec_Hook().Call_Original(...)`) oder die Ausführung der Pawn-`public` beendet.
      6. **Stack-Manipulation:** Wenn die Ausführung der Pawn-`public` unterbrochen wird (`PLUGIN_PUBLIC_STOP`), korrigiert der `Amx_Exec_Detour` den AMX-Stack (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`), um Inkonsistenzen zu vermeiden.
   - **Beispiel (`Amx_Exec_Detour`):**
      ```cpp
      // Vereinfachter Ausschnitt aus interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          // ... Logik zur Bestimmung des Public-Namens ...
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
   - **Gehookte Funktion:** `amx_FindPublic`
   - **Zweck:** Fängt die Suche nach `publics` nach Namen ab.
   - **Mechanismus der "Ghost Publics":** Wenn die ursprüngliche `amx_FindPublic` eine `public` im Pawn nicht findet, aber der `Public_Dispatcher` einen C++-Handler für diesen Namen registriert hat, gibt dieser Hook `AMX_ERR_NONE` und einen speziellen `index` (`PLUGIN_EXEC_GHOST_PUBLIC`) zurück. Dies lässt die SA-MP API "denken", dass die `public` existiert, wodurch der nachfolgende `amx_Exec`-Aufruf (für diesen speziellen Index) vom `Amx_Exec_Detour` abgefangen werden kann, der dann zum C++-Handler umleitet.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Wird verwendet, um den Namen der `public` an den `Amx_Exec_Detour` zu übergeben, wenn ein "Ghost Public" erkannt wird, da `amx_Exec` nur den Index, nicht den Namen, empfängt.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Gehookte Funktionen:** `amx_Init` / `amx_Cleanup`
   - **Zweck:** Verwalten der Liste aktiver `AMX*`-Instanzen.
   - **Aktion:** `Amx_Init_Detour` ruft `Amx_Manager::Instance().Add_Amx()` auf, und `Amx_Cleanup_Detour` ruft `Amx_Manager::Instance().Remove_Amx()` auf.

### 4.5. `amx_manager.hpp`: Verwalten von `AMX*`-Instanzen

Dieses `Singleton` führt ein dynamisches Register aller aktuell auf dem Server geladenen AMX-Virtual-Machines. Es ist unerlässlich für Funktionen, die mit "allen Skripten" interagieren oder ein bestimmtes Skript finden müssen.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Beschreibung:** Eine Liste von Zeigern zu allen `AMX*`-Instanzen, die initialisiert wurden (Gamemode und Filterscripts).
   - **Verwaltung:** Wird von den Hooks `Amx_Init_Detour` gefüllt und von `Amx_Cleanup_Detour` geleert.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Zweck:** Schützt `loaded_amx_` vor gleichzeitigem Zugriff in Multi-Thread-Umgebungen (obwohl SA-MP größtenteils Single-Thread ist, ist dies eine gute Sicherheitspraxis). `std::shared_mutex` erlaubt mehrere gleichzeitige Leser, aber nur einen Schreiber.
- **`std::atomic<uint32_t> generation_`**:
   - **Zweck:** Ein Zähler, der jedes Mal inkrementiert wird, wenn ein AMX hinzugefügt oder entfernt wird.
   - **Verwendung:** Wird vom `Caller_Cache` in `callbacks.hpp` verwendet, um zu erkennen, wenn sich die Liste der AMXs geändert hat, wodurch Caches für die Suche nach `publics` ungültig werden und sichergestellt wird, dass die `Pawn_Public`-Aufrufe immer mit aktualisierten Informationen arbeiten. Dies optimiert die Leistung, indem wiederholte Suchen in einem unveränderten Zustand vermieden werden.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Beschreibung:** Durchsucht `loaded_amx_` (vom neuesten zum ältesten, was in der Regel den Gamemode oder das relevanteste Filterscript zuerst platziert), um die `public` mit dem angegebenen Namen zu finden.
   - **Mechanismus:** Verwendet `amx::Find_Public` für jede `AMX*`-Instanz.
   - **Auswirkung:** Ist die Grundlage für `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: Der `Plugin_Public`-Callback-Router

Dieses `Singleton` ist die Komponente, die Pawn-`public`-Namen den entsprechenden C++-`Plugin_Public`-Funktionen zuordnet.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Schlüssel:** Der FNV1a-Hash des `public`-Namens (z.B. `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Wert:** Ein `std::vector` von `std::function<cell(AMX*)>`, wobei jede `std::function` ein registrierter C++-Handler für diese `public` ist.
   - **Mechanismus:** Der `std::vector` ermöglicht es, mehrere `Plugin_Public`s für denselben Callback zu registrieren (z.B. mehrere Plugins, die `OnPlayerCommandText` abfangen wollen). Die Handler werden in umgekehrter Reihenfolge der Registrierung ausgeführt.
- **`Public_Registrar`**:
   - **Mechanismus:** Dies ist eine Template-Klasse, deren Makro `PLUGIN_PUBLIC_REGISTRATION` eine statische globale Instanz erstellt. Im statischen Konstruktor (`static bool registered = [...]`) registriert sie ihren `Plugin_Public`-Handler im `Public_Dispatcher`. Dies ist ein "Compile-Time/Initialisierungszeit"-Registrierungsmuster.
   - **Beispiel (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Registrar<decltype(&name), &name, hash_##name> registrar_##name;
      ```

- **`Public_Traits` und `Wrapper()`**:
   - **Mechanismus:** `Public_Traits` ist ein Trait-Template, das mithilfe von Metaprogrammierung eine Funktion `static cell Wrapper(AMX* amx)` generiert.
   - **Zweck:** Dieser `Wrapper` ist die `Amx_Handler_Func`, die der `Public_Dispatcher` tatsächlich speichert und aufruft. Er ist verantwortlich für:
      1. Aufrufen von `Public_Param_Reader::Get_Public_Params(amx, args...)`, um die Parameter aus dem AMX-Stack zu extrahieren.
      2. Aufrufen Ihrer eigentlichen C++-`Plugin_Public`-Funktion (`func_ptr`) mit den bereits in die korrekten C++-Typen konvertierten Parametern.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Beschreibung:** Eine Reihe von rekursiven Template-Funktionen, die die Werte vom AMX-Stack lesen und sie in die in der `Plugin_Public`-Deklaration angegebenen C++-Typen konvertieren.
   - **Mechanismus:** Verwendet `Get_Stack_Cell()` für den Zugriff auf die `cell`s im Stack. Nutzt `if constexpr` (C++17+) oder `std::is_same<T>::value` (C++14), um die korrekte Konvertierung anzuwenden (`amx::AMX_CTOF` für Float, `Samp_SDK::Get_String` für String, direkter Cast für Int).

### 4.7. `native.hpp`: Verwalten und Aufrufen von Plugin-Natives

Dieser Header widmet sich der Erstellung und Verwaltung von C++-Natives, die Ihr Plugin für Pawn bereitstellt.

- **`Native_List_Holder`**:
   - **Beschreibung:** Ein globales `Singleton`, das alle in Ihrem Plugin deklarierten `Plugin_Native`s (aus allen `.cpp`-Dateien, die `SAMP_SDK_WANT_AMX_EVENTS` verwenden) speichert.
   - **`std::vector<Native> natives_`**: Enthält `Native`-Objekte (die den Namen der Native und den Zeiger auf die C++-Funktion `Native_Handler` speichern).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Eine Hash-optimierte Map für schnelle Suchen nach internen `Plugin_Native`s (verwendet von `Plugin_Call`).
- **`Native_Registrar`**:
   - **Mechanismus:** Ähnlich wie der `Public_Registrar` ist dies eine Template-Klasse, deren Makro `Plugin_Native` eine statische globale Instanz erstellt. In ihrem Konstruktor fügt sie die Native dem `Native_List_Holder` hinzu.
   - **Auswirkung:** Ermöglicht es Ihnen, `Plugin_Native`s in mehreren `.cpp`-Dateien zu deklarieren, ohne sich um die manuelle Registrierung kümmern zu müssen. Alle werden automatisch gesammelt.
- **`Native_Registry`**:
   - **Beschreibung:** Eine Hilfsklasse, die beim `OnAmxLoad` die vollständige Liste der `Native`s vom `Native_List_Holder` nimmt und sie in ein `AMX_NATIVE_INFO`-Array formatiert.
   - **Mechanismus:** Ruft `amx::Register(amx, amx_natives_info_.data(), -1)` auf, um alle Ihre Natives in der gerade geladenen AMX-Instanz zu registrieren.
- **`Plugin_Call_Impl(...)`**:
   - **Beschreibung:** Die zugrunde liegende Implementierung des Makros `Plugin_Call`.
   - **Mechanismus:** Verwendet `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)`, um den Pointer der C++-Funktion direkt zu erhalten.
   - **Umgebung:** Führt die Native in einer `Amx_Sandbox`-Umgebung (isoliert) aus, um den temporären Stack und Heap zu verwalten, ähnlich wie `Pawn_Native` funktioniert.

### 4.8. `callbacks.hpp` & `amx_memory.hpp`: C++ -> Pawn-Aufrufe und RAII

Diese Header bilden das Rückgrat für das Aufrufen von Pawn-Funktionen aus C++ (`Pawn_*`-Makros) und gewährleisten die Speichersicherheit.

- **`Amx_Sandbox`**:
   - **Beschreibung:** Eine `thread_local` Struktur, die eine minimale und isolierte `AMX`-Umgebung für `Pawn_Native`- und `Plugin_Call`-Aufrufe simuliert.
   - **Mechanismus:** Besitzt eine eigene `AMX`-Struktur, `AMX_HEADER` und einen `std::vector<unsigned char> heap`, um den Speicher eines Skripts zu simulieren. Dies ermöglicht, dass `amx::Push`, `amx::Allot` usw. aufgerufen werden, ohne den Zustand realer, laufender Pawn-Skripte zu beeinträchtigen.
   - **`thread_local`:** Stellt sicher, dass jeder Thread seine eigene `Amx_Sandbox` hat, wodurch Race Conditions verhindert werden, wenn das SDK in einem Multi-Thread-Kontext verwendet wird (z.B. ein zukünftiger Thread-Pool für Nicht-Pawn-Operationen).
   - **Beispiel (`Amx_Sandbox`):**
      ```cpp
      // Vereinfachter Ausschnitt aus callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Simulierter Speicher für Stack/Heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Initialisiert die AMX und den Header
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
   - **Beschreibung:** Eine Reihe überladener Template-Funktionen, die das `Marshalling` *jedes* C++-Parameters in das von AMX erwartete `cell`-Format und umgekehrt für Ausgabeparameter verwalten.
   - **Eingabeverarbeitung:**
       - Für `int`, `float`, `bool`: Konvertiert direkt in `cell`.
       - Für `const char*`, `std::string`: Allokiert Speicher im `Amx_Sandbox`-Heap (oder echtem AMX für `Pawn_Public`), kopiert den String und legt die AMX-Adresse auf den Stack.
   - **Ausgabeverarbeitung (`is_output_arg`):**
       - **Mechanismus:** Wenn ein Argument eine nicht-konstante Lvalue-Referenz ist (erkannt durch das Trait `is_output_arg`), legt der `Parameter_Processor` nicht den Wert, sondern eine *AMX-Adresse* für eine temporär im Heap allokierte `cell` auf den Stack.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Nach dem Aufruf der Pawn-Native wird eine Liste von Lambdas (`post_call_updaters`) ausgeführt. Jedes Lambda ist dafür verantwortlich, den endgültigen Wert der im AMX allokierten `cell` zu lesen und ihn der ursprünglichen C++-Variable zuzuweisen (z.B. `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mechanismus:** Ein `std::integral_constant` (Typ-Trait), das zur Kompilierungszeit auswertet, ob ein C++-Parametertyp eine modifizierbare Referenz ist (z.B. `int&`, `float&`, `std::string&`). Dies ermöglicht es dem `Parameter_Processor`, Eingabe- von Ausgabeparametern zu unterscheiden.
   - **Beispiel (`is_output_arg`):**
      ```cpp
      // Vereinfachter Ausschnitt aus callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Beschreibung:** Eine RAII-Klasse (`Resource Acquisition Is Initialization`), die die Allokation und Freigabe von Speicher im AMX kapselt.
   - **Mechanismus:** Im Konstruktor ruft sie `amx::Allot` auf, um eine `amx_addr` und eine `phys_addr` zu erhalten. Im Destruktor ruft sie `amx::Release` auf, um diesen Speicher freizugeben.
   - **Auswirkung:** **Entscheidend, um Speicherlecks im AMX-Heap zu verhindern.** Stellt sicher, dass temporärer Speicher, der für Strings oder Ausgabeparameter verwendet wird, immer freigegeben wird, selbst wenn Ausnahmen auftreten oder frühzeitig zurückgekehrt wird.

### 4.9. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Abstrahierter AMX-Zugriff

Diese Header bieten die grundlegenden Definitionen und High-Level-Tools für die Interaktion mit Pawn.

- **`amx_defs.h`**:
   - **Inhalt:** Enthält die Rohdefinitionen der AMX-Strukturen (`AMX`, `AMX_HEADER`), Typen (`cell`, `ucell`) und Fehlermeldungen (`AmxError`). Definiert auch `AMX_NATIVE` und `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Verwendet Pack-Attribute (`#pragma pack(push, 1)` / `__attribute__((packed))`), um sicherzustellen, dass die AMX-Strukturen das korrekte Speicherlayout haben, was für die Interoperabilität entscheidend ist.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Beschreibung:** Die Haupt-Template-Funktion zum Aufrufen der vom Server bereitgestellten AMX-API-Funktionen.
   - **Mechanismus:** Ruft den Funktionszeiger über `Core::Instance().Get_AMX_Export(Index)` ab und ruft ihn auf. Zentralisiert die Fehlerbehandlung, falls der Funktionszeiger nicht verfügbar ist.
   - **Auswirkung:** Konvertiert Low-Level-Aufrufe (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) in idiomatische und typsichere C++-Aufrufe (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Beschreibung:** Wesentliche Funktionen zum Konvertieren von `cell`-Werten in `float` und umgekehrt, wobei eine bitweise Uminterpretation des Speichers durchgeführt wird.
   - **`static_assert`:** Enthält `static_assert`, um sicherzustellen, dass `sizeof(cell) == sizeof(float)` zur Kompilierungszeit, wodurch Fehler auf Plattformen mit unterschiedlichen Typgrößen verhindert werden.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Beschreibung:** Helfer zum Konvertieren einer AMX-Stringadresse in einen `std::string`.
   - **Mechanismus:** Ruft zuerst die physische Adresse (`cell* phys_addr`) des Strings in der AMX mit `amx::Get_Addr` ab. Verwendet dann `amx::STR_Len`, um die Länge zu bestimmen, und `amx::Get_String`, um die Bytes in einen `std::string` zu kopieren.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Beschreibung:** Die Basis-Stringformatierungsfunktion (`printf`-ähnlich) für das SDK.
   - **Mechanismus:** Verwendet `vsnprintf` in zwei Durchgängen: zuerst, um die erforderliche Stringlänge zu bestimmen, und dann, um den String in den dynamisch zugewiesenen `std::string` zu formatieren. Dies verhindert Pufferüberläufe.

## 5. Kompilierung und Bereitstellung

### Anforderungen an Architektur und Plattform

- Ihr Plugin **MUSS** für die Architektur **x86 (32-Bit)** kompiliert werden. Der Hooking-Mechanismus des SDK ist spezifisch für diese Architektur.
- Unterstützte Plattformen: Windows (.dll) und Linux (.so).

### Beispiele für Kompilierungsbefehle

#### **MSVC (Visual Studio)**

1. Erstellen Sie ein neues Projekt für eine "Dynamic-Link Library (DLL)".
2. Stellen Sie in den Projekteinstellungen die "Lösungsplattform" auf **x86** ein.
3. Stellen Sie sicher, dass der C++-Sprachstandard mindestens C++14 ist.

#### **GCC / Clang (Linux)**

```bash
# Für ein Plugin namens 'my_plugin.so' aus 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Kompiliert für 32-Bit.
- `-shared`: Erstellt eine freigegebene Bibliothek (`.so`).
- `-std=c++17`: Definiert den C++-Standard auf C++17 (kann `c++14` oder `c++20` sein).
- `-O2`: Optimierungsstufe 2.
- `-fPIC`: Erzeugt position-unabhängigen Code, notwendig für freigegebene Bibliotheken.
- `-Wall -Wextra`: Aktiviert zusätzliche Warnungen, um Fehler abzufangen.
- `-Wl,--no-undefined`: Verhindert die Erstellung der Bibliothek, wenn undefinierte Symbole vorhanden sind.

#### **GCC / Clang (MinGW unter Windows)**

```bash
# Für ein Plugin namens 'my_plugin.dll' aus 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Linkt die C++-Standardbibliothek statisch. Unerlässlich, um zu vermeiden, dass Ihr Plugin von compilerspezifischen Laufzeit-DLLs abhängt, die auf dem System des Benutzers möglicherweise nicht vorhanden sind.
- `-static-libgcc`: Linkt die GCC-Bibliothek statisch.

### Überlegungen zur Verteilung

- **Dateiname:** Ihr Plugin muss die Erweiterung `.dll` (Windows) oder `.so` (Linux) haben. Beispiel: `my_plugin.dll`.
- **Speicherort:** Legen Sie die kompilierte Datei in den Ordner `plugins/` Ihres SA-MP-Servers.
- **server.cfg:** Fügen Sie den Namen Ihres Plugins (unter Windows ohne Erweiterung) der Zeile `plugins` in `server.cfg` hinzu.
   ```
   plugins my_plugin (wenn Linux, my_plugin.so)
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