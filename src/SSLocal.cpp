#include "SSLocalInternal.hpp"

#include <atomic>
#include <functional>
#include <utility>
#include <vector>
#include <set>
std::set<std::string> touchedKeys;

std::map<std::string, ValueStorage> langMaps[SS_LANG_COUNT];
SSL10n::Language currentLanguage = SSL10n::L_English;
std::vector<std::pair<SSL10n::callback_id_ty, std::function<void(void)>>> langChangeCallbacks;
std::atomic_int nextCallbackId = 1;
int currentEpoch = 0;

std::string SSL10n::Get(const std::string& key){
    auto & map = langMaps[currentLanguage];
    auto it = map.find(key);
    if(it == map.end()){
        auto & fallback = langMaps[SSL10n::Language::L_English];
        auto itt = fallback.find(key);
        if(itt != fallback.end()){
            if(itt->second.currentEpoch != currentEpoch){
                touchedKeys.insert(key);
                itt->second.currentEpoch = currentEpoch;
            }
            return itt->second.value;
        }
        return key;
    }
    if(it->second.currentEpoch != currentEpoch){
        touchedKeys.insert(key);
        it->second.currentEpoch = currentEpoch;
    }
    return it->second.value;
}
std::string SSL10n::Get(const std::string& key, Language forLang){
    if(forLang >=0 && forLang < SS_LANG_COUNT){
        auto & map = langMaps[forLang];
        auto it = map.find(key);
        if(it == map.end())
            return key;
        if(it->second.currentEpoch != currentEpoch){
            touchedKeys.insert(key);
            it->second.currentEpoch = currentEpoch;
        }
        return it->second.value;
    }
    return key;
}
SSL10n::callback_id_ty SSL10n::AddLangChangeCallback(std::function<void(void)> f){
    int id = nextCallbackId++;
    langChangeCallbacks.emplace_back(std::make_pair(id, f));
    return id;
}
void SSL10n::RemoveLangChangeCallback(callback_id_ty callbackId){
    std::erase_if(langChangeCallbacks, [callbackId](decltype(langChangeCallbacks)::value_type& x){
        return x.first == callbackId;
    });
}
SSL10n::Language SSL10n::GetCurrentLanguage(){
    return currentLanguage;
}

