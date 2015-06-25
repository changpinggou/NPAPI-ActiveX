#ifndef WEBAPP_ACTIVEX_UTIL_H__
#define WEBAPP_ACTIVEX_UTIL_H__

#include <activscp.h>
#include <string>
#include <assert.h>
#include <atlbase.h>
#include <atlcom.h>
#include "common/baseclass.h"

class ActiveXUtil
{
public:
    static HRESULT GetDispatchMemberId(IDispatch *dispatch, const WCHAR *name,
                                       DISPID *dispid);
    static HRESULT GetDispatchProperty(IDispatch *dispatch, const WCHAR *name,
                                       VARIANT *value);
    static HRESULT GetDispatchProperty(IDispatch *dispatch, DISPID dispid,
                                       VARIANT *value);

    static HRESULT AddAndSetDispatchProperty(IDispatch* dispatch,const WCHAR* name,
                                             const VARIANT *value);

    static HRESULT AddDispatchProperty(IDispatch* dispatch,
                                       const WCHAR* name,DISPID* dispid);
    static HRESULT SetDispatchProperty(IDispatch *dispatch, const WCHAR *name,
                                       const VARIANT *value);
    static HRESULT SetDispatchProperty(IDispatch *dispatch, 
                                       DISPID dispid, const VARIANT *value);


    static bool JsTokenIsObject(VARIANT t);
    static bool JsTokenIsArray(VARIANT t);
    static bool JsTokenIsCallback(VARIANT t);

    static JsParamType JsTokenGetType(VARIANT t);

    static bool JsTokenToBool(VARIANT token,bool *out);
    static bool JsTokenToInt32(VARIANT token,int *out);
    static bool JsTokenToDouble(VARIANT token,double *out);
    static bool JsTokenToString(VARIANT token,std::wstring *out);
    static bool JsTokenToArray(VARIANT token,JsArray **out);
    static bool JsTokenToObject(VARIANT token,JsObject **out);
    static bool JsTokenToFunction(VARIANT token,JsCallBackFun **out);
};

#endif //WEBAPP_ACTIVEX_UTIL_H__