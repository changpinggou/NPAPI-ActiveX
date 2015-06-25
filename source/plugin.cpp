/*#include "StdAfx.h"*/
#include <Windowsx.h>
#include <windows.h>
#include <Shlwapi.h>
#include <ShlObj.h>
#include <shellapi.h>
#include <atlstr.h>



#include "launcherobj.h"
//#include "dispathcer.h"
#include "string_util.h"
#include "qqgame_util.h"

#pragma warning(disable: 4129)


extern HRESULT Query(/*[in]*/BSTR instr, /*[out]*/BSTR *outstr);

#ifdef XP_MAC
#include <TextEdit.h>
#endif

#ifdef XP_UNIX
#include <string.h>
#endif

#include "plugin.h"
/*#include "npfunctions.h"*/

static NPObject *sWindowObj;
TCHAR g_szQuery[1024] = {0};

static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  return DefWindowProc(hWnd, msg, wParam, lParam);
}


CPlugin::CPlugin(NPP pNPInstance) :
m_pNPInstance(pNPInstance),
m_pNPStream(NULL),
m_bInitialized(FALSE),
m_bAllow(false),
//m_lpOldProc(NULL),
m_pScriptableObject(NULL)
{
  m_hWnd = NULL;
  NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &sWindowObj);

// 	const char *ua = NPN_UserAgent(m_pNPInstance);
// 	strcpy_s(m_String, ua);
}

CPlugin::~CPlugin()
{
	if (sWindowObj)
		NPN_ReleaseObject(sWindowObj);
	if (m_pScriptableObject)
		NPN_ReleaseObject(m_pScriptableObject);

	sWindowObj = NULL;
}

void CPlugin::GetUrl()
{
	//获取Firefox地址栏上的url，因为有可能嵌套一层网页，所以要获得父窗口的url
	NPObject *tempObj = NULL;
	NPObject *locObj = NULL;
	NPVariant rval;
	NPIdentifier n;

	n = NPN_GetStringIdentifier("parent");
	NPN_GetProperty(m_pNPInstance, sWindowObj, n, &rval);

	/*在谷歌浏览器下每一次的tempObj多不一样，所以没办法退出循环，必须用iTimes强制退出循环，
	在火狐浏览器下是没这个问题的，*/
	int iTiems = 0;
	while(iTiems++ < 7 && NPVARIANT_IS_OBJECT(rval) && (tempObj = NPVARIANT_TO_OBJECT(rval)))
	{

		if (locObj == tempObj || tempObj == NULL)
		{
			break;
		}
		locObj = tempObj;
		n = NPN_GetStringIdentifier("parent");
		NPN_GetProperty(m_pNPInstance, tempObj, n, &rval);
  }

	if (NULL != locObj)
	{
		n = NPN_GetStringIdentifier("location");
		NPN_GetProperty(m_pNPInstance, locObj, n, &rval);
		locObj = NPVARIANT_TO_OBJECT(rval);

		n = NPN_GetStringIdentifier("href");
		NPN_GetProperty(m_pNPInstance, locObj, n, &rval);
		if (NPVARIANT_IS_STRING(rval)) 
		{
      m_url = rval.value.stringValue.utf8characters;
			NPN_ReleaseVariantValue(&rval);
		}
	}
}


NPBool CPlugin::init(NPWindow* pNPWindow)
{
  if(pNPWindow == NULL){
    return FALSE;
  }

  if (m_bInitialized){
    return TRUE;
  }
#ifdef _DEBUG
  ::MessageBox(NULL, L"CPlugin::init", L"CPlugin::init", MB_OK);
#endif

  m_hWnd = (HWND)pNPWindow->window;
  if(m_hWnd == NULL){
    return FALSE; 
  }

  //m_lpOldProc = SubclassWindow(m_hWnd, (WNDPROC)PluginWinProc);
  SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this); //has risk of null ptr when accessing userdata(this)


