# samp-sdk

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Language](https://img.shields.io/badge/Language-C-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![SDK](https://img.shields.io/badge/SA--MP-SDK-orange.svg)](https://github.com/spc-samp/samp-sdk)
[![Platform Windows](https://img.shields.io/badge/Windows-0078D6?style=flat&logo=windows&logoColor=white)](https://github.com/spc-samp/samp-sdk)
[![Platform Linux](https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black)](https://github.com/spc-samp/samp-sdk)
[![Platform FreeBSD](https://img.shields.io/badge/FreeBSD-AB2B28?style=flat&logo=freebsd&logoColor=white)](https://github.com/spc-samp/samp-sdk)
[![AMX](https://img.shields.io/badge/AMX-Powered-yellow.svg)](https://github.com/spc-samp/samp-sdk)
[![Native Support](https://img.shields.io/badge/Natives-Supported-success.svg)](https://github.com/spc-samp/samp-sdk)
[![Memory Safe](https://img.shields.io/badge/Memory-Safe-red.svg)](https://github.com/spc-samp/samp-sdk)

SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) представляет собой всеобъемлющую коллекцию C-файлов и заголовочных файлов (headers), которые позволяют разработчикам создавать плагины для сервера SA-MP. Этот SDK предоставляет основу для расширения функциональности сервера SA-MP через нативные функции, позволяя разработчикам реализовывать возможности, выходящие за пределы доступного в скриптах Pawn.

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
      - [Основные заголовочные файлы AMX](#основные-заголовочные-файлы-amx)
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
      - [1. Объем лицензии](#1-объем-лицензии)
      - [2. Обязательные условия](#2-обязательные-условия)
      - [3. Авторские права](#3-авторские-права)
      - [4. Отказ от гарантий и ограничение ответственности](#4-отказ-от-гарантий-и-ограничение-ответственности)

## Основные компоненты

### Система AMX

AMX (Abstract Machine eXecutor) — это виртуальная машина, которая выполняет скрипты Pawn в SA-MP. SDK предоставляет всестороннюю поддержку для взаимодействия с системой AMX через различные C-файлы и заголовочные файлы.

#### Основные заголовочные файлы AMX

1. **amx.h**

    Основной заголовочный файл, объединяющий всю функциональность, связанную с AMX:
    - Основные функции для выполнения скриптов
    - Управление памятью
    - Регистрация нативных функций
    - Обработка строк
    - Поддержка UTF-8

    Важные функции включают:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);         // Инициализация экземпляра AMX
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index); // Выполнение публичной функции
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number); // Регистрация нативных функций
    ```

2. **amx_platform.h**

    Отвечает за определение платформы и конфигурацию:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```
    - Определяет системы, такие как Linux, FreeBSD, OpenBSD и macOS.
    - Включает `sclinux.h` для Unix-подобных систем.
    - Определяет 64-битные архитектуры:
      ```c
      #if defined _LP64 || defined WIN64 || defined _WIN64
          #define __64BIT__
      #endif
      ```
    - Вычисляет версию GCC, если применимо:
      ```c
      #if defined __GNUC__
          #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #endif
      ```

3. **amx_constants.h**

    Определяет базовые константы для функциональности AMX:
    - **Версии**:
      ```c
      #define CUR_FILE_VERSION  9   // Текущая версия формата файла
      #define MIN_FILE_VERSION  6   // Минимальная поддерживаемая версия
      #define MIN_AMX_VERSION   10  // Минимальная версия AMX
      #define MAX_FILE_VER_JIT  8   // Максимальная версия с поддержкой JIT
      #define MIN_AMX_VER_JIT   8   // Минимальная версия с поддержкой JIT
      ```
    - **Магические коды**:
      ```c
      #define AMX_MAGIC_16    0xf1e2  // Для 16-битных ячеек
      #define AMX_MAGIC_32    0xf1e0  // Для 32-битных ячеек
      #define AMX_MAGIC_64    0xf1e1  // Для 64-битных ячеек
      ```
    - **Коды ошибок**:
      ```c
      enum {
          AMX_ERR_NONE,         // Нет ошибки
          AMX_ERR_EXIT,         // Скрипт завершен
          AMX_ERR_ASSERT,       // Утверждение не выполнено
          AMX_ERR_STACKERR,     // Ошибка стека
          AMX_ERR_BOUNDS,       // Выход за пределы
          AMX_ERR_MEMACCESS,    // Недопустимый доступ к памяти
          AMX_ERR_INVINSTR,     // Недопустимая инструкция
          AMX_ERR_STACKLOW,     // Стек слишком мал
          AMX_ERR_HEAPLOW,      // Куча слишком мала
          AMX_ERR_CALLBACK,     // Ошибка обратного вызова
          AMX_ERR_NATIVE,       // Ошибка нативной функции
          AMX_ERR_DIVIDE,       // Деление на ноль
          AMX_ERR_SLEEP,        // Режим сна активирован
          AMX_ERR_INVSTATE,     // Недопустимое состояние
          AMX_ERR_MEMORY = 16,  // Недостаточно памяти
          AMX_ERR_FORMAT,       // Недопустимый формат
          AMX_ERR_VERSION,      // Несовместимая версия
          AMX_ERR_NOTFOUND,     // Ресурс не найден
          AMX_ERR_INDEX,        // Недопустимый индекс
          AMX_ERR_DEBUG,        // Ошибка отладки
          AMX_ERR_INIT,         // Ошибка инициализации
          AMX_ERR_USERDATA,     // Ошибка пользовательских данных
          AMX_ERR_INIT_JIT,     // Ошибка инициализации JIT
          AMX_ERR_PARAMS,       // Недопустимые параметры
          AMX_ERR_DOMAIN,       // Ошибка домена
          AMX_ERR_GENERAL,      // Общая ошибка
      };
      ```
    - **Флаги**:
      ```c
      #define AMX_FLAG_DEBUG      0x02   // Режим отладки
      #define AMX_FLAG_COMPACT    0x04   // Компактное кодирование
      #define AMX_FLAG_SLEEP      0x08   // Поддержка сна
      #define AMX_FLAG_NOCHECKS   0x10   // Без проверок безопасности
      #define AMX_FLAG_NO_RELOC   0x200  // Без перемещения
      #define AMX_FLAG_NO_SYSREQD 0x400  // Без sysreq.d
      #define AMX_FLAG_SYSREQN    0x800  // Поддержка sysreq.n
      #define AMX_FLAG_NTVREG     0x1000 // Регистрация нативных функций
      #define AMX_FLAG_JITC       0x2000 // JIT-компиляция
      #define AMX_FLAG_BROWSE     0x4000 // Режим просмотра
      #define AMX_FLAG_RELOC      0x8000 // Перемещение включено
      ```
    - **Коды выполнения**:
      ```c
      #define AMX_EXEC_MAIN   (-1)  // Выполнить главную функцию
      #define AMX_EXEC_CONT   (-2)  // Продолжить выполнение
      ```

4. **amx_memory.h**

    Управляет выделением памяти:
    - Поддержка `alloca`:
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
    - Определяет запас сжатия:
      ```c
      #if !defined AMX_COMPACTMARGIN
          #define AMX_COMPACTMARGIN 64
      #endif
      ```

5. **amx_calling.h**

    Определяет соглашения о вызовах:
    - Для нативных функций и API:
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

    Определяет стандартизированные целочисленные типы:
    - Поддержка `stdint.h` или ручные определения:
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

    Предоставляет полезные макросы:
    - **Вычисление адреса**:
      ```c
      #define amx_Address(amx,addr) \
          (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))
      ```
    - **Обработка строк**:
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
    - **Количество параметров**:
      ```c
      #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))
      ```
    - **Регистрация функций**:
      ```c
      #define amx_RegisterFunc(amx, name, func) \
          amx_Register((amx), amx_NativeInfo((name),(func)), 1)
      ```

8. **amx_cell.h**

    Определяет типы ячеек:
    - Настраивает `PAWN_CELL_SIZE` (по умолчанию: 32):
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
    - Поддержка чисел с плавающей точкой:
      ```c
      #if PAWN_CELL_SIZE==32
          #define amx_ftoc(f)   (*(cell*)&(f))  // Float в ячейку
          #define amx_ctof(c)   (*(float*)&(c))  // Ячейка в float
      #elif PAWN_CELL_SIZE==64
          #define amx_ftoc(f)   (*(cell*)&(f))  // Double в ячейку
          #define amx_ctof(c)   (*(double*)&(c)) // Ячейка в double
      #endif
      ```
    - Манипуляция символами:
      ```c
      #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))  // Для 32-бит
      ```

9. **amx_structures.h**

    Определяет основные структуры:
    - **AMX**:
      ```c
      typedef struct tagAMX {
          unsigned char _FAR *base;    // Базовый адрес
          unsigned char _FAR *data;    // Сегмент данных
          AMX_CALLBACK callback;       // Функция обратного вызова
          AMX_DEBUG debug;            // Отладочный обратный вызов
          cell cip;                   // Указатель инструкции кода
          cell frm;                   // База кадра стека
          cell hea;                   // База кучи
          cell hlw;                   // Нижняя граница кучи
          cell stk;                   // Указатель стека
          cell stp;                   // Вершина стека
          int flags;                  // Флаги
          long usertags[AMX_USERNUM]; // Пользовательские теги
          void _FAR *userdata[AMX_USERNUM]; // Пользовательские данные
          int error;                  // Код ошибки
          int paramcount;             // Количество параметров
          cell pri;                   // Первичный регистр
          cell alt;                   // Альтернативный регистр
          cell reset_stk;             // Сброс стека
          cell reset_hea;             // Сброс кучи
          cell sysreq_d;              // Адрес sysreq.d
          #if defined JIT
              int reloc_size;         // Размер перемещения
              long code_size;         // Размер кода
          #endif
      } AMX;
      ```
    - **AMX_HEADER**:
      ```c
      typedef struct tagAMX_HEADER {
          int32_t size;          // Размер файла
          uint16_t magic;        // Сигнатура
          char    file_version;  // Версия файла
          char    amx_version;   // Версия AMX
          int16_t flags;         // Флаги
          int16_t defsize;       // Размер определения
          int32_t cod;           // Начало кода
          int32_t dat;           // Начало данных
          int32_t hea;           // Начало кучи
          int32_t stp;           // Вершина стека
          int32_t cip;           // Начальный указатель инструкции кода
          int32_t publics;       // Смещение до публичных функций
          int32_t natives;       // Смещение до нативных функций
          int32_t libraries;     // Смещение до библиотек
          int32_t pubvars;       // Смещение до публичных переменных
          int32_t tags;          // Смещение до тегов
          int32_t nametable;     // Смещение до таблицы имен
      } AMX_HEADER;
      ```

### Поддержка платформ

SDK содержит надежную платформозависимую обработку через различные заголовочные файлы:

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

    Управляет определениями, специфичными для операционной системы:
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
    SUPPORTS_AMX_NATIVES = 0x10000,
    SUPPORTS_PROCESS_TICK = 0x20000
};

enum PLUGIN_DATA_TYPE {
    PLUGIN_DATA_LOGPRINTF = 0x00,
    PLUGIN_DATA_AMX_EXPORTS = 0x10,
    PLUGIN_DATA_CALLPUBLIC_FS = 0x11,
    PLUGIN_DATA_CALLPUBLIC_GM = 0x12
};
```

#### amxplugin.c

Файл `amxplugin.c` является ключевым компонентом SA-MP SDK и предоставляет платформозависимые реализации функций AMX. Он реализует два подхода в зависимости от платформы и компилятора:

1. **Реализация для Windows MSVC (32-бит)**
    - Использует "голые" функции с ассемблером для прямого доступа к таблице функций:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Кросс-платформенная реализация**
    - Использует указатели на функции для независимости от платформы:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

**Ключевые особенности**:

3. **Управление таблицей функций**
    - Использует статический указатель `pAMXFunctions` для хранения таблицы функций AMX.
    - Обеспечивает доступ ко всем основным функциям AMX.
    - Управляет разрешением функций в реальном времени.

4. **Платформозависимые оптимизации**
    - Windows 32-бит: Прямая реализация на ассемблере с голыми функциями.
    - Другие платформы: Косвенное использование через указатели на функции.
    - Специальная обработка для 64-битных систем.

5. **Реализованные категории функций**

    a. **Функции управления памятью**:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. **Функции выполнения**:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. **Управление символами**:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. **Обработка строк**:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Функции поддержки UTF-8
    
    e. **Отладка и информация**:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Условная компиляция**
    - Управляет различными платформами через директивы препроцессора.
    - Специальная обработка для 64-битных систем.
    - Опциональная поддержка JIT:
      ```c
      #if defined _I64_MAX || defined HAVE_I64
          DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
              PLUGIN_AMX_EXPORT_Align64)
      #endif
      ```

7. **Интеграция обработки ошибок**
    - Реализует `amx_RaiseError` для отчетности об ошибках.
    - Сохраняет коды ошибок между вызовами функций.
    - Интегрируется с системой отладки AMX.

### Нативные функции AMX

SDK предоставляет полную поддержку для создания и управления нативными функциями:
```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

**Основные операции с нативными функциями**:
- Регистрация через `amx_Register`.
- Доступ и проверка параметров через `amx_NumParams`.
- Управление возвращаемыми значениями.
- Отчетность об ошибках через `amx_RaiseError`.

## Технические детали

### Управление памятью

SDK предлагает обширные инструменты для управления памятью:

1. **amx_memory.h**

    Управляет выделением памяти и платформозависимыми операциями:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```
    - Определяет `AMX_COMPACTMARGIN` как 64 по умолчанию для сжатия памяти.

2. **amx_alignment.h**

    Управляет требованиями к выравниванию памяти:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Операции с памятью

SDK включает несколько функций для манипуляции с памятью:

1. **Выделение памяти**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Выделяет память в куче AMX.
    - Возвращает адреса AMX и физические адреса.
    - Управляет требованиями к выравниванию.

2. **Доступ к памяти**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Преобразует адреса AMX в физические адреса.
    - Проверяет доступ к памяти.
    - Управляет границами памяти.

3. **Информация о памяти**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Получает информацию о расположении памяти.
    - Сообщает размеры сегментов.
    - Полезно для отладки и оптимизации.

### Обработка ошибок

SDK содержит обширную систему обработки ошибок, определенную в `amx_constants.h`:
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
            ((result)=(void*)alloca((result##_length_+1)*sizeof(*(result))))!=NULL) \
        amx_GetString((char*)(result),amx_Address(amx,param), \
                            sizeof(*(result))>1,result##_length_+1); \
        else (result)=NULL; \
    } while(0)
```
- Альтернатива для `char*`:
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

### Строковые операции

1. **Длина строки**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Вычисляет длину строки.
    - Управляет упакованными и неупакованными строками.
    - Возвращает длину в символах.

2. **Преобразование строк**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Преобразует C-строки в AMX-строки.
    - Поддерживает упакованные и неупакованные форматы.
    - Управляет преобразованием Unicode.

## Поддержка Unicode

SDK предоставляет полную поддержку Unicode через функции обработки UTF-8:
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
    - Проверяет строки, закодированные в UTF-8.
    - Сообщает длину строки в символах.
    - Обнаруживает ошибки кодирования.

2. **Преобразование символов**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Извлекает символы Unicode.
    - Управляет многобайтовыми последовательностями.
    - Сообщает об ошибках разбора.

## Кросс-платформенная совместимость

SDK обеспечивает кросс-платформенную совместимость через:

1. **Управление порядком байтов**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Управление путями**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

3. **Платформонезависимые типы**
    - Определены в `amx_types.h` для согласованности.

## Системные требования

SDK поддерживает несколько платформ и компиляторов:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Поддержка компиляторов

1. **Microsoft Visual C++**
    - Управление pragma.
    - Подавление предупреждений.
    - Соглашения о вызовах через `amx_calling.h`.

2. **GCC**
    - Диагностические проверки.
    - Спецификации атрибутов.
    - Платформозависимые оптимизации.

3. **Clang**
    - Конфигурации предупреждений.
    - Кросс-платформенная совместимость.
    - Современные функции C++.

## Лучшие практики

При использовании SA-MP SDK учитывайте следующие лучшие практики:

1. **Управление памятью**
    - Всегда освобождайте выделенные ресурсы.
    - Используйте правильное выравнивание памяти.
    - Грамотно обрабатывайте ошибки памяти.
    - Отслеживайте использование кучи.
    - Реализуйте корректную проверку границ памяти.
    - Используйте пулы памяти для частых выделений.
    - Освобождайте ресурсы в обратном порядке выделения.

2. **Обработка ошибок**
    - Проверяйте возвращаемые значения функций AMX.
    - Реализуйте правильную обработку ошибок в нативных функциях.
    - Используйте предоставленные константы ошибок.
    - Ведите соответствующий журнал ошибок.
    - Реализуйте механизмы восстановления после ошибок.
    - Предоставляйте осмысленные сообщения об ошибках.
    - Обрабатывайте ошибки, специфичные для системы.

3. **Кросс-платформенная разработка**
    - Используйте платформонезависимые типы.
    - Применяйте предоставленные макросы для платформозависимого кода.
    - Тестируйте на нескольких платформах.
    - Управляйте различиями в порядке байтов.
    - Используйте правильные разделители путей.
    - Учитывайте различия в файловых системах.
    - Реализуйте оптимизации для конкретных платформ.

4. **Рекомендации по производительности**
    - Используйте подходящие размеры ячеек.
    - Реализуйте эффективную обработку строк.
    - Оптимизируйте вызовы нативных функций.
    - Минимизируйте выделение памяти.
    - Используйте подходящие структуры данных.
    - Применяйте кэширование там, где это уместно.
    - Профилируйте критические пути кода.

При работе с функциональностью `amxplugin.c`:

1. **Платформозависимая разработка**
    - Учитывайте различия платформ в реализации функций.
    - Тестируйте на 32-битных и 64-битных системах.
    - Управляйте платформозависимыми требованиями к выравниванию.
    - Проверяйте указатель таблицы функций перед использованием.
    - Реализуйте соответствующую проверку ошибок для каждой платформы.
    - Оценивайте влияние различных реализаций на производительность.

2. **Управление таблицей функций**
    - Инициализируйте таблицу функций перед использованием.
    - Проверяйте доступность функций.
    - Грамотно обрабатывайте отсутствующие функции.
    - Реализуйте соответствующие процедуры очистки.
    - Кэшируйте часто используемые указатели на функции.
    - Проверяйте целостность таблицы функций.

3. **Обработка ошибок**
    - Реализуйте соответствующую проверку ошибок для платформозависимого кода.
    - Корректно обрабатывайте ошибки выравнивания.
    - Проверяйте записи таблицы функций.
    - Предоставляйте осмысленные сообщения об ошибках.
    - Реализуйте механизмы восстановления.
    - Ведите журнал платформозависимых ошибок.

## Внутренние структуры

### Структура AMX Header

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Размер файла
    uint16_t magic;        // Сигнатура
    char    file_version;  // Версия формата файла
    char    amx_version;   // Требуемая версия AMX
    int16_t flags;         // Флаги
    int16_t defsize;       // Размер записи определения
    int32_t cod;           // Начальное значение COD - блок кода
    int32_t dat;           // Начальное значение DAT - сегмент данных
    int32_t hea;           // Начальное значение HEA - начало кучи
    int32_t stp;           // Начальное значение STP - вершина стека
    int32_t cip;           // Начальное значение CIP - указатель инструкции кода
    int32_t publics;       // Смещение до публичных функций
    int32_t natives;       // Смещение до нативных функций
    int32_t libraries;     // Смещение до библиотек
    int32_t pubvars;       // Смещение до публичных переменных
    int32_t tags;          // Смещение до тегов
    int32_t nametable;     // Смещение до таблицы имен
} AMX_HEADER;
```

Эта структура имеет решающее значение для понимания формата файла AMX и того, как виртуальная машина загружает и выполняет скрипты.

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

SDK предоставляет полную поддержку для работы с публичными функциями:

1. **Поиск публичных функций**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Находит публичные функции по имени.
    - Возвращает индекс функции.
    - Проверяет существование функции.

2. **Выполнение публичных функций**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Выполняет публичные функции.
    - Управляет возвращаемыми значениями.
    - Управляет контекстом выполнения.

## Информация о версиях

SDK содержит константы версий для проверки совместимости:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Совместимость версий

SDK поддерживает совместимость через:
1. Проверку версии файла.
2. Валидацию версии AMX.
3. Проверку совместимости JIT.
4. Обнаружение функций.
5. Управление версиями, специфичными для платформ.

## Лицензия

**Уведомление о правах собственности**: **SA-MP SDK**, содержащийся в этом репозитории, состоит из файлов с различными правообладателями, как подробно описано ниже:
- Файлы `amxplugin.c`, `plugin.h` и `plugincommon.h`, специфичные для **San Andreas Multiplayer (SA-MP)**, являются интеллектуальной собственностью **Kalcor и, возможно, членов команды SA-MP**, оригинальных создателей SA-MP.
- Файлы, связанные с **Pawn Abstract Machine (AMX)**, включая, но не ограничиваясь, `amx.h`, `amx.c`, `osdefs.h` и другими заголовочными файлами и реализациями, необходимыми для языка программирования Pawn, являются интеллектуальной собственностью **CompuPhase**, оригинального создателя Pawn, базирующегося в Нидерландах.
- Файл `sclinux.h`, вероятно, происходит из **SELinux или пользовательского подсистемы ядра Linux**, являясь частью среды, подобной Unix.
- Файлы `getch.h` и `getch.c` представляют собой независимые реализации, совместимые с POSIX, основанные на стандартных функциях, таких как `termios`, для ввода символов.
- **SA-MP Programming Community (SPC)** не претендует на авторские права на оригинальное содержимое **SA-MP SDK**, файлы **CompuPhase**, `sclinux.h` или `getch.h/c`. Единственная цель этого репозитория — облегчить доступ и организацию материалов для разработчиков плагинов в соответствии с принципами добросовестного использования и практиками сообщества.

**Лицензия, применимая к улучшениям**: Любые улучшения, модификации или дополнительные файлы, созданные **SA-MP Programming Community (SPC)** и включенные в этот репозиторий, лицензируются на условиях **Лицензии MIT**. Лицензия MIT применяется исключительно к этим конкретным вкладам и не распространяется на оригинальное содержимое **SA-MP SDK**, файлы **CompuPhase**, `sclinux.h` или `getch.h/c`. Копию Лицензии MIT можно найти по адресу: [MIT License](https://opensource.org/licenses/MIT).

**Лицензии оригинальных файлов**:
- Файлы `amx.h`, `amx.c`, `osdefs.h` (принадлежащие **CompuPhase**) и `sclinux.h` (вероятно, принадлежащие **SELinux или пользовательскому ядру**) лицензированы под **Apache License 2.0**. Подробности лицензии можно найти по адресу: [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0).
- Файлы `getch.h` и `getch.c` лицензированы под **Mozilla Public License 2.0 (MPL-2.0)**. Подробности лицензии можно найти по адресу: [MPL-2.0](https://www.mozilla.org/en-US/MPL/2.0/).
- Файлы `amxplugin.c`, `plugin.h` и `plugincommon.h` (принадлежащие **Kalcor и, возможно, членам команды SA-MP**) не имеют указанной лицензии.

### Условия использования

#### 1. Объем лицензии
Лицензия MIT предоставляет бесплатно любому лицу, получившему копию улучшений или дополнительных файлов, созданных **SPC**, следующие права:
- Использовать, копировать, изменять, объединять, публиковать, распространять, сублицензировать и/или продавать копии этих вкладов без ограничений.
- Разрешать лицам, которым предоставлены эти вклады, делать то же самое при соблюдении условий, указанных ниже.

#### 2. Обязательные условия
Все копии или существенные части вкладов **SPC** должны включать:
- Уведомление об авторских правах **SPC** на улучшения.
- Настоящее уведомление о разрешении.
- Уведомление об отказе от ответственности, указанное ниже.

#### 3. Авторские права
Улучшения и дополнительные файлы, созданные **SPC**, защищены законами об авторском праве, и **SPC** сохраняет право собственности на авторские права для этих конкретных вкладов. Файлы `amxplugin.c`, `plugin.h` и `plugincommon.h` остаются собственностью **Kalcor и, возможно, членов команды SA-MP**. Файлы **Pawn Abstract Machine (AMX)**, включая `osdefs.h`, остаются собственностью **CompuPhase**. Файл `sclinux.h`, вероятно, принадлежит **SELinux или пользовательскому подсистеме ядра Linux**, а `getch.h/c` — это независимая реализация POSIX. **SPC** не претендует на авторские права на эти оригинальные материалы.

#### 4. Отказ от гарантий и ограничение ответственности
ВКЛАДЫ **SPC** ПРЕДОСТАВЛЯЮТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, ЯВНЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ, НО НЕ ОГРАНИЧИВАЯСЬ, ГАРАНТИЯМИ ТОВАРНОЙ ПРИГОДНОСТИ, ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННОЙ ЦЕЛИ И НЕНАРУШЕНИЯ ПРАВ.

НИ ПРИ КАКИХ ОБСТОЯТЕЛЬСТВАХ **SPC** ИЛИ ВЛАДЕЛЬЦЫ АВТОРСКИХ ПРАВ НА УЛУЧШЕНИЯ НЕ НЕСУТ ОТВЕТСТВЕННОСТИ ЗА ЛЮБЫЕ ПРЕТЕНЗИИ, УБЫТКИ ИЛИ ИНУЮ ОТВЕТСТВЕННОСТЬ, БУДЬ ТО В РАМКАХ ДОГОВОРНОГО, ДЕЛИКТНОГО ИЛИ ИНОГО ДЕЙСТВИЯ, ВЫТЕКАЮЩЕГО ИЗ, ВНЕ ИЛИ В СВЯЗИ С ВКЛАДАМИ **SPC** ИЛИ ИСПОЛЬЗОВАНИЕМ ИЛИ ИНЫМИ ДЕЙСТВИЯМИ, СВЯЗАННЫМИ С ЭТИМИ ВКЛАДАМИ.

**Примечание об оригинальных файлах**: Пользователи несут ответственность за обеспечение соответствия использования файлов **SA-MP SDK** применимым лицензиям:
- Для `amx.h`, `amx.c`, `osdefs.h` и `sclinux.h` следуйте условиям **Apache License 2.0**.
- Для `getch.h` и `getch.c` следуйте условиям **Mozilla Public License 2.0 (MPL-2.0)**.
- Для `amxplugin.c`, `plugin.h` и `plugincommon.h`, поскольку у них нет указанной лицензии, пользователи должны обеспечить соблюдение любых условий, установленных **Kalcor и, возможно, членами команды SA-MP**, или применимых законов. **SPC** не предоставляет никаких гарантий и не несет ответственности за использование этих оригинальных материалов.

---

Для получения подробной информации о Лицензии MIT см.: [MIT License](https://opensource.org/licenses/MIT)