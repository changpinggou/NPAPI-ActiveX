#ifndef WEBAPP_JS_CALL_CONTEXT_H__
#define WEBAPP_JS_CALL_CONTEXT_H__

#include <string>
#include "jstypes.h"
#include "jsobject.h"

typedef wchar_t char16;
class JsRunnerInterface;

class JsCallContextBase 
{
public:
    JsCallContextBase() {}
    ~JsCallContextBase() {}

public:
    virtual JsParamType JsTokenGetType(int index, JsContextPtr cx)=0;
    virtual JsParamType GetArgumentType(int i)=0;
    virtual bool GetArguments(int argc, JsArgument *argv)=0;
    virtual int GetArgumentCount()=0;
    virtual bool GetArgumentAsBool(int i, bool *out)=0;
    virtual bool GetArgumentAsInt(int i, int *out)=0;
    virtual bool GetArgumentAsDouble(int i, double *out)=0;
    virtual bool GetArgumentAsString(int i, std::wstring *out)=0;
    virtual bool GetArgumentAsCallback(int i,JsCallBackFun **out)=0;
    virtual bool GetArgumentAsJsObject(int i,JsObject **out)=0;
    virtual bool GetArgumentAsJsArray(int i,JsArray **out)=0;

    virtual void SetReturnValue(JsParamType type, const void *value_ptr)=0;
    virtual void SetException(const std::wstring &message)=0;
    virtual bool IsExceptionSet()=0;
    virtual bool IsReturnValueSet()=0;

    //virtual bool JsTokenToNewCallback(JsToken t, JsContextPtr cx, JsCallBackFun **out)=0;


};

class JsCallContext_IE : public JsCallContextBase
{
public:
    JsCallContext_IE(DISPPARAMS FAR *disp_params, VARIANT FAR *retval,
                     EXCEPINFO FAR *excep_info);

    virtual JsParamType JsTokenGetType(int index, JsContextPtr cx);
    virtual JsParamType GetArgumentType(int i);

    virtual int GetArgumentCount();
    virtual bool GetArguments(int argc, JsArgument *argv);
    
    virtual bool GetArgumentAsBool(int i,bool *out);
    virtual bool GetArgumentAsInt(int i,int *out);
    virtual bool GetArgumentAsDouble(int i,double *out);
    virtual bool GetArgumentAsString(int i,std::wstring *out);
    virtual bool GetArgumentAsCallback(int i,JsCallBackFun **out);
    virtual bool GetArgumentAsJsObject(int i,JsObject **out);
    virtual bool GetArgumentAsJsArray(int i,JsArray **out);

    virtual void SetReturnValue(JsParamType type, const void *value_ptr);
    virtual void SetException(const std::wstring &message);

    virtual bool IsExceptionSet(){return is_exception_set_;};
    virtual bool IsReturnValueSet(){return is_return_value_set_;};

private:
    bool JsTokenToBool(VARIANT t, bool *out);
    bool JsTokenToInt(VARIANT t, int *out);
    bool JsTokenToInt64(VARIANT t, LONGLONG *out);
    bool JsTokenToDouble(VARIANT t, double *out);
    bool JsTokenToString(VARIANT t, std::wstring *out);
    bool JsTokenToObject(VARIANT t, JsObject **out);
    bool JsTokenToArray(VARIANT t, JsArray **out);
    bool JsTokenToNewCallback(VARIANT t, JsCallBackFun **out);
    bool ConvertTokenToArgument(int index,JsArgument *param);

private:
    DISPPARAMS FAR *disp_params_;
    VARIANT FAR *retval_;
    EXCEPINFO FAR *exception_info_;
    bool is_exception_set_;
    bool is_return_value_set_;
};

class JsCallContext_CR : public JsCallContextBase
{
public:
//     JsCallContext_CR(JsContextPtr js_context, NPObject *object,
//         int argc, const JsToken *argv, JsToken *retval);
private:

    int argc_;
    const JsToken *argv_;
    JsToken *retval_;
};


#endif //WEBAPP_JS_CALL_CONTEXT_H__