# SAMP SDK

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

- [SAMP SDK](#samp-sdk)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [1. Introduzione e Filosofia di Design](#1-introduzione-e-filosofia-di-design)
    - [Il Problema con l'API C Standard di SA-MP](#il-problema-con-lapi-c-standard-di-sa-mp)
    - [La Soluzione di SAMP SDK: Astrazione con Sicurezza e Performance](#la-soluzione-di-samp-sdk-astrazione-con-sicurezza-e-performance)
    - [Modello Header-Only: Vantaggi e Implicazioni](#modello-header-only-vantaggi-e-implicazioni)
  - [2. Configurazione e Ambiente](#2-configurazione-e-ambiente)
    - [Requisiti di Compilazione](#requisiti-di-compilazione)
    - [Struttura di File Raccomandata](#struttura-di-file-raccomandata)
    - [Macro Essenziali di Configurazione\*\*](#macro-essenziali-di-configurazione)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definizioni e Costanti di SA-MP (`samp_defs.hpp`)](#definizioni-e-costanti-di-sa-mp-samp_defshpp)
  - [3. Guida all'Uso Completo dell'API](#3-guida-alluso-completo-dellapi)
    - [3.1. Il Ciclo di Vita del Plugin](#31-il-ciclo-di-vita-del-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Intercettazione di Eventi Pawn](#32-plugin_public-intercettazione-di-eventi-pawn)
      - [Sintassi e Dichiarazione](#sintassi-e-dichiarazione)
      - [Marshalling Automatico dei Parametri](#marshalling-automatico-dei-parametri)
      - [Controllo di Flusso: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#controllo-di-flusso-plugin_public_continue-vs-plugin_public_stop)
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
      - [Ritorno di Valori](#ritorno-di-valori)
    - [3.4. `Pawn_*` Macro: Chiamata di Funzioni Pawn da C++](#34-pawn_-macro-chiamata-di-funzioni-pawn-da-c)
      - [`Pawn_Native(NomeDellaNativa, ...)`](#pawn_nativenomedellanativa-)
      - [`Pawn_Public(NomeDellaPublic, ...)`](#pawn_publicnomedellapublic-)
      - [`Pawn(NomeDellaFuncao, ...)`](#pawnnomedellafuncao-)
      - [Sintassi e Convenzioni](#sintassi-e-convenzioni)
      - [Marshalling dei Parametri di Input](#marshalling-dei-parametri-di-input)
      - [Marshalling dei Parametri di Output (Riferimenti: `int&`, `float&`, `std::string&`)](#marshalling-dei-parametri-di-output-riferimenti-int-float-stdstring)
      - [L'Oggetto `Callback_Result`: Analisi Completa](#loggetto-callback_result-analisi-completa)
      - [**3.5. `Plugin_Module`: Gestione dei Moduli Dinamici**](#35-plugin_module-gestione-dei-moduli-dinamici)
      - [Sintassi e Scopo](#sintassi-e-scopo)
      - [Ciclo di Vita di un Modulo](#ciclo-di-vita-di-un-modulo)
      - [Vantaggi della Modularizzazione](#vantaggi-della-modularizzazione)
    - [3.6. `Plugin_Call`: Chiamata di Native Interne del Plugin](#36-plugin_call-chiamata-di-native-interne-del-plugin)
      - [Sintassi e Vantaggi di Performance](#sintassi-e-vantaggi-di-performance)
    - [**3.7. Funzioni Utility dell'SDK**](#37-funzioni-utility-dellsdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Raccomandato)](#stdstring-plugin_formatconst-char-format--raccomandato)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Dettaglio di Implementazione)](#stdstring-samp_sdkformatconst-char-format--dettaglio-di-implementazione)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. **Anatomia Interna e Architettura dell'SDK**](#4-anatomia-interna-e-architettura-dellsdk)
    - [4.1. `core.hpp`: La Fondazione Minimalista](#41-corehpp-la-fondazione-minimalista)
    - [**4.2. `platform.hpp` e `version.hpp`: Compatibilità e Metadati**](#42-platformhpp-e-versionhpp-compatibilità-e-metadati)
    - [4.3. `function_hook.hpp`: Il Motore di Intercettazione x86](#43-function_hookhpp-il-motore-di-intercettazione-x86)
    - [4.4. `interceptor_manager.hpp`: Il Controllore di Hooks dell'AMX](#44-interceptor_managerhpp-il-controllore-di-hooks-dellamx)
    - [4.5. `amx_manager.hpp`: Gestione delle Istanze `AMX*`](#45-amx_managerhpp-gestione-delle-istanze-amx)
    - [4.6. `public_dispatcher.hpp`: Il Router di Callbacks `Plugin_Public`](#46-public_dispatcherhpp-il-router-di-callbacks-plugin_public)
    - [4.7. `native.hpp`: Gestione e Chiamata di Native del Plugin](#47-nativehpp-gestione-e-chiamata-di-native-del-plugin)
    - [4.8. `callbacks.hpp` \& `amx_memory.hpp`: Chiamate C++ -\> Pawn e RAII](#48-callbackshpp--amx_memoryhpp-chiamate-c---pawn-e-raii)
    - [4.9. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Accesso Astratto all'AMX](#49-amx_apihpp--amx_helpershpp--amx_defsh-accesso-astratto-allamx)
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

L'API di plugin di SA-MP è un'interfaccia di programmazione in C. Sebbene funzionale e fondamentale, presenta le sfide inerenti alla programmazione di basso livello:
- **Gestione Manuale della Memoria:** Funzioni come `amx_Allot` e `amx_Release` richiedono che lo sviluppatore allochi e deallochi esplicitamente la memoria nell'heap dell'AMX. Questo è una fonte comune di perdite di memoria e errori di runtime.
- **Tipizzazione Debole e Conversioni Manuali:** I parametri sono passati come un array di `cell`s, forzando conversioni esplicite (e spesso insicure) tra `cell`, `int`, `float`, e `char*`.
- **Verbosity e Boilerplate:** Estrarre più parametri da un array `cell* params`, gestire le dimensioni delle stringhe e gestire lo stack dell'AMX per le chiamate di ritorno da C++ a Pawn richiede codice ripetitivo.
- **Fragilità dell'Interfaccia:** La mancanza di verifica in fase di compilazione (type safety) significa che errori nel passaggio di parametri o tipi possono passare inosservati fino all'esecuzione, causando crash o comportamenti indefiniti.

### La Soluzione di SAMP SDK: Astrazione con Sicurezza e Performance

Il SAMP SDK affronta questi problemi fornendo un potente strato di astrazione in C++:
- **RAII (Resource Acquisition Is Initialization):** Gestione automatica della memoria nell'AMX. `Amx_Scoped_Memory` garantisce che la memoria allocata sia rilasciata.
- **Sicurezza dei Tipi:** Conversione automatica e sicura dei parametri tra C++ e Pawn. Si gestiscono direttamente `int`, `float`, `std::string`.
- **Sintassi Concisa e Idiomatica:** Macro e template forniscono un'API pulita che assomiglia più al C++ moderno che all'API C tradizionale.
- **Intercettazione Robusta:** Un motore di hooking avanzato permette l'intercettazione trasparente di callbacks Pawn (`Plugin_Public`) e la registrazione dinamica di native.
- **Alte Performance:** Uso estensivo di hashing in tempo di compilazione (FNV1a), caching di funzioni e ottimizzazioni `thread_local` per minimizzare l'overhead delle astrazioni.

### Modello Header-Only: Vantaggi e Implicazioni

L'SDK è composto esclusivamente da file di intestazione (`.hpp`, `.h`).
- **Vantaggi:**
   - **Integrazione Semplificata:** Non ci sono librerie da costruire, linkare o distribuire. Basta includere gli header.
   - **Ottimizzazioni del Compilatore:** Il compilatore ha piena visibilità del codice dell'SDK e del tuo plugin, permettendo inlining aggressivo e ottimizzazioni in fase di link, il che può risultare in binari più veloci.
- **Implicazioni:**
   - **Tempo di Compilazione:** Per progetti molto grandi, la compilazione può richiedere più tempo a causa dell'inclusione ripetuta del codice dell'SDK. Questo è mitigato da guardie di inclusione e dalla natura "includere solo ciò che è necessario" del C++.
   - **Macro di Implementazione:** La necessità della macro `SAMP_SDK_IMPLEMENTATION` è una conseguenza del modello header-only per evitare ridefinizioni di simboli.

## 2. Configurazione e Ambiente

### Requisiti di Compilazione

- **Compilatore C++:** Compatibile con C++14 o superiore (l'SDK utilizza funzionalità di C++14, C++17 e C++20 per ottimizzazioni specifiche, ma C++14 è il minimo).
   - GCC (versione 7+)
   - Clang (versione 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Architettura:** **x86 (32-bit)**. SA-MP opera esclusivamente su questa architettura. L'SDK include verifiche in `platform.hpp` che emetteranno errori di compilazione se viene rilevata un'architettura errata.
- **Sistema Operativo:** Windows o Linux.

### Struttura di File Raccomandata

Per chiarezza e organizzazione, è comune organizzare l'SDK in una sottocartella `samp-sdk`.

```
meu_plugin/
├── samp-sdk/
│   ├── // Outros arquivos do SDK
│   └── samp_sdk.hpp             // O principal header a ser incluído
│
├── src/
│   ├── main.cpp                  // Onde SAMP_SDK_IMPLEMENTATION é definido
│   └── my_custom_logic.cpp       // Opcional, para organizar código
│
└── CMakeLists.txt (ou .vcxproj, Makefile)
```

### Macro Essenziali di Configurazione**

Definisci sempre queste macro *prima* di includere `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Scopo:** Segnala al compilatore che questo file `.cpp` deve generare le implementazioni delle funzioni di esportazione del plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **L'SDK si occupa automaticamente dell'esportazione di queste funzioni, eliminando la necessità di file `.def` (su Windows) o dichiarazioni `__attribute__((visibility("default")))` (su Linux) per queste funzioni.**
- **Impatto Tecnico:** Senza questa macro, il linker non troverà le esportazioni necessarie e il server SA-MP non potrà caricare il tuo plugin.
- **Regola Fondamentale:** **Definisci questa macro in UN SOLO file `.cpp` in tutto il tuo progetto.** Definirla in più di un file causerà un errore di linkaggio di "simbolo duplicato".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // A macro faz o SDK exportar as funções necessárias automaticamente.
#include "samp-sdk/samp_sdk.hpp"

// ... seu código de plugin ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Scopo:** Abilita le funzionalità dell'SDK relative all'interazione con l'ambiente dell'AMX (macchina virtuale Pawn).
- **Funzionalità Attivate:**
   - Dichiarazione e registrazione di native C++ usando `Plugin_Native`.
   - Callbacks `OnAmxLoad(AMX* amx)` e `OnAmxUnload(AMX* amx)`.
   - La macro `Plugin_Call` per invocare le native del plugin stesso.
- **Impatto Tecnico:** Quando questa macro è definita, l'SDK raccoglie automaticamente tutte le tue `Plugin_Native`s. Nella funzione `Supports()`, la flag `SUPPORTS_AMX_NATIVES` viene aggiunta automaticamente.
- **Flessibilità:** **Puoi definire questa macro in più file `.cpp`**. Il sistema di registrazione statica dell'SDK (`Native_Registrar`) consoliderà tutte le native da diverse unità di compilazione in un'unica lista globale.

```cpp
// my_natives.cpp (pode ser um arquivo separado do main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Apenas para habilitar Plugin_Native
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Scopo:** Abilita il callback `OnProcessTick()`, che viene invocato regolarmente dal server.
- **Impatto Tecnico:** Aggiunge automaticamente la flag `SUPPORTS_PROCESS_TICK` nella funzione `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Lógica executada a cada "tick" do servidor (ex: 20ms)
    // Cuidado com operações pesadas aqui!
}
```

### Definizioni e Costanti di SA-MP (`samp_defs.hpp`)

Questo file fornisce tutte le costanti e i limiti noti di SA-MP, come `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, ecc. Viene automaticamente incluso da `samp_sdk.hpp` e deve essere utilizzato per garantire la compatibilità e la leggibilità del codice.

## 3. Guida all'Uso Completo dell'API

### 3.1. Il Ciclo di Vita del Plugin

Le seguenti funzioni sono i punti di ingresso e di uscita del tuo plugin, esportate automaticamente dall'SDK.

#### `bool OnLoad()`

- **Descrizione:** Prima funzione chiamata dal server SA-MP dopo il caricamento riuscito del tuo plugin in memoria.
- **Uso:** Ideale per inizializzare qualsiasi sistema, caricare configurazioni, aprire connessioni a database o caricare moduli (`Plugin_Module`).
- **Ritorno:**
   - `true`: Il plugin è stato inizializzato con successo e il caricamento continua.
   - `false`: Il plugin ha fallito l'inizializzazione. Il caricamento verrà abortito e il plugin verrà scaricato.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Inicializando MeuPlugin v1.0...");

    // Exemplo: Carregar um módulo (mais detalhes na seção 3.5)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Módulo de Banco de Dados carregado.")) {
        Samp_SDK::Log("ERRO: Falha ao carregar o módulo de banco de dados!");

        return false; // Aborta o carregamento do plugin principal
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
    Samp_SDK::Log("MeuPlugin descarregado. Liberando recursos...");
    // Nenhuma ação manual é necessária para módulos carregados via Plugin_Module;
    // o SDK cuida disso.
}
```

#### `unsigned int GetSupportFlags()`

- **Descrizione:** Informa al server SA-MP quali risorse il tuo plugin supporta e desidera utilizzare.
- **Uso:** **Restituisci sempre `SUPPORTS_VERSION` (o `SAMP_PLUGIN_VERSION`).** Le altre flag (`SUPPORTS_AMX_NATIVES`, `SUPPORTS_PROCESS_TICK`) vengono aggiunte automaticamente dall'SDK se le macro `SAMP_SDK_WANT_AMX_EVENTS` e `SAMP_SDK_WANT_PROCESS_TICK` sono definite. Ciò semplifica la manutenzione ed evita errori.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // O SDK adiciona as flags necessárias automaticamente.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Richiede:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrizione:** Chiamata ogni volta che un nuovo script Pawn (un Gamemode o Filterscript) viene caricato e inizializzato sul server.
- **Uso:** Se hai bisogno di logica specifica per ogni script AMX, come la registrazione di native personalizzate (anche se `Plugin_Native` lo fa automaticamente), o l'inizializzazione di dati specifici per script.

```cpp
// main.cpp (com SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxLoad(AMX* amx) {
    // amx representa a nova instância do script carregado.
    // Você pode, por exemplo, chamar uma public específica neste script:
    // Pawn_Public_OnAmx("OnMyPluginLoaded", amx); // Exemplo hipotético de uma API mais avançada.
    Samp_SDK::Log("Script AMX carregado: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Richiede:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrizione:** Chiamata quando uno script Pawn viene scaricato dal server.
- **Uso:** Per pulire qualsiasi risorsa specifica che hai allocato o associato a quel particolare `AMX*`.

```cpp
// main.cpp (com SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX descarregado: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Richiede:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Descrizione:** Chiamata ripetutamente ad ogni "tick" del server (generalmente 20 volte al secondo, o ogni 50ms).
- **Uso:** Per logica di fondo continua, timer, aggiornamenti di stato che non dipendono da eventi del giocatore, o sincronizzazione di dati.
- **Attenzione:** Evita operazioni bloccanti o computazionalmente pesanti qui, poiché potrebbero causare lag nel server.

```cpp
// main.cpp (com SAMP_SDK_WANT_PROCESS_TICK definido)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // A cada 10 segundos (20 ticks/seg * 10 seg = 200 ticks)
        Samp_SDK::Log("Servidor ativo por %d segundos.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Intercettazione di Eventi Pawn

La macro `Plugin_Public` è il ponte primario per ricevere callbacks Pawn nel tuo codice C++.

#### Sintassi e Dichiarazione

- `Plugin_Public(NomeDellaPublic, Tipo1 Param1, Tipo2 Param2, ...)`
- Il nome della funzione C++ che dichiari **deve essere lo stesso** del callback Pawn (es: `OnPlayerConnect`).
- I tipi di parametri C++ (`int`, `float`, `std::string`) vengono automaticamente convertiti dall'SDK.

```cpp
// Intercepta OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    // ...
}
```

#### Marshalling Automatico dei Parametri

L'SDK gestisce automaticamente la lettura dello `cell stack` dell'AMX e la conversione ai tipi C++ specificati:
- `int`: Convertito direttamente da `cell`.
- `float`: Convertito da `cell` usando `amx::AMX_CTOF`.
- `std::string`: L'SDK legge l'indirizzo della stringa nell'AMX, alloca una `std::string` in C++ e copia il contenuto.

#### Controllo di Flusso: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

Il valore restituito dalla tua funzione `Plugin_Public` è cruciale e determina il flusso di esecuzione del callback:
- `return PLUGIN_PUBLIC_CONTINUE;` (valore `1`): Indica che l'esecuzione del callback deve **continuare**. Se ci sono altri plugin che intercettano questo callback, verranno chiamati. Successivamente, verrà invocata la `public` originale nello script Pawn.
- `return PLUGIN_PUBLIC_STOP;` (valore `0`): Indica che l'esecuzione del callback deve essere **interrotta**. Nessun altro plugin o la `public` originale nello script Pawn verrà invocato per questo evento. Questo è ideale per implementare un sistema che "sovrascrive" o "blocca" un comportamento predefinito di SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Congela o jogador
        Pawn_Native(SendClientMessage, playerid, -1, Pawn_Format("Jogador %d congelado.", playerid));

        return PLUGIN_PUBLIC_STOP; // Impede que o comando seja processado por outros scripts.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Permite que outros comandos sejam processados.
}
```

### 3.3. `Plugin_Native`: Creazione di Funzioni Native in C++

`Plugin_Native` ti consente di estendere la funzionalità di Pawn con codice C++ ad alte prestazioni.

#### Sintassi e Firma Fissa

- `Plugin_Native(NomeDellaNativa, AMX* amx, cell* params)`
- La funzione C++ deve avere esattamente questa firma: `cell NomeDellaNativa(AMX* amx, cell* params)`.
- `NomeDellaNativa` è il nome che gli script Pawn useranno.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementação ...
    return 0;
}
```

#### Registrazione Automatica delle Native

> [!NOTE]
> **Non è necessario** chiamare `amx_Register` manualmente. L'SDK rileva tutte le tue `Plugin_Native`s (in qualsiasi file `.cpp` con `SAMP_SDK_WANT_AMX_EVENTS`) e le registra automaticamente in ogni script AMX caricato (`OnAmxLoad`).

#### Estrazione dei Parametri: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Descrizione:** Helper più semplice per estrarre più parametri sequenzialmente.
- **Uso:** `Register_Parameters(variabile1, variabile2, ...)`
- **Limitazioni:** Per parametri di input. Non gestisce parametri opzionali o accesso per indice.
- **Tipi Supportati:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extrai os 3 parâmetros
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)

- **Descrizione:** Una classe wrapper che fornisce un'interfaccia orientata agli oggetti per accedere ai parametri di una nativa. Più potente per scenari complessi.
- **Costruzione:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Descrizione:** Restituisce il numero di parametri passati alla nativa.
- **Uso:** Essenziale per gestire i parametri opzionali.

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

    // Obtém os valores das referências (o Pawn passou endereços)
    p.Get_REF(1, health); // Lê o valor de Float:health
    p.Get_REF(2, money);   // Lê o valor de money
    
    Samp_SDK::Log("Jogador %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Agora, modifique-os
    health = 50.0f;
    money += 100;
    
    // E os escreve de volta na memória do Pawn
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

#### Ritorno di Valori

- La tua funzione `Plugin_Native` deve restituire una `cell`.
- Per restituire un `int` o `bool`, usa un cast a `cell`.
- Per restituire un `float`, usa `amx::AMX_FTOC(meu_float)`.

```cpp
// Retorna um bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    int playerid = p.Get<int>(0);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Retorna um float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Retorna 100.0f
}
```

### 3.4. `Pawn_*` Macro: Chiamata di Funzioni Pawn da C++

Queste macro sono l'inverso di `Plugin_Public` e `Plugin_Native`: permettono al tuo codice C++ di invocare funzioni Pawn.

#### `Pawn_Native(NomeDellaNativa, ...)`

- **Scopo:** Il modo raccomandato per chiamare funzioni native di SA-MP (o di altri plugin) da C++.
- **Meccanismo:** Cerca il puntatore della nativa nella cache interna dell'SDK (popolata da `Amx_Register_Detour`). Se trovata, esegue la nativa in un ambiente `Amx_Sandbox` (un'istanza AMX fittizia e isolata).
- **Performance:** La più efficiente, poiché evita la costosa ricerca di `publics` e interagisce direttamente con il puntatore della nativa.

#### `Pawn_Public(NomeDellaPublic, ...)`

- **Scopo:** Chiama una funzione pubblica specifica in uno script Pawn.
- **Meccanismo:** Scorre le istanze `AMX*` gestite da `Amx_Manager`, cerca la `public` per nome e la esegue.
- **Performance:** Meno efficiente di `Pawn_Native` a causa della ricerca e del vero `amx_Exec`. Generalmente, le `publics` sono più lente delle `natives`.
- **Uso:** Ideale per invocare eventi personalizzati nei tuoi Gamemode/Filterscripts che non sono native.

#### `Pawn(NomeDellaFuncao, ...)`

- **Scopo:** Una macro di convenienza che tenta di indovinare se la funzione è nativa o pubblica.
- **Meccanismo:** Inizialmente, tenta di chiamare come `Pawn_Native`. Se fallisce (la nativa non viene trovata), tenta di chiamare come `Pawn_Public`.
- **Performance:** Può essere leggermente più lenta di `Pawn_Native` se la funzione è nativa, a causa del doppio tentativo di ricerca. Per le `publics`, le prestazioni sono le stesse di `Pawn_Public`.
- **Uso:** Per funzioni dove non sei sicuro se siano native o pubbliche, o per evitare il boilerplate di tentare una e poi l'altra.

#### Sintassi e Convenzioni

- **Nome della Funzione:** Usa sempre il nome della funzione Pawn **direttamente, senza virgolette**. L'SDK lo convertirà internamente in stringa.
- **Parametri:** Passa i parametri C++ direttamente.

```cpp
// Certo:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Errado (mas tecnicamente funcionaria devido ao hash, evite):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling dei Parametri di Input

L'SDK converte i tuoi tipi C++ nel formato `cell` dell'AMX, gestendo la memoria come necessario:
-   `int`, `bool`, `long`, `enum` -> `cell`
-   `float`, `double` -> `cell` (usando `amx::AMX_FTOC`)
-   `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (alloca memoria nell'AMX, copia la stringa e passa l'indirizzo `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling dei Parametri di Output (Riferimenti: `int&`, `float&`, `std::string&`)

Questa è una funzionalità chiave per comodità e sicurezza. Per le funzioni Pawn che si aspettano un puntatore (riferimento), l'SDK automatizza l'intero processo di allocazione/deallocazione della memoria e la copia dei dati.

- **Come usare:** Basta passare la tua variabile per riferimento (`&`).
- **Meccanismo:** L'SDK alloca memoria nell'heap dell'AMX, passa l'indirizzo AMX alla funzione Pawn, si aspetta che la funzione Pawn riempia questo indirizzo, legge il valore indietro e libera la memoria dell'AMX. Tutto in modo trasparente.
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

    Samp_SDK::Log("Localização de %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interior:%d World:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### L'Oggetto `Callback_Result`: Analisi Completa

Tutte le chiamate `Pawn_*` restituiscono un oggetto `Callback_Result`. Questo oggetto è un wrapper sicuro per il risultato della chiamata Pawn.

- `Callback_Result() noexcept`: Costruttore predefinito, indica fallimento (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Costruttore per successo o fallimento con valore.
- `explicit operator bool() const`: Permette di usare `if (result)` per verificare se la chiamata è riuscita.
- `operator cell() const`: Permette di convertire il risultato in `cell` per ottenere il valore.
- `float As_Float() const`: Convenienza per ottenere il risultato come `float`.
- `cell Value() const`: Restituisce il valore raw `cell`.
- `bool Success() const`: Restituisce `true` se la chiamata Pawn è riuscita.
- `int Get_Amx_Error() const`: Restituisce il codice di errore dell'AMX se la chiamata è fallita (0 per successo).

```cpp
// Exemplo: Obtendo a vida de um jogador.
// A nativa GetPlayerHealth(playerid, &Float:health) espera um playerid e uma referência para a vida.
int playerid = 0; // Exemplo de ID de jogador
float player_health = 0.0f;

// Chamamos GetPlayerHealth, passando playerid e player_health por referência.
// O SDK cuidará do marshalling para o parâmetro de saída 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Verifica se a chamada foi bem-sucedida (operator bool)
    // O valor retornado por result.As_Float() ou result (operator cell)
    // seria o valor de retorno da *nativa*, não o parâmetro de saída.
    // O valor da vida já foi atualizado em 'player_health' devido ao marshalling do parâmetro de saída.
    Samp_SDK::Log("Jogador %d tem %.1f de vida.", playerid, player_health);
} else {
    // A chamada falhou, talvez o jogador não exista ou a nativa não foi encontrada.
    Samp_SDK::Log("Erro ao obter vida do jogador %d. Código AMX: %d", playerid, result.Get_Amx_Error());
}

// Para nativas que retornam um valor e usam parâmetros de saída (menos comum, mas possível),
// você usaria ambos:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param já está atualizado
// }
```

#### **3.5. `Plugin_Module`: Gestione dei Moduli Dinamici**

La macro `Plugin_Module` consente al tuo plugin di fungere da "caricatore" per altri plugin, creando un'architettura modulare ed estensibile. Un modulo caricato in questo modo viene trattato come un plugin di prima classe, con il proprio ciclo di vita degli eventi gestito dal plugin ospitante.

#### Sintassi e Scopo

- `Plugin_Module(const char* nome_do_arquivo_base, const char* diretorio_do_modulo, const char* mensagem_sucesso_opcional)`
- `nome_do_arquivo_base`: Il nome *base* del file del modulo, **senza l'estensione** (ad esempio, per `my_module.dll` o `my_module.so`, usa `"my_module"`). L'SDK aggiungerà automaticamente l'estensione `.dll` o `.so` appropriata.
- `diretorio_do_modulo`: Il percorso della directory in cui si trova il file del modulo (ad esempio, `"plugins/my_custom_modules"`). **Non includere il nome del file qui.** L'SDK concatenerà il percorso completo (`diretorio_do_modulo/nome_do_arquivo_base.ext`).
- `mensagem_sucesso_opcional`: Un messaggio opzionale da registrare nella console del server se il modulo viene caricato con successo.

```cpp
// main.cpp, all'interno di OnLoad()

// Carica il modulo 'core_logic.dll' (o 'core_logic.so')
// che si trova nella cartella 'modules/custom/' del server.
if (!Plugin_Module("core_logic", "modules/custom", "Modulo di Logica Principale caricato con successo!"))
    return (Samp_SDK::Log("ERRORE FATALE: Impossibile caricare il modulo 'core_logic'!"), false);

// Carica il modulo 'admin_system.dll' (o 'admin_system.so')
// che si trova direttamente nella cartella 'plugins/' del server.
if (!Plugin_Module("admin_system", "plugins", "Modulo di Amministrazione attivato."))
    Samp_SDK::Log("AVVISO: Impossibile caricare il Modulo di Amministrazione.");
```

#### Ciclo di Vita di un Modulo

Un modulo deve esportare le funzioni `Load`, `Unload` e `Supports`, proprio come un plugin normale. L'SDK gestisce il ciclo di vita del modulo come segue:

- **Caricamento:** Quando viene chiamato `Plugin_Module`, l'SDK:
   1. Costruisce il percorso completo del file (ad esempio, `modules/custom/core_logic.dll`).
   2. Utilizza `Dynamic_Library` (`LoadLibrary`/`dlopen`) per caricare il binario.
   3. **Ottiene i puntatori per TUTTE le funzioni del ciclo di vita del modulo:**
      - **Obbligatorie:** `Load`, `Unload`, `Supports`. Se una di queste manca, il caricamento del modulo fallisce.
      - **Facoltative:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Chiama la funzione `Load` del modulo, passando `ppData` del plugin principale.
   5. Se `Load` restituisce `true`, il modulo viene aggiunto alla lista interna dei moduli caricati.

- **Inoltro degli Eventi:** Il plugin ospitante **inoltra automaticamente** gli eventi a tutti i moduli caricati.
 > [!IMPORTANT]
 > Affinché gli eventi vengano inoltrati correttamente, il **plugin ospitante** (quello che chiama `Plugin_Module`) deve essere configurato per ricevere questi eventi.
 > - Affinché `AmxLoad` e `AmxUnload` funzionino nei moduli, il plugin ospitante deve definire la macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Affinché `ProcessTick` funzioni nei moduli, il plugin ospitante deve definire la macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Scarico:** Durante `OnUnload` del plugin principale, l'SDK scarica tutti i moduli caricati tramite `Plugin_Module`. Questo avviene in **ordine inverso** rispetto al caricamento (l'ultimo modulo caricato è il primo ad essere scaricato), il che è cruciale per gestire le dipendenze e garantire il corretto rilascio delle risorse.

#### Vantaggi della Modularizzazione

- **Organizzazione del Codice:** Suddividi i grandi plugin in componenti più piccoli e gestibili, ciascuno nel proprio file di modulo.
- **Riutilizzabilità:** Crea moduli generici (ad esempio, un modulo di database, un modulo di sistema di registrazione avanzato) che possono essere utilizzati da diversi plugin, promuovendo il riutilizzo del codice.
- **Componenti Indipendenti:** Crea moduli che sono **completamente guidati dagli eventi e indipendenti**. Un modulo può avere i propri `Plugin_Native`s, intercettare `Plugin_Public`s e avere la propria logica `OnProcessTick`, operando come un plugin autonomo, ma caricato da un ospitante.
- **Aggiornamenti Dinamici:** In scenari controllati, consente l'aggiornamento di parti del sistema (sostituendo un file di modulo `.dll` o `.so`) senza la necessità di ricompilare e riavviare il plugin principale o l'intero server (anche se ciò richiede una gestione rigorosa delle versioni e della compatibilità).

### 3.6. `Plugin_Call`: Chiamata di Native Interne del Plugin

Usa `Plugin_Call` per invocare una `Plugin_Native` definita **all'interno del tuo stesso plugin**.

#### Sintassi e Vantaggi di Performance

- `Plugin_Call(NomeDellaNativa, Param1, Param2, ...)`
- **Vantaggio:** Evita l'overhead di cercare la nativa nell'array di native dell'AMX. L'SDK mantiene una mappa diretta di hash di nomi a puntatori di funzione per le proprie native, rendendo questo il modo più veloce per chiamarle internamente.
- **Richiede:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Lógica para verificar o nível
    return (playerid % 2 == 0) ? 1 : 0; // Exemplo: nível par para IDs pares
}

void CheckAllPlayersLevel() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Chama sua própria nativa
                Samp_SDK::Log("Jogador %d está em um nível alto!", i);
        }
    }
}
```

### **3.7. Funzioni Utility dell'SDK**

#### `Samp_SDK::Log(const char* format, ...)`

- **Descrizione:** Stampa messaggi nella console del server e nel file `server_log.txt`. Un wrapper sicuro per `logprintf`.
- **Uso:** Per debug, messaggi di stato ed errori.
- **Meccanismo:** Internamente, l'SDK ottiene il puntatore a `logprintf` tramite `ppData[PLUGIN_DATA_LOGPRINTF]`. La funzione gestisce la formattazione della stringa in modo sicuro.

```cpp
// Em qualquer lugar do seu plugin
Samp_SDK::Log("O plugin foi inicializado com um valor %d e uma string '%s'.", 123, "teste");
```

#### `std::string Plugin_Format(const char* format, ...)` (Raccomandato)

- **Descrizione:** Formatta una stringa in modo sicuro (simile a `sprintf`) e restituisce una `std::string`. Questo è il modo **raccomandato e più idiomatico** per formattare stringhe da usare all'interno del tuo plugin.
- **Uso:** Ideale per costruire messaggi formattati prima di passarli a `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, o per qualsiasi altra esigenza di stringa all'interno del tuo codice C++.
- **Meccanismo:** Internamente, `Plugin_Format` è una macro che chiama `Samp_SDK::Format`. Utilizza `vsnprintf` per determinare la dimensione esatta della stringa formattata e alloca una `std::string` con capacità sufficiente, evitando overflow del buffer.

```cpp
int playerid = 0; // Exemplo de ID
int health = 50;
std::string status_message = Plugin_Format("Jogador %d, sua vida atual é %d.", playerid, health); // Usando a macro Plugin_Format
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, status_message);

// Também pode ser usado para logs internos
Samp_SDK::Log(Plugin_Format("DEBUG: Processando status para o ID %d", playerid).c_str());
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Dettaglio di Implementazione)

- **Descrizione:** La funzione di implementazione sottostante per la formattazione delle stringhe, situata all'interno del namespace `Samp_SDK`.
- **Uso:** Generalmente non è chiamata direttamente dall'utente. La macro `Plugin_Format` è fornita come una convenienza per questa funzione, allineandosi con la convenzione di denominazione di altre macro dell'SDK (`Plugin_Public`, `Plugin_Native`). La chiameresti direttamente solo se volessi evitare la macro `Plugin_Format` per qualche motivo specifico.

```cpp
// Exemplo de como Samp_SDK::Format funciona, mas prefira Plugin_Format
std::string raw_status = Samp_SDK::Format("Apenas para uso interno: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Descrizione:** Converte un indirizzo di stringa AMX (`cell amx_addr`) in una `std::string` C++.
- **Uso:** Principalmente all'interno di `Plugin_Native` quando hai bisogno di accedere a stringhe che non vengono automaticamente convertite da `Register_Parameters` o `Native_Params` (es: se il parametro Pawn è una `const` `string` e non è stato dichiarato come `std::string` nel tuo `Plugin_Native` o `Plugin_Public` per il Marshalling automatico).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Obtém o endereço da string na AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String da AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. **Anatomia Interna e Architettura dell'SDK**

Questa sezione svela i meccanismi sottostanti del SAMP SDK, esplorando la sua architettura, i componenti chiave e come interagiscono per fornire l'astrazione di alto livello. Una comprensione profonda di queste viscere consente allo sviluppatore di ottimizzare l'uso dell'SDK, eseguire il debug di problemi complessi e persino estenderne le funzionalità.

### 4.1. `core.hpp`: La Fondazione Minimalista

Il `Samp_SDK::Core` è un `singleton` che funge da punto di accesso iniziale e centralizzato ai dati di basso livello forniti dall'ambiente del plugin SA-MP. La sua responsabilità principale è incapsulare ed esporre le funzionalità essenziali.

- **`Samp_SDK::Core::Instance()`**:
   - **Descrizione:** Restituisce l'unica istanza globale della classe `Core`. Questo è un design pattern `singleton` per garantire che l'accesso ai dati del plugin (`ppData`) sia coerente e centralizzato.
   - **Meccanismo:** L'istanza viene inizializzata una sola volta quando `Core::Instance().Load(ppData)` viene chiamato nella funzione `Load()` del tuo plugin.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Descrizione:** Consente l'accesso sicuro e indicizzato ai puntatori di funzione dell'API AMX. L'array `pAMXFunctions` (ricevuto tramite `ppData[PLUGIN_DATA_AMX_EXPORTS]`) contiene gli indirizzi di funzioni critiche come `amx_Exec`, `amx_Register`, ecc.
   - **Impatto:** Invece di usare `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, l'SDK offre wrapper type-safe nel namespace `amx::` (es: `amx::Exec(...)`), rendendo il codice più leggibile e meno propenso a errori di cast.
   - **Esempio Interno (`amx_api.hpp`):**
      ```cpp
      // Trecho simplificado de amx_api.hpp
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
   - **Descrizione:** Un puntatore alla funzione `logprintf` di SA-MP, che è l'interfaccia standard per stampare messaggi nella console del server e nel `server_log.txt`.
   - **Meccanismo:** `Samp_SDK::Log` è un wrapper sicuro che utilizza questo puntatore, garantendo che i tuoi messaggi vengano visualizzati correttamente nell'ambiente SA-MP.

### **4.2. `platform.hpp` e `version.hpp`: Compatibilità e Metadati**

Questi header sono la base per la portabilità e l'ottimizzazione dell'SDK, adattandolo a diversi ambienti di compilazione e sfruttando funzionalità specifiche del C++ moderno.

- **Rilevamento della Piattaforma e dell'Architettura:**
   - **Meccanismo:** Utilizza macro del precompilatore (`#if defined(WIN32)`, `#if defined(__linux__)`, ecc.) per identificare il sistema operativo.
   - **Verifica dell'Architettura:** Contiene `static_assert` o `#error` per garantire che il plugin sia compilato per x86 (32-bit), un requisito critico per la compatibilità con SA-MP e il meccanismo di hooking.
   - **Gestione dell'Esportazione dei Simboli:**
      - `SAMP_SDK_EXPORT`: Una macro definita in `platform.hpp` che si espande in `extern "C"` e, su Linux, aggiunge `__attribute__((visibility("default")))`. Su Windows, garantisce solo `extern "C"` perché l'SDK utilizza `pragma comment(linker, "/EXPORT:...")` (per MSVC) o lo standard MinGW per esportare le funzioni principali.
      - Questo garantisce che le funzioni del ciclo di vita del plugin (`Supports`, `Load`, `Unload`, ecc.) siano correttamente esportate dal tuo DLL/SO, indipendentemente dall'ambiente di compilazione, **senza la necessità di file `.def` o di aggiungere `__attribute__((visibility("default")))` manualmente** nella tua implementazione.
   - **Esempio (`platform.hpp` - frammento rilevante):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // Para MSVC, a exportação é gerenciada por pragma linker commands
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // Para GCC/Clang no Linux, usamos o atributo de visibilidade
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... outras definições ...
      ```
   - **Esempio (`samp_sdk.hpp` - frammento rilevante dell'implementazione):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // No Windows (MSVC), usamos pragma comment para exportar as funções.
          // Isso elimina a necessidade de um arquivo .def.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... outras exports ...
      #endif

      // Implementação das funções exportadas
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... outras funções ...
      #endif
      ```

- **Macro di Ottimizzazione e Previsione di Branch:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Meccanismo:** `__forceinline` (MSVC) o `__attribute__((always_inline)) inline` (GCC/Clang). Suggerisce fortemente al compilatore di inserire il corpo della funzione direttamente nel punto di chiamata, eliminando l'overhead di una vera e propria chiamata di funzione.
      - **Uso:** Applicato a funzioni piccole e critiche per le prestazioni all'interno dell'SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Meccanismo:** `[[likely]]` / `[[unlikely]]` (C++20) o `__builtin_expect` (GCC/Clang). Suggerimenti al compilatore su quale percorso di un `if/else` è più probabile che venga preso.
      - **Impatto:** Aiuta il compilatore a generare codice più efficiente per la previsione dei salti (branch prediction), riducendo la latenza della CPU.
      - **Esempio (`platform.hpp`):**
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

- **Definizioni C++ Standard (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Meccanismo:** Macro definite in base al valore di `__cplusplus` e `_MSVC_LANG`.
   - **Uso:** Consentono all'SDK di utilizzare funzionalità C++ più recenti (come `std::apply` e `if constexpr` di C++17, o `std::is_same_v` di C++17) quando disponibili, mantenendo la compatibilità con standard più vecchi.
   - **Esempio (`version.hpp` - uso di `if constexpr`):**
      ```cpp
      // Trecho simplificado de public_dispatcher.hpp
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

### 4.3. `function_hook.hpp`: Il Motore di Intercettazione x86

Questo header definisce il meccanismo di basso livello per eseguire hook (intercettazioni) di funzioni, che è fondamentale per il funzionamento dell'SDK. Dipende strettamente dall'architettura x86 (32-bit).

- **`X86_Detour`**:
   - **Descrizione:** Una classe che incapsula la logica di sovrascrivere l'inizio di una funzione in memoria con un'istruzione di salto a una funzione di deviazione.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Meccanismo:** In x86, l'istruzione di salto (`JMP`) relativa ha generalmente 5 byte: `0xE9` (opcode per JMP near, relative) seguito da 4 byte che rappresentano l'offset dell'indirizzo di destinazione rispetto all'istruzione successiva.
      - **Esempio di istruzione:** `E9 XX XX XX XX` (dove `XX` sono i byte dell'offset).
   - **`Apply(void* target, void* detour)`**:
      - **Azione:** Installa l'hook. In primo luogo, memorizza i `JUMP_INSTRUCTION_SIZE` byte originali della funzione `target` (`original_bytes_`). Quindi, calcola l'indirizzo relativo del `detour` rispetto al `target` e sovrascrive l'inizio di `target` con l'istruzione `JMP`.
      - **Esempio del calcolo dell'indirizzo relativo:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Endereço do desvio - (Endereço do alvo + Tamanho da instrução de JMP)
         ```
   - **`Revert()`**:
      - **Azione:** Disinstalla l'hook, ripristinando gli `original_bytes_` nella funzione `target`.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Meccanismo:** Su Windows, usa `VirtualProtect`; su Linux, `mprotect`. Queste chiamate di sistema modificano i permessi della pagina di memoria dove risiede la funzione in `EXECUTE_READWRITE` (Windows) o `PROT_WRITE | PROT_EXEC` (Linux), consentendo la modifica del codice in fase di esecuzione.
      - **Esempio (`Unprotect_Memory`):**
         ```cpp
         // Trecho simplificado de function_hook.hpp
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
   - **Descrizione:** Un wrapper C++ `type-safe` per la `X86_Detour`, che garantisce che i tipi di puntatore di funzione siano corretti.
   - `Install(void* target, void* detour)`: Incapsula la chiamata `X86_Detour::Apply`.
   - `Uninstall()`: Incapsula la chiamata `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Meccanismo di Sicurezza (Guarda di Ricorsione):** Questa funzione è critica per evitare loop infiniti quando la deviazione deve chiamare la funzione originale. Essa **disinstalla temporaneamente l'hook (`detour_.Revert()`)**, chiama la funzione originale (`Get_Original()(args...)`), e quindi **reinstalla l'hook (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Un contatore che garantisce che l'hook venga reinstallato solo quando la chiamata originale di livello più alto è completata, consentendo chiamate ricorsive sicure della funzione originale (se la funzione originale è ricorsiva, ad esempio). Il `thread_local` garantisce che il `recursion_guard` sia isolato per ogni thread, importante in ambienti multi-threaded.
      - **Esempio (`Call_Original` com Scope_Guard):**
         ```cpp
         // Trecho simplificado de function_hook.hpp
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

Questo `singleton` è il centro nevralgico dell'interazione dell'SDK con la macchina virtuale AMX di SA-MP. Coordina l'installazione degli hook forniti da `function_hook.hpp` nelle funzioni dell'API AMX esposte dal server, reindirizzando il flusso di esecuzione alla logica dell'SDK.

- **`Activate()` / `Deactivate()`**:
   - **Descrizione:** Metodi pubblici per installare e disinstallare tutti gli hook necessari. Chiamati in `OnLoad()` e `OnUnload()` del tuo plugin, rispettivamente.
   - **Meccanismo:** Ottiene i puntatori delle funzioni AMX (come `amx_Register`, `amx_Exec`, ecc.) usando `Core::Instance().Get_AMX_Export(...)` e installa le deviazioni.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Funzione Hooked:** `amx_Register`
   - **Scopo:** Intercetta la registrazione di *tutte* le native (da SA-MP, altri plugin o gamemode).
   - **Azione:** Chiama `Interceptor_Manager::Instance().Cache_Natives()` per memorizzare i puntatori e i nomi delle native in una cache interna.
   - **Impatto:** Questa cache è fondamentale per le prestazioni di `Pawn_Native`, consentendo una ricerca estremamente rapida del puntatore della nativa anziché una ricerca costosa nell'AMX.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Funzione Hooked:** `amx_Exec`
   - **Scopo:** **Questo è l'hook più critico.** Intercetta *qualsiasi* esecuzione di codice nell'AMX, inclusa la chiamata di `publics` di Pawn.
   - **Meccanismo di Intercettazione di `Plugin_Public`:**
      1. Quando `amx_Exec` viene chiamato per una `public` (o `AMX_EXEC_MAIN`), viene eseguito `Amx_Exec_Detour`.
      2. Ottiene il nome della `public` (usando `Get_Public_Name_By_Index` o `tl_public_name`).
      3. Interroga `Public_Dispatcher::Instance().Dispatch()` per verificare se ci sono handler C++ registrati per questo nome.
      4. Se ci sono handler, li esegue. Il `Public_Dispatcher` gestisce il `marshalling` dei parametri dall'AMX ai tipi C++ corretti.
      5. In base al valore di ritorno del `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), decide se chiamare l'originale `amx_Exec` (`Get_Amx_Exec_Hook().Call_Original(...)`) o terminare l'esecuzione della `public` Pawn.
      6. **Manipolazione dello Stack:** Se l'esecuzione della `public` Pawn viene interrotta (`PLUGIN_PUBLIC_STOP`), `Amx_Exec_Detour` corregge lo stack dell'AMX (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) per evitare incongruenze.
   - **Esempio (`Amx_Exec_Detour`):**
      ```cpp
      // Trecho simplificado de interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          // ... lógica para determinar o nome da public ...
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
   - **Funzione Hooked:** `amx_FindPublic`
   - **Scopo:** Intercetta la ricerca di `publics` per nome.
   - **Meccanismo di "Ghost Publics":** Se `amx_FindPublic` originale non trova una `public` in Pawn, ma il `Public_Dispatcher` ha un handler C++ registrato per quel nome, questo hook restituisce `AMX_ERR_NONE` e un `index` speciale (`PLUGIN_EXEC_GHOST_PUBLIC`). Questo fa sì che l'API di SA-MP "pensi" che la `public` esista, permettendo che la successiva chiamata `amx_Exec` (per questo indice speciale) sia intercettata da `Amx_Exec_Detour`, che poi reindirizza all'handler C++.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Usata per passare il nome della `public` a `Amx_Exec_Detour` quando viene rilevato un "ghost public", poiché `amx_Exec` riceve solo l'indice, non il nome.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Funzioni Hooked:** `amx_Init` / `amx_Cleanup`
   - **Scopo:** Gestire la lista delle istanze `AMX*` attive.
   - **Azione:** `Amx_Init_Detour` chiama `Amx_Manager::Instance().Add_Amx()`, e `Amx_Cleanup_Detour` chiama `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Gestione delle Istanze `AMX*`

Questo `singleton` mantiene un registro dinamico di tutte le macchine virtuali AMX attualmente caricate sul server. È essenziale per le funzioni che devono interagire con "tutti gli script" o trovare uno script specifico.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Descrizione:** Una lista di puntatori a tutte le istanze `AMX*` che sono state inizializzate (gamemode e filterscripts).
   - **Gestione:** Popolata dagli hook `Amx_Init_Detour` e svuotata da `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Scopo:** Protegge `loaded_amx_` contro l'accesso concorrente in ambienti multi-threaded (anche se SA-MP è prevalentemente single-thread, questa è una buona pratica di sicurezza). `std::shared_mutex` consente più lettori simultaneamente, ma un solo scrittore.
- **`std::atomic<uint32_t> generation_`**:
   - **Scopo:** Un contatore che incrementa ogni volta che un AMX viene aggiunto o rimosso.
   - **Uso:** Viene utilizzato da `Caller_Cache` in `callbacks.hpp` per rilevare quando la lista di AMX è cambiata, invalidando le cache di ricerca di `publics` e garantendo che le chiamate `Pawn_Public` operino sempre con informazioni aggiornate. Questo ottimizza le prestazioni evitando ricerche ripetitive in uno stato che non è cambiato.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Descrizione:** Scorre `loaded_amx_` (dal più recente al più vecchio, il che di solito mette per primo il gamemode o il filterscript più rilevante) per trovare la `public` con il nome specificato.
   - **Meccanismo:** Usa `amx::Find_Public` per ogni istanza `AMX*`.
   - **Impatto:** È la base per `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: Il Router di Callbacks `Plugin_Public`

Questo `singleton` è il componente che mappa i nomi delle `publics` di Pawn alle tue funzioni C++ `Plugin_Public`.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Chiave:** L'hash FNV1a del nome della `public` (es: `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Valore:** Un `std::vector` di `std::function<cell(AMX*)>`, dove ogni `std::function` è un handler C++ registrato per quella `public`.
   - **Meccanismo:** La `std::vector` consente di registrare più `Plugin_Public`s per lo stesso callback (es: più plugin che vogliono intercettare `OnPlayerCommandText`). Gli handler vengono eseguiti in ordine inverso di registrazione.
- **`Public_Registrar`**:
   - **Meccanismo:** Questa è una classe template la cui macro `PLUGIN_PUBLIC_REGISTRATION` crea un'istanza statica globale. Nel costruttore statico (`static bool registered = [...]`), essa registra il suo handler `Plugin_Public` nel `Public_Dispatcher`. Questo è un modello di "registrazione statica in fase di compilazione/inizializzazione".
   - **Esempio (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Registrar<decltype(&name), &name, hash_##name> registrar_##name;
      ```

- **`Public_Traits` e `Wrapper()`**:
   - **Meccanismo:** `Public_Traits` è un template di trait che, usando la metaprogrammazione, genera una funzione `static cell Wrapper(AMX* amx)`.
   - **Scopo:** Questa `Wrapper` è la `Amx_Handler_Func` che il `Public_Dispatcher` effettivamente memorizza e chiama. È responsabile di:
      1. Chiamare `Public_Param_Reader::Get_Public_Params(amx, args...)` per estrarre i parametri dallo stack dell'AMX.
      2. Chiamare la tua vera funzione `Plugin_Public` C++ (`func_ptr`) con i parametri già convertiti nei tipi C++ corretti.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Descrizione:** Un insieme di funzioni template ricorsive che leggono i valori dallo stack dell'AMX e li convertono ai tipi C++ specificati nella dichiarazione di `Plugin_Public`.
   - **Meccanismo:** Usa `Get_Stack_Cell()` per accedere alle `cell` nello stack. Utilizza `if constexpr` (C++17+) o `std::is_same<T>::value` (C++14) per applicare la conversione corretta (`amx::AMX_CTOF` per float, `Samp_SDK::Get_String` per stringa, cast diretto per int).

### 4.7. `native.hpp`: Gestione e Chiamata di Native del Plugin

Questo header è dedicato alla creazione e alla gestione di native C++ che il tuo plugin espone a Pawn.

- **`Native_List_Holder`**:
   - **Descrizione:** Un `singleton` globale che memorizza tutte le `Plugin_Native`s dichiarate nel tuo plugin (da tutti i file `.cpp` che usano `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Contiene oggetti `Native` (che memorizzano il nome della nativa e il puntatore alla funzione C++ `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Una mappa ottimizzata per hash per ricerche rapide di `Plugin_Native`s interne (usato da `Plugin_Call`).
- **`Native_Registrar`**:
   - **Meccanismo:** Proprio come il `Public_Registrar`, questa è una classe template la cui macro `Plugin_Native` crea un'istanza statica globale. Nel suo costruttore, aggiunge la nativa al `Native_List_Holder`.
   - **Impatto:** Ti permette di dichiarare `Plugin_Native`s in più file `.cpp` senza preoccuparti della registrazione manuale. Tutte verranno raccolte automaticamente.
- **`Native_Registry`**:
   - **Descrizione:** Una classe ausiliaria che, in `OnAmxLoad`, prende l'elenco completo di `Native`s dal `Native_List_Holder` e le formatta in un array `AMX_NATIVE_INFO`.
   - **Meccanismo:** Chiama `amx::Register(amx, amx_natives_info_.data(), -1)` per registrare tutte le tue native nell'istanza AMX che è stata appena caricata.
- **`Plugin_Call_Impl(...)`**:
   - **Descrizione:** L'implementazione sottostante della macro `Plugin_Call`.
   - **Meccanismo:** Utilizza `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` per ottenere direttamente il puntatore della funzione C++.
   - **Ambiente:** Esegue la nativa in un ambiente `Amx_Sandbox` (isolato) per gestire lo stack e l'heap temporanei, in modo simile a come funziona `Pawn_Native`.

### 4.8. `callbacks.hpp` & `amx_memory.hpp`: Chiamate C++ -> Pawn e RAII

Questi header formano la spina dorsale per chiamare funzioni Pawn da C++ (`Pawn_*` macros) e garantiscono la sicurezza della memoria.

- **`Amx_Sandbox`**:
   - **Descrizione:** Una struttura `thread_local` che simula un ambiente `AMX` minimalista e isolato per chiamate `Pawn_Native` e `Plugin_Call`.
   - **Meccanismo:** Ha la propria struct `AMX`, `AMX_HEADER` e un `std::vector<unsigned char> heap` per simulare la memoria di uno script. Ciò consente di chiamare `amx::Push`, `amx::Allot`, ecc., senza interferire con lo stato degli script Pawn reali in esecuzione.
   - **`thread_local`:** Garantisce che ogni thread abbia la propria `Amx_Sandbox`, prevenendo condizioni di gara se l'SDK viene utilizzato in un contesto multi-threaded (es: un futuro pool di thread per operazioni non-Pawn).
   - **Esempio (`Amx_Sandbox`):**
      ```cpp
      // Trecho simplificado de callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Memória simulada para stack/heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Inicializa a AMX e a header
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
   - **Descrizione:** Un insieme di funzioni template sovraccaricate che gestisce il `marshalling` di *ogni* parametro C++ al formato `cell` previsto dall'AMX, e viceversa per i parametri di output.
   - **Elaborazione dell'Input:**
       - Per `int`, `float`, `bool`: Converte direttamente in `cell`.
       - Per `const char*`, `std::string`: Alloca memoria nell'heap della `Amx_Sandbox` (o AMX reale per `Pawn_Public`), copia la stringa e spinge l'indirizzo AMX nello stack.
   - **Elaborazione dell'Output (`is_output_arg`):**
       - **Meccanismo:** Quando un argomento è un riferimento lvalue non-const (rilevato dal trait `is_output_arg`), il `Parameter_Processor` non spinge il valore, ma un *indirizzo AMX* per una `cell` allocata temporaneamente nell'heap.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Dopo la chiamata della nativa Pawn, viene eseguita una lista di lambda (`post_call_updaters`). Ogni lambda è responsabile di leggere il valore finale della `cell` allocata nell'AMX e riassegnarlo alla variabile C++ originale (es: `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Meccanismo:** Un `std::integral_constant` (trait di tipo) che, in fase di compilazione, valuta se un tipo di parametro C++ è un riferimento modificabile (es: `int&`, `float&`, `std::string&`). Ciò consente al `Parameter_Processor` di distinguere i parametri di input da quelli di output.
   - **Esempio (`is_output_arg`):**
      ```cpp
      // Trecho simplificado de callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Descrizione:** Una classe RAII (`Resource Acquisition Is Initialization`) che incapsula l'allocazione e la deallocazione della memoria nell'AMX.
   - **Meccanismo:** Nel costruttore, chiama `amx::Allot` per ottenere un `amx_addr` e un `phys_addr`. Nel distruttore, chiama `amx::Release` per liberare questa memoria.
   - **Impatto:** **Cruciale per prevenire perdite di memoria nell'heap dell'AMX.** Garantisce che la memoria temporanea utilizzata per stringhe o parametri di output sia sempre liberata, anche se si verificano eccezioni o ritorni anticipati.

### 4.9. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Accesso Astratto all'AMX

Questi header forniscono le definizioni fondamentali e gli strumenti di alto livello per interagire con Pawn.

- **`amx_defs.h`**:
   - **Contenuto:** Contiene le definizioni raw delle strutture AMX (`AMX`, `AMX_HEADER`), tipi (`cell`, `ucell`) ed enum di errore (`AmxError`). Definisce anche `AMX_NATIVE` e `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Utilizza attributi di impacchettamento (`#pragma pack(push, 1)` / `__attribute__((packed))`) per garantire che le strutture AMX abbiano il layout di memoria corretto, fondamentale per l'interoperabilità.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Descrizione:** La funzione template principale per invocare le funzioni dell'API AMX esposte dal server.
   - **Meccanismo:** Ottiene il puntatore della funzione tramite `Core::Instance().Get_AMX_Export(Index)` e lo chiama. Centralizza la gestione degli errori se il puntatore della funzione non è disponibile.
   - **Impatto:** Converte chiamate di basso livello (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) in chiamate C++ idiomatiche e type-safe (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Descrizione:** Funzioni essenziali per convertire valori `cell` in `float` e viceversa, eseguendo una reinterpretazione bitwise della memoria.
   - **`static_assert`:** Includono `static_assert` per garantire che `sizeof(cell) == sizeof(float)` in fase di compilazione, prevenendo errori su piattaforme con dimensioni di tipo diverse.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Descrizione:** Helper per convertire un indirizzo AMX di stringa in `std::string`.
   - **Meccanismo:** In primo luogo, ottiene l'indirizzo fisico (`cell* phys_addr`) della stringa nell'AMX usando `amx::Get_Addr`. Quindi, usa `amx::STR_Len` per determinare la lunghezza e `amx::Get_String` per copiare i byte in una `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Descrizione:** La funzione base di formattazione delle stringhe (`printf`-like) per l'SDK.
   - **Meccanismo:** Utilizza `vsnprintf` in due passaggi: prima per determinare la dimensione necessaria della stringa, e poi per formattare la stringa nella `std::string` allocata dinamicamente. Questo evita gli overflow del buffer.

## 5. Compilazione e Deploy

### Requisiti di Architettura e Piattaforma

- Il tuo plugin **DEVE** essere compilato per l'architettura **x86 (32-bit)**. Il meccanismo di hooking dell'SDK è specifico per questa architettura.
- Piattaforme Supportate: Windows (.dll) e Linux (.so).

### Esempi di Comandi di Compilazione

#### **MSVC (Visual Studio)**

1. Crea un nuovo progetto di "Dynamic-Link Library (DLL)".
2. Nelle impostazioni del progetto, imposta la "Piattaforma Soluzione" su **x86**.
3. Assicurati che lo standard del linguaggio C++ sia almeno C++14.

#### **GCC / Clang (Linux)**

```bash
# Para um plugin chamado 'my_plugin.so' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compila per 32-bit.
- `-shared`: Crea una libreria condivisa (`.so`).
- `-std=c++17`: Definisce lo standard C++ su C++17 (può essere `c++14` o `c++20`).
- `-O2`: Livello di ottimizzazione 2.
- `-fPIC`: Genera codice indipendente dalla posizione, necessario per le librerie condivise.
- `-Wall -Wextra`: Attiva avvisi aggiuntivi per aiutare a individuare errori.
- `-Wl,--no-undefined`: Impedisce la creazione della libreria se ci sono simboli indefiniti.

#### **GCC / Clang (MinGW su Windows)**

```bash
# Para um plugin chamado 'my_plugin.dll' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Collega la libreria standard C++ staticamente. Essenziale per evitare che il tuo plugin dipenda da DLL di runtime specifiche del compilatore che potrebbero non essere presenti sul sistema dell'utente.
- `-static-libgcc`: Collega la libreria GCC staticamente.

### Considerazioni per la Distribuzione

- **Nome del File:** Il tuo plugin deve avere l'estensione `.dll` (Windows) o `.so` (Linux). Es: `my_plugin.dll`.
- **Posizione:** Inserisci il file compilato nella cartella `plugins/` del tuo server SA-MP.
- **server.cfg:** Aggiungi il nome del tuo plugin (se Windows, senza estensione) alla riga `plugins` in `server.cfg`.
   ```
   plugins my_plugin (se for Linux, my_plugin.so)
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