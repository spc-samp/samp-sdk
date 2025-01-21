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

Le SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) est une collection complète de fichiers et headers C et d'éléments permettant aux développeurs de créer des plugins pour le serveur SA-MP. Ce SDK fournit une base pour étendre les fonctionnalités du serveur SA-MP grâce à des fonctions natives, permettant aux développeurs d'implémenter des fonctionnalités au-delà de ce qui est disponible dans le script Pawn.

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
    - [Système de Plugin](#système-de-plugin)
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
    - [Structure du Header AMX](#structure-du-header-amx)
  - [Fonctionnalités Avancées](#fonctionnalités-avancées)
    - [Support de la Compilation JIT](#support-de-la-compilation-jit)
    - [Interface de Débogage](#interface-de-débogage)
    - [Interface des Fonctions Publiques](#interface-des-fonctions-publiques)
  - [Informations de Version](#informations-de-version)
    - [Compatibilité des Versions](#compatibilité-des-versions)
  - [Licence](#licence)
    - [Ce que vous pouvez faire ✅](#ce-que-vous-pouvez-faire-)
    - [Ce que vous devez faire ⚠️](#ce-que-vous-devez-faire-️)
    - [Ce que vous ne pouvez pas faire ❌](#ce-que-vous-ne-pouvez-pas-faire-)

## Composants Principaux

### Système AMX

L'AMX (Abstract Machine eXecutor) est la machine virtuelle qui exécute les scripts Pawn dans SA-MP. Le SDK fournit un support complet pour interagir avec AMX via divers fichiers C et headers:

#### Headers AMX Principaux

1. **amx.h**

    Le header principal qui consolide toutes les fonctionnalités liées à AMX. Il comprend:
    - Fonctions AMX principales pour l'exécution des scripts
    - Gestion de la mémoire
    - Enregistrement des fonctions natives
    - Gestion des chaînes
    - Support UTF-8

    Les fonctions principales incluent:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    ```

2. **amx_cell.h**

    Définit les types de données fondamentaux utilisés dans le système AMX:
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

    Contient les structures essentielles pour le fonctionnement d'AMX:

    ```c
    typedef struct tagAMX {
        unsigned char _FAR *base;    // Adresse de base
        unsigned char _FAR *data;    // Segment de données
        AMX_CALLBACK callback;       // Fonction de callback
        AMX_DEBUG debug;            // Callback de débogage
        cell cip;                   // Pointeur d'instruction de code
        cell frm;                   // Base du cadre de pile
        cell hea;                   // Base du tas
        cell stk;                   // Pointeur de pile
        // ... champs supplémentaires
    } AMX;
    ```

### Support des Plateformes

Le SDK inclut une gestion robuste des spécificités des plateformes via divers headers:

1. **amx_platform.h**

    Fournit la détection et la configuration de la plateforme:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Gère les définitions spécifiques au système d'exploitation:
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

### Système de Plugin

#### plugincommon.h

Définit l'interface principale du plugin et les structures de support:

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

Le fichier `amxplugin.c` est un composant crucial du SDK SA-MP qui fournit des implémentations spécifiques aux plateformes des fonctions AMX. Il implémente deux approches différentes selon la plateforme et le compilateur:

1. **Implémentation Windows MSVC (32-bit)**
    - Utilise des fonctions nues avec assembly pour l'accès direct à la table des fonctions
    - Fournit des performances optimisées grâce aux sauts directs vers les fonctions AMX
    - Structure exemple:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Implémentation Multi-plateformes**
    - Utilise des pointeurs de fonction pour l'indépendance de la plateforme
    - Implémente un système basé sur des macros pour les définitions de fonction
    - Structure exemple:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

Caractéristiques Principales:

3. **Gestion de la Table des Fonctions**
    - Utilise un pointeur statique `pAMXFunctions` pour stocker la table des fonctions AMX
    - Fournit l'accès à toutes les fonctions AMX principales
    - Gère la résolution des fonctions à l'exécution

4. **Optimisations Spécifiques aux Plateformes**
    - Windows 32-bit: Utilise des fonctions nues pour l'implémentation directe en assembly
    - Autres plateformes: Utilise l'indirection des pointeurs de fonction
    - Traitement spécial pour les systèmes 64-bit

5. **Catégories de Fonctions Implémentées**

    a. Fonctions de Gestion de la Mémoire:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. Fonctions d'Exécution:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. Gestion des Symboles:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. Gestion des Chaînes:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Fonctions de support UTF-8
    
    e. Débogage et Information:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Compilation Conditionnelle**
    - Gère différentes plateformes via des directives de préprocesseur
    - Traitement spécial pour les systèmes 64-bit
    - Support JIT optionnel
    ```c
    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
            PLUGIN_AMX_EXPORT_Align64)
    #endif
    ```

7. **Intégration de la Gestion des Erreurs**
    - Implémente `amx_RaiseError` pour le signalement des erreurs
    - Préserve les codes d'erreur à travers les appels de fonction
    - S'intègre avec le système de débogage AMX

### Fonctions Natives AMX

Le SDK fournit un support complet pour la création et la gestion des fonctions natives:

```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

Opérations principales sur les fonctions natives:
- Enregistrement via `amx_Register`
- Accès et validation des paramètres
- Gestion des valeurs de retour
- Signalement des erreurs

## Détails Techniques

### Gestion de la Mémoire

Le SDK fournit des facilités complètes de gestion de la mémoire:

1. **amx_memory.h**

   Gère l'allocation mémoire et les opérations mémoire spécifiques à la plateforme:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```

2. **amx_alignment.h**

    Gère les exigences d'alignement mémoire:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Opérations Mémoire

Le SDK inclut plusieurs fonctions pour la manipulation de la mémoire:

1. **Allocation Mémoire**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Alloue de la mémoire dans le tas AMX
    - Retourne les adresses AMX et physiques
    - Gère les exigences d'alignement

2. **Accès Mémoire**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Convertit les adresses AMX en adresses physiques
    - Valide l'accès mémoire
    - Gère les limites de mémoire

3. **Information Mémoire**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Récupère les informations de disposition mémoire
    - Rapporte les tailles des segments
    - Utile pour le débogage et l'optimisation

### Gestion des Erreurs

Le SDK inclut un système complet de gestion des erreurs défini dans `amx_constants.h`:

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

Le SDK fournit des capacités robustes de gestion des chaînes via diverses macros et fonctions:

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

### Opérations sur les Chaînes

1. **Longueur de Chaîne**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Calcule la longueur de la chaîne
    - Gère les chaînes compactées et non compactées
    - Retourne la longueur en caractères

2. **Conversion de Chaîne**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Convertit les chaînes C en chaînes AMX
    - Supporte les formats compactés et non compactés
    - Gère la conversion Unicode

## Support Unicode

Le SDK inclut un support Unicode complet via des fonctions de gestion UTF-8:

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
    - Valide les chaînes encodées en UTF-8
    - Rapporte la longueur de la chaîne en caractères
    - Détecte les erreurs d'encodage

2. **Conversion de Caractères**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extrait les caractères Unicode
    - Gère les séquences multi-octets
    - Rapporte les erreurs d'analyse

## Compatibilité Multi-plateformes

Le SDK assure la compatibilité multi-plateformes via:

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

## Configuration Requise

Le SDK supporte plusieurs plateformes et compilateurs:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Support des Compilateurs

1. **Microsoft Visual C++**
   - Gestion des pragma
   - Suppression des avertissements
   - Conventions d'appel

2. **GCC**
   - Contrôles de diagnostic
   - Spécifications d'attributs
   - Optimisations spécifiques aux plateformes

3. **Clang**
   - Configurations des avertissements
   - Compatibilité multi-plateformes
   - Fonctionnalités C++ modernes

## Meilleures Pratiques

Lors de l'utilisation du SDK SA-MP, considérez les meilleures pratiques suivantes:

1. **Gestion de la Mémoire**
   - Toujours nettoyer les ressources allouées
   - Utiliser l'alignement mémoire approprié
   - Gérer les erreurs mémoire avec élégance
   - Surveiller l'utilisation du tas
   - Implémenter une vérification appropriée des limites mémoire
   - Utiliser des pools de mémoire pour les allocations fréquentes
   - Nettoyer les ressources dans l'ordre inverse de l'allocation

2. **Gestion des Erreurs**
   - Vérifier les valeurs de retour des fonctions AMX
   - Implémenter une gestion appropriée des erreurs dans les fonctions natives
   - Utiliser les constantes d'erreur fournies
   - Journaliser les erreurs de manière appropriée
   - Implémenter des mécanismes de récupération d'erreurs
   - Fournir des messages d'erreur significatifs
   - Gérer les erreurs spécifiques au système

3. **Développement Multi-plateformes**
   - Utiliser des types indépendants de la plateforme
   - Utiliser les macros fournies pour le code spécifique à la plateforme
   - Tester sur plusieurs plateformes
   - Gérer les différences d'endianness
   - Utiliser les séparateurs de chemin appropriés
   - Considérer les différences de système de fichiers
   - Implémenter des optimisations spécifiques à la plateforme

4. **Considérations de Performance**
   - Utiliser les tailles de cellules appropriées
   - Implémenter une gestion efficace des chaînes
   - Optimiser les appels de fonctions natives
   - Minimiser les allocations mémoire
   - Utiliser des structures de données appropriées
   - Implémenter la mise en cache lorsque approprié
   - Profiler les chemins de code critiques

Lors du travail avec la fonctionnalité `amxplugin.c`:

1. **Développement Spécifique à la Plateforme**
   - Considérer les différences de plateforme dans les implémentations de fonctions
   - Tester sur les systèmes 32-bit et 64-bit
   - Gérer les exigences d'alignement spécifiques à la plateforme
   - Valider le pointeur de table de fonctions avant utilisation
   - Implémenter une vérification d'erreur appropriée pour chaque plateforme
   - Considérer les implications de performance des différentes implémentations

2. **Gestion de la Table des Fonctions**
   - Initialiser la table des fonctions avant utilisation
   - Vérifier la disponibilité des fonctions
   - Gérer gracieusement les fonctions manquantes
   - Implémenter des procédures de nettoyage appropriées
   - Mettre en cache les pointeurs de fonction fréquemment utilisés
   - Valider l'intégrité de la table des fonctions

3. **Gestion des Erreurs**
   - Implémenter une vérification d'erreur appropriée pour le code spécifique à la plateforme
   - Gérer les erreurs d'alignement de manière appropriée
   - Valider les entrées de la table des fonctions
   - Fournir des messages d'erreur significatifs
   - Implémenter des mécanismes de récupération
   - Journaliser les erreurs spécifiques à la plateforme

## Structures Internes

### Structure du Header AMX

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Taille du "fichier"
    uint16_t magic;        // Signature
    char    file_version;  // Version du format de fichier
    char    amx_version;   // Version AMX requise
    int16_t flags;         // Drapeaux
    int16_t defsize;      // Taille d'un enregistrement de définition
    int32_t cod;          // Valeur initiale de COD - bloc de code
    int32_t dat;          // Valeur initiale de DAT - bloc de données
    int32_t hea;          // Valeur initiale de HEA - début du tas
    int32_t stp;          // Valeur initiale de STP - sommet de la pile
    int32_t cip;          // Valeur initiale de CIP - pointeur d'instruction de code
    int32_t publics;      // Décalage vers les fonctions publiques
    int32_t natives;      // Décalage vers la table des fonctions natives
    int32_t libraries;    // Décalage vers les bibliothèques
    int32_t pubvars;      // Décalage vers les variables publiques
    int32_t tags;         // Décalage vers les tags
    int32_t nametable;    // Décalage vers la table des noms
} AMX_HEADER;
```

Cette structure est cruciale pour comprendre le format de fichier AMX et comment la machine virtuelle charge et exécute les scripts.

## Fonctionnalités Avancées

### Support de la Compilation JIT

Le SDK inclut le support pour la compilation Just-In-Time:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Interface de Débogage

Le support de débogage est fourni via:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Interface des Fonctions Publiques

Le SDK fournit un support complet pour travailler avec les fonctions publiques:

1. **Recherche de Fonctions Publiques**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Localise les fonctions publiques par nom
    - Retourne l'index de la fonction
    - Valide l'existence de la fonction

2. **Exécution de Fonctions Publiques**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Exécute les fonctions publiques
    - Gère les valeurs de retour
    - Gère le contexte d'exécution

## Informations de Version

Le SDK inclut des constantes de version pour la vérification de compatibilité:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Compatibilité des Versions

Le SDK maintient la compatibilité via:
1. Vérification de la version du fichier
2. Validation de la version AMX
3. Vérification de la compatibilité JIT
4. Détection des fonctionnalités
5. Gestion des versions spécifiques à la plateforme

## Licence

Copyright © SA-MP Programming Community

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Vous pouvez obtenir une copie de la licence sur:
https://opensource.org/licenses/MIT

### Ce que vous pouvez faire ✅

1. **Usage Commercial**:
   - Liberté totale pour l'usage commercial
   - Possibilité de vendre des produits basés sur le code
   - Pas de paiement de redevances nécessaire
   - Utilisation possible dans des produits propriétaires

2. **Modification**:
   - Modification complète du code source
   - Création de travaux dérivés
   - Adaptation à tout usage
   - Intégration avec d'autres systèmes

3. **Distribution**:
   - Distribution du logiciel original
   - Partage des versions modifiées
   - Inclusion dans d'autres projets
   - Distribution commerciale

4. **Usage Privé**:
   - Utilisation dans des projets privés
   - Modifications confidentielles
   - Aucune obligation de divulgation
   - Usage interne sans restriction

5. **Sous-licence**:
   - Possibilité de changer la licence du code dérivé
   - Choix de différents termes pour vos modifications
   - Combinaison avec d'autres licences
   - Création de vos propres termes de distribution

### Ce que vous devez faire ⚠️

1. **Inclure la Licence**:
   - Conserver une copie de la licence avec le code
   - Inclure dans toutes les distributions
   - Préserver le texte original
   - Maintenir visible et accessible

2. **Attribution**:
   - Maintenir l'avis de droits d'auteur
   - Inclure dans toutes les copies
   - Préserver les crédits originaux
   - Documenter l'origine du code

### Ce que vous ne pouvez pas faire ❌

1. **Tenir les Auteurs Responsables**:
   - Pas de garanties de fonctionnement
   - Les auteurs ne sont pas responsables des dommages
   - Pas de support obligatoire
   - Utilisation à vos propres risques