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

El SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) es una colección integral de archivos C y headers que permiten a los desarrolladores crear plugins para el servidor SA-MP. Este SDK proporciona una base para extender la funcionalidad del servidor SA-MP a través de funciones nativas, permitiendo a los desarrolladores implementar características más allá de lo disponible en el script Pawn.

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
    - [Lo que puedes hacer ✅](#lo-que-puedes-hacer-)
    - [Lo que debes hacer ⚠️](#lo-que-debes-hacer-️)
    - [Lo que no puedes hacer ❌](#lo-que-no-puedes-hacer-)

## Componentes Principales

### Sistema AMX

El AMX (Abstract Machine eXecutor) es la máquina virtual que ejecuta scripts Pawn en SA-MP. El SDK proporciona soporte extenso para interactuar con AMX a través de varios archivos C y headers:

#### Headers AMX Principales

1. **amx.h**

    El archivo header principal que consolida toda la funcionalidad relacionada con AMX. Incluye:
    - Funciones principales de AMX para ejecución de scripts
    - Gestión de memoria
    - Registro de funciones nativas
    - Manejo de strings
    - Soporte UTF-8

    Funciones principales incluyen:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    ```

2. **amx_cell.h**

    Define los tipos de datos fundamentales utilizados en el sistema AMX:
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

    Contiene estructuras esenciales para la operación de AMX:

    ```c
    typedef struct tagAMX {
        unsigned char _FAR *base;    // Dirección base
        unsigned char _FAR *data;    // Segmento de datos
        AMX_CALLBACK callback;       // Función de callback
        AMX_DEBUG debug;            // Callback de depuración
        cell cip;                   // Puntero de instrucción de código
        cell frm;                   // Base del marco de pila
        cell hea;                   // Base del heap
        cell stk;                   // Puntero de pila
        // ... campos adicionales
    } AMX;
    ```

### Soporte de Plataformas

El SDK incluye manejo robusto específico de plataforma a través de varios headers:

1. **amx_platform.h**

    Proporciona detección y configuración de plataforma:
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

Define la interfaz principal del plugin y las estructuras de soporte:

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

El archivo `amxplugin.c` es un componente crucial del SA-MP SDK que proporciona implementaciones específicas de plataforma para funciones AMX. Implementa dos enfoques diferentes según la plataforma y el compilador:

1. **Implementación Windows MSVC (32-bit)**
    - Usa funciones naked con ensamblador para acceso directo a la tabla de funciones
    - Proporciona rendimiento optimizado a través de saltos directos a funciones AMX
    - Estructura de ejemplo:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Implementación Multiplataforma**
    - Usa punteros a funciones para independencia de plataforma
    - Implementa un sistema basado en macros para definiciones de funciones
    - Estructura de ejemplo:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

Características Principales:

3. **Gestión de Tabla de Funciones**
    - Usa un puntero estático `pAMXFunctions` para almacenar la tabla de funciones AMX
    - Proporciona acceso a todas las funciones principales de AMX
    - Maneja la resolución de funciones en tiempo de ejecución

4. **Optimizaciones Específicas de Plataforma**
    - Windows 32-bit: Usa funciones naked para implementación directa en ensamblador
    - Otras plataformas: Usa indirección de punteros a funciones
    - Manejo especial para sistemas de 64 bits

5. **Categorías de Funciones Implementadas**

    a. Funciones de Gestión de Memoria:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. Funciones de Ejecución:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. Gestión de Símbolos:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. Manejo de Strings:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Funciones de soporte UTF-8
    
    e. Depuración e Información:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Compilación Condicional**
    - Maneja diferentes plataformas a través de directivas de preprocesador
    - Manejo especial para sistemas de 64 bits
    - Soporte JIT opcional
    ```c
    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
            PLUGIN_AMX_EXPORT_Align64)
    #endif
    ```

7. **Integración de Manejo de Errores**
    - Implementa `amx_RaiseError` para reportar errores
    - Preserva códigos de error a través de llamadas a funciones
    - Se integra con el sistema de depuración AMX

### Funciones Nativas AMX

El SDK proporciona soporte integral para crear y gestionar funciones nativas:

```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

Operaciones principales de funciones nativas:
- Registro a través de `amx_Register`
- Acceso y validación de parámetros
- Manejo de valores de retorno
- Reporte de errores

## Detalles Técnicos

### Gestión de Memoria

El SDK proporciona instalaciones completas de gestión de memoria:

1. **amx_memory.h**

   Maneja la asignación de memoria y operaciones de memoria específicas de plataforma:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```

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
    - Asigna memoria en el heap AMX
    - Devuelve direcciones AMX y físicas
    - Maneja requisitos de alineación

2. **Acceso a Memoria**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Convierte direcciones AMX a direcciones físicas
    - Valida acceso a memoria
    - Maneja límites de memoria

3. **Información de Memoria**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Recupera información del diseño de memoria
    - Reporta tamaños de segmentos
    - Útil para depuración y optimización

### Manejo de Errores

El SDK incluye un sistema integral de manejo de errores definido en `amx_constants.h`:

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
            ((result)=(type)alloca((result##_length_+1)*sizeof(*(result))))!=NULL) \
        amx_GetString((char*)(result),amx_Address(amx,param), \
                            sizeof(*(result))>1,result##_length_+1); \
        else (result)=NULL; \
    } while(0)
```

### Operaciones de Strings

1. **Longitud de String**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Calcula la longitud del string
    - Maneja strings empaquetados y no empaquetados
    - Devuelve la longitud en caracteres

2. **Conversión de Strings**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Convierte strings C a strings AMX
    - Soporta formatos empaquetados y no empaquetados
    - Maneja conversión Unicode

## Soporte Unicode

El SDK incluye soporte integral para Unicode a través de funciones de manejo UTF-8:

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
    - Valida strings codificados en UTF-8
    - Reporta longitud del string en caracteres
    - Detecta errores de codificación

2. **Conversión de Caracteres**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extrae caracteres Unicode
    - Maneja secuencias multi-byte
    - Reporta errores de análisis

## Compatibilidad Multiplataforma

El SDK asegura compatibilidad multiplataforma a través de:

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

## Requisitos del Sistema

El SDK soporta múltiples plataformas y compiladores:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Soporte de Compiladores

1. **Microsoft Visual C++**
   - Manejo de pragmas
   - Supresión de advertencias
   - Convenciones de llamada

2. **GCC**
   - Controles de diagnóstico
   - Especificaciones de atributos
   - Optimizaciones específicas de plataforma

3. **Clang**
   - Configuraciones de advertencias
   - Compatibilidad multiplataforma
   - Características modernas de C++

## Mejores Prácticas

Al usar el SA-MP SDK, considere las siguientes mejores prácticas:

1. **Gestión de Memoria**
   - Siempre limpie los recursos asignados
   - Use alineación de memoria apropiada
   - Maneje errores de memoria con elegancia
   - Monitoree el uso del heap
   - Implemente verificación apropiada de límites de memoria
   - Use pools de memoria para asignaciones frecuentes
   - Limpie recursos en orden inverso a la asignación

2. **Manejo de Errores**
   - Verifique valores de retorno de funciones AMX
   - Implemente manejo apropiado de errores en funciones nativas
   - Use las constantes de error proporcionadas
   - Registre errores apropiadamente
   - Implemente mecanismos de recuperación de errores
   - Proporcione mensajes de error significativos
   - Maneje errores específicos del sistema

3. **Desarrollo Multiplataforma**
   - Use tipos independientes de plataforma
   - Utilice macros proporcionados para código específico de plataforma
   - Pruebe en múltiples plataformas
   - Maneje diferencias de endianness
   - Use separadores de ruta apropiados
   - Considere diferencias del sistema de archivos
   - Implemente optimizaciones específicas de plataforma

4. **Consideraciones de Rendimiento**
   - Use tamaños de cell apropiados
   - Implemente manejo eficiente de strings
   - Optimice llamadas a funciones nativas
   - Minimice asignaciones de memoria
   - Use estructuras de datos apropiadas
   - Implemente caché donde sea apropiado
   - Perfile rutas críticas de código

Cuando trabaje con la funcionalidad de `amxplugin.c`:

1. **Desarrollo Específico de Plataforma**
   - Considere diferencias de plataforma en implementaciones de funciones
   - Pruebe en sistemas de 32 bits y 64 bits
   - Maneje requisitos de alineación específicos de plataforma
   - Valide el puntero de tabla de funciones antes de usar
   - Implemente verificación de errores apropiada para cada plataforma
   - Considere implicaciones de rendimiento de diferentes implementaciones

2. **Gestión de Tabla de Funciones**
   - Inicialice la tabla de funciones antes de usar
   - Verifique disponibilidad de funciones
   - Maneje funciones faltantes con elegancia
   - Implemente procedimientos apropiados de limpieza
   - Cache punteros de funciones frecuentemente usados
   - Valide integridad de la tabla de funciones

3. **Manejo de Errores**
   - Implemente verificación apropiada de errores para código específico de plataforma
   - Maneje errores de alineación apropiadamente
   - Valide entradas de tabla de funciones
   - Proporcione mensajes de error significativos
   - Implemente mecanismos de recuperación
   - Registre errores específicos de plataforma

## Estructuras Internas

### Estructura del Header AMX

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Tamaño del "archivo"
    uint16_t magic;        // Firma
    char    file_version;  // Versión del formato de archivo
    char    amx_version;   // Versión AMX requerida
    int16_t flags;         // Banderas
    int16_t defsize;      // Tamaño de un registro de definición
    int32_t cod;          // Valor inicial de COD - bloque de código
    int32_t dat;          // Valor inicial de DAT - bloque de datos
    int32_t hea;          // Valor inicial de HEA - inicio del heap
    int32_t stp;          // Valor inicial de STP - tope de pila
    int32_t cip;          // Valor inicial de CIP - puntero de instrucción de código
    int32_t publics;      // Desplazamiento a funciones públicas
    int32_t natives;      // Desplazamiento a tabla de funciones nativas
    int32_t libraries;    // Desplazamiento a bibliotecas
    int32_t pubvars;      // Desplazamiento a variables públicas
    int32_t tags;         // Desplazamiento a tags
    int32_t nametable;    // Desplazamiento a tabla de nombres
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

El soporte de depuración se proporciona a través de:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Interfaz de Funciones Públicas

El SDK proporciona soporte integral para trabajar con funciones públicas:

1. **Búsqueda de Funciones Públicas**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Localiza funciones públicas por nombre
    - Devuelve índice de función
    - Valida existencia de función

2. **Ejecución de Funciones Públicas**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Ejecuta funciones públicas
    - Maneja valores de retorno
    - Gestiona contexto de ejecución

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

El SDK mantiene compatibilidad a través de:
1. Verificación de versión de archivo
2. Validación de versión AMX
3. Verificación de compatibilidad JIT
4. Detección de características
5. Manejo de versión específico de plataforma

## Licencia

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

Puede obtener una copia de la licencia en:
https://opensource.org/licenses/MIT

### Lo que puedes hacer ✅

1. **Uso Comercial**: 
   - Libertad total para uso comercial
   - Puede vender productos basados en el código
   - Sin necesidad de pago de regalías
   - Puede usar en productos propietarios

2. **Modificación**: 
   - Modificación completa del código fuente
   - Crear trabajos derivados
   - Adaptar para cualquier propósito
   - Integrar con otros sistemas

3. **Distribución**: 
   - Distribuir el software original
   - Compartir versiones modificadas
   - Incluir en otros proyectos
   - Distribuir comercialmente

4. **Uso Privado**: 
   - Uso en proyectos privados
   - Modificaciones confidenciales
   - Sin obligación de divulgación
   - Uso interno sin restricciones

5. **Sublicenciamiento**: 
   - Puede cambiar la licencia del código derivado
   - Elegir diferentes términos para sus modificaciones
   - Combinar con otras licencias
   - Crear términos propios para distribución

### Lo que debes hacer ⚠️

1. **Incluir Licencia**: 
   - Mantener copia de la licencia con el código
   - Incluir en todas las distribuciones
   - Preservar texto original
   - Mantener visible y accesible

2. **Atribución**: 
   - Mantener aviso de derechos de autor
   - Incluir en todas las copias
   - Preservar créditos originales
   - Documentar origen del código

### Lo que no puedes hacer ❌

1. **Responsabilizar a los Autores**: 
   - Sin garantías de funcionamiento
   - Autores no son responsables por daños
   - Sin soporte obligatorio
   - Uso por cuenta y riesgo