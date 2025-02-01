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

SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) представляет собой комплексную коллекцию C-файлов и headers, которые позволяют разработчикам создавать плагины для сервера SA-MP. Этот SDK предоставляет основу для расширения функциональности сервера SA-MP через нативные функции, позволяя разработчикам реализовывать функции, выходящие за рамки того, что доступно в скриптах Pawn.

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

- [samp-sdk](#samp-sdk)
  - [Языки](#языки)
  - [Оглавление](#оглавление)
  - [Основные компоненты](#основные-компоненты)
    - [Система AMX](#система-amx)
      - [Основные AMX Headers](#основные-amx-headers)
    - [Поддержка платформ](#поддержка-платформ)
    - [Система плагинов](#система-плагинов)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [Нативные функции AMX](#нативные-функции-amx)
  - [Технические детали](#технические-детали)
    - [Управление памятью](#управление-памятью)
    - [Операции с памятью](#операции-с-памятью)
    - [Обработка ошибок](#обработка-ошибок)
    - [Обработка строк](#обработка-строк)
    - [Строковые операции](#строковые-операции)
  - [Поддержка Unicode](#поддержка-unicode)
    - [Операции с Unicode](#операции-с-unicode)
  - [Кросс-платформенная совместимость](#кросс-платформенная-совместимость)
  - [Системные требования](#системные-требования)
    - [Поддержка компиляторов](#поддержка-компиляторов)
  - [Лучшие практики](#лучшие-практики)
  - [Внутренние структуры](#внутренние-структуры)
    - [Структура AMX Header](#структура-amx-header)
  - [Расширенные функции](#расширенные-функции)
    - [Поддержка JIT-компиляции](#поддержка-jit-компиляции)
    - [Интерфейс отладки](#интерфейс-отладки)
    - [Интерфейс публичных функций](#интерфейс-публичных-функций)
  - [Информация о версиях](#информация-о-версиях)
    - [Совместимость версий](#совместимость-версий)
  - [Лицензия](#лицензия)
    - [Условия использования](#условия-использования)
      - [1. Предоставленные разрешения](#1-предоставленные-разрешения)
      - [2. Обязательные условия](#2-обязательные-условия)
      - [3. Авторские права](#3-авторские-права)
      - [4. Отказ от гарантий и ограничение ответственности](#4-отказ-от-гарантий-и-ограничение-ответственности)

## Основные компоненты

### Система AMX

AMX (Abstract Machine eXecutor) - это виртуальная машина, которая выполняет скрипты Pawn в SA-MP. SDK предоставляет обширную поддержку для взаимодействия с AMX через различные C-файлы и headers:

#### Основные AMX Headers

1. **amx.h**

    Основной header-файл, который объединяет всю функциональность, связанную с AMX. Включает:
    - Основные функции AMX для выполнения скриптов
    - Управление памятью
    - Регистрация нативных функций
    - Обработка строк
    - Поддержка UTF-8

    Ключевые функции включают:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    ```

2. **amx_cell.h**

    Определяет фундаментальные типы данных, используемые в системе AMX:
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

    Содержит основные структуры для работы AMX:

    ```c
    typedef struct tagAMX {
        unsigned char _FAR *base;    // Базовый адрес
        unsigned char _FAR *data;    // Сегмент данных
        AMX_CALLBACK callback;       // Функция обратного вызова
        AMX_DEBUG debug;            // Отладочный callback
        cell cip;                   // Указатель инструкции кода
        cell frm;                   // База кадра стека
        cell hea;                   // База кучи
        cell stk;                   // Указатель стека
        // ... дополнительные поля
    } AMX;
    ```

### Поддержка платформ

SDK включает надежную обработку специфики платформ через различные headers:

1. **amx_platform.h**

    Обеспечивает определение платформы и конфигурацию:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Обрабатывает определения, специфичные для операционной системы:
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

### Система плагинов

#### plugincommon.h

Определяет основной интерфейс плагина и вспомогательные структуры:

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

Файл `amxplugin.c` является важным компонентом SA-MP SDK, который предоставляет платформо-зависимые реализации функций AMX. Он реализует два различных подхода в зависимости от платформы и компилятора:

1. **Реализация для Windows MSVC (32-bit)**
    - Использует naked функции с ассемблером для прямого доступа к таблице функций
    - Обеспечивает оптимизированную производительность через прямые переходы к функциям AMX
    - Пример структуры:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Кросс-платформенная реализация**
    - Использует указатели на функции для платформенной независимости
    - Реализует систему, основанную на макросах, для определения функций
    - Пример структуры:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

Ключевые особенности:

3. **Управление таблицей функций**
    - Использует статический указатель `pAMXFunctions` для хранения таблицы функций AMX
    - Обеспечивает доступ ко всем основным функциям AMX
    - Обрабатывает разрешение функций во время выполнения

4. **Платформо-специфичные оптимизации**
    - Windows 32-bit: Использует naked функции для прямой реализации на ассемблере
    - Другие платформы: Использует косвенные указатели на функции
    - Специальная обработка для 64-битных систем

5. **Реализованные категории функций**

    a. Функции управления памятью:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. Функции выполнения:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. Управление символами:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. Обработка строк:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Функции поддержки UTF-8
    
    e. Отладка и информация:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Условная компиляция**
    - Обрабатывает различные платформы через директивы препроцессора
    - Специальная обработка для 64-битных систем
    - Опциональная поддержка JIT
    ```c
    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
            PLUGIN_AMX_EXPORT_Align64)
    #endif
    ```

7. **Интеграция обработки ошибок**
    - Реализует `amx_RaiseError` для отчетов об ошибках
    - Сохраняет коды ошибок между вызовами функций
    - Интегрируется с системой отладки AMX

### Нативные функции AMX

SDK предоставляет комплексную поддержку для создания и управления нативными функциями:

```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

Ключевые операции с нативными функциями:
- Регистрация через `amx_Register`
- Доступ к параметрам и валидация
- Обработка возвращаемых значений
- Отчеты об ошибках

## Технические детали

### Управление памятью

SDK предоставляет комплексные средства управления памятью:

1. **amx_memory.h**

   Обрабатывает выделение памяти и платформо-зависимые операции с памятью:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```

2. **amx_alignment.h**

    Управляет требованиями выравнивания памяти:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Операции с памятью

SDK включает несколько функций для манипуляции памятью:

1. **Выделение памяти**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Выделяет память в куче AMX
    - Возвращает как AMX, так и физические адреса
    - Обрабатывает требования выравнивания

2. **Доступ к памяти**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Преобразует AMX адреса в физические адреса
    - Проверяет доступ к памяти
    - Обрабатывает границы памяти

3. **Информация о памяти**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Получает информацию о размещении памяти
    - Сообщает размеры сегментов
    - Полезно для отладки и оптимизации

### Обработка ошибок

SDK включает комплексную систему обработки ошибок, определенную в `amx_constants.h`:

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

### Обработка строк

SDK предоставляет надежные возможности обработки строк через различные макросы и функции:

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

### Строковые операции

1. **Длина строки**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Вычисляет длину строки
    - Обрабатывает упакованные и неупакованные строки
    - Возвращает длину в символах

2. **Преобразование строк**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Преобразует C-строки в AMX-строки
    - Поддерживает упакованные и неупакованные форматы
    - Обрабатывает преобразование Unicode

## Поддержка Unicode

SDK включает комплексную поддержку Unicode через функции обработки UTF-8:

```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Операции с Unicode

1. **Проверка UTF-8**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - Проверяет UTF-8 кодированные строки
    - Сообщает длину строки в символах
    - Обнаруживает ошибки кодирования

2. **Преобразование символов**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Извлекает Unicode символы
    - Обрабатывает многобайтовые последовательности
    - Сообщает об ошибках разбора

## Кросс-платформенная совместимость

SDK обеспечивает кросс-платформенную совместимость через:

1. **Обработка порядка байтов**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Обработка путей**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

## Системные требования

SDK поддерживает несколько платформ и компиляторов:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Поддержка компиляторов

1. **Microsoft Visual C++**
   - Обработка pragma
   - Подавление предупреждений
   - Соглашения о вызовах

2. **GCC**
   - Управление диагностикой
   - Спецификации атрибутов
   - Платформо-специфичные оптимизации

3. **Clang**
   - Конфигурации предупреждений
   - Кросс-платформенная совместимость
   - Современные функции C++

## Лучшие практики

При использовании SA-MP SDK учитывайте следующие лучшие практики:

1. **Управление памятью**
   - Всегда очищайте выделенные ресурсы
   - Используйте правильное выравнивание памяти
   - Корректно обрабатывайте ошибки памяти
   - Отслеживайте использование кучи
   - Реализуйте правильную проверку границ памяти
   - Используйте пулы памяти для частых выделений
   - Очищайте ресурсы в обратном порядке выделения

2. **Обработка ошибок**
   - Проверяйте возвращаемые значения функций AMX
   - Реализуйте правильную обработку ошибок в нативных функциях
   - Используйте предоставленные константы ошибок
   - Корректно логируйте ошибки
   - Реализуйте механизмы восстановления после ошибок
   - Предоставляйте осмысленные сообщения об ошибках
   - Обрабатывайте системно-специфичные ошибки

3. **Кросс-платформенная разработка**
   - Используйте платформо-независимые типы
   - Используйте предоставленные макросы для платформо-специфичного кода
   - Тестируйте на нескольких платформах
   - Обрабатывайте различия в порядке байтов
   - Используйте правильные разделители путей
   - Учитывайте различия файловых систем
   - Реализуйте платформо-специфичные оптимизации

4. **Соображения производительности**
   - Используйте подходящие размеры ячеек
   - Реализуйте эффективную обработку строк
   - Оптимизируйте вызовы нативных функций
   - Минимизируйте выделения памяти
   - Используйте подходящие структуры данных
   - Реализуйте кэширование где уместно
   - Профилируйте критические пути кода

При работе с функционалом `amxplugin.c`:

1. **Платформо-специфичная разработка**
   - Учитывайте различия платформ в реализациях функций
   - Тестируйте на 32-битных и 64-битных системах
   - Обрабатывайте платформо-специфичные требования выравнивания
   - Проверяйте указатель таблицы функций перед использованием
   - Реализуйте соответствующую проверку ошибок для каждой платформы
   - Учитывайте влияние различных реализаций на производительность

2. **Управление таблицей функций**
   - Инициализируйте таблицу функций перед использованием
   - Проверяйте доступность функций
   - Корректно обрабатывайте отсутствующие функции
   - Реализуйте правильные процедуры очистки
   - Кэшируйте часто используемые указатели на функции
   - Проверяйте целостность таблицы функций

3. **Обработка ошибок**
   - Реализуйте правильную проверку ошибок для платформо-специфичного кода
   - Корректно обрабатывайте ошибки выравнивания
   - Проверяйте записи таблицы функций
   - Предоставляйте осмысленные сообщения об ошибках
   - Реализуйте механизмы восстановления
   - Логируйте платформо-специфичные ошибки

## Внутренние структуры

### Структура AMX Header

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Размер "файла"
    uint16_t magic;        // Сигнатура
    char    file_version;  // Версия формата файла
    char    amx_version;   // Требуемая версия AMX
    int16_t flags;         // Флаги
    int16_t defsize;      // Размер записи определения
    int32_t cod;          // Начальное значение COD - блок кода
    int32_t dat;          // Начальное значение DAT - блок данных
    int32_t hea;          // Начальное значение HEA - начало кучи
    int32_t stp;          // Начальное значение STP - вершина стека
    int32_t cip;          // Начальное значение CIP - указатель инструкции кода
    int32_t publics;      // Смещение до публичных функций
    int32_t natives;      // Смещение до таблицы нативных функций
    int32_t libraries;    // Смещение до библиотек
    int32_t pubvars;      // Смещение до публичных переменных
    int32_t tags;         // Смещение до тегов
    int32_t nametable;    // Смещение до таблицы имен
} AMX_HEADER;
```

Эта структура критически важна для понимания формата файла AMX и того, как виртуальная машина загружает и выполняет скрипты.

## Расширенные функции

### Поддержка JIT-компиляции

SDK включает поддержку Just-In-Time компиляции:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Интерфейс отладки

Поддержка отладки предоставляется через:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Интерфейс публичных функций

SDK предоставляет комплексную поддержку для работы с публичными функциями:

1. **Поиск публичных функций**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Находит публичные функции по имени
    - Возвращает индекс функции
    - Проверяет существование функции

2. **Выполнение публичных функций**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Выполняет публичные функции
    - Обрабатывает возвращаемые значения
    - Управляет контекстом выполнения

## Информация о версиях

SDK включает константы версий для проверки совместимости:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Совместимость версий

SDK поддерживает совместимость через:
1. Проверку версии файла
2. Проверку версии AMX
3. Проверку совместимости JIT
4. Определение функций
5. Обработку версий для конкретных платформ

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