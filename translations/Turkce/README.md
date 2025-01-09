# SA-MP SDK

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Language](https://img.shields.io/badge/Language-C-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![SDK](https://img.shields.io/badge/SA--MP-SDK-orange.svg)](https://github.com/spc-samp/samp-sdk)
[![Platform Windows](https://img.shields.io/badge/Windows-0078D6?style=flat&logo=windows&logoColor=white)](https://github.com/spc-samp/samp-sdk)
[![Platform Linux](https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black)](https://github.com/spc-samp/samp-sdk)
[![Platform FreeBSD](https://img.shields.io/badge/FreeBSD-AB2B28?style=flat&logo=freebsd&logoColor=white)](https://github.com/spc-samp/samp-sdk)
[![AMX](https://img.shields.io/badge/AMX-Powered-yellow.svg)](https://github.com/spc-samp/samp-sdk)
[![Native Support](https://img.shields.io/badge/Natives-Supported-success.svg)](https://github.com/spc-samp/samp-sdk)
[![Memory Safe](https://img.shields.io/badge/Memory-Safe-red.svg)](https://github.com/spc-samp/samp-sdk)

SA-MP (San Andreas Multiplayer) Software Development Kit (SDK), geliştiricilerin SA-MP sunucusu için eklentiler oluşturmasına olanak tanıyan kapsamlı bir C dosyaları ve header'lar koleksiyonudur. Bu SDK, geliştiricilerin Pawn scriptinde mevcut olanın ötesinde özellikler uygulamasına olanak tanıyan native fonksiyonlar aracılığıyla SA-MP sunucusunun işlevselliğini genişletmek için bir temel sağlar.

## Diller

- Português: [README](../../README.md)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)

## İçindekiler

- [SA-MP SDK](#sa-mp-sdk)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [Temel Bileşenler](#temel-bileşenler)
    - [AMX Sistemi](#amx-sistemi)
      - [Temel AMX Header'ları](#temel-amx-headerları)
    - [Platform Desteği](#platform-desteği)
    - [Eklenti Sistemi](#eklenti-sistemi)
      - [plugincommon.h](#plugincommonh)
      - [amxplugin.c](#amxpluginc)
    - [AMX Native Fonksiyonları](#amx-native-fonksiyonları)
  - [Teknik Detaylar](#teknik-detaylar)
    - [Bellek Yönetimi](#bellek-yönetimi)
    - [Bellek İşlemleri](#bellek-i̇şlemleri)
    - [Hata Yönetimi](#hata-yönetimi)
    - [String İşleme](#string-i̇şleme)
    - [String İşlemleri](#string-i̇şlemleri)
  - [Unicode Desteği](#unicode-desteği)
    - [Unicode İşlemleri](#unicode-i̇şlemleri)
  - [Çapraz Platform Uyumluluğu](#çapraz-platform-uyumluluğu)
  - [Sistem Gereksinimleri](#sistem-gereksinimleri)
    - [Derleyici Desteği](#derleyici-desteği)
  - [En İyi Uygulamalar](#en-i̇yi-uygulamalar)
  - [Dahili Yapılar](#dahili-yapılar)
    - [AMX Header Yapısı](#amx-header-yapısı)
  - [Gelişmiş Özellikler](#gelişmiş-özellikler)
    - [JIT Derleme Desteği](#jit-derleme-desteği)
    - [Hata Ayıklama Arayüzü](#hata-ayıklama-arayüzü)
    - [Public Fonksiyon Arayüzü](#public-fonksiyon-arayüzü)
  - [Versiyon Bilgisi](#versiyon-bilgisi)
    - [Versiyon Uyumluluğu](#versiyon-uyumluluğu)

## Temel Bileşenler

### AMX Sistemi

AMX (Abstract Machine eXecutor), SA-MP'de Pawn scriptlerini çalıştıran sanal makinedir. SDK, çeşitli C ve header dosyaları aracılığıyla AMX ile etkileşim için kapsamlı destek sağlar:

#### Temel AMX Header'ları

1. **amx.h**

    Tüm AMX ile ilgili işlevselliği birleştiren ana header dosyası. Şunları içerir:
    - Script yürütme için temel AMX fonksiyonları
    - Bellek yönetimi
    - Native fonksiyon kaydı
    - String işleme
    - UTF-8 desteği

    Temel fonksiyonlar:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
    ```

2. **amx_cell.h**

    AMX sisteminde kullanılan temel veri tiplerini tanımlar:
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

    AMX işlemi için gerekli yapıları içerir:

    ```c
    typedef struct tagAMX {
        unsigned char _FAR *base;    // Temel adres
        unsigned char _FAR *data;    // Veri segmenti
        AMX_CALLBACK callback;       // Callback fonksiyonu
        AMX_DEBUG debug;            // Debug callback
        cell cip;                   // Kod talimat işaretçisi
        cell frm;                   // Stack frame tabanı
        cell hea;                   // Heap tabanı
        cell stk;                   // Stack işaretçisi
        // ... ek alanlar
    } AMX;
    ```

### Platform Desteği

SDK, çeşitli header'lar aracılığıyla sağlam platform-spesifik işleme içerir:

1. **amx_platform.h**

    Platform algılama ve yapılandırma sağlar:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```

2. **osdefs.h**

    İşletim sistemine özgü tanımlamaları yönetir:
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

### Eklenti Sistemi

#### plugincommon.h

Temel eklenti arayüzünü ve destek yapılarını tanımlar:

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

`amxplugin.c` dosyası, AMX fonksiyonlarının platform-spesifik uygulamalarını sağlayan SA-MP SDK'nın kritik bir bileşenidir. Platform ve derleyiciye bağlı olarak iki farklı yaklaşım uygular:

1. **Windows MSVC Uygulaması (32-bit)**
    - Doğrudan fonksiyon tablosu erişimi için assembly ile çıplak fonksiyonlar kullanır
    - AMX fonksiyonlarına doğrudan atlamalarla optimize edilmiş performans sağlar
    - Örnek yapı:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Çapraz Platform Uygulaması**
    - Platform bağımsızlığı için fonksiyon işaretçileri kullanır
    - Fonksiyon tanımlamaları için makro tabanlı bir sistem uygular
    - Örnek yapı:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

Temel Özellikler:

3. **Fonksiyon Tablosu Yönetimi**
    - AMX fonksiyon tablosunu saklamak için statik bir `pAMXFunctions` işaretçisi kullanır
    - Tüm temel AMX fonksiyonlarına erişim sağlar
    - Çalışma zamanında fonksiyon çözümlemeyi yönetir

4. **Platform-Spesifik Optimizasyonlar**
    - Windows 32-bit: Doğrudan assembly uygulaması için çıplak fonksiyonlar kullanır
    - Diğer platformlar: Fonksiyon işaretçisi yönlendirmesi kullanır
    - 64-bit sistemler için özel işleme

5. **Uygulanan Fonksiyon Kategorileri**

    a. Bellek Yönetimi Fonksiyonları:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. Yürütme Fonksiyonları:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. Sembol Yönetimi:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. String İşleme:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - UTF-8 destek fonksiyonları
    
    e. Hata Ayıklama ve Bilgi:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Koşullu Derleme**
    - Önişlemci yönergeleri aracılığıyla farklı platformları yönetir
    - 64-bit sistemler için özel işleme
    - İsteğe bağlı JIT desteği
    ```c
    #if defined _I64_MAX || defined HAVE_I64
        DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
            PLUGIN_AMX_EXPORT_Align64)
    #endif
    ```

7. **Hata Yönetimi Entegrasyonu**
    - Hata raporlama için `amx_RaiseError` uygular
    - Fonksiyon çağrıları arasında hata kodlarını korur
    - AMX hata ayıklama sistemi ile entegre olur

### AMX Native Fonksiyonları

SDK, native fonksiyonlar oluşturmak ve yönetmek için kapsamlı destek sağlar:

```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

Temel native fonksiyon işlemleri:
- `amx_Register` üzerinden kayıt
- Parametre erişimi ve doğrulama
- Dönüş değeri işleme
- Hata raporlama

## Teknik Detaylar

### Bellek Yönetimi

SDK kapsamlı bellek yönetimi olanakları sağlar:

1. **amx_memory.h**

   Bellek tahsisi ve platforma özgü bellek işlemlerini yönetir:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```

2. **amx_alignment.h**

    Bellek hizalama gereksinimlerini yönetir:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Bellek İşlemleri

SDK bellek manipülasyonu için çeşitli fonksiyonlar içerir:

1. **Bellek Tahsisi**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - AMX heap'inde bellek tahsis eder
    - Hem AMX hem de fiziksel adresleri döndürür
    - Hizalama gereksinimlerini yönetir

2. **Bellek Erişimi**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - AMX adreslerini fiziksel adreslere dönüştürür
    - Bellek erişimini doğrular
    - Bellek sınırlarını yönetir

3. **Bellek Bilgisi**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Bellek düzeni bilgisini alır
    - Segment boyutlarını raporlar
    - Hata ayıklama ve optimizasyon için faydalıdır

### Hata Yönetimi

SDK, `amx_constants.h` içinde kapsamlı bir hata yönetim sistemi içerir:

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

### String İşleme

SDK, çeşitli makrolar ve fonksiyonlar aracılığıyla güçlü string işleme yetenekleri sağlar:

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

### String İşlemleri

1. **String Uzunluğu**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - String uzunluğunu hesaplar
    - Paketlenmiş ve paketlenmemiş stringleri yönetir
    - Karakter cinsinden uzunluğu döndürür

2. **String Dönüşümü**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - C stringlerini AMX stringlerine dönüştürür
    - Paketlenmiş ve paketlenmemiş formatları destekler
    - Unicode dönüşümünü yönetir

## Unicode Desteği

SDK, UTF-8 işleme fonksiyonları aracılığıyla kapsamlı Unicode desteği içerir:

```c
int AMXAPI amx_UTF8Check(const char* string, int* length);
int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
int AMXAPI amx_UTF8Len(const cell* cstr, int* length);
int AMXAPI amx_UTF8Put(char* string, char** endptr, int maxchars, cell value);
```

### Unicode İşlemleri

1. **UTF-8 Doğrulama**
    ```c
    int AMXAPI amx_UTF8Check(const char* string, int* length);
    ```
    - UTF-8 kodlu stringleri doğrular
    - Karakter cinsinden string uzunluğunu raporlar
    - Kodlama hatalarını tespit eder

2. **Karakter Dönüşümü**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Unicode karakterleri çıkarır
    - Çok baytlı dizileri yönetir
    - Ayrıştırma hatalarını raporlar

## Çapraz Platform Uyumluluğu

SDK, şunlar aracılığıyla çapraz platform uyumluluğunu sağlar:

1. **Endianness Yönetimi**
    ```c
    #ifndef BYTE_ORDER
        #if defined(UCLINUX)
            #define BYTE_ORDER BIG_ENDIAN
        #else
            #define BYTE_ORDER LITTLE_ENDIAN
        #endif
    #endif
    ```

2. **Yol Yönetimi**
    ```c
    #if defined(__MSDOS__) || defined(__WIN32__) || defined(_Windows)
        #define DIRSEP_CHAR '\\'
    #elif defined(macintosh)
        #define DIRSEP_CHAR ':'
    #else
        #define DIRSEP_CHAR '/'
    #endif
    ```

## Sistem Gereksinimleri

SDK birden çok platformu ve derleyiciyi destekler:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Derleyici Desteği

1. **Microsoft Visual C++**
   - Pragma yönetimi
   - Uyarı bastırma
   - Çağrı kuralları

2. **GCC**
   - Tanı kontrolleri
   - Özellik tanımlamaları
   - Platform-spesifik optimizasyonlar

3. **Clang**
   - Uyarı yapılandırmaları
   - Çapraz platform uyumluluğu
   - Modern C++ özellikleri

## En İyi Uygulamalar

SA-MP SDK'yı kullanırken aşağıdaki en iyi uygulamaları göz önünde bulundurun:

1. **Bellek Yönetimi**
   - Her zaman tahsis edilen kaynakları temizleyin
   - Uygun bellek hizalaması kullanın
   - Bellek hatalarını düzgün şekilde yönetin
   - Heap kullanımını izleyin
   - Uygun bellek sınırları kontrolü uygulayın
   - Sık tahsisler için bellek havuzları kullanın
   - Kaynakları tahsis sırasının tersine temizleyin

2. **Hata Yönetimi**
   - AMX fonksiyonlarından dönüş değerlerini kontrol edin
   - Native fonksiyonlarda uygun hata yönetimi uygulayın
   - Sağlanan hata sabitlerini kullanın
   - Hataları uygun şekilde günlüğe kaydedin
   - Hata kurtarma mekanizmaları uygulayın
   - Anlamlı hata mesajları sağlayın
   - Sisteme özgü hataları yönetin

3. **Çapraz Platform Geliştirme**
   - Platform-bağımsız tipler kullanın
   - Platform-spesifik kod için sağlanan makroları kullanın
   - Birden çok platformda test edin
   - Endianness farklılıklarını yönetin
   - Uygun yol ayırıcıları kullanın
   - Dosya sistemi farklılıklarını dikkate alın
   - Platform-spesifik optimizasyonlar uygulayın

4. **Performans Düşünceleri**
   - Uygun hücre boyutları kullanın
   - Verimli string işleme uygulayın
   - Native fonksiyon çağrılarını optimize edin
   - Bellek tahsislerini minimize edin
   - Uygun veri yapıları kullanın
   - Uygun yerlerde önbelleğe alma uygulayın
   - Kritik kod yollarını profilleyin

`amxplugin.c` işlevselliğiyle çalışırken:

1. **Platform-Spesifik Geliştirme**
   - Fonksiyon uygulamalarında platform farklılıklarını dikkate alın
   - Hem 32-bit hem de 64-bit sistemlerde test edin
   - Platform-spesifik hizalama gereksinimlerini yönetin
   - Kullanmadan önce fonksiyon tablosu işaretçisini doğrulayın
   - Her platform için uygun hata kontrolü uygulayın
   - Farklı uygulamaların performans etkilerini dikkate alın

2. **Fonksiyon Tablosu Yönetimi**
   - Kullanmadan önce fonksiyon tablosunu başlatın
   - Fonksiyon kullanılabilirliğini doğrulayın
   - Eksik fonksiyonları düzgün şekilde yönetin
   - Uygun temizleme prosedürleri uygulayın
   - Sık kullanılan fonksiyon işaretçilerini önbelleğe alın
   - Fonksiyon tablosu bütünlüğünü doğrulayın

3. **Hata Yönetimi**
   - Platform-spesifik kod için uygun hata kontrolü uygulayın
   - Hizalama hatalarını uygun şekilde yönetin
   - Fonksiyon tablosu girişlerini doğrulayın
   - Anlamlı hata mesajları sağlayın
   - Kurtarma mekanizmaları uygulayın
   - Platform-spesifik hataları günlüğe kaydedin

## Dahili Yapılar

### AMX Header Yapısı

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // "Dosya" boyutu
    uint16_t magic;        // İmza
    char    file_version;  // Dosya format versiyonu
    char    amx_version;   // Gerekli AMX versiyonu
    int16_t flags;         // Bayraklar
    int16_t defsize;      // Tanımlama kaydı boyutu
    int32_t cod;          // COD'un başlangıç değeri - kod bloğu
    int32_t dat;          // DAT'ın başlangıç değeri - veri bloğu
    int32_t hea;          // HEA'nın başlangıç değeri - heap başlangıcı
    int32_t stp;          // STP'nin başlangıç değeri - stack üstü
    int32_t cip;          // CIP'in başlangıç değeri - kod talimat işaretçisi
    int32_t publics;      // Public fonksiyonlara offset
    int32_t natives;      // Native fonksiyon tablosuna offset
    int32_t libraries;    // Kütüphanelere offset
    int32_t pubvars;      // Public değişkenlere offset
    int32_t tags;         // Etiketlere offset
    int32_t nametable;    // İsim tablosuna offset
} AMX_HEADER;
```

Bu yapı, AMX dosya formatını ve sanal makinenin scriptleri nasıl yüklediğini ve çalıştırdığını anlamak için çok önemlidir.

## Gelişmiş Özellikler

### JIT Derleme Desteği

SDK, Anında Derleme için destek içerir:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Hata Ayıklama Arayüzü

Hata ayıklama desteği şunlar aracılığıyla sağlanır:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Public Fonksiyon Arayüzü

SDK, public fonksiyonlarla çalışmak için kapsamlı destek sağlar:

1. **Public Fonksiyonları Bulma**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - İsme göre public fonksiyonları bulur
    - Fonksiyon indeksini döndürür
    - Fonksiyon varlığını doğrular

2. **Public Fonksiyonları Çalıştırma**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Public fonksiyonları çalıştırır
    - Dönüş değerlerini yönetir
    - Çalıştırma bağlamını yönetir

## Versiyon Bilgisi

SDK, uyumluluk kontrolü için versiyon sabitleri içerir:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Versiyon Uyumluluğu

SDK, uyumluluğu şunlar aracılığıyla sürdürür:
1. Dosya sürümü kontrolü  
2. AMX sürüm doğrulaması  
3. JIT uyumluluk doğrulaması  
4. Özellik algılama  
5. Platforma özgü sürüm yönetimi  