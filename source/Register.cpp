
#include "define.h"
#include "dllmain.h"

#define STRING_REG_NPQSCALL _T("SOFTWARE\\MozillaPlugins\\@qq.com/npQQGameAssist")
#define STRING_REG_NPQSCALL_DESCRIPTION _T("Description")
#define STRING_REG_NPQSCALL_DESCRIPTION_VALUE _T("npQQGameAssist")
#define STRING_REG_NPQSCALL_PATH _T("Path")
#define STRING_REG_NPQSCALL_VENDER _T("Vender")
#define STRING_REG_NPQSCALL_VENDER_VALUE _T("Tencent, Inc.")
#define STRING_REG_NPQSCALL_MIMETYPES_APPLICATIONQSCALLPLUGIN _T("SOFTWARE\\MozillaPlugins\\@qq.com/npQQGameAssist\\MimeTypes\\application/x-QGAssist")

#define QGASSIST_ACTIVEX_SUB_KEY L"QQGameHall.Assist"
#define QGASSIST_ACTIVEX_SUB_GUID_SUB_KEY L"QQGameHall.Assist\\CLSID"
#define QGASSIST_ACTIVEX_SUB_CURVER_SUB_KEY L"QQGameHall.Assist\\CurVer"

#define QGASSIST_ACTIVEX_VER_SUB_KEY L"QQGameHall.Assist.1"
#define QGASSIST_ACTIVEX_VER_SUB_GUID_SUB_KEY L"QQGameHall.Assist.1\\CLSID"
#define QGASSIST_ACTIVEX_GUID L"{10C3DA1D-B8AA-4e0a-9612-D051649B660C}"

#define QGASSIST_ACTIVEX_GUID_SUB_KEY L"CLSID\\{10C3DA1D-B8AA-4e0a-9612-D051649B660C}"
#define QGASSIST_ACTIVEX_InprocServer32_SUB_KEY L"CLSID\\{10C3DA1D-B8AA-4e0a-9612-D051649B660C}\\InprocServer32"

HINSTANCE g_hDll = NULL;
CQQGameAssistPluginModule _AtlModule;

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_hDll = hInstance;
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
	}
	return _AtlModule.DllMain(dwReason, lpReserved); 
}

// 返回一个类工厂以创建所请求类型的对象
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllRegisterServer()
{
	HRESULT hr = _AtlModule.DllRegisterServer();
	HRESULT hrRet = E_FAIL;
 
	HKEY hSubKey = NULL;
	LONG lRet = RegCreateKey( HKEY_LOCAL_MACHINE, STRING_REG_NPQSCALL, &hSubKey );

	if ( ERROR_SUCCESS == lRet )
	{
		RegSetValueEx( hSubKey, STRING_REG_NPQSCALL_DESCRIPTION, 0, REG_SZ, (CONST BYTE *)STRING_REG_NPQSCALL_DESCRIPTION_VALUE, sizeof(STRING_REG_NPQSCALL_DESCRIPTION_VALUE) );
		RegSetValueEx( hSubKey, STRING_REG_NPQSCALL_VENDER, 0, REG_SZ, (CONST BYTE *)STRING_REG_NPQSCALL_VENDER_VALUE, sizeof(STRING_REG_NPQSCALL_VENDER_VALUE) );

		TCHAR szPath[MAX_PATH] = {0};
		DWORD dwCount = GetModuleFileName( g_hDll, szPath, MAX_PATH );
		RegSetValueEx( hSubKey, STRING_REG_NPQSCALL_PATH, 0, REG_SZ, (CONST BYTE *)szPath, dwCount * sizeof(TCHAR) );

		RegCloseKey( hSubKey );

		lRet = RegCreateKey( HKEY_LOCAL_MACHINE, STRING_REG_NPQSCALL_MIMETYPES_APPLICATIONQSCALLPLUGIN, &hSubKey );
		if ( ERROR_SUCCESS == lRet )
		{
			RegSetValueEx( hSubKey, STRING_REG_NPQSCALL_DESCRIPTION, 0, REG_SZ, (CONST BYTE *)STRING_REG_NPQSCALL_DESCRIPTION_VALUE, sizeof(STRING_REG_NPQSCALL_DESCRIPTION_VALUE) );
			RegCloseKey( hSubKey );
			hrRet = S_OK;
		}
	}

	//ActiveX QQGameHall.Assist
	hSubKey = NULL;
	RegCreateKey(HKEY_CLASSES_ROOT, QGASSIST_ACTIVEX_SUB_KEY, &hSubKey );
    lRet = RegCreateKey(HKEY_CLASSES_ROOT, QGASSIST_ACTIVEX_SUB_GUID_SUB_KEY, &hSubKey);
	if (ERROR_SUCCESS == lRet)
	{
		RegSetValueEx( hSubKey, NULL, 0, REG_SZ, (CONST BYTE *)QGASSIST_ACTIVEX_GUID, sizeof(QGASSIST_ACTIVEX_GUID) );
	}

	lRet = RegCreateKey(HKEY_CLASSES_ROOT, QGASSIST_ACTIVEX_SUB_CURVER_SUB_KEY, &hSubKey);
	if (ERROR_SUCCESS == lRet)
	{
		RegSetValueEx( hSubKey, NULL, 0, REG_SZ, (CONST BYTE *)QGASSIST_ACTIVEX_VER_SUB_KEY, sizeof(QGASSIST_ACTIVEX_VER_SUB_KEY) );
	}

    //QQGameHall.Assist.1

	RegCreateKey(HKEY_CLASSES_ROOT, QGASSIST_ACTIVEX_VER_SUB_KEY, &hSubKey);
	lRet = RegCreateKey(HKEY_CLASSES_ROOT, QGASSIST_ACTIVEX_VER_SUB_GUID_SUB_KEY, &hSubKey);
	if (ERROR_SUCCESS == lRet)
	{
		RegSetValueEx( hSubKey, NULL, 0, REG_SZ, (CONST BYTE *)QGASSIST_ACTIVEX_GUID, sizeof(QGASSIST_ACTIVEX_GUID) );
	}


	return hrRet;
}

STDAPI DllUnregisterServer()
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	HRESULT hrRet = E_FAIL;

	LONG lRet = RegDeleteKey( HKEY_LOCAL_MACHINE, STRING_REG_NPQSCALL );
	if ( ERROR_SUCCESS == lRet )
	{
		hrRet = S_OK;
	}

	return hrRet;
}

//检查插件注册表的完整性
STDAPI DLLCheckRegistry()
{
	HKEY hk = NULL;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, STRING_REG_NPQSCALL, 0, KEY_READ, &hk) != 0 ||
		RegOpenKeyEx(HKEY_CLASSES_ROOT,QGASSIST_ACTIVEX_SUB_KEY, 0, KEY_READ, &hk) != 0 || 
		RegOpenKeyEx(HKEY_CLASSES_ROOT,QGASSIST_ACTIVEX_VER_SUB_KEY,0, KEY_READ, &hk) !=0 ||
		RegOpenKeyEx(HKEY_CLASSES_ROOT,QGASSIST_ACTIVEX_GUID_SUB_KEY,0, KEY_READ, &hk) !=0 ||
		RegOpenKeyEx(HKEY_CLASSES_ROOT,QGASSIST_ACTIVEX_InprocServer32_SUB_KEY,0, KEY_READ, &hk) !=0)
	{
		/*    DllRegisterServer();*/
		return E_FAIL;
	}

	return S_OK;
}

