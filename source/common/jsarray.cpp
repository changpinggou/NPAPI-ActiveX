#include "common/jsobject.h"
#include "jsarray.h"
#include "ie/activexutil.h"

JsParamType JsArray_IE::GetElementType(int index)
{
    CComVariant out;
    GetElement(index,&out);
    return ActiveXUtil::JsTokenGetType(out);
}

bool JsArray_IE::GetElement(int index, CComVariant* out)
{
    wchar_t strIndex[20]= {0};
    swprintf_s(strIndex,sizeof(strIndex)/sizeof(wchar_t), L"%d", index);
    
    HRESULT hr = ActiveXUtil::GetDispatchProperty(array_.pdispVal,strIndex,out);
    if (SUCCEEDED(hr))
    {
        return true;
    }else if(hr == DISP_E_UNKNOWNNAME){
        out->Clear();
    }

    return false;
}

bool JsArray_IE::SetElement(int index, const CComVariant &token)
{
    wchar_t strIndex[20]= {0};
    swprintf_s(strIndex,sizeof(strIndex)/sizeof(wchar_t), L"%d", index);

    HRESULT hr = ActiveXUtil::SetDispatchProperty(array_.pdispVal,strIndex,&token);
    if (FAILED(hr))
    {
        return false;
    }
    return true;
}

bool JsArray_IE::GetLength(int *length)
{
    if (!ActiveXUtil::JsTokenIsArray(array_))
    {
        return false;
    }

    CComVariant out;
    if (FAILED(ActiveXUtil::GetDispatchProperty(array_.pdispVal,L"length",&out)))
    {
        return false;

    }

    if (out.vt != VT_I4) return false;

    *length = out.lVal;

    return true;
}

bool JsArray_IE::GetElementAsBool(int index, bool *out)
{
    CComVariant token;
    if (!GetElement(index, &token))
    {
        return false;
    }

    return ActiveXUtil::JsTokenToBool(token,out);
}

bool JsArray_IE::GetElementAsInt(int index, int *out)
{
    CComVariant token;
    if (!GetElement(index, &token))
    {
        return false;
    }

    return ActiveXUtil::JsTokenToInt32(token,out);
}

bool JsArray_IE::GetElementAsDouble(int index, double *out)
{
    CComVariant token;
    if (!GetElement(index, &token))
    {
        return false;
    }

    return ActiveXUtil::JsTokenToDouble(token,out);
}

bool JsArray_IE::GetElementAsString(int index, std::wstring *out)
{
    CComVariant token;
    if (!GetElement(index, &token))
    {
        return false;
    }

    return ActiveXUtil::JsTokenToString(token,out);
}

bool JsArray_IE::GetElementAsArray(int index, JsArray **out)
{
    CComVariant token;
    if (!GetElement(index, &token))
    {
        return false;
    }
    
    return ActiveXUtil::JsTokenToArray(token,out);
}

bool JsArray_IE::GetElementAsObject(int index, JsObject **out)
{
    CComVariant token;
    if (!GetElement(index, &token))
    {
        return false;
    }

    return ActiveXUtil::JsTokenToObject(token,out);
}

bool JsArray_IE::GetElementAsFunction(int index,JsCallBackFun **out)
{
    CComVariant token;
    if (!GetElement(index, &token))
    {
        return false;
    }

    return ActiveXUtil::JsTokenToFunction(token,out);
}

bool JsArray_IE::SetElementBool(int index, bool value)
{
    CComVariant token(value);
    return SetElement(index,token);
}

bool JsArray_IE::SetElementInt(int index, int value)
{
    CComVariant token(value);
    return SetElement(index,token);
}

bool JsArray_IE::SetElementDouble(int index, double value)
{
    CComVariant token(value);
    return SetElement(index,token);
}

bool JsArray_IE::SetElementString(int index, const std::wstring &value)
{
    CComVariant token(value.c_str());
    return SetElement(index,token);
}

bool JsArray_IE::SetElementArray(int index, JsArray *value)
{
    return true;
}

bool JsArray_IE::SetElementObject(int index, JsObject *value)
{
    return true;
}

bool JsArray_IE::SetElementFunction(int index, JsCallBackFun *value)
{
    return true;
}

bool JsArray_IE::SetElementModule(int index, ModuleImplBaseClass *value)
{
    return true;
}

bool JsArray_IE::SetElementNull(int index)
{
    return true;
}

bool JsArray_IE::SetElementUndefined(int index)
{
    return true;
}