//   std::string strPlaySource = GetEmbedElementSrcAttr();
//   std::wstring wstrPlaySource = StringUtil::Utf8ToUnicode(strPlaySource.c_str());
//   //file:///C:/Users/applechang/AppData/Roaming/yfe/gjqx.mp4
//   //std::wstring::size_type  pos = wstrPlaySource.rfind(L"file:///");
//   //std::wstring disk_path = wstrPlaySource.rep
//   if (wstrPlaySource.find(L"file:///") != std::wstring::npos){
//     wstrPlaySource = wstrPlaySource.substr(8,wstrPlaySource.length() - 8);
//   }
//   //std::wstring wstrPlaySource = L"C:\\Users\\applechang\\AppData\\Roaming\\kanpian\\3.0.61.0\\plugins\\gjqx.mp4";
//   m_pCtrl->PlaySource(wstrPlaySource.c_str());
  m_Window = pNPWindow;
  m_bInitialized = TRUE;
  return TRUE;
}

void CPlugin::shut()
{
  //SubclassWindow(m_hWnd, m_lpOldProc);
  m_hWnd = NULL;
  m_bInitialized = FALSE;
}

NPBool CPlugin::isInitialized()
{
	return m_bInitialized;
}

int16 CPlugin::handleEvent(void* event)
{
#ifdef XP_MAC
	NPEvent* ev = (NPEvent*)event;
	if (m_Window) {
		Rect box = { m_Window->y, m_Window->x,
			m_Window->y + m_Window->height, m_Window->x + m_Window->width };
		if (ev->what == updateEvt) {
			::TETextBox(m_String, strlen(m_String), &box, teJustCenter);
		}
	}
#endif
	return 0;
}

// this will force to draw a version string in the plugin window
void CPlugin::showVersion()
{
	const char *ua = NPN_UserAgent(m_pNPInstance);
	strcpy_s(m_String, ua);

#ifdef XP_WIN
	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);
#endif

	if (m_Window) {
		NPRect r =
		{
			(uint16)m_Window->y, (uint16)m_Window->x,
			(uint16)(m_Window->y + m_Window->height),
			(uint16)(m_Window->x + m_Window->width)
		};

		NPN_InvalidateRect(m_pNPInstance, &r);
	}
}

// this will clean the plugin window
void CPlugin::clear()
{
	strcpy_s(m_String, "");

#ifdef XP_WIN
	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);
#endif
}

static NPObject *AllocateScriptablePluginObject(NPP npp, NPClass *aClass)
{
  return new ScriptablePluginObject(npp);
}

DECLARE_NPOBJECT_CLASS_WITH_BASE(ScriptablePluginObject, AllocateScriptablePluginObject);

NPObject *CPlugin::GetScriptableObject()
{
  if (!m_pScriptableObject) {
    m_pScriptableObject = NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(ScriptablePluginObject));
  }

  if (m_pScriptableObject) {
    NPN_RetainObject(m_pScriptableObject);
  }

  ((ScriptablePluginObject*)m_pScriptableObject)->SetAllow(m_bAllow);

  return m_pScriptableObject;
}

bool CPlugin::LaunchQQGameWithParam(const std::wstring& param){
  if (param.length() > QQGAME_MAX_PARAM_LENGTH){
	  NPN_SetException(m_pScriptableObject, "param exceed limit");
	  return false;
  }

  std::wstring strFullPath;
  if (!qqgame::GetQQGwpExePath(strFullPath)){
	  NPN_SetException(m_pScriptableObject, "QQGameHall doesn't exist");
	  return false;
  }

  if (!qqgame::LaunchQQGwpInternal(strFullPath, param)){
	  NPN_SetException(m_pScriptableObject, "launch failed");
	  return false;
  }

  return true;
}

bool CPlugin::GetQQGameHallVer(std::wstring& strCurVer){
  return qqgame::GetQQGameCUVer(strCurVer);
}


bool CPlugin::GetPluginVer(std::wstring& strCurVer){
  return qqgame::GetPluginCUVer(strCurVer);
}