#include <fstream>
#include "DictionaryChinese.h"
#include "SplitChinese.h"
DictionaryChinese::DictionaryChinese(std::string src_path,
                                     std::string dict_path,
                                     std::string stop_path,
                                     std::string json_path)
    : Dictionary(std::move(src_path),
                 std::move(dict_path),
                 std::make_shared<SplitChinese>(std::move(stop_path), std::move(json_path))) {

}

