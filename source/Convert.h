#pragma once

namespace Util
{
	namespace Convert
	{

		inline CStringA Utf8FromWSLimit(int limit, const wchar_t * str, int len)
		{
			if(len<0) len = _tcslen(str);
			CStringA  sr;
			if (limit <= 0 || len == 0)
			{
				return sr;
			}
			int utf8len = 0;
			for (int i=0; i<len; ++i)
			{
				int marki = i;
				unsigned short us = str[i];
				if (us == 0)
				{
					utf8len += 2;
				}
				else if (us <= 0x7f)
				{
					utf8len += 1;
				}
				else if (us <= 0x7ff)
				{
					utf8len += 2;
				}
				else if (0xd800 <= us && us <= 0xdbff && i+1<len)
				{
					unsigned short ul = str[i+1];
					if (0xdc00 <= ul && ul <= 0xdfff)
					{
						++i;
						utf8len += 4;
					}
					else
					{
						utf8len += 3;
					}
				}
				else
				{
					utf8len += 3;
				}
				if (utf8len > limit)
				{
					len = marki;
					break;
				}
			}

			PBYTE pc = (PBYTE)sr.GetBuffer(utf8len+1);
			for (int i=0; i<len; ++i)
			{
				unsigned short us = str[i];
				if (us == 0)
				{
					*pc ++ = 0xc0;
					*pc ++ = 0x80;
				}
				else if (us <= 0x7f)
				{
					*pc ++ = (char)us;
				}
				else if (us <= 0x7ff)
				{
					*pc ++ = 0xc0 | (us >> 6);
					*pc ++ = 0x80 | (us & 0x3f);
				}
				else if(0xd800 <= us && us <= 0xdbff && i+1<len)
				{
					unsigned short ul = str[i+1];
					if (0xdc00 <= ul && ul <= 0xdfff)
					{
						++i;
						UINT bc = (us-0xD800)*0x400 + (ul-0xDC00) + 0x10000;
						*pc ++ = (BYTE)(0xf0 | ((bc >> 18) & 0x07));
						*pc ++ = (BYTE)(0x80 | ((bc >> 12) & 0x3f));
						*pc ++ = (BYTE)(0x80 | ((bc >>  6) & 0x3f));
						*pc ++ = (BYTE)(0x80 | ((bc      ) & 0x3f));
					}
					else
					{
						*pc ++ = (BYTE) (0xe0 | ((us >> 12) & 0x0f));
						*pc ++ = (BYTE) (0x80 | ((us >>  6) & 0x3f));
						*pc ++ = (BYTE) (0x80 | ((us      ) & 0x3f));
					}
				}
				else
				{
					*pc ++ = (BYTE) (0xe0 | ((us >> 12) & 0x0f));
					*pc ++ = (BYTE) (0x80 | ((us >>  6) & 0x3f));
					*pc ++ = (BYTE) (0x80 | ((us      ) & 0x3f));
				}
			}
			* pc++ = 0;
			sr.ReleaseBuffer();
			return sr;
		}

		inline CStringA Utf8FromWS(const wchar_t * str, int len)
		{
			return Utf8FromWSLimit(0x7fffffff, str, len);
		}

		inline CStringW Utf8ToWS(const char * str, int len)
		{
			CStringW sw;
			if (str == 0) return sw;
			if (len <  0) len = (int)strlen(str);
			if (len == 0) return sw;
#ifdef WIN32
			int nLength = MultiByteToWideChar(CP_UTF8,0,str,len,0,0);
			MultiByteToWideChar(CP_UTF8,0,str,len,sw.GetBuffer(nLength+1),nLength);
			sw.ReleaseBuffer(nLength);
#else
#ifdef __LINUX__
			iconv_t cd = iconv_open ("UCS-4LE", "UTF-8");
#else	
			iconv_t cd = iconv_open ("UCS-4-INTERNAL", "UTF-8");
#endif
			int ee = errno;
			char *p = strerror(ee);
			char *outbuf = (char*)calloc(len +1, sizeof(wchar_t));
			char *tmpBuf = outbuf;
			*outbuf = 0;
			size_t outbytesleft = sizeof(wchar_t) * (len + 1);
			size_t inbytesleft = len;
			while (inbytesleft > 0) 
			{
				ee = iconv(cd, (char**)&str, &inbytesleft, &tmpBuf, &outbytesleft);
				if (ee == (size_t)(-1)) 
				{
					ee = errno;
					p = strerror(ee);
					break;
				}
			}
			//iconv(cd, &str, &inbytesleft, &outbuf, &outbytesleft);
			iconv_close(cd);

			sw = (wchar_t*)outbuf;
			free(outbuf);
#endif
			return sw;
		}

	}
}