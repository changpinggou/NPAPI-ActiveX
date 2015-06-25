#include "jsrunnerie.h"
#include "common/externalwrapper.h"

/*****************IInternetHostSecurityManager*******************/
STDMETHODIMP JsRunnerImpl::ProcessUrlAction(DWORD action, BYTE *policy,
                                            DWORD policy_size, BYTE *context,
                                            DWORD context_size, DWORD flags,
                                            DWORD reserved)
{
    *policy = URLPOLICY_DISALLOW;
    return S_FALSE;
}


STDMETHODIMP JsRunnerImpl::QueryCustomPolicy(REFGUID guid_key, BYTE **policy,
                                             DWORD *policy_size, BYTE *context,
                                             DWORD context_size, DWORD reserved) 
{
    return E_NOTIMPL;
}


STDMETHODIMP JsRunnerImpl::GetSecurityId(BYTE *security_id,
                                         DWORD *security_id_size,DWORD_PTR reserved) 
{
    return E_NOTIMPL;
}

// IActiveScriptSiteImpl overrid
STDMETHODIMP JsRunnerImpl::LookupNamedItem(const OLECHAR *name, IUnknown **item)
{
    NameToObjectMap::const_iterator found =
        global_name_to_object_.find(std::wstring(name));
    if (found == global_name_to_object_.end()) 
    {
        return TYPE_E_ELEMENTNOTFOUND;
    }

    found->second->AddRef();
    *item = found->second;
    return S_OK;
}

STDMETHODIMP JsRunnerImpl::HandleScriptError(EXCEPINFO *ei, ULONG line, LONG pos, BSTR src)
{
    return S_OK;
}


bool JsRunner_IE::Eval(const std::wstring &script)
{
    return false;
}

void JsRunner_IE::SetErrorHandler(void* error_handler)
{

}

JsObject *JsRunner_IE::NewObject(bool dump_on_error)
{
    return NULL;
}

JsObject *JsRunner_IE::NewError(const std::wstring &message,bool dump_on_error)
{
    return NULL;
}

JsArray* JsRunner_IE::NewArray()
{
    return NULL;
}

bool JsRunner_IE::InitializeModuleWrapper(ModuleImplBaseClass *module,
                                          DispatcherInterface *dispatcher,
                                          JsCallContextBase *context)
{
    CComObject<ExternalWrapper_IE> *module_wrapper;
    HRESULT hr = CComObject<ExternalWrapper_IE>::CreateInstance(&module_wrapper);
    if (FAILED(hr)) 
    {
        if (context) 
        {
            context->SetException(L"Module creation failed.");
        }

        return false;
    }

    module_wrapper->Init(module, dispatcher);
    module->SetJsWrapper(module_wrapper);
    return true;
}

bool JsRunner_IE::InvokeCallback(const JsCallBackFun* callback,
                                 int argc, JsParamToSend *argv,
                                 JsToken* retval,std::wstring* exception)
{

    return true;
}