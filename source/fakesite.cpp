#include "plugin.h"
#include "define.h"
#include "Common/Include/Log.h"
#include "Common/Include/UtilCoreConvert.h"
#include "npupp.h"
#include "windowsx.h"
#include "qscall_spobject.h"
#include "WinInet.h"

#pragma comment (lib, "wininet.lib")

//#define ENABLE_LOCAL_FILE_CREATE_OBJECT

#define ARRAY_SIZE(a) (sizeof (a) / sizeof (a[0]))
#define APPROVED_DOMAIN_COUNT  7
char* _approvedDomains[APPROVED_DOMAIN_COUNT] = { "qq.com", "paipai.com", "tencent.com", "soso.com", "taotao.com", "tenpay.com", "foxmail.com" };

#define LOGFILTER	L"CPlugin"

CPlugin::CPlugin(NPP pNPInstance) :
m_pNPInstance(pNPInstance),
m_pNPStream(NULL),
m_bInitialized(FALSE),
m_pScriptableObject(NULL)
{
#ifdef XP_WIN
	m_hWnd = NULL;
#endif
}

CPlugin::~CPlugin()
{
	if (m_pScriptableObject)
		NPN_ReleaseObject(m_pScriptableObject);
}

#ifdef XP_WIN
	static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);
	static WNDPROC lpOldProc = NULL;
#endif

	bool MatchDomains(char* approvedDomain, char* ourDomain)
	{
		int apDomLen  = lstrlenA(approvedDomain);
		int ourDomLen = lstrlenA(ourDomain);

		if ( apDomLen > ourDomLen )
			return false;

		if ( lstrcmpiA(ourDomain + ourDomLen - apDomLen, approvedDomain) != 0)
			return false;

		if ( apDomLen == ourDomLen )
			return true;

		if ( ourDomain[ourDomLen - apDomLen - 1] == '.' )
			return true;

		return false;
	}

	INTERNET_SCHEME GetScheme(const char* url)
	{
		char buf[64];

		URL_COMPONENTSA uc;
		ZeroMemory(&uc, sizeof (uc));

		uc.dwStructSize = sizeof (uc);
		uc.lpszScheme = buf;
		uc.dwSchemeLength = sizeof (buf);

		if ( InternetCrackUrlA(url, ::lstrlenA(url), ICU_DECODE, &uc) )
			return uc.nScheme;
		else
			return INTERNET_SCHEME_UNKNOWN;
	}

	bool GetDomain(const char* url, char* buf, int cbBuf)
	{
		URL_COMPONENTSA uc;
		ZeroMemory(&uc, sizeof (uc));

		uc.dwStructSize = sizeof (uc);
		uc.lpszHostName = buf;
		uc.dwHostNameLength = cbBuf;

		return !!InternetCrackUrlA(url, lstrlenA(url), ICU_DECODE, &uc);
	}

	bool IsApprovedDomain(const char* ourUrl)
	{
		INTERNET_SCHEME ourScheme = GetScheme(ourUrl);

#ifdef ENABLE_LOCAL_FILE_CREATE_OBJECT
		if ( ourScheme == INTERNET_SCHEME_FILE )
			return true;
#endif

		if ( ourScheme != INTERNET_SCHEME_HTTP 
			&& ourScheme != INTERNET_SCHEME_HTTPS )
			return false;

		char ourDomain[INTERNET_MAX_URL_LENGTH];
		if ( !GetDomain(ourUrl, ourDomain, sizeof (ourDomain)) )
			return false;

		for (int i = 0; i < ARRAY_SIZE(_approvedDomains); ++i)
		{
			if ( MatchDomains(_approvedDomains[i], ourDomain) )
			{
				return true;
			}
		}

		return false;
	}

NPBool CPlugin::init(NPWindow* pNPWindow)
{
	if ( pNPWindow == NULL )
		return PR_FALSE;

	//测试是否是限制域：
	NPObject *sW = NULL;
	NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &sW);
	if ( sW == NULL )
	{
		return PR_FALSE;
	}

	NPVariant variantValue;
	if ( NPN_GetProperty(m_pNPInstance, sW, NPN_GetStringIdentifier("location"), &variantValue) )
	{
		NPN_ReleaseObject(sW);

		NPVariant variantValue2;
		if ( NPN_GetProperty( m_pNPInstance, NPVARIANT_TO_OBJECT(variantValue), NPN_GetStringIdentifier("href"), &variantValue2) )
		{
			const NPUTF8 * szHref = NPVARIANT_TO_STRING(variantValue2).utf8characters;
			if ( IsApprovedDomain(szHref) )
			{				
				NPN_ReleaseVariantValue(&variantValue);
				NPN_ReleaseVariantValue(&variantValue2);				
			}
			else
			{
				TXLog2(LOGFILTER, L"%s is not approved domains", (LPCTSTR)Util::Convert::Utf8ToWS(szHref));				
				NPN_ReleaseVariantValue(&variantValue);
				NPN_ReleaseVariantValue(&variantValue2);
				return PR_FALSE;
			}
		}
		else
		{
			NPN_ReleaseVariantValue(&variantValue);
			return PR_FALSE;
		}
	}

#ifdef XP_WIN
	m_hWnd = (HWND)pNPWindow->window;
	if(m_hWnd == NULL)
		return FALSE;

	// subclass window so we can intercept window messages and
	// do our drawing to it
	lpOldProc = SubclassWindow(m_hWnd, (WNDPROC)PluginWinProc);

	// associate window with our CPlugin object so we can access 
	// it in the window procedure
	SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
#endif

	m_Window = pNPWindow;
	m_bInitialized = TRUE;

	return TRUE;
}

void CPlugin::shut()
{
#ifdef XP_WIN
	// subclass it back
	SubclassWindow(m_hWnd, lpOldProc);
	m_hWnd = NULL;
#endif
	m_bInitialized = FALSE;
}

NPBool CPlugin::isInitialized()
{
	return m_bInitialized;
}

int16 CPlugin::handleEvent(void* event)
{
	return 0;
}

NPObject *
CPlugin::GetScriptableObject()
{
	if (!m_pScriptableObject) 
	{
		m_pScriptableObject = NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(QscallSPObject));
	}

	if (m_pScriptableObject) 
	{
		NPN_RetainObject(m_pScriptableObject);
	}

	return m_pScriptableObject;
}

#ifdef XP_WIN
static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
#endif
