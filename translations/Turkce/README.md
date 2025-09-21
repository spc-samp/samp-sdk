# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14/17/20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**SA-MP eklentileri ve modülleri geliştirmek için modern, yalnızca başlık içeren ve yüksek seviyeli bir C++ SDK'sı.**

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

- [SA-MP SDK](#sa-mp-sdk)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [1. Giriş ve Tasarım Felsefesi](#1-giriş-ve-tasarım-felsefesi)
    - [SA-MP'nin Standart C API'si ile İlgili Sorun](#sa-mpnin-standart-c-apisi-ile-i̇lgili-sorun)
    - [SA-MP SDK Çözümü: Güvenlik ve Performansla Soyutlama](#sa-mp-sdk-çözümü-güvenlik-ve-performansla-soyutlama)
    - [Yalnızca Başlık Modeli: Avantajlar ve Etkileri](#yalnızca-başlık-modeli-avantajlar-ve-etkileri)
  - [2. Kurulum ve Ortam](#2-kurulum-ve-ortam)
    - [Derleme Gereksinimleri](#derleme-gereksinimleri)
    - [Önerilen Dosya Yapısı](#önerilen-dosya-yapısı)
    - [Temel Yapılandırma Makroları](#temel-yapılandırma-makroları)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP Tanımları ve Sabitleri (`samp_defs.hpp`)](#sa-mp-tanımları-ve-sabitleri-samp_defshpp)
  - [3. Kapsamlı API Kullanım Kılavuzu](#3-kapsamlı-api-kullanım-kılavuzu)
    - [3.1. Eklentinin Yaşam Döngüsü](#31-eklentinin-yaşam-döngüsü)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. `Plugin_Public`: Pawn Olaylarını Yakalama](#32-plugin_public-pawn-olaylarını-yakalama)
      - [Sözdizimi ve Bildirim](#sözdizimi-ve-bildirim)
      - [Otomatik Parametre Marshalling'i](#otomatik-parametre-marshallingi)
      - [Akış Kontrolü: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#akış-kontrolü-plugin_public_continue-vs-plugin_public_stop)
      - [Hayalet Callbacks](#hayalet-callbacks)
    - [3.3. `Plugin_Native`: C++'da Yerel Fonksiyonlar Oluşturma](#33-plugin_native-cda-yerel-fonksiyonlar-oluşturma)
      - [Sözdizimi ve Sabit İmza](#sözdizimi-ve-sabit-i̇mza)
      - [Nativelerin Otomatik Kaydı](#nativelerin-otomatik-kaydı)
      - [Parametre Çıkarma: `Register_Parameters` vs. `Native_Params`](#parametre-çıkarma-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Tam API: `Get`, `Get_REF`, `Set_REF`)](#native_params-tam-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Değerlerin Geri Dönüşü](#değerlerin-geri-dönüşü)
    - [3.4. `Plugin_Native_Hook`: Mevcut SA-MP Nativelerini Yakalama](#34-plugin_native_hook-mevcut-sa-mp-nativelerini-yakalama)
      - [Sözdizimi ve Sabit İmza](#sözdizimi-ve-sabit-i̇mza-1)
      - [Hook'un Kaydı ve Aktivasyonu](#hookun-kaydı-ve-aktivasyonu)
      - [Orijinal Native'i Çağırma (Hook Zinciri): `Call_Original_Native`](#orijinal-nativei-çağırma-hook-zinciri-call_original_native)
      - [`Plugin_Native_Hook` için Tam Örnek](#plugin_native_hook-için-tam-örnek)
    - [3.5. `Pawn_*` Makroları: C++'dan Pawn Fonksiyonlarını Çağırma](#35-pawn_-makroları-cdan-pawn-fonksiyonlarını-çağırma)
      - [`Pawn_Native(NativeAdı, ...)`](#pawn_nativenativeadı-)
      - [`Pawn_Public(PublicAdı, ...)`](#pawn_publicpublicadı-)
      - [`Pawn(FonksiyonAdı, ...)`](#pawnfonksiyonadı-)
      - [Sözdizimi ve Kurallar](#sözdizimi-ve-kurallar)
      - [Girdi Parametrelerinin Marshalling'i](#girdi-parametrelerinin-marshallingi)
      - [Çıktı Parametrelerinin Marshalling'i (Referanslar: `int&`, `float&`, `std::string&`)](#çıktı-parametrelerinin-marshallingi-referanslar-int-float-stdstring)
      - [`Callback_Result` Nesnesi: Kapsamlı Analiz](#callback_result-nesnesi-kapsamlı-analiz)
    - [3.6. `Plugin_Module`: Dinamik Modül Yönetimi](#36-plugin_module-dinamik-modül-yönetimi)
      - [Sözdizimi ve Amaç](#sözdizimi-ve-amaç)
      - [Bir Modülün Yaşam Döngüsü](#bir-modülün-yaşam-döngüsü)
      - [Modülerleşmenin Faydaları](#modülerleşmenin-faydaları)
    - [3.7. `Plugin_Call`: Eklentinin Dahili Nativelerini Çağırma](#37-plugin_call-eklentinin-dahili-nativelerini-çağırma)
      - [Sözdizimi ve Performans Avantajları](#sözdizimi-ve-performans-avantajları)
    - [3.8. SDK Yardımcı Fonksiyonları](#38-sdk-yardımcı-fonksiyonları)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Önerilir)](#stdstring-plugin_formatconst-char-format--önerilir)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Uygulama Detayı)](#stdstring-samp_sdkformatconst-char-format--uygulama-detayı)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. SDK'nın İç Anatomisi ve Mimarisi](#4-sdknın-i̇ç-anatomisi-ve-mimarisi)
    - [4.1. `core.hpp`: Minimalist Temel](#41-corehpp-minimalist-temel)
    - [4.2. `platform.hpp` ve `version.hpp`: Uyumluluk ve Metadatalar](#42-platformhpp-ve-versionhpp-uyumluluk-ve-metadatalar)
    - [4.3. `function_hook.hpp`: x86 Yakalama Motoru](#43-function_hookhpp-x86-yakalama-motoru)
    - [4.4. `interceptor_manager.hpp`: AMX Hook Kontrolcüsü](#44-interceptor_managerhpp-amx-hook-kontrolcüsü)
    - [4.5. `amx_manager.hpp`: `AMX*` Örneklerini Yönetme](#45-amx_managerhpp-amx-örneklerini-yönetme)
    - [4.6. `public_dispatcher.hpp`: `Plugin_Public` Callbacks Yönlendiricisi](#46-public_dispatcherhpp-plugin_public-callbacks-yönlendiricisi)
    - [4.7. `native.hpp`: Eklenti Nativelerini Yönetme ve Çağırma](#47-nativehpp-eklenti-nativelerini-yönetme-ve-çağırma)
    - [4.8. `native_hook_manager.hpp`: Nativelerin Hook Motoru](#48-native_hook_managerhpp-nativelerin-hook-motoru)
    - [4.9. `callbacks.hpp` \& `amx_memory.hpp`: C++ -\> Pawn Çağrıları ve RAII](#49-callbackshpp--amx_memoryhpp-c---pawn-çağrıları-ve-raii)
    - [4.10. `amx_api.hpp` \& `amx_helpers.hpp` \& `amx_defs.h`: AMX'e Soyutlanmış Erişim](#410-amx_apihpp--amx_helpershpp--amx_defsh-amxe-soyutlanmış-erişim)
  - [5. Derleme ve Dağıtım](#5-derleme-ve-dağıtım)
    - [Mimari ve Platform Gereksinimleri](#mimari-ve-platform-gereksinimleri)
    - [Derleme Komut Örnekleri](#derleme-komut-örnekleri)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (Windows'ta MinGW)**](#gcc--clang-windowsta-mingw)
    - [Dağıtım İçin Dikkate Alınması Gerekenler](#dağıtım-i̇çin-dikkate-alınması-gerekenler)
  - [Lisans](#lisans)
    - [Kullanım Şartları ve Koşulları](#kullanım-şartları-ve-koşulları)
      - [1. Verilen İzinler](#1-verilen-i̇zinler)
      - [2. Zorunlu Koşullar](#2-zorunlu-koşullar)
      - [3. Telif Hakları](#3-telif-hakları)
      - [4. Garanti Reddi ve Sorumluluk Sınırlaması](#4-garanti-reddi-ve-sorumluluk-sınırlaması)

## 1. Giriş ve Tasarım Felsefesi

### SA-MP'nin Standart C API'si ile İlgili Sorun

SA-MP eklenti API'si bir C programlama arayüzüdür. İşlevsel ve temel olmasına rağmen, düşük seviyeli programlamanın doğasında bulunan zorlukları sunar:
- **Manuel Bellek Yönetimi:** `amx_Allot` ve `amx_Release` gibi fonksiyonlar, geliştiricinin AMX yığınında belleği açıkça ayırmasını ve serbest bırakmasını gerektirir. Bu, yaygın bir bellek sızıntısı ve çalışma zamanı hatası kaynağıdır.
- **Zayıf Türleme ve Manuel Dönüşümler:** Parametreler bir `cell` dizisi olarak geçirilir, bu da `cell`, `int`, `float` ve `char*` arasında açık (ve genellikle güvensiz) dönüşümleri zorunlu kılar.
- **Sözcük ve Tekrarlayan Kod:** Bir `cell* params` dizisinden birden çok parametre çıkarmak, string boyutlarıyla uğraşmak ve C++'dan Pawn'a geri çağrılar için AMX yığınını yönetmek tekrarlayan kod gerektirir.
- **Arayüzün Kırılganlığı:** Derleme zamanı doğrulamasının (type safety) olmaması, parametre geçişindeki veya türlerdeki hataların yürütmeye kadar fark edilmeyebileceği, çökmelere veya tanımsız davranışlara neden olabileceği anlamına gelir.

### SA-MP SDK Çözümü: Güvenlik ve Performansla Soyutlama

SA-MP SDK bu sorunları güçlü bir C++ soyutlama katmanı sağlayarak ele alır:
- **RAII (Resource Acquisition Is Initialization):** AMX'de otomatik bellek yönetimi. `Amx_Scoped_Memory`, ayrılan belleğin serbest bırakılmasını garanti eder.
- **Tip Güvenliği:** Parametrelerin C++ ve Pawn arasında otomatik ve güvenli dönüşümü. `int`, `float`, `std::string` ile doğrudan ilgilenirsiniz.
- **Kompakt ve İdiomatik Sözdizimi:** Makrolar ve şablonlar, geleneksel C API'sinden çok modern C++'a benzeyen temiz bir API sağlar.
- **Sağlam Yakalama:** Gelişmiş bir hooking motoru, Pawn geri çağrılarının şeffaf bir şekilde yakalanmasını (`Plugin_Public`), yeni nativelerin oluşturulmasını (`Plugin_Native`) ve **mevcut SA-MP native fonksiyonlarının hooklanmasını ve zincirlenmesini (`Plugin_Native_Hook`)** sağlar.
- **Yüksek Performans:** Soyutlamaların ek yükünü en aza indirmek için derleme zamanı hashing'i (FNV1a), fonksiyon önbelleğe alma ve `thread_local` optimizasyonları yaygın olarak kullanılır.

### Yalnızca Başlık Modeli: Avantajlar ve Etkileri

SDK yalnızca başlık dosyalarından (`.hpp`, `.h`) oluşur.
- **Avantajlar:**
   - **Basitleştirilmiş Entegrasyon:** Oluşturulacak, bağlanacak veya dağıtılacak kütüphaneler yoktur. Sadece başlıkları dahil edin.
   - **Derleyici Optimizasyonları:** Derleyici, SDK ve eklentinizin kodunun tamamını görebilir, agresif inlining ve bağlama zamanı optimizasyonlarına izin verir, bu da daha hızlı ikili dosyalara yol açabilir.
- **Etkileri:**
   - **Derleme Süresi:** Çok büyük projeler için, SDK kodunun tekrar tekrar dahil edilmesi nedeniyle derleme daha uzun sürebilir. Bu, dahil etme koruyucuları ve C++'ın "yalnızca ihtiyacınız olanı dahil et" doğası ile hafifletilir.
   - **Uygulama Makroları:** `SAMP_SDK_IMPLEMENTATION` makrosuna olan ihtiyaç, sembol yeniden tanımlarını önlemek için yalnızca başlık modelinin bir sonucudur.

## 2. Kurulum ve Ortam

### Derleme Gereksinimleri

- **C++ Derleyici:** C++14 veya üzeri ile uyumlu (SDK belirli optimizasyonlar için C++14, C++17 ve C++20 özelliklerini kullanır, ancak C++14 minimumdur).
   - GCC (sürüm 7+)
   - Clang (sürüm 5+)
   - MSVC (Visual Studio 2015/2017/2019/2022)
- **Mimari:** **x86 (32-bit)**. SA-MP yalnızca bu mimaride çalışır. SDK, yanlış mimarinin tespit edilmesi durumunda derleme hataları verecek olan `platform.hpp` içinde kontroller içerir.
- **İşletim Sistemi:** Windows veya Linux.

### Önerilen Dosya Yapısı

Açıklık ve düzen için, SDK'yı bir `samp-sdk` alt klasöründe düzenlemek yaygındır.

```
meu_plugin/
├── samp-sdk/
│   ├── // Outros arquivos do SDK
│   └── samp_sdk.hpp             // The main header to include
│
├── src/
│   ├── main.cpp                  // Where SAMP_SDK_IMPLEMENTATION is defined
│   └── my_custom_logic.cpp       // Optional, to organize code
│
└── CMakeLists.txt (ou .vcxproj, Makefile)
```

### Temel Yapılandırma Makroları

Bu makroları her zaman `samp_sdk.hpp`'yi dahil etmeden *önce* tanımlayın.

#### `SAMP_SDK_IMPLEMENTATION`

- **Amaç:** Bu `.cpp` dosyasının eklentinin dışa aktarma fonksiyonlarının (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`) uygulamalarını oluşturması gerektiğini derleyiciye bildirir. **SDK, bu fonksiyonlar için `.def` dosyalarına (Windows'ta) veya `__attribute__((visibility("default")))` bildirimlerine (Linux'ta) gerek kalmadan bu fonksiyonların dışa aktarılmasını otomatik olarak halleder.**
- **Teknik Etki:** Bu makro olmadan, bağlayıcı gerekli dışa aktarmaları bulamaz ve SA-MP sunucusu eklentinizi yükleyemez.
- **Temel Kural:** **Bu makroyu tüm projenizde SADECE BİR `.cpp` dosyasında tanımlayın.** Birden fazla dosyada tanımlamak "çift sembol" bağlama hatasına neden olur.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // The macro makes the SDK export the necessary functions automatically.
#include "samp-sdk/samp_sdk.hpp"

// ... your plugin code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Amaç:** Pawn komut dosyasının yaşam döngüsü geri çağrılarını (`OnAmxLoad`, `OnAmxUnload`) ve C++'da yeni native'ler oluşturma işlevselliğini (`Plugin_Native`) etkinleştirir.
- **Etkinleştirilen İşlevler:**
   - `OnAmxLoad(AMX* amx)` ve `OnAmxUnload(AMX* amx)` geri çağrıları.
   - `Plugin_Native` kullanarak yeni C++ native'lerinin bildirimi ve kaydı.
   - Kendi eklentiniz içinde `Plugin_Native` ile oluşturulan native'leri çağırmak için `Plugin_Call` makrosu.
- **Teknik Etki:** Bu makro tanımlandığında, SDK tüm `Plugin_Native`'lerinizi otomatik olarak toplar. `Supports()` fonksiyonunda, projenizde herhangi bir `Plugin_Native` varsa `SUPPORTS_AMX_NATIVES` bayrağı otomatik olarak eklenir.
- **Esneklik:** **Bu makroyu birden çok `.cpp` dosyasında tanımlayabilirsiniz.** SDK'nın statik kayıt sistemi, farklı derleme birimlerindeki tüm native'leri tek bir global listede birleştirecektir.

```cpp
// my_natives.cpp (can be a separate file from main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Only to enable Plugin_Native and the OnAmxLoad/OnAmxUnload callbacks
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Amaç:** Sunucu tarafından düzenli olarak çağrılan `OnProcessTick()` geri çağrısını etkinleştirir.
- **Teknik Etki:** `SUPPORTS_PROCESS_TICK` bayrağını `Supports()` fonksiyonuna otomatik olarak ekler.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logic executed every server "tick" (e.g., 20ms)
    // Be careful with heavy operations here!
}
```

### SA-MP Tanımları ve Sabitleri (`samp_defs.hpp`)

Bu dosya, `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST` gibi bilinen tüm SA-MP sabitlerini ve limitlerini sağlar. `samp_sdk.hpp` tarafından otomatik olarak dahil edilir ve kodun uyumluluğunu ve okunabilirliğini sağlamak için kullanılmalıdır.

## 3. Kapsamlı API Kullanım Kılavuzu

### 3.1. Eklentinin Yaşam Döngüsü

Aşağıdaki fonksiyonlar, eklentinizin SDK tarafından otomatik olarak dışa aktarılan giriş ve çıkış noktalarıdır.

#### `bool OnLoad()`

- **Açıklama:** SA-MP sunucusu tarafından eklentiniz belleğe başarıyla yüklendikten sonra çağrılan ilk fonksiyon.
- **Kullanım:** Herhangi bir sistemi başlatmak, yapılandırmaları yüklemek, veritabanı bağlantılarını açmak veya modülleri yüklemek (`Plugin_Module`) için idealdir.
- **Dönüş Değeri:**
   - `true`: Eklenti başarıyla başlatıldı ve yükleme devam ediyor.
   - `false`: Eklenti başlatılırken bir hata oluştu. Yükleme iptal edilecek ve eklenti boşaltılacaktır.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Example: Load a module (more details in section 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database Module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load the database module!");

        return false; // Aborts loading of the main plugin
    }

    return true;
}
```

#### `void OnUnload()`

- **Açıklama:** SA-MP sunucusu tarafından eklentiniz bellekten boşaltılmadan önce çağrılan son fonksiyon.
- **Kullanım:** Kaynakları temizlemek, bağlantıları kapatmak, durumları kaydetmek ve hiçbir kaynağın sızdırılmamasını sağlamak için idealdir. SDK, modüllerin (`Plugin_Module`) boşaltılmasını otomatik olarak yönetir.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // No manual action is needed for modules loaded via Plugin_Module;
    // the SDK handles it.
}
```

#### `unsigned int GetSupportFlags()`

- **Açıklama:** SA-MP sunucusuna eklentinizin hangi özellikleri desteklediğini ve kullanmak istediğini bildirir.
- **Kullanım:** **Her zaman `SUPPORTS_VERSION` (veya `SAMP_PLUGIN_VERSION`) döndürün.** `SUPPORTS_AMX_NATIVES` ve `SUPPORTS_PROCESS_TICK` bayrakları, sırasıyla `Plugin_Native`'ler varsa ve/veya `SAMP_SDK_WANT_PROCESS_TICK` makrosu tanımlıysa SDK tarafından otomatik olarak eklenir. Bu, bakımı basitleştirir ve hataları önler.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // The SDK automatically adds the necessary flags.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Gerektirir:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Açıklama:** Sunucuda yeni bir Pawn script (bir Gamemode veya Filterscript) yüklendiğinde ve başlatıldığında çağrılır.
- **Kullanım:** Her AMX scripti için belirli bir mantığa ihtiyacınız varsa veya script başına belirli verileri başlatıyorsanız.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxLoad(AMX* amx) {
    // amx represents the new loaded script instance.
    Samp_SDK::Log("AMX script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Gerektirir:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Açıklama:** Bir Pawn scripti sunucudan boşaltıldığında çağrılır.
- **Kullanım:** O belirli `AMX*` ile ayırdığınız veya ilişkilendirdiğiniz kaynakları temizlemek için.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Gerektirir:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Açıklama:** Sunucu "tick"i başına tekrar tekrar çağrılır (genellikle saniyede 20 kez veya her 50ms'de bir).
- **Kullanım:** Sürekli arka plan mantığı, zamanlayıcılar, oyuncu olaylarına bağlı olmayan durum güncellemeleri veya veri senkronizasyonu için.
- **Dikkat:** Sunucuda gecikmeye neden olabileceğinden, burada engelleme veya hesaplama açısından yoğun işlemlerden kaçının.

```cpp
// main.cpp (with SAMP_SDK_WANT_PROCESS_TICK defined)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Every 10 seconds (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. `Plugin_Public`: Pawn Olaylarını Yakalama

`Plugin_Public` makrosu, Pawn geri çağrılarını C++ kodunuzda almak için birincil köprüdür.

#### Sözdizimi ve Bildirim

- `Plugin_Public(PublicAdı, Tip1 Param1, Tip2 Param2, ...)`
- Bildirdiğiniz C++ fonksiyonunun adı, Pawn geri çağrısının adıyla **aynı olmalıdır** (ör: `OnPlayerConnect`).
- C++ parametre türleri (`int`, `float`, `std::string`) SDK tarafından otomatik olarak dönüştürülür.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Player %d said: %s", playerid, text.c_str());

    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Otomatik Parametre Marshalling'i

SDK, AMX'in `cell stack`'inden okuma ve belirtilen C++ türlerine dönüştürme işlemlerini otomatik olarak halleder:
- `int`: Doğrudan `cell`'den dönüştürülür.
- `float`: `amx::AMX_CTOF` kullanılarak `cell`'den dönüştürülür.
- `std::string`: SDK, AMX'deki string adresini okur, C++'da bir `std::string` ayırır ve içeriği kopyalar.

#### Akış Kontrolü: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

`Plugin_Public` fonksiyonunuz tarafından döndürülen değer çok önemlidir ve geri çağrının yürütme akışını belirler:
- `return PLUGIN_PUBLIC_CONTINUE;` (değer `1`): Geri çağrı yürütmesinin **devam etmesi gerektiğini** belirtir. Bu geri çağrıyı yakalayan başka eklentiler varsa, bunlar çağrılacaktır (ters yükleme sırasına göre). Ardından, Pawn scriptindeki orijinal `public` çağrılacaktır.
- `return PLUGIN_PUBLIC_STOP;` (değer `0`): Geri çağrı yürütmesinin **durdurulması gerektiğini** belirtir. Bu olay için başka hiçbir eklenti (daha düşük öncelikli olanlar) veya Pawn scriptindeki orijinal `public` çağrılmayacaktır. Bu, SA-MP'nin varsayılan davranışını "geçersiz kılan" veya "engelleyen" bir sistem uygulamak için idealdir.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Freezes the player
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Player %d frozen.", playerid));

        return PLUGIN_PUBLIC_STOP; // Prevents the command from being processed by other scripts.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Allows other commands to be processed.
}
```

#### Hayalet Callbacks

`Plugin_Public`'in gelişmiş bir özelliği "Hayalet Geri Çağrılar" desteğidir. Bu, Pawn geri çağrısını, gamemode veya filterscript'in `.amx` scriptinde **mevcut olmasa bile** yakalayabileceğiniz anlamına gelir. SDK, sunucuyu C++ hook'unuzu yine de çağırması için "kandırır". Bu, dahili geri çağrılar veya Pawn scriptinde bir `public`'in varlığına bağlı kalmadan yeni işlevler oluşturmak için kullanışlıdır.

```cpp
// You can define a callback that the Pawn script does not have, but your plugin will hear it.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Custom internal event received: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// To "trigger" this event from another point in your C++ code:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// The call will go to your Plugin_Public above, even if there is no OnMyCustomInternalEvent in Pawn.
```

### 3.3. `Plugin_Native`: C++'da Yerel Fonksiyonlar Oluşturma

`Plugin_Native`, Pawn işlevselliğini yüksek performanslı C++ koduyla genişletmenize olanak tanır.

#### Sözdizimi ve Sabit İmza

- `Plugin_Native(NativeAdı, AMX* amx, cell* params)`
- C++ fonksiyonu tam olarak bu imzaya sahip olmalıdır: `cell NativeAdı(AMX* amx, cell* params)`.
- `NativeAdı`, Pawn scriptlerinin kullanacağı addır.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementation ...
    return 0;
}
```

#### Nativelerin Otomatik Kaydı

> [!NOTE]
> `amx_Register`'ı manuel olarak çağırmanız **gerekmez**. SDK, tüm `Plugin_Native`'lerinizi (`samp_sdk.hpp`'yi dahil etmiş ve `SAMP_SDK_WANT_AMX_EVENTS`'i tanımlamış herhangi bir `.cpp` dosyasında) otomatik olarak algılar ve her yüklenen AMX scriptinde (`OnAmxLoad`) bunları otomatik olarak kaydeder.

#### Parametre Çıkarma: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Açıklama:** Birden çok parametreyi sırayla çıkarmak için daha basit bir yardımcı.
- **Kullanım:** `Register_Parameters(değişken1, değişken2, ...)`
- **Sınırlamalar:** Yalnızca girdi parametreleri içindir. İsteğe bağlı parametreleri veya dizine göre erişimi işlemez.
- **Desteklenen Türler:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extracts the 3 parameters
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (Tam API: `Get`, `Get_REF`, `Set_REF`)

- **Açıklama:** Bir nativenin parametrelerine erişmek için nesne yönelimli bir arayüz sağlayan bir sarıcı sınıfı. Karmaşık senaryolar için daha güçlüdür.
- **Oluşturma:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Açıklama:** Native'e geçirilen parametre sayısını döndürür.
- **Kullanım:** İsteğe bağlı parametreleri işlemek için önemlidir.

###### `p.Get<T>(size_t index)`

- **Açıklama:** Dizine göre bir giriş parametresini çıkarır ve `T` türüne dönüştürür.
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

- **Açıklama:** Bir **referans** parametresinin (Pawn işaretçisi) değerini alır ve `out_value`'ya depolar.
- **Kullanım:** Pawn'dan referans yoluyla geçirilen değerleri okumak için.
- **Dönüş Değeri:** AMX adresi geçerliyse `true`, aksi takdirde `false`.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Gets the values from references (Pawn passed addresses)
    p.Get_REF(1, health); // Reads the value of Float:health
    p.Get_REF(2, money);   // Reads the value of money
    
    Samp_SDK::Log("Player %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Now, modify them
    health = 50.0f;
    money += 100;
    
    // And writes them back to Pawn's memory
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Açıklama:** Bir referans parametresini okumak için bir `std::optional<T>` döndürür. C++17 ve üzeri için daha güvenlidir.

###### `p.Set_REF<T>(size_t index, T value)`

- **Açıklama:** Bir `T` değerini bir Pawn **referans** parametresine yazar (Pawn'ın geçirdiği adres).
- **Kullanım:** Referans yoluyla geçirilen değerleri değiştirmek için, Pawn'ın değişikliği görmesini sağlar.
- **Dönüş Değeri:** Yazma başarılı olursa `true`, aksi takdirde `false`.

#### Değerlerin Geri Dönüşü

- `Plugin_Native` fonksiyonunuz bir `cell` döndürmelidir.
- Bir `int` veya `bool` döndürmek için, `cell`'e bir cast kullanın.
- Bir `float` döndürmek için `amx::AMX_FTOC(benim_float)` kullanın.

```cpp
// Returns a bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Returns a float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Returns 100.0f
}
```

### 3.4. `Plugin_Native_Hook`: Mevcut SA-MP Nativelerini Yakalama

`Plugin_Native_Hook` makrosu, mevcut herhangi bir SA-MP native fonksiyonunun veya diğer eklentilerin davranışını yakalamanıza ve değiştirmenize olanak tanır. Bu, sunucunun varsayılan mantığını genişletmek veya değiştirmek için güçlü bir mekanizmadır.

#### Sözdizimi ve Sabit İmza

- `Plugin_Native_Hook(NativeAdı, AMX* amx, cell* params)`
- C++ fonksiyonu tam olarak bu imzaya sahip olmalıdır: `cell NativeAdı(AMX* amx, cell* params)`.
- `NativeAdı`, hooklamak istediğiniz native'in tam adı olmalıdır (ör: `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepts the SendClientMessage native
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Important to call the original
}
```

#### Hook'un Kaydı ve Aktivasyonu

> [!NOTE]
> `Plugin_Native_Hook` için `amx_Register`'ı manuel olarak çağırmanız veya `SAMP_SDK_WANT_AMX_EVENTS`'i özellikle tanımlamanız **gerekmez**. SDK, hook'larınızı otomatik olarak algılar ve kaydeder. Bir AMX scriptinin ilk yürütülmesinde, SDK, native tablosundaki native işaretçisini, `Plugin_Native_Hook` fonksiyonunuza yönlendiren bir "trampoline" ile değiştirir. Bu süreç, birden çok eklentinin güvenli hook zincirini garanti eder.

#### Orijinal Native'i Çağırma (Hook Zinciri): `Call_Original_Native`

`Plugin_Native_Hook` fonksiyonunuz içinde, orijinal fonksiyonu (veya zincirdeki bir sonraki hook'u) çağırmak için `Call_Original_Native(NativeAdı)` makrosunu **KULLANMALISINIZ**. Bu, aşağıdakiler için hayati öneme sahiptir:
- **İşlevselliği Korumak:** Orijinalini çağırmazsanız, hook'lanan native diğer eklentiler veya sunucu için çalışmayı durdurur.
- **Hook Zincirlemesi:** Birden çok eklentinin aynı native'i hooklamasına ve tüm hook'ların sırayla yürütülmesine olanak tanır.
- **Dönüş Değeri Manipülasyonu:** `Call_Original_Native`'in dönüş değerini, hook fonksiyonunuzdan döndürmeden önce inceleyebilir ve hatta değiştirebilirsiniz.

```cpp
// Example: Blocking SendClientMessage if it contains a specific word
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extract parameters for analysis
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // We don't need the color for this logic
    std::string message = p.Get_String(2); // Get the message string

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGE BLOCKED for playerid %d: %s", playerid, message.c_str());

        return 0; // Returns 0 (false) to Pawn, indicating the message was not sent.
                  // And most importantly, we DO NOT call Call_Original_Native, blocking the message.
    }

    // If the message does not contain the prohibited word, we call the original native
    // and return its value, ensuring that the message is sent normally
    // and that other hooks (if they exist) are executed.
    return Call_Original_Native(SendClientMessage);
}
```

#### `Plugin_Native_Hook` için Tam Örnek

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS is not strictly necessary for hooks, but it's common to have OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook for the CreateVehicle native
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extract the CreateVehicle native parameters for inspection
    int modelid = p.Get<int>(0);
    float x = p.Get<float>(1);
    float y = p.Get<float>(2);
    float z = p.Get<float>(3);
    float angle = p.Get<float>(4);
    int color1 = p.Get<int>(5);
    int color2 = p.Get<int>(6);
    int respawn_delay = p.Get<int>(7);
    bool addsiren = p.Get<bool>(8);

    Samp_SDK::Log("HOOK: CreateVehicle called! Model: %d, Pos: (%.2f, %.2f, %.2f)", modelid, x, y, z);

    // Example of how to *modify* an input parameter
    // If the model is 400 (Landstalker), we change it to 401 (Bravura)
    if (modelid == 400) {
        // We directly modify the 'params' array for the original call
        params[1] = static_cast<cell>(401); // The model is at position 0 of the parameter array (params[1])
        Samp_SDK::Log("  -> Model 400 changed to 401 before creation.");
    }
    
    // We call the original native (or the next hook in the chain) with the potentially modified parameters
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle returned: %d (Vehicle ID)", (int)original_retval);

    // You can modify the return value here before returning it to Pawn.
    // Example: if vehicle creation failed, return a custom invalid ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Vehicle creation failed in the original native.");

        return -1; // Return a different value to Pawn.
    }

    return original_retval; // Return the value that the original native returned (or the modified one above).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Minimal implementations for the lifecycle
bool OnLoad() {
    Samp_SDK::Log("Native Hook Example Plugin loaded!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Native Hook Example Plugin unloaded!");
}

// These callbacks will only be present if SAMP_SDK_WANT_AMX_EVENTS is defined
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detected: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detected: %p", (void*)amx);
}*/
```
> [!WARNING]
> Girdi parametrelerini değiştirmek için `cell* params` dizisini doğrudan değiştirmek dikkat gerektirir. Parametrelerin sırasını ve türünü anladığınızdan emin olun. Çoğu kullanım durumu için, incelemek için `p.Get(...)` ve zinciri devam ettirmek için `Call_Original_Native(...)` yeterlidir. `params`'ı doğrudan değiştirmek, yalnızca parametrenin bir değer olduğunu ve orijinal çağrı için değiştirilmesi gerektiğini bildiğinizde yapılmalıdır. Stringler ve diziler için, değişiklik daha karmaşıktır ve genellikle mevcut adrese yazmak veya yeniden tahsis etmek için `amx::Set_String` kullanmayı içerir; bu da yeni değerlerle `Pawn_Native` aracılığıyla native'i çağırmak ve orijinal çağrıyı iptal etmek için hook'unuzdan `0` döndürmekle yönetmek daha kolay olabilir.

### 3.5. `Pawn_*` Makroları: C++'dan Pawn Fonksiyonlarını Çağırma

Bu makrolar `Plugin_Public` ve `Plugin_Native`'in tersidir: C++ kodunuzun Pawn fonksiyonlarını çağırmasına izin verirler.

#### `Pawn_Native(NativeAdı, ...)`

- **Amaç:** C++'dan SA-MP native fonksiyonlarını (veya diğer eklentilerin native'lerini) çağırmak için önerilen yol.
- **Mekanizma:** SDK'nın dahili önbelleğinde native işaretçisini arar (`Amx_Register_Detour` tarafından doldurulur). Bulunursa, native'i bir `Amx_Sandbox` ortamında (sahte ve yalıtılmış bir AMX örneği) yürütür.
- **Performans:** En verimli olanıdır, çünkü pahalı `public` aramasını önler ve doğrudan native işaretçisiyle etkileşime girer.

#### `Pawn_Public(PublicAdı, ...)`

- **Amaç:** Bir Pawn scriptindeki belirli bir public fonksiyonu çağırır.
- **Mekanizma:** `Amx_Manager` tarafından yönetilen `AMX*` örnekleri arasında döner, adı ile `public`'i arar ve yürütür.
- **Performans:** Arama ve gerçek `amx_Exec` nedeniyle `Pawn_Native`'den daha az verimlidir. Genellikle `public`'ler `native`'lerden daha yavaştır.
- **Kullanım:** Gamemode/Filterscript'lerinizde native olmayan özel olayları çağırmak için idealdir.

#### `Pawn(FonksiyonAdı, ...)`

- **Amaç:** Fonksiyonun native mi yoksa public mi olduğunu tahmin etmeye çalışan bir kolaylık makrosu.
- **Mekanizma:** İlk olarak, `Pawn_Native` olarak çağırmayı dener. Başarısız olursa (native bulunamazsa), `Pawn_Public` olarak çağırmayı dener.
- **Performans:** Fonksiyon native ise, çift arama denemesi nedeniyle `Pawn_Native`'den biraz daha yavaş olabilir. `public`'ler için performans `Pawn_Public` ile aynıdır.
- **Kullanım:** Native mi yoksa public mi olduğundan emin olmadığınız fonksiyonlar için veya birini diğerinden sonra deneme tekrarlayan koddan kaçınmak için.

#### Sözdizimi ve Kurallar

- **Fonksiyon Adı:** Her zaman Pawn fonksiyonunun adını **doğrudan, tırnak işaretleri olmadan** kullanın. SDK bunu dahili olarak string'e dönüştürecektir.
- **Parametreler:** C++ parametrelerini doğrudan geçirin.

```cpp
// Correct:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Incorrect (but would technically work due to hashing, avoid):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Girdi Parametrelerinin Marshalling'i

SDK, C++ türlerinizi AMX'in `cell` formatına dönüştürür, gerektiğinde belleği yönetir:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (`amx::AMX_FTOC` kullanılarak)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (AMX'de bellek ayırır, string'i kopyalar ve `amx_addr` adresini geçirir)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Çıktı Parametrelerinin Marshalling'i (Referanslar: `int&`, `float&`, `std::string&`)

Bu, kolaylık ve güvenlik için önemli bir anahtar işlevdir. Bir işaretçi (referans) bekleyen Pawn fonksiyonları için, SDK tüm bellek ayırma/serbest bırakma ve veri kopyalama sürecini otomatikleştirir.

- **Nasıl kullanılır:** Değişkeninizi referans yoluyla (`&`) geçirin.
- **Mekanizma:** SDK, AMX yığınında bellek ayırır, bu AMX adresini Pawn fonksiyonuna geçirir, Pawn fonksiyonunun bu adresi doldurmasını bekler, değeri geri okur ve AMX belleğini serbest bırakır. Hepsi şeffaf bir şekilde.
- **`std::string&` ile:** SDK, string için AMX'de standart bir tampon (256 hücre) ayırır.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Location of %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interior:%d World:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### `Callback_Result` Nesnesi: Kapsamlı Analiz

Tüm `Pawn_*` çağrıları bir `Callback_Result` nesnesi döndürür. Bu nesne, Pawn çağrısının sonucu için güvenli bir sarıcıdır.

- `Callback_Result() noexcept`: Varsayılan yapılandırıcı, başarısızlığı gösterir (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Değeri ile başarı veya başarısızlık için yapılandırıcı.
- `explicit operator bool() const`: Çağrının başarılı olup olmadığını kontrol etmek için `if (result)` kullanılmasına izin verir.
- `operator cell() const`: Değeri almak için sonucu `cell`'e dönüştürmeye izin verir.
- `float As_Float() const`: Sonucu `float` olarak almak için kolaylık.
- `cell Value() const`: Ham `cell` değerini döndürür.
- `bool Success() const`: Pawn çağrısı başarılı olursa `true` döndürür.
- `int Get_Amx_Error() const`: Çağrı başarısız olursa AMX hata kodunu döndürür (başarılı için 0).

```cpp
// Example: Getting a player's health.
// The native GetPlayerHealth(playerid, &Float:health) expects a playerid and a reference to health.
int playerid = 0; // Example player ID
float player_health = 0.0f;

// We call GetPlayerHealth, passing playerid and player_health by reference.
// The SDK will handle the marshalling for the 'health' output parameter.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Checks if the call was successful (operator bool)
    // The value returned by result.As_Float() or result (operator cell)
    // would be the return value of the *native*, not the output parameter.
    // The health value has already been updated in 'player_health' due to output parameter marshalling.
    Samp_SDK::Log("Player %d has %.1f health.", playerid, player_health);
}
else {
    // The call failed, perhaps the player does not exist or the native was not found.
    Samp_SDK::Log("Error getting player %d health. AMX code: %d", playerid, result.Get_Amx_Error());
}

// For natives that return a value and use output parameters (less common, but possible),
// you would use both:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param is already updated
// }
```

### 3.6. `Plugin_Module`: Dinamik Modül Yönetimi

`Plugin_Module` makrosu, eklentinizin diğer eklentiler için bir "yükleyici" görevi görmesini sağlayarak modüler ve genişletilebilir bir mimari oluşturur. Bu şekilde yüklenen bir modül, kendi olay yaşam döngüsü ana eklenti tarafından yönetilen birinci sınıf bir eklenti olarak ele alınır.

#### Sözdizimi ve Amaç

- `Plugin_Module(const char* base_filename, const char* module_directory, const char* optional_success_message)`
- `base_filename`: Modül dosyasının **uzantısız** *temel* adı (ör: `my_module.dll` veya `my_module.so` için `"my_module"` kullanın). SDK otomatik olarak uygun `.dll` veya `.so` uzantısını ekleyecektir.
- `module_directory`: Modül dosyasının bulunduğu dizinin yolu (ör: `"plugins/my_custom_modules"`). **Dosya adını buraya eklemeyin.** SDK tam yolu birleştirecektir (`module_directory/base_filename.ext`).
- `optional_success_message`: Modül başarıyla yüklenirse sunucu konsoluna günlüklenmek üzere isteğe bağlı bir mesaj.

```cpp
// main.cpp, inside OnLoad()

// Loads the 'core_logic.dll' (or 'core_logic.so') module
// which is located in the server's 'modules/custom/' folder.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic Module loaded successfully!"))
    return (Samp_SDK::Log("FATAL ERROR: Failed to load 'core_logic' module!"), false);

// Loads the 'admin_system.dll' (or 'admin_system.so') module
// which is located directly in the server's 'plugins/' folder.
if (!Plugin_Module("admin_system", "plugins", "Administration Module activated."))
    Samp_SDK::Log("WARNING: Administration Module could not be loaded.");
```

#### Bir Modülün Yaşam Döngüsü

Bir modül, normal bir eklenti gibi `Load`, `Unload` ve `Supports` fonksiyonlarını dışa aktarmalıdır. SDK, modülün yaşam döngüsünü aşağıdaki gibi yönetir:

- **Yükleme:** `Plugin_Module` çağrıldığında, SDK:
   1. Tam dosya yolunu oluşturur (ör: `modules/custom/core_logic.dll`).
   2. İkili dosyayı yüklemek için `Dynamic_Library` (`LoadLibrary`/`dlopen`) kullanır.
   3. **Modülün TÜM yaşam döngüsü fonksiyonlarına yönelik işaretçileri alır:**
      - **Zorunlu:** `Load`, `Unload`, `Supports`. Herhangi biri eksikse, modülün yüklenmesi başarısız olur.
      - **İsteğe Bağlı:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Ana eklentinin `ppData`'sını geçirerek modülün `Load` fonksiyonunu çağırır.
   5. `Load` `true` döndürürse, modül dahili yüklü modüller listesine eklenir.

- **Olay Yönlendirme:** Ana eklenti, olayları tüm yüklü modüllere **otomatik olarak yönlendirir**.
 > [!IMPORTANT]
 > Olayların doğru bir şekilde yönlendirilmesi için **ana eklenti** (`Plugin_Module`'ı çağıran eklenti) bu olayları alacak şekilde yapılandırılmış olmalıdır.
 > - `AmxLoad` ve `AmxUnload`'ın modüllerde çalışması için, ana eklentinin `SAMP_SDK_WANT_AMX_EVENTS` makrosunu tanımlaması gerekir.
 > - `ProcessTick`'in modüllerde çalışması için, ana eklentinin `SAMP_SDK_WANT_PROCESS_TICK` makrosunu tanımlaması gerekir.

- **Boşaltma:** Ana eklentinizin `OnUnload`'u sırasında, SDK `Plugin_Module` aracılığıyla yüklenen tüm modülleri boşaltır. Bu, yükleme sırasının **tersine** (en son yüklenen, ilk boşaltılır) yapılır, bu da bağımlılıkları yönetmek ve kaynakların doğru bir şekilde serbest bırakılmasını sağlamak için kritik öneme sahiptir.

#### Modülerleşmenin Faydaları

- **Kod Düzenlemesi:** Büyük eklentileri daha küçük, yönetilebilir bileşenlere ayırın, her biri kendi modül dosyasında.
- **Yeniden Kullanılabilirlik:** Kodun yeniden kullanımını teşvik ederek farklı eklentiler tarafından kullanılabilecek genel modüller (ör: bir veritabanı modülü, gelişmiş bir günlük sistemi modülü) oluşturun.
- **Bağımsız Bileşenler:** **Tamamen olay odaklı ve bağımsız** modüller oluşturun. Bir modülün kendi `Plugin_Native`'leri, `Plugin_Public`'leri yakalayabilir ve kendi `OnProcessTick` mantığına sahip olabilir, bağımsız bir eklenti olarak çalışırken bir ana bilgisayar tarafından yüklenir.
- **Dinamik Güncellemeler:** Kontrollü senaryolarda, ana eklentiyi veya tüm sunucuyu yeniden derlemeye ve yeniden başlatmaya gerek kalmadan sisteminizin parçalarını (bir modül `.dll` veya `.so` dosyasını değiştirerek) güncellemeye olanak tanır (ancak bu, sıkı bir sürüm yönetimi ve uyumluluk gerektirir).

### 3.7. `Plugin_Call`: Eklentinin Dahili Nativelerini Çağırma

Kendi eklentiniz içinde tanımlanmış bir `Plugin_Native`'i çağırmak için `Plugin_Call` kullanın.

#### Sözdizimi ve Performans Avantajları

- `Plugin_Call(NativeAdı, Param1, Param2, ...)`
- **Avantaj:** AMX native dizisinde native'i arama ek yükünü önler. SDK, kendi native'leri için ad hash'lerinden fonksiyon işaretçilerine doğrudan bir harita tutar, bu da onları dahili olarak çağırmanın en hızlı yolu haline getirir.
- **Gerektirir:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logic to check level
    return (playerid % 2 == 0) ? 1 : 0; // Example: even level for even IDs
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Calls its own native
                Samp_SDK::Log("Player %d is at a high level!", i);
        }
    }
}
```

### 3.8. SDK Yardımcı Fonksiyonları

#### `Samp_SDK::Log(const char* format, ...)`

- **Açıklama:** Sunucu konsoluna ve `server_log.txt` dosyasına mesajlar yazdırır. `logprintf` için güvenli bir sarıcı.
- **Kullanım:** Hata ayıklama, durum mesajları ve hatalar için.
- **Mekanizma:** Dahili olarak, SDK `ppData[PLUGIN_DATA_LOGPRINTF]` aracılığıyla `logprintf` işaretçisini alır. Fonksiyon, stringin biçimlendirmesini güvenli bir şekilde halleder.

```cpp
// Anywhere in your plugin
Samp_SDK::Log("The plugin was initialized with a value %d and a string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Önerilir)

- **Açıklama:** Bir string'i güvenli bir şekilde biçimlendirir (`sprintf` benzeri) ve bir `std::string` döndürür. Bu, eklentiniz içinde kullanılmak üzere stringleri biçimlendirmenin **önerilen ve en idiomatik yoludur**.
- **Kullanım:** `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, veya C++ kodunuzdaki diğer string ihtiyaçları için biçimlendirilmiş mesajlar oluşturmak için idealdir.
- **Mekanizma:** Dahili olarak, `Plugin_Format` bir `Samp_SDK::Format` çağıran bir makrodur. Biçimlendirilmiş stringin tam boyutunu belirlemek için `vsnprintf` kullanır ve yeterli kapasiteye sahip bir `std::string` ayırır, arabellek taşmalarını önler.

```cpp
int playerid = 0; // Example ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Player %d, your current health is %d.", playerid, health));

// Can also be used for internal logs
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Uygulama Detayı)

- **Açıklama:** `Samp_SDK` ad alanı içinde bulunan, string biçimlendirme için temel uygulama fonksiyonu.
- **Kullanım:** Genellikle kullanıcı tarafından doğrudan çağrılmaz. `Plugin_Format` makrosu, bu fonksiyon için bir kolaylık olarak sağlanır ve diğer SDK makrolarının (`Plugin_Public`, `Plugin_Native`) adlandırma kuralıyla uyumludur. Yalnızca belirli bir nedenle `Plugin_Format` makrosundan kaçınmak istiyorsanız doğrudan çağırırsınız.

```cpp
// Example of how Samp_SDK::Format works, but prefer Plugin_Format
std::string raw_status = Samp_SDK::Format("For internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Açıklama:** Bir AMX string adresini (`cell amx_addr`) bir C++ `std::string`'ine dönüştürür.
- **Kullanım:** Esas olarak `Plugin_Native` ve `Plugin_Native_Hook` içinde, `Register_Parameters` veya `Native_Params` tarafından otomatik olarak dönüştürülmeyen stringlere erişmeniz gerektiğinde (ör: Pawn parametresi bir `const` `string` ise ve otomatik Marshalling için `Plugin_Native` veya `Plugin_Public`'ınızda `std::string` olarak bildirilmemişse).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Gets the string address in AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String from AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. SDK'nın İç Anatomisi ve Mimarisi

Bu bölüm, SA-MP SDK'nın altında yatan mekanizmalarını, mimarisini, ana bileşenlerini ve yüksek seviyeli soyutlamayı sağlamak için nasıl etkileşimde bulunduklarını ortaya koyar. Bu iç işleyişin derinlemesine anlaşılması, geliştiriciyi SDK'yı optimize etmeye, karmaşık sorunları ayıklamaya ve hatta işlevselliğini genişletmeye yetkilendirir.

### 4.1. `core.hpp`: Minimalist Temel

`Samp_SDK::Core`, SA-MP eklenti ortamı tarafından sağlanan düşük seviyeli verilere ilk ve merkezi erişim noktası olarak hizmet veren bir `singleton`'dır. Temel sorumluluğu, temel işlevleri kapsüllemek ve ifşa etmektir.

- **`Samp_SDK::Core::Instance()`**:
   - **Açıklama:** `Core` sınıfının tek global örneğini döndürür. Bu, eklenti verilerine (`ppData`) erişimin tutarlı ve merkezi olmasını sağlamak için bir `singleton` tasarım desenidir.
   - **Mekanizma:** Örnek, eklentinizin `Load()` fonksiyonunda `Core::Instance().Load(ppData)` çağrıldığında bir kez başlatılır.

- **`Get_AMX_Export(PLUGIN_AMX_EXPORT_...)`**:
   - **Açıklama:** AMX API'sinin fonksiyon işaretçilerine güvenli ve dizine göre erişime izin verir. `pAMXFunctions` dizisi (`ppData[PLUGIN_DATA_AMX_EXPORTS]` aracılığıyla alınan) `amx_Exec`, `amx_Register` gibi kritik fonksiyonların adreslerini içerir.
   - **Etki:** `((MyFuncType)((void**)Core::Instance().Get_AMX_Data())[INDEX])(...)` yerine, SDK `amx::` ad alanında tür güvenli sarıcılar (ör: `amx::Exec(...)`) sunarak kodu daha okunabilir ve cast hatalarına daha az eğilimli hale getirir.
   - **Dahili Örnek (`amx_api.hpp`):**
      ```cpp
      // Simplified snippet from amx_api.hpp
      namespace amx {
          template <typename Func, int Index, typename... Args>
          inline auto Call(Args... args) -> decltype(std::declval<Func>()(args...)) {
              using Return_Type = decltype(std::declval<Func>()(args...));
              auto func_ptr = reinterpret_cast<Func>(Core::Instance().Get_AMX_Export(Index));

              if (SAMP_SDK_UNLIKELY(!func_ptr)) {
                  Log("[SA-MP SDK] Fatal: Attempted to call AMX export at index %d, but pAMXFunctions was not loaded!", Index);
                
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
   - **Açıklama:** Sunucu konsoluna ve `server_log.txt`'ye mesaj yazdırmak için standart arayüz olan SA-MP'nin `logprintf` fonksiyonuna bir işaretçi.
   - **Mekanizma:** `Samp_SDK::Log`, mesajlarınızın SA-MP ortamında doğru bir şekilde görüntülenmesini sağlayan bu işaretçiyi kullanan güvenli bir sarıcıdır.

### 4.2. `platform.hpp` ve `version.hpp`: Uyumluluk ve Metadatalar

Bu başlıklar, SDK'nın taşınabilirliği ve optimizasyonu için temel oluşturur, farklı derleme ortamlarına uyum sağlar ve modern C++'ın belirli özelliklerinden yararlanır.

- **Platform ve Mimari Tespiti:**
   - **Mekanizma:** İşletim sistemini tanımlamak için önişlemci makroları (`#if defined(WIN32)`, `#if defined(__linux__)` vb.) kullanır.
   - **Mimari Doğrulama:** SA-MP ve hooking mekanizmasıyla uyumluluk için kritik bir gereksinim olan eklentinin x86 (32-bit) için derlendiğini sağlamak için `static_assert` veya `#error` içerir.
   - **Sembol Dışa Aktarma Yönetimi:**
      - `SAMP_SDK_EXPORT`: `platform.hpp`'de tanımlanan bir makro, `extern "C"` olarak genişler ve Linux'ta `__attribute__((visibility("default")))` ekler. Windows'ta, SDK ana fonksiyonları dışa aktarmak için `pragma comment(linker, "/EXPORT:...")` (MSVC için) veya MinGW standardını kullandığından yalnızca `extern "C"`'yi garanti eder.
      - Bu, eklentinizin yaşam döngüsü fonksiyonlarının (`Supports`, `Load`, `Unload` vb.), derleme ortamından bağımsız olarak, `.def` dosyalarına veya uygulamanızda `__attribute__((visibility("default")))`'ı manuel olarak eklemeye **gerek kalmadan** DLL/SO'nuzdan doğru bir şekilde dışa aktarılmasını sağlar.
   - **Örnek (`platform.hpp` - ilgili parça):**
      ```cpp
      #if defined(SAMP_SDK_WINDOWS)
          // For MSVC, export is managed by pragma linker commands
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C
      #else // Linux
          // For GCC/Clang on Linux, we use the visibility attribute
          #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
      #endif
      // ... other definitions ...
      ```
   - **Örnek (`samp_sdk.hpp` - uygulamanın ilgili parçası):**
      ```cpp
      #if defined(SAMP_SDK_IMPLEMENTATION)

      #if defined(SAMP_SDK_WINDOWS)
          // On Windows (MSVC), we use pragma comment to export the functions.
          // This eliminates the need for a .def file.
          #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
          #pragma comment(linker, "/EXPORT:Load=_Load@4")
          #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
          // ... other exports ...
      #endif

      // Implementation of exported functions
      SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() { /* ... */ }
      SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) { /* ... */ }
      SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() { /* ... */ }
      // ... other functions ...
      #endif
      ```

- **Optimizasyon ve Dallar Tahmini Makroları:**
   - `SAMP_SDK_FORCE_INLINE`:
      - **Mekanizma:** `__forceinline` (MSVC) veya `__attribute__((always_inline)) inline` (GCC/Clang). Derleyiciye fonksiyon gövdesini doğrudan çağrı yerine eklemesini şiddetle önerir, gerçek bir fonksiyon çağrısının ek yükünü ortadan kaldırır.
      - **Kullanım:** SDK içinde küçük ve performans açısından kritik fonksiyonlara uygulanır.
   - `SAMP_SDK_LIKELY(x)` / `SAMP_SDK_UNLIKELY(x)`:
      - **Mekanizma:** `[[likely]]` / `[[unlikely]]` (C++20) veya `__builtin_expect` (GCC/Clang). Bir `if/else` yolunun hangisinin daha olası olduğunu derleyiciye ipuçları.
      - **Etki:** Derleyicinin dallanma tahmini için daha verimli kod üretmesine yardımcı olur, CPU gecikmesini azaltır.
      - **Örnek (`platform.hpp`):**
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

- **Standart C++ Tanımları (`SAMP_SDK_CXX14`, `SAMP_SDK_CXX_MODERN`):**
   - **Mekanizma:** `__cplusplus` ve `_MSVC_LANG` değerlerine dayalı olarak tanımlanan makrolar.
   - **Kullanım:** SDK'nın mevcut olduğunda daha yeni C++ işlevlerini (C++17'den `std::apply` ve `if constexpr` veya C++17'den `std::is_same_v` gibi) kullanmasına olanak tanırken, eski standartlarla uyumluluğu korur.
   - **Örnek (`version.hpp` - `if constexpr` kullanımı):**
      ```cpp
      // Simplified snippet from public_dispatcher.hpp
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
                  // C++14 compatibility: use the Assign_Parameter_By_Type helper function
                  Assign_Parameter_By_Type(amx, &value, first); 
      #endif
          }

          Get_Public_Params_Recursive(amx, index + 1, rest...);
      }
      ```

### 4.3. `function_hook.hpp`: x86 Yakalama Motoru

Bu başlık, SDK'nın çalışması için temel olan fonksiyonların hooklanması (yakalanması) için düşük seviyeli mekanizmayı tanımlar. Kesinlikle x86 (32-bit) mimarisine bağlıdır.

- **`X86_Detour`**:
   - **Açıklama:** Bellekteki bir fonksiyonun başlangıcını bir atlama fonksiyonuna atlama talimatıyla üzerine yazma mantığını kapsayan bir sınıf.
   - **`JUMP_INSTRUCTION_SIZE = 5`**:
      - **Mekanizma:** x86'da, göreceli atlama (`JMP`) talimatı genellikle 5 bayttır: `0xE9` (yakın, göreceli JMP için opcode) ve ardından sonraki talimata göre hedef adresin ofsetini temsil eden 4 bayt.
      - **Talimat örneği:** `E9 XX XX XX XX` (burada `XX` ofsetin baytlarıdır).
   - **`Apply(void* target, void* detour)`**:
      - **Eylem:** Hook'u kurar. İlk olarak, `target` fonksiyonunun orijinal `JUMP_INSTRUCTION_SIZE` baytını saklar (`original_bytes_`). Daha sonra, `detour`'un `target`'a göre göreceli adresini hesaplar ve `target`'ın başlangıcını `JMP` talimatıyla üzerine yazar.
      - **Göreli adres hesaplama örneği:**
         ```cpp
         // (uintptr_t)detour_func_ - ((uintptr_t)target_func_ + JUMP_INSTRUCTION_SIZE)
         // Detour address - (Target address + JMP instruction size)
         ```
   - **`Revert()`**:
      - **Eylem:** Hook'u kaldırır, `target` fonksiyonundaki `original_bytes_`'i geri yükler.
   - **`Unprotect_Memory(void* address, size_t size)`**:
      - **Mekanizma:** Windows'ta `VirtualProtect`; Linux'ta `mprotect` kullanır. Bu sistem çağrıları, fonksiyonun bulunduğu bellek sayfasının izinlerini `EXECUTE_READWRITE` (Windows) veya `PROT_WRITE | PROT_EXEC` (Linux) olarak değiştirir, böylece kod çalışma zamanında değiştirilebilir.
      - **Örnek (`Unprotect_Memory`):**
         ```cpp
         // Simplified snippet from function_hook.hpp
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
   - **Açıklama:** `X86_Detour` için bir C++ `type-safe` sarıcı, fonksiyon işaretçisi türlerinin doğru olmasını sağlar.
   - `Install(void* target, void* detour)`: `X86_Detour::Apply` çağrısını kapsüller.
   - `Uninstall()`: `X86_Detour::Revert` çağrısını kapsüller.
   - **`Call_Original(Args... args)`**:
      - **Güvenlik Mekanizması (Özyineleme Koruması):** Bu fonksiyon, detour'un orijinal fonksiyonu çağırması gerektiğinde sonsuz döngüleri önlemek için kritiktir. **Hook'u geçici olarak kaldırır (`detour_.Revert()`)**, orijinal fonksiyonu çağırır (`Get_Original()(args...)`) ve ardından **hook'u yeniden kurar (`detour_.Reapply()`)**.
      - **`static thread_local int recursion_guard`**: En üst düzey orijinal çağrı tamamlandığında hook'un yalnızca yeniden kurulmasını sağlayan bir sayıcıdır, orijinal fonksiyonun güvenli özyinelemeli çağrılarına izin verir (örneğin, orijinal fonksiyon özyinelemeliyse). `thread_local`, `recursion_guard`'ın her iş parçacığı için yalıtılmasını sağlar, bu da çok iş parçacıklı ortamlarda önemlidir.
      - **Örnek (`Call_Original` ile Scope_Guard):**
         ```cpp
         // Simplified snippet from function_hook.hpp
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

Bu `singleton`, SDK'nın SA-MP'nin AMX sanal makinesi ile etkileşiminin ana merkezidir. `function_hook.hpp` tarafından sağlanan hook'ların sunucu tarafından açığa çıkarılan AMX API fonksiyonlarına kurulumunu koordine eder, yürütme akışını SDK mantığına yönlendirir.

- **`Activate()` / `Deactivate()`**:
   - **Açıklama:** Gerekli tüm hook'ları kurmak ve kaldırmak için genel yöntemler. Eklentinizin `OnLoad()` ve `OnUnload()` fonksiyonlarında çağrılırlar.
   - **Mekanizma:** `Core::Instance().Get_AMX_Export(...)` kullanarak AMX fonksiyon işaretçilerini (`amx_Register`, `amx_Exec` vb.) alır ve detour'ları kurar.
- **`int SAMP_SDK_AMX_API Amx_Register_Detour(...)`**:
   - **Hooklanmış Fonksiyon:** `amx_Register`
   - **Amaç:** *Tüm* native'lerin (SA-MP, diğer eklentiler veya gamemode tarafından) kaydını yakalar.
   - **Eylem:** Kaydedilen her native için, `Interceptor_Manager` onu dahili bir önbelleğe ekler (`Cache_Data::native_cache`).
   - **Etki:** Bu önbellek, `Pawn_Native` performansı için temeldir, AMX'te pahalı bir arama yerine native işaretçisinin son derece hızlı bir şekilde aranmasına izin verir.
   - **`Plugin_Native_Hook` için ek fonksiyon:** Bu detour *ayrıca* native'ler kaydedilmeden önce native listesini değiştirmekten sorumludur. Bir native'in ilişkilendirilmiş bir `Plugin_Native_Hook`'u varsa, kayıt listesindeki fonksiyon işaretçisi `Native_Hook_Manager` tarafından oluşturulan trampoline ile değiştirilir. Bu, hook'unuzun ilk çağrılmasını sağlar.
- **`int SAMP_SDK_AMX_API Amx_Exec_Detour(...)`**:
   - **Hooklanmış Fonksiyon:** `amx_Exec`
   - **Amaç:** **Bu en kritik hook'tur.** Pawn `public`'lerinin çağrılması dahil, AMX'teki *herhangi bir* kod yürütmesini yakalar.
   - **`Plugin_Public` Yakalama Mekanizması:**
      1. Bir `public` (veya `AMX_EXEC_MAIN`) için `amx_Exec` çağrıldığında, `Amx_Exec_Detour` yürütülür.
      2. `public` adını alır (daha önce `Amx_Find_Public_Detour` tarafından doldurulan `tl_public_name` kullanarak).
      3. Bu ad için kayıtlı C++ işleyicileri olup olmadığını kontrol etmek için `Public_Dispatcher::Instance().Dispatch()` sorgular.
      4. İşleyici varsa, bunları yürütür. `Public_Dispatcher`, AMX'teki parametrelerin C++ türlerine `marshalling`'ini halleder.
      5. `Public_Dispatcher`'ın dönüş değerine (`PLUGIN_PUBLIC_STOP`/`PLUGIN_PUBLIC_CONTINUE`) dayanarak, orijinal `amx_Exec`'i mi (`Get_Amx_Exec_Hook().Call_Original(...)`) çağıracağına yoksa Pawn `public` yürütmesini sonlandıracağına mı karar verir.
      6. **Yığın Manipülasyonu:** Pawn `public` yürütmesi durdurulursa (`PLUGIN_PUBLIC_STOP`), `Amx_Exec_Detour` AMX yığınını düzeltir (`amx->stk += amx->paramcount * sizeof(cell); amx->paramcount = 0;`) tutarsızlıkları önlemek için.
   - **`Plugin_Native_Hook` Aktivasyonu (AMX Yaması):**
      - Bir `AMX*` ilk kez yürütüldüğünde, bu detour AMX'in zaten "yama yapılıp yapılmadığını" kontrol eder (`!manager.Is_Amx_Patched(amx)`).
      - Yapılmadıysa, **o belirli AMX örneğinin bellekteki** native tablosunu dolaşır.
      - `Native_Hook_Manager`'da kayıtlı bir `Plugin_Native_Hook`'a sahip her native için, tablodaki native adresini `Native_Hook_Manager` tarafından oluşturulan bir trampoline ile değiştirir. Orijinal adres (veya önceki hook'un adresi) `Native_Hook` nesnesinde saklanır.
      - AMX daha sonra gereksiz yeniden işlemeyi önlemek için "yama yapılmış" olarak işaretlenir.
   - **Örnek (`Amx_Exec_Detour` - `Plugin_Native_Hook` detaylarıyla):**
      ```cpp
      // Simplified snippet from interceptor_manager.hpp
      inline int SAMP_SDK_AMX_API Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
          auto& manager = Interceptor_Manager::Instance();

          std::unique_ptr<std::string> public_name_ptr;

          // Plugin_Public interception logic (as described above)
          // ...

          int exec_result = Get_Amx_Exec_Hook().Call_Original(amx, retval, index);

          // Patching Logic for Plugin_Native_Hook
          if (SAMP_SDK_UNLIKELY(!manager.Is_Amx_Patched(amx))) {
              auto& hook_manager = Native_Hook_Manager::Instance();
              auto& hooks_to_apply = hook_manager.Get_All_Hooks();

              if (!hooks_to_apply.empty()) {
                  AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
                  AMX_FUNCSTUBNT* natives = reinterpret_cast<AMX_FUNCSTUBNT*>(reinterpret_cast<unsigned char*>(hdr) + hdr->natives);

                  int num_natives;

                  amx::Num_Natives(amx, &num_natives);

                  for (auto& hook_to_apply : hooks_to_apply) { // Iterates through all registered Plugin_Native_Hooks
                      uint32_t hook_hash = hook_to_apply.Get_Hash();

                      for (int i = 0; i < num_natives; ++i) { // Iterates through AMX natives
                          const char* native_name = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(hdr) + natives[i].nameofs);

                          if (FNV1a_Hash(native_name) == hook_hash) { // If the AMX native name matches a hook
                              AMX_NATIVE current_func = reinterpret_cast<AMX_NATIVE>(natives[i].address);

                              hook_to_apply.Set_Next_In_Chain(current_func); // Saves the pointer to the original/previous function

                              AMX_NATIVE trampoline = hook_manager.Get_Trampoline(hook_hash); // Gets the trampoline for this hook

                              if (trampoline)
                                  natives[i].address = reinterpret_cast<ucell>(trampoline); // Replaces in the AMX table
                              
                              break;
                          }
                      }
                  }
              }
              
              manager.On_Amx_Patched(amx); // Marks AMX as patched
          }
          
          return exec_result;
      }
      ```
- **`int SAMP_SDK_AMX_API Amx_Find_Public_Detour(...)`**:
   - **Hooklanmış Fonksiyon:** `amx_FindPublic`
   - **Amaç:** `public`'lerin adlarına göre aranmasını yakalar.
   - **"Hayalet Publicler" Mekanizması:** Orijinal `amx_FindPublic` Pawn'da bir `public` bulamazsa, ancak `Public_Dispatcher`'ın o ad için kayıtlı bir C++ işleyicisi varsa, bu hook `AMX_ERR_NONE` ve özel bir `index` (`PLUGIN_EXEC_GHOST_PUBLIC`) döndürür. Bu, SA-MP API'sinin `public`'in var olduğunu "düşünmesini" sağlar ve sonraki `amx_Exec` çağrısının (bu özel dizin için) `Amx_Exec_Detour` tarafından yakalanmasına izin verir, bu da C++ işleyiciye yönlendirir.
   - **`static thread_local std::unique_ptr<std::string> tl_public_name`**: Bir "hayalet public" tespit edildiğinde `public` adını `Amx_Exec_Detour`'a iletmek için kullanılır, çünkü `amx_Exec` yalnızca dizini alır, adı değil.
- **`int SAMP_SDK_AMX_API Amx_Init_Detour(...)` / `Amx_Cleanup_Detour(...)`**:
   - **Hooklanmış Fonksiyonlar:** `amx_Init` / `amx_Cleanup`
   - **Amaç:** Aktif `AMX*` örnekleri listesini yönetmek.
   - **Eylem:** `Amx_Init_Detour`, `Amx_Manager::Instance().Add_Amx()`'i çağırır ve `Amx_Cleanup_Detour`, `Amx_Manager::Instance().Remove_Amx()`'i çağırır.

### 4.5. `amx_manager.hpp`: `AMX*` Örneklerini Yönetme

Bu `singleton`, sunucuda şu anda yüklü olan tüm AMX sanal makinelerinin dinamik bir kaydını tutar. "Tüm scriptlerle" etkileşime girmesi veya belirli bir scripti bulması gereken fonksiyonlar için temeldir.

- **`std::vector<AMX*> loaded_amx_`**:
   - **Açıklama:** Başlatılmış tüm `AMX*` örneklerinin (gamemode ve filterscriptler) bir işaretçi listesi.
   - **Yönetim:** `Amx_Init_Detour` hook'ları tarafından doldurulur ve `Amx_Cleanup_Detour` hook'ları tarafından boşaltılır.
- **`std::shared_mutex mtx_` (C++17+) / `std::mutex mtx_` (C++14)**:
   - **Amaç:** Çoklu iş parçacıklı ortamlarda eşzamanlı erişime karşı `loaded_amx_`'i korur (SA-MP çoğunlukla tek iş parçacıklı olsa da, bu iyi bir güvenlik uygulamasıdır). `std::shared_mutex` aynı anda birden çok okuyucuya, ancak yalnızca bir yazıcıya izin verir.
- **`std::atomic<uint32_t> generation_`**:
   - **Amaç:** Her AMX eklendiğinde veya kaldırıldığında artan bir sayıcı.
   - **Kullanım:** `callbacks.hpp` içindeki `Caller_Cache` tarafından AMX listesi değiştiğinde algılamak, `public` arama önbelleklerini geçersiz kılmak ve `Pawn_Public` çağrılarının her zaman güncel bilgilerle çalışmasını sağlamak için kullanılır. Bu, değişmeyen bir durumda tekrar eden aramaları önleyerek performansı optimize eder.
- **`AMX* Find_Public(const char* name, int& index)`**:
   - **Açıklama:** Belirtilen adda `public`'i bulmak için `loaded_amx_`'i (en yeniden en eskiye, bu genellikle en alakalı gamemode veya filterscript'i ilk sıraya koyar) dolaşır.
   - **Mekanizma:** Her `AMX*` örneği için `amx::Find_Public` kullanır.
   - **Etki:** `Pawn_Public` için temeldir.

### 4.6. `public_dispatcher.hpp`: `Plugin_Public` Callbacks Yönlendiricisi

Bu `singleton`, Pawn `public` adlarını C++ `Plugin_Public` fonksiyonlarınızla eşleştiren bileşendir.

- **`std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_`**:
   - **Anahtar:** `public` adının FNV1a hash'i (ör: `FNV1a_Hash_Const("OnPlayerConnect")`).
   - **Değer:** `std::function<cell(AMX*)>` bir `std::vector`, burada her `std::function` o `public` için kayıtlı bir C++ işleyicisidir.
   - **Mekanizma:** `std::vector`, aynı geri çağrı için birden çok `Plugin_Public`'in kaydedilmesine izin verir (ör: birden çok eklenti `OnPlayerCommandText`'i yakalamak istiyor). İşleyiciler ters kayıt sırasına göre yürütülür.
- **`Public_Register`**:
   - **Mekanizma:** Bu, `PLUGIN_PUBLIC_REGISTRATION` makrosunun global statik bir örnek oluşturduğu bir şablon sınıfıdır. Statik yapılandırıcıda (`static bool registered = [...]`), `Plugin_Public` işleyicinizi `Public_Dispatcher`'a kaydeder. Bu, bir "derleme/başlatma zamanı statik kaydı" desenidir.
   - **Örnek (`public_dispatcher.hpp`):**
      ```cpp
      #define PLUGIN_PUBLIC_REGISTRATION(name) \
          constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
          Samp_SDK::Detail::Public_Register<decltype(&name), &name, hash_##name> register_##name;
      ```

- **`Public_Traits` ve `Wrapper()`**:
   - **Mekanizma:** `Public_Traits`, metaprogramlama kullanarak `static cell Wrapper(AMX* amx)` fonksiyonunu oluşturan bir özellik şablonudur.
   - **Amaç:** Bu `Wrapper`, `Public_Dispatcher`'ın gerçekten depoladığı ve çağırdığı `Amx_Handler_Func`'dır. Aşağıdakilerden sorumludur:
      1. AMX yığınından parametreleri çıkarmak için `Public_Param_Reader::Get_Public_Params(amx, args...)` çağrısı.
      2. Parametreler zaten doğru C++ türlerine dönüştürülmüş olarak gerçek C++ `Plugin_Public` fonksiyonunuzu (`func_ptr`) çağırmak.
- **`Public_Param_Reader::Get_Public_Params(...)`**:
   - **Açıklama:** AMX yığınındaki değerleri okuyan ve bunları `Plugin_Public` bildiriminde belirtilen C++ türlerine dönüştüren bir dizi özyinelemeli şablon fonksiyonu.
   - **Mekanizma:** Yığındaki `cell`'lere erişmek için `Get_Stack_Cell()` kullanır. Doğru dönüşümü uygulamak için `if constexpr` (C++17+) veya `std::is_same<T>::value` (C++14) kullanır (float için `amx::AMX_CTOF`, string için `Samp_SDK::Get_String`, int için doğrudan cast).

### 4.7. `native.hpp`: Eklenti Nativelerini Yönetme ve Çağırma

Bu başlık, eklentinizin Pawn'a açtığı C++ native'lerinin oluşturulmasına ve yönetimine adanmıştır.

- **`Native_List_Holder`**:
   - **Açıklama:** Eklentinizde bildirilen tüm `Plugin_Native`'leri (SAMP_SDK_WANT_AMX_EVENTS kullanan tüm `.cpp` dosyalarından) depolayan global bir `singleton`.
   - **`std::vector<Native> natives_`**: `Native` nesnelerini (native adını ve C++ fonksiyon işaretçisini `Native_Handler` depolayan) içerir.
   - **`std::unordered_map<uint32_t, Native_Handler> plugin_natives_`**: Dahili `Plugin_Native`'leri hızlı aramak için hash ile optimize edilmiş bir harita (`Plugin_Call` tarafından kullanılır).
- **`Native_Register`**:
   - **Mekanizma:** `Public_Register` gibi, bu da `Plugin_Native` makrosunun global statik bir örnek oluşturduğu bir şablon sınıfıdır. Yapılandırıcısında, native'i `Native_List_Holder`'a ekler.
   - **Etki:** Birden çok `.cpp` dosyasında `Plugin_Native`'leri manuel kaydetme endişesi olmadan bildirmenizi sağlar. Hepsi otomatik olarak toplanacaktır.
- **`Native_Registry`**:
   - **Açıklama:** `OnAmxLoad`'da, `Native_List_Holder`'dan `Native`'lerin tam listesini alan ve bunları bir `AMX_NATIVE_INFO` dizisi olarak biçimlendiren yardımcı bir sınıf.
   - **Mekanizma:** `amx::Register(amx, amx_natives_info_.data(), -1)` çağrısı yaparak tüm native'lerinizi yeni yüklenen AMX örneğine kaydeder.
- **`Plugin_Call_Impl(...)`**:
   - **Açıklama:** `Plugin_Call` makrosunun altında yatan uygulaması.
   - **Mekanizma:** Doğrudan C++ fonksiyon işaretçisini almak için `Native_List_Holder::Instance().Find_Plugin_Native(native_hash)` kullanır.
   - **Ortam:** Native'i, `Pawn_Native`'in nasıl çalıştığına benzer şekilde, geçici yığını ve yığını yönetmek için bir `Amx_Sandbox` (yalıtılmış) ortamında yürütür.

### 4.8. `native_hook_manager.hpp`: Nativelerin Hook Motoru

Bu, aynı native için birden çok eklentinin hook zincirini yönetmek üzere tasarlanmış sağlam bir native hook sistemi.

- **`Native_Hook`**:
   - **Açıklama:** Tek bir native hook'unu temsil eden bir sınıf. Native adının hash'ini, kullanıcı tarafından sağlanan C++ işleyici fonksiyonunu (`user_handler_`) ve bir `std::atomic<AMX_NATIVE> next_in_chain_`'i depolar.
   - **`user_handler_`**: Sizin C++ `Plugin_Native_Hook` fonksiyonunuz.
   - **`next_in_chain_`**: Orijinal native'e veya daha düşük önceliğe sahip bir eklentinin hook'una işaretçi. Okuma/yazmada iş parçacığı güvenliğini sağlamak için bir `std::atomic`'tir.
   - **`Dispatch(AMX* amx, cell* params)`**: Kullanıcı işleyicinizi (`user_handler_`) yürütmek için trampoline tarafından çağrılır.
   - **`Call_Original(AMX* amx, cell* params)`**: Hook'unuzun orijinal işlevselliği veya zincirdeki bir sonraki hook'u çağırmasına izin veren kritik yöntem, `next_in_chain_`'i çağırır.
- **`Trampoline_Allocator`**:
   - **Açıklama:** Yürütülebilir bellek bloklarını tahsis etmekten ve bu bloklarda "trampoline" assembly kodunu oluşturmaktan sorumlu bir sınıf.
   - **`Generate_Trampoline_Code(unsigned char* memory, int hook_id)`**: 10 bayt assembly kodu yazar:
      1. `B8 XX XX XX XX`: `MOV EAX, hook_id` (benzersiz hook ID'sini EAX kaydedicisine yerleştirir).
      2. `E9 XX XX XX XX`: `JMP relative_address_to_Dispatch_Wrapper_Asm` (SDK'nın genel gönderme fonksiyonuna göreli adrese atlar).
   - **`Allocation_Size = 4096`**: Verimlilik ve önbellek hizalaması için sayfa boyutunda bellek tahsis eder.
   - **Bellek İzinleri:** Oluşturulan kodun yürütülebilir olmasını sağlamak için `EXECUTE_READWRITE` izinleriyle `VirtualAlloc` (Windows) veya `mmap` (Linux) kullanır.
- **`Dispatch_Wrapper_Asm()`**:
   - **Açıklama:** Tüm trampolinlerin hedefi olarak hizmet veren küçük bir assembly fonksiyonu (`__declspec(naked)` veya `asm volatile` ile tanımlanır).
   - **Eylem:** Kaydedicileri kaydeder, `EAX`'ı (`hook_id`'yi içeren) yığına taşır ve C++'daki `Dispatch_Hook` fonksiyonunu çağırır. `Dispatch_Hook`'tan döndükten sonra kaydedicileri geri yükler ve döner.
- **`cell SAMP_SDK_CDECL Dispatch_Hook(int hook_id, AMX* amx, cell* params)`**:
   - **Açıklama:** `Dispatch_Wrapper_Asm` tarafından çağrılan genel C++ fonksiyonu.
   - **Eylem:** `hook_id`'yi kullanarak `Native_Hook_Manager`'daki ilgili `Native_Hook`'u bulur ve `Dispatch()` yöntemini çağırır, bu da sırasıyla kullanıcının `Plugin_Native_Hook` işleyicisini çağırır.
- **`Native_Hook_Manager`**:
   - **Açıklama:** Tüm kayıtlı `Native_Hook`'ları ve trampolinlerini yöneten merkezi `singleton`.
   - **`std::list<Native_Hook> hooks_`**: Hook listesini sırayla depolar.
   - **`std::unordered_map<uint32_t, Trampoline_Func> hash_to_trampoline_`**: Native adının hash'ini oluşturulan trampoline'in işaretçisiyle eşleştirir.
   - **`std::vector<uint32_t> hook_id_to_hash_`**: Hook'un tam sayı ID'sini (trampoline'de kullanılır) native adının hash'ine geri eşleştirir.
   - **`Get_Trampoline(uint32_t hash)`**: Belirli bir native hash'i için bir trampoline işaretçisi döndürür (veya oluşturur ve tahsis eder).
- **`PLUGIN_NATIVE_HOOK_REGISTRATION`**:
   - **Mekanizma:** Her `Plugin_Native_Hook` için statik global bir sınıf (`Native_Hook_Register_##name`) oluşturan bir makro. Bu sınıfın statik yapılandırıcısında, kullanıcı işleyicisini `Native_Hook_Manager`'a kaydeder.

### 4.9. `callbacks.hpp` & `amx_memory.hpp`: C++ -> Pawn Çağrıları ve RAII

Bu başlıklar, C++'dan Pawn fonksiyonlarını çağırmak (`Pawn_*` makroları) için omurgayı oluşturur ve bellek güvenliğini sağlar.

- **`Amx_Sandbox`**:
   - **Açıklama:** `Pawn_Native` ve `Plugin_Call` çağrıları için minimalist ve yalıtılmış bir `AMX` ortamını simüle eden `thread_local` bir yapı.
   - **Mekanizma:** `AMX` struct'ına, `AMX_HEADER`'a ve bir scriptin belleğini simüle etmek için `std::vector<unsigned char> heap`'e sahiptir. Bu, gerçek çalışan Pawn scriptlerinin durumuna müdahale etmeden `amx::Push`, `amx::Allot` vb. çağrılarının yapılmasına izin verir.
   - **`thread_local`:** SDK'nın çok iş parçacıklı bir bağlamda kullanılması durumunda (ör: Pawn dışı işlemler için gelecekteki bir iş parçacığı havuzu), her iş parçacığının kendi `Amx_Sandbox`'ına sahip olmasını sağlar, yarış koşullarını önler.
   - **Örnek (`Amx_Sandbox`):**
      ```cpp
      // Simplified snippet from callbacks.hpp
      struct Amx_Sandbox {
          AMX amx;
          AMX_HEADER amx_header;
          std::vector<unsigned char> heap; // Simulated memory for stack/heap

          Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
              Reset(); // Initializes the AMX and header
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
   - **Açıklama:** Her C++ parametresinin AMX tarafından beklenen `cell` formatına, ve çıktı parametreleri için tersine `marshalling`'ini yöneten bir dizi aşırı yüklenmiş şablon fonksiyonu.
   - **Girdi İşleme:**
       - `int`, `float`, `bool` için: Doğrudan `cell`'e dönüştürür.
       - `const char*`, `std::string` için: `Amx_Sandbox`'ın yığınında bellek ayırır (veya `Pawn_Public` için gerçek AMX'te), string'i kopyalar ve AMX adresini yığına iter.
   - **Çıktı İşleme (`is_output_arg`):**
       - **Mekanizma:** Bir argüman const olmayan bir lvalue referansı olduğunda (`is_output_arg` özelliği tarafından algılanır), `Parameter_Processor` değeri itmez, bunun yerine yığında geçici olarak ayrılan bir `cell` için bir *AMX adresi* iter.
       - **`std::vector<std::function<void()>> post_call_updaters`**: Pawn native çağrısından sonra, bir lambda listesi (`post_call_updaters`) yürütülür. Her lambda, AMX'te ayrılan `cell`'in nihai değerini okumaktan ve bunu orijinal C++ değişkenine geri atamaktan sorumludur (ör: `x = amx::AMX_CTOF(*phys_addr)`).
- **`is_output_arg`**:
   - **Mekanizma:** Derleme zamanında bir C++ parametre türünün değiştirilebilir bir referans olup olmadığını (ör: `int&`, `float&`, `std::string&`) değerlendiren bir `std::integral_constant` (tür özelliği). Bu, `Parameter_Processor`'ın girdi ve çıktı parametrelerini ayırt etmesini sağlar.
   - **Örnek (`is_output_arg`):**
      ```cpp
      // Simplified snippet from callbacks.hpp
      template <typename T>
      struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
      ```
- **`Amx_Scoped_Memory`**:
   - **Açıklama:** AMX'teki bellek tahsisini ve serbest bırakılmasını kapsayan bir RAII (`Resource Acquisition Is Initialization`) sınıfı.
   - **Mekanizma:** Yapılandırıcıda, bir `amx_addr` ve bir `phys_addr` almak için `amx::Allot` çağrısı yapar. Yıkıcıda, bu belleği serbest bırakmak için `amx::Release` çağrısı yapar.
   - **Etki:** **AMX yığınında bellek sızıntılarını önlemek için kritiktir.** Stringler veya çıktı parametreleri için kullanılan geçici belleğin, istisnalar veya erken dönüşler meydana gelse bile her zaman serbest bırakılmasını sağlar.

### 4.10. `amx_api.hpp` & `amx_helpers.hpp` & `amx_defs.h`: AMX'e Soyutlanmış Erişim

Bu başlıklar, temel tanımları ve Pawn ile etkileşim kurmak için yüksek seviyeli araçları sağlar.

- **`amx_defs.h`**:
   - **İçerik:** AMX yapılarının (`AMX`, `AMX_HEADER`), türlerinin (`cell`, `ucell`) ve hata enumlarının (`AmxError`) ham tanımlarını içerir. Ayrıca `AMX_NATIVE` ve `AMX_CALLBACK`'ı tanımlar.
   - **`SAMP_SDK_PACKED`**: Birlikte çalışabilirlik için temel olan AMX yapılarının doğru bellek düzenine sahip olmasını sağlamak için paketleme özniteliklerini (`#pragma pack(push, 1)` / `__attribute__((packed))`) kullanır.
- **`Samp_SDK::amx::Call<Func, Index, ...>`**:
   - **Açıklama:** Sunucu tarafından açığa çıkarılan AMX API fonksiyonlarını çağırmak için ana şablon fonksiyonu.
   - **Mekanizma:** `Core::Instance().Get_AMX_Export(Index)` aracılığıyla fonksiyon işaretçisini alır ve çağırır. Fonksiyon işaretçisi mevcut değilse hata işlemeyi merkezileştirir.
   - **Etki:** Düşük seviyeli çağrıları (`Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec)`) idiomatik ve tür güvenli C++ çağrılarına (`amx::Exec`) dönüştürür.
- **`Samp_SDK::amx::AMX_CTOF(cell c)` / `AMX_FTOC(float f)`**:
   - **Açıklama:** `cell` değerlerini `float`'a ve tersine dönüştürmek için temel fonksiyonlar, belleğin bit bazında yeniden yorumlanmasını gerçekleştirir.
   - **`static_assert`:** Derleme zamanında `sizeof(cell) == sizeof(float)` olmasını sağlamak için `static_assert` içerir, farklı tür boyutlarına sahip platformlarda hataları önler.
- **`Samp_SDK::Get_String(AMX* amx, cell amx_addr)`**:
   - **Açıklama:** Bir AMX string adresini `std::string`'e dönüştürmek için yardımcı.
   - **Mekanizma:** İlk olarak, `amx::Get_Addr` kullanarak stringin AMX'teki fiziksel adresini (`cell* phys_addr`) alır. Daha sonra, uzunluğu belirlemek için `amx::STR_Len` ve baytları bir `std::string`'e kopyalamak için `amx::Get_String` kullanır.
- **`std::string Samp_SDK::Format(const char* format, ...)`**:
   - **Açıklama:** SDK için temel string biçimlendirme fonksiyonu (`printf` benzeri).
   - **Mekanizma:** İki geçişte `vsnprintf` kullanır: önce gerekli string boyutunu belirlemek için, sonra dinamik olarak tahsis edilen `std::string`'e stringi biçimlendirmek için. Bu, arabellek taşmalarını önler.

## 5. Derleme ve Dağıtım

### Mimari ve Platform Gereksinimleri

- Eklentiniz **x86 (32-bit)** mimarisi için derlenmelidir.
- Desteklenen Platformlar: Windows (.dll) ve Linux (.so).

### Derleme Komut Örnekleri

#### **MSVC (Visual Studio)**

1. Yeni bir "Dynamic-Link Library (DLL)" projesi oluşturun.
2. Proje ayarlarında "Çözüm Platformu"nu **x86** olarak ayarlayın.
3. C++ Dil Standardının en az C++14 olduğundan emin olun.

#### **GCC / Clang (Linux)**

```bash
# For a plugin named 'my_plugin.so' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: 32-bit için derler.
- `-shared`: Paylaşılan bir kütüphane (`.so`) oluşturur.
- `-std=c++17`: C++ standardını C++17 olarak ayarlar (`c++14` veya `c++20` olabilir).
- `-O2`: Optimizasyon seviyesi 2.
- `-fPIC`: Paylaşılan kütüphaneler için gerekli olan konumdan bağımsız kod üretir.
- `-Wall -Wextra`: Hataları yakalamaya yardımcı olmak için ek uyarıları etkinleştirir.
- `-Wl,--no-undefined`: Tanımsız semboller varsa kütüphane oluşturmayı engeller.

#### **GCC / Clang (Windows'ta MinGW)**

```bash
# For a plugin named 'my_plugin.dll' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: C++ standart kütüphanesini statik olarak bağlar. Eklentinizin kullanıcının sisteminde bulunmayabilecek derleyiciye özgü çalışma zamanı DLL'lerine bağımlı olmasını önlemek için önemlidir.
- `-static-libgcc`: GCC kütüphanesini statik olarak bağlar.

### Dağıtım İçin Dikkate Alınması Gerekenler

- **Dosya Adı:** Eklentiniz `.dll` (Windows) veya `.so` (Linux) uzantısına sahip olmalıdır. Örn: `my_plugin.dll`.
- **Konum:** Derlenmiş dosyayı SA-MP sunucunuzun `plugins/` klasörüne yerleştirin.
- **server.cfg:** Eklentinizin adını (Windows ise uzantısız) `server.cfg` dosyasındaki `plugins` satırına ekleyin.
   ```
   plugins my_plugin (if Linux, my_plugin.so)
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