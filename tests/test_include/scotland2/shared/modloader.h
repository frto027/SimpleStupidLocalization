#pragma once

namespace modloader{
    class ModInfo{
    public:
        const char * modid;
        int version;
        int version2;
        ModInfo(const char*,int,int){}
        ModInfo to_c(){
            return *this;
        }
    };
}
using CModInfo = modloader::ModInfo;

#define MOD_ID "modid"
#define VERSION 0