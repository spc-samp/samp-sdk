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

SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) to kompleksowy zbiór plików C i headerów oraz elementów, które pozwalają programistom tworzyć wtyczki dla serwera SA-MP. Ten SDK zapewnia podstawę do rozszerzania funkcjonalności serwera SA-MP poprzez funkcje natywne, umożliwiając programistom implementację funkcji wykraczających poza to, co jest dostępne w skrypcie Pawn.

## Języki

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Spis treści

- [samp-sdk](#samp-sdk)
  - [Języki](#języki)
  - [Spis treści](#spis-treści)
  - [Główne komponenty](#główne-komponenty)
    - [System AMX](#system-amx)
      - [Główne headery AMX](#główne-headery-amx)
    - [Wsparcie platform](#wsparcie-platform)
    - [System wtyczek](#system-wtyczek)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [Funkcje natywne AMX](#funkcje-natywne-amx)
  - [Szczegóły techniczne](#szczegóły-techniczne)
    - [Zarządzanie pamięcią](#zarządzanie-pamięcią)
    - [Operacje pamięci](#operacje-pamięci)
    - [Obsługa błędów](#obsługa-błędów)
    - [Obsługa ciągów znaków](#obsługa-ciągów-znaków)
    - [Operacje na ciągach znaków](#operacje-na-ciągach-znaków)
  - [Wsparcie Unicode](#wsparcie-unicode)
    - [Operacje Unicode](#operacje-unicode)
  - [Kompatybilność międzyplatformowa](#kompatybilność-międzyplatformowa)
  - [Wymagania systemowe](#wymagania-systemowe)
    - [Wsparcie kompilatorów](#wsparcie-kompilatorów)
  - [Najlepsze praktyki](#najlepsze-praktyki)
  - [Struktury wewnętrzne](#struktury-wewnętrzne)
    - [Struktura nagłówka AMX](#struktura-nagłówka-amx)
  - [Zaawansowane funkcje](#zaawansowane-funkcje)
    - [Wsparcie kompilacji JIT](#wsparcie-kompilacji-jit)
    - [Interfejs debugowania](#interfejs-debugowania)
    - [Interfejs funkcji publicznych](#interfejs-funkcji-publicznych)
  - [Informacje o wersji](#informacje-o-wersji)
    - [Kompatybilność wersji](#kompatybilność-wersji)
  - [Licencja](#licencja)
    - [Warunki użytkowania](#warunki-użytkowania)
      - [1. Przyznane uprawnienia](#1-przyznane-uprawnienia)
      - [2. Obowiązkowe warunki](#2-obowiązkowe-warunki)
      - [3. Prawa autorskie](#3-prawa-autorskie)
      - [4. Wyłączenie gwarancji i ograniczenie odpowiedzialności](#4-wyłączenie-gwarancji-i-ograniczenie-odpowiedzialności)

## Główne komponenty

### System AMX

AMX (Abstract Machine eXecutor) to maszyna wirtualna, która wykonuje skrypty Pawn w SA-MP. SDK zapewnia obszerne wsparcie dla interakcji z AMX poprzez różne pliki C i headery:

#### Główne headery AMX

1. **amx.h**

    Główny plik nagłówkowy, który łączy wszystkie funkcje związane z AMX. Zawiera:
    - Podstawowe funkcje AMX do wykonywania skryptów
    - Zarządzanie pamięcią
    - Rejestrację funkcji natywnych
    - Obsługę ciągów znaków
    - Wsparcie UTF-8

    Kluczowe funkcje to:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    ```

2. **amx_cell.h**

    Definiuje podstawowe typy danych używane w systemie AMX:
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

    Zawiera niezbędne struktury do działania AMX:

    ```c
    typedef struct tagAMX {
        unsigned char _FAR *base;    // Adres bazowy
        unsigned char _FAR *data;    // Segment danych
        AMX_CALLBACK callback;       // Funkcja callback
        AMX_DEBUG debug;            // Callback debugowania
        cell cip;                   // Wskaźnik instrukcji kodu
        cell frm;                   // Baza ramki stosu
        cell hea;                   // Baza sterty
        cell stk;                   // Wskaźnik stosu
        // ... dodatkowe pola
    } AMX;
    ```

### Wsparcie platform

SDK zawiera solidną obsługę platform poprzez różne headery:

1. **amx_platform.h**

    Zapewnia wykrywanie i konfigurację platformy:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Obsługuje definicje specyficzne dla systemu operacyjnego:
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

### System wtyczek

#### plugincommon.h

Definiuje podstawowy interfejs wtyczek i struktury wsparcia:

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

Plik `amxplugin.c` jest kluczowym komponentem SA-MP SDK, który dostarcza implementacje funkcji AMX specyficzne dla platformy. Implementuje dwa różne podejścia w zależności od platformy i kompilatora:

1. **Implementacja Windows MSVC (32-bit)**
    - Używa nagich funkcji z asemblerem do bezpośredniego dostępu do tabeli funkcji
    - Zapewnia zoptymalizowaną wydajność poprzez bezpośrednie skoki do funkcji AMX
    - Przykładowa struktura:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Implementacja międzyplatformowa**
    - Używa wskaźników funkcji dla niezależności od platformy
    - Implementuje system oparty na makrach do definicji funkcji
    - Przykładowa struktura:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

Kluczowe funkcje:

3. **Zarządzanie tabelą funkcji**
    - Używa statycznego wskaźnika `pAMXFunctions` do przechowywania tabeli funkcji AMX
    - Zapewnia dostęp do wszystkich podstawowych funkcji AMX
    - Obsługuje rozwiązywanie funkcji w czasie wykonywania

4. **Optymalizacje specyficzne dla platformy**
    - Windows 32-bit: Używa nagich funkcji do bezpośredniej implementacji asemblera
    - Inne platformy: Używa pośrednictwa wskaźników funkcji
    - Specjalna obsługa dla systemów 64-bitowych

5. **Zaimplementowane kategorie funkcji**

    a. Funkcje zarządzania pamięcią:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. Funkcje wykonawcze:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. Zarządzanie symbolami:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. Obsługa ciągów znaków:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Funkcje wsparcia UTF-8
    
    e. Debugowanie i informacje:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Kompilacja warunkowa**
    - Obsługuje różne platformy poprzez dyrektywy preprocesora
    - Specjalna obsługa dla systemów 64-bitowych
    - Opcjonalne wsparcie JIT
    ```c
    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
            PLUGIN_AMX_EXPORT_Align64)
    #endif
    ```

7. **Integracja obsługi błędów**
    - Implementuje `amx_RaiseError` do raportowania błędów
    - Zachowuje kody błędów między wywołaniami funkcji
    - Integruje się z systemem debugowania AMX

### Funkcje natywne AMX

SDK zapewnia kompleksowe wsparcie dla tworzenia i zarządzania funkcjami natywnymi:

```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

Kluczowe operacje funkcji natywnych:
- Rejestracja poprzez `amx_Register`
- Dostęp i walidacja parametrów
- Obsługa wartości zwracanych
- Raportowanie błędów

## Szczegóły techniczne

### Zarządzanie pamięcią

SDK zapewnia kompleksowe narzędzia do zarządzania pamięcią:

1. **amx_memory.h**

   Obsługuje alokację pamięci i operacje specyficzne dla platformy:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```

2. **amx_alignment.h**

    Zarządza wymaganiami dotyczącymi wyrównania pamięci:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Operacje pamięci

SDK zawiera kilka funkcji do manipulacji pamięcią:

1. **Alokacja pamięci**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Alokuje pamięć na stercie AMX
    - Zwraca zarówno adresy AMX jak i fizyczne
    - Obsługuje wymagania wyrównania

2. **Dostęp do pamięci**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Konwertuje adresy AMX na adresy fizyczne
    - Waliduje dostęp do pamięci
    - Obsługuje granice pamięci

3. **Informacje o pamięci**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Pobiera informacje o układzie pamięci
    - Raportuje rozmiary segmentów
    - Przydatne do debugowania i optymalizacji

### Obsługa błędów

SDK zawiera kompleksowy system obsługi błędów zdefiniowany w `amx_constants.h`:

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

### Obsługa ciągów znaków

SDK zapewnia solidne możliwości obsługi ciągów znaków poprzez różne makra i funkcje:

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

### Operacje na ciągach znaków

1. **Długość ciągu**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Oblicza długość ciągu
    - Obsługuje ciągi spakowane i niespakowane
    - Zwraca długość w znakach

2. **Konwersja ciągów**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Konwertuje ciągi C na ciągi AMX
    - Wspiera formaty spakowane i niespakowane
    - Obsługuje konwersję Unicode

## Wsparcie Unicode

SDK zawiera kompleksowe wsparcie Unicode poprzez funkcje obsługi UTF-8:

```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Operacje Unicode

1. **Walidacja UTF-8**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - Waliduje ciągi zakodowane w UTF-8
    - Raportuje długość ciągu w znakach
    - Wykrywa błędy kodowania

2. **Konwersja znaków**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Wyodrębnia znaki Unicode
    - Obsługuje sekwencje wielobajtowe
    - Raportuje błędy parsowania

## Kompatybilność międzyplatformowa

SDK zapewnia kompatybilność międzyplatformową poprzez:

1. **Obsługa kolejności bajtów**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Obsługa ścieżek**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

## Wymagania systemowe

SDK wspiera wiele platform i kompilatorów:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Wsparcie kompilatorów

1. **Microsoft Visual C++**
   - Obsługa pragma
   - Tłumienie ostrzeżeń
   - Konwencje wywołań

2. **GCC**
   - Kontrole diagnostyczne
   - Specyfikacje atrybutów
   - Optymalizacje specyficzne dla platformy

3. **Clang**
   - Konfiguracje ostrzeżeń
   - Kompatybilność międzyplatformowa
   - Nowoczesne funkcje C++

## Najlepsze praktyki

Podczas korzystania z SA-MP SDK, należy wziąć pod uwagę następujące najlepsze praktyki:

1. **Zarządzanie pamięcią**
   - Zawsze czyść zaalokowane zasoby
   - Używaj odpowiedniego wyrównania pamięci
   - Obsługuj błędy pamięci z gracją
   - Monitoruj wykorzystanie sterty
   - Implementuj właściwe sprawdzanie granic pamięci
   - Używaj pul pamięci dla częstych alokacji
   - Czyść zasoby w odwrotnej kolejności alokacji

2. **Obsługa błędów**
   - Sprawdzaj wartości zwracane z funkcji AMX
   - Implementuj właściwą obsługę błędów w funkcjach natywnych
   - Używaj dostarczonych stałych błędów
   - Odpowiednio loguj błędy
   - Implementuj mechanizmy odzyskiwania po błędach
   - Dostarczaj znaczące komunikaty o błędach
   - Obsługuj błędy specyficzne dla systemu

3. **Rozwój międzyplatformowy**
   - Używaj typów niezależnych od platformy
   - Wykorzystuj dostarczone makra dla kodu specyficznego dla platformy
   - Testuj na wielu platformach
   - Obsługuj różnice w kolejności bajtów
   - Używaj właściwych separatorów ścieżek
   - Uwzględniaj różnice w systemach plików
   - Implementuj optymalizacje specyficzne dla platformy

4. **Aspekty wydajnościowe**
   - Używaj odpowiednich rozmiarów komórek
   - Implementuj wydajną obsługę ciągów znaków
   - Optymalizuj wywołania funkcji natywnych
   - Minimalizuj alokacje pamięci
   - Używaj odpowiednich struktur danych
   - Implementuj buforowanie tam, gdzie to właściwe
   - Profiluj krytyczne ścieżki kodu

Podczas pracy z funkcjonalnością `amxplugin.c`:

1. **Rozwój specyficzny dla platformy**
   - Uwzględniaj różnice platformowe w implementacjach funkcji
   - Testuj na systemach 32-bitowych i 64-bitowych
   - Obsługuj wymagania wyrównania specyficzne dla platformy
   - Waliduj wskaźnik tabeli funkcji przed użyciem
   - Implementuj odpowiednie sprawdzanie błędów dla każdej platformy
   - Uwzględniaj implikacje wydajnościowe różnych implementacji

2. **Zarządzanie tabelą funkcji**
   - Inicjalizuj tabelę funkcji przed użyciem
   - Weryfikuj dostępność funkcji
   - Obsługuj brakujące funkcje z gracją
   - Implementuj właściwe procedury czyszczenia
   - Buforuj często używane wskaźniki funkcji
   - Waliduj integralność tabeli funkcji

3. **Obsługa błędów**
   - Implementuj właściwe sprawdzanie błędów dla kodu specyficznego dla platformy
   - Odpowiednio obsługuj błędy wyrównania
   - Waliduj wpisy tabeli funkcji
   - Dostarczaj znaczące komunikaty o błędach
   - Implementuj mechanizmy odzyskiwania
   - Loguj błędy specyficzne dla platformy

## Struktury wewnętrzne

### Struktura nagłówka AMX

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Rozmiar "pliku"
    uint16_t magic;        // Sygnatura
    char    file_version;  // Wersja formatu pliku
    char    amx_version;   // Wymagana wersja AMX
    int16_t flags;         // Flagi
    int16_t defsize;      // Rozmiar rekordu definicji
    int32_t cod;          // Początkowa wartość COD - blok kodu
    int32_t dat;          // Początkowa wartość DAT - blok danych
    int32_t hea;          // Początkowa wartość HEA - początek sterty
    int32_t stp;          // Początkowa wartość STP - szczyt stosu
    int32_t cip;          // Początkowa wartość CIP - wskaźnik instrukcji kodu
    int32_t publics;      // Offset do funkcji publicznych
    int32_t natives;      // Offset do tabeli funkcji natywnych
    int32_t libraries;    // Offset do bibliotek
    int32_t pubvars;      // Offset do zmiennych publicznych
    int32_t tags;         // Offset do tagów
    int32_t nametable;    // Offset do tabeli nazw
} AMX_HEADER;
```

Ta struktura jest kluczowa dla zrozumienia formatu pliku AMX i sposobu, w jaki maszyna wirtualna ładuje i wykonuje skrypty.

## Zaawansowane funkcje

### Wsparcie kompilacji JIT

SDK zawiera wsparcie dla kompilacji Just-In-Time:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Interfejs debugowania

Wsparcie debugowania jest zapewniane przez:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Interfejs funkcji publicznych

SDK zapewnia kompleksowe wsparcie dla pracy z funkcjami publicznymi:

1. **Wyszukiwanie funkcji publicznych**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Lokalizuje funkcje publiczne po nazwie
    - Zwraca indeks funkcji
    - Waliduje istnienie funkcji

2. **Wykonywanie funkcji publicznych**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Wykonuje funkcje publiczne
    - Obsługuje wartości zwracane
    - Zarządza kontekstem wykonania

## Informacje o wersji

SDK zawiera stałe wersji do sprawdzania kompatybilności:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Kompatybilność wersji

SDK utrzymuje kompatybilność poprzez:
1. Sprawdzanie wersji pliku
2. Walidację wersji AMX
3. Weryfikację kompatybilności JIT
4. Wykrywanie funkcji
5. Obsługę wersji specyficznych dla platformy

## Licencja

Copyright © **SA-MP Programming Community**

To oprogramowanie jest licencjonowane na warunkach licencji MIT ("Licencja"); możesz korzystać z tego oprogramowania zgodnie z warunkami Licencji. Kopię Licencji można uzyskać pod adresem: [MIT License](https://opensource.org/licenses/MIT)

### Warunki użytkowania

#### 1. Przyznane uprawnienia

Niniejsza licencja bezpłatnie przyznaje każdej osobie otrzymującej kopię tego oprogramowania i powiązanych plików dokumentacji następujące prawa:

* Używanie, kopiowanie, modyfikowanie, łączenie, publikowanie, rozpowszechnianie, sublicencjonowanie i/lub sprzedaż kopii oprogramowania bez ograniczeń
* Zezwalanie osobom, którym oprogramowanie jest dostarczane, na to samo, pod warunkiem przestrzegania poniższych warunków

#### 2. Obowiązkowe warunki

Wszystkie kopie lub istotne części oprogramowania muszą zawierać:

* Powyższą informację o prawach autorskich
* Niniejsze zezwolenie
* Poniższe wyłączenie odpowiedzialności

#### 3. Prawa autorskie

Oprogramowanie i cała powiązana dokumentacja są chronione prawami autorskimi. **SA-MP Programming Community** zachowuje oryginalne prawa autorskie do oprogramowania.

#### 4. Wyłączenie gwarancji i ograniczenie odpowiedzialności

OPROGRAMOWANIE JEST DOSTARCZANE "TAK JAK JEST", BEZ JAKIEJKOLWIEK GWARANCJI, WYRAŹNEJ LUB DOROZUMIANEJ, W TYM MIĘDZY INNYMI GWARANCJI PRZYDATNOŚCI HANDLOWEJ, PRZYDATNOŚCI DO OKREŚLONEGO CELU I NIENARUSZANIA PRAW.

W ŻADNYM WYPADKU AUTORZY LUB POSIADACZE PRAW AUTORSKICH NIE PONOSZĄ ODPOWIEDZIALNOŚCI ZA JAKIEKOLWIEK ROSZCZENIA, SZKODY LUB INNE ZOBOWIĄZANIA, CZY TO W RAMACH DZIAŁAŃ UMOWNYCH, DELIKTOWYCH CZY INNYCH, WYNIKAJĄCYCH Z OPROGRAMOWANIA LUB ZWIĄZANYCH Z NIM LUB Z JEGO UŻYTKOWANIEM LUB INNYMI CZYNNOŚCIAMI W OPROGRAMOWANIU.

---

Szczegółowe informacje o licencji MIT można znaleźć pod adresem: https://opensource.org/licenses/MIT