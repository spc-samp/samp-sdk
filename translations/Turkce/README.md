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

SA-MP (San Andreas Multiplayer) Yazılım Geliştirme Kiti (SDK), geliştiricilerin SA-MP sunucusu için eklentiler oluşturmasını sağlayan kapsamlı bir C dosyaları ve header koleksiyonudur. Bu SDK, geliştiricilerin Pawn scriptinde mevcut olanın ötesinde özellikler uygulamasına olanak tanıyan native fonksiyonlar aracılığıyla SA-MP sunucusunun işlevselliğini genişletmek için bir temel sunar.

## Diller

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)

## İçindekiler

- [samp-sdk](#samp-sdk)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [Ana Bileşenler](#ana-bileşenler)
    - [AMX Sistemi](#amx-sistemi)
      - [Ana AMX Header'ları](#ana-amx-headerları)
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
  - [Lisans](#lisans)
    - [Kullanım Şartları ve Koşulları](#kullanım-şartları-ve-koşulları)
      - [1. Lisansın Kapsamı](#1-lisansın-kapsamı)
      - [2. Zorunlu Koşullar](#2-zorunlu-koşullar)
      - [3. Telif Hakları](#3-telif-hakları)
      - [4. Garanti Reddi ve Sorumluluk Sınırlaması](#4-garanti-reddi-ve-sorumluluk-sınırlaması)

## Ana Bileşenler

### AMX Sistemi

AMX (Abstract Machine eXecutor), SA-MP'de Pawn scriptlerini çalıştıran sanal makinedir. SDK, çeşitli C dosyaları ve header'lar aracılığıyla AMX sistemi ile etkileşim için kapsamlı destek sağlar.

#### Ana AMX Header'ları

1. **amx.h**

    AMX ile ilgili tüm işlevselliği birleştiren ana header dosyası:
    - Script çalıştırma için temel fonksiyonlar
    - Bellek yönetimi
    - Native fonksiyon kaydı
    - String işleme
    - UTF-8 desteği

    Önemli fonksiyonlar:
    ```c
    int AMXAPI amx_Init(AMX* amx, void* program);         // Bir AMX örneğini başlatır
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index); // Public fonksiyon çalıştırır
    int AMXAPI amx_Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number); // Native fonksiyonları kaydeder
    ```

2. **amx_platform.h**

    Platform algılama ve yapılandırma için sorumludur:
    ```c
    #if (defined __linux || defined __linux__) && !defined __LINUX__
        #define __LINUX__
    #endif
    #if defined FREEBSD && !defined __FreeBSD__
        #define __FreeBSD__
    #endif
    ```
    - Linux, FreeBSD, OpenBSD ve macOS gibi sistemleri algılar.
    - Unix benzeri sistemler için `sclinux.h` içerir.
    - 64-bit mimarileri tanımlar:
      ```c
      #if defined _LP64 || defined WIN64 || defined _WIN64
          #define __64BIT__
      #endif
      ```
    - GCC sürümünü hesaplar (varsa):
      ```c
      #if defined __GNUC__
          #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #endif
      ```

3. **amx_constants.h**

    AMX işlevselliği için temel sabitleri tanımlar:
    - **Sürümler**:
      ```c
      #define CUR_FILE_VERSION  9   // Geçerli dosya formatı sürümü
      #define MIN_FILE_VERSION  6   // Desteklenen en düşük sürüm
      #define MIN_AMX_VERSION   10  // En düşük AMX sürümü
      #define MAX_FILE_VER_JIT  8   // JIT destekli en yüksek sürüm
      #define MIN_AMX_VER_JIT   8   // JIT destekli en düşük sürüm
      ```
    - **Sihirli Kodlar**:
      ```c
      #define AMX_MAGIC_16    0xf1e2  // 16-bit hücreler için
      #define AMX_MAGIC_32    0xf1e0  // 32-bit hücreler için
      #define AMX_MAGIC_64    0xf1e1  // 64-bit hücreler için
      ```
    - **Hata Kodları**:
      ```c
      enum {
          AMX_ERR_NONE,         // Hata yok
          AMX_ERR_EXIT,         // Script sona erdi
          AMX_ERR_ASSERT,       // Doğrulama başarısız
          AMX_ERR_STACKERR,     // Yığın hatası
          AMX_ERR_BOUNDS,       // Sınır dışı erişim
          AMX_ERR_MEMACCESS,    // Geçersiz bellek erişimi
          AMX_ERR_INVINSTR,     // Geçersiz komut
          AMX_ERR_STACKLOW,     // Yığın çok düşük
          AMX_ERR_HEAPLOW,      // Heap çok düşük
          AMX_ERR_CALLBACK,     // Geri çağrı hatası
          AMX_ERR_NATIVE,       // Native fonksiyon hatası
          AMX_ERR_DIVIDE,       // Sıfıra bölme
          AMX_ERR_SLEEP,        // Uyku modu etkin
          AMX_ERR_INVSTATE,     // Geçersiz durum
          AMX_ERR_MEMORY = 16,  // Yetersiz bellek
          AMX_ERR_FORMAT,       // Geçersiz format
          AMX_ERR_VERSION,      // Uyumsuz sürüm
          AMX_ERR_NOTFOUND,     // Kaynak bulunamadı
          AMX_ERR_INDEX,        // Geçersiz indeks
          AMX_ERR_DEBUG,        // Hata ayıklama hatası
          AMX_ERR_INIT,         // Başlatma başarısız
          AMX_ERR_USERDATA,     // Kullanıcı veri hatası
          AMX_ERR_INIT_JIT,     // JIT başlatma başarısız
          AMX_ERR_PARAMS,       // Geçersiz parametreler
          AMX_ERR_DOMAIN,       // Alan hatası
          AMX_ERR_GENERAL,      // Genel hata
      };
      ```
    - **Bayraklar**:
      ```c
      #define AMX_FLAG_DEBUG      0x02   // Hata ayıklama modu
      #define AMX_FLAG_COMPACT    0x04   // Kompakt kodlama
      #define AMX_FLAG_SLEEP      0x08   // Uyku desteği
      #define AMX_FLAG_NOCHECKS   0x10   // Güvenlik kontrolleri yok
      #define AMX_FLAG_NO_RELOC   0x200  // Yeniden yerleştirme yok
      #define AMX_FLAG_NO_SYSREQD 0x400  // sysreq.d yok
      #define AMX_FLAG_SYSREQN    0x800  // sysreq.n desteği
      #define AMX_FLAG_NTVREG     0x1000 // Native kayıt
      #define AMX_FLAG_JITC       0x2000 // JIT derleme
      #define AMX_FLAG_BROWSE     0x4000 // Tarama modu
      #define AMX_FLAG_RELOC      0x8000 // Yeniden yerleştirme etkin
      ```
    - **Çalıştırma Kodları**:
      ```c
      #define AMX_EXEC_MAIN   (-1)  // Ana fonksiyonu çalıştır
      #define AMX_EXEC_CONT   (-2)  // Çalıştırmaya devam et
      ```

4. **amx_memory.h**

    Bellek tahsisini yönetir:
    - `alloca` desteği:
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
    - Sıkıştırma marjını tanımlar:
      ```c
      #if !defined AMX_COMPACTMARGIN
          #define AMX_COMPACTMARGIN 64
      #endif
      ```

5. **amx_calling.h**

    Çağrı kurallarını tanımlar:
    - Native fonksiyonlar ve API için:
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

    Standart tamsayı türlerini tanımlar:
    - `stdint.h` desteği veya manuel tanımlar:
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

    Kullanışlı makrolar sağlar:
    - **Adres Hesaplama**:
      ```c
      #define amx_Address(amx,addr) \
          (cell*)(((uintptr_t)((amx)->data ? (amx)->data : (amx)->base+(int)((AMX_HEADER *)(amx)->base)->dat)) + ((uintptr_t)(addr)))
      ```
    - **String İşleme**:
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
    - **Parametre Sayısı**:
      ```c
      #define amx_NumParams(params) ((params)[0] / (cell)sizeof(cell))
      ```
    - **Fonksiyon Kaydı**:
      ```c
      #define amx_RegisterFunc(amx, name, func) \
          amx_Register((amx), amx_NativeInfo((name),(func)), 1)
      ```

8. **amx_cell.h**

    Hücre türlerini tanımlar:
    - `PAWN_CELL_SIZE` yapılandırır (varsayılan: 32):
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
    - Kayan nokta desteği:
      ```c
      #if PAWN_CELL_SIZE==32
          #define amx_ftoc(f)   (*(cell*)&(f))  // Float'tan hücreye
          #define amx_ctof(c)   (*(float*)&(c))  // Hücreden float'a
      #elif PAWN_CELL_SIZE==64
          #define amx_ftoc(f)   (*(cell*)&(f))  // Double'dan hücreye
          #define amx_ctof(c)   (*(double*)&(c)) // Hücreden double'a
      #endif
      ```
    - Karakter manipülasyonu:
      ```c
      #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))  // 32-bit için
      ```

9. **amx_structures.h**

    Ana yapıları tanımlar:
    - **AMX**:
      ```c
      typedef struct tagAMX {
          unsigned char _FAR *base;    // Temel adres
          unsigned char _FAR *data;    // Veri segmenti
          AMX_CALLBACK callback;       // Geri çağrı fonksiyonu
          AMX_DEBUG debug;            // Hata ayıklama geri çağrısı
          cell cip;                   // Kod komut işaretçisi
          cell frm;                   // Yığın çerçevesi tabanı
          cell hea;                   // Heap tabanı
          cell hlw;                   // Heap alt sınırı
          cell stk;                   // Yığın işaretçisi
          cell stp;                   // Yığın üstü
          int flags;                  // Bayraklar
          long usertags[AMX_USERNUM]; // Kullanıcı etiketleri
          void _FAR *userdata[AMX_USERNUM]; // Kullanıcı verileri
          int error;                  // Hata kodu
          int paramcount;             // Parametre sayısı
          cell pri;                   // Birincil kayıt
          cell alt;                   // Alternatif kayıt
          cell reset_stk;             // Sıfırlanmış yığın
          cell reset_hea;             // Sıfırlanmış heap
          cell sysreq_d;              // sysreq.d adresi
          #if defined JIT
              int reloc_size;         // Yeniden yerleştirme boyutu
              long code_size;         // Kod boyutu
          #endif
      } AMX;
      ```
    - **AMX_HEADER**:
      ```c
      typedef struct tagAMX_HEADER {
          int32_t size;          // Dosya boyutu
          uint16_t magic;        // İmza
          char    file_version;  // Dosya sürümü
          char    amx_version;   // AMX sürümü
          int16_t flags;         // Bayraklar
          int16_t defsize;       // Tanımlama boyutu
          int32_t cod;           // Kod başlangıcı
          int32_t dat;           // Veri başlangıcı
          int32_t hea;           // Heap başlangıcı
          int32_t stp;           // Yığın üstü
          int32_t cip;           // Başlangıç kod komut işaretçisi
          int32_t publics;       // Public fonksiyonlara ofset
          int32_t natives;       // Native fonksiyonlara ofset
          int32_t libraries;     // Kütüphanelere ofset
          int32_t pubvars;       // Public değişkenlere ofset
          int32_t tags;          // Etiketlere ofset
          int32_t nametable;     // İsim tablosuna ofset
      } AMX_HEADER;
      ```

### Platform Desteği

SDK, çeşitli header'lar aracılığıyla sağlam platforma özgü destek içerir:

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

    İşletim sistemine özgü tanımları yönetir:
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

Birincil eklenti arayüzünü ve destek yapılarını tanımlar:
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

`amxplugin.c` dosyası, SA-MP SDK'nın temel bir bileşenidir ve AMX fonksiyonları için platforma özgü uygulamalar sağlar. Platform ve derleyiciye dayalı iki yaklaşım uygular:

1. **Windows MSVC Uygulaması (32-bit)**
    - Fonksiyon tablosuna doğrudan erişim için assembler ile "çıplak" fonksiyonlar kullanır:
    ```c
    #define NUDE __declspec(naked)
    #define AMX_JUMP_HELPER(index) { 
        _asm { mov eax, pAMXFunctions } 
        _asm { jmp dword ptr[eax + index * 4] } 
    }
    ```

2. **Çapraz Platform Uygulaması**
    - Platform bağımsızlığı için fonksiyon işaretçileri kullanır:
    ```c
    #define DEFINE_AMX_FN_TYPE(name, ret_type, ...) \
        typedef ret_type AMXAPI (*name##_t)(__VA_ARGS__); \
        ret_type AMXAPI name(__VA_ARGS__) { \
            name##_t fn = ((name##_t*)pAMXFunctions)[PLUGIN_AMX_EXPORT_##name]; \
            return fn(__VA_ARGS__); \
        }
    ```

**Ana Özellikler**:

3. **Fonksiyon Tablosu Yönetimi**
    - AMX fonksiyon tablosunu saklamak için statik bir `pAMXFunctions` işaretçisi kullanır.
    - Tüm ana AMX fonksiyonlarına erişim sağlar.
    - Çalışma zamanında fonksiyon çözümlemeyi yönetir.

4. **Platforma Özgü Optimizasyonlar**
    - Windows 32-bit: Çıplak fonksiyonlarla doğrudan assembler uygulaması.
    - Diğer platformlar: Fonksiyon işaretçisi yönlendirmesi.
    - 64-bit sistemler için özel işleme.

5. **Uygulanan Fonksiyon Kategorileri**

    a. **Bellek Yönetimi Fonksiyonları**:
    - `amx_Align16`, `amx_Align32`, `amx_Align64`
    - `amx_Allot`, `amx_Release`

    b. **Çalıştırma Fonksiyonları**:
    - `amx_Exec`, `amx_Callback`
    - `amx_Init`, `amx_InitJIT`
    - `amx_Cleanup`, `amx_Clone`
    
    c. **Sembol Yönetimi**:
    - `amx_FindPublic`, `amx_FindPubVar`
    - `amx_FindNative`, `amx_FindTagId`
    - `amx_GetPublic`, `amx_GetPubVar`
    
    d. **String İşleme**:
    - `amx_GetString`, `amx_SetString`
    - `amx_StrLen`
    - UTF-8 destek fonksiyonları
    
    e. **Hata Ayıklama ve Bilgi**:
    - `amx_SetDebugHook`
    - `amx_Flags`, `amx_MemInfo`
    - `amx_NameLength`

6. **Koşullu Derleme**
    - Farklı platformları ön işlemci yönergeleriyle yönetir.
    - 64-bit sistemler için özel işleme.
    - İsteğe bağlı JIT desteği:
      ```c
      #if defined _I64_MAX || defined HAVE_I64
          DEFINE_AMX_NAKED_FN(uint64_t* AMXAPI amx_Align64(uint64_t* v), 
              PLUGIN_AMX_EXPORT_Align64)
      #endif
      ```

7. **Hata Yönetimi Entegrasyonu**
    - Hata raporlama için `amx_RaiseError` uygular.
    - Fonksiyon çağrıları arasında hata kodlarını korur.
    - AMX hata ayıklama sistemi ile entegre olur.

### AMX Native Fonksiyonları

SDK, native fonksiyonları oluşturma ve yönetme için tam destek sağlar:
```c
typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);

typedef struct tagAMX_NATIVE_INFO {
    const char _FAR *name;
    AMX_NATIVE func;
} AMX_NATIVE_INFO;
```

**Native Fonksiyonlarla Temel İşlemler**:
- `amx_Register` ile kayıt.
- `amx_NumParams` ile parametre erişimi ve doğrulama.
- Dönüş değeri yönetimi.
- `amx_RaiseError` ile hata raporlama.

## Teknik Detaylar

### Bellek Yönetimi

SDK, kapsamlı bellek yönetimi araçları sunar:

1. **amx_memory.h**

    Bellek tahsisi ve platforma özgü işlemleri yönetir:
    ```c
    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif
    ```
    - Bellek sıkıştırması için varsayılan olarak `AMX_COMPACTMARGIN` 64 olarak tanımlar.

2. **amx_alignment.h**

    Bellek hizalama gereksinimlerini yönetir:
    ```c
    #if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
        #define AMX_NO_ALIGN
    #endif 
    ```

### Bellek İşlemleri

SDK, bellek manipülasyonu için birkaç fonksiyon içerir:

1. **Bellek Tahsisi**
    ```c
    int AMXAPI amx_Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
    ```
    - AMX heap'inde bellek tahsis eder.
    - AMX ve fiziksel adresleri döndürür.
    - Hizalama gereksinimlerini yönetir.

2. **Bellek Erişimi**
    ```c
    int AMXAPI amx_GetAddr(AMX* amx, cell amx_addr, cell** phys_addr);
    ```
    - AMX adreslerini fiziksel adreslere dönüştürür.
    - Bellek erişimini doğrular.
    - Bellek sınırlarını yönetir.

3. **Bellek Bilgisi**
    ```c
    int AMXAPI amx_MemInfo(AMX* amx, long* codesize, long* datasize, long* stackheap);
    ```
    - Bellek düzeni bilgisi alır.
    - Segment boyutlarını raporlar.
    - Hata ayıklama ve optimizasyon için faydalıdır.

### Hata Yönetimi

SDK, `amx_constants.h` içinde tanımlı kapsamlı bir hata yönetim sistemi içerir:
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

SDK, çeşitli makrolar ve fonksiyonlar aracılığıyla sağlam string işleme yetenekleri sunar:
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
- `char*` için alternatif:
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

### String İşlemleri

1. **String Uzunluğu**
    ```c
    int AMXAPI amx_StrLen(const cell* cstring, int* length);
    ```
    - String uzunluğunu hesaplar.
    - Paketlenmiş ve paketlenmemiş stringleri yönetir.
    - Karakter cinsinden uzunluk döndürür.

2. **String Dönüşümü**
    ```c
    int AMXAPI amx_SetString(cell* dest, const char* source, int pack, int use_wchar, size_t size);
    ```
    - C stringlerini AMX stringlerine dönüştürür.
    - Paketlenmiş ve paketlenmemiş formatları destekler.
    - Unicode dönüşümünü yönetir.

## Unicode Desteği

SDK, UTF-8 işleme fonksiyonları aracılığıyla tam Unicode desteği sağlar:
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
    - UTF-8 kodlu stringleri doğrular.
    - Karakter cinsinden string uzunluğunu raporlar.
    - Kodlama hatalarını tespit eder.

2. **Karakter Dönüşümü**
    ```c
    int AMXAPI amx_UTF8Get(const char* string, const char** endptr, cell* value);
    ```
    - Unicode karakterleri çıkarır.
    - Çok baytlı dizileri yönetir.
    - Ayrıştırma hatalarını raporlar.

## Çapraz Platform Uyumluluğu

SDK, çapraz platform uyumluluğunu şu yollarla sağlar:

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

3. **Platformdan Bağımsız Türler**
    - Tutarlılık için `amx_types.h` içinde tanımlanmıştır.

## Sistem Gereksinimleri

SDK, birden çok platformu ve derleyiciyi destekler:
- Windows (MSVC, MinGW)
- Linux (GCC)
- FreeBSD
- OpenBSD
- macOS

### Derleyici Desteği

1. **Microsoft Visual C++**
    - Pragma yönetimi.
    - Uyarı bastırma.
    - `amx_calling.h` aracılığıyla çağrı kuralları.

2. **GCC**
    - Tanısal kontroller.
    - Özellik tanımlamaları.
    - Platforma özgü optimizasyonlar.

3. **Clang**
    - Uyarı yapılandırmaları.
    - Çapraz platform uyumluluğu.
    - Modern C++ özellikleri.

## En İyi Uygulamalar

SA-MP SDK'yı kullanırken aşağıdaki en iyi uygulamaları göz önünde bulundurun:

1. **Bellek Yönetimi**
    - Her zaman tahsis edilen kaynakları temizleyin.
    - Uygun bellek hizalaması kullanın.
    - Bellek hatalarını zarif bir şekilde yönetin.
    - Heap kullanımını izleyin.
    - Bellek sınırlarını doğru bir şekilde kontrol edin.
    - Sık tahsisler için bellek havuzları kullanın.
    - Kaynakları tahsis sırasının tersine temizleyin.

2. **Hata Yönetimi**
    - AMX fonksiyonlarından dönen değerleri kontrol edin.
    - Native fonksiyonlarda uygun hata yönetimi uygulayın.
    - Sağlanan hata sabitlerini kullanın.
    - Hataları uygun şekilde günlüğe kaydedin.
    - Hata kurtarma mekanizmaları uygulayın.
    - Anlamlı hata mesajları sağlayın.
    - Sisteme özgü hataları yönetin.

3. **Çapraz Platform Geliştirme**
    - Platformdan bağımsız türler kullanın.
    - Platforma özgü kod için sağlanan makroları kullanın.
    - Birden çok platformda test edin.
    - Endianness farklılıklarını yönetin.
    - Uygun yol ayırıcıları kullanın.
    - Dosya sistemi farklılıklarını göz önünde bulundurun.
    - Platforma özgü optimizasyonlar uygulayın.

4. **Performans Hususları**
    - Uygun hücre boyutları kullanın.
    - Verimli string işleme uygulayın.
    - Native fonksiyon çağrılarını optimize edin.
    - Bellek tahsislerini en aza indirin.
    - Uygun veri yapıları kullanın.
    - Gerektiğinde önbellekleme uygulayın.
    - Kritik kod yollarını profilleyin.

`amxplugin.c` işlevselliği ile çalışırken:

1. **Platforma Özgü Geliştirme**
    - Fonksiyon uygulamalarındaki platform farklılıklarını göz önünde bulundurun.
    - Hem 32-bit hem de 64-bit sistemlerde test edin.
    - Platforma özgü hizalama gereksinimlerini yönetin.
    - Kullanmadan önce fonksiyon tablosu işaretçisini doğrulayın.
    - Her platform için uygun hata kontrolü uygulayın.
    - Farklı uygulamaların performans etkilerini değerlendirin.

2. **Fonksiyon Tablosu Yönetimi**
    - Kullanmadan önce fonksiyon tablosunu başlatın.
    - Fonksiyon kullanılabilirliğini doğrulayın.
    - Eksik fonksiyonları zarif bir şekilde yönetin.
    - Uygun temizleme prosedürleri uygulayın.
    - Sık kullanılan fonksiyon işaretçilerini önbelleğe alın.
    - Fonksiyon tablosu bütünlüğünü doğrulayın.

3. **Hata Yönetimi**
    - Platforma özgü kod için uygun hata kontrolü uygulayın.
    - Hizalama hatalarını uygun şekilde yönetin.
    - Fonksiyon tablosu girişlerini doğrulayın.
    - Anlamlı hata mesajları sağlayın.
    - Kurtarma mekanizmaları uygulayın.
    - Platforma özgü hataları günlüğe kaydedin.

## Dahili Yapılar

### AMX Header Yapısı

```c
typedef struct tagAMX_HEADER {
    int32_t size;          // "Dosya" boyutu
    uint16_t magic;        // İmza
    char    file_version;  // Dosya formatı sürümü
    char    amx_version;   // Gerekli AMX sürümü
    int16_t flags;         // Bayraklar
    int16_t defsize;       // Tanımlama kaydı boyutu
    int32_t cod;           // COD başlangıç değeri - kod bloğu
    int32_t dat;           // DAT başlangıç değeri - veri bloğu
    int32_t hea;           // HEA başlangıç değeri - heap başlangıcı
    int32_t stp;           // STP başlangıç değeri - yığın üstü
    int32_t cip;           // CIP başlangıç değeri - kod komut işaretçisi
    int32_t publics;       // Public fonksiyonlara ofset
    int32_t natives;       // Native fonksiyon tablosuna ofset
    int32_t libraries;     // Kütüphanelere ofset
    int32_t pubvars;       // Public değişkenlere ofset
    int32_t tags;          // Etiketlere ofset
    int32_t nametable;     // İsim tablosuna ofset
} AMX_HEADER;
```

Bu yapı, AMX dosya formatını ve sanal makinenin scriptleri nasıl yükleyip çalıştırdığını anlamak için kritik öneme sahiptir.

## Gelişmiş Özellikler

### JIT Derleme Desteği

SDK, Just-In-Time derleme desteği içerir:
```c
int AMXAPI amx_InitJIT(AMX* amx, void* reloc_table, void* native_code);
```

### Hata Ayıklama Arayüzü

Hata ayıklama desteği şu şekilde sağlanır:
```c
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
int AMXAPI amx_SetDebugHook(AMX* amx, AMX_DEBUG debug);
```

### Public Fonksiyon Arayüzü

SDK, public fonksiyonlarla çalışmak için tam destek sağlar:

1. **Public Fonksiyonları Bulma**
    ```c
    int AMXAPI amx_FindPublic(AMX* amx, const char* funcname, int* index);
    ```
    - İsimle public fonksiyonları bulur.
    - Fonksiyon indeksini döndürür.
    - Fonksiyon varlığını doğrular.

2. **Public Fonksiyonları Çalıştırma**
    ```c
    int AMXAPI amx_Exec(AMX* amx, cell* retval, int index);
    ```
    - Public fonksiyonları çalıştırır.
    - Dönüş değerlerini yönetir.
    - Çalıştırma bağlamını yönetir.

## Versiyon Bilgisi

SDK, uyumluluk kontrolü için sürüm sabitleri içerir:
```c
#define CUR_FILE_VERSION  9
#define MIN_FILE_VERSION  6
#define MIN_AMX_VERSION   10
#define MAX_FILE_VER_JIT  8
#define MIN_AMX_VER_JIT   8
```

### Versiyon Uyumluluğu

SDK, uyumluluğu şu yollarla sürdürür:
1. Dosya sürüm doğrulaması.
2. AMX sürüm doğrulaması.
3. JIT uyumluluk kontrolü.
4. Özellik algılama.
5. Platforma özgü sürüm yönetimi.

## Lisans

**Mülkiyet Bildirimi**: Bu depoda bulunan **SA-MP SDK**, aşağıda detaylı olarak belirtildiği üzere farklı telif hakkı sahiplerine sahip dosyalardan oluşmaktadır:
- **San Andreas Multiplayer (SA-MP)** için özel olan `amxplugin.c`, `plugin.h` ve `plugincommon.h` dosyaları, SA-MP’nin orijinal yaratıcıları olan **Kalcor ve muhtemelen SA-MP Ekibi üyelerinin** fikri mülkiyetidir.
- **Pawn Abstract Machine (AMX)** ile ilgili dosyalar, bunlarla sınırlı olmamak üzere `amx.h`, `amx.c`, `osdefs.h` ve Pawn programlama dili için gerekli diğer başlıklar ve uygulamalar, Hollanda merkezli **CompuPhase**’in, Pawn’ın orijinal yaratıcısının fikri mülkiyetidir.
- `sclinux.h` dosyası muhtemelen **SELinux veya özelleştirilmiş bir Linux çekirdek alt sisteminden** kaynaklanmaktadır ve Unix benzeri bir ortamın parçasıdır.
- `getch.h` ve `getch.c` dosyaları, karakter girişi için `termios` gibi standart işlevlere dayanan POSIX uyumlu bağımsız uygulamalardır.
- **SA-MP Programlama Topluluğu (SPC)**, **SA-MP SDK**’nın orijinal içeriği, **CompuPhase** dosyaları, `sclinux.h` veya `getch.h/c` üzerinde herhangi bir telif hakkı iddia etmez. Bu deponun tek amacı, adil kullanım ve topluluk uygulamalarına uygun olarak eklenti geliştiricileri için materyale erişimi ve organizasyonu kolaylaştırmaktır.

**İyileştirmelere Uygulanabilir Lisans**: **SA-MP Programlama Topluluğu (SPC)** tarafından oluşturulan ve bu depoya dahil edilen herhangi bir iyileştirme, değişiklik veya ek dosya, **MIT Lisansı** şartları altında lisanslanmıştır. MIT Lisansı yalnızca bu belirli katkılara uygulanır ve **SA-MP SDK**’nın orijinal içeriğine, **CompuPhase** dosyalarına, `sclinux.h` veya `getch.h/c`’ye uygulanmaz. MIT Lisansı’nın bir kopyası şu adreste bulunabilir: [MIT License](https://opensource.org/licenses/MIT).

**Orijinal Dosyaların Lisansları**:
- `amx.h`, `amx.c`, `osdefs.h` (**CompuPhase**’e ait) ve `sclinux.h` (muhtemelen **SELinux veya özelleştirilmiş bir çekirdeğe ait**) dosyaları **Apache License 2.0** altında lisanslanmıştır. Lisans detayları şu adreste bulunabilir: [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0).
- `getch.h` ve `getch.c` dosyaları **Mozilla Public License 2.0 (MPL-2.0)** altında lisanslanmıştır. Lisans detayları şu adreste bulunabilir: [MPL-2.0](https://www.mozilla.org/en-US/MPL/2.0/).
- `amxplugin.c`, `plugin.h` ve `plugincommon.h` dosyaları (**Kalcor ve muhtemelen SA-MP Ekibi üyelerine ait**) belirtilmiş bir lisansa sahip değildir.

### Kullanım Şartları ve Koşulları

#### 1. Lisansın Kapsamı
MIT Lisansı, **SPC** tarafından oluşturulan iyileştirmelerin veya ek dosyaların bir kopyasını elde eden herhangi bir kişiye ücretsiz olarak aşağıdaki hakları verir:
- Bu katkıları kısıtlama olmaksızın kullanma, kopyalama, değiştirme, birleştirme, yayınlama, dağıtma, alt lisans verme ve/veya satma.
- Bu katkıların sağlandığı kişilere, aşağıdaki koşullara tabi olarak aynı şeyi yapma izni verme.

#### 2. Zorunlu Koşullar
**SPC** katkılarının tüm kopyaları veya önemli kısımları şunları içermelidir:
- İyileştirmeler için **SPC** telif hakkı bildirimi.
- Bu izin bildirimi.
- Aşağıdaki sorumluluk reddi bildirimi.

#### 3. Telif Hakları
**SPC** tarafından oluşturulan iyileştirmeler ve ek dosyalar telif hakkı yasalarıyla korunur ve **SPC**, bu belirli katkılar için telif haklarının sahipliğini korur. `amxplugin.c`, `plugin.h` ve `plugincommon.h` dosyaları **Kalcor ve muhtemelen SA-MP Ekibi üyelerinin** mülkiyetinde kalır. **Pawn Abstract Machine (AMX)** dosyaları, `osdefs.h` dahil, **CompuPhase**’in mülkiyetinde kalır. `sclinux.h` dosyası muhtemelen **SELinux veya özelleştirilmiş bir Linux çekirdek alt sistemine** aittir ve `getch.h/c` bağımsız bir POSIX uygulamasıdır. **SPC**, bu orijinal içerikler üzerinde herhangi bir yazarlık hakkı iddia etmez.

#### 4. Garanti Reddi ve Sorumluluk Sınırlaması
**SPC** KATKILARI “OLDUĞU GİBİ” SAĞLANIR, AÇIK VEYA ZIMNİ HİÇBİR GARANTİ OLMAKSIZIN, BUNLARLA SINIRLI OLMAMAK ÜZERE TİCARİ ELVERİŞLİLİK, BELİRLİ BİR AMACA UYGUNLUK VE İHLAL ETMEME GARANTİLERİ DAHİL.

HİÇBİR DURUMDA **SPC** VEYA İYİLEŞTİRMELERİN TELİF HAKKI SAHİPLERİ, SÖZLEŞME, HAKSIZ FİİL VEYA BAŞKA BİR ŞEKİLDE, **SPC** KATKILARINDAN, BUNLARIN KULLANIMINDAN VEYA BUNLARLA İLGİLİ DİĞER İŞLEMLERDEN KAYNAKLANAN, DIŞINDA VEYA BUNLARLA BAĞLANTILI HERHANGİ BİR TALEP, ZARAR VEYA DİĞER SORUMLULUKTAN SORUMLU OLMAYACAKTIR.

**Orijinal Dosyalar Hakkında Not**: Kullanıcılar, **SA-MP SDK** dosyalarının kullanımının geçerli lisanslara uygun olduğundan emin olmaktan sorumludur:
- `amx.h`, `amx.c`, `osdefs.h` ve `sclinux.h` için **Apache License 2.0** şartlarını izleyin.
- `getch.h` ve `getch.c` için **Mozilla Public License 2.0 (MPL-2.0)** şartlarını izleyin.
- `amxplugin.c`, `plugin.h` ve `plugincommon.h` için, belirtilmiş bir lisans olmadığından, kullanıcılar **Kalcor ve muhtemelen SA-MP Ekibi üyeleri** tarafından belirlenen herhangi bir şartı veya geçerli yasaları yerine getirmelidir. **SPC**, bu orijinal içeriklerin kullanımı için hiçbir garanti sunmaz veya sorumluluk kabul etmez.

---

MIT Lisansı hakkında detaylı bilgi için bkz.: [MIT License](https://opensource.org/licenses/MIT)