#ifndef QQGAME_UTIL_H__
#define QQGAME_UTIL_H__
#include <string>
#include <Windows.h>

#define QQGAME_SUBKEY_PATH        L"Software\\TENCENT\\QQGame\\SYS"
#define WM_QQGAME_EXTERN_CMD      WM_USER + 234
#define QQGAME_EXTERN_CMD         234
#define QQGAME_MAINFRAME_WNDCLASS L"QQGame_MainFrame"
#define QQGAME_SETUP_WNDCLASS     L"GLBSWizard"
#define QQGAME_MALL_EXE           L"QQGame.exe"
#define QQGAME_HALL_MALL_EXE      L"QQGameHall.exe"

#define QQGAME_MAX_PARAM_LENGTH   4096


namespace qqgame
{
  bool CheckQQGameRunning(HWND* hMsgWnd);
  bool CheckQQGameSetup(HWND* hMsgWnd);
  bool GetQQGameHallInstallDir(std::wstring& QQGameHallInstallDir);
  bool GetQQGameCUVer(std::wstring& strCurVer); //get current user QQGameHall version
  bool GetPluginCUVer(std::wstring& strCurVer); //get current user plugin version
  bool GetQQGwpExePath(std::wstring& QQGwpFullPath);
  bool LaunchQQGwpInternal(std::wstring& strExePath, const std::wstring& strParam);
} //namespace

#endif //QQGAME_UTIL_H__