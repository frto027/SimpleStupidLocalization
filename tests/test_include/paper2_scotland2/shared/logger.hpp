#pragma once

#include <fmt/format.h>
#include <iostream>

namespace Paper{
    struct PaperContext{
        const char * tag = "";
        template <typename... T>
        void info(fmt::format_string<T...> fmt, T&&... args)const{
            std::cout << fmt::format(fmt, args...) << std::endl;
        }
    };
    constexpr inline PaperContext ConstLoggerContext(const char *){
        return {};
    }


    namespace Logger{
        template<typename T>
        void RegisterFileContextId(T t){}
    }
}