#include "GameHooks.hpp"
#include "BGLib/Polyglot/CsvReader.hpp"
#include "UnityEngine/PlayerPrefs.hpp"
#include "SSL10n.hpp"
#include "UnityEngine/zzzz__PlayerPrefs_def.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "BGLib/Polyglot/CsvReader.hpp"
#include "BGLib/Polyglot/Localization.hpp"
#include "main.hpp"
#include "SSLocalInternal.hpp"

#if 0
#include "BGLib/Polyglot/Localization.hpp"
#include "BGLib/Polyglot/LocalizationModel.hpp"
#include "BGLib/Polyglot/Language.hpp"
static void SyncPolyglotLanguageFromPolyglot(){
    switch(BGLib::Polyglot::Localization::get_Instance()->get_SelectedLanguage()){

        #define CASE(lang)                                                          \
            case BGLib::Polyglot::Language::lang:                                   \
                SSL10n::LanguageController::SetCurrentLanguage(SSL10n::L_##lang);   \
            break;
        FOR_EACH_LANGUAGES(CASE)
        #undef CASE

        default:
            break;
    }
}
#endif

// handle soft restart
// FIXME: use other hook site
MAKE_HOOK_MATCH(
    MenuTransitionsHelper_RestartGame,
    &GlobalNamespace::MenuTransitionsHelper::RestartGame,
    void,
    GlobalNamespace::MenuTransitionsHelper* self,
    System::Action_1<Zenject::DiContainer*>* finishCallback
) {
    PaperLogger.info("handle soft restart");

    if(followGameLanguage){
        int selectedLanguage = UnityEngine::PlayerPrefs::GetInt("Polyglot.SelectedLanguage", -1);
        if(selectedLanguage >= SSL10n::L_English && selectedLanguage < SSL10n::L_Bosnian){
            SSL10n::LanguageController::SetCurrentLanguage((SSL10n::Language)selectedLanguage);
        }
    }
    MenuTransitionsHelper_RestartGame(self, finishCallback);
}

MAKE_HOOK_MATCH(
    Polyglot_CsvParser,
    &BGLib::Polyglot::CsvReader::Parse,
    ::System::Collections::Generic::List_1<::System::Collections::Generic::List_1<::StringW>*>*,
    ::StringW src
    ){
    PaperLogger.info("Parse csv file from polyglot");
    std::string srcstr(src);
    SSL10n::Database::PolyglotFormat::AddCSVContent(srcstr.c_str(), srcstr.size());
    return Polyglot_CsvParser(src);
}

void SSL10n::GameHooks::Init(){
    INSTALL_HOOK(PaperLogger, MenuTransitionsHelper_RestartGame);
    INSTALL_HOOK(PaperLogger, Polyglot_CsvParser);
}