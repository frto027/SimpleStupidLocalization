#pragma once

#include <bitset>
#include <string>
#include <map>
#include "SSL10n.hpp"

#define SS_LANG_COUNT 18

struct KeyStorage{
    std::bitset<SS_LANG_COUNT> valueExists;
    std::string values[SS_LANG_COUNT];
};

extern std::map<std::string, KeyStorage> langMaps;
extern SSL10n::Language currentLanguage;
