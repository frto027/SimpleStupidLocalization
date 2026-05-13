#pragma once

#include "SSL10n.hpp"

namespace LANG{
#define V(key, value) inline std::string key(){ return SSL10n::Get(#key); }
#define V_FMT(key, value) template <typename... T> std::string key(T... args) { return SSL10n::FormatKeyWithDefault(#key, value, args...);}
#include "english.inl"
#undef V
#undef V_FMT

};


inline void importLanguages(){
    #define V(key, value) .p(#key, value)
    #define V_FMT(key, value) .p(#key, value)
    SSL10n::Database::Helper()
    #include "english.inl"
    ;

    SSL10n::Database::Helper(SSL10n::Language::L_Simplified_Chinese)
    #include "chinese.inl"
    ;
    #undef V
    #undef V_FMT
}