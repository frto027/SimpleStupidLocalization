#include "SSL10n.hpp"
#include "SSLocalInternal.hpp"
#include "main.hpp"

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
        OnLanguageChangeCallback.invoke();
    }
}
