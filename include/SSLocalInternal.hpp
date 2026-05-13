#pragma once

#include <vector>
#include <map>
#include "SSL10n.hpp"
#include <set>

#define SS_LANG_COUNT 18

extern std::set<std::string> touchedKeys;

struct ValueStorage{
    std::string value;
    int currentEpoch = 0;
};

extern std::map<std::string, ValueStorage> langMaps[SS_LANG_COUNT];
extern SSL10n::Language currentLanguage;
extern std::vector<std::pair<SSL10n::callback_id_ty, std::function<void(void)>>> langChangeCallbacks;
extern std::atomic_int nextCallbackId;
extern int currentEpoch;