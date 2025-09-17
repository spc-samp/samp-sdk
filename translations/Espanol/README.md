# SAMP SDK

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

- [SAMP SDK](#samp-sdk)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [1. Introducción y Filosofía de Diseño](#1-introducción-y-filosofía-de-diseño)
    - [El Problema con la API C Estándar de SA-MP](#el-problema-con-la-api-c-estándar-de-sa-mp)
    - [La Solución del SAMP SDK: Abstracción con Seguridad y Performance](#la-solución-del-samp-sdk-abstracción-con-seguridad-y-performance)
    - [Modelo Header-Only: Ventajas e Implicaciones](#modelo-header-only-ventajas-e-implicaciones)
  - [2. Configuración y Ambiente](#2-configuración-y-ambiente)
    - [Requisitos de Compilación](#requisitos-de-compilación)
    - [Estructura de Archivos Recomendada](#estructura-de-archivos-recomendada)
    - [Macros Esenciales de Configuración\*\*](#macros-esenciales-de-configuración)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definiciones y Constantes del SA-MP (`samp_defs.hpp`)](#definiciones-y-constantes-del-sa-mp-samp_defshpp)
  - [3. Guía de Uso Abrangente de la API](#3-guía-de-uso-abrangente-de-la-api)
    - [3.1. El Ciclo de Vida del Plugin](#31-el-ciclo-de-vida-del-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Interceptando Eventos del Pawn](#32-plugin_public-interceptando-eventos-del-pawn)
      - [Sintaxis y Declaración](#sintaxis-y-declaración)
      - [Marshalling Automático de Parámetros](#marshalling-automático-de-parámetros)
      - [Control de Flujo: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#control-de-flujo-plugin_public_continue-vs-plugin_public_stop)
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
    - [3.4. `Pawn_*` Macros: Llamando Funciones del Pawn a Partir de C++](#34-pawn_-macros-llamando-funciones-del-pawn-a-partir-de-c)
      - [`Pawn_Native(NomeDaNativa, ...)`](#pawn_nativenomedanativa-)
      - [`Pawn_Public(NomeDaPublic, ...)`](#pawn_publicnomedapublic-)
      - [`Pawn(NomeDaFuncao, ...)`](#pawnnomedafuncao-)
      - [Sintaxis y Convenciones](#sintaxis-y-convenciones)
      - [Marshalling de Parámetros de Entrada](#marshalling-de-parámetros-de-entrada)
      - [Marshalling de Parámetros de Salida (Referencias: `int&`, `float&`, `std::string&`)](#marshalling-de-parámetros-de-salida-referencias-int-float-stdstring)
      - [El Objeto `Callback_Result`: Análisis Completo](#el-objeto-callback_result-análisis-completo)
      - [**3.5. `Plugin_Module`: Gestión de Módulos Dinámicos**](#35-plugin_module-gestión-de-módulos-dinámicos)
      - [Sintaxis y Propósito](#sintaxis-y-propósito)
      - [Ciclo de Vida de un Módulo](#ciclo-de-vida-de-un-módulo)
      - [Beneficios de la Modularización](#beneficios-de-la-modularización)
    - [3.6. `Plugin_Call`: Llamando Nativas Internas del Plugin](#36-plugin_call-llamando-nativas-internas-del-plugin)
      - [Sintaxis y Ventajas de Performance](#sintaxis-y-ventajas-de-performance)
    - [**3.7. Funciones Utilitarias del SDK**](#37-funciones-utilitarias-del-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Recomendado)](#stdstring-plugin_formatconst-char-format--recomendado)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Detalle de Implementación)](#stdstring-samp_sdkformatconst-char-format--detalle-de-implementación)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. **Anatomía Interna y Arquitectura del SDK**](#4-anatomía-interna-y-arquitectura-del-sdk)
    - [4.1. `core.hpp`: La Fundación Minimalista](#41-corehpp-la-fundación-minimalista)
    - [**4.2. `platform.hpp` y `version.hpp`: Compatibilidad y Metadatos**](#42-platformhpp-y-versionhpp-compatibilidad-y-metadatos)
    - [4.3. `function_hook.hpp`: El Motor de Interceptación x86](#43-function_hookhpp-el-motor-de-interceptación-x86)
    - [4.4. `interceptor_manager.hpp`: El Controlador de Hooks del AMX](#44-interceptor_managerhpp-el-controlador-de-hooks-del-amx)
    - [4.5. `amx_manager.hpp`: Gestionando Instancias `AMX*`](#45-amx_managerhpp-gestionando-instancias-amx)
    - [4.6. `public_dispatcher.hpp`: El Enrutador de Callbacks `Plugin_Public`](#46-public_dispatcherhpp-el-enrutador-de-callbacks-plugin_public)
    - [4.7. `native.hpp`: Gestionando y Llamando Nativas del Plugin](#47-nativehpp-gestionando-y-llamando-nativas-del-plugin)
    - [4.8. `callbacks.hpp` \& `amx_memory.hpp`: Llamadas C++ -\> Pawn y RAII](#48-callbackshpp--amx_memoryhpp-llamadas-c---pawn-y-raii)
    - [4.9. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Acceso Abstraído a la AMX](#49-amx_apihpp--amx_helpershpp--amx_defsh-acceso-abstraído-a-la-amx)
  - [5. Compilación y Deploy](#5-compilación-y-deploy)
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
- **Gestión Manual de Memoria:** Funciones como `amx_Allot` y `amx_Release` exigen que el desarrollador asigne y desasigne explícitamente la memoria en la heap de la AMX. Esto es una fuente común de fugas de memoria y fallos de runtime.
- **Tipado Débil y Conversiones Manuales:** Los parámetros se pasan como un array de `cell`s, forzando conversiones explícitas (y muchas veces inseguras) entre `cell`, `int`, `float`, y `char*`.
- **Verbosidad y Boilerplate:** Extraer múltiples parámetros de un array `cell* params`, lidiar con tamaños de strings, y gestionar la stack de la AMX para llamadas de retorno C++ a Pawn exige código repetitivo.
- **Fragilidad de la Interfaz:** La falta de verificación en tiempo de compilación (type safety) significa que los errores en la pasada de parámetros o tipos pueden pasar desapercibidos hasta la ejecución, causando crashes o comportamientos indefinidos.

### La Solución del SAMP SDK: Abstracción con Seguridad y Performance

El SAMP SDK aborda estos problemas proporcionando una poderosa capa de abstracción en C++:
- **RAII (Resource Acquisition Is Initialization):** Gestión automática de memoria en la AMX. `Amx_Scoped_Memory` garantiza que la memoria asignada sea liberada.
- **Seguridad de Tipos:** Conversión automática y segura de parámetros entre C++ y Pawn. Usted maneja `int`, `float`, `std::string` directamente.
- **Sintaxis Concisa e Idiomática:** Macros y plantillas proporcionan una API limpia que se asemeja más al C++ moderno que a la API C tradicional.
- **Interceptación Robusta:** Un motor de hooking avanzado permite la interceptación transparente de callbacks del Pawn (`Plugin_Public`) y el registro dinámico de nativas.
- **Alto Rendimiento:** Uso extensivo de hashing en tiempo de compilación (FNV1a), caché de funciones y optimizaciones de `thread_local` para minimizar la sobrecarga de las abstracciones.

### Modelo Header-Only: Ventajas e Implicaciones

El SDK está compuesto exclusivamente por archivos de cabecera (`.hpp`, `.h`).
- **Ventajas:**
   - **Integración Simplificada:** No hay bibliotecas para construir, vincular o distribuir. Basta con incluir los headers.
   - **Optimizaciones del Compilador:** El compilador tiene visibilidad completa del código del SDK y de su plugin, permitiendo inlining agresivo y optimizaciones en tiempo de enlazado, lo que puede resultar en binarios más rápidos.
- **Implicaciones:**
   - **Tiempo de Compilación:** Para proyectos muy grandes, la compilación puede llevar más tiempo debido a la inclusión repetida del código del SDK. Esto se mitiga con guardas de inclusión y por la naturaleza de "incluir solo lo que es necesario" de C++.
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
meu_plugin/
├── samp-sdk/
│   ├── // Outros arquivos do SDK
│   └── samp_sdk.hpp             // O principal header a ser incluído
│
├── src/
│   ├── main.cpp                  // Onde SAMP_SDK_IMPLEMENTATION é definido
│   └── my_custom_logic.cpp       // Opcional, para organizar código
│
└── CMakeLists.txt (ou .vcxproj, Makefile)
```

### Macros Esenciales de Configuración**

Siempre defina estas macros *antes* de incluir `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Propósito:** Señala al compilador que este archivo `.cpp` debe generar las implementaciones de las funciones de exportación del plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **El SDK se encarga de la exportación de estas funciones automáticamente, eliminando la necesidad de archivos `.def` (en Windows) o declaraciones `__attribute__((visibility("default")))` (en Linux) para estas funciones.**
- **Impacto Técnico:** Sin esta macro, el enlazador no encontrará las exportaciones necesarias, y el servidor SA-MP no podrá cargar su plugin.
- **Regla Fundamental:** **Defina esta macro en SOLO UN archivo `.cpp` en todo su proyecto.** Definirla en más de un archivo causará un error de enlazado de "símbolo duplicado".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // A macro faz o SDK exportar as funções necessárias automaticamente.
#include "samp-sdk/samp_sdk.hpp"

// ... seu código de plugin ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Propósito:** Habilita las funcionalidades del SDK relacionadas con la interacción con el entorno de la AMX (máquina virtual de Pawn).
- **Funcionalidades Activadas:**
   - Declaración y registro de nativas C++ usando `Plugin_Native`.
   - Callbacks `OnAmxLoad(AMX* amx)` y `OnAmxUnload(AMX* amx)`.
   - La macro `Plugin_Call` para invocar nativas del propio plugin.
- **Impacto Técnico:** Cuando esta macro se define, el SDK recolecta automáticamente todas sus `Plugin_Native`s. En la función `Supports()`, la flag `SUPPORTS_AMX_NATIVES` se añade automáticamente.
- **Flexibilidad:** **Puede definir esta macro en múltiples archivos `.cpp`**. El sistema de registro estático del SDK (`Native_Registrar`) consolidará todas las nativas de diferentes unidades de compilación en una única lista global.

```cpp
// my_natives.cpp (pode ser um arquivo separado do main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Apenas para habilitar Plugin_Native
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
    // Lógica executada a cada "tick" do servidor (ex: 20ms)
    // Cuidado com operações pesadas aqui!
}
```

### Definiciones y Constantes del SA-MP (`samp_defs.hpp`)

Este archivo proporciona todas las constantes y límites conocidos del SA-MP, como `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. Se incluye automáticamente por `samp_sdk.hpp` y debe usarse para garantizar la compatibilidad y legibilidad del código.

## 3. Guía de Uso Abrangente de la API

### 3.1. El Ciclo de Vida del Plugin

Las siguientes funciones son los puntos de entrada y salida de su plugin, exportadas automáticamente por el SDK.

#### `bool OnLoad()`

- **Descripción:** Primera función llamada por el servidor SA-MP después de la carga exitosa de su plugin en memoria.
- **Uso:** Ideal para inicializar cualquier sistema, cargar configuraciones, abrir conexiones con bases de datos o cargar módulos (`Plugin_Module`).
- **Retorno:**
   - `true`: El plugin se inicializó con éxito y la carga continúa.
   - `false`: El plugin falló al inicializar. La carga se abortará y el plugin se descargará.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Inicializando MeuPlugin v1.0...");

    // Exemplo: Carregar um módulo (mais detalhes na seção 3.5)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Módulo de Banco de Dados carregado.")) {
        Samp_SDK::Log("ERRO: Falha ao carregar o módulo de banco de dados!");

        return false; // Aborta o carregamento do plugin principal
    }

    return true;
}
```

#### `void OnUnload()`

- **Descripción:** Última función llamada por el servidor SA-MP antes de descargar su plugin de la memoria.
- **Uso:** Ideal para limpiar recursos, cerrar conexiones, guardar estados y asegurar que no se filtren recursos. El SDK gestiona la descarga de módulos (`Plugin_Module`) automáticamente.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MeuPlugin descarregado. Liberando recursos...");
    // Nenhuma ação manual é necessária para módulos carregados via Plugin_Module;
    // o SDK cuida disso.
}
```

#### `unsigned int GetSupportFlags()`

- **Descripción:** Informa al servidor SA-MP qué recursos soporta y desea usar su plugin.
- **Uso:** **Siempre devuelva `SUPPORTS_VERSION` (o `SAMP_PLUGIN_VERSION`).** Las otras flags (`SUPPORTS_AMX_NATIVES`, `SUPPORTS_PROCESS_TICK`) son añadidas automáticamente por el SDK si las macros `SAMP_SDK_WANT_AMX_EVENTS` y `SAMP_SDK_WANT_PROCESS_TICK` están definidas. Esto simplifica el mantenimiento y evita errores.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // O SDK adiciona as flags necessárias automaticamente.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requiere:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descripción:** Se llama siempre que se carga e inicializa un nuevo script Pawn (un Gamemode o Filterscript) en el servidor.
- **Uso:** Si necesita lógica específica para cada script AMX, como registrar nativas personalizadas (aunque `Plugin_Native` lo hace automáticamente), o inicializar datos específicos por script.

```cpp
// main.cpp (com SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxLoad(AMX* amx) {
    // amx representa a nova instância do script carregado.
    // Você pode, por exemplo, chamar uma public específica neste script:
    // Pawn_Public_OnAmx("OnMyPluginLoaded", amx); // Exemplo hipotético de uma API mais avançada.
    Samp_SDK::Log("Script AMX carregado: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Requiere:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descripción:** Se llama cuando un script Pawn se descarga del servidor.
- **Uso:** Para limpiar cualquier recurso específico que haya asignado o asociado a ese `AMX*` en particular.

```cpp
// main.cpp (com SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX descarregado: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requiere:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Descripción:** Se llama repetidamente en cada "tick" del servidor (generalmente 20 veces por segundo, o cada 50ms).
- **Uso:** Para lógica de fondo continua, temporizadores, actualizaciones de estado que no dependen de eventos de jugador, o sincronización de datos.
- **Cuidado:** Evite operaciones de bloqueo o computacionalmente pesadas aquí, ya que pueden causar lag en el servidor.

```cpp
// main.cpp (com SAMP_SDK_WANT_PROCESS_TICK definido)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // A cada 10 segundos (20 ticks/seg * 10 seg = 200 ticks)
        Samp_SDK::Log("Servidor ativo por %d segundos.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Interceptando Eventos del Pawn

La macro `Plugin_Public` es el puente principal para recibir callbacks del Pawn en su código C++.

#### Sintaxis y Declaración

- `Plugin_Public(NomeDaPublic, Tipo1 Param1, Tipo2 Param2, ...)`
- El nombre de la función C++ que usted declara **debe ser el mismo** del callback Pawn (ej: `OnPlayerConnect`).
- Los tipos de parámetros C++ (`int`, `float`, `std::string`) son automáticamente convertidos por el SDK.

```cpp
// Intercepta OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    // ...
}
```

#### Marshalling Automático de Parámetros

El SDK automáticamente maneja la lectura de la `cell stack` de la AMX y la conversión a los tipos C++ especificados:
- `int`: Convertido directamente de `cell`.
- `float`: Convertido de `cell` usando `amx::AMX_CTOF`.
- `std::string`: El SDK lee la dirección de la string en la AMX, asigna un `std::string` en C++ y copia el contenido.

#### Control de Flujo: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

El valor devuelto por su función `Plugin_Public` es crucial y determina el flujo de ejecución del callback:
- `return PLUGIN_PUBLIC_CONTINUE;` (valor `1`): Indica que la ejecución del callback debe **continuar**. Si hay otros plugins que también interceptan este callback, serán llamados. Luego, la `public` original en el script Pawn será invocada.
- `return PLUGIN_PUBLIC_STOP;` (valor `0`): Indica que la ejecución del callback debe ser **interrumpida**. Ningún otro plugin o la `public` original en el script Pawn será invocado para este evento. Esto es ideal para implementar un sistema que "sobrescribe" o "bloquea" un comportamiento estándar de SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Congela o jogador
        Pawn_Native(SendClientMessage, playerid, -1, Pawn_Format("Jogador %d congelado.", playerid));

        return PLUGIN_PUBLIC_STOP; // Impede que o comando seja processado por outros scripts.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Permite que outros comandos sejam processados.
}
```

### 3.3. `Plugin_Native`: Creando Funciones Nativas en C++

`Plugin_Native` le permite extender la funcionalidad de Pawn con código C++ de alto rendimiento.

#### Sintaxis y Firma Fija

- `Plugin_Native(NomeDaNativa, AMX* amx, cell* params)`
- La función C++ debe tener exactamente esta firma: `cell NomeDaNativa(AMX* amx, cell* params)`.
- `NomeDaNativa` es el nombre que usarán los scripts Pawn.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementação ...
    return 0;
}
```

#### Registro Automático de Nativas

> [!NOTE]
> Usted **no necesita** llamar a `amx_Register` manualmente. El SDK detecta todas sus `Plugin_Native`s (en cualquier archivo `.cpp` con `SAMP_SDK_WANT_AMX_EVENTS`) y las registra automáticamente en cada script AMX cargado (`OnAmxLoad`).

#### Extracción de Parámetros: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Descripción:** Un ayudante más simple para extraer múltiples parámetros secuencialmente.
- **Uso:** `Register_Parameters(variable1, variable2, ...)`
- **Limitaciones:** Para parámetros de entrada. No maneja parámetros opcionales o acceso por índice.
- **Tipos Soportados:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extrai os 3 parâmetros
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)

- **Descripción:** Una clase envoltorio que proporciona una interfaz orientada a objetos para acceder a los parámetros de una nativa. Más potente para escenarios complejos.
- **Construcción:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Descripción:** Retorna el número de parámetros pasados a la nativa.
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
- **Uso:** Para leer valores que fueron pasados por referencia de Pawn.
- **Retorno:** `true` si la dirección AMX es válida, `false` en caso contrario.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Obtém os valores das referências (o Pawn passou endereços)
    p.Get_REF(1, health); // Lê o valor de Float:health
    p.Get_REF(2, money);   // Lê o valor de money
    
    Samp_SDK::Log("Jogador %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Agora, modifique-os
    health = 50.0f;
    money += 100;
    
    // E os escreve de volta na memória do Pawn
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Descripción:** Retorna un `std::optional<T>` para leer un parámetro de referencia. Más seguro para C++17 y superior.

###### `p.Set_REF<T>(size_t index, T value)`

- **Descripción:** Escribe un valor `T` en un parámetro de **referencia** Pawn (la dirección que Pawn pasó).
- **Uso:** Para modificar valores que fueron pasados por referencia, haciendo que Pawn vea la alteración.
- **Retorno:** `true` si la escritura fue exitosa, `false` en caso contrario.

#### Retorno de Valores

- Su función `Plugin_Native` debe retornar una `cell`.
- Para retornar un `int` o `bool`, use un cast a `cell`.
- Para retornar un `float`, use `amx::AMX_FTOC(mi_float)`.

```cpp
// Retorna um bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    int playerid = p.Get<int>(0);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Retorna um float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Retorna 100.0f
}
```

### 3.4. `Pawn_*` Macros: Llamando Funciones del Pawn a Partir de C++

Estas macros son lo inverso de `Plugin_Public` y `Plugin_Native`: permiten que su código C++ invoque funciones Pawn.

#### `Pawn_Native(NomeDaNativa, ...)`

- **Propósito:** La forma recomendada de llamar a funciones nativas de SA-MP (o de otros plugins) desde C++.
- **Mecanismo:** Busca el puntero de la nativa en la caché interna del SDK (rellenada por `Amx_Register_Detour`). Si se encuentra, ejecuta la nativa en un entorno `Amx_Sandbox` (una instancia AMX falsa y aislada).
- **Rendimiento:** La más eficiente, ya que evita la costosa búsqueda de `publics` e interactúa directamente con el puntero de la nativa.

#### `Pawn_Public(NomeDaPublic, ...)`

- **Propósito:** Llama a una función pública específica en un script Pawn.
- **Mecanismo:** Recorre las instancias `AMX*` gestionadas por el `Amx_Manager`, busca la `public` por su nombre y la ejecuta.
- **Rendimiento:** Menos eficiente que `Pawn_Native` debido a la búsqueda y al `amx_Exec` real. Generalmente, las `publics` son más lentas que las `natives`.
- **Uso:** Ideal para invocar eventos personalizados en su Gamemode/Filterscripts que no son nativas.

#### `Pawn(NomeDaFuncao, ...)`

- **Propósito:** Una macro de conveniencia que intenta adivinar si la función es una nativa o una pública.
- **Mecanismo:** Primero, intenta llamar como `Pawn_Native`. Si falla (no se encuentra la nativa), intenta llamar como `Pawn_Public`.
- **Rendimiento:** Puede ser un poco más lenta que `Pawn_Native` si la función es nativa, debido al intento de doble búsqueda. Para `publics`, el rendimiento es el mismo que `Pawn_Public`.
- **Uso:** Para funciones donde no está seguro si son nativas o públicas, o para evitar el código repetitivo de intentar una y luego la otra.

#### Sintaxis y Convenciones

- **Nombre de la Función:** Siempre use el nombre de la función Pawn **directamente, sin comillas**. El SDK lo convertirá a string internamente.
- **Parámetros:** Pase los parámetros C++ directamente.

```cpp
// Certo:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Errado (mas tecnicamente funcionaria devido ao hash, evite):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling de Parámetros de Entrada

El SDK convierte sus tipos C++ al formato `cell` de la AMX, gestionando la memoria según sea necesario:
-   `int`, `bool`, `long`, `enum` -> `cell`
-   `float`, `double` -> `cell` (usando `amx::AMX_FTOC`)
-   `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (asigna memoria en la AMX, copia la string, y pasa la dirección `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling de Parámetros de Salida (Referencias: `int&`, `float&`, `std::string&`)

Esta es una funcionalidad clave para la conveniencia y seguridad. Para funciones Pawn que esperan un puntero (referencia), el SDK automatiza todo el proceso de asignación/liberación de memoria y copia de datos.

- **Cómo usar:** Basta con pasar su variable por referencia (`&`).
- **Mecanismo:** El SDK asigna memoria en la heap de la AMX, pasa la dirección AMX a la función Pawn, espera que la función Pawn rellene esa dirección, lee el valor de vuelta y libera la memoria de la AMX. Todo de forma transparente.
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

    Samp_SDK::Log("Localização de %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interior:%d World:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### El Objeto `Callback_Result`: Análisis Completo

Todas las llamadas `Pawn_*` retornan un objeto `Callback_Result`. Este objeto es un envoltorio seguro para el resultado de la llamada Pawn.

- `Callback_Result() noexcept`: Constructor estándar, indica fallo (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Constructor para éxito o fallo con valor.
- `explicit operator bool() const`: Permite usar `if (result)` para verificar si la llamada fue exitosa.
- `operator cell() const`: Permite convertir el resultado a `cell` para obtener el valor.
- `float As_Float() const`: Conveniencia para obtener el resultado como `float`.
- `cell Value() const`: Retorna el valor bruto `cell`.
- `bool Success() const`: Retorna `true` si la llamada Pawn fue exitosa.
- `int Get_Amx_Error() const`: Retorna el código de error de la AMX si la llamada falló (0 para éxito).

```cpp
// Exemplo: Obtendo a vida de um jogador.
// A nativa GetPlayerHealth(playerid, &Float:health) espera um playerid e uma referência para a vida.
int playerid = 0; // Exemplo de ID de jogador
float player_health = 0.0f;

// Chamamos GetPlayerHealth, passando playerid e player_health por referência.
// O SDK cuidará do marshalling para o parâmetro de saída 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Verifica se a chamada foi bem-sucedida (operator bool)
    // O valor retornado por result.As_Float() ou result (operator cell)
    // seria o valor de retorno da *nativa*, não o parâmetro de saída.
    // O valor da vida já foi atualizado em 'player_health' devido ao marshalling do parâmetro de saída.
    Samp_SDK::Log("Jogador %d tem %.1f de vida.", playerid, player_health);
} else {
    // A chamada falhou, talvez o jogador não exista ou a nativa não foi encontrada.
    Samp_SDK::Log("Erro ao obter vida do jogador %d. Código AMX: %d", playerid, result.Get_Amx_Error());
}

// Para nativas que retornam um valor e usam parâmetros de saída (menos comum, mas possível),
// você usaria ambos:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param já está atualizado
// }
```

#### **3.5. `Plugin_Module`: Gestión de Módulos Dinámicos**

La macro `Plugin_Module` permite que su plugin actúe como un "cargador" para otros plugins, creando una arquitectura modular y extensible. Un módulo cargado de esta manera se trata como un plugin de primera clase, con su propio ciclo de vida de eventos gestionado por el plugin anfitrión.

#### Sintaxis y Propósito

- `Plugin_Module(const char* nome_do_arquivo_base, const char* diretorio_do_modulo, const char* mensagem_sucesso_opcional)`
- `nome_do_arquivo_base`: El nombre *base* del archivo del módulo, **sin la extensión** (por ejemplo, para `my_module.dll` o `my_module.so`, use `"my_module"`). El SDK añadirá automáticamente la extensión `.dll` o `.so` correspondiente.
- `diretorio_do_modulo`: La ruta del directorio donde se encuentra el archivo del módulo (por ejemplo, `"plugins/my_custom_modules"`). **No incluya el nombre del archivo aquí.** El SDK concatenará la ruta completa (`diretorio_do_modulo/nome_do_arquivo_base.ext`).
- `mensagem_sucesso_opcional`: Un mensaje opcional para ser registrado en la consola del servidor si el módulo se carga con éxito.

```cpp
// main.cpp, dentro de OnLoad()

// Carga el módulo 'core_logic.dll' (o 'core_logic.so')
// que está ubicado en la carpeta 'modules/custom/' del servidor.
if (!Plugin_Module("core_logic", "modules/custom", "¡Módulo de Lógica Principal cargado con éxito!"))
    return (Samp_SDK::Log("ERROR FATAL: ¡Fallo al cargar el módulo 'core_logic'!"), false);

// Carga el módulo 'admin_system.dll' (o 'admin_system.so')
// que está ubicado directamente en la carpeta 'plugins/' del servidor.
if (!Plugin_Module("admin_system", "plugins", "Módulo de Administración activado."))
    Samp_SDK::Log("ADVERTENCIA: No se pudo cargar el Módulo de Administración.");
```

#### Ciclo de Vida de un Módulo

Un módulo debe exportar las funciones `Load`, `Unload` y `Supports`, al igual que un plugin normal. El SDK gestiona el ciclo de vida del módulo de la siguiente manera:

- **Carga:** Cuando se llama a `Plugin_Module`, el SDK:
   1. Construye la ruta completa del archivo (por ejemplo, `modules/custom/core_logic.dll`).
   2. Usa `Dynamic_Library` (`LoadLibrary`/`dlopen`) para cargar el binario.
   3. **Obtiene los punteros para TODAS las funciones del ciclo de vida del módulo:**
      - **Obligatorias:** `Load`, `Unload`, `Supports`. Si falta alguna, la carga del módulo falla.
      - **Opcionales:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Llama a la función `Load` del módulo, pasando `ppData` del plugin principal.
   5. Si `Load` devuelve `true`, el módulo se añade a la lista interna de módulos cargados.

- **Reenvío de Eventos:** El plugin anfitrión **reenvía automáticamente** los eventos a todos los módulos cargados.
 > [!IMPORTANT]
 > Para que los eventos se reenvíen correctamente, el **plugin anfitrión** (el que llama a `Plugin_Module`) debe estar configurado para recibir estos eventos.
 > - Para que `AmxLoad` y `AmxUnload` funcionen en los módulos, el plugin anfitrión debe definir la macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Para que `ProcessTick` funcione en los módulos, el plugin anfitrión debe definir la macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Descarga:** Durante `OnUnload` del plugin principal, el SDK descarga todos los módulos cargados a través de `Plugin_Module`. Esto se hace en **orden inverso** al de la carga (el último módulo cargado es el primero en descargarse), lo cual es crucial para gestionar dependencias y garantizar la liberación correcta de recursos.

#### Beneficios de la Modularización

- **Organización del Código:** Divida plugins grandes en componentes más pequeños y manejables, cada uno en su propio archivo de módulo.
- **Reusabilidad:** Cree módulos genéricos (por ejemplo, un módulo de base de datos, un módulo de sistema de registro avanzado) que puedan ser utilizados por diferentes plugins, promoviendo la reutilización de código.
- **Componentes Independientes:** Cree módulos que sean **completamente orientados a eventos e independientes**. Un módulo puede tener sus propios `Plugin_Native`s, interceptar `Plugin_Public`s y tener su propia lógica `OnProcessTick`, operando como un plugin autónomo, pero cargado por un anfitrión.
- **Actualizaciones Dinámicas:** En escenarios controlados, permite actualizar partes de su sistema (reemplazando un archivo de módulo `.dll` o `.so`) sin necesidad de recompilar y reiniciar el plugin principal o el servidor completo (aunque esto requiere una gestión estricta de versiones y compatibilidad).

### 3.6. `Plugin_Call`: Llamando Nativas Internas del Plugin

Use `Plugin_Call` para invocar una `Plugin_Native` definida **dentro de su propio plugin**.

#### Sintaxis y Ventajas de Performance

- `Plugin_Call(NomeDaNativa, Param1, Param2, ...)`
- **Ventaja:** Evita la sobrecarga de buscar la nativa en el array de nativas de la AMX. El SDK mantiene un mapa directo de hashes de nombre a punteros de función para sus propias nativas, haciendo de esta la forma más rápida de llamarlas internamente.
- **Requiere:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Lógica para verificar o nível
    return (playerid % 2 == 0) ? 1 : 0; // Exemplo: nível par para IDs pares
}

void CheckAllPlayersLevel() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Chama sua própria nativa
                Samp_SDK::Log("Jogador %d está em um nível alto!", i);
        }
    }
}
```

### **3.7. Funciones Utilitarias del SDK**

#### `Samp_SDK::Log(const char* format, ...)`

- **Descripción:** Imprime mensajes en la consola del servidor y en el archivo `server_log.txt`. Un envoltorio seguro para `logprintf`.
- **Uso:** Para depuración, mensajes de estado y errores.
- **Mecanismo:** Internamente, el SDK obtiene el puntero a `logprintf` a través de `ppData[PLUGIN_DATA_LOGPRINTF]`. La función maneja el formateo de la string de forma segura.

```cpp
// Em qualquer lugar do seu plugin
Samp_SDK::Log("O plugin foi inicializado com um valor %d e uma string '%s'.", 123, "teste");
```

#### `std::string Plugin_Format(const char* format, ...)` (Recomendado)

- **Descripción:** Formatea una string de forma segura (similar a `sprintf`) y retorna un `std::string`. Esta es la forma **recomendada y más idiomática** de formatear strings para usar dentro de su plugin.
- **Uso:** Ideal para construir mensajes formateados antes de pasarlos a `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, o para cualquier otra necesidad de string dentro de su código C++.
- **Mecanismo:** Internamente, `Plugin_Format` es una macro que llama a `Samp_SDK::Format`. Utiliza `vsnprintf` para determinar el tamaño exacto de la string formateada y asigna un `std::string` con capacidad suficiente, evitando desbordamientos de búfer.

```cpp
int playerid = 0; // Exemplo de ID
int health = 50;
std::string status_message = Plugin_Format("Jogador %d, sua vida atual é %d.", playerid, health); // Usando a macro Plugin_Format
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, status_message);

// Também pode ser usado para logs internos
Samp_SDK::Log(Plugin_Format("DEBUG: Processando status para o ID %d", playerid).c_str());
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Detalle de Implementación)

- **Descripción:** La función de implementación subyacente para el formateo de strings, ubicada dentro del namespace `Samp_SDK`.
- **Uso:** Generalmente no es llamada directamente por el usuario. La macro `Plugin_Format` se proporciona como una conveniencia para esta función, alineándose con la convención de nomenclatura de otras macros del SDK (`Plugin_Public`, `Plugin_Native`). Solo la llamaría directamente si quisiera evitar la macro `Plugin_Format` por alguna razón específica.

```cpp
// Exemplo de como Samp_SDK::Format funciona, mas prefira Plugin_Format
std::string raw_status = Samp_SDK::Format("Apenas para uso interno: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Descripción:** Convierte una dirección de string de la AMX (`cell amx_addr`) en un `std::string` C++.
- **Uso:** Principalmente dentro de `Plugin_Native` cuando necesita acceder a strings que no son convertidas automáticamente por `Register_Parameters` o `Native_Params` (ej: si el parámetro Pawn es un `const` `string` y no fue declarado como `std::string` en su `Plugin_Native` o `Plugin_Public` para el Marshalling automático).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Obtém o endereço da string na AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String da AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. **Anatomía Interna y Arquitectura del SDK**

Esta sección desvela los mecanismos subyacentes del SAMP SDK, explorando su arquitectura, los componentes clave y cómo interactúan para proporcionar la abstracción de alto nivel. Una comprensión profunda de estas entrañas capacita al desarrollador a optimizar el uso del SDK, depurar problemas complejos e incluso extender sus funcionalidades.

### 4.1. `core.hpp`: La Fundación Minimalista

El `Samp_SDK::Core` es un `singleton` que sirve como punto de acceso inicial y centralizado a los datos de bajo nivel proporcionados por el entorno del plugin SA-MP. Su principal responsabilidad es encapsular y exponer las funcionalidades esenciales.

- **`Samp_SDK::Core::Instance()`**:
   - **Descripción:** Devuelve la única instancia global de la clase `Core`. Este es un patrón de diseño `singleton` para garantizar que el acceso a los datos del plugin (`ppData`) sea consistente y centralizado.
   - **Mecanismo:** La instancia se inicializa una única vez cuando `Core::Instance().Load(ppData)` es llamado en la función `Load()` de su plugin.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Descripción:** Permite acceso seguro e indexado a los punteros de función de la API AMX. El array `pAMXFunctions` (recibido vía `ppData[PLUGIN_DATA_AMX_EXPORTS]`) contiene las direcciones de funciones críticas como `amx_Exec`, `amx_Register`, etc.
   - **Impacto:** En lugar de usar `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, el SDK ofrece envoltorios type-safe en el namespace `amx::` (ej: `amx::Exec(...)`), haciendo el código más legible y menos propenso a errores de cast.
   - **Ejemplo Interno (`amx_api.hpp`):**
      ```cpp
      // Trecho simplificado de amx_api.hpp
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
   - **Descripción:** Un puntero a la función `logprintf` de SA-MP, que es la interfaz estándar para imprimir mensajes en la consola del servidor y en `server_log.txt`.
   - **Mecanismo:** El `Samp_SDK::Log` es un envoltorio seguro que utiliza este puntero, garantizando que sus mensajes se muestren correctamente en el entorno de SA-MP.

### **4.2. `platform.hpp` y `version.hpp`: Compatibilidad y Metadatos**

Estos headers son la base para la portabilidad y optimización del SDK, adaptándolo a diferentes entornos de compilación y aprovechando características específicas del C++ moderno.

- **Detección de Plataforma y Arquitectura:**
   - **Mecanismo:** Utiliza macros de preprocesador (`#if defined(WIN32)`, `#if defined(__linux__)`, etc.) para identificar el sistema operativo.
   - **Verificación de Arquitectura:** Contiene `static_assert` o `#error` para garantizar que el plugin se esté compilando para x86 (32-bit), un requisito crítico para la compatibilidad con SA-MP y el mecanismo de hooking.
   - **Gestión de Exportación de Símbolos:**
      - `SAMP_SDK_EXPORT`: Una macro definida en `platform.hpp` que se expande a `extern "C"` y, en Linux, añade `__attribute__((visibility("default")))`. En Windows, solo garantiza `extern "C"` porque el SDK utiliza `pragma comment(linker, "/EXPORT:...")` (para MSVC) o el estándar MinGW para exportar las funciones principales.
      - Esto garantiza que las funciones del ciclo de vida del plugin (`Supports`, `Load`, `Unload`, etc.) se exporten correctamente desde su DLL/SO, independientemente del entorno de compilación, **sin la necesidad de archivos `.def` o de añadir `__attribute__((visibility("default")))` manualmente** en su implementación.
   - **Ejemplo (`platform.hpp` - fragmento relevante):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // Para MSVC, a exportação é gerenciada por pragma linker commands
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // Para GCC/Clang no Linux, usamos o atributo de visibilidade
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... outras definições ...
      ```
   - **Ejemplo (`samp_sdk.hpp` - fragmento relevante de la implementación):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // No Windows (MSVC), usamos pragma comment para exportar as funções.
          // Isso elimina a necessidade de um arquivo .def.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... outras exports ...
      #endif

      // Implementação das funções exportadas
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... outras funções ...
      #endif
      ```

- **Macros de Optimización y Predicción de Ramas:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mecanismo:** `__forceinline` (MSVC) o `__attribute__((always_inline)) inline` (GCC/Clang). Sugiere fuertemente al compilador que inserte el cuerpo de la función directamente en el lugar de la llamada, eliminando la sobrecarga de una llamada de función real.
      - **Uso:** Aplicado a funciones pequeñas y críticas para el rendimiento dentro del SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mecanismo:** `[[likely]]` / `[[unlikely]]` (C++20) o `__builtin_expect` (GCC/Clang). Pistas para el compilador sobre qué camino de un `if/else` es más probable que se tome.
      - **Impacto:** Ayuda al compilador a generar código más eficiente para la predicción de desvíos (branch prediction), reduciendo la latencia de la CPU.
      - **Ejemplo (`platform.hpp`):**
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

- **Definiciones C++ Estándar (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mecanismo:** Macros definidas en base al valor de `__cplusplus` y `_MSVC_LANG`.
   - **Uso:** Permiten que el SDK utilice funcionalidades más recientes de C++ (como `std::apply` e `if constexpr` de C++17, o `std::is_same_v` de C++17) cuando estén disponibles, manteniendo la compatibilidad con estándares más antiguos.
   - **Ejemplo (`version.hpp` - uso de `if constexpr`):**
      ```cpp
      // Trecho simplificado de public_dispatcher.hpp
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

### 4.3. `function_hook.hpp`: El Motor de Interceptación x86

Este header define el mecanismo de bajo nivel para realizar hooks (interceptaciones) de funciones, lo cual es fundamental para el funcionamiento del SDK. Es estrictamente dependiente de la arquitectura x86 (32-bit).

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
         // Endereço do desvio - (Endereço do alvo + Tamanho da instrução de JMP)
         ```
   - **`Revert()`**:
      - **Acción:** Desinstala el hook, restaurando los `original_bytes_` en la función `target`.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mecanismo:** En Windows, usa `VirtualProtect`; en Linux, `mprotect`. Estas llamadas al sistema cambian los permisos de la página de memoria donde reside la función a `EXECUTE_READWRITE` (Windows) o `PROT_WRITE | PROT_EXEC` (Linux), permitiendo que el código se modifique en tiempo de ejecución.
      - **Ejemplo (`Unprotect_Memory`):**
         ```cpp
         // Trecho simplificado de function_hook.hpp
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
   - **Descripción:** Un envoltorio C++ `type-safe` para `X86_Detour`, garantizando que los tipos de puntero de función sean correctos.
   - `Install(void* target, void* detour)`: Encapsula la llamada a `X86_Detour::Apply`.
   - `Uninstall()`: Encapsula la llamada a `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Mecanismo de Seguridad (Guarda de Recursión):** Esta función es crítica para evitar bucles infinitos cuando el desvío necesita llamar a la función original. **Temporalmente desinstala el hook (`detour_.Revert()`)**, llama a la función original (`Get_Original()(args...)`), y luego **reinstala el hook (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Un contador que garantiza que el hook solo se reinstale cuando la llamada original de nivel superior haya terminado, permitiendo llamadas recursivas seguras de la función original (si la función original es recursiva, por ejemplo). `thread_local` garantiza que `recursion_guard` esté aislado para cada hilo, importante en entornos multihilo.
      - **Ejemplo (`Call_Original` con Scope_Guard):**
         ```cpp
         // Trecho simplificado de function_hook.hpp
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
   - **Descripción:** Métodos públicos para instalar y desinstalar todos los hooks necesarios. Se llaman en `OnLoad()` y `OnUnload()` de su plugin, respectivamente.
   - **Mecanismo:** Obtiene los punteros de las funciones AMX (como `amx_Register`, `amx_Exec`, etc.) usando `Core::Instance().Get_AMX_Export(...)` e instala los desvíos.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Función Hooked:** `amx_Register`
   - **Propósito:** Intercepta el registro de *todas* las nativas (por SA-MP, otros plugins o gamemode).
   - **Acción:** Llama a `Interceptor_Manager::Instance().Cache_Natives()` para almacenar los punteros y nombres de las nativas en una caché interna.
   - **Impacto:** Esta caché es fundamental para el rendimiento de `Pawn_Native`, permitiendo una búsqueda extremadamente rápida del puntero de la nativa en lugar de una búsqueda costosa en la AMX.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Función Hooked:** `amx_Exec`
   - **Propósito:** **Este es el hook más crítico.** Intercepta *cualquier* ejecución de código en la AMX, incluyendo la llamada de `publics` del Pawn.
   - **Mecanismo de Interceptación de `Plugin_Public`:**
      1. Cuando se llama a `amx_Exec` para una `public` (o `AMX_EXEC_MAIN`), se ejecuta `Amx_Exec_Detour`.
      2. Obtiene el nombre de la `public` (usando `Get_Public_Name_By_Index` o `tl_public_name`).
      3. Consulta `Public_Dispatcher::Instance().Dispatch()` para verificar si hay handlers C++ registrados para este nombre.
      4. Si hay handlers, los ejecuta. `Public_Dispatcher` maneja el `marshalling` de los parámetros de la AMX a los tipos C++ correctos.
      5. Basado en el valor de retorno de `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), decide si llama a la `amx_Exec` original (`Get_Amx_Exec_Hook().Call_Original(...)`) o si finaliza la ejecución de la `public` Pawn.
      6. **Manipulación de la Stack:** Si la ejecución de la `public` Pawn se interrumpe (`PLUGIN_PUBLIC_STOP`), el `Amx_Exec_Detour` corrige la stack de la AMX (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) para evitar inconsistencias.
   - **Ejemplo (`Amx_Exec_Detour`):**
      ```cpp
      // Trecho simplificado de interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          // ... lógica para determinar o nome da public ...
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
   - **Función Hooked:** `amx_FindPublic`
   - **Propósito:** Intercepta la búsqueda de `publics` por nombre.
   - **Mecanismo de "Ghost Publics":** Si `amx_FindPublic` original no encuentra una `public` en Pawn, pero el `Public_Dispatcher` tiene un handler C++ registrado para ese nombre, este hook devuelve `AMX_ERR_NONE` y un `index` especial (`PLUGIN_EXEC_GHOST_PUBLIC`). Esto hace que la API de SA-MP "piense" que la `public` existe, permitiendo que la llamada `amx_Exec` posterior (para este índice especial) sea interceptada por el `Amx_Exec_Detour`, que luego redirige al handler C++.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Se utiliza para pasar el nombre de la `public` al `Amx_Exec_Detour` cuando se detecta un "ghost public", ya que `amx_Exec` solo recibe el índice, no el nombre.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Funciones Hooked:** `amx_Init` / `amx_Cleanup`
   - **Propósito:** Gestionar la lista de instancias `AMX*` activas.
   - **Acción:** `Amx_Init_Detour` llama a `Amx_Manager::Instance().Add_Amx()`, y `Amx_Cleanup_Detour` llama a `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Gestionando Instancias `AMX*`

Este `singleton` mantiene un registro dinámico de todas las máquinas virtuales AMX actualmente cargadas en el servidor. Es esencial para funciones que necesitan interactuar con "todos los scripts" o encontrar un script específico.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Descripción:** Una lista de punteros a todas las instancias `AMX*` que han sido inicializadas (gamemode y filterscripts).
   - **Gestión:** Rellenada por los hooks `Amx_Init_Detour` y vaciada por `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Propósito:** Protege `loaded_amx_` contra el acceso concurrente en entornos multihilo (aunque SA-MP es predominantemente monohilo, esta es una buena práctica de seguridad). `std::shared_mutex` permite múltiples lectores simultáneamente, pero solo un escritor.
- **`std::atomic<uint32_t> generation_`**:
   - **Propósito:** Un contador que se incrementa cada vez que se añade o elimina una AMX.
   - **Uso:** Lo utiliza `Caller_Cache` en `callbacks.hpp` para detectar cuándo ha cambiado la lista de AMXs, invalidando las cachés de búsqueda de `publics` y garantizando que las llamadas a `Pawn_Public` siempre operen con información actualizada. Esto optimiza el rendimiento al evitar búsquedas repetitivas en un estado que no ha cambiado.
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
- **`Public_Registrar`**:
   - **Mecanismo:** Esta es una clase plantilla cuya macro `PLUGIN_PUBLIC_REGISTRATION` crea una instancia estática global. En el constructor estático (`static bool registered = [...]`), registra su handler `Plugin_Public` en el `Public_Dispatcher`. Este es un patrón de "registro estático en tiempo de compilación/inicialización".
   - **Ejemplo (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Registrar<decltype(&name), &name, hash_##name> registrar_##name;
      ```

- **`Public_Traits` y `Wrapper()`**:
   - **Mecanismo:** `Public_Traits` es una plantilla de trait que, usando metaprogramación, genera una función `static cell Wrapper(AMX* amx)`.
   - **Propósito:** Esta `Wrapper` es la `Amx_Handler_Func` que el `Public_Dispatcher` realmente almacena y llama. Es responsable de:
      1. Llamar a `Public_Param_Reader::Get_Public_Params(amx, args...)` para extraer los parámetros de la stack de la AMX.
      2. Llamar a su función `Plugin_Public` C++ real (`func_ptr`) con los parámetros ya convertidos a los tipos C++ correctos.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Descripción:** Un conjunto de funciones plantilla recursivas que leen los valores de la stack de la AMX y los convierten a los tipos C++ especificados en la declaración de `Plugin_Public`.
   - **Mecanismo:** Usa `Get_Stack_Cell()` para acceder a las `cell`s en la stack. Utiliza `if constexpr` (C++17+) o `std::is_same<T>::value` (C++14) para aplicar la conversión correcta (`amx::AMX_CTOF` para float, `Samp_SDK::Get_String` para string, cast directo para int).

### 4.7. `native.hpp`: Gestionando y Llamando Nativas del Plugin

Este header está dedicado a la creación y gestión de nativas C++ que su plugin expone a Pawn.

- **`Native_List_Holder`**:
   - **Descripción:** Un `singleton` global que almacena todas las `Plugin_Native`s declaradas en su plugin (de todos los archivos `.cpp` que usan `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Contiene objetos `Native` (que almacenan el nombre de la nativa y el puntero a la función C++ `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Un mapa optimizado por hash para búsquedas rápidas de `Plugin_Native`s internas (usado por `Plugin_Call`).
- **`Native_Registrar`**:
   - **Mecanismo:** Al igual que `Public_Registrar`, esta es una clase plantilla cuya macro `Plugin_Native` crea una instancia estática global. En su constructor, añade la nativa a `Native_List_Holder`.
   - **Impacto:** Permite declarar `Plugin_Native`s en múltiples archivos `.cpp` sin preocuparse por el registro manual. Todas se recopilarán automáticamente.
- **`Native_Registry`**:
   - **Descripción:** Una clase auxiliar que, en `OnAmxLoad`, toma la lista completa de `Native`s de `Native_List_Holder` y las formatea en un array `AMX_NATIVE_INFO`.
   - **Mecanismo:** Llama a `amx::Register(amx, amx_natives_info_.data(), -1)` para registrar todas sus nativas en la instancia AMX que acaba de ser cargada.
- **`Plugin_Call_Impl(...)`**:
   - **Descripción:** La implementación subyacente de la macro `Plugin_Call`.
   - **Mecanismo:** Utiliza `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` para obtener directamente el puntero de la función C++.
   - **Entorno:** Ejecuta la nativa en un entorno `Amx_Sandbox` (aislado) para gestionar la stack y la heap temporales, de forma similar a cómo funciona `Pawn_Native`.

### 4.8. `callbacks.hpp` & `amx_memory.hpp`: Llamadas C++ -> Pawn y RAII

Estos headers forman la columna vertebral para llamar funciones de Pawn desde C++ (macros `Pawn_*`) y garantizan la seguridad de la memoria.

- **`Amx_Sandbox`**:
   - **Descripción:** Una estructura `thread_local` que simula un entorno `AMX` minimalista y aislado para llamadas `Pawn_Native` y `Plugin_Call`.
   - **Mecanismo:** Tiene su propia estructura `AMX`, `AMX_HEADER` y un `std::vector<unsigned char> heap` para simular la memoria de un script. Esto permite que se llamen `amx::Push`, `amx::Allot`, etc., sin interferir con el estado de los scripts Pawn reales en ejecución.
   - **`thread_local`:** Garantiza que cada hilo tenga su propia `Amx_Sandbox`, evitando condiciones de carrera si el SDK se utiliza en un contexto multihilo (ej: un futuro pool de hilos para operaciones no-Pawn).
   - **Ejemplo (`Amx_Sandbox`):**
      ```cpp
      // Trecho simplificado de callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Memória simulada para stack/heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Inicializa a AMX e a header
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
       - Para `const char*`, `std::string`: Asigna memoria en la heap de `Amx_Sandbox` (o AMX real para `Pawn_Public`), copia la string, y empuja la dirección AMX a la stack.
   - **Procesamiento de Salida (`is_output_arg`):**
       - **Mecanismo:** Cuando un argumento es una referencia de lvalue no-const (detectado por el trait `is_output_arg`), `Parameter_Processor` no empuja el valor, sino una *dirección AMX* para una `cell` asignada temporalmente en la heap.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Después de la llamada a la nativa Pawn, se ejecuta una lista de lambdas (`post_call_updaters`). Cada lambda es responsable de leer el valor final de la `cell` asignada en la AMX y asignarlo de nuevo a la variable C++ original (ej: `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mecanismo:** Una `std::integral_constant` (trait de tipo) que, en tiempo de compilación, evalúa si un tipo de parámetro C++ es una referencia modificable (ej: `int&`, `float&`, `std::string&`). Esto permite que el `Parameter_Processor` diferencie los parámetros de entrada de los de salida.
   - **Ejemplo (`is_output_arg`):**
      ```cpp
      // Trecho simplificado de callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Descripción:** Una clase RAII (`Resource Acquisition Is Initialization`) que encapsula la asignación y desasignación de memoria en la AMX.
   - **Mecanismo:** En el constructor, llama a `amx::Allot` para obtener una `amx_addr` y una `phys_addr`. En el destructor, llama a `amx::Release` para liberar esa memoria.
   - **Impacto:** **Crucial para prevenir fugas de memoria en la heap de la AMX.** Garantiza que la memoria temporal utilizada para strings o parámetros de salida siempre se libere, incluso si ocurren excepciones o retornos anticipados.

### 4.9. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Acceso Abstraído a la AMX

Estos headers proporcionan las definiciones fundamentales y las herramientas de alto nivel para interactuar con Pawn.

- **`amx_defs.h`**:
   - **Contenido:** Contiene las definiciones brutas de las estructuras de la AMX (`AMX`, `AMX_HEADER`), tipos (`cell`, `ucell`), y enums de error (`AmxError`). También define `AMX_NATIVE` y `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Utiliza atributos de empaquetamiento (`#pragma pack(push, 1)` / `__attribute__((packed))`) para garantizar que las estructuras de la AMX tengan el diseño de memoria correcto, fundamental para la interoperabilidad.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Descripción:** La función plantilla principal para invocar las funciones de la API AMX expuestas por el servidor.
   - **Mecanismo:** Obtiene el puntero de la función a través de `Core::Instance().Get_AMX_Export(Index)` y lo llama. Centraliza el manejo de errores si el puntero de la función no está disponible.
   - **Impacto:** Convierte llamadas de bajo nivel (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) en llamadas C++ idiomáticas y type-safe (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Descripción:** Funciones esenciales para convertir valores `cell` a `float` y viceversa, realizando una reinterpretación bit a bit de la memoria.
   - **`static_assert`:** Incluyen `static_assert` para garantizar que `sizeof(cell) == sizeof(float)` en tiempo de compilación, previniendo errores en plataformas con diferentes tamaños de tipo.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Descripción:** Ayudante para convertir una dirección AMX de string en `std::string`.
   - **Mecanismo:** Primero, obtiene la dirección física (`cell* phys_addr`) de la string en la AMX usando `amx::Get_Addr`. Luego, usa `amx::STR_Len` para determinar la longitud y `amx::Get_String` para copiar los bytes a un `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Descripción:** La función base de formateo de strings (`printf`-like) para el SDK.
   - **Mecanismo:** Utiliza `vsnprintf` en dos pasadas: primero para determinar el tamaño necesario de la string, y luego para formatear la string en el `std::string` asignado dinámicamente. Esto evita desbordamientos de búfer.

## 5. Compilación y Deploy

### Requisitos de Arquitectura y Plataforma

- Su plugin **DEBE** ser compilado para la arquitectura **x86 (32-bit)**. El mecanismo de hooking del SDK es específico para esta arquitectura.
- Plataformas Soportadas: Windows (.dll) y Linux (.so).

### Ejemplos de Comandos de Compilación

#### **MSVC (Visual Studio)**

1. Cree un nuevo proyecto de "Dynamic-Link Library (DLL)".
2. En la configuración del proyecto, establezca la "Plataforma de Solución" a **x86**.
3. Asegúrese de que el Estándar del Lenguaje C++ sea al menos C++14.

#### **GCC / Clang (Linux)**

```bash
# Para un plugin llamado 'my_plugin.so' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compila para 32-bit.
- `-shared`: Crea una biblioteca compartida (`.so`).
- `-std=c++17`: Define el estándar C++ para C++17 (puede ser `c++14` o `c++20`).
- `-O2`: Nivel de optimización 2.
- `-fPIC`: Genera código independiente de posición, necesario para bibliotecas compartidas.
- `-Wall -Wextra`: Activa advertencias adicionales para ayudar a detectar errores.
- `-Wl,--no-undefined`: Impide la creación de la biblioteca si hay símbolos indefinidos.

#### **GCC / Clang (MinGW en Windows)**

```bash
# Para un plugin llamado 'my_plugin.dll' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Enlaza la biblioteca estándar C++ estáticamente. Esencial para evitar que su plugin dependa de DLLs de runtime específicas del compilador que podrían no estar presentes en el sistema del usuario.
- `-static-libgcc`: Enlaza la biblioteca GCC estáticamente.

### Consideraciones para la Distribución

- **Nombre del Archivo:** Su plugin debe tener la extensión `.dll` (Windows) o `.so` (Linux). Ej: `my_plugin.dll`.
- **Ubicación:** Coloque el archivo compilado en la carpeta `plugins/` de su servidor SA-MP.
- **server.cfg:** Añada el nombre de su plugin (si es Windows, sin la extensión) a la línea `plugins` en `server.cfg`.
   ```
   plugins my_plugin (se for Linux, my_plugin.so)
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