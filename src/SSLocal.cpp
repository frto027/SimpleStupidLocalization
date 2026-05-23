#include "SSL10n.hpp"
#include "SSLocalInternal.hpp"

#include <locale>
#include <utility>

std::map<std::string, KeyStorage> langMaps;
SSL10n::Language currentLanguage = SSL10n::L_English;

std::optional<std::string> readFallback(SSL10n::Language lang, KeyStorage &storage) {
#define TRY_RETURN(lang)                                                                                               \
    do {                                                                                                               \
        if (storage.valueExists.test(SSL10n::lang))                                                                    \
            return storage.values[SSL10n::lang];                                                                       \
    } while (0)
    switch (lang) {
    default:
        TRY_RETURN(L_English);
        return std::nullopt;
    case SSL10n::L_Simplified_Chinese:
        TRY_RETURN(L_Traditional_Chinese);
        TRY_RETURN(L_English);
        return std::nullopt;
    case SSL10n::L_Traditional_Chinese:
        if (SSL10n::LanguageController::TraditionalChinese::isPreferSimplifiedChinese())
            TRY_RETURN(L_Simplified_Chinese);
        TRY_RETURN(L_English);
        return std::nullopt;
    }
#undef TRY_RETURN
}

std::string SSL10n::Get(const std::string &key, bool withFallback) {
    return GetOptional(key, withFallback).value_or(key);
}

std::string SSL10n::Get(const std::string &key, Language forLang, bool withFallback) {
    return GetOptional(key, forLang, withFallback).value_or(key);
}
std::string SSL10n::GetDefault(const std::string &key, const std::string &defaultValue, bool withFallback) {
    return GetOptional(key, withFallback).value_or(defaultValue);
}

std::optional<std::string> SSL10n::GetOptional(const std::string &key, bool withFallback) {
    auto it = langMaps.find(key);
    if (it == langMaps.end()) [[unlikely]] {
        return std::nullopt;
    }
    auto lang = currentLanguage;
    if (it->second.valueExists.test(lang)) [[likely]] {
        return it->second.values[lang];
    }
    if (withFallback) [[likely]] {
        return readFallback(lang, it->second);
    }
    return std::nullopt;
}
std::optional<std::string> SSL10n::GetOptional(const std::string &key, Language forLang, bool withFallback) {
    if (forLang >= 0 && forLang < SS_LANG_COUNT) [[likely]] {
        auto it = langMaps.find(key);
        if (it == langMaps.end()) [[unlikely]]
            return std::nullopt;
        if (it->second.valueExists.test(forLang)) [[likely]] {
            return it->second.values[forLang];
        }
        if (withFallback) [[likely]] {
            return readFallback(forLang, it->second);
        }
    }
    return std::nullopt;
}

EventCallback<> SSL10n::OnLanguageChangeCallback;

SSL10n::Language SSL10n::GetCurrentLanguage() { return currentLanguage; }

const std::locale &SSL10n::GetCurrentLocale() { return GetLanguageLocale(currentLanguage); }
const std::locale &SSL10n::GetLanguageLocale(Language lang) {
    static std::locale en_US("en_US.UTF-8");
    static std::locale locale_English("en_US.UTF-8");
    static std::locale locale_French("fr_FR.UTF-8");
    static std::locale locale_Spanish("es_ES.UTF-8");
    static std::locale locale_German("de_DE.UTF-8");
    static std::locale locale_Italian("it_IT.UTF-8");
    static std::locale locale_Portuguese_Brazil("pt_BR.UTF-8");
    static std::locale locale_Portuguese("pt_PT.UTF-8");
    static std::locale locale_Russian("ru_RU.UTF-8");
    static std::locale locale_Greek("el_GR.UTF-8");
    static std::locale locale_Turkish("tr_TR.UTF-8");
    static std::locale locale_Danish("da_DK.UTF-8");
    static std::locale locale_Norwegian("nb_NO.UTF-8");
    static std::locale locale_Swedish("sv_SE.UTF-8");
    static std::locale locale_Dutch("nl_NL.UTF-8");
    static std::locale locale_Polish("pl_PL.UTF-8");
    static std::locale locale_Finnish("fi_FI.UTF-8");
    static std::locale locale_Japanese("ja_JP.UTF-8");
    static std::locale locale_Simplified_Chinese("zh_CN.UTF-8");
    static std::locale locale_Traditional_Chinese("zh_HK.UTF-8");
    static std::locale locale_Korean("ko_KR.UTF-8");
    static std::locale locale_Czech("cs_CZ.UTF-8");
    static std::locale locale_Hungarian("hu_HU.UTF-8");
    static std::locale locale_Romanian("ro_RO.UTF-8");
    static std::locale locale_Thai("th_TH.UTF-8");
    static std::locale locale_Bulgarian("bg_BG.UTF-8");
    static std::locale locale_Hebrew("he_IL.UTF-8");
    static std::locale locale_Arabic("ar_AE.UTF-8");
    static std::locale locale_Bosnian("bs_BA.UTF-8");

    switch (lang) {
    default:
        return en_US;
#define CASE(x)                                                                                                        \
    case Language::L_##x:                                                                                              \
        return locale_##x;
        FOR_EACH_LANGUAGES(CASE)
#undef CASE
    }
}
