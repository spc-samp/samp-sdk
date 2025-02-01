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

O SA-MP (San Andreas Multiplayer) Software Development Kit (SDK) é uma coleção abrangente de arquivos C, headers e itens que permitem aos desenvolvedores criar plugins para o servidor SA-MP. Este SDK fornece uma base para estender a funcionalidade do servidor SA-MP através de funções nativas, permitindo que os desenvolvedores implementem recursos além do que está disponível no script Pawn.

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

- [samp-sdk](#samp-sdk)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Componentes Principais](#componentes-principais)
    - [Sistema AMX](#sistema-amx)
      - [Headers AMX Principais](#headers-amx-principais)
    - [Suporte a Plataformas](#suporte-a-plataformas)
    - [Sistema de Plugin](#sistema-de-plugin)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [Funções Nativas AMX](#funções-nativas-amx)
  - [Detalhes Técnicos](#detalhes-técnicos)
    - [Gerenciamento de Memória](#gerenciamento-de-memória)
    - [Operações de Memória](#operações-de-memória)
    - [Tratamento de Erros](#tratamento-de-erros)
    - [Manipulação de Strings](#manipulação-de-strings)
    - [Operações com Strings](#operações-com-strings)
  - [Suporte a Unicode](#suporte-a-unicode)
    - [Operações Unicode](#operações-unicode)
  - [Compatibilidade Multiplataforma](#compatibilidade-multiplataforma)
  - [Requisitos do Sistema](#requisitos-do-sistema)
    - [Suporte a Compiladores](#suporte-a-compiladores)
  - [Melhores Práticas](#melhores-práticas)
  - [Estruturas Internas](#estruturas-internas)
    - [Estrutura do Header AMX](#estrutura-do-header-amx)
  - [Recursos Avançados](#recursos-avançados)
    - [Suporte à Compilação JIT](#suporte-à-compilação-jit)
    - [Interface de Depuração](#interface-de-depuração)
    - [Interface de Função Pública](#interface-de-função-pública)
  - [Informações de Versão](#informações-de-versão)
    - [Compatibilidade de Versão](#compatibilidade-de-versão)
  - [Licença](#licença)
    - [Termos e Condições de Uso](#termos-e-condições-de-uso)
      - [1. Permissões Concedidas](#1-permissões-concedidas)
      - [2. Condições Obrigatórias](#2-condições-obrigatórias)
      - [3. Direitos Autorais](#3-direitos-autorais)
      - [4. Isenção de Garantias e Limitação de Responsabilidade](#4-isenção-de-garantias-e-limitação-de-responsabilidade)

## Componentes Principais

### Sistema AMX

O AMX (Abstract Machine eXecutor) é a máquina virtual que executa scripts Pawn no SA-MP. O SDK fornece suporte extensivo para interação com AMX através de vários arquivos C e headers:

#### Headers AMX Principais

1. **amx.h**

    O header principal que consolida todas as funcionalidades relacionadas ao AMX. Inclui:
    - Funções principais do AMX para execução de script
    - Gerenciamento de memória
    - Registro de funções nativas
    - Manipulação de strings
    - Suporte a UTF-8

    Funções principais incluem:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    ```

2. **amx_cell.h**

    Define os tipos de dados fundamentais usados no sistema AMX:
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

    Contém estruturas essenciais para operação do AMX:

    ```c
    typedef struct tagAMX {
        unsigned char _FAR *base;    // Endereço base
        unsigned char _FAR *data;    // Segmento de dados
        AMX_CALLBACK callback;       // Função de callback
        AMX_DEBUG debug;            // Callback de debug
        cell cip;                   // Ponteiro de instrução de código
        cell frm;                   // Base do frame da pilha
        cell hea;                   // Base do heap
        cell stk;                   // Ponteiro da pilha
        // ... campos adicionais
    } AMX;
    ```

### Suporte a Plataformas

O SDK inclui tratamento robusto específico para plataformas através de vários headers:

1. **amx_platform.h**

    Fornece detecção e configuração de plataforma:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    Lida com definições específicas do sistema operacional:
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

### Sistema de Plugin

#### plugincommon.h

Define a interface principal do plugin e estruturas de suporte:

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

O arquivo `amxplugin.c` é um componente crucial do SA-MP SDK que fornece implementações específicas de plataforma para funções AMX. Implementa duas abordagens diferentes baseadas na plataforma e compilador:

1. **Implementação Windows MSVC (32-bit)**
    - Usa funções naked com assembly para acesso direto à tabela de funções
    - Fornece desempenho otimizado através de jumps diretos para funções AMX
    - Exemplo de estrutura:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Implementação Multiplataforma**
    - Usa ponteiros de função para independência de plataforma
    - Implementa um sistema baseado em macros para definições de funções
    - Exemplo de estrutura:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

Características Principais:

3. **Gerenciamento de Tabela de Funções**
    - Usa um ponteiro estático `pAMXFunctions` para armazenar a tabela de funções AMX
    - Fornece acesso a todas as funções principais do AMX
    - Lida com resolução de função em tempo de execução

4. **Otimizações Específicas de Plataforma**
    - Windows 32-bit: Usa funções naked para implementação direta em assembly
    - Outras plataformas: Usa indireção de ponteiro de função
    - Tratamento especial para sistemas 64-bit

5. **Categorias de Funções Implementadas**

    a. Funções de Gerenciamento de Memória:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. Funções de Execução:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. Gerenciamento de Símbolos:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. Manipulação de Strings:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - Funções de suporte UTF-8
    
    e. Debug e Informações:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Compilação Condicional**
    - Lida com diferentes plataformas através de diretivas de pré-processador
    - Tratamento especial para sistemas 64-bit
    - Suporte JIT opcional
    ```c
    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
            PLUGIN_AMX_EXPORT_Align64)
    #endif
    ```

7. **Integração de Tratamento de Erros**
    - Implementa `amx_RaiseError` para relatório de erros
    - Preserva códigos de erro através de chamadas de função
    - Integra com sistema de debug AMX

### Funções Nativas AMX

O SDK fornece suporte abrangente para criar e gerenciar funções nativas:

```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

Operações principais de funções nativas:
- Registro através de `amx_Register`
- Acesso e validação de parâmetros
- Manipulação de valor de retorno
- Relatório de erros

## Detalhes Técnicos

### Gerenciamento de Memória

O SDK fornece facilidades abrangentes de gerenciamento de memória:

1. **amx_memory.h**

   Lida com alocação de memória e operações específicas de plataforma:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```

2. **amx_alignment.h**

    Gerencia requisitos de alinhamento de memória:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Operações de Memória

O SDK inclui várias funções para manipulação de memória:

1. **Alocação de Memória**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - Aloca memória no heap AMX
    - Retorna endereços AMX e físicos
    - Lida com requisitos de alinhamento

2. **Acesso à Memória**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - Converte endereços AMX para endereços físicos
    - Valida acesso à memória
    - Lida com limites de memória

3. **Informações de Memória**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Recupera informações de layout de memória
    - Reporta tamanhos de segmento
    - Útil para depuração e otimização

### Tratamento de Erros

O SDK inclui um sistema abrangente de tratamento de erros definido em `amx_constants.h`:

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

### Manipulação de Strings

O SDK fornece capacidades robustas de manipulação de strings através de vários macros e funções:

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

### Operações com Strings

1. **Comprimento de String**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - Calcula comprimento da string
    - Lida com strings empacotadas e não empacotadas
    - Retorna comprimento em caracteres

2. **Conversão de String**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - Converte strings C para strings AMX
    - Suporta formatos empacotados e não empacotados
    - Lida com conversão Unicode

## Suporte a Unicode

O SDK inclui suporte abrangente a Unicode através de funções de manipulação UTF-8:

```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Operações Unicode

1. **Validação UTF-8**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - Valida strings codificadas em UTF-8
    - Reporta comprimento da string em caracteres
    - Detecta erros de codificação

2. **Conversão de Caracteres**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Extrai caracteres Unicode
    - Lida com sequências multi-byte
    - Reporta erros de análise

## Compatibilidade Multiplataforma

O SDK garante compatibilidade multiplataforma através de:

1. **Tratamento de Endianness**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Tratamento de Caminhos**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

## Requisitos do Sistema

O SDK suporta múltiplas plataformas e compiladores:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Suporte a Compiladores

1. **Microsoft Visual C++**
   - Tratamento de pragmas
   - Supressão de avisos
   - Convenções de chamada

2. **GCC**
   - Controles de diagnóstico
   - Especificações de atributos
   - Otimizações específicas de plataforma

3. **Clang**
   - Configurações de aviso
   - Compatibilidade multiplataforma
   - Recursos modernos de C++

## Melhores Práticas

Ao usar o SA-MP SDK, considere as seguintes melhores práticas:

1. **Gerenciamento de Memória**
   - Sempre limpe recursos alocados
   - Use alinhamento de memória apropriado
   - Trate erros de memória graciosamente
   - Monitore uso do heap
   - Implemente verificação adequada de limites de memória
   - Use pools de memória para alocações frequentes
   - Limpe recursos na ordem inversa da alocação

2. **Tratamento de Erros**
   - Verifique valores de retorno das funções AMX
   - Implemente tratamento adequado de erros em funções nativas
   - Use as constantes de erro fornecidas
   - Registre erros apropriadamente
   - Implemente mecanismos de recuperação de erros
   - Forneça mensagens de erro significativas
   - Trate erros específicos do sistema

3. **Desenvolvimento Multiplataforma**
   - Use tipos independentes de plataforma
   - Utilize macros fornecidos para código específico de plataforma
   - Teste em múltiplas plataformas
   - Lide com diferenças de endianness
   - Use separadores de caminho apropriados
   - Considere diferenças do sistema de arquivos
   - Implemente otimizações específicas de plataforma

4. **Considerações de Performance**
   - Use tamanhos de cell apropriados
   - Implemente manipulação eficiente de strings
   - Otimize chamadas de funções nativas
   - Minimize alocações de memória
   - Use estruturas de dados apropriadas
   - Implemente cache quando apropriado
   - Profile caminhos críticos de código

Ao trabalhar com funcionalidade `amxplugin.c`:

1. **Desenvolvimento Específico de Plataforma**
   - Considere diferenças de plataforma nas implementações de função
   - Teste em sistemas 32-bit e 64-bit
   - Lide com requisitos de alinhamento específicos de plataforma
   - Valide ponteiro da tabela de funções antes do uso
   - Implemente verificação de erro apropriada para cada plataforma
   - Considere implicações de performance de diferentes implementações

2. **Gerenciamento de Tabela de Funções**
   - Inicialize tabela de funções antes do uso
   - Verifique disponibilidade de função
   - Lide graciosamente com funções ausentes
   - Implemente procedimentos adequados de limpeza
   - Cache ponteiros de função frequentemente usados
   - Valide integridade da tabela de funções

3. **Tratamento de Erros**
   - Implemente verificação de erro adequada para código específico de plataforma
   - Trate erros de alinhamento apropriadamente
   - Valide entradas da tabela de funções
   - Forneça mensagens de erro significativas
   - Implemente mecanismos de recuperação
   - Registre erros específicos de plataforma

## Estruturas Internas

### Estrutura do Header AMX

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // Tamanho do "arquivo"
    uint16_t magic;        // Assinatura
    char    file_version;  // Versão do formato do arquivo
    char    amx_version;   // Versão AMX requerida
    int16_t flags;         // Flags
    int16_t defsize;      // Tamanho de um registro de definição
    int32_t cod;          // Valor inicial de COD - bloco de código
    int32_t dat;          // Valor inicial de DAT - bloco de dados
    int32_t hea;          // Valor inicial de HEA - início do heap
    int32_t stp;          // Valor inicial de STP - topo da pilha
    int32_t cip;          // Valor inicial de CIP - ponteiro de instrução de código
    int32_t publics;      // Offset para funções públicas
    int32_t natives;      // Offset para tabela de funções nativas
    int32_t libraries;    // Offset para bibliotecas
    int32_t pubvars;      // Offset para variáveis públicas
    int32_t tags;         // Offset para tags
    int32_t nametable;    // Offset para tabela de nomes
} AMX_HEADER;
```

Esta estrutura é crucial para entender o formato de arquivo AMX e como a máquina virtual carrega e executa scripts.

## Recursos Avançados

### Suporte à Compilação JIT

O SDK inclui suporte para compilação Just-In-Time:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Interface de Depuração

Suporte à depuração é fornecido através de:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Interface de Função Pública

O SDK fornece suporte abrangente para trabalhar com funções públicas:

1. **Encontrando Funções Públicas**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - Localiza funções públicas por nome
    - Retorna índice da função
    - Valida existência da função

2. **Executando Funções Públicas**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Executa funções públicas
    - Lida com valores de retorno
    - Gerencia contexto de execução

## Informações de Versão

O SDK inclui constantes de versão para verificação de compatibilidade:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Compatibilidade de Versão

O SDK mantém compatibilidade através de:
1. Verificação de versão do arquivo
2. Validação de versão AMX
3. Verificação de compatibilidade JIT
4. Detecção de recursos
5. Tratamento de versão específico de plataforma

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