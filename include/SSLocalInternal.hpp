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
extern bool followGameLanguage;
#define FOR_EACH_LANGUAGES(CASE)    \
    CASE(English)                   \
    CASE(French)                    \
    CASE(Spanish)                   \
    CASE(German)                    \
    CASE(Italian)                   \
    CASE(Portuguese_Brazil)         \
    CASE(Portuguese)                \
    CASE(Russian)                   \
    CASE(Greek)                     \
    CASE(Turkish)                   \
    CASE(Danish)                    \
    CASE(Norwegian)                 \
    CASE(Swedish)                   \
    CASE(Dutch)                     \
    CASE(Polish)                    \
    CASE(Finnish)                   \
    CASE(Japanese)                  \
    CASE(Simplified_Chinese)        \
    CASE(Traditional_Chinese)       \
    CASE(Korean)                    \
    CASE(Czech)                     \
    CASE(Hungarian)                 \
    CASE(Romanian)                  \
    CASE(Thai)                      \
    CASE(Bulgarian)                 \
    CASE(Hebrew)                    \
    CASE(Arabic)                    \
    CASE(Bosnian)
