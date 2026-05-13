# SSL10n

WIP

a library for Simple Stupid Localization


it's not thread safe, only works in main thread.

# Usage

```cpp
#include "SSL10n.hpp"

void late_load(){
    // You need some way to tell the library about your key-values for each languages
    /*
        if you want parse a csv file
    */
    SSL10n::Database::PolyglotFormat::AddCSVFile("/sdcard/your_mod_asset.csv");
    SSL10n::Database::PolyglotFormat::AddCSVContent(text, sizeof(text));
    /*
        if you want add some key-value in your program
    */
    SSL10n::Database::AddKeyValue("MYMOD_KEY", "en_value"); // for english
    SSL10n::Database::AddKeyValue("MYMOD_KEY", "sc_value", SSL10n::L_Simplified_Chinese);
    SSL10n::Database::Helper()
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
    std::string result2 = SSL10n::FormatKey("MYMOD_KEYx", 1,2,3);
    std::string result3 = SSL10n::FormatKeyWithDefault("MYMOD_KEYx", "the awnswer is {}", 42);
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

Use `qpm s build` to build
Same goes for `qpm s copy` and `qpm s qmod`

## Credits

* [zoller27osu](https://github.com/zoller27osu), [Sc2ad](https://github.com/Sc2ad) and [jakibaki](https://github.com/jakibaki) - [beatsaber-hook](https://github.com/sc2ad/beatsaber-hook)
* [raftario](https://github.com/raftario)
* [Lauriethefish](https://github.com/Lauriethefish), [danrouse](https://github.com/danrouse) and [Bobby Shmurner](https://github.com/BobbyShmurner) for [this template](https://github.com/Lauriethefish/quest-mod-template)
