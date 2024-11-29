#include "DictionaryEnglish.h"
#include "SplitEnglish.h"
DictionaryEnglish::DictionaryEnglish(std::string src_path, std::string dict_path, std::string stop_path)
  : Dictionary(std::move(src_path), std::move(dict_path),std::make_shared<SplitEnglish>(std::move(stop_path)))
{

}
