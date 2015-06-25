#pragma once

#include "exdisp.h"

extern CString g_strLocationURL;
extern const GUID CLSID_FakeSite;

class ATL_NO_VTABLE CFakeSite :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFakeSite, &CLSID_FakeSite>,
	public IServiceProviderImpl<CFakeSite>,
	public IDispatchImpl<IWebBrowser2>
{
public:	
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister) { return S_OK; }

	BEGIN_COM_MAP(CFakeSite)
		COM_INTERFACE_ENTRY(IServiceProvider)
		COM_INTERFACE_ENTRY(IWebBrowser2)
	END_COM_MAP()

	BEGIN_SERVICE_MAP(CFakeSite)
		SERVICE_ENTRY(__uuidof(IWebBrowser2))
	END_SERVICE_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{}

	CFakeSite()	{}
	virtual ~CFakeSite(){}	

	HRESULT STDMETHODCALLTYPE get_LocationURL(BSTR *LocationURL)
	{	
		if ( NULL == LocationURL )
		{
			return E_INVALIDARG;
		}

		*LocationURL = g_strLocationURL.AllocSysString();
		return S_OK;
	}
	HRESULT STDMETHODCALLTYPE GoBack()
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE GoForward()
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE GoHome()
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE GoSearch()
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE Navigate(BSTR URL, VARIANT *Flags, VARIANT *TargetFrameName, VARIANT *PostData, VARIANT *Headers)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE Refresh()
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE Refresh2(VARIANT *Level)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE Stop()
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Application(IDispatch **ppDisp)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Parent(IDispatch **ppDisp)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Container(IDispatch **ppDisp)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Document(IDispatch **ppDisp)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_TopLevelContainer(VARIANT_BOOL *pBool)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Type(BSTR *Type)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Left(long *pl)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_Left(long Left)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Top(long *pl)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_Top(long Top)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Width(long *pl)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_Width(long Width)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Height(long *pl)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_Height(long Height)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_LocationName(BSTR *LocationName)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Busy(VARIANT_BOOL *pBool)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE Quit()
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE ClientToWindow(int *pcx, int *pcy)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE PutProperty(BSTR Property, VARIANT vtValue)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE GetProperty(BSTR Property, VARIANT *pvtValue)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Name(BSTR *Name)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_HWND(SHANDLE_PTR *pHWND)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_FullName(BSTR *FullName)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Path(BSTR *Path)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Visible(VARIANT_BOOL *pBool)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_Visible(VARIANT_BOOL Value)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_StatusBar(VARIANT_BOOL *pBool)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_StatusBar(VARIANT_BOOL Value)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_StatusText(BSTR *StatusText)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_StatusText(BSTR StatusText)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_ToolBar(int *Value)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_ToolBar(int Value)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_MenuBar(VARIANT_BOOL *Value)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_MenuBar(VARIANT_BOOL Value)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_FullScreen(VARIANT_BOOL *pbFullScreen)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_FullScreen(VARIANT_BOOL bFullScreen)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE Navigate2(VARIANT *URL, VARIANT *Flags, VARIANT *TargetFrameName, VARIANT *PostData, VARIANT *Headers)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE QueryStatusWB(OLECMDID cmdID, OLECMDF *pcmdf)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE ExecWB(OLECMDID cmdID, OLECMDEXECOPT cmdexecopt, VARIANT *pvaIn, VARIANT *pvaOut)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE ShowBrowserBar(VARIANT *pvaClsid, VARIANT *pvarShow, VARIANT *pvarSize)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_ReadyState(READYSTATE *plReadyState)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Offline(VARIANT_BOOL *pbOffline)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_Offline(VARIANT_BOOL bOffline)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Silent(VARIANT_BOOL *pbSilent)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_Silent(VARIANT_BOOL bSilent)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_RegisterAsBrowser(VARIANT_BOOL *pbRegister)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_RegisterAsBrowser(VARIANT_BOOL bRegister)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_RegisterAsDropTarget(VARIANT_BOOL *pbRegister)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_RegisterAsDropTarget(VARIANT_BOOL bRegister)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_TheaterMode(VARIANT_BOOL *pbRegister)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_TheaterMode(VARIANT_BOOL bRegister)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_AddressBar(VARIANT_BOOL *Value)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_AddressBar(VARIANT_BOOL Value)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE get_Resizable(VARIANT_BOOL *Value)
	{
		return E_NOTIMPL;
	}
	HRESULT STDMETHODCALLTYPE put_Resizable(VARIANT_BOOL Value)
	{
		return E_NOTIMPL;
	}
};

OBJECT_ENTRY_AUTO(CLSID_FakeSite, CFakeSite)