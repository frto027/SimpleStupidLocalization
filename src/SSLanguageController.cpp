#include "SSL10n.hpp"
#include "SSLocalInternal.hpp"
#include "main.hpp"
#include "modconfig.hpp"
bool followGameLanguage = true;

namespace SSL10n {
namespace LanguageController {
namespace TraditionalChinese {
static bool isPreferSimplified = true;

bool isPreferSimplifiedChinese() { return isPreferSimplified; }
void setPreferSimplifiedChinese(bool v) { isPreferSimplified = v; }
} // namespace TraditionalChinese
} // namespace LanguageController
} // namespace SSL10n

void SSL10n::LanguageController::SetCurrentLanguage(Language nextLanguage) {
    PaperLogger.info("Set language to {}, will print caller.", (int)nextLanguage);
    PaperLogger.Backtrace(3);

    if (nextLanguage == currentLanguage)
        return;
    if (nextLanguage >= 0 && nextLanguage < SS_LANG_COUNT) {
        currentLanguage = nextLanguage;
        if (getConfig().LastLanguage.GetValue() != nextLanguage) {
            getConfig().LastLanguage.SetValue(nextLanguage);
        }
        OnLanguageChangeCallback.invoke();
    }
}
void SSL10n::LanguageController::SetFollowGameLanguage(bool followGameLanguage) {
    PaperLogger.info("Set follow game language to {}. will print caller.", followGameLanguage);
    PaperLogger.Backtrace(3);
    ::followGameLanguage = followGameLanguage;
}
