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

Le SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) est une collection complète de fichiers C, d'en-têtes (headers) et de composants qui permettent aux développeurs de créer des plugins pour le serveur SA-MP. Ce SDK fournit une base pour étendre les fonctionnalités du serveur SA-MP grâce à des fonctions natives, permettant aux développeurs d'implémenter des fonctionnalités au-delà de ce qui est disponible dans les scripts Pawn.

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

## Index

- [samp-sdk](#samp-sdk)
  - [Langues](#langues)
  - [Index](#index)
  - [Composants Principaux](#composants-principaux)
    - [Système AMX](#système-amx)
      - [Headers AMX Principaux](#headers-amx-principaux)
    - [Support des Plateformes](#support-des-plateformes)
    - [Système de Plugins](#système-de-plugins)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [Fonctions Natives AMX](#fonctions-natives-amx)
  - [Détails Techniques](#détails-techniques)
    - [Gestion de la Mémoire](#gestion-de-la-mémoire)
    - [Opérations Mémoire](#opérations-mémoire)
    - [Gestion des Erreurs](#gestion-des-erreurs)
    - [Gestion des Chaînes](#gestion-des-chaînes)
    - [Opérations sur les Chaînes](#opérations-sur-les-chaînes)
  - [Support Unicode](#support-unicode)
    - [Opérations Unicode](#opérations-unicode)
  - [Compatibilité Multi-plateformes](#compatibilité-multi-plateformes)
  - [Configuration Requise](#configuration-requise)
    - [Support des Compilateurs](#support-des-compilateurs)
  - [Meilleures Pratiques](#meilleures-pratiques)
  - [Structures Internes](#structures-internes)
    - [Structure de l'En-tête AMX](#structure-de-len-tête-amx)
  - [Fonctionnalités Avancées](#fonctionnalités-avancées)
    - [Support de la Compilation JIT](#support-de-la-compilation-jit)
    - [Interface de Débogage](#interface-de-débogage)
    - [Interface des Fonctions Publiques](#interface-des-fonctions-publiques)
  - [Informations de Version](#informations-de-version)
    - [Compatibilité des Versions](#compatibilité-des-versions)
  - [Licence](#licence)
    - [Conditions Générales d'Utilisation](#conditions-générales-dutilisation)
      - [1. Autorisations Accordées](#1-autorisations-accordées)
      - [2. Conditions Obligatoires](#2-conditions-obligatoires)
      - [3. Droits d'Auteur](#3-droits-dauteur)
      - [4. Exclusion de Garantie et Limitation de Responsabilité](#4-exclusion-de-garantie-et-limitation-de-responsabilité)

## Composants Principaux

### Système AMX

L'AMX (Abstract Machine eXecutor) est la machine virtuelle qui exécute les scripts Pawn dans SA-MP. Le SDK fournit un support étendu pour interagir avec le système AMX à travers divers fichiers C et en-têtes.

#### Headers AMX Principaux

1. **amx.h**

    L'en-tête principal qui consolide toutes les fonctionnalités liées à AMX :
    - Fonctions principales pour l'exécution des scripts
    - Gestion de la mémoire
    - Enregistrement des fonctions natives
    - Gestion des chaînes
    - Support UTF-8

    Les fonctions clés incluent :
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);         // Initialise une instance AMX
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index); // Exécute une fonction publique
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number); // Enregistre des fonctions natives
    ```

2. **amx_platform.h**

    Responsable de la détection et de la configuration des plateformes :
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```
    - Détecte des systèmes comme Linux, FreeBSD, OpenBSD et macOS.
    - Inclut `sclinux.h` pour les systèmes de type Unix.
    - Identifie les architectures 64 bits :
      ```c
      #if defined _LP64 || defined WIN64 || defined _WIN64
          #define __64BIT__
      #endif
      ```
    - Calcule la version de GCC si applicable :
      ```c
      #if defined __GNUC__
          #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #endif
      ```

3. **amx_constants.h**

    Définit les constantes essentielles pour le fonctionnement d'AMX :
    - **Versions** :
      ```c
      #define CUR_FILE_VERSION  9   // Version actuelle du format de fichier
      #define MIN_FILE_VERSION  6   // Version minimale supportée
      #define MIN_AMX_VERSION   10  // Version minimale d'AMX
      #define MAX_FILE_VER_JIT  8   // Version maximale avec support JIT
      #define MIN_AMX_VER_JIT   8   // Version minimale avec support JIT
      ```
    - **Codes Magiques** :
      ```c
      #define AMX_MAGIC_16    0xf1e2  // Pour cellules de 16 bits
      #define AMX_MAGIC_32    0xf1e0  // Pour cellules de 32 bits
      #define AMX_MAGIC_64    0xf1e1  // Pour cellules de 64 bits
      ```
    - **Codes d'Erreur** :
      ```c
      enum {
          AMX_ERR_NONE,         // Pas d'erreur
          AMX_ERR_EXIT,         // Script terminé
          AMX_ERR_ASSERT,       // Assertion échouée
          AMX_ERR_STACKERR,     // Erreur de pile
          AMX_ERR_BOUNDS,       // Accès hors limites
          AMX_ERR_MEMACCESS,    // Accès mémoire invalide
          AMX_ERR_INVINSTR,     // Instruction invalide
          AMX_ERR_STACKLOW,     // Pile trop basse
          AMX_ERR_HEAPLOW,      // Tas trop bas
          AMX_ERR_CALLBACK,     // Erreur de callback
          AMX_ERR_NATIVE,       // Erreur de fonction native
          AMX_ERR_DIVIDE,       // Division par zéro
          AMX_ERR_SLEEP,        // Mode veille activé
          AMX_ERR_INVSTATE,     // État invalide
          AMX_ERR_MEMORY = 16,  // Mémoire insuffisante
          AMX_ERR_FORMAT,       // Format invalide
          AMX_ERR_VERSION,      // Version incompatible
          AMX_ERR_NOTFOUND,     // Ressource non trouvée
          AMX_ERR_INDEX,        // Indice invalide
          AMX_ERR_DEBUG,        // Erreur de débogage
          AMX_ERR_INIT,         // Échec d'initialisation
          AMX_ERR_USERDATA,     // Erreur de données utilisateur
          AMX_ERR_INIT_JIT,     // Échec d'initialisation JIT
          AMX_ERR_PARAMS,       // Paramètres invalides
          AMX_ERR_DOMAIN,       // Erreur de domaine
          AMX_ERR_GENERAL,      // Erreur générale
      };
      ```
    - **Drapeaux** :
      ```c
      #define AMX_FLAG_DEBUG      0x02   // Mode débogage
      #define AMX_FLAG_COMPACT    0x04   // Encodage compact
      #define AMX_FLAG_SLEEP      0x08   // Support veille
      #define AMX_FLAG_NOCHECKS   0x10   // Pas de vérifications de sécurité
      #define AMX_FLAG_NO_RELOC   0x200  // Pas de relocalisation
      #define AMX_FLAG_NO_SYSREQD 0x400  // Pas de sysreq.d
      #define AMX_FLAG_SYSREQN    0x800  // Support sysreq.n
      #define AMX_FLAG_NTVREG     0x1000 // Enregistrement natif
      #define AMX_FLAG_JITC       0x2000 // Compilation JIT
      #define AMX_FLAG_BROWSE     0x4000 // Mode navigation
      #define AMX_FLAG_RELOC      0x8000 // Relocalisation activée
      ```
    - **Codes d'Exécution** :
      ```c
      #define AMX_EXEC_MAIN   (-1)  // Exécuter la fonction principale
      #define AMX_EXEC_CONT   (-2)  // Continuer l'exécution
      ```

4. **amx_memory.h**

    Gère l'allocation mémoire :
    - Support pour `alloca` :
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
    - Définit la marge de compression :
      ```c
      #if !defined AMX_COMPACTMARGIN
          #define AMX_COMPACTMARGIN 64
      #endif
      ```

5. **amx_calling.h**

    Définit les conventions d'appel :
    - Pour les fonctions natives et APIs :
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

    Définit les types entiers standardisés :
    - Support pour `stdint.h` ou définitions manuelles :
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

    Fournit des macros utiles :
    - **Calcul d'Adresse** :
      ```c
      #define amx_Address(amx,addr) \
          (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))
      ```
    - **Gestion des Chaînes** :
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
    - **Comptage des Paramètres** :
      ```c
      #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))
      ```
    - **Enregistrement des Fonctions** :
      ```c
      #define amx_RegisterFunc(amx, name, func) \
          amx_Register((amx), amx_NativeInfo((name),(func)), 1)
      ```

8. **amx_cell.h**

    Définit les types de cellules :
    - Configure `PAWN_CELL_SIZE` (par défaut : 32) :
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
    - Support pour les nombres à virgule flottante :
      ```c
      #if PAWN_CELL_SIZE==32
          #define amx_ftoc(f)   (*(cell*)&(f))  // Float vers cellule
          #define amx_ctof(c)   (*(float*)&(c))  // Cellule vers float
      #elif PAWN_CELL_SIZE==64
          #define amx_ftoc(f)   (*(cell*)&(f))  // Double vers cellule
          #define amx_ctof(c)   (*(double*)&(c)) // Cellule vers double
      #endif
      ```
    - Manipulation des caractères :
      ```c
      #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))  // Pour 32 bits
      ```

9. **amx_structures.h**

    Définit les structures principales :
    - **AMX** :
      ```c
      typedef struct tagAMX {
          unsigned char _FAR *base;    // Adresse de base
          unsigned char _FAR *data;    // Segment de données
          AMX_CALLBACK callback;       // Fonction de rappel
          AMX_DEBUG debug;            // Rappel de débogage
          cell cip;                   // Pointeur d'instruction de code
          cell frm;                   // Base du cadre
          cell hea;                   // Base du tas
          cell hlw;                   // Limite inférieure du tas
          cell stk;                   // Pointeur de pile
          cell stp;                   // Sommet de la pile
          int flags;                  // Drapeaux
          long usertags[AMX_USERNUM]; // Étiquettes utilisateur
          void _FAR *userdata[AMX_USERNUM]; // Données utilisateur
          int error;                  // Code d'erreur
          int paramcount;             // Nombre de paramètres
          cell pri;                   // Registre primaire
          cell alt;                   // Registre alternatif
          cell reset_stk;             // Pile réinitialisée
          cell reset_hea;             // Tas réinitialisé
          cell sysreq_d;              // Adresse sysreq.d
          #if defined JIT
              int reloc_size;         // Taille de relocalisation
              long code_size;         // Taille du code
          #endif
      } AMX;
      ```
    - **AMX_HEADER** :
      ```c
      typedef struct tagAMX_HEADER {
          int32_t size;          // Taille du fichier
          uint16_t magic;        // Signature
          char    file_version;  // Version du fichier
          char    amx_version;   // Version d'AMX
          int16_t flags;         // Drapeaux
          int16_t defsize;       // Taille de définition
          int32_t cod;           // Début du code
          int32_t dat;           // Début des données
          int32_t hea;           // Début du tas
          int32_t stp;           // Sommet de la pile
          int32_t cip;           // Pointeur d'instruction initial
          int32_t publics;       // Décalage vers les fonctions publiques
          int32_t natives;       // Décalage vers les fonctions natives
          int32_t libraries;     // Décalage vers les bibliothèques
          int32_t pubvars;       // Décalage vers les variables publiques
          int32_t tags;          // Décalage vers les étiquettes
          int32_t nametable;     // Décalage vers la table des noms
      } AMX_HEADER;
      ```

### Support des Plateformes

Le SDK inclut une gestion robuste spécifique aux plateformes à travers divers en-têtes :

1. **amx_platform.h**

    Fournit la détection et la configuration des plateformes :
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Gère les définitions spécifiques au système d'exploitation :
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

### Système de Plugins

#### plugincommon.h

Définit l'interface principale du plugin et les structures de support :
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

Le fichier `amxplugin.c` est un composant clé du SA-MP SDK, fournissant des implémentations spécifiques aux plateformes pour les fonctions AMX. Il implémente deux approches basées sur la plateforme et le compilateur :

1. **Implémentation Windows MSVC (32-bit)**
    - Utilise des fonctions "nues" avec assembleur pour un accès direct à la table des fonctions :
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Implémentation Multi-plateformes**
    - Utilise des pointeurs de fonctions pour l'indépendance de la plateforme :
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

**Caractéristiques Clés** :

3. **Gestion de la Table des Fonctions**
    - Utilise un pointeur statique `pAMXFunctions` pour stocker la table des fonctions AMX.
    - Fournit l'accès à toutes les fonctions principales d'AMX.
    - Gère la résolution des fonctions à l'exécution.

4. **Optimisations Spécifiques aux Plateformes**
    - Windows 32-bit : Implémentation directe en assembleur avec des fonctions nues.
    - Autres plateformes : Indirection des pointeurs de fonctions.
    - Gestion spéciale pour les systèmes 64 bits.

5. **Catégories de Fonctions Implémentées**

    a. **Fonctions de Gestion de la Mémoire** :
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. **Fonctions d'Exécution** :
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. **Gestion des Symboles** :
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. **Gestion des Chaînes** :
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Fonctions de support UTF-8
    
    e. **Débogage et Information** :
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Compilation Conditionnelle**
    - Gère différentes plateformes via des directives de préprocesseur.
    - Gestion spéciale pour les systèmes 64 bits.
    - Support optionnel pour JIT :
      ```c
      #if defined _I64_MAX || defined HAVE_I64
          DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
              PLUGIN_AMX_EXPORT_Align64)
      #endif
      ```

7. **Intégration de la Gestion des Erreurs**
    - Implémente `amx_RaiseError` pour le signalement des erreurs.
    - Préserve les codes d'erreur à travers les appels de fonction.
    - S'intègre avec le système de débogage AMX.

### Fonctions Natives AMX

Le SDK fournit un support complet pour créer et gérer des fonctions natives :
```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

**Opérations Clés avec les Fonctions Natives** :
- Enregistrement via `amx_Register`.
- Accès et validation des paramètres via `amx_NumParams`.
- Gestion des valeurs de retour.
- Signalement des erreurs avec `amx_RaiseError`.

## Détails Techniques

### Gestion de la Mémoire

Le SDK offre des installations complètes de gestion de la mémoire :

1. **amx_memory.h**

    Gère l'allocation mémoire et les opérations spécifiques à la plateforme :
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```
    - Définit `AMX_COMPACTMARGIN` à 64 par défaut pour la compression mémoire.

2. **amx_alignment.h**

    Gère les exigences d'alignement mémoire :
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Opérations Mémoire

Le SDK inclut plusieurs fonctions pour la manipulation de la mémoire :

1. **Allocation Mémoire**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Alloue de la mémoire dans le tas AMX.
    - Retourne les adresses AMX et physiques.
    - Gère les exigences d'alignement.

2. **Accès Mémoire**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Convertit les adresses AMX en adresses physiques.
    - Valide l'accès mémoire.
    - Gère les limites de mémoire.

3. **Information Mémoire**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Récupère les informations sur la disposition de la mémoire.
    - Rapporte les tailles des segments.
    - Utile pour le débogage et l'optimisation.

### Gestion des Erreurs

Le SDK inclut un système complet de gestion des erreurs défini dans `amx_constants.h` :
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

### Gestion des Chaînes

Le SDK fournit des capacités robustes de gestion des chaînes à travers divers macros et fonctions :
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
- Alternative pour `char*` :
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

### Opérations sur les Chaînes

1. **Longueur de Chaîne**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Calcule la longueur de la chaîne.
    - Gère les chaînes compactées et non compactées.
    - Retourne la longueur en caractères.

2. **Conversion de Chaîne**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Convertit les chaînes C en chaînes AMX.
    - Supporte les formats compactés et non compactés.
    - Gère la conversion Unicode.

## Support Unicode

Le SDK fournit un support complet pour Unicode à travers des fonctions de gestion UTF-8 :
```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Opérations Unicode

1. **Validation UTF-8**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - Valide les chaînes encodées en UTF-8.
    - Rapporte la longueur de la chaîne en caractères.
    - Détecte les erreurs d'encodage.

2. **Conversion de Caractères**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extrait les caractères Unicode.
    - Gère les séquences multi-octets.
    - Rapporte les erreurs d'analyse.

## Compatibilité Multi-plateformes

Le SDK assure la compatibilité multi-plateformes grâce à :

1. **Gestion de l'Endianness**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Gestion des Chemins**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

3. **Types Indépendants de la Plateforme**
    - Définis dans `amx_types.h` pour la cohérence.

## Configuration Requise

Le SDK supporte plusieurs plateformes et compilateurs :
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Support des Compilateurs

1. **Microsoft Visual C++**
    - Gestion des pragmas.
    - Suppression des avertissements.
    - Conventions d'appel via `amx_calling.h`.

2. **GCC**
    - Contrôles de diagnostic.
    - Spécifications d'attributs.
    - Optimisations spécifiques à la plateforme.

3. **Clang**
    - Configurations des avertissements.
    - Compatibilité multi-plateformes.
    - Fonctionnalités modernes de C++.

## Meilleures Pratiques

Lors de l'utilisation du SA-MP SDK, considérez les meilleures pratiques suivantes :

1. **Gestion de la Mémoire**
    - Toujours nettoyer les ressources allouées.
    - Utiliser un alignement mémoire approprié.
    - Gérer les erreurs mémoire avec élégance.
    - Surveiller l'utilisation du tas.
    - Implémenter une vérification appropriée des limites mémoire.
    - Utiliser des pools de mémoire pour les allocations fréquentes.
    - Nettoyer les ressources dans l'ordre inverse de l'allocation.

2. **Gestion des Erreurs**
    - Vérifier les valeurs de retour des fonctions AMX.
    - Implémenter une gestion appropriée des erreurs dans les fonctions natives.
    - Utiliser les constantes d'erreur fournies.
    - Journaliser les erreurs de manière appropriée.
    - Implémenter des mécanismes de récupération d'erreurs.
    - Fournir des messages d'erreur significatifs.
    - Gérer les erreurs spécifiques au système.

3. **Développement Multi-plateformes**
    - Utiliser des types indépendants de la plateforme.
    - Utiliser les macros fournies pour le code spécifique à la plateforme.
    - Tester sur plusieurs plateformes.
    - Gérer les différences d'endianness.
    - Utiliser les séparateurs de chemin appropriés.
    - Considérer les différences de système de fichiers.
    - Implémenter des optimisations spécifiques à la plateforme.

4. **Considérations de Performance**
    - Utiliser des tailles de cellules appropriées.
    - Implémenter une gestion efficace des chaînes.
    - Optimiser les appels de fonctions natives.
    - Minimiser les allocations mémoire.
    - Utiliser des structures de données appropriées.
    - Implémenter la mise en cache lorsque approprié.
    - Profiler les chemins de code critiques.

Lors du travail avec la fonctionnalité de `amxplugin.c` :

1. **Développement Spécifique à la Plateforme**
    - Considérer les différences de plateforme dans les implémentations de fonctions.
    - Tester sur les systèmes 32 bits et 64 bits.
    - Gérer les exigences d'alignement spécifiques à la plateforme.
    - Valider le pointeur de la table des fonctions avant utilisation.
    - Implémenter une vérification d'erreur appropriée pour chaque plateforme.
    - Considérer les implications de performance des différentes implémentations.

2. **Gestion de la Table des Fonctions**
    - Initialiser la table des fonctions avant utilisation.
    - Vérifier la disponibilité des fonctions.
    - Gérer les fonctions manquantes avec élégance.
    - Implémenter des procédures de nettoyage appropriées.
    - Mettre en cache les pointeurs de fonctions fréquemment utilisés.
    - Valider l'intégrité de la table des fonctions.

3. **Gestion des Erreurs**
    - Implémenter une vérification d'erreur appropriée pour le code spécifique à la plateforme.
    - Gérer les erreurs d'alignement de manière appropriée.
    - Valider les entrées de la table des fonctions.
    - Fournir des messages d'erreur significatifs.
    - Implémenter des mécanismes de récupération.
    - Journaliser les erreurs spécifiques à la plateforme.

## Structures Internes

### Structure de l'En-tête AMX

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Taille du "fichier"
    uint16_t magic;        // Signature
    char    file_version;  // Version du format de fichier
    char    amx_version;   // Version AMX requise
    int16_t flags;         // Drapeaux
    int16_t defsize;       // Taille d'un enregistrement de définition
    int32_t cod;           // Valeur initiale de COD - bloc de code
    int32_t dat;           // Valeur initiale de DAT - bloc de données
    int32_t hea;           // Valeur initiale de HEA - début du tas
    int32_t stp;           // Valeur initiale de STP - sommet de la pile
    int32_t cip;           // Valeur initiale de CIP - pointeur d'instruction de code
    int32_t publics;       // Décalage vers les fonctions publiques
    int32_t natives;       // Décalage vers la table des fonctions natives
    int32_t libraries;     // Décalage vers les bibliothèques
    int32_t pubvars;       // Décalage vers les variables publiques
    int32_t tags;          // Décalage vers les étiquettes
    int32_t nametable;     // Décalage vers la table des noms
} AMX_HEADER;
```

Cette structure est cruciale pour comprendre le format de fichier AMX et comment la machine virtuelle charge et exécute les scripts.

## Fonctionnalités Avancées

### Support de la Compilation JIT

Le SDK inclut le support pour la compilation Just-In-Time :
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Interface de Débogage

Le support de débogage est fourni via :
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Interface des Fonctions Publiques

Le SDK fournit un support complet pour travailler avec les fonctions publiques :

1. **Recherche de Fonctions Publiques**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Localise les fonctions publiques par nom.
    - Retourne l'index de la fonction.
    - Valide l'existence de la fonction.

2. **Exécution de Fonctions Publiques**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Exécute les fonctions publiques.
    - Gère les valeurs de retour.
    - Gère le contexte d'exécution.

## Informations de Version

Le SDK inclut des constantes de version pour la vérification de compatibilité :
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Compatibilité des Versions

Le SDK maintient la compatibilité via :
1. Vérification de la version du fichier.
2. Validation de la version AMX.
3. Vérification de la compatibilité JIT.
4. Détection des fonctionnalités.
5. Gestion des versions spécifiques à la plateforme.

## Licence

Copyright © **SA-MP Programming Community**

Ce logiciel est sous licence selon les termes de la Licence MIT ("Licence") ; vous pouvez utiliser ce logiciel conformément aux termes de la Licence. Une copie de la Licence peut être obtenue à : [MIT License](https://opensource.org/licenses/MIT)

### Conditions Générales d'Utilisation

#### 1. Autorisations Accordées

Cette licence accorde, gratuitement, à toute personne obtenant une copie de ce logiciel et des fichiers de documentation associés, les droits suivants :
- Utiliser, copier, modifier, fusionner, publier, distribuer, sous-licencier et/ou vendre des copies du logiciel sans restriction.
- Permettre aux personnes à qui le logiciel est fourni de faire de même, sous réserve des conditions suivantes.

#### 2. Conditions Obligatoires

Toutes les copies ou parties substantielles du logiciel doivent inclure :
- L'avis de droit d'auteur ci-dessus.
- Cet avis d'autorisation.
- L'avis de non-responsabilité ci-dessous.

#### 3. Droits d'Auteur

Le logiciel et toute la documentation associée sont protégés par les lois sur le droit d'auteur. La **SA-MP Programming Community** conserve les droits d'auteur originaux du logiciel.

#### 4. Exclusion de Garantie et Limitation de Responsabilité

LE LOGICIEL EST FOURNI "TEL QUEL", SANS GARANTIE D'AUCUNE SORTE, EXPRESSE OU IMPLICITE, Y COMPRIS, MAIS SANS S'Y LIMITER, LES GARANTIES DE COMMERCIALISATION, D'ADÉQUATION À UN USAGE PARTICULIER ET DE NON-VIOLATION.

EN AUCUN CAS LES AUTEURS OU LES DÉTENTEURS DES DROITS D'AUTEUR NE SERONT RESPONSABLES DE TOUTE RÉCLAMATION, DOMMAGE OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS UNE ACTION DE CONTRAT, UN DÉLIT OU AUTRE, DÉCOULANT DE, HORS DE OU EN RELATION AVEC LE LOGICIEL OU L'UTILISATION OU D'AUTRES TRANSACTIONS DANS LE LOGICIEL.

---

Pour des informations détaillées sur la Licence MIT, consultez : https://opensource.org/licenses/MIT