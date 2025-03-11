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

SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) to kompleksowy zbiór plików C, nagłówków i komponentów, które umożliwiają programistom tworzenie wtyczek dla serwera SA-MP. Ten SDK dostarcza podstawę do rozszerzania funkcjonalności serwera SA-MP za pomocą funkcji natywnych, co pozwala programistom na implementację funkcji wykraczających poza możliwości skryptów Pawn.

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
      - [Główne nagłówki AMX](#główne-nagłówki-amx)
    - [Wsparcie dla platform](#wsparcie-dla-platform)
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
  - [Wsparcie dla Unicode](#wsparcie-dla-unicode)
    - [Operacje Unicode](#operacje-unicode)
  - [Kompatybilność międzyplatformowa](#kompatybilność-międzyplatformowa)
  - [Wymagania systemowe](#wymagania-systemowe)
    - [Wsparcie dla kompilatorów](#wsparcie-dla-kompilatorów)
  - [Najlepsze praktyki](#najlepsze-praktyki)
  - [Struktury wewnętrzne](#struktury-wewnętrzne)
    - [Struktura nagłówka AMX](#struktura-nagłówka-amx)
  - [Zaawansowane funkcje](#zaawansowane-funkcje)
    - [Wsparcie dla kompilacji JIT](#wsparcie-dla-kompilacji-jit)
    - [Interfejs debugowania](#interfejs-debugowania)
    - [Interfejs funkcji publicznych](#interfejs-funkcji-publicznych)
  - [Informacje o wersji](#informacje-o-wersji)
    - [Kompatybilność wersji](#kompatybilność-wersji)
  - [Licencja](#licencja)
    - [Warunki użytkowania](#warunki-użytkowania)
      - [1. Przyznane uprawnienia](#1-przyznane-uprawnienia)
      - [2. Warunki obowiązkowe](#2-warunki-obowiązkowe)
      - [3. Prawa autorskie](#3-prawa-autorskie)
      - [4. Wyłączenie gwarancji i ograniczenie odpowiedzialności](#4-wyłączenie-gwarancji-i-ograniczenie-odpowiedzialności)

## Główne komponenty

### System AMX

AMX (Abstract Machine eXecutor) to maszyna wirtualna, która wykonuje skrypty Pawn w SA-MP. SDK zapewnia szerokie wsparcie dla interakcji z systemem AMX poprzez różne pliki C i nagłówki.

#### Główne nagłówki AMX

1. **amx.h**

    Główny nagłówek, który konsoliduje wszystkie funkcje związane z AMX:
    - Główne funkcje do wykonywania skryptów
    - Zarządzanie pamięcią
    - Rejestracja funkcji natywnych
    - Obsługa ciągów znaków
    - Wsparcie dla UTF-8

    Kluczowe funkcje obejmują:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);         // Inicjalizuje instancję AMX
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index); // Wykonuje funkcję publiczną
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number); // Rejestruje funkcje natywne
    ```

2. **amx_platform.h**

    Odpowiada za wykrywanie i konfigurację platform:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```
    - Wykrywa systemy takie jak Linux, FreeBSD, OpenBSD i macOS.
    - Zawiera `sclinux.h` dla systemów typu Unix.
    - Identyfikuje architektury 64-bitowe:
      ```c
      #if defined _LP64 || defined WIN64 || defined _WIN64
          #define __64BIT__
      #endif
      ```
    - Oblicza wersję GCC, jeśli dotyczy:
      ```c
      #if defined __GNUC__
          #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #endif
      ```

3. **amx_constants.h**

    Definiuje podstawowe stałe dla działania AMX:
    - **Wersje**:
      ```c
      #define CUR_FILE_VERSION  9   // Aktualna wersja formatu pliku
      #define MIN_FILE_VERSION  6   // Minimalna obsługiwana wersja
      #define MIN_AMX_VERSION   10  // Minimalna wersja AMX
      #define MAX_FILE_VER_JIT  8   // Maksymalna wersja z obsługą JIT
      #define MIN_AMX_VER_JIT   8   // Minimalna wersja z obsługą JIT
      ```
    - **Kody magiczne**:
      ```c
      #define AMX_MAGIC_16    0xf1e2  // Dla komórek 16-bitowych
      #define AMX_MAGIC_32    0xf1e0  // Dla komórek 32-bitowych
      #define AMX_MAGIC_64    0xf1e1  // Dla komórek 64-bitowych
      ```
    - **Kody błędów**:
      ```c
      enum {
          AMX_ERR_NONE,         // Brak błędu
          AMX_ERR_EXIT,         // Skrypt zakończony
          AMX_ERR_ASSERT,       // Nieudane potwierdzenie
          AMX_ERR_STACKERR,     // Błąd stosu
          AMX_ERR_BOUNDS,       // Dostęp poza granice
          AMX_ERR_MEMACCESS,    // Nieprawidłowy dostęp do pamięci
          AMX_ERR_INVINSTR,     // Nieprawidłowa instrukcja
          AMX_ERR_STACKLOW,     // Stos zbyt niski
          AMX_ERR_HEAPLOW,      // Stos zbyt niski
          AMX_ERR_CALLBACK,     // Błąd wywołania zwrotnego
          AMX_ERR_NATIVE,       // Błąd funkcji natywnej
          AMX_ERR_DIVIDE,       // Dzielenie przez zero
          AMX_ERR_SLEEP,        // Aktywowany tryb uśpienia
          AMX_ERR_INVSTATE,     // Nieprawidłowy stan
          AMX_ERR_MEMORY = 16,  // Niewystarczająca pamięć
          AMX_ERR_FORMAT,       // Nieprawidłowy format
          AMX_ERR_VERSION,      // Niezgodna wersja
          AMX_ERR_NOTFOUND,     // Nie znaleziono zasobu
          AMX_ERR_INDEX,        // Nieprawidłowy indeks
          AMX_ERR_DEBUG,        // Błąd debugowania
          AMX_ERR_INIT,         // Niepowodzenie inicjalizacji
          AMX_ERR_USERDATA,     // Błąd danych użytkownika
          AMX_ERR_INIT_JIT,     // Niepowodzenie inicjalizacji JIT
          AMX_ERR_PARAMS,       // Nieprawidłowe parametry
          AMX_ERR_DOMAIN,       // Błąd domeny
          AMX_ERR_GENERAL,      // Błąd ogólny
      };
      ```
    - **Flagi**:
      ```c
      #define AMX_FLAG_DEBUG      0x02   // Tryb debugowania
      #define AMX_FLAG_COMPACT    0x04   // Kodowanie kompaktowe
      #define AMX_FLAG_SLEEP      0x08   // Obsługa uśpienia
      #define AMX_FLAG_NOCHECKS   0x10   // Brak kontroli bezpieczeństwa
      #define AMX_FLAG_NO_RELOC   0x200  // Brak relokacji
      #define AMX_FLAG_NO_SYSREQD 0x400  // Brak sysreq.d
      #define AMX_FLAG_SYSREQN    0x800  // Obsługa sysreq.n
      #define AMX_FLAG_NTVREG     0x1000 // Rejestracja natywna
      #define AMX_FLAG_JITC       0x2000 // Kompilacja JIT
      #define AMX_FLAG_BROWSE     0x4000 // Tryb przeglądania
      #define AMX_FLAG_RELOC      0x8000 // Relokacja włączona
      ```
    - **Kody wykonania**:
      ```c
      #define AMX_EXEC_MAIN   (-1)  // Wykonaj funkcję główną
      #define AMX_EXEC_CONT   (-2)  // Kontynuuj wykonywanie
      ```

4. **amx_memory.h**

    Zarządza alokacją pamięci:
    - Obsługa dla `alloca`:
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
    - Definiuje margines kompresji:
      ```c
      #if !defined AMX_COMPACTMARGIN
          #define AMX_COMPACTMARGIN 64
      #endif
      ```

5. **amx_calling.h**

    Definiuje konwencje wywoływania:
    - Dla funkcji natywnych i API:
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

    Definiuje standardowe typy całkowite:
    - Obsługa dla `stdint.h` lub definicje ręczne:
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

    Dostarcza przydatne makra:
    - **Obliczanie adresu**:
      ```c
      #define amx_Address(amx,addr) \
          (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))
      ```
    - **Obsługa ciągów znaków**:
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
    - **Liczenie parametrów**:
      ```c
      #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))
      ```
    - **Rejestracja funkcji**:
      ```c
      #define amx_RegisterFunc(amx, name, func) \
          amx_Register((amx), amx_NativeInfo((name),(func)), 1)
      ```

8. **amx_cell.h**

    Definiuje typy komórek:
    - Konfiguruje `PAWN_CELL_SIZE` (domyślnie: 32):
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
    - Obsługa liczb zmiennoprzecinkowych:
      ```c
      #if PAWN_CELL_SIZE==32
          #define amx_ftoc(f)   (*(cell*)&(f))  // Float na komórkę
          #define amx_ctof(c)   (*(float*)&(c))  // Komórka na float
      #elif PAWN_CELL_SIZE==64
          #define amx_ftoc(f)   (*(cell*)&(f))  // Double na komórkę
          #define amx_ctof(c)   (*(double*)&(c)) // Komórka na double
      #endif
      ```
    - Manipulacja znakami:
      ```c
      #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))  // Dla 32 bitów
      ```

9. **amx_structures.h**

    Definiuje główne struktury:
    - **AMX**:
      ```c
      typedef struct tagAMX {
          unsigned char _FAR *base;    // Adres bazowy
          unsigned char _FAR *data;    // Segment danych
          AMX_CALLBACK callback;       // Funkcja wywołania zwrotnego
          AMX_DEBUG debug;            // Wywołanie zwrotne debugowania
          cell cip;                   // Wskaźnik instrukcji kodu
          cell frm;                   // Baza ramki
          cell hea;                   // Baza sterty
          cell hlw;                   // Dolna granica sterty
          cell stk;                   // Wskaźnik stosu
          cell stp;                   // Wierzchołek stosu
          int flags;                  // Flagi
          long usertags[AMX_USERNUM]; // Tagi użytkownika
          void _FAR *userdata[AMX_USERNUM]; // Dane użytkownika
          int error;                  // Kod błędu
          int paramcount;             // Liczba parametrów
          cell pri;                   // Rejestr główny
          cell alt;                   // Rejestr alternatywny
          cell reset_stk;             // Zresetowany stos
          cell reset_hea;             // Zresetowana sterta
          cell sysreq_d;              // Adres sysreq.d
          #if defined JIT
              int reloc_size;         // Rozmiar relokacji
              long code_size;         // Rozmiar kodu
          #endif
      } AMX;
      ```
    - **AMX_HEADER**:
      ```c
      typedef struct tagAMX_HEADER {
          int32_t size;          // Rozmiar pliku
          uint16_t magic;        // Sygnatura
          char    file_version;  // Wersja pliku
          char    amx_version;   // Wersja AMX
          int16_t flags;         // Flagi
          int16_t defsize;       // Rozmiar definicji
          int32_t cod;           // Początek kodu
          int32_t dat;           // Początek danych
          int32_t hea;           // Początek sterty
          int32_t stp;           // Wierzchołek stosu
          int32_t cip;           // Początkowy wskaźnik instrukcji
          int32_t publics;       // Offset do funkcji publicznych
          int32_t natives;       // Offset do funkcji natywnych
          int32_t libraries;     // Offset do bibliotek
          int32_t pubvars;       // Offset do zmiennych publicznych
          int32_t tags;          // Offset do tagów
          int32_t nametable;     // Offset do tabeli nazw
      } AMX_HEADER;
      ```

### Wsparcie dla platform

SDK zawiera solidne wsparcie specyficzne dla platform poprzez różne nagłówki:

1. **amx_platform.h**

    Zapewnia wykrywanie i konfigurację platform:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Zarządza definicjami specyficznymi dla systemu operacyjnego:
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

Definiuje główny interfejs wtyczek i struktury wsparcia:
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

Plik `amxplugin.c` jest kluczowym komponentem SDK SA-MP, dostarczając implementacje specyficzne dla platform dla funkcji AMX. Implementuje dwa podejścia oparte na platformie i kompilatorze:

1. **Implementacja Windows MSVC (32-bit)**
    - Używa funkcji "nagich" z assemblerem dla bezpośredniego dostępu do tabeli funkcji:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Implementacja międzyplatformowa**
    - Używa wskaźników funkcji dla niezależności od platformy:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

**Kluczowe cechy**:

3. **Zarządzanie tabelą funkcji**
    - Używa statycznego wskaźnika `pAMXFunctions` do przechowywania tabeli funkcji AMX.
    - Zapewnia dostęp do wszystkich głównych funkcji AMX.
    - Zarządza rozwiązywaniem funkcji w czasie rzeczywistym.

4. **Optymalizacje specyficzne dla platform**
    - Windows 32-bit: Bezpośrednia implementacja w assemblerze z funkcjami nagimi.
    - Inne platformy: Pośrednictwo przez wskaźniki funkcji.
    - Specjalna obsługa dla systemów 64-bitowych.

5. **Kategorie zaimplementowanych funkcji**

    a. **Funkcje zarządzania pamięcią**:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. **Funkcje wykonawcze**:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. **Zarządzanie symbolami**:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. **Obsługa ciągów znaków**:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Funkcje wsparcia UTF-8
    
    e. **Debugowanie i informacje**:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Kompilacja warunkowa**
    - Obsługuje różne platformy za pomocą dyrektyw preprocesora.
    - Specjalna obsługa dla systemów 64-bitowych.
    - Opcjonalne wsparcie dla JIT:
      ```c
      #if defined _I64_MAX || defined HAVE_I64
          DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
              PLUGIN_AMX_EXPORT_Align64)
      #endif
      ```

7. **Integracja obsługi błędów**
    - Implementuje `amx_RaiseError` do zgłaszania błędów.
    - Zachowuje kody błędów przez wywołania funkcji.
    - Integruje się z systemem debugowania AMX.

### Funkcje natywne AMX

SDK zapewnia pełne wsparcie dla tworzenia i zarządzania funkcjami natywnymi:
```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

**Kluczowe operacje z funkcjami natywnymi**:
- Rejestracja za pomocą `amx_Register`.
- Dostęp i walidacja parametrów za pomocą `amx_NumParams`.
- Obsługa wartości zwracanych.
- Zgłaszanie błędów za pomocą `amx_RaiseError`.

## Szczegóły techniczne

### Zarządzanie pamięcią

SDK oferuje kompleksowe narzędzia do zarządzania pamięcią:

1. **amx_memory.h**

    Zarządza alokacją pamięci i operacjami specyficznymi dla platformy:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```
    - Definiuje `AMX_COMPACTMARGIN` na 64 domyślnie dla kompresji pamięci.

2. **amx_alignment.h**

    Zarządza wymaganiami wyrównania pamięci:
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
    - Alokuje pamięć na stercie AMX.
    - Zwraca adresy AMX i fizyczne.
    - Obsługuje wymagania wyrównania.

2. **Dostęp do pamięci**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Konwertuje adresy AMX na adresy fizyczne.
    - Weryfikuje dostęp do pamięci.
    - Zarządza granicami pamięci.

3. **Informacje o pamięci**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Pobiera informacje o układzie pamięci.
    - Raportuje rozmiary segmentów.
    - Przydatne do debugowania i optymalizacji.

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
            ((result)=(void*)alloca((result##_length_+1)*sizeof(*(result))))!=NULL) \
        amx_GetString((char*)(result),amx_Address(amx,param), \
                            sizeof(*(result))>1,result##_length_+1); \
        else (result)=NULL; \
    } while(0)
```
- Alternatywa dla `char*`:
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

### Operacje na ciągach znaków

1. **Długość ciągu znaków**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Oblicza długość ciągu znaków.
    - Obsługuje ciągi spakowane i niespakowane.
    - Zwraca długość w znakach.

2. **Konwersja ciągu znaków**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Konwertuje ciągi C na ciągi AMX.
    - Obsługuje formaty spakowane i niespakowane.
    - Zarządza konwersją Unicode.

## Wsparcie dla Unicode

SDK zapewnia pełne wsparcie dla Unicode poprzez funkcje obsługi UTF-8:
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
    - Weryfikuje ciągi zakodowane w UTF-8.
    - Raportuje długość ciągu w znakach.
    - Wykrywa błędy kodowania.

2. **Konwersja znaków**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Wyodrębnia znaki Unicode.
    - Obsługuje sekwencje wielobajtowe.
    - Raportuje błędy parsowania.

## Kompatybilność międzyplatformowa

SDK zapewnia kompatybilność międzyplatformową dzięki:

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

3. **Typy niezależne od platformy**
    - Zdefiniowane w `amx_types.h` dla spójności.

## Wymagania systemowe

SDK obsługuje wiele platform i kompilatorów:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Wsparcie dla kompilatorów

1. **Microsoft Visual C++**
    - Zarządzanie pragmami.
    - Tłumienie ostrzeżeń.
    - Konwencje wywoływania poprzez `amx_calling.h`.

2. **GCC**
    - Kontrole diagnostyczne.
    - Specyfikacje atrybutów.
    - Optymalizacje specyficzne dla platformy.

3. **Clang**
    - Konfiguracje ostrzeżeń.
    - Kompatybilność międzyplatformowa.
    - Nowoczesne funkcje C++.

## Najlepsze praktyki

Podczas korzystania z SDK SA-MP należy rozważyć następujące najlepsze praktyki:

1. **Zarządzanie pamięcią**
    - Zawsze zwalniaj zaalokowane zasoby.
    - Używaj odpowiedniego wyrównania pamięci.
    - Obsługuj błędy pamięci z gracją.
    - Monitoruj użycie sterty.
    - Wdrażaj odpowiednie sprawdzanie granic pamięci.
    - Używaj pul pamięci dla częstych alokacji.
    - Zwalniaj zasoby w odwrotnej kolejności alokacji.

2. **Obsługa błędów**
    - Sprawdzaj wartości zwracane przez funkcje AMX.
    - Wdrażaj odpowiednią obsługę błędów w funkcjach natywnych.
    - Używaj dostarczonych stałych błędów.
    - Odpowiednio rejestruj błędy.
    - Wdrażaj mechanizmy odzyskiwania po błędach.
    - Dostarczaj znaczące komunikaty o błędach.
    - Obsługuj błędy specyficzne dla systemu.

3. **Rozwój międzyplatformowy**
    - Używaj typów niezależnych od platformy.
    - Wykorzystuj dostarczone makra dla kodu specyficznego dla platformy.
    - Testuj na wielu platformach.
    - Obsługuj różnice w kolejności bajtów.
    - Używaj odpowiednich separatorów ścieżek.
    - Uwzględniaj różnice w systemach plików.
    - Wdrażaj optymalizacje specyficzne dla platformy.

4. **Uwagi dotyczące wydajności**
    - Używaj odpowiednich rozmiarów komórek.
    - Wdrażaj efektywną obsługę ciągów znaków.
    - Optymalizuj wywołania funkcji natywnych.
    - Minimalizuj alokacje pamięci.
    - Używaj odpowiednich struktur danych.
    - Wdrażaj buforowanie tam, gdzie to odpowiednie.
    - Profiluj krytyczne ścieżki kodu.

Podczas pracy z funkcjonalnością `amxplugin.c`:

1. **Rozwój specyficzny dla platformy**
    - Uwzględniaj różnice platformowe w implementacjach funkcji.
    - Testuj na systemach 32-bitowych i 64-bitowych.
    - Obsługuj wymagania wyrównania specyficzne dla platformy.
    - Weryfikuj wskaźnik tabeli funkcji przed użyciem.
    - Wdrażaj odpowiednie sprawdzanie błędów dla każdej platformy.
    - Uwzględniaj wpływ na wydajność różnych implementacji.

2. **Zarządzanie tabelą funkcji**
    - Inicjalizuj tabelę funkcji przed użyciem.
    - Weryfikuj dostępność funkcji.
    - Obsługuj brakujące funkcje z gracją.
    - Wdrażaj odpowiednie procedury czyszczenia.
    - Buforuj często używane wskaźniki funkcji.
    - Weryfikuj integralność tabeli funkcji.

3. **Obsługa błędów**
    - Wdrażaj odpowiednie sprawdzanie błędów dla kodu specyficznego dla platformy.
    - Obsługuj błędy wyrównania w odpowiedni sposób.
    - Weryfikuj wpisy w tabeli funkcji.
    - Dostarczaj znaczące komunikaty o błędach.
    - Wdrażaj mechanizmy odzyskiwania.
    - Rejestruj błędy specyficzne dla platformy.

## Struktury wewnętrzne

### Struktura nagłówka AMX

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Rozmiar "pliku"
    uint16_t magic;        // Sygnatura
    char    file_version;  // Wersja formatu pliku
    char    amx_version;   // Wymagana wersja AMX
    int16_t flags;         // Flagi
    int16_t defsize;       // Rozmiar rekordu definicji
    int32_t cod;           // Początkowa wartość COD - blok kodu
    int32_t dat;           // Początkowa wartość DAT - blok danych
    int32_t hea;           // Początkowa wartość HEA - początek sterty
    int32_t stp;           // Początkowa wartość STP - wierzchołek stosu
    int32_t cip;           // Początkowa wartość CIP - wskaźnik instrukcji kodu
    int32_t publics;       // Offset do funkcji publicznych
    int32_t natives;       // Offset do tabeli funkcji natywnych
    int32_t libraries;     // Offset do bibliotek
    int32_t pubvars;       // Offset do zmiennych publicznych
    int32_t tags;          // Offset do tagów
    int32_t nametable;     // Offset do tabeli nazw
} AMX_HEADER;
```

Ta struktura jest kluczowa dla zrozumienia formatu pliku AMX i sposobu, w jaki maszyna wirtualna ładuje i wykonuje skrypty.

## Zaawansowane funkcje

### Wsparcie dla kompilacji JIT

SDK zawiera wsparcie dla kompilacji Just-In-Time:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Interfejs debugowania

Wsparcie dla debugowania jest zapewnione poprzez:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Interfejs funkcji publicznych

SDK zapewnia pełne wsparcie dla pracy z funkcjami publicznymi:

1. **Wyszukiwanie funkcji publicznych**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Lokalizuje funkcje publiczne po nazwie.
    - Zwraca indeks funkcji.
    - Weryfikuje istnienie funkcji.

2. **Wykonywanie funkcji publicznych**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Wykonuje funkcje publiczne.
    - Obsługuje wartości zwracane.
    - Zarządza kontekstem wykonania.

## Informacje o wersji

SDK zawiera stałe wersji do weryfikacji kompatybilności:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Kompatybilność wersji

SDK utrzymuje kompatybilność poprzez:
1. Weryfikację wersji pliku.
2. Walidację wersji AMX.
3. Weryfikację kompatybilności JIT.
4. Wykrywanie funkcji.
5. Zarządzanie wersjami specyficznymi dla platformy.

## Licencja

Copyright © **SA-MP Programming Community**

To oprogramowanie jest licencjonowane na warunkach Licencji MIT ("Licencja"); możesz używać tego oprogramowania zgodnie z warunkami Licencji. Kopię Licencji można uzyskać pod adresem: [MIT License](https://opensource.org/licenses/MIT)

### Warunki użytkowania

#### 1. Przyznane uprawnienia

Niniejsza licencja przyznaje bezpłatnie każdej osobie uzyskującej kopię tego oprogramowania i powiązanych plików dokumentacji następujące prawa:
- Używanie, kopiowanie, modyfikowanie, łączenie, publikowanie, dystrybucję, udzielanie sublicencji i/lub sprzedaż kopii oprogramowania bez ograniczeń.
- Zezwalanie osobom, którym oprogramowanie jest dostarczane, na to samo, pod warunkiem przestrzegania poniższych warunków.

#### 2. Warunki obowiązkowe

Wszystkie kopie lub istotne części oprogramowania muszą zawierać:
- Powyższe powiadomienie o prawach autorskich.
- Niniejsze pozwolenie.
- Poniższe wyłączenie odpowiedzialności.

#### 3. Prawa autorskie

Oprogramowanie i cała powiązana dokumentacja są chronione prawami autorskimi. **SA-MP Programming Community** zachowuje oryginalne prawa autorskie do oprogramowania.

#### 4. Wyłączenie gwarancji i ograniczenie odpowiedzialności

OPROGRAMOWANIE JEST DOSTARCZANE "TAK JAK JEST", BEZ JAKIEJKOLWIEK GWARANCJI, WYRAŹNEJ LUB DOROZUMIANEJ, W TYM MIĘDZY INNYMI GWARANCJI PRZYDATNOŚCI HANDLOWEJ, PRZYDATNOŚCI DO OKREŚLONEGO CELU I NIENARUSZALNOŚCI PRAW.

W ŻADNYM WYPADKU AUTORZY ANI POSIADACZE PRAW AUTORSKICH NIE BĘDĄ ODPOWIEDZIALNI ZA JAKIEKOLWIEK ROSZCZENIA, SZKODY LUB INNE ZOBOWIĄZANIA, CZY TO W RAMACH UMOWY, CZYNU NIEDOZWOLONEGO, CZY W INNY SPOSÓB, WYNIKAJĄCE Z OPROGRAMOWANIA, ZWIĄZANE Z NIM LUB Z JEGO UŻYCIEM LUB INNYMI DZIAŁANIAMI W OPROGRAMOWANIU.

---

Aby uzyskać szczegółowe informacje o Licencji MIT, odwiedź: https://opensource.org/licenses/MIT