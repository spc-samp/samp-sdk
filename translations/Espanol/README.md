# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Un SDK C++ moderno, header-only y de alto nivel para el desarrollo de plugins y módulos para SA-MP.**

</div>

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

- [SA-MP SDK](#sa-mp-sdk)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [1. Introducción y Filosofía de Diseño](#1-introducción-y-filosofía-de-diseño)
    - [El Problema con la API C Estándar de SA-MP](#el-problema-con-la-api-c-estándar-de-sa-mp)
    - [La Solución del SA-MP SDK: Abstracción con Seguridad y Performance](#la-solución-del-sa-mp-sdk-abstracción-con-seguridad-y-performance)
    - [Modelo Header-Only: Ventajas e Implicaciones](#modelo-header-only-ventajas-e-implicaciones)
  - [2. Configuración y Ambiente](#2-configuración-y-ambiente)
    - [Requisitos de Compilación](#requisitos-de-compilación)
    - [Estructura de Archivos Recomendada](#estructura-de-archivos-recomendada)
    - [Macros Esenciales de Configuración](#macros-esenciales-de-configuración)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definiciones y Constantes de SA-MP (`samp_defs.hpp`)](#definiciones-y-constantes-de-sa-mp-samp_defshpp)
  - [3. Guía de Uso Abrangente de la API](#3-guía-de-uso-abrangente-de-la-api)
    - [3.1. El Ciclo de Vida del Plugin](#31-el-ciclo-de-vida-del-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Interceptando Eventos de Pawn](#32-plugin_public-interceptando-eventos-de-pawn)
      - [Sintaxis y Declaración](#sintaxis-y-declaración)
      - [Marshalling Automático de Parámetros](#marshalling-automático-de-parámetros)
      - [Control de Flujo: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#control-de-flujo-plugin_public_continue-vs-plugin_public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.3. `Plugin_Native`: Creando Funciones Nativas en C++](#33-plugin_native-creando-funciones-nativas-en-c)
      - [Sintaxis y Firma Fija](#sintaxis-y-firma-fija)
      - [Registro Automático de Nativas](#registro-automático-de-nativas)
      - [Extracción de Parámetros: `Register_Parameters` vs. `Native_Params`](#extracción-de-parámetros-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)](#native_params-api-completa-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Retorno de Valores](#retorno-de-valores)
    - [3.4. `Plugin_Native_Hook`: Interceptando Nativas Existentes de SA-MP](#34-plugin_native_hook-interceptando-nativas-existentes-de-sa-mp)
      - [Sintaxis y Firma Fija](#sintaxis-y-firma-fija-1)
      - [Registro y Activación del Hook](#registro-y-activación-del-hook)
      - [Llamando a la Native Original (Cadena de Hooks): `Call_Original_Native`](#llamando-a-la-native-original-cadena-de-hooks-call_original_native)
      - [Ejemplo Completo de `Plugin_Native_Hook`](#ejemplo-completo-de-plugin_native_hook)
    - [3.5. `Pawn_*` Macros: Llamando Funciones de Pawn desde C++](#35-pawn_-macros-llamando-funciones-de-pawn-desde-c)
      - [`Pawn_Native(NombreDeLaNative, ...)`](#pawn_nativenombredelanative-)
      - [`Pawn_Public(NombreDeLaPublic, ...)`](#pawn_publicnombredelapublic-)
      - [`Pawn(NombreDeLaFuncion, ...)`](#pawnnombredelafuncion-)
      - [Sintaxis y Convenciones](#sintaxis-y-convenciones)
      - [Marshalling de Parámetros de Entrada](#marshalling-de-parámetros-de-entrada)
      - [Marshalling de Parámetros de Salida (Referencias: `int&`, `float&`, `std::string&`)](#marshalling-de-parámetros-de-salida-referencias-int-float-stdstring)
      - [El Objeto `Callback_Result`: Análisis Completo](#el-objeto-callback_result-análisis-completo)
    - [3.6. `Plugin_Module`: Administración de Módulos Dinámicos](#36-plugin_module-administración-de-módulos-dinámicos)
      - [Sintaxis y Propósito](#sintaxis-y-propósito)
      - [Ciclo de Vida de un Módulo](#ciclo-de-vida-de-un-módulo)
      - [Beneficios de la Modularización](#beneficios-de-la-modularización)
    - [3.7. `Plugin_Call`: Llamando Nativas Internas del Plugin](#37-plugin_call-llamando-nativas-internas-del-plugin)
      - [Sintaxis y Ventajas de Performance](#sintaxis-y-ventajas-de-performance)
    - [3.8. Funciones Utilitarias del SDK](#38-funciones-utilitarias-del-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Recomendado)](#stdstring-plugin_formatconst-char-format--recomendado)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Detalle de Implementación)](#stdstring-samp_sdkformatconst-char-format--detalle-de-implementación)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Anatomía Interna y Arquitectura del SDK](#4-anatomía-interna-y-arquitectura-del-sdk)
    - [4.1. `core.hpp`: La Fundación Minimalista](#41-corehpp-la-fundación-minimalista)
    - [4.2. `platform.hpp` y `version.hpp`: Compatibilidad y Metadatos](#42-platformhpp-y-versionhpp-compatibilidad-y-metadatos)
    - [4.3. `function_hook.hpp`: El Motor de Interceptación x86](#43-function_hookhpp-el-motor-de-interceptación-x86)
    - [4.4. `interceptor_manager.hpp`: El Controlador de Hooks del AMX](#44-interceptor_managerhpp-el-controlador-de-hooks-del-amx)
    - [4.5. `amx_manager.hpp`: Administrando Instancias `AMX*`](#45-amx_managerhpp-administrando-instancias-amx)
    - [4.6. `public_dispatcher.hpp`: El Enrutador de Callbacks `Plugin_Public`](#46-public_dispatcherhpp-el-enrutador-de-callbacks-plugin_public)
    - [4.7. `native.hpp`: Administrando y Llamando Nativas del Plugin](#47-nativehpp-administrando-y-llamando-nativas-del-plugin)
    - [4.8. `native_hook_manager.hpp`: El Motor de Hooks de Natives](#48-native_hook_managerhpp-el-motor-de-hooks-de-natives)
    - [4.9. `callbacks.hpp` \& `amx_memory.hpp`: Llamadas C++ -\> Pawn y RAII](#49-callbackshpp--amx_memoryhpp-llamadas-c---pawn-y-raii)
    - [4.10. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Acceso Abstraído a la AMX](#410-amx_apihpp--amx_helpershpp--amx_defsh-acceso-abstraído-a-la-amx)
  - [5. Compilación y Despliegue](#5-compilación-y-despliegue)
    - [Requisitos de Arquitectura y Plataforma](#requisitos-de-arquitectura-y-plataforma)
    - [Ejemplos de Comandos de Compilación](#ejemplos-de-comandos-de-compilación)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW en Windows)**](#gcc--clang-mingw-en-windows)
    - [Consideraciones para la Distribución](#consideraciones-para-la-distribución)
  - [Licencia](#licencia)
    - [Términos y Condiciones de Uso](#términos-y-condiciones-de-uso)
      - [1. Permisos Otorgados](#1-permisos-otorgados)
      - [2. Condiciones Obligatorias](#2-condiciones-obligatorias)
      - [3. Derechos de Autor](#3-derechos-de-autor)
      - [4. Exención de Garantías y Limitación de Responsabilidad](#4-exención-de-garantías-y-limitación-de-responsabilidad)

## 1. Introducción y Filosofía de Diseño

### El Problema con la API C Estándar de SA-MP

La API de plugins de SA-MP es una interfaz de programación en C. Aunque funcional y fundamental, presenta los desafíos inherentes a la programación de bajo nivel:
- **Administración Manual de Memoria:** Funciones como `amx_Allot` y `amx_Release` exigen que el desarrollador asigne y desasigne explícitamente la memoria en el heap de la AMX. Esto es una fuente común de fugas de memoria y fallos de runtime.
- **Tipado Débil y Conversiones Manuales:** Los parámetros se pasan como un array de `cell`s, forzando conversiones explícitas (y muchas veces inseguras) entre `cell`, `int`, `float` y `char*`.
- **Verbosidad y Código Repetitivo (Boilerplate):** Extraer múltiples parámetros de un array `cell* params`, manejar tamaños de strings y administrar la pila de la AMX para las llamadas de retorno de C++ a Pawn requiere código repetitivo.
- **Fragilidad de la Interfaz:** La falta de verificación en tiempo de compilación (type safety) significa que los errores en el paso de parámetros o tipos pueden pasar desapercibidos hasta la ejecución, causando bloqueos o comportamientos indefinidos.

### La Solución del SA-MP SDK: Abstracción con Seguridad y Performance

El SA-MP SDK aborda estos problemas proporcionando una potente capa de abstracción en C++:
- **RAII (Resource Acquisition Is Initialization):** Administración automática de memoria en la AMX. `Amx_Scoped_Memory` garantiza que la memoria asignada sea liberada.
- **Seguridad de Tipos:** Conversión automática y segura de parámetros entre C++ y Pawn. Usted trabaja con `int`, `float`, `std::string` directamente.
- **Sintaxis Concisa e Idiomática:** Las macros y las plantillas proporcionan una API limpia que se asemeja más al C++ moderno que a la API C tradicional.
- **Interceptación Robusta:** Un motor de hooking avanzado permite la interceptación transparente de callbacks de Pawn (`Plugin_Public`), la creación de nuevas nativas (`Plugin_Native`), y **el hooking y encadenamiento de funciones nativas existentes de SA-MP (`Plugin_Native_Hook`)**.
- **Alto Rendimiento:** Uso extensivo de hashing en tiempo de compilación (FNV1a), caching de funciones y optimizaciones de `thread_local` para minimizar la sobrecarga de las abstracciones.

### Modelo Header-Only: Ventajas e Implicaciones

El SDK está compuesto exclusivamente por archivos de cabecera (`.hpp`, `.h`).
- **Ventajas:**
   - **Integración Simplificada:** No hay bibliotecas para construir, vincular o distribuir. Simplemente incluya los headers.
   - **Optimizaciones del Compilador:** El compilador tiene visibilidad completa del código del SDK y de su plugin, permitiendo inlining agresivo y optimizaciones de tiempo de enlazado, lo que puede resultar en binarios más rápidos.
- **Implicaciones:**
   - **Tiempo de Compilación:** Para proyectos muy grandes, la compilación puede llevar más tiempo debido a la inclusión repetida del código del SDK. Esto se mitiga con guards de inclusión y por la naturaleza de "incluir solo lo necesario" de C++.
   - **Macros de Implementación:** La necesidad de la macro `SAMP_SDK_IMPLEMENTATION` es una consecuencia del modelo header-only para evitar redefiniciones de símbolos.

## 2. Configuración y Ambiente

### Requisitos de Compilación

- **Compilador C++:** Compatible con C++14 o superior (el SDK utiliza características de C++14, C++17 y C++20 para optimizaciones específicas, pero C++14 es el mínimo).
   - GCC (versión 7+)
   - Clang (versión 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Arquitectura:** **x86 (32-bit)**. SA-MP opera exclusivamente en esta arquitectura. El SDK incluye verificaciones en `platform.hpp` que emitirán errores de compilación si se detecta la arquitectura incorrecta.
- **Sistema Operativo:** Windows o Linux.

### Estructura de Archivos Recomendada

Para mayor claridad y organización, es común organizar el SDK en una subcarpeta `samp-sdk`.

```
my_plugin/
├── samp-sdk/
│   ├── // Otros archivos del SDK
│   └── samp_sdk.hpp             // El principal header a incluir
│
├── src/
│   ├── main.cpp                  // Donde se define SAMP_SDK_IMPLEMENTATION
│   └── my_custom_logic.cpp       // Opcional, para organizar el código
│
└── CMakeLists.txt (o .vcxproj, Makefile)
```

### Macros Esenciales de Configuración

Siempre defina estas macros *antes* de incluir `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Propósito:** Señaliza al compilador que este archivo `.cpp` debe generar las implementaciones de las funciones de exportación del plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **El SDK se encarga de la exportación de estas funciones automáticamente, eliminando la necesidad de archivos `.def` (en Windows) o declaraciones `__attribute__((visibility("default")))` (en Linux) para estas funciones.**
- **Impacto Técnico:** Sin esta macro, el enlazador no encontrará las exportaciones necesarias, y el servidor SA-MP no podrá cargar su plugin.
- **Regla Fundamental:** **Defina esta macro en SÓLO UN archivo `.cpp` en todo su proyecto.** Definirla en más de un archivo causará un error de enlazado de "símbolo duplicado".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // La macro hace que el SDK exporte las funciones necesarias automáticamente.
#include "samp-sdk/samp_sdk.hpp"

// ... su código de plugin ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Propósito:** Habilita los callbacks de ciclo de vida del script Pawn (`OnAmxLoad`, `OnAmxUnload`) y la funcionalidad de crear nuevas nativas en C++ (`Plugin_Native`).
- **Funcionalidades Activadas:**
   - Callbacks `OnAmxLoad(AMX* amx)` y `OnAmxUnload(AMX* amx)`.
   - Declaración y registro de nuevas nativas C++ usando `Plugin_Native`.
   - La macro `Plugin_Call` para invocar nativas creadas con `Plugin_Native` dentro de su propio plugin.
- **Impacto Técnico:** Cuando se define esta macro, el SDK recolecta automáticamente todas sus `Plugin_Native`s. En la función `Supports()`, la flag `SUPPORTS_AMX_NATIVES` se añade automáticamente si hay alguna `Plugin_Native` en su proyecto.
- **Flexibilidad:** **Puede definir esta macro en múltiples archivos `.cpp`**. El sistema de registro estático del SDK consolidará todas las nativas de diferentes unidades de compilación en una única lista global.

```cpp
// my_natives.cpp (puede ser un archivo separado de main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Solo para habilitar Plugin_Native y los callbacks OnAmxLoad/OnAmxUnload
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Propósito:** Habilita el callback `OnProcessTick()`, que es invocado regularmente por el servidor.
- **Impacto Técnico:** Añade automáticamente la flag `SUPPORTS_PROCESS_TICK` en la función `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Lógica ejecutada en cada "tick" del servidor (ej: 20ms)
    // ¡Cuidado con operaciones pesadas aquí!
}
```

### Definiciones y Constantes de SA-MP (`samp_defs.hpp`)

Este archivo proporciona todas las constantes y límites conocidos de SA-MP, como `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. Se incluye automáticamente por `samp_sdk.hpp` y debe usarse para garantizar la compatibilidad y legibilidad del código.

## 3. Guía de Uso Abrangente de la API

### 3.1. El Ciclo de Vida del Plugin

Las siguientes funciones son los puntos de entrada y salida de su plugin, exportadas automáticamente por el SDK.

#### `bool OnLoad()`

- **Descripción:** Primera función llamada por el servidor SA-MP después de la carga exitosa de su plugin en memoria.
- **Uso:** Ideal para inicializar cualquier sistema, cargar configuraciones, abrir conexiones a bases de datos o cargar módulos (`Plugin_Module`).
- **Retorno:**
   - `true`: El plugin se inicializó con éxito y la carga continúa.
   - `false`: El plugin falló al inicializar. La carga se abortará y el plugin se descargará.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Inicializando MeuPlugin v1.0...");

    // Ejemplo: Cargar un módulo (más detalles en la sección 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Módulo de Base de Datos cargado.")) {
        Samp_SDK::Log("ERROR: ¡Fallo al cargar el módulo de base de datos!");

        return false; // Aborta la carga del plugin principal
    }

    return true;
}
```

#### `void OnUnload()`

- **Descripción:** Última función llamada por el servidor SA-MP antes de descargar su plugin de la memoria.
- **Uso:** Ideal para limpiar recursos, cerrar conexiones, guardar estados y garantizar que no se filtren recursos. El SDK administra la descarga de módulos (`Plugin_Module`) automáticamente.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MeuPlugin descargado. Liberando recursos...");
    // No se requiere ninguna acción manual para los módulos cargados a través de Plugin_Module;
    // el SDK se encarga de ello.
}
```

#### `unsigned int GetSupportFlags()`

- **Descripción:** Informa al servidor SA-MP qué recursos soporta y desea utilizar su plugin.
- **Uso:** **Siempre devuelva `SUPPORTS_VERSION` (o `SAMP_PLUGIN_VERSION`).** Las flags `SUPPORTS_AMX_NATIVES` y `SUPPORTS_PROCESS_TICK` son añadidas automáticamente por el SDK si hay `Plugin_Native`s, y/o si la macro `SAMP_SDK_WANT_PROCESS_TICK` está definida, respectivamente. Esto simplifica el mantenimiento y evita errores.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // El SDK añade las flags necesarias automáticamente.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requiere:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descripción:** Llamada cada vez que se carga e inicializa un nuevo script Pawn (un Gamemode o Filterscript) en el servidor.
- **Uso:** Si necesita lógica específica para cada script AMX, o inicializar datos específicos por script.

```cpp
// main.cpp (con SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxLoad(AMX* amx) {
    // amx representa la nueva instancia del script cargado.
    Samp_SDK::Log("Script AMX cargado: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Requiere:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descripción:** Llamada cuando un script Pawn se descarga del servidor.
- **Uso:** Para limpiar cualquier recurso específico que haya asignado o asociado a esa `AMX*` en particular.

```cpp
// main.cpp (con SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX descargado: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requiere:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Descripción:** Llamada repetidamente en cada "tick" del servidor (generalmente 20 veces por segundo, o cada 50ms).
- **Uso:** Para lógica de fondo continua, temporizadores, actualizaciones de estado que no dependen de eventos del jugador, o sincronización de datos.
- **Cuidado:** Evite operaciones de bloqueo o computacionalmente pesadas aquí, ya que pueden causar lag en el servidor.

```cpp
// main.cpp (con SAMP_SDK_WANT_PROCESS_TICK definido)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Cada 10 segundos (20 ticks/seg * 10 seg = 200 ticks)
        Samp_SDK::Log("Servidor activo por %d segundos.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Interceptando Eventos de Pawn

La macro `Plugin_Public` es el puente principal para recibir callbacks de Pawn en su código C++.

#### Sintaxis y Declaración

- `Plugin_Public(NombreDeLaPublic, Tipo1 Param1, Tipo2 Param2, ...)`
- El nombre de la función C++ que usted declara **debe ser el mismo** que el callback de Pawn (ej: `OnPlayerConnect`).
- Los tipos de parámetros C++ (`int`, `float`, `std::string`) son automáticamente convertidos por el SDK.

```cpp
// Intercepta OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Jugador %d dijo: %s", playerid, text.c_str());

    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Marshalling Automático de Parámetros

El SDK maneja automáticamente la lectura de la `cell stack` de la AMX y la conversión a los tipos C++ especificados:
- `int`: Convertido directamente de `cell`.
- `float`: Convertido de `cell` usando `amx::AMX_CTOF`.
- `std::string`: El SDK lee la dirección de la string en la AMX, asigna una `std::string` en C++ y copia el contenido.

#### Control de Flujo: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

El valor devuelto por su función `Plugin_Public` es crucial y determina el flujo de ejecución del callback:
- `return PLUGIN_PUBLIC_CONTINUE;` (valor `1`): Indica que la ejecución del callback debe **continuar**. Si hay otros plugins que también interceptan este callback, se les llamará (en orden inverso de carga). Luego, se invocará la `public` original en el script Pawn.
- `return PLUGIN_PUBLIC_STOP;` (valor `0`): Indica que la ejecución del callback debe ser **interrumpida**. Ningún otro plugin (con menor prioridad) o la `public` original en el script Pawn será invocado para este evento. Esto es ideal para implementar un sistema que "sobrescribe" o "bloquea" un comportamiento estándar de SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Congela al jugador
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Jugador %d congelado.", playerid));

        return PLUGIN_PUBLIC_STOP; // Impide que el comando sea procesado por otros scripts.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Permite que otros comandos sean procesados.
}
```

#### Ghost Callbacks

Una característica avanzada de `Plugin_Public` es el soporte a "Ghost Callbacks". Esto significa que puede interceptar un callback de Pawn incluso si **no está presente** en el script `.amx` del gamemode o filterscript. El SDK "engaña" al servidor para que llame a su hook C++ de todas formas. Esto es útil para callbacks internos o para crear nuevas funcionalidades sin depender de la presencia de una `public` en el script Pawn.

```cpp
// Puede definir un callback que el script Pawn no posee, pero su plugin lo escuchará.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Evento interno personalizado recibido: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// Para "disparar" este evento desde otro punto de su código C++:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// La llamada irá a su Plugin_Public anterior, incluso si no hay OnMyCustomInternalEvent en Pawn.
```

### 3.3. `Plugin_Native`: Creando Funciones Nativas en C++

`Plugin_Native` le permite extender la funcionalidad de Pawn con código C++ de alto rendimiento.

#### Sintaxis y Firma Fija

- `Plugin_Native(NombreDeLaNative, AMX* amx, cell* params)`
- La función C++ debe tener exactamente esta firma: `cell NombreDeLaNative(AMX* amx, cell* params)`.
- `NombreDeLaNative` es el nombre que utilizarán los scripts Pawn.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementación ...
    return 0;
}
```

#### Registro Automático de Nativas

> [!NOTE]
> No necesita llamar a `amx_Register` manualmente. El SDK detecta todas sus `Plugin_Native`s (en cualquier archivo `.cpp` que haya incluido `samp_sdk.hpp` y definido `SAMP_SDK_WANT_AMX_EVENTS`) y las registra automáticamente en cada script AMX cargado (`OnAmxLoad`).

#### Extracción de Parámetros: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Descripción:** Un asistente más simple para extraer múltiples parámetros secuencialmente.
- **Uso:** `Register_Parameters(variable1, variable2, ...)`
- **Limitaciones:** Para parámetros de entrada. No maneja parámetros opcionales o acceso por índice.
- **Tipos Soportados:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extrae los 3 parámetros
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)

- **Descripción:** Una clase wrapper que proporciona una interfaz orientada a objetos para acceder a los parámetros de una nativa. Más potente para escenarios complejos.
- **Construcción:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Descripción:** Devuelve el número de parámetros pasados a la nativa.
- **Uso:** Esencial para manejar parámetros opcionales.

###### `p.Get<T>(size_t index)`

- **Descripción:** Extrae un parámetro de entrada por índice y lo convierte al tipo `T`.
- **Tipos Soportados:** `int`, `float`, `std::string`.

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

- **Descripción:** Obtiene el valor de un parámetro de **referencia** (puntero Pawn) y lo almacena en `out_value`.
- **Uso:** Para leer valores que fueron pasados por referencia desde Pawn.
- **Retorno:** `true` si la dirección AMX es válida, `false` en caso contrario.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Obtiene los valores de las referencias (Pawn pasó direcciones)
    p.Get_REF(1, health); // Lee el valor de Float:health
    p.Get_REF(2, money);   // Lee el valor de money
    
    Samp_SDK::Log("Jugador %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Ahora, modificarlos
    health = 50.0f;
    money += 100;
    
    // Y escribirlos de vuelta en la memoria de Pawn
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Descripción:** Devuelve un `std::optional<T>` para leer un parámetro de referencia. Más seguro para C++17 y superior.

###### `p.Set_REF<T>(size_t index, T value)`

- **Descripción:** Escribe un valor `T` en un parámetro de **referencia** de Pawn (la dirección que Pawn pasó).
- **Uso:** Para modificar valores que fueron pasados por referencia, haciendo que Pawn vea el cambio.
- **Retorno:** `true` si la escritura fue exitosa, `false` en caso contrario.

#### Retorno de Valores

- Su función `Plugin_Native` debe retornar una `cell`.
- Para retornar un `int` o `bool`, use un cast a `cell`.
- Para retornar un `float`, use `amx::AMX_FTOC(mi_float)`.

```cpp
// Retorna un bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Retorna un float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Retorna 100.0f
}
```

### 3.4. `Plugin_Native_Hook`: Interceptando Nativas Existentes de SA-MP

La macro `Plugin_Native_Hook` le permite interceptar y modificar el comportamiento de cualquier función nativa existente de SA-MP o de otros plugins. Este es un mecanismo potente para extender o alterar la lógica estándar del servidor.

#### Sintaxis y Firma Fija

- `Plugin_Native_Hook(NombreDeLaNative, AMX* amx, cell* params)`
- La función C++ debe tener exactamente esta firma: `cell NombreDeLaNative(AMX* amx, cell* params)`.
- `NombreDeLaNative` debe ser el nombre exacto de la native que desea hookear (ej: `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepta la native SendClientMessage
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Importante llamar a la original
}
```

#### Registro y Activación del Hook

> [!NOTE]
> No necesita llamar a `amx_Register` manualmente o definir `SAMP_SDK_WANT_AMX_EVENTS` específicamente para `Plugin_Native_Hook`. El SDK detecta y registra automáticamente sus hooks. En la primera ejecución de un script AMX, el SDK reemplaza el puntero de la native en la tabla por un "trampoline" que redirige a su función `Plugin_Native_Hook`. Este proceso garantiza el encadenamiento seguro de hooks de múltiples plugins.

#### Llamando a la Native Original (Cadena de Hooks): `Call_Original_Native`

Dentro de su función `Plugin_Native_Hook`, **DEBE** usar la macro `Call_Original_Native(NombreDeLaNative)` para invocar la función original (o el siguiente hook en la cadena). Esto es vital para:
- **Preservar la Funcionalidad:** Si no llama a la original, la native hookeada simplemente dejará de funcionar para otros plugins o para el servidor.
- **Encadenamiento de Hooks:** Permite que múltiples plugins hookeen la misma native y que todos los hooks se ejecuten en una secuencia.
- **Manipulación de Retorno:** Puede inspeccionar e incluso modificar el valor de retorno de `Call_Original_Native` antes de retornarlo desde su función de hook.

```cpp
// Ejemplo: Bloqueando SendClientMessage si contiene una palabra específica
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extrae los parámetros para análisis
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // No necesitamos el color para esta lógica
    std::string message = p.Get_String(2); // Obtiene la string del mensaje

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MENSAJE BLOQUEADO para playerid %d: %s", playerid, message.c_str());

        return 0; // Retorna 0 (false) a Pawn, indicando que el mensaje no fue enviado.
                  // Y lo que es más importante, NO llamamos a Call_Original_Native, bloqueando el mensaje.
    }

    // Si el mensaje no contiene la palabra prohibida, llamamos a la native original
    // y retornamos su valor, garantizando que el mensaje se envíe normalmente
    // y que otros hooks (si existen) se ejecuten.
    return Call_Original_Native(SendClientMessage);
}
```

#### Ejemplo Completo de `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS no es estrictamente necesario para hooks, pero es común tener OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook para la native CreateVehicle
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extrae los parámetros de la native CreateVehicle para inspección
    int modelid = p.Get<int>(0);
    float x = p.Get<float>(1);
    float y = p.Get<float>(2);
    float z = p.Get<float>(3);
    float angle = p.Get<float>(4);
    int color1 = p.Get<int>(5);
    int color2 = p.Get<int>(6);
    int respawn_delay = p.Get<int>(7);
    bool addsiren = p.Get<bool>(8);

    Samp_SDK::Log("HOOK: CreateVehicle llamado! Model: %d, Pos: (%.2f, %.2f, %.2f)", modelid, x, y, z);

    // Ejemplo de cómo *modificar* un parámetro de entrada
    // Si el modelo es 400 (Landstalker), lo cambiamos a 401 (Bravura)
    if (modelid == 400) {
        // Modificamos directamente el array 'params' para la llamada original
        params[1] = static_cast<cell>(401); // El modelo está en la posición 0 del array de parámetros (params[1])
        Samp_SDK::Log("  -> Modelo 400 cambiado a 401 antes de la creación.");
    }
    
    // Llamamos a la native original (o el siguiente hook en la cadena) con los parámetros posiblemente modificados
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle retornó: %d (ID del vehículo)", (int)original_retval);

    // Puede modificar el valor de retorno aquí antes de retornarlo a Pawn.
    // Ejemplo: si el vehículo falló en la creación, retorne un ID inválido personalizado.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> La creación del vehículo falló en la native original.");

        return -1; // Retorna un valor diferente a Pawn.
    }

    return original_retval; // Retorna el valor que la native original retornó (o el modificado anteriormente).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Implementaciones mínimas para el ciclo de vida
bool OnLoad() {
    Samp_SDK::Log("¡Plugin de Ejemplo de Native Hook cargado!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("¡Plugin de Ejemplo de Native Hook descargado!");
}

// Estos callbacks solo estarán presentes si SAMP_SDK_WANT_AMX_EVENTS está definido
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detectado: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detectado: %p", (void*)amx);
}*/
```
> [!WARNING]
> La manipulación directa del array `cell* params` para alterar parámetros de entrada exige cautela. Asegúrese de entender el orden y el tipo de los parámetros. Para la mayoría de los casos de uso, `p.Get(...)` para inspeccionar y `Call_Original_Native(...)` para continuar la cadena es suficiente. La alteración directa de `params` debe hacerse solo si sabe que el parámetro es un valor y necesita ser modificado para la llamada original. Para strings y arrays, la modificación es más compleja y generalmente implica `amx::Set_String` para escribir en la dirección existente o reasignar, lo que puede ser más fácil de manejar llamando a la native a través de `Pawn_Native` con los nuevos valores y retornando `0` de su hook para cancelar la llamada original.

### 3.5. `Pawn_*` Macros: Llamando Funciones de Pawn desde C++

Estas macros son el inverso de `Plugin_Public` y `Plugin_Native`: permiten que su código C++ invoque funciones de Pawn.

#### `Pawn_Native(NombreDeLaNative, ...)`

- **Propósito:** La forma recomendada de llamar funciones nativas de SA-MP (o de otros plugins) desde C++.
- **Mecanismo:** Busca el puntero de la nativa en el caché interno del SDK (rellenado por `Amx_Register_Detour`). Si se encuentra, ejecuta la nativa en un entorno `Amx_Sandbox` (una instancia AMX falsa y aislada).
- **Rendimiento:** La más eficiente, ya que evita la costosa búsqueda de `publics` e interactúa directamente con el puntero de la nativa.

#### `Pawn_Public(NombreDeLaPublic, ...)`

- **Propósito:** Llama a una función pública específica en un script Pawn.
- **Mecanismo:** Recorre las instancias `AMX*` administradas por el `Amx_Manager`, busca la `public` por su nombre y la ejecuta.
- **Rendimiento:** Menos eficiente que `Pawn_Native` debido a la búsqueda y al `amx_Exec` real. Generalmente, las `publics` son más lentas que las `natives`.
- **Uso:** Ideal para invocar eventos personalizados en su Gamemode/Filterscripts que no son nativas.

#### `Pawn(NombreDeLaFuncion, ...)`

- **Propósito:** Una macro de conveniencia que intenta adivinar si la función es una nativa o una pública.
- **Mecanismo:** Primero, intenta llamar como `Pawn_Native`. Si falla (no se encuentra la nativa), intenta llamar como `Pawn_Public`.
- **Rendimiento:** Puede ser un poco más lenta que `Pawn_Native` si la función es nativa, debido al intento de búsqueda doble. Para `publics`, el rendimiento es el mismo que `Pawn_Public`.
- **Uso:** Para funciones donde no está seguro si son nativas o públicas, o para evitar el código repetitivo de intentar una y luego la otra.

#### Sintaxis y Convenciones

- **Nombre de la Función:** Siempre use el nombre de la función Pawn **directamente, sin comillas**. El SDK lo convertirá a string internamente.
- **Parámetros:** Pase los parámetros C++ directamente.

```cpp
// Correcto:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Incorrecto (pero técnicamente funcionaría debido al hash, evítelo):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling de Parámetros de Entrada

El SDK convierte sus tipos C++ al formato `cell` de la AMX, administrando la memoria según sea necesario:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (usando `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (asigna memoria en la AMX, copia la string y pasa la dirección `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling de Parámetros de Salida (Referencias: `int&`, `float&`, `std::string&`)

Esta es una funcionalidad clave para la comodidad y seguridad. Para funciones de Pawn que esperan un puntero (referencia), el SDK automatiza todo el proceso de asignación/liberación de memoria y copia de datos.

- **Cómo usar:** Simplemente pase su variable por referencia (`&`).
- **Mecanismo:** El SDK asigna memoria en el heap de la AMX, pasa la dirección AMX a la función de Pawn, espera que la función de Pawn rellene esa dirección, lee el valor de vuelta y libera la memoria de la AMX. Todo de forma transparente.
- **Con `std::string&`:** El SDK asigna un búfer estándar (256 celdas) en la AMX para la string.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Ubicación de %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interior:%d World:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### El Objeto `Callback_Result`: Análisis Completo

Todas las llamadas `Pawn_*` devuelven un objeto `Callback_Result`. Este objeto es un envoltorio seguro para el resultado de la llamada de Pawn.

- `Callback_Result() noexcept`: Constructor predeterminado, indica fallo (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Constructor para éxito o fallo con valor.
- `explicit operator bool() const`: Permite usar `if (result)` para verificar si la llamada fue exitosa.
- `operator cell() const`: Permite convertir el resultado a `cell` para obtener el valor.
- `float As_Float() const`: Conveniencia para obtener el resultado como `float`.
- `cell Value() const`: Retorna el valor `cell` bruto.
- `bool Success() const`: Retorna `true` si la llamada de Pawn fue exitosa.
- `int Get_Amx_Error() const`: Retorna el código de error de la AMX si la llamada falló (0 para éxito).

```cpp
// Ejemplo: Obteniendo la vida de un jugador.
// La nativa GetPlayerHealth(playerid, &Float:health) espera un playerid y una referencia para la vida.
int playerid = 0; // Ejemplo de ID de jugador
float player_health = 0.0f;

// Llamamos a GetPlayerHealth, pasando playerid y player_health por referencia.
// El SDK se encargará del marshalling para el parámetro de salida 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Verifica si la llamada fue exitosa (operator bool)
    // El valor retornado por result.As_Float() o result (operator cell)
    // sería el valor de retorno de la *nativa*, no el parámetro de salida.
    // El valor de la vida ya se actualizó en 'player_health' debido al marshalling del parámetro de salida.
    Samp_SDK::Log("Jugador %d tiene %.1f de vida.", playerid, player_health);
}
else {
    // La llamada falló, quizás el jugador no existe o la nativa no fue encontrada.
    Samp_SDK::Log("Error al obtener vida del jugador %d. Código AMX: %d", playerid, result.Get_Amx_Error());
}

// Para nativas que devuelven un valor y usan parámetros de salida (menos común, pero posible),
// usted usaría ambos:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param ya está actualizado
// }
```

### 3.6. `Plugin_Module`: Administración de Módulos Dinámicos

La macro `Plugin_Module` permite que su plugin actúe como un "cargador" para otros plugins, creando una arquitectura modular y extensible. Un módulo cargado de esta forma es tratado como un plugin de primera clase, con su propio ciclo de vida de eventos administrado por el plugin anfitrión.

#### Sintaxis y Propósito

- `Plugin_Module(const char* nombre_del_archivo_base, const char* directorio_del_modulo, const char* mensaje_exito_opcional)`
- `nombre_del_archivo_base`: El nombre *base* del archivo del módulo, **sin la extensión** (ej: para `my_module.dll` o `my_module.so`, use `"my_module"`). El SDK agregará automáticamente la extensión `.dll` o `.so` apropiada.
- `directorio_del_modulo`: La ruta del directorio donde se encuentra el archivo del módulo (ej: `"plugins/my_custom_modules"`). **No incluya el nombre del archivo aquí.** El SDK concatenará la ruta completa (`directorio_del_modulo/nombre_del_archivo_base.ext`).
- `mensaje_exito_opcional`: Un mensaje opcional que se registrará en la consola del servidor si el módulo se carga con éxito.

```cpp
// main.cpp, dentro de OnLoad()

// Carga el módulo 'core_logic.dll' (o 'core_logic.so')
// que está ubicado en la carpeta 'modules/custom/' del servidor.
if (!Plugin_Module("core_logic", "modules/custom", "¡Módulo de Lógica Core cargado con éxito!"))
    return (Samp_SDK::Log("¡ERROR FATAL: Fallo al cargar el módulo 'core_logic'!"), false);

// Carga el módulo 'admin_system.dll' (o 'admin_system.so')
// que está ubicado directamente en la carpeta 'plugins/' del servidor.
if (!Plugin_Module("admin_system", "plugins", "Módulo de Administración activado."))
    Samp_SDK::Log("AVISO: El módulo de Administración no pudo ser cargado.");
```

#### Ciclo de Vida de un Módulo

Un módulo debe exportar las funciones `Load`, `Unload` y `Supports`, al igual que un plugin normal. El SDK administra el ciclo de vida del módulo de la siguiente manera:

- **Carga:** Cuando se llama a `Plugin_Module`, el SDK:
   1. Construye la ruta completa del archivo (ej: `modules/custom/core_logic.dll`).
   2. Usa `Dynamic_Library` (`LoadLibrary`/`dlopen`) para cargar el binario.
   3. **Obtiene los punteros a TODAS las funciones del ciclo de vida del módulo:**
      - **Obligatorias:** `Load`, `Unload`, `Supports`. Si alguna falta, la carga del módulo falla.
      - **Opcionales:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Llama a la función `Load` del módulo, pasando `ppData` del plugin principal.
   5. Si `Load` devuelve `true`, el módulo se añade a la lista interna de módulos cargados.

- **Reenvío de Eventos:** El plugin anfitrión **reenvía automáticamente** los eventos a todos los módulos cargados.
 > [!IMPORTANT]
 > Para que los eventos se reenvíen correctamente, el **plugin anfitrión** (el que llama a `Plugin_Module`) debe estar configurado para recibir esos eventos.
 > - Para que `AmxLoad` y `AmxUnload` funcionen en los módulos, el plugin anfitrión debe definir la macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Para que `ProcessTick` funcione en los módulos, el plugin anfitrión debe definir la macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Descarga:** Durante `OnUnload` de su plugin principal, el SDK descarga todos los módulos que fueron cargados a través de `Plugin_Module`. Esto se realiza en **orden inverso** a la carga (el último en cargarse es el primero en descargarse), lo cual es crucial para administrar dependencias y garantizar la liberación correcta de recursos.

#### Beneficios de la Modularización

- **Organización del Código:** Divida grandes plugins en componentes más pequeños y manejables, cada uno en su propio archivo de módulo.
- **Reusabilidad:** Cree módulos genéricos (ej: un módulo de base de datos, un módulo de sistema de registro avanzado) que puedan ser utilizados por diferentes plugins, promoviendo la reutilización de código.
- **Componentes Independientes:** Cree módulos que sean **totalmente orientados a eventos e independientes**. Un módulo puede tener sus propias `Plugin_Native`s, interceptar `Plugin_Public`s y tener su propia lógica `OnProcessTick`, operando como un plugin autónomo, pero cargado por un anfitrión.
- **Actualizaciones Dinámicas:** En escenarios controlados, permite la actualización de partes de su sistema (reemplazando un `.dll` o `.so` de módulo) sin la necesidad de recompilar y reiniciar el plugin principal o el servidor completo (aunque esto requiere una gestión de versiones y compatibilidad rigurosas).

### 3.7. `Plugin_Call`: Llamando Nativas Internas del Plugin

Utilice `Plugin_Call` para invocar una `Plugin_Native` definida **dentro de su propio plugin**.

#### Sintaxis y Ventajas de Performance

- `Plugin_Call(NombreDeLaNative, Param1, Param2, ...)`
- **Ventaja:** Evita la sobrecarga de buscar la nativa en el array de nativas de la AMX. El SDK mantiene un mapa directo de hashes de nombre a punteros de función para sus propias nativas, lo que hace de esta la forma más rápida de llamarlas internamente.
- **Requiere:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Lógica para verificar el nivel
    return (playerid % 2 == 0) ? 1 : 0; // Ejemplo: nivel par para IDs pares
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Llama a su propia nativa
                Samp_SDK::Log("¡Jugador %d está en un nivel alto!", i);
        }
    }
}
```

### 3.8. Funciones Utilitarias del SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Descripción:** Imprime mensajes en la consola del servidor y en el archivo `server_log.txt`. Un envoltorio seguro para `logprintf`.
- **Uso:** Para depuración, mensajes de estado y errores.
- **Mecanismo:** Internamente, el SDK obtiene el puntero a `logprintf` a través de `ppData[PLUGIN_DATA_LOGPRINTF]`. La función maneja el formato de la string de forma segura.

```cpp
// En cualquier lugar de su plugin
Samp_SDK::Log("El plugin fue inicializado con un valor %d y una string '%s'.", 123, "prueba");
```

#### `std::string Plugin_Format(const char* format, ...)` (Recomendado)

- **Descripción:** Formatea una string de forma segura (similar a `sprintf`) y devuelve un `std::string`. Esta es la manera **recomendada y más idiomática** de formatear strings para usar dentro de su plugin.
- **Uso:** Ideal para construir mensajes formateados antes de pasarlos a `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, o para cualquier otra necesidad de string dentro de su código C++.
- **Mecanismo:** Internamente, `Plugin_Format` es una macro que llama a `Samp_SDK::Format`. Utiliza `vsnprintf` para determinar el tamaño exacto de la string formateada y asigna un `std::string` con capacidad suficiente, evitando desbordamientos de búfer.

```cpp
int playerid = 0; // Ejemplo de ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Jugador %d, tu vida actual es %d.", playerid, health));

// También se puede usar para logs internos
Samp_SDK::Log(Plugin_Format("DEBUG: Procesando estado para el ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Detalle de Implementación)

- **Descripción:** La función de implementación subyacente para el formato de strings, ubicada dentro del namespace `Samp_SDK`.
- **Uso:** Generalmente no es llamada directamente por el usuario. La macro `Plugin_Format` se proporciona como una conveniencia para esta función, alineándose con la convención de nombres de otras macros del SDK (`Plugin_Public`, `Plugin_Native`). Solo la llamaría directamente si quisiera evitar la macro `Plugin_Format` por alguna razón específica.

```cpp
// Ejemplo de cómo funciona Samp_SDK::Format, pero prefiera Plugin_Format
std::string raw_status = Samp_SDK::Format("Solo para uso interno: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Descripción:** Convierte una dirección de string de la AMX (`cell amx_addr`) en un `std::string` de C++.
- **Uso:** Principalmente dentro de `Plugin_Native` y `Plugin_Native_Hook` cuando necesita acceder a strings que no son convertidas automáticamente por `Register_Parameters` o `Native_Params` (ej: si el parámetro de Pawn es un `const` `string` y no fue declarado como `std::string` en su `Plugin_Native` o `Plugin_Public` para el Marshalling automático).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Obtiene la dirección de la string en la AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String de la AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Anatomía Interna y Arquitectura del SDK

Esta sección desvela los mecanismos subyacentes del SA-MP SDK, explorando su arquitectura, los componentes clave y cómo interactúan para proporcionar la abstracción de alto nivel. Una comprensión profunda de estas entrañas capacita al desarrollador para optimizar el uso del SDK, depurar problemas complejos e incluso extender sus funcionalidades.

### 4.1. `core.hpp`: La Fundación Minimalista

`Samp_SDK::Core` es un `singleton` que sirve como el punto de acceso inicial y centralizado a los datos de bajo nivel proporcionados por el entorno del plugin SA-MP. Su principal responsabilidad es encapsular y exponer las funcionalidades esenciales.

- **`Samp_SDK::Core::Instance()`**:
   - **Descripción:** Devuelve la única instancia global de la clase `Core`. Este es un patrón de diseño `singleton` para garantizar que el acceso a los datos del plugin (`ppData`) sea consistente y centralizado.
   - **Mecanismo:** La instancia se inicializa una única vez cuando `Core::Instance().Load(ppData)` es llamada en la función `Load()` de su plugin.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Descripción:** Permite acceso seguro e indexado a los punteros de función de la API AMX. El array `pAMXFunctions` (recibido a través de `ppData[PLUGIN_DATA_AMX_EXPORTS]`) contiene las direcciones de funciones críticas como `amx_Exec`, `amx_Register`, etc.
   - **Impacto:** En lugar de usar `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, el SDK ofrece wrappers type-safe en el namespace `amx::` (ej: `amx::Exec(...)`), lo que hace el código más legible y menos propenso a errores de cast.
   - **Ejemplo Interno (`amx_api.hpp`):**
      ```cpp
      // Fragmento simplificado de amx_api.hpp
      namespace amx {
          template <typename Func, int Index, typename... Args>
          inline auto Call(Args... args) -> decltype(std::declval<Func>()(args...)) {
              using Return_Type = decltype(std::declval<Func>()(args...));
              auto func_ptr = reinterpret_cast<Func>(Core::Instance().Get_AMX_Export(Index));

              if (SAMP_SDK_UNLIKELY(!func_ptr)) {
                  Log("[SA-MP SDK] Fatal: Se intentó llamar a una exportación de AMX en el índice %d, ¡pero pAMXFunctions no se cargó!", Index);
                
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
   - **Descripción:** Un puntero a la función `logprintf` de SA-MP, que es la interfaz estándar para imprimir mensajes en la consola del servidor y en `server_log.txt`.
   - **Mecanismo:** `Samp_SDK::Log` es un envoltorio seguro que utiliza este puntero, garantizando que sus mensajes se muestren correctamente en el entorno de SA-MP.

### 4.2. `platform.hpp` y `version.hpp`: Compatibilidad y Metadatos

Estos headers son la base para la portabilidad y optimización del SDK, adaptándolo a diferentes entornos de compilación y aprovechando características específicas del C++ moderno.

- **Detección de Plataforma y Arquitectura:**
   - **Mecanismo:** Utiliza macros de preprocesador (`#if defined(WIN32)`, `#if defined(__linux__)`, etc.) para identificar el sistema operativo.
   - **Verificación de Arquitectura:** Contiene `static_assert` o `#error` para garantizar que el plugin se esté compilando para x86 (32 bits), un requisito crítico para la compatibilidad con SA-MP y el mecanismo de hooking.
   - **Administración de Exportación de Símbolos:**
      - `SAMP_SDK_EXPORT`: Una macro definida en `platform.hpp` que se expande a `extern "C"` y, en Linux, añade `__attribute__((visibility("default")))`. En Windows, solo garantiza `extern "C"` porque el SDK utiliza `pragma comment(linker, "/EXPORT:...")` (para MSVC) o el estándar MinGW para exportar las funciones principales.
      - Esto garantiza que las funciones del ciclo de vida del plugin (`Supports`, `Load`, `Unload`, etc.) se exporten correctamente desde su DLL/SO, independientemente del entorno de compilación, **sin la necesidad de archivos `.def` o de añadir `__attribute__((visibility("default")))` manualmente** en su implementación.
   - **Ejemplo (`platform.hpp` - fragmento relevante):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // Para MSVC, la exportación es administrada por comandos de enlace pragma
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // Para GCC/Clang en Linux, usamos el atributo de visibilidad
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... otras definiciones ...
      ```
   - **Ejemplo (`samp_sdk.hpp` - fragmento relevante de la implementación):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // En Windows (MSVC), usamos pragma comment para exportar las funciones.
          // Esto elimina la necesidad de un archivo .def.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... otras exports ...
      #endif

      // Implementación de las funciones exportadas
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... otras funciones ...
      #endif
      ```

- **Macros de Optimización y Predicción de Branch:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mecanismo:** `__forceinline` (MSVC) o `__attribute__((always_inline)) inline` (GCC/Clang). Sugiere fuertemente al compilador que inserte el cuerpo de la función directamente en el lugar de la llamada, eliminando el overhead de una llamada a función real.
      - **Uso:** Aplicado a funciones pequeñas y críticas para el rendimiento dentro del SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mecanismo:** `[[likely]]` / `[[unlikely]]` (C++20) o `__builtin_expect` (GCC/Clang). Pistas para el compilador sobre qué camino de un `if/else` es más probable que se tome.
      - **Impacto:** Ayuda al compilador a generar código más eficiente para la predicción de desvíos (branch prediction), reduciendo la latencia de la CPU.
      - **Ejemplo (`platform.hpp`):**
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
      - **Mecanismo:** `__attribute__((used))` (GCC/Clang). Informa al compilador que un símbolo (en este caso, una función) es utilizado, incluso si no hay referencias a él en el código C++.
      - **Impacto:** Crucial para funciones C++ que son llamadas a partir de bloques de assembly incrustado (`asm volatile`). Sin este atributo, el optimizador del compilador puede remover la función por error, resultando en un error de "símbolo indefinido" en el linker.
      - **Ejemplo (`platform.hpp`):**
         ```cpp
         #if defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
             #define SAMP_SDK_USED_BY_ASM __attribute__((used))
         #else
             #define SAMP_SDK_USED_BY_ASM
         #endif
         ```

- **Definiciones C++ Estándar (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mecanismo:** Macros definidas en base al valor de `__cplusplus` y `_MSVC_LANG`.
   - **Uso:** Permiten que el SDK utilice funcionalidades más recientes de C++ (como `std::apply` e `if constexpr` de C++17, o `std::is_same_v` de C++17) cuando estén disponibles, manteniendo la compatibilidad con estándares más antiguos.
   - **Ejemplo (`version.hpp` - uso de `if constexpr`):**
      ```cpp
      // Fragmento simplificado de public_dispatcher.hpp
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
                  // Compatibilidad C++14: usar la función auxiliar Assign_Parameter_By_Type
                  Assign_Parameter_By_Type(amx, &value, first); 
      #endif
          }

          Get_Public_Params_Recursive(amx, index + 1, rest...);
      }
      ```

### 4.3. `function_hook.hpp`: El Motor de Interceptación x86

Este encabezado define el mecanismo de bajo nivel para realizar hooks (interceptaciones) de funciones, lo cual es fundamental para el funcionamiento del SDK. Es estrictamente dependiente de la arquitectura x86 (32 bits).

- **`X86_Detour`**:
   - **Descripción:** Una clase que encapsula la lógica de sobrescribir el inicio de una función en la memoria con una instrucción de salto a una función de desvío.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mecanismo:** En x86, la instrucción de salto (`JMP`) relativa generalmente tiene 5 bytes: `0xE9` (opcode para JMP near, relative) seguido de 4 bytes que representan el desplazamiento (offset) de la dirección del objetivo en relación con la siguiente instrucción.
      - **Ejemplo de instrucción:** `E9 XX XX XX XX` (donde `XX` son los bytes del desplazamiento).
   - **`Apply(void* target, void* detour)`**:
      - **Acción:** Instala el hook. Primero, almacena los `JUMP_INSTRUCTION_SIZE` bytes originales de la función `target` (`original_bytes_`). Luego, calcula la dirección relativa del `detour` en relación con el `target` y sobrescribe el inicio de `target` con la instrucción `JMP`.
      - **Ejemplo del cálculo de la dirección relativa:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Dirección del desvío - (Dirección del objetivo + Tamaño de la instrucción de JMP)
         ```
   - **`Revert()`**:
      - **Acción:** Desinstala el hook, restaurando los `original_bytes_` en la función `target`.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mecanismo:** En Windows, usa `VirtualProtect`; en Linux, `mprotect`. Estas llamadas al sistema cambian los permisos de la página de memoria donde reside la función a `EXECUTE_READWRITE` (Windows) o `PROT_WRITE | PROT_EXEC` (Linux), permitiendo que el código sea modificado en tiempo de ejecución.
      - **Ejemplo (`Unprotect_Memory`):**
         ```cpp
         // Fragmento simplificado de function_hook.hpp
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
   - **Descripción:** Un envoltorio C++ `type-safe` para `X86_Detour`, asegurando que los tipos de puntero de función sean correctos.
   - `Install(void* target, void* detour)`: Encapsula la llamada `X86_Detour::Apply`.
   - `Uninstall()`: Encapsula la llamada `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Mecanismo de Seguridad (Guarda de Recursión):** Esta función es crítica para evitar bucles infinitos cuando el desvío necesita llamar a la función original. **Desinstala temporalmente el hook (`detour_.Revert()`)**, llama a la función original (`Get_Original()(args...)`), y luego **reinstala el hook (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Un contador que garantiza que el hook solo se reinstale cuando la llamada original de más alto nivel haya terminado, permitiendo llamadas recursivas seguras de la función original (si la función original es recursiva, por ejemplo). `thread_local` garantiza que `recursion_guard` esté aislado para cada hilo, lo cual es importante en entornos multihilo.
      - **Ejemplo (`Call_Original` con Scope_Guard):**
         ```cpp
         // Fragmento simplificado de function_hook.hpp
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

### 4.4. `interceptor_manager.hpp`: El Controlador de Hooks del AMX

Este `singleton` es el centro neurálgico de la interacción del SDK con la máquina virtual AMX de SA-MP. Coordina la instalación de los hooks proporcionados por `function_hook.hpp` en las funciones de la API AMX expuestas por el servidor, redirigiendo el flujo de ejecución a la lógica del SDK.

- **`Activate()` / `Deactivate()`**:
   - **Descripción:** Métodos públicos para instalar y desinstalar todos los hooks necesarios. Llamados en `OnLoad()` y `OnUnload()` de su plugin, respectivamente.
   - **Mecanismo:** Obtiene los punteros de las funciones AMX (como `amx_Register`, `amx_Exec`, etc.) usando `Core::Instance().Get_AMX_Export(...)` e instala los desvíos.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Función Hookeada:** `amx_Register`
   - **Propósito:** Intercepta el registro de *todas* las nativas (por SA-MP, otros plugins o gamemode).
   - **Acción:** Por cada nativa registrada, el `Interceptor_Manager` la añade a un caché interno (`Cache_Data::native_cache`).
   - **Impacto:** Este caché es fundamental para el rendimiento de `Pawn_Native`, permitiendo una búsqueda extremadamente rápida del puntero de la nativa en lugar de una búsqueda costosa en la AMX.
   - **Función adicional para `Plugin_Native_Hook`:** Este desvío *también* es responsable de modificar la lista de nativas antes de que se registren. Si una nativa tiene un `Plugin_Native_Hook` asociado, el puntero de la función en la lista de registro se reemplaza por el trampoline generado por el `Native_Hook_Manager`. Esto permite que su hook sea el primero en ser llamado.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Función Hookeada:** `amx_Exec`
   - **Propósito:** **Este es el hook más crítico.** Intercepta *cualquier* ejecución de código en la AMX, incluyendo la llamada de `publics` de Pawn.
   - **Mecanismo de Interceptación de `Plugin_Public`:**
      1. Cuando `amx_Exec` es llamado para una `public` (o `AMX_EXEC_MAIN`), se ejecuta el `Amx_Exec_Detour`.
      2. Obtiene el nombre de la `public` (usando `tl_public_name` que fue llenado por `Amx_Find_Public_Detour`).
      3. Consulta `Public_Dispatcher::Instance().Dispatch()` para verificar si hay handlers C++ registrados para este nombre.
      4. Si hay handlers, los ejecuta. `Public_Dispatcher` maneja el `marshalling` de los parámetros de la AMX a los tipos C++.
      5. Basándose en el valor de retorno de `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), decide si llama a la `amx_Exec` original (`Get_Amx_Exec_Hook().Call_Original(...)`) o si finaliza la ejecución de la `public` de Pawn.
      6. **Manipulación de la Pila:** Si la ejecución de la `public` de Pawn se interrumpe (`PLUGIN_PUBLIC_STOP`), el `Amx_Exec_Detour` corrige la pila de la AMX (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) para evitar inconsistencias.
   - **Activación de `Plugin_Native_Hook` (Parcheo de AMX):**
      - La primera vez que se ejecuta un `AMX*`, este desvío verifica si la AMX ya ha sido "parcheada" (`!manager.Is_Amx_Patched(amx)`).
      - Si no lo ha sido, recorre la tabla de nativas **de esa instancia AMX específica en la memoria**.
      - Por cada nativa que tiene un `Plugin_Native_Hook` registrado en `Native_Hook_Manager`, reemplaza la dirección de la nativa en la tabla por un trampoline generado por `Native_Hook_Manager`. La dirección original (o del hook anterior) se guarda en el objeto `Native_Hook`.
      - La AMX se marca entonces como "parcheada" para evitar un reprocesamiento innecesario.
   - **Ejemplo (`Amx_Exec_Detour` - con detalles de `Plugin_Native_Hook`):**
      ```cpp
      // Fragmento simplificado de interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          auto& manager = Interceptor_Manager::Instance();

          std::unique_ptr<std::string> public_name_ptr;

          // Lógica de interceptación de Plugin_Public (como se describió anteriormente)
          // ...

          int exec_result = Get_Amx_Exec_Hook().Call_Original(amx, retval, index);

          // Lógica de Parcheo para Plugin_Native_Hook
          if (SAMP_SDK_UNLIKELY(!manager.Is_Amx_Patched(amx))) {
              auto& hook_manager = Native_Hook_Manager::Instance();
              auto& hooks_to_apply = hook_manager.Get_All_Hooks();

              if (!hooks_to_apply.empty()) {
                  AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
                  AMX_FUNCSTUBNT* natives = reinterpret_cast<AMX_FUNCSTUBNT*>(reinterpret_cast<unsigned char*>(hdr) + hdr->natives);

                  int num_natives;

                  amx::Num_Natives(amx, &num_natives);

                  for (auto& hook_to_apply : hooks_to_apply) { // Recorre todos los Plugin_Native_Hook registrados
                      uint32_t hook_hash = hook_to_apply.Get_Hash();

                      for (int i = 0; i < num_natives; ++i) { // Recorre las nativas de la AMX
                          const char* native_name = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(hdr) + natives[i].nameofs);

                          if (FNV1a_Hash(native_name) == hook_hash) { // Si el nombre de la nativa de la AMX coincide con un hook
                              AMX_NATIVE current_func = reinterpret_cast<AMX_NATIVE>(natives[i].address);

                              hook_to_apply.Set_Next_In_Chain(current_func); // Guarda el puntero de la función original/anterior

                              AMX_NATIVE trampoline = hook_manager.Get_Trampoline(hook_hash); // Obtiene el trampoline para este hook

                              if (trampoline)
                                  natives[i].address = reinterpret_cast<ucell>(trampoline); // Reemplaza en la tabla de la AMX
                              
                              break;
                          }
                      }
                  }
              }
              
              manager.On_Amx_Patched(amx); // Marca la AMX como parcheada
          }
          
          return exec_result;
      }
      ```
- **`int SAMP_SDK_AMX_API Amx_Find_Public_Detour(...)`**:
   - **Función Hookeada:** `amx_FindPublic`
   - **Propósito:** Intercepta la búsqueda de `publics` por nombre.
   - **Mecanismo de "Ghost Publics":** Si `amx_FindPublic` original no encuentra una `public` en Pawn, pero `Public_Dispatcher` tiene un handler C++ registrado para ese nombre, este hook devuelve `AMX_ERR_NONE` y un `index` especial (`PLUGIN_EXEC_GHOST_PUBLIC`). Esto hace que la API de SA-MP "piense" que la `public` existe, permitiendo que la llamada `amx_Exec` subsiguiente (para este índice especial) sea interceptada por `Amx_Exec_Detour`, que luego redirige al handler C++.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Se utiliza para pasar el nombre de la `public` a `Amx_Exec_Detour` cuando se detecta una "public fantasma", ya que `amx_Exec` solo recibe el índice, no el nombre.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Funciones Hookeadas:** `amx_Init` / `amx_Cleanup`
   - **Propósito:** Administrar la lista de instancias `AMX*` activas.
   - **Acción:** `Amx_Init_Detour` llama a `Amx_Manager::Instance().Add_Amx()`, y `Amx_Cleanup_Detour` llama a `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Administrando Instancias `AMX*`

Este `singleton` mantiene un registro dinámico de todas las máquinas virtuales AMX actualmente cargadas en el servidor. Es esencial para funciones que necesitan interactuar con "todos los scripts" o encontrar un script específico.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Descripción:** Una lista de punteros a todas las instancias `AMX*` que han sido inicializadas (gamemode y filterscripts).
   - **Administración:** Poblada por los hooks `Amx_Init_Detour` y vaciada por `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Propósito:** Protege `loaded_amx_` contra el acceso concurrente en entornos multihilo (aunque SA-MP es principalmente monohilo, esta es una buena práctica de seguridad). `std::shared_mutex` permite múltiples lectores simultáneamente, pero solo un escritor.
- **`std::atomic<uint32_t> generation_`**:
   - **Propósito:** Un contador que se incrementa cada vez que se añade o elimina una AMX.
   - **Uso:** Lo utiliza `Caller_Cache` en `callbacks.hpp` para detectar cuándo ha cambiado la lista de AMXs, invalidando los cachés de búsqueda de `publics` y asegurando que las llamadas `Pawn_Public` operen siempre con información actualizada. Esto optimiza el rendimiento al evitar búsquedas repetitivas en un estado que no ha cambiado.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Descripción:** Recorre `loaded_amx_` (del más reciente al más antiguo, lo que generalmente coloca el gamemode o el filterscript más relevante primero) para encontrar la `public` con el nombre especificado.
   - **Mecanismo:** Usa `amx::Find_Public` para cada instancia `AMX*`.
   - **Impacto:** Es la base para `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: El Enrutador de Callbacks `Plugin_Public`

Este `singleton` es el componente que mapea nombres de `publics` de Pawn a sus funciones C++ `Plugin_Public`.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Clave:** El hash FNV1a del nombre de la `public` (ej: `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Valor:** Un `std::vector` de `std::function<cell(AMX*)>`, donde cada `std::function` es un handler C++ registrado para esa `public`.
   - **Mecanismo:** El `std::vector` permite que múltiples `Plugin_Public`s se registren para el mismo callback (ej: varios plugins queriendo interceptar `OnPlayerCommandText`). Los handlers se ejecutan en orden inverso de registro.
- **`Public_Register`**:
   - **Mecanismo:** Esta es una clase plantilla cuya macro `PLUGIN_PUBLIC_REGISTRATION` crea una instancia estática global. En el constructor estático (`static bool registered = [...]`), registra su handler `Plugin_Public` en el `Public_Dispatcher`. Este es un patrón de "registro estático en tiempo de compilación/inicialización".
   - **Ejemplo (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Register<decltype(&name), &name, hash_##name> register_##name;
      ```

- **`Public_Traits` y `Wrapper()`**:
   - **Mecanismo:** `Public_Traits` es un template de trait que, utilizando metaprogramación, genera una función `static cell Wrapper(AMX* amx)`.
   - **Propósito:** Esta `Wrapper` es la `Amx_Handler_Func` que el `Public_Dispatcher` realmente almacena y llama. Es responsable de:
      1. Llamar a `Public_Param_Reader::Get_Public_Params(amx, args...)` para extraer los parámetros de la pila de la AMX.
      2. Llamar a su función `Plugin_Public` C++ real (`func_ptr`) con los parámetros ya convertidos a los tipos C++ correctos.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Descripción:** Un conjunto de funciones plantilla recursivas que leen los valores de la pila de la AMX y los convierten a los tipos C++ especificados en la declaración de `Plugin_Public`.
   - **Mecanismo:** Usa `Get_Stack_Cell()` para acceder a las `cell`s en la pila. Utiliza `if constexpr` (C++17+) o `std::is_same<T>::value` (C++14) para aplicar la conversión correcta (`amx::AMX_CTOF` para float, `Samp_SDK::Get_String` para string, cast directo para int).

### 4.7. `native.hpp`: Administrando y Llamando Nativas del Plugin

Este encabezado está dedicado a la creación y gestión de nativas C++ que su plugin expone a Pawn.

- **`Native_List_Holder`**:
   - **Descripción:** Un `singleton` global que almacena todas las `Plugin_Native`s declaradas en su plugin (de todos los archivos `.cpp` que usan `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Contiene objetos `Native` (que almacenan el nombre de la nativa y el puntero a la función C++ `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Un mapa optimizado por hash para búsquedas rápidas de `Plugin_Native`s internas (usado por `Plugin_Call`).
- **`Native_Register`**:
   - **Mecanismo:** Al igual que `Public_Register`, esta es una clase plantilla cuya macro `Plugin_Native` crea una instancia estática global. En su constructor, añade la nativa a `Native_List_Holder`.
   - **Impacto:** Le permite declarar `Plugin_Native`s en múltiples archivos `.cpp` sin preocuparse por el registro manual. Todas se recopilarán automáticamente.
- **`Native_Registry`**:
   - **Descripción:** Una clase auxiliar que, en `OnAmxLoad`, toma la lista completa de `Native`s de `Native_List_Holder` y las formatea en un array `AMX_NATIVE_INFO`.
   - **Mecanismo:** Llama a `amx::Register(amx, amx_natives_info_.data(), -1)` para registrar todas sus nativas en la instancia AMX que acaba de cargarse.
- **`Plugin_Call_Impl(...)`**:
   - **Descripción:** La implementación subyacente de la macro `Plugin_Call`.
   - **Mecanismo:** Utiliza `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` para obtener directamente el puntero de la función C++.
   - **Entorno:** Ejecuta la nativa en un entorno `Amx_Sandbox` (aislado) para gestionar la pila y el heap temporales, de forma similar a cómo funciona `Pawn_Native`.

### 4.8. `native_hook_manager.hpp`: El Motor de Hooks de Natives

Este es el robusto sistema de hooking de nativas, diseñado para gestionar el encadenamiento de hooks de múltiples plugins para la misma native.

- **`Native_Hook`**:
   - **Descripción:** Una clase que representa un único hook de native. Almacena el hash del nombre de la native, la función handler C++ proporcionada por el usuario (`user_handler_`) y un `std::atomic<AMX_NATIVE> next_in_chain_`.
   - **`user_handler_`**: Su función `Plugin_Native_Hook` C++.
   - **`next_in_chain_`**: El puntero a la native original o al hook de un plugin con prioridad más baja. Es un `std::atomic` para garantizar thread-safety en lectura/escritura.
   - **`Dispatch(AMX* amx, cell* params)`**: Llamada por el trampoline para ejecutar su `user_handler_`.
   - **`Call_Original(AMX* amx, cell* params)`**: Método crucial que llama `next_in_chain_`, permitiendo que su hook invoque la funcionalidad original o el siguiente hook en la cadena.
- **`Trampoline_Allocator`**:
   - **Descripción:** Una clase responsable de asignar bloques de memoria ejecutable y generar el código assembly "trampoline" en esos bloques.
   - **`Generate_Trampoline_Code(unsigned char* memory, int hook_id)`**: Escribe 10 bytes de assembly:
      1. `B8 XX XX XX XX`: `MOV EAX, hook_id` (coloca el ID único del hook en el registro EAX).
      2. `E9 XX XX XX XX`: `JMP relative_address_to_Dispatch_Wrapper_Asm` (salta a la función de despacho genérica del SDK).
   - **`Allocation_Size = 4096`**: Asigna memoria en páginas para eficiencia y alineación de cache.
   - **Permisos de Memoria:** Usa `VirtualAlloc` (Windows) o `mmap` (Linux) con permisos `EXECUTE_READWRITE` para garantizar que el código generado pueda ser ejecutado.
- **`Dispatch_Wrapper_Asm()`**:
   - **Descripción:** Una pequeña función en assembly (definida con `__declspec(naked)` o `asm volatile`) que sirve como el destino de todos los trampolines.
   - **Acción:** Salva los registros, mueve `EAX` (que contiene el `hook_id`) a la stack, y llama la función `Dispatch_Hook` en C++. Después del retorno de `Dispatch_Hook`, restaura los registros y retorna.
- **`cell SAMP_SDK_CDECL Dispatch_Hook(int hook_id, AMX* amx, cell* params)`**:
   - **Descripción:** La función C++ genérica llamada por `Dispatch_Wrapper_Asm`.
   - **Acción:** Usa `hook_id` para encontrar el `Native_Hook` correspondiente en el `Native_Hook_Manager` y llama su método `Dispatch()`, que a su vez invoca el handler `Plugin_Native_Hook` del usuario.
   - **Consideraciones de Linkagem:** Esta función es un punto crítico de interoperabilidad entre C++ y assembly. Para garantizar que sea correctamente exportada y encontrada por el linker en Linux (GCC/Clang), es definida con tres características importantes:
      1. **`extern "C"`**: Impide el C++ Name Mangling, garantizando que el símbolo tenga el nombre C puro `Dispatch_Hook`, que es lo que busca el código assembly.
      2. **`inline`**: Permite que la definición de la función resida en el archivo de encabezado (necesario para una biblioteca header-only) sin causar errores de "definición múltiple" (ODR - One Definition Rule).
      3. **`SAMP_SDK_USED_BY_ASM` (`__attribute__((used))` en GCC/Clang)**: Fuerza al compilador a emitir el código para la función, incluso si no encuentra ninguna llamada a ella a partir de otro código C++. Esto evita que el optimizador la elimine por error.
- **`Native_Hook_Manager`**:
   - **Descripción:** El `singleton` central que gestiona todos los `Native_Hook`s registrados y sus trampolines.
   - **`std::list<Native_Hook> hooks_`**: Almacena la lista de hooks en orden.
   - **`std::unordered_map<uint32_t, Trampoline_Func> hash_to_trampoline_`**: Mapea el hash del nombre de la native al puntero del trampoline generado.
   - **`std::vector<uint32_t> hook_id_to_hash_`**: Mapea el ID entero del hook (usado en el trampoline) de vuelta al hash del nombre de la native.
   - **`Get_Trampoline(uint32_t hash)`**: Retorna (o crea y asigna) un puntero de trampoline para un determinado hash de native.
- **`PLUGIN_NATIVE_HOOK_REGISTRATION`**:
   - **Mecanismo:** Una macro que crea una clase estática global (`Native_Hook_Register_##name`) para cada `Plugin_Native_Hook`. En el constructor estático de esa clase, registra el `handler` del usuario en el `Native_Hook_Manager`.

### 4.9. `callbacks.hpp` & `amx_memory.hpp`: Llamadas C++ -> Pawn y RAII

Estos encabezados forman la columna vertebral para llamar a funciones de Pawn desde C++ (macros `Pawn_*`) y garantizan la seguridad de la memoria.

- **`Amx_Sandbox`**:
   - **Descripción:** Una estructura `thread_local` que simula un entorno `AMX` minimalista y aislado para llamadas `Pawn_Native` y `Plugin_Call`.
   - **Mecanismo:** Posee su propia estructura `AMX`, `AMX_HEADER` y un `std::vector<unsigned char> heap` para simular la memoria de un script. Esto permite que `amx::Push`, `amx::Allot`, etc., se llamen sin interferir con el estado de los scripts Pawn reales en ejecución.
   - **`thread_local`:** Garantiza que cada hilo tenga su propio `Amx_Sandbox`, previniendo condiciones de carrera si el SDK se usa en un contexto multi-hilo (ej: un futuro pool de hilos para operaciones no-Pawn).
   - **Ejemplo (`Amx_Sandbox`):**
      ```cpp
      // Fragmento simplificado de callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Memoria simulada para stack/heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Inicializa la AMX y la cabecera
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
   - **Descripción:** Un conjunto de funciones plantilla sobrecargadas que gestiona el `marshalling` de *cada* parámetro C++ al formato `cell` esperado por la AMX, y viceversa para los parámetros de salida.
   - **Procesamiento de Entrada:**
       - Para `int`, `float`, `bool`: Convierte directamente a `cell`.
       - Para `const char*`, `std::string`: Asigna memoria en el heap de `Amx_Sandbox` (o AMX real para `Pawn_Public`), copia la string y empuja la dirección AMX a la pila.
   - **Procesamiento de Salida (`is_output_arg`):**
       - **Mecanismo:** Cuando un argumento es una referencia de l-value no-const (detectado por el trait `is_output_arg`), `Parameter_Processor` no empuja el valor, sino una *dirección AMX* a una `cell` asignada temporalmente en el heap.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Después de la llamada a la nativa de Pawn, se ejecuta una lista de lambdas (`post_call_updaters`). Cada lambda es responsable de leer el valor final de la `cell` asignada en la AMX y asignárselo de nuevo a la variable C++ original (ej: `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mecanismo:** Un `std::integral_constant` (trait de tipo) que, en tiempo de compilación, evalúa si un tipo de parámetro C++ es una referencia modificable (ej: `int&`, `float&`, `std::string&`). Esto permite que el `Parameter_Processor` diferencie los parámetros de entrada de los de salida.
   - **Ejemplo (`is_output_arg`):**
      ```cpp
      // Fragmento simplificado de callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Descripción:** Una clase RAII (`Resource Acquisition Is Initialization`) que encapsula la asignación y desasignación de memoria en la AMX.
   - **Mecanismo:** En el constructor, llama a `amx::Allot` para obtener una `amx_addr` y una `phys_addr`. En el destructor, llama a `amx::Release` para liberar esa memoria.
   - **Impacto:** **Crucial para prevenir fugas de memoria en el heap de la AMX.** Garantiza que la memoria temporal utilizada para strings o parámetros de salida siempre se libere, incluso si ocurren excepciones o retornos anticipados.

### 4.10. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Acceso Abstraído a la AMX

Estos encabezados proporcionan las definiciones fundamentales y las herramientas de alto nivel para interactuar con Pawn.

- **`amx_defs.h`**:
   - **Contenido:** Contiene las definiciones brutas de las estructuras de la AMX (`AMX`, `AMX_HEADER`), tipos (`cell`, `ucell`) y enums de error (`AmxError`). También define `AMX_NATIVE` y `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Utiliza atributos de empaquetado (`#pragma pack(push, 1)` / `__attribute__((packed))`) para garantizar que las estructuras de la AMX tengan el diseño de memoria correcto, fundamental para la interoperabilidad.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Descripción:** La función plantilla principal para invocar las funciones de la API AMX expuestas por el servidor.
   - **Mecanismo:** Obtiene el puntero de la función a través de `Core::Instance().Get_AMX_Export(Index)` y lo llama. Centraliza el tratamiento de errores si el puntero de la función no está disponible.
   - **Impacto:** Convierte llamadas de bajo nivel (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) en llamadas C++ idiomáticas y type-safe (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Descripción:** Funciones esenciales para convertir valores `cell` a `float` y viceversa, realizando una reinterpretación bit a bit de la memoria.
   - **`static_assert`:** Incluyen `static_assert` para garantizar que `sizeof(cell) == sizeof(float)` en tiempo de compilación, previniendo errores en plataformas con tamaños de tipo diferentes.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Descripción:** Un asistente para convertir una dirección AMX de string en `std::string`.
   - **Mecanismo:** Primero, obtiene la dirección física (`cell* phys_addr`) de la string en la AMX usando `amx::Get_Addr`. Luego, usa `amx::STR_Len` para determinar la longitud y `amx::Get_String` para copiar los bytes a un `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Descripción:** La función base de formato de strings (estilo `printf`) para el SDK.
   - **Mecanismo:** Utiliza `vsnprintf` en dos pasadas: primero para determinar el tamaño necesario de la string, y luego para formatear la string en el `std::string` asignado dinámicamente. Esto evita desbordamientos de búfer.

## 5. Compilación y Despliegue

### Requisitos de Arquitectura y Plataforma

- Su plugin **DEBE** ser compilado para la arquitectura **x86 (32-bit)**.
- Plataformas Soportadas: Windows (.dll) y Linux (.so).

### Ejemplos de Comandos de Compilación

#### **MSVC (Visual Studio)**

1. Cree un nuevo proyecto de "Dynamic-Link Library (DLL)".
2. En las configuraciones del proyecto, defina la "Plataforma de Solución" a **x86**.
3. Asegúrese de que el estándar del lenguaje C++ sea al menos C++14.

#### **GCC / Clang (Linux)**

```bash
# Para un plugin llamado 'my_plugin.so' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compila para 32-bit.
- `-shared`: Crea una biblioteca compartida (`.so`).
- `-std=c++17`: Define el estándar C++ a C++17 (puede ser `c++14` o `c++20`).
- `-O2`: Nivel de optimización 2.
- `-fPIC`: Genera código independiente de la posición, necesario para bibliotecas compartidas.
- `-Wall -Wextra`: Activa advertencias adicionales para ayudar a detectar errores.
- `-Wl,--no-undefined`: Impide la creación de la biblioteca si hay símbolos indefinidos.

#### **GCC / Clang (MinGW en Windows)**

```bash
# Para un plugin llamado 'my_plugin.dll' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Enlaza la biblioteca estándar C++ estáticamente. Es esencial para evitar que su plugin dependa de DLLs de tiempo de ejecución específicas del compilador que podrían no estar presentes en el sistema del usuario.
- `-static-libgcc`: Enlaza la biblioteca GCC estáticamente.

### Consideraciones para la Distribución

- **Nombre del Archivo:** Su plugin debe tener la extensión `.dll` (Windows) o `.so` (Linux). Ej: `my_plugin.dll`.
- **Ubicación:** Coloque el archivo compilado en la carpeta `plugins/` de su servidor SA-MP.
- **server.cfg:** Agregue el nombre de su plugin (si es Windows, sin la extensión) a la línea `plugins` en `server.cfg`.
   ```
   plugins my_plugin (si es Linux, my_plugin.so)
   ```

## Licencia

Copyright © **SA-MP Programming Community**

Este software está licenciado bajo los términos de la Licencia MIT ("Licencia"); puede utilizar este software de acuerdo con las condiciones de la Licencia. Puede obtener una copia de la Licencia en: [MIT License](https://opensource.org/licenses/MIT)

### Términos y Condiciones de Uso

#### 1. Permisos Otorgados

La presente licencia otorga, gratuitamente, a cualquier persona que obtenga una copia de este software y archivos de documentación asociados, los siguientes derechos:
* Usar, copiar, modificar, fusionar, publicar, distribuir, sublicenciar y/o vender copias del software sin restricciones
* Permitir que las personas a las que se les proporciona el software hagan lo mismo, sujeto a las siguientes condiciones

#### 2. Condiciones Obligatorias

Todas las copias o partes sustanciales del software deben incluir:
* El aviso de derechos de autor anterior
* Este aviso de permiso
* El aviso de exención de responsabilidad a continuación

#### 3. Derechos de Autor

El software y toda la documentación asociada están protegidos por leyes de derechos de autor. La **SA-MP Programming Community** mantiene la titularidad de los derechos de autor originales del software.

#### 4. Exención de Garantías y Limitación de Responsabilidad

EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN.

EN NINGÚN CASO LOS AUTORES O TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE CUALQUIER RECLAMACIÓN, DAÑOS U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE OTRO MODO, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTROS TRATOS EN EL SOFTWARE.

---

Para información detallada sobre la Licencia MIT, consulte: https://opensource.org/licenses/MIT