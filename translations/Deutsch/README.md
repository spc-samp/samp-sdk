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

Das SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) ist eine umfassende Sammlung von C-Dateien, Header-Dateien und Elementen, die es Entwicklern ermöglichen, Plugins für den SA-MP-Server zu erstellen. Dieses SDK bietet eine Grundlage zur Erweiterung der Funktionalität des SA-MP-Servers durch native Funktionen und erlaubt Entwicklern, Features zu implementieren, die über die Möglichkeiten von Pawn-Skripten hinausgehen.

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
      - [Wichtige AMX-Header](#wichtige-amx-header)
    - [Plattformunterstützung](#plattformunterstützung)
    - [Pluginsystem](#pluginsystem)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [AMX Native Funktionen](#amx-native-funktionen)
  - [Technische Details](#technische-details)
    - [Speicherverwaltung](#speicherverwaltung)
    - [Speicheroperationen](#speicheroperationen)
    - [Fehlerbehandlung](#fehlerbehandlung)
    - [Stringverarbeitung](#stringverarbeitung)
    - [Stringoperationen](#stringoperationen)
  - [Unicode-Unterstützung](#unicode-unterstützung)
    - [Unicode-Operationen](#unicode-operationen)
  - [Plattformübergreifende Kompatibilität](#plattformübergreifende-kompatibilität)
  - [Systemanforderungen](#systemanforderungen)
    - [Compiler-Unterstützung](#compiler-unterstützung)
  - [Best Practices](#best-practices)
  - [Interne Strukturen](#interne-strukturen)
    - [AMX-Header-Struktur](#amx-header-struktur)
  - [Erweiterte Funktionen](#erweiterte-funktionen)
    - [JIT-Kompilierungsunterstützung](#jit-kompilierungsunterstützung)
    - [Debug-Schnittstelle](#debug-schnittstelle)
    - [Öffentliche Funktionsschnittstelle](#öffentliche-funktionsschnittstelle)
  - [Versionsinformationen](#versionsinformationen)
    - [Versionskompatibilität](#versionskompatibilität)
  - [Lizenz](#lizenz)
    - [Nutzungsbedingungen](#nutzungsbedingungen)
      - [1. Gewährte Berechtigungen](#1-gewährte-berechtigungen)
      - [2. Verpflichtende Bedingungen](#2-verpflichtende-bedingungen)
      - [3. Urheberrecht](#3-urheberrecht)
      - [4. Gewährleistungsausschluss und Haftungsbeschränkung](#4-gewährleistungsausschluss-und-haftungsbeschränkung)

## Kernkomponenten

### AMX-System

Der AMX (Abstract Machine eXecutor) ist die virtuelle Maschine, die Pawn-Skripte in SA-MP ausführt. Das SDK bietet umfassende Unterstützung für die Interaktion mit dem AMX-System über verschiedene C- und Header-Dateien.

#### Wichtige AMX-Header

1. **amx.h**

    Der zentrale Header, der alle AMX-bezogenen Funktionalitäten bündelt:
    - Kernfunktionen zur Skriptausführung
    - Speicherverwaltung
    - Registrierung nativer Funktionen
    - Stringverarbeitung
    - UTF-8-Unterstützung

    Wichtige Funktionen:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);         // Initialisiert eine AMX-Instanz
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index); // Führt eine öffentliche Funktion aus
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number); // Registriert native Funktionen
    ```

2. **amx_platform.h**

    Verantwortlich für Plattformerkennung und -konfiguration:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```
    - Erkennt Systeme wie Linux, FreeBSD, OpenBSD und macOS.
    - Bezieht `sclinux.h` für Unix-ähnliche Systeme ein.
    - Identifiziert 64-Bit-Architekturen:
      ```c
      #if defined _LP64 || defined WIN64 || defined _WIN64
          #define __64BIT__
      #endif
      ```
    - Berechnet GCC-Version, falls zutreffend:
      ```c
      #if defined __GNUC__
          #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #endif
      ```

3. **amx_constants.h**

    Definiert essentielle Konstanten für den AMX-Betrieb:
    - **Versionen**:
      ```c
      #define CUR_FILE_VERSION  9   // Aktuelle Dateiformat-Version
      #define MIN_FILE_VERSION  6   // Mindestens unterstützte Version
      #define MIN_AMX_VERSION   10  // Mindest-AMX-Version
      #define MAX_FILE_VER_JIT  8   // Maximale Version mit JIT-Unterstützung
      #define MIN_AMX_VER_JIT   8   // Minimale Version mit JIT-Unterstützung
      ```
    - **Magische Codes**:
      ```c
      #define AMX_MAGIC_16    0xf1e2  // Für 16-Bit-Zellen
      #define AMX_MAGIC_32    0xf1e0  // Für 32-Bit-Zellen
      #define AMX_MAGIC_64    0xf1e1  // Für 64-Bit-Zellen
      ```
    - **Fehlercodes**:
      ```c
      enum {
          AMX_ERR_NONE,         // Kein Fehler
          AMX_ERR_EXIT,         // Skript beendet
          AMX_ERR_ASSERT,       // Assertion fehlgeschlagen
          AMX_ERR_STACKERR,     // Stapelfehler
          AMX_ERR_BOUNDS,       // Zugriff außerhalb der Grenzen
          AMX_ERR_MEMACCESS,    // Ungültiger Speicherzugriff
          AMX_ERR_INVINSTR,     // Ungültige Anweisung
          AMX_ERR_STACKLOW,     // Stapel zu klein
          AMX_ERR_HEAPLOW,      // Heap zu klein
          AMX_ERR_CALLBACK,     // Callback-Fehler
          AMX_ERR_NATIVE,       // Fehler in nativer Funktion
          AMX_ERR_DIVIDE,       // Division durch Null
          AMX_ERR_SLEEP,        // Sleep-Modus aktiviert
          AMX_ERR_INVSTATE,     // Ungültiger Zustand
          AMX_ERR_MEMORY = 16,  // Unzureichender Speicher
          AMX_ERR_FORMAT,       // Ungültiges Format
          AMX_ERR_VERSION,      // Inkompatible Version
          AMX_ERR_NOTFOUND,     // Ressource nicht gefunden
          AMX_ERR_INDEX,        // Ungültiger Index
          AMX_ERR_DEBUG,        // Debugging-Fehler
          AMX_ERR_INIT,         // Initialisierungsfehler
          AMX_ERR_USERDATA,     // Fehler in Benutzerdaten
          AMX_ERR_INIT_JIT,     // JIT-Initialisierungsfehler
          AMX_ERR_PARAMS,       // Ungültige Parameter
          AMX_ERR_DOMAIN,       // Domänenfehler
          AMX_ERR_GENERAL,      // Allgemeiner Fehler
      };
      ```
    - **Flags**:
      ```c
      #define AMX_FLAG_DEBUG      0x02   // Debugging-Modus
      #define AMX_FLAG_COMPACT    0x04   // Komprimierte Kodierung
      #define AMX_FLAG_SLEEP      0x08   // Sleep-Unterstützung
      #define AMX_FLAG_NOCHECKS   0x10   // Keine Sicherheitsprüfungen
      #define AMX_FLAG_NO_RELOC   0x200  // Keine Relokation
      #define AMX_FLAG_NO_SYSREQD 0x400  // Kein sysreq.d
      #define AMX_FLAG_SYSREQN    0x800  // sysreq.n-Unterstützung
      #define AMX_FLAG_NTVREG     0x1000 // Registrierung nativer Funktionen
      #define AMX_FLAG_JITC       0x2000 // JIT-Kompilierung
      #define AMX_FLAG_BROWSE     0x4000 // Browse-Modus
      #define AMX_FLAG_RELOC      0x8000 // Relokation aktiviert
      ```
    - **Ausführungscodes**:
      ```c
      #define AMX_EXEC_MAIN   (-1)  // Hauptfunktion ausführen
      #define AMX_EXEC_CONT   (-2)  // Ausführung fortsetzen
      ```

4. **amx_memory.h**

    Verwaltet Speicherzuweisungen:
    - Unterstützung für `alloca`:
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
    - Definiert Komprimierungsmarge:
      ```c
      #if !defined AMX_COMPACTMARGIN
          #define AMX_COMPACTMARGIN 64
      #endif
      ```

5. **amx_calling.h**

    Definiert Aufrufkonventionen:
    - Für native Funktionen und APIs:
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

    Definiert standardisierte Ganzzahltypen:
    - Unterstützung für `stdint.h` oder manuelle Definitionen:
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

    Stellt nützliche Makros bereit:
    - **Adressberechnung**:
      ```c
      #define amx_Address(amx,addr) \
          (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))
      ```
    - **Stringverarbeitung**:
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
    - **Parameteranzahl**:
      ```c
      #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))
      ```
    - **Funktionsregistrierung**:
      ```c
      #define amx_RegisterFunc(amx, name, func) \
          amx_Register((amx), amx_NativeInfo((name),(func)), 1)
      ```

8. **amx_cell.h**

    Definiert Zelltypen:
    - Konfiguriert `PAWN_CELL_SIZE` (Standard: 32):
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
    - Unterstützung für Gleitkommazahlen:
      ```c
      #if PAWN_CELL_SIZE==32
          #define amx_ftoc(f)   (*(cell*)&(f))  // Float zu Cell
          #define amx_ctof(c)   (*(float*)&(c))  // Cell zu Float
      #elif PAWN_CELL_SIZE==64
          #define amx_ftoc(f)   (*(cell*)&(f))  // Double zu Cell
          #define amx_ctof(c)   (*(double*)&(c)) // Cell zu Double
      #endif
      ```
    - Zeichenmanipulation:
      ```c
      #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))  // Für 32 Bit
      ```

9. **amx_structures.h**

    Definiert Hauptstrukturen:
    - **AMX**:
      ```c
      typedef struct tagAMX {
          unsigned char _FAR *base;    // Basisadresse
          unsigned char _FAR *data;    // Datensegment
          AMX_CALLBACK callback;       // Callback-Funktion
          AMX_DEBUG debug;            // Debug-Callback
          cell cip;                   // Code-Befehlszeiger
          cell frm;                   // Stapelrahmenbasis
          cell hea;                   // Heap-Basis
          cell hlw;                   // Unteres Heap-Limit
          cell stk;                   // Stapelzeiger
          cell stp;                   // Stapelobergrenze
          int flags;                  // Flags
          long usertags[AMX_USERNUM]; // Benutzertags
          void _FAR *userdata[AMX_USERNUM]; // Benutzerdaten
          int error;                  // Fehlercode
          int paramcount;             // Parameteranzahl
          cell pri;                   // Primärregister
          cell alt;                   // Alternativregister
          cell reset_stk;             // Zurückgesetzter Stapel
          cell reset_hea;             // Zurückgesetzter Heap
          cell sysreq_d;              // sysreq.d Adresse
          #if defined JIT
              int reloc_size;         // Relokationsgröße
              long code_size;         // Codegröße
          #endif
      } AMX;
      ```
    - **AMX_HEADER**:
      ```c
      typedef struct tagAMX_HEADER {
          int32_t size;          // Dateigröße
          uint16_t magic;        // Signatur
          char    file_version;  // Dateiversion
          char    amx_version;   // AMX-Version
          int16_t flags;         // Flags
          int16_t defsize;       // Größe eines Definitionsdatensatzes
          int32_t cod;           // Codeblock-Start
          int32_t dat;           // Datenblock-Start
          int32_t hea;           // Heap-Start
          int32_t stp;           // Stapelobergrenze
          int32_t cip;           // Initialer Befehlszeiger
          int32_t publics;       // Offset zu öffentlichen Funktionen
          int32_t natives;       // Offset zu nativen Funktionen
          int32_t libraries;     // Offset zu Bibliotheken
          int32_t pubvars;       // Offset zu öffentlichen Variablen
          int32_t tags;          // Offset zu Tags
          int32_t nametable;     // Offset zu Namenstabelle
      } AMX_HEADER;
      ```

### Plattformunterstützung

Das SDK bietet robuste plattformspezifische Unterstützung durch verschiedene Header:

1. **amx_platform.h**

    Ermöglicht Plattformerkennung und -konfiguration:
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

### Pluginsystem

#### plugincommon.h

Definiert die Haupt-Plugin-Schnittstelle und unterstützende Strukturen:
```c
#define SAMP_PLUGIN_VERSION 0x0200

enum SUPPORTS_FLAGS {
    SUPPORTS_VERSION = SAMP_PLUGIN_VERSION,
    SUPPORTS_VERSION_MASK = 0xffff,
    SUPPORTS_AMX_NATIVES = 0x10000,
    SUPPORTS_PROCESS_TICK = 0x20000
};

enum PLUGIN_DATA_TYPE {
    PLUGIN_DATA_LOGPRINTF = 0x00,
    PLUGIN_DATA_AMX_EXPORTS = 0x10,
    PLUGIN_DATA_CALLPUBLIC_FS = 0x11,
    PLUGIN_DATA_CALLPUBLIC_GM = 0x12
};
```

#### amxplugin.c

Die Datei `amxplugin.c` ist eine zentrale Komponente des SA-MP SDK und stellt plattformspezifische Implementierungen für AMX-Funktionen bereit. Es gibt zwei Ansätze basierend auf Plattform und Compiler:

1. **Windows MSVC Implementierung (32-Bit)**
    - Nutzt "nackte" Funktionen mit Assembly für direkten Zugriff auf die Funktionstabelle:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Plattformübergreifende Implementierung**
    - Nutzt Funktionszeiger für Plattformunabhängigkeit:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

**Hauptmerkmale**:

3. **Funktionstabellenverwaltung**
    - Nutzt einen statischen Zeiger `pAMXFunctions` zur Speicherung der AMX-Funktionstabelle.
    - Bietet Zugriff auf alle Kern-AMX-Funktionen.
    - Handhabt Funktionsauflösung zur Laufzeit.

4. **Plattformspezifische Optimierungen**
    - Windows 32-Bit: Direkte Assembly-Implementierung mit nackten Funktionen.
    - Andere Plattformen: Funktionszeiger-Indirektion.
    - Spezielle Behandlung für 64-Bit-Systeme.

5. **Implementierte Funktionskategorien**

    a. **Speicherverwaltungsfunktionen**:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. **Ausführungsfunktionen**:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. **Symbolverwaltung**:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. **Stringverarbeitung**:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - UTF-8-Unterstützungsfunktionen
    
    e. **Debugging und Informationen**:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Bedingte Kompilierung**
    - Behandelt verschiedene Plattformen durch Präprozessor-Direktiven.
    - Spezielle Behandlung für 64-Bit-Systeme.
    - Optionale JIT-Unterstützung:
      ```c
      #if defined _I64_MAX || defined HAVE_I64
          DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
              PLUGIN_AMX_EXPORT_Align64)
      #endif
      ```

7. **Fehlerbehandlungsintegration**
    - Implementiert `amx_RaiseError` für Fehlerberichterstattung.
    - Bewahrt Fehlercodes über Funktionsaufrufe hinweg.
    - Integriert sich in das AMX-Debug-System.

### AMX Native Funktionen

Das SDK bietet umfassende Unterstützung für die Erstellung und Verwaltung nativer Funktionen:
```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

**Wichtige Operationen mit nativen Funktionen**:
- Registrierung über `amx_Register`.
- Zugriff und Validierung von Parametern über `amx_NumParams`.
- Behandlung von Rückgabewerten.
- Fehlerberichterstattung mit `amx_RaiseError`.

## Technische Details

### Speicherverwaltung

Das SDK bietet umfassende Funktionen zur Speicherverwaltung:

1. **amx_memory.h**

    Verwaltet Speicherallokation und plattformspezifische Operationen:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```
    - Definiert `AMX_COMPACTMARGIN` standardmäßig als 64 für Speicherkomprimierung.

2. **amx_alignment.h**

    Verwaltet Anforderungen an die Speicherausrichtung:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Speicheroperationen

Das SDK enthält mehrere Funktionen zur Speichermanipulation:

1. **Speicherallokation**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Allokiert Speicher im AMX-Heap.
    - Gibt AMX- und physische Adressen zurück.
    - Berücksichtigt Ausrichtungsanforderungen.

2. **Speicherzugriff**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Konvertiert AMX-Adressen in physische Adressen.
    - Validiert Speicherzugriff.
    - Handhabt Speichergrenzen.

3. **Speicherinformationen**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Ruft Informationen zum Speicherlayout ab.
    - Meldet Segmentgrößen.
    - Nützlich für Debugging und Optimierung.

### Fehlerbehandlung

Das SDK enthält ein umfassendes Fehlerbehandlungssystem, definiert in `amx_constants.h`:
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

### Stringverarbeitung

Das SDK bietet robuste Funktionen zur Stringverarbeitung über verschiedene Makros und Funktionen:
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
- Alternative für `char*`:
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

### Stringoperationen

1. **Stringlänge**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Berechnet die Stringlänge.
    - Handhabt gepackte und ungepackte Strings.
    - Gibt die Länge in Zeichen zurück.

2. **Stringkonvertierung**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Konvertiert C-Strings in AMX-Strings.
    - Unterstützt gepackte und ungepackte Formate.
    - Handhabt Unicode-Konvertierung.

## Unicode-Unterstützung

Das SDK bietet umfassende Unterstützung für Unicode über UTF-8-Verarbeitungsfunktionen:
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
    - Validiert UTF-8-kodierte Strings.
    - Meldet die Stringlänge in Zeichen.
    - Erkennt Kodierungsfehler.

2. **Zeichenkonvertierung**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extrahiert Unicode-Zeichen.
    - Handhabt Multi-Byte-Sequenzen.
    - Meldet Parsing-Fehler.

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

3. **Plattformunabhängige Typen**
    - In `amx_types.h` definiert für Konsistenz.

## Systemanforderungen

Das SDK unterstützt mehrere Plattformen und Compiler:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Compiler-Unterstützung

1. **Microsoft Visual C++**
    - Behandlung von Pragmas.
    - Unterdrückung von Warnungen.
    - Aufrufkonventionen über `amx_calling.h`.

2. **GCC**
    - Diagnosesteuerungen.
    - Attributspezifikationen.
    - Plattformspezifische Optimierungen.

3. **Clang**
    - Warnungskonfigurationen.
    - Plattformübergreifende Kompatibilität.
    - Moderne C++-Funktionen.

## Best Practices

Bei der Nutzung des SA-MP SDK sollten folgende bewährte Praktiken beachtet werden:

1. **Speicherverwaltung**
    - Zugewiesene Ressourcen stets bereinigen.
    - Geeignete Speicherausrichtung verwenden.
    - Speicherfehler angemessen behandeln.
    - Heap-Nutzung überwachen.
    - Korrekte Speichergrenzenprüfung implementieren.
    - Speicherpools für häufige Zuweisungen nutzen.
    - Ressourcen in umgekehrter Reihenfolge der Zuweisung bereinigen.

2. **Fehlerbehandlung**
    - Rückgabewerte von AMX-Funktionen überprüfen.
    - Geeignete Fehlerbehandlung in nativen Funktionen implementieren.
    - Bereitgestellte Fehlerkonstanten verwenden.
    - Fehler angemessen protokollieren.
    - Wiederherstellungsmechanismen implementieren.
    - Aussagekräftige Fehlermeldungen bereitstellen.
    - Systemspezifische Fehler behandeln.

3. **Plattformübergreifende Entwicklung**
    - Plattformunabhängige Typen verwenden.
    - Bereitgestellte Makros für plattformspezifischen Code nutzen.
    - Auf mehreren Plattformen testen.
    - Endianness-Unterschiede behandeln.
    - Geeignete Pfadtrenner verwenden.
    - Dateisystemunterschiede berücksichtigen.
    - Plattformspezifische Optimierungen implementieren.

4. **Leistungsüberlegungen**
    - Geeignete Zellgrößen verwenden.
    - Effiziente Stringverarbeitung implementieren.
    - Aufrufe nativer Funktionen optimieren.
    - Speicherzuweisungen minimieren.
    - Geeignete Datenstrukturen verwenden.
    - Caching bei Bedarf implementieren.
    - Kritische Codepfade profilieren.

Bei der Arbeit mit `amxplugin.c`-Funktionalität:

1. **Plattformspezifische Entwicklung**
    - Plattformunterschiede in Funktionsimplementierungen berücksichtigen.
    - Auf 32-Bit- und 64-Bit-Systemen testen.
    - Plattformspezifische Ausrichtungsanforderungen behandeln.
    - Funktionstabelle-Zeiger vor Nutzung validieren.
    - Geeignete Fehlerprüfung für jede Plattform implementieren.
    - Leistungsauswirkungen verschiedener Implementierungen berücksichtigen.

2. **Funktionstabellenverwaltung**
    - Funktionstabelle vor Nutzung initialisieren.
    - Funktionsverfügbarkeit prüfen.
    - Fehlende Funktionen angemessen behandeln.
    - Korrekte Aufräumprozeduren implementieren.
    - Häufig genutzte Funktionszeiger zwischenspeichern.
    - Integrität der Funktionstabelle validieren.

3. **Fehlerbehandlung**
    - Geeignete Fehlerprüfung für plattformspezifischen Code implementieren.
    - Ausrichtungsfehler angemessen behandeln.
    - Funktionseinträge validieren.
    - Aussagekräftige Fehlermeldungen bereitstellen.
    - Wiederherstellungsmechanismen implementieren.
    - Plattformspezifische Fehler protokollieren.

## Interne Strukturen

### AMX-Header-Struktur

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Größe der "Datei"
    uint16_t magic;        // Signatur
    char    file_version;  // Dateiformat-Version
    char    amx_version;   // Erforderliche AMX-Version
    int16_t flags;         // Flags
    int16_t defsize;       // Größe eines Definitionseintrags
    int32_t cod;           // Start des Codeblocks
    int32_t dat;           // Start des Datenblocks
    int32_t hea;           // Start des Heaps
    int32_t stp;           // Stapelobergrenze
    int32_t cip;           // Initialer Befehlszeiger
    int32_t publics;       // Offset zu öffentlichen Funktionen
    int32_t natives;       // Offset zu nativen Funktionen
    int32_t libraries;     // Offset zu Bibliotheken
    int32_t pubvars;       // Offset zu öffentlichen Variablen
    int32_t tags;          // Offset zu Tags
    int32_t nametable;     // Offset zu Namenstabelle
} AMX_HEADER;
```

Diese Struktur ist entscheidend, um das AMX-Dateiformat zu verstehen und wie die virtuelle Maschine Skripte lädt und ausführt.

## Erweiterte Funktionen

### JIT-Kompilierungsunterstützung

Das SDK bietet Unterstützung für Just-In-Time-Kompilierung:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Debug-Schnittstelle

Debugging-Unterstützung wird bereitgestellt durch:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Öffentliche Funktionsschnittstelle

Das SDK bietet umfassende Unterstützung für die Arbeit mit öffentlichen Funktionen:

1. **Öffentliche Funktionen finden**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Lokalisiert öffentliche Funktionen nach Namen.
    - Gibt den Funktionsindex zurück.
    - Validiert die Existenz der Funktion.

2. **Öffentliche Funktionen ausführen**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Führt öffentliche Funktionen aus.
    - Handhabt Rückgabewerte.
    - Verwaltet den Ausführungskontext.

## Versionsinformationen

Das SDK enthält Versionskonstanten zur Kompatibilitätsprüfung:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Versionskompatibilität

Das SDK gewährleistet Kompatibilität durch:
1. Überprüfung der Dateiversion.
2. Validierung der AMX-Version.
3. Verifizierung der JIT-Kompatibilität.
4. Erkennung von Funktionen.
5. Plattformspezifische Versionsbehandlung.

## Lizenz

Copyright © **SA-MP Programming Community**

Diese Software ist unter den Bedingungen der MIT-Lizenz ("Lizenz") lizenziert; Sie dürfen diese Software gemäß den Lizenzbedingungen nutzen. Eine Kopie der Lizenz finden Sie unter: [MIT License](https://opensource.org/licenses/MIT)

### Nutzungsbedingungen

#### 1. Gewährte Berechtigungen

Diese Lizenz gewährt jeder Person, die eine Kopie dieser Software und der zugehörigen Dokumentationsdateien erhält, kostenlos folgende Rechte:
- Die Software ohne Einschränkungen zu nutzen, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, zu unterlizenzieren und/oder zu verkaufen.
- Personen, denen die Software zur Verfügung gestellt wird, dies unter den folgenden Bedingungen zu gestatten.

#### 2. Verpflichtende Bedingungen

Alle Kopien oder wesentlichen Teile der Software müssen enthalten:
- Den obigen Urheberrechtshinweis.
- Diesen Erlaubnishinweis.
- Den nachstehenden Haftungsausschluss.

#### 3. Urheberrecht

Die Software und alle zugehörige Dokumentation sind durch Urheberrechtsgesetze geschützt. Die **SA-MP Programming Community** behält die ursprünglichen Urheberrechte an der Software.

#### 4. Gewährleistungsausschluss und Haftungsbeschränkung

DIE SOFTWARE WIRD "WIE BESEHEN" ZUR VERFÜGUNG GESTELLT, OHNE JEGLICHE AUSDRÜCKLICHE ODER IMPLIZITE GEWÄHRLEISTUNG, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT, DER EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND DER NICHTVERLETZUNG VON RECHTEN DRITTER.

DIE AUTOREN ODER URHEBERRECHTSINHABER SIND IN KEINEM FALL HAFTBAR FÜR ANSPRÜCHE, SCHÄDEN ODER ANDERE VERPFLICHTUNGEN, OB IN EINER VERTRAGS- ODER DELIKTKLAGE, DIE AUS ODER IN VERBINDUNG MIT DER SOFTWARE ODER DER NUTZUNG ODER ANDEREN GESCHÄFTEN MIT DER SOFTWARE ENTSTEHEN.

---

Für detaillierte Informationen zur MIT-Lizenz besuchen Sie: https://opensource.org/licenses/MIT