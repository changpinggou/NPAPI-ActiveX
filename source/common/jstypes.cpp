#include "jstypes.h"
#include "jsobject.h"
#include "baseclass.h"

bool ConvertJsParamToVariant(const JsParamToSend &param, CComVariant *token)
{
    switch (param.type) 
    {
    case JSPARAM_BOOL: 
        {
            const bool *value = static_cast<const bool *>(param.value_ptr);
            *token = *value;  // CComVariant understands 'bool'
            break;
        }
    case JSPARAM_INT: 
        {
            const int *value = static_cast<const int *>(param.value_ptr);
            *token = *value;  // CComVariant understands 'int'
            break;
        }
    case JSPARAM_INT64: 
        {
            const double *dvalue = static_cast<const double *>(param.value_ptr);
            *token = *dvalue;  // CComVariant understands 'double'
            break;

        }
    case JSPARAM_DOUBLE: 
        {
            const double *value = static_cast<const double *>(param.value_ptr);
            *token = *value;  // CComVariant understands 'double'
            break;                 
        }
    case JSPARAM_STRING16: 
        {
            const std::wstring *value = static_cast<const std::wstring *>(param.value_ptr);
            *token = value->c_str();  // copies 'wchar*' for us
            break;
        }
    case JSPARAM_OBJECT: 
        {
            //             const JsObject *value = static_cast<const JsObject *>(param.value_ptr);
            //             *token = value->token();
            break;                 
        }
    case JSPARAM_ARRAY: 
        {
//             const JsArray *value = static_cast<const JsArray *>(param.value_ptr);
//             *token = value->token();
            break;                
        }
    case JSPARAM_FUNCTION: 
        {
            //             const JsRootedCallback *value = static_cast<const JsRootedCallback *>(param.value_ptr);
            //             *token = value->token();
            break;                  
        }
    case JSPARAM_MODULE: 
        {
            const ModuleImplBaseClass *value =static_cast<const ModuleImplBaseClass *>(param.value_ptr);
            JsToken* pToken = value->GetWrapperToken();
            if (!pToken)
            {
                return false;
            }
            pToken->TokenToVariant(token);
            break;
        }
    case JSPARAM_NULL:
        VARIANT null_variant;
        null_variant.vt = VT_NULL;
        *token = null_variant;
        break;
    case JSPARAM_UNDEFINED:
        // Setting *token = VT_EMPTY doesn't seem to work.
        token->Clear();
        break;
    case JSPARAM_TOKEN: 
        {
            *token = *static_cast<const VARIANT *>(param.value_ptr);
            break;
        }
    default:
        assert(false);
    }
    return true;
}
// bool JsTokenIE::BoolToJsToken(JsContextPtr context, bool value)
// {
//     CComVariant token;
//     token = value;
//     token.Detach(&token_);
//     return true;
// }
// 
// bool JsTokenIE::IntToJsToken(JsContextPtr context, int value)
// {
//     CComVariant token;
//     token = value;
//     token.Detach(&token_);
//     return true;
// }
// 
// bool JsTokenIE::StringToJsToken(JsContextPtr context, const wchar_t *value)
// {
//     CComVariant token;
//     token = value;
//     token.Detach(&token_);
//     return true;
// }
// 
// bool JsTokenIE::DoubleToJsToken(JsContextPtr context, double value)
// {
//     CComVariant token;
//     token = value;
//     token.Detach(&token_);
//     return true;
// }
// 
// bool JsTokenIE::NullToJsToken(JsContextPtr context)
// {
//     VARIANT null_variant;
//     null_variant.vt = VT_NULL;
//     token_ = null_variant;
//     return true;
// }
// 
// bool JsTokenIE::UndefinedToJsToken(JsContextPtr context)
// {
//     VARIANT undefined_variant;
//     undefined_variant.vt = VT_EMPTY;
//     token_ = undefined_variant;
//     return true;
// }
// 
// 
// bool JsTokenIE::JsTokenToBool(JsContextPtr cx, bool *out)
// {
//     if (token_.vt != VT_BOOL) 
//     { 
//         return false; 
//     }
//     *out = (token_.boolVal == VARIANT_TRUE);
//     
//     return true;
// }
// 
// bool JsTokenIE::JsTokenToInt(JsContextPtr cx, int *out)
// {
//     if (token_.vt != VT_I4)
//     {
//         return false;
//     }
//     *out = token_.lVal;
// 
//     return true;
// }
// 
// //virtual bool JsTokenToInt64(JsToken t, JsContextPtr cx, LONGLONG *out);
// bool JsTokenIE::JsTokenToDouble(JsContextPtr cx, double *out)
// {
//     if (token_.vt != VT_R8)
//     {
//         *out = token_.dblVal;
//         return true;
//     } else if (token_.vt == VT_I4) {
//         *out = static_cast<double>(token_.lVal);
//         return true;
//     }
// 
//     return false;
// }
// 
// bool JsTokenIE::JsTokenToString(JsContextPtr cx, std::wstring *out)
// {
//     if (token_.vt != VT_BSTR) 
//     { 
//         return false; 
//     }
// 
//     if (!token_.bstrVal) 
//     {
//         out->clear();
//     } else {
//         out->assign(token_.bstrVal);
//     }
// 
//     return true;
// }
// 
// bool JsTokenIE::JsTokenToObject(JsContextPtr cx, JsObject **out)
// {
//     //scoped_ptr<JsObjectImpl> object(new JsObjectImpl);
//     JsObject *object = new JsObject_IE();
//     if (!object->Initialize(this, cx)) 
//     {
//         return false;
//     }
// 
//     *out = object;
//     return true;
// }
// 
// bool JsTokenIE::JsTokenToArray(JsContextPtr cx, JsArray **out)
// {
//    return true;
// }

bool JsCallBackFunIE::InvokeCallback(int argc, JsParamToSend *argv,
                            JsToken** retval,std::wstring* str_exception)
{
    if ((callback_.vt != VT_DISPATCH) || !callback_.pdispVal) 
    { 
        return false; 
    }

    scoped_array<CComVariant> arguments(new CComVariant[argc]);
    for (int i = 0; i < argc; ++i)
    {
        int dest = argc - 1 - i;  // args are expected in reverse order!!
        ConvertJsParamToVariant(argv[i], &arguments[dest]);
    }

    // Invoke the method.
    DISPPARAMS invoke_params = {0};
    invoke_params.cArgs = argc;
    invoke_params.rgvarg = arguments.get();

    VARIANT varRet = {0};
    EXCEPINFO exception;
    HRESULT hr = callback_.pdispVal->Invoke(
        DISPID_VALUE, IID_NULL,
        LOCALE_SYSTEM_DEFAULT,
        DISPATCH_METHOD,
        &invoke_params,
        retval ? &varRet : NULL,
        &exception,
        NULL);

    if (FAILED(hr)) 
    {
        if (DISP_E_EXCEPTION == hr && str_exception) {
            *str_exception = exception.bstrDescription;
        }

        return false;
    }

    if (retval) 
    {
        *retval = new JsTokenIE(varRet);
    }

    return true;
}