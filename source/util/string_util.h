#ifndef STRING_UTIL_H__
#define STRING_UTIL_H__

#include <string>

namespace StringUtil
{
  std::wstring Utf8ToUnicode(const char* mbstr);
  std::string UnicodetoUtf8(const wchar_t* wcstr);
}

#endif//