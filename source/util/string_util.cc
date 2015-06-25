#include "../stdafx.h"
#include <string>
#include "string_util.h"

namespace StringUtil
{
  std::wstring Utf8ToUnicode(const char* mbstr)
  {
    if (!mbstr)
    {
      return std::wstring();
    }

    wchar_t* wcstr = NULL;

    // Get the size of wchar_t after converted
#ifdef WIN32
    int size = MultiByteToWideChar(CP_UTF8, 0, mbstr, -1, NULL, 0);
#else
    size_t size = mbstowcs(NULL, mbstr, 0);
#endif

    wcstr = new wchar_t[size+1];
    if (wcstr)
    {
      memset(wcstr, 0, size * sizeof(wchar_t));
#ifdef WIN32
      int ret = MultiByteToWideChar(CP_UTF8, 0, mbstr, -1, wcstr, size);
      if (ret == 0) // MultiByteToWideChar returns 0 if it does not succeed.
#else
      size_t ret = mbstowcs(wcstr, mbstr, size+1);
      if (ret == -1)
#endif
      {
        delete[] wcstr;
        wcstr = NULL;

        return std::wstring();
      }
    }

    std::wstring strResult = wcstr;
    delete[] wcstr;
    return strResult;
  }

  std::string UnicodetoUtf8(const wchar_t* wcstr)
  {
    if (!wcstr)
    {
      return std::string();
    }

    char* mbstr = NULL;

    // Get the size of char after converted
#ifdef WIN32
    int size = WideCharToMultiByte(CP_UTF8, 0, wcstr, -1, NULL, 0, NULL, NULL);
#else
    size_t size = wcstombs(NULL, wcstr, 0);
#endif

    mbstr = new char[size+1];
    if (mbstr)
    {
      memset(mbstr, 0, size * sizeof(char));
#ifdef WIN32
      int ret = WideCharToMultiByte(CP_UTF8, 0, wcstr, -1, mbstr, size, NULL, NULL);
      if (ret == 0) // MultiByteToWideChar returns 0 if it does not succeed.
#else
      size_t ret = wcstombs(mbstr, wcstr, size+1);
      if (ret == -1)
#endif
      {
        delete[] mbstr;
        mbstr = NULL;

        return std::string();
      }
    }

    std::string strResult = mbstr;
    delete[] mbstr;
    return strResult;
  }
}