# SAMP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Um SDK C++ moderno, header-only e de alto nível para o desenvolvimento de plugins e módulos para SA-MP.**

</div>

## Idiomas

- Deutsch: [README](translations/Deutsch/README.md)
- English: [README](translations/English/README.md)
- Español: [README](translations/Espanol/README.md)
- Français: [README](translations/Francais/README.md)
- Italiano: [README](translations/Italiano/README.md)
- Polski: [README](translations/Polski/README.md)
- Русский: [README](translations/Русский/README.md)
- Svenska: [README](translations/Svenska/README.md)
- Türkçe: [README](translations/Turkce/README.md)

## Índice

- [SAMP SDK](#samp-sdk)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [1. Introdução e Filosofia de Design](#1-introdução-e-filosofia-de-design)
    - [O Problema com a API C Padrão do SA-MP](#o-problema-com-a-api-c-padrão-do-sa-mp)
    - [A Solução do SAMP SDK: Abstração com Segurança e Performance](#a-solução-do-samp-sdk-abstração-com-segurança-e-performance)
    - [Modelo Header-Only: Vantagens e Implicações](#modelo-header-only-vantagens-e-implicações)
  - [2. Configuração e Ambiente](#2-configuração-e-ambiente)
    - [Requisitos de Compilação](#requisitos-de-compilação)
    - [Estrutura de Arquivos Recomendada](#estrutura-de-arquivos-recomendada)
    - [Macros Essenciais de Configuração\*\*](#macros-essenciais-de-configuração)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definições e Constantes do SA-MP (`samp_defs.hpp`)](#definições-e-constantes-do-sa-mp-samp_defshpp)
  - [3. Guia de Uso Abrangente da API](#3-guia-de-uso-abrangente-da-api)
    - [3.1. O Ciclo de Vida do Plugin](#31-o-ciclo-de-vida-do-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Interceptando Eventos do Pawn](#32-plugin_public-interceptando-eventos-do-pawn)
      - [Sintaxe e Declaração](#sintaxe-e-declaração)
      - [Marshalling Automático de Parâmetros](#marshalling-automático-de-parâmetros)
      - [Controle de Fluxo: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#controle-de-fluxo-plugin_public_continue-vs-plugin_public_stop)
    - [3.3. `Plugin_Native`: Criando Funções Nativas em C++](#33-plugin_native-criando-funções-nativas-em-c)
      - [Sintaxe e Assinatura Fixa](#sintaxe-e-assinatura-fixa)
      - [Registro Automático de Nativas](#registro-automático-de-nativas)
      - [Extração de Parâmetros: `Register_Parameters` vs. `Native_Params`](#extração-de-parâmetros-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)](#native_params-api-completa-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Retorno de Valores](#retorno-de-valores)
    - [3.4. `Pawn_*` Macros: Chamando Funções do Pawn a Partir do C++](#34-pawn_-macros-chamando-funções-do-pawn-a-partir-do-c)
      - [`Pawn_Native(NomeDaNativa, ...)`](#pawn_nativenomedanativa-)
      - [`Pawn_Public(NomeDaPublic, ...)`](#pawn_publicnomedapublic-)
      - [`Pawn(NomeDaFuncao, ...)`](#pawnnomedafuncao-)
      - [Sintaxe e Convenções](#sintaxe-e-convenções)
      - [Marshalling de Parâmetros de Entrada](#marshalling-de-parâmetros-de-entrada)
      - [Marshalling de Parâmetros de Saída (Referências: `int&`, `float&`, `std::string&`)](#marshalling-de-parâmetros-de-saída-referências-int-float-stdstring)
      - [O Objeto `Callback_Result`: Análise Completa](#o-objeto-callback_result-análise-completa)
    - [3.5. `Plugin_Module`: Gerenciamento de Módulos Dinâmicos](#35-plugin_module-gerenciamento-de-módulos-dinâmicos)
      - [Sintaxe e Propósito](#sintaxe-e-propósito)
      - [Ciclo de Vida de um Módulo](#ciclo-de-vida-de-um-módulo)
      - [Benefícios da Modularização](#benefícios-da-modularização)
    - [3.6. `Plugin_Call`: Chamando Nativas Internas do Plugin](#36-plugin_call-chamando-nativas-internas-do-plugin)
      - [Sintaxe e Vantagens de Performance](#sintaxe-e-vantagens-de-performance)
    - [**3.7. Funções Utilitárias do SDK**](#37-funções-utilitárias-do-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Recomendado)](#stdstring-plugin_formatconst-char-format--recomendado)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Detalhe de Implementação)](#stdstring-samp_sdkformatconst-char-format--detalhe-de-implementação)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. **Anatomia Interna e Arquitetura do SDK**](#4-anatomia-interna-e-arquitetura-do-sdk)
    - [4.1. `core.hpp`: A Fundação Minimalista](#41-corehpp-a-fundação-minimalista)
    - [**4.2. `platform.hpp` e `version.hpp`: Compatibilidade e Metadados**](#42-platformhpp-e-versionhpp-compatibilidade-e-metadados)
    - [4.3. `function_hook.hpp`: O Motor de Interceptação x86](#43-function_hookhpp-o-motor-de-interceptação-x86)
    - [4.4. `interceptor_manager.hpp`: O Controlador de Hooks do AMX](#44-interceptor_managerhpp-o-controlador-de-hooks-do-amx)
    - [4.5. `amx_manager.hpp`: Gerenciando Instâncias `AMX*`](#45-amx_managerhpp-gerenciando-instâncias-amx)
    - [4.6. `public_dispatcher.hpp`: O Roteador de Callbacks `Plugin_Public`](#46-public_dispatcherhpp-o-roteador-de-callbacks-plugin_public)
    - [4.7. `native.hpp`: Gerenciando e Chamando Nativas do Plugin](#47-nativehpp-gerenciando-e-chamando-nativas-do-plugin)
    - [4.8. `callbacks.hpp` \& `amx_memory.hpp`: Chamadas C++ -\> Pawn e RAII](#48-callbackshpp--amx_memoryhpp-chamadas-c---pawn-e-raii)
    - [4.9. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Acesso Abstraído à AMX](#49-amx_apihpp--amx_helpershpp--amx_defsh-acesso-abstraído-à-amx)
  - [5. Compilação e Deploy](#5-compilação-e-deploy)
    - [Requisitos de Arquitetura e Plataforma](#requisitos-de-arquitetura-e-plataforma)
    - [Exemplos de Comandos de Compilação](#exemplos-de-comandos-de-compilação)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW no Windows)**](#gcc--clang-mingw-no-windows)
    - [Considerações para Distribuição](#considerações-para-distribuição)
  - [Licença](#licença)
    - [Termos e Condições de Uso](#termos-e-condições-de-uso)
      - [1. Permissões Concedidas](#1-permissões-concedidas)
      - [2. Condições Obrigatórias](#2-condições-obrigatórias)
      - [3. Direitos Autorais](#3-direitos-autorais)
      - [4. Isenção de Garantias e Limitação de Responsabilidade](#4-isenção-de-garantias-e-limitação-de-responsabilidade)

## 1. Introdução e Filosofia de Design

### O Problema com a API C Padrão do SA-MP

A API de plugins do SA-MP é uma interface de programação em C. Embora funcional e fundamental, ela apresenta os desafios inerentes à programação de baixo nível:
- **Gerenciamento Manual de Memória:** Funções como `amx_Allot` e `amx_Release` exigem que o desenvolvedor aloque e desaloque explicitamente a memória na heap da AMX. Isso é uma fonte comum de vazamentos de memória e falhas de runtime.
- **Tipagem Fraca e Conversões Manuais:** Parâmetros são passados como um array de `cell`s, forçando conversões explícitas (e muitas vezes inseguras) entre `cell`, `int`, `float`, e `char*`.
- **Verbosidade e Boilerplate:** Extrair múltiplos parâmetros de um array `cell* params`, lidar com tamanhos de strings, e gerenciar a stack da AMX para chamadas de retorno C++ para Pawn exige código repetitivo.
- **Fragilidade da Interface:** A falta de verificação em tempo de compilação (type safety) significa que erros na passagem de parâmetros ou tipos podem passar despercebidos até a execução, causando crashes ou comportamentos indefinidos.

### A Solução do SAMP SDK: Abstração com Segurança e Performance

O SAMP SDK aborda esses problemas fornecendo uma poderosa camada de abstração em C++:
- **RAII (Resource Acquisition Is Initialization):** Gerenciamento automático de memória na AMX. `Amx_Scoped_Memory` garante que a memória alocada seja liberada.
- **Segurança de Tipos:** Conversão automática e segura de parâmetros entre C++ e Pawn. Você lida com `int`, `float`, `std::string` diretamente.
- **Sintaxe Concisa e Idiomática:** Macros e templates fornecem uma API limpa que se assemelha mais ao C++ moderno do que à API C tradicional.
- **Interceptação Robusta:** Um motor de hooking avançado permite a interceptação transparente de callbacks do Pawn (`Plugin_Public`) e o registro dinâmico de nativas.
- **Alta Performance:** Uso extensivo de hashing em tempo de compilação (FNV1a), caching de funções e otimizações de `thread_local` para minimizar o overhead das abstrações.

### Modelo Header-Only: Vantagens e Implicações

O SDK é composto exclusivamente por arquivos de cabeçalho (`.hpp`, `.h`).
- **Vantagens:**
   - **Integração Simplificada:** Não há bibliotecas para construir, vincular ou distribuir. Basta incluir os headers.
   - **Otimizações do Compilador:** O compilador tem visibilidade completa do código do SDK e do seu plugin, permitindo inlining agressivo e otimizações de tempo de linkagem, o que pode resultar em binários mais rápidos.
- **Implicações:**
   - **Tempo de Compilação:** Para projetos muito grandes, a compilação pode levar mais tempo devido à inclusão repetida do código do SDK. Isso é mitigado por guards de inclusão e pela natureza de "incluir apenas o que é necessário" do C++.
   - **Macros de Implementação:** A necessidade da macro `SAMP_SDK_IMPLEMENTATION` é uma consequência do modelo header-only para evitar redefinições de símbolos.

## 2. Configuração e Ambiente

### Requisitos de Compilação

- **Compilador C++:** Compatível com C++14 ou superior (o SDK utiliza recursos de C++14, C++17 e C++20 para otimizações específicas, mas C++14 é o mínimo).
   - GCC (versão 7+)
   - Clang (versão 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Arquitetura:** **x86 (32-bit)**. O SA-MP opera exclusivamente nesta arquitetura. O SDK inclui verificações em `platform.hpp` que emitirão erros de compilação se a arquitetura incorreta for detectada.
- **Sistema Operacional:** Windows ou Linux.

### Estrutura de Arquivos Recomendada

Para clareza e organização, é comum organizar o SDK em uma subpasta `samp-sdk`.

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

### Macros Essenciais de Configuração**

Sempre defina estas macros *antes* de incluir `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Propósito:** Sinaliza ao compilador que este arquivo `.cpp` deve gerar as implementações das funções de exportação do plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **O SDK cuida da exportação dessas funções automaticamente, eliminando a necessidade de arquivos `.def` (no Windows) ou declarações `__attribute__((visibility("default")))` (no Linux) para estas funções.**
- **Impacto Técnico:** Sem esta macro, o linker não encontrará as exportações necessárias, e o servidor SA-MP não conseguirá carregar seu plugin.
- **Regra Fundamental:** **Defina esta macro em APENAS UM arquivo `.cpp` em todo o seu projeto.** Definí-la em mais de um arquivo causará um erro de linkagem de "símbolo duplicado".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // A macro faz o SDK exportar as funções necessárias automaticamente.
#include "samp-sdk/samp_sdk.hpp"

// ... seu código de plugin ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Propósito:** Habilita as funcionalidades do SDK relacionadas à interação com o ambiente da AMX (máquina virtual do Pawn).
- **Funcionalidades Ativadas:**
   - Declaração e registro de nativas C++ usando `Plugin_Native`.
   - Callbacks `OnAmxLoad(AMX* amx)` e `OnAmxUnload(AMX* amx)`.
   - A macro `Plugin_Call` para invocar nativas do próprio plugin.
- **Impacto Técnico:** Quando esta macro é definida, o SDK coleta automaticamente todas as suas `Plugin_Native`s. Na função `Supports()`, a flag `SUPPORTS_AMX_NATIVES` é automaticamente adicionada.
- **Flexibilidade:** **Você pode definir esta macro em múltiplos arquivos `.cpp`**. O sistema de registro estático do SDK (`Native_Registrar`) consolidará todas as nativas de diferentes unidades de compilação em uma única lista global.

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

- **Propósito:** Habilita o callback `OnProcessTick()`, que é invocado regularmente pelo servidor.
- **Impacto Técnico:** Adiciona automaticamente a flag `SUPPORTS_PROCESS_TICK` na função `Supports()`.

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

### Definições e Constantes do SA-MP (`samp_defs.hpp`)

Este arquivo fornece todas as constantes e limites conhecidos do SA-MP, como `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. É automaticamente incluído por `samp_sdk.hpp` e deve ser usado para garantir a compatibilidade e legibilidade do código.

## 3. Guia de Uso Abrangente da API

### 3.1. O Ciclo de Vida do Plugin

As seguintes funções são os pontos de entrada e saída do seu plugin, exportadas automaticamente pelo SDK.

#### `bool OnLoad()`

- **Descrição:** Primeira função chamada pelo servidor SA-MP após o carregamento bem-sucedido do seu plugin na memória.
- **Uso:** Ideal para inicializar qualquer sistema, carregar configurações, abrir conexões com banco de dados, ou carregar módulos (`Plugin_Module`).
- **Retorno:**
   - `true`: O plugin foi inicializado com sucesso e o carregamento continua.
   - `false`: O plugin falhou ao inicializar. O carregamento será abortado e o plugin será descarregado.

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

- **Descrição:** Última função chamada pelo servidor SA-MP antes de descarregar seu plugin da memória.
- **Uso:** Ideal para limpar recursos, fechar conexões, salvar estados, e garantir que nenhum recurso seja vazado. O SDK gerencia o descarregamento de módulos (`Plugin_Module`) automaticamente.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MeuPlugin descarregado. Liberando recursos...");
    // Nenhuma ação manual é necessária para módulos carregados via Plugin_Module;
    // o SDK cuida disso.
}
```

#### `unsigned int GetSupportFlags()`

- **Descrição:** Informa ao servidor SA-MP quais recursos seu plugin suporta e deseja usar.
- **Uso:** **Sempre retorne `SUPPORTS_VERSION` (ou `SAMP_PLUGIN_VERSION`).** As outras flags (`SUPPORTS_AMX_NATIVES`, `SUPPORTS_PROCESS_TICK`) são adicionadas automaticamente pelo SDK se as macros `SAMP_SDK_WANT_AMX_EVENTS` e `SAMP_SDK_WANT_PROCESS_TICK` forem definidas. Isso simplifica a manutenção e evita erros.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // O SDK adiciona as flags necessárias automaticamente.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requer:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrição:** Chamada sempre que um novo script Pawn (um Gamemode ou Filterscript) é carregado e inicializado no servidor.
- **Uso:** Se você precisar de lógica específica para cada script AMX, como registrar nativas personalizadas (embora o `Plugin_Native` faça isso automaticamente), ou inicializar dados específicos por script.

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

- **Requer:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrição:** Chamada quando um script Pawn é descarregado do servidor.
- **Uso:** Para limpar quaisquer recursos específicos que você alocou ou associou àquele `AMX*` em particular.

```cpp
// main.cpp (com SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX descarregado: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requer:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Descrição:** Chamada repetidamente a cada "tick" do servidor (geralmente 20 vezes por segundo, ou a cada 50ms).
- **Uso:** Para lógica de fundo contínua, temporizadores, atualizações de estado que não dependem de eventos de jogador, ou sincronização de dados.
- **Cuidado:** Evite operações de bloqueio ou computacionalmente pesadas aqui, pois podem causar lag no servidor.

```cpp
// main.cpp (com SAMP_SDK_WANT_PROCESS_TICK definido)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // A cada 10 segundos (20 ticks/seg * 10 seg = 200 ticks)
        Samp_SDK::Log("Servidor ativo por %d segundos.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Interceptando Eventos do Pawn

A macro `Plugin_Public` é a ponte primária para receber callbacks do Pawn em seu código C++.

#### Sintaxe e Declaração

- `Plugin_Public(NomeDaPublic, Tipo1 Param1, Tipo2 Param2, ...)`
- O nome da função C++ que você declara **deve ser o mesmo** do callback Pawn (ex: `OnPlayerConnect`).
- Os tipos de parâmetros C++ (`int`, `float`, `std::string`) são automaticamente convertidos pelo SDK.

```cpp
// Intercepta OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    // ...
}
```

#### Marshalling Automático de Parâmetros

O SDK automaticamente lida com a leitura da `cell stack` da AMX e a conversão para os tipos C++ especificados:
- `int`: Convertido diretamente de `cell`.
- `float`: Convertido de `cell` usando `amx::AMX_CTOF`.
- `std::string`: O SDK lê o endereço da string na AMX, aloca um `std::string` em C++ e copia o conteúdo.

#### Controle de Fluxo: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

O valor retornado pela sua função `Plugin_Public` é crucial e determina o fluxo de execução do callback:
- `return PLUGIN_PUBLIC_CONTINUE;` (valor `1`): Indica que a execução do callback deve **continuar**. Se houver outros plugins que também interceptam este callback, eles serão chamados. Em seguida, a `public` original no script Pawn será invocada.
- `return PLUGIN_PUBLIC_STOP;` (valor `0`): Indica que a execução do callback deve ser **interrompida**. Nenhum outro plugin ou a `public` original no script Pawn será invocado para este evento. Isso é ideal para implementar um sistema que "sobrescreve" ou "bloqueia" um comportamento padrão do SA-MP.

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

### 3.3. `Plugin_Native`: Criando Funções Nativas em C++

`Plugin_Native` permite que você estenda a funcionalidade do Pawn com código C++ de alta performance.

#### Sintaxe e Assinatura Fixa

- `Plugin_Native(NomeDaNativa, AMX* amx, cell* params)`
- A função C++ deve ter exatamente esta assinatura: `cell NomeDaNativa(AMX* amx, cell* params)`.
- `NomeDaNativa` é o nome que os scripts Pawn usarão.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementação ...
    return 0;
}
```

#### Registro Automático de Nativas

> [!NOTE]
> Você **não precisa** chamar `amx_Register` manualmente. O SDK detecta todas as suas `Plugin_Native`s (em qualquer arquivo `.cpp` com `SAMP_SDK_WANT_AMX_EVENTS`) e as registra automaticamente em cada script AMX carregado (`OnAmxLoad`).

#### Extração de Parâmetros: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Descrição:** Helper mais simples para extrair múltiplos parâmetros sequencialmente.
- **Uso:** `Register_Parameters(variavel1, variavel2, ...)`
- **Limitações:** Para parâmetros de entrada. Não lida com parâmetros opcionais ou acesso por índice.
- **Tipos Suportados:** `int`, `float`, `std::string`.

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

- **Descrição:** Uma classe wrapper que fornece uma interface orientada a objetos para acessar os parâmetros de uma nativa. Mais poderosa para cenários complexos.
- **Construção:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Descrição:** Retorna o número de parâmetros passados para a nativa.
- **Uso:** Essencial para lidar com parâmetros opcionais.

###### `p.Get<T>(size_t index)`

- **Descrição:** Extrai um parâmetro de entrada por índice e o converte para o tipo `T`.
- **Tipos Suportados:** `int`, `float`, `std::string`.

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

- **Descrição:** Obtém o valor de um parâmetro de **referência** (ponteiro Pawn) e o armazena em `out_value`.
- **Uso:** Para ler valores que foram passados por referência do Pawn.
- **Retorno:** `true` se o endereço AMX for válido, `false` caso contrário.

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

- **Descrição:** Retorna um `std::optional<T>` para ler um parâmetro de referência. Mais seguro para C++17 e superior.

###### `p.Set_REF<T>(size_t index, T value)`

- **Descrição:** Escreve um valor `T` em um parâmetro de **referência** Pawn (o endereço que o Pawn passou).
- **Uso:** Para modificar valores que foram passados por referência, fazendo com que o Pawn veja a alteração.
- **Retorno:** `true` se a escrita foi bem-sucedida, `false` caso contrário.

#### Retorno de Valores

- Sua função `Plugin_Native` deve retornar um `cell`.
- Para retornar um `int` ou `bool`, use um cast para `cell`.
- Para retornar um `float`, use `amx::AMX_FTOC(meu_float)`.

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

### 3.4. `Pawn_*` Macros: Chamando Funções do Pawn a Partir do C++

Estas macros são o inverso de `Plugin_Public` e `Plugin_Native`: elas permitem que seu código C++ invoque funções Pawn.

#### `Pawn_Native(NomeDaNativa, ...)`

- **Propósito:** A forma recomendada de chamar funções nativas do SA-MP (ou de outros plugins) a partir do C++.
- **Mecanismo:** Busca o ponteiro da nativa no cache interno do SDK (preenchido por `Amx_Register_Detour`). Se encontrado, executa a nativa em um ambiente `Amx_Sandbox` (uma instância AMX falsa e isolada).
- **Performance:** A mais eficiente, pois evita a busca cara de `publics` e interage diretamente com o ponteiro da nativa.

#### `Pawn_Public(NomeDaPublic, ...)`

- **Propósito:** Chama uma função pública específica em um script Pawn.
- **Mecanismo:** Percorre as instâncias `AMX*` gerenciadas pelo `Amx_Manager`, busca a `public` pelo nome, e a executa.
- **Performance:** Menos eficiente que `Pawn_Native` devido à busca e ao `amx_Exec` real. Geralmente, `publics` são mais lentas que `natives`.
- **Uso:** Ideal para invocar eventos personalizados em seu Gamemode/Filterscripts que não são nativas.

#### `Pawn(NomeDaFuncao, ...)`

- **Propósito:** Uma macro de conveniência que tenta adivinhar se a função é uma nativa ou uma pública.
- **Mecanismo:** Primeiro, tenta chamar como `Pawn_Native`. Se falhar (a nativa não é encontrada), tenta chamar como `Pawn_Public`.
- **Performance:** Pode ser um pouco mais lenta que `Pawn_Native` se a função for nativa, devido à tentativa de busca dupla. Para `publics`, o desempenho é o mesmo de `Pawn_Public`.
- **Uso:** Para funções onde você não tem certeza se são nativas ou públicas, ou para evitar o boilerplate de tentar uma e depois a outra.

#### Sintaxe e Convenções

- **Nome da Função:** Sempre use o nome da função Pawn **diretamente, sem aspas**. O SDK o converterá para string internamente.
- **Parâmetros:** Passe os parâmetros C++ diretamente.

```cpp
// Certo:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Errado (mas tecnicamente funcionaria devido ao hash, evite):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling de Parâmetros de Entrada

O SDK converte seus tipos C++ para o formato `cell` da AMX, gerenciando a memória conforme necessário:
-   `int`, `bool`, `long`, `enum` -> `cell`
-   `float`, `double` -> `cell` (usando `amx::AMX_FTOC`)
-   `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (aloca memória na AMX, copia a string, e passa o endereço `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling de Parâmetros de Saída (Referências: `int&`, `float&`, `std::string&`)

Esta é uma funcionalidade-chave para conveniência e segurança. Para funções Pawn que esperam um ponteiro (referência), o SDK automatiza todo o processo de alocação/liberação de memória e cópia de dados.

- **Como usar:** Basta passar sua variável por referência (`&`).
- **Mecanismo:** O SDK aloca memória na heap da AMX, passa o endereço AMX para a função Pawn, espera que a função Pawn preencha esse endereço, lê o valor de volta, e libera a memória da AMX. Tudo de forma transparente.
- **Com `std::string&`:** O SDK aloca um buffer padrão (256 células) na AMX para a string.

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

#### O Objeto `Callback_Result`: Análise Completa

Todas as chamadas `Pawn_*` retornam um objeto `Callback_Result`. Este objeto é um wrapper seguro para o resultado da chamada Pawn.

- `Callback_Result() noexcept`: Construtor padrão, indica falha (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Construtor para sucesso ou falha com valor.
- `explicit operator bool() const`: Permite usar `if (result)` para verificar se a chamada foi bem-sucedida.
- `operator cell() const`: Permite converter o resultado para `cell` para obter o valor.
- `float As_Float() const`: Conveniência para obter o resultado como `float`.
- `cell Value() const`: Retorna o valor bruto `cell`.
- `bool Success() const`: Retorna `true` se a chamada Pawn foi bem-sucedida.
- `int Get_Amx_Error() const`: Retorna o código de erro da AMX se a chamada falhou (0 para sucesso).

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

### 3.5. `Plugin_Module`: Gerenciamento de Módulos Dinâmicos

A macro `Plugin_Module` permite que seu plugin atue como um "carregador" para outros plugins, criando uma arquitetura modular e extensível.

#### Sintaxe e Propósito

- `Plugin_Module(const char* nome_do_arquivo_base, const char* diretorio_do_modulo, const char* mensagem_sucesso_opcional)`
- `nome_do_arquivo_base`: O nome *base* do arquivo do módulo, **sem a extensão** (ex: para `my_module.dll` ou `my_module.so`, use `"my_module"`). O SDK adicionará automaticamente a extensão `.dll` ou `.so` apropriada.
- `diretorio_do_modulo`: O caminho do diretório onde o arquivo do módulo está localizado (ex: `"plugins/my_custom_modules"`). **Não inclua o nome do arquivo aqui.** O SDK fará a concatenação do caminho completo (`diretorio_do_modulo/nome_do_arquivo_base.ext`).
- `mensagem_sucesso_opcional`: Uma mensagem opcional para ser logada no console do servidor se o módulo carregar com sucesso.

```cpp
// main.cpp, dentro de OnLoad()

// Carrega o módulo 'core_logic.dll' (ou 'core_logic.so')
// que está localizado na pasta 'modules/custom/' do servidor.
if (!Plugin_Module("core_logic", "modules/custom", "Módulo de Lógica Core carregado com sucesso!"))
    return (Samp_SDK::Log("ERRO FATAL: Falha ao carregar o módulo 'core_logic'!"), false);

// Carrega o módulo 'admin_system.dll' (ou 'admin_system.so')
// que está localizado diretamente na pasta 'plugins/' do servidor.
if (!Plugin_Module("admin_system", "plugins", "Módulo de Administração ativado."))
    Samp_SDK::Log("AVISO: Módulo de Administração não pôde ser carregado.");
```

#### Ciclo de Vida de um Módulo

- **Carregamento:** Quando `Plugin_Module` é chamado, o SDK:
   1. Constrói o caminho completo do arquivo (ex: `plugins/custom/core_logic.dll`).
   2. Usa `Dynamic_Library` (`LoadLibrary`/`dlopen`) para carregar o binário.
   3. Obtém os ponteiros para as funções de ciclo de vida do módulo: `Load`, `Unload` e `Supports`.
   4. Chama a função `Load` do módulo, passando `ppData` do plugin principal.
   5. Se `Load` retornar `true`, o módulo é adicionado à lista interna de módulos carregados.
- **Descarregamento:** Durante `OnUnload` do seu plugin principal, o SDK descarrega todos os módulos que foram carregados via `Plugin_Module`. Isso é feito na **ordem inversa** ao carregamento (o último a ser carregado é o primeiro a ser descarregado), o que é crucial para gerenciar dependências e garantir a liberação correta de recursos.

#### Benefícios da Modularização

- **Organização do Código:** Divida grandes plugins em componentes menores e gerenciáveis, cada um em seu próprio arquivo de módulo.
- **Reusabilidade:** Crie módulos genéricos (ex: um módulo de banco de dados, um módulo de sistema de log avançado) que podem ser usados por diferentes plugins, promovendo a reutilização de código.
- **Atualizações Dinâmicas:** Em cenários controlados, permite a atualização de partes do seu sistema (substituindo um `.dll` ou `.so` de módulo) sem a necessidade de recompilar e reiniciar o plugin principal ou o servidor inteiro (embora isso exija um gerenciamento de versão e compatibilidade rigorosos).

### 3.6. `Plugin_Call`: Chamando Nativas Internas do Plugin

Use `Plugin_Call` para invocar uma `Plugin_Native` definida **dentro do seu próprio plugin**.

#### Sintaxe e Vantagens de Performance

- `Plugin_Call(NomeDaNativa, Param1, Param2, ...)`
- **Vantagem:** Evita a sobrecarga de procurar a nativa no array de nativas da AMX. O SDK mantém um mapa direto de hashes de nome para ponteiros de função para suas próprias nativas, tornando esta a forma mais rápida de chamá-las internamente.
- **Requer:** `SAMP_SDK_WANT_AMX_EVENTS`.

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

### **3.7. Funções Utilitárias do SDK**

#### `Samp_SDK::Log(const char* format, ...)`

- **Descrição:** Imprime mensagens no console do servidor e no arquivo `server_log.txt`. Um wrapper seguro para `logprintf`.
- **Uso:** Para depuração, mensagens de status e erros.
- **Mecanismo:** Internamente, o SDK obtém o ponteiro para `logprintf` através de `ppData[PLUGIN_DATA_LOGPRINTF]`. A função lida com a formatação da string de forma segura.

```cpp
// Em qualquer lugar do seu plugin
Samp_SDK::Log("O plugin foi inicializado com um valor %d e uma string '%s'.", 123, "teste");
```

#### `std::string Plugin_Format(const char* format, ...)` (Recomendado)

- **Descrição:** Formata uma string de forma segura (similar a `sprintf`) e retorna um `std::string`. Esta é a maneira **recomendada e mais idiomática** de formatar strings para uso dentro do seu plugin.
- **Uso:** Ideal para construir mensagens formatadas antes de passá-las para `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, ou para qualquer outra necessidade de string dentro do seu código C++.
- **Mecanismo:** Internamente, `Plugin_Format` é uma macro que chama `Samp_SDK::Format`. Ele utiliza `vsnprintf` para determinar o tamanho exato da string formatada e aloca um `std::string` com capacidade suficiente, evitando estouros de buffer.

```cpp
int playerid = 0; // Exemplo de ID
int health = 50;
std::string status_message = Plugin_Format("Jogador %d, sua vida atual é %d.", playerid, health); // Usando a macro Plugin_Format
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, status_message);

// Também pode ser usado para logs internos
Samp_SDK::Log(Plugin_Format("DEBUG: Processando status para o ID %d", playerid).c_str());
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Detalhe de Implementação)

- **Descrição:** A função de implementação subjacente para formatação de strings, localizada dentro do namespace `Samp_SDK`.
- **Uso:** Geralmente não é chamada diretamente pelo usuário. A macro `Plugin_Format` é fornecida como uma conveniência para esta função, alinhando-se com a convenção de nomenclatura de outras macros do SDK (`Plugin_Public`, `Plugin_Native`). Você só a chamaria diretamente se quisesse evitar a macro `Plugin_Format` por algum motivo específico.

```cpp
// Exemplo de como Samp_SDK::Format funciona, mas prefira Plugin_Format
std::string raw_status = Samp_SDK::Format("Apenas para uso interno: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Descrição:** Converte um endereço de string da AMX (`cell amx_addr`) em um `std::string` C++.
- **Uso:** Principalmente dentro de `Plugin_Native` quando você precisa acessar strings que não são automaticamente convertidas por `Register_Parameters` ou `Native_Params` (ex: se o parâmetro Pawn é um `const` `string` e não foi declarado como `std::string` no seu `Plugin_Native` ou `Plugin_Public` para Marshalling automático).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Obtém o endereço da string na AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String da AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. **Anatomia Interna e Arquitetura do SDK**

Esta seção desvela os mecanismos subjacentes do SAMP SDK, explorando sua arquitetura, os componentes-chave e como eles interagem para fornecer a abstração de alto nível. Uma compreensão profunda destas entranhas capacita o desenvolvedor a otimizar o uso do SDK, depurar problemas complexos e até mesmo estender suas funcionalidades.

### 4.1. `core.hpp`: A Fundação Minimalista

O `Samp_SDK::Core` é um `singleton` que serve como o ponto de acesso inicial e centralizado aos dados de baixo nível fornecidos pelo ambiente do plugin SA-MP. Sua principal responsabilidade é encapsular e expor as funcionalidades essenciais.

- **`Samp_SDK::Core::Instance()`**:
   - **Descrição:** Retorna a única instância global da classe `Core`. Este é um padrão de design `singleton` para garantir que o acesso aos dados do plugin (`ppData`) seja consistente e centralizado.
   - **Mecanismo:** A instância é inicializada uma única vez quando `Core::Instance().Load(ppData)` é chamado na função `Load()` do seu plugin.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Descrição:** Permite acesso seguro e indexado aos ponteiros de função da API AMX. O array `pAMXFunctions` (recebido via `ppData[PLUGIN_DATA_AMX_EXPORTS]`) contém os endereços de funções críticas como `amx_Exec`, `amx_Register`, etc.
   - **Impacto:** Em vez de usar `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)`, o SDK oferece wrappers type-safe no `amx::` namespace (ex: `amx::Exec(...)`), tornando o código mais legível e menos propenso a erros de cast.
   - **Exemplo Interno (`amx_api.hpp`):**
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
   - **Descrição:** Um ponteiro para a função `logprintf` do SA-MP, que é a interface padrão para imprimir mensagens no console do servidor e no `server_log.txt`.
   - **Mecanismo:** O `Samp_SDK::Log` é um wrapper seguro que utiliza este ponteiro, garantindo que suas mensagens sejam exibidas corretamente no ambiente do SA-MP.

### **4.2. `platform.hpp` e `version.hpp`: Compatibilidade e Metadados**

Estes headers são a base para a portabilidade e otimização do SDK, adaptando-o a diferentes ambientes de compilação e tirando proveito de recursos específicos do C++ moderno.

- **Detecção de Plataforma e Arquitetura:**
   - **Mecanismo:** Utiliza macros de pré-processador (`#if defined(WIN32)`, `#if defined(__linux__)`, etc.) para identificar o sistema operacional.
   - **Verificação de Arquitetura:** Contém `static_assert` ou `#error` para garantir que o plugin esteja sendo compilado para x86 (32-bit), uma exigência crítica para a compatibilidade com o SA-MP e o mecanismo de hooking.
   - **Gerenciamento de Exportação de Símbolos:**
      - `SAMP_SDK_EXPORT`: Uma macro definida em `platform.hpp` que se expande para `extern "C"` e, no Linux, adiciona `__attribute__((visibility("default")))`. No Windows, ela apenas garante `extern "C"` porque o SDK utiliza `pragma comment(linker, "/EXPORT:...")` (para MSVC) ou o padrão MinGW para exportar as funções principais.
      - Isso garante que as funções de ciclo de vida do plugin (`Supports`, `Load`, `Unload`, etc.) sejam corretamente exportadas do seu DLL/SO, independentemente do ambiente de compilação, **sem a necessidade de arquivos `.def` ou de adicionar `__attribute__((visibility("default")))` manualmente** na sua implementação.
   - **Exemplo (`platform.hpp` - fragmento relevante):**
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
   - **Exemplo (`samp_sdk.hpp` - fragmento relevante da implementação):**
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

- **Macros de Otimização e Previsão de Branch:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mecanismo:** `__forceinline` (MSVC) ou `__attribute__((always_inline)) inline` (GCC/Clang). Sugere fortemente ao compilador que insira o corpo da função diretamente no local da chamada, eliminando o overhead de uma chamada de função real.
      - **Uso:** Aplicado a funções pequenas e críticas para o desempenho dentro do SDK.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mecanismo:** `[[likely]]` / `[[unlikely]]` (C++20) ou `__builtin_expect` (GCC/Clang). Dicas para o compilador sobre qual caminho de um `if/else` é mais provável de ser tomado.
      - **Impacto:** Ajuda o compilador a gerar código mais eficiente para a previsão de desvios (branch prediction), reduzindo a latência da CPU.
      - **Exemplo (`platform.hpp`):**
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

- **Definições C++ Padrão (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mecanismo:** Macros definidas com base no valor de `__cplusplus` e `_MSVC_LANG`.
   - **Uso:** Permitem que o SDK utilize funcionalidades mais recentes do C++ (como `std::apply` e `if constexpr` do C++17, ou `std::is_same_v` do C++17) quando disponíveis, mantendo a compatibilidade com padrões mais antigos.
   - **Exemplo (`version.hpp` - uso de `if constexpr`):**
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

### 4.3. `function_hook.hpp`: O Motor de Interceptação x86

Este header define o mecanismo de baixo nível para realizar hooks (interceptações) de funções, que é fundamental para a operação do SDK. Ele é estritamente dependente da arquitetura x86 (32-bit).

- **`X86_Detour`**:
   - **Descrição:** Uma classe que encapsula a lógica de sobrescrever o início de uma função na memória com uma instrução de salto para uma função de desvio.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mecanismo:** Em x86, a instrução de salto (`JMP`) relativa geralmente tem 5 bytes: `0xE9` (opcode para JMP near, relative) seguido de 4 bytes que representam o deslocamento (offset) do endereço do alvo em relação à próxima instrução.
      - **Exemplo de instrução:** `E9 XX XX XX XX` (onde `XX` são os bytes do deslocamento).
   - **`Apply(void* target, void* detour)`**:
      - **Ação:** Instala o hook. Primeiro, armazena os `JUMP_INSTRUCTION_SIZE` bytes originais da função `target` (`original_bytes_`). Em seguida, calcula o endereço relativo do `detour` em relação ao `target` e sobrescreve o início de `target` com a instrução `JMP`.
      - **Exemplo do cálculo do endereço relativo:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Endereço do desvio - (Endereço do alvo + Tamanho da instrução de JMP)
         ```
   - **`Revert()`**:
      - **Ação:** Desinstala o hook, restaurando os `original_bytes_` na função `target`.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mecanismo:** No Windows, usa `VirtualProtect`; no Linux, `mprotect`. Estas chamadas de sistema alteram as permissões da página de memória onde a função reside para `EXECUTE_READWRITE` (Windows) ou `PROT_WRITE | PROT_EXEC` (Linux), permitindo que o código seja modificado em tempo de execução.
      - **Exemplo (`Unprotect_Memory`):**
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
   - **Descrição:** Um wrapper C++ `type-safe` para a `X86_Detour`, garantindo que os tipos de ponteiro de função sejam corretos.
   - `Install(void* target, void* detour)`: Encapsula a chamada `X86_Detour::Apply`.
   - `Uninstall()`: Encapsula a chamada `X86_Detour::Revert`.
   - **`Call_Original(Args... args)`**:
      - **Mecanismo de Segurança (Guarda de Recursão):** Esta função é crítica para evitar loops infinitos quando o desvio precisa chamar a função original. Ela **temporariamente desinstala o hook (`detour_.Revert()`)**, chama a função original (`Get_Original()(args...)`), e então **reinstala o hook (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Um contador que garante que o hook só seja reinstalado quando a chamada original de mais alto nível for concluída, permitindo chamadas recursivas seguras da função original (se a função original for recursiva, por exemplo). O `thread_local` garante que o `recursion_guard` seja isolado para cada thread, importante em ambientes multi-threaded.
      - **Exemplo (`Call_Original` com Scope_Guard):**
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

### 4.4. `interceptor_manager.hpp`: O Controlador de Hooks do AMX

Este `singleton` é o centro nervoso da interação do SDK com a máquina virtual AMX do SA-MP. Ele coordena a instalação dos hooks fornecidos por `function_hook.hpp` nas funções da API AMX expostas pelo servidor, redirecionando o fluxo de execução para a lógica do SDK.

- **`Activate()` / `Deactivate()`**:
   - **Descrição:** Métodos públicos para instalar e desinstalar todos os hooks necessários. Chamados em `OnLoad()` e `OnUnload()` do seu plugin, respectivamente.
   - **Mecanismo:** Obtém os ponteiros das funções AMX (como `amx_Register`, `amx_Exec`, etc.) usando `Core::Instance().Get_AMX_Export(...)` e instala os desvios.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Função Hooked:** `amx_Register`
   - **Propósito:** Intercepta o registro de *todas* as nativas (pelo SA-MP, outros plugins ou gamemode).
   - **Ação:** Chama `Interceptor_Manager::Instance().Cache_Natives()` para armazenar os ponteiros e nomes das nativas em um cache interno.
   - **Impacto:** Este cache é fundamental para a performance de `Pawn_Native`, permitindo uma busca extremamente rápida do ponteiro da nativa em vez de uma busca cara na AMX.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Função Hooked:** `amx_Exec`
   - **Propósito:** **Este é o hook mais crítico.** Ele intercepta *qualquer* execução de código na AMX, incluindo a chamada de `publics` do Pawn.
   - **Mecanismo de Interceptação de `Plugin_Public`:**
      1. Quando `amx_Exec` é chamado para uma `public` (ou `AMX_EXEC_MAIN`), o `Amx_Exec_Detour` é executado.
      2. Ele obtém o nome da `public` (usando `Get_Public_Name_By_Index` ou `tl_public_name`).
      3. Consulta o `Public_Dispatcher::Instance().Dispatch()` para verificar se há handlers C++ registrados para este nome.
      4. Se houver handlers, ele os executa. O `Public_Dispatcher` lida com o `marshalling` dos parâmetros da AMX para os tipos C++.
      5. Com base no valor de retorno do `Public_Dispatcher` (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`), ele decide se chama a `amx_Exec` original (`Get_Amx_Exec_Hook().Call_Original(...)`) ou se encerra a execução da `public` Pawn.
      6. **Manipulação da Stack:** Se a execução da `public` Pawn for interrompida (`PLUGIN_PUBLIC_STOP`), o `Amx_Exec_Detour` corrige a stack da AMX (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) para evitar inconsistências.
   - **Exemplo (`Amx_Exec_Detour`):**
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
   - **Função Hooked:** `amx_FindPublic`
   - **Propósito:** Intercepta a busca por `publics` pelo nome.
   - **Mecanismo de "Ghost Publics":** Se `amx_FindPublic` original não encontrar uma `public` no Pawn, mas o `Public_Dispatcher` tiver um handler C++ registrado para aquele nome, este hook retorna `AMX_ERR_NONE` e um `index` especial (`PLUGIN_EXEC_GHOST_PUBLIC`). Isso faz com que a API do SA-MP "pense" que a `public` existe, permitindo que a chamada `amx_Exec` subsequente (para este índice especial) seja interceptada pelo `Amx_Exec_Detour`, que então redireciona para o handler C++.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Usada para passar o nome da `public` para o `Amx_Exec_Detour` quando um "ghost public" é detectado, pois o `amx_Exec` só recebe o índice, não o nome.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Funções Hooked:** `amx_Init` / `amx_Cleanup`
   - **Propósito:** Gerenciar a lista de instâncias `AMX*` ativas.
   - **Ação:** `Amx_Init_Detour` chama `Amx_Manager::Instance().Add_Amx()`, e `Amx_Cleanup_Detour` chama `Amx_Manager::Instance().Remove_Amx()`.

### 4.5. `amx_manager.hpp`: Gerenciando Instâncias `AMX*`

Este `singleton` mantém um registro dinâmico de todas as máquinas virtuais AMX atualmente carregadas no servidor. É essencial para funções que precisam interagir com "todos os scripts" ou encontrar um script específico.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Descrição:** Uma lista de ponteiros para todas as instâncias `AMX*` que foram inicializadas (gamemode e filterscripts).
   - **Gerenciamento:** Populada pelos hooks `Amx_Init_Detour` e esvaziada por `Amx_Cleanup_Detour`.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Propósito:** Protege a `loaded_amx_` contra acesso concorrente em ambientes multi-threaded (embora o SA-MP seja majoritariamente single-thread, esta é uma boa prática de segurança). `std::shared_mutex` permite múltiplos leitores simultaneamente, mas apenas um escritor.
- **`std::atomic<uint32_t> generation_`**:
   - **Propósito:** Um contador que incrementa a cada vez que uma AMX é adicionada ou removida.
   - **Uso:** É utilizado pelo `Caller_Cache` em `callbacks.hpp` para detectar quando a lista de AMXs mudou, invalidando caches de busca de `publics` e garantindo que as chamadas `Pawn_Public` operem sempre com informações atualizadas. Isso otimiza o desempenho ao evitar buscas repetitivas em um estado que não mudou.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Descrição:** Percorre `loaded_amx_` (do mais recente para o mais antigo, o que geralmente coloca o gamemode ou o filterscript mais relevante primeiro) para encontrar a `public` com o nome especificado.
   - **Mecanismo:** Usa `amx::Find_Public` para cada instância `AMX*`.
   - **Impacto:** É a base para `Pawn_Public`.

### 4.6. `public_dispatcher.hpp`: O Roteador de Callbacks `Plugin_Public`

Este `singleton` é o componente que mapeia nomes de `publics` do Pawn para as suas funções C++ `Plugin_Public`.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Chave:** O hash FNV1a do nome da `public` (ex: `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Valor:** Uma `std::vector` de `std::function<cell(AMX*)>`, onde cada `std::function` é um handler C++ registrado para aquela `public`.
   - **Mecanismo:** A `std::vector` permite que múltiplos `Plugin_Public`s sejam registrados para o mesmo callback (ex: vários plugins querendo interceptar `OnPlayerCommandText`). Os handlers são executados em ordem inversa de registro.
- **`Public_Registrar`**:
   - **Mecanismo:** Esta é uma classe template cuja macro `PLUGIN_PUBLIC_REGISTRATION` cria uma instância estática global. No construtor estático (`static bool registered = [...]`), ela registra seu handler `Plugin_Public` no `Public_Dispatcher`. Este é um padrão de "registro estático em tempo de compilação/inicialização".
   - **Exemplo (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Registrar<decltype(&name), &name, hash_##name> registrar_##name;
      ```

- **`Public_Traits` e `Wrapper()`**:
   - **Mecanismo:** `Public_Traits` é um template de trait que, usando metaprogramação, gera uma função `static cell Wrapper(AMX* amx)`.
   - **Propósito:** Esta `Wrapper` é a `Amx_Handler_Func` que o `Public_Dispatcher` realmente armazena e chama. Ela é responsável por:
      1. Chamar `Public_Param_Reader::Get_Public_Params(amx, args...)` para extrair os parâmetros da stack da AMX.
      2. Chamar a sua função `Plugin_Public` C++ real (`func_ptr`) com os parâmetros já convertidos para os tipos C++ corretos.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Descrição:** Um conjunto de funções template recursivas que lêem os valores da stack da AMX e os convertem para os tipos C++ especificados na declaração do `Plugin_Public`.
   - **Mecanismo:** Usa `Get_Stack_Cell()` para acessar os `cell`s na stack. Utiliza `if constexpr` (C++17+) ou `std::is_same<T>::value` (C++14) para aplicar a conversão correta (`amx::AMX_CTOF` para float, `Samp_SDK::Get_String` para string, cast direto para int).

### 4.7. `native.hpp`: Gerenciando e Chamando Nativas do Plugin

Este header é dedicado à criação e ao gerenciamento de nativas C++ que seu plugin expõe ao Pawn.

- **`Native_List_Holder`**:
   - **Descrição:** Um `singleton` global que armazena todas as `Plugin_Native`s declaradas no seu plugin (de todos os arquivos `.cpp` que usam `SAMP_SDK_WANT_AMX_EVENTS`).
   - **`std::vector<Native> natives_`**: Contém objetos `Native` (que armazenam o nome da nativa e o ponteiro para a função C++ `Native_Handler`).
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Um mapa otimizado por hash para buscas rápidas de `Plugin_Native`s internas (usado por `Plugin_Call`).
- **`Native_Registrar`**:
   - **Mecanismo:** Assim como o `Public_Registrar`, esta é uma classe template cuja macro `Plugin_Native` cria uma instância estática global. No seu construtor, ela adiciona a nativa ao `Native_List_Holder`.
   - **Impacto:** Permite que você declare `Plugin_Native`s em múltiplos arquivos `.cpp` sem se preocupar com o registro manual. Todas serão coletadas automaticamente.
- **`Native_Registry`**:
   - **Descrição:** Uma classe auxiliar que, no `OnAmxLoad`, pega a lista completa de `Native`s do `Native_List_Holder` e as formata em um array `AMX_NATIVE_INFO`.
   - **Mecanismo:** Chama `amx::Register(amx, amx_natives_info_.data(), -1)` para registrar todas as suas nativas na instância AMX que acabou de ser carregada.
- **`Plugin_Call_Impl(...)`**:
   - **Descrição:** A implementação subjacente da macro `Plugin_Call`.
   - **Mecanismo:** Utiliza `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` para obter diretamente o ponteiro da função C++.
   - **Ambiente:** Executa a nativa em um ambiente `Amx_Sandbox` (isolado) para gerenciar a stack e heap temporárias, de forma semelhante a como `Pawn_Native` funciona.

### 4.8. `callbacks.hpp` & `amx_memory.hpp`: Chamadas C++ -> Pawn e RAII

Estes headers formam a espinha dorsal para chamar funções Pawn a partir do C++ (`Pawn_*` macros) e garantem a segurança da memória.

- **`Amx_Sandbox`**:
   - **Descrição:** Uma estrutura `thread_local` que simula um ambiente `AMX` minimalista e isolado para chamadas `Pawn_Native` e `Plugin_Call`.
   - **Mecanismo:** Possui sua própria `AMX` struct, `AMX_HEADER` e um `std::vector<unsigned char> heap` para simular a memória de um script. Isso permite que a `amx::Push`, `amx::Allot`, etc., sejam chamadas sem interferir com o estado de scripts Pawn reais em execução.
   - **`thread_local`:** Garante que cada thread tenha sua própria `Amx_Sandbox`, prevenindo condições de corrida se o SDK for usado em um contexto multi-threaded (ex: um futuro pool de threads para operações não-Pawn).
   - **Exemplo (`Amx_Sandbox`):**
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
   - **Descrição:** Um conjunto de funções template sobrecarregadas que gerencia o `marshalling` de *cada* parâmetro C++ para o formato `cell` esperado pela AMX, e vice-versa para parâmetros de saída.
   - **Processamento de Entrada:**
       - Para `int`, `float`, `bool`: Converte diretamente para `cell`.
       - Para `const char*`, `std::string`: Aloca memória na heap da `Amx_Sandbox` (ou AMX real para `Pawn_Public`), copia a string, e empurra o endereço AMX na stack.
   - **Processamento de Saída (`is_output_arg`):**
       - **Mecanismo:** Quando um argumento é uma referência de lvalue não-const (detectado pelo trait `is_output_arg`), o `Parameter_Processor` não empurra o valor, mas sim um *endereço AMX* para uma `cell` alocada temporariamente na heap.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Após a chamada da nativa Pawn, uma lista de lambdas (`post_call_updaters`) é executada. Cada lambda é responsável por ler o valor final da `cell` alocada na AMX e atribuí-lo de volta à variável C++ original (ex: `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mecanismo:** Um `std::integral_constant` (trait de tipo) que, em tempo de compilação, avalia se um tipo de parâmetro C++ é uma referência modificável (ex: `int&`, `float&`, `std::string&`). Isso permite que o `Parameter_Processor` diferencie parâmetros de entrada de saída.
   - **Exemplo (`is_output_arg`):**
      ```cpp
      // Trecho simplificado de callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Descrição:** Uma classe RAII (`Resource Acquisition Is Initialization`) que encapsula a alocação e desalocação de memória na AMX.
   - **Mecanismo:** No construtor, ela chama `amx::Allot` para obter um `amx_addr` e um `phys_addr`. No destrutor, ela chama `amx::Release` para liberar essa memória.
   - **Impacto:** **Crucial para prevenir vazamentos de memória na heap da AMX.** Garante que a memória temporária usada para strings ou parâmetros de saída seja sempre liberada, mesmo que ocorram exceções ou retornos antecipados.

### 4.9. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Acesso Abstraído à AMX

Estes headers fornecem as definições fundamentais e as ferramentas de alto nível para interagir com o Pawn.

- **`amx_defs.h`**:
   - **Conteúdo:** Contém as definições brutas das estruturas da AMX (`AMX`, `AMX_HEADER`), tipos (`cell`, `ucell`), e enums de erro (`AmxError`). Também define `AMX_NATIVE` e `AMX_CALLBACK`.
   - **`SAMP_SDK_PACKED`**: Utiliza atributos de empacotamento (`#pragma pack(push, 1)` / `__attribute__((packed))`) para garantir que as estruturas da AMX tenham o layout de memória correto, fundamental para a interoperabilidade.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Descrição:** A função template principal para invocar as funções da API AMX expostas pelo servidor.
   - **Mecanismo:** Obtém o ponteiro da função através do `Core::Instance().Get_AMX_Export(Index)` e o chama. Centraliza o tratamento de erros se o ponteiro da função não estiver disponível.
   - **Impacto:** Converte chamadas de baixo nível (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) em chamadas C++ idiomáticas e type-safe (`amx::Exec`).
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Descrição:** Funções essenciais para converter valores `cell` para `float` e vice-versa, realizando uma reinterpretação bitwise da memória.
   - **`static_assert`:** Incluem `static_assert` para garantir que `sizeof(cell) == sizeof(float)` em tempo de compilação, prevenindo erros em plataformas com tamanhos de tipo diferentes.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Descrição:** Helper para converter um endereço AMX de string em `std::string`.
   - **Mecanismo:** Primeiro, obtém o endereço físico (`cell* phys_addr`) da string na AMX usando `amx::Get_Addr`. Em seguida, usa `amx::STR_Len` para determinar o comprimento e `amx::Get_String` para copiar os bytes para um `std::string`.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Descrição:** A função base de formatação de strings (`printf`-like) para o SDK.
   - **Mecanismo:** Utiliza `vsnprintf` em duas passagens: primeiro para determinar o tamanho necessário da string, e depois para formatar a string no `std::string` alocado dinamicamente. Isso evita estouros de buffer.

## 5. Compilação e Deploy

### Requisitos de Arquitetura e Plataforma

- Seu plugin **DEVE** ser compilado para a arquitetura **x86 (32-bit)**. O mecanismo de hooking do SDK é específico para esta arquitetura.
- Plataformas Suportadas: Windows (.dll) e Linux (.so).

### Exemplos de Comandos de Compilação

#### **MSVC (Visual Studio)**

1. Crie um novo projeto de "Dynamic-Link Library (DLL)".
2. Nas configurações do projeto, defina a "Plataforma de Solução" para **x86**.
3. Garanta que o C++ Language Standard seja pelo menos C++14.

#### **GCC / Clang (Linux)**

```bash
# Para um plugin chamado 'my_plugin.so' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compila para 32-bit.
- `-shared`: Cria uma biblioteca compartilhada (`.so`).
- `-std=c++17`: Define o padrão C++ para C++17 (pode ser `c++14` ou `c++20`).
- `-O2`: Nível de otimização 2.
- `-fPIC`: Gera código independente de posição, necessário para bibliotecas compartilhadas.
- `-Wall -Wextra`: Ativa avisos adicionais para ajudar a pegar erros.
- `-Wl,--no-undefined`: Impede a criação da biblioteca se houver símbolos indefinidos.

#### **GCC / Clang (MinGW no Windows)**

```bash
# Para um plugin chamado 'my_plugin.dll' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Linka a biblioteca padrão C++ estaticamente. Essencial para evitar que seu plugin dependa de DLLs de runtime específicas do compilador que podem não estar presentes no sistema do usuário.
- `-static-libgcc`: Linka a biblioteca GCC estaticamente.

### Considerações para Distribuição

- **Nome do Arquivo:** Seu plugin deve ter a extensão `.dll` (Windows) ou `.so` (Linux). Ex: `my_plugin.dll`.
- **Localização:** Coloque o arquivo compilado na pasta `plugins/` do seu servidor SA-MP.
- **server.cfg:** Adicione o nome do seu plugin (se for Windows, sem a extensão) à linha `plugins` no `server.cfg`.
   ```
   plugins my_plugin (se for Linux, my_plugin.so)
   ```

## Licença

Copyright © **SA-MP Programming Community**

Este software é licenciado sob os termos da Licença MIT ("Licença"); você pode utilizar este software de acordo com as condições da Licença. Uma cópia da Licença pode ser obtida em: [MIT License](https://opensource.org/licenses/MIT)

### Termos e Condições de Uso

#### 1. Permissões Concedidas

A presente licença concede, gratuitamente, a qualquer pessoa que obtenha uma cópia deste software e arquivos de documentação associados, os seguintes direitos:
* Utilizar, copiar, modificar, mesclar, publicar, distribuir, sublicenciar e/ou vender cópias do software sem restrições
* Permitir que pessoas para as quais o software é fornecido façam o mesmo, desde que sujeitas às condições a seguir

#### 2. Condições Obrigatórias

Todas as cópias ou partes substanciais do software devem incluir:
* O aviso de direitos autorais acima
* Este aviso de permissão
* O aviso de isenção de responsabilidade abaixo

#### 3. Direitos Autorais

O software e toda a documentação associada são protegidos por leis de direitos autorais. A **SA-MP Programming Community** mantém a titularidade dos direitos autorais originais do software.

#### 4. Isenção de Garantias e Limitação de Responsabilidade

O SOFTWARE É FORNECIDO "COMO ESTÁ", SEM GARANTIA DE QUALQUER TIPO, EXPRESSA OU IMPLÍCITA, INCLUINDO, MAS NÃO SE LIMITANDO ÀS GARANTIAS DE COMERCIALIZAÇÃO, ADEQUAÇÃO A UM DETERMINADO FIM E NÃO VIOLAÇÃO. 

EM NENHUMA CIRCUNSTÂNCIA OS AUTORES OU TITULARES DOS DIREITOS AUTORAIS SERÃO RESPONSÁVEIS POR QUALQUER REIVINDICAÇÃO, DANOS OU OUTRA RESPONSABILIDADE, SEJA EM AÇÃO DE CONTRATO, DELITO OU DE OUTRA FORMA, DECORRENTE DE, FORA DE OU EM CONEXÃO COM O SOFTWARE OU O USO OU OUTRAS NEGOCIAÇÕES NO SOFTWARE.

---

Para informações detalhadas sobre a Licença MIT, consulte: https://opensource.org/licenses/MIT