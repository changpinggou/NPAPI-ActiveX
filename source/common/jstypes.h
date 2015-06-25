#ifndef WEBAPP_JS_TYPES_H__
#define WEBAPP_JS_TYPES_H__
#include <atlcomcli.h>
#include <string>
#include <vector>

//#include "jsobject.h"
class JsObject;
class JsArray;
// The JsParam* types define values for sending and receiving JS parameters.
enum JsParamType 
{
    JSPARAM_BOOL,
    JSPARAM_INT,
    JSPARAM_INT64,
    JSPARAM_DOUBLE,
    JSPARAM_STRING16,
    JSPARAM_OBJECT,
    JSPARAM_ARRAY,
    JSPARAM_FUNCTION,
    JSPARAM_MODULE,
    JSPARAM_DOM_ELEMENT,
    JSPARAM_NULL,
    JSPARAM_UNDEFINED,
    JSPARAM_UNKNOWN,
    JSPARAM_ABSTRACT_TOKEN,
    JSPARAM_TOKEN
};

enum JsParamRequirement 
{
    JSPARAM_OPTIONAL,
    JSPARAM_REQUIRED,
};

struct JsParamToSend 
{
    JsParamType type;
    const void *value_ptr;
};

struct JsArgument 
{
    JsParamRequirement requirement;
    JsParamType type;
    void* value_ptr;
    bool was_specified;
};


typedef void* JsContextPtr;  // unused in IE

bool ConvertJsParamToVariant(const JsParamToSend &param, CComVariant *token);
//AbstractJsToken JsTokenPtrToAbstractJsToken(JsToken *token);

class JsToken
{
public:
    JsToken()
    {

    }
    ~JsToken()
    {

    }
public:
    virtual void TokenToVariant(VARIANT *token)
    {
    }

//     virtual bool BoolToJsToken(JsContextPtr context, bool value);
//     virtual bool IntToJsToken(JsContextPtr context, int value);
//     virtual bool StringToJsToken(JsContextPtr context, const wchar_t *value);
//     virtual bool DoubleToJsToken(JsContextPtr context, double value);
//     virtual bool NullToJsToken(JsContextPtr context);
//     virtual bool UndefinedToJsToken(JsContextPtr context);
// 
//     virtual bool JsTokenToBool(JsContextPtr cx, bool *out);
//     virtual bool JsTokenToInt(JsContextPtr cx, int *out);
//     //virtual bool JsTokenToInt64(JsToken t, JsContextPtr cx, LONGLONG *out);
//     virtual bool JsTokenToDouble(JsContextPtr cx, double *out);
//     virtual bool JsTokenToString(JsContextPtr cx, std::wstring *out);
//     virtual bool JsTokenToObject(JsContextPtr cx, JsObject **out);
//     virtual bool JsTokenToArray(JsContextPtr cx, JsArray **out);
};

class JsTokenIE : public JsToken
{
public:
    JsTokenIE(VARIANT token)
    {
        VariantInit(&token_);
        VariantCopy(&token_,&token);
    }
    ~JsTokenIE()
    {
        VariantClear(&token_);
    }
public:
    virtual void TokenToVariant(VARIANT *token)
    {
        //VariantCopy(token,&token_);
        *token = token_;
        //token = &token_;
    }


//     virtual bool BoolToJsToken(JsContextPtr context, bool value);
//     virtual bool IntToJsToken(JsContextPtr context, int value);
//     virtual bool StringToJsToken(JsContextPtr context, const wchar_t *value);
//     virtual bool DoubleToJsToken(JsContextPtr context, double value);
//     virtual bool NullToJsToken(JsContextPtr context);
//     virtual bool UndefinedToJsToken(JsContextPtr context);
// 
//     virtual bool JsTokenToBool(JsContextPtr cx, bool *out);
//     virtual bool JsTokenToInt(JsContextPtr cx, int *out);
//     //virtual bool JsTokenToInt64(JsToken t, JsContextPtr cx, LONGLONG *out);
//     virtual bool JsTokenToDouble(JsContextPtr cx, double *out);
//     virtual bool JsTokenToString(JsContextPtr cx, std::wstring *out);
//     virtual bool JsTokenToObject(JsContextPtr cx, JsObject **out);
//     virtual bool JsTokenToArray(JsContextPtr cx, JsArray **out);
private:
    VARIANT token_;
};

class JsTokenCR
{
public:
};


class JsCallBackFun
{
public:
    JsCallBackFun()
    {

    }
    ~JsCallBackFun()
    {

    }

    virtual bool IsValidCallback() const = 0;
    virtual bool InvokeCallback(int argc, JsParamToSend *argv,
                       JsToken** retval,std::wstring* str_exception)=0;
};

class JsCallBackFunIE :public JsCallBackFun
{
public:
    JsCallBackFunIE(VARIANT callback)
    {
        callback_.Attach(&callback);
        //token_ = new JsTokenIE(callback);
    }
    ~JsCallBackFunIE()
    {
//         if (token_)
//         {
//             delete token_;
//             token_ = NULL;
//         }
    }

    virtual bool IsValidCallback() const
    {
        return true;
    }

    virtual bool JsCallBackFunIE::InvokeCallback(int argc, JsParamToSend *argv,
        JsToken** retval,std::wstring* str_exception);
//     virtual JsToken* token()
//     {
//         return token_;
//     };
private:
    CComVariant callback_;
    //JsToken *token_;
};


class JsCallBackFunCR : public JsCallBackFun
{
public:

};

#endif //WEBAPP_JS_TYPES_H__