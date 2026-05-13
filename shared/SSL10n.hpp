#pragma once

#include <fmt/base.h>
#include <fmt/format.h>
#include <functional>
#include <string>

#ifdef SSLOCAL_MAIN_MOD
#define SSLOCAL_EXTERN __attribute__((visibility("default")))
#else
#define SSLOCAL_EXTERN
#endif

namespace SSL10n {
    enum Language{
        L_English,
        L_French,
        L_Spanish,
        L_German,
        L_Italian,
        L_Portuguese_Brazil,
        L_Portuguese,
        L_Russian,
        L_Greek,
        L_Turkish,
        L_Danish,
        L_Norwegian,
        L_Swedish,
        L_Dutch,
        L_Polish,
        L_Finnish,
        L_Japanese,
        L_Simplified_Chinese,
        L_Traditional_Chinese,
        L_Korean,
        L_Czech,
        L_Hungarian,
        L_Romanian,
        L_Thai,
        L_Bulgarian,
        L_Hebrew,
        L_Arabic,
        L_Bosnian,
    };
    using callback_id_ty = int;

    SSLOCAL_EXTERN std::string Get(const std::string& key);
    SSLOCAL_EXTERN std::string Get(const std::string& key, Language forLang);
    /* returns callback id that can be use for remove */
    SSLOCAL_EXTERN callback_id_ty AddLangChangeCallback(std::function<void(void)>);
    SSLOCAL_EXTERN void RemoveLangChangeCallback(callback_id_ty callbackId);

    SSLOCAL_EXTERN Language GetCurrentLanguage();

    namespace Database {
        namespace PolyglotFormat{
            SSLOCAL_EXTERN void AddCSVFile(const std::string& path);
            SSLOCAL_EXTERN void AddCSVContent(const char * text, int size);
        }

        SSLOCAL_EXTERN void AddKeyValue(const std::string& key, const std::string& value, Language forLanguage = Language::L_English );
        struct HelperStorage;
        struct Helper{
            HelperStorage * storage;
            SSLOCAL_EXTERN Helper(Language lang = Language::L_English);
            SSLOCAL_EXTERN Helper& p(const std::string & key, const std::string& value);
            SSLOCAL_EXTERN ~Helper();
        };
        
    }

    namespace LanguageController {
        // called by mods to inform the mods' ui are dirty, and will not updated unless game restart
        SSLOCAL_EXTERN void InformDirtyUI();

        // these funcs should be called by language controller
        SSLOCAL_EXTERN void SetCurrentLanguage(Language nextLanguage);
        SSLOCAL_EXTERN bool IsUIDirty();
    }

    template <typename... T>
    std::string FormatKeyWithDefault(std::string key, fmt::format_string<T...> fmt, T&&... args){
        std::string r = Get(key);
        if(r == key){
            return fmt::vformat(fmt, fmt::make_format_args(args...));
        }else{
            return fmt::vformat(r, fmt::make_format_args(args...));
        }
    }
    template <typename... T>
    std::string FormatKey(std::string key, T&&... args){
        return fmt::vformat(Get(key), fmt::make_format_args(args...));
    }
    namespace CommonKeys {
        inline const char * YES = "SSLOCAL_YES";
        inline const char * NO = "SSLOCAL_NO";
        inline const char * CANCEL = "SSLOCAL_CANCEL";
    }

}