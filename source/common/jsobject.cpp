#include <assert.h>

#include "jsobject.h"
#include "ie/activexutil.h"

// JsToken* JsObject_IE::token()
// {
//     //JsToken *token = new JsTokenIE()
// }

bool JsObject_IE::Initialize(JsToken *value, JsContextPtr context)
{
    if (!value)
    {
        return false;
    }

    value->TokenToVariant(&token_);
    
    return true;
}

bool JsObject_IE::GetPropertyAsBool(const std::wstring &name,bool *out)
{
    CComVariant token;
    if (!GetProperty(name, &token)) return false;

    return ActiveXUtil::JsTokenToBool(token,out);
}

bool JsObject_IE::GetPropertyAsInt(const std::wstring &name,int *out)
{
    CComVariant token;

    if (!GetProperty(name,&token))
    {
        return false;
    }

    return ActiveXUtil::JsTokenToInt32(token,out);
}

bool JsObject_IE::GetPropertyAsDouble(const std::wstring &name,double *out)
{
    CComVariant token;

    if (!GetProperty(name,&token))
    {
        return false;
    }

    return ActiveXUtil::JsTokenToDouble(token,out);
}

bool JsObject_IE::GetPropertyAsString(const std::wstring &name,std::wstring *out)
{
    CComVariant token;

    if (!GetProperty(name,&token))
    {
        return false;
    }

    return ActiveXUtil::JsTokenToString(token,out);
}

bool JsObject_IE::GetPropertyAsArray(const std::wstring &name,JsArray **out)
{
    return true;
}

bool JsObject_IE::GetPropertyAsObject(const std::wstring &name,JsObject **out)
{
    return true;
}

bool JsObject_IE::GetPropertyAsFunction(const std::wstring &name,JsCallBackFun **out)
{
    CComVariant token;
    if (!GetProperty(name, &token))
    {
        return false;
    }
    
    return ActiveXUtil::JsTokenToFunction(token,out);
}

JsParamType JsObject_IE::GetPropertyType(const std::wstring &name)
{
    CComVariant token;
    if (!GetProperty(name, &token)) return JSPARAM_UNKNOWN;

    return ActiveXUtil::JsTokenGetType(token);
}

bool JsObject_IE::GetPropertyNames(std::vector<std::wstring> *out)
{
    return true;
}

bool JsObject_IE::SetPropertyBool(const std::wstring& name,bool value)
{
    return true;
}

bool JsObject_IE::SetPropertyInt(const std::wstring &name,int value)
{
    return true;
}

bool JsObject_IE::SetPropertyDouble(const std::wstring& name,double value)
{
    return true;
}

bool JsObject_IE::SetPropertyString(const std::wstring &name,
                               const std::wstring &value)
{
    return true;
}
bool JsObject_IE::SetPropertyArray(const std::wstring& name,
                              JsArray* value)
{
    return true;
}

bool JsObject_IE::SetPropertyObject(const std::wstring& name,
                               JsObject* value)
{
    return true;
}

bool JsObject_IE::SetPropertyFunction(const std::wstring& name,
                                 JsCallBackFun* value)
{
    return true;
}

bool JsObject_IE::SetPropertyModule(const std::wstring& name,
                               ModuleImplBaseClass* value)
{
    return true;
}

bool JsObject_IE::SetPropertyNull(const std::wstring &name)
{
    return true;
}

bool JsObject_IE::SetPropertyUndefined(const std::wstring &name)
{
    return true;
}
//      bool SetPropertyMarshaledJsToken(
//         const std::wstring& name,
//         ModuleEnvironment* module_environment,
//         MarshaledJsToken* value);

// const JsScopedToken& JsObject_IE::token()
// {
// }

 bool JsObject_IE::GetProperty(const std::wstring &name,CComVariant *value)
 {
     if (token_.vt != VT_DISPATCH || !token_.pdispVal)
     {
         return false;
     }

     // If the property name is unknown, GetDispatchProperty will return
     // DISP_E_UNKNOWNNAME and out will be unchanged.
     HRESULT hr = ActiveXUtil::GetDispatchProperty(token_.pdispVal,name.c_str(),value);
     if (DISP_E_UNKNOWNNAME == hr) {
         // Set the token to the equivalent of JSPARAM_UNDEFINED.
         value->Clear();
         return true;
     }

     return SUCCEEDED(hr);
 }

 bool JsObject_IE::SetProperty(const std::wstring &name,const JsToken &value)
 {
     return true;
 }