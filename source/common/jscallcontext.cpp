#include <assert.h>
#include <string>

#include "baseclass.h"
#include "jscallcontext.h"
#include "jsarray.h"
#include "ie/activexutil.h"


JsCallContext_IE::JsCallContext_IE(DISPPARAMS FAR *disp_params, VARIANT FAR *retval,
                                   EXCEPINFO FAR *excep_info)
{
    disp_params_=disp_params;
    retval_     =retval;
    exception_info_ =excep_info;
    is_exception_set_ =false;
    is_return_value_set_ =false;
}

int JsCallContext_IE::GetArgumentCount() 
{
    return disp_params_->cArgs;
}

bool JsCallContext_IE::GetArguments(int output_argc, JsArgument *output_argv) 
{
    if (GetArgumentCount() > output_argc) 
    {
        return false;
    }

    // Intitialize all arguments to indicate unspecified.
    for (int i = 0; i < output_argc; ++i) 
    {
        output_argv[i].was_specified = false;
    }

    for (int i = 0; i < output_argc; ++i) 
    {
        assert(output_argv[i].value_ptr);
         // Do we have more arguments to look at?
        if (i >= GetArgumentCount()) 
        {
            for (; i < output_argc; ++i) 
            {
                if (output_argv[i].requirement == JSPARAM_REQUIRED) 
                 {
                     return false;
                 }
             }

             return true;
         }
 
         if ((GetArgumentType(i) == JSPARAM_NULL ||
             GetArgumentType(i) == JSPARAM_UNDEFINED)) 
         {
             if (output_argv[i].requirement == JSPARAM_REQUIRED) 
             {
                 return false;
             }
         } else {
             if (!ConvertTokenToArgument(i, &output_argv[i])) 
             {
                 //fail
                 return false;
             }
 
             output_argv[i].was_specified = true;
         }
     }

    return true;
}

bool JsCallContext_IE::ConvertTokenToArgument(int index,JsArgument *param)
{
    int arg_index = disp_params_->cArgs - index - 1;
    VARIANT arg = disp_params_->rgvarg[arg_index];

    switch (param->type) 
    {
    case JSPARAM_BOOL: 
     {
         bool *value = static_cast<bool *>(param->value_ptr);

         if (!JsTokenToBool(arg, value)) 
         {
             return false;
         }
         break;
     }
    case JSPARAM_INT: 
     {
         int *value = static_cast<int *>(param->value_ptr);
         if (!JsTokenToInt(arg, value)) 
         {
             return false;
         }
         break;     
     }
    case JSPARAM_INT64: 
     {
         LONGLONG *value = static_cast<LONGLONG *>(param->value_ptr);
         if (!JsTokenToInt64(arg, value)) 
         {
             return false;
         }
         break;                
     }
    case JSPARAM_DOUBLE: 
     {
         double *value = static_cast<double *>(param->value_ptr);
         if (!JsTokenToDouble(arg, value)) 
         {
             return false;
         }
         break;          
     }
    case JSPARAM_OBJECT: 
     {
         JsObject **value = static_cast<JsObject **>(param->value_ptr);
         if (!JsTokenToObject(arg, value)) 
         {
             return false;
         }
         break;
     }
    case JSPARAM_ARRAY: 
     {
         JsArray **value = static_cast<JsArray **>(param->value_ptr);
         if (!JsTokenToArray(arg, value)) 
         {
             return false;
         }
         break;         
     }
    case JSPARAM_FUNCTION: 
     {
         JsCallBackFun **value = static_cast<JsCallBackFun **>(param->value_ptr);
         if (!JsTokenToNewCallback(arg,value))
         {
             return false;
         }
         break;                   
     }
    case JSPARAM_STRING16: 
     {
         std::wstring *value = static_cast<std::wstring *>(param->value_ptr);
         if (!JsTokenToString(arg, value)) 
         {
             return false;
         }
         break;                   
     }
    case JSPARAM_TOKEN: 
     {
         VARIANT *value = static_cast<VARIANT *>(param->value_ptr);
         *value = arg;
         return true;            
     }
//     case JSPARAM_MODULE: 
//      {
//          ModuleImplBaseClass **value =
//              static_cast<ModuleImplBaseClass **>(param->value_ptr);
//          if (!JsTokenToModule(NULL,context->js_context(), variant, value)) 
//          {
//              return false;
//          }
//          break;                 
//      }
    default:
     return false;                                   
    }

    return true;
}


JsParamType JsCallContext_IE::GetArgumentType(int i) 
{
    if (i >= GetArgumentCount()) 
    {
        return JSPARAM_UNKNOWN;
    }

    return JsTokenGetType(i, NULL);
}

JsParamType JsCallContext_IE::JsTokenGetType(int index, JsContextPtr cx) 
{
    int arg_index = disp_params_->cArgs - index - 1;
    VARIANT token = disp_params_->rgvarg[arg_index];

    if (token.vt == VT_BOOL) {
        return JSPARAM_BOOL;
    } else if (token.vt == VT_I4) {
        return JSPARAM_INT;
    } else if (token.vt == VT_R8) {
        return JSPARAM_DOUBLE;
    } else if (token.vt == VT_BSTR) {
        return JSPARAM_STRING16;
    } else if (token.vt == VT_NULL) {
        return JSPARAM_NULL;
    } else if (token.vt == VT_EMPTY) {
        return JSPARAM_UNDEFINED;
    } else if (ActiveXUtil::JsTokenIsArray(token)) { 
        return JSPARAM_ARRAY;
    } else if (ActiveXUtil::JsTokenIsCallback(token)) {
        return JSPARAM_FUNCTION;
    } else if (ActiveXUtil::JsTokenIsObject(token)) {
        return JSPARAM_OBJECT;
    } else {
        return JSPARAM_UNKNOWN;  // Unsupported type
    }
}

