# SSL10n

WIP

for game BeatSaber.

a library for Simple Stupid Localization

it's not thread safe, only works in main thread.

All mods shares the same key pool, so prefix your key with something like your mod id.

# Usage

WIP, not avaliable

add this library to your `qpm.json` and rerun `qpm restore`

```
    {
      "id": "sslocalization",
      "versionRange": "^0.1.0",
      "additionalData": {}
    }
```

```cpp
#include "SSL10n.hpp"
#include "SSL10n/GameKeys.hpp"

void late_load(){
    // You need some way to tell the library about your key-values for each languages
    /*
        if you want parse a csv file
    */
    SSL10n::Database::PolyglotFormat::AddCSVFile("/sdcard/your_mod_asset.csv");
    SSL10n::Database::PolyglotFormat::AddCSVContent(text, sizeof(text));
    /*
        if you want add some key-value directly
    */
    SSL10n::Database::AddKeyValue("MYMOD_KEY", "en_value"); // for english
    SSL10n::Database::AddKeyValue("MYMOD_KEY", "sc_value", SSL10n::L_Simplified_Chinese);
    SSL10n::Database::Helper()
        .p("MY_FORMAT_KEY", "answer is {}")
        .p("MYMOD_key1","en_value1")
        .p("MYMOD_key2","en_value2")
        .p("MYMOD_key3","en_value3");
    SSL10n::Database::Helper(SSL10n::L_Simplified_Chinese)
        .p("MYMOD_key1","sc_value1")
        .p("MYMOD_key2","sc_value2")
        .p("MYMOD_key3","sc_value3");

    /* 
        to get the result of current language, just use SSL10n::Get
    */
    std::string result = SSL10n::Get("MYMOD_key1");
    // see https://fmt.dev/ for more format details
    std::string result2 = SSL10n::FormatKey("MY_FORMAT_KEY", 42);
    // you can use a default fmt value to provide an IDE check and compile-time error detect
    std::string result3 = SSL10n::FormatKeyWithDefault("MY_FORMAT_KEY", "the awnswer is {}", 42);

    /*
        to get the result of some game keys, use SSL10n::GameKeys.
        this is for compile time check
    */
    std::string result_game_key = SSL10n::Get(SSL10n::GameKeys::LANGUAGE_THIS_EN);

    /* 
        You can update your UI when language changes.
        This is not required. The localize mod will tell players restart the game
        if you have dirty key didn't accessed after lang change.
    */
    AddLangChangeCallback([](){
        std::string result = SSL10n::Get("MYMOD_key1");
        some_log(result);
    });
}
```

## Qmod build

- build `qpm s build`
- debug `qpm s copy`
- release `qpm qmod zip`. no release, this is a library
- local install, for develop `qpm install`
## Bump Guide

- update qpm.json, qpm.shared.json
- update GameHooks.cpp if it broken (unlikely)
- update GameKeys.hpp with `scripts/update_source.py`

## Credits

* [zoller27osu](https://github.com/zoller27osu), [Sc2ad](https://github.com/Sc2ad) and [jakibaki](https://github.com/jakibaki) - [beatsaber-hook](https://github.com/sc2ad/beatsaber-hook)
* [raftario](https://github.com/raftario)
* [Lauriethefish](https://github.com/Lauriethefish), [danrouse](https://github.com/danrouse) and [Bobby Shmurner](https://github.com/BobbyShmurner) for [this template](https://github.com/Lauriethefish/quest-mod-template)
