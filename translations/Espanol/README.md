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

El SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) es una colección integral de archivos C, headers y componentes que permiten a los desarrolladores crear plugins para el servidor SA-MP. Este SDK proporciona una base para extender la funcionalidad del servidor SA-MP a través de funciones nativas, permitiendo a los desarrolladores implementar características más allá de lo disponible en los scripts Pawn.

> [!WARNING]
> Este repositorio pone a disposición los archivos del **SA-MP SDK**, cuyo titular legítimo de los derechos es **Kalcor**, creador original de **SA-MP**. No se reclama ningún derecho de autor sobre el **SDK** — el propósito es simplemente facilitar el acceso y la organización del material para **desarrolladores de plugins**. La **licencia MIT** se ha aplicado únicamente como formalidad para mantener la estructura estándar de **GitHub**, ya que no se encontró la **licencia original del SDK**. Esta licencia no se aplica al contenido original del **SDK**, sino a posibles mejoras o archivos adicionales incluidos en el **repositorio**.

## Idiomas

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Índice

- [samp-sdk](#samp-sdk)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Componentes Principales](#componentes-principales)
    - [Sistema AMX](#sistema-amx)
      - [Headers AMX Principales](#headers-amx-principales)
    - [Soporte de Plataformas](#soporte-de-plataformas)
    - [Sistema de Plugins](#sistema-de-plugins)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [Funciones Nativas AMX](#funciones-nativas-amx)
  - [Detalles Técnicos](#detalles-técnicos)
    - [Gestión de Memoria](#gestión-de-memoria)
    - [Operaciones de Memoria](#operaciones-de-memoria)
    - [Manejo de Errores](#manejo-de-errores)
    - [Manejo de Strings](#manejo-de-strings)
    - [Operaciones de Strings](#operaciones-de-strings)
  - [Soporte Unicode](#soporte-unicode)
    - [Operaciones Unicode](#operaciones-unicode)
  - [Compatibilidad Multiplataforma](#compatibilidad-multiplataforma)
  - [Requisitos del Sistema](#requisitos-del-sistema)
    - [Soporte de Compiladores](#soporte-de-compiladores)
  - [Mejores Prácticas](#mejores-prácticas)
  - [Estructuras Internas](#estructuras-internas)
    - [Estructura del Header AMX](#estructura-del-header-amx)
  - [Características Avanzadas](#características-avanzadas)
    - [Soporte de Compilación JIT](#soporte-de-compilación-jit)
    - [Interfaz de Depuración](#interfaz-de-depuración)
    - [Interfaz de Funciones Públicas](#interfaz-de-funciones-públicas)
  - [Información de Versión](#información-de-versión)
    - [Compatibilidad de Versiones](#compatibilidad-de-versiones)
  - [Licencia](#licencia)
    - [Términos y Condiciones de Uso](#términos-y-condiciones-de-uso)
      - [1. Permisos Otorgados](#1-permisos-otorgados)
      - [2. Condiciones Obligatorias](#2-condiciones-obligatorias)
      - [3. Derechos de Autor](#3-derechos-de-autor)
      - [4. Exención de Garantías y Limitación de Responsabilidad](#4-exención-de-garantías-y-limitación-de-responsabilidad)

## Componentes Principales

### Sistema AMX

El AMX (Abstract Machine eXecutor) es la máquina virtual que ejecuta scripts Pawn en SA-MP. El SDK proporciona soporte extenso para interactuar con el sistema AMX a través de varios archivos C y headers.

#### Headers AMX Principales

1. **amx.h**

    El header principal que consolida toda la funcionalidad relacionada con AMX:
    - Funciones principales para la ejecución de scripts
    - Gestión de memoria
    - Registro de funciones nativas
    - Manejo de strings
    - Soporte UTF-8

    Funciones clave incluyen:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);         // Inicializa una instancia AMX
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index); // Ejecuta una función pública
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number); // Registra funciones nativas
    ```

2. **amx_platform.h**

    Responsable de la detección y configuración de plataformas:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```
    - Detecta sistemas como Linux, FreeBSD, OpenBSD y macOS.
    - Incluye `sclinux.h` para sistemas tipo Unix.
    - Identifica arquitecturas de 64 bits:
      ```c
      #if defined _LP64 || defined WIN64 || defined _WIN64
          #define __64BIT__
      #endif
      ```
    - Calcula la versión de GCC si aplica:
      ```c
      #if defined __GNUC__
          #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #endif
      ```

3. **amx_constants.h**

    Define constantes esenciales para la operación de AMX:
    - **Versiones**:
      ```c
      #define CUR_FILE_VERSION  9   // Versión actual del formato de archivo
      #define MIN_FILE_VERSION  6   // Versión mínima soportada
      #define MIN_AMX_VERSION   10  // Versión mínima de AMX
      #define MAX_FILE_VER_JIT  8   // Versión máxima con soporte JIT
      #define MIN_AMX_VER_JIT   8   // Versión mínima con soporte JIT
      ```
    - **Códigos Mágicos**:
      ```c
      #define AMX_MAGIC_16    0xf1e2  // Para celdas de 16 bits
      #define AMX_MAGIC_32    0xf1e0  // Para celdas de 32 bits
      #define AMX_MAGIC_64    0xf1e1  // Para celdas de 64 bits
      ```
    - **Códigos de Error**:
      ```c
      enum {
          AMX_ERR_NONE,         // Sin error
          AMX_ERR_EXIT,         // Script terminado
          AMX_ERR_ASSERT,       // Afirmación fallida
          AMX_ERR_STACKERR,     // Error de pila
          AMX_ERR_BOUNDS,       // Acceso fuera de límites
          AMX_ERR_MEMACCESS,    // Acceso a memoria inválido
          AMX_ERR_INVINSTR,     // Instrucción inválida
          AMX_ERR_STACKLOW,     // Pila demasiado baja
          AMX_ERR_HEAPLOW,      // Heap demasiado bajo
          AMX_ERR_CALLBACK,     // Error de callback
          AMX_ERR_NATIVE,       // Error en función nativa
          AMX_ERR_DIVIDE,       // División por cero
          AMX_ERR_SLEEP,        // Modo sleep activado
          AMX_ERR_INVSTATE,     // Estado inválido
          AMX_ERR_MEMORY = 16,  // Memoria insuficiente
          AMX_ERR_FORMAT,       // Formato inválido
          AMX_ERR_VERSION,      // Versión incompatible
          AMX_ERR_NOTFOUND,     // Recurso no encontrado
          AMX_ERR_INDEX,        // Índice inválido
          AMX_ERR_DEBUG,        // Error de depuración
          AMX_ERR_INIT,         // Fallo de inicialización
          AMX_ERR_USERDATA,     // Error en datos de usuario
          AMX_ERR_INIT_JIT,     // Fallo de inicialización JIT
          AMX_ERR_PARAMS,       // Parámetros inválidos
          AMX_ERR_DOMAIN,       // Error de dominio
          AMX_ERR_GENERAL,      // Error general
      };
      ```
    - **Banderas**:
      ```c
      #define AMX_FLAG_DEBUG      0x02   // Modo de depuración
      #define AMX_FLAG_COMPACT    0x04   // Codificación compacta
      #define AMX_FLAG_SLEEP      0x08   // Soporte de sleep
      #define AMX_FLAG_NOCHECKS   0x10   // Sin verificaciones de seguridad
      #define AMX_FLAG_NO_RELOC   0x200  // Sin relocación
      #define AMX_FLAG_NO_SYSREQD 0x400  // Sin sysreq.d
      #define AMX_FLAG_SYSREQN    0x800  // Soporte sysreq.n
      #define AMX_FLAG_NTVREG     0x1000 // Registro de nativas
      #define AMX_FLAG_JITC       0x2000 // Compilación JIT
      #define AMX_FLAG_BROWSE     0x4000 // Modo exploración
      #define AMX_FLAG_RELOC      0x8000 // Relocación habilitada
      ```
    - **Códigos de Ejecución**:
      ```c
      #define AMX_EXEC_MAIN   (-1)  // Ejecutar función principal
      #define AMX_EXEC_CONT   (-2)  // Continuar ejecución
      ```

4. **amx_memory.h**

    Gestiona la asignación de memoria:
    - Soporte para `alloca`:
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
    - Define el margen de compresión:
      ```c
      #if !defined AMX_COMPACTMARGIN
          #define AMX_COMPACTMARGIN 64
      #endif
      ```

5. **amx_calling.h**

    Define convenciones de llamada:
    - Para funciones nativas y APIs:
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

    Define tipos enteros estandarizados:
    - Soporte para `stdint.h` o definiciones manuales:
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
              typedef __int64          Sunday, October 20, 2024 int64_t;
              typedef unsigned __int64  uint64_t;
          #endif
      #endif
      ```

7. **amx_macros.h**

    Proporciona macros útiles:
    - **Cálculo de Dirección**:
      ```c
      #define amx_Address(amx,addr) \
          (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))
      ```
    - **Manejo de Strings**:
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
    - **Conteo de Parámetros**:
      ```c
      #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))
      ```
    - **Registro de Funciones**:
      ```c
      #define amx_RegisterFunc(amx, name, func) \
          amx_Register((amx), amx_NativeInfo((name),(func)), 1)
      ```

8. **amx_cell.h**

    Define tipos de celdas:
    - Configura `PAWN_CELL_SIZE` (por defecto: 32):
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
    - Soporte para punto flotante:
      ```c
      #if PAWN_CELL_SIZE==32
          #define amx_ftoc(f)   (*(cell*)&(f))  // Float a celda
          #define amx_ctof(c)   (*(float*)&(c))  // Celda a float
      #elif PAWN_CELL_SIZE==64
          #define amx_ftoc(f)   (*(cell*)&(f))  // Double a celda
          #define amx_ctof(c)   (*(double*)&(c)) // Celda a double
      #endif
      ```
    - Manipulación de caracteres:
      ```c
      #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))  // Para 32 bits
      ```

9. **amx_structures.h**

    Define estructuras principales:
    - **AMX**:
      ```c
      typedef struct tagAMX {
          unsigned char _FAR *base;    // Dirección base
          unsigned char _FAR *data;    // Segmento de datos
          AMX_CALLBACK callback;       // Función de callback
          AMX_DEBUG debug;            // Callback de depuración
          cell cip;                   // Puntero de instrucción de código
          cell frm;                   // Base del marco
          cell hea;                   // Base del heap
          cell hlw;                   // Límite inferior del heap
          cell stk;                   // Puntero de pila
          cell stp;                   // Tope de pila
          int flags;                  // Banderas
          long usertags[AMX_USERNUM]; // Etiquetas de usuario
          void _FAR *userdata[AMX_USERNUM]; // Datos de usuario
          int error;                  // Código de error
          int paramcount;             // Conteo de parámetros
          cell pri;                   // Registro primario
          cell alt;                   // Registro alternativo
          cell reset_stk;             // Pila reiniciada
          cell reset_hea;             // Heap reiniciado
          cell sysreq_d;              // Dirección sysreq.d
          #if defined JIT
              int reloc_size;         // Tamaño de relocación
              long code_size;         // Tamaño de código
          #endif
      } AMX;
      ```
    - **AMX_HEADER**:
      ```c
      typedef struct tagAMX_HEADER {
          int32_t size;          // Tamaño del archivo
          uint16_t magic;        // Firma
          char    file_version;  // Versión del archivo
          char    amx_version;   // Versión de AMX
          int16_t flags;         // Banderas
          int16_t defsize;       // Tamaño de definición
          int32_t cod;           // Inicio del código
          int32_t dat;           // Inicio de datos
          int32_t hea;           // Inicio del heap
          int32_t stp;           // Tope de pila
          int32_t cip;           // Puntero de instrucción inicial
          int32_t publics;       // Offset a funciones públicas
          int32_t natives;       // Offset a funciones nativas
          int32_t libraries;     // Offset a bibliotecas
          int32_t pubvars;       // Offset a variables públicas
          int32_t tags;          // Offset a etiquetas
          int32_t nametable;     // Offset a tabla de nombres
      } AMX_HEADER;
      ```

### Soporte de Plataformas

El SDK incluye un manejo robusto específico de plataformas a través de varios headers:

1. **amx_platform.h**

    Proporciona detección y configuración de plataformas:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Maneja definiciones específicas del sistema operativo:
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

### Sistema de Plugins

#### plugincommon.h

Define la interfaz principal del plugin y estructuras de soporte:
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

El archivo `amxplugin.c` es un componente clave del SA-MP SDK, proporcionando implementaciones específicas de plataforma para funciones AMX. Implementa dos enfoques basados en la plataforma y el compilador:

1. **Implementación Windows MSVC (32-bit)**
    - Usa funciones "naked" con ensamblador para acceso directo a la tabla de funciones:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Implementación Multiplataforma**
    - Usa punteros de funciones para independencia de plataforma:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

**Características Clave**:

3. **Gestión de Tabla de Funciones**
    - Usa un puntero estático `pAMXFunctions` para almacenar la tabla de funciones AMX.
    - Proporciona acceso a todas las funciones principales de AMX.
    - Maneja la resolución de funciones en tiempo de ejecución.

4. **Optimizaciones Específicas de Plataforma**
    - Windows 32-bit: Implementación directa en ensamblador con funciones naked.
    - Otras plataformas: Indirección de punteros de funciones.
    - Manejo especial para sistemas de 64 bits.

5. **Categorías de Funciones Implementadas**

    a. **Funciones de Gestión de Memoria**:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. **Funciones de Ejecución**:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. **Gestión de Símbolos**:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. **Manejo de Strings**:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Funciones de soporte UTF-8
    
    e. **Depuración e Información**:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Compilación Condicional**
    - Maneja diferentes plataformas mediante directivas de preprocesador.
    - Manejo especial para sistemas de 64 bits.
    - Soporte opcional para JIT:
      ```c
      #if defined _I64_MAX || defined HAVE_I64
          DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
              PLUGIN_AMX_EXPORT_Align64)
      #endif
      ```

7. **Integración de Manejo de Errores**
    - Implementa `amx_RaiseError` para reportes de errores.
    - Preserva códigos de error a través de llamadas a funciones.
    - Se integra con el sistema de depuración de AMX.

### Funciones Nativas AMX

El SDK proporciona soporte completo para crear y gestionar funciones nativas:
```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

**Operaciones Clave con Funciones Nativas**:
- Registro mediante `amx_Register`.
- Acceso y validación de parámetros mediante `amx_NumParams`.
- Manejo de valores de retorno.
- Reporte de errores con `amx_RaiseError`.

## Detalles Técnicos

### Gestión de Memoria

El SDK ofrece instalaciones completas de gestión de memoria:

1. **amx_memory.h**

    Maneja la asignación de memoria y operaciones específicas de plataforma:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```
    - Define `AMX_COMPACTMARGIN` como 64 por defecto para compresión de memoria.

2. **amx_alignment.h**

    Gestiona requisitos de alineación de memoria:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Operaciones de Memoria

El SDK incluye varias funciones para manipulación de memoria:

1. **Asignación de Memoria**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Asigna memoria en el heap de AMX.
    - Devuelve direcciones AMX y físicas.
    - Maneja requisitos de alineación.

2. **Acceso a Memoria**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Convierte direcciones AMX a direcciones físicas.
    - Valida el acceso a memoria.
    - Maneja límites de memoria.

3. **Información de Memoria**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Recupera información del diseño de memoria.
    - Reporta tamaños de segmentos.
    - Útil para depuración y optimización.

### Manejo de Errores

El SDK incluye un sistema completo de manejo de errores definido en `amx_constants.h`:
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

### Manejo de Strings

El SDK proporciona capacidades robustas de manejo de strings a través de varios macros y funciones:
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
- Alternativa para `char*`:
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

### Operaciones de Strings

1. **Longitud de String**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Calcula la longitud del string.
    - Maneja strings empaquetados y no empaquetados.
    - Devuelve la longitud en caracteres.

2. **Conversión de Strings**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Convierte strings C a strings AMX.
    - Soporta formatos empaquetados y no empaquetados.
    - Maneja conversión Unicode.

## Soporte Unicode

El SDK proporciona soporte completo para Unicode a través de funciones de manejo UTF-8:
```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Operaciones Unicode

1. **Validación UTF-8**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - Valida strings codificados en UTF-8.
    - Reporta la longitud del string en caracteres.
    - Detecta errores de codificación.

2. **Conversión de Caracteres**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extrae caracteres Unicode.
    - Maneja secuencias multi-byte.
    - Reporta errores de análisis.

## Compatibilidad Multiplataforma

El SDK asegura compatibilidad multiplataforma mediante:

1. **Manejo de Endianness**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Manejo de Rutas**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

3. **Tipos Independientes de Plataforma**
    - Definidos en `amx_types.h` para consistencia.

## Requisitos del Sistema

El SDK soporta múltiples plataformas y compiladores:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Soporte de Compiladores

1. **Microsoft Visual C++**
    - Manejo de pragmas.
    - Supresión de advertencias.
    - Convenciones de llamada mediante `amx_calling.h`.

2. **GCC**
    - Controles de diagnóstico.
    - Especificaciones de atributos.
    - Optimizaciones específicas de plataforma.

3. **Clang**
    - Configuraciones de advertencias.
    - Compatibilidad multiplataforma.
    - Características modernas de C++.

## Mejores Prácticas

Al usar el SA-MP SDK, considere las siguientes mejores prácticas:

1. **Gestión de Memoria**
    - Siempre limpie los recursos asignados.
    - Use alineación de memoria adecuada.
    - Maneje errores de memoria con elegancia.
    - Monitoree el uso del heap.
    - Implemente verificación adecuada de límites de memoria.
    - Use pools de memoria para asignaciones frecuentes.
    - Limpie recursos en orden inverso de asignación.

2. **Manejo de Errores**
    - Verifique los valores de retorno de las funciones AMX.
    - Implemente manejo adecuado de errores en funciones nativas.
    - Use las constantes de error proporcionadas.
    - Registre errores de manera apropiada.
    - Implemente mecanismos de recuperación de errores.
    - Proporcione mensajes de error significativos.
    - Maneje errores específicos del sistema.

3. **Desarrollo Multiplataforma**
    - Use tipos independientes de plataforma.
    - Utilice macros proporcionados para código específico de plataforma.
    - Pruebe en múltiples plataformas.
    - Maneje diferencias de endianness.
    - Use separadores de ruta apropiados.
    - Considere diferencias del sistema de archivos.
    - Implemente optimizaciones específicas de plataforma.

4. **Consideraciones de Rendimiento**
    - Use tamaños de celda adecuados.
    - Implemente manejo eficiente de strings.
    - Optimice las llamadas a funciones nativas.
    - Minimice las asignaciones de memoria.
    - Use estructuras de datos apropiadas.
    - Implemente caché donde sea adecuado.
    - Perfile rutas críticas de código.

Cuando trabaje con la funcionalidad de `amxplugin.c`:

1. **Desarrollo Específico de Plataforma**
    - Considere diferencias de plataforma en implementaciones de funciones.
    - Pruebe en sistemas de 32 y 64 bits.
    - Maneje requisitos de alineación específicos de plataforma.
    - Valide el puntero de la tabla de funciones antes de usarlo.
    - Implemente verificación de errores adecuada para cada plataforma.
    - Considere las implicaciones de rendimiento de diferentes implementaciones.

2. **Gestión de Tabla de Funciones**
    - Inicialice la tabla de funciones antes de usarla.
    - Verifique la disponibilidad de funciones.
    - Maneje funciones faltantes con elegancia.
    - Implemente procedimientos de limpieza adecuados.
    - Almacene en caché punteros de funciones usados frecuentemente.
    - Valide la integridad de la tabla de funciones.

3. **Manejo de Errores**
    - Implemente verificación adecuada de errores para código específico de plataforma.
    - Maneje errores de alineación de manera apropiada.
    - Valide las entradas de la tabla de funciones.
    - Proporcione mensajes de error significativos.
    - Implemente mecanismos de recuperación.
    - Registre errores específicos de plataforma.

## Estructuras Internas

### Estructura del Header AMX

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Tamaño del "archivo"
    uint16_t magic;        // Firma
    char    file_version;  // Versión del formato de archivo
    char    amx_version;   // Versión AMX requerida
    int16_t flags;         // Banderas
    int16_t defsize;       // Tamaño de un registro de definición
    int32_t cod;           // Valor inicial de COD - bloque de código
    int32_t dat;           // Valor inicial de DAT - bloque de datos
    int32_t hea;           // Valor inicial de HEA - inicio del heap
    int32_t stp;           // Valor inicial de STP - tope de pila
    int32_t cip;           // Valor inicial de CIP - puntero de instrucción de código
    int32_t publics;       // Offset a funciones públicas
    int32_t natives;       // Offset a tabla de funciones nativas
    int32_t libraries;     // Offset a bibliotecas
    int32_t pubvars;       // Offset a variables públicas
    int32_t tags;          // Offset a etiquetas
    int32_t nametable;     // Offset a tabla de nombres
} AMX_HEADER;
```

Esta estructura es crucial para entender el formato de archivo AMX y cómo la máquina virtual carga y ejecuta scripts.

## Características Avanzadas

### Soporte de Compilación JIT

El SDK incluye soporte para compilación Just-In-Time:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Interfaz de Depuración

El soporte de depuración se proporciona mediante:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Interfaz de Funciones Públicas

El SDK proporciona soporte completo para trabajar con funciones públicas:

1. **Búsqueda de Funciones Públicas**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Localiza funciones públicas por nombre.
    - Devuelve el índice de la función.
    - Valida la existencia de la función.

2. **Ejecución de Funciones Públicas**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Ejecuta funciones públicas.
    - Maneja valores de retorno.
    - Gestiona el contexto de ejecución.

## Información de Versión

El SDK incluye constantes de versión para verificación de compatibilidad:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Compatibilidad de Versiones

El SDK mantiene compatibilidad mediante:
1. Verificación de la versión del archivo.
2. Validación de la versión AMX.
3. Verificación de compatibilidad JIT.
4. Detección de características.
5. Manejo de versiones específico de plataforma.

## Licencia

Copyright © **SA-MP Programming Community**

Este software está licenciado bajo los términos de la Licencia MIT ("Licencia"); puede utilizar este software de acuerdo con los términos de la Licencia. Una copia de la Licencia puede obtenerse en: [MIT License](https://opensource.org/licenses/MIT)

### Términos y Condiciones de Uso

#### 1. Permisos Otorgados

Esta licencia otorga, de forma gratuita, a cualquier persona que obtenga una copia de este software y los archivos de documentación asociados, los siguientes derechos:
- Usar, copiar, modificar, fusionar, publicar, distribuir, sublicenciar y/o vender copias del software sin restricciones.
- Permitir a las personas a quienes se les proporcione el software hacer lo mismo, sujeto a las siguientes condiciones.

#### 2. Condiciones Obligatorias

Todas las copias o partes sustanciales del software deben incluir:
- El aviso de derechos de autor anterior.
- Este aviso de permiso.
- El aviso de exención de responsabilidad a continuación.

#### 3. Derechos de Autor

El software y toda la documentación asociada están protegidos por las leyes de derechos de autor. La **SA-MP Programming Community** conserva los derechos de autor originales del software.

#### 4. Exención de Garantías y Limitación de Responsabilidad

EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O IMPLÍCITA, INCLUYENDO, PERO NO LIMITADO A, LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN.

EN NINGÚN CASO LOS AUTORES O TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGÚN RECLAMO, DAÑOS U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE OTRO MODO, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTROS TRATOS CON EL SOFTWARE.

---

Para información detallada sobre la Licencia MIT, visite: https://opensource.org/licenses/MIT