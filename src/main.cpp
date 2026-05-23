#include "main.hpp"

#include "GameHooks.hpp"
#include "scotland2/shared/modloader.h"
#include <fmt/base.h>
#include <fmt/format.h>

#include "SSL10n.hpp"
#include "SSL10n/GameKeys.hpp"
#include "modconfig.hpp"
#include "SSL10n.hpp"
#include "SSLocalInternal.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};
// Stores the ID and version of our mod, and is sent to
// the modloader upon startup

// Called at the early stages of game loading
MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
    *info = modInfo.to_c();

    getConfig().Init(modInfo);

    // File logging
    Paper::Logger::RegisterFileContextId(PaperLogger.tag);

    // load last language before the game hook
    if (followGameLanguage) {
        SSL10n::LanguageController::SetCurrentLanguage((SSL10n::Language)getConfig().LastLanguage.GetValue());
    }

    PaperLogger.info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();

    PaperLogger.info("Installing hooks...");
    SSL10n::GameHooks::Init();
    PaperLogger.info("Installed all hooks!");

}