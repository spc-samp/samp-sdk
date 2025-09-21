# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Un SDK C++ moderno, header-only e di alto livello per lo sviluppo di plugin e moduli per SA-MP.**

</div>

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

- [SA-MP SDK](#sa-mp-sdk)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [1. Introduzione e Filosofia di Design](#1-introduzione-e-filosofia-di-design)
    - [Il Problema con l'API C Standard di SA-MP](#il-problema-con-lapi-c-standard-di-sa-mp)
    - [La Soluzione del SA-MP SDK: Astrazione con Sicurezza e Performance](#la-soluzione-del-sa-mp-sdk-astrazione-con-sicurezza-e-performance)
    - [Modello Header-Only: Vantaggi e Implicazioni](#modello-header-only-vantaggi-e-implicazioni)
  - [2. Configurazione e Ambiente](#2-configurazione-e-ambiente)
    - [Requisiti di Compilazione](#requisiti-di-compilazione)
    - [Struttura di File Raccomandata](#struttura-di-file-raccomandata)
    - [Macro Essenziali di Configurazione](#macro-essenziali-di-configurazione)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definizioni e Costanti di SA-MP (`samp_defs.hpp`)](#definizioni-e-costanti-di-sa-mp-samp_defshpp)
  - [3. Guida all'Uso Completa dell'API](#3-guida-alluso-completa-dellapi)
    - [3.1. Il Ciclo di Vita del Plugin](#31-il-ciclo-di-vita-del-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Intercettazione degli Eventi Pawn](#32-plugin_public-intercettazione-degli-eventi-pawn)
      - [Sintassi e Dichiarazione](#sintassi-e-dichiarazione)
      - [Marshalling Automatico dei Parametri](#marshalling-automatico-dei-parametri)
      - [Controllo di Flusso: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#controllo-di-flusso-plugin_public_continue-vs-plugin_public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.3. `Plugin_Native`: Creazione di Funzioni Native in C++](#33-plugin_native-creazione-di-funzioni-native-in-c)
      - [Sintassi e Firma Fissa](#sintassi-e-firma-fissa)
      - [Registrazione Automatica delle Native](#registrazione-automatica-delle-native)
      - [Estrazione dei Parametri: `Register_Parameters` vs. `Native_Params`](#estrazione-dei-parametri-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)](#native_params-api-completa-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Restituzione di Valori](#restituzione-di-valori)
    - [3.4. `Plugin_Native_Hook`: Intercettazione delle Native SA-MP Esistenti](#34-plugin_native_hook-intercettazione-delle-native-sa-mp-esistenti)
      - [Sintassi e Firma Fissa](#sintassi-e-firma-fissa-1)
      - [Registrazione e Attivazione dell'Hook](#registrazione-e-attivazione-dellhook)
      - [Chiamata della Native Originale (Catena di Hooks): `Call_Original_Native`](#chiamata-della-native-originale-catena-di-hooks-call_original_native)
      - [Esempio Completo di `Plugin_Native_Hook`](#esempio-completo-di-plugin_native_hook)
    - [3.5. `Pawn_*` Macro: Chiamata di Funzioni Pawn da C++](#35-pawn_-macro-chiamata-di-funzioni-pawn-da-c)
      - [`Pawn_Native(NomeDellaNative, ...)`](#pawn_nativenomedellanative-)
      - [`Pawn_Public(NomeDellaPublic, ...)`](#pawn_publicnomedellapublic-)
      - [`Pawn(NomeDellaFunzione, ...)`](#pawnnomedellafunzione-)
      - [Sintassi e Convenzioni](#sintassi-e-convenzioni)
      - [Marshalling dei Parametri di Input](#marshalling-dei-parametri-di-input)
      - [Marshalling dei Parametri di Output (Riferimenti: `int&`, `float&`, `std::string&`)](#marshalling-dei-parametri-di-output-riferimenti-int-float-stdstring)
      - [L'Oggetto `Callback_Result`: Analisi Completa](#loggetto-callback_result-analisi-completa)
    - [3.6. `Plugin_Module`: Gestione dei Moduli Dinamici](#36-plugin_module-gestione-dei-moduli-dinamici)
      - [Sintassi e Scopo](#sintassi-e-scopo)
      - [Ciclo di Vita di un Modulo](#ciclo-di-vita-di-un-modulo)
      - [Benefici della Modularizzazione](#benefici-della-modularizzazione)
    - [3.7. `Plugin_Call`: Chiamata delle Native Interne del Plugin](#37-plugin_call-chiamata-delle-native-interne-del-plugin)
      - [Sintassi e Vantaggi di Performance](#sintassi-e-vantaggi-di-performance)
    - [3.8. Funzioni Utilità dell'SDK](#38-funzioni-utilità-dellsdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Raccomandato)](#stdstring-plugin_formatconst-char-format--raccomandato)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Dettaglio di Implementazione)](#stdstring-samp_sdkformatconst-char-format--dettaglio-di-implementazione)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Anatomia Interna e Architettura dell'SDK](#4-anatomia-interna-e-architettura-dellsdk)
    - [4.1. `core.hpp`: La Fondazione Minimalista](#41-corehpp-la-fondazione-minimalista)
    - [4.2. `platform.hpp` e `version.hpp`: Compatibilità e Metadati](#42-platformhpp-e-versionhpp-compatibilità-e-metadati)
    - [4.3. `function_hook.hpp`: Il Motore di Intercettazione x86](#43-function_hookhpp-il-motore-di-intercettazione-x86)
    - [4.4. `interceptor_manager.hpp`: Il Controllore di Hooks dell'AMX](#44-interceptor_managerhpp-il-controllore-di-hooks-dellamx)
    - [4.5. `amx_manager.hpp`: Gestione delle Istanze `AMX*`](#45-amx_managerhpp-gestione-delle-istanze-amx)
    - [4.6. `public_dispatcher.hpp`: Il Router di Callbacks `Plugin_Public`](#46-public_dispatcherhpp-il-router-di-callbacks-plugin_public)
    - [4.7. `native.hpp`: Gestione e Chiamata delle Native del Plugin](#47-nativehpp-gestione-e-chiamata-delle-native-del-plugin)
    - [4.8. `native_hook_manager.hpp`: Il Motore di Hooks delle Native](#48-native_hook_managerhpp-il-motore-di-hooks-delle-native)
    - [4.9. `callbacks.hpp` \& `amx_memory.hpp`: Chiamate C++ -\> Pawn e RAII](#49-callbackshpp--amx_memoryhpp-chiamate-c---pawn-e-raii)
    - [4.10. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Accesso Astratto all'AMX](#410-amx_apihpp--amx_helpershpp--amx_defsh-accesso-astratto-allamx)
  - [5. Compilazione e Deploy](#5-compilazione-e-deploy)
    - [Requisiti di Architettura e Piattaforma](#requisiti-di-architettura-e-piattaforma)
    - [Esempi di Comandi di Compilazione](#esempi-di-comandi-di-compilazione)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW su Windows)**](#gcc--clang-mingw-su-windows)
    - [Considerazioni per la Distribuzione](#considerazioni-per-la-distribuzione)
  - [Licenza](#licenza)
    - [Termini e Condizioni d'Uso](#termini-e-condizioni-duso)
      - [1. Permessi Concessi](#1-permessi-concessi)
      - [2. Condizioni Obbligatorie](#2-condizioni-obbligatorie)
      - [3. Diritti d'Autore](#3-diritti-dautore)
      - [4. Esclusione di Garanzia e Limitazione di Responsabilità](#4-esclusione-di-garanzia-e-limitazione-di-responsabilità)

## 1. Introduzione e Filosofia di Design

### Il Problema con l'API C Standard di SA-MP

L'API dei plugin di SA-MP è un'interfaccia di programmazione in C. Sebbene funzionale e fondamentale, presenta le sfide inerenti alla programmazione di basso livello:
- **Gestione Manuale della Memoria:** Funzioni come `amx_Allot` e `amx_Release` richiedono che lo sviluppatore allochi e deallochi esplicitamente la memoria nell'heap dell'AMX. Questa è una fonte comune di perdite di memoria e errori di runtime.
- **Tipizzazione Debole e Conversioni Manuali:** I parametri vengono passati come un array di `cell`, forzando conversioni esplicite (e spesso insicure) tra `cell`, `int`, `float` e `char*`.
- **Verbosità e Boilerplate:** Estrarre più parametri da un array `cell* params`, gestire le dimensioni delle stringhe e gestire lo stack dell'AMX per le chiamate di ritorno da C++ a Pawn richiede codice ripetitivo.
- **Fragilità dell'Interfaccia:** La mancanza di verifica in fase di compilazione (type safety) significa che gli errori nel passaggio dei parametri o nei tipi possono passare inosservati fino all'esecuzione, causando crash o comportamenti indefiniti.

### La Soluzione del SA-MP SDK: Astrazione con Sicurezza e Performance

L'SA-MP SDK affronta questi problemi fornendo un potente strato di astrazione in C++:
- **RAII (Resource Acquisition Is Initialization):** Gestione automatica della memoria nell'AMX. `Amx_Scoped_Memory` garantisce che la memoria allocata venga liberata.
- **Sicurezza dei Tipi:** Conversione automatica e sicura dei parametri tra C++ e Pawn. Si gestiscono direttamente `int`, `float`, `std::string`.
- **Sintassi Concisa e Idiomatica:** Macro e template forniscono un'API pulita che assomiglia più al C++ moderno che all'API C tradizionale.
- **Intercettazione Robusta:** Un motore di hooking avanzato consente l'intercettazione trasparente dei callbacks di Pawn (`Plugin_Public`), la creazione di nuove native (`Plugin_Native`) e **l'hooking e l'incatenamento di funzioni native SA-MP esistenti (`Plugin_Native_Hook`)**.
- **Alte Performance:** Uso estensivo di hashing in fase di compilazione (FNV1a), caching delle funzioni e ottimizzazioni di `thread_local` per minimizzare l'overhead delle astrazioni.

### Modello Header-Only: Vantaggi e Implicazioni

L'SDK è composto esclusivamente da file di intestazione (`.hpp`, `.h`).
- **Vantaggi:**
   - **Integrazione Semplificata:** Non ci sono librerie da costruire, collegare o distribuire. Basta includere gli header.
   - **Ottimizzazioni del Compilatore:** Il compilatore ha piena visibilità del codice SDK e del tuo plugin, consentendo un inlining aggressivo e ottimizzazioni in fase di linking, che possono portare a binari più veloci.
- **Implicazioni:**
   - **Tempo di Compilazione:** Per progetti molto grandi, la compilazione potrebbe richiedere più tempo a causa dell'inclusione ripetuta del codice SDK. Questo è mitigato dalle guardie di inclusione e dalla natura "includi solo ciò che è necessario" del C++.
   - **Macro di Implementazione:** La necessità della macro `SAMP_SDK_IMPLEMENTATION` è una conseguenza del modello header-only per evitare ridefinizioni di simboli.

## 2. Configurazione e Ambiente

### Requisiti di Compilazione

- **Compilatore C++:** Compatibile con C++14 o superiore (l'SDK utilizza funzionalità di C++14, C++17 e C++20 per ottimizzazioni specifiche, ma C++14 è il minimo).
   - GCC (versione 7+)
   - Clang (versione 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Architettura:** **x86 (32-bit)**. SA-MP opera esclusivamente su questa architettura. L'SDK include verifiche in `platform.hpp` che emetteranno errori di compilazione se viene rilevata l'architettura errata.
- **Sistema Operativo:** Windows o Linux.

### Struttura di File Raccomandata

Per chiarezza e organizzazione, è comune organizzare l'SDK in una sottocartella `samp-sdk`.

```
my_plugin/
├── samp-sdk/
│   ├── // Altri file dell'SDK
│   └── samp_sdk.hpp             // L'header principale da includere
│
├── src/
│   ├── main.cpp                  // Dove SAMP_SDK_IMPLEMENTATION è definito
│   └── my_custom_logic.cpp       // Opzionale, per organizzare il codice
│
└── CMakeLists.txt (o .vcxproj, Makefile)
```

### Macro Essenziali di Configurazione

Definire sempre queste macro *prima* di includere `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Scopo:** Segnala al compilatore che questo file `.cpp` deve generare le implementazioni delle funzioni di esportazione del plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **L'SDK si occupa automaticamente dell'esportazione di queste funzioni, eliminando la necessità di file `.def` (su Windows) o dichiarazioni `__attribute__((visibility("default")))` (su Linux) per queste funzioni.**
- **Impatto Tecnico:** Senza questa macro, il linker non troverà le esportazioni necessarie e il server SA-MP non sarà in grado di caricare il tuo plugin.
- **Regola Fondamentale:** **Definire questa macro in SOLO UN file `.cpp` in tutto il tuo progetto.** Definirla in più di un file causerà un errore di linking di "simbolo duplicato".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // La macro fa sì che l'SDK esporti automaticamente le funzioni necessarie.
#include "samp-sdk/samp_sdk.hpp"

// ... il tuo codice plugin ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Scopo:** Abilita i callbacks del ciclo di vita dello script Pawn (`OnAmxLoad`, `OnAmxUnload`) e la funzionalità di creare nuove native in C++ (`Plugin_Native`).
- **Funzionalità Attivate:**
   - Callbacks `OnAmxLoad(AMX* amx)` e `OnAmxUnload(AMX* amx)`.
   - Dichiarazione e registrazione di nuove native C++ usando `Plugin_Native`.
   - La macro `Plugin_Call` per invocare native create con `Plugin_Native` all'interno del proprio plugin.
- **Impatto Tecnico:** Quando questa macro è definita, l'SDK raccoglie automaticamente tutte le tue `Plugin_Native`s. Nella funzione `Supports()`, il flag `SUPPORTS_AMX_NATIVES` viene automaticamente aggiunto se ci sono `Plugin_Native`s nel tuo progetto.
- **Flessibilità:** **Puoi definire questa macro in più file `.cpp`**. Il sistema di registrazione statico dell'SDK consoliderà tutte le native da diverse unità di compilazione in un'unica lista globale.

```cpp
// my_natives.cpp (può essere un file separato da main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Solo per abilitare Plugin_Native e i callbacks OnAmxLoad/OnAmxUnload
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Scopo:** Abilita il callback `OnProcessTick()`, che viene invocato regolarmente dal server.
- **Impatto Tecnico:** Aggiunge automaticamente il flag `SUPPORTS_PROCESS_TICK` alla funzione `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logica eseguita ad ogni "tick" del server (es: 20ms)
    // Attenzione con operazioni pesanti qui!
}
```

### Definizioni e Costanti di SA-MP (`samp_defs.hpp`)

Questo file fornisce tutte le costanti e i limiti noti di SA-MP, come `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, ecc. È automaticamente incluso da `samp_sdk.hpp` e deve essere utilizzato per garantire compatibilità e leggibilità del codice.

## 3. Guida all'Uso Completa dell'API

### 3.1. Il Ciclo di Vita del Plugin

Le seguenti funzioni sono i punti di ingresso e uscita del tuo plugin, esportate automaticamente dall'SDK.

#### `bool OnLoad()`

- **Descrizione:** Prima funzione chiamata dal server SA-MP dopo il caricamento riuscito del tuo plugin in memoria.
- **Uso:** Ideale per inizializzare qualsiasi sistema, caricare configurazioni, aprire connessioni a database o caricare moduli (`Plugin_Module`).
- **Ritorno:**
   - `true`: Il plugin è stato inizializzato con successo e il caricamento continua.
   - `false`: Il plugin non è riuscito a inizializzare. Il caricamento verrà interrotto e il plugin verrà scaricato.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Inizializzando MyPlugin v1.0...");

    // Esempio: Caricare un modulo (maggiori dettagli nella sezione 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Modulo Database caricato.")) {
        Samp_SDK::Log("ERRORE: Impossibile caricare il modulo database!");

        return false; // Aborta il caricamento del plugin principale
    }

    return true;
}
```

#### `void OnUnload()`

- **Descrizione:** Ultima funzione chiamata dal server SA-MP prima di scaricare il tuo plugin dalla memoria.
- **Uso:** Ideale per pulire risorse, chiudere connessioni, salvare stati e garantire che nessuna risorsa venga persa. L'SDK gestisce automaticamente lo scaricamento dei moduli (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin scaricato. Rilascio risorse...");
    // Nessuna azione manuale è necessaria per i moduli caricati tramite Plugin_Module;
    // l'SDK se ne occupa.
}
```

#### `unsigned int GetSupportFlags()`

- **Descrizione:** Informa il server SA-MP quali funzionalità il tuo plugin supporta e desidera utilizzare.
- **Uso:** **Restituire sempre `SUPPORTS_VERSION` (o `SAMP_PLUGIN_VERSION`).** I flag `SUPPORTS_AMX_NATIVES` e `SUPPORTS_PROCESS_TICK` vengono aggiunti automaticamente dall'SDK se sono presenti `Plugin_Native`s e/o se la macro `SAMP_SDK_WANT_PROCESS_TICK` è definita, rispettivamente. Questo semplifica la manutenzione ed evita errori.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // L'SDK aggiunge automaticamente i flag necessari.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Richiede:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrizione:** Chiamato ogni volta che un nuovo script Pawn (un Gamemode o Filterscript) viene caricato e inizializzato sul server.
- **Uso:** Se hai bisogno di logica specifica per ogni script AMX, o inizializzare dati specifici per script.

```cpp
// main.cpp (con SAMP_SDK_WANT_AMX_EVENTS definito)
void OnAmxLoad(AMX* amx) {
    // amx rappresenta la nuova istanza dello script caricato.
    Samp_SDK::Log("Script AMX caricato: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Richiede:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrizione:** Chiamato quando uno script Pawn viene scaricato dal server.
- **Uso:** Per pulire qualsiasi risorsa specifica che hai allocato o associato a quella particolare `AMX*`.

```cpp
// main.cpp (con SAMP_SDK_WANT_AMX_EVENTS definito)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX scaricato: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Richiede:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Descrizione:** Chiamato ripetutamente ad ogni "tick" del server (solitamente 20 volte al secondo, o ogni 50ms).
- **Uso:** Per logiche di background continue, timer, aggiornamenti di stato che non dipendono dagli eventi del giocatore, o sincronizzazione dei dati.
- **Attenzione:** Evitare operazioni bloccanti o computazionalmente pesanti qui, poiché possono causare lag nel server.

```cpp
// main.cpp (con SAMP_SDK_WANT_PROCESS_TICK definito)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Ogni 10 secondi (20 tick/sec * 10 sec = 200 tick)
        Samp_SDK::Log("Server attivo da %d secondi.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Intercettazione degli Eventi Pawn

La macro `Plugin_Public` è il ponte primario per ricevere callbacks da Pawn nel tuo codice C++.

#### Sintassi e Dichiarazione

- `Plugin_Public(NomeDellaPublic, Tipo1 Param1, Tipo2 Param2, ...)`
- Il nome della funzione C++ che dichiari **deve essere lo stesso** del callback Pawn (es: `OnPlayerConnect`).
- I tipi di parametri C++ (`int`, `float`, `std::string`) vengono automaticamente convertiti dall'SDK.

```cpp
// Intercetta OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Giocatore %d ha detto: %s", playerid, text.c_str());

    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Marshalling Automatico dei Parametri

L'SDK gestisce automaticamente la lettura dello `cell stack` dell'AMX e la conversione ai tipi C++ specificati:
- `int`: Convertito direttamente da `cell`.
- `float`: Convertito da `cell` usando `amx::AMX_CTOF`.
- `std::string`: L'SDK legge l'indirizzo della stringa nell'AMX, alloca una `std::string` in C++ e copia il contenuto.

#### Controllo di Flusso: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

Il valore restituito dalla tua funzione `Plugin_Public` è cruciale e determina il flusso di esecuzione del callback:
- `return PLUGIN_PUBLIC_CONTINUE;` (valore `1`): Indica che l'esecuzione del callback deve **continuare**. Se ci sono altri plugin che intercettano questo callback, verranno chiamati (in ordine inverso di caricamento). Successivamente, la `public` originale nello script Pawn verrà invocata.
- `return PLUGIN_PUBLIC_STOP;` (valore `0`): Indica che l'esecuzione del callback deve essere **interrotta**. Nessun altro plugin (con priorità inferiore) o la `public` originale nello script Pawn verrà invocato per questo evento. Questo è ideale per implementare un sistema che "sovrascrive" o "blocca" un comportamento standard di SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Congela il giocatore
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Giocatore %d congelato.", playerid));

        return PLUGIN_PUBLIC_STOP; // Impedisce che il comando venga elaborato da altri script.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Permette che altri comandi vengano elaborati.
}
```

#### Ghost Callbacks

Una caratteristica avanzata di `Plugin_Public` è il supporto ai "Ghost Callbacks". Ciò significa che puoi intercettare un callback Pawn anche se **non è presente** nello script `.amx` del gamemode o del filterscript. L'SDK "inganna" il server in modo che chiami il tuo hook C++ comunque. Questo è utile per callbacks interni o per creare nuove funzionalità senza dipendere dalla presenza di una `public` nello script Pawn.

```cpp
// Puoi definire un callback che lo script Pawn non possiede, ma il tuo plugin lo ascolterà.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Evento interno personalizzato ricevuto: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// Per "attivare" questo evento da un altro punto del tuo codice C++:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// La chiamata andrà al tuo Plugin_Public qui sopra, anche se non c'è OnMyCustomInternalEvent in Pawn.
```

### 3.3. `Plugin_Native`: Creazione di Funzioni Native in C++

`Plugin_Native` ti permette di estendere la funzionalità di Pawn con codice C++ ad alte prestazioni.

#### Sintassi e Firma Fissa

- `Plugin_Native(NomeDellaNative, AMX* amx, cell* params)`
- La funzione C++ deve avere esattamente questa firma: `cell NomeDellaNative(AMX* amx, cell* params)`.
- `NomeDellaNative` è il nome che gli script Pawn useranno.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementazione ...
    return 0;
}
```

#### Registrazione Automatica delle Native

> [!NOTE]
> **Non è necessario** chiamare `amx_Register` manualmente. L'SDK rileva tutte le tue `Plugin_Native`s (in qualsiasi file `.cpp` che abbia incluso `samp_sdk.hpp` e definito `SAMP_SDK_WANT_AMX_EVENTS`) e le registra automaticamente in ogni script AMX caricato (`OnAmxLoad`).

#### Estrazione dei Parametri: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Descrizione:** Helper più semplice per estrarre più parametri in sequenza.
- **Uso:** `Register_Parameters(variabile1, variabile2, ...)`
- **Limitazioni:** Per parametri di input. Non gestisce parametri opzionali o accesso per indice.
- **Tipi Supportati:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Estrae i 3 parametri
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)

- **Descrizione:** Una classe wrapper che fornisce un'interfaccia orientata agli oggetti per accedere ai parametri di una native. Più potente per scenari complessi.
- **Costruzione:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Descrizione:** Restituisce il numero di parametri passati alla native.
- **Uso:** Essenziale per gestire parametri opzionali.

###### `p.Get<T>(size_t index)`

- **Descrizione:** Estrae un parametro di input per indice e lo converte al tipo `T`.
- **Tipi Supportati:** `int`, `float`, `std::string`.

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

- **Descrizione:** Ottiene il valore di un parametro di **riferimento** (puntatore Pawn) e lo memorizza in `out_value`.
- **Uso:** Per leggere valori che sono stati passati per riferimento da Pawn.
- **Ritorno:** `true` se l'indirizzo AMX è valido, `false` altrimenti.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Ottiene i valori dei riferimenti (Pawn ha passato indirizzi)
    p.Get_REF(1, health); // Legge il valore di Float:health
    p.Get_REF(2, money);   // Legge il valore di money
    
    Samp_SDK::Log("Giocatore %d, Vita: %.1f, Denaro: %d", playerid, health, money);
    
    // Ora, modificali
    health = 50.0f;
    money += 100;
    
    // E li riscrive nella memoria di Pawn
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Descrizione:** Restituisce un `std::optional<T>` per leggere un parametro di riferimento. Più sicuro per C++17 e superiori.

###### `p.Set_REF<T>(size_t index, T value)`

- **Descrizione:** Scrive un valore `T` in un parametro di **riferimento** Pawn (l'indirizzo che Pawn ha passato).
- **Uso:** Per modificare valori che sono stati passati per riferimento, facendo in modo che Pawn veda la modifica.
- **Ritorno:** `true` se la scrittura è avvenuta con successo, `false` altrimenti.

#### Restituzione di Valori

- La tua funzione `Plugin_Native` deve restituire una `cell`.
- Per restituire un `int` o `bool`, usa un cast a `cell`.
- Per restituire un `float`, usa `amx::AMX_FTOC(mio_float)`.

```cpp
// Restituisce un bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Restituisce un float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Restituisce 100.0f
}
```

### 3.4. `Plugin_Native_Hook`: Intercettazione delle Native SA-MP Esistenti

La macro `Plugin_Native_Hook` ti permette di intercettare e modificare il comportamento di qualsiasi funzione nativa SA-MP esistente o di altri plugin. Questo è un meccanismo potente per estendere o alterare la logica standard del server.

#### Sintassi e Firma Fissa

- `Plugin_Native_Hook(NomeDellaNative, AMX* amx, cell* params)`
- La funzione C++ deve avere esattamente questa firma: `cell NomeDellaNative(AMX* amx, cell* params)`.
- `NomeDellaNative` deve essere il nome esatto della native che vuoi hookare (es: `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercetta la native SendClientMessage
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Importante chiamare l'originale
}
```

#### Registrazione e Attivazione dell'Hook

> [!NOTE]
> **Non è necessario** chiamare `amx_Register` manualmente o definire `SAMP_SDK_WANT_AMX_EVENTS` specificamente per `Plugin_Native_Hook`. L'SDK rileva e registra automaticamente i tuoi hook. Alla prima esecuzione di uno script AMX, l'SDK sostituisce il puntatore della native nella tabella con un "trampoline" che reindirizza alla tua funzione `Plugin_Native_Hook`. Questo processo garantisce l'incatenamento sicuro degli hook di più plugin.

#### Chiamata della Native Originale (Catena di Hooks): `Call_Original_Native`

All'interno della tua funzione `Plugin_Native_Hook`, **DEVI** usare la macro `Call_Original_Native(NomeDellaNative)` per invocare la funzione originale (o il prossimo hook nella catena). Questo è vitale per:
- **Preservare la Funzionalità:** Se non chiami l'originale, la native hookata smetterà semplicemente di funzionare per altri plugin o per il server.
- **Incatenamento di Hooks:** Permette a più plugin di hookare la stessa native e che tutti gli hook vengano eseguiti in sequenza.
- **Manipolazione del Ritorno:** Puoi ispezionare e persino modificare il valore di ritorno di `Call_Original_Native` prima di restituirlo dalla tua funzione di hook.

```cpp
// Esempio: Blocco di SendClientMessage se contiene una parola specifica
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Estrae i parametri per l'analisi
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // Non abbiamo bisogno del colore per questa logica
    std::string message = p.Get_String(2); // Ottiene la stringa del messaggio

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGGIO BLOCCATO per playerid %d: %s", playerid, message.c_str());

        return 0; // Restituisce 0 (false) a Pawn, indicando che il messaggio non è stato inviato.
                  // E, cosa più importante, NON chiamiamo Call_Original_Native, bloccando il messaggio.
    }

    // Se il messaggio non contiene la parola proibita, chiamiamo la native originale
    // e ne restituiamo il valore, garantendo che il messaggio venga inviato normalmente
    // e che altri hook (se esistono) vengano eseguiti.
    return Call_Original_Native(SendClientMessage);
}
```

#### Esempio Completo di `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS non è strettamente necessario per gli hook, ma è comune avere OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook per la native CreateVehicle
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Estrae i parametri della native CreateVehicle per l'ispezione
    int modelid = p.Get<int>(0);
    float x = p.Get<float>(1);
    float y = p.Get<float>(2);
    float z = p.Get<float>(3);
    float angle = p.Get<float>(4);
    int color1 = p.Get<int>(5);
    int color2 = p.Get<int>(6);
    int respawn_delay = p.Get<int>(7);
    bool addsiren = p.Get<bool>(8);

    Samp_SDK::Log("HOOK: CreateVehicle chiamato! Modello: %d, Pos: (%.2f, %.2f, %.2f)", modelid, x, y, z);

    // Esempio di come *modificare* un parametro di input
    // Se il modello è 400 (Landstalker), lo cambiamo in 401 (Bravura)
    if (modelid == 400) {
        // Modifichiamo direttamente l'array 'params' per la chiamata originale
        params[1] = static_cast<cell>(401); // Il modello è nella posizione 0 dell'array di parametri (params[1])
        Samp_SDK::Log("  -> Modello 400 cambiato in 401 prima della creazione.");
    }
    
    // Chiamiamo la native originale (o il prossimo hook nella catena) con i parametri eventualmente modificati
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle ha restituito: %d (ID del veicolo)", (int)original_retval);

    // Puoi modificare il valore di ritorno qui prima di restituirlo a Pawn.
    // Esempio: se la creazione del veicolo è fallita, restituisci un ID invalido personalizzato.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Creazione del veicolo fallita nella native originale.");

        return -1; // Restituisce un valore diverso a Pawn.
    }

    return original_retval; // Restituisce il valore restituito dalla native originale (o quello modificato sopra).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Implementazioni minime per il ciclo di vita
bool OnLoad() {
    Samp_SDK::Log("Plugin di Esempio di Native Hook caricato!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Plugin di Esempio di Native Hook scaricato!");
}

// Questi callbacks saranno presenti solo se SAMP_SDK_WANT_AMX_EVENTS è definito
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load rilevato: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload rilevato: %p", (void*)amx);
}*/
```
> [!WARNING]
> La manipolazione diretta dell'array `cell* params` per alterare i parametri di input richiede cautela. Assicurati di comprendere l'ordine e il tipo dei parametri. Per la maggior parte dei casi d'uso, `p.Get(...)` per ispezionare e `Call_Original_Native(...)` per continuare la catena è sufficiente. La modifica diretta di `params` dovrebbe essere fatta solo se sai che il parametro è un valore e deve essere modificato per la chiamata originale. Per stringhe e array, la modifica è più complessa e generalmente coinvolge `amx::Set_String` per scrivere all'indirizzo esistente o riallocare, il che può essere più facile da gestire chiamando la native tramite `Pawn_Native` con i nuovi valori e restituendo `0` dal tuo hook per annullare la chiamata originale.

### 3.5. `Pawn_*` Macro: Chiamata di Funzioni Pawn da C++

Queste macro sono l'inverso di `Plugin_Public` e `Plugin_Native`: permettono al tuo codice C++ di invocare funzioni Pawn.

#### `Pawn_Native(NomeDellaNative, ...)`

- **Scopo:** Il modo raccomandato per chiamare funzioni native di SA-MP (o di altri plugin) da C++.
- **Meccanismo:** Cerca il puntatore della native nella cache interna dell'SDK (popolata da `Amx_Register_Detour`). Se trovato, esegue la native in un ambiente `Amx_Sandbox` (un'istanza AMX fittizia e isolata).
- **Performance:** La più efficiente, poiché evita la costosa ricerca di `publics` e interagisce direttamente con il puntatore della native.

#### `Pawn_Public(NomeDellaPublic, ...)`

- **Scopo:** Chiama una funzione pubblica specifica in uno script Pawn.
- **Meccanismo:** Percorre le istanze `AMX*` gestite da `Amx_Manager`, cerca la `public` per nome e la esegue.
- **Performance:** Meno efficiente di `Pawn_Native` a causa della ricerca e dell'`amx_Exec` reale. Generalmente, le `publics` sono più lente delle `natives`.
- **Uso:** Ideale per invocare eventi personalizzati nei tuoi Gamemode/Filterscripts che non sono native.

#### `Pawn(NomeDellaFunzione, ...)`

- **Scopo:** Una macro di convenienza che tenta di indovinare se la funzione è una native o una public.
- **Meccanismo:** Per prima cosa, tenta di chiamare come `Pawn_Native`. Se fallisce (la native non viene trovata), tenta di chiamare come `Pawn_Public`.
- **Performance:** Può essere leggermente più lenta di `Pawn_Native` se la funzione è native, a causa del doppio tentativo di ricerca. Per le `publics`, le prestazioni sono le stesse di `Pawn_Public`.
- **Uso:** Per funzioni dove non sei sicuro se sono native o public, o per evitare il boilerplate di tentare una e poi l'altra.

#### Sintassi e Convenzioni

- **Nome della Funzione:** Usa sempre il nome della funzione Pawn **direttamente, senza virgolette**. L'SDK lo convertirà internamente in una stringa.
- **Parametri:** Passa direttamente i parametri C++.

```cpp
// Corretto:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Errato (ma tecnicamente funzionerebbe a causa dell'hash, evitare):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling dei Parametri di Input

L'SDK converte i tuoi tipi C++ nel formato `cell` dell'AMX, gestendo la memoria come necessario:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (usando `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (alloca memoria nell'AMX, copia la stringa e passa l'indirizzo `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling dei Parametri di Output (Riferimenti: `int&`, `float&`, `std::string&`)

Questa è una funzionalità chiave per comodità e sicurezza. Per le funzioni Pawn che si aspettano un puntatore (riferimento), l'SDK automatizza l'intero processo di allocazione/deallocazione della memoria e copia dei dati.

- **Come usare:** Basta passare la tua variabile per riferimento (`&`).
- **Meccanismo:** L'SDK alloca memoria nell'heap dell'AMX, passa l'indirizzo AMX alla funzione Pawn, si aspetta che la funzione Pawn riempia questo indirizzo, rilegge il valore e libera la memoria dell'AMX. Tutto in modo trasparente.
- **Con `std::string&`:** L'SDK alloca un buffer standard (256 celle) nell'AMX per la stringa.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Posizione di %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interno:%d Mondo:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### L'Oggetto `Callback_Result`: Analisi Completa

Tutte le chiamate `Pawn_*` restituiscono un oggetto `Callback_Result`. Questo oggetto è un wrapper sicuro per il risultato della chiamata Pawn.

- `Callback_Result() noexcept`: Costruttore predefinito, indica fallimento (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Costruttore per successo o fallimento con valore.
- `explicit operator bool() const`: Permette di usare `if (result)` per verificare se la chiamata ha avuto successo.
- `operator cell() const`: Permette di convertire il risultato in `cell` per ottenere il valore.
- `float As_Float() const`: Comodità per ottenere il risultato come `float`.
- `cell Value() const`: Restituisce il valore `cell` grezzo.
- `bool Success() const`: Restituisce `true` se la chiamata Pawn ha avuto successo.
- `int Get_Amx_Error() const`: Restituisce il codice di errore dell'AMX se la chiamata è fallita (0 per successo).

```cpp
// Esempio: Ottenere la vita di un giocatore.
// La native GetPlayerHealth(playerid, &Float:health) si aspetta un playerid e un riferimento alla vita.
int playerid = 0; // Esempio di ID giocatore
float player_health = 0.0f;

// Chiamiamo GetPlayerHealth, passando playerid e player_health per riferimento.
// L'SDK si occuperà del marshalling per il parametro di output 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Verifica se la chiamata ha avuto successo (operatore bool)
    // Il valore restituito da result.As_Float() o result (operatore cell)
    // sarebbe il valore di ritorno della *native*, non il parametro di output.
    // Il valore della vita è già stato aggiornato in 'player_health' a causa del marshalling del parametro di output.
    Samp_SDK::Log("Giocatore %d ha %.1f di vita.", playerid, player_health);
}
else {
    // La chiamata è fallita, forse il giocatore non esiste o la native non è stata trovata.
    Samp_SDK::Log("Errore nell'ottenere la vita del giocatore %d. Codice AMX: %d", playerid, result.Get_Amx_Error());
}

// Per le native che restituiscono un valore e usano parametri di output (meno comune, ma possibile),
// useresti entrambi:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param è già aggiornato
// }
```

### 3.6. `Plugin_Module`: Gestione dei Moduli Dinamici

La macro `Plugin_Module` consente al tuo plugin di agire come un "caricatore" per altri plugin, creando un'architettura modulare ed estensibile. Un modulo caricato in questo modo è trattato come un plugin di prima classe, con il proprio ciclo di vita degli eventi gestito dal plugin host.

#### Sintassi e Scopo

- `Plugin_Module(const char* nome_del_file_base, const char* directory_del_modulo, const char* messaggio_di_successo_opzionale)`
- `nome_del_file_base`: Il nome *base* del file del modulo, **senza estensione** (es: per `my_module.dll` o `my_module.so`, usa `"my_module"`). L'SDK aggiungerà automaticamente l'estensione `.dll` o `.so` appropriata.
- `directory_del_modulo`: Il percorso della directory in cui si trova il file del modulo (es: `"plugins/my_custom_modules"`). **Non includere il nome del file qui.** L'SDK concatenerà il percorso completo (`directory_del_modulo/nome_del_file_base.ext`).
- `messaggio_di_successo_opzionale`: Un messaggio opzionale da loggare nella console del server se il modulo viene caricato con successo.

```cpp
// main.cpp, all'interno di OnLoad()

// Carica il modulo 'core_logic.dll' (o 'core_logic.so')
// che si trova nella cartella 'modules/custom/' del server.
if (!Plugin_Module("core_logic", "modules/custom", "Modulo Logica Core caricato con successo!"))
    return (Samp_SDK::Log("ERRORE FATALE: Impossibile caricare il modulo 'core_logic'!"), false);

// Carica il modulo 'admin_system.dll' (o 'admin_system.so')
// che si trova direttamente nella cartella 'plugins/' del server.
if (!Plugin_Module("admin_system", "plugins", "Modulo di Amministrazione attivato."))
    Samp_SDK::Log("AVVISO: Impossibile caricare il modulo di Amministrazione.");
```

#### Ciclo di Vita di un Modulo

Un modulo deve esportare le funzioni `Load`, `Unload` e `Supports`, proprio come un normale plugin. L'SDK gestisce il ciclo di vita del modulo come segue:

- **Caricamento:** Quando viene chiamato `Plugin_Module`, l'SDK:
   1. Costruisce il percorso completo del file (es: `modules/custom/core_logic.dll`).
   2. Usa `Dynamic_Library` (`LoadLibrary`/`dlopen`) per caricare il binario.
   3. **Ottiene i puntatori a TUTTE le funzioni del ciclo di vita del modulo:**
      - **Obbligatorie:** `Load`, `Unload`, `Supports`. Se ne manca una, il caricamento del modulo fallisce.
      - **Opzionali:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Chiama la funzione `Load` del modulo, passando `ppData` del plugin principale.
   5. Se `Load` restituisce `true`, il modulo viene aggiunto alla lista interna dei moduli caricati.

- **Inoltro di Eventi:** Il plugin host **inoltra automaticamente** gli eventi a tutti i moduli caricati.
 > [!IMPORTANT]
 > Affinché gli eventi vengano inoltrati correttamente, il **plugin host** (quello che chiama `Plugin_Module`) deve essere configurato per ricevere tali eventi.
 > - Affinché `AmxLoad` e `AmxUnload` funzionino nei moduli, il plugin host deve definire la macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Affinché `ProcessTick` funzioni nei moduli, il plugin host deve definire la macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Scaricamento:** Durante `OnUnload` del tuo plugin principale, l'SDK scarica tutti i moduli che sono stati caricati tramite `Plugin_Module`. Questo viene fatto in **ordine inverso** rispetto al caricamento (l'ultimo caricato è il primo a essere scaricato), il che è cruciale per gestire le dipendenze e garantire il corretto rilascio delle risorse.

#### Benefici della Modularizzazione

- **Organizzazione del Codice:** Dividi grandi plugin in componenti più piccoli e gestibili, ognuno nel proprio file modulo.
- **Riusabilità:** Crea moduli generici (es: un modulo database, un modulo avanzato di sistema di log) che possono essere usati da diversi plugin, promuovendo la riusabilità del codice.
- **Componenti Indipendenti:** Crea moduli che sono **totalmente orientati agli eventi e indipendenti**. Un modulo può avere le proprie `Plugin_Native`s, intercettare `Plugin_Public`s e avere la propria logica `OnProcessTick`, operando come un plugin autonomo, ma caricato da un host.
- **Aggiornamenti Dinamici:** In scenari controllati, consente l'aggiornamento di parti del tuo sistema (sostituendo una `.dll` o `.so` del modulo) senza la necessità di ricompilare e riavviare il plugin principale o l'intero server (anche se ciò richiede una gestione rigorosa della versione e della compatibilità).

### 3.7. `Plugin_Call`: Chiamata delle Native Interne del Plugin

Usa `Plugin_Call` per invocare una `Plugin_Native` definita **all'interno del tuo stesso plugin**.

#### Sintassi e Vantaggi di Performance

- `Plugin_Call(NomeDellaNative, Param1, Param2, ...)`
- **Vantaggio:** Evita l'overhead di cercare la native nell'array di native dell'AMX. L'SDK mantiene una mappa diretta di hash di nomi a puntatori di funzione per le proprie native, rendendo questo il modo più veloce per chiamarle internamente.
- **Richiede:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logica per verificare il livello
    return (playerid % 2 == 0) ? 1 : 0; // Esempio: livello pari per ID pari
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Chiama la tua stessa native
                Samp_SDK::Log("Giocatore %d è di alto livello!", i);
        }
    }
}
```

### 3.8. Funzioni Utilità dell'SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Descrizione:** Stampa messaggi nella console del server e nel file `server_log.txt`. Un wrapper sicuro per `logprintf`.
- **Uso:** Per debug, messaggi di stato ed errori.
- **Meccanismo:** Internamente, l'SDK ottiene il puntatore a `logprintf` tramite `ppData[PLUGIN_DATA_LOGPRINTF]`. La funzione gestisce la formattazione della stringa in modo sicuro.

```cpp
// Ovunque nel tuo plugin
Samp_SDK::Log("Il plugin è stato inizializzato con un valore %d e una stringa '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Raccomandato)

- **Descrizione:** Formatta una stringa in modo sicuro (simile a `sprintf`) e restituisce una `std::string`. Questo è il modo **raccomandato e più idiomatico** per formattare stringhe da utilizzare all'interno del tuo plugin.
- **Uso:** Ideale per costruire messaggi formattati prima di passarli a `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, o per qualsiasi altra esigenza di stringa all'interno del tuo codice C++.
- **Meccanismo:** Internamente, `Plugin_Format` è una macro che chiama `Samp_SDK::Format`. Utilizza `vsnprintf` per determinare la dimensione esatta della stringa formattata e alloca una `std::string` con capacità sufficiente, evitando overflow del buffer.

```cpp
int playerid = 0; // Esempio di ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Giocatore %d, la tua vita attuale è %d.", playerid, health));

// Può essere usato anche per i log interni
Samp_SDK::Log(Plugin_Format("DEBUG: Elaborazione dello stato per l'ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Dettaglio di Implementazione)

- **Descrizione:** La funzione di implementazione sottostante per la formattazione di stringhe, situata all'interno del namespace `Samp_SDK`.
- **Uso:** Generalmente non è chiamata direttamente dall'utente. La macro `Plugin_Format` è fornita come una convenienza per questa funzione, allineandosi con la convenzione di denominazione di altre macro dell'SDK (`Plugin_Public`, `Plugin_Native`). La chiameresti direttamente solo se volessi evitare la macro `Plugin_Format` per qualche motivo specifico.

```cpp
// Esempio di come funziona Samp_SDK::Format, ma preferisci Plugin_Format
std::string raw_status = Samp_SDK::Format("Solo per uso interno: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Descrizione:** Converte un indirizzo di stringa AMX (`cell amx_addr`) in una `std::string` C++.
- **Uso:** Principalmente all'interno di `Plugin_Native` e `Plugin_Native_Hook` quando è necessario accedere a stringhe che non vengono automaticamente convertite da `Register_Parameters` o `Native_Params` (es: se il parametro Pawn è una `const` `string` e non è stato dichiarato come `std::string` nel tuo `Plugin_Native` o `Plugin_Public` per il Marshalling automatico).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Ottiene l'indirizzo della stringa nell'AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("Stringa dall'AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Anatomia Interna e Architettura dell'SDK

Questa sezione svela i meccanismi sottostanti dell'SA-MP SDK, esplorando la sua architettura, i componenti chiave e come interagiscono per fornire l'astrazione di alto livello. Una comprensione approfondita di questi interni consente allo sviluppatore di ottimizzare l'uso dell'SDK, eseguire il debug di problemi complessi e persino estenderne le funzionalità.

### 4.1. `core.hpp`: La Fondazione Minimalista

Il `Samp_SDK::Core` è un `singleton` che funge da punto di accesso iniziale e centralizzato ai dati di basso livello forniti dall'ambiente del plugin SA-MP. La sua responsabilità principale è incapsulare ed esporre le funzionalità essenziali.

- **`Samp_SDK::Core::Instance()`**:
   - **Descrizione:** Restituisce l'unica istanza globale della classe `Core`. Questo è un design pattern `singleton` per garantire che l'accesso ai dati del plugin (`ppData`) sia coerente e centralizzato.
   - **Meccanismo:** L'istanza viene inizializzata una sola volta quando `Core::Instance().Load(ppData)` viene chiamato nella funzione `Load()` del tuo plugin.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Descrizione:** Permette l'accesso sicuro e indicizzato ai puntatori di funzione dell'API AMX. L'array `pAMXFunctions` (ricevuto tramite `ppData[PLUGIN_DATA_AMX_EXPORTS]`) contiene gli indirizzi di funzioni critiche come `amx_Exec`, `amx_Register`, ecc.
   - **Impatto:** Invece di usare `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, l'SDK offre wrapper type-safe nel namespace `amx::` (es: `amx::Exec(...)`), rendendo il codice più leggibile e meno propenso a errori di cast.
   - **Esempio Interno (`amx_api.hpp`):**
      ```cpp
      // Snippet semplificato di amx_api.hpp
      namespace amx {
          template <typename Func, int Index, typename... Args>
          inline auto Call(Args... args) -> decltype(std::declval<Func>()(args...)) {
              using Return_Type = decltype(std::declval<Func>()(args...));
              auto func_ptr = reinterpret_cast<Func>(Core::Instance().Get_AMX_Export(Index));

              if (SAMP_SDK_UNLIKELY(!func_ptr)) {
                  Log("[SA-MP SDK] Fatal: Tentativo di chiamare l'export AMX all'indice %d, ma pAMXFunctions non è stato caricato!", Index);
                
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
   - **Descrizione:** Un puntatore alla funzione `logprintf` di SA-MP, che è l'interfaccia standard per stampare messaggi nella console del server e nel `server_log.txt`.
   - **Meccanismo:** Il `Samp_SDK::Log` è un wrapper sicuro che utilizza questo puntatore, garantendo che i tuoi messaggi vengano visualizzati correttamente nell'ambiente SA-MP.

### 4.2. `platform.hpp` e `version.hpp`: Compatibilità e Metadati

Questi header sono la base per la portabilità e l'ottimizzazione dell'SDK, adattandolo a diversi ambienti di compilazione e sfruttando funzionalità specifiche del C++ moderno.

- **Rilevamento di Piattaforma e Architettura:**
   - **Meccanismo:** Utilizza macro di precompilazione (`#if defined(WIN32)`, `#if defined(__linux__)`, ecc.) per identificare il sistema operativo.
   - **Verifica dell'Architettura:** Contiene `static_assert` o `#error` per garantire che il plugin sia compilato per x86 (32-bit), un requisito critico per la compatibilità con SA-MP e il meccanismo di hooking.
   - **Gestione dell'Esportazione di Simboli:**
      - `SAMP_SDK_EXPORT`: Una macro definita in `platform.hpp` che si espande in `extern "C"` e, su Linux, aggiunge `__attribute__((visibility("default")))`. Su Windows, garantisce solo `extern "C"` perché l'SDK utilizza `pragma comment(linker, "/EXPORT:...")` (per MSVC) o lo standard MinGW per esportare le funzioni principali.
      - Questo garantisce che le funzioni del ciclo di vita del plugin (`Supports`, `Load`, `Unload`, ecc.) siano correttamente esportate dal tuo DLL/SO, indipendentemente dall'ambiente di compilazione, **senza la necessità di file `.def` o di aggiungere `__attribute__((visibility("default")))` manualmente** nella tua implementazione.
   - **Esempio (`platform.hpp` - frammento rilevante):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // Per MSVC, l'esportazione è gestita dai comandi del linker pragma
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // Per GCC/Clang su Linux, usiamo l'attributo di visibilità
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... altre definizioni ...
      ```
   - **Esempio (`samp_sdk.hpp` - frammento rilevante dell'implementazione):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // Su Windows (MSVC), usiamo pragma comment per esportare le funzioni.
          // Questo elimina la necessità di un file .def.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... altre esportazioni ...
      #endif

      // Implementazione delle funzioni esportate
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... altre funzioni ...
      #endif
      ```

- **Macro di Ottimizzazione e Previsione di Branch:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Meccanismo:** `__forceinline` (MSVC) o `__attribute__((always_inline)) inline` (GCC/Clang). Suggerisce fortemente al compilatore di inserire il corpo della funzione direttamente nel punto di chiamata, eliminando l'overhead di una chiamata di funzione reale.
      - **Uso:** Applicato a funzioni piccole e critiche per le prestazioni all'interno dell'SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Meccanismo:** `[[likely]]` / `[[unlikely]]` (C++20) o `__builtin_expect` (GCC/Clang). Suggerimenti al compilatore su quale percorso di un `if/else` è più probabile che venga preso.
      - **Impatto:** Aiuta il compilatore a generare codice più efficiente per la previsione dei salti (branch prediction), riducendo la latenza della CPU.
      - **Esempio (`platform.hpp`):**
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

- **Definizioni C++ Standard (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Meccanismo:** Macro definite in base al valore di `__cplusplus` e `_MSVC_LANG`.
   - **Uso:** Consentono all'SDK di utilizzare funzionalità C++ più recenti (come `std::apply` e `if constexpr` di C++17, o `std::is_same_v` di C++17) quando disponibili, mantenendo la compatibilità con standard più vecchi.
   - **Esempio (`version.hpp` - uso di `if constexpr`):**
      ```cpp
      // Snippet semplificato di public_dispatcher.hpp
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
                  // Compatibilità C++14: usare la funzione ausiliaria Assign_Parameter_By_Type
                  Assign_Parameter_By_Type(amx, &value, first); 
      #endif
          }

          Get_Public_Params_Recursive(amx, index + 1, rest...);
      }
      ```

### 4.3. `function_hook.hpp`: Il Motore di Intercettazione x86

Questo header definisce il meccanismo di basso livello per eseguire gli hook (intercettazioni) delle funzioni, che è fondamentale per il funzionamento dell'SDK. Dipende strettamente dall'architettura x86 (32-bit).

- **`X86_Detour`**:
   - **Descrizione:** Una classe che incapsula la logica di sovrascrivere l'inizio di una funzione in memoria con un'istruzione di salto a una funzione di deviazione.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Meccanismo:** In x86, l'istruzione di salto (`JMP`) relativa ha generalmente 5 byte: `0xE9` (opcode per JMP near, relative) seguito da 4 byte che rappresentano lo scostamento (offset) dell'indirizzo di destinazione rispetto alla prossima istruzione.
      - **Esempio di istruzione:** `E9 XX XX XX XX` (dove `XX` sono i byte dello scostamento).
   - **`Apply(void* target, void* detour)`**:
      - **Azione:** Installa l'hook. Per prima cosa, memorizza i `JUMP_INSTRUCTION_SIZE` byte originali della funzione `target` (`original_bytes_`). Quindi, calcola l'indirizzo relativo di `detour` rispetto a `target` e sovrascrive l'inizio di `target` con l'istruzione `JMP`.
      - **Esempio del calcolo dell'indirizzo relativo:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Indirizzo della deviazione - (Indirizzo del target + Dimensione dell'istruzione JMP)
         ```
   - **`Revert()`**:
      - **Azione:** Disinstalla l'hook, ripristinando gli `original_bytes_` nella funzione `target`.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Meccanismo:** Su Windows, usa `VirtualProtect`; su Linux, `mprotect`. Queste chiamate di sistema modificano i permessi della pagina di memoria in cui risiede la funzione in `EXECUTE_READWRITE` (Windows) o `PROT_WRITE | PROT_EXEC` (Linux), consentendo la modifica del codice in fase di esecuzione.
      - **Esempio (`Unprotect_Memory`):**
         ```cpp
         // Snippet semplificato di function_hook.hpp
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
   - **Descrizione:** Un wrapper C++ `type-safe` per `X86_Detour`, che garantisce che i tipi di puntatore a funzione siano corretti.
   - `Install(void* target, void* detour)`: Incapsula la chiamata `X86_Detour::Apply`.
   - `Uninstall()`: Incapsula la chiamata `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Meccanismo di Sicurezza (Guarda di Ricorsione):** Questa funzione è critica per evitare loop infiniti quando la deviazione deve chiamare la funzione originale. Essa **disinstalla temporaneamente l'hook (`detour_.Revert()`)**, chiama la funzione originale (`Get_Original()(args...)`), e quindi **reinstalla l'hook (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Un contatore che garantisce che l'hook venga reinstallato solo quando la chiamata originale di livello superiore è completata, consentendo chiamate ricorsive sicure della funzione originale (se la funzione originale è ricorsiva, ad esempio). Il `thread_local` garantisce che `recursion_guard` sia isolato per ogni thread, importante in ambienti multi-threaded.
      - **Esempio (`Call_Original` con Scope_Guard):**
         ```cpp
         // Snippet semplificato di function_hook.hpp
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

### 4.4. `interceptor_manager.hpp`: Il Controllore di Hooks dell'AMX

Questo `singleton` è il centro nevralgico dell'interazione dell'SDK con la macchina virtuale AMX di SA-MP. Coordina l'installazione degli hook forniti da `function_hook.hpp` nelle funzioni API AMX esposte dal server, reindirizzando il flusso di esecuzione alla logica dell'SDK.

- **`Activate()` / `Deactivate()`**:
   - **Descrizione:** Metodi pubblici per installare e disinstallare tutti gli hook necessari. Chiamati in `OnLoad()` e `OnUnload()` del tuo plugin, rispettivamente.
   - **Meccanismo:** Ottiene i puntatori delle funzioni AMX (come `amx_Register`, `amx_Exec`, ecc.) usando `Core::Instance().Get_AMX_Export(...)` e installa le deviazioni.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Funzione Hooked:** `amx_Register`
   - **Scopo:** Intercetta la registrazione di *tutte* le native (da SA-MP, altri plugin o gamemode).
   - **Azione:** Per ogni native registrata, l'`Interceptor_Manager` la aggiunge a una cache interna (`Cache_Data::native_cache`).
   - **Impatto:** Questa cache è fondamentale per le prestazioni di `Pawn_Native`, consentendo una ricerca estremamente rapida del puntatore della native invece di una costosa ricerca nell'AMX.
   - **Funzione aggiuntiva per `Plugin_Native_Hook`:** Questo detour *è anche* responsabile della modifica dell'elenco delle native prima che vengano registrate. Se una native ha un `Plugin_Native_Hook` associato, il puntatore della funzione nell'elenco di registrazione viene sostituito dal trampoline generato dal `Native_Hook_Manager`. Questo consente al tuo hook di essere il primo ad essere chiamato.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Funzione Hooked:** `amx_Exec`
   - **Scopo:** **Questo è l'hook più critico.** Intercetta *qualsiasi* esecuzione di codice nell'AMX, inclusa la chiamata di `publics` di Pawn.
   - **Meccanismo di Intercettazione di `Plugin_Public`:**
      1. Quando `amx_Exec` viene chiamato per una `public` (o `AMX_EXEC_MAIN`), viene eseguito l'`Amx_Exec_Detour`.
      2. Ottiene il nome della `public` (usando `tl_public_name` che è stato riempito da `Amx_Find_Public_Detour`).
      3. Interroga il `Public_Dispatcher::Instance().Dispatch()` per verificare se ci sono gestori C++ registrati per questo nome.
      4. Se ci sono gestori, li esegue. Il `Public_Dispatcher` si occupa del `marshalling` dei parametri dall'AMX ai tipi C++ corretti.
      5. In base al valore di ritorno del `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), decide se chiamare l'`amx_Exec` originale (`Get_Amx_Exec_Hook().Call_Original(...)`) o se terminare l'esecuzione della `public` di Pawn.
      6. **Manipolazione dello Stack:** Se l'esecuzione della `public` di Pawn viene interrotta (`PLUGIN_PUBLIC_STOP`), l'`Amx_Exec_Detour` corregge lo stack dell'AMX (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) per evitare incongruenze.
   - **Attivazione di `Plugin_Native_Hook` (Patching AMX):**
      - La prima volta che un `AMX*` viene eseguito, questo detour verifica se l'AMX è già stata "patchata" (`!manager.Is_Amx_Patched(amx)`).
      - Se non lo è, scorre la tabella delle native **di quella specifica istanza AMX in memoria**.
      - Per ogni native che ha un `Plugin_Native_Hook` registrato nel `Native_Hook_Manager`, sostituisce l'indirizzo della native nella tabella con un trampoline generato dal `Native_Hook_Manager`. L'indirizzo originale (o dell'hook precedente) viene salvato nell'oggetto `Native_Hook`.
      - L'AMX viene quindi contrassegnata come "patchata" per evitare una rielaborazione non necessaria.
   - **Esempio (`Amx_Exec_Detour` - con dettagli di `Plugin_Native_Hook`):**
      ```cpp
      // Snippet semplificato di interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          auto& manager = Interceptor_Manager::Instance();

          std::unique_ptr<std::string> public_name_ptr;

          // Logica di intercettazione di Plugin_Public (come descritto sopra)
          // ...

          int exec_result = Get_Amx_Exec_Hook().Call_Original(amx, retval, index);

          // Logica di Patching per Plugin_Native_Hook
          if (SAMP_SDK_UNLIKELY(!manager.Is_Amx_Patched(amx))) {
              auto& hook_manager = Native_Hook_Manager::Instance();
              auto& hooks_to_apply = hook_manager.Get_All_Hooks();

              if (!hooks_to_apply.empty()) {
                  AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
                  AMX_FUNCSTUBNT* natives = reinterpret_cast<AMX_FUNCSTUBNT*>(reinterpret_cast<unsigned char*>(hdr) + hdr->natives);

                  int num_natives;

                  amx::Num_Natives(amx, &num_natives);

                  for (auto& hook_to_apply : hooks_to_apply) { // Percorre tutti i Plugin_Native_Hook registrati
                      uint32_t hook_hash = hook_to_apply.Get_Hash();

                      for (int i = 0; i < num_natives; ++i) { // Percorre le native dell'AMX
                          const char* native_name = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(hdr) + natives[i].nameofs);

                          if (FNV1a_Hash(native_name) == hook_hash) { // Se il nome della native dell'AMX corrisponde a un hook
                              AMX_NATIVE current_func = reinterpret_cast<AMX_NATIVE>(natives[i].address);

                              hook_to_apply.Set_Next_In_Chain(current_func); // Salva il puntatore della funzione originale/precedente

                              AMX_NATIVE trampoline = hook_manager.Get_Trampoline(hook_hash); // Ottiene il trampoline per questo hook

                              if (trampoline)
                                  natives[i].address = reinterpret_cast<ucell>(trampoline); // Sostituisce nella tabella dell'AMX
                              
                              break;
                          }
                      }
                  }
              }
              
              manager.On_Amx_Patched(amx); // Marca l'AMX come patchata
          }
          
          return exec_result;
      }
      ```
- **`int SAMP_SDK_AMX_API Amx_Find_Public_Detour(...)`**:
   - **Funzione Hooked:** `amx_FindPublic`
   - **Scopo:** Intercetta la ricerca di `publics` per nome.
   - **Meccanismo di "Ghost Publics":** Se `amx_FindPublic` originale non trova una `public` in Pawn, ma il `Public_Dispatcher` ha un handler C++ registrato per quel nome, questo hook restituisce `AMX_ERR_NONE` e un `index` speciale (`PLUGIN_EXEC_GHOST_PUBLIC`). Questo fa sì che l'API di SA-MP "pensi" che la `public` esista, consentendo che la successiva chiamata `amx_Exec` (per questo indice speciale) venga intercettata da `Amx_Exec_Detour`, che poi reindirizza all'handler C++.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Usata per passare il nome della `public` all'`Amx_Exec_Detour` quando viene rilevato un "ghost public", poiché `amx_Exec` riceve solo l'indice, non il nome.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Funzioni Hooked:** `amx_Init` / `amx_Cleanup`
   - **Scopo:** Gestire l'elenco delle istanze `AMX*` attive.
   - **Azione:** `Amx_Init_Detour` chiama `Amx_Manager::Instance().Add_Amx()`, e `Amx_Cleanup_Detour` chiama `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Gestione delle Istanze `AMX*`

Questo `singleton` mantiene un registro dinamico di tutte le macchine virtuali AMX attualmente caricate nel server. È essenziale per funzioni che devono interagire con "tutti gli script" o trovare uno script specifico.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Descrizione:** Un elenco di puntatori a tutte le istanze `AMX*` che sono state inizializzate (gamemode e filterscripts).
   - **Gestione:** Popolato dagli hook `Amx_Init_Detour` e svuotato da `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Scopo:** Protegge `loaded_amx_` dall'accesso concorrente in ambienti multi-threaded (anche se SA-MP è prevalentemente single-thread, questa è una buona pratica di sicurezza). `std::shared_mutex` consente più lettori contemporaneamente, ma solo uno scrittore.
- **`std::atomic<uint32_t> generation_`**:
   - **Scopo:** Un contatore che si incrementa ogni volta che un AMX viene aggiunto o rimosso.
   - **Uso:** Viene utilizzato da `Caller_Cache` in `callbacks.hpp` per rilevare quando l'elenco di AMX è cambiato, invalidando le cache di ricerca delle `publics` e garantendo che le chiamate `Pawn_Public` operino sempre con informazioni aggiornate. Questo ottimizza le prestazioni evitando ricerche ripetitive in uno stato che non è cambiato.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Descrizione:** Scorre `loaded_amx_` (dal più recente al più vecchio, il che di solito mette il gamemode o il filterscript più rilevante per primo) per trovare la `public` con il nome specificato.
   - **Meccanismo:** Usa `amx::Find_Public` per ogni istanza `AMX*`.
   - **Impatto:** È la base per `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: Il Router di Callbacks `Plugin_Public`

Questo `singleton` è il componente che mappa i nomi delle `publics` di Pawn alle tue funzioni C++ `Plugin_Public`.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Chiave:** L'hash FNV1a del nome della `public` (es: `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Valore:** Un `std::vector` di `std::function<cell(AMX*)>`, dove ogni `std::function` è un handler C++ registrato per quella `public`.
   - **Meccanismo:** La `std::vector` consente di registrare più `Plugin_Public` per lo stesso callback (es: diversi plugin che vogliono intercettare `OnPlayerCommandText`). I gestori vengono eseguiti in ordine inverso di registrazione.
- **`Public_Register`**:
   - **Meccanismo:** Questa è una classe template la cui macro `PLUGIN_PUBLIC_REGISTRATION` crea un'istanza statica globale. Nel costruttore statico (`static bool registered = [...]`), essa registra il suo handler `Plugin_Public` nel `Public_Dispatcher`. Questo è un pattern di "registrazione statica in fase di compilazione/inizializzazione".
   - **Esempio (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Register<decltype(&name), &name, hash_##name> register_##name;
      ```

- **`Public_Traits` e `Wrapper()`**:
   - **Meccanismo:** `Public_Traits` è un template di trait che, usando la metaprogrammazione, genera una funzione `static cell Wrapper(AMX* amx)`.
   - **Scopo:** Questa `Wrapper` è la `Amx_Handler_Func` che il `Public_Dispatcher` effettivamente memorizza e chiama. È responsabile di:
      1. Chiamare `Public_Param_Reader::Get_Public_Params(amx, args...)` per estrarre i parametri dallo stack AMX.
      2. Chiamare la tua vera funzione C++ `Plugin_Public` (`func_ptr`) con i parametri già convertiti nei tipi C++ corretti.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Descrizione:** Un insieme di funzioni template ricorsive che leggono i valori dallo stack AMX e li convertono nei tipi C++ specificati nella dichiarazione del `Plugin_Public`.
   - **Meccanismo:** Usa `Get_Stack_Cell()` per accedere alle `cell` nello stack. Utilizza `if constexpr` (C++17+) o `std::is_same<T>::value` (C++14) per applicare la conversione corretta (`amx::AMX_CTOF` per float, `Samp_SDK::Get_String` per stringa, cast diretto per int).

### 4.7. `native.hpp`: Gestione e Chiamata delle Native del Plugin

Questo header è dedicato alla creazione e alla gestione delle native C++ che il tuo plugin espone a Pawn.

- **`Native_List_Holder`**:
   - **Descrizione:** Un `singleton` globale che memorizza tutte le `Plugin_Native`s dichiarate nel tuo plugin (da tutti i file `.cpp` che usano `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Contiene oggetti `Native` (che memorizzano il nome della native e il puntatore alla funzione C++ `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Una mappa ottimizzata per hash per ricerche veloci di `Plugin_Native` interne (usata da `Plugin_Call`).
- **`Native_Register`**:
   - **Meccanismo:** Come `Public_Register`, questa è una classe template la cui macro `Plugin_Native` crea un'istanza statica globale. Nel suo costruttore, aggiunge la native al `Native_List_Holder`.
   - **Impatto:** Ti permette di dichiarare `Plugin_Native`s in più file `.cpp` senza preoccuparti della registrazione manuale. Tutte verranno raccolte automaticamente.
- **`Native_Registry`**:
   - **Descrizione:** Una classe ausiliaria che, in `OnAmxLoad`, prende l'elenco completo delle `Native`s da `Native_List_Holder` e le formatta in un array `AMX_NATIVE_INFO`.
   - **Meccanismo:** Chiama `amx::Register(amx, amx_natives_info_.data(), -1)` per registrare tutte le tue native nell'istanza AMX appena caricata.
- **`Plugin_Call_Impl(...)`**:
   - **Descrizione:** L'implementazione sottostante della macro `Plugin_Call`.
   - **Meccanismo:** Utilizza `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` per ottenere direttamente il puntatore alla funzione C++.
   - **Ambiente:** Esegue la native in un ambiente `Amx_Sandbox` (isolato) per gestire lo stack e l'heap temporanei, in modo simile a come funziona `Pawn_Native`.

### 4.8. `native_hook_manager.hpp`: Il Motore di Hooks delle Native

Questo è il robusto sistema di hooking delle native, progettato per gestire l'incatenamento di hook di più plugin per la stessa native.

- **`Native_Hook`**:
   - **Descrizione:** Una classe che rappresenta un singolo hook di native. Memorizza l'hash del nome della native, la funzione handler C++ fornita dall'utente (`user_handler_`) e un `std::atomic<AMX_NATIVE> next_in_chain_`.
   - **`user_handler_`**: La tua funzione C++ `Plugin_Native_Hook`.
   - **`next_in_chain_`**: Il puntatore alla native originale o all'hook di un plugin con priorità inferiore. È un `std::atomic` per garantire la thread-safety in lettura/scrittura.
   - **`Dispatch(AMX* amx, cell* params)`**: Chiamata dal trampoline per eseguire il tuo `user_handler_`.
   - **`Call_Original(AMX* amx, cell* params)`**: Metodo cruciale che chiama `next_in_chain_`, permettendo al tuo hook di invocare la funzionalità originale o il prossimo hook nella catena.
- **`Trampoline_Allocator`**:
   - **Descrizione:** Una classe responsabile dell'allocazione di blocchi di memoria eseguibile e della generazione del codice assembly "trampoline" in questi blocchi.
   - **`Generate_Trampoline_Code(unsigned char* memory, int hook_id)`**: Scrive 10 byte di assembly:
      1. `B8 XX XX XX XX`: `MOV EAX, hook_id` (inserisce l'ID univoco dell'hook nel registro EAX).
      2. `E9 XX XX XX XX`: `JMP relative_address_to_Dispatch_Wrapper_Asm` (salta alla funzione di dispatch generica dell'SDK).
   - **`Allocation_Size = 4096`**: Alloca memoria in pagine per efficienza e allineamento della cache.
   - **Permessi di Memoria:** Usa `VirtualAlloc` (Windows) o `mmap` (Linux) con permessi `EXECUTE_READWRITE` per garantire che il codice generato possa essere eseguito.
- **`Dispatch_Wrapper_Asm()`**:
   - **Descrizione:** Una piccola funzione in assembly (definita con `__declspec(naked)` o `asm volatile`) che serve come destinazione per tutti i trampoline.
   - **Azione:** Salva i registri, sposta `EAX` (che contiene l'`hook_id`) sullo stack e chiama la funzione `Dispatch_Hook` in C++. Dopo il ritorno da `Dispatch_Hook`, ripristina i registri e ritorna.
- **`cell SAMP_SDK_CDECL Dispatch_Hook(int hook_id, AMX* amx, cell* params)`**:
   - **Descrizione:** La funzione C++ generica chiamata da `Dispatch_Wrapper_Asm`.
   - **Azione:** Usa `hook_id` per trovare il `Native_Hook` corrispondente nel `Native_Hook_Manager` e chiama il suo metodo `Dispatch()`, che a sua volta invoca l'handler `Plugin_Native_Hook` dell'utente.
- **`Native_Hook_Manager`**:
   - **Descrizione:** Il `singleton` centrale che gestisce tutti i `Native_Hook`s registrati e i loro trampoline.
   - **`std::list<Native_Hook> hooks_`**: Memorizza l'elenco degli hook in ordine.
   - **`std::unordered_map<uint32_t, Trampoline_Func> hash_to_trampoline_`**: Mappa l'hash del nome della native al puntatore del trampoline generato.
   - **`std::vector<uint32_t> hook_id_to_hash_`**: Mappa l'ID intero dell'hook (usato nel trampoline) all'hash del nome della native.
   - **`Get_Trampoline(uint32_t hash)`**: Restituisce (o crea e alloca) un puntatore trampoline per un dato hash di native.
- **`PLUGIN_NATIVE_HOOK_REGISTRATION`**:
   - **Meccanismo:** Una macro che crea una classe statica globale (`Native_Hook_Register_##name`) per ogni `Plugin_Native_Hook`. Nel costruttore statico di questa classe, registra l'handler dell'utente nel `Native_Hook_Manager`.

### 4.9. `callbacks.hpp` & `amx_memory.hpp`: Chiamate C++ -> Pawn e RAII

Questi header costituiscono la spina dorsale per chiamare funzioni Pawn da C++ (macro `Pawn_*`) e garantiscono la sicurezza della memoria.

- **`Amx_Sandbox`**:
   - **Descrizione:** Una struttura `thread_local` che simula un ambiente `AMX` minimalista e isolato per le chiamate `Pawn_Native` e `Plugin_Call`.
   - **Meccanismo:** Possiede la propria `AMX` struct, `AMX_HEADER` e un `std::vector<unsigned char> heap` per simulare la memoria di uno script. Questo permette di chiamare `amx::Push`, `amx::Allot`, ecc., senza interferire con lo stato degli script Pawn reali in esecuzione.
   - **`thread_local`:** Garantisce che ogni thread abbia la propria `Amx_Sandbox`, prevenendo condizioni di gara se l'SDK viene utilizzato in un contesto multi-threaded (es: un futuro pool di thread per operazioni non-Pawn).
   - **Esempio (`Amx_Sandbox`):**
      ```cpp
      // Snippet semplificato di callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Memoria simulata per stack/heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Inizializza l'AMX e l'header
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
   - **Descrizione:** Un insieme di funzioni template sovraccaricate che gestisce il `marshalling` di *ogni* parametro C++ nel formato `cell` atteso dall'AMX, e viceversa per i parametri di output.
   - **Elaborazione Input:**
       - Per `int`, `float`, `bool`: Converte direttamente in `cell`.
       - Per `const char*`, `std::string`: Alloca memoria nell'heap di `Amx_Sandbox` (o AMX reale per `Pawn_Public`), copia la stringa e spinge l'indirizzo AMX sullo stack.
   - **Elaborazione Output (`is_output_arg`):**
       - **Meccanismo:** Quando un argomento è un riferimento lvalue non-const (rilevato dal trait `is_output_arg`), il `Parameter_Processor` non spinge il valore, ma un *indirizzo AMX* per una `cell` allocata temporaneamente nell'heap.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Dopo la chiamata della native Pawn, viene eseguita una lista di lambda (`post_call_updaters`). Ogni lambda è responsabile di leggere il valore finale della `cell` allocata nell'AMX e assegnarlo di nuovo alla variabile C++ originale (es: `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Meccanismo:** Un `std::integral_constant` (trait di tipo) che, in fase di compilazione, valuta se un tipo di parametro C++ è un riferimento modificabile (es: `int&`, `float&`, `std::string&`). Ciò consente al `Parameter_Processor` di distinguere i parametri di input da quelli di output.
   - **Esempio (`is_output_arg`):**
      ```cpp
      // Snippet semplificato di callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Descrizione:** Una classe RAII (`Resource Acquisition Is Initialization`) che incapsula l'allocazione e la deallocazione della memoria nell'AMX.
   - **Meccanismo:** Nel costruttore, chiama `amx::Allot` per ottenere un `amx_addr` e un `phys_addr`. Nel distruttore, chiama `amx::Release` per liberare questa memoria.
   - **Impatto:** **Cruciale per prevenire perdite di memoria nell'heap dell'AMX.** Garantisce che la memoria temporanea usata per stringhe o parametri di output sia sempre liberata, anche se si verificano eccezioni o ritorni anticipati.

### 4.10. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Accesso Astratto all'AMX

Questi header forniscono le definizioni fondamentali e gli strumenti di alto livello per interagire con Pawn.

- **`amx_defs.h`**:
   - **Contenuto:** Contiene le definizioni grezze delle strutture AMX (`AMX`, `AMX_HEADER`), tipi (`cell`, `ucell`) ed enum di errore (`AmxError`). Definisce anche `AMX_NATIVE` e `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Utilizza attributi di impacchettamento (`#pragma pack(push, 1)` / `__attribute__((packed))`) per garantire che le strutture AMX abbiano il layout di memoria corretto, fondamentale per l'interoperabilità.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Descrizione:** La funzione template principale per invocare le funzioni dell'API AMX esposte dal server.
   - **Meccanismo:** Ottiene il puntatore della funzione tramite `Core::Instance().Get_AMX_Export(Index)` e lo chiama. Centralizza la gestione degli errori se il puntatore della funzione non è disponibile.
   - **Impatto:** Converte le chiamate di basso livello (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) in chiamate C++ idiomatiche e type-safe (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Descrizione:** Funzioni essenziali per convertire valori `cell` in `float` e viceversa, eseguendo una reinterpretazione bit per bit della memoria.
   - **`static_assert`:** Includono `static_assert` per garantire che `sizeof(cell) == sizeof(float)` in fase di compilazione, prevenendo errori su piattaforme con dimensioni di tipo diverse.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Descrizione:** Helper per convertire un indirizzo AMX di stringa in `std::string`.
   - **Meccanismo:** Innanzitutto, ottiene l'indirizzo fisico (`cell* phys_addr`) della stringa nell'AMX usando `amx::Get_Addr`. Quindi, usa `amx::STR_Len` per determinarne la lunghezza e `amx::Get_String` per copiare i byte in una `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Descrizione:** La funzione base di formattazione delle stringhe (`printf`-like) per l'SDK.
   - **Meccanismo:** Utilizza `vsnprintf` in due passaggi: prima per determinare la dimensione necessaria della stringa, e poi per formattare la stringa nella `std::string` allocata dinamicamente. Questo evita overflow del buffer.

## 5. Compilazione e Deploy

### Requisiti di Architettura e Piattaforma

- Il tuo plugin **DEVE** essere compilato per l'architettura **x86 (32-bit)**.
- Piattaforme Supportate: Windows (.dll) e Linux (.so).

### Esempi di Comandi di Compilazione

#### **MSVC (Visual Studio)**

1. Crea un nuovo progetto di "Dynamic-Link Library (DLL)".
2. Nelle impostazioni del progetto, imposta la "Piattaforma di Soluzione" su **x86**.
3. Assicurati che lo standard del linguaggio C++ sia almeno C++14.

#### **GCC / Clang (Linux)**

```bash
# Per un plugin chiamato 'my_plugin.so' da 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compila per 32-bit.
- `-shared`: Crea una libreria condivisa (`.so`).
- `-std=c++17`: Definisce lo standard C++ come C++17 (può essere `c++14` o `c++20`).
- `-O2`: Livello di ottimizzazione 2.
- `-fPIC`: Genera codice indipendente dalla posizione, necessario per le librerie condivise.
- `-Wall -Wextra`: Attiva avvisi aggiuntivi per aiutare a rilevare errori.
- `-Wl,--no-undefined`: Impedisce la creazione della libreria se ci sono simboli indefiniti.

#### **GCC / Clang (MinGW su Windows)**

```bash
# Per un plugin chiamato 'my_plugin.dll' da 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Collega la libreria standard C++ in modo statico. Essenziale per evitare che il tuo plugin dipenda da DLL di runtime specifiche del compilatore che potrebbero non essere presenti nel sistema dell'utente.
- `-static-libgcc`: Collega la libreria GCC in modo statico.

### Considerazioni per la Distribuzione

- **Nome del File:** Il tuo plugin deve avere l'estensione `.dll` (Windows) o `.so` (Linux). Es: `my_plugin.dll`.
- **Posizione:** Posiziona il file compilato nella cartella `plugins/` del tuo server SA-MP.
- **server.cfg:** Aggiungi il nome del tuo plugin (se è Windows, senza estensione) alla riga `plugins` in `server.cfg`.
   ```
   plugins my_plugin (se è Linux, my_plugin.so)
   ```

## Licenza

Copyright © **SA-MP Programming Community**

Questo software è concesso in licenza secondo i termini della Licenza MIT ("Licenza"); è possibile utilizzare questo software in conformità con le condizioni della Licenza. Una copia della Licenza può essere ottenuta su: [MIT License](https://opensource.org/licenses/MIT)

### Termini e Condizioni d'Uso

#### 1. Permessi Concessi

La presente licenza concede gratuitamente a chiunque ottenga una copia di questo software e dei file di documentazione associati i seguenti diritti:
* Utilizzare, copiare, modificare, unire, pubblicare, distribuire, sublicenziare e/o vendere copie del software senza restrizioni
* Permettere alle persone a cui il software viene fornito di fare lo stesso, soggetto alle seguenti condizioni

#### 2. Condizioni Obbligatorie

Tutte le copie o parti sostanziali del software devono includere:
* L'avviso di copyright sopra riportato
* Questo avviso di permesso
* L'avviso di esclusione di responsabilità sotto riportato

#### 3. Diritti d'Autore

Il software e tutta la documentazione associata sono protetti dalle leggi sul diritto d'autore. La **SA-MP Programming Community** mantiene la titolarità dei diritti d'autore originali del software.

#### 4. Esclusione di Garanzia e Limitazione di Responsabilità

IL SOFTWARE VIENE FORNITO "COSÌ COM'È", SENZA GARANZIE DI ALCUN TIPO, ESPLICITE O IMPLICITE, INCLUSE, MA NON LIMITATE A, LE GARANZIE DI COMMERCIABILITÀ, IDONEITÀ PER UN PARTICOLARE SCOPO E NON VIOLAZIONE.

IN NESSUN CASO GLI AUTORI O I TITOLARI DEL COPYRIGHT SARANNO RESPONSABILI PER QUALSIASI RECLAMO, DANNO O ALTRA RESPONSABILITÀ, SIA IN UN'AZIONE DI CONTRATTO, ILLECITO O ALTRO, DERIVANTE DA, FUORI O IN CONNESSIONE CON IL SOFTWARE O L'USO O ALTRE OPERAZIONI NEL SOFTWARE.

---

Per informazioni dettagliate sulla Licenza MIT, consultare: https://opensource.org/licenses/MIT