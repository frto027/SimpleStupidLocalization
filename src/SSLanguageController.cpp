#include "SSLocalInternal.hpp"

bool isDirtyUIInformed = false;
int keyTouchedCountBeforeSwitchLanguage = 0;

void SSL10n::LanguageController::InformDirtyUI(){
    isDirtyUIInformed = true;
}

void SSL10n::LanguageController::SetCurrentLanguage(Language nextLanguage){
    if(nextLanguage >=0 && nextLanguage < SS_LANG_COUNT){
        isDirtyUIInformed = false;
        currentLanguage = nextLanguage;
        if(keyTouchedCountBeforeSwitchLanguage < touchedKeys.size())
            keyTouchedCountBeforeSwitchLanguage = touchedKeys.size();
        touchedKeys.clear();
        currentEpoch++;
        for(auto & cb : langChangeCallbacks){
            cb.second();
        }
    }
}

bool SSL10n::LanguageController::IsUIDirty(){
    if(isDirtyUIInformed)
        return true;
    if(touchedKeys.size() < keyTouchedCountBeforeSwitchLanguage)
        return true;
    return false;
}
