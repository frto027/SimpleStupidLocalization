#include "GameHooks.hpp"
#include "SSL10n.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "main.hpp"
#include "SSLocalInternal.hpp"

#include "BGLib/Polyglot/Language.hpp"
#include "BGLib/Polyglot/CsvReader.hpp"
#include "BGLib/Polyglot/ILocalize.hpp"
#include "BGLib/Polyglot/Localization.hpp"
#include "BGLib/Polyglot/LocalizationModel.hpp"
#include "BGLib/Polyglot/LocalizationImporter.hpp"
#include "BGLib/Polyglot/LocalizationAsyncInstaller.hpp"

static bool SyncPolyglotLanguageFromPolyglot(BGLib::Polyglot::LocalizationModel *instance) {
    switch (instance->get_SelectedLanguage()) {

#define CASE(lang)                                                                                                     \
    case BGLib::Polyglot::Language::lang:                                                                              \
        if (SSL10n::GetCurrentLanguage() == SSL10n::L_##lang)                                                          \
            return false;                                                                                              \
        SSL10n::LanguageController::SetCurrentLanguage(SSL10n::L_##lang);                                              \
        return true;
        FOR_EACH_LANGUAGES(CASE)
#undef CASE

    default:
        return false;
    }
}

// load KVs from the game
MAKE_HOOK_MATCH(Polyglot_CsvParser, &BGLib::Polyglot::CsvReader::Parse,
                ::System::Collections::Generic::List_1<::System::Collections::Generic::List_1<::StringW> *> *,
                ::StringW src) {
    PaperLogger.info("Parse csv file from polyglot");
    std::string srcstr(src);
    SSL10n::Database::PolyglotFormat::AddCSVContent(srcstr.c_str(), srcstr.size());
    return Polyglot_CsvParser(src);
}

// sync game language settings
MAKE_HOOK_MATCH(Localization_SetSelectLang, &BGLib::Polyglot::LocalizationModel::set_SelectedLanguage, void,
                ::BGLib::Polyglot::LocalizationModel *self, ::BGLib::Polyglot::Language lang) {
    Localization_SetSelectLang(self, lang);

    if (followGameLanguage) {
        PaperLogger.info("On localize executed");
        if (SyncPolyglotLanguageFromPolyglot(self)) {
            PaperLogger.info("Language has been updated to {}.", (int)SSL10n::GetCurrentLanguage());
        }
    } else {
        PaperLogger.info("Not follow game language");
    }
}

void SSL10n::GameHooks::Init() {
    INSTALL_HOOK(PaperLogger, Localization_SetSelectLang);
    INSTALL_HOOK(PaperLogger, Polyglot_CsvParser);
}