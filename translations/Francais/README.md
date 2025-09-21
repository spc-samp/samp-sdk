# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Un SDK C++ moderne, header-only et de haut niveau pour le développement de plugins et de modules pour SA-MP.**

</div>

## Langues

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Table des matières

- [SA-MP SDK](#sa-mp-sdk)
  - [Langues](#langues)
  - [Table des matières](#table-des-matières)
  - [1. Introduction et philosophie de conception](#1-introduction-et-philosophie-de-conception)
    - [Le problème avec l'API C standard de SA-MP](#le-problème-avec-lapi-c-standard-de-sa-mp)
    - [La solution SA-MP SDK : Abstraction avec sécurité et performance](#la-solution-sa-mp-sdk--abstraction-avec-sécurité-et-performance)
    - [Modèle Header-Only : Avantages et implications](#modèle-header-only--avantages-et-implications)
  - [2. Configuration et environnement](#2-configuration-et-environnement)
    - [Exigences de compilation](#exigences-de-compilation)
    - [Structure de fichiers recommandée](#structure-de-fichiers-recommandée)
    - [Macros de configuration essentielles](#macros-de-configuration-essentielles)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Définitions et constantes de SA-MP (`samp_defs.hpp`)](#définitions-et-constantes-de-sa-mp-samp_defshpp)
  - [3. Guide d'utilisation complet de l'API](#3-guide-dutilisation-complet-de-lapi)
    - [3.1. Le cycle de vie du plugin](#31-le-cycle-de-vie-du-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Interception des événements Pawn](#32-plugin_public-interception-des-événements-pawn)
      - [Syntaxe et déclaration](#syntaxe-et-déclaration)
      - [Marshalling automatique des paramètres](#marshalling-automatique-des-paramètres)
      - [Contrôle de flux : `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#contrôle-de-flux--plugin_public_continue-vs-plugin_public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.3. `Plugin_Native`: Création de fonctions natives en C++](#33-plugin_native-création-de-fonctions-natives-en-c)
      - [Syntaxe et signature fixe](#syntaxe-et-signature-fixe)
      - [Enregistrement automatique des natives](#enregistrement-automatique-des-natives)
      - [Extraction des paramètres : `Register_Parameters` vs. `Native_Params`](#extraction-des-paramètres--register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (API complète : `Get`, `Get_REF`, `Set_REF`)](#native_params-api-complète--get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Retour de valeurs](#retour-de-valeurs)
    - [3.4. `Plugin_Native_Hook`: Interception des natives SA-MP existantes](#34-plugin_native_hook-interception-des-natives-sa-mp-existantes)
      - [Syntaxe et signature fixe](#syntaxe-et-signature-fixe-1)
      - [Enregistrement et activation du hook](#enregistrement-et-activation-du-hook)
      - [Appel de la native originale (chaîne de hooks) : `Call_Original_Native`](#appel-de-la-native-originale-chaîne-de-hooks--call_original_native)
      - [Exemple complet de `Plugin_Native_Hook`](#exemple-complet-de-plugin_native_hook)
    - [3.5. Macros `Pawn_*`: Appel de fonctions Pawn depuis le C++](#35-macros-pawn_-appel-de-fonctions-pawn-depuis-le-c)
      - [`Pawn_Native(NomDeLaNative, ...)`](#pawn_nativenomdelanative-)
      - [`Pawn_Public(NomDeLaPublic, ...)`](#pawn_publicnomdelapublic-)
      - [`Pawn(NomDeLaFonction, ...)`](#pawnnomdelafonction-)
      - [Syntaxe et conventions](#syntaxe-et-conventions)
      - [Marshalling des paramètres d'entrée](#marshalling-des-paramètres-dentrée)
      - [Marshalling des paramètres de sortie (références : `int&`, `float&`, `std::string&`)](#marshalling-des-paramètres-de-sortie-références--int-float-stdstring)
      - [L'objet `Callback_Result`: Analyse complète](#lobjet-callback_result-analyse-complète)
    - [3.6. `Plugin_Module`: Gestion des modules dynamiques](#36-plugin_module-gestion-des-modules-dynamiques)
      - [Syntaxe et objectif](#syntaxe-et-objectif)
      - [Cycle de vie d'un module](#cycle-de-vie-dun-module)
      - [Avantages de la modularisation](#avantages-de-la-modularisation)
    - [3.7. `Plugin_Call`: Appel des natives internes du plugin](#37-plugin_call-appel-des-natives-internes-du-plugin)
      - [Syntaxe et avantages en termes de performances](#syntaxe-et-avantages-en-termes-de-performances)
    - [3.8. Fonctions utilitaires du SDK](#38-fonctions-utilitaires-du-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (recommandé)](#stdstring-plugin_formatconst-char-format--recommandé)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (détail d'implémentation)](#stdstring-samp_sdkformatconst-char-format--détail-dimplémentation)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Anatomie interne et architecture du SDK](#4-anatomie-interne-et-architecture-du-sdk)
    - [4.1. `core.hpp`: La fondation minimaliste](#41-corehpp-la-fondation-minimaliste)
    - [4.2. `platform.hpp` et `version.hpp`: Compatibilité et métadonnées](#42-platformhpp-et-versionhpp-compatibilité-et-métadonnées)
    - [4.3. `function_hook.hpp`: Le moteur d'interception x86](#43-function_hookhpp-le-moteur-dinterception-x86)
    - [4.4. `interceptor_manager.hpp`: Le contrôleur de hooks de l'AMX](#44-interceptor_managerhpp-le-contrôleur-de-hooks-de-lamx)
    - [4.5. `amx_manager.hpp`: Gestion des instances `AMX*`](#45-amx_managerhpp-gestion-des-instances-amx)
    - [4.6. `public_dispatcher.hpp`: Le routeur de callbacks `Plugin_Public`](#46-public_dispatcherhpp-le-routeur-de-callbacks-plugin_public)
    - [4.7. `native.hpp`: Gestion et appel des natives du plugin](#47-nativehpp-gestion-et-appel-des-natives-du-plugin)
    - [4.8. `native_hook_manager.hpp`: Le Moteur de Hooks de Natives](#48-native_hook_managerhpp-le-moteur-de-hooks-de-natives)
    - [4.9. `callbacks.hpp` \& `amx_memory.hpp`: Appels C++ -\> Pawn et RAII](#49-callbackshpp--amx_memoryhpp-appels-c---pawn-et-raii)
    - [4.10. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Accès abstrait à l'AMX](#410-amx_apihpp--amx_helpershpp--amx_defsh-accès-abstrait-à-lamx)
  - [5. Compilation et déploiement](#5-compilation-et-déploiement)
    - [Exigences d'architecture et de plateforme](#exigences-darchitecture-et-de-plateforme)
    - [Exemples de commandes de compilation](#exemples-de-commandes-de-compilation)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW sur Windows)**](#gcc--clang-mingw-sur-windows)
    - [Considérations pour la distribution](#considérations-pour-la-distribution)
  - [Licence](#licence)
    - [Conditions Générales d'Utilisation](#conditions-générales-dutilisation)
      - [1. Autorisations Accordées](#1-autorisations-accordées)
      - [2. Conditions Obligatoires](#2-conditions-obligatoires)
      - [3. Droits d'Auteur](#3-droits-dauteur)
      - [4. Exclusion de Garantie et Limitation de Responsabilité](#4-exclusion-de-garantie-et-limitation-de-responsabilité)

## 1. Introduction et philosophie de conception

### Le problème avec l'API C standard de SA-MP

L'API de plugins de SA-MP est une interface de programmation en C. Bien que fonctionnelle et fondamentale, elle présente les défis inhérents à la programmation de bas niveau :
- **Gestion manuelle de la mémoire :** Des fonctions comme `amx_Allot` et `amx_Release` exigent que le développeur alloue et désalloue explicitement la mémoire dans le tas de l'AMX. C'est une source courante de fuites de mémoire et de pannes d'exécution.
- **Typage faible et conversions manuelles :** Les paramètres sont passés sous forme de tableau de `cell`s, ce qui force des conversions explicites (et souvent dangereuses) entre `cell`, `int`, `float`, et `char*`.
- **Verbosité et boilerplate :** Extraire plusieurs paramètres d'un tableau `cell* params`, gérer les tailles de chaînes et gérer la pile de l'AMX pour les rappels C++ vers Pawn exige un code répétitif.
- **Fragilité de l'interface :** Le manque de vérification au moment de la compilation (type safety) signifie que les erreurs de passage de paramètres ou de types peuvent passer inaperçues jusqu'à l'exécution, provoquant des plantages ou des comportements indéfinis.

### La solution SA-MP SDK : Abstraction avec sécurité et performance

Le SA-MP SDK aborde ces problèmes en fournissant une puissante couche d'abstraction en C++ :
- **RAII (Resource Acquisition Is Initialization) :** Gestion automatique de la mémoire dans l'AMX. `Amx_Scoped_Memory` garantit que la mémoire allouée est libérée.
- **Sécurité des types :** Conversion automatique et sécurisée des paramètres entre C++ et Pawn. Vous traitez directement avec `int`, `float`, `std::string`.
- **Syntaxe concise et idiomatique :** Les macros et les modèles fournissent une API propre qui ressemble davantage au C++ moderne qu'à l'API C traditionnelle.
- **Interception robuste :** Un moteur de hooking avancé permet l'interception transparente des callbacks Pawn (`Plugin_Public`), la création de nouvelles natives (`Plugin_Native`), et **le hooking et l'enchaînement des fonctions natives SA-MP existantes (`Plugin_Native_Hook`)**.
- **Haute performance :** Utilisation intensive du hachage au moment de la compilation (FNV1a), de la mise en cache des fonctions et des optimisations `thread_local` pour minimiser la surcharge des abstractions.

### Modèle Header-Only : Avantages et implications

Le SDK est composé exclusivement de fichiers d'en-tête (`.hpp`, `.h`).
- **Avantages :**
   - **Intégration simplifiée :** Il n'y a pas de bibliothèques à construire, lier ou distribuer. Il suffit d'inclure les en-têtes.
   - **Optimisations du compilateur :** Le compilateur a une visibilité complète du code du SDK et de votre plugin, ce qui permet un inlining agressif et des optimisations au moment de l'édition des liens, ce qui peut se traduire par des binaires plus rapides.
- **Implications :**
   - **Temps de compilation :** Pour les très grands projets, la compilation peut prendre plus de temps en raison de l'inclusion répétée du code du SDK. Cela est atténué par les gardes d'inclusion et la nature "n'inclure que ce qui est nécessaire" du C++.
   - **Macros d'implémentation :** La nécessité de la macro `SAMP_SDK_IMPLEMENTATION` est une conséquence du modèle header-only pour éviter les redéfinitions de symboles.

## 2. Configuration et environnement

### Exigences de compilation

- **Compilateur C++ :** Compatible avec C++14 ou supérieur (le SDK utilise des fonctionnalités C++14, C++17 et C++20 pour des optimisations spécifiques, mais C++14 est le minimum).
   - GCC (version 7+)
   - Clang (version 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Architecture :** **x86 (32-bit)**. SA-MP fonctionne exclusivement sur cette architecture. Le SDK inclut des vérifications dans `platform.hpp` qui émettront des erreurs de compilation si une architecture incorrecte est détectée.
- **Système d'exploitation :** Windows ou Linux.

### Structure de fichiers recommandée

Pour plus de clarté et d'organisation, il est courant d'organiser le SDK dans un sous-dossier `samp-sdk`.

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

### Macros de configuration essentielles

Définissez toujours ces macros *avant* d'inclure `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Objectif :** Indique au compilateur que ce fichier `.cpp` doit générer les implémentations des fonctions d'exportation du plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **Le SDK gère automatiquement l'exportation de ces fonctions, éliminant le besoin de fichiers `.def` (sous Windows) ou de déclarations `__attribute__((visibility("default")))` (sous Linux) pour ces fonctions.**
- **Impact technique :** Sans cette macro, l'éditeur de liens ne trouvera pas les exportations nécessaires, et le serveur SA-MP ne pourra pas charger votre plugin.
- **Règle fondamentale :** **Définissez cette macro dans UN SEUL fichier `.cpp` de tout votre projet.** La définir dans plus d'un fichier provoquera une erreur de liaison de "symbole dupliqué".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // The macro makes the SDK export the necessary functions automatically.
#include "samp-sdk/samp_sdk.hpp"

// ... your plugin code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Objectif :** Active les callbacks de cycle de vie du script Pawn (`OnAmxLoad`, `OnAmxUnload`) et la fonctionnalité de création de nouvelles natives en C++ (`Plugin_Native`).
- **Fonctionnalités activées :**
   - Callbacks `OnAmxLoad(AMX* amx)` et `OnAmxUnload(AMX* amx)`.
   - Déclaration et enregistrement de nouvelles natives C++ utilisant `Plugin_Native`.
   - La macro `Plugin_Call` pour invoquer des natives créées avec `Plugin_Native` au sein de votre propre plugin.
- **Impact technique :** Lorsque cette macro est définie, le SDK collecte automatiquement toutes vos `Plugin_Native`s. Dans la fonction `Supports()`, le drapeau `SUPPORTS_AMX_NATIVES` est automatiquement ajouté s'il y a des `Plugin_Native`s dans votre projet.
- **Flexibilité :** **Vous pouvez définir cette macro dans plusieurs fichiers `.cpp`**. Le système d'enregistrement statique du SDK consolidera toutes les natives de différentes unités de compilation en une seule liste globale.

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

- **Objectif :** Active le callback `OnProcessTick()`, qui est invoqué régulièrement par le serveur.
- **Impact technique :** Ajoute automatiquement le drapeau `SUPPORTS_PROCESS_TICK` dans la fonction `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logic executed at each server "tick" (e.g. 20ms)
    // Be careful with heavy operations here!
}
```

### Définitions et constantes de SA-MP (`samp_defs.hpp`)

Ce fichier fournit toutes les constantes et limites connues de SA-MP, telles que `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. Il est automatiquement inclus par `samp_sdk.hpp` et doit être utilisé pour garantir la compatibilité et la lisibilité du code.

## 3. Guide d'utilisation complet de l'API

### 3.1. Le cycle de vie du plugin

Les fonctions suivantes sont les points d'entrée et de sortie de votre plugin, exportées automatiquement par le SDK.

#### `bool OnLoad()`

- **Description :** Première fonction appelée par le serveur SA-MP après le chargement réussi de votre plugin en mémoire.
- **Utilisation :** Idéal pour initialiser tout système, charger des configurations, ouvrir des connexions à des bases de données ou charger des modules (`Plugin_Module`).
- **Retour :**
   - `true` : Le plugin a été initialisé avec succès et le chargement se poursuit.
   - `false` : Le plugin a échoué à s'initialiser. Le chargement sera annulé et le plugin sera déchargé.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Example: Load a module (more details in section 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load database module!");

        return false; // Aborts loading of the main plugin
    }

    return true;
}
```

#### `void OnUnload()`

- **Description :** Dernière fonction appelée par le serveur SA-MP avant de décharger votre plugin de la mémoire.
- **Utilisation :** Idéal pour nettoyer les ressources, fermer les connexions, sauvegarder les états et s'assurer qu'aucune ressource n'est fuite. Le SDK gère automatiquement le déchargement des modules (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // No manual action is needed for modules loaded via Plugin_Module;
    // the SDK takes care of it.
}
```

#### `unsigned int GetSupportFlags()`

- **Description :** Informe le serveur SA-MP des fonctionnalités que votre plugin prend en charge et souhaite utiliser.
- **Utilisation :** **Retournez toujours `SUPPORTS_VERSION` (ou `SAMP_PLUGIN_VERSION`).** Les flags `SUPPORTS_AMX_NATIVES` et `SUPPORTS_PROCESS_TICK` sont automatiquement ajoutés par le SDK s'il y a des `Plugin_Native`s, et/ou si la macro `SAMP_SDK_WANT_PROCESS_TICK` est définie, respectivement. Cela simplifie la maintenance et évite les erreurs.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // The SDK adds the necessary flags automatically.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requis :** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description :** Appelée chaque fois qu'un nouveau script Pawn (un Gamemode ou Filterscript) est chargé et initialisé sur le serveur.
- **Utilisation :** Si vous avez besoin d'une logique spécifique pour chaque script AMX, ou d'initialiser des données spécifiques par script.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxLoad(AMX* amx) {
    // amx represents the new loaded script instance.
    Samp_SDK::Log("AMX script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Requis :** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description :** Appelée lorsqu'un script Pawn est déchargé du serveur.
- **Utilisation :** Pour nettoyer les ressources spécifiques que vous avez allouées ou associées à cet `AMX*` particulier.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requis :** `SAMP_SDK_WANT_PROCESS_TICK`
- **Description :** Appelée de manière répétée à chaque "tick" du serveur (généralement 20 fois par seconde, soit toutes les 50ms).
- **Utilisation :** Pour la logique de fond continue, les minuteries, les mises à jour d'état qui ne dépendent pas des événements du joueur, ou la synchronisation des données.
- **Attention :** Évitez les opérations bloquantes ou gourmandes en calcul ici, car elles peuvent provoquer des latences sur le serveur.

```cpp
// main.cpp (with SAMP_SDK_WANT_PROCESS_TICK defined)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Every 10 seconds (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Interception des événements Pawn

La macro `Plugin_Public` est le pont principal pour recevoir les rappels Pawn dans votre code C++.

#### Syntaxe et déclaration

- `Plugin_Public(NomDeLaPublic, Type1 Param1, Type2 Param2, ...)`
- Le nom de la fonction C++ que vous déclarez **doit être le même** que le callback Pawn (ex : `OnPlayerConnect`).
- Les types de paramètres C++ (`int`, `float`, `std::string`) sont automatiquement convertis par le SDK.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Player %d said: %s", playerid, text.c_str());

    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Marshalling automatique des paramètres

Le SDK gère automatiquement la lecture de la `cell stack` de l'AMX et la conversion vers les types C++ spécifiés :
- `int` : Converti directement de `cell`.
- `float` : Converti de `cell` en utilisant `amx::AMX_CTOF`.
- `std::string` : Le SDK lit l'adresse de la chaîne dans l'AMX, alloue un `std::string` en C++ et copie le contenu.

#### Contrôle de flux : `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

La valeur retournée par votre fonction `Plugin_Public` est cruciale et détermine le flux d'exécution du callback :
- `return PLUGIN_PUBLIC_CONTINUE;` (valeur `1`) : Indique que l'exécution du callback doit **continuer**. S'il y a d'autres plugins qui interceptent également ce callback, ils seront appelés (dans l'ordre inverse de chargement). Ensuite, la `public` originale dans le script Pawn sera invoquée.
- `return PLUGIN_PUBLIC_STOP;` (valeur `0`) : Indique que l'exécution du callback doit être **interrompue**. Aucun autre plugin (avec une priorité inférieure) ou la `public` originale dans le script Pawn ne sera invoqué pour cet événement. C'est idéal pour implémenter un système qui "remplace" ou "bloque" un comportement par défaut de SA-MP.

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

Une caractéristique avancée de `Plugin_Public` est le support des "Ghost Callbacks". Cela signifie que vous pouvez intercepter un callback Pawn même s'il **n'est pas présent** dans le script `.amx` du gamemode ou du filterscript. Le SDK "trompe" le serveur pour qu'il appelle votre hook C++ de toute façon. C'est utile pour les callbacks internes ou pour créer de nouvelles fonctionnalités sans dépendre de la présence d'une `public` dans le script Pawn.

```cpp
// You can define a callback that the Pawn script does not have, but your plugin will hear it.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Custom internal event received: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// To "fire" this event from another point in your C++ code:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// The call will go to your Plugin_Public above, even if there is no OnMyCustomInternalEvent in Pawn.
```

### 3.3. `Plugin_Native`: Création de fonctions natives en C++

`Plugin_Native` vous permet d'étendre la fonctionnalité de Pawn avec du code C++ haute performance.

#### Syntaxe et signature fixe

- `Plugin_Native(NomeDaNativa, AMX* amx, cell* params)`
- La fonction C++ doit avoir exactement cette signature : `cell NomeDaNativa(AMX* amx, cell* params)`.
- `NomeDaNativa` est le nom que les scripts Pawn utiliseront.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementation ...
    return 0;
}
```

#### Enregistrement automatique des natives

> [!NOTE]
> Vous **n'avez pas besoin** d'appeler `amx_Register` manuellement. Le SDK détecte toutes vos `Plugin_Native`s (dans n'importe quel fichier `.cpp` qui a inclus `samp_sdk.hpp` et défini `SAMP_SDK_WANT_AMX_EVENTS`) et les enregistre automatiquement dans chaque script AMX chargé (`OnAmxLoad`).

#### Extraction des paramètres : `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Description :** Aide plus simple pour extraire plusieurs paramètres séquentiellement.
- **Utilisation :** `Register_Parameters(variable1, variable2, ...)`
- **Limitations :** Pour les paramètres d'entrée. Ne gère pas les paramètres facultatifs ou l'accès par index.
- **Types pris en charge :** `int`, `float`, `std::string`.

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

##### `Native_Params` (API complète : `Get`, `Get_REF`, `Set_REF`)

- **Description :** Une classe wrapper qui fournit une interface orientée objet pour accéder aux paramètres d'une native. Plus puissante pour les scénarios complexes.
- **Construction :** `Native_Params p(amx, params);`

###### `p.Count()`

- **Description :** Retourne le nombre de paramètres passés à la native.
- **Utilisation :** Essentiel pour gérer les paramètres facultatifs.

###### `p.Get<T>(size_t index)`

- **Description :** Extrait un paramètre d'entrée par index et le convertit au type `T`.
- **Types pris en charge :** `int`, `float`, `std::string`.

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

- **Description :** Obtient la valeur d'un paramètre de **référence** (pointeur Pawn) et la stocke dans `out_value`.
- **Utilisation :** Pour lire des valeurs qui ont été passées par référence depuis Pawn.
- **Retour :** `true` si l'adresse AMX est valide, `false` sinon.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Gets the values from the references (Pawn passed addresses)
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

- **Description :** Retourne un `std::optional<T>` pour lire un paramètre de référence. Plus sûr pour C++17 et supérieur.

###### `p.Set_REF<T>(size_t index, T value)`

- **Description :** Écrit une valeur `T` dans un paramètre de **référence** Pawn (l'adresse que Pawn a passée).
- **Utilisation :** Pour modifier des valeurs qui ont été passées par référence, faisant en sorte que Pawn voit la modification.
- **Retour :** `true` si l'écriture a réussi, `false` sinon.

#### Retour de valeurs

- Votre fonction `Plugin_Native` doit retourner un `cell`.
- Pour retourner un `int` ou `bool`, utilisez un cast vers `cell`.
- Pour retourner un `float`, utilisez `amx::AMX_FTOC(mon_float)`.

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

### 3.4. `Plugin_Native_Hook`: Interception des natives SA-MP existantes

La macro `Plugin_Native_Hook` vous permet d'intercepter et de modifier le comportement de toute fonction native SA-MP existante ou d'autres plugins. C'est un mécanisme puissant pour étendre ou modifier la logique standard du serveur.

#### Syntaxe et signature fixe

- `Plugin_Native_Hook(NomDeLaNative, AMX* amx, cell* params)`
- La fonction C++ doit avoir exactement cette signature : `cell NomDeLaNative(AMX* amx, cell* params)`.
- `NomDeLaNative` doit être le nom exact de la native que vous souhaitez hooker (ex : `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepts the SendClientMessage native
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Important to call the original
}
```

#### Enregistrement et activation du hook

> [!NOTE]
> Vous **n'avez pas besoin** d'appeler `amx_Register` manuellement ou de définir `SAMP_SDK_WANT_AMX_EVENTS` spécifiquement pour `Plugin_Native_Hook`. Le SDK détecte et enregistre automatiquement vos hooks. Lors de la première exécution d'un script AMX, le SDK remplace le pointeur de la native dans la table par un "trampoline" qui redirige vers votre fonction `Plugin_Native_Hook`. Ce processus garantit l'enchaînement sécurisé des hooks de plusieurs plugins.

#### Appel de la native originale (chaîne de hooks) : `Call_Original_Native`

Dans votre fonction `Plugin_Native_Hook`, vous **DEVEZ** utiliser la macro `Call_Original_Native(NomDeLaNative)` pour invoquer la fonction originale (ou le hook suivant dans la chaîne). C'est vital pour :
- **Préserver la fonctionnalité :** Si vous n'appelez pas l'original, la native hookée cessera simplement de fonctionner pour les autres plugins ou pour le serveur.
- **Enchaînement des hooks :** Permet à plusieurs plugins de hooker la même native et à tous les hooks d'être exécutés séquentiellement.
- **Manipulation du retour :** Vous pouvez inspecter et même modifier la valeur de retour de `Call_Original_Native` avant de la retourner depuis votre fonction de hook.

```cpp
// Example: Blocking SendClientMessage if it contains a specific word
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extracts parameters for analysis
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // We don't need the color for this logic
    std::string message = p.Get_String(2); // Gets the message string

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGE BLOCKED for playerid %d: %s", playerid, message.c_str());

        return 0; // Returns 0 (false) to Pawn, indicating the message was not sent.
                  // And most importantly, we do NOT call Call_Original_Native, blocking the message.
    }

    // If the message does not contain the forbidden word, we call the original native
    // and return its value, ensuring the message is sent normally
    // and that other hooks (if any) are executed.
    return Call_Original_Native(SendClientMessage);
}
```

#### Exemple complet de `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS is not strictly necessary for hooks, but it's common to have OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook for the CreateVehicle native
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extracts the parameters of the CreateVehicle native for inspection
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
        params[1] = static_cast<cell>(401); // The model is at position 0 in the parameters array (params[1])
        Samp_SDK::Log("  -> Model 400 changed to 401 before creation.");
    }
    
    // We call the original native (or the next hook in the chain) with the potentially modified parameters
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle returned: %d (Vehicle ID)", (int)original_retval);

    // You can modify the return value here before returning it to Pawn.
    // Example: if vehicle creation failed, return a custom invalid ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Vehicle creation failed in the original native.");

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
> La manipulation directe du tableau `cell* params` pour modifier les paramètres d'entrée nécessite de la prudence. Assurez-vous de comprendre l'ordre et le type des paramètres. Pour la plupart des cas d'utilisation, `p.Get(...)` pour inspecter et `Call_Original_Native(...)` pour continuer la chaîne est suffisant. La modification directe de `params` ne doit être effectuée que si vous savez que le paramètre est une valeur et doit être modifié pour l'appel original. Pour les chaînes et les tableaux, la modification est plus complexe et implique généralement `amx::Set_String` pour écrire à l'adresse existante ou réallouer, ce qui peut être plus facile à gérer en appelant la native via `Pawn_Native` avec les nouvelles valeurs et en retournant `0` de votre hook pour annuler l'appel original.

### 3.5. Macros `Pawn_*`: Appel de fonctions Pawn depuis le C++

Ces macros sont l'inverse de `Plugin_Public` et `Plugin_Native` : elles permettent à votre code C++ d'invoquer des fonctions Pawn.

#### `Pawn_Native(NomDeLaNative, ...)`

- **Objectif :** La manière recommandée d'appeler des fonctions natives SA-MP (ou d'autres plugins) depuis C++.
- **Mécanisme :** Recherche le pointeur de la native dans le cache interne du SDK (rempli par `Amx_Register_Detour`). Si trouvé, exécute la native dans un `Amx_Sandbox` (une instance AMX fausse et isolée).
- **Performance :** La plus efficace, car elle évite la recherche coûteuse des `publics` et interagit directement avec le pointeur de la native.

#### `Pawn_Public(NomDeLaPublic, ...)`

- **Objectif :** Appelle une fonction publique spécifique dans un script Pawn.
- **Mécanisme :** Parcourt les instances `AMX*` gérées par l'`Amx_Manager`, recherche la `public` par son nom et l'exécute.
- **Performance :** Moins efficace que `Pawn_Native` en raison de la recherche et du véritable `amx_Exec`. Généralement, les `publics` sont plus lentes que les `natives`.
- **Utilisation :** Idéal pour invoquer des événements personnalisés dans vos Gamemode/Filterscripts qui ne sont pas des natives.

#### `Pawn(NomDeLaFonction, ...)`

- **Objectif :** Une macro de commodité qui tente de deviner si la fonction est une native ou une publique.
- **Mécanisme :** D'abord, tente d'appeler comme `Pawn_Native`. Si cela échoue (la native n'est pas trouvée), tente d'appeler comme `Pawn_Public`.
- **Performance :** Peut être légèrement plus lente que `Pawn_Native` si la fonction est native, en raison de la double tentative de recherche. Pour les `publics`, les performances sont les mêmes que `Pawn_Public`.
- **Utilisation :** Pour les fonctions dont vous n'êtes pas sûr qu'elles soient natives ou publiques, ou pour éviter la répétition de code en essayant l'une puis l'autre.

#### Syntaxe et conventions

- **Nom de la fonction :** Utilisez toujours le nom de la fonction Pawn **directement, sans guillemets**. Le SDK le convertira en chaîne de caractères en interne.
- **Paramètres :** Passez les paramètres C++ directement.

```cpp
// Correct:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Incorrect (but would technically work due to hashing, avoid):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling des paramètres d'entrée

Le SDK convertit vos types C++ au format `cell` de l'AMX, gérant la mémoire selon les besoins :
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (en utilisant `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (alloue de la mémoire dans l'AMX, copie la chaîne et passe l'adresse `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling des paramètres de sortie (références : `int&`, `float&`, `std::string&`)

Ceci est une fonctionnalité clé pour la commodité et la sécurité. Pour les fonctions Pawn qui attendent un pointeur (référence), le SDK automatise tout le processus d'allocation/désallocation de mémoire et de copie des données.

- **Comment utiliser :** Il suffit de passer votre variable par référence (`&`).
- **Mécanisme :** Le SDK alloue de la mémoire sur le tas de l'AMX, passe l'adresse AMX à la fonction Pawn, attend que la fonction Pawn remplisse cette adresse, relit la valeur et libère la mémoire de l'AMX. Tout cela de manière transparente.
- **Avec `std::string&` :** Le SDK alloue un buffer standard (256 cellules) dans l'AMX pour la chaîne.

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

#### L'objet `Callback_Result`: Analyse complète

Tous les appels `Pawn_*` renvoient un objet `Callback_Result`. Cet objet est un wrapper sécurisé pour le résultat de l'appel Pawn.

- `Callback_Result() noexcept` : Constructeur par défaut, indique l'échec (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept` : Constructeur pour succès ou échec avec valeur.
- `explicit operator bool() const` : Permet d'utiliser `if (result)` pour vérifier si l'appel a réussi.
- `operator cell() const` : Permet de convertir le résultat en `cell` pour obtenir la valeur.
- `float As_Float() const` : Commodité pour obtenir le résultat sous forme de `float`.
- `cell Value() const` : Retourne la valeur brute `cell`.
- `bool Success() const` : Retourne `true` si l'appel Pawn a réussi.
- `int Get_Amx_Error() const` : Retourne le code d'erreur de l'AMX si l'appel a échoué (0 pour succès).

```cpp
// Example: Getting a player's health.
// The native GetPlayerHealth(playerid, &Float:health) expects a playerid and a reference to the health.
int playerid = 0; // Example player ID
float player_health = 0.0f;

// We call GetPlayerHealth, passing playerid and player_health by reference.
// The SDK will handle marshalling for the 'health' output parameter.
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

### 3.6. `Plugin_Module`: Gestion des modules dynamiques

La macro `Plugin_Module` permet à votre plugin d'agir comme un "chargeur" pour d'autres plugins, créant une architecture modulaire et extensible. Un module chargé de cette manière est traité comme un plugin de première classe, avec son propre cycle de vie d'événements géré par le plugin hôte.

#### Syntaxe et objectif

- `Plugin_Module(const char* nom_du_fichier_de_base, const char* repertoire_du_module, const char* message_de_succes_optionnel)`
- `nom_du_fichier_de_base` : Le nom *de base* du fichier du module, **sans l'extension** (ex : pour `my_module.dll` ou `my_module.so`, utilisez `"my_module"`). Le SDK ajoutera automatiquement l'extension `.dll` ou `.so` appropriée.
- `repertoire_du_module` : Le chemin du répertoire où se trouve le fichier du module (ex : `"plugins/my_custom_modules"`). **N'incluez pas le nom du fichier ici.** Le SDK concaténera le chemin complet (`repertoire_du_module/nom_du_fichier_de_base.ext`).
- `message_de_succes_optionnel` : Un message facultatif à afficher dans la console du serveur si le module se charge avec succès.

```cpp
// main.cpp, inside OnLoad()

// Loads the 'core_logic.dll' (or 'core_logic.so') module
// located in the server's 'modules/custom/' folder.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic Module loaded successfully!"))
    return (Samp_SDK::Log("FATAL ERROR: Failed to load 'core_logic' module!"), false);

// Loads the 'admin_system.dll' (or 'admin_system.so') module
// located directly in the server's 'plugins/' folder.
if (!Plugin_Module("admin_system", "plugins", "Administration Module activated."))
    Samp_SDK::Log("WARNING: Administration Module could not be loaded.");
```

#### Cycle de vie d'un module

Un module doit exporter les fonctions `Load`, `Unload` et `Supports`, tout comme un plugin normal. Le SDK gère le cycle de vie du module comme suit :

- **Chargement :** Lorsque `Plugin_Module` est appelé, le SDK :
   1. Construit le chemin complet du fichier (ex : `modules/custom/core_logic.dll`).
   2. Utilise `Dynamic_Library` (`LoadLibrary`/`dlopen`) pour charger le binaire.
   3. **Obtient les pointeurs de TOUTES les fonctions de cycle de vie du module :**
      - **Obligatoires :** `Load`, `Unload`, `Supports`. Si l'une d'elles manque, le chargement du module échoue.
      - **Optionnelles :** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Appelle la fonction `Load` du module, en passant `ppData` du plugin principal.
   5. Si `Load` retourne `true`, le module est ajouté à la liste interne des modules chargés.

- **Transfert d'événements :** Le plugin hôte **transfère automatiquement** les événements à tous les modules chargés.
 > [!IMPORTANT]
 > Pour que les événements soient transférés correctement, le **plugin hôte** (celui qui appelle `Plugin_Module`) doit être configuré pour recevoir ces événements.
 > - Pour que `AmxLoad` et `AmxUnload` fonctionnent dans les modules, le plugin hôte doit définir la macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Pour que `ProcessTick` fonctionne dans les modules, le plugin hôte doit définir la macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Déchargement :** Lors du `OnUnload` de votre plugin principal, le SDK décharge tous les modules qui ont été chargés via `Plugin_Module`. Cela se fait dans l'**ordre inverse** du chargement (le dernier chargé est le premier déchargé), ce qui est crucial pour gérer les dépendances et garantir la libération correcte des ressources.

#### Avantages de la modularisation

- **Organisation du code :** Divisez les gros plugins en composants plus petits et gérables, chacun dans son propre fichier de module.
- **Réutilisabilité :** Créez des modules génériques (ex : un module de base de données, un module de système de journalisation avancé) qui peuvent être utilisés par différents plugins, favorisant la réutilisation du code.
- **Composants indépendants :** Créez des modules qui sont **totalement orientés événements et indépendants**. Un module peut avoir ses propres `Plugin_Native`s, intercepter des `Plugin_Public`s et avoir sa propre logique `OnProcessTick`, fonctionnant comme un plugin autonome, mais chargé par un hôte.
- **Mises à jour dynamiques :** Dans des scénarios contrôlés, permet la mise à jour de parties de votre système (en remplaçant un `.dll` ou un `.so` de module) sans avoir besoin de recompiler et de redémarrer le plugin principal ou l'ensemble du serveur (bien que cela nécessite une gestion rigoureuse des versions et de la compatibilité).

### 3.7. `Plugin_Call`: Appel des natives internes du plugin

Utilisez `Plugin_Call` pour invoquer une `Plugin_Native` définie **au sein de votre propre plugin**.

#### Syntaxe et avantages en termes de performances

- `Plugin_Call(NomeDaNativa, Param1, Param2, ...)`
- **Avantage :** Évite la surcharge de la recherche de la native dans le tableau des natives de l'AMX. Le SDK maintient une carte directe des hachages de noms vers les pointeurs de fonction pour ses propres natives, ce qui en fait le moyen le plus rapide de les appeler en interne.
- **Requis :** `SAMP_SDK_WANT_AMX_EVENTS`.

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
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Calls its own native
                Samp_SDK::Log("Player %d is at a high level!", i);
        }
    }
}
```

### 3.8. Fonctions utilitaires du SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Description :** Imprime des messages sur la console du serveur et dans le fichier `server_log.txt`. Un wrapper sécurisé pour `logprintf`.
- **Utilisation :** Pour le débogage, les messages d'état et les erreurs.
- **Mécanisme :** En interne, le SDK obtient le pointeur de `logprintf` via `ppData[PLUGIN_DATA_LOGPRINTF]`. La fonction gère le formatage de la chaîne de manière sécurisée.

```cpp
// Anywhere in your plugin
Samp_SDK::Log("The plugin was initialized with a value %d and a string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (recommandé)

- **Description :** Formate une chaîne de caractères de manière sécurisée (similaire à `sprintf`) et renvoie un `std::string`. C'est le moyen **recommandé et le plus idiomatique** de formater des chaînes de caractères pour une utilisation dans votre plugin.
- **Utilisation :** Idéal pour construire des messages formatés avant de les passer à `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, ou pour tout autre besoin de chaîne de caractères dans votre code C++.
- **Mécanisme :** En interne, `Plugin_Format` est une macro qui appelle `Samp_SDK::Format`. Il utilise `vsnprintf` pour déterminer la taille exacte de la chaîne formatée et alloue un `std::string` avec une capacité suffisante, évitant les débordements de tampon.

```cpp
int playerid = 0; // Example ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Player %d, your current health is %d.", playerid, health));

// Can also be used for internal logs
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (détail d'implémentation)

- **Description :** La fonction d'implémentation sous-jacente pour le formatage des chaînes, située dans le namespace `Samp_SDK`.
- **Utilisation :** Généralement non appelée directement par l'utilisateur. La macro `Plugin_Format` est fournie comme une commodité pour cette fonction, s'alignant sur la convention de nommage des autres macros du SDK (`Plugin_Public`, `Plugin_Native`). Vous ne l'appelleriez directement que si vous vouliez éviter la macro `Plugin_Format` pour une raison spécifique.

```cpp
// Example of how Samp_SDK::Format works, but prefer Plugin_Format
std::string raw_status = Samp_SDK::Format("For internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Description :** Convertit une adresse de chaîne de l'AMX (`cell amx_addr`) en un `std::string` C++.
- **Utilisation :** Principalement à l'intérieur de `Plugin_Native` et `Plugin_Native_Hook` lorsque vous devez accéder à des chaînes qui ne sont pas automatiquement converties par `Register_Parameters` ou `Native_Params` (par exemple, si le paramètre Pawn est une `const` `string` et n'a pas été déclaré comme `std::string` dans votre `Plugin_Native` ou `Plugin_Public` pour le marshalling automatique).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Gets the string address in AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String from AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Anatomie interne et architecture du SDK

Cette section dévoile les mécanismes sous-jacents du SDK SA-MP, en explorant son architecture, les composants clés et la manière dont ils interagissent pour fournir une abstraction de haut niveau. Une compréhension approfondie de ces rouages permet au développeur d'optimiser l'utilisation du SDK, de déboguer des problèmes complexes et même d'étendre ses fonctionnalités.

### 4.1. `core.hpp`: La fondation minimaliste

Le `Samp_SDK::Core` est un `singleton` qui sert de point d'accès initial et centralisé aux données de bas niveau fournies par l'environnement du plugin SA-MP. Sa principale responsabilité est d'encapsuler et d'exposer les fonctionnalités essentielles.

- **`Samp_SDK::Core::Instance()`** :
   - **Description :** Retourne l'unique instance globale de la classe `Core`. C'est un modèle de conception `singleton` pour garantir que l'accès aux données du plugin (`ppData`) est cohérent et centralisé.
   - **Mécanisme :** L'instance est initialisée une seule fois lorsque `Core::Instance().Load(ppData)` est appelé dans la fonction `Load()` de votre plugin.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`** :
   - **Description :** Permet un accès sécurisé et indexé aux pointeurs de fonction de l'API AMX. Le tableau `pAMXFunctions` (reçu via `ppData[PLUGIN_DATA_AMX_EXPORTS]`) contient les adresses de fonctions critiques comme `amx_Exec`, `amx_Register`, etc.
   - **Impact :** Au lieu d'utiliser `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, le SDK offre des wrappers `type-safe` dans le namespace `amx::` (ex : `amx::Exec(...)`), rendant le code plus lisible et moins sujet aux erreurs de cast.
   - **Exemple interne (`amx_api.hpp`) :**
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

- **`logprintf_ptr`** :
   - **Description :** Un pointeur vers la fonction `logprintf` de SA-MP, qui est l'interface standard pour imprimer des messages sur la console du serveur et dans le `server_log.txt`.
   - **Mécanisme :** Le `Samp_SDK::Log` est un wrapper sécurisé qui utilise ce pointeur, garantissant que vos messages sont affichés correctement dans l'environnement de SA-MP.

### 4.2. `platform.hpp` et `version.hpp`: Compatibilité et métadonnées

Ces en-têtes sont la base de la portabilité et de l'optimisation du SDK, l'adaptant à différents environnements de compilation et tirant parti des fonctionnalités spécifiques du C++ moderne.

- **Détection de la plateforme et de l'architecture :**
   - **Mécanisme :** Utilise des macros de préprocesseur (`#if defined(WIN32)`, `#if defined(__linux__)`, etc.) pour identifier le système d'exploitation.
   - **Vérification de l'architecture :** Contient `static_assert` ou `#error` pour s'assurer que le plugin est compilé pour x86 (32 bits), une exigence critique pour la compatibilité avec SA-MP et le mécanisme de hooking.
   - **Gestion de l'exportation des symboles :**
      - `SAMP_SDK_EXPORT` : Une macro définie dans `platform.hpp` qui s'étend à `extern "C"` et, sous Linux, ajoute `__attribute__((visibility("default")))`. Sous Windows, elle garantit seulement `extern "C"` car le SDK utilise `pragma comment(linker, "/EXPORT:...")` (pour MSVC) ou le standard MinGW pour exporter les fonctions principales.
      - Cela garantit que les fonctions de cycle de vie du plugin (`Supports`, `Load`, `Unload`, etc.) sont correctement exportées de votre DLL/SO, quel que soit l'environnement de compilation, **sans la nécessité de fichiers `.def` ou d'ajouter `__attribute__((visibility("default")))` manuellement** dans votre implémentation.
   - **Exemple (`platform.hpp` - fragment pertinent) :**
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
   - **Exemple (`samp_sdk.hpp` - fragment pertinent de l'implémentation) :**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // On Windows (MSVC), we use pragma comment to export functions.
          // This eliminates the need for a .def file.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... other exports ...
      #endif

      // Implementation of exported functions
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... other functions ...
      #endif
      ```

- **Macros d'Optimisation et de Prédiction de Branch:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mécanisme:** `__forceinline` (MSVC) ou `__attribute__((always_inline)) inline` (GCC/Clang). Suggère fortement au compilateur d'insérer le corps de la fonction directement à l'emplacement de l'appel, éliminant le surcoût d'un appel de fonction réel.
      - **Utilisation:** Appliqué aux fonctions petites et critiques pour la performance au sein du SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mécanisme:** `[[likely]]` / `[[unlikely]]` (C++20) ou `__builtin_expect` (GCC/Clang). Indique au compilateur quel chemin d'un `if/else` est le plus susceptible d'être pris.
      - **Impact:** Aide le compilateur à générer un code plus efficace pour la prédiction de branche (branch prediction), réduisant la latence du CPU.
      - **Exemple (`platform.hpp`):**
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
      - **Mécanisme:** `__attribute__((used))` (GCC/Clang). Informe le compilateur qu'un symbole (dans ce cas, une fonction) est utilisé, même s'il n'y a pas de références à celui-ci dans le code C++.
      - **Impact:** Crucial pour les fonctions C++ qui sont appelées à partir de blocs d'assembly intégré (`asm volatile`). Sans cet attribut, l'optimiseur du compilateur peut supprimer la fonction par erreur, ce qui entraîne une erreur de "symbole indéfini" au niveau de l'éditeur de liens.
      - **Exemple (`platform.hpp`):**
         ```cpp
         #if defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
             #define SAMP_SDK_USED_BY_ASM __attribute__((used))
         #else
             #define SAMP_SDK_USED_BY_ASM
         #endif
         ```

- **Définitions C++ standard (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`) :**
   - **Mécanisme :** Macros définies en fonction de la valeur de `__cplusplus` et `_MSVC_LANG`.
   - **Utilisation :** Permettent au SDK d'utiliser les fonctionnalités les plus récentes du C++ (comme `std::apply` et `if constexpr` de C++17, ou `std::is_same_v` de C++17) lorsqu'elles sont disponibles, tout en maintenant la compatibilité avec les standards plus anciens.
   - **Exemple (`version.hpp` - utilisation de `if constexpr`) :**
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

### 4.3. `function_hook.hpp`: Le moteur d'interception x86

Cet en-tête définit le mécanisme de bas niveau pour réaliser des hooks (interceptions) de fonctions, ce qui est fondamental pour le fonctionnement du SDK. Il est strictement dépendant de l'architecture x86 (32 bits).

- **`X86_Detour`** :
   - **Description :** Une classe qui encapsule la logique de surcharge du début d'une fonction en mémoire avec une instruction de saut vers une fonction de détournement.
   - **`JUMP_INSTRUCTION_SIZE = 5`** :
      - **Mécanisme :** En x86, l'instruction de saut (`JMP`) relative a généralement 5 octets : `0xE9` (opcode pour JMP near, relative) suivi de 4 octets qui représentent le décalage (offset) de l'adresse de la cible par rapport à l'instruction suivante.
      - **Exemple d'instruction :** `E9 XX XX XX XX` (où `XX` sont les octets du décalage).
   - **`Apply(void* target, void* detour)`** :
      - **Action :** Installe le hook. D'abord, stocke les `JUMP_INSTRUCTION_SIZE` octets originaux de la fonction `target` (`original_bytes_`). Ensuite, calcule l'adresse relative du `detour` par rapport au `target` et écrase le début de `target` avec l'instruction `JMP`.
      - **Exemple de calcul de l'adresse relative :**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Detour address - (Target address + JMP instruction size)
         ```
   - **`Revert()`** :
      - **Action :** Désinstalle le hook, restaurant les `original_bytes_` dans la fonction `target`.
   - **`Unprotect_Memory(void* address, size_t size)`** :
      - **Mécanisme :** Sous Windows, utilise `VirtualProtect` ; sous Linux, `mprotect`. Ces appels système modifient les permissions de la page mémoire où réside la fonction en `EXECUTE_READWRITE` (Windows) ou `PROT_WRITE | PROT_EXEC` (Linux), permettant de modifier le code au moment de l'exécution.
      - **Exemple (`Unprotect_Memory`) :**
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

- **`Function_Hook<FuncPtr>`** :
   - **Description :** Un wrapper C++ `type-safe` pour le `X86_Detour`, garantissant que les types de pointeurs de fonction sont corrects.
   - `Install(void* target, void* detour)` : Encapsule l'appel `X86_Detour::Apply`.
   - `Uninstall()` : Encapsule l'appel `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`** :
      - **Mécanisme de sécurité (Garde de récursion) :** Cette fonction est critique pour éviter les boucles infinies lorsque le détournement doit appeler la fonction originale. Elle **désinstalle temporairement le hook (`detour_.Revert()`)**, appelle la fonction originale (`Get_Original()(args...)`), puis **réinstalle le hook (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`** : Un compteur qui garantit que le hook n'est réinstallé que lorsque l'appel original de plus haut niveau est terminé, permettant des appels récursifs sécurisés de la fonction originale (si la fonction originale est récursive, par exemple). Le `thread_local` garantit que le `recursion_guard` est isolé pour chaque thread, important dans les environnements multi-threaded.
      - **Exemple (`Call_Original` avec Scope_Guard) :**
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

### 4.4. `interceptor_manager.hpp`: Le contrôleur de hooks de l'AMX

Ce `singleton` est le centre névralgique de l'interaction du SDK avec la machine virtuelle AMX de SA-MP. Il coordonne l'installation des hooks fournis par `function_hook.hpp` dans les fonctions de l'API AMX exposées par le serveur, redirigeant le flux d'exécution vers la logique du SDK.

- **`Activate()` / `Deactivate()`** :
   - **Description :** Méthodes publiques pour installer et désinstaller tous les hooks nécessaires. Appelés dans `OnLoad()` et `OnUnload()` de votre plugin, respectivement.
   - **Mécanisme :** Obtient les pointeurs des fonctions AMX (telles que `amx_Register`, `amx_Exec`, etc.) en utilisant `Core::Instance().Get_AMX_Export(...)` et installe les détours.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`** :
   - **Fonction hookée :** `amx_Register`
   - **Objectif :** Intercepte l'enregistrement de *toutes* les natives (par SA-MP, d'autres plugins ou le gamemode).
   - **Action :** Pour chaque native enregistrée, l'`Interceptor_Manager` l'ajoute à un cache interne (`Cache_Data::native_cache`).
   - **Impact :** Ce cache est fondamental pour la performance de `Pawn_Native`, permettant une recherche extrêmement rapide du pointeur de la native au lieu d'une recherche coûteuse dans l'AMX.
   - **Fonction supplémentaire pour `Plugin_Native_Hook` :** Ce détour est *également* responsable de la modification de la liste des natives avant leur enregistrement. Si une native a un `Plugin_Native_Hook` associé, le pointeur de la fonction dans la liste d'enregistrement est remplacé par le trampoline généré par le `Native_Hook_Manager`. Cela permet à votre hook d'être le premier à être appelé.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`** :
   - **Fonction hookée :** `amx_Exec`
   - **Objectif :** **Ceci est le hook le plus critique.** Il intercepte *toute* exécution de code dans l'AMX, y compris l'appel des `publics` de Pawn.
   - **Mécanisme d'interception de `Plugin_Public` :**
      1. Lorsque `amx_Exec` est appelé pour une `public` (ou `AMX_EXEC_MAIN`), l'`Amx_Exec_Detour` est exécuté.
      2. Il obtient le nom de la `public` (en utilisant `tl_public_name` qui a été rempli par `Amx_Find_Public_Detour`).
      3. Consulte le `Public_Dispatcher::Instance().Dispatch()` pour vérifier s'il y a des handlers C++ enregistrés pour ce nom.
      4. S'il y a des handlers, il les exécute. Le `Public_Dispatcher` gère le `marshalling` des paramètres de l'AMX vers les types C++ corrects.
      5. En fonction de la valeur de retour du `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), il décide s'il appelle l'`amx_Exec` original (`Get_Amx_Exec_Hook().Call_Original(...)`) ou s'il met fin à l'exécution de la `public` Pawn.
      6. **Manipulation de la pile :** Si l'exécution de la `public` Pawn est interrompue (`PLUGIN_PUBLIC_STOP`), l'`Amx_Exec_Detour` corrige la pile de l'AMX (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) pour éviter les incohérences.
   - **Activation de `Plugin_Native_Hook` (Patching AMX) :**
      - La première fois qu'un `AMX*` est exécuté, ce détour vérifie si l'AMX a déjà été "patchée" (`!manager.Is_Amx_Patched(amx)`).
      - Si ce n'est pas le cas, il parcourt la table des natives **de cette instance AMX spécifique en mémoire**.
      - Pour chaque native qui a un `Plugin_Native_Hook` enregistré dans le `Native_Hook_Manager`, il remplace l'adresse de la native dans la table par un trampoline généré par le `Native_Hook_Manager`. L'adresse originale (ou du hook précédent) est sauvegardée dans l'objet `Native_Hook`.
      - L'AMX est ensuite marquée comme "patchée" pour éviter un nouveau traitement inutile.
   - **Exemple (`Amx_Exec_Detour` - avec les détails de `Plugin_Native_Hook`) :**
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

                  for (auto& hook_to_apply : hooks_to_apply) { // Iterates through all registered Plugin_Native_Hook
                      uint32_t hook_hash = hook_to_apply.Get_Hash();

                      for (int i = 0; i < num_natives; ++i) { // Iterates through the AMX natives
                          const char* native_name = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(hdr) + natives[i].nameofs);

                          if (FNV1a_Hash(native_name) == hook_hash) { // If the AMX native name matches a hook
                              AMX_NATIVE current_func = reinterpret_cast<AMX_NATIVE>(natives[i].address);

                              hook_to_apply.Set_Next_In_Chain(current_func); // Saves the original/previous function pointer

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
- **`int SAMP_SDK_AMX_API Amx_Find_Public_Detour(...)`** :
   - **Fonction hookée :** `amx_FindPublic`
   - **Objectif :** Intercepte la recherche de `publics` par leur nom.
   - **Mécanisme des "Ghost Publics" :** Si `amx_FindPublic` original ne trouve pas de `public` dans le Pawn, mais que le `Public_Dispatcher` a un handler C++ enregistré pour ce nom, ce hook renvoie `AMX_ERR_NONE` et un `index` spécial (`PLUGIN_EXEC_GHOST_PUBLIC`). Cela fait en sorte que l'API SA-MP "pense" que la `public` existe, permettant que l'appel `amx_Exec` subséquent (pour cet index spécial) soit intercepté par l'`Amx_Exec_Detour`, qui redirige ensuite vers le handler C++.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`** : Utilisé pour passer le nom de la `public` à l'`Amx_Exec_Detour` lorsqu'un "ghost public" est détecté, car l'`amx_Exec` ne reçoit que l'index, pas le nom.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`** :
   - **Fonctions hookées :** `amx_Init` / `amx_Cleanup`
   - **Objectif :** Gérer la liste des instances `AMX*` actives.
   - **Action :** `Amx_Init_Detour` appelle `Amx_Manager::Instance().Add_Amx()`, et `Amx_Cleanup_Detour` appelle `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Gestion des instances `AMX*`

Ce `singleton` conserve un registre dynamique de toutes les machines virtuelles AMX actuellement chargées sur le serveur. Il est essentiel pour les fonctions qui doivent interagir avec "tous les scripts" ou trouver un script spécifique.

- **`std::vector<AMX*> loaded_amx_`** :
   - **Description :** Une liste de pointeurs vers toutes les instances `AMX*` qui ont été initialisées (gamemode et filterscripts).
   - **Gestion :** Remplie par les hooks `Amx_Init_Detour` et vidée par `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)** :
   - **Objectif :** Protège `loaded_amx_` contre l'accès concurrent dans les environnements multi-threaded (bien que SA-MP soit majoritairement single-thread, c'est une bonne pratique de sécurité). `std::shared_mutex` permet plusieurs lecteurs simultanément, mais un seul écrivain.
- **`std::atomic<uint32_t> generation_`** :
   - **Objectif :** Un compteur qui s'incrémente chaque fois qu'une AMX est ajoutée ou supprimée.
   - **Utilisation :** Il est utilisé par le `Caller_Cache` dans `callbacks.hpp` pour détecter quand la liste des AMX a changé, invalidant les caches de recherche de `publics` et garantissant que les appels `Pawn_Public` fonctionnent toujours avec des informations à jour. Cela optimise les performances en évitant des recherches répétitives dans un état qui n'a pas changé.
- **`AMX* Find_Public(const char* name, int& index)`** :
   - **Description :** Parcourt `loaded_amx_` (du plus récent au plus ancien, ce qui place généralement le gamemode ou le filterscript le plus pertinent en premier) pour trouver la `public` avec le nom spécifié.
   - **Mécanisme :** Utilise `amx::Find_Public` pour chaque instance `AMX*`.
   - **Impact :** C'est la base de `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: Le routeur de callbacks `Plugin_Public`

Ce `singleton` est le composant qui mappe les noms de `publics` du Pawn à ses fonctions C++ `Plugin_Public`.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`** :
   - **Clé :** Le hash FNV1a du nom de la `public` (ex : `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Valeur :** Un `std::vector` de `std::function<cell(AMX*)>`, où chaque `std::function` est un handler C++ enregistré pour cette `public`.
   - **Mécanisme :** Le `std::vector` permet d'enregistrer plusieurs `Plugin_Public`s pour le même callback (ex : plusieurs plugins voulant intercepter `OnPlayerCommandText`). Les handlers sont exécutés dans l'ordre inverse de l'enregistrement.
- **`Public_Register`** :
   - **Mécanisme :** C'est une classe template dont la macro `PLUGIN_PUBLIC_REGISTRATION` crée une instance statique globale. Dans le constructeur statique (`static bool registered = [...]`), elle enregistre son handler `Plugin_Public` dans le `Public_Dispatcher`. C'est un modèle de "enregistrement statique au moment de la compilation/initialisation".
   - **Exemple (`public_dispatcher.hpp`) :**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Register<decltype(&name), &name, hash_##name> register_##name;
      ```

- **`Public_Traits` et `Wrapper()`** :
   - **Mécanisme :** `Public_Traits` est un modèle de trait qui, utilisant la métaprogrammation, génère une fonction `static cell Wrapper(AMX* amx)`.
   - **Objectif :** Cette `Wrapper` est la `Amx_Handler_Func` que le `Public_Dispatcher` stocke et appelle réellement. Elle est responsable de :
      1. Appeler `Public_Param_Reader::Get_Public_Params(amx, args...)` pour extraire les paramètres de la pile de l'AMX.
      2. Appeler votre fonction `Plugin_Public` C++ réelle (`func_ptr`) avec les paramètres déjà convertis aux types C++ corrects.
- **`Public_Param_Reader::Get_Public_Params(...)`** :
   - **Description :** Un ensemble de fonctions de modèle récursives qui lisent les valeurs de la pile de l'AMX et les convertissent aux types C++ spécifiés dans la déclaration du `Plugin_Public`.
   - **Mécanisme :** Utilise `Get_Stack_Cell()` pour accéder aux `cell`s de la pile. Utilise `if constexpr` (C++17+) ou `std::is_same<T>::value` (C++14) pour appliquer la conversion correcte (`amx::AMX_CTOF` pour float, `Samp_SDK::Get_String` pour string, cast direct pour int).

### 4.7. `native.hpp`: Gestion et appel des natives du plugin

Cet en-tête est dédié à la création et à la gestion des natives C++ que votre plugin expose à Pawn.

- **`Native_List_Holder`** :
   - **Description :** Un `singleton` global qui stocke toutes les `Plugin_Native`s déclarées dans votre plugin (de tous les fichiers `.cpp` qui utilisent `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`** : Contient des objets `Native` (qui stockent le nom de la native et le pointeur vers la fonction C++ `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`** : Une carte optimisée par hachage pour les recherches rapides de `Plugin_Native`s internes (utilisée par `Plugin_Call`).
- **`Native_Register`** :
   - **Mécanisme :** Tout comme le `Public_Register`, c'est une classe template dont la macro `Plugin_Native` crée une instance statique globale. Dans son constructeur, elle ajoute la native au `Native_List_Holder`.
   - **Impact :** Vous permet de déclarer des `Plugin_Native`s dans plusieurs fichiers `.cpp` sans vous soucier de l'enregistrement manuel. Toutes seront collectées automatiquement.
- **`Native_Registry`** :
   - **Description :** Une classe auxiliaire qui, dans `OnAmxLoad`, prend la liste complète des `Native`s du `Native_List_Holder` et les formate dans un tableau `AMX_NATIVE_INFO`.
   - **Mécanisme :** Appelle `amx::Register(amx, amx_natives_info_.data(), -1)` pour enregistrer toutes vos natives dans l'instance AMX qui vient d'être chargée.
- **`Plugin_Call_Impl(...)`** :
   - **Description :** L'implémentation sous-jacente de la macro `Plugin_Call`.
   - **Mécanisme :** Utilise `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` pour obtenir directement le pointeur de la fonction C++.
   - **Environnement :** Exécute la native dans un environnement `Amx_Sandbox` (isolé) pour gérer la pile et le tas temporaires, de manière similaire à la façon dont `Pawn_Native` fonctionne.

### 4.8. `native_hook_manager.hpp`: Le Moteur de Hooks de Natives

C'est le système robuste de hooking de natives, conçu pour gérer l'enchaînement de hooks de multiples plugins pour la même native.

- **`Native_Hook`**:
   - **Description:** Une classe qui représente un unique hook de native. Elle stocke le hash du nom de la native, la fonction handler C++ fournie par l'utilisateur (`user_handler_`) et un `std::atomic<AMX_NATIVE> next_in_chain_`.
   - **`user_handler_`**: Votre fonction `Plugin_Native_Hook` C++.
   - **`next_in_chain_`**: Le pointeur vers la native originale ou vers le hook d'un plugin avec une priorité plus basse. C'est un `std::atomic` pour garantir la sécurité des threads en lecture/écriture.
   - **`Dispatch(AMX* amx, cell* params)`**: Appelée par le trampoline pour exécuter votre `user_handler_`.
   - **`Call_Original(AMX* amx, cell* params)`**: Méthode cruciale qui appelle `next_in_chain_`, permettant à votre hook d'invoquer la fonctionnalité originale ou le prochain hook dans la chaîne.
- **`Trampoline_Allocator`**:
   - **Description:** Une classe responsable d'allouer des blocs de mémoire exécutable et de générer le code assembly "trampoline" dans ces blocs.
   - **`Generate_Trampoline_Code(unsigned char* memory, int hook_id)`**: Écrit 10 octets d'assembly:
      1. `B8 XX XX XX XX`: `MOV EAX, hook_id` (place l'ID unique du hook dans le registre EAX).
      2. `E9 XX XX XX XX`: `JMP relative_address_to_Dispatch_Wrapper_Asm` (saute vers la fonction de dispatch générique du SDK).
   - **`Allocation_Size = 4096`**: Alloue de la mémoire en pages pour l'efficacité et l'alignement du cache.
   - **Permissions de Mémoire:** Utilise `VirtualAlloc` (Windows) ou `mmap` (Linux) avec les permissions `EXECUTE_READWRITE` pour garantir que le code généré peut être exécuté.
- **`Dispatch_Wrapper_Asm()`**:
   - **Description:** Une petite fonction en assembly (définie avec `__declspec(naked)` ou `asm volatile`) qui sert de destination à tous les trampolines.
   - **Action:** Sauvegarde les registres, déplace `EAX` (qui contient le `hook_id`) vers la pile, et appelle la fonction `Dispatch_Hook` en C++. Après le retour de `Dispatch_Hook`, elle restaure les registres et retourne.
- **`cell SAMP_SDK_CDECL Dispatch_Hook(int hook_id, AMX* amx, cell* params)`**:
   - **Description:** La fonction C++ générique appelée par `Dispatch_Wrapper_Asm`.
   - **Action:** Utilise `hook_id` pour trouver le `Native_Hook` correspondant dans le `Native_Hook_Manager` et appelle sa méthode `Dispatch()`, qui à son tour invoque le handler `Plugin_Native_Hook` de l'utilisateur.
   - **Considérations de Linkage:** Cette fonction est un point critique d'interopérabilité entre C++ et assembly. Pour garantir qu'elle soit correctement exportée et trouvée par l'éditeur de liens sous Linux (GCC/Clang), elle est définie avec trois caractéristiques importantes:
      1. **`extern "C"`**: Empêche le C++ Name Mangling, garantissant que le symbole ait le nom C pur `Dispatch_Hook`, ce que le code assembly recherche.
      2. **`inline`**: Permet que la définition de la fonction réside dans le fichier d'en-tête (nécessaire pour une bibliothèque header-only) sans causer d'erreurs de "définition multiple" (ODR - One Definition Rule).
      3. **`SAMP_SDK_USED_BY_ASM` (`__attribute__((used))` sous GCC/Clang)**: Force le compilateur à émettre le code pour la fonction, même s'il ne trouve aucun appel à celle-ci à partir d'un autre code C++. Cela évite que l'optimiseur ne la supprime par erreur.
- **`Native_Hook_Manager`**:
   - **Description:** Le `singleton` central qui gère tous les `Native_Hook`s enregistrés et leurs trampolines.
   - **`std::list<Native_Hook> hooks_`**: Stocke la liste des hooks dans l'ordre.
   - **`std::unordered_map<uint32_t, Trampoline_Func> hash_to_trampoline_`**: Mappe le hash du nom de la native vers le pointeur du trampoline généré.
   - **`std::vector<uint32_t> hook_id_to_hash_`**: Mappe l'ID entier du hook (utilisé dans le trampoline) vers le hash du nom de la native.
   - **`Get_Trampoline(uint32_t hash)`**: Retourne (ou crée et alloue) un pointeur de trampoline pour un hash de native donné.
- **`PLUGIN_NATIVE_HOOK_REGISTRATION`**:
   - **Mécanisme:** Une macro qui crée une classe statique globale (`Native_Hook_Register_##name`) pour chaque `Plugin_Native_Hook`. Dans le constructeur statique de cette classe, elle enregistre le `handler` de l'utilisateur dans le `Native_Hook_Manager`.

### 4.9. `callbacks.hpp` & `amx_memory.hpp`: Appels C++ -> Pawn et RAII

Ces en-têtes constituent l'épine dorsale pour appeler des fonctions Pawn depuis C++ (macros `Pawn_*`) et garantissent la sécurité de la mémoire.

- **`Amx_Sandbox`** :
   - **Description :** Une structure `thread_local` qui simule un environnement `AMX` minimaliste et isolé pour les appels `Pawn_Native` et `Plugin_Call`.
   - **Mécanisme :** Possède sa propre structure `AMX`, `AMX_HEADER` et un `std::vector<unsigned char> heap` pour simuler la mémoire d'un script. Cela permet d'appeler `amx::Push`, `amx::Allot`, etc., sans interférer avec l'état des scripts Pawn réels en cours d'exécution.
   - **`thread_local` :** Garantit que chaque thread a son propre `Amx_Sandbox`, évitant les conditions de concurrence si le SDK est utilisé dans un contexte multi-threadé (ex : un futur pool de threads pour des opérations non-Pawn).
   - **Exemple (`Amx_Sandbox`) :**
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

- **`Parameter_Processor`** :
   - **Description :** Un ensemble de fonctions de modèle surchargées qui gèrent le `marshalling` de *chaque* paramètre C++ au format `cell` attendu par l'AMX, et vice versa pour les paramètres de sortie.
   - **Traitement d'entrée :**
       - Pour `int`, `float`, `bool` : Convertit directement en `cell`.
       - Pour `const char*`, `std::string` : Alloue de la mémoire sur le tas de l'`Amx_Sandbox` (ou l'AMX réelle pour `Pawn_Public`), copie la chaîne et pousse l'adresse AMX sur la pile.
   - **Traitement de sortie (`is_output_arg`) :**
       - **Mécanisme :** Lorsqu'un argument est une référence de lvalue non-const (détectée par le trait `is_output_arg`), le `Parameter_Processor` ne pousse pas la valeur, mais une *adresse AMX* pour une `cell` allouée temporairement sur le tas.
       - **`std::vector<std::function<void()>> post_call_updaters`** : Après l'appel de la native Pawn, une liste de lambdas (`post_call_updaters`) est exécutée. Chaque lambda est responsable de lire la valeur finale de la `cell` allouée dans l'AMX et de l'attribuer à la variable C++ originale (ex : `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`** :
   - **Mécanisme :** Un `std::integral_constant` (trait de type) qui, au moment de la compilation, évalue si un type de paramètre C++ est une référence modifiable (ex : `int&`, `float&`, `std::string&`). Cela permet au `Parameter_Processor` de différencier les paramètres d'entrée des paramètres de sortie.
   - **Exemple (`is_output_arg`) :**
      ```cpp
      // Simplified snippet from callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`** :
   - **Description :** Une classe RAII (`Resource Acquisition Is Initialization`) qui encapsule l'allocation et la désallocation de mémoire dans l'AMX.
   - **Mécanisme :** Dans le constructeur, elle appelle `amx::Allot` pour obtenir un `amx_addr` et un `phys_addr`. Dans le destructeur, elle appelle `amx::Release` pour libérer cette mémoire.
   - **Impact :** **Crucial pour prévenir les fuites de mémoire sur le tas de l'AMX.** Garantit que la mémoire temporaire utilisée pour les chaînes ou les paramètres de sortie est toujours libérée, même si des exceptions ou des retours anticipés se produisent.

### 4.10. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Accès abstrait à l'AMX

Ces en-têtes fournissent les définitions fondamentales et les outils de haut niveau pour interagir avec le Pawn.

- **`amx_defs.h`** :
   - **Contenu :** Contient les définitions brutes des structures AMX (`AMX`, `AMX_HEADER`), des types (`cell`, `ucell`), et des enums d'erreur (`AmxError`). Définit également `AMX_NATIVE` et `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`** : Utilise des attributs de packing (`#pragma pack(push, 1)` / `__attribute__((packed))`) pour garantir que les structures AMX ont la disposition mémoire correcte, fondamentale pour l'interopérabilité.
- **`Samp_SDK::amx::Call<Func, Index, ...>`** :
   - **Description :** La fonction template principale pour invoquer les fonctions de l'API AMX exposées par le serveur.
   - **Mécanisme :** Obtient le pointeur de la fonction via `Core::Instance().Get_AMX_Export(Index)` et l'appelle. Centralise le traitement des erreurs si le pointeur de la fonction n'est pas disponible.
   - **Impact :** Convertit les appels de bas niveau (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) en appels C++ idiomatiques et type-safe (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`** :
   - **Description :** Fonctions essentielles pour convertir les valeurs `cell` en `float` et vice versa, en effectuant une réinterprétation bit à bit de la mémoire.
   - **`static_assert` :** Incluent `static_assert` pour garantir que `sizeof(cell) == sizeof(float)` au moment de la compilation, prévenant les erreurs sur les plateformes avec des tailles de type différentes.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`** :
   - **Description :** Helper pour convertir une adresse AMX de chaîne en `std::string`.
   - **Mécanisme :** D'abord, obtient l'adresse physique (`cell* phys_addr`) de la chaîne dans l'AMX en utilisant `amx::Get_Addr`. Ensuite, utilise `amx::STR_Len` pour déterminer la longueur et `amx::Get_String` pour copier les octets dans un `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`** :
   - **Description :** La fonction de base de formatage de chaînes (`printf`-like) pour le SDK.
   - **Mécanisme :** Utilise `vsnprintf` en deux passes : d'abord pour déterminer la taille nécessaire de la chaîne, puis pour formater la chaîne dans le `std::string` alloué dynamiquement. Cela évite les débordements de tampon.

## 5. Compilation et déploiement

### Exigences d'architecture et de plateforme

- Votre plugin **DOIT** être compilé pour l'architecture **x86 (32 bits)**.
- Plateformes prises en charge : Windows (.dll) et Linux (.so).

### Exemples de commandes de compilation

#### **MSVC (Visual Studio)**

1. Créez un nouveau projet de "Dynamic-Link Library (DLL)".
2. Dans les paramètres du projet, définissez la "Plateforme de solution" sur **x86**.
3. Assurez-vous que le standard de langage C++ est au moins C++14.

#### **GCC / Clang (Linux)**

```bash
# For a plugin named 'my_plugin.so' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32` : Compile pour 32 bits.
- `-shared` : Crée une bibliothèque partagée (`.so`).
- `-std=c++17` : Définit le standard C++ sur C++17 (peut être `c++14` ou `c++20`).
- `-O2` : Niveau d'optimisation 2.
- `-fPIC` : Génère du code indépendant de la position, nécessaire pour les bibliothèques partagées.
- `-Wall -Wextra` : Active des avertissements supplémentaires pour aider à détecter les erreurs.
- `-Wl,--no-undefined` : Empêche la création de la bibliothèque s'il y a des symboles non définis.

#### **GCC / Clang (MinGW sur Windows)**

```bash
# For a plugin named 'my_plugin.dll' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++` : Lie la bibliothèque standard C++ statiquement. Essentiel pour éviter que votre plugin ne dépende de DLLs d'exécution spécifiques au compilateur qui pourraient ne pas être présentes sur le système de l'utilisateur.
- `-static-libgcc` : Lie la bibliothèque GCC statiquement.

### Considérations pour la distribution

- **Nom du fichier :** Votre plugin doit avoir l'extension `.dll` (Windows) ou `.so` (Linux). Ex : `my_plugin.dll`.
- **Emplacement :** Placez le fichier compilé dans le dossier `plugins/` de votre serveur SA-MP.
- **server.cfg :** Ajoutez le nom de votre plugin (si Windows, sans l'extension) à la ligne `plugins` dans le `server.cfg`.
   ```
   plugins my_plugin (if Linux, my_plugin.so)
   ```

## Licence

Copyright © **SA-MP Programming Community**

Ce logiciel est sous licence selon les termes de la Licence MIT ("Licence"); vous pouvez utiliser ce logiciel conformément aux conditions de la Licence. Une copie de la Licence peut être obtenue à: [MIT License](https://opensource.org/licenses/MIT)

### Conditions Générales d'Utilisation

#### 1. Autorisations Accordées

La présente licence accorde gratuitement à toute personne obtenant une copie de ce logiciel et des fichiers de documentation associés les droits suivants:
* Utiliser, copier, modifier, fusionner, publier, distribuer, sous-licencier et/ou vendre des copies du logiciel sans restriction
* Permettre aux personnes à qui le logiciel est fourni de faire de même, sous réserve des conditions suivantes

#### 2. Conditions Obligatoires

Toutes les copies ou parties substantielles du logiciel doivent inclure:
* L'avis de droit d'auteur ci-dessus
* Cet avis d'autorisation
* L'avis de non-responsabilité ci-dessous

#### 3. Droits d'Auteur

Le logiciel et toute la documentation associée sont protégés par les lois sur le droit d'auteur. La **SA-MP Programming Community** conserve la propriété des droits d'auteur originaux du logiciel.

#### 4. Exclusion de Garantie et Limitation de Responsabilité

LE LOGICIEL EST FOURNI "TEL QUEL", SANS GARANTIE D'AUCUNE SORTE, EXPRESSE OU IMPLICITE, Y COMPRIS MAIS NON LIMITÉ AUX GARANTIES DE COMMERCIALISATION, D'ADÉQUATION À UN USAGE PARTICULIER ET DE NON-VIOLATION.

EN AUCUN CAS LES AUTEURS OU LES DÉTENTEURS DES DROITS D'AUTEUR NE SERONT RESPONSABLES DE TOUTE RÉCLAMATION, DOMMAGE OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS UNE ACTION DE CONTRAT, UN DÉLIT OU AUTRE, DÉCOULANT DE, HORS DE OU EN RELATION AVEC LE LOGICIEL OU L'UTILISATION OU D'AUTRES TRANSACTIONS DANS LE LOGICIEL.

---

Pour des informations détaillées sur la Licence MIT, consultez: https://opensource.org/licenses/MIT