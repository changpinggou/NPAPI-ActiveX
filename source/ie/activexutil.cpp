#include <DispEx.h>
#include "activexutil.h"
#include "common/jsarray.h"

HRESULT ActiveXUtil::GetDispatchMemberId(IDispatch *dispatch, const WCHAR *name,
                                          DISPID *dispid) 
{
    *dispid = DISPID_UNKNOWN;
    return dispatch->GetIDsOfNames(IID_NULL, const_cast<WCHAR**>(&name), 1, 0,dispid);
}
HRESULT ActiveXUtil::GetDispatchProperty(IDispatch *dispatch, const WCHAR *name,
                                          VARIANT *value)
{
    DISPID dispid;
    HRESULT hr = GetDispatchMemberId(dispatch, name, &dispid);
    if (FAILED(hr)) return hr;
    return GetDispatchProperty(dispatch, dispid, value);
}

HRESULT ActiveXUtil::GetDispatchProperty(IDispatch *dispatch, DISPID dispid,
                                          VARIANT *value)
{
    assert(dispatch);
    assert(value);
    DISPPARAMS dispparams = { NULL, NULL, 0, 0 };
    return dispatch->Invoke(dispid, IID_NULL,LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET,
                            &dispparams, value, NULL, NULL);
}

HRESULT ActiveXUtil::AddAndSetDispatchProperty(IDispatch* dispatch,const WCHAR* name,
                                               const VARIANT *value)
{
    DISPID dispid;
    HRESULT hr = AddDispatchProperty(dispatch,name,&dispid);
    if (FAILED(hr))
    {
        return hr;
    }

    return SetDispatchProperty(dispatch,dispid,value);
}

HRESULT ActiveXUtil::AddDispatchProperty(IDispatch* dispatch,
                                    const WCHAR* name,DISPID* dispid) 
{
    CComQIPtr<IDispatchEx> dispatchex = dispatch;
    if (!dispatchex)
    {
        return E_NOINTERFACE;
    }

    return dispatchex->GetDispID(CComBSTR(name), fdexNameCaseSensitive | fdexNameEnsure, dispid);
}


HRESULT ActiveXUtil::SetDispatchProperty(IDispatch *dispatch, const WCHAR *name,
                                         const VARIANT *value) 
{
    DISPID dispid;
    HRESULT hr = dispatch->GetIDsOfNames(IID_NULL,const_cast<WCHAR**>(&name),1,0,&dispid);

    if (FAILED(hr)) 
    {
        return hr;
    }

    return SetDispatchProperty(dispatch, dispid, value);

}

HRESULT ActiveXUtil::SetDispatchProperty(IDispatch *dispatch, 
                                         DISPID dispid, const VARIANT *value)
{
    DISPPARAMS dispparams = {NULL, NULL, 1, 1};
    dispparams.rgvarg = const_cast<VARIANT*>(value);
    DISPID dispidPut = DISPID_PROPERTYPUT;
    dispparams.rgdispidNamedArgs = &dispidPut;

    WORD flags = (value->vt == VT_DISPATCH) ?
                  DISPATCH_PROPERTYPUTREF : 
                  DISPATCH_PROPERTYPUT;

    return dispatch->Invoke(dispid,IID_NULL,LOCALE_USER_DEFAULT,
                            flags,&dispparams,NULL,NULL,NULL);
}

bool ActiveXUtil::JsTokenIsObject(VARIANT t)
{
    return t.vt == VT_DISPATCH && t.pdispVal;
}

bool ActiveXUtil::JsTokenIsArray(VARIANT t)
{
    CComVariant out;
    if (FAILED(ActiveXUtil::GetDispatchProperty(t.pdispVal,std::wstring(L"join").c_str(),&out))) 
    {
        return false;
    }

    return true;
}

bool ActiveXUtil::JsTokenIsCallback(VARIANT t)
{
    CComVariant out;
    if (FAILED(ActiveXUtil::GetDispatchProperty(t.pdispVal,std::wstring(L"call").c_str(),&out))) 
    {
        return false;
    }

    return true;
}

JsParamType ActiveXUtil::JsTokenGetType(VARIANT t)
{
    if (t.vt == VT_BOOL) 
    {
        return JSPARAM_BOOL;
    } else if (t.vt == VT_I4) 
    {
        return JSPARAM_INT;
    } else if (t.vt == VT_R8) 
    {
        return JSPARAM_DOUBLE;
    } else if (t.vt == VT_BSTR) 
    {
        return JSPARAM_STRING16;
    } else if (t.vt == VT_NULL) 
    {
        return JSPARAM_NULL;
    } else if (t.vt == VT_EMPTY)
    {  // Must come after the previous test
        return JSPARAM_UNDEFINED;
    } else if (ActiveXUtil::JsTokenIsArray(t)) { 
        return JSPARAM_ARRAY;
    } else if (ActiveXUtil::JsTokenIsCallback(t)) {
        return JSPARAM_FUNCTION;
    } else if (ActiveXUtil::JsTokenIsObject(t)) {
        return JSPARAM_OBJECT;
    } else {
        return JSPARAM_UNKNOWN;  // Unsupported type
    }
}

bool ActiveXUtil::JsTokenToBool(VARIANT token,bool *out)
{
    if (token.vt != VT_BOOL) { return false; }
    *out = (token.boolVal == VARIANT_TRUE);

    return true;
}

bool ActiveXUtil::JsTokenToInt32(VARIANT token,int *out)
{
    if (token.vt != VT_I4) 
    {
        return false; 
    }
    *out = token.lVal;

    return true;
}

bool ActiveXUtil::JsTokenToDouble(VARIANT token,double *out)
{
    if (token.vt == VT_R8) 
    {
        *out = token.dblVal;
        return true;
    } else if (token.vt == VT_I4) 
    {
        *out = static_cast<double>(token.lVal);
        return true;
    }

    return true;
}

bool ActiveXUtil::JsTokenToString(VARIANT token,std::wstring *out)
{
    if (token.vt != VT_BSTR)
    {
        return false; 
    }

    if (!token.bstrVal) 
    {
        out->clear();
    } else {
        out->assign(token.bstrVal);
    }

    return true;
}

bool ActiveXUtil::JsTokenToArray(VARIANT token,JsArray **out)
{
    JsArray* newarr = new JsArray_IE(token);
    *out = newarr;

    return true;
}

bool ActiveXUtil::JsTokenToObject(VARIANT token,JsObject **out)
{
    JsObject* newobj = new JsObject_IE(token);
    *out = newobj;
    
    return true;
}

bool ActiveXUtil::JsTokenToFunction(VARIANT token,JsCallBackFun **out)
{
    JsCallBackFun* callback = new JsCallBackFunIE(token);
    *out = callback;

    return true;
}