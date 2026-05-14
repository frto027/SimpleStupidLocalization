#include "SSL10n.hpp"
#include "SSLocalInternal.hpp"

void SSL10n::LanguageController::SetCurrentLanguage(Language nextLanguage){
    if(nextLanguage >=0 && nextLanguage < SS_LANG_COUNT){
        currentLanguage = nextLanguage;
        OnLanguageChangeCallback.invoke();
    }
}