bool JsCallContext_IE::GetArgumentAsBool(int i,bool *out) 
{
    if (i >= GetArgumentCount())
    {
        return false;
    }

    int arg_index = disp_params_->cArgs - i - 1;
    VARIANT arg = disp_params_->rgvarg[arg_index];
    return JsTokenToBool(arg, out);
    return false;
}

bool JsCallContext_IE::GetArgumentAsInt(int i,int *out) 
{
    if (i >= GetArgumentCount()) 
    {
        return false;
    }

    int arg_index = disp_params_->cArgs - i - 1;
    VARIANT arg = disp_params_->rgvarg[arg_index];
    return JsTokenToInt(arg, out);

    return false;
}

bool JsCallContext_IE::GetArgumentAsDouble(int i,double *out) 
{
    if (i >= GetArgumentCount())
    {
        return false;
    }

    int arg_index = disp_params_->cArgs - i - 1;
    VARIANT arg = disp_params_->rgvarg[arg_index];
    return JsTokenToDouble(arg, out);

    return false;
}

bool JsCallContext_IE::GetArgumentAsString(int i,std::wstring *out) 
{
    if (i >= GetArgumentCount()) 
    {
        return false;
    }

    int arg_index = disp_params_->cArgs - i - 1;
    VARIANT arg = disp_params_->rgvarg[arg_index];
    return JsTokenToString(arg, out);

    return false;
}

bool JsCallContext_IE::GetArgumentAsCallback(int i,JsCallBackFun **out)
{
    int arg_index = disp_params_->cArgs - i - 1;
    VARIANT arg = disp_params_->rgvarg[arg_index];
    if (!JsTokenToNewCallback(arg,out))
    {
        return false;
    }

    return true;
}

bool JsCallContext_IE::GetArgumentAsJsObject(int i,JsObject **out)
{
    int arg_index = disp_params_->cArgs - i - 1;
    VARIANT arg = disp_params_->rgvarg[arg_index];
    if (!JsTokenToObject(arg,out))
    {
        return false;
    }

    return true;
}

bool JsCallContext_IE::GetArgumentAsJsArray(int i,JsArray **out)
{
    int arg_index = disp_params_->cArgs - i - 1;
    VARIANT arg = disp_params_->rgvarg[arg_index];
    if (!JsTokenToArray(arg,out))
    {
        return false;
    }

    return true;
}

bool JsCallContext_IE::JsTokenToBool(VARIANT t, bool *out)
{
    if (t.vt != VT_BOOL) { return false; }
    *out = (t.boolVal == VARIANT_TRUE);
    return true;
}

bool JsCallContext_IE::JsTokenToInt(VARIANT t, int *out)
{
    if (t.vt != VT_I4) { return false; }
    *out = t.lVal;
    return true;
}

bool JsCallContext_IE::JsTokenToInt64(VARIANT t, LONGLONG *out)
{
    double dbl;
    if (!JsTokenToDouble(t,&dbl))
    {
        return false;
    }
    *out = static_cast<LONGLONG>(dbl);
    
    return true;
}

bool JsCallContext_IE::JsTokenToDouble(VARIANT t, double *out)
{
    if (t.vt == VT_R8) 
    {
        *out = t.dblVal;
        return true;
    } else if (t.vt == VT_I4) 
    {
        *out = static_cast<double>(t.lVal);
        return true;
    }
    return false;
}

bool JsCallContext_IE::JsTokenToString(VARIANT t, std::wstring *out)
{
    if (t.vt != VT_BSTR) 
    { 
        return false; 
    }

    if (!t.bstrVal) 
    {
        out->clear();
    } else {
        out->assign(t.bstrVal);
    }

    return true;
}

bool JsCallContext_IE::JsTokenToObject(VARIANT t, JsObject **out)
{
    JsObject* object = new JsObject_IE;
    JsToken* token = new JsTokenIE(t);

    if (!object->Initialize(token, NULL)) 
    {
        return false;
    }

    *out = object;
    delete token;

    return true;
}

bool JsCallContext_IE::JsTokenToArray(VARIANT t, JsArray **out)
{
    if (!ActiveXUtil::JsTokenIsArray(t))
    {
        return false;
    }
    *out = new JsArray_IE(t);

    return true;
}

bool JsCallContext_IE::JsTokenToNewCallback(VARIANT t, JsCallBackFun **out)
{
    if (!ActiveXUtil::JsTokenIsCallback(t))
    {
        return false;
    }
    *out = new JsCallBackFunIE(t);

    return true;
}

void JsCallContext_IE::SetReturnValue(JsParamType type, const void *value_ptr)
{
    if (retval_) 
    {
        JsParamToSend retval = { type, value_ptr };
        CComVariant token;

        if (ConvertJsParamToVariant(retval, &token))
        {
            is_return_value_set_ = true;
            token.Detach(retval_);
        }else{
            SetException(L"Return value is out of range.");
       }
    }
}

void JsCallContext_IE::SetException(const std::wstring &message)
{
    assert(!message.empty());
    if (!exception_info_) 
    {
        return;
    }

    exception_info_->wCode = 1001; // Not used, MSDN says must be > 1000.
    exception_info_->wReserved = 0;
    exception_info_->bstrSource = SysAllocString(L"QPlusWebApp");
    exception_info_->bstrDescription = SysAllocString(message.c_str());
    exception_info_->bstrHelpFile = NULL;
    exception_info_->dwHelpContext = 0;
    exception_info_->pvReserved = NULL;
    exception_info_->pfnDeferredFillIn = NULL;
    exception_info_->scode = 0;

    is_exception_set_ = true;
}