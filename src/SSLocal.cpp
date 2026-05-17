#include "SSL10n.hpp"
#include "SSLocalInternal.hpp"

#include <locale>
#include <utility>

std::map<std::string, KeyStorage> langMaps;
SSL10n::Language currentLanguage = SSL10n::L_English;

SSL10n::Language fallbackLanguage(SSL10n::Language language){
    switch (language) {
        case SSL10n::L_Simplified_Chinese:
            return  SSL10n::L_Traditional_Chinese;
        default:
            return SSL10n::L_English;
    }
}

std::string SSL10n::Get(const std::string& key){
    auto it = langMaps.find(key);
    if(it == langMaps.end())[[unlikely]]{
        return key;
    }
    auto lang = currentLanguage;
    if(it->second.valueExists.test(lang))[[likely]]{
        return it->second.values[lang];
    }
    while(true){
        if(lang == L_English)
            return key;
        lang = fallbackLanguage(lang);
        if(it->second.valueExists.test(lang))[[likely]]{
            return it->second.values[lang];
        }
    }
}
std::string SSL10n::Get(const std::string& key, Language forLang, bool withFallback){
    if(forLang >=0 && forLang < SS_LANG_COUNT)[[likely]]{
        auto it = langMaps.find(key);
        if(it == langMaps.end())
            [[unlikely]] return key;
        if(it->second.valueExists.test(forLang))[[likely]]{
            return it->second.values[forLang];
        }
        if(withFallback)[[unlikely]]{
            while(true){
                if(forLang == L_English)
                    return key;
                forLang = fallbackLanguage(forLang);
                if(it->second.valueExists.test(forLang))[[likely]]
                    return it->second.values[forLang];
            }
        }
        return key;

    }
    return key;
}

EventCallback<> SSL10n::OnLanguageChangeCallback;

SSL10n::Language SSL10n::GetCurrentLanguage(){
    return currentLanguage;
}

const std::locale& SSL10n::GetCurrentLocale(){
    return GetLanguageLocale(currentLanguage);
}
const std::locale& SSL10n::GetLanguageLocale(Language lang){
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
        #define CASE(x) case Language::L_##x: return locale_##x;
        FOR_EACH_LANGUAGES(CASE)
        #undef CASE
    }
}
