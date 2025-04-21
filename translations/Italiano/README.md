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

Il SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) è una raccolta completa di file C, header e componenti che consentono agli sviluppatori di creare plugin per il server SA-MP. Questo SDK fornisce una base per estendere le funzionalità del server SA-MP attraverso funzioni native, permettendo agli sviluppatori di implementare funzionalità che vanno oltre quelle disponibili negli script Pawn.

## Lingue

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Indice

- [samp-sdk](#samp-sdk)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [Componenti Principali](#componenti-principali)
    - [Sistema AMX](#sistema-amx)
      - [Header AMX Principali](#header-amx-principali)
    - [Supporto Piattaforme](#supporto-piattaforme)
    - [Sistema Plugin](#sistema-plugin)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [Funzioni Native AMX](#funzioni-native-amx)
  - [Dettagli Tecnici](#dettagli-tecnici)
    - [Gestione della Memoria](#gestione-della-memoria)
    - [Operazioni di Memoria](#operazioni-di-memoria)
    - [Gestione degli Errori](#gestione-degli-errori)
    - [Gestione delle Stringhe](#gestione-delle-stringhe)
    - [Operazioni sulle Stringhe](#operazioni-sulle-stringhe)
  - [Supporto Unicode](#supporto-unicode)
    - [Operazioni Unicode](#operazioni-unicode)
  - [Compatibilità Multi-Piattaforma](#compatibilità-multi-piattaforma)
  - [Requisiti di Sistema](#requisiti-di-sistema)
    - [Supporto Compilatori](#supporto-compilatori)
  - [Migliori Pratiche](#migliori-pratiche)
  - [Strutture Interne](#strutture-interne)
    - [Struttura dell'Header AMX](#struttura-dellheader-amx)
  - [Funzionalità Avanzate](#funzionalità-avanzate)
    - [Supporto Compilazione JIT](#supporto-compilazione-jit)
    - [Interfaccia di Debug](#interfaccia-di-debug)
    - [Interfaccia Funzioni Pubbliche](#interfaccia-funzioni-pubbliche)
  - [Informazioni sulla Versione](#informazioni-sulla-versione)
    - [Compatibilità Versioni](#compatibilità-versioni)
  - [Licenza](#licenza)
    - [Termini e Condizioni d'Uso](#termini-e-condizioni-duso)
      - [1. Permessi Concessi](#1-permessi-concessi)
      - [2. Condizioni Obbligatorie](#2-condizioni-obbligatorie)
      - [3. Diritti d'Autore](#3-diritti-dautore)
      - [4. Esclusione di Garanzia e Limitazione di Responsabilità](#4-esclusione-di-garanzia-e-limitazione-di-responsabilità)

## Componenti Principali

### Sistema AMX

L'AMX (Abstract Machine eXecutor) è la macchina virtuale che esegue gli script Pawn in SA-MP. L'SDK fornisce un supporto esteso per interagire con il sistema AMX attraverso vari file C e header.

#### Header AMX Principali

1. **amx.h**

    L'header principale che consolida tutte le funzionalità legate ad AMX:
    - Funzioni principali per l'esecuzione degli script
    - Gestione della memoria
    - Registrazione delle funzioni native
    - Gestione delle stringhe
    - Supporto UTF-8

    Le funzioni chiave includono:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);         // Inizializza un'istanza AMX
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index); // Esegue una funzione pubblica
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number); // Registra funzioni native
    ```

2. **amx_platform.h**

    Responsabile del rilevamento e della configurazione delle piattaforme:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```
    - Rileva sistemi come Linux, FreeBSD, OpenBSD e macOS.
    - Include `sclinux.h` per sistemi di tipo Unix.
    - Identifica le architetture a 64 bit:
      ```c
      #if defined _LP64 || defined WIN64 || defined _WIN64
          #define __64BIT__
      #endif
      ```
    - Calcola la versione di GCC se applicabile:
      ```c
      #if defined __GNUC__
          #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #endif
      ```

3. **amx_constants.h**

    Definisce costanti essenziali per il funzionamento di AMX:
    - **Versioni**:
      ```c
      #define CUR_FILE_VERSION  9   // Versione corrente del formato file
      #define MIN_FILE_VERSION  6   // Versione minima supportata
      #define MIN_AMX_VERSION   10  // Versione minima di AMX
      #define MAX_FILE_VER_JIT  8   // Versione massima con supporto JIT
      #define MIN_AMX_VER_JIT   8   // Versione minima con supporto JIT
      ```
    - **Codici Magici**:
      ```c
      #define AMX_MAGIC_16    0xf1e2  // Per celle a 16 bit
      #define AMX_MAGIC_32    0xf1e0  // Per celle a 32 bit
      #define AMX_MAGIC_64    0xf1e1  // Per celle a 64 bit
      ```
    - **Codici di Errore**:
      ```c
      enum {
          AMX_ERR_NONE,         // Nessun errore
          AMX_ERR_EXIT,         // Script terminato
          AMX_ERR_ASSERT,       // Assert fallito
          AMX_ERR_STACKERR,     // Errore di stack
          AMX_ERR_BOUNDS,       // Accesso fuori dai limiti
          AMX_ERR_MEMACCESS,    // Accesso alla memoria non valido
          AMX_ERR_INVINSTR,     // Istruzione non valida
          AMX_ERR_STACKLOW,     // Stack troppo basso
          AMX_ERR_HEAPLOW,      // Heap troppo basso
          AMX_ERR_CALLBACK,     // Errore di callback
          AMX_ERR_NATIVE,       // Errore di funzione nativa
          AMX_ERR_DIVIDE,       // Divisione per zero
          AMX_ERR_SLEEP,        // Modalità sleep attivata
          AMX_ERR_INVSTATE,     // Stato non valido
          AMX_ERR_MEMORY = 16,  // Memoria insufficiente
          AMX_ERR_FORMAT,       // Formato non valido
          AMX_ERR_VERSION,      // Versione incompatibile
          AMX_ERR_NOTFOUND,     // Risorsa non trovata
          AMX_ERR_INDEX,        // Indice non valido
          AMX_ERR_DEBUG,        // Errore di debug
          AMX_ERR_INIT,         // Fallimento inizializzazione
          AMX_ERR_USERDATA,     // Errore dati utente
          AMX_ERR_INIT_JIT,     // Fallimento inizializzazione JIT
          AMX_ERR_PARAMS,       // Parametri non validi
          AMX_ERR_DOMAIN,       // Errore di dominio
          AMX_ERR_GENERAL,      // Errore generale
      };
      ```
    - **Flag**:
      ```c
      #define AMX_FLAG_DEBUG      0x02   // Modalità debug
      #define AMX_FLAG_COMPACT    0x04   // Codifica compatta
      #define AMX_FLAG_SLEEP      0x08   // Supporto sleep
      #define AMX_FLAG_NOCHECKS   0x10   // Nessun controllo di sicurezza
      #define AMX_FLAG_NO_RELOC   0x200  // Nessuna rilocalizzazione
      #define AMX_FLAG_NO_SYSREQD 0x400  // Nessun sysreq.d
      #define AMX_FLAG_SYSREQN    0x800  // Supporto sysreq.n
      #define AMX_FLAG_NTVREG     0x1000 // Registrazione nativa
      #define AMX_FLAG_JITC       0x2000 // Compilazione JIT
      #define AMX_FLAG_BROWSE     0x4000 // Modalità esplorazione
      #define AMX_FLAG_RELOC      0x8000 // Rilocalizzazione abilitata
      ```
    - **Codici di Esecuzione**:
      ```c
      #define AMX_EXEC_MAIN   (-1)  // Esegue la funzione principale
      #define AMX_EXEC_CONT   (-2)  // Continua l'esecuzione
      ```

4. **amx_memory.h**

    Gestisce l'allocazione della memoria:
    - Supporto per `alloca`:
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
    - Definisce il margine di compressione:
      ```c
      #if !defined AMX_COMPACTMARGIN
          #define AMX_COMPACTMARGIN 64
      #endif
      ```

5. **amx_calling.h**

    Definisce le convenzioni di chiamata:
    - Per funzioni native e API:
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

    Definisce tipi interi standardizzati:
    - Supporto per `stdint.h` o definizioni manuali:
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

    Fornisce macro utili:
    - **Calcolo dell'Indirizzo**:
      ```c
      #define amx_Address(amx,addr) \
          (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))
      ```
    - **Gestione delle Stringhe**:
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
    - **Conteggio dei Parametri**:
      ```c
      #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))
      ```
    - **Registrazione delle Funzioni**:
      ```c
      #define amx_RegisterFunc(amx, name, func) \
          amx_Register((amx), amx_NativeInfo((name),(func)), 1)
      ```

8. **amx_cell.h**

    Definisce i tipi di celle:
    - Configura `PAWN_CELL_SIZE` (default: 32):
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
    - Supporto per i numeri a virgola mobile:
      ```c
      #if PAWN_CELL_SIZE==32
          #define amx_ftoc(f)   (*(cell*)&(f))  // Float a cella
          #define amx_ctof(c)   (*(float*)&(c))  // Cella a float
      #elif PAWN_CELL_SIZE==64
          #define amx_ftoc(f)   (*(cell*)&(f))  // Double a cella
          #define amx_ctof(c)   (*(double*)&(c)) // Cella a double
      #endif
      ```
    - Manipolazione dei caratteri:
      ```c
      #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))  // Per 32 bit
      ```

9. **amx_structures.h**

    Definisce le strutture principali:
    - **AMX**:
      ```c
      typedef struct tagAMX {
          unsigned char _FAR *base;    // Indirizzo base
          unsigned char _FAR *data;    // Segmento dati
          AMX_CALLBACK callback;       // Funzione di callback
          AMX_DEBUG debug;            // Callback di debug
          cell cip;                   // Puntatore istruzioni codice
          cell frm;                   // Base del frame
          cell hea;                   // Base dell'heap
          cell hlw;                   // Limite inferiore dell'heap
          cell stk;                   // Puntatore dello stack
          cell stp;                   // Top dello stack
          int flags;                  // Flag
          long usertags[AMX_USERNUM]; // Tag utente
          void _FAR *userdata[AMX_USERNUM]; // Dati utente
          int error;                  // Codice errore
          int paramcount;             // Conteggio parametri
          cell pri;                   // Registro primario
          cell alt;                   // Registro alternativo
          cell reset_stk;             // Stack ripristinato
          cell reset_hea;             // Heap ripristinato
          cell sysreq_d;              // Indirizzo sysreq.d
          #if defined JIT
              int reloc_size;         // Dimensione rilocalizzazione
              long code_size;         // Dimensione codice
          #endif
      } AMX;
      ```
    - **AMX_HEADER**:
      ```c
      typedef struct tagAMX_HEADER {
          int32_t size;          // Dimensione del file
          uint16_t magic;        // Firma
          char    file_version;  // Versione del file
          char    amx_version;   // Versione AMX
          int16_t flags;         // Flag
          int16_t defsize;       // Dimensione definizione
          int32_t cod;           // Inizio del codice
          int32_t dat;           // Inizio dei dati
          int32_t hea;           // Inizio dell'heap
          int32_t stp;           // Top dello stack
          int32_t cip;           // Puntatore istruzioni iniziale
          int32_t publics;       // Offset alle funzioni pubbliche
          int32_t natives;       // Offset alle funzioni native
          int32_t libraries;     // Offset alle librerie
          int32_t pubvars;       // Offset alle variabili pubbliche
          int32_t tags;          // Offset ai tag
          int32_t nametable;     // Offset alla tabella dei nomi
      } AMX_HEADER;
      ```

### Supporto Piattaforme

L'SDK include una gestione robusta specifica delle piattaforme attraverso vari header:

1. **amx_platform.h**

    Fornisce rilevamento e configurazione delle piattaforme:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Gestisce definizioni specifiche del sistema operativo:
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

### Sistema Plugin

#### plugincommon.h

Definisce l'interfaccia principale del plugin e le strutture di supporto:
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

Il file `amxplugin.c` è un componente chiave dell'SDK SA-MP, fornendo implementazioni specifiche delle piattaforme per le funzioni AMX. Implementa due approcci basati sulla piattaforma e sul compilatore:

1. **Implementazione Windows MSVC (32-bit)**
    - Usa funzioni "naked" con assembly per l'accesso diretto alla tabella delle funzioni:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Implementazione Multi-Piattaforma**
    - Usa puntatori a funzione per l'indipendenza dalla piattaforma:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

**Caratteristiche Chiave**:

3. **Gestione della Tabella delle Funzioni**
    - Usa un puntatore statico `pAMXFunctions` per memorizzare la tabella delle funzioni AMX.
    - Fornisce accesso a tutte le funzioni principali di AMX.
    - Gestisce la risoluzione delle funzioni a runtime.

4. **Ottimizzazioni Specifiche delle Piattaforme**
    - Windows 32-bit: Implementazione diretta in assembly con funzioni naked.
    - Altre piattaforme: Indirezione tramite puntatori a funzione.
    - Gestione speciale per sistemi a 64 bit.

5. **Categorie di Funzioni Implementate**

    a. **Funzioni di Gestione della Memoria**:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. **Funzioni di Esecuzione**:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. **Gestione dei Simboli**:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. **Gestione delle Stringhe**:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Funzioni di supporto UTF-8
    
    e. **Debug e Informazioni**:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Compilazione Condizionale**
    - Gestisce diverse piattaforme tramite direttive di preprocessore.
    - Gestione speciale per sistemi a 64 bit.
    - Supporto opzionale per JIT:
      ```c
      #if defined _I64_MAX || defined HAVE_I64
          DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
              PLUGIN_AMX_EXPORT_Align64)
      #endif
      ```

7. **Integrazione della Gestione degli Errori**
    - Implementa `amx_RaiseError` per la segnalazione degli errori.
    - Preserva i codici di errore attraverso le chiamate alle funzioni.
    - Si integra con il sistema di debug di AMX.

### Funzioni Native AMX

L'SDK fornisce un supporto completo per creare e gestire funzioni native:
```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

**Operazioni Chiave con le Funzioni Native**:
- Registrazione tramite `amx_Register`.
- Accesso e validazione dei parametri tramite `amx_NumParams`.
- Gestione dei valori di ritorno.
- Segnalazione degli errori con `amx_RaiseError`.

## Dettagli Tecnici

### Gestione della Memoria

L'SDK offre strutture complete per la gestione della memoria:

1. **amx_memory.h**

    Gestisce l'allocazione della memoria e le operazioni specifiche della piattaforma:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```
    - Definisce `AMX_COMPACTMARGIN` a 64 per default per la compressione della memoria.

2. **amx_alignment.h**

    Gestisce i requisiti di allineamento della memoria:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Operazioni di Memoria

L'SDK include diverse funzioni per la manipolazione della memoria:

1. **Allocazione della Memoria**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Alloca memoria nell'heap AMX.
    - Restituisce indirizzi AMX e fisici.
    - Gestisce i requisiti di allineamento.

2. **Accesso alla Memoria**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Converte indirizzi AMX in indirizzi fisici.
    - Valida l'accesso alla memoria.
    - Gestisce i limiti della memoria.

3. **Informazioni sulla Memoria**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Recupera informazioni sul layout della memoria.
    - Riporta le dimensioni dei segmenti.
    - Utile per il debug e l'ottimizzazione.

### Gestione degli Errori

L'SDK include un sistema completo di gestione degli errori definito in `amx_constants.h`:
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

### Gestione delle Stringhe

L'SDK fornisce robuste capacità di gestione delle stringhe attraverso varie macro e funzioni:
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
- Alternativa per `char*`:
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

### Operazioni sulle Stringhe

1. **Lunghezza della Stringa**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Calcola la lunghezza della stringa.
    - Gestisce stringhe packed e unpacked.
    - Restituisce la lunghezza in caratteri.

2. **Conversione della Stringa**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Converte stringhe C in stringhe AMX.
    - Supporta formati packed e unpacked.
    - Gestisce la conversione Unicode.

## Supporto Unicode

L'SDK fornisce un supporto completo per Unicode attraverso funzioni di gestione UTF-8:
```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Operazioni Unicode

1. **Validazione UTF-8**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - Valida stringhe codificate in UTF-8.
    - Riporta la lunghezza della stringa in caratteri.
    - Rileva errori di codifica.

2. **Conversione dei Caratteri**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Estrae caratteri Unicode.
    - Gestisce sequenze multi-byte.
    - Riporta errori di parsing.

## Compatibilità Multi-Piattaforma

L'SDK assicura la compatibilità multi-piattaforma tramite:

1. **Gestione dell'Endianness**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Gestione dei Percorsi**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

3. **Tipi Indipendenti dalla Piattaforma**
    - Definiti in `amx_types.h` per coerenza.

## Requisiti di Sistema

L'SDK supporta più piattaforme e compilatori:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Supporto Compilatori

1. **Microsoft Visual C++**
    - Gestione dei pragma.
    - Soppressione degli avvisi.
    - Convenzioni di chiamata tramite `amx_calling.h`.

2. **GCC**
    - Controlli diagnostici.
    - Specifiche degli attributi.
    - Ottimizzazioni specifiche della piattaforma.

3. **Clang**
    - Configurazioni degli avvisi.
    - Compatibilità multi-piattaforma.
    - Funzionalità moderne di C++.

## Migliori Pratiche

Quando si utilizza l'SDK SA-MP, considerare le seguenti migliori pratiche:

1. **Gestione della Memoria**
    - Pulire sempre le risorse allocate.
    - Utilizzare un allineamento della memoria appropriato.
    - Gestire gli errori di memoria con eleganza.
    - Monitorare l'utilizzo dell'heap.
    - Implementare un controllo adeguato dei limiti della memoria.
    - Utilizzare pool di memoria per allocazioni frequenti.
    - Pulire le risorse nell'ordine inverso rispetto all'allocazione.

2. **Gestione degli Errori**
    - Verificare i valori di ritorno delle funzioni AMX.
    - Implementare una gestione adeguata degli errori nelle funzioni native.
    - Utilizzare le costanti di errore fornite.
    - Registrare gli errori in modo appropriato.
    - Implementare meccanismi di recupero degli errori.
    - Fornire messaggi di errore significativi.
    - Gestire errori specifici del sistema.

3. **Sviluppo Multi-Piattaforma**
    - Utilizzare tipi indipendenti dalla piattaforma.
    - Utilizzare le macro fornite per codice specifico della piattaforma.
    - Testare su più piattaforme.
    - Gestire le differenze di endianness.
    - Utilizzare separatori di percorso appropriati.
    - Considerare le differenze del file system.
    - Implementare ottimizzazioni specifiche della piattaforma.

4. **Considerazioni sulle Prestazioni**
    - Utilizzare dimensioni delle celle appropriate.
    - Implementare una gestione efficiente delle stringhe.
    - Ottimizzare le chiamate alle funzioni native.
    - Minimizzare le allocazioni di memoria.
    - Utilizzare strutture dati appropriate.
    - Implementare il caching dove appropriato.
    - Profilare i percorsi critici del codice.

Quando si lavora con la funzionalità di `amxplugin.c`:

1. **Sviluppo Specifico della Piattaforma**
    - Considerare le differenze di piattaforma nelle implementazioni delle funzioni.
    - Testare su sistemi a 32 e 64 bit.
    - Gestire i requisiti di allineamento specifici della piattaforma.
    - Validare il puntatore della tabella delle funzioni prima dell'uso.
    - Implementare un controllo degli errori appropriato per ogni piattaforma.
    - Considerare le implicazioni sulle prestazioni delle diverse implementazioni.

2. **Gestione della Tabella delle Funzioni**
    - Inizializzare la tabella delle funzioni prima dell'uso.
    - Verificare la disponibilità delle funzioni.
    - Gestire con eleganza le funzioni mancanti.
    - Implementare procedure di pulizia appropriate.
    - Memorizzare in cache i puntatori delle funzioni usate frequentemente.
    - Validare l'integrità della tabella delle funzioni.

3. **Gestione degli Errori**
    - Implementare un controllo degli errori appropriato per il codice specifico della piattaforma.
    - Gestire gli errori di allineamento in modo appropriato.
    - Validare le voci della tabella delle funzioni.
    - Fornire messaggi di errore significativi.
    - Implementare meccanismi di recupero.
    - Registrare errori specifici della piattaforma.

## Strutture Interne

### Struttura dell'Header AMX

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Dimensione del "file"
    uint16_t magic;        // Firma
    char    file_version;  // Versione del formato file
    char    amx_version;   // Versione AMX richiesta
    int16_t flags;         // Flag
    int16_t defsize;       // Dimensione di un record di definizione
    int32_t cod;           // Valore iniziale di COD - blocco codice
    int32_t dat;           // Valore iniziale di DAT - blocco dati
    int32_t hea;           // Valore iniziale di HEA - inizio dell'heap
    int32_t stp;           // Valore iniziale di STP - top dello stack
    int32_t cip;           // Valore iniziale di CIP - puntatore istruzioni codice
    int32_t publics;       // Offset alle funzioni pubbliche
    int32_t natives;       // Offset alla tabella delle funzioni native
    int32_t libraries;     // Offset alle librerie
    int32_t pubvars;       // Offset alle variabili pubbliche
    int32_t tags;          // Offset ai tag
    int32_t nametable;     // Offset alla tabella dei nomi
} AMX_HEADER;
```

Questa struttura è cruciale per comprendere il formato del file AMX e come la macchina virtuale carica ed esegue gli script.

## Funzionalità Avanzate

### Supporto Compilazione JIT

L'SDK include il supporto per la compilazione Just-In-Time:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Interfaccia di Debug

Il supporto al debug è fornito tramite:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Interfaccia Funzioni Pubbliche

L'SDK fornisce un supporto completo per lavorare con le funzioni pubbliche:

1. **Ricerca Funzioni Pubbliche**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Localizza funzioni pubbliche per nome.
    - Restituisce l'indice della funzione.
    - Valida l'esistenza della funzione.

2. **Esecuzione Funzioni Pubbliche**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Esegue funzioni pubbliche.
    - Gestisce i valori di ritorno.
    - Gestisce il contesto di esecuzione.

## Informazioni sulla Versione

L'SDK include costanti di versione per la verifica della compatibilità:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Compatibilità Versioni

L'SDK mantiene la compatibilità tramite:
1. Verifica della versione del file.
2. Validazione della versione AMX.
3. Verifica della compatibilità JIT.
4. Rilevamento delle funzionalità.
5. Gestione delle versioni specifiche della piattaforma.

## Licenza

Copyright © **SA-MP Programming Community**

Questo software è concesso in licenza secondo i termini della Licenza MIT ("Licenza"); puoi utilizzare questo software in conformità con i termini della Licenza. Una copia della Licenza può essere ottenuta su: [MIT License](https://opensource.org/licenses/MIT)

### Termini e Condizioni d'Uso

#### 1. Permessi Concessi

Questa licenza concede, gratuitamente, a chiunque ottenga una copia di questo software e dei file di documentazione associati, i seguenti diritti:
- Utilizzare, copiare, modificare, unire, pubblicare, distribuire, sublicenziare e/o vendere copie del software senza restrizioni.
- Permettere alle persone a cui il software è fornito di fare lo stesso, soggetto alle seguenti condizioni.

#### 2. Condizioni Obbligatorie

Tutte le copie o parti sostanziali del software devono includere:
- L'avviso di copyright sopra riportato.
- Questo avviso di permesso.
- L'avviso di esclusione di responsabilità qui sotto.

#### 3. Diritti d'Autore

Il software e tutta la documentazione associata sono protetti dalle leggi sul diritto d'autore. La **SA-MP Programming Community** conserva i diritti d'autore originali del software.

#### 4. Esclusione di Garanzia e Limitazione di Responsabilità

IL SOFTWARE È FORNITO "COSÌ COM'È", SENZA GARANZIE DI ALCUN TIPO, ESPLICITE O IMPLICITE, INCLUSE, MA NON LIMITATE A, GARANZIE DI COMMERCIABILITÀ, IDONEITÀ PER UNO SCOPO PARTICOLARE E NON VIOLAZIONE.

IN NESSUN CASO GLI AUTORI O I TITOLARI DEI DIRITTI D'AUTORE SARANNO RESPONSABILI PER QUALSIASI RECLAMO, DANNO O ALTRA RESPONSABILITÀ, SIA IN UN'AZIONE DI CONTRATTO, ILLECITO O ALTRO, DERIVANTE DA, FUORI O IN CONNESSIONE CON IL SOFTWARE O L'USO O ALTRE OPERAZIONI NEL SOFTWARE.

---

Per informazioni dettagliate sulla Licenza MIT, consulta: https://opensource.org/licenses/MIT