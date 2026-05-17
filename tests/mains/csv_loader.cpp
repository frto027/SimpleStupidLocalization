#include <iostream>
#include "SSL10n.hpp"
using namespace std;

int main(int argc, char ** argv){
    if(argc != 2){
        std::cout<<"Usage: "<<argv[0]<<" <csv path>\n";
        exit(1);
    }
    SSL10n::Database::PolyglotFormat::AddCSVFile(argv[1]);

    for(int i=SSL10n::L_English; i<SSL10n::L_Bosnian; i++){
        SSL10n::LanguageController::SetCurrentLanguage((SSL10n::Language)i);
        std::cout<<SSL10n::Get("CONTEXT_CLASS_DEMON") << " " << SSL10n::Get("CONTEXT_CLASS_THIEF") <<std::endl;
    }

    return 0;    
}