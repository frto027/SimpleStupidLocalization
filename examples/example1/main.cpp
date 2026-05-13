#include "lang.hpp"

void late_load(){
    importLanguages();

    std::string some_var = LANG::MYMOD_KEY1();
    std::string some_fmt_var = LANG::MYMOD_KEYX(42);
}