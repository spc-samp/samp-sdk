# SAMP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Un SDK C++ moderne, header-only et de haut niveau pour le développement de plugins et modules pour SA-MP.**

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

- [SAMP SDK](#samp-sdk)
  - [Langues](#langues)
  - [Table des matières](#table-des-matières)
  - [1. Introduction et philosophie de conception](#1-introduction-et-philosophie-de-conception)
    - [Le problème avec l'API C standard de SA-MP](#le-problème-avec-lapi-c-standard-de-sa-mp)
    - [La solution du SAMP SDK : Abstraction avec sécurité et performance](#la-solution-du-samp-sdk--abstraction-avec-sécurité-et-performance)
    - [Modèle Header-Only : Avantages et implications](#modèle-header-only--avantages-et-implications)
  - [2. Configuration et environnement](#2-configuration-et-environnement)
    - [Exigences de compilation](#exigences-de-compilation)
    - [Structure de fichiers recommandée](#structure-de-fichiers-recommandée)
    - [Macros de configuration essentielles\*\*](#macros-de-configuration-essentielles)
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
    - [3.2. `Plugin_Public` : Intercepter les événements Pawn](#32-plugin_public--intercepter-les-événements-pawn)
      - [Syntaxe et déclaration](#syntaxe-et-déclaration)
      - [Marshalling automatique des paramètres](#marshalling-automatique-des-paramètres)
      - [Contrôle de flux : `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#contrôle-de-flux--plugin_public_continue-vs-plugin_public_stop)
    - [3.3. `Plugin_Native` : Créer des fonctions natives en C++](#33-plugin_native--créer-des-fonctions-natives-en-c)
      - [Syntaxe et signature fixe](#syntaxe-et-signature-fixe)
      - [Enregistrement automatique des natives](#enregistrement-automatique-des-natives)
      - [Extraction de paramètres : `Register_Parameters` vs. `Native_Params`](#extraction-de-paramètres--register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (API Complète : `Get`, `Get_REF`, `Set_REF`)](#native_params-api-complète--get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Retour de valeurs](#retour-de-valeurs)
    - [3.4. Macros `Pawn_*` : Appeler des fonctions Pawn depuis le C++](#34-macros-pawn_--appeler-des-fonctions-pawn-depuis-le-c)
      - [`Pawn_Native(NomDeLaNative, ...)`](#pawn_nativenomdelanative-)
      - [`Pawn_Public(NomDeLaPublic, ...)`](#pawn_publicnomdelapublic-)
      - [`Pawn(NomDeLaFonction, ...)`](#pawnnomdelafonction-)
      - [Syntaxe et conventions](#syntaxe-et-conventions)
      - [Marshalling des paramètres d'entrée](#marshalling-des-paramètres-dentrée)
      - [Marshalling des paramètres de sortie (Références : `int&`, `float&`, `std::string&`)](#marshalling-des-paramètres-de-sortie-références--int-float-stdstring)
      - [L'objet `Callback_Result` : Analyse complète](#lobjet-callback_result--analyse-complète)
      - [**3.5. `Plugin_Module` : Gestion des Modules Dynamiques**](#35-plugin_module--gestion-des-modules-dynamiques)
      - [Syntaxe et Objectif](#syntaxe-et-objectif)
      - [Cycle de Vie d'un Module](#cycle-de-vie-dun-module)
      - [Avantages de la Modularisation](#avantages-de-la-modularisation)
    - [3.6. `Plugin_Call` : Appeler les natives internes du plugin](#36-plugin_call--appeler-les-natives-internes-du-plugin)
      - [Syntaxe et avantages de performance](#syntaxe-et-avantages-de-performance)
    - [**3.7. Fonctions utilitaires du SDK**](#37-fonctions-utilitaires-du-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Recommandé)](#stdstring-plugin_formatconst-char-format--recommandé)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Détail d'implémentation)](#stdstring-samp_sdkformatconst-char-format--détail-dimplémentation)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. **Anatomie interne et architecture du SDK**](#4-anatomie-interne-et-architecture-du-sdk)
    - [4.1. `core.hpp` : La fondation minimaliste](#41-corehpp--la-fondation-minimaliste)
    - [**4.2. `platform.hpp` et `version.hpp` : Compatibilité et métadonnées**](#42-platformhpp-et-versionhpp--compatibilité-et-métadonnées)
    - [4.3. `function_hook.hpp` : Le moteur d'interception x86](#43-function_hookhpp--le-moteur-dinterception-x86)
    - [4.4. `interceptor_manager.hpp` : Le contrôleur de hooks de l'AMX](#44-interceptor_managerhpp--le-contrôleur-de-hooks-de-lamx)
    - [4.5. `amx_manager.hpp` : Gestion des instances `AMX*`](#45-amx_managerhpp--gestion-des-instances-amx)
    - [4.6. `public_dispatcher.hpp` : Le routeur de Callbacks `Plugin_Public`](#46-public_dispatcherhpp--le-routeur-de-callbacks-plugin_public)
    - [4.7. `native.hpp` : Gestion et appel des natives du plugin](#47-nativehpp--gestion-et-appel-des-natives-du-plugin)
    - [4.8. `callbacks.hpp` \& `amx_memory.hpp` : Appels C++ -\> Pawn et RAII](#48-callbackshpp--amx_memoryhpp--appels-c---pawn-et-raii)
    - [4.9. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h` : Accès abstrait à l'AMX](#49-amx_apihpp--amx_helpershpp--amx_defsh--accès-abstrait-à-lamx)
  - [5. Compilation et déploiement](#5-compilation-et-déploiement)
    - [Exigences d'architecture et de plateforme](#exigences-darchitecture-et-de-plateforme)
    - [Exemples de commandes de compilation](#exemples-de-commandes-de-compilation)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW sous Windows)**](#gcc--clang-mingw-sous-windows)
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
- **Gestion manuelle de la mémoire :** Des fonctions comme `amx_Allot` et `amx_Release` exigent du développeur d'allouer et de désallouer explicitement la mémoire sur le tas de l'AMX. C'est une source courante de fuites de mémoire et de défaillances d'exécution.
- **Typage faible et conversions manuelles :** Les paramètres sont passés sous forme de tableau de `cell`s, forçant des conversions explicites (et souvent non sécurisées) entre `cell`, `int`, `float`, et `char*`.
- **Verbosité et boilerplate :** Extraire plusieurs paramètres d'un tableau `cell* params`, gérer les tailles de chaînes et la pile de l'AMX pour les rappels C++ vers Pawn exige un code répétitif.
- **Fragilité de l'interface :** L'absence de vérification au moment de la compilation (type safety) signifie que les erreurs de passage de paramètres ou de types peuvent passer inaperçues jusqu'à l'exécution, provoquant des crashs ou des comportements indéfinis.

### La solution du SAMP SDK : Abstraction avec sécurité et performance

Le SAMP SDK aborde ces problèmes en fournissant une puissante couche d'abstraction en C++ :
- **RAII (Resource Acquisition Is Initialization) :** Gestion automatique de la mémoire dans l'AMX. `Amx_Scoped_Memory` garantit que la mémoire allouée est libérée.
- **Sécurité des types :** Conversion automatique et sécurisée des paramètres entre C++ et Pawn. Vous manipulez directement `int`, `float`, `std::string`.
- **Syntaxe concise et idiomatique :** Les macros et les templates offrent une API propre qui ressemble plus au C++ moderne qu'à l'API C traditionnelle.
- **Interception robuste :** Un moteur de hooking avancé permet l'interception transparente des rappels Pawn (`Plugin_Public`) et l'enregistrement dynamique des natives.
- **Haute performance :** Utilisation extensive du hachage au moment de la compilation (FNV1a), de la mise en cache des fonctions et des optimisations `thread_local` pour minimiser le surcoût des abstractions.

### Modèle Header-Only : Avantages et implications

Le SDK est composé exclusivement de fichiers d'en-tête (`.hpp`, `.h`).
- **Avantages :**
   - **Intégration simplifiée :** Il n'y a pas de bibliothèques à construire, lier ou distribuer. Il suffit d'inclure les en-têtes.
   - **Optimisations du compilateur :** Le compilateur a une visibilité complète du code du SDK et de votre plugin, permettant un inlining agressif et des optimisations au moment de la liaison, ce qui peut résulter en des binaires plus rapides.
- **Implications :**
   - **Temps de compilation :** Pour de très grands projets, la compilation peut prendre plus de temps en raison de l'inclusion répétée du code du SDK. Cela est atténué par les gardes d'inclusion et la nature "inclure uniquement ce qui est nécessaire" du C++.
   - **Macros d'implémentation :** La nécessité de la macro `SAMP_SDK_IMPLEMENTATION` est une conséquence du modèle header-only pour éviter les redéfinitions de symboles.

## 2. Configuration et environnement

### Exigences de compilation

- **Compilateur C++ :** Compatible avec C++14 ou supérieur (le SDK utilise des fonctionnalités de C++14, C++17 et C++20 pour des optimisations spécifiques, mais C++14 est le minimum).
   - GCC (version 7+)
   - Clang (version 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Architecture :** **x86 (32-bit)**. SA-MP fonctionne exclusivement sur cette architecture. Le SDK inclut des vérifications dans `platform.hpp` qui émettront des erreurs de compilation si une architecture incorrecte est détectée.
- **Système d'exploitation :** Windows ou Linux.

### Structure de fichiers recommandée

Pour plus de clarté et d'organisation, il est courant d'organiser le SDK dans un sous-dossier `samp-sdk`.

```
mon_plugin/
├── samp-sdk/
│   ├── // Autres fichiers du SDK
│   └── samp_sdk.hpp             // L'en-tête principal à inclure
│
├── src/
│   ├── main.cpp                  // Où SAMP_SDK_IMPLEMENTATION est défini
│   └── my_custom_logic.cpp       // Optionnel, pour organiser le code
│
└── CMakeLists.txt (ou .vcxproj, Makefile)
```

### Macros de configuration essentielles**

Définissez toujours ces macros *avant* d'inclure `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Objectif :** Indique au compilateur que ce fichier `.cpp` doit générer les implémentations des fonctions d'exportation du plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **Le SDK gère automatiquement l'exportation de ces fonctions, éliminant le besoin de fichiers `.def` (sous Windows) ou de déclarations `__attribute__((visibility("default")))` (sous Linux) pour ces fonctions.**
- **Impact technique :** Sans cette macro, l'éditeur de liens ne trouvera pas les exportations nécessaires et le serveur SA-MP ne pourra pas charger votre plugin.
- **Règle fondamentale :** **Définissez cette macro dans UN SEUL fichier `.cpp` de tout votre projet.** La définir dans plus d'un fichier entraînera une erreur de liaison de "symbole dupliqué".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // La macro fait en sorte que le SDK exporte automatiquement les fonctions nécessaires.
#include "samp-sdk/samp_sdk.hpp"

// ... votre code de plugin ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Objectif :** Active les fonctionnalités du SDK liées à l'interaction avec l'environnement de l'AMX (machine virtuelle Pawn).
- **Fonctionnalités activées :**
   - Déclaration et enregistrement de natives C++ à l'aide de `Plugin_Native`.
   - Rappels `OnAmxLoad(AMX* amx)` et `OnAmxUnload(AMX* amx)`.
   - La macro `Plugin_Call` pour invoquer les natives du plugin lui-même.
- **Impact technique :** Lorsque cette macro est définie, le SDK collecte automatiquement toutes vos `Plugin_Native`s. Dans la fonction `Supports()`, le flag `SUPPORTS_AMX_NATIVES` est automatiquement ajouté.
- **Flexibilité :** **Vous pouvez définir cette macro dans plusieurs fichiers `.cpp`**. Le système d'enregistrement statique du SDK (`Native_Registrar`) consolidera toutes les natives de différentes unités de compilation en une seule liste globale.

```cpp
// my_natives.cpp (peut être un fichier séparé de main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Uniquement pour activer Plugin_Native
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Objectif :** Active le rappel `OnProcessTick()`, qui est invoqué régulièrement par le serveur.
- **Impact technique :** Ajoute automatiquement le flag `SUPPORTS_PROCESS_TICK` à la fonction `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logique exécutée à chaque "tick" du serveur (ex: 20ms)
    // Attention aux opérations lourdes ici !
}
```

### Définitions et constantes de SA-MP (`samp_defs.hpp`)

Ce fichier fournit toutes les constantes et limites connues de SA-MP, telles que `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. Il est automatiquement inclus par `samp_sdk.hpp` et doit être utilisé pour garantir la compatibilité et la lisibilité du code.

## 3. Guide d'utilisation complet de l'API

### 3.1. Le cycle de vie du plugin

Les fonctions suivantes sont les points d'entrée et de sortie de votre plugin, exportées automatiquement par le SDK.

#### `bool OnLoad()`

- **Description :** Première fonction appelée par le serveur SA-MP après le chargement réussi de votre plugin en mémoire.
- **Utilisation :** Idéale pour initialiser tout système, charger des configurations, ouvrir des connexions à des bases de données ou charger des modules (`Plugin_Module`).
- **Retour :**
   - `true` : Le plugin a été initialisé avec succès et le chargement continue.
   - `false` : Le plugin a échoué à l'initialisation. Le chargement sera interrompu et le plugin sera déchargé.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initialisation de MyPlugin v1.0...");

    // Exemple : Charger un module (plus de détails dans la section 3.5)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Module de base de données chargé.")) {
        Samp_SDK::Log("ERREUR : Échec du chargement du module de base de données !");

        return false; // Annule le chargement du plugin principal
    }

    return true;
}
```

#### `void OnUnload()`

- **Description :** Dernière fonction appelée par le serveur SA-MP avant de décharger votre plugin de la mémoire.
- **Utilisation :** Idéale pour nettoyer les ressources, fermer les connexions, sauvegarder les états et s'assurer qu'aucune ressource n'est fuite. Le SDK gère automatiquement le déchargement des modules (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin déchargé. Libération des ressources...");
    // Aucune action manuelle n'est nécessaire pour les modules chargés via Plugin_Module ;
    // le SDK s'en charge.
}
```

#### `unsigned int GetSupportFlags()`

- **Description :** Informe le serveur SA-MP des fonctionnalités que votre plugin prend en charge et souhaite utiliser.
- **Utilisation :** **Retournez toujours `SUPPORTS_VERSION` (ou `SAMP_PLUGIN_VERSION`).** Les autres flags (`SUPPORTS_AMX_NATIVES`, `SUPPORTS_PROCESS_TICK`) sont ajoutés automatiquement par le SDK si les macros `SAMP_SDK_WANT_AMX_EVENTS` et `SAMP_SDK_WANT_PROCESS_TICK` sont définies. Cela simplifie la maintenance et évite les erreurs.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // Le SDK ajoute automatiquement les drapeaux nécessaires.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requis :** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description :** Appelé chaque fois qu'un nouveau script Pawn (un Gamemode ou Filterscript) est chargé et initialisé sur le serveur.
- **Utilisation :** Si vous avez besoin d'une logique spécifique pour chaque script AMX, comme enregistrer des natives personnalisées (bien que `Plugin_Native` le fasse automatiquement), ou initialiser des données spécifiques par script.

```cpp
// main.cpp (avec SAMP_SDK_WANT_AMX_EVENTS défini)
void OnAmxLoad(AMX* amx) {
    // amx représente la nouvelle instance du script chargé.
    // Vous pouvez, par exemple, appeler une public spécifique dans ce script :
    // Pawn_Public_OnAmx("OnMyPluginLoaded", amx); // Exemple hypothétique d'une API plus avancée.
    Samp_SDK::Log("Script AMX chargé : %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Requis :** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description :** Appelé lorsqu'un script Pawn est déchargé du serveur.
- **Utilisation :** Pour nettoyer toutes les ressources spécifiques que vous avez allouées ou associées à cet `AMX*` particulier.

```cpp
// main.cpp (avec SAMP_SDK_WANT_AMX_EVENTS défini)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX déchargé : %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requis :** `SAMP_SDK_WANT_PROCESS_TICK`
- **Description :** Appelé de manière répétée à chaque "tick" du serveur (généralement 20 fois par seconde, ou toutes les 50ms).
- **Utilisation :** Pour la logique de fond continue, les minuteurs, les mises à jour d'état qui ne dépendent pas des événements du joueur ou la synchronisation des données.
- **Attention :** Évitez les opérations bloquantes ou gourmandes en calcul ici, car elles peuvent provoquer un lag sur le serveur.

```cpp
// main.cpp (avec SAMP_SDK_WANT_PROCESS_TICK défini)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Toutes les 10 secondes (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Serveur actif depuis %d secondes.", tick_count / 20);
}
```

### 3.2. `Plugin_Public` : Intercepter les événements Pawn

La macro `Plugin_Public` est le pont principal pour recevoir les rappels Pawn dans votre code C++.

#### Syntaxe et déclaration

- `Plugin_Public(NomDeLaPublic, Type1 Param1, Type2 Param2, ...)`
- Le nom de la fonction C++ que vous déclarez **doit être le même** que le rappel Pawn (ex: `OnPlayerConnect`).
- Les types de paramètres C++ (`int`, `float`, `std::string`) sont automatiquement convertis par le SDK.

```cpp
// Intercepte OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    // ...
}
```

#### Marshalling automatique des paramètres

Le SDK gère automatiquement la lecture de la `cell stack` de l'AMX et la conversion vers les types C++ spécifiés :
- `int` : Converti directement depuis `cell`.
- `float` : Converti depuis `cell` en utilisant `amx::AMX_CTOF`.
- `std::string` : Le SDK lit l'adresse de la chaîne dans l'AMX, alloue un `std::string` en C++ et copie le contenu.

#### Contrôle de flux : `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

La valeur retournée par votre fonction `Plugin_Public` est cruciale et détermine le flux d'exécution du rappel :
- `return PLUGIN_PUBLIC_CONTINUE;` (valeur `1`) : Indique que l'exécution du rappel doit **continuer**. S'il y a d'autres plugins qui interceptent également ce rappel, ils seront appelés. Ensuite, le `public` original dans le script Pawn sera invoqué.
- `return PLUGIN_PUBLIC_STOP;` (valeur `0`) : Indique que l'exécution du rappel doit être **interrompue**. Aucun autre plugin ou le `public` original dans le script Pawn ne sera invoqué pour cet événement. C'est idéal pour implémenter un système qui "écrase" ou "bloque" un comportement par défaut de SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Gèle le joueur
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Joueur %d gelé.", playerid));

        return PLUGIN_PUBLIC_STOP; // Empêche la commande d'être traitée par d'autres scripts.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Permet aux autres commandes d'être traitées.
}
```

### 3.3. `Plugin_Native` : Créer des fonctions natives en C++

`Plugin_Native` vous permet d'étendre les fonctionnalités de Pawn avec du code C++ haute performance.

#### Syntaxe et signature fixe

- `Plugin_Native(NomDeLaNative, AMX* amx, cell* params)`
- La fonction C++ doit avoir exactement cette signature : `cell NomDeLaNative(AMX* amx, cell* params)`.
- `NomDeLaNative` est le nom que les scripts Pawn utiliseront.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implémentation ...
    return 0;
}
```

#### Enregistrement automatique des natives

> [!NOTE]
> Vous **n'avez pas besoin** d'appeler `amx_Register` manuellement. Le SDK détecte toutes vos `Plugin_Native`s (dans n'importe quel fichier `.cpp` avec `SAMP_SDK_WANT_AMX_EVENTS`) et les enregistre automatiquement dans chaque script AMX chargé (`OnAmxLoad`).

#### Extraction de paramètres : `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Description :** Helper plus simple pour extraire plusieurs paramètres séquentiellement.
- **Utilisation :** `Register_Parameters(variable1, variable2, ...)`
- **Limitations :** Pour les paramètres d'entrée. Ne gère pas les paramètres optionnels ou l'accès par index.
- **Types supportés :** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extrait les 3 paramètres
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (API Complète : `Get`, `Get_REF`, `Set_REF`)

- **Description :** Une classe wrapper qui fournit une interface orientée objet pour accéder aux paramètres d'une native. Plus puissante pour les scénarios complexes.
- **Construction :** `Native_Params p(amx, params);`

###### `p.Count()`

- **Description :** Retourne le nombre de paramètres passés à la native.
- **Utilisation :** Essentiel pour gérer les paramètres optionnels.

###### `p.Get<T>(size_t index)`

- **Description :** Extrait un paramètre d'entrée par index et le convertit au type `T`.
- **Types supportés :** `int`, `float`, `std::string`.

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

    // Obtient les valeurs des références (le Pawn a passé des adresses)
    p.Get_REF(1, health); // Lit la valeur de Float:health
    p.Get_REF(2, money);   // Lit la valeur de money
    
    Samp_SDK::Log("Joueur %d, Santé : %.1f, Argent : %d", playerid, health, money);
    
    // Maintenant, modifiez-les
    health = 50.0f;
    money += 100;
    
    // Et les réécrit en mémoire Pawn
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
// Retourne un bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    int playerid = p.Get<int>(0);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Retourne un float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Retourne 100.0f
}
```

### 3.4. Macros `Pawn_*` : Appeler des fonctions Pawn depuis le C++

Ces macros sont l'inverse de `Plugin_Public` et `Plugin_Native` : elles permettent à votre code C++ d'invoquer des fonctions Pawn.

#### `Pawn_Native(NomDeLaNative, ...)`

- **Objectif :** La méthode recommandée pour appeler les fonctions natives de SA-MP (ou d'autres plugins) depuis le C++.
- **Mécanisme :** Recherche le pointeur de la native dans le cache interne du SDK (rempli par `Amx_Register_Detour`). Si trouvé, exécute la native dans un environnement `Amx_Sandbox` (une instance AMX fausse et isolée).
- **Performance :** La plus efficace, car elle évite la recherche coûteuse de `publics` et interagit directement avec le pointeur de la native.

#### `Pawn_Public(NomDeLaPublic, ...)`

- **Objectif :** Appelle une fonction publique spécifique dans un script Pawn.
- **Mécanisme :** Parcourt les instances `AMX*` gérées par `Amx_Manager`, recherche la `public` par son nom et l'exécute.
- **Performance :** Moins efficace que `Pawn_Native` en raison de la recherche et de l'exécution réelle de `amx_Exec`. Généralement, les `publics` sont plus lentes que les `natives`.
- **Utilisation :** Idéale pour invoquer des événements personnalisés dans votre Gamemode/Filterscripts qui ne sont pas des natives.

#### `Pawn(NomDeLaFonction, ...)`

- **Objectif :** Une macro de commodité qui tente de deviner si la fonction est une native ou une publique.
- **Mécanisme :** D'abord, tente d'appeler comme `Pawn_Native`. Si cela échoue (la native n'est pas trouvée), tente d'appeler comme `Pawn_Public`.
- **Performance :** Peut être un peu plus lente que `Pawn_Native` si la fonction est native, en raison de la double tentative de recherche. Pour les `publics`, la performance est la même que `Pawn_Public`.
- **Utilisation :** Pour les fonctions où vous n'êtes pas sûr si elles sont natives ou publiques, ou pour éviter le code répétitif de tenter l'une puis l'autre.

#### Syntaxe et conventions

- **Nom de la fonction :** Utilisez toujours le nom de la fonction Pawn **directement, sans guillemets**. Le SDK le convertira en chaîne de caractères en interne.
- **Paramètres :** Passez les paramètres C++ directement.

```cpp
// Correct :
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Incorrect (mais fonctionnerait techniquement en raison du hachage, à éviter) :
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling des paramètres d'entrée

Le SDK convertit vos types C++ au format `cell` de l'AMX, gérant la mémoire si nécessaire :
-   `int`, `bool`, `long`, `enum` -> `cell`
-   `float`, `double` -> `cell` (en utilisant `amx::AMX_FTOC`)
-   `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (alloue de la mémoire sur l'AMX, copie la chaîne et passe l'adresse `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling des paramètres de sortie (Références : `int&`, `float&`, `std::string&`)

Ceci est une fonctionnalité clé pour la commodité et la sécurité. Pour les fonctions Pawn qui attendent un pointeur (référence), le SDK automatise tout le processus d'allocation/libération de mémoire et de copie des données.

- **Comment utiliser :** Il suffit de passer votre variable par référence (`&`).
- **Mécanisme :** Le SDK alloue de la mémoire sur le tas de l'AMX, passe l'adresse AMX à la fonction Pawn, attend que la fonction Pawn remplisse cette adresse, lit la valeur en retour et libère la mémoire de l'AMX. Le tout de manière transparente.
- **Avec `std::string&` :** Le SDK alloue un tampon standard (256 cellules) sur l'AMX pour la chaîne.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Localisation de %s (ID:%d) : Pos(%.2f, %.2f, %.2f) Intérieur:%d Monde:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### L'objet `Callback_Result` : Analyse complète

Tous les appels `Pawn_*` retournent un objet `Callback_Result`. Cet objet est un wrapper sécurisé pour le résultat de l'appel Pawn.

- `Callback_Result() noexcept` : Constructeur par défaut, indique un échec (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept` : Constructeur pour succès ou échec avec valeur.
- `explicit operator bool() const` : Permet d'utiliser `if (result)` pour vérifier si l'appel a réussi.
- `operator cell() const` : Permet de convertir le résultat en `cell` pour obtenir la valeur.
- `float As_Float() const` : Commodité pour obtenir le résultat en tant que `float`.
- `cell Value() const` : Retourne la valeur `cell` brute.
- `bool Success() const` : Retourne `true` si l'appel Pawn a réussi.
- `int Get_Amx_Error() const` : Retourne le code d'erreur de l'AMX si l'appel a échoué (0 pour succès).

```cpp
// Exemple : Obtenir la vie d'un joueur.
// La native GetPlayerHealth(playerid, &Float:health) attend un playerid et une référence à la vie.
int playerid = 0; // Exemple d'ID de joueur
float player_health = 0.0f;

// Nous appelons GetPlayerHealth, en passant playerid et player_health par référence.
// Le SDK s'occupera du marshalling pour le paramètre de sortie 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Vérifie si l'appel a réussi (operator bool)
    // La valeur retournée par result.As_Float() ou result (operator cell)
    // serait la valeur de retour de la *native*, pas le paramètre de sortie.
    // La valeur de la vie a déjà été mise à jour dans 'player_health' grâce au marshalling du paramètre de sortie.
    Samp_SDK::Log("Joueur %d a %.1f de vie.", playerid, player_health);
} else {
    // L'appel a échoué, peut-être que le joueur n'existe pas ou que la native n'a pas été trouvée.
    Samp_SDK::Log("Erreur lors de l'obtention de la vie du joueur %d. Code AMX : %d", playerid, result.Get_Amx_Error());
}

// Pour les natives qui retournent une valeur et utilisent des paramètres de sortie (moins courant, mais possible),
// vous utiliseriez les deux :
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param est déjà mis à jour
// }
```

#### **3.5. `Plugin_Module` : Gestion des Modules Dynamiques**

La macro `Plugin_Module` permet à votre plugin d'agir comme un "chargeur" pour d'autres plugins, créant une architecture modulaire et extensible. Un module chargé de cette manière est traité comme un plugin de première classe, avec son propre cycle de vie d'événements géré par le plugin hôte.

#### Syntaxe et Objectif

- `Plugin_Module(const char* nome_do_arquivo_base, const char* diretorio_do_modulo, const char* mensagem_sucesso_opcional)`
- `nome_do_arquivo_base` : Le nom *de base* du fichier du module, **sans l'extension** (par exemple, pour `my_module.dll` ou `my_module.so`, utilisez `"my_module"`). Le SDK ajoutera automatiquement l'extension `.dll` ou `.so` appropriée.
- `diretorio_do_modulo` : Le chemin du répertoire où se trouve le fichier du module (par exemple, `"plugins/my_custom_modules"`). **Ne pas inclure le nom du fichier ici.** Le SDK concaténera le chemin complet (`diretorio_do_modulo/nome_do_arquivo_base.ext`).
- `mensagem_sucesso_opcional` : Un message facultatif à enregistrer dans la console du serveur si le module est chargé avec succès.

```cpp
// main.cpp, dans OnLoad()

// Charge le module 'core_logic.dll' (ou 'core_logic.so')
// situé dans le dossier 'modules/custom/' du serveur.
if (!Plugin_Module("core_logic", "modules/custom", "Module de Logique de Base chargé avec succès !"))
    return (Samp_SDK::Log("ERREUR FATALE : Échec du chargement du module 'core_logic' !"), false);

// Charge le module 'admin_system.dll' (ou 'admin_system.so')
// situé directement dans le dossier 'plugins/' du serveur.
if (!Plugin_Module("admin_system", "plugins", "Module d'Administration activé."))
    Samp_SDK::Log("AVERTISSEMENT : Le module d'Administration n'a pas pu être chargé.");
```

#### Cycle de Vie d'un Module

Un module doit exporter les fonctions `Load`, `Unload` et `Supports`, comme un plugin normal. Le SDK gère le cycle de vie du module de la manière suivante :

- **Chargement :** Lorsque `Plugin_Module` est appelé, le SDK :
   1. Construit le chemin complet du fichier (par exemple, `modules/custom/core_logic.dll`).
   2. Utilise `Dynamic_Library` (`LoadLibrary`/`dlopen`) pour charger le binaire.
   3. **Obtient les pointeurs pour TOUTES les fonctions du cycle de vie du module :**
      - **Obligatoires :** `Load`, `Unload`, `Supports`. Si l'une d'elles manque, le chargement du module échoue.
      - **Facultatives :** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Appelle la fonction `Load` du module, en passant `ppData` du plugin principal.
   5. Si `Load` retourne `true`, le module est ajouté à la liste interne des modules chargés.

- **Transfert d'Événements :** Le plugin hôte **transfère automatiquement** les événements à tous les modules chargés.
 > [!IMPORTANT]
 > Pour que les événements soient correctement transférés, le **plugin hôte** (celui qui appelle `Plugin_Module`) doit être configuré pour recevoir ces événements.
 > - Pour que `AmxLoad` et `AmxUnload` fonctionnent dans les modules, le plugin hôte doit définir la macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Pour que `ProcessTick` fonctionne dans les modules, le plugin hôte doit définir la macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Déchargement :** Lors de `OnUnload` du plugin principal, le SDK décharge tous les modules chargés via `Plugin_Module`. Cela se fait dans **l'ordre inverse** du chargement (le dernier module chargé est le premier à être déchargé), ce qui est crucial pour gérer les dépendances et assurer un nettoyage correct des ressources.

#### Avantages de la Modularisation

- **Organisation du Code :** Divisez les gros plugins en composants plus petits et gérables, chacun dans son propre fichier de module.
- **Réutilisabilité :** Créez des modules génériques (par exemple, un module de base de données, un module de système de journalisation avancé) qui peuvent être utilisés par différents plugins, favorisant la réutilisation du code.
- **Composants Indépendants :** Créez des modules qui sont **entièrement pilotés par des événements et indépendants**. Un module peut avoir ses propres `Plugin_Native`s, intercepter des `Plugin_Public`s et avoir sa propre logique `OnProcessTick`, fonctionnant comme un plugin autonome, mais chargé par un hôte.
- **Mises à Jour Dynamiques :** Dans des scénarios contrôlés, permet de mettre à jour des parties de votre système (en remplaçant un fichier de module `.dll` ou `.so`) sans avoir besoin de recompiler et redémarrer le plugin principal ou l'ensemble du serveur (bien que cela nécessite une gestion stricte des versions et de la compatibilité).

### 3.6. `Plugin_Call` : Appeler les natives internes du plugin

Utilisez `Plugin_Call` pour invoquer une `Plugin_Native` définie **à l'intérieur de votre propre plugin**.

#### Syntaxe et avantages de performance

- `Plugin_Call(NomDeLaNative, Param1, Param2, ...)`
- **Avantage :** Évite la surcharge de la recherche de la native dans le tableau des natives de l'AMX. Le SDK maintient une carte directe des hachages de noms aux pointeurs de fonction pour ses propres natives, ce qui en fait le moyen le plus rapide de les appeler en interne.
- **Requis :** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logique pour vérifier le niveau
    return (playerid % 2 == 0) ? 1 : 0; // Exemple : niveau pair pour les IDs pairs
}

void CheckAllPlayersLevel() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Appelle votre propre native
                Samp_SDK::Log("Joueur %d est à un niveau élevé !", i);
        }
    }
}
```

### **3.7. Fonctions utilitaires du SDK**

#### `Samp_SDK::Log(const char* format, ...)`

- **Description :** Imprime des messages dans la console du serveur et dans le fichier `server_log.txt`. Un wrapper sécurisé pour `logprintf`.
- **Utilisation :** Pour le débogage, les messages d'état et les erreurs.
- **Mécanisme :** En interne, le SDK obtient le pointeur de `logprintf` via `ppData[PLUGIN_DATA_LOGPRINTF]`. La fonction gère le formatage de la chaîne de manière sécurisée.

```cpp
// N'importe où dans votre plugin
Samp_SDK::Log("Le plugin a été initialisé avec une valeur %d et une chaîne '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Recommandé)

- **Description :** Formate une chaîne de caractères de manière sécurisée (similaire à `sprintf`) et retourne un `std::string`. C'est la manière **recommandée et la plus idiomatique** de formater des chaînes pour une utilisation au sein de votre plugin.
- **Utilisation :** Idéal pour construire des messages formatés avant de les passer à `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, ou pour tout autre besoin de chaîne de caractères dans votre code C++.
- **Mécanisme :** En interne, `Plugin_Format` est une macro qui appelle `Samp_SDK::Format`. Il utilise `vsnprintf` pour déterminer la taille exacte de la chaîne formatée et alloue un `std::string` avec une capacité suffisante, évitant les débordements de tampon.

```cpp
int playerid = 0; // Exemple d'ID
int health = 50;
std::string status_message = Plugin_Format("Joueur %d, votre vie actuelle est %d.", playerid, health); // Utilisation de la macro Plugin_Format
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, status_message);

// Peut également être utilisé pour les logs internes
Samp_SDK::Log(Plugin_Format("DEBUG: Traitement du statut pour l'ID %d", playerid).c_str());
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Détail d'implémentation)

- **Description :** La fonction d'implémentation sous-jacente pour le formatage de chaînes, située dans l'espace de noms `Samp_SDK`.
- **Utilisation :** Généralement, elle n'est pas appelée directement par l'utilisateur. La macro `Plugin_Format` est fournie comme une commodité pour cette fonction, s'alignant sur la convention de nommage des autres macros du SDK (`Plugin_Public`, `Plugin_Native`). Vous ne l'appelleriez directement que si vous vouliez éviter la macro `Plugin_Format` pour une raison spécifique.

```cpp
// Exemple de fonctionnement de Samp_SDK::Format, mais préférez Plugin_Format
std::string raw_status = Samp_SDK::Format("Uniquement pour usage interne : %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Description :** Convertit une adresse de chaîne AMX (`cell amx_addr`) en un `std::string` C++.
- **Utilisation :** Principalement dans `Plugin_Native` lorsque vous devez accéder à des chaînes qui ne sont pas automatiquement converties par `Register_Parameters` ou `Native_Params` (ex: si le paramètre Pawn est une `const` `string` et n'a pas été déclaré comme `std::string` dans votre `Plugin_Native` ou `Plugin_Public` pour le Marshalling automatique).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Obtient l'adresse de la chaîne dans l'AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("Chaîne de l'AMX : %s", cpp_string.c_str());

    return 1;
}
```

## 4. **Anatomie interne et architecture du SDK**

Cette section dévoile les mécanismes sous-jacents du SAMP SDK, explorant son architecture, les composants clés et la manière dont ils interagissent pour fournir l'abstraction de haut niveau. Une compréhension approfondie de ces rouages permet au développeur d'optimiser l'utilisation du SDK, de déboguer des problèmes complexes et même d'étendre ses fonctionnalités.

### 4.1. `core.hpp` : La fondation minimaliste

Le `Samp_SDK::Core` est un `singleton` qui sert de point d'accès initial et centralisé aux données de bas niveau fournies par l'environnement du plugin SA-MP. Sa principale responsabilité est d'encapsuler et d'exposer les fonctionnalités essentielles.

- **`Samp_SDK::Core::Instance()`** :
   - **Description :** Retourne l'unique instance globale de la classe `Core`. C'est un modèle de conception `singleton` pour garantir que l'accès aux données du plugin (`ppData`) est cohérent et centralisé.
   - **Mécanisme :** L'instance est initialisée une seule fois lorsque `Core::Instance().Load(ppData)` est appelé dans la fonction `Load()` de votre plugin.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`** :
   - **Description :** Permet un accès sécurisé et indexé aux pointeurs de fonction de l'API AMX. Le tableau `pAMXFunctions` (reçu via `ppData[PLUGIN_DATA_AMX_EXPORTS]`) contient les adresses de fonctions critiques comme `amx_Exec`, `amx_Register`, etc.
   - **Impact :** Au lieu d'utiliser `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, le SDK offre des wrappers type-safe dans l'espace de noms `amx::` (ex: `amx::Exec(...)`), rendant le code plus lisible et moins sujet aux erreurs de cast.
   - **Exemple interne (`amx_api.hpp`) :**
      ```cpp
      // Extrait simplifié de amx_api.hpp
      namespace amx {
          template <typename Func, int Index, typename... Args>
          inline auto Call(Args... args) -> decltype(std::declval<Func>()(args...)) {
              using Return_Type = decltype(std::declval<Func>()(args...));
              auto func_ptr = reinterpret_cast<Func>(Core::Instance().Get_AMX_Export(Index));

              if (SAMP_SDK_UNLIKELY(!func_ptr))
                  return (Samp_SDK::Log("[SAMP SDK] Fatal: Tentative d'appeler l'export AMX à l'index %d, mais pAMXFunctions n'a pas été chargé !", Index),
                  Samp_SDK::amx::Detail::Amx_Call_Error_Handler<Return_Type>(typename std::is_pointer<Return_Type>::type{}));

              return func_ptr(args...);
          }

          inline int Exec(AMX* amx, cell* retval, int index) {
              return Call<Exec_t, PLUGIN_AMX_EXPORT_Exec>(amx, retval, index);
          }
      } // namespace amx
      ```

- **`logprintf_ptr`** :
   - **Description :** Un pointeur vers la fonction `logprintf` de SA-MP, qui est l'interface standard pour imprimer des messages dans la console du serveur et dans `server_log.txt`.
   - **Mécanisme :** Le `Samp_SDK::Log` est un wrapper sécurisé qui utilise ce pointeur, garantissant que vos messages sont affichés correctement dans l'environnement SA-MP.

### **4.2. `platform.hpp` et `version.hpp` : Compatibilité et métadonnées**

Ces en-têtes sont la base de la portabilité et de l'optimisation du SDK, l'adaptant à différents environnements de compilation et tirant parti des fonctionnalités spécifiques du C++ moderne.

- **Détection de plateforme et d'architecture :**
   - **Mécanisme :** Utilise des macros de préprocesseur (`#if defined(WIN32)`, `#if defined(__linux__)`, etc.) pour identifier le système d'exploitation.
   - **Vérification d'architecture :** Contient `static_assert` ou `#error` pour garantir que le plugin est compilé pour x86 (32 bits), une exigence critique pour la compatibilité avec SA-MP et le mécanisme de hooking.
   - **Gestion de l'exportation des symboles :**
      - `SAMP_SDK_EXPORT` : Une macro définie dans `platform.hpp` qui s'étend à `extern "C"` et, sous Linux, ajoute `__attribute__((visibility("default")))`. Sous Windows, elle garantit simplement `extern "C"` car le SDK utilise `pragma comment(linker, "/EXPORT:...")` (pour MSVC) ou la norme MinGW pour exporter les fonctions principales.
      - Cela garantit que les fonctions du cycle de vie du plugin (`Supports`, `Load`, `Unload`, etc.) sont correctement exportées de votre DLL/SO, quel que soit l'environnement de compilation, **sans avoir besoin de fichiers `.def` ou d'ajouter `__attribute__((visibility("default")))` manuellement** dans votre implémentation.
   - **Exemple (`platform.hpp` - fragment pertinent) :**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // Pour MSVC, l'exportation est gérée par des commandes pragma linker
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // Pour GCC/Clang sous Linux, nous utilisons l'attribut de visibilité
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... autres définitions ...
      ```
   - **Exemple (`samp_sdk.hpp` - fragment pertinent de l'implémentation) :**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // Sous Windows (MSVC), nous utilisons pragma comment pour exporter les fonctions.
          // Cela élimine le besoin d'un fichier .def.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... autres exports ...
      #endif

      // Implémentation des fonctions exportées
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... autres fonctions ...
      #endif
      ```

- **Macros d'optimisation et de prédiction de branchement :**
   - `SAMP_SDK_FORCE_INLINE` :
      - **Mécanisme :** `__forceinline` (MSVC) ou `__attribute__((always_inline)) inline` (GCC/Clang). Suggère fortement au compilateur d'insérer le corps de la fonction directement à l'emplacement de l'appel, éliminant le surcoût d'un appel de fonction réel.
      - **Utilisation :** Appliqué aux fonctions petites et critiques pour les performances au sein du SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)` :
      - **Mécanisme :** `[[likely]]` / `[[unlikely]]` (C++20) ou `__builtin_expect` (GCC/Clang). Indications au compilateur sur la branche d'un `if/else` la plus susceptible d'être prise.
      - **Impact :** Aide le compilateur à générer un code plus efficace pour la prédiction de branchement, réduisant la latence du CPU.
      - **Exemple (`platform.hpp`) :**
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

- **Définitions C++ standard (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`) :**
   - **Mécanisme :** Macros définies en fonction de la valeur de `__cplusplus` et `_MSVC_LANG`.
   - **Utilisation :** Permettent au SDK d'utiliser des fonctionnalités C++ plus récentes (comme `std::apply` et `if constexpr` de C++17, ou `std::is_same_v` de C++17) lorsqu'elles sont disponibles, tout en maintenant la compatibilité avec des standards plus anciens.
   - **Exemple (`version.hpp` - utilisation de `if constexpr`) :**
      ```cpp
      // Extrait simplifié de public_dispatcher.hpp
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

### 4.3. `function_hook.hpp` : Le moteur d'interception x86

Cet en-tête définit le mécanisme de bas niveau pour réaliser des hooks (interceptions) de fonctions, ce qui est fondamental pour le fonctionnement du SDK. Il est strictement dépendant de l'architecture x86 (32 bits).

- **`X86_Detour`** :
   - **Description :** Une classe qui encapsule la logique de surcharge du début d'une fonction en mémoire avec une instruction de saut vers une fonction de déroutement.
   - **`JUMP_INSTRUCTION_SIZE = 5`** :
      - **Mécanisme :** En x86, l'instruction de saut (`JMP`) relative a généralement 5 octets : `0xE9` (opcode pour JMP near, relative) suivi de 4 octets qui représentent le décalage (offset) de l'adresse de la cible par rapport à l'instruction suivante.
      - **Exemple d'instruction :** `E9 XX XX XX XX` (où `XX` sont les octets du décalage).
   - **`Apply(void* target, void* detour)`** :
      - **Action :** Installe le hook. Premièrement, stocke les `JUMP_INSTRUCTION_SIZE` octets originaux de la fonction `target` (`original_bytes_`). Ensuite, calcule l'adresse relative du `detour` par rapport au `target` et écrase le début de `target` avec l'instruction `JMP`.
      - **Exemple de calcul de l'adresse relative :**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Adresse du déroutement - (Adresse de la cible + Taille de l'instruction JMP)
         ```
   - **`Revert()`** :
      - **Action :** Désinstalle le hook, restaurant les `original_bytes_` dans la fonction `target`.
   - **`Unprotect_Memory(void* address, size_t size)`** :
      - **Mécanisme :** Sous Windows, utilise `VirtualProtect` ; sous Linux, `mprotect`. Ces appels système modifient les permissions de la page de mémoire où réside la fonction en `EXECUTE_READWRITE` (Windows) ou `PROT_WRITE | PROT_EXEC` (Linux), permettant de modifier le code au moment de l'exécution.
      - **Exemple (`Unprotect_Memory`) :**
         ```cpp
         // Extrait simplifié de function_hook.hpp
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
      - **Mécanisme de sécurité (Garde de récursion) :** Cette fonction est critique pour éviter les boucles infinies lorsque le déroutement doit appeler la fonction originale. Elle **désinstalle temporairement le hook (`detour_.Revert()`)**, appelle la fonction originale (`Get_Original()(args...)`), puis **réinstalle le hook (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`** : Un compteur qui garantit que le hook n'est réinstallé que lorsque l'appel original de plus haut niveau est terminé, permettant des appels récursifs sécurisés de la fonction originale (si la fonction originale est récursive, par exemple). Le `thread_local` garantit que le `recursion_guard` est isolé pour chaque thread, important dans les environnements multithread.
      - **Exemple (`Call_Original` avec Scope_Guard) :**
         ```cpp
         // Extrait simplifié de function_hook.hpp
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

### 4.4. `interceptor_manager.hpp` : Le contrôleur de hooks de l'AMX

Ce `singleton` est le centre nerveux de l'interaction du SDK avec la machine virtuelle AMX de SA-MP. Il coordonne l'installation des hooks fournis par `function_hook.hpp` sur les fonctions de l'API AMX exposées par le serveur, redirigeant le flux d'exécution vers la logique du SDK.

- **`Activate()` / `Deactivate()`** :
   - **Description :** Méthodes publiques pour installer et désinstaller tous les hooks nécessaires. Appelé dans `OnLoad()` et `OnUnload()` de votre plugin, respectivement.
   - **Mécanisme :** Obtient les pointeurs des fonctions AMX (comme `amx_Register`, `amx_Exec`, etc.) en utilisant `Core::Instance().Get_AMX_Export(...)` et installe les déviations.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`** :
   - **Fonction Hooked :** `amx_Register`
   - **Objectif :** Intercepte l'enregistrement de *toutes* les natives (par SA-MP, d'autres plugins ou le gamemode).
   - **Action :** Appelle `Interceptor_Manager::Instance().Cache_Natives()` pour stocker les pointeurs et les noms des natives dans un cache interne.
   - **Impact :** Ce cache est fondamental pour la performance de `Pawn_Native`, permettant une recherche extrêmement rapide du pointeur de la native au lieu d'une recherche coûteuse dans l'AMX.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`** :
   - **Fonction Hooked :** `amx_Exec`
   - **Objectif :** **C'est le hook le plus critique.** Il intercepte *toute* exécution de code dans l'AMX, y compris l'appel de `publics` du Pawn.
   - **Mécanisme d'interception de `Plugin_Public` :**
      1. Lorsque `amx_Exec` est appelé pour une `public` (ou `AMX_EXEC_MAIN`), le `Amx_Exec_Detour` est exécuté.
      2. Il obtient le nom de la `public` (en utilisant `Get_Public_Name_By_Index` ou `tl_public_name`).
      3. Interroge le `Public_Dispatcher::Instance().Dispatch()` pour vérifier s'il y a des gestionnaires C++ enregistrés pour ce nom.
      4. S'il y a des gestionnaires, il les exécute. Le `Public_Dispatcher` gère le `marshalling` des paramètres de l'AMX vers les types C++ corrects.
      5. En fonction de la valeur de retour du `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), il décide s'il appelle l'`amx_Exec` original (`Get_Amx_Exec_Hook().Call_Original(...)`) ou s'il met fin à l'exécution du `public` Pawn.
      6. **Manipulation de la pile :** Si l'exécution du `public` Pawn est interrompue (`PLUGIN_PUBLIC_STOP`), le `Amx_Exec_Detour` corrige la pile de l'AMX (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) pour éviter les incohérences.
   - **Exemple (`Amx_Exec_Detour`) :**
      ```cpp
      // Extrait simplifié de interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          // ... logique pour déterminer le nom de la public ...
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

- **`int SAMP_SDK_AMX_API Amx_Find_Public_Detour(...)`** :
   - **Fonction Hooked :** `amx_FindPublic`
   - **Objectif :** Intercepte la recherche de `publics` par nom.
   - **Mécanisme des "Ghost Publics" :** Si `amx_FindPublic` original ne trouve pas de `public` dans le Pawn, mais que le `Public_Dispatcher` a un gestionnaire C++ enregistré pour ce nom, ce hook retourne `AMX_ERR_NONE` et un `index` spécial (`PLUGIN_EXEC_GHOST_PUBLIC`). Cela fait en sorte que l'API de SA-MP "pense" que la `public` existe, permettant à l'appel `amx_Exec` suivant (pour cet index spécial) d'être intercepté par `Amx_Exec_Detour`, qui redirige ensuite vers le gestionnaire C++.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`** : Utilisé pour passer le nom du `public` à l'`Amx_Exec_Detour` lorsqu'un "public fantôme" est détecté, car l'`amx_Exec` ne reçoit que l'index, pas le nom.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`** :
   - **Fonctions Hooked :** `amx_Init` / `amx_Cleanup`
   - **Objectif :** Gérer la liste des instances `AMX*` actives.
   - **Action :** `Amx_Init_Detour` appelle `Amx_Manager::Instance().Add_Amx()`, et `Amx_Cleanup_Detour` appelle `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp` : Gestion des instances `AMX*`

Ce `singleton` maintient un registre dynamique de toutes les machines virtuelles AMX actuellement chargées sur le serveur. Il est essentiel pour les fonctions qui doivent interagir avec "tous les scripts" ou trouver un script spécifique.

- **`std::vector<AMX*> loaded_amx_`** :
   - **Description :** Une liste de pointeurs vers toutes les instances `AMX*` qui ont été initialisées (gamemode et filterscripts).
   - **Gestion :** Remplie par les hooks `Amx_Init_Detour` et vidée par `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)** :
   - **Objectif :** Protège `loaded_amx_` contre les accès concurrents dans des environnements multithreadés (bien que SA-MP soit majoritairement monothread, c'est une bonne pratique de sécurité). `std::shared_mutex` permet plusieurs lecteurs simultanément, mais un seul écrivain.
- **`std::atomic<uint32_t> generation_`** :
   - **Objectif :** Un compteur qui s'incrémente chaque fois qu'une AMX est ajoutée ou supprimée.
   - **Utilisation :** Il est utilisé par le `Caller_Cache` dans `callbacks.hpp` pour détecter quand la liste des AMX a changé, invalidant les caches de recherche de `publics` et garantissant que les appels `Pawn_Public` fonctionnent toujours avec des informations à jour. Cela optimise les performances en évitant les recherches répétitives dans un état inchangé.
- **`AMX* Find_Public(const char* name, int& index)`** :
   - **Description :** Parcourt `loaded_amx_` (du plus récent au plus ancien, ce qui place généralement le gamemode ou le filterscript le plus pertinent en premier) pour trouver la `public` avec le nom spécifié.
   - **Mécanisme :** Utilise `amx::Find_Public` pour chaque instance `AMX*`.
   - **Impact :** C'est la base de `Pawn_Public`.

### 4.6. `public_dispatcher.hpp` : Le routeur de Callbacks `Plugin_Public`

Ce `singleton` est le composant qui mappe les noms de `publics` de Pawn à vos fonctions C++ `Plugin_Public`.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`** :
   - **Clé :** Le hachage FNV1a du nom de la `public` (ex: `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Valeur :** Un `std::vector` de `std::function<cell(AMX*)>`, où chaque `std::function` est un gestionnaire C++ enregistré pour cette `public`.
   - **Mécanisme :** Le `std::vector` permet à plusieurs `Plugin_Public`s d'être enregistrés pour le même rappel (ex: plusieurs plugins voulant intercepter `OnPlayerCommandText`). Les gestionnaires sont exécutés dans l'ordre inverse de leur enregistrement.
- **`Public_Registrar`** :
   - **Mécanisme :** C'est une classe template dont la macro `PLUGIN_PUBLIC_REGISTRATION` crée une instance statique globale. Dans son constructeur statique (`static bool registered = [...]`), elle enregistre son gestionnaire `Plugin_Public` dans le `Public_Dispatcher`. C'est un modèle d'"enregistrement statique au moment de la compilation/initialisation".
   - **Exemple (`public_dispatcher.hpp`) :**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Registrar<decltype(&name), &name, hash_##name> registrar_##name;
      ```

- **`Public_Traits` et `Wrapper()`** :
   - **Mécanisme :** `Public_Traits` est un template de trait qui, utilisant la métaprogrammation, génère une fonction `static cell Wrapper(AMX* amx)`.
   - **Objectif :** Ce `Wrapper` est le `Amx_Handler_Func` que le `Public_Dispatcher` stocke et appelle réellement. Il est responsable de :
      1. Appeler `Public_Param_Reader::Get_Public_Params(amx, args...)` pour extraire les paramètres de la pile de l'AMX.
      2. Appeler votre fonction `Plugin_Public` C++ réelle (`func_ptr`) avec les paramètres déjà convertis aux types C++ corrects.
- **`Public_Param_Reader::Get_Public_Params(...)`** :
   - **Description :** Un ensemble de fonctions template récursives qui lisent les valeurs de la pile de l'AMX et les convertissent aux types C++ spécifiés dans la déclaration du `Plugin_Public`.
   - **Mécanisme :** Utilise `Get_Stack_Cell()` pour accéder aux `cell`s sur la pile. Utilise `if constexpr` (C++17+) ou `std::is_same<T>::value` (C++14) pour appliquer la conversion correcte (`amx::AMX_CTOF` pour float, `Samp_SDK::Get_String` pour string, cast direct pour int).

### 4.7. `native.hpp` : Gestion et appel des natives du plugin

Cet en-tête est dédié à la création et à la gestion des natives C++ que votre plugin expose à Pawn.

- **`Native_List_Holder`** :
   - **Description :** Un `singleton` global qui stocke toutes les `Plugin_Native`s déclarées dans votre plugin (depuis tous les fichiers `.cpp` qui utilisent `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`** : Contient des objets `Native` (qui stockent le nom de la native et le pointeur vers la fonction C++ `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`** : Une carte optimisée par hachage pour des recherches rapides de `Plugin_Native`s internes (utilisée par `Plugin_Call`).
- **`Native_Registrar`** :
   - **Mécanisme :** Tout comme le `Public_Registrar`, c'est une classe template dont la macro `Plugin_Native` crée une instance statique globale. Dans son constructeur, elle ajoute la native au `Native_List_Holder`.
   - **Impact :** Vous permet de déclarer des `Plugin_Native`s dans plusieurs fichiers `.cpp` sans vous soucier de l'enregistrement manuel. Toutes seront collectées automatiquement.
- **`Native_Registry`** :
   - **Description :** Une classe auxiliaire qui, dans `OnAmxLoad`, prend la liste complète des `Native`s du `Native_List_Holder` et les formate dans un tableau `AMX_NATIVE_INFO`.
   - **Mécanisme :** Appelle `amx::Register(amx, amx_natives_info_.data(), -1)` pour enregistrer toutes vos natives dans l'instance AMX qui vient d'être chargée.
- **`Plugin_Call_Impl(...)`** :
   - **Description :** L'implémentation sous-jacente de la macro `Plugin_Call`.
   - **Mécanisme :** Utilise `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` pour obtenir directement le pointeur de la fonction C++.
   - **Environnement :** Exécute la native dans un environnement `Amx_Sandbox` (isolé) pour gérer la pile et le tas temporaires, de manière similaire au fonctionnement de `Pawn_Native`.

### 4.8. `callbacks.hpp` & `amx_memory.hpp` : Appels C++ -> Pawn et RAII

Ces en-têtes constituent l'épine dorsale des appels de fonctions Pawn depuis le C++ (macros `Pawn_*`) et garantissent la sécurité de la mémoire.

- **`Amx_Sandbox`** :
   - **Description :** Une structure `thread_local` qui simule un environnement `AMX` minimaliste et isolé pour les appels `Pawn_Native` et `Plugin_Call`.
   - **Mécanisme :** Possède sa propre structure `AMX`, `AMX_HEADER` et un `std::vector<unsigned char> heap` pour simuler la mémoire d'un script. Cela permet aux fonctions `amx::Push`, `amx::Allot`, etc., d'être appelées sans interférer avec l'état des scripts Pawn réels en cours d'exécution.
   - **`thread_local` :** Garantit que chaque thread possède son propre `Amx_Sandbox`, évitant les conditions de course si le SDK est utilisé dans un contexte multithread (ex: un futur pool de threads pour des opérations non-Pawn).
   - **Exemple (`Amx_Sandbox`) :**
      ```cpp
      // Extrait simplifié de callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Mémoire simulée pour pile/tas

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Initialise l'AMX et l'en-tête
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
   - **Description :** Un ensemble de fonctions template surchargées qui gèrent le `marshalling` de *chaque* paramètre C++ au format `cell` attendu par l'AMX, et vice-versa pour les paramètres de sortie.
   - **Traitement d'entrée :**
       - Pour `int`, `float`, `bool` : Convertit directement en `cell`.
       - Pour `const char*`, `std::string` : Alloue de la mémoire sur le tas du `Amx_Sandbox` (ou AMX réel pour `Pawn_Public`), copie la chaîne, et pousse l'adresse AMX sur la pile.
   - **Traitement de sortie (`is_output_arg`) :**
       - **Mécanisme :** Lorsqu'un argument est une référence de lvalue non-const (détecté par le trait `is_output_arg`), le `Parameter_Processor` ne pousse pas la valeur, mais plutôt une *adresse AMX* pour une `cell` allouée temporairement sur le tas.
       - **`std::vector<std::function<void()>> post_call_updaters`** : Après l'appel de la native Pawn, une liste de lambdas (`post_call_updaters`) est exécutée. Chaque lambda est responsable de lire la valeur finale de la `cell` allouée sur l'AMX et de l'affecter à la variable C++ originale (ex: `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`** :
   - **Mécanisme :** Un `std::integral_constant` (trait de type) qui, au moment de la compilation, évalue si un type de paramètre C++ est une référence modifiable (ex: `int&`, `float&`, `std::string&`). Cela permet au `Parameter_Processor` de différencier les paramètres d'entrée des paramètres de sortie.
   - **Exemple (`is_output_arg`) :**
      ```cpp
      // Extrait simplifié de callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`** :
   - **Description :** Une classe RAII (`Resource Acquisition Is Initialization`) qui encapsule l'allocation et la désallocation de mémoire dans l'AMX.
   - **Mécanisme :** Dans le constructeur, elle appelle `amx::Allot` pour obtenir une `amx_addr` et une `phys_addr`. Dans le destructeur, elle appelle `amx::Release` pour libérer cette mémoire.
   - **Impact :** **Crucial pour prévenir les fuites de mémoire sur le tas de l'AMX.** Garantit que la mémoire temporaire utilisée pour les chaînes ou les paramètres de sortie est toujours libérée, même si des exceptions se produisent ou si des retours anticipés ont lieu.

### 4.9. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h` : Accès abstrait à l'AMX

Ces en-têtes fournissent les définitions fondamentales et les outils de haut niveau pour interagir avec Pawn.

- **`amx_defs.h`** :
   - **Contenu :** Contient les définitions brutes des structures AMX (`AMX`, `AMX_HEADER`), des types (`cell`, `ucell`), et des enums d'erreur (`AmxError`). Définit également `AMX_NATIVE` et `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`** : Utilise des attributs de packaging (`#pragma pack(push, 1)` / `__attribute__((packed))`) pour garantir que les structures AMX ont la bonne disposition mémoire, fondamentale pour l'interopérabilité.
- **`Samp_SDK::amx::Call<Func, Index, ...>`** :
   - **Description :** La fonction template principale pour invoquer les fonctions de l'API AMX exposées par le serveur.
   - **Mécanisme :** Obtient le pointeur de la fonction via `Core::Instance().Get_AMX_Export(Index)` et l'appelle. Centralise le traitement des erreurs si le pointeur de la fonction n'est pas disponible.
   - **Impact :** Convertit les appels de bas niveau (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) en appels C++ idiomatiques et type-safe (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`** :
   - **Description :** Fonctions essentielles pour convertir les valeurs `cell` en `float` et vice-versa, en effectuant une réinterprétation bit à bit de la mémoire.
   - **`static_assert` :** Inclut `static_assert` pour garantir que `sizeof(cell) == sizeof(float)` au moment de la compilation, prévenant les erreurs sur les plateformes avec des tailles de type différentes.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`** :
   - **Description :** Helper pour convertir une adresse de chaîne AMX en `std::string`.
   - **Mécanisme :** Premièrement, obtient l'adresse physique (`cell* phys_addr`) de la chaîne dans l'AMX en utilisant `amx::Get_Addr`. Ensuite, utilise `amx::STR_Len` pour déterminer la longueur et `amx::Get_String` pour copier les octets dans un `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`** :
   - **Description :** La fonction de base de formatage de chaînes (type `printf`) pour le SDK.
   - **Mécanisme :** Utilise `vsnprintf` en deux passages : d'abord pour déterminer la taille nécessaire de la chaîne, puis pour formater la chaîne dans le `std::string` alloué dynamiquement. Cela évite les débordements de tampon.

## 5. Compilation et déploiement

### Exigences d'architecture et de plateforme

- Votre plugin **DOIT** être compilé pour l'architecture **x86 (32 bits)**. Le mécanisme de hooking du SDK est spécifique à cette architecture.
- Plateformes prises en charge : Windows (.dll) et Linux (.so).

### Exemples de commandes de compilation

#### **MSVC (Visual Studio)**

1. Créez un nouveau projet de "Dynamic-Link Library (DLL)".
2. Dans les paramètres du projet, définissez la "Plateforme de solution" sur **x86**.
3. Assurez-vous que la norme du langage C++ est au moins C++14.

#### **GCC / Clang (Linux)**

```bash
# Pour un plugin nommé 'my_plugin.so' à partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32` : Compile pour 32 bits.
- `-shared` : Crée une bibliothèque partagée (`.so`).
- `-std=c++17` : Définit la norme C++ à C++17 (peut être `c++14` ou `c++20`).
- `-O2` : Niveau d'optimisation 2.
- `-fPIC` : Génère du code indépendant de la position, nécessaire pour les bibliothèques partagées.
- `-Wall -Wextra` : Active les avertissements supplémentaires pour aider à détecter les erreurs.
- `-Wl,--no-undefined` : Empêche la création de la bibliothèque s'il y a des symboles indéfinis.

#### **GCC / Clang (MinGW sous Windows)**

```bash
# Pour un plugin nommé 'my_plugin.dll' à partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++` : Lie la bibliothèque standard C++ statiquement. Essentiel pour éviter que votre plugin ne dépende de DLLs de runtime spécifiques au compilateur qui pourraient ne pas être présentes sur le système de l'utilisateur.
- `-static-libgcc` : Lie la bibliothèque GCC statiquement.

### Considérations pour la distribution

- **Nom du fichier :** Votre plugin doit avoir l'extension `.dll` (Windows) ou `.so` (Linux). Ex : `my_plugin.dll`.
- **Emplacement :** Placez le fichier compilé dans le dossier `plugins/` de votre serveur SA-MP.
- **server.cfg :** Ajoutez le nom de votre plugin (si Windows, sans l'extension) à la ligne `plugins` dans le `server.cfg`.
   ```
   plugins my_plugin (si Linux, my_plugin.so)
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