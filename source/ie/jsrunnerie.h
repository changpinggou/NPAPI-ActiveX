#ifndef WEBAPP_JS_RUNNER_IE_H__
#define WEBAPP_JS_RUNNER_IE_H__

#include <activscp.h>
#include <string>
#include <assert.h>
#include <atlbase.h>
#include <atlcom.h>
#include <map>

#include "common/baseclass.h"

typedef wchar_t char16;

class ATL_NO_VTABLE IActiveScriptSiteImpl : public IActiveScriptSite
{
public:
	STDMETHOD(GetLCID)(LCID *plcid)
	{
		*plcid = LOCALE_SYSTEM_DEFAULT;
		return NOERROR;
	};

	STDMETHOD(GetItemInfo)(LPCOLESTR pstrName,DWORD dwMask,LPUNKNOWN* ppunkItem,LPTYPEINFO* ppTypeInfo)
	{
		CComPtr<IUnknown> spUnk;
        HRESULT hr = LookupNamedItem(pstrName,&spUnk);
        if (FAILED(hr))
        {
            return hr;
        }

		if(dwMask & SCRIPTINFO_ITYPEINFO) {
			CComPtr<ITypeInfo> spTI;
			CComQIPtr<IProvideClassInfo> spPCI = spUnk;
			if(!!spPCI) {
				// Got IProvideClassInfo interface so use it
                hr = spPCI->GetClassInfo(&spTI);
                if (FAILED(hr))
                {
                    return hr;
                }
				spPCI.Release();
			} else {
				// Try for IDispatch::GetTypeInfo
				CComQIPtr<IDispatch> spDisp = spUnk;
				if(!!spDisp) {
                    hr = spDisp->GetTypeInfo(0,LOCALE_SYSTEM_DEFAULT,&spTI);
                    if (FAILED(hr))
                    {
                        return hr;
                    }
					spDisp.Release();
				}
			}
			*ppTypeInfo = spTI.Detach();
		}

		if(dwMask & SCRIPTINFO_IUNKNOWN) {
			*ppunkItem = spUnk.Detach();
		}

		return NOERROR;
	}

	STDMETHOD(GetDocVersionString)(BSTR *pbstrversionString)
	{
// 		if(pbstrversionString==NULL)
// 			return E_POINTER;
// 		USES_CONVERSION;
// 		*pbstrversionString = ::SysAllocString(T2OLE(SCRIPTSITE_APPNAME));
		return NOERROR;
	};

	// This method is called when the script engine terminates
	STDMETHOD(OnScriptTerminate)(const VARIANT* /*pvarResult*/,const EXCEPINFO* /*pexcepinfo*/)
	{
		return NOERROR;
	};

	// This method is called when the script engine's state is changed
	STDMETHOD(OnStateChange)(SCRIPTSTATE /*ssScriptState*/)
	{
		return NOERROR;
	};

	// This method is called when the script engine wants to report an error to the user
	STDMETHOD(OnScriptError)(IActiveScriptError* pase)
	{
		if(pase==NULL)
        {
            return E_POINTER;
        }

		EXCEPINFO ei;
        HRESULT hr = pase->GetExceptionInfo(&ei);
        if(FAILED(hr))
        {
            return hr;
        }

// 		if(ei.pfnDeferredFillIn!=NULL) 
//         {
// 
// 			HR((*ei.pfnDeferredFillIn)(&ei));
// 		}

		DWORD dwContext = 0;
		ULONG ulLine = 0;
		LONG lPos = 0;
		pase->GetSourcePosition(&dwContext,&ulLine,&lPos);
		CComBSTR src;
		pase->GetSourceLineText(&src);
		return HandleScriptError(&ei,ulLine,lPos,src);
	}

	// This method is called when (before) the script engine starts executing the script/event handler
	STDMETHOD(OnEnterScript)(void)
	{
		return NOERROR;
	};

