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

SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) är en omfattande samling av C-filer och headers som gör det möjligt för utvecklare att skapa plugins för SA-MP-servern. Detta SDK tillhandahåller en grund för att utöka funktionaliteten i SA-MP-servern genom nativa funktioner, vilket gör det möjligt för utvecklare att implementera funktioner utöver vad som finns tillgängligt i Pawn-skriptet.

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

- [samp-sdk](#samp-sdk)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [Kärnkomponenter](#kärnkomponenter)
    - [AMX-system](#amx-system)
      - [AMX Core Headers](#amx-core-headers)
    - [Plattformsstöd](#plattformsstöd)
    - [Plugin-system](#plugin-system)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [AMX Nativa Funktioner](#amx-nativa-funktioner)
  - [Tekniska Detaljer](#tekniska-detaljer)
    - [Minneshantering](#minneshantering)
    - [Minnesoperationer](#minnesoperationer)
    - [Felhantering](#felhantering)
    - [Stränghantering](#stränghantering)
    - [Strängoperationer](#strängoperationer)
  - [Unicode-stöd](#unicode-stöd)
    - [Unicode-operationer](#unicode-operationer)
  - [Plattformsoberoende Kompatibilitet](#plattformsoberoende-kompatibilitet)
  - [Systemkrav](#systemkrav)
    - [Kompilatorstöd](#kompilatorstöd)
  - [Bästa Praxis](#bästa-praxis)
  - [Interna Strukturer](#interna-strukturer)
    - [AMX Header-struktur](#amx-header-struktur)
  - [Avancerade Funktioner](#avancerade-funktioner)
    - [JIT-kompileringsstöd](#jit-kompileringsstöd)
    - [Debug-gränssnitt](#debug-gränssnitt)
    - [Publikt Funktionsgränssnitt](#publikt-funktionsgränssnitt)
  - [Versionsinformation](#versionsinformation)
    - [Versionskompatibilitet](#versionskompatibilitet)

## Kärnkomponenter

### AMX-system

AMX (Abstract Machine eXecutor) är den virtuella maskinen som kör Pawn-skript i SA-MP. SDK:n ger omfattande stöd för att interagera med AMX genom olika C-filer och headers:

#### AMX Core Headers

1. **amx.h**

    Huvudheadern som samlar all AMX-relaterad funktionalitet. Den inkluderar:
    - Grundläggande AMX-funktioner för skriptexekvering
    - Minneshantering
    - Registrering av nativa funktioner
    - Stränghantering
    - UTF-8-stöd

    Viktiga funktioner inkluderar:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    ```

2. **amx_cell.h**

    Definierar grundläggande datatyper som används i AMX-systemet:
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

    Innehåller viktiga strukturer för AMX-operation:

    ```c
    typedef struct tagAMX {
        unsigned char _FAR *base;    // Basadress
        unsigned char _FAR *data;    // Datasegment
        AMX_CALLBACK callback;       // Callback-funktion
        AMX_DEBUG debug;            // Debug callback
        cell cip;                   // Kodinstruktionspekare
        cell frm;                   // Stackramens bas
        cell hea;                   // Heap-bas
        cell stk;                   // Stackpekare
        // ... ytterligare fält
    } AMX;
    ```

### Plattformsstöd

SDK:n inkluderar robust plattformsspecifik hantering genom olika headers:

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

    Hanterar operativsystemsspecifika definitioner:
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

Definierar plugin-gränssnittets kärna och stödstrukturer:

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

`amxplugin.c`-filen är en avgörande komponent i SA-MP SDK som tillhandahåller plattformsspecifika implementeringar av AMX-funktioner. Den implementerar två olika tillvägagångssätt baserat på plattform och kompilator:

1. **Windows MSVC Implementation (32-bit)**
    - Använder nakna funktioner med assembly för direkt funktionstabell-åtkomst
    - Ger optimerad prestanda genom direkta hopp till AMX-funktioner
    - Exempelstruktur:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Plattformsoberoende Implementation**
    - Använder funktionspekare för plattformsoberoende
    - Implementerar ett makrobaserat system för funktionsdefinitioner
    - Exempelstruktur:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

Viktiga funktioner:

3. **Funktionstabell-hantering**
    - Använder en statisk pekare `pAMXFunctions` för att lagra AMX-funktionstabellen
    - Ger åtkomst till alla AMX-kärnfunktioner
    - Hanterar funktionsupplösning under körning

4. **Plattformsspecifika Optimeringar**
    - Windows 32-bit: Använder nakna funktioner för direkt assembly-implementation
    - Andra plattformar: Använder funktionspekare-indirektion
    - Särskild hantering för 64-bitars system

5. **Implementerade Funktionskategorier**

    a. Minneshanteringsfunktioner:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. Exekveringsfunktioner:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. Symbolhantering:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. Stränghantering:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - UTF-8-stödfunktioner
    
    e. Debug och Information:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Villkorlig Kompilering**
    - Hanterar olika plattformar genom preprocessordirektiv
    - Särskild hantering för 64-bitars system
    - Valfritt JIT-stöd
    ```c
    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
            PLUGIN_AMX_EXPORT_Align64)
    #endif
    ```

7. **Felhanteringsintegration**
    - Implementerar `amx_RaiseError` för felrapportering
    - Bevarar felkoder över funktionsanrop
    - Integreras med AMX-debugsystemet

### AMX Nativa Funktioner

SDK:n tillhandahåller omfattande stöd för att skapa och hantera nativa funktioner:

```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

Viktiga nativa funktionsoperationer:
- Registrering genom `amx_Register`
- Parameteråtkomst och validering
- Returvärdeshantering
- Felrapportering

## Tekniska Detaljer

### Minneshantering

SDK:n tillhandahåller omfattande minneshanteringsfaciliteter:

1. **amx_memory.h**

   Hanterar minnesallokering och plattformsspecifika minnesoperationer:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```

2. **amx_alignment.h**

    Hanterar minnesjusteringskrav:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Minnesoperationer

SDK:n inkluderar flera funktioner för minnesmanipulering:

1. **Minnesallokering**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Allokerar minne i AMX-heapen
    - Returnerar både AMX- och fysiska adresser
    - Hanterar justeringskrav

2. **Minnesåtkomst**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Konverterar AMX-adresser till fysiska adresser
    - Validerar minnesåtkomst
    - Hanterar minnesgränser

3. **Minnesinformation**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Hämtar minneslayoutinformation
    - Rapporterar segmentstorlekar
    - Användbar för debugging och optimering

### Felhantering

SDK:n inkluderar ett omfattande felhanteringssystem definierat i `amx_constants.h`:

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

SDK:n tillhandahåller robusta stränghanteringsmöjligheter genom olika makron och funktioner:

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

### Strängoperationer

1. **Stränglängd**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Beräknar stränglängd
    - Hanterar packade och opackade strängar
    - Returnerar längd i tecken

2. **Strängkonvertering**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Konverterar C-strängar till AMX-strängar
    - Stöder packade och opackade format
    - Hanterar Unicode-konvertering

## Unicode-stöd

SDK:n inkluderar omfattande Unicode-stöd genom UTF-8-hanteringsfunktioner:

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
    - Validerar UTF-8-kodade strängar
    - Rapporterar stränglängd i tecken
    - Upptäcker kodningsfel

2. **Teckenkonvertering**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extraherar Unicode-tecken
    - Hanterar multi-byte-sekvenser
    - Rapporterar tolkningsfel

## Plattformsoberoende Kompatibilitet

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

## Systemkrav

SDK:n stöder flera plattformar och kompilatorer:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Kompilatorstöd

1. **Microsoft Visual C++**
   - Pragma-hantering
   - Varningsundertryckning
   - Anropskonventioner

2. **GCC**
   - Diagnostikkontroller
   - Attributspecifikationer
   - Plattformsspecifika optimeringar

3. **Clang**
   - Varningskonfigurationer
   - Plattformsoberoende kompatibilitet
   - Moderna C++-funktioner

## Bästa Praxis

Vid användning av SA-MP SDK, överväg följande bästa praxis:

1. **Minneshantering**
   - Städa alltid upp allokerade resurser
   - Använd lämplig minnesjustering
   - Hantera minnesfel elegant
   - Övervaka heap-användning
   - Implementera korrekt minnesgränskontroll
   - Använd minnespooler för frekventa allokeringar
   - Städa upp resurser i omvänd ordning från allokering

2. **Felhantering**
   - Kontrollera returvärden från AMX-funktioner
   - Implementera korrekt felhantering i nativa funktioner
   - Använd tillhandahållna felkonstanter
   - Logga fel på lämpligt sätt
   - Implementera felåterställningsmekanismer
   - Tillhandahåll meningsfulla felmeddelanden
   - Hantera systemspecifika fel

3. **Plattformsoberoende Utveckling**
   - Använd plattformsoberoende typer
   - Utnyttja tillhandahållna makron för plattformsspecifik kod
   - Testa på flera plattformar
   - Hantera endianness-skillnader
   - Använd korrekta sökvägsseparatorer
   - Beakta filsystemsskillnader
   - Implementera plattformsspecifika optimeringar

4. **Prestandaöverväganden**
   - Använd lämpliga cellstorlekar
   - Implementera effektiv stränghantering
   - Optimera nativa funktionsanrop
   - Minimera minnesallokeringar
   - Använd lämpliga datastrukturer
   - Implementera caching där lämpligt
   - Profilera kritiska kodvägar

När du arbetar med `amxplugin.c`-funktionalitet:

1. **Plattformsspecifik Utveckling**
   - Beakta plattformsskillnader i funktionsimplementeringar
   - Testa på både 32-bitars och 64-bitars system
   - Hantera plattformsspecifika justeringskrav
   - Validera funktionstabellpekare före användning
   - Implementera lämplig felkontroll för varje plattform
   - Beakta prestandakonsekvenser av olika implementeringar

2. **Funktionstabellhantering**
   - Initiera funktionstabell före användning
   - Verifiera funktionstillgänglighet
   - Hantera saknade funktioner elegant
   - Implementera korrekta städrutiner
   - Cacha ofta använda funktionspekare
   - Validera funktionstabellintegritet

3. **Felhantering**
   - Implementera korrekt felkontroll för plattformsspecifik kod
   - Hantera justeringsfel på lämpligt sätt
   - Validera funktionstabellposter
   - Tillhandahåll meningsfulla felmeddelanden
   - Implementera återställningsmekanismer
   - Logga plattformsspecifika fel

## Interna Strukturer

### AMX Header-struktur

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Storlek på "filen"
    uint16_t magic;        // Signatur
    char    file_version;  // Filformatsversion
    char    amx_version;   // Krävd AMX-version
    int16_t flags;         // Flaggor
    int16_t defsize;      // Storlek på en definitionspost
    int32_t cod;          // Initialt värde för COD - kodblock
    int32_t dat;          // Initialt värde för DAT - datablock
    int32_t hea;          // Initialt värde för HEA - heapstart
    int32_t stp;          // Initialt värde för STP - stacktopp
    int32_t cip;          // Initialt värde för CIP - kodinstruktionspekare
    int32_t publics;      // Offset till publika funktioner
    int32_t natives;      // Offset till nativ funktionstabell
    int32_t libraries;    // Offset till bibliotek
    int32_t pubvars;      // Offset till publika variabler
    int32_t tags;         // Offset till taggar
    int32_t nametable;    // Offset till namntabell
} AMX_HEADER;
```

Denna struktur är avgörande för att förstå AMX-filformatet och hur den virtuella maskinen laddar och exekverar skript.

## Avancerade Funktioner

### JIT-kompileringsstöd

SDK:n inkluderar stöd för Just-In-Time-kompilering:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Debug-gränssnitt

Debuggingsstöd tillhandahålls genom:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Publikt Funktionsgränssnitt

SDK:n tillhandahåller omfattande stöd för att arbeta med publika funktioner:

1. **Hitta Publika Funktioner**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Lokaliserar publika funktioner efter namn
    - Returnerar funktionsindex
    - Validerar funktionsexistens

2. **Exekvera Publika Funktioner**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Exekverar publika funktioner
    - Hanterar returvärden
    - Hanterar exekveringskontext

## Versionsinformation

SDK:n inkluderar versionskonstanter för kompatibilitetskontroll:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Versionskompatibilitet

SDK:n upprätthåller kompatibilitet genom:
1. Filversionsverifiering
2. AMX-versionsvalidering
3. JIT-kompatibilitetsverifiering
4. Funktionsdetektering
5. Plattformsspecifik versionshantering