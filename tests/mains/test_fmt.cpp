#include <iostream>
#include "SSL10n.hpp"
using namespace std;

int main(void){

    SSL10n::Database::Helper()
        .p("KEY_HELLO", "Hello, I'm {}")
        .p("KEY_WORLD", "world!");

    SSL10n::Database::Helper(SSL10n::L_Simplified_Chinese)
        .p("KEY_HELLO", "你好 {} {}")
        .p("KEY_WORLD", "世界");

    //default is english
    std::cout<<SSL10n::FormatKeyWithDefault("KEY_HELLO", "Hi, {}", 43) << " " << SSL10n::Get("KEY_WORLD") <<std::endl;

    //should output simplified chinese
    SSL10n::LanguageController::SetCurrentLanguage(SSL10n::L_Simplified_Chinese);
    std::cout<<SSL10n::FormatKeyWithDefault("KEY_HELLO", "Hi, {}", 43) << " " << SSL10n::Get("KEY_WORLD") <<std::endl;

    //should fallback to english
    SSL10n::LanguageController::SetCurrentLanguage(SSL10n::L_Bosnian);
    std::cout<<SSL10n::FormatKeyWithDefault("KEY_HELLO", "Hi, {}", 43) << " " << SSL10n::Get("KEY_WORLD") <<std::endl;

    return 0;    
}