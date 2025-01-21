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

Il SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) è una raccolta completa di file e header C ed elementi che permettono agli sviluppatori di creare plugin per il server SA-MP. Questo SDK fornisce una base per estendere le funzionalità del server SA-MP attraverso funzioni native, permettendo agli sviluppatori di implementare funzionalità oltre quelle disponibili nello script Pawn.

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
    - [Struttura Header AMX](#struttura-header-amx)
  - [Funzionalità Avanzate](#funzionalità-avanzate)
    - [Supporto Compilazione JIT](#supporto-compilazione-jit)
    - [Interfaccia di Debug](#interfaccia-di-debug)
    - [Interfaccia Funzioni Pubbliche](#interfaccia-funzioni-pubbliche)
  - [Informazioni sulla Versione](#informazioni-sulla-versione)
    - [Compatibilità Versioni](#compatibilità-versioni)

## Componenti Principali

### Sistema AMX

L'AMX (Abstract Machine eXecutor) è la macchina virtuale che esegue gli script Pawn in SA-MP. L'SDK fornisce un ampio supporto per l'interazione con AMX attraverso vari file C e header:

#### Header AMX Principali

1. **amx.h**

    Il file header principale che consolida tutte le funzionalità relative ad AMX. Include:
    - Funzioni AMX principali per l'esecuzione degli script
    - Gestione della memoria
    - Registrazione delle funzioni native
    - Gestione delle stringhe
    - Supporto UTF-8

    Le funzioni chiave includono:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    ```

2. **amx_cell.h**

    Definisce i tipi di dati fondamentali utilizzati nel sistema AMX:
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

    Contiene strutture essenziali per il funzionamento di AMX:

    ```c
    typedef struct tagAMX {
        unsigned char _FAR *base;    // Indirizzo base
        unsigned char _FAR *data;    // Segmento dati
        AMX_CALLBACK callback;       // Funzione di callback
        AMX_DEBUG debug;            // Callback di debug
        cell cip;                   // Puntatore istruzione codice
        cell frm;                   // Base frame stack
        cell hea;                   // Base heap
        cell stk;                   // Puntatore stack
        // ... campi aggiuntivi
    } AMX;
    ```

### Supporto Piattaforme

L'SDK include una gestione robusta delle specifiche delle piattaforme attraverso vari header:

1. **amx_platform.h**

    Fornisce rilevamento e configurazione della piattaforma:
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

Definisce l'interfaccia plugin principale e le strutture di supporto:

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

Il file `amxplugin.c` è un componente cruciale dell'SDK SA-MP che fornisce implementazioni specifiche per piattaforma delle funzioni AMX. Implementa due approcci diversi basati sulla piattaforma e sul compilatore:

1. **Implementazione Windows MSVC (32-bit)**
    - Utilizza funzioni naked con assembly per l'accesso diretto alla tabella delle funzioni
    - Fornisce prestazioni ottimizzate attraverso salti diretti alle funzioni AMX
    - Struttura esempio:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Implementazione Multi-Piattaforma**
    - Utilizza puntatori a funzione per l'indipendenza dalla piattaforma
    - Implementa un sistema basato su macro per le definizioni delle funzioni
    - Struttura esempio:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

Caratteristiche Principali:

3. **Gestione Tabella Funzioni**
    - Utilizza un puntatore statico `pAMXFunctions` per memorizzare la tabella delle funzioni AMX
    - Fornisce accesso a tutte le funzioni AMX principali
    - Gestisce la risoluzione delle funzioni a runtime

4. **Ottimizzazioni Specifiche per Piattaforma**
    - Windows 32-bit: Utilizza funzioni naked per implementazione diretta in assembly
    - Altre piattaforme: Utilizza indirezione tramite puntatori a funzione
    - Gestione speciale per sistemi 64-bit

5. **Categorie di Funzioni Implementate**

    a. Funzioni di Gestione Memoria:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. Funzioni di Esecuzione:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. Gestione Simboli:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. Gestione Stringhe:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Funzioni di supporto UTF-8
    
    e. Debug e Informazioni:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Compilazione Condizionale**
    - Gestisce diverse piattaforme attraverso direttive preprocessore
    - Gestione speciale per sistemi 64-bit
    - Supporto JIT opzionale
    ```c
    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
            PLUGIN_AMX_EXPORT_Align64)
    #endif
    ```

7. **Integrazione Gestione Errori**
    - Implementa `amx_RaiseError` per la segnalazione degli errori
    - Preserva i codici di errore attraverso le chiamate alle funzioni
    - Si integra con il sistema di debug AMX

### Funzioni Native AMX

L'SDK fornisce un supporto completo per la creazione e la gestione di funzioni native:

```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

Operazioni chiave delle funzioni native:
- Registrazione attraverso `amx_Register`
- Accesso e validazione dei parametri
- Gestione dei valori di ritorno
- Segnalazione degli errori

## Dettagli Tecnici

### Gestione della Memoria

L'SDK fornisce strutture complete per la gestione della memoria:

1. **amx_memory.h**

   Gestisce l'allocazione della memoria e le operazioni specifiche della piattaforma:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```

2. **amx_alignment.h**

    Gestisce i requisiti di allineamento della memoria:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Operazioni di Memoria

L'SDK include diverse funzioni per la manipolazione della memoria:

1. **Allocazione Memoria**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Alloca memoria nell'heap AMX
    - Restituisce sia indirizzi AMX che fisici
    - Gestisce requisiti di allineamento

2. **Accesso alla Memoria**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Converte indirizzi AMX in indirizzi fisici
    - Valida l'accesso alla memoria
    - Gestisce i limiti della memoria

3. **Informazioni sulla Memoria**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Recupera informazioni sul layout della memoria
    - Riporta dimensioni dei segmenti
    - Utile per debug e ottimizzazione

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
            ((result)=(type)alloca((result##_length_+1)*sizeof(*(result))))!=NULL) \
        amx_GetString((char*)(result),amx_Address(amx,param), \
                            sizeof(*(result))>1,result##_length_+1); \
        else (result)=NULL; \
    } while(0)
```

### Operazioni sulle Stringhe

1. **Lunghezza Stringa**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Calcola la lunghezza della stringa
    - Gestisce stringhe packed e unpacked
    - Restituisce la lunghezza in caratteri

2. **Conversione Stringa**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Converte stringhe C in stringhe AMX
    - Supporta formati packed e unpacked
    - Gestisce la conversione Unicode

## Supporto Unicode

L'SDK include un supporto completo Unicode attraverso funzioni di gestione UTF-8:

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
    - Valida stringhe codificate in UTF-8
    - Riporta la lunghezza della stringa in caratteri
    - Rileva errori di codifica

2. **Conversione Caratteri**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Estrae caratteri Unicode
    - Gestisce sequenze multi-byte
    - Riporta errori di parsing

## Compatibilità Multi-Piattaforma

L'SDK assicura la compatibilità multi-piattaforma attraverso:

1. **Gestione Endianness**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Gestione Percorsi**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

## Requisiti di Sistema

L'SDK supporta multiple piattaforme e compilatori:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Supporto Compilatori

1. **Microsoft Visual C++**
   - Gestione pragma
   - Soppressione warning
   - Convenzioni di chiamata

2. **GCC**
   - Controlli diagnostici
   - Specifiche attributi
   - Ottimizzazioni specifiche per piattaforma

3. **Clang**
   - Configurazioni warning
   - Compatibilità multi-piattaforma
   - Funzionalità C++ moderne

## Migliori Pratiche

Quando si utilizza l'SDK SA-MP, considerare le seguenti best practice:

1. **Gestione della Memoria**
   - Pulire sempre le risorse allocate
   - Utilizzare l'allineamento di memoria appropriato
   - Gestire gli errori di memoria con eleganza
   - Monitorare l'utilizzo dell'heap
   - Implementare un corretto controllo dei limiti della memoria
   - Utilizzare pool di memoria per allocazioni frequenti
   - Pulire le risorse in ordine inverso rispetto all'allocazione

2. **Gestione degli Errori**
   - Controllare i valori di ritorno dalle funzioni AMX
   - Implementare una corretta gestione degli errori nelle funzioni native
   - Utilizzare le costanti di errore fornite
   - Registrare gli errori in modo appropriato
   - Implementare meccanismi di recupero errori
   - Fornire messaggi di errore significativi
   - Gestire errori specifici del sistema

3. **Sviluppo Multi-Piattaforma**
   - Utilizzare tipi indipendenti dalla piattaforma
   - Utilizzare macro fornite per codice specifico della piattaforma
   - Testare su più piattaforme
   - Gestire le differenze di endianness
   - Utilizzare separatori di percorso appropriati
   - Considerare le differenze del file system
   - Implementare ottimizzazioni specifiche per piattaforma

4. **Considerazioni sulle Prestazioni**
   - Utilizzare dimensioni cell appropriate
   - Implementare una gestione efficiente delle stringhe
   - Ottimizzare le chiamate a funzioni native
   - Minimizzare le allocazioni di memoria
   - Utilizzare strutture dati appropriate
   - Implementare il caching dove appropriato
   - Profilare i percorsi critici del codice

Quando si lavora con la funzionalità `amxplugin.c`:

1. **Sviluppo Specifico per Piattaforma**
   - Considerare le differenze di piattaforma nelle implementazioni delle funzioni
   - Testare sia su sistemi 32-bit che 64-bit
   - Gestire i requisiti di allineamento specifici della piattaforma
   - Validare il puntatore alla tabella delle funzioni prima dell'uso
   - Implementare controlli di errore appropriati per ogni piattaforma
   - Considerare le implicazioni sulle prestazioni delle diverse implementazioni

2. **Gestione Tabella Funzioni**
   - Inizializzare la tabella delle funzioni prima dell'uso
   - Verificare la disponibilità delle funzioni
   - Gestire con eleganza le funzioni mancanti
   - Implementare procedure di pulizia appropriate
   - Memorizzare in cache i puntatori a funzione utilizzati frequentemente
   - Validare l'integrità della tabella delle funzioni

3. **Gestione degli Errori**
   - Implementare un controllo appropriato degli errori per il codice specifico della piattaforma
   - Gestire gli errori di allineamento in modo appropriato
   - Validare le voci della tabella delle funzioni
   - Fornire messaggi di errore significativi
   - Implementare meccanismi di recupero
   - Registrare errori specifici della piattaforma

## Strutture Interne

### Struttura Header AMX

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Dimensione del "file"
    uint16_t magic;        // Firma
    char    file_version;  // Versione formato file
    char    amx_version;   // Versione AMX richiesta
    int16_t flags;         // Flag
    int16_t defsize;      // Dimensione di un record di definizione
    int32_t cod;          // Valore iniziale di COD - blocco codice
    int32_t dat;          // Valore iniziale di DAT - blocco dati
    int32_t hea;          // Valore iniziale di HEA - inizio heap
    int32_t stp;          // Valore iniziale di STP - top dello stack
    int32_t cip;          // Valore iniziale di CIP - puntatore istruzione codice
    int32_t publics;      // Offset alle funzioni pubbliche
    int32_t natives;      // Offset alla tabella delle funzioni native
    int32_t libraries;    // Offset alle librerie
    int32_t pubvars;      // Offset alle variabili pubbliche
    int32_t tags;         // Offset ai tag
    int32_t nametable;    // Offset alla tabella dei nomi
} AMX_HEADER;
```

Questa struttura è cruciale per comprendere il formato file AMX e come la macchina virtuale carica ed esegue gli script.

## Funzionalità Avanzate

### Supporto Compilazione JIT

L'SDK include il supporto per la compilazione Just-In-Time:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Interfaccia di Debug

Il supporto al debug è fornito attraverso:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Interfaccia Funzioni Pubbliche

L'SDK fornisce un supporto completo per lavorare con funzioni pubbliche:

1. **Ricerca Funzioni Pubbliche**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Localizza funzioni pubbliche per nome
    - Restituisce l'indice della funzione
    - Valida l'esistenza della funzione

2. **Esecuzione Funzioni Pubbliche**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Esegue funzioni pubbliche
    - Gestisce valori di ritorno
    - Gestisce il contesto di esecuzione

## Informazioni sulla Versione

L'SDK include costanti di versione per il controllo della compatibilità:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Compatibilità Versioni

L'SDK mantiene la compatibilità attraverso:
1. Controllo versione file
2. Validazione versione AMX
3. Verifica compatibilità JIT
4. Rilevamento funzionalità
5. Gestione versione specifica per piattaforma