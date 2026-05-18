#include "SSL10n.hpp"
#include "SSLocalInternal.hpp"

bool followGameLanguage = true;


namespace SSL10n{
    namespace LanguageController {
        namespace TraditionalChinese {
            static bool isPreferSimplified = true;

            bool isPreferSimplifiedChinese(){
                return isPreferSimplified;
            }
            void setPreferSimplifiedChinese(bool v){
                isPreferSimplified = v;
            }
        }
    }
}

void SSL10n::LanguageController::SetCurrentLanguage(Language nextLanguage){
    if(nextLanguage == currentLanguage)
        return;
    if(nextLanguage >=0 && nextLanguage < SS_LANG_COUNT){
        currentLanguage = nextLanguage;
        OnLanguageChangeCallback.invoke();
    }
}
void SSL10n::LanguageController::SetFollowGameLanguage(bool followGameLanguage){
    ::followGameLanguage = followGameLanguage;
}
