# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Современный, header-only, высокоуровневый C++ SDK для разработки плагинов и модулей для SA-MP.**

</div>

## Языки

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Оглавление

- [SA-MP SDK](#sa-mp-sdk)
  - [Языки](#языки)
  - [Оглавление](#оглавление)
  - [1. Введение и философия дизайна](#1-введение-и-философия-дизайна)
    - [Проблема со стандартным C API SA-MP](#проблема-со-стандартным-c-api-sa-mp)
    - [Решение SA-MP SDK: абстракция с безопасностью и производительностью](#решение-sa-mp-sdk-абстракция-с-безопасностью-и-производительностью)
    - [Модель Header-Only: преимущества и последствия](#модель-header-only-преимущества-и-последствия)
  - [2. Настройка и окружение](#2-настройка-и-окружение)
    - [Требования к компиляции](#требования-к-компиляции)
    - [Рекомендуемая структура файлов](#рекомендуемая-структура-файлов)
    - [Основные макросы конфигурации](#основные-макросы-конфигурации)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Определения и константы SA-MP (`samp_defs.hpp`)](#определения-и-константы-sa-mp-samp_defshpp)
  - [3. Полное руководство по использованию API](#3-полное-руководство-по-использованию-api)
    - [3.1. Жизненный цикл плагина](#31-жизненный-цикл-плагина)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Перехват Pawn-событий](#32-plugin_public-перехват-pawn-событий)
      - [Синтаксис и объявление](#синтаксис-и-объявление)
      - [Автоматический маршалинг параметров](#автоматический-маршалинг-параметров)
      - [Управление потоком: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#управление-потоком-plugin_public_continue-vs-plugin_public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.3. `Plugin_Native`: Создание нативных функций на C++](#33-plugin_native-создание-нативных-функций-на-c)
      - [Синтаксис и фиксированная сигнатура](#синтаксис-и-фиксированная-сигнатура)
      - [Автоматическая регистрация Natives](#автоматическая-регистрация-natives)
      - [Извлечение параметров: `Register_Parameters` vs. `Native_Params`](#извлечение-параметров-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Полный API: `Get`, `Get_REF`, `Set_REF`)](#native_params-полный-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Возврат значений](#возврат-значений)
    - [3.4. `Plugin_Native_Hook`: Перехват существующих Natives SA-MP](#34-plugin_native_hook-перехват-существующих-natives-sa-mp)
      - [Синтаксис и фиксированная сигнатура](#синтаксис-и-фиксированная-сигнатура-1)
      - [Регистрация и активация Hook](#регистрация-и-активация-hook)
      - [Вызов оригинальной Native (цепь Hooks): `Call_Original_Native`](#вызов-оригинальной-native-цепь-hooks-call_original_native)
      - [Полный пример `Plugin_Native_Hook`](#полный-пример-plugin_native_hook)
    - [3.5. `Pawn_*` Макросы: Вызов Pawn-функций из C++](#35-pawn_-макросы-вызов-pawn-функций-из-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Синтаксис и соглашения](#синтаксис-и-соглашения)
      - [Маршалинг входных параметров](#маршалинг-входных-параметров)
      - [Маршалинг выходных параметров (Ссылки: `int&`, `float&`, `std::string&`)](#маршалинг-выходных-параметров-ссылки-int-float-stdstring)
      - [Объект `Callback_Result`: полный анализ](#объект-callback_result-полный-анализ)
    - [3.6. `Plugin_Module`: Управление динамическими модулями](#36-plugin_module-управление-динамическими-модулями)
      - [Синтаксис и назначение](#синтаксис-и-назначение)
      - [Жизненный цикл модуля](#жизненный-цикл-модуля)
      - [Преимущества модульности](#преимущества-модульности)
    - [3.7. `Plugin_Call`: Вызов внутренних Native-функций плагина](#37-plugin_call-вызов-внутренних-native-функций-плагина)
      - [Синтаксис и преимущества производительности](#синтаксис-и-преимущества-производительности)
    - [3.8. Утилитарные функции SDK](#38-утилитарные-функции-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Рекомендуется)](#stdstring-plugin_formatconst-char-format--рекомендуется)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Деталь реализации)](#stdstring-samp_sdkformatconst-char-format--деталь-реализации)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Внутреннее строение и архитектура SDK](#4-внутреннее-строение-и-архитектура-sdk)
    - [4.1. `core.hpp`: Минималистичный фундамент](#41-corehpp-минималистичный-фундамент)
    - [4.2. `platform.hpp` и `version.hpp`: Совместимость и метаданные](#42-platformhpp-и-versionhpp-совместимость-и-метаданные)
    - [4.3. `function_hook.hpp`: Движок перехвата x86](#43-function_hookhpp-движок-перехвата-x86)
    - [4.4. `interceptor_manager.hpp`: Контроллер хуков AMX](#44-interceptor_managerhpp-контроллер-хуков-amx)
    - [4.5. `amx_manager.hpp`: Управление экземплярами `AMX*`](#45-amx_managerhpp-управление-экземплярами-amx)
    - [4.6. `public_dispatcher.hpp`: Маршрутизатор коллбэков `Plugin_Public`](#46-public_dispatcherhpp-маршрутизатор-коллбэков-plugin_public)
    - [4.7. `native.hpp`: Управление и вызов нативных функций плагина](#47-nativehpp-управление-и-вызов-нативных-функций-плагина)
    - [4.8. `native_hook_manager.hpp`: Движок хуков нативных функций](#48-native_hook_managerhpp-движок-хуков-нативных-функций)
    - [4.9. `callbacks.hpp` \& `amx_memory.hpp`: Вызовы C++ -\> Pawn и RAII](#49-callbackshpp--amx_memoryhpp-вызовы-c---pawn-и-raii)
    - [4.10. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Абстрагированный доступ к AMX](#410-amx_apihpp--amx_helpershpp--amx_defsh-абстрагированный-доступ-к-amx)
  - [5. Компиляция и развертывание](#5-компиляция-и-развертывание)
    - [Требования к архитектуре и платформе](#требования-к-архитектуре-и-платформе)
    - [Примеры команд компиляции](#примеры-команд-компиляции)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW в Windows)**](#gcc--clang-mingw-в-windows)
    - [Соображения по распространению](#соображения-по-распространению)
  - [Лицензия](#лицензия)
    - [Условия использования](#условия-использования)
      - [1. Предоставленные разрешения](#1-предоставленные-разрешения)
      - [2. Обязательные условия](#2-обязательные-условия)
      - [3. Авторские права](#3-авторские-права)
      - [4. Отказ от гарантий и ограничение ответственности](#4-отказ-от-гарантий-и-ограничение-ответственности)

## 1. Введение и философия дизайна

### Проблема со стандартным C API SA-MP

API плагинов SA-MP — это программный интерфейс на C. Хотя он функционален и фундаментален, он представляет собой проблемы, присущие низкоуровневому программированию:
- **Ручное управление памятью:** Функции, такие как `amx_Allot` и `amx_Release`, требуют, чтобы разработчик явно выделял и освобождал память в куче AMX. Это распространенный источник утечек памяти и сбоев во время выполнения.
- **Слабая типизация и ручные преобразования:** Параметры передаются в виде массива `cell`s, что требует явных (и часто небезопасных) преобразований между `cell`, `int`, `float` и `char*`.
- **Многословность и boilerplate:** Извлечение нескольких параметров из массива `cell* params`, работа с размерами строк и управление стеком AMX для обратных вызовов C++ в Pawn требует повторяющегося кода.
- **Хрупкость интерфейса:** Отсутствие проверки типов во время компиляции (type safety) означает, что ошибки при передаче параметров или типов могут оставаться незамеченными до выполнения, вызывая сбои или неопределенное поведение.

### Решение SA-MP SDK: абстракция с безопасностью и производительностью

SA-MP SDK решает эти проблемы, предоставляя мощный уровень абстракции на C++:
- **RAII (Resource Acquisition Is Initialization):** Автоматическое управление памятью в AMX. `Amx_Scoped_Memory` гарантирует освобождение выделенной памяти.
- **Безопасность типов:** Автоматическое и безопасное преобразование параметров между C++ и Pawn. Вы работаете напрямую с `int`, `float`, `std::string`.
- **Краткий и идиоматический синтаксис:** Макросы и шаблоны предоставляют чистый API, который больше похож на современный C++, чем на традиционный C API.
- **Надежный перехват:** Расширенный механизм hooking позволяет прозрачно перехватывать коллбэки Pawn (`Plugin_Public`), создавать новые нативные функции (`Plugin_Native`) и **перехватывать и связывать существующие нативные функции SA-MP (`Plugin_Native_Hook`)**.
- **Высокая производительность:** Широкое использование хеширования во время компиляции (FNV1a), кеширование функций и оптимизации `thread_local` для минимизации накладных расходов абстракций.

### Модель Header-Only: преимущества и последствия

SDK состоит исключительно из заголовочных файлов (`.hpp`, `.h`).
- **Преимущества:**
   - **Упрощенная интеграция:** Нет библиотек для сборки, компоновки или распространения. Просто включите заголовки.
   - **Оптимизации компилятора:** Компилятор имеет полный доступ к коду SDK и вашему плагину, что позволяет агрессивное встраивание и оптимизации на этапе компоновки, что может привести к более быстрым бинарникам.
- **Последствия:**
   - **Время компиляции:** Для очень больших проектов компиляция может занимать больше времени из-за повторного включения кода SDK. Это смягчается guards включения и природой C++ "включать только то, что необходимо".
   - **Макросы реализации:** Необходимость макроса `SAMP_SDK_IMPLEMENTATION` является следствием модели header-only для предотвращения переопределения символов.

## 2. Настройка и окружение

### Требования к компиляции

- **C++ Компилятор:** Совместим с C++14 или новее (SDK использует функции C++14, C++17 и C++20 для специфических оптимизаций, но C++14 является минимумом).
   - GCC (версия 7+)
   - Clang (версия 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Архитектура:** **x86 (32-бит)**. SA-MP работает исключительно на этой архитектуре. SDK включает проверки в `platform.hpp`, которые выдадут ошибки компиляции, если обнаружена неверная архитектура.
- **Операционная система:** Windows или Linux.

### Рекомендуемая структура файлов

Для ясности и организации обычно SDK размещается в подпапке `samp-sdk`.

```
meu_plugin/
├── samp-sdk/
│   ├── // Other SDK files
│   └── samp_sdk.hpp             // The main header to include
│
├── src/
│   ├── main.cpp                  // Where SAMP_SDK_IMPLEMENTATION is defined
│   └── my_custom_logic.cpp       // Optional, to organize code
│
└── CMakeLists.txt (ou .vcxproj, Makefile)
```

### Основные макросы конфигурации

Всегда определяйте эти макросы *перед* включением `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Цель:** Сигнализирует компилятору, что этот файл `.cpp` должен генерировать реализации экспортных функций плагина (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **SDK автоматически берет на себя экспорт этих функций, устраняя необходимость в файлах `.def` (в Windows) или объявлениях `__attribute__((visibility("default")))` (в Linux) для этих функций.**
- **Техническое воздействие:** Без этого макроса компоновщик не найдет необходимые экспорты, и сервер SA-MP не сможет загрузить ваш плагин.
- **Фундаментальное правило:** **Определите этот макрос ТОЛЬКО в ОДНОМ файле `.cpp` во всем вашем проекте.** Определение его в более чем одном файле вызовет ошибку компоновки "дублирующийся символ".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // The macro makes the SDK export the necessary functions automatically.
#include "samp-sdk/samp_sdk.hpp"

// ... your plugin code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Цель:** Включает коллбэки жизненного цикла Pawn-скрипта (`OnAmxLoad`, `OnAmxUnload`) и функциональность создания новых нативных функций на C++ (`Plugin_Native`).
- **Включенные функции:**
   - Коллбэки `OnAmxLoad(AMX* amx)` и `OnAmxUnload(AMX* amx)`.
   - Объявление и регистрация новых нативных функций C++ с использованием `Plugin_Native`.
   - Макрос `Plugin_Call` для вызова нативных функций, созданных с помощью `Plugin_Native` внутри вашего собственного плагина.
- **Техническое воздействие:** Когда этот макрос определен, SDK автоматически собирает все ваши `Plugin_Native`s. В функции `Supports()` флаг `SUPPORTS_AMX_NATIVES` автоматически добавляется, если в вашем проекте есть какие-либо `Plugin_Native`.
- **Гибкость:** **Вы можете определить этот макрос в нескольких файлах `.cpp`**. Система статической регистрации SDK объединит все нативные функции из разных единиц компиляции в единый глобальный список.

```cpp
// my_natives.cpp (can be a separate file from main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Only to enable Plugin_Native and OnAmxLoad/OnAmxUnload callbacks
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Цель:** Включает коллбэк `OnProcessTick()`, который регулярно вызывается сервером.
- **Техническое воздействие:** Автоматически добавляет флаг `SUPPORTS_PROCESS_TICK` в функцию `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logic executed at each server "tick" (e.g., 20ms)
    // Be careful with heavy operations here!
}
```

### Определения и константы SA-MP (`samp_defs.hpp`)

Этот файл предоставляет все известные константы и лимиты SA-MP, такие как `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST` и т.д. Он автоматически включается `samp_sdk.hpp` и должен использоваться для обеспечения совместимости и читабельности кода.

## 3. Полное руководство по использованию API

### 3.1. Жизненный цикл плагина

Следующие функции являются точками входа и выхода вашего плагина, автоматически экспортируемыми SDK.

#### `bool OnLoad()`

- **Описание:** Первая функция, вызываемая SA-MP сервером после успешной загрузки вашего плагина в память.
- **Использование:** Идеально подходит для инициализации любой системы, загрузки конфигураций, открытия соединений с базой данных или загрузки модулей (`Plugin_Module`).
- **Возврат:**
   - `true`: Плагин успешно инициализирован, и загрузка продолжается.
   - `false`: Плагин не удалось инициализировать. Загрузка будет прервана, и плагин будет выгружен.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Example: Load a module (more details in section 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database Module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load the database module!");

        return false; // Aborts the main plugin loading
    }

    return true;
}
```

#### `void OnUnload()`

- **Описание:** Последняя функция, вызываемая SA-MP сервером перед выгрузкой вашего плагина из памяти.
- **Использование:** Идеально подходит для очистки ресурсов, закрытия соединений, сохранения состояний и обеспечения отсутствия утечек ресурсов. SDK автоматически управляет выгрузкой модулей (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // No manual action is needed for modules loaded via Plugin_Module;
    // the SDK handles it.
}
```

#### `unsigned int GetSupportFlags()`

- **Описание:** Информирует SA-MP сервер о том, какие функции ваш плагин поддерживает и хочет использовать.
- **Использование:** **Всегда возвращайте `SUPPORTS_VERSION` (или `SAMP_PLUGIN_VERSION`).** Флаги `SUPPORTS_AMX_NATIVES` и `SUPPORTS_PROCESS_TICK` автоматически добавляются SDK, если есть `Plugin_Native`s, и/или если определен макрос `SAMP_SDK_WANT_PROCESS_TICK` соответственно. Это упрощает обслуживание и предотвращает ошибки.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // The SDK automatically adds the necessary flags.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Требуется:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Описание:** Вызывается всякий раз, когда новый Pawn-скрипт (Gamemode или Filterscript) загружается и инициализируется на сервере.
- **Использование:** Если вам нужна специфическая логика для каждого AMX-скрипта или инициализация данных, специфичных для скрипта.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxLoad(AMX* amx) {
    // amx represents the new instance of the loaded script.
    Samp_SDK::Log("AMX script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Требуется:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Описание:** Вызывается, когда Pawn-скрипт выгружается с сервера.
- **Использование:** Для очистки любых специфических ресурсов, которые вы выделили или связали с этим конкретным `AMX*`.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Требуется:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Описание:** Вызывается повторно с каждым "тиком" сервера (обычно 20 раз в секунду или каждые 50 мс).
- **Использование:** Для непрерывной фоновой логики, таймеров, обновлений состояния, которые не зависят от событий игрока, или синхронизации данных.
- **Внимание:** Избегайте блокирующих или вычислительно тяжелых операций здесь, так как они могут вызвать задержку на сервере.

```cpp
// main.cpp (with SAMP_SDK_WANT_PROCESS_TICK defined)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Every 10 seconds (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Перехват Pawn-событий

Макрос `Plugin_Public` является основным мостом для получения Pawn-коллбэков в вашем коде C++.

#### Синтаксис и объявление

- `Plugin_Public(NameOfPublic, Type1 Param1, Type2 Param2, ...)`
- Имя функции C++, которую вы объявляете, **должно совпадать** с именем Pawn-коллбэка (например: `OnPlayerConnect`).
- Типы параметров C++ (`int`, `float`, `std::string`) автоматически преобразуются SDK.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Player %d said: %s", playerid, text.c_str());

    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Автоматический маршалинг параметров

SDK автоматически обрабатывает чтение `cell stack` AMX и преобразование в указанные типы C++:
- `int`: Преобразуется напрямую из `cell`.
- `float`: Преобразуется из `cell` с использованием `amx::AMX_CTOF`.
- `std::string`: SDK считывает адрес строки в AMX, выделяет `std::string` в C++ и копирует содержимое.

#### Управление потоком: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

Возвращаемое значение вашей функции `Plugin_Public` имеет решающее значение и определяет поток выполнения коллбэка:
- `return PLUGIN_PUBLIC_CONTINUE;` (значение `1`): Указывает, что выполнение коллбэка должно **продолжаться**. Если есть другие плагины, которые также перехватывают этот коллбэк, они будут вызваны (в обратном порядке загрузки). Затем будет вызвана оригинальная `public` в Pawn-скрипте.
- `return PLUGIN_PUBLIC_STOP;` (значение `0`): Указывает, что выполнение коллбэка должно быть **прервано**. Никакие другие плагины (с меньшим приоритетом) или оригинальная `public` в Pawn-скрипте не будут вызваны для этого события. Это идеально подходит для реализации системы, которая "переопределяет" или "блокирует" стандартное поведение SA-MP.

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

Расширенная функция `Plugin_Public` — это поддержка "Ghost Callbacks". Это означает, что вы можете перехватить Pawn-коллбэк, даже если он **отсутствует** в `.amx` скрипте gamemode или filterscript. SDK "обманывает" сервер, чтобы он все равно вызывал ваш C++ хук. Это полезно для внутренних коллбэков или для создания новой функциональности без зависимости от наличия `public` в Pawn-скрипте.

```cpp
// You can define a callback that the Pawn script doesn't have, but your plugin will listen to it.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Custom internal event received: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// To "fire" this event from another point in your C++ code:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// The call will go to your Plugin_Public above, even if there's no OnMyCustomInternalEvent in Pawn.
```

### 3.3. `Plugin_Native`: Создание нативных функций на C++

`Plugin_Native` позволяет расширять функциональность Pawn с помощью высокопроизводительного кода C++.

#### Синтаксис и фиксированная сигнатура

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- Функция C++ должна иметь точно такую сигнатуру: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` — это имя, которое будут использовать Pawn-скрипты.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementation ...
    return 0;
}
```

#### Автоматическая регистрация Natives

> [!NOTE]
> Вам **не нужно** вручную вызывать `amx_Register`. SDK обнаруживает все ваши `Plugin_Native`s (в любом файле `.cpp`, который включает `samp_sdk.hpp` и определяет `SAMP_SDK_WANT_AMX_EVENTS`) и автоматически регистрирует их в каждом загруженном AMX-скрипте (`OnAmxLoad`).

#### Извлечение параметров: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Описание:** Более простой вспомогательный инструмент для последовательного извлечения нескольких параметров.
- **Использование:** `Register_Parameters(variable1, variable2, ...)`
- **Ограничения:** Для входных параметров. Не работает с необязательными параметрами или доступом по индексу.
- **Поддерживаемые типы:** `int`, `float`, `std::string`.

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

##### `Native_Params` (Полный API: `Get`, `Get_REF`, `Set_REF`)

- **Описание:** Класс-обертка, предоставляющий объектно-ориентированный интерфейс для доступа к параметрам нативной функции. Более мощный для сложных сценариев.
- **Создание:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Описание:** Возвращает количество параметров, переданных нативной функции.
- **Использование:** Необходимо для работы с необязательными параметрами.

###### `p.Get<T>(size_t index)`

- **Описание:** Извлекает входной параметр по индексу и преобразует его в тип `T`.
- **Поддерживаемые типы:** `int`, `float`, `std::string`.

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

- **Описание:** Получает значение **ссылочного** параметра (Pawn-указателя) и сохраняет его в `out_value`.
- **Использование:** Для чтения значений, переданных по ссылке из Pawn.
- **Возврат:** `true`, если AMX-адрес действителен, `false` в противном случае.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Get the values from the references (Pawn passed addresses)
    p.Get_REF(1, health); // Reads the value of Float:health
    p.Get_REF(2, money);   // Reads the value of money
    
    Samp_SDK::Log("Player %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Now, modify them
    health = 50.0f;
    money += 100;
    
    // And write them back to Pawn memory
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Описание:** Возвращает `std::optional<T>` для чтения ссылочного параметра. Более безопасно для C++17 и выше.

###### `p.Set_REF<T>(size_t index, T value)`

- **Описание:** Записывает значение `T` в **ссылочный** параметр Pawn (адрес, переданный Pawn).
- **Использование:** Для изменения значений, переданных по ссылке, чтобы Pawn видел изменения.
- **Возврат:** `true`, если запись прошла успешно, `false` в противном случае.

#### Возврат значений

- Ваша функция `Plugin_Native` должна возвращать `cell`.
- Чтобы вернуть `int` или `bool`, используйте приведение к `cell`.
- Чтобы вернуть `float`, используйте `amx::AMX_FTOC(my_float)`.

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

### 3.4. `Plugin_Native_Hook`: Перехват существующих Natives SA-MP

Макрос `Plugin_Native_Hook` позволяет перехватывать и изменять поведение любой существующей нативной функции SA-MP или других плагинов. Это мощный механизм для расширения или изменения стандартной логики сервера.

#### Синтаксис и фиксированная сигнатура

- `Plugin_Native_Hook(NativeName, AMX* amx, cell* params)`
- Функция C++ должна иметь точно такую сигнатуру: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` должно быть точным именем нативной функции, которую вы хотите хукнуть (например, `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepts the SendClientMessage native
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Important to call the original
}
```

#### Регистрация и активация Hook

> [!NOTE]
> Вам **не нужно** вручную вызывать `amx_Register` или определять `SAMP_SDK_WANT_AMX_EVENTS` специально для `Plugin_Native_Hook`. SDK автоматически обнаруживает и регистрирует ваши хуки. При первом выполнении AMX-скрипта SDK заменяет указатель на native в таблице на "trampoline", который перенаправляет на вашу функцию `Plugin_Native_Hook`. Этот процесс обеспечивает безопасное связывание хуков из нескольких плагинов.

#### Вызов оригинальной Native (цепь Hooks): `Call_Original_Native`

Внутри вашей функции `Plugin_Native_Hook` вы **ДОЛЖНЫ** использовать макрос `Call_Original_Native(NativeName)` для вызова оригинальной функции (или следующего хука в цепочке). Это жизненно важно для:
- **Сохранения функциональности:** Если вы не вызовете оригинал, захуканная native просто перестанет работать для других плагинов или для сервера.
- **Цепочки хуков:** Позволяет нескольким плагинам хукать одну и ту же native и выполнять все хуки последовательно.
- **Обработки возврата:** Вы можете проверять и даже изменять возвращаемое значение `Call_Original_Native` перед возвратом его из вашей функции хука.

```cpp
// Example: Blocking SendClientMessage if it contains a specific word
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extract parameters for analysis
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // We don't need the color for this logic
    std::string message = p.Get_String(2); // Gets the message string

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGE BLOCKED for playerid %d: %s", playerid, message.c_str());

        return 0; // Returns 0 (false) to Pawn, indicating that the message was not sent.
                  // And more importantly, we DO NOT call Call_Original_Native, blocking the message.
    }

    // If the message does not contain the prohibited word, we call the original native
    // and return its value, ensuring that the message is sent normally
    // and that other hooks (if any) are executed.
    return Call_Original_Native(SendClientMessage);
}
```

#### Полный пример `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS is not strictly necessary for hooks, but it is common to have OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook for the CreateVehicle native
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extract CreateVehicle native parameters for inspection
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
        params[1] = static_cast<cell>(401); // The model is at position 0 of the parameters array (params[1])
        Samp_SDK::Log("  -> Model 400 changed to 401 before creation.");
    }
    
    // We call the original native (or the next hook in the chain) with the possibly modified parameters
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
> Прямая манипуляция массивом `cell* params` для изменения входных параметров требует осторожности. Убедитесь, что вы понимаете порядок и тип параметров. В большинстве случаев достаточно `p.Get(...)` для проверки и `Call_Original_Native(...)` для продолжения цепочки. Прямое изменение `params` следует выполнять только в том случае, если вы знаете, что параметр является значением и должен быть изменен для исходного вызова. Для строк и массивов изменение более сложно и обычно включает `amx::Set_String` для записи по существующему адресу или перераспределения, что может быть проще управлять, вызывая native через `Pawn_Native` с новыми значениями и возвращая `0` из вашего хука, чтобы отменить исходный вызов.

### 3.5. `Pawn_*` Макросы: Вызов Pawn-функций из C++

Эти макросы являются противоположностью `Plugin_Public` и `Plugin_Native`: они позволяют вашему коду C++ вызывать Pawn-функции.

#### `Pawn_Native(NativeName, ...)`

- **Цель:** Рекомендуемый способ вызова нативных функций SA-MP (или других плагинов) из C++.
- **Механизм:** Ищет указатель на нативную функцию во внутреннем кэше SDK (заполненном `Amx_Register_Detour`). Если найдено, выполняет нативную функцию в среде `Amx_Sandbox` (фальшивый и изолированный экземпляр AMX).
- **Производительность:** Наиболее эффективный, поскольку избегает дорогостоящего поиска `publics` и напрямую взаимодействует с указателем на нативную функцию.

#### `Pawn_Public(PublicName, ...)`

- **Цель:** Вызывает конкретную публичную функцию в Pawn-скрипте.
- **Механизм:** Проходит по экземплярам `AMX*`, управляемым `Amx_Manager`, ищет `public` по имени и выполняет ее.
- **Производительность:** Менее эффективен, чем `Pawn_Native` из-за поиска и реального `amx_Exec`. Обычно `publics` медленнее, чем `natives`.
- **Использование:** Идеально подходит для вызова пользовательских событий в вашем Gamemode/Filterscripts, которые не являются нативными функциями.

#### `Pawn(FunctionName, ...)`

- **Цель:** Вспомогательный макрос, который пытается определить, является ли функция нативной или публичной.
- **Механизм:** Сначала пытается вызвать как `Pawn_Native`. Если не удается (нативная функция не найдена), пытается вызвать как `Pawn_Public`.
- **Производительность:** Может быть немного медленнее, чем `Pawn_Native`, если функция является нативной, из-за двойной попытки поиска. Для `publics` производительность такая же, как у `Pawn_Public`.
- **Использование:** Для функций, в которых вы не уверены, являются ли они нативными или публичными, или чтобы избежать повторяющегося кода попыток одной, а затем другой.

#### Синтаксис и соглашения

- **Имя функции:** Всегда используйте имя Pawn-функции **напрямую, без кавычек**. SDK преобразует его в строку внутри.
- **Параметры:** Передавайте C++ параметры напрямую.

```cpp
// Correct:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Incorrect (but would technically work due to hashing, avoid):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Маршалинг входных параметров

SDK преобразует ваши типы C++ в формат `cell` AMX, управляя памятью по мере необходимости:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (с использованием `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (выделяет память в AMX, копирует строку и передает адрес `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Маршалинг выходных параметров (Ссылки: `int&`, `float&`, `std::string&`)

Это ключевая особенность для удобства и безопасности. Для функций Pawn, которые ожидают указатель (ссылку), SDK автоматизирует весь процесс выделения/освобождения памяти и копирования данных.

- **Как использовать:** Просто передайте вашу переменную по ссылке (`&`).
- **Механизм:** SDK выделяет память в куче AMX, передает AMX-адрес Pawn-функции, ждет, пока Pawn-функция заполнит этот адрес, считывает значение обратно и освобождает память AMX. Все это прозрачно.
- **С `std::string&`:** SDK выделяет стандартный буфер (256 ячеек) в AMX для строки.

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

#### Объект `Callback_Result`: полный анализ

Все вызовы `Pawn_*` возвращают объект `Callback_Result`. Этот объект является безопасной оберткой для результата вызова Pawn.

- `Callback_Result() noexcept`: Конструктор по умолчанию, указывает на сбой (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Конструктор для успеха или сбоя со значением.
- `explicit operator bool() const`: Позволяет использовать `if (result)` для проверки успешности вызова.
- `operator cell() const`: Позволяет преобразовать результат в `cell` для получения значения.
- `float As_Float() const`: Удобство для получения результата в виде `float`.
- `cell Value() const`: Возвращает сырое значение `cell`.
- `bool Success() const`: Возвращает `true`, если вызов Pawn был успешным.
- `int Get_Amx_Error() const`: Возвращает код ошибки AMX, если вызов не удался (0 для успеха).

```cpp
// Example: Getting a player's health.
// The native GetPlayerHealth(playerid, &Float:health) expects a playerid and a reference to health.
int playerid = 0; // Example player ID
float player_health = 0.0f;

// We call GetPlayerHealth, passing playerid and player_health by reference.
// The SDK will handle marshalling for the output parameter 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Checks if the call was successful (operator bool)
    // The value returned by result.As_Float() or result (operator cell)
    // would be the return value of the *native*, not the output parameter.
    // The health value has already been updated in 'player_health' due to output parameter marshalling.
    Samp_SDK::Log("Player %d has %.1f health.", playerid, player_health);
}
else {
    // The call failed, perhaps the player doesn't exist or the native was not found.
    Samp_SDK::Log("Error getting player %d health. AMX Code: %d", playerid, result.Get_Amx_Error());
}

// For natives that return a value and use output parameters (less common, but possible),
// you would use both:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param is already updated
// }
```

### 3.6. `Plugin_Module`: Управление динамическими модулями

Макрос `Plugin_Module` позволяет вашему плагину выступать в качестве "загрузчика" для других плагинов, создавая модульную и расширяемую архитектуру. Модуль, загруженный таким образом, рассматривается как плагин первого класса, со своим собственным жизненным циклом событий, управляемым хост-плагином.

#### Синтаксис и назначение

- `Plugin_Module(const char* base_filename, const char* module_directory, const char* optional_success_message)`
- `base_filename`: **Базовое** имя файла модуля, **без расширения** (например, для `my_module.dll` или `my_module.so` используйте `"my_module"`). SDK автоматически добавит соответствующее расширение `.dll` или `.so`.
- `module_directory`: Путь к каталогу, где находится файл модуля (например, `"plugins/my_custom_modules"`). **Не включайте имя файла сюда.** SDK выполнит конкатенацию полного пути (`module_directory/base_filename.ext`).
- `optional_success_message`: Необязательное сообщение, которое будет записано в консоль сервера, если модуль успешно загрузится.

```cpp
// main.cpp, inside OnLoad()

// Loads the module 'core_logic.dll' (or 'core_logic.so')
// which is located in the server's 'modules/custom/' folder.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic Module loaded successfully!"))
    return (Samp_SDK::Log("FATAL ERROR: Failed to load module 'core_logic'!"), false);

// Loads the module 'admin_system.dll' (or 'admin_system.so')
// which is located directly in the server's 'plugins/' folder.
if (!Plugin_Module("admin_system", "plugins", "Administration Module activated."))
    Samp_SDK::Log("WARNING: Administration Module could not be loaded.");
```

#### Жизненный цикл модуля

Модуль должен экспортировать функции `Load`, `Unload` и `Supports`, как обычный плагин. SDK управляет жизненным циклом модуля следующим образом:

- **Загрузка:** При вызове `Plugin_Module` SDK:
   1. Создает полный путь к файлу (например, `modules/custom/core_logic.dll`).
   2. Использует `Dynamic_Library` (`LoadLibrary`/`dlopen`) для загрузки бинарного файла.
   3. **Получает указатели на ВСЕ функции жизненного цикла модуля:**
      - **Обязательные:** `Load`, `Unload`, `Supports`. Если какая-либо отсутствует, загрузка модуля завершается неудачей.
      - **Необязательные:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Вызывает функцию `Load` модуля, передавая `ppData` основного плагина.
   5. Если `Load` возвращает `true`, модуль добавляется во внутренний список загруженных модулей.

- **Перенаправление событий:** Хост-плагин **автоматически перенаправляет** события всем загруженным модулям.
 > [!IMPORTANT]
 > Чтобы события перенаправлялись правильно, **хост-плагин** (который вызывает `Plugin_Module`) должен быть настроен на получение этих событий.
 > - Для работы `AmxLoad` и `AmxUnload` в модулях хост-плагин должен определить макрос `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Для работы `ProcessTick` в модулях хост-плагин должен определить макрос `SAMP_SDK_WANT_PROCESS_TICK`.

- **Выгрузка:** Во время `OnUnload` вашего основного плагина SDK выгружает все модули, которые были загружены через `Plugin_Module`. Это делается в **обратном порядке** к загрузке (последний загруженный выгружается первым), что критически важно для управления зависимостями и обеспечения правильного освобождения ресурсов.

#### Преимущества модульности

- **Организация кода:** Разделите большие плагины на более мелкие, управляемые компоненты, каждый в своем файле модуля.
- **Повторное использование:** Создавайте общие модули (например, модуль базы данных, модуль расширенной системы логирования), которые могут использоваться различными плагинами, способствуя повторному использованию кода.
- **Независимые компоненты:** Создавайте модули, которые **полностью ориентированы на события и независимы**. Модуль может иметь свои собственные `Plugin_Native`s, перехватывать `Plugin_Public`s и иметь свою собственную логику `OnProcessTick`, работая как автономный плагин, но загружаемый хостом.
- **Динамические обновления:** В контролируемых сценариях позволяет обновлять части вашей системы (заменяя `.dll` или `.so` модуля) без необходимости перекомпилировать и перезапускать основной плагин или весь сервер (хотя это требует строгого управления версиями и совместимостью).

### 3.7. `Plugin_Call`: Вызов внутренних Native-функций плагина

Используйте `Plugin_Call` для вызова `Plugin_Native`, определенной **внутри вашего собственного плагина**.

#### Синтаксис и преимущества производительности

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Преимущество:** Избегает накладных расходов на поиск native в массиве native AMX. SDK поддерживает прямую карту хэшей имен на указатели функций для ваших собственных native, что делает этот способ самым быстрым для их вызова внутри.
- **Требуется:** `SAMP_SDK_WANT_AMX_EVENTS`.

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
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Calls your own native
                Samp_SDK::Log("Player %d is at a high level!", i);
        }
    }
}
```

### 3.8. Утилитарные функции SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Описание:** Печатает сообщения в консоль сервера и в файл `server_log.txt`. Безопасная обертка для `logprintf`.
- **Использование:** Для отладки, сообщений о статусе и ошибках.
- **Механизм:** Внутри SDK получает указатель на `logprintf` через `ppData[PLUGIN_DATA_LOGPRINTF]`. Функция безопасно обрабатывает форматирование строки.

```cpp
// Anywhere in your plugin
Samp_SDK::Log("The plugin was initialized with a value %d and a string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Рекомендуется)

- **Описание:** Безопасно форматирует строку (подобно `sprintf`) и возвращает `std::string`. Это **рекомендуемый и наиболее идиоматичный** способ форматирования строк для использования внутри вашего плагина.
- **Использование:** Идеально подходит для создания отформатированных сообщений перед их передачей в `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, или для любых других потребностей в строках внутри вашего кода C++.
- **Механизм:** Внутри `Plugin_Format` является макросом, который вызывает `Samp_SDK::Format`. Он использует `vsnprintf` для определения точного размера форматированной строки и выделяет `std::string` достаточной емкости, предотвращая переполнение буфера.

```cpp
int playerid = 0; // Example ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Player %d, your current health is %d.", playerid, health));

// Can also be used for internal logs
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Деталь реализации)

- **Описание:** Базовая функция реализации для форматирования строк, расположенная в пространстве имен `Samp_SDK`.
- **Использование:** Обычно не вызывается пользователем напрямую. Макрос `Plugin_Format` предоставляется как удобство для этой функции, соответствуя соглашению об именовании других макросов SDK (`Plugin_Public`, `Plugin_Native`). Вы бы вызывали его напрямую только в том случае, если бы хотели избежать макроса `Plugin_Format` по какой-либо конкретной причине.

```cpp
// Example of how Samp_SDK::Format works, but prefer Plugin_Format
std::string raw_status = Samp_SDK::Format("For internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Описание:** Преобразует AMX-адрес строки (`cell amx_addr`) в `std::string` C++.
- **Использование:** В основном внутри `Plugin_Native` и `Plugin_Native_Hook`, когда вам нужно получить доступ к строкам, которые не преобразуются автоматически `Register_Parameters` или `Native_Params` (например, если Pawn-параметр является `const` `string` и не был объявлен как `std::string` в вашем `Plugin_Native` или `Plugin_Public` для автоматического маршалинга).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Gets the string address in AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String from AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Внутреннее строение и архитектура SDK

Этот раздел раскрывает базовые механизмы SA-MP SDK, исследуя его архитектуру, ключевые компоненты и то, как они взаимодействуют для обеспечения высокоуровневой абстракции. Глубокое понимание этих внутренних механизмов позволяет разработчику оптимизировать использование SDK, отлаживать сложные проблемы и даже расширять его функциональность.

### 4.1. `core.hpp`: Минималистичный фундамент

`Samp_SDK::Core` — это `singleton`, который служит начальной и централизованной точкой доступа к низкоуровневым данным, предоставляемым средой плагина SA-MP. Его основная ответственность — инкапсулировать и предоставлять основные функции.

- **`Samp_SDK::Core::Instance()`**:
   - **Описание:** Возвращает единственный глобальный экземпляр класса `Core`. Это шаблон проектирования `singleton`, гарантирующий, что доступ к данным плагина (`ppData`) будет последовательным и централизованным.
   - **Механизм:** Экземпляр инициализируется один раз, когда `Core::Instance().Load(ppData)` вызывается в функции `Load()` вашего плагина.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Описание:** Обеспечивает безопасный индексированный доступ к указателям функций AMX API. Массив `pAMXFunctions` (полученный через `ppData[PLUGIN_DATA_AMX_EXPORTS]`) содержит адреса критически важных функций, таких как `amx_Exec`, `amx_Register` и т.д.
   - **Воздействие:** Вместо использования `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, SDK предлагает type-safe обертки в пространстве имен `amx::` (например, `amx::Exec(...)`), что делает код более читаемым и менее подверженным ошибкам приведения типов.
   - **Внутренний пример (`amx_api.hpp`):**
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

- **`logprintf_ptr`**:
   - **Описание:** Указатель на функцию `logprintf` SA-MP, которая является стандартным интерфейсом для вывода сообщений в консоль сервера и в `server_log.txt`.
   - **Механизм:** `Samp_SDK::Log` — это безопасная обертка, использующая этот указатель, гарантирующая, что ваши сообщения будут корректно отображаться в среде SA-MP.

### 4.2. `platform.hpp` и `version.hpp`: Совместимость и метаданные

Эти заголовки являются основой для переносимости и оптимизации SDK, адаптируя его к различным средам компиляции и используя преимущества конкретных функций современного C++.

- **Обнаружение платформы и архитектуры:**
   - **Механизм:** Использует макросы препроцессора (`#if defined(WIN32)`, `#if defined(__linux__)` и т. д.) для идентификации операционной системы.
   - **Проверка архитектуры:** Содержит `static_assert` или `#error` для обеспечения компиляции плагина для x86 (32-бит), что является критическим требованием для совместимости с SA-MP и механизмом хукинга.
   - **Управление экспортом символов:**
      - `SAMP_SDK_EXPORT`: Макрос, определенный в `platform.hpp`, который раскрывается в `extern "C"`, а в Linux добавляет `__attribute__((visibility("default")))`. В Windows он просто гарантирует `extern "C"`, потому что SDK использует `pragma comment(linker, "/EXPORT:...")` (для MSVC) или стандарт MinGW для экспорта основных функций.
      - Это гарантирует, что функции жизненного цикла плагина (`Supports`, `Load`, `Unload` и т. д.) правильно экспортируются из вашей DLL/SO, независимо от среды компиляции, **без необходимости в файлах `.def` или ручного добавления `__attribute__((visibility("default")))`** в вашей реализации.
   - **Пример (`platform.hpp` - соответствующий фрагмент):**
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
   - **Пример (`samp_sdk.hpp` - соответствующий фрагмент реализации):**
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

- **Макросы оптимизации и предсказания ветвлений:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Механизм:** `__forceinline` (MSVC) или `__attribute__((always_inline)) inline` (GCC/Clang). Настоятельно предлагает компилятору вставить тело функции непосредственно в место вызова, устраняя накладные расходы на фактический вызов функции.
      - **Использование:** Применяется к небольшим, критически важным для производительности функциям в SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Механизм:** `[[likely]]` / `[[unlikely]]` (C++20) или `__builtin_expect` (GCC/Clang). Подсказки компилятору о том, какой путь `if/else` наиболее вероятен.
      - **Влияние:** Помогает компилятору генерировать более эффективный код для предсказания ветвлений (branch prediction), уменьшая задержку ЦП.
      - **Пример (`platform.hpp`):**
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
      - **Механизм:** `__attribute__((used))` (GCC/Clang). Информирует компилятор о том, что символ (в данном случае функция) используется, даже если на него нет ссылок в коде C++.
      - **Влияние:** Крайне важно для функций C++, которые вызываются из встроенных ассемблерных блоков (`asm volatile`). Без этого атрибута оптимизатор компилятора может по ошибке удалить функцию, что приведет к ошибке "неопределенный символ" в компоновщике.
      - **Пример (`platform.hpp`):**
         ```cpp
         #if defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
             #define SAMP_SDK_USED_BY_ASM __attribute__((used))
         #else
             #define SAMP_SDK_USED_BY_ASM
         #endif
         ```

- **Стандартные определения C++ (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Механизм:** Макросы, определенные на основе значения `__cplusplus` и `_MSVC_LANG`.
   - **Использование:** Позволяют SDK использовать более новые функции C++ (такие как `std::apply` и `if constexpr` из C++17 или `std::is_same_v` из C++17) при их наличии, сохраняя совместимость со старыми стандартами.
   - **Пример (`version.hpp` - использование `if constexpr`):**
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

### 4.3. `function_hook.hpp`: Движок перехвата x86

Этот заголовок определяет низкоуровневый механизм для выполнения хуков (перехватов) функций, который является фундаментальным для работы SDK. Он строго зависит от архитектуры x86 (32-бит).

- **`X86_Detour`**:
   - **Описание:** Класс, инкапсулирующий логику перезаписи начала функции в памяти инструкцией перехода к функции-девиации.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Механизм:** В x86 инструкция перехода (`JMP`) относительного типа обычно имеет 5 байт: `0xE9` (код операции для JMP near, relative), за которым следуют 4 байта, представляющие смещение (offset) адреса цели относительно следующей инструкции.
      - **Пример инструкции:** `E9 XX XX XX XX` (где `XX` — байты смещения).
   - **`Apply(void* target, void* detour)`**:
      - **Действие:** Устанавливает хук. Сначала сохраняет `JUMP_INSTRUCTION_SIZE` исходных байтов функции `target` (`original_bytes_`). Затем вычисляет относительный адрес `detour` относительно `target` и перезаписывает начало `target` инструкцией `JMP`.
      - **Пример расчета относительного адреса:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Адрес девиации - (Адрес цели + Размер инструкции JMP)
         ```
   - **`Revert()`**:
      - **Действие:** Удаляет хук, восстанавливая `original_bytes_` в функции `target`.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Механизм:** В Windows используется `VirtualProtect`; в Linux — `mprotect`. Эти системные вызовы изменяют разрешения страницы памяти, где находится функция, на `EXECUTE_READWRITE` (Windows) или `PROT_WRITE | PROT_EXEC` (Linux), что позволяет изменять код во время выполнения.
      - **Пример (`Unprotect_Memory`):**
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

- **`Function_Hook<FuncPtr>`**:
   - **Описание:** `type-safe` обертка C++ для `X86_Detour`, гарантирующая правильность типов указателей функций.
   - `Install(void* target, void* detour)`: Инкапсулирует вызов `X86_Detour::Apply`.
   - `Uninstall()`: Инкапсулирует вызов `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Механизм безопасности (Guard от рекурсии):** Эта функция критически важна для предотвращения бесконечных циклов, когда девиация должна вызывать исходную функцию. Она **временно удаляет хук (`detour_.Revert()`)**, вызывает исходную функцию (`Get_Original()(args...)`), а затем **переустанавливает хук (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Счетчик, который гарантирует, что хук будет переустановлен только после завершения вызова исходной функции самого верхнего уровня, что позволяет безопасные рекурсивные вызовы исходной функции (например, если исходная функция рекурсивна). `thread_local` гарантирует, что `recursion_guard` изолирован для каждого потока, что важно в многопоточной среде.
      - **Пример (`Call_Original` с Scope_Guard):**
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

### 4.4. `interceptor_manager.hpp`: Контроллер хуков AMX

Этот `singleton` является нервным центром взаимодействия SDK с виртуальной машиной AMX SA-MP. Он координирует установку хуков, предоставляемых `function_hook.hpp`, в функции AMX API, экспортируемые сервером, перенаправляя поток выполнения на логику SDK.

- **`Activate()` / `Deactivate()`**:
   - **Описание:** Публичные методы для установки и удаления всех необходимых хуков. Вызываются в `OnLoad()` и `OnUnload()` вашего плагина соответственно.
   - **Механизм:** Получает указатели на функции AMX (такие как `amx_Register`, `amx_Exec` и т. д.) с помощью `Core::Instance().Get_AMX_Export(...)` и устанавливает девиации.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Захуканная функция:** `amx_Register`
   - **Назначение:** Перехватывает регистрацию *всех* нативных функций (SA-MP, других плагинов или gamemode).
   - **Действие:** Для каждой зарегистрированной нативной функции `Interceptor_Manager` добавляет ее во внутренний кеш (`Cache_Data::native_cache`).
   - **Воздействие:** Этот кеш является фундаментальным для производительности `Pawn_Native`, обеспечивая чрезвычайно быстрый поиск указателя на нативную функцию вместо дорогостоящего поиска в AMX.
   - **Дополнительная функция для `Plugin_Native_Hook`:** Этот детур *также* отвечает за изменение списка нативных функций перед их регистрацией. Если нативная функция имеет связанный `Plugin_Native_Hook`, указатель функции в списке регистрации заменяется трамплином, сгенерированным `Native_Hook_Manager`. Это позволяет вашему хуку быть вызванным первым.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Захуканная функция:** `amx_Exec`
   - **Назначение:** **Это самый критический хук.** Он перехватывает *любое* выполнение кода в AMX, включая вызов `publics` Pawn.
   - **Механизм перехвата `Plugin_Public`:**
      1. Когда `amx_Exec` вызывается для `public` (или `AMX_EXEC_MAIN`), выполняется `Amx_Exec_Detour`.
      2. Он получает имя `public` (используя `tl_public_name`, которое было заполнено `Amx_Find_Public_Detour`).
      3. Запрашивает `Public_Dispatcher::Instance().Dispatch()`, чтобы проверить, есть ли зарегистрированные обработчики C++ для этого имени.
      4. Если есть обработчики, он их выполняет. `Public_Dispatcher` обрабатывает `marshalling` параметров из AMX в правильные типы C++.
      5. Основываясь на возвращаемом значении `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), он решает, вызывать ли оригинальную `amx_Exec` (`Get_Amx_Exec_Hook().Call_Original(...)`) или завершить выполнение `public` Pawn.
      6. **Манипуляция стеком:** Если выполнение `public` Pawn прерывается (`PLUGIN_PUBLIC_STOP`), `Amx_Exec_Detour` корректирует стек AMX (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`), чтобы избежать несоответствий.
   - **Активация `Plugin_Native_Hook` (Патчинг AMX):**
      - При первом выполнении `AMX*` этот детур проверяет, была ли AMX уже "патчена" (`!manager.Is_Amx_Patched(amx)`).
      - Если нет, он проходит по таблице нативных функций **этого конкретного экземпляра AMX в памяти**.
      - Для каждой нативной функции, которая имеет зарегистрированный `Plugin_Native_Hook` в `Native_Hook_Manager`, он заменяет адрес нативной функции в таблице на трамплин, сгенерированный `Native_Hook_Manager`. Оригинальный адрес (или адрес предыдущего хука) сохраняется в объекте `Native_Hook`.
      - Затем AMX помечается как "патченая", чтобы избежать ненужной повторной обработки.
   - **Пример (`Amx_Exec_Detour` - с подробностями `Plugin_Native_Hook`):**
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

                  for (auto& hook_to_apply : hooks_to_apply) { // Iterates through all registered Plugin_Native_Hooks
                      uint32_t hook_hash = hook_to_apply.Get_Hash();

                      for (int i = 0; i < num_natives; ++i) { // Iterates through AMX natives
                          const char* native_name = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(hdr) + natives[i].nameofs);

                          if (FNV1a_Hash(native_name) == hook_hash) { // If the AMX native name matches a hook
                              AMX_NATIVE current_func = reinterpret_cast<AMX_NATIVE>(natives[i].address);

                              hook_to_apply.Set_Next_In_Chain(current_func); // Saves the pointer to the original/previous function

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
- **`int SAMP_SDK_AMX_API Amx_Find_Public_Detour(...)`**:
   - **Захуканная функция:** `amx_FindPublic`
   - **Назначение:** Перехватывает поиск `publics` по имени.
   - **Механизм "Ghost Publics":** Если оригинальная `amx_FindPublic` не находит `public` в Pawn, но `Public_Dispatcher` имеет зарегистрированный C++ обработчик для этого имени, этот хук возвращает `AMX_ERR_NONE` и специальный `index` (`PLUGIN_EXEC_GHOST_PUBLIC`). Это заставляет SA-MP API "думать", что `public` существует, позволяя последующему вызову `amx_Exec` (для этого специального индекса) быть перехваченным `Amx_Exec_Detour`, который затем перенаправляет его на C++ обработчик.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Используется для передачи имени `public` в `Amx_Exec_Detour`, когда обнаружен "ghost public", так как `amx_Exec` получает только индекс, а не имя.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Захуканные функции:** `amx_Init` / `amx_Cleanup`
   - **Назначение:** Управление списком активных экземпляров `AMX*`.
   - **Действие:** `Amx_Init_Detour` вызывает `Amx_Manager::Instance().Add_Amx()`, а `Amx_Cleanup_Detour` вызывает `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Управление экземплярами `AMX*`

Этот `singleton` ведет динамический учет всех загруженных в настоящее время AMX-виртуальных машин на сервере. Он необходим для функций, которым нужно взаимодействовать со "всеми скриптами" или найти конкретный скрипт.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Описание:** Список указателей на все экземпляры `AMX*`, которые были инициализированы (gamemode и filterscripts).
   - **Управление:** Заполняется хуками `Amx_Init_Detour` и очищается `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Назначение:** Защищает `loaded_amx_` от одновременного доступа в многопоточных средах (хотя SA-MP в основном однопоточный, это хорошая практика безопасности). `std::shared_mutex` позволяет множеству читателей одновременно, но только одному писателю.
- **`std::atomic<uint32_t> generation_`**:
   - **Назначение:** Счетчик, который увеличивается каждый раз, когда AMX добавляется или удаляется.
   - **Использование:** Используется `Caller_Cache` в `callbacks.hpp` для обнаружения изменений в списке AMX, инвалидации кэшей поиска `publics` и обеспечения того, чтобы вызовы `Pawn_Public` всегда работали с актуальной информацией. Это оптимизирует производительность, избегая повторяющихся поисков в неизмененном состоянии.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Описание:** Проходит по `loaded_amx_` (от самого нового к самому старому, что обычно помещает gamemode или наиболее релевантный filterscript первым) для поиска `public` с указанным именем.
   - **Механизм:** Использует `amx::Find_Public` для каждого экземпляра `AMX*`.
   - **Воздействие:** Является основой для `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: Маршрутизатор коллбэков `Plugin_Public`

Этот `singleton` является компонентом, который сопоставляет имена `publics` Pawn с вашими функциями C++ `Plugin_Public`.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Ключ:** FNV1a-хеш имени `public` (например, `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Значение:** `std::vector` из `std::function<cell(AMX*)>`, где каждая `std::function` — это обработчик C++, зарегистрированный для этой `public`.
   - **Механизм:** `std::vector` позволяет регистрировать несколько `Plugin_Public` для одного и того же коллбэка (например, несколько плагинов, желающих перехватить `OnPlayerCommandText`). Обработчики выполняются в обратном порядке регистрации.
- **`Public_Register`**:
   - **Механизм:** Это шаблонный класс, макрос `PLUGIN_PUBLIC_REGISTRATION` которого создает статическую глобальную переменную. В статическом конструкторе (`static bool registered = [...]`) он регистрирует свой обработчик `Plugin_Public` в `Public_Dispatcher`. Это шаблон "статической регистрации во время компиляции/инициализации".
   - **Пример (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Register<decltype(&name), &name, hash_##name> register_##name;
      ```

- **`Public_Traits` и `Wrapper()`**:
   - **Механизм:** `Public_Traits` — это шаблон трейта, который с помощью метапрограммирования генерирует функцию `static cell Wrapper(AMX* amx)`.
   - **Назначение:** Этот `Wrapper` является `Amx_Handler_Func`, который `Public_Dispatcher` фактически хранит и вызывает. Он отвечает за:
      1. Вызов `Public_Param_Reader::Get_Public_Params(amx, args...)` для извлечения параметров из стека AMX.
      2. Вызов вашей реальной функции `Plugin_Public` C++ (`func_ptr`) с параметрами, уже преобразованными в правильные типы C++.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Описание:** Набор рекурсивных шаблонных функций, которые считывают значения из стека AMX и преобразуют их в типы C++, указанные в объявлении `Plugin_Public`.
   - **Механизм:** Использует `Get_Stack_Cell()` для доступа к `cell`s в стеке. Использует `if constexpr` (C++17+) или `std::is_same<T>::value` (C++14) для применения правильного преобразования (`amx::AMX_CTOF` для float, `Samp_SDK::Get_String` для string, прямое приведение для int).

### 4.7. `native.hpp`: Управление и вызов нативных функций плагина

Этот заголовок посвящен созданию и управлению нативными функциями C++, которые ваш плагин предоставляет Pawn.

- **`Native_List_Holder`**:
   - **Описание:** Глобальный `singleton`, который хранит все `Plugin_Native`s, объявленные в вашем плагине (из всех файлов `.cpp`, использующих `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Содержит объекты `Native` (которые хранят имя нативной функции и указатель на функцию C++ `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Оптимизированная по хешу карта для быстрого поиска внутренних `Plugin_Native`s (используется `Plugin_Call`).
- **`Native_Register`**:
   - **Механизм:** Подобно `Public_Register`, это шаблонный класс, макрос `Plugin_Native` которого создает статический глобальный экземпляр. В его конструкторе он добавляет нативную функцию в `Native_List_Holder`.
   - **Воздействие:** Позволяет объявлять `Plugin_Native`s в нескольких файлах `.cpp` без беспокойства о ручной регистрации. Все они будут собраны автоматически.
- **`Native_Registry`**:
   - **Описание:** Вспомогательный класс, который в `OnAmxLoad` берет полный список `Native`s из `Native_List_Holder` и форматирует их в массив `AMX_NATIVE_INFO`.
   - **Механизм:** Вызывает `amx::Register(amx, amx_natives_info_.data(), -1)` для регистрации всех ваших нативных функций в только что загруженном экземпляре AMX.
- **`Plugin_Call_Impl(...)`**:
   - **Описание:** Базовая реализация макроса `Plugin_Call`.
   - **Механизм:** Использует `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` для прямого получения указателя на функцию C++.
   - **Среда:** Выполняет нативную функцию в среде `Amx_Sandbox` (изолированной) для управления временным стеком и кучей, аналогично тому, как работает `Pawn_Native`.

### 4.8. `native_hook_manager.hpp`: Движок хуков нативных функций

Это надежная система хуков нативных функций, предназначенная для управления цепочкой хуков нескольких плагинов для одной и той же нативной функции.

- **`Native_Hook`**:
   - **Описание:** Класс, представляющий один хук нативной функции. Хранит хеш имени нативной функции, предоставленную пользователем функцию-обработчик C++ (`user_handler_`) и `std::atomic<AMX_NATIVE> next_in_chain_`.
   - **`user_handler_`**: Ваша функция C++ `Plugin_Native_Hook`.
   - **`next_in_chain_`**: Указатель на оригинальную нативную функцию или на хук плагина с более низким приоритетом. Является `std::atomic` для обеспечения потокобезопасности при чтении/записи.
   - **`Dispatch(AMX* amx, cell* params)`**: Вызывается трамплином для выполнения вашего `user_handler_`.
   - **`Call_Original(AMX* amx, cell* params)`**: Ключевой метод, который вызывает `next_in_chain_`, позволяя вашему хуку вызывать оригинальную функциональность или следующий хук в цепочке.
- **`Trampoline_Allocator`**:
   - **Описание:** Класс, отвечающий за выделение исполняемых блоков памяти и генерацию ассемблерного кода "трамплина" в этих блоках.
   - **`Generate_Trampoline_Code(unsigned char* memory, int hook_id)`**: Записывает 10 байт ассемблерного кода:
      1. `B8 XX XX XX XX`: `MOV EAX, hook_id` (помещает уникальный ID хука в регистр EAX).
      2. `E9 XX XX XX XX`: `JMP relative_address_to_Dispatch_Wrapper_Asm` (переход к общей функции диспетчеризации SDK).
   - **`Allocation_Size = 4096`**: Выделяет память постранично для эффективности и выравнивания кэша.
   - **Разрешения памяти:** Использует `VirtualAlloc` (Windows) или `mmap` (Linux) с разрешениями `EXECUTE_READWRITE` для обеспечения возможности выполнения сгенерированного кода.
- **`Dispatch_Wrapper_Asm()`**:
   - **Описание:** Небольшая ассемблерная функция (определенная с помощью `__declspec(naked)` или `asm volatile`), которая служит местом назначения для всех трамплинов.
   - **Действие:** Сохраняет регистры, перемещает `EAX` (содержащий `hook_id`) в стек и вызывает функцию C++ `Dispatch_Hook`. После возврата из `Dispatch_Hook` восстанавливает регистры и возвращается.
- **`cell SAMP_SDK_CDECL Dispatch_Hook(int hook_id, AMX* amx, cell* params)`**:
   - **Описание:** Общая функция C++, вызываемая `Dispatch_Wrapper_Asm`.
   - **Действие:** Использует `hook_id` для поиска соответствующего `Native_Hook` в `Native_Hook_Manager` и вызывает его метод `Dispatch()`, который, в свою очередь, вызывает обработчик `Plugin_Native_Hook` пользователя.
   - **Соображения компоновки:** Эта функция является критической точкой взаимодействия между C++ и ассемблером. Чтобы гарантировать ее корректный экспорт и обнаружение компоновщиком в Linux (GCC/Clang), она определяется с тремя важными характеристиками:
      1. **`extern "C"`**: Предотвращает C++ Name Mangling, гарантируя, что символ имеет чистое имя C `Dispatch_Hook`, которое ищет ассемблерный код.
      2. **`inline`**: Позволяет определению функции находиться в заголовочном файле (необходимо для header-only библиотеки), не вызывая ошибок "множественное определение" (ODR - One Definition Rule).
      3. **`SAMP_SDK_USED_BY_ASM` (`__attribute__((used))` в GCC/Clang)**: Заставляет компилятор генерировать код для функции, даже если он не находит никаких вызовов к ней из другого кода C++. Это предотвращает ее ошибочное удаление оптимизатором.
- **`Native_Hook_Manager`**:
   - **Описание:** Центральный `singleton`, который управляет всеми зарегистрированными `Native_Hook`s и их трамплинами.
   - **`std::list<Native_Hook> hooks_`**: Хранит список хуков по порядку.
   - **`std::unordered_map<uint32_t, Trampoline_Func> hash_to_trampoline_`**: Сопоставляет хеш имени нативной функции с указателем на сгенерированный трамплин.
   - **`std::vector<uint32_t> hook_id_to_hash_`**: Сопоставляет целочисленный ID хука (используемый в трамплине) обратно с хешем имени нативной функции.
   - **`Get_Trampoline(uint32_t hash)`**: Возвращает (или создает и выделяет) указатель трамплина для заданного хеша нативной функции.
- **`PLUGIN_NATIVE_HOOK_REGISTRATION`**:
   - **Механизм:** Макрос, который создает глобальный статический класс (`Native_Hook_Register_##name`) для каждого `Plugin_Native_Hook`. В статическом конструкторе этого класса он регистрирует `handler` пользователя в `Native_Hook_Manager`.

### 4.9. `callbacks.hpp` & `amx_memory.hpp`: Вызовы C++ -> Pawn и RAII

Эти заголовки составляют основу для вызова Pawn-функций из C++ (макросы `Pawn_*`) и обеспечивают безопасность памяти.

- **`Amx_Sandbox`**:
   - **Описание:** Структура `thread_local`, которая имитирует минималистичную и изолированную среду `AMX` для вызовов `Pawn_Native` и `Plugin_Call`.
   - **Механизм:** Имеет собственную структуру `AMX`, `AMX_HEADER` и `std::vector<unsigned char> heap` для имитации памяти скрипта. Это позволяет вызывать `amx::Push`, `amx::Allot` и т. д., не вмешиваясь в состояние реальных выполняющихся Pawn-скриптов.
   - **`thread_local`:** Гарантирует, что каждый поток имеет свою собственную `Amx_Sandbox`, предотвращая состояния гонки, если SDK используется в многопоточном контексте (например, будущий пул потоков для операций, не связанных с Pawn).
   - **Пример (`Amx_Sandbox`):**
      ```cpp
      // Simplified snippet from callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Simulated memory for stack/heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Initializes AMX and header
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
   - **Описание:** Набор перегруженных шаблонных функций, которые управляют `marshalling` *каждого* C++ параметра в формат `cell`, ожидаемый AMX, и наоборот для выходных параметров.
   - **Обработка ввода:**
       - Для `int`, `float`, `bool`: Преобразует напрямую в `cell`.
       - Для `const char*`, `std::string`: Выделяет память в куче `Amx_Sandbox` (или реальной AMX для `Pawn_Public`), копирует строку и помещает AMX-адрес в стек.
   - **Обработка вывода (`is_output_arg`):**
       - **Механизм:** Когда аргумент является неконстантной ссылкой lvalue (обнаруживается трейтом `is_output_arg`), `Parameter_Processor` не помещает значение, а вместо этого помещает *AMX-адрес* для `cell`, временно выделенной в куче.
       - **`std::vector<std::function<void()>> post_call_updaters`**: После вызова нативной функции Pawn выполняется список лямбд (`post_call_updaters`). Каждая лямбда отвечает за чтение конечного значения `cell`, выделенной в AMX, и присвоение его обратно исходной переменной C++ (например, `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Механизм:** `std::integral_constant` (трейт типа), который во время компиляции оценивает, является ли тип параметра C++ изменяемой ссылкой (например, `int&`, `float&`, `std::string&`). Это позволяет `Parameter_Processor` различать входные и выходные параметры.
   - **Пример (`is_output_arg`):**
      ```cpp
      // Simplified snippet from callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Описание:** Класс RAII (`Resource Acquisition Is Initialization`), инкапсулирующий выделение и освобождение памяти в AMX.
   - **Механизм:** В конструкторе он вызывает `amx::Allot` для получения `amx_addr` и `phys_addr`. В деструкторе он вызывает `amx::Release` для освобождения этой памяти.
   - **Воздействие:** **Критически важно для предотвращения утечек памяти в куче AMX.** Гарантирует, что временная память, используемая для строк или выходных параметров, всегда освобождается, даже если возникают исключения или преждевременные возвраты.

### 4.10. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Абстрагированный доступ к AMX

Эти заголовки предоставляют фундаментальные определения и высокоуровневые инструменты для взаимодействия с Pawn.

- **`amx_defs.h`**:
   - **Содержание:** Содержит необработанные определения структур AMX (`AMX`, `AMX_HEADER`), типов (`cell`, `ucell`) и перечислений ошибок (`AmxError`). Также определяет `AMX_NATIVE` и `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Использует атрибуты упаковки (`#pragma pack(push, 1)` / `__attribute__((packed))`), чтобы гарантировать правильное расположение AMX-структур в памяти, что является фундаментальным для взаимодействия.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Описание:** Основная шаблонная функция для вызова функций AMX API, экспортируемых сервером.
   - **Механизм:** Получает указатель на функцию через `Core::Instance().Get_AMX_Export(Index)` и вызывает ее. Централизует обработку ошибок, если указатель на функцию недоступен.
   - **Воздействие:** Преобразует низкоуровневые вызовы (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) в идиоматические и типобезопасные вызовы C++ (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Описание:** Основные функции для преобразования значений `cell` в `float` и наоборот, выполняющие битовое переинтерпретацию памяти.
   - **`static_assert`:** Включают `static_assert` для обеспечения того, чтобы `sizeof(cell) == sizeof(float)` во время компиляции, предотвращая ошибки на платформах с разными размерами типов.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Описание:** Вспомогательная функция для преобразования AMX-адреса строки в `std::string`.
   - **Механизм:** Сначала получает физический адрес (`cell* phys_addr`) строки в AMX с помощью `amx::Get_Addr`. Затем использует `amx::STR_Len` для определения длины и `amx::Get_String` для копирования байтов в `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Описание:** Базовая функция форматирования строк (`printf`-подобная) для SDK.
   - **Механизм:** Использует `vsnprintf` в два прохода: сначала для определения необходимого размера строки, а затем для форматирования строки в динамически выделенный `std::string`. Это предотвращает переполнение буфера.

## 5. Компиляция и развертывание

### Требования к архитектуре и платформе

- Ваш плагин **ДОЛЖЕН** быть скомпилирован для архитектуры **x86 (32-бит)**.
- Поддерживаемые платформы: Windows (.dll) и Linux (.so).

### Примеры команд компиляции

#### **MSVC (Visual Studio)**

1. Создайте новый проект "Динамически подключаемая библиотека (DLL)".
2. В параметрах проекта установите "Платформа решения" на **x86**.
3. Убедитесь, что стандарт языка C++ не ниже C++14.

#### **GCC / Clang (Linux)**

```bash
# For a plugin named 'my_plugin.so' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Компилирует для 32-битной архитектуры.
- `-shared`: Создает общую библиотеку (`.so`).
- `-std=c++17`: Устанавливает стандарт C++ на C++17 (может быть `c++14` или `c++20`).
- `-O2`: Уровень оптимизации 2.
- `-fPIC`: Генерирует позиционно-независимый код, необходимый для общих библиотек.
- `-Wall -Wextra`: Включает дополнительные предупреждения для выявления ошибок.
- `-Wl,--no-undefined`: Предотвращает создание библиотеки, если есть неопределенные символы.

#### **GCC / Clang (MinGW в Windows)**

```bash
# For a plugin named 'my_plugin.dll' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Статически компонует стандартную библиотеку C++. Важно для предотвращения зависимости вашего плагина от специфических для компилятора DLL среды выполнения, которые могут отсутствовать в системе пользователя.
- `-static-libgcc`: Статически компонует библиотеку GCC.

### Соображения по распространению

- **Имя файла:** Ваш плагин должен иметь расширение `.dll` (Windows) или `.so` (Linux). Например: `my_plugin.dll`.
- **Расположение:** Поместите скомпилированный файл в папку `plugins/` вашего SA-MP сервера.
- **server.cfg:** Добавьте имя вашего плагина (если Windows, без расширения) в строку `plugins` в `server.cfg`.
   ```
   plugins my_plugin (if Linux, my_plugin.so)
   ```

## Лицензия

Copyright © **SA-MP Programming Community**

Данное программное обеспечение лицензируется в соответствии с условиями лицензии MIT ("Лицензия"); вы можете использовать это программное обеспечение в соответствии с условиями Лицензии. Копию Лицензии можно получить по адресу: [MIT License](https://opensource.org/licenses/MIT)

### Условия использования

#### 1. Предоставленные разрешения

Настоящая лицензия бесплатно предоставляет любому лицу, получающему копию данного программного обеспечения и связанных с ним файлов документации, следующие права:
* Использовать, копировать, изменять, объединять, публиковать, распространять, сублицензировать и/или продавать копии программного обеспечения без ограничений
* Разрешать лицам, которым предоставляется программное обеспечение, делать то же самое при соблюдении указанных ниже условий

#### 2. Обязательные условия

Все копии или существенные части программного обеспечения должны включать:
* Вышеуказанное уведомление об авторских правах
* Данное уведомление о разрешении
* Приведенное ниже заявление об отказе от ответственности

#### 3. Авторские права

Программное обеспечение и вся связанная с ним документация защищены законами об авторских правах. **SA-MP Programming Community** сохраняет за собой оригинальные авторские права на программное обеспечение.

#### 4. Отказ от гарантий и ограничение ответственности

ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ "КАК ЕСТЬ", БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, ЯВНЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ, НО НЕ ОГРАНИЧИВАЯСЬ ГАРАНТИЯМИ ТОВАРНОЙ ПРИГОДНОСТИ, ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОЙ ЦЕЛИ И НЕНАРУШЕНИЯ ПРАВ.

НИ ПРИ КАКИХ ОБСТОЯТЕЛЬСТВАХ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ ОТВЕТСТВЕННОСТИ ЗА ЛЮБЫЕ ПРЕТЕНЗИИ, УБЫТКИ ИЛИ ИНУЮ ОТВЕТСТВЕННОСТЬ, БУДЬ ТО В СИЛУ ДОГОВОРА, ДЕЛИКТА ИЛИ ИНЫМ ОБРАЗОМ, ВОЗНИКАЮЩИЕ ИЗ, ИЗ-ЗА ИЛИ В СВЯЗИ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ ИЛИ ИСПОЛЬЗОВАНИЕМ ИЛИ ИНЫМИ ДЕЙСТВИЯМИ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.

---

Для подробной информации о лицензии MIT посетите: https://opensource.org/licenses/MIT