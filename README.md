# SSL10n

for game BeatSaber. This is for modder. For other part, refer to [this](https://github.com/frto027/ssl10n.csv/tree/master).

a **backend** library for Simple Stupid Localization

it's not thread safe, don't call this outside the unity thread.

All mods shares the same key pool, so prefix your key with something like your mod id.

# Usage

add this library to your `qpm.json` and rerun `qpm restore`

```
    {
      "id": "sslocalization",
      "versionRange": "0.6.*",
      "additionalData": {}
    }
```

Usage. See [SSL10n.hpp](/shared/SSL10n.hpp) for more functions.

```cpp
#include "SSL10n.hpp"
#include "SSL10n/GameKeys.hpp"

void late_load(){

    //////////////////////////////////////////////////////////////////
    // ------------------ add your key-value database --------------//
    //////////////////////////////////////////////////////////////////

    // You need some way to tell the library about your key-values for each languages
    // If you want parse a csv file, use `SSL10n::Database::PolyhglotFormat`
    // Compat with polyglotunity's format. https://github.com/agens-no/PolyglotUnity
    // Clone the [master sheet] of the following link and export csv file.
    // https://docs.google.com/spreadsheets/d/17f0dQawb-s_Fd7DHgmVvJoEGDMH_yoSd8EYigrb0zmM/
    SSL10n::Database::PolyglotFormat::AddCSVFile("/sdcard/your_mod_asset.csv");
    SSL10n::Database::PolyglotFormat::AddCSVContent(text, sizeof(text));
    // If you want add some key-value directly
    SSL10n::Database::AddKeyValue("MYMOD_KEY", "en_value"); // for english
    SSL10n::Database::AddKeyValue("MYMOD_KEY", "sc_value", SSL10n::L_Simplified_Chinese);
    SSL10n::Database::Helper()
        .v("MY_FORMAT_KEY", "answer is {}")
        .v("MYMOD_key1","en_value1")
        .v("MYMOD_key2","en_value2")
        .v("MYMOD_key3","en_value3");
    SSL10n::Database::Helper(SSL10n::L_Simplified_Chinese)
        .v("MYMOD_key1","sc_value1")
        .v("MYMOD_key2","sc_value2")
        .v("MYMOD_key3","sc_value3");

    ///////////////////////////////////////////////////////////////
    // ------------------- use key-values -----------------------//
    ///////////////////////////////////////////////////////////////

    // To get the result of current language, just use SSL10n::Get
    std::string result = SSL10n::Get("MYMOD_key1");
    // See https://fmt.dev/ for more format details
    std::string result2 = SSL10n::FormatKey("MY_FORMAT_KEY", 42);
    // You can use a default fmt value to provide an IDE check and compile-time error detect
    std::string result3 = SSL10n::FormatKeyWithDefault("MY_FORMAT_KEY", "the awnswer is {}", 42);
    /*
        The mod also load csv files from the game's polyglot system, so you can access the game's i18n
        texts. To get the result of some game keys, use the game keys directly or use SSL10n::GameKeys.
    */
    std::string result_game_key = SSL10n::Get(SSL10n::GameKeys::LANGUAGE_THIS_EN);


    //////////////////////////////////////////////////////////////
    //------------------ handle language change ----------------//
    //////////////////////////////////////////////////////////////

    /* 
        Not required.
        The game re-creates most of UIs automatically when switch language.
    */
    SSL10n::OnLanguageChangeCallback.addCallback([](){
        std::string result = SSL10n::Get("MYMOD_key1");
        some_log(result);
    });
}
```

See [csv.md](/docs/csv.md).

## Qmod build

- build `qpm s build`
- debug `qpm s copy`
- release `qpm qmod zip`. no release, this is a library
- local install, for develop `qpm install`

## Bump Guide

- update qpm.json, qpm.shared.json
- update GameHooks.cpp if it broken (unlikely)
- update GameKeys.hpp with `scripts/update_source.py`. after this, don't forget add a game version in the file manually.

## Time Machine / Build for old games

```sh
qpm s time_machine 1.40.6
```

The `time_machine` script generate old version qpm manifests. Do NOT git commit the result of `time_machine` into master branch. Python required.

The mod focus on the latest moddable game version, but will make it avaliable for old/future game versions when needed.

Mod Version | Game Version
:---:|:---:
`0.1.*`|`1.35.0`
`0.2.*`|`1.37.0`
`0.3.*`|`1.40.4`
`0.4.*`|`1.40.6`
`0.5.*`|`1.40.7`
`0.6.*`|`1.40.8`
`0.7.*`|`1.41.0`
`0.8.*`|`1.42.0`

## Tests

There's a test folder. In there you can compile an executable that uses the lib source without android ndk.

## About the Language Controller Mod

This library/mod doesn't have UI, what it does is just follows game language.

Another language controller mod can be made to control the mod language, or setup some preference like language fallback behaviors.

Designed to be work with [Loqolizer](https://github.com/BeatSaberCN/Loqolizer/tree/master).

Naturally works with [PolyglotInject](https://github.com/qe201020335/PolyglotInject).

See namespace `SSL10n::LanguageController` in `SSL10n.hpp`

## Credits

* [zoller27osu](https://github.com/zoller27osu), [Sc2ad](https://github.com/Sc2ad) and [jakibaki](https://github.com/jakibaki) - [beatsaber-hook](https://github.com/sc2ad/beatsaber-hook)
* [raftario](https://github.com/raftario)
* [Lauriethefish](https://github.com/Lauriethefish), [danrouse](https://github.com/danrouse) and [Bobby Shmurner](https://github.com/BobbyShmurner) for [this template](https://github.com/Lauriethefish/quest-mod-template)
