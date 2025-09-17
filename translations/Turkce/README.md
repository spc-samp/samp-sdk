# SAMP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**SA-MP için eklenti ve modül geliştirmeye yönelik modern, yalnızca başlık içeren (header-only) ve yüksek seviyeli bir C++ SDK'sı.**

</div>

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

- [SAMP SDK](#samp-sdk)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [1. Giriş ve Tasarım Felsefesi](#1-giriş-ve-tasarım-felsefesi)
    - [SA-MP'nin Standart C API'si ile İlgili Sorun](#sa-mpnin-standart-c-apisi-ile-i̇lgili-sorun)
    - [SAMP SDK'nın Çözümü: Güvenlik ve Performans ile Soyutlama](#samp-sdknın-çözümü-güvenlik-ve-performans-ile-soyutlama)
    - [Yalnızca Başlık Modeli (Header-Only): Avantajlar ve Etkileri](#yalnızca-başlık-modeli-header-only-avantajlar-ve-etkileri)
  - [2. Kurulum ve Ortam](#2-kurulum-ve-ortam)
    - [Derleme Gereksinimleri](#derleme-gereksinimleri)
    - [Önerilen Dosya Yapısı](#önerilen-dosya-yapısı)
    - [Temel Yapılandırma Makroları\*\*](#temel-yapılandırma-makroları)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP Tanımları ve Sabitleri (`samp_defs.hpp`)](#sa-mp-tanımları-ve-sabitleri-samp_defshpp)
  - [3. Kapsamlı API Kullanım Kılavuzu](#3-kapsamlı-api-kullanım-kılavuzu)
    - [3.1. Eklenti Yaşam Döngüsü](#31-eklenti-yaşam-döngüsü)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Pawn Etkinliklerini Yakalama](#32-plugin_public-pawn-etkinliklerini-yakalama)
      - [Sözdizimi ve Bildirim](#sözdizimi-ve-bildirim)
      - [Otomatik Parametre Marshalling](#otomatik-parametre-marshalling)
      - [Akış Kontrolü: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#akış-kontrolü-plugin_public_continue-vs-plugin_public_stop)
    - [3.3. `Plugin_Native`: C++'da Yerel Fonksiyonlar Oluşturma](#33-plugin_native-cda-yerel-fonksiyonlar-oluşturma)
      - [Sözdizimi ve Sabit İmza](#sözdizimi-ve-sabit-i̇mza)
      - [Yerel Fonksiyonların Otomatik Kaydı](#yerel-fonksiyonların-otomatik-kaydı)
      - [Parametre Çıkarma: `Register_Parameters` vs. `Native_Params`](#parametre-çıkarma-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Tam API: `Get`, `Get_REF`, `Set_REF`)](#native_params-tam-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Değerlerin Döndürülmesi](#değerlerin-döndürülmesi)
    - [3.4. `Pawn_*` Makroları: C++'dan Pawn Fonksiyonlarını Çağırma](#34-pawn_-makroları-cdan-pawn-fonksiyonlarını-çağırma)
      - [`Pawn_Native(YerelFonksiyonAdı, ...)`](#pawn_nativeyerelfonksiyonadı-)
      - [`Pawn_Public(GenelFonksiyonAdı, ...)`](#pawn_publicgenelfonksiyonadı-)
      - [`Pawn(FonksiyonAdı, ...)`](#pawnfonksiyonadı-)
      - [Sözdizimi ve Kurallar](#sözdizimi-ve-kurallar)
      - [Giriş Parametrelerinin Marshalling'i](#giriş-parametrelerinin-marshallingi)
      - [Çıkış Parametrelerinin Marshalling'i (Referanslar: `int&`, `float&`, `std::string&`)](#çıkış-parametrelerinin-marshallingi-referanslar-int-float-stdstring)
      - [`Callback_Result` Nesnesi: Tam Analiz](#callback_result-nesnesi-tam-analiz)
      - [**3.5. `Plugin_Module`: Dinamik Modül Yönetimi**](#35-plugin_module-dinamik-modül-yönetimi)
      - [Söz Dizimi ve Amaç](#söz-dizimi-ve-amaç)
      - [Modülün Yaşam Döngüsü](#modülün-yaşam-döngüsü)
      - [Modülerleştirmenin Avantajları](#modülerleştirmenin-avantajları)
    - [3.6. `Plugin_Call`: Eklentinin Dahili Yerel Fonksiyonlarını Çağırma](#36-plugin_call-eklentinin-dahili-yerel-fonksiyonlarını-çağırma)
      - [Sözdizimi ve Performans Avantajları](#sözdizimi-ve-performans-avantajları)
    - [**3.7. SDK Yardımcı Fonksiyonları**](#37-sdk-yardımcı-fonksiyonları)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Önerilen)](#stdstring-plugin_formatconst-char-format--önerilen)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Uygulama Detayı)](#stdstring-samp_sdkformatconst-char-format--uygulama-detayı)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. **SDK'nın Dahili Anatomisi ve Mimarisi**](#4-sdknın-dahili-anatomisi-ve-mimarisi)
    - [4.1. `core.hpp`: Minimalist Temel](#41-corehpp-minimalist-temel)
    - [**4.2. `platform.hpp` ve `version.hpp`: Uyumluluk ve Metadatalar**](#42-platformhpp-ve-versionhpp-uyumluluk-ve-metadatalar)
    - [4.3. `function_hook.hpp`: x86 Yakalama Motoru](#43-function_hookhpp-x86-yakalama-motoru)
    - [4.4. `interceptor_manager.hpp`: AMX Hook Kontrolcüsü](#44-interceptor_managerhpp-amx-hook-kontrolcüsü)
    - [4.5. `amx_manager.hpp`: `AMX*` Örneklerini Yönetme](#45-amx_managerhpp-amx-örneklerini-yönetme)
    - [4.6. `public_dispatcher.hpp`: `Plugin_Public` Geri Çağrı Yönlendiricisi](#46-public_dispatcherhpp-plugin_public-geri-çağrı-yönlendiricisi)
    - [4.7. `native.hpp`: Eklenti Yerel Fonksiyonlarını Yönetme ve Çağırma](#47-nativehpp-eklenti-yerel-fonksiyonlarını-yönetme-ve-çağırma)
    - [4.8. `callbacks.hpp` \& `amx_memory.hpp`: C++ -\> Pawn Çağrıları ve RAII](#48-callbackshpp--amx_memoryhpp-c---pawn-çağrıları-ve-raii)
    - [4.9. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: Soyutlanmış AMX Erişimi](#49-amx_apihpp--amx_helpershpp--amx_defsh-soyutlanmış-amx-erişimi)
  - [5. Derleme ve Dağıtım](#5-derleme-ve-dağıtım)
    - [Mimari ve Platform Gereksinimleri](#mimari-ve-platform-gereksinimleri)
    - [Derleme Komut Örnekleri](#derleme-komut-örnekleri)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (Windows'ta MinGW)**](#gcc--clang-windowsta-mingw)
    - [Dağıtım Hususları](#dağıtım-hususları)
  - [Lisans](#lisans)
    - [Kullanım Şartları ve Koşulları](#kullanım-şartları-ve-koşulları)
      - [1. Verilen İzinler](#1-verilen-i̇zinler)
      - [2. Zorunlu Koşullar](#2-zorunlu-koşullar)
      - [3. Telif Hakları](#3-telif-hakları)
      - [4. Garanti Reddi ve Sorumluluk Sınırlaması](#4-garanti-reddi-ve-sorumluluk-sınırlaması)

## 1. Giriş ve Tasarım Felsefesi

### SA-MP'nin Standart C API'si ile İlgili Sorun

SA-MP eklenti API'si bir C programlama arayüzüdür. İşlevsel ve temel olmasına rağmen, düşük seviyeli programlamanın doğal zorluklarını sunar:
- **Manuel Bellek Yönetimi:** `amx_Allot` ve `amx_Release` gibi fonksiyonlar, geliştiricinin AMX yığınında belleği açıkça ayırmasını ve serbest bırakmasını gerektirir. Bu, yaygın bir bellek sızıntısı ve çalışma zamanı hatası kaynağıdır.
- **Zayıf Türleme ve Manuel Dönüşümler:** Parametreler `cell`'lerden oluşan bir dizi olarak geçirilir ve `cell`, `int`, `float` ve `char*` arasında açık (ve genellikle güvensiz) dönüşümleri zorlar.
- **Uzunluk ve Tekrarlayan Kod:** `cell* params` dizisinden birden çok parametreyi çıkarmak, dizelerin boyutlarını yönetmek ve C++'dan Pawn'a geri çağrılar için AMX yığınını yönetmek tekrarlayan kod gerektirir.
- **Arayüz Kırılganlığı:** Derleme zamanı doğrulamasının (type safety) olmaması, parametre geçişi veya türlerdeki hataların yürütülene kadar fark edilmeyebileceği, çökmelere veya tanımsız davranışlara neden olabileceği anlamına gelir.

### SAMP SDK'nın Çözümü: Güvenlik ve Performans ile Soyutlama

SAMP SDK, bu sorunları güçlü bir C++ soyutlama katmanı sağlayarak ele alır:
- **RAII (Resource Acquisition Is Initialization):** AMX'deki belleğin otomatik yönetimi. `Amx_Scoped_Memory` ayrılan belleğin serbest bırakılmasını garanti eder.
- **Tip Güvenliği:** C++ ve Pawn arasında parametrelerin otomatik ve güvenli dönüşümü. Doğrudan `int`, `float`, `std::string` ile ilgilenirsiniz.
- **Kısa ve İdiyomatik Sözdizimi:** Makrolar ve şablonlar, geleneksel C API'sinden daha çok modern C++'ya benzeyen temiz bir API sağlar.
- **Sağlam Yakalama:** Gelişmiş bir hooking motoru, Pawn geri çağrılarının (`Plugin_Public`) şeffaf bir şekilde yakalanmasına ve yerel fonksiyonların dinamik olarak kaydedilmesine olanak tanır.
- **Yüksek Performans:** Soyutlamaların yükünü en aza indirmek için derleme zamanı hashing (FNV1a), fonksiyon önbelleğe alma ve `thread_local` optimizasyonları yoğun bir şekilde kullanılır.

### Yalnızca Başlık Modeli (Header-Only): Avantajlar ve Etkileri

SDK yalnızca başlık dosyalarından (`.hpp`, `.h`) oluşur.
- **Avantajlar:**
   - **Basitleştirilmiş Entegrasyon:** Oluşturulacak, bağlanacak veya dağıtılacak kütüphane yoktur. Sadece başlıkları eklemeniz yeterlidir.
   - **Derleyici Optimizasyonları:** Derleyici, SDK ve eklenti kodunun tamamını görür, bu da agresif satır içi kodlama ve bağlama zamanı optimizasyonlarına izin verir, bu da daha hızlı ikili dosyalara yol açabilir.
- **Etkileri:**
   - **Derleme Zamanı:** Çok büyük projeler için, SDK kodunun tekrarlı dahil edilmesi nedeniyle derleme daha uzun sürebilir. Bu, dahil etme korumaları ve C++'nın "yalnızca ihtiyacınız olanı dahil edin" doğası ile hafifletilir.
   - **Uygulama Makroları:** Sembollerin yeniden tanımlanmasını önlemek için `SAMP_SDK_IMPLEMENTATION` makrosuna olan ihtiyaç, yalnızca başlık modelinin bir sonucudur.

## 2. Kurulum ve Ortam

### Derleme Gereksinimleri

- **C++ Derleyici:** C++14 veya üstü ile uyumlu (SDK, belirli optimizasyonlar için C++14, C++17 ve C++20 özelliklerini kullanır, ancak C++14 minimumdur).
   - GCC (sürüm 7+)
   - Clang (sürüm 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Mimari:** **x86 (32-bit)**. SA-MP yalnızca bu mimaride çalışır. SDK, yanlış mimari algılanırsa derleme hataları verecek olan `platform.hpp` içinde kontroller içerir.
- **İşletim Sistemi:** Windows veya Linux.

### Önerilen Dosya Yapısı

Açıklık ve düzen için, SDK'yı `samp-sdk` adında bir alt klasörde düzenlemek yaygındır.

```
meu_plugin/
├── samp-sdk/
│   ├── // Diğer SDK dosyaları
│   └── samp_sdk.hpp             // Dahil edilecek ana başlık
│
├── src/
│   ├── main.cpp                  // SAMP_SDK_IMPLEMENTATION'ın tanımlandığı yer
│   └── my_custom_logic.cpp       // İsteğe bağlı, kodu düzenlemek için
│
└── CMakeLists.txt (veya .vcxproj, Makefile)
```

### Temel Yapılandırma Makroları**

Bu makroları her zaman `samp_sdk.hpp`'yi dahil etmeden *önce* tanımlayın.

#### `SAMP_SDK_IMPLEMENTATION`

- **Amaç:** Bu `.cpp` dosyasının eklenti dışa aktarma fonksiyonlarının (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`) uygulamalarını oluşturması gerektiğini derleyiciye işaret eder. **SDK, bu fonksiyonlar için `.def` dosyalarına (Windows'ta) veya `__attribute__((visibility("default")))` bildirimlerine (Linux'ta) gerek kalmadan bu fonksiyonların dışa aktarılmasını otomatik olarak halleder.**
- **Teknik Etki:** Bu makro olmadan, bağlayıcı gerekli dışa aktarmaları bulamaz ve SA-MP sunucusu eklentinizi yükleyemez.
- **Temel Kural:** **Bu makroyu projenizin tamamında YALNIZCA BİR `.cpp` dosyasında tanımlayın.** Birden fazla dosyada tanımlamak, "yinelenen sembol" bağlama hatasına neden olur.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // Makro, SDK'nın gerekli fonksiyonları otomatik olarak dışa aktarmasını sağlar.
#include "samp-sdk/samp_sdk.hpp"

// ... eklenti kodunuz ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Amaç:** SDK'nın AMX (Pawn sanal makinesi) ortamıyla etkileşime ilişkin işlevlerini etkinleştirir.
- **Etkinleştirilen İşlevler:**
   - `Plugin_Native` kullanarak C++ yerel fonksiyonlarının bildirimi ve kaydı.
   - `OnAmxLoad(AMX* amx)` ve `OnAmxUnload(AMX* amx)` geri çağrıları.
   - Eklentinin kendi yerel fonksiyonlarını çağırmak için `Plugin_Call` makrosu.
- **Teknik Etki:** Bu makro tanımlandığında, SDK tüm `Plugin_Native`'lerinizi otomatik olarak toplar. `Supports()` fonksiyonunda, `SUPPORTS_AMX_NATIVES` bayrağı otomatik olarak eklenir.
- **Esneklik:** **Bu makroyu birden çok `.cpp` dosyasında tanımlayabilirsiniz.** SDK'nın statik kayıt sistemi (`Native_Registrar`), farklı derleme birimlerinden gelen tüm yerel fonksiyonları tek bir global listede birleştirir.

```cpp
// my_natives.cpp (main.cpp'den ayrı bir dosya olabilir)
#define SAMP_SDK_WANT_AMX_EVENTS // Sadece Plugin_Native'i etkinleştirmek için
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Amaç:** Sunucu tarafından düzenli olarak çağrılan `OnProcessTick()` geri çağrısını etkinleştirir.
- **Teknik Etki:** `Supports()` fonksiyonuna `SUPPORTS_PROCESS_TICK` bayrağını otomatik olarak ekler.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Sunucunun her "tick"inde (örneğin 20ms) yürütülen mantık
    // Burada ağır işlemlere dikkat edin!
}
```

### SA-MP Tanımları ve Sabitleri (`samp_defs.hpp`)

Bu dosya, `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST` gibi SA-MP'nin bilinen tüm sabitlerini ve limitlerini sağlar. `samp_sdk.hpp` tarafından otomatik olarak dahil edilir ve kodun uyumluluğunu ve okunabilirliğini sağlamak için kullanılmalıdır.

## 3. Kapsamlı API Kullanım Kılavuzu

### 3.1. Eklenti Yaşam Döngüsü

Aşağıdaki fonksiyonlar, SDK tarafından otomatik olarak dışa aktarılan eklentinizin giriş ve çıkış noktalarıdır.

#### `bool OnLoad()`

- **Açıklama:** Eklentinizin başarıyla belleğe yüklendikten sonra SA-MP sunucusu tarafından çağrılan ilk fonksiyon.
- **Kullanım:** Herhangi bir sistemi başlatmak, yapılandırmaları yüklemek, veritabanı bağlantılarını açmak veya modülleri (`Plugin_Module`) yüklemek için idealdir.
- **Dönüş:**
   - `true`: Eklenti başarıyla başlatıldı ve yükleme devam ediyor.
   - `false`: Eklenti başlatılırken başarısız oldu. Yükleme iptal edilecek ve eklenti boşaltılacaktır.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("MeuPlugin v1.0 başlatılıyor...");

    // Örnek: Bir modül yükleme (ayrıntılar bölüm 3.5'te)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Veritabanı Modülü yüklendi.")) {
        Samp_SDK::Log("HATA: Veritabanı modülü yüklenirken başarısız oldu!");

        return false; // Ana eklentinin yüklemesini iptal eder
    }

    return true;
}
```

#### `void OnUnload()`

- **Açıklama:** Eklentinizin bellekten boşaltılmadan önce SA-MP sunucusu tarafından çağrılan son fonksiyon.
- **Kullanım:** Kaynakları temizlemek, bağlantıları kapatmak, durumları kaydetmek ve hiçbir kaynağın sızdırılmamasını sağlamak için idealdir. SDK, modüllerin (`Plugin_Module`) boşaltılmasını otomatik olarak yönetir.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MeuPlugin boşaltıldı. Kaynaklar serbest bırakılıyor...");
    // Plugin_Module aracılığıyla yüklenen modüller için manuel bir işlem gerekmez;
    // SDK bunu halleder.
}
```

#### `unsigned int GetSupportFlags()`

- **Açıklama:** SA-MP sunucusuna eklentinizin hangi özellikleri desteklediğini ve kullanmak istediğini bildirir.
- **Kullanım:** **Her zaman `SUPPORTS_VERSION` (veya `SAMP_PLUGIN_VERSION`) döndürün.** Diğer bayraklar (`SUPPORTS_AMX_NATIVES`, `SUPPORTS_PROCESS_TICK`), `SAMP_SDK_WANT_AMX_EVENTS` ve `SAMP_SDK_WANT_PROCESS_TICK` makroları tanımlanmışsa SDK tarafından otomatik olarak eklenir. Bu, bakımı basitleştirir ve hataları önler.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // SDK gerekli bayrakları otomatik olarak ekler.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Gerektirir:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Açıklama:** Sunucuda yeni bir Pawn scripti (bir Gamemode veya Filterscript) her yüklendiğinde ve başlatıldığında çağrılır.
- **Kullanım:** Her AMX scripti için özel mantığa ihtiyacınız varsa, örneğin özel yerel fonksiyonları kaydetmek için (ancak `Plugin_Native` bunu otomatik olarak yapar) veya scripte özgü verileri başlatmak için.

```cpp
// main.cpp (SAMP_SDK_WANT_AMX_EVENTS tanımlanmışsa)
void OnAmxLoad(AMX* amx) {
    // amx, yeni yüklenen scriptin bir örneğini temsil eder.
    // Örneğin, bu scriptte belirli bir public'i çağırabilirsiniz:
    // Pawn_Public_OnAmx("OnMyPluginLoaded", amx); // Daha gelişmiş bir API'nin varsayımsal örneği.
    Samp_SDK::Log("AMX Script yüklendi: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Gerektirir:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Açıklama:** Bir Pawn scripti sunucudan boşaltıldığında çağrılır.
- **Kullanım:** Belirli bir `AMX*` ile ayırdığınız veya ilişkilendirdiğiniz tüm kaynakları temizlemek için.

```cpp
// main.cpp (SAMP_SDK_WANT_AMX_EVENTS tanımlanmışsa)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Script boşaltıldı: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Gerektirir:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Açıklama:** Sunucunun her "tick"inde (genellikle saniyede 20 kez veya her 50ms'de bir) tekrar tekrar çağrılır.
- **Kullanım:** Sürekli arka plan mantığı, zamanlayıcılar, oyuncu olaylarına bağlı olmayan durum güncellemeleri veya veri senkronizasyonu için.
- **Dikkat:** Burada engelleme yapan veya yoğun hesaplama gerektiren işlemlerden kaçının, aksi takdirde sunucuda gecikmeye neden olabilir.

```cpp
// main.cpp (SAMP_SDK_WANT_PROCESS_TICK tanımlanmışsa)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Her 10 saniyede bir (20 tick/saniye * 10 saniye = 200 tick)
        Samp_SDK::Log("Sunucu %d saniyedir aktif.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Pawn Etkinliklerini Yakalama

`Plugin_Public` makrosu, Pawn geri çağrılarını C++ kodunuzda almak için birincil köprüdür.

#### Sözdizimi ve Bildirim

- `Plugin_Public(PublicAdı, Tip1 Param1, Tip2 Param2, ...)`
- Bildirdiğiniz C++ fonksiyonunun adı, Pawn geri çağrısının **aynısı olmalıdır** (örneğin: `OnPlayerConnect`).
- C++ parametre türleri (`int`, `float`, `std::string`) SDK tarafından otomatik olarak dönüştürülür.

```cpp
// OnPlayerText(playerid, text[])'i yakalar
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    // ...
}
```

#### Otomatik Parametre Marshalling

SDK, AMX'in `cell stack`'ini okuma ve belirtilen C++ türlerine dönüştürme işlemini otomatik olarak halleder:
- `int`: Doğrudan `cell`'den dönüştürülür.
- `float`: `amx::AMX_CTOF` kullanılarak `cell`'den dönüştürülür.
- `std::string`: SDK, AMX'deki dizenin adresini okur, C++'da bir `std::string` ayırır ve içeriği kopyalar.

#### Akış Kontrolü: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

`Plugin_Public` fonksiyonunuzun döndürdüğü değer çok önemlidir ve geri çağrı yürütme akışını belirler:
- `return PLUGIN_PUBLIC_CONTINUE;` (`1` değeri): Geri çağrı yürütmesinin **devam etmesi gerektiğini** belirtir. Bu geri çağrıyı yakalayan başka eklentiler varsa, onlar çağrılacaktır. Ardından, Pawn scriptindeki orijinal `public` çağrılacaktır.
- `return PLUGIN_PUBLIC_STOP;` (`0` değeri): Geri çağrı yürütmesinin **durdurulması gerektiğini** belirtir. Başka hiçbir eklenti veya Pawn scriptindeki orijinal `public` bu olay için çağrılmayacaktır. Bu, SA-MP'nin varsayılan davranışını "geçersiz kılan" veya "engelleyen" bir sistem uygulamak için idealdir.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Oyuncuyu dondurur
        Pawn_Native(SendClientMessage, playerid, -1, Pawn_Format("Oyuncu %d donduruldu.", playerid));

        return PLUGIN_PUBLIC_STOP; // Komutun diğer scriptler tarafından işlenmesini engeller.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Diğer komutların işlenmesine izin verir.
}
```

### 3.3. `Plugin_Native`: C++'da Yerel Fonksiyonlar Oluşturma

`Plugin_Native`, Pawn'ın işlevselliğini yüksek performanslı C++ koduyla genişletmenize olanak tanır.

#### Sözdizimi ve Sabit İmza

- `Plugin_Native(YerelFonksiyonAdı, AMX* amx, cell* params)`
- C++ fonksiyonu tam olarak bu imzaya sahip olmalıdır: `cell NativeFunctionName(AMX* amx, cell* params)`.
- `NativeFunctionName`, Pawn scriptlerinin kullanacağı addır.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Uygulama ...
    return 0;
}
```

#### Yerel Fonksiyonların Otomatik Kaydı

> [!NOTE]
> `amx_Register`'ı manuel olarak çağırmanıza **gerek yoktur**. SDK, tüm `Plugin_Native`'lerinizi ( `SAMP_SDK_WANT_AMX_EVENTS` kullanan herhangi bir `.cpp` dosyasında) algılar ve her yüklü AMX scriptine (`OnAmxLoad`) otomatik olarak kaydeder.

#### Parametre Çıkarma: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Açıklama:** Birden çok parametreyi ardışık olarak çıkarmak için daha basit bir yardımcı.
- **Kullanım:** `Register_Parameters(değişken1, değişken2, ...)`
- **Sınırlamalar:** Giriş parametreleri için. İsteğe bağlı parametreleri veya dizine göre erişimi işlemez.
- **Desteklenen Türler:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // 3 parametreyi çıkarır
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (Tam API: `Get`, `Get_REF`, `Set_REF`)

- **Açıklama:** Bir yerel fonksiyonun parametrelerine erişmek için nesne yönelimli bir arayüz sağlayan bir sarmalayıcı sınıfı. Karmaşık senaryolar için daha güçlü.
- **Oluşturma:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Açıklama:** Yerel fonksiyona geçirilen parametre sayısını döndürür.
- **Kullanım:** İsteğe bağlı parametreleri işlemek için önemlidir.

###### `p.Get<T>(size_t index)`

- **Açıklama:** Belirli bir dizindeki bir giriş parametresini çıkarır ve `T` türüne dönüştürür.
- **Desteklenen Türler:** `int`, `float`, `std::string`.

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

- **Açıklama:** Bir **referans** parametresinin (Pawn işaretçisi) değerini alır ve `out_value` içinde saklar.
- **Kullanım:** Pawn'dan referansla geçirilen değerleri okumak için.
- **Dönüş:** AMX adresi geçerliyse `true`, aksi takdirde `false`.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Referans değerlerini alır (Pawn adresleri geçti)
    p.Get_REF(1, health); // Float:health değerini okur
    p.Get_REF(2, money);   // money değerini okur
    
    Samp_SDK::Log("Oyuncu %d, Sağlık: %.1f, Para: %d", playerid, health, money);
    
    // Şimdi, onları değiştirin
    health = 50.0f;
    money += 100;
    
    // Ve onları Pawn belleğine geri yazar
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Açıklama:** Bir referans parametresini okumak için `std::optional<T>` döndürür. C++17 ve üstü için daha güvenlidir.

###### `p.Set_REF<T>(size_t index, T value)`

- **Açıklama:** Bir `T` değerini bir Pawn **referans** parametresine (Pawn'ın geçirdiği adres) yazar.
- **Kullanım:** Referansla geçirilen değerleri değiştirmek için, böylece Pawn değişikliği görür.
- **Dönüş:** Yazma başarılı olursa `true`, aksi takdirde `false`.

#### Değerlerin Döndürülmesi

- `Plugin_Native` fonksiyonunuz bir `cell` döndürmelidir.
- Bir `int` veya `bool` döndürmek için, `cell`'e bir cast kullanın.
- Bir `float` döndürmek için `amx::AMX_FTOC(benim_float)` kullanın.

```cpp
// Bir bool döndürür
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    int playerid = p.Get<int>(0);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Bir float döndürür
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // 100.0f döndürür
}
```

### 3.4. `Pawn_*` Makroları: C++'dan Pawn Fonksiyonlarını Çağırma

Bu makrolar `Plugin_Public` ve `Plugin_Native`'in tersidir: C++ kodunuzun Pawn fonksiyonlarını çağırmasına izin verirler.

#### `Pawn_Native(YerelFonksiyonAdı, ...)`

- **Amaç:** C++'dan SA-MP (veya diğer eklentilerin) yerel fonksiyonlarını çağırmak için önerilen yol.
- **Mekanizma:** Yerel fonksiyonun işaretçisini SDK'nın dahili önbelleğinde (`Amx_Register_Detour` tarafından doldurulur) arar. Bulunursa, yerel fonksiyonu bir `Amx_Sandbox` (sahte ve izole edilmiş bir AMX örneği) ortamında yürütür.
- **Performans:** En verimli olanıdır, çünkü pahalı `public` aramalarını önler ve doğrudan yerel fonksiyon işaretçisiyle etkileşime girer.

#### `Pawn_Public(GenelFonksiyonAdı, ...)`

- **Amaç:** Bir Pawn scriptindeki belirli bir public fonksiyonu çağırır.
- **Mekanizma:** `Amx_Manager` tarafından yönetilen `AMX*` örnekleri arasında döngü yapar, `public`'i adına göre arar ve yürütür.
- **Performans:** Arama ve gerçek `amx_Exec` nedeniyle `Pawn_Native`'den daha az verimlidir. Genellikle `public`'ler `native`'lerden daha yavaştır.
- **Kullanım:** Gamemode/Filterscript'lerinizde yerel fonksiyon olmayan özel olayları çağırmak için idealdir.

#### `Pawn(FonksiyonAdı, ...)`

- **Amaç:** Fonksiyonun yerel mi yoksa public mi olduğunu tahmin etmeye çalışan bir kolaylık makrosu.
- **Mekanizma:** Önce `Pawn_Native` olarak çağırmayı dener. Başarısız olursa (yerel fonksiyon bulunamazsa), `Pawn_Public` olarak çağırmayı dener.
- **Performans:** Fonksiyon yerel ise, iki kez arama denemesi nedeniyle `Pawn_Native`'den biraz daha yavaş olabilir. `public`'ler için performans, `Pawn_Public` ile aynıdır.
- **Kullanım:** Fonksiyonların yerel mi yoksa public mi olduğundan emin olmadığınızda veya birini denememek ve sonra diğerini denemek için tekrarlayan koddan kaçınmak için.

#### Sözdizimi ve Kurallar

- **Fonksiyon Adı:** Pawn fonksiyonunun adını **doğrudan, tırnaksız** kullanın. SDK bunu dahili olarak dizeye dönüştürecektir.
- **Parametreler:** C++ parametrelerini doğrudan geçirin.

```cpp
// Doğru:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Yanlış (ancak hash nedeniyle teknik olarak çalışır, kaçının):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Giriş Parametrelerinin Marshalling'i

SDK, C++ türlerinizi AMX'in `cell` formatına dönüştürür ve gerektiğinde belleği yönetir:
-   `int`, `bool`, `long`, `enum` -> `cell`
-   `float`, `double` -> `cell` (`amx::AMX_FTOC` kullanarak)
-   `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (AMX'de bellek ayırır, dizeyi kopyalar ve `amx_addr` adresini geçirir)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Çıkış Parametrelerinin Marshalling'i (Referanslar: `int&`, `float&`, `std::string&`)

Bu, kolaylık ve güvenlik için önemli bir özelliktir. İşaretçi (referans) bekleyen Pawn fonksiyonları için, SDK tüm bellek ayırma/serbest bırakma ve veri kopyalama sürecini otomatikleştirir.

- **Nasıl kullanılır:** Değişkeninizi referansla (`&`) geçirmeniz yeterlidir.
- **Mekanizma:** SDK, AMX yığınında bellek ayırır, AMX adresini Pawn fonksiyonuna geçirir, Pawn fonksiyonunun bu adresi doldurmasını bekler, değeri geri okur ve AMX belleğini serbest bırakır. Hepsi şeffaf bir şekilde.
- **`std::string&` ile:** SDK, dize için AMX'de standart bir tampon (256 hücre) ayırır.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Konum %s (ID:%d): Pos(%.2f, %.2f, %.2f) İç Mekan:%d Dünya:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### `Callback_Result` Nesnesi: Tam Analiz

Tüm `Pawn_*` çağrıları bir `Callback_Result` nesnesi döndürür. Bu nesne, Pawn çağrısının sonucu için güvenli bir sarmalayıcıdır.

- `Callback_Result() noexcept`: Varsayılan yapılandırıcı, başarısızlığı (`success_ = false`) belirtir.
- `Callback_Result(bool success, cell value) noexcept`: Değerle birlikte başarı veya başarısızlık için yapılandırıcı.
- `explicit operator bool() const`: Çağrının başarılı olup olmadığını kontrol etmek için `if (result)` kullanılmasına izin verir.
- `operator cell() const`: Değeri almak için sonucu `cell`'e dönüştürmeye izin verir.
- `float As_Float() const`: Sonucu `float` olarak almak için kolaylık.
- `cell Value() const`: Ham `cell` değerini döndürür.
- `bool Success() const`: Pawn çağrısı başarılı olursa `true` döndürür.
- `int Get_Amx_Error() const`: Çağrı başarısız olursa AMX hata kodunu döndürür (başarılı için 0).

```cpp
// Örnek: Bir oyuncunun canını almak.
// GetPlayerHealth(playerid, &Float:health) yerel fonksiyonu bir playerid ve can için bir referans bekler.
int playerid = 0; // Oyuncu ID'si örneği
float player_health = 0.0f;

// GetPlayerHealth'i çağırıyoruz, playerid ve player_health'i referansla geçiriyoruz.
// SDK, 'health' çıkış parametresinin marshalling'ini halledecektir.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Çağrının başarılı olup olmadığını kontrol eder (operator bool)
    // result.As_Float() veya result (operator cell) tarafından döndürülen değer
    // *yerel fonksiyonun* dönüş değeri olacaktır, çıkış parametresi değil.
    // Can değeri, çıkış parametresinin marshalling'i nedeniyle zaten 'player_health' içinde güncellenmiştir.
    Samp_SDK::Log("Oyuncu %d'nin canı %.1f.", playerid, player_health);
} else {
    // Çağrı başarısız oldu, belki oyuncu yok veya yerel fonksiyon bulunamadı.
    Samp_SDK::Log("Oyuncu %d'nin canını alırken hata oluştu. AMX kodu: %d", playerid, result.Get_Amx_Error());
}

// Bir değer döndüren ve çıkış parametreleri kullanan yerel fonksiyonlar için (daha az yaygın, ancak mümkün),
// her ikisini de kullanırsınız:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param zaten güncellendi
// }
```

#### **3.5. `Plugin_Module`: Dinamik Modül Yönetimi**

`Plugin_Module` makrosu, eklentinizin diğer eklentiler için bir "yükleyici" olarak çalışmasını sağlar ve modüler, genişletilebilir bir mimari oluşturur. Bu şekilde yüklenen bir modül, ana eklenti tarafından yönetilen kendi olay yaşam döngüsüne sahip birinci sınıf bir eklenti olarak kabul edilir.

#### Söz Dizimi ve Amaç

- `Plugin_Module(const char* nome_do_arquivo_base, const char* diretorio_do_modulo, const char* mensagem_sucesso_opcional)`
- `nome_do_arquivo_base`: Modül dosyasının temel adı, **uzantı olmadan** (örneğin, `my_module.dll` veya `my_module.so` için `"my_module"` kullanın). SDK, uygun `.dll` veya `.so` uzantısını otomatik olarak ekler.
- `diretorio_do_modulo`: Modül dosyasının bulunduğu dizinin yolu (örneğin, `"plugins/my_custom_modules"`). **Burada dosya adını dahil etmeyin.** SDK, tam yolu birleştirir (`diretorio_do_modulo/nome_do_arquivo_base.ext`).
- `mensagem_sucesso_opcional`: Modül başarıyla yüklendiğinde sunucu konsoluna kaydedilecek isteğe bağlı bir mesaj.

```cpp
// main.cpp, OnLoad() içinde

// Sunucunun 'modules/custom/' klasöründe bulunan
// 'core_logic.dll' (veya 'core_logic.so') modülünü yükler.
if (!Plugin_Module("core_logic", "modules/custom", "Çekirdek Mantık Modülü başarıyla yüklendi!"))
    return (Samp_SDK::Log("KRİTİK HATA: 'core_logic' modülü yüklenemedi!"), false);

// Sunucunun doğrudan 'plugins/' klasöründe bulunan
// 'admin_system.dll' (veya 'admin_system.so') modülünü yükler.
if (!Plugin_Module("admin_system", "plugins", "Yönetim Modülü etkinleştirildi."))
    Samp_SDK::Log("UYARI: Yönetim Modülü yüklenemedi.");
```

#### Modülün Yaşam Döngüsü

Bir modül, normal bir eklenti gibi `Load`, `Unload` ve `Supports` işlevlerini dışa aktarmalıdır. SDK, modülün yaşam döngüsünü şu şekilde yönetir:

- **Yükleme:** `Plugin_Module` çağrıldığında, SDK:
   1. Dosyanın tam yolunu oluşturur (örneğin, `modules/custom/core_logic.dll`).
   2. İkili dosyayı yüklemek için `Dynamic_Library` (`LoadLibrary`/`dlopen`) kullanır.
   3. **Modülün TÜM yaşam döngüsü işlevlerine işaretçileri alır:**
      - **Zorunlu:** `Load`, `Unload`, `Supports`. Bunlardan biri eksikse, modül yüklemesi başarısız olur.
      - **İsteğe bağlı:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Modülün `Load` işlevini çağırır ve ana eklentiden `ppData` parametresini geçirir.
   5. Eğer `Load` `true` döndürürse, modül yüklü modüllerin dahili listesine eklenir.

- **Olay Yönlendirme:** Ana eklenti, yüklü tüm modüllere olayları **otomatik olarak yönlendirir**.
 > [!IMPORTANT]
 > Olayların doğru bir şekilde yönlendirilmesi için, **ana eklentinin** (`Plugin_Module` çağıran) bu olayları alacak şekilde yapılandırılmış olması gerekir.
 > - `AmxLoad` ve `AmxUnload` modüllerde çalışması için, ana eklenti `SAMP_SDK_WANT_AMX_EVENTS` makrosunu tanımlamalıdır.
 > - `ProcessTick` modüllerde çalışması için, ana eklenti `SAMP_SDK_WANT_PROCESS_TICK` makrosunu tanımlamalıdır.

- **Yük Kaldırma:** Ana eklentinin `OnUnload` işlemi sırasında, SDK, `Plugin_Module` aracılığıyla yüklenen tüm modülleri kaldırır. Bu, yükleme sırasının **tersine** yapılır (son yüklenen modül ilk kaldırılır), bu da bağımlılıkları yönetmek ve kaynakların doğru şekilde serbest bırakılmasını sağlamak için kritik öneme sahiptir.

#### Modülerleştirmenin Avantajları

- **Kod Organizasyonu:** Büyük eklentileri, her biri kendi modül dosyasında bulunan daha küçük, yönetilebilir bileşenlere ayırın.
- **Yeniden Kullanılabilirlik:** Farklı eklentiler tarafından kullanılabilen genel modüller (örneğin, bir veritabanı modülü, gelişmiş bir günlük sistemi modülü) oluşturun, böylece kod yeniden kullanımını teşvik edin.
- **Bağımsız Bileşenler:** **Tamamen olay odaklı ve bağımsız** modüller oluşturun. Bir modül, kendi `Plugin_Native`s, `Plugin_Public`s yakalama ve kendi `OnProcessTick` mantığına sahip olabilir, bağımsız bir eklenti gibi çalışır, ancak bir ana eklenti tarafından yüklenir.
- **Dinamik Güncellemeler:** Kontrollü senaryolarda, sistemin bazı bölümlerini güncelleme (bir modülün `.dll` veya `.so` dosyasını değiştirerek) ana eklentiyi veya tüm sunucuyu yeniden derlemeden ve yeniden başlatmadan yapma imkanı sağlar (ancak bu, sıkı bir sürüm ve uyumluluk yönetimi gerektirir).

### 3.6. `Plugin_Call`: Eklentinin Dahili Yerel Fonksiyonlarını Çağırma

Kendi eklentiniz içinde tanımlanmış bir `Plugin_Native`'i çağırmak için `Plugin_Call`'ı kullanın.

#### Sözdizimi ve Performans Avantajları

- `Plugin_Call(YerelFonksiyonAdı, Param1, Param2, ...)`
- **Avantaj:** Yerel fonksiyonu AMX'in yerel fonksiyonlar dizisinde arama yükünü önler. SDK, kendi yerel fonksiyonları için isim hash'lerinden fonksiyon işaretçilerine doğrudan bir harita tutar, bu da onları dahili olarak çağırmanın en hızlı yolunu yapar.
- **Gerektirir:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Seviyeyi kontrol etme mantığı
    return (playerid % 2 == 0) ? 1 : 0; // Örnek: çift ID'ler için çift seviye
}

void CheckAllPlayersLevel() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Kendi yerel fonksiyonunuzu çağırır
                Samp_SDK::Log("Oyuncu %d yüksek seviyede!", i);
        }
    }
}
```

### **3.7. SDK Yardımcı Fonksiyonları**

#### `Samp_SDK::Log(const char* format, ...)`

- **Açıklama:** Sunucu konsoluna ve `server_log.txt` dosyasına mesajlar yazdırır. `logprintf` için güvenli bir sarmalayıcı.
- **Kullanım:** Hata ayıklama, durum mesajları ve hatalar için.
- **Mekanizma:** Dahili olarak SDK, `ppData[PLUGIN_DATA_LOGPRINTF]` aracılığıyla `logprintf` işaretçisini alır. Fonksiyon, dizenin güvenli bir şekilde biçimlendirilmesini halleder.

```cpp
// Eklentinizin herhangi bir yerinde
Samp_SDK::Log("Eklenti %d değeri ve '%s' dizesiyle başlatıldı.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Önerilen)

- **Açıklama:** Bir dizeyi güvenli bir şekilde biçimlendirir (`sprintf` benzeri) ve bir `std::string` döndürür. Bu, eklentiniz içinde kullanılmak üzere dizeleri biçimlendirmenin **önerilen ve en idiyomatik** yoludur.
- **Kullanım:** `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, veya C++ kodunuzda başka herhangi bir dize ihtiyacı için biçimlendirilmiş mesajlar oluşturmak için idealdir.
- **Mekanizma:** Dahili olarak, `Plugin_Format` bir makro olup `Samp_SDK::Format`'ı çağırır. Biçimlendirilmiş dizenin tam boyutunu belirlemek için `vsnprintf` kullanır ve yeterli kapasiteye sahip bir `std::string` ayırarak arabellek taşmalarını önler.

```cpp
int playerid = 0; // ID örneği
int health = 50;
std::string status_message = Plugin_Format("Oyuncu %d, mevcut canınız %d.", playerid, health); // Plugin_Format makrosunu kullanarak
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, status_message);

// Dahili loglar için de kullanılabilir
Samp_SDK::Log(Plugin_Format("DEBUG: ID %d için durum işleniyor", playerid).c_str());
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Uygulama Detayı)

- **Açıklama:** `Samp_SDK` ad alanı içinde bulunan, dizeleri biçimlendirmek için temel uygulama fonksiyonu.
- **Kullanım:** Genellikle kullanıcı tarafından doğrudan çağrılmaz. `Plugin_Format` makrosu, diğer SDK makrolarının (`Plugin_Public`, `Plugin_Native`) adlandırma kuralına uygun olarak bu fonksiyon için bir kolaylık olarak sağlanmıştır. Sadece belirli bir nedenle `Plugin_Format` makrosundan kaçınmak isterseniz doğrudan çağırırsınız.

```cpp
// Samp_SDK::Format'ın nasıl çalıştığına dair örnek, ancak Plugin_Format'ı tercih edin
std::string raw_status = Samp_SDK::Format("Yalnızca dahili kullanım için: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Açıklama:** Bir AMX dize adresini (`cell amx_addr`) bir C++ `std::string`'e dönüştürür.
- **Kullanım:** Esas olarak `Plugin_Native` içinde, `Register_Parameters` veya `Native_Params` tarafından otomatik olarak dönüştürülmeyen dizelere erişmeniz gerektiğinde (örn: Pawn parametresi bir `const` `string` ise ve `Plugin_Native` veya `Plugin_Public` içinde otomatik Marshalling için `std::string` olarak bildirilmemişse).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // AMX'deki dize adresini alır

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("AMX Dizesi: %s", cpp_string.c_str());

    return 1;
}
```

## 4. **SDK'nın Dahili Anatomisi ve Mimarisi**

Bu bölüm, SAMP SDK'nın yüksek seviyeli soyutlamayı sağlamak için temel mekanizmalarını, temel bileşenlerini ve bunların nasıl etkileştiğini ortaya koymaktadır. Bu iç işleyişin derinlemesine anlaşılması, geliştiriciyi SDK kullanımını optimize etme, karmaşık sorunları ayıklama ve hatta işlevselliğini genişletme konusunda güçlendirir.

### 4.1. `core.hpp`: Minimalist Temel

`Samp_SDK::Core`, SA-MP eklenti ortamı tarafından sağlanan düşük seviyeli verilere ilk ve merkezi erişim noktası olarak hizmet veren bir `singleton`'dır. Temel sorumluluğu, temel işlevsellikleri kapsüllemek ve ifşa etmektir.

- **`Samp_SDK::Core::Instance()`**:
   - **Açıklama:** `Core` sınıfının tek global örneğini döndürür. Bu, eklenti verilerine (`ppData`) erişimin tutarlı ve merkezi olmasını sağlamak için bir `singleton` tasarım desenidir.
   - **Mekanizma:** Örnek, eklentinizin `Load()` fonksiyonunda `Core::Instance().Load(ppData)` çağrıldığında bir kez başlatılır.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Açıklama:** AMX API fonksiyon işaretçilerine güvenli ve indeksli erişim sağlar. `pAMXFunctions` dizisi (`ppData[PLUGIN_DATA_AMX_EXPORTS]` aracılığıyla alınır) `amx_Exec`, `amx_Register` gibi kritik fonksiyonların adreslerini içerir.
   - **Etki:** `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)` yerine, SDK, `amx::` ad alanında type-safe sarmalayıcılar (örn: `amx::Exec(...)`) sunarak kodu daha okunabilir ve cast hatalarına daha az yatkın hale getirir.
   - **Dahili Örnek (`amx_api.hpp`):**
      ```cpp
      // amx_api.hpp'den basitleştirilmiş kesit
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
   - **Açıklama:** SA-MP'nin `logprintf` fonksiyonuna bir işaretçi, sunucu konsoluna ve `server_log.txt`'ye mesaj yazdırmak için standart arayüzdür.
   - **Mekanizma:** `Samp_SDK::Log`, bu işaretçiyi kullanan güvenli bir sarmalayıcıdır ve mesajlarınızın SA-MP ortamında doğru şekilde görüntülenmesini sağlar.

### **4.2. `platform.hpp` ve `version.hpp`: Uyumluluk ve Metadatalar**

Bu başlıklar, SDK'nın taşınabilirliği ve optimizasyonu için temel oluşturur, onu farklı derleme ortamlarına uyarlar ve modern C++'ın belirli özelliklerinden yararlanır.

- **Platform ve Mimari Algılama:**
   - **Mekanizma:** İşletim sistemini tanımlamak için ön işlemci makrolarını (`#if defined(WIN32)`, `#if defined(__linux__)`, vb.) kullanır.
   - **Mimari Doğrulama:** Eklentinin x86 (32-bit) için derlendiğinden emin olmak için `static_assert` veya `#error` içerir, bu SA-MP ve hooking mekanizması ile uyumluluk için kritik bir gereksinimdir.
   - **Sembol Dışa Aktarma Yönetimi:**
      - `SAMP_SDK_EXPORT`: `platform.hpp` içinde tanımlanmış bir makro olup `extern "C"` olarak genişler ve Linux'ta `__attribute__((visibility("default")))` ekler. Windows'ta, sadece `extern "C"`'yi garanti eder çünkü SDK, ana fonksiyonları dışa aktarmak için `pragma comment(linker, "/EXPORT:...")` (MSVC için) veya MinGW standardını kullanır.
      - Bu, eklentinizin yaşam döngüsü fonksiyonlarının (`Supports`, `Load`, `Unload`, vb.) derleme ortamından bağımsız olarak DLL/SO'nuzdan doğru bir şekilde dışa aktarılmasını sağlar, **`.def` dosyalarına veya manuel olarak `__attribute__((visibility("default")))` eklemeye gerek kalmadan** kendi uygulamanıza.
   - **Örnek (`platform.hpp` - ilgili kesit):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // MSVC için, dışa aktarma pragma linker komutları tarafından yönetilir
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // Linux'ta GCC/Clang için görünürlük özniteliğini kullanırız
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... diğer tanımlar ...
      ```
   - **Örnek (`samp_sdk.hpp` - uygulamanın ilgili kesiti):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // Windows'ta (MSVC), fonksiyonları dışa aktarmak için pragma comment kullanırız.
          // Bu, bir .def dosyasına olan ihtiyacı ortadan kaldırır.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... diğer dışa aktarmalar ...
      #endif

      // Dışa aktarılan fonksiyonların uygulanması
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... diğer fonksiyonlar ...
      #endif
      ```

- **Optimizasyon ve Dal Tahmini Makroları:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mekanizma:** `__forceinline` (MSVC) veya `__attribute__((always_inline)) inline` (GCC/Clang). Derleyiciye fonksiyonun gövdesini doğrudan çağrı yerine eklemesini güçlü bir şekilde önerir, bu da gerçek bir fonksiyon çağrısının yükünü ortadan kaldırır.
      - **Kullanım:** SDK içindeki küçük ve performans açısından kritik fonksiyonlara uygulanır.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mekanizma:** `[[likely]]` / `[[unlikely]]` (C++20) veya `__builtin_expect` (GCC/Clang). Derleyiciye bir `if/else` yolunun hangisinin daha olası olduğuna dair ipuçları verir.
      - **Etki:** Derleyicinin dal tahmini (branch prediction) için daha verimli kod üretmesine yardımcı olur, CPU gecikmesini azaltır.
      - **Örnek (`platform.hpp`):**
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

- **Standart C++ Tanımları (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mekanizma:** `__cplusplus` ve `_MSVC_LANG` değerine göre tanımlanmış makrolar.
   - **Kullanım:** SDK'nın, daha eski standartlarla uyumluluğu korurken, mevcut olduğunda daha yeni C++ işlevselliklerini (C++17'den `std::apply` ve `if constexpr` veya C++17'den `std::is_same_v` gibi) kullanmasına olanak tanır.
   - **Örnek (`version.hpp` - `if constexpr` kullanımı):**
      ```cpp
      // public_dispatcher.hpp'den basitleştirilmiş kesit
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

### 4.3. `function_hook.hpp`: x86 Yakalama Motoru

Bu başlık, SDK'nın çalışması için temel olan fonksiyonları yakalamak (hooking) için düşük seviyeli mekanizmayı tanımlar. Kesinlikle x86 (32-bit) mimarisine bağlıdır.

- **`X86_Detour`**:
   - **Açıklama:** Bellekteki bir fonksiyonun başlangıcını bir atlama fonksiyonuna atlama talimatıyla üzerine yazma mantığını kapsülleyen bir sınıf.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mekanizma:** x86'da, göreceli atlama (`JMP`) talimatı genellikle 5 bayttır: `0xE9` (JMP near, relative için opcode) ve ardından sonraki talimata göre hedef adresin ofsetini temsil eden 4 bayt.
      - **Talimat örneği:** `E9 XX XX XX XX` (burada `XX` ofset baytlarıdır).
   - **`Apply(void* target, void* detour)`**:
      - **Eylem:** Hook'u kurar. Önce `target` fonksiyonunun orijinal `JUMP_INSTRUCTION_SIZE` baytını (`original_bytes_`) depolar. Ardından, `detour`'un `target`'a göre göreceli adresini hesaplar ve `target`'ın başlangıcını `JMP` talimatıyla üzerine yazar.
      - **Göreceli adres hesaplama örneği:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Sapma adresi - (Hedef adresi + JMP talimatının boyutu)
         ```
   - **`Revert()`**:
      - **Eylem:** `target` fonksiyonundaki `original_bytes_`'i geri yükleyerek hook'u kaldırır.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mekanizma:** Windows'ta `VirtualProtect`; Linux'ta `mprotect` kullanır. Bu sistem çağrıları, fonksiyonun bulunduğu bellek sayfasının izinlerini `EXECUTE_READWRITE` (Windows) veya `PROT_WRITE | PROT_EXEC` (Linux) olarak değiştirir, bu da kodun çalışma zamanında değiştirilmesine izin verir.
      - **Örnek (`Unprotect_Memory`):**
         ```cpp
         // function_hook.hpp'den basitleştirilmiş kesit
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
   - **Açıklama:** `X86_Detour` için bir C++ `type-safe` sarmalayıcı, fonksiyon işaretçisi türlerinin doğru olmasını sağlar.
   - `Install(void* target, void* detour)`: `X86_Detour::Apply` çağrısını kapsüller.
   - `Uninstall()`: `X86_Detour::Revert` çağrısını kapsüller.
   - **`Call_Original(Args... args)`**:
      - **Güvenlik Mekanizması (Özyineleme Koruması):** Bu fonksiyon, sapmanın orijinal fonksiyonu çağırması gerektiğinde sonsuz döngüleri önlemek için kritiktir. **Geçici olarak hook'u kaldırır (`detour_.Revert()`)**, orijinal fonksiyonu çağırır (`Get_Original()(args...)`) ve ardından **hook'u yeniden kurar (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: Sapmanın en üst düzey orijinal çağrısı tamamlandığında hook'un yalnızca yeniden kurulmasını sağlayan bir sayaç, orijinal fonksiyonun güvenli özyinelemeli çağrılarına izin verir (örneğin, orijinal fonksiyon özyinelemeliyse). `thread_local`, `recursion_guard`'ın her iş parçacığı için izole edilmesini garanti eder, çok iş parçacıklı ortamlarda önemlidir.
      - **Örnek (`Call_Original` ile Scope_Guard):**
         ```cpp
         // function_hook.hpp'den basitleştirilmiş kesit
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

### 4.4. `interceptor_manager.hpp`: AMX Hook Kontrolcüsü

Bu `singleton`, SDK'nın SA-MP'nin AMX sanal makinesiyle etkileşiminin merkezidir. Sunucu tarafından dışa aktarılan AMX API fonksiyonlarına `function_hook.hpp` tarafından sağlanan hook'ların kurulumunu koordine ederek yürütme akışını SDK mantığına yönlendirir.

- **`Activate()` / `Deactivate()`**:
   - **Açıklama:** Gerekli tüm hook'ları kurmak ve kaldırmak için genel yöntemler. Eklentinizin `OnLoad()` ve `OnUnload()` fonksiyonlarında çağrılırlar.
   - **Mekanizma:** `Core::Instance().Get_AMX_Export(...)` kullanarak AMX fonksiyonlarının ( `amx_Register`, `amx_Exec` vb.) işaretçilerini alır ve sapmaları kurar.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Hook'lanmış Fonksiyon:** `amx_Register`
   - **Amaç:** *Tüm* yerel fonksiyonların (SA-MP, diğer eklentiler veya gamemode tarafından) kaydını yakalar.
   - **Eylem:** `Interceptor_Manager::Instance().Cache_Natives()`'i çağırarak yerel fonksiyonların işaretçilerini ve adlarını dahili bir önbellekte saklar.
   - **Etki:** Bu önbellek, `Pawn_Native` performansı için temeldir, pahalı bir AMX araması yerine yerel fonksiyon işaretçisinin son derece hızlı bir şekilde aranmasına izin verir.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Hook'lanmış Fonksiyon:** `amx_Exec`
   - **Amaç:** **Bu en kritik hook'tur.** Pawn `public`'lerinin çağrılması dahil olmak üzere AMX'deki *herhangi bir* kod yürütmesini yakalar.
   - **`Plugin_Public` Yakalama Mekanizması:**
      1. Bir `public` (veya `AMX_EXEC_MAIN`) için `amx_Exec` çağrıldığında, `Amx_Exec_Detour` yürütülür.
      2. `public`'in adını alır (`Get_Public_Name_By_Index` veya `tl_public_name` kullanarak).
      3. Bu ad için kayıtlı C++ işleyicileri olup olmadığını kontrol etmek için `Public_Dispatcher::Instance().Dispatch()`'i sorgular.
      4. İşleyiciler varsa, onları yürütür. `Public_Dispatcher`, AMX parametrelerinin C++ türlerine `marshalling`'ini halleder.
      5. `Public_Dispatcher`'ın dönüş değerine (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`) bağlı olarak, orijinal `amx_Exec`'i çağırıp çağırmayacağına (`Get_Amx_Exec_Hook().Call_Original(...)`) veya Pawn `public` yürütmesini sonlandırıp sonlandırmayacağına karar verir.
      6. **Yığın Yönetimi:** Pawn `public` yürütmesi durdurulursa (`PLUGIN_PUBLIC_STOP`), `Amx_Exec_Detour`, AMX yığınını düzeltir (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) tutarsızlıkları önlemek için.
   - **Örnek (`Amx_Exec_Detour`):**
      ```cpp
      // interceptor_manager.hpp'den basitleştirilmiş kesit
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          // ... public adını belirleme mantığı ...
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
   - **Hook'lanmış Fonksiyon:** `amx_FindPublic`
   - **Amaç:** `public`'lerin adına göre aranmasını yakalar.
   - **"Hayalet Publics" Mekanizması:** Orijinal `amx_FindPublic`, Pawn'da bir `public` bulamazsa, ancak `Public_Dispatcher` bu ad için kayıtlı bir C++ işleyicisine sahipse, bu hook `AMX_ERR_NONE` ve özel bir `index` (`PLUGIN_EXEC_GHOST_PUBLIC`) döndürür. Bu, SA-MP API'sinin `public`'in var olduğunu "düşünmesini" sağlar ve sonraki `amx_Exec` çağrısının (bu özel indeks için) `Amx_Exec_Detour` tarafından yakalanmasına izin verir, bu da daha sonra C++ işleyicisine yönlendirir.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Bir "hayalet public" algılandığında `public`'in adını `Amx_Exec_Detour`'a geçirmek için kullanılır, çünkü `amx_Exec` sadece indeksi alır, adı değil.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Hook'lanmış Fonksiyonlar:** `amx_Init` / `amx_Cleanup`
   - **Amaç:** Etkin `AMX*` örneklerinin listesini yönetmek.
   - **Eylem:** `Amx_Init_Detour`, `Amx_Manager::Instance().Add_Amx()`'i çağırır ve `Amx_Cleanup_Detour`, `Amx_Manager::Instance().Remove_Amx()`'i çağırır.

### 4.5. `amx_manager.hpp`: `AMX*` Örneklerini Yönetme

Bu `singleton`, sunucuda şu anda yüklü olan tüm AMX sanal makinelerinin dinamik bir kaydını tutar. "Tüm scriptlerle" etkileşime girmesi veya belirli bir scripti bulması gereken fonksiyonlar için önemlidir.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Açıklama:** Başlatılan tüm `AMX*` örneklerinin (gamemode ve filterscriptler) bir listesi.
   - **Yönetim:** `Amx_Init_Detour` hook'ları tarafından doldurulur ve `Amx_Cleanup_Detour` tarafından boşaltılır.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Amaç:** Çok iş parçacıklı ortamlarda (`loaded_amx_`'i eşzamanlı erişime karşı korur (SA-MP çoğunlukla tek iş parçacıklı olsa da, bu iyi bir güvenlik uygulamasıdır). `std::shared_mutex` aynı anda birden fazla okuyucuya, ancak yalnızca bir yazıcıya izin verir.
- **`std::atomic<uint32_t> generation_`**:
   - **Amaç:** Bir AMX her eklendiğinde veya kaldırıldığında artan bir sayaç.
   - **Kullanım:** `callbacks.hpp` içindeki `Caller_Cache` tarafından, AMX listesinin ne zaman değiştiğini algılamak, `public` arama önbelleklerini geçersiz kılmak ve `Pawn_Public` çağrılarının her zaman güncel bilgilerle çalışmasını sağlamak için kullanılır. Bu, değişmeyen bir durumda tekrar eden aramaları önleyerek performansı optimize eder.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Açıklama:** Belirtilen addaki `public`'i bulmak için `loaded_amx_` içinde (genellikle gamemode veya en alakalı filterscript'i önce yerleştiren en yeniye en eskiye doğru) döngü yapar.
   - **Mekanizma:** Her `AMX*` örneği için `amx::Find_Public` kullanır.
   - **Etki:** `Pawn_Public` için temeldir.

### 4.6. `public_dispatcher.hpp`: `Plugin_Public` Geri Çağrı Yönlendiricisi

Bu `singleton`, Pawn `public`'lerinin adlarını kendi C++ `Plugin_Public` fonksiyonlarınızla eşleştiren bileşendir.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Anahtar:** `public`'in adının FNV1a hash'i (örn: `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Değer:** Her `std::function`'ın o `public` için kayıtlı bir C++ işleyicisi olduğu `std::function<cell(AMX*)>`'lerin bir `std::vector`'u.
   - **Mekanizma:** `std::vector`, aynı geri çağrı için birden çok `Plugin_Public`'in kaydedilmesine izin verir (örn: birden çok eklentinin `OnPlayerCommandText`'i yakalamak istemesi). İşleyiciler, kayıt sırasının tersine yürütülür.
- **`Public_Registrar`**:
   - **Mekanizma:** Bu, `PLUGIN_PUBLIC_REGISTRATION` makrosunun statik global bir örneğini oluşturan bir şablon sınıfıdır. Statik yapıcısında (`static bool registered = [...]`), `Plugin_Public` işleyicinizi `Public_Dispatcher`'a kaydeder. Bu, bir "derleme/başlangıç zamanı statik kaydı" desenidir.
   - **Örnek (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Registrar<decltype(&name), &name, hash_##name> registrar_##name;
      ```

- **`Public_Traits` ve `Wrapper()`**:
   - **Mekanizma:** `Public_Traits`, metaprogramlama kullanarak `static cell Wrapper(AMX* amx)` fonksiyonunu üreten bir trait şablonudur.
   - **Amaç:** Bu `Wrapper`, `Public_Dispatcher`'ın gerçekten depoladığı ve çağırdığı `Amx_Handler_Func`'dır. Sorumluluğu şunlardır:
      1. AMX yığınından parametreleri çıkarmak için `Public_Param_Reader::Get_Public_Params(amx, args...)`'ı çağırmak.
      2. Parametreleri zaten doğru C++ türlerine dönüştürülmüş olarak gerçek C++ `Plugin_Public` fonksiyonunuzu (`func_ptr`) çağırmak.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Açıklama:** AMX yığınındaki değerleri okuyan ve `Plugin_Public` bildiriminde belirtilen C++ türlerine dönüştüren bir dizi özyinelemeli şablon fonksiyonu.
   - **Mekanizma:** Yığındaki `cell`'lere erişmek için `Get_Stack_Cell()` kullanır. Doğru dönüşümü uygulamak için `if constexpr` (C++17+) veya `std::is_same<T>::value` (C++14) kullanır (float için `amx::AMX_CTOF`, string için `Samp_SDK::Get_String`, int için doğrudan cast).

### 4.7. `native.hpp`: Eklenti Yerel Fonksiyonlarını Yönetme ve Çağırma

Bu başlık, eklentinizin Pawn'a açtığı C++ yerel fonksiyonlarının oluşturulmasına ve yönetilmesine adanmıştır.

- **`Native_List_Holder`**:
   - **Açıklama:** Eklentinizde bildirilen tüm `Plugin_Native`'leri ( `SAMP_SDK_WANT_AMX_EVENTS` kullanan tüm `.cpp` dosyalarından) depolayan global bir `singleton`.
   - **`std::vector<Native> natives_`**: `Native` nesnelerini (yerel fonksiyon adını ve C++ fonksiyon işaretçisini `Native_Handler` depolayan) içerir.
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Dahili `Plugin_Native` aramaları için hash ile optimize edilmiş bir harita (`Plugin_Call` tarafından kullanılır).
- **`Native_Registrar`**:
   - **Mekanizma:** `Public_Registrar` gibi, bu da `Plugin_Native` makrosunun statik global bir örneğini oluşturan bir şablon sınıfıdır. Yapıcısında, yerel fonksiyonu `Native_List_Holder`'a ekler.
   - **Etki:** `Plugin_Native`'leri manuel kaydetme endişesi duymadan birden çok `.cpp` dosyasında bildirmenize olanak tanır. Hepsi otomatik olarak toplanacaktır.
- **`Native_Registry`**:
   - **Açıklama:** `OnAmxLoad`'da, `Native_List_Holder`'dan `Native`'lerin tam listesini alan ve bunları bir `AMX_NATIVE_INFO` dizisi olarak biçimlendiren yardımcı bir sınıf.
   - **Mekanizma:** Yeni yüklenen AMX örneğine tüm yerel fonksiyonlarınızı kaydetmek için `amx::Register(amx, amx_natives_info_.data(), -1)`'i çağırır.
- **`Plugin_Call_Impl(...)`**:
   - **Açıklama:** `Plugin_Call` makrosunun temel uygulaması.
   - **Mekanizma:** C++ fonksiyon işaretçisini doğrudan almak için `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` kullanır.
   - **Ortam:** Tıpkı `Pawn_Native`'in çalıştığı gibi, geçici yığını ve yığını yönetmek için bir `Amx_Sandbox` (izole edilmiş) ortamında yerel fonksiyonu yürütür.

### 4.8. `callbacks.hpp` & `amx_memory.hpp`: C++ -> Pawn Çağrıları ve RAII

Bu başlıklar, C++'dan Pawn fonksiyonlarını çağırmak (`Pawn_*` makroları) ve bellek güvenliğini sağlamak için omurgayı oluşturur.

- **`Amx_Sandbox`**:
   - **Açıklama:** `Pawn_Native` ve `Plugin_Call` çağrıları için minimal ve izole edilmiş bir `AMX` ortamını simüle eden `thread_local` bir yapı.
   - **Mekanizma:** Kendi `AMX` yapısı, `AMX_HEADER` ve bir `std::vector<unsigned char> heap`'e sahiptir ve bir scriptin belleğini simüle eder. Bu, gerçek çalışan Pawn scriptlerinin durumunu etkilemeden `amx::Push`, `amx::Allot` vb. çağrılmasına izin verir.
   - **`thread_local`:** SDK'nın çok iş parçacıklı bir bağlamda (örn: Pawn dışı işlemler için gelecekteki bir iş parçacığı havuzu) kullanılması durumunda her iş parçacığının kendi `Amx_Sandbox`'ına sahip olmasını sağlayarak yarış koşullarını önler.
   - **Örnek (`Amx_Sandbox`):**
      ```cpp
      // callbacks.hpp'den basitleştirilmiş kesit
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Yığın/heap için simüle edilmiş bellek

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // AMX ve başlığı başlatır
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
   - **Açıklama:** Her C++ parametresinin AMX tarafından beklenen `cell` formatına ve çıkış parametreleri için tersine `marshalling`'ini yöneten bir dizi aşırı yüklenmiş şablon fonksiyonu.
   - **Giriş İşleme:**
       - `int`, `float`, `bool` için: Doğrudan `cell`'e dönüştürür.
       - `const char*`, `std::string` için: `Amx_Sandbox` (veya `Pawn_Public` için gerçek AMX) yığınında bellek ayırır, dizeyi kopyalar ve AMX adresini yığına iter.
   - **Çıkış İşleme (`is_output_arg`):**
       - **Mekanizma:** Bir argüman const olmayan bir lvalue referansı olduğunda (`is_output_arg` trait'i tarafından algılanır), `Parameter_Processor` değeri itmez, bunun yerine yığında geçici olarak ayrılmış bir `cell` için bir *AMX adresi* iter.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Pawn yerel fonksiyon çağrısından sonra, bir lambda listesi (`post_call_updaters`) yürütülür. Her lambda, AMX'de ayrılan `cell`'in nihai değerini okumaktan ve bunu orijinal C++ değişkenine atamaktan sorumludur (örn: `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mekanizma:** Bir C++ parametre türünün değiştirilebilir bir referans olup olmadığını (örn: `int&`, `float&`, `std::string&`) derleme zamanında değerlendiren bir `std::integral_constant` (tür trait'i). Bu, `Parameter_Processor`'ın giriş parametrelerini çıkış parametrelerinden ayırt etmesini sağlar.
   - **Örnek (`is_output_arg`):**
      ```cpp
      // callbacks.hpp'den basitleştirilmiş kesit
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Açıklama:** AMX'deki bellek ayırma ve serbest bırakmayı kapsülleyen bir RAII (`Resource Acquisition Is Initialization`) sınıfı.
   - **Mekanizma:** Yapıcıda, bir `amx_addr` ve bir `phys_addr` almak için `amx::Allot`'u çağırır. Yıkıcıda, bu belleği serbest bırakmak için `amx::Release`'i çağırır.
   - **Etki:** **AMX yığınında bellek sızıntılarını önlemek için kritiktir.** Dizeler veya çıkış parametreleri için kullanılan geçici belleğin, istisnalar veya erken dönüşler olsa bile her zaman serbest bırakılmasını sağlar.

### 4.9. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: Soyutlanmış AMX Erişimi

Bu başlıklar, Pawn ile etkileşim kurmak için temel tanımları ve yüksek seviyeli araçları sağlar.

- **`amx_defs.h`**:
   - **İçerik:** Ham AMX yapılarının (`AMX`, `AMX_HEADER`), türlerinin (`cell`, `ucell`) ve hata enum'larının (`AmxError`) tanımlarını içerir. Ayrıca `AMX_NATIVE` ve `AMX_CALLBACK`'ı tanımlar.
   - **`SAMP_SDK_PACKED`**: Birlikte çalışabilirlik için temel olan AMX yapılarının doğru bellek düzenine sahip olmasını sağlamak için paketleme özniteliklerini (`#pragma pack(push, 1)` / `__attribute__((packed))`) kullanır.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Açıklama:** Sunucu tarafından dışa aktarılan AMX API fonksiyonlarını çağırmak için ana şablon fonksiyonu.
   - **Mekanizma:** `Core::Instance().Get_AMX_Export(Index)` aracılığıyla fonksiyon işaretçisini alır ve çağırır. Fonksiyon işaretçisi mevcut değilse hata işlemeyi merkezileştirir.
   - **Etki:** Düşük seviyeli çağrıları (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) idiyomatik ve type-safe C++ çağrılarına (`amx::Exec`) dönüştürür.
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Açıklama:** Belleğin bitwise yeniden yorumlanmasını gerçekleştirerek `cell` değerlerini `float`'a ve tersine dönüştürmek için temel fonksiyonlar.
   - **`static_assert`:** Derleme zamanında `sizeof(cell) == sizeof(float)` olmasını sağlamak için `static_assert` içerir, farklı tür boyutlarına sahip platformlarda hataları önler.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Açıklama:** Bir AMX dize adresini `std::string`'e dönüştürmek için yardımcı.
   - **Mekanizma:** Önce `amx::Get_Addr` kullanarak AMX'deki dizenin fiziksel adresini (`cell* phys_addr`) alır. Ardından, uzunluğu belirlemek için `amx::STR_Len`'i ve baytları bir `std::string`'e kopyalamak için `amx::Get_String`'i kullanır.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Açıklama:** SDK için temel dize biçimlendirme (`printf`-benzeri) fonksiyonu.
   - **Mekanizma:** `vsnprintf`'i iki geçişte kullanır: önce dizenin gerekli boyutunu belirlemek için, sonra dizeyi dinamik olarak ayrılmış `std::string`'e biçimlendirmek için. Bu, arabellek taşmalarını önler.

## 5. Derleme ve Dağıtım

### Mimari ve Platform Gereksinimleri

- Eklentiniz **x86 (32-bit)** mimarisi için derlenmelidir. SDK'nın hooking mekanizması bu mimariye özeldir.
- Desteklenen Platformlar: Windows (.dll) ve Linux (.so).

### Derleme Komut Örnekleri

#### **MSVC (Visual Studio)**

1. Yeni bir "Dynamic-Link Library (DLL)" projesi oluşturun.
2. Proje ayarlarında, "Çözüm Platformu"nu **x86** olarak ayarlayın.
3. C++ Dil Standardının en az C++14 olduğundan emin olun.

#### **GCC / Clang (Linux)**

```bash
# 'main.cpp'den 'my_plugin.so' adlı bir eklenti için
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: 32-bit için derler.
- `-shared`: Paylaşılan bir kütüphane (`.so`) oluşturur.
- `-std=c++17`: C++ standardını C++17 olarak ayarlar (`c++14` veya `c++20` olabilir).
- `-O2`: Optimizasyon seviyesi 2.
- `-fPIC`: Paylaşılan kütüphaneler için gerekli olan konumdan bağımsız kod üretir.
- `-Wall -Wextra`: Hataları yakalamaya yardımcı olmak için ek uyarıları etkinleştirir.
- `-Wl,--no-undefined`: Tanımsız semboller varsa kütüphanenin oluşturulmasını engeller.

#### **GCC / Clang (Windows'ta MinGW)**

```bash
# 'main.cpp'den 'my_plugin.dll' adlı bir eklenti için
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Standart C++ kütüphanesini statik olarak bağlar. Eklentinizin kullanıcının sisteminde bulunmayan derleyiciye özel çalışma zamanı DLL'lerine bağımlı olmasını önlemek için önemlidir.
- `-static-libgcc`: GCC kütüphanesini statik olarak bağlar.

### Dağıtım Hususları

- **Dosya Adı:** Eklentiniz `.dll` (Windows) veya `.so` (Linux) uzantısına sahip olmalıdır. Örn: `my_plugin.dll`.
- **Konum:** Derlenen dosyayı SA-MP sunucunuzun `plugins/` klasörüne yerleştirin.
- **server.cfg:** Eklentinizin adını (Windows ise uzantısız) `server.cfg` dosyasındaki `plugins` satırına ekleyin.
   ```
   plugins my_plugin (Linux ise, my_plugin.so)
   ```

## Lisans

Copyright © **SA-MP Programming Community**

Bu yazılım MIT Lisansı ("Lisans") şartları altında lisanslanmıştır; bu yazılımı Lisans şartlarına uygun olarak kullanabilirsiniz. Lisansın bir kopyasını şu adresten edinebilirsiniz: [MIT License](https://opensource.org/licenses/MIT)

### Kullanım Şartları ve Koşulları

#### 1. Verilen İzinler

Bu lisans, bu yazılımın ve ilgili dokümantasyon dosyalarının bir kopyasını edinen herhangi bir kişiye ücretsiz olarak aşağıdaki hakları vermektedir:
* Yazılımın kopyalarını kullanma, kopyalama, değiştirme, birleştirme, yayınlama, dağıtma, alt lisans verme ve/veya satma hakkı
* Yazılımın sağlandığı kişilerin de aynısını yapmasına izin verme hakkı (aşağıdaki koşullara tabi olmak kaydıyla)

#### 2. Zorunlu Koşullar

Yazılımın tüm kopyaları veya önemli parçaları şunları içermelidir:
* Yukarıdaki telif hakkı bildirimi
* Bu izin bildirimi
* Aşağıdaki sorumluluk reddi

#### 3. Telif Hakları

Yazılım ve ilgili tüm dokümantasyon telif hakkı yasaları ile korunmaktadır. **SA-MP Programming Community** yazılımın orijinal telif haklarını elinde tutmaktadır.

#### 4. Garanti Reddi ve Sorumluluk Sınırlaması

YAZILIM "OLDUĞU GİBİ" SAĞLANMAKTADIR, HİÇBİR TÜRDE GARANTİ VERİLMEMEKTEDİR, AÇIK VEYA ZIMNİ, TİCARİ ELVERİŞLİLİK, BELİRLİ BİR AMACA UYGUNLUK VE İHLAL ETMEME GARANTİLERİ DAHİL ANCAK BUNLARLA SINIRLI OLMAMAK ÜZERE.

HİÇBİR KOŞULDA YAZARLAR VEYA TELİF HAKKI SAHİPLERİ HERHANGİ BİR İDDİA, HASAR VEYA DİĞER YÜKÜMLÜLÜKLERDEN SORUMLU TUTULAMAZ, İSTER SÖZLEŞME KAPSAMINDA, HAKSIZ FİİL VEYA BAŞKA BİR ŞEKİLDE OLSUN, YAZILIMDAN VEYA YAZILIMIN KULLANIMINDAN VEYA DİĞER İŞLEMLERDEN KAYNAKLANAN DURUMLAR İÇİN.

---

MIT Lisansı hakkında detaylı bilgi için: https://opensource.org/licenses/MIT