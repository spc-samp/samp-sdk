# SAMP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Nowoczesne, header-only, wysokopoziomowe SDK C++ do tworzenia pluginów i modułów dla SA-MP.**

</div>

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

## Spis Treści

- [SAMP SDK](#samp-sdk)
  - [Języki](#języki)
  - [Spis Treści](#spis-treści)
  - [1. Wprowadzenie i Filozofia Projektowania](#1-wprowadzenie-i-filozofia-projektowania)
    - [Problem ze Standardowym API C SA-MP](#problem-ze-standardowym-api-c-sa-mp)
    - [Rozwiązanie SAMP SDK: Abstrakcja z Bezpieczeństwem i Wydajnością](#rozwiązanie-samp-sdk-abstrakcja-z-bezpieczeństwem-i-wydajnością)
    - [Model Header-Only: Zalety i Implikacje](#model-header-only-zalety-i-implikacje)
  - [2. Konfiguracja i Środowisko](#2-konfiguracja-i-środowisko)
    - [Wymagania Kompilacji](#wymagania-kompilacji)
    - [Zalecana Struktura Plików](#zalecana-struktura-plików)
    - [Podstawowe Makra Konfiguracyjne\*\*](#podstawowe-makra-konfiguracyjne)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definicje i Stałe SA-MP (`samp_defs.hpp`)](#definicje-i-stałe-sa-mp-samp_defshpp)
  - [3. Kompleksowy Przewodnik po API](#3-kompleksowy-przewodnik-po-api)
    - [3.1. Cykl Życia Pluginu](#31-cykl-życia-pluginu)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Interceptowanie Zdarzeń z Pawna](#32-plugin_public-interceptowanie-zdarzeń-z-pawna)
      - [Składnia i Deklaracja](#składnia-i-deklaracja)
      - [Automatyczne Marshalling Parametrów](#automatyczne-marshalling-parametrów)
      - [Kontrola Przepływu: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#kontrola-przepływu-plugin_public_continue-vs-plugin_public_stop)
    - [3.3. `Plugin_Native`: Tworzenie Funkcji Natywnych w C++](#33-plugin_native-tworzenie-funkcji-natywnych-w-c)
      - [Składnia i Stała Sygnatura](#składnia-i-stała-sygnatura)
      - [Automatyczna Rejestracja Natywów](#automatyczna-rejestracja-natywów)
      - [Ekstrakcja Parametrów: `Register_Parameters` vs. `Native_Params`](#ekstrakcja-parametrów-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Pełne API: `Get`, `Get_REF`, `Set_REF`)](#native_params-pełne-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Zwracanie Wartości](#zwracanie-wartości)
    - [3.4. Makra `Pawn_*`: Wywoływanie Funkcji Pawna z C++](#34-makra-pawn_-wywoływanie-funkcji-pawna-z-c)
      - [`Pawn_Native(NomeDaNativa, ...)`](#pawn_nativenomedanativa-)
      - [`Pawn_Public(NomeDaPublic, ...)`](#pawn_publicnomedapublic-)
      - [`Pawn(NomeDaFuncao, ...)`](#pawnnomedafuncao-)
      - [Składnia i Konwencje](#składnia-i-konwencje)
      - [Marshalling Parametrów Wejściowych](#marshalling-parametrów-wejściowych)
      - [Marshalling Parametrów Wyjściowych (Referencje: `int&`, `float&`, `std::string&`)](#marshalling-parametrów-wyjściowych-referencje-int-float-stdstring)
      - [Obiekt `Callback_Result`: Pełna Analiza](#obiekt-callback_result-pełna-analiza)
      - [**3.5. `Plugin_Module`: Zarządzanie Modułami Dynamicznymi**](#35-plugin_module-zarządzanie-modułami-dynamicznymi)
      - [Składnia i Cel](#składnia-i-cel)
      - [Cykl Życia Modułu](#cykl-życia-modułu)
      - [Korzyści z Modularizacji](#korzyści-z-modularizacji)
    - [3.6. `Plugin_Call`: Wywoływanie Wewnętrznych Natywów Pluginu](#36-plugin_call-wywoływanie-wewnętrznych-natywów-pluginu)
      - [Składnia i Zalety Wydajności](#składnia-i-zalety-wydajności)
    - [**3.7. Funkcje Użytkowe SDK**](#37-funkcje-użytkowe-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Zalecane)](#stdstring-plugin_formatconst-char-format--zalecane)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Szczegóły Implementacji)](#stdstring-samp_sdkformatconst-char-format--szczegóły-implementacji)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. **Wewnętrzna Anatomia i Architektura SDK**](#4-wewnętrzna-anatomia-i-architektura-sdk)
    - [4.1. `core.hpp`: Minimalistyczne Fundamenty](#41-corehpp-minimalistyczne-fundamenty)
    - [**4.2. `platform.hpp` i `version.hpp`: Kompatybilność i Metadane**](#42-platformhpp-i-versionhpp-kompatybilność-i-metadane)
    - [4.3. `function_hook.hpp`: Silnik Interceptowania x86](#43-function_hookhpp-silnik-interceptowania-x86)
    - [4.4. `interceptor_manager.hpp`: Kontroler Hooków AMX](#44-interceptor_managerhpp-kontroler-hooków-amx)
    - [4.5. `amx_manager.hpp`: Zarządzanie Instancjami `AMX*`](#45-amx_managerhpp-zarządzanie-instancjami-amx)
    - [4.6. `public_dispatcher.hpp`: Router Callbacks `Plugin_Public`](#46-public_dispatcherhpp-router-callbacks-plugin_public)
    - [4.7. `native.hpp`: Zarządzanie i Wywoływanie Natywów Pluginu](#47-nativehpp-zarządzanie-i-wywoływanie-natywów-pluginu)
    - [4.8. `callbacks.hpp` \& `amx_memory.hpp`: Wywołania C++ -\> Pawn i RAII](#48-callbackshpp--amx_memoryhpp-wywołania-c---pawn-i-raii)
    - [4.9. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Abstrakcyjny Dostęp do AMX](#49-amx_apihpp--amx_helpershpp--amx_defsh-abstrakcyjny-dostęp-do-amx)
  - [5. Kompilacja i Wdrożenie](#5-kompilacja-i-wdrożenie)
    - [Wymagania Architektury i Platformy](#wymagania-architektury-i-platformy)
    - [Przykłady Poleceń Kompilacji](#przykłady-poleceń-kompilacji)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW na Windows)**](#gcc--clang-mingw-na-windows)
    - [Wskazówki Dotyczące Dystrybucji](#wskazówki-dotyczące-dystrybucji)
  - [Licencja](#licencja)
    - [Warunki użytkowania](#warunki-użytkowania)
      - [1. Przyznane uprawnienia](#1-przyznane-uprawnienia)
      - [2. Obowiązkowe warunki](#2-obowiązkowe-warunki)
      - [3. Prawa autorskie](#3-prawa-autorskie)
      - [4. Wyłączenie gwarancji i ograniczenie odpowiedzialności](#4-wyłączenie-gwarancji-i-ograniczenie-odpowiedzialności)

## 1. Wprowadzenie i Filozofia Projektowania

### Problem ze Standardowym API C SA-MP

API pluginów SA-MP to interfejs programowania w C. Choć funkcjonalny i fundamentalny, przedstawia wyzwania nieodłącznie związane z programowaniem niskopoziomowym:
- **Ręczne Zarządzanie Pamięcią:** Funkcje takie jak `amx_Allot` i `amx_Release` wymagają od programisty jawnego alokowania i zwalniania pamięci na stosie AMX. Jest to częste źródło wycieków pamięci i błędów wykonawczych.
- **Słabe Typowanie i Ręczne Konwersje:** Parametry są przekazywane jako tablica `cell`i, wymuszając jawne (i często niebezpieczne) konwersje między `cell`, `int`, `float` i `char*`.
- **Wielość i Powtarzalność Kodu:** Ekstrakcja wielu parametrów z tablicy `cell* params`, obsługa długości stringów i zarządzanie stosem AMX dla wywołań zwrotnych C++ do Pawna wymaga powtarzalnego kodu.
- **Kruchość Interfejsu:** Brak weryfikacji w czasie kompilacji (bezpieczeństwo typów) oznacza, że błędy w przekazywaniu parametrów lub typów mogą pozostać niezauważone aż do wykonania, powodując awarie lub niezdefiniowane zachowania.

### Rozwiązanie SAMP SDK: Abstrakcja z Bezpieczeństwem i Wydajnością

SAMP SDK rozwiązuje te problemy, dostarczając potężną warstwę abstrakcji w C++:
- **RAII (Resource Acquisition Is Initialization):** Automatyczne zarządzanie pamięcią w AMX. `Amx_Scoped_Memory` gwarantuje, że zaalokowana pamięć zostanie zwolniona.
- **Bezpieczeństwo Typów:** Automatyczna i bezpieczna konwersja parametrów między C++ a Pawn. Bezpośrednio operujesz na `int`, `float`, `std::string`.
- **Zwięzła i Idiomatyczna Składnia:** Makra i szablony zapewniają czyste API, które bardziej przypomina nowoczesne C++ niż tradycyjne API C.
- **Solidne Interceptowanie:** Zaawansowany silnik hookingu umożliwia przezroczyste interceptowanie callbacks z Pawna (`Plugin_Public`) i dynamiczną rejestrację natywów.
- **Wysoka Wydajność:** Obszerne wykorzystanie haszowania w czasie kompilacji (FNV1a), buforowanie funkcji i optymalizacje `thread_local` w celu zminimalizowania narzutu abstrakcji.

### Model Header-Only: Zalety i Implikacje

SDK składa się wyłącznie z plików nagłówkowych (`.hpp`, `.h`).
- **Zalety:**
   - **Uproszczona Integracja:** Brak bibliotek do budowania, linkowania czy dystrybuowania. Wystarczy dołączyć nagłówki.
   - **Optymalizacje Kompilatora:** Kompilator ma pełny wgląd w kod SDK i twój plugin, co pozwala na agresywne inlining i optymalizacje czasu linkowania, co może skutkować szybszymi binarkami.
- **Implikacje:**
   - **Czas Kompilacji:** Dla bardzo dużych projektów kompilacja może trwać dłużej z powodu wielokrotnego dołączania kodu SDK. Jest to łagodzone przez zabezpieczenia przed wielokrotnym dołączaniem i naturę "dołączaj tylko to, co potrzebne" w C++.
   - **Makra Implementacji:** Potrzeba makra `SAMP_SDK_IMPLEMENTATION` jest konsekwencją modelu header-only, aby uniknąć redefinicji symboli.

## 2. Konfiguracja i Środowisko

### Wymagania Kompilacji

- **Kompilator C++:** Kompatybilny z C++14 lub nowszym (SDK wykorzystuje funkcje C++14, C++17 i C++20 dla specyficznych optymalizacji, ale C++14 to minimum).
   - GCC (wersja 7+)
   - Clang (wersja 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Architektura:** **x86 (32-bit)**. SA-MP działa wyłącznie na tej architekturze. SDK zawiera sprawdzenia w `platform.hpp`, które wyemitują błędy kompilacji, jeśli zostanie wykryta nieprawidłowa architektura.
- **System Operacyjny:** Windows lub Linux.

### Zalecana Struktura Plików

Dla przejrzystości i organizacji, powszechne jest umieszczanie SDK w podfolderze `samp-sdk`.

```
my_plugin/
├── samp-sdk/
│   ├── // Inne pliki SDK
│   └── samp_sdk.hpp             // Główny nagłówek do dołączenia
│
├── src/
│   ├── main.cpp                  // Gdzie zdefiniowano SAMP_SDK_IMPLEMENTATION
│   └── my_custom_logic.cpp       // Opcjonalne, do organizacji kodu
│
└── CMakeLists.txt (lub .vcxproj, Makefile)
```

### Podstawowe Makra Konfiguracyjne**

Zawsze definiuj te makra *przed* dołączeniem `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Cel:** Sygnalizuje kompilatorowi, że ten plik `.cpp` powinien wygenerować implementacje funkcji eksportu pluginu (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **SDK automatycznie zajmuje się eksportowaniem tych funkcji, eliminując potrzebę plików `.def` (na Windowsie) lub deklaracji `__attribute__((visibility("default")))` (na Linuxie) dla tych funkcji.**
- **Wpływ Techniczny:** Bez tego makra linker nie znajdzie niezbędnych eksportów, a serwer SA-MP nie będzie w stanie załadować twojego pluginu.
- **Podstawowa Zasada:** **Zdefiniuj to makro w TYLKO JEDNYM pliku `.cpp` w całym swoim projekcie.** Zdefiniowanie go w więcej niż jednym pliku spowoduje błąd linkowania "podwójnego symbolu".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // Makro sprawia, że SDK automatycznie eksportuje niezbędne funkcje.
#include "samp-sdk/samp_sdk.hpp"

// ... twój kod pluginu ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Cel:** Włącza funkcjonalności SDK związane z interakcją ze środowiskiem AMX (maszyna wirtualna Pawna).
- **Aktywowane Funkcjonalności:**
   - Deklaracja i rejestracja natywów C++ za pomocą `Plugin_Native`.
   - Callbacks `OnAmxLoad(AMX* amx)` i `OnAmxUnload(AMX* amx)`.
   - Makro `Plugin_Call` do wywoływania natywów samego pluginu.
- **Wpływ Techniczny:** Gdy to makro jest zdefiniowane, SDK automatycznie zbiera wszystkie twoje `Plugin_Native`s. W funkcji `Supports()`, flaga `SUPPORTS_AMX_NATIVES` jest automatycznie dodawana.
- **Elastyczność:** **Możesz zdefiniować to makro w wielu plikach `.cpp`**. System rejestracji statycznej SDK (`Native_Registrar`) skonsoliduje wszystkie natywy z różnych jednostek kompilacji w jedną globalną listę.

```cpp
// my_natives.cpp (może być oddzielny plik od main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Tylko do włączenia Plugin_Native
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Cel:** Włącza callback `OnProcessTick()`, który jest regularnie wywoływany przez serwer.
- **Wpływ Techniczny:** Automatycznie dodaje flagę `SUPPORTS_PROCESS_TICK` w funkcji `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logika wykonywana co "tick" serwera (np. 20ms)
    // Ostrożnie z ciężkimi operacjami tutaj!
}
```

### Definicje i Stałe SA-MP (`samp_defs.hpp`)

Ten plik dostarcza wszystkie znane stałe i limity SA-MP, takie jak `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, itp. Jest automatycznie dołączany przez `samp_sdk.hpp` i powinien być używany w celu zapewnienia kompatybilności i czytelności kodu.

## 3. Kompleksowy Przewodnik po API

### 3.1. Cykl Życia Pluginu

Następujące funkcje są punktami wejścia i wyjścia twojego pluginu, automatycznie eksportowanymi przez SDK.

#### `bool OnLoad()`

- **Opis:** Pierwsza funkcja wywoływana przez serwer SA-MP po pomyślnym załadowaniu twojego pluginu do pamięci.
- **Użycie:** Idealne do inicjalizacji wszelkich systemów, ładowania konfiguracji, otwierania połączeń z bazami danych lub ładowania modułów (`Plugin_Module`).
- **Zwrot:**
   - `true`: Plugin został pomyślnie zainicjowany, a ładowanie jest kontynuowane.
   - `false`: Plugin nie powiódł się z inicjalizacją. Ładowanie zostanie przerwane, a plugin zostanie wyładowany.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Inicjalizowanie MojegoPluginu v1.0...");

    // Przykład: Ładowanie modułu (więcej szczegółów w sekcji 3.5)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Moduł bazy danych załadowany.")) {
        Samp_SDK::Log("BŁĄD: Nie udało się załadować modułu bazy danych!");

        return false; // Przerywa ładowanie głównego pluginu
    }

    return true;
}
```

#### `void OnUnload()`

- **Opis:** Ostatnia funkcja wywoływana przez serwer SA-MP przed zwolnieniem twojego pluginu z pamięci.
- **Użycie:** Idealne do czyszczenia zasobów, zamykania połączeń, zapisywania stanów i upewniania się, że żadne zasoby nie wyciekły. SDK automatycznie zarządza wyładowywaniem modułów (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MójPlugin wyładowany. Zwalnianie zasobów...");
    // Żadne manualne działania nie są wymagane dla modułów załadowanych przez Plugin_Module;
    // SDK zajmuje się tym.
}
```

#### `unsigned int GetSupportFlags()`

- **Opis:** Informuje serwer SA-MP, które funkcje twój plugin obsługuje i chce używać.
- **Użycie:** **Zawsze zwracaj `SUPPORTS_VERSION` (lub `SAMP_PLUGIN_VERSION`).** Inne flagi (`SUPPORTS_AMX_NATIVES`, `SUPPORTS_PROCESS_TICK`) są automatycznie dodawane przez SDK, jeśli zdefiniowane są makra `SAMP_SDK_WANT_AMX_EVENTS` i `SAMP_SDK_WANT_PROCESS_TICK`. Upraszcza to konserwację i zapobiega błędom.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // SDK automatycznie dodaje niezbędne flagi.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Wymaga:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Opis:** Wywoływana za każdym razem, gdy nowy skrypt Pawn (Gamemode lub Filterscript) jest ładowany i inicjowany na serwerze.
- **Użycie:** Jeśli potrzebujesz specyficznej logiki dla każdego skryptu AMX, takiej jak rejestrowanie niestandardowych natywów (chociaż `Plugin_Native` robi to automatycznie), lub inicjalizowanie danych specyficznych dla skryptu.

```cpp
// main.cpp (z zdefiniowanym SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxLoad(AMX* amx) {
    // amx reprezentuje nową instancję załadowanego skryptu.
    // Możesz na przykład wywołać konkretną publiczną funkcję w tym skrypcie:
    // Pawn_Public_OnAmx("OnMyPluginLoaded", amx); // Hipotetyczny przykład bardziej zaawansowanego API.
    Samp_SDK::Log("Skrypt AMX załadowany: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Wymaga:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Opis:** Wywoływana, gdy skrypt Pawn jest wyładowywany z serwera.
- **Użycie:** Do czyszczenia wszelkich specyficznych zasobów, które zaalokowałeś lub skojarzyłeś z danym `AMX*`.

```cpp
// main.cpp (z zdefiniowanym SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Skrypt AMX wyładowany: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Wymaga:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Opis:** Wywoływana wielokrotnie co "tick" serwera (zazwyczaj 20 razy na sekundę, czyli co 50ms).
- **Użycie:** Do ciągłej logiki w tle, timerów, aktualizacji stanu, które nie zależą od zdarzeń graczy, lub synchronizacji danych.
- **Ostrożnie:** Unikaj operacji blokujących lub intensywnych obliczeniowo, ponieważ mogą one powodować opóźnienia na serwerze.

```cpp
// main.cpp (z zdefiniowanym SAMP_SDK_WANT_PROCESS_TICK)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Co 10 sekund (20 ticków/sek * 10 sek = 200 ticków)
        Samp_SDK::Log("Serwer aktywny przez %d sekund.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Interceptowanie Zdarzeń z Pawna

Makro `Plugin_Public` jest głównym mostem do odbierania callbacków z Pawna w twoim kodzie C++.

#### Składnia i Deklaracja

- `Plugin_Public(NazwaPubliczna, Typ1 Param1, Typ2 Param2, ...)`
- Nazwa funkcji C++, którą deklarujesz, **musi być taka sama** jak nazwa callbacka Pawn (np. `OnPlayerConnect`).
- Typy parametrów C++ (`int`, `float`, `std::string`) są automatycznie konwertowane przez SDK.

```cpp
// Interceptuje OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    // ...
}
```

#### Automatyczne Marshalling Parametrów

SDK automatycznie zajmuje się odczytywaniem `cell stack` z AMX i konwersją na określone typy C++:
- `int`: Konwertowany bezpośrednio z `cell`.
- `float`: Konwertowany z `cell` za pomocą `amx::AMX_CTOF`.
- `std::string`: SDK odczytuje adres stringa w AMX, alokuje `std::string` w C++ i kopiuje zawartość.

#### Kontrola Przepływu: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

Wartość zwracana przez twoją funkcję `Plugin_Public` jest kluczowa i określa przepływ wykonania callbacka:
- `return PLUGIN_PUBLIC_CONTINUE;` (wartość `1`): Wskazuje, że wykonanie callbacka powinno **kontynuować się**. Jeśli istnieją inne pluginy, które również przechwytują ten callback, zostaną one wywołane. Następnie oryginalna funkcja `public` w skrypcie Pawn zostanie wywołana.
- `return PLUGIN_PUBLIC_STOP;` (wartość `0`): Wskazuje, że wykonanie callbacka powinno zostać **przerwane**. Żaden inny plugin ani oryginalna funkcja `public` w skrypcie Pawn nie zostanie wywołana dla tego zdarzenia. Jest to idealne rozwiązanie do zaimplementowania systemu, który "nadpisuje" lub "blokuje" domyślne zachowanie SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Zamraża gracza
        Pawn_Native(SendClientMessage, playerid, -1, Pawn_Format("Gracz %d zamrożony.", playerid));

        return PLUGIN_PUBLIC_STOP; // Zapobiega przetwarzaniu polecenia przez inne skrypty.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Pozwala na przetwarzanie innych poleceń.
}
```

### 3.3. `Plugin_Native`: Tworzenie Funkcji Natywnych w C++

`Plugin_Native` pozwala na rozszerzenie funkcjonalności Pawna o wysokowydajny kod C++.

#### Składnia i Stała Sygnatura

- `Plugin_Native(NazwaNatywnej, AMX* amx, cell* params)`
- Funkcja C++ musi mieć dokładnie tę sygnaturę: `cell NazwaNatywnej(AMX* amx, cell* params)`.
- `NazwaNatywnej` to nazwa, której będą używać skrypty Pawn.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementacja ...
    return 0;
}
```

#### Automatyczna Rejestracja Natywów

> [!NOTE]
> **Nie musisz** ręcznie wywoływać `amx_Register`. SDK wykrywa wszystkie twoje `Plugin_Native`s (w dowolnym pliku `.cpp` z `SAMP_SDK_WANT_AMX_EVENTS`) i automatycznie je rejestruje w każdym załadowanym skrypcie AMX (`OnAmxLoad`).

#### Ekstrakcja Parametrów: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Opis:** Prostszy pomocnik do sekwencyjnej ekstrakcji wielu parametrów.
- **Użycie:** `Register_Parameters(zmienna1, zmienna2, ...)`
- **Ograniczenia:** Dla parametrów wejściowych. Nie obsługuje parametrów opcjonalnych ani dostępu przez indeks.
- **Obsługiwane Typy:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Ekstrahuje 3 parametry
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (Pełne API: `Get`, `Get_REF`, `Set_REF`)

- **Opis:** Klasa opakowująca, która zapewnia obiektowo zorientowany interfejs do dostępu do parametrów natywnych. Bardziej potężna dla złożonych scenariuszy.
- **Konstrukcja:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Opis:** Zwraca liczbę parametrów przekazanych do natywnego.
- **Użycie:** Niezbędne do obsługi parametrów opcjonalnych.

###### `p.Get<T>(size_t index)`

- **Opis:** Wyodrębnia parametr wejściowy według indeksu i konwertuje go na typ `T`.
- **Obsługiwane Typy:** `int`, `float`, `std::string`.

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

- **Opis:** Pobiera wartość parametru **referencyjnego** (wskaźnik Pawn) i zapisuje ją w `out_value`.
- **Użycie:** Do odczytywania wartości, które zostały przekazane przez referencję z Pawna.
- **Zwrot:** `true`, jeśli adres AMX jest poprawny, `false` w przeciwnym razie.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Pobiera wartości z referencji (Pawn przekazał adresy)
    p.Get_REF(1, health); // Odczytuje wartość Float:health
    p.Get_REF(2, money);   // Odczytuje wartość money
    
    Samp_SDK::Log("Gracz %d, Zdrowie: %.1f, Pieniądze: %d", playerid, health, money);
    
    // Teraz je modyfikujemy
    health = 50.0f;
    money += 100;
    
    // I zapisujemy je z powrotem do pamięci Pawna
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Opis:** Zwraca `std::optional<T>` w celu odczytania parametru referencyjnego. Bezpieczniejsze dla C++17 i nowszych.

###### `p.Set_REF<T>(size_t index, T value)`

- **Opis:** Zapisuje wartość `T` do parametru **referencyjnego** Pawn (adres, który Pawn przekazał).
- **Użycie:** Do modyfikowania wartości, które zostały przekazane przez referencję, sprawiając, że Pawn widzi zmianę.
- **Zwrot:** `true`, jeśli zapis powiódł się, `false` w przeciwnym razie.

#### Zwracanie Wartości

- Twoja funkcja `Plugin_Native` powinna zwracać `cell`.
- Aby zwrócić `int` lub `bool`, użyj rzutowania na `cell`.
- Aby zwrócić `float`, użyj `amx::AMX_FTOC(mój_float)`.

```cpp
// Zwraca bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    int playerid = p.Get<int>(0);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Zwraca float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Zwraca 100.0f
}
```

### 3.4. Makra `Pawn_*`: Wywoływanie Funkcji Pawna z C++

Te makra są odwrotnością `Plugin_Public` i `Plugin_Native`: pozwalają twojemu kodowi C++ wywoływać funkcje Pawna.

#### `Pawn_Native(NomeDaNativa, ...)`

- **Cel:** Zalecany sposób wywoływania natywnych funkcji SA-MP (lub innych pluginów) z C++.
- **Mechanizm:** Wyszukuje wskaźnik natywnej w wewnętrznym cache'u SDK (wypełnianym przez `Amx_Register_Detour`). Jeśli zostanie znaleziony, wykonuje natywną w środowisku `Amx_Sandbox` (fałszywa i izolowana instancja AMX).
- **Wydajność:** Najbardziej wydajne, ponieważ unika kosztownego wyszukiwania `publics` i bezpośrednio wchodzi w interakcję ze wskaźnikiem natywnej.

#### `Pawn_Public(NomeDaPublic, ...)`

- **Cel:** Wywołuje konkretną funkcję publiczną w skrypcie Pawn.
- **Mechanizm:** Przegląda instancje `AMX*` zarządzane przez `Amx_Manager`, wyszukuje `public` po nazwie i ją wykonuje.
- **Wydajność:** Mniej wydajne niż `Pawn_Native` z powodu wyszukiwania i rzeczywistego `amx_Exec`. Ogólnie `publics` są wolniejsze niż `natives`.
- **Użycie:** Idealne do wywoływania niestandardowych zdarzeń w trybie gry/filtrach, które nie są natywami.

#### `Pawn(NomeDaFuncao, ...)`

- **Cel:** Makro ułatwiające, które próbuje odgadnąć, czy funkcja jest natywna czy publiczna.
- **Mechanizm:** Najpierw próbuje wywołać jako `Pawn_Native`. Jeśli to się nie powiedzie (natywna nie zostanie znaleziona), próbuje wywołać jako `Pawn_Public`.
- **Wydajność:** Może być nieco wolniejsze niż `Pawn_Native`, jeśli funkcja jest natywna, z powodu podwójnej próby wyszukiwania. Dla `publics` wydajność jest taka sama jak `Pawn_Public`.
- **Użycie:** Dla funkcji, co do których nie jesteś pewien, czy są natywne czy publiczne, lub aby uniknąć powtarzalnego kodu próbującego jedną, a potem drugą.

#### Składnia i Konwencje

- **Nazwa Funkcji:** Zawsze używaj nazwy funkcji Pawn **bezpośrednio, bez cudzysłowów**. SDK wewnętrznie przekonwertuje ją na string.
- **Parametry:** Przekaż parametry C++ bezpośrednio.

```cpp
// Poprawnie:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Błąd (ale technicznie zadziałałoby ze względu na hash, unikaj):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling Parametrów Wejściowych

SDK konwertuje twoje typy C++ na format `cell` AMX, zarządzając pamięcią w razie potrzeby:
-   `int`, `bool`, `long`, `enum` -> `cell`
-   `float`, `double` -> `cell` (używając `amx::AMX_FTOC`)
-   `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (alokuje pamięć w AMX, kopiuje string i przekazuje adres `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling Parametrów Wyjściowych (Referencje: `int&`, `float&`, `std::string&`)

Jest to kluczowa funkcjonalność zapewniająca wygodę i bezpieczeństwo. Dla funkcji Pawn, które oczekują wskaźnika (referencji), SDK automatyzuje cały proces alokacji/dealokacji pamięci i kopiowania danych.

- **Jak używać:** Wystarczy przekazać zmienną przez referencję (`&`).
- **Mechanizm:** SDK alokuje pamięć na stosie AMX, przekazuje adres AMX do funkcji Pawn, oczekuje, że funkcja Pawn wypełni ten adres, odczytuje wartość z powrotem i zwalnia pamięć AMX. Wszystko w sposób przezroczysty.
- **Z `std::string&`:** SDK alokuje bufor standardowy (256 komórek) w AMX dla stringa.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Lokalizacja %s (ID:%d): Pozycja(%.2f, %.2f, %.2f) Wnętrze:%d Świat:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### Obiekt `Callback_Result`: Pełna Analiza

Wszystkie wywołania `Pawn_*` zwracają obiekt `Callback_Result`. Ten obiekt jest bezpiecznym wrapperem dla wyniku wywołania Pawn.

- `Callback_Result() noexcept`: Konstruktor domyślny, wskazuje na niepowodzenie (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Konstruktor dla sukcesu lub niepowodzenia z wartością.
- `explicit operator bool() const`: Pozwala używać `if (result)` do sprawdzenia, czy wywołanie powiodło się.
- `operator cell() const`: Pozwala przekonwertować wynik na `cell` w celu uzyskania wartości.
- `float As_Float() const`: Ułatwienie do uzyskania wyniku jako `float`.
- `cell Value() const`: Zwraca surową wartość `cell`.
- `bool Success() const`: Zwraca `true`, jeśli wywołanie Pawn powiodło się.
- `int Get_Amx_Error() const`: Zwraca kod błędu AMX, jeśli wywołanie nie powiodło się (0 dla sukcesu).

```cpp
// Przykład: Pobieranie zdrowia gracza.
// Natywna GetPlayerHealth(playerid, &Float:health) oczekuje playerid i referencji do zdrowia.
int playerid = 0; // Przykład ID gracza
float player_health = 0.0f;

// Wywołujemy GetPlayerHealth, przekazując playerid i player_health przez referencję.
// SDK zajmie się marshallingiem dla parametru wyjściowego 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Sprawdza, czy wywołanie powiodło się (operator bool)
    // Wartość zwracana przez result.As_Float() lub result (operator cell)
    // byłaby wartością zwracaną przez *natywną*, a nie parametrem wyjściowym.
    // Wartość zdrowia została już zaktualizowana w 'player_health' dzięki marshallingowi parametru wyjściowego.
    Samp_SDK::Log("Gracz %d ma %.1f zdrowia.", playerid, player_health);
} else {
    // Wywołanie nie powiodło się, być może gracz nie istnieje lub natywna nie została znaleziona.
    Samp_SDK::Log("Błąd podczas pobierania zdrowia gracza %d. Kod AMX: %d", playerid, result.Get_Amx_Error());
}

// Dla natywów, które zwracają wartość i używają parametrów wyjściowych (mniej powszechne, ale możliwe),
// użyłbyś obu:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param jest już zaktualizowany
// }
```

#### **3.5. `Plugin_Module`: Zarządzanie Modułami Dynamicznymi**

Makro `Plugin_Module` pozwala Twojemu pluginowi działać jako „ładowarka” dla innych pluginów, tworząc modułową i rozszerzalną architekturę. Moduł załadowany w ten sposób jest traktowany jako plugin pierwszej klasy, z własnym cyklem życia zdarzeń zarządzanym przez plugin nadrzędny.

#### Składnia i Cel

- `Plugin_Module(const char* nome_do_arquivo_base, const char* diretorio_do_modulo, const char* mensagem_sucesso_opcional)`
- `nome_do_arquivo_base`: *Bazowa* nazwa pliku modułu, **bez rozszerzenia** (np. dla `my_module.dll` lub `my_module.so`, użyj `"my_module"`). SDK automatycznie doda odpowiednie rozszerzenie `.dll` lub `.so`.
- `diretorio_do_modulo`: Ścieżka do katalogu, w którym znajduje się plik modułu (np. `"plugins/my_custom_modules"`). **Nie podawaj tutaj nazwy pliku.** SDK połączy pełną ścieżkę (`diretorio_do_modulo/nome_do_arquivo_base.ext`).
- `mensagem_sucesso_opcional`: Opcjonalna wiadomość, która zostanie zapisana w konsoli serwera, jeśli moduł zostanie pomyślnie załadowany.

```cpp
// main.cpp, wewnątrz OnLoad()

// Ładuje moduł 'core_logic.dll' (lub 'core_logic.so')
// znajdujący się w folderze 'modules/custom/' serwera.
if (!Plugin_Module("core_logic", "modules/custom", "Moduł Logiki Głównej załadowany pomyślnie!"))
    return (Samp_SDK::Log("BŁĄD KRYTYCZNY: Nie udało się załadować modułu 'core_logic'!"), false);

// Ładuje moduł 'admin_system.dll' (lub 'admin_system.so')
// znajdujący się bezpośrednio w folderze 'plugins/' serwera.
if (!Plugin_Module("admin_system", "plugins", "Moduł Administracyjny aktywowany."))
    Samp_SDK::Log("OSTRZEŻENIE: Moduł Administracyjny nie mógł zostać załadowany.");
```

#### Cykl Życia Modułu

Moduł musi eksportować funkcje `Load`, `Unload` oraz `Supports`, tak jak zwykły plugin. SDK zarządza cyklem życia modułu w następujący sposób:

- **Ładowanie:** Gdy wywoływane jest `Plugin_Module`, SDK:
   1. Tworzy pełną ścieżkę do pliku (np. `modules/custom/core_logic.dll`).
   2. Używa `Dynamic_Library` (`LoadLibrary`/`dlopen`), aby załadować binarium.
   3. **Pobiera wskaźniki do WSZYSTKICH funkcji cyklu życia modułu:**
      - **Wymagane:** `Load`, `Unload`, `Supports`. Jeśli którejś brakuje, ładowanie modułu nie powiedzie się.
      - **Opcjonalne:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Wywołuje funkcję `Load` modułu, przekazując `ppData` z głównego pluginu.
   5. Jeśli `Load` zwróci `true`, moduł zostanie dodany do wewnętrznej listy załadowanych modułów.

- **Przekazywanie Zdarzeń:** Plugin nadrzędny **automatycznie przekazuje** zdarzenia do wszystkich załadowanych modułów.
 > [!IMPORTANT]
 > Aby zdarzenia były poprawnie przekazywane, **plugin nadrzędny** (ten, który wywołuje `Plugin_Module`) musi być skonfigurowany do odbierania tych zdarzeń.
 > - Aby `AmxLoad` i `AmxUnload` działały w modułach, plugin nadrzędny musi zdefiniować makro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Aby `ProcessTick` działał w modułach, plugin nadrzędny musi zdefiniować makro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Rozładowanie:** Podczas `OnUnload` głównego pluginu, SDK rozładowuje wszystkie moduły załadowane przez `Plugin_Module`. Odbywa się to w **odwrotnej kolejności** ładowania (ostatni załadowany moduł jest rozładowywany jako pierwszy), co jest kluczowe dla zarządzania zależnościami i zapewnienia poprawnego zwalniania zasobów.

#### Korzyści z Modularizacji

- **Organizacja Kodu:** Podziel duże pluginy na mniejsze, łatwe do zarządzania komponenty, każdy w osobnym pliku modułu.
- **Ponowne Wykorzystanie:** Twórz ogólne moduły (np. moduł bazy danych, moduł zaawansowanego systemu logowania), które mogą być używane przez różne pluginy, promując ponowne wykorzystanie kodu.
- **Niezależne Komponenty:** Twórz moduły, które są **całkowicie sterowane zdarzeniami i niezależne**. Moduł może mieć własne `Plugin_Native`s, przechwytywać `Plugin_Public`s i mieć własną logikę `OnProcessTick`, działając jak samodzielny plugin, ale ładowany przez nadrzędny.
- **Dynamiczne Aktualizacje:** W kontrolowanych scenariuszach umożliwia aktualizację części systemu (poprzez zastąpienie pliku modułu `.dll` lub `.so`) bez konieczności ponownego kompilowania i restartowania głównego pluginu lub całego serwera (choć wymaga to ścisłego zarządzania wersjami i kompatybilnością).

### 3.6. `Plugin_Call`: Wywoływanie Wewnętrznych Natywów Pluginu

Użyj `Plugin_Call`, aby wywołać `Plugin_Native` zdefiniowaną **wewnątrz twojego własnego pluginu**.

#### Składnia i Zalety Wydajności

- `Plugin_Call(NazwaNatywnej, Param1, Param2, ...)`
- **Zaleta:** Unika narzutu związanego z wyszukiwaniem natywnej w tablicy natywów AMX. SDK utrzymuje bezpośrednią mapę hashów nazw do wskaźników funkcji dla swoich własnych natywów, co czyni to najszybszym sposobem ich wewnętrznego wywoływania.
- **Wymaga:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logika do sprawdzenia poziomu
    return (playerid % 2 == 0) ? 1 : 0; // Przykład: poziom parzysty dla parzystych ID
}

void CheckAllPlayersLevel() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Wywołuje własną natywną funkcję
                Samp_SDK::Log("Gracz %d jest na wysokim poziomie!", i);
        }
    }
}
```

### **3.7. Funkcje Użytkowe SDK**

#### `Samp_SDK::Log(const char* format, ...)`

- **Opis:** Wyświetla komunikaty w konsoli serwera i w pliku `server_log.txt`. Bezpieczny wrapper dla `logprintf`.
- **Użycie:** Do debugowania, komunikatów o statusie i błędów.
- **Mechanizm:** Wewnętrznie, SDK pobiera wskaźnik do `logprintf` poprzez `ppData[PLUGIN_DATA_LOGPRINTF]`. Funkcja bezpiecznie obsługuje formatowanie stringa.

```cpp
// W dowolnym miejscu twojego pluginu
Samp_SDK::Log("Plugin został zainicjalizowany wartością %d i stringiem '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Zalecane)

- **Opis:** Bezpiecznie formatuje string (podobnie do `sprintf`) i zwraca `std::string`. Jest to **zalecany i najbardziej idiomatyczny sposób** formatowania stringów do użytku w twoim pluginie.
- **Użycie:** Idealne do konstruowania sformatowanych wiadomości przed przekazaniem ich do `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, lub do innych potrzeb związanych ze stringami w twoim kodzie C++.
- **Mechanizm:** Wewnętrznie, `Plugin_Format` jest makrem, które wywołuje `Samp_SDK::Format`. Wykorzystuje `vsnprintf` do określenia dokładnego rozmiaru sformatowanego stringa i alokuje `std::string` z wystarczającą pojemnością, zapobiegając przepełnieniom bufora.

```cpp
int playerid = 0; // Przykład ID
int health = 50;
std::string status_message = Plugin_Format("Gracz %d, twoje aktualne zdrowie to %d.", playerid, health); // Użycie makra Plugin_Format
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, status_message);

// Może być również używany do logów wewnętrznych
Samp_SDK::Log(Plugin_Format("DEBUG: Przetwarzanie statusu dla ID %d", playerid).c_str());
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Szczegóły Implementacji)

- **Opis:** Funkcja implementacji leżąca u podstaw formatowania stringów, znajdująca się w przestrzeni nazw `Samp_SDK`.
- **Użycie:** Zazwyczaj nie jest wywoływana bezpośrednio przez użytkownika. Makro `Plugin_Format` jest dostarczane jako udogodnienie dla tej funkcji, zgodne z konwencją nazewnictwa innych makr SDK (`Plugin_Public`, `Plugin_Native`). Wywołałbyś ją bezpośrednio tylko, gdybyś z jakiegoś konkretnego powodu chciał uniknąć makra `Plugin_Format`.

```cpp
// Przykład, jak działa Samp_SDK::Format, ale preferuj Plugin_Format
std::string raw_status = Samp_SDK::Format("Tylko do użytku wewnętrznego: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Opis:** Konwertuje adres stringa AMX (`cell amx_addr`) na `std::string` C++.
- **Użycie:** Głównie wewnątrz `Plugin_Native`, gdy potrzebujesz dostępu do stringów, które nie są automatycznie konwertowane przez `Register_Parameters` lub `Native_Params` (np. jeśli parametr Pawn jest `const` `string` i nie został zadeklarowany jako `std::string` w twoim `Plugin_Native` lub `Plugin_Public` do automatycznego marshallingu).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Pobiera adres stringa w AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String z AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. **Wewnętrzna Anatomia i Architektura SDK**

Ta sekcja odkrywa mechanizmy leżące u podstaw SAMP SDK, badając jego architekturę, kluczowe komponenty i sposób ich interakcji w celu zapewnienia wysokopoziomowej abstrakcji. Głębokie zrozumienie tych wewnętrznych mechanizmów pozwala programiście optymalizować wykorzystanie SDK, debugować złożone problemy, a nawet rozszerzać jego funkcjonalność.

### 4.1. `core.hpp`: Minimalistyczne Fundamenty

`Samp_SDK::Core` to `singleton`, który służy jako początkowy i scentralizowany punkt dostępu do niskopoziomowych danych dostarczanych przez środowisko pluginu SA-MP. Jego główną odpowiedzialnością jest hermetyzacja i udostępnianie podstawowych funkcjonalności.

- **`Samp_SDK::Core::Instance()`**:
   - **Opis:** Zwraca jedyną globalną instancję klasy `Core`. Jest to wzorzec projektowy `singleton`, aby zapewnić spójny i scentralizowany dostęp do danych pluginu (`ppData`).
   - **Mechanizm:** Instancja jest inicjowana tylko raz, gdy `Core::Instance().Load(ppData)` jest wywoływane w funkcji `Load()` twojego pluginu.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Opis:** Umożliwia bezpieczny i indeksowany dostęp do wskaźników funkcji API AMX. Tablica `pAMXFunctions` (otrzymana poprzez `ppData[PLUGIN_DATA_AMX_EXPORTS]`) zawiera adresy krytycznych funkcji, takich jak `amx_Exec`, `amx_Register`, itp.
   - **Wpływ:** Zamiast używać `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, SDK oferuje bezpieczne typowo wrappery w przestrzeni nazw `amx::` (np. `amx::Exec(...)`), czyniąc kod bardziej czytelnym i mniej podatnym na błędy rzutowania.
   - **Przykład Wewnętrzny (`amx_api.hpp`):**
      ```cpp
      // Uproszczony fragment amx_api.hpp
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
   - **Opis:** Wskaźnik do funkcji `logprintf` SA-MP, która jest standardowym interfejsem do drukowania wiadomości w konsoli serwera i w pliku `server_log.txt`.
   - **Mechanizm:** `Samp_SDK::Log` jest bezpiecznym wrapperem, który wykorzystuje ten wskaźnik, zapewniając poprawne wyświetlanie twoich wiadomości w środowisku SA-MP.

### **4.2. `platform.hpp` i `version.hpp`: Kompatybilność i Metadane**

Te nagłówki są podstawą przenośności i optymalizacji SDK, dostosowując je do różnych środowisk kompilacji i wykorzystując specyficzne funkcje nowoczesnego C++.

- **Wykrywanie Platformy i Architektury:**
   - **Mechanizm:** Wykorzystuje makra preprocesora (`#if defined(WIN32)`, `#if defined(__linux__)`, itp.) do identyfikacji systemu operacyjnego.
   - **Sprawdzanie Architektury:** Zawiera `static_assert` lub `#error`, aby upewnić się, że plugin jest kompilowany dla x86 (32-bit), co jest krytycznym wymogiem dla kompatybilności z SA-MP i mechanizmem hookingu.
   - **Zarządzanie Eksportem Symboli:**
      - `SAMP_SDK_EXPORT`: Makro zdefiniowane w `platform.hpp`, które rozszerza się do `extern "C"` i, w systemie Linux, dodaje `__attribute__((visibility("default")))`. W systemie Windows, zapewnia tylko `extern "C"`, ponieważ SDK używa `pragma comment(linker, "/EXPORT:...")` (dla MSVC) lub standardu MinGW do eksportowania głównych funkcji.
      - Gwarantuje to, że funkcje cyklu życia pluginu (`Supports`, `Load`, `Unload` itd.) są poprawnie eksportowane z twojego DLL/SO, niezależnie od środowiska kompilacji, **bez potrzeby plików `.def` ani ręcznego dodawania `__attribute__((visibility("default")))`** w twojej implementacji.
   - **Przykład (`platform.hpp` - odpowiedni fragment):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // Dla MSVC, eksport jest zarządzany przez pragma linker commands
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // Dla GCC/Clang w systemie Linux używamy atrybutu widoczności
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... inne definicje ...
      ```
   - **Przykład (`samp_sdk.hpp` - odpowiedni fragment implementacji):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // W systemie Windows (MSVC) używamy pragma comment do eksportowania funkcji.
          // To eliminuje potrzebę pliku .def.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... inne eksporty ...
      #endif

      // Implementacja eksportowanych funkcji
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... inne funkcje ...
      #endif
      ```

- **Makra Optymalizacji i Przewidywania Rozgałęzień:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mechanizm:** `__forceinline` (MSVC) lub `__attribute__((always_inline)) inline` (GCC/Clang). Zdecydowanie sugeruje kompilatorowi, aby wstawiał treść funkcji bezpośrednio w miejscu wywołania, eliminując narzut związany z rzeczywistym wywołaniem funkcji.
      - **Użycie:** Stosowane do małych i krytycznych dla wydajności funkcji w SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mechanizm:** `[[likely]]` / `[[unlikely]]` (C++20) lub `__builtin_expect` (GCC/Clang). Wskazówki dla kompilatora, która ścieżka `if/else` jest bardziej prawdopodobna.
      - **Wpływ:** Pomaga kompilatorowi generować bardziej wydajny kod dla przewidywania rozgałęzień (branch prediction), zmniejszając opóźnienie CPU.
      - **Przykład (`platform.hpp`):**
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

- **Standardowe Definicje C++ (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mechanizm:** Makra zdefiniowane na podstawie wartości `__cplusplus` i `_MSVC_LANG`.
   - **Użycie:** Pozwalają SDK wykorzystywać nowsze funkcjonalności C++ (takie jak `std::apply` i `if constexpr` z C++17, lub `std::is_same_v` z C++17), gdy są dostępne, zachowując jednocześnie kompatybilność ze starszymi standardami.
   - **Przykład (`version.hpp` - użycie `if constexpr`):**
      ```cpp
      // Uproszczony fragment public_dispatcher.hpp
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

### 4.3. `function_hook.hpp`: Silnik Interceptowania x86

Ten nagłówek definiuje niskopoziomowy mechanizm do wykonywania hooków (interceptacji) funkcji, który jest fundamentalny dla działania SDK. Jest on ściśle zależny od architektury x86 (32-bitowej).

- **`X86_Detour`**:
   - **Opis:** Klasa, która hermetyzuje logikę nadpisywania początku funkcji w pamięci instrukcją skoku do funkcji obejścia.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mechanizm:** W architekturze x86 instrukcja skoku (`JMP`) względna zazwyczaj ma 5 bajtów: `0xE9` (opcode dla JMP near, relative), po którym następuje 4 bajty reprezentujące przesunięcie (offset) adresu celu w stosunku do następnej instrukcji.
      - **Przykład instrukcji:** `E9 XX XX XX XX` (gdzie `XX` to bajty przesunięcia).
   - **`Apply(void* target, void* detour)`**:
      - **Działanie:** Instaluje hook. Najpierw przechowuje oryginalne `JUMP_INSTRUCTION_SIZE` bajtów funkcji `target` (`original_bytes_`). Następnie oblicza względny adres `detour` w stosunku do `target` i nadpisuje początek `target` instrukcją `JMP`.
      - **Przykład obliczania adresu względnego:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Adres obejścia - (Adres celu + Rozmiar instrukcji JMP)
         ```
   - **`Revert()`**:
      - **Działanie:** Odinstalowuje hook, przywracając `original_bytes_` w funkcji `target`.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mechanizm:** W systemie Windows używa `VirtualProtect`; w systemie Linux `mprotect`. Te wywołania systemowe zmieniają uprawnienia strony pamięci, w której znajduje się funkcja, na `EXECUTE_READWRITE` (Windows) lub `PROT_WRITE | PROT_EXEC` (Linux), umożliwiając modyfikację kodu w czasie wykonywania.
      - **Przykład (`Unprotect_Memory`):**
         ```cpp
         // Uproszczony fragment function_hook.hpp
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
   - **Opis:** Wrapper C++ `type-safe` dla `X86_Detour`, zapewniający poprawność typów wskaźników funkcji.
   - `Install(void* target, void* detour)`: Hermetyzuje wywołanie `X86_Detour::Apply`.
   - `Uninstall()`: Hermetyzuje wywołanie `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Mechanizm Bezpieczeństwa (Zabezpieczenie przed Rekursją):** Ta funkcja jest krytyczna, aby uniknąć nieskończonych pętli, gdy obejście musi wywołać oryginalną funkcję. **Tymczasowo odinstalowuje hook (`detour_.Revert()`)**, wywołuje oryginalną funkcję (`Get_Original()(args...)`), a następnie **ponownie instaluje hook (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Licznik, który zapewnia, że hook zostanie ponownie zainstalowany tylko po zakończeniu najwyższego poziomu wywołania oryginalnego, umożliwiając bezpieczne rekurencyjne wywołania oryginalnej funkcji (jeśli oryginalna funkcja jest rekurencyjna, na przykład). `thread_local` gwarantuje, że `recursion_guard` jest izolowany dla każdego wątku, co jest ważne w środowiskach wielowątkowych.
      - **Przykład (`Call_Original` z Scope_Guard):**
         ```cpp
         // Uproszczony fragment function_hook.hpp
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

### 4.4. `interceptor_manager.hpp`: Kontroler Hooków AMX

Ten `singleton` jest centrum interakcji SDK z maszyną wirtualną AMX SA-MP. Koordynuje instalację hooków dostarczonych przez `function_hook.hpp` na funkcjach API AMX udostępnionych przez serwer, przekierowując przepływ wykonania do logiki SDK.

- **`Activate()` / `Deactivate()`**:
   - **Opis:** Publiczne metody do instalowania i odinstalowywania wszystkich niezbędnych hooków. Wywoływane odpowiednio w `OnLoad()` i `OnUnload()` twojego pluginu.
   - **Mechanizm:** Pobiera wskaźniki funkcji AMX (takich jak `amx_Register`, `amx_Exec` itp.) za pomocą `Core::Instance().Get_AMX_Export(...)` i instaluje obejścia.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Zahaczona Funkcja:** `amx_Register`
   - **Cel:** Przechwytuje rejestrację *wszystkich* natywów (przez SA-MP, inne pluginy lub gamemode).
   - **Akcja:** Wywołuje `Interceptor_Manager::Instance().Cache_Natives()` w celu przechowywania wskaźników i nazw natywów w wewnętrznym cache'u.
   - **Wpływ:** Ten cache jest fundamentalny dla wydajności `Pawn_Native`, umożliwiając niezwykle szybkie wyszukiwanie wskaźnika natywnego zamiast kosztownego wyszukiwania w AMX.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Zahaczona Funkcja:** `amx_Exec`
   - **Cel:** **Jest to najważniejszy hook.** Przechwytuje *każde* wykonanie kodu w AMX, w tym wywołanie `publics` z Pawna.
   - **Mechanizm Interceptowania `Plugin_Public`:**
      1. Gdy `amx_Exec` jest wywoływane dla `public` (lub `AMX_EXEC_MAIN`), wykonywane jest `Amx_Exec_Detour`.
      2. Pobiera nazwę `public` (używając `Get_Public_Name_By_Index` lub `tl_public_name`).
      3. Sprawdza `Public_Dispatcher::Instance().Dispatch()` w celu weryfikacji, czy istnieją zarejestrowane obsługi C++ dla tej nazwy.
      4. Jeśli istnieją obsługi, wykonuje je. `Public_Dispatcher` obsługuje `marshalling` parametrów z AMX na poprawne typy C++.
      5. Na podstawie wartości zwracanej przez `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), decyduje, czy wywołać oryginalny `amx_Exec` (`Get_Amx_Exec_Hook().Call_Original(...)`), czy zakończyć wykonanie `public` Pawn.
      6. **Manipulacja Stosem:** Jeśli wykonanie `public` Pawn zostanie przerwane (`PLUGIN_PUBLIC_STOP`), `Amx_Exec_Detour` koryguje stos AMX (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`), aby uniknąć niespójności.
   - **Przykład (`Amx_Exec_Detour`):**
      ```cpp
      // Uproszczony fragment interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          // ... logika do określenia nazwy publicznej ...
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
   - **Zahaczona Funkcja:** `amx_FindPublic`
   - **Cel:** Przechwytuje wyszukiwanie `publics` po nazwie.
   - **Mechanizm "Ghost Publics":** Jeśli oryginalny `amx_FindPublic` nie znajdzie `public` w Pawn, ale `Public_Dispatcher` ma zarejestrowaną obsługę C++ dla tej nazwy, ten hook zwraca `AMX_ERR_NONE` i specjalny `index` (`PLUGIN_EXEC_GHOST_PUBLIC`). Sprawia to, że API SA-MP "myśli", że `public` istnieje, co pozwala na przechwycenie kolejnego wywołania `amx_Exec` (dla tego specjalnego indeksu) przez `Amx_Exec_Detour`, który następnie przekierowuje do obsługi C++.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Używana do przekazywania nazwy `public` do `Amx_Exec_Detour`, gdy wykryta zostanie "ghost public", ponieważ `amx_Exec` otrzymuje tylko indeks, a nie nazwę.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Zahaczone Funkcje:** `amx_Init` / `amx_Cleanup`
   - **Cel:** Zarządzanie listą aktywnych instancji `AMX*`.
   - **Akcja:** `Amx_Init_Detour` wywołuje `Amx_Manager::Instance().Add_Amx()`, a `Amx_Cleanup_Detour` wywołuje `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Zarządzanie Instancjami `AMX*`

Ten `singleton` utrzymuje dynamiczny rejestr wszystkich maszyn wirtualnych AMX aktualnie załadowanych na serwerze. Jest to niezbędne dla funkcji, które muszą wchodzić w interakcje z "wszystkimi skryptami" lub znaleźć konkretny skrypt.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Opis:** Lista wskaźników do wszystkich instancji `AMX*`, które zostały zainicjalizowane (gamemode i filterscripts).
   - **Zarządzanie:** Wypełniana przez hooki `Amx_Init_Detour` i opróżniana przez `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Cel:** Chroni `loaded_amx_` przed równoczesnym dostępem w środowiskach wielowątkowych (chociaż SA-MP jest w większości jednowątkowe, jest to dobra praktyka bezpieczeństwa). `std::shared_mutex` pozwala na wielu równoczesnych czytelników, ale tylko jednego pisarza.
- **`std::atomic<uint32_t> generation_`**:
   - **Cel:** Licznik, który zwiększa się za każdym razem, gdy AMX jest dodawany lub usuwany.
   - **Użycie:** Jest używany przez `Caller_Cache` w `callbacks.hpp` do wykrywania, kiedy lista AMX uległa zmianie, unieważniając pamięć podręczną wyszukiwania `publics` i zapewniając, że wywołania `Pawn_Public` zawsze działają z aktualnymi informacjami. Optymalizuje to wydajność, unikając powtarzających się wyszukiwań w stanie, który się nie zmienił.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Opis:** Przegląda `loaded_amx_` (od najnowszego do najstarszego, co zazwyczaj umieszcza gamemode lub najbardziej istotny filterscript na początku) w celu znalezienia `public` o określonej nazwie.
   - **Mechanizm:** Używa `amx::Find_Public` dla każdej instancji `AMX*`.
   - **Wpływ:** Jest podstawą dla `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: Router Callbacks `Plugin_Public`

Ten `singleton` to komponent, który mapuje nazwy `publics` Pawna na twoje funkcje C++ `Plugin_Public`.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Klucz:** Hash FNV1a nazwy `public` (np. `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Wartość:** `std::vector` z `std::function<cell(AMX*)>`, gdzie każda `std::function` jest obsługą C++ zarejestrowaną dla tej `public`.
   - **Mechanizm:** `std::vector` pozwala na rejestrację wielu `Plugin_Public`s dla tego samego callbacka (np. wiele pluginów chce przechwycić `OnPlayerCommandText`). Obsługi są wykonywane w odwrotnej kolejności rejestracji.
- **`Public_Registrar`**:
   - **Mechanizm:** Jest to klasa szablonowa, której makro `PLUGIN_PUBLIC_REGISTRATION` tworzy statyczną globalną instancję. W konstruktorze statycznym (`static bool registered = [...]`) rejestruje ona swoją obsługę `Plugin_Public` w `Public_Dispatcher`. Jest to wzorzec "rejestracji statycznej w czasie kompilacji/inicjalizacji".
   - **Przykład (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Registrar<decltype(&name), &name, hash_##name> registrar_##name;
      ```

- **`Public_Traits` i `Wrapper()`**:
   - **Mechanizm:** `Public_Traits` to szablon trait, który za pomocą metaprogramowania generuje funkcję `static cell Wrapper(AMX* amx)`.
   - **Cel:** Ten `Wrapper` jest funkcją `Amx_Handler_Func`, którą `Public_Dispatcher` faktycznie przechowuje i wywołuje. Jest odpowiedzialny za:
      1. Wywołanie `Public_Param_Reader::Get_Public_Params(amx, args...)` w celu wyodrębnienia parametrów ze stosu AMX.
      2. Wywołanie twojej rzeczywistej funkcji C++ `Plugin_Public` (`func_ptr`) z parametrami już przekonwertowanymi na poprawne typy C++.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Opis:** Zestaw rekurencyjnych funkcji szablonowych, które odczytują wartości ze stosu AMX i konwertują je na typy C++ określone w deklaracji `Plugin_Public`.
   - **Mechanizm:** Używa `Get_Stack_Cell()` do dostępu do `cell`i na stosie. Wykorzystuje `if constexpr` (C++17+) lub `std::is_same<T>::value` (C++14) do zastosowania poprawnej konwersji (`amx::AMX_CTOF` dla float, `Samp_SDK::Get_String` dla stringa, bezpośrednie rzutowanie na int).

### 4.7. `native.hpp`: Zarządzanie i Wywoływanie Natywów Pluginu

Ten nagłówek jest poświęcony tworzeniu i zarządzaniu natywnymi funkcjami C++, które twój plugin udostępnia Pawn.

- **`Native_List_Holder`**:
   - **Opis:** Globalny `singleton`, który przechowuje wszystkie `Plugin_Native`s zadeklarowane w twoim pluginie (ze wszystkich plików `.cpp` używających `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Zawiera obiekty `Native` (które przechowują nazwę natywnej i wskaźnik do funkcji C++ `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Zoptymalizowana mapa po hashu do szybkiego wyszukiwania wewnętrznych `Plugin_Native`s (używana przez `Plugin_Call`).
- **`Native_Registrar`**:
   - **Mechanizm:** Podobnie jak `Public_Registrar`, jest to klasa szablonowa, której makro `Plugin_Native` tworzy statyczną globalną instancję. W swoim konstruktorze dodaje natywną do `Native_List_Holder`.
   - **Wpływ:** Pozwala na deklarowanie `Plugin_Native`s w wielu plikach `.cpp` bez martwienia się o ręczną rejestrację. Wszystkie zostaną automatycznie zebrane.
- **`Native_Registry`**:
   - **Opis:** Klasa pomocnicza, która w `OnAmxLoad` pobiera kompletną listę `Native`s z `Native_List_Holder` i formatuje je w tablicę `AMX_NATIVE_INFO`.
   - **Mechanizm:** Wywołuje `amx::Register(amx, amx_natives_info_.data(), -1)` w celu zarejestrowania wszystkich twoich natywów w instancji AMX, która właśnie została załadowana.
- **`Plugin_Call_Impl(...)`**:
   - **Opis:** Podstawowa implementacja makra `Plugin_Call`.
   - **Mechanizm:** Wykorzystuje `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` do bezpośredniego uzyskania wskaźnika do funkcji C++.
   - **Środowisko:** Wykonuje natywną w środowisku `Amx_Sandbox` (izolowanym) w celu zarządzania tymczasowym stosem i stertą, podobnie do tego, jak działa `Pawn_Native`.

### 4.8. `callbacks.hpp` & `amx_memory.hpp`: Wywołania C++ -> Pawn i RAII

Te nagłówki stanowią szkielet dla wywoływania funkcji Pawn z C++ (makra `Pawn_*`) i zapewniają bezpieczeństwo pamięci.

- **`Amx_Sandbox`**:
   - **Opis:** `thread_local` struktura, która symuluje minimalistyczne i izolowane środowisko `AMX` dla wywołań `Pawn_Native` i `Plugin_Call`.
   - **Mechanizm:** Posiada własną strukturę `AMX`, `AMX_HEADER` i `std::vector<unsigned char> heap` do symulowania pamięci skryptu. Pozwala to na wywoływanie `amx::Push`, `amx::Allot` itp. bez ingerowania w stan rzeczywistych skryptów Pawn w trakcie wykonywania.
   - **`thread_local`:** Gwarantuje, że każdy wątek ma swoją własną `Amx_Sandbox`, zapobiegając warunkom wyścigu, jeśli SDK jest używane w kontekście wielowątkowym (np. przyszła pula wątków dla operacji nie-Pawn).
   - **Przykład (`Amx_Sandbox`):**
      ```cpp
      // Uproszczony fragment callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Symulowana pamięć dla stosu/sterty

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Inicjalizuje AMX i nagłówek
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
   - **Opis:** Zestaw przeciążonych funkcji szablonowych, które zarządzają `marshallingiem` *każdego* parametru C++ do formatu `cell` oczekiwanego przez AMX i odwrotnie dla parametrów wyjściowych.
   - **Przetwarzanie Wejścia:**
       - Dla `int`, `float`, `bool`: Konwertuje bezpośrednio na `cell`.
       - Dla `const char*`, `std::string`: Alokuje pamięć na stosie `Amx_Sandbox` (lub rzeczywistym AMX dla `Pawn_Public`), kopiuje string i umieszcza adres AMX na stosie.
   - **Przetwarzanie Wyjścia (`is_output_arg`):**
       - **Mechanizm:** Gdy argument jest niemodyfikowalną referencją l-value (wykrywaną przez cechę `is_output_arg`), `Parameter_Processor` nie umieszcza wartości, ale *adres AMX* dla tymczasowo zaalokowanej `cell` na stosie.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Po wywołaniu natywnej funkcji Pawn, wykonywana jest lista lambd (`post_call_updaters`). Każda lambda jest odpowiedzialna za odczytanie końcowej wartości zaalokowanej `cell` w AMX i przypisanie jej z powrotem do oryginalnej zmiennej C++ (np. `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mechanizm:** `std::integral_constant` (cecha typu), która w czasie kompilacji ocenia, czy typ parametru C++ jest modyfikowalną referencją (np. `int&`, `float&`, `std::string&`). Pozwala to `Parameter_Processorowi` odróżniać parametry wejściowe od wyjściowych.
   - **Przykład (`is_output_arg`):**
      ```cpp
      // Uproszczony fragment callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Opis:** Klasa RAII (`Resource Acquisition Is Initialization`), która hermetyzuje alokację i dealokację pamięci w AMX.
   - **Mechanizm:** W konstruktorze wywołuje `amx::Allot` w celu uzyskania `amx_addr` i `phys_addr`. W destruktorze wywołuje `amx::Release` w celu zwolnienia tej pamięci.
   - **Wpływ:** **Kluczowe dla zapobiegania wyciekom pamięci w stosie AMX.** Gwarantuje, że pamięć tymczasowa używana dla stringów lub parametrów wyjściowych jest zawsze zwalniana, nawet jeśli wystąpią wyjątki lub wcześniejsze powroty.

### 4.9. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Abstrakcyjny Dostęp do AMX

Te nagłówki dostarczają fundamentalne definicje i wysokopoziomowe narzędzia do interakcji z Pawn.

- **`amx_defs.h`**:
   - **Zawartość:** Zawiera surowe definicje struktur AMX (`AMX`, `AMX_HEADER`), typów (`cell`, `ucell`) i enumów błędów (`AmxError`). Definiuje również `AMX_NATIVE` i `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Wykorzystuje atrybuty pakowania (`#pragma pack(push, 1)` / `__attribute__((packed))`), aby zapewnić, że struktury AMX mają prawidłowy układ pamięci, co jest kluczowe dla interoperacyjności.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Opis:** Główna funkcja szablonowa do wywoływania funkcji API AMX udostępnianych przez serwer.
   - **Mechanizm:** Pobiera wskaźnik funkcji poprzez `Core::Instance().Get_AMX_Export(Index)` i wywołuje go. Centralizuje obsługę błędów, jeśli wskaźnik funkcji nie jest dostępny.
   - **Wpływ:** Konwertuje niskopoziomowe wywołania (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) na idiomatyczne i bezpieczne typowo wywołania C++ (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Opis:** Podstawowe funkcje do konwersji wartości `cell` na `float` i odwrotnie, wykonujące bitową reinterpretację pamięci.
   - **`static_assert`:** Zawiera `static_assert`, aby zagwarantować, że `sizeof(cell) == sizeof(float)` w czasie kompilacji, zapobiegając błędom na platformach o różnych rozmiarach typów.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Opis:** Pomocnik do konwersji adresu stringa AMX na `std::string`.
   - **Mechanizm:** Najpierw pobiera fizyczny adres (`cell* phys_addr`) stringa w AMX za pomocą `amx::Get_Addr`. Następnie używa `amx::STR_Len` do określenia długości i `amx::Get_String` do skopiowania bajtów do `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Opis:** Podstawowa funkcja formatowania stringów (podobna do `printf`) dla SDK.
   - **Mechanizm:** Wykorzystuje `vsnprintf` w dwóch przejściach: najpierw do określenia wymaganego rozmiaru stringa, a następnie do sformatowania stringa w dynamicznie zaalokowanym `std::string`. Pozwala to uniknąć przepełnień bufora.

## 5. Kompilacja i Wdrożenie

### Wymagania Architektury i Platformy

- Twój plugin **MUSI** być skompilowany dla architektury **x86 (32-bitowej)**. Mechanizm hookingu SDK jest specyficzny dla tej architektury.
- Obsługiwane platformy: Windows (.dll) i Linux (.so).

### Przykłady Poleceń Kompilacji

#### **MSVC (Visual Studio)**

1. Utwórz nowy projekt "Dynamic-Link Library (DLL)".
2. W ustawieniach projektu, ustaw "Platformę Rozwiązania" na **x86**.
3. Upewnij się, że standard języka C++ to co najmniej C++14.

#### **GCC / Clang (Linux)**

```bash
# Dla pluginu o nazwie 'my_plugin.so' z 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Kompiluje dla 32-bitów.
- `-shared`: Tworzy bibliotekę współdzieloną (`.so`).
- `-std=c++17`: Ustawia standard C++ na C++17 (może być `c++14` lub `c++20`).
- `-O2`: Poziom optymalizacji 2.
- `-fPIC`: Generuje kod niezależny od pozycji, niezbędny dla bibliotek współdzielonych.
- `-Wall -Wextra`: Włącza dodatkowe ostrzeżenia, aby pomóc w wyłapywaniu błędów.
- `-Wl,--no-undefined`: Zapobiega tworzeniu biblioteki, jeśli istnieją niezdefiniowane symbole.

#### **GCC / Clang (MinGW na Windows)**

```bash
# Dla pluginu o nazwie 'my_plugin.dll' z 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Statycznie łączy standardową bibliotekę C++. Niezbędne, aby twój plugin nie był zależny od specyficznych dla kompilatora bibliotek wykonawczych DLL, które mogą nie być obecne w systemie użytkownika.
- `-static-libgcc`: Statycznie łączy bibliotekę GCC.

### Wskazówki Dotyczące Dystrybucji

- **Nazwa Pliku:** Twój plugin powinien mieć rozszerzenie `.dll` (Windows) lub `.so` (Linux). Np. `my_plugin.dll`.
- **Lokalizacja:** Umieść skompilowany plik w folderze `plugins/` swojego serwera SA-MP.
- **server.cfg:** Dodaj nazwę swojego pluginu (jeśli Windows, bez rozszerzenia) do linii `plugins` w `server.cfg`.
   ```
   plugins my_plugin (jeśli Linux, my_plugin.so)
   ```

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