#include "qqgame_util.h"

#include <WinVer.h>
#include <Shlwapi.h>
#include <atlstr.h>

namespace qqgame
{
  bool CheckQQGameRunning(HWND* hMsgWnd)
  {
    return (*hMsgWnd = ::FindWindowEx(NULL, NULL, QQGAME_MAINFRAME_WNDCLASS, NULL)) != NULL;
  }

  bool CheckQQGameSetup(HWND* hMsgWnd)
  {
    return (*hMsgWnd = ::FindWindowEx(NULL, NULL, QQGAME_SETUP_WNDCLASS, NULL)) != NULL;
  }

	bool GetQQGwpExePath(std::wstring& QQGwpFullPath){
		HKEY mq;
		DWORD rec,rbt;
		rec = REG_SZ;
		rbt = MAX_PATH;

    wchar_t buf[MAX_PATH] = {0};
		long rs = RegOpenKeyEx(HKEY_CURRENT_USER, QQGAME_SUBKEY_PATH, 0,  KEY_ALL_ACCESS, &mq);
		if((rs==ERROR_SUCCESS) && 
       (RegQueryValueEx(mq,L"HallDirectory",NULL,&rec,(LPBYTE)buf, &rbt) == ERROR_SUCCESS))
    {
        PathAppendW(buf, L"QQGwp.exe");

        QQGwpFullPath = buf;
        RegCloseKey(mq);
		}

    return !!PathFileExists(QQGwpFullPath.c_str());
	}

  bool GetQQGameHallInstallDir(std::wstring& QQGameHallInstallDir){
    HKEY mq;
    DWORD rec,rbt;
    rec = REG_SZ;
    rbt = MAX_PATH;

    wchar_t buf[MAX_PATH] = {0};
    long rs = RegOpenKeyEx(HKEY_CURRENT_USER, QQGAME_SUBKEY_PATH, 0,  KEY_ALL_ACCESS, &mq);
    if((rs==ERROR_SUCCESS) && 
      (RegQueryValueEx(mq,L"HallDirectory",NULL,&rec,(LPBYTE)buf, &rbt) == ERROR_SUCCESS))
    {
      QQGameHallInstallDir = buf;
      RegCloseKey(mq);
    }

    return !!PathFileExists(QQGameHallInstallDir.c_str());
  }


   bool LaunchQQGwpInternal(std::wstring& strExePath, const std::wstring& strParam)
   {
        std::wstring strCmdTemp = L"\"";
        strCmdTemp += strParam;
        strCmdTemp +=L"\"";
        
        HINSTANCE ret = (HINSTANCE)ShellExecute(NULL, L"open", strExePath.c_str(), strCmdTemp.c_str(), NULL, SW_SHOWNORMAL);
        return (DWORD)ret > 32 ? true : false;
   }

  bool GetQQGameCUVer(std::wstring& strCurVer)
  {
    std::wstring QQGameHallInstallPath;
    GetQQGameHallInstallDir(QQGameHallInstallPath);
    QQGameHallInstallPath +=L"\\";
    QQGameHallInstallPath += QQGAME_MALL_EXE;
	  DWORD dwHandle = 0;
	  DWORD dwSize = 0;
    dwSize = GetFileVersionInfoSize(QQGameHallInstallPath.c_str(),&dwHandle);
    if (!dwSize)
    {
      return false;
    }
    BYTE *Buf = new BYTE[dwSize];
    ZeroMemory(Buf,sizeof(BYTE)*dwSize);
    if (GetFileVersionInfo(QQGameHallInstallPath.c_str(),NULL,dwSize,Buf))
    {
      ATL::CStringW  szVersion;
      VS_FIXEDFILEINFO *pvi;
      VerQueryValue(Buf,_T("\\"),(LPVOID*)&pvi,(PUINT)&dwSize);
      if (dwSize)
      {
        szVersion.Format(L"%d.%d.%d.%d",HIWORD(pvi->dwFileVersionMS),LOWORD(pvi->dwFileVersionMS),
                         HIWORD(pvi->dwFileVersionLS), LOWORD(pvi->dwFileVersionLS));
      }
      if (szVersion.GetLength() > 0)
      {
        strCurVer.append(szVersion.GetBuffer(0));
      }
    }
    delete []Buf;
    return true;
  }

  bool GetPluginCUVer(std::wstring& strCurVer)
  {
    wchar_t system_buffer[MAX_PATH];
    system_buffer[0] = 0;
    HMODULE this_module = reinterpret_cast<HMODULE>(&__ImageBase);

    ::GetModuleFileName(this_module, system_buffer, MAX_PATH);

    DWORD dwHandle = 0;
    DWORD dwSize = 0;
    dwSize = GetFileVersionInfoSize(system_buffer,&dwHandle);
    if (!dwSize)
    {
      return false;
    }
    BYTE *Buf = new BYTE[dwSize];
    ZeroMemory(Buf,sizeof(BYTE)*dwSize);
    if (GetFileVersionInfo(system_buffer,NULL,dwSize,Buf))
    {
      ATL::CStringW  szVersion;
      VS_FIXEDFILEINFO *pvi;
      VerQueryValue(Buf,_T("\\"),(LPVOID*)&pvi,(PUINT)&dwSize);
      if (dwSize)
      {
        szVersion.Format(L"%d.%d.%d.%d",HIWORD(pvi->dwFileVersionMS),LOWORD(pvi->dwFileVersionMS),
          HIWORD(pvi->dwFileVersionLS), LOWORD(pvi->dwFileVersionLS));
      }
      if (szVersion.GetLength() > 0)
      {
        strCurVer.append(szVersion.GetBuffer(0));
      }
    }
    delete []Buf;
    return true;
  }

} //namespace