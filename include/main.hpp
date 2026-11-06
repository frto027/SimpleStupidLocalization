#pragma once

// Include the modloader header, which allows us to tell the modloader which mod
// this is, and the version etc.
#include "scotland2/shared/modloader.h"

#include "paper2_scotland2/shared/logger.hpp"

#include "_config.hpp"

constexpr auto PaperLogger = Paper::ConstLoggerContext("sslocalization");
