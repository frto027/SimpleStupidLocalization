#pragma once

#include "beatsaber-hook/shared/utils/typedefs-wrappers.hpp"
#include <fmt/base.h>
#include <fmt/format.h>
#include <locale>
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

    SSLOCAL_EXTERN std::string Get(const std::string& key);
    SSLOCAL_EXTERN std::string Get(const std::string& key, Language forLang, bool withFallback = false);

    extern SSLOCAL_EXTERN EventCallback<> OnLanguageChangeCallback;

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
            SSLOCAL_EXTERN Helper& v(const std::string & key, const std::string& value);
            SSLOCAL_EXTERN ~Helper();
        };
        
    }

    namespace LanguageController {
        // these funcs should be called by language controller
        SSLOCAL_EXTERN void SetCurrentLanguage(Language nextLanguage);
        SSLOCAL_EXTERN void SetFollowGameLanguage(bool followGameLanguage);
    }

    SSLOCAL_EXTERN const std::locale& GetCurrentLocale();
    SSLOCAL_EXTERN const std::locale& GetLanguageLocale(Language lang);

    template <typename... T>
    std::string FormatKeyWithDefault(std::string key, fmt::format_string<T...> fmt, T&&... args){
        std::string r = Get(key);
        if(r != key){
            try{
                return fmt::vformat(GetCurrentLocale(), r, fmt::make_format_args(args...));
            }catch(...){
            }
        }

        try{
            return fmt::vformat(GetCurrentLocale(), fmt, fmt::make_format_args(args...));
        }catch(...){
        }

        if(r != key){
            return r;
        }
        return std::string(fmt.get().data(), fmt.get().size());
    }
    template <typename... T>
    std::string FormatKey(std::string key, T&&... args){
        try{
            return fmt::vformat(GetCurrentLocale(), Get(key), fmt::make_format_args(args...));
        }catch(...){
            return Get(key);
        }
    }
}