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

SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) är en omfattande samling av C-filer, header-filer och komponenter som gör det möjligt för utvecklare att skapa plugins för SA-MP-servern. Detta SDK tillhandahåller en grund för att utöka funktionaliteten hos SA-MP-servern genom nativa funktioner, vilket gör det möjligt för utvecklare att implementera funktioner som går utöver vad som är tillgängligt i Pawn-skript.

## Språk

- Português: [README](../../LICENSE)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Türkçe: [README](../Turkce/README.md)

## Innehållsförteckning

- [samp-sdk](#samp-sdk)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [Huvudkomponenter](#huvudkomponenter)
    - [AMX-systemet](#amx-systemet)
      - [Huvudsakliga AMX-headers](#huvudsakliga-amx-headers)
    - [Plattformsstöd](#plattformsstöd)
    - [Plugin-system](#plugin-system)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [AMX Nativa Funktioner](#amx-nativa-funktioner)
  - [Tekniska detaljer](#tekniska-detaljer)
    - [Minneshantering](#minneshantering)
    - [Minnesoperationer](#minnesoperationer)
    - [Felhantering](#felhantering)
    - [Stränghantering](#stränghantering)
    - [Strängoperationer](#strängoperationer)
  - [Unicode-stöd](#unicode-stöd)
    - [Unicode-operationer](#unicode-operationer)
  - [Plattformsoberoende kompatibilitet](#plattformsoberoende-kompatibilitet)
  - [Systemkrav](#systemkrav)
    - [Kompilatorstöd](#kompilatorstöd)
  - [Bästa praxis](#bästa-praxis)
  - [Interna strukturer](#interna-strukturer)
    - [AMX Header-struktur](#amx-header-struktur)
  - [Avancerade funktioner](#avancerade-funktioner)
    - [JIT-kompileringsstöd](#jit-kompileringsstöd)
    - [Felsökningsgränssnitt](#felsökningsgränssnitt)
    - [Gränssnitt för publika funktioner](#gränssnitt-för-publika-funktioner)
  - [Versionsinformation](#versionsinformation)
    - [Versionskompatibilitet](#versionskompatibilitet)
  - [Licens](#licens)
    - [Användarvillkor](#användarvillkor)
      - [1. Beviljade rättigheter](#1-beviljade-rättigheter)
      - [2. Obligatoriska villkor](#2-obligatoriska-villkor)
      - [3. Upphovsrätt](#3-upphovsrätt)
      - [4. Garantifriskrivning och ansvarsbegränsning](#4-garantifriskrivning-och-ansvarsbegränsning)

## Huvudkomponenter

### AMX-systemet

AMX (Abstract Machine eXecutor) är den virtuella maskinen som kör Pawn-skript i SA-MP. SDK:n ger omfattande stöd för att interagera med AMX-systemet genom olika C-filer och header-filer.

#### Huvudsakliga AMX-headers

1. **amx.h**

    Den primära headern som konsoliderar all AMX-relaterad funktionalitet:
    - Huvudfunktioner för skriptexekvering
    - Minneshantering
    - Registrering av nativa funktioner
    - Stränghantering
    - UTF-8-stöd

    Viktiga funktioner inkluderar:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);         // Initierar en AMX-instans
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index); // Kör en publik funktion
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number); // Registrerar nativa funktioner
    ```

2. **amx_platform.h**

    Ansvarar för plattformsdetektering och konfiguration:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```
    - Upptäcker system som Linux, FreeBSD, OpenBSD och macOS.
    - Inkluderar `sclinux.h` för Unix-liknande system.
    - Identifierar 64-bitars arkitekturer:
      ```c
      #if defined _LP64 || defined WIN64 || defined _WIN64
          #define __64BIT__
      #endif
      ```
    - Beräknar GCC-versionen om tillämpligt:
      ```c
      #if defined __GNUC__
          #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #endif
      ```

3. **amx_constants.h**

    Definierar grundläggande konstanter för AMX-funktionalitet:
    - **Versioner**:
      ```c
      #define CUR_FILE_VERSION  9   // Nuvarande filformatversion
      #define MIN_FILE_VERSION  6   // Minsta supported version
      #define MIN_AMX_VERSION   10  // Minsta AMX-version
      #define MAX_FILE_VER_JIT  8   // Högsta version med JIT-stöd
      #define MIN_AMX_VER_JIT   8   // Minsta version med JIT-stöd
      ```
    - **Magiska koder**:
      ```c
      #define AMX_MAGIC_16    0xf1e2  // För 16-bitars celler
      #define AMX_MAGIC_32    0xf1e0  // För 32-bitars celler
      #define AMX_MAGIC_64    0xf1e1  // För 64-bitars celler
      ```
    - **Felkoder**:
      ```c
      enum {
          AMX_ERR_NONE,         // Inget fel
          AMX_ERR_EXIT,         // Skript avslutat
          AMX_ERR_ASSERT,       // Assertion misslyckades
          AMX_ERR_STACKERR,     // Stackfel
          AMX_ERR_BOUNDS,       // Åtkomst utanför gränser
          AMX_ERR_MEMACCESS,    // Ogiltig minnesåtkomst
          AMX_ERR_INVINSTR,     // Ogiltig instruktion
          AMX_ERR_STACKLOW,     // Stack för lågt
          AMX_ERR_HEAPLOW,      // Heap för lågt
          AMX_ERR_CALLBACK,     // Callback-fel
          AMX_ERR_NATIVE,       // Native funktion fel
          AMX_ERR_DIVIDE,       // Division med noll
          AMX_ERR_SLEEP,        // Sömnläge aktiverat
          AMX_ERR_INVSTATE,     // Ogiltigt tillstånd
          AMX_ERR_MEMORY = 16,  // Otillräckligt minne
          AMX_ERR_FORMAT,       // Ogiltigt format
          AMX_ERR_VERSION,      // Inkompatibel version
          AMX_ERR_NOTFOUND,     // Resurs ej hittad
          AMX_ERR_INDEX,        // Ogiltigt index
          AMX_ERR_DEBUG,        // Debug-fel
          AMX_ERR_INIT,         // Initiering misslyckades
          AMX_ERR_USERDATA,     // Användardatafel
          AMX_ERR_INIT_JIT,     // JIT-initiering misslyckades
          AMX_ERR_PARAMS,       // Ogiltiga parametrar
          AMX_ERR_DOMAIN,       // Domänfel
          AMX_ERR_GENERAL,      // Allmänt fel
      };
      ```
    - **Flaggor**:
      ```c
      #define AMX_FLAG_DEBUG      0x02   // Debug-läge
      #define AMX_FLAG_COMPACT    0x04   // Kompakt kodning
      #define AMX_FLAG_SLEEP      0x08   // Sömnstöd
      #define AMX_FLAG_NOCHECKS   0x10   // Inga säkerhetskontroller
      #define AMX_FLAG_NO_RELOC   0x200  // Ingen omplacering
      #define AMX_FLAG_NO_SYSREQD 0x400  // Ingen sysreq.d
      #define AMX_FLAG_SYSREQN    0x800  // Stöd för sysreq.n
      #define AMX_FLAG_NTVREG     0x1000 // Native registrering
      #define AMX_FLAG_JITC       0x2000 // JIT-kompilering
      #define AMX_FLAG_BROWSE     0x4000 // Bläddringsläge
      #define AMX_FLAG_RELOC      0x8000 // Omplacering aktiverad
      ```
    - **Exekveringskoder**:
      ```c
      #define AMX_EXEC_MAIN   (-1)  // Kör huvudfunktionen
      #define AMX_EXEC_CONT   (-2)  // Fortsätt exekvering
      ```

4. **amx_memory.h**

    Hanterar minnesallokering:
    - Stöd för `alloca`:
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
    - Definierar kompressionsmarginal:
      ```c
      #if !defined AMX_COMPACTMARGIN
          #define AMX_COMPACTMARGIN 64
      #endif
      ```

5. **amx_calling.h**

    Definierar anropskonventioner:
    - För nativa funktioner och API:
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

    Definierar standardiserade heltalstyper:
    - Stöd för `stdint.h` eller manuella definitioner:
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
              typedef __int64          int64_t;
              typedef unsigned __int64 uint64_t;
          #endif
      #endif
      ```

7. **amx_macros.h**

    Tillhandahåller användbara makron:
    - **Adressberäkning**:
      ```c
      #define amx_Address(amx,addr) \
          (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))
      ```
    - **Stränghantering**:
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
    - **Parameterantal**:
      ```c
      #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))
      ```
    - **Funktionsregistrering**:
      ```c
      #define amx_RegisterFunc(amx, name, func) \
          amx_Register((amx), amx_NativeInfo((name),(func)), 1)
      ```

8. **amx_cell.h**

    Definierar celltyper:
    - Konfigurerar `PAWN_CELL_SIZE` (standard: 32):
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
    - Stöd för flyttal:
      ```c
      #if PAWN_CELL_SIZE==32
          #define amx_ftoc(f)   (*(cell*)&(f))  // Float till cell
          #define amx_ctof(c)   (*(float*)&(c))  // Cell till float
      #elif PAWN_CELL_SIZE==64
          #define amx_ftoc(f)   (*(cell*)&(f))  // Double till cell
          #define amx_ctof(c)   (*(double*)&(c)) // Cell till double
      #endif
      ```
    - Teckenmanipulation:
      ```c
      #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))  // För 32-bitars
      ```

9. **amx_structures.h**

    Definierar huvudsakliga strukturer:
    - **AMX**:
      ```c
      typedef struct tagAMX {
          unsigned char _FAR *base;    // Basadress
          unsigned char _FAR *data;    // Datasegment
          AMX_CALLBACK callback;       // Callback-funktion
          AMX_DEBUG debug;            // Debug-callback
          cell cip;                   // Kodinstruktionspekare
          cell frm;                   // Stackramens bas
          cell hea;                   // Heap-bas
          cell hlw;                   // Heap nedre gräns
          cell stk;                   // Stackpekare
          cell stp;                   // Stacktopp
          int flags;                  // Flaggor
          long usertags[AMX_USERNUM]; // Användartaggar
          void _FAR *userdata[AMX_USERNUM]; // Användardata
          int error;                  // Felkod
          int paramcount;             // Antal parametrar
          cell pri;                   // Primär register
          cell alt;                   // Alternativ register
          cell reset_stk;             // Återställd stack
          cell reset_hea;             // Återställd heap
          cell sysreq_d;              // Sysreq.d-adress
          #if defined JIT
              int reloc_size;         // Omplaceringens storlek
              long code_size;         // Kodstorlek
          #endif
      } AMX;
      ```
    - **AMX_HEADER**:
      ```c
      typedef struct tagAMX_HEADER {
          int32_t size;          // Filstorlek
          uint16_t magic;        // Signatur
          char    file_version;  // Filversion
          char    amx_version;   // AMX-version
          int16_t flags;         // Flaggor
          int16_t defsize;       // Definitionsstorlek
          int32_t cod;           // Kodstart
          int32_t dat;           // Datastart
          int32_t hea;           // Heapstart
          int32_t stp;           // Stacktopp
          int32_t cip;           // Startkodinstruktionspekare
          int32_t publics;       // Offset till publika funktioner
          int32_t natives;       // Offset till nativa funktioner
          int32_t libraries;     // Offset till bibliotek
          int32_t pubvars;       // Offset till publika variabler
          int32_t tags;          // Offset till taggar
          int32_t nametable;     // Offset till namntabell
      } AMX_HEADER;
      ```

### Plattformsstöd

SDK:n innehåller robust plattformsspecifik hantering genom olika headers:

1. **amx_platform.h**

    Tillhandahåller plattformsdetektering och konfiguration:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Hanterar operativsystemspecifika definitioner:
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

### Plugin-system

#### plugincommon.h

Definierar det primära plugin-gränssnittet och stödstrukturer:
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

Filen `amxplugin.c` är en nyckelkomponent i SA-MP SDK och tillhandahåller plattformsspecifika implementeringar för AMX-funktioner. Den implementerar två tillvägagångssätt baserade på plattform och kompilator:

1. **Windows MSVC-implementering (32-bitars)**
    - Använder "nakna" funktioner med assembler för direkt åtkomst till funktionstabellen:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Plattformsoberoende implementering**
    - Använder funktionspekare för plattformsoberoende:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

**Nyckelfunktioner**:

3. **Funktionstabellhantering**
    - Använder en statisk pekare `pAMXFunctions` för att lagra AMX-funktionstabellen.
    - Ger åtkomst till alla huvudsakliga AMX-funktioner.
    - Hanterar funktionsupplösning i realtid.

4. **Plattformsspecifika optimeringar**
    - Windows 32-bitars: Direkt assembler-implementering med nakna funktioner.
    - Andra plattformar: Indirektion via funktionspekare.
    - Särskild hantering för 64-bitars system.

5. **Implementerade funktionskategorier**

    a. **Minneshanteringsfunktioner**:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. **Exekveringsfunktioner**:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. **Symbolhantering**:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. **Stränghantering**:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - UTF-8-stödfunktioner
    
    e. **Felsökning och information**:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Villkorlig kompilering**
    - Hanterar olika plattformar via preprocessordirektiv.
    - Särskild hantering för 64-bitars system.
    - Valfritt stöd för JIT:
      ```c
      #if defined _I64_MAX || defined HAVE_I64
          DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
              PLUGIN_AMX_EXPORT_Align64)
      #endif
      ```

7. **Integrering av felhantering**
    - Implementerar `amx_RaiseError` för felrapportering.
    - Bevarar felkoder genom funktionsanrop.
    - Integrerar med AMX-felsökningssystemet.

### AMX Nativa Funktioner

SDK:n ger omfattande stöd för att skapa och hantera nativa funktioner:
```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

**Nyckeloperationer med nativa funktioner**:
- Registrering via `amx_Register`.
- Åtkomst och validering av parametrar via `amx_NumParams`.
- Hantering av returvärden.
- Felrapportering med `amx_RaiseError`.

## Tekniska detaljer

### Minneshantering

SDK:n erbjuder omfattande verktyg för minneshantering:

1. **amx_memory.h**

    Hanterar minnesallokering och plattformsspecifika operationer:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```
    - Definierar `AMX_COMPACTMARGIN` till 64 som standard för minneskomprimering.

2. **amx_alignment.h**

    Hanterar krav på minnesjustering:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Minnesoperationer

SDK:n inkluderar flera funktioner för minnesmanipulation:

1. **Minnesallokering**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Allokerar minne i AMX-heapen.
    - Returnerar AMX- och fysiska adresser.
    - Hanterar justeringskrav.

2. **Minnesåtkomst**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Omvandlar AMX-adresser till fysiska adresser.
    - Validerar minnesåtkomst.
    - Hanterar minnesgränser.

3. **Minnesinformation**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Hämtar information om minneslayout.
    - Rapporterar segmentstorlekar.
    - Användbart för felsökning och optimering.

### Felhantering

SDK:n innehåller ett omfattande felhanteringssystem definierat i `amx_constants.h`:
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

### Stränghantering

SDK:n tillhandahåller robusta möjligheter för stränghantering genom olika makron och funktioner:
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
- Alternativ för `char*`:
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

### Strängoperationer

1. **Stränglängd**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Beräknar stränglängd.
    - Hanterar packade och opackade strängar.
    - Returnerar längd i tecken.

2. **Strängkonvertering**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Konverterar C-strängar till AMX-strängar.
    - Stöder packade och opackade format.
    - Hanterar Unicode-konvertering.

## Unicode-stöd

SDK:n tillhandahåller fullt stöd för Unicode genom UTF-8-hanteringsfunktioner:
```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Unicode-operationer

1. **UTF-8-validering**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - Validerar UTF-8-kodade strängar.
    - Rapporterar stränglängd i tecken.
    - Upptäcker kodningsfel.

2. **Teckenkonvertering**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extraherar Unicode-tecken.
    - Hanterar multi-byte-sekvenser.
    - Rapporterar tolkningsfel.

## Plattformsoberoende kompatibilitet

SDK:n säkerställer plattformsoberoende kompatibilitet genom:

1. **Endianness-hantering**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Sökvägshantering**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

3. **Plattformsoberoende typer**
    - Definierade i `amx_types.h` för konsekvens.

## Systemkrav

SDK:n stöder flera plattformar och kompilatorer:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Kompilatorstöd

1. **Microsoft Visual C++**
    - Hantering av pragman.
    - Undertryckning av varningar.
    - Anropskonventioner via `amx_calling.h`.

2. **GCC**
    - Diagnostiska kontroller.
    - Attributspecifikationer.
    - Plattformsspecifika optimeringar.

3. **Clang**
    - Varningskonfigurationer.
    - Plattformsoberoende kompatibilitet.
    - Moderna C++-funktioner.

## Bästa praxis

När du använder SA-MP SDK, överväg följande bästa praxis:

1. **Minneshantering**
    - Rensa alltid allokerade resurser.
    - Använd lämplig minnesjustering.
    - Hantera minnesfel med elegans.
    - Övervaka heap-användning.
    - Implementera korrekt gränskontroll för minnet.
    - Använd minnespooler för frekventa allokeringar.
    - Rensa resurser i omvänd ordning från allokering.

2. **Felhantering**
    - Kontrollera returvärden från AMX-funktioner.
    - Implementera korrekt felhantering i nativa funktioner.
    - Använd de medföljande felkonstanterna.
    - Logga fel på ett lämpligt sätt.
    - Implementera mekanismer för felåterställning.
    - Ge meningsfulla felmeddelanden.
    - Hantera systemspecifika fel.

3. **Plattformsoberoende utveckling**
    - Använd plattformsoberoende typer.
    - Utnyttja de medföljande makrona för plattformsspecifik kod.
    - Testa på flera plattformar.
    - Hantera skillnader i endianness.
    - Använd korrekta sökvägsseparatorer.
    - Beakta skillnader i filsystem.
    - Implementera plattformsspecifika optimeringar.

4. **Prestandaöverväganden**
    - Använd lämpliga cellstorlekar.
    - Implementera effektiv stränghantering.
    - Optimera anrop till nativa funktioner.
    - Minimera minnesallokeringar.
    - Använd lämpliga datastrukturer.
    - Implementera cachning där det är lämpligt.
    - Profilera kritiska kodvägar.

När du arbetar med funktionaliteten i `amxplugin.c`:

1. **Plattformsspecifik utveckling**
    - Beakta plattformsskillnader i funktionsimplementeringar.
    - Testa på både 32-bitars och 64-bitars system.
    - Hantera plattformsspecifika justeringskrav.
    - Validera funktionstabellpekaren före användning.
    - Implementera lämplig felkontroll för varje plattform.
    - Beakta prestandakonsekvenserna av olika implementeringar.

2. **Funktionstabellhantering**
    - Initiera funktionstabellen före användning.
    - Verifiera funktionstillgänglighet.
    - Hantera saknade funktioner med elegans.
    - Implementera lämpliga rengöringsrutiner.
    - Cacha ofta använda funktionspekare.
    - Validera funktionstabellens integritet.

3. **Felhantering**
    - Implementera lämplig felkontroll för plattformsspecifik kod.
    - Hantera justeringsfel på ett lämpligt sätt.
    - Validera funktionstabellposter.
    - Ge meningsfulla felmeddelanden.
    - Implementera återställningsmekanismer.
    - Logga plattformsspecifika fel.

## Interna strukturer

### AMX Header-struktur

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Filens storlek
    uint16_t magic;        // Signatur
    char    file_version;  // Filformatversion
    char    amx_version;   // Krävd AMX-version
    int16_t flags;         // Flaggor
    int16_t defsize;       // Storlek på definitionsrekord
    int32_t cod;           // Initialt värde för COD - kodblock
    int32_t dat;           // Initialt värde för DAT - datasegment
    int32_t hea;           // Initialt värde för HEA - heapstart
    int32_t stp;           // Initialt värde för STP - stacktopp
    int32_t cip;           // Initialt värde för CIP - kodinstruktionspekare
    int32_t publics;       // Offset till publika funktioner
    int32_t natives;       // Offset till nativa funktioner
    int32_t libraries;     // Offset till bibliotek
    int32_t pubvars;       // Offset till publika variabler
    int32_t tags;          // Offset till taggar
    int32_t nametable;     // Offset till namntabell
} AMX_HEADER;
```

Denna struktur är avgörande för att förstå AMX-filformatet och hur den virtuella maskinen laddar och kör skript.

## Avancerade funktioner

### JIT-kompileringsstöd

SDK:n inkluderar stöd för Just-In-Time-kompilering:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Felsökningsgränssnitt

Stöd för felsökning tillhandahålls genom:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Gränssnitt för publika funktioner

SDK:n ger omfattande stöd för att arbeta med publika funktioner:

1. **Sökning efter publika funktioner**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Lokaliserar publika funktioner efter namn.
    - Returnerar funktionsindex.
    - Validerar funktionens existens.

2. **Exekvering av publika funktioner**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Kör publika funktioner.
    - Hanterar returvärden.
    - Hanterar exekveringskontext.

## Versionsinformation

SDK:n innehåller versionskonstanter för kompatibilitetskontroll:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Versionskompatibilitet

SDK:n upprätthåller kompatibilitet genom:
1. Verifiering av filversion.
2. Validering av AMX-version.
3. Kontroll av JIT-kompatibilitet.
4. Funktionsdetektering.
5. Hantering av plattformsspecifika versioner.

## Licens

Copyright © **SA-MP Programming Community**

Denna programvara är licensierad under villkoren för MIT-licensen ("Licensen"); du får använda denna programvara i enlighet med Licensens villkor. En kopia av Licensen kan erhållas på: [MIT License](https://opensource.org/licenses/MIT)

### Användarvillkor

#### 1. Beviljade rättigheter

Denna licens ger kostnadsfritt varje person som erhåller en kopia av denna programvara och tillhörande dokumentationsfiler följande rättigheter:
- Att använda, kopiera, modifiera, sammanfoga, publicera, distribuera, underlicensiera och/eller sälja kopior av programvaran utan begränsningar.
- Att tillåta personer som programvaran tillhandahålls till att göra detsamma, under förutsättning att följande villkor uppfylls.

#### 2. Obligatoriska villkor

Alla kopior eller väsentliga delar av programvaran måste inkludera:
- Ovanstående upphovsrättsmeddelande.
- Detta tillståndsmeddelande.
- Nedanstående friskrivning.

#### 3. Upphovsrätt

Programvaran och all tillhörande dokumentation är skyddad av upphovsrättslagar. **SA-MP Programming Community** behåller den ursprungliga upphovsrätten till programvaran.

#### 4. Garantifriskrivning och ansvarsbegränsning

PROGRAMVARAN TILLHANDAHÅLLS "I BEFINTLIGT SKICK", UTAN NÅGON SOM HELST GARANTI, VARE SIG UTTRYCKLIG ELLER UNDERFÖRSTÅDD, INKLUSIVE MEN INTE BEGRÄNSAT TILL GARANTIER FÖR SÄLJBARHET, LÄMPLIGHET FÖR ETT SÄRSKILT ÄNDAMÅL OCH ICKE-INTRÅNG.

UNDER INGA OMSTÄNDIGHETER SKA UTVECKLARNA ELLER UPPHOVSRÄTTSINNEHAVARNA HÅLLAS ANSVARIGA FÖR NÅGRA ANSPRÅK, SKADOR ELLER ANNAT ANSVAR, VARE SIG I AVTAL, SKADESTÅND ELLER ANNAT, SOM UPPSTÅR FRÅN, UT UR ELLER I SAMBAND MED PROGRAMVARAN ELLER ANVÄNDNINGEN ELLER ANNAN HANTERING AV PROGRAMVARAN.

---

För detaljerad information om MIT-licensen, besök: https://opensource.org/licenses/MIT