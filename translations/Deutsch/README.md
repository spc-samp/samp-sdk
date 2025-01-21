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

Das SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) ist eine umfassende Sammlung von C-Dateien und Headers sowie Elementen, die es Entwicklern ermöglichen, Plugins für den SA-MP-Server zu erstellen. Dieses SDK bietet eine Grundlage für die Erweiterung der Funktionalität des SA-MP-Servers durch native Funktionen und ermöglicht es Entwicklern, Funktionen zu implementieren, die über das in Pawn-Skripten Verfügbare hinausgehen.

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

- [samp-sdk](#samp-sdk)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [Kernkomponenten](#kernkomponenten)
    - [AMX-System](#amx-system)
      - [Core AMX Headers](#core-amx-headers)
    - [Plattform-Unterstützung](#plattform-unterstützung)
    - [Plugin-System](#plugin-system)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [AMX Native Funktionen](#amx-native-funktionen)
  - [Technische Details](#technische-details)
    - [Speicherverwaltung](#speicherverwaltung)
    - [Speicheroperationen](#speicheroperationen)
    - [Fehlerbehandlung](#fehlerbehandlung)
    - [String-Behandlung](#string-behandlung)
    - [String-Operationen](#string-operationen)
  - [Unicode-Unterstützung](#unicode-unterstützung)
    - [Unicode-Operationen](#unicode-operationen)
  - [Plattformübergreifende Kompatibilität](#plattformübergreifende-kompatibilität)
  - [Systemanforderungen](#systemanforderungen)
    - [Compiler-Unterstützung](#compiler-unterstützung)
  - [Best Practices](#best-practices)
  - [Interne Strukturen](#interne-strukturen)
    - [AMX Header Struktur](#amx-header-struktur)
  - [Erweiterte Funktionen](#erweiterte-funktionen)
    - [JIT-Compilation-Unterstützung](#jit-compilation-unterstützung)
    - [Debug-Schnittstelle](#debug-schnittstelle)
    - [Public Function Schnittstelle](#public-function-schnittstelle)
  - [Versionsinformationen](#versionsinformationen)
    - [Versionskompatibilität](#versionskompatibilität)

## Kernkomponenten

### AMX-System

Der AMX (Abstract Machine eXecutor) ist die virtuelle Maschine, die Pawn-Skripte in SA-MP ausführt. Das SDK bietet umfangreiche Unterstützung für die Interaktion mit AMX durch verschiedene C- und Header-Dateien:

#### Core AMX Headers

1. **amx.h**

    Die Haupt-Header-Datei, die alle AMX-bezogenen Funktionalitäten zusammenfasst. Sie enthält:
    - Kern-AMX-Funktionen für Skriptausführung
    - Speicherverwaltung
    - Native Funktionsregistrierung
    - String-Behandlung
    - UTF-8-Unterstützung

    Wichtige Funktionen sind:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    ```

2. **amx_cell.h**

    Definiert die grundlegenden Datentypen, die im AMX-System verwendet werden:
    ```c
    #if PAWN_CELL_SIZE==32
        typedef uint32_t  ucell;
        typedef int32_t   cell;
    #elif PAWN_CELL_SIZE==64
        typedef uint64_t  ucell;
        typedef int64_t   cell;
    #endif
    ```

3. **amx_structures.h**

    Enthält wesentliche Strukturen für den AMX-Betrieb:

    ```c
    typedef struct tagAMX {
        unsigned char _FAR *base;    // Basisadresse
        unsigned char _FAR *data;    // Datensegment
        AMX_CALLBACK callback;       // Callback-Funktion
        AMX_DEBUG debug;            // Debug-Callback
        cell cip;                   // Code-Instruktionszeiger
        cell frm;                   // Stack-Frame-Basis
        cell hea;                   // Heap-Basis
        cell stk;                   // Stack-Zeiger
        // ... zusätzliche Felder
    } AMX;
    ```

### Plattform-Unterstützung

Das SDK enthält robuste plattformspezifische Behandlung durch verschiedene Header:

1. **amx_platform.h**

    Bietet Plattformerkennung und -konfiguration:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Behandelt betriebssystemspezifische Definitionen:
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

### Plugin-System

#### plugincommon.h

Definiert die Kern-Plugin-Schnittstelle und Unterstützungsstrukturen:

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

Die Datei `amxplugin.c` ist eine wichtige Komponente des SA-MP SDK, die plattformspezifische Implementierungen von AMX-Funktionen bereitstellt. Sie implementiert zwei verschiedene Ansätze basierend auf Plattform und Compiler:

1. **Windows MSVC Implementierung (32-bit)**
    - Verwendet nackte Funktionen mit Assembly für direkten Funktionstabell-Zugriff
    - Bietet optimierte Leistung durch direkte Sprünge zu AMX-Funktionen
    - Beispielstruktur:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Plattformübergreifende Implementierung**
    - Verwendet Funktionszeiger für Plattformunabhängigkeit
    - Implementiert ein makrobasiertes System für Funktionsdefinitionen
    - Beispielstruktur:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

Hauptmerkmale:

3. **Funktionstabell-Verwaltung**
    - Verwendet einen statischen Zeiger `pAMXFunctions` zur Speicherung der AMX-Funktionstabelle
    - Bietet Zugriff auf alle Kern-AMX-Funktionen
    - Handhabt Funktionsauflösung zur Laufzeit

4. **Plattformspezifische Optimierungen**
    - Windows 32-bit: Verwendet nackte Funktionen für direkte Assembly-Implementierung
    - Andere Plattformen: Verwendet Funktionszeiger-Indirektion
    - Spezielle Behandlung für 64-bit-Systeme

5. **Implementierte Funktionskategorien**

    a. Speicherverwaltungsfunktionen:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. Ausführungsfunktionen:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. Symbolmanagement:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. String-Behandlung:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - UTF-8-Unterstützungsfunktionen
    
    e. Debug und Information:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Bedingte Kompilierung**
    - Behandelt verschiedene Plattformen durch Präprozessor-Direktiven
    - Spezielle Behandlung für 64-bit-Systeme
    - Optionale JIT-Unterstützung
    ```c
    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
            PLUGIN_AMX_EXPORT_Align64)
    #endif
    ```

7. **Fehlerbehandlungsintegration**
    - Implementiert `amx_RaiseError` für Fehlerberichterstattung
    - Bewahrt Fehlercodes über Funktionsaufrufe hinweg
    - Integriert sich mit AMX-Debug-System

### AMX Native Funktionen

Das SDK bietet umfassende Unterstützung für die Erstellung und Verwaltung nativer Funktionen:

```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

Wichtige native Funktionsoperationen:
- Registrierung durch `amx_Register`
- Parameterzugriff und -validierung
- Rückgabewertbehandlung
- Fehlerberichterstattung

## Technische Details

### Speicherverwaltung

Das SDK bietet umfassende Speicherverwaltungsfunktionen:

1. **amx_memory.h**

   Handhabt Speicherallokation und plattformspezifische Speicheroperationen:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```

2. **amx_alignment.h**

    Verwaltet Speicherausrichtungsanforderungen:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Speicheroperationen

Das SDK enthält mehrere Funktionen für Speichermanipulation:

1. **Speicherallokation**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Allokiert Speicher im AMX-Heap
    - Gibt sowohl AMX- als auch physische Adressen zurück
    - Handhabt Ausrichtungsanforderungen

2. **Speicherzugriff**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Konvertiert AMX-Adressen in physische Adressen
    - Validiert Speicherzugriff
    - Handhabt Speichergrenzen

3. **Speicherinformation**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Ruft Speicherlayout-Informationen ab
    - Berichtet Segmentgrößen
    - Nützlich für Debugging und Optimierung

### Fehlerbehandlung

Das SDK enthält ein umfassendes Fehlerbehandlungssystem, das in `amx_constants.h` definiert ist:

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

### String-Behandlung

Das SDK bietet robuste String-Behandlungsfähigkeiten durch verschiedene Makros und Funktionen:

```c
#define amx_StrParam(amx,param,result) \
    do { \
        int result##_length_; \
        amx_StrLen(amx_Address(amx,param),&result##_length_); \
        if (result##_length_>0 && \
            ((result)=(type)alloca((result##_length_+1)*sizeof(*(result))))!=NULL) \
        amx_GetString((char*)(result),amx_Address(amx,param), \
                            sizeof(*(result))>1,result##_length_+1); \
        else (result)=NULL; \
    } while(0)
```

### String-Operationen

1. **String-Länge**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Berechnet String-Länge
    - Handhabt gepackte und ungepackte Strings
    - Gibt Länge in Zeichen zurück

2. **String-Konvertierung**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Konvertiert C-Strings in AMX-Strings
    - Unterstützt gepackte und ungepackte Formate
    - Handhabt Unicode-Konvertierung

## Unicode-Unterstützung

Das SDK enthält umfassende Unicode-Unterstützung durch UTF-8-Behandlungsfunktionen:

```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Unicode-Operationen

1. **UTF-8-Validierung**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - Validiert UTF-8-kodierte Strings
    - Berichtet String-Länge in Zeichen
    - Erkennt Kodierungsfehler

2. **Zeichenkonvertierung**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extrahiert Unicode-Zeichen
    - Handhabt Multi-Byte-Sequenzen
    - Berichtet Parsing-Fehler

## Plattformübergreifende Kompatibilität

Das SDK gewährleistet plattformübergreifende Kompatibilität durch:

1. **Endianness-Behandlung**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Pfadbehandlung**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

## Systemanforderungen

Das SDK unterstützt mehrere Plattformen und Compiler:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Compiler-Unterstützung

1. **Microsoft Visual C++**
   - Pragma-Behandlung
   - Warnungsunterdrückung
   - Aufrufkonventionen

2. **GCC**
   - Diagnosesteuerungen
   - Attributspezifikationen
   - Plattformspezifische Optimierungen

3. **Clang**
   - Warnungskonfigurationen
   - Plattformübergreifende Kompatibilität
   - Moderne C++-Funktionen

## Best Practices

Bei der Verwendung des SA-MP SDK sollten folgende Best Practices beachtet werden:

1. **Speicherverwaltung**
   - Immer zugewiesene Ressourcen bereinigen
   - Geeignete Speicherausrichtung verwenden
   - Speicherfehler angemessen behandeln
   - Heap-Nutzung überwachen
   - Korrekte Speichergrenzenprüfung implementieren
   - Speicherpools für häufige Zuweisungen verwenden
   - Ressourcen in umgekehrter Reihenfolge der Zuweisung bereinigen

2. **Fehlerbehandlung**
   - Rückgabewerte von AMX-Funktionen prüfen
   - Angemessene Fehlerbehandlung in nativen Funktionen implementieren
   - Bereitgestellte Fehlerkonstanten verwenden
   - Fehler angemessen protokollieren
   - Fehlerwiederherstellungsmechanismen implementieren
   - Aussagekräftige Fehlermeldungen bereitstellen
   - Systemspezifische Fehler behandeln

3. **Plattformübergreifende Entwicklung**
   - Plattformunabhängige Typen verwenden
   - Bereitgestellte Makros für plattformspezifischen Code nutzen
   - Auf mehreren Plattformen testen
   - Endianness-Unterschiede behandeln
   - Korrekte Pfadtrenner verwenden
   - Dateisystemunterschiede berücksichtigen
   - Plattformspezifische Optimierungen implementieren

4. **Leistungsüberlegungen**
   - Geeignete Zellgrößen verwenden
   - Effiziente String-Behandlung implementieren
   - Native Funktionsaufrufe optimieren
   - Speicherzuweisungen minimieren
   - Geeignete Datenstrukturen verwenden
   - Caching wo angebracht implementieren
   - Kritische Codepfade profilieren

Bei der Arbeit mit `amxplugin.c`-Funktionalität:

1. **Plattformspezifische Entwicklung**
   - Plattformunterschiede in Funktionsimplementierungen berücksichtigen
   - Auf 32-Bit- und 64-Bit-Systemen testen
   - Plattformspezifische Ausrichtungsanforderungen behandeln
   - Funktionstabell-Zeiger vor Verwendung validieren
   - Angemessene Fehlerprüfung für jede Plattform implementieren
   - Leistungsauswirkungen verschiedener Implementierungen berücksichtigen

2. **Funktionstabell-Verwaltung**
   - Funktionstabell vor Verwendung initialisieren
   - Funktionsverfügbarkeit überprüfen
   - Fehlende Funktionen angemessen behandeln
   - Korrekte Aufräumprozeduren implementieren
   - Häufig verwendete Funktionszeiger zwischenspeichern
   - Funktionsintegritätsvalidierung durchführen

3. **Fehlerbehandlung**
   - Korrekte Fehlerprüfung für plattformspezifischen Code implementieren
   - Ausrichtungsfehler angemessen behandeln
   - Funktionseinträge validieren
   - Aussagekräftige Fehlermeldungen bereitstellen
   - Wiederherstellungsmechanismen implementieren
   - Plattformspezifische Fehler protokollieren

## Interne Strukturen

### AMX Header Struktur

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Größe der "Datei"
    uint16_t magic;        // Signatur
    char    file_version;  // Dateiformat-Version
    char    amx_version;   // Erforderliche AMX-Version
    int16_t flags;         // Flags
    int16_t defsize;      // Größe eines Definitionseintrags
    int32_t cod;          // Initialwert von COD - Codeblock
    int32_t dat;          // Initialwert von DAT - Datenblock
    int32_t hea;          // Initialwert von HEA - Heap-Start
    int32_t stp;          // Initialwert von STP - Stack-Top
    int32_t cip;          // Initialwert von CIP - Code-Instruktionszeiger
    int32_t publics;      // Offset zu öffentlichen Funktionen
    int32_t natives;      // Offset zur nativen Funktionstabelle
    int32_t libraries;    // Offset zu Bibliotheken
    int32_t pubvars;      // Offset zu öffentlichen Variablen
    int32_t tags;         // Offset zu Tags
    int32_t nametable;    // Offset zur Namenstabelle
} AMX_HEADER;
```

Diese Struktur ist entscheidend für das Verständnis des AMX-Dateiformats und wie die virtuelle Maschine Skripte lädt und ausführt.

## Erweiterte Funktionen

### JIT-Compilation-Unterstützung

Das SDK enthält Unterstützung für Just-In-Time-Kompilierung:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Debug-Schnittstelle

Debugging-Unterstützung wird bereitgestellt durch:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Public Function Schnittstelle

Das SDK bietet umfassende Unterstützung für die Arbeit mit öffentlichen Funktionen:

1. **Öffentliche Funktionen finden**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Lokalisiert öffentliche Funktionen nach Namen
    - Gibt Funktionsindex zurück
    - Validiert Funktionsexistenz

2. **Öffentliche Funktionen ausführen**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Führt öffentliche Funktionen aus
    - Handhabt Rückgabewerte
    - Verwaltet Ausführungskontext

## Versionsinformationen

Das SDK enthält Versionskonstanten für Kompatibilitätsprüfungen:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Versionskompatibilität

Das SDK behält die Kompatibilität bei durch:
1. Dateiversions-Prüfung
2. AMX-Versions-Validierung
3. JIT-Kompatibilitäts-Verifizierung
4. Funktionserkennung
5. Plattformspezifische Versionshandhabung