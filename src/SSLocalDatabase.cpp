#include "SSL10n.hpp"
#include "SSLocalInternal.hpp"
#include "beatsaber-hook/shared/utils/utils-functions.h"
#include "main.hpp"
#include <ctime>
#include <sstream>
#include <string>
#include <string_view>
#include <time.h>
#include <vector>

namespace SSL10n{
    namespace Database {
        namespace PolyglotFormat {
            /* return true means a line break */
            bool parse_csv_cell(std::string_view& remains, std::vector<std::string> &output){
                if(remains.size() == 0){
                    return true;
                }
                if(remains[0] == '"'){
                    std::stringstream ss;
                    for(size_t i=1;i<remains.size();i++){
                        auto ch = remains[i];
                        if(ch == '"'){
                            if(i+1>=remains.size()){
                                remains = {};
                                output.emplace_back(ss.str());
                                return true;
                            }
                            if(remains[i+1] == ','){
                                remains = remains.substr(i+2);
                                output.emplace_back(ss.str());
                                return false;
                            }
                            if(remains[i+1] == '\r'){
                                if(i+2 < remains.size()){
                                    if(remains[i+2] == '\n'){
                                        remains = remains.substr(i+3);
                                        output.emplace_back(ss.str());
                                        return true;
                                    }
                                }
                            }
                            ss << remains[i+1];
                            i++;
                        }else{
                            ss << ch;
                        }
                    }
                    // file truncated
                    output.emplace_back(ss.str());
                    remains = {};
                    return true;
                }else{
                    int end_pos;
                    for(end_pos = 0; end_pos < remains.size(); end_pos++){
                        if(remains[end_pos] == ',' || (remains[end_pos] == '\r' && remains.size() > end_pos+1 && remains[end_pos+1] == '\n')){
                            break;
                        }
                    }
                    if(end_pos >= remains.size()){
                        output.emplace_back(remains);
                        remains = {};
                        return true;
                    }
                    if(remains[end_pos] == ','){
                        output.emplace_back(remains.substr(0, end_pos));
                        remains = remains.substr(end_pos+1);
                        return false;
                    }
                    if(remains[end_pos] == '\r' && remains.size() > end_pos+1 && remains[end_pos+1] == '\n'){
                        output.emplace_back(remains.substr(0, end_pos));
                        remains = remains.substr(end_pos+2);
                        return true;
                    }
                    safeAbort(__FUNCTION__, __FILE__, __LINE__);
                }
            }
            void parse_csv(std::string_view str){
                struct timespec time_start, time_end;
                size_t file_size = str.size();
                
                clock_gettime(CLOCK_MONOTONIC, &time_start);

                std::vector<std::vector<std::string>> lines;
                while(str.size() > 0){
                    std::vector<std::string> line;
                    while(str.size() > 0){
                        if(parse_csv_cell(str, line)){
                            lines.emplace_back(std::move(line));
                            line = {};
                        }
                    }
                    if(line.size() > 0){
                        lines.emplace_back(std::move(line));
                    }
                }
                bool got_first_line = false;
                for(auto& line : lines){
                    if(!got_first_line){
                        if(line.size() > 2 && line[0] == "Polyglot" && line[1] == "100"){
                            got_first_line = true;
                        }
                        continue;
                    }

                    if(line.size() < 1)
                        continue;
                    std::string key = line[0];
                    auto & keyStorage = langMaps[key];
                    for(int i=2;i<line.size(); i++){
                        int lang = i - 2;
                        if(lang < L_English || lang > L_Bosnian)
                            break;
                        if(line[i].size() == 0)
                            continue;
                        keyStorage.values[lang] = line[i];
                        keyStorage.valueExists.set(lang);
                    }
                }

                clock_gettime(CLOCK_MONOTONIC, &time_end);
                long long elapsed_ns = (time_end.tv_sec - time_start.tv_sec) * 1000000000LL + 
                        (time_end.tv_nsec - time_start.tv_nsec);
                PaperLogger.info("Parsed polyglot csv file, file size= {} bytes, parse time= {} ns", file_size, elapsed_ns);
            }
        }
    }
}


void SSL10n::Database::PolyglotFormat::AddCSVFile(const std::string& path){
    FILE * file = fopen(path.c_str(), "rb");
    if(!file)
        return;
    auto file_size = std::filesystem::file_size(path);
    std::string buff(file_size, 0);
    size_t i=0;
    while(i<file_size){
        auto ret = fread(&buff.data()[i], 1, file_size - i, file);
        i += ret;
        if(ret == 0){
            break;
        }
    }
    if(i != file_size || !feof(file)){
        fclose(file);
        return;
    }
    fclose(file);
    parse_csv(buff);
}
void SSL10n::Database::PolyglotFormat::AddCSVContent(const char * text, int size){
    parse_csv(std::string_view(text, size));
}

void SSL10n::Database::AddKeyValue(const std::string& key, const std::string& value, Language forLanguage){
    if(forLanguage >= 0 && forLanguage < SS_LANG_COUNT){
        auto & elem = langMaps[key];
        elem.values[forLanguage] = value;
        elem.valueExists.set(forLanguage);
    }
}

namespace SSL10n {
    namespace Database {
        struct HelperStorage{
            bool isValid;
            Language forLang;
            HelperStorage(Language lang){
                if(lang >= 0 && lang < SS_LANG_COUNT){
                    isValid = true;
                    forLang = lang;
                }else{
                    isValid = false;
                }
            }
        };
    }
}

SSL10n::Database::Helper::Helper(Language lang){
    storage = new HelperStorage(lang);
}

SSL10n::Database::Helper& SSL10n::Database::Helper::p(const std::string & key, const std::string& value){
    if(storage->isValid){
        auto & elem = langMaps[key];
        elem.values[storage->forLang] = value;
        elem.valueExists.set(storage->forLang);
    }
    return *this;
}
SSL10n::Database::Helper::~Helper(){
    delete storage;
}