	// This method is called when (after) the script engine finishes executing the script/event handler
	STDMETHOD(OnLeaveScript)(void)
	{
		return NOERROR;
	};

	STDMETHOD(LookupNamedItem)(LPCOLESTR pstrName,LPUNKNOWN* ppunkItem)
	{
		return TYPE_E_ELEMENTNOTFOUND;
	}

	STDMETHOD(HandleScriptError)(EXCEPINFO* pei,ULONG ulLine,LONG lPos,BSTR src)
	{
		return NOERROR;
	}
};

class ATL_NO_VTABLE JsRunnerImpl: 
    public CComObjectRootEx<CComMultiThreadModel>,
    public IDispatchImpl<IDispatch>,
    public IActiveScriptSiteImpl,
    public IInternetHostSecurityManager,
    public IServiceProviderImpl<JsRunnerImpl>
{
public:
    BEGIN_COM_MAP(JsRunnerImpl)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IActiveScriptSite)
        COM_INTERFACE_ENTRY(IInternetHostSecurityManager)
        COM_INTERFACE_ENTRY(IServiceProvider)
    END_COM_MAP()

    BEGIN_SERVICE_MAP(JsRunnerImpl)
        SERVICE_ENTRY(SID_SInternetHostSecurityManager)
    END_SERVICE_MAP()

    JsRunnerImpl() : coinit_succeeded_(false) {}
    ~JsRunnerImpl();
    // JsRunner implementation
    bool AddGlobal(const std::wstring &name, IUnknown *object);
    bool Start(const std::wstring &full_script);
    bool Start(const std::wstring &name, const std::wstring &full_script);
    bool Stop();
    bool Eval(const std::wstring &script);
    
//     void SetErrorHandler(JsErrorHandlerInterface *error_handler) 
//     {
//         error_handler_ = error_handler;
//     }

    bool CleanUpJsGlobalVariables();

    // IActiveScriptSiteImpl overrides
    STDMETHOD(LookupNamedItem)(const OLECHAR *name, IUnknown **item);
    STDMETHOD(HandleScriptError)(EXCEPINFO *ei, ULONG line, LONG pos, BSTR src);

    // Implement IInternetHostSecurityManager. We use this to prevent the script
    // engine from creating ActiveX objects, using Java, using scriptlets and
    // various other questionable activities.
    STDMETHOD(GetSecurityId)(BYTE *securityId, DWORD *securityIdSize,
        DWORD_PTR reserved);
    STDMETHOD(ProcessUrlAction)(DWORD action, BYTE *policy, DWORD policy_size,
        BYTE *context, DWORD context_size, DWORD flags,
        DWORD reserved);
    STDMETHOD(QueryCustomPolicy)(REFGUID guid_key, BYTE **policy,
        DWORD *policy_size, BYTE *context,
        DWORD context_size, DWORD reserved);
private:
    CComPtr<IActiveScript> javascript_engine_;
    //JsErrorHandlerInterface *error_handler_;

    typedef std::map<std::wstring, IUnknown *> NameToObjectMap;
    NameToObjectMap global_name_to_object_;

    bool coinit_succeeded_;
};

class JsRunner_IE : public JsRunnerInterface
{
public:
    virtual bool Eval(const std::wstring &script);
    virtual void SetErrorHandler(void* error_handler);
    virtual JsObject *NewObject(bool dump_on_error = false);
    virtual JsObject *NewError(const std::wstring &message,bool dump_on_error = false);
    virtual JsArray* NewArray();

    virtual bool InitializeModuleWrapper(ModuleImplBaseClass *module,
        DispatcherInterface *dispatcher,
        JsCallContextBase *context);

    virtual bool InvokeCallback(const JsCallBackFun* callback,
        int argc, JsParamToSend *argv,
        JsToken* retval,std::wstring* exception);
};

#endif //WEBAPP_JS_RUNNER_IE_H__