#ifndef WEBAPP_JS_OBJECT_H__
#define WEBAPP_JS_OBJECT_H__
#include <string>
#include "jstypes.h"
//#include "jsarray.h"
class ModuleImplBaseClass;

class JsObject{
public:
    virtual ~JsObject() {}
    virtual bool Initialize(JsToken *value, JsContextPtr context)=0;
    // GetPropertyXxx returns false on failure, including if the requested element
    // does not exist.
    virtual bool GetPropertyAsBool(const std::wstring &name,
        bool *out)= 0;
    virtual bool GetPropertyAsInt(const std::wstring &name,
        int *out) = 0;
    virtual bool GetPropertyAsDouble(const std::wstring &name,
        double *out) = 0;
    virtual bool GetPropertyAsString(const std::wstring &name,
        std::wstring *out)= 0;
    virtual bool GetPropertyAsArray(const std::wstring &name,
        JsArray **out) = 0;
    virtual bool GetPropertyAsObject(const std::wstring &name,
        JsObject **out) = 0;
    virtual bool GetPropertyAsFunction(const std::wstring &name,
        JsCallBackFun **out) = 0;

    virtual JsParamType GetPropertyType(const std::wstring &name) = 0;
    virtual bool GetPropertyNames(std::vector<std::wstring> *out) = 0;

    virtual bool SetPropertyBool(const std::wstring& name,
        bool value) = 0;
    virtual bool SetPropertyInt(const std::wstring &name,
        int value) = 0;
    virtual bool SetPropertyDouble(const std::wstring& name,
        double value) = 0;
    virtual bool SetPropertyString(const std::wstring &name,
        const std::wstring &value) = 0;
    virtual bool SetPropertyArray(const std::wstring& name,
        JsArray* value) = 0;
    virtual bool SetPropertyObject(const std::wstring& name,
        JsObject* value) = 0;
    virtual bool SetPropertyFunction(const std::wstring& name,
        JsCallBackFun* value) = 0;
    virtual bool SetPropertyModule(const std::wstring& name,
        ModuleImplBaseClass* value) = 0;
    virtual bool SetPropertyNull(const std::wstring &name) = 0;
    virtual bool SetPropertyUndefined(const std::wstring &name) = 0;
//     virtual bool SetPropertyMarshaledJsToken(
//         const std::wstring& name,
//         ModuleEnvironment* module_environment,
//         MarshaledJsToken* value) = 0;

/*    virtual const JsScopedToken &token() const = 0*/;

//     virtual bool GetProperty(const std::wstring &name,
//         JsScopedToken *value) const = 0;
//     virtual bool SetProperty(const std::wstring &name,
//         const JsToken &value) = 0;
    //virtual JsContextPtr js_context() const = 0;
};

class JsObject_IE : public JsObject
{
public:
    JsObject_IE()
    {
    }

    JsObject_IE(VARIANT t)
    {
        token_.Attach(&t);
    }

    virtual bool Initialize(JsToken *value, JsContextPtr context);

    virtual bool GetPropertyAsBool(const std::wstring &name,bool *out);
    virtual bool GetPropertyAsInt(const std::wstring &name,int *out);
    virtual bool GetPropertyAsDouble(const std::wstring &name,double *out);
    virtual bool GetPropertyAsString(const std::wstring &name,std::wstring *out);
    virtual bool GetPropertyAsArray(const std::wstring &name,JsArray **out);
    virtual bool GetPropertyAsObject(const std::wstring &name,JsObject **out);
    virtual bool GetPropertyAsFunction(const std::wstring &name,JsCallBackFun **out);

    virtual JsParamType GetPropertyType(const std::wstring &name);
    virtual bool GetPropertyNames(std::vector<std::wstring> *out);

    virtual bool SetPropertyBool(const std::wstring& name,bool value);
    virtual bool SetPropertyInt(const std::wstring &name,int value);
    virtual bool SetPropertyDouble(const std::wstring& name,double value);
    virtual bool SetPropertyString(const std::wstring &name,
        const std::wstring &value);
    virtual bool SetPropertyArray(const std::wstring& name,
        JsArray* value);
    virtual bool SetPropertyObject(const std::wstring& name,
        JsObject* value);
    virtual bool SetPropertyFunction(const std::wstring& name,
        JsCallBackFun* value);
    virtual bool SetPropertyModule(const std::wstring& name,
        ModuleImplBaseClass* value);
    virtual bool SetPropertyNull(const std::wstring &name);
    virtual bool SetPropertyUndefined(const std::wstring &name);

    JsToken* token();

    virtual bool GetProperty(const std::wstring &name,CComVariant *value);
    virtual bool SetProperty(const std::wstring &name,const JsToken &value);

protected:
private:
    CComVariant token_;
};


class JsObject_CR : public JsObject
{
public:
    virtual bool GetPropertyAsBool(const std::wstring &name,bool *out);
    virtual bool GetPropertyAsInt(const std::wstring &name,int *out);
    virtual bool GetPropertyAsDouble(const std::wstring &name,double *out);
    virtual bool GetPropertyAsString(const std::wstring &name,std::wstring *out);
    virtual bool GetPropertyAsArray(const std::wstring &name,JsArray **out);
    virtual bool GetPropertyAsObject(const std::wstring &name,JsObject **out);
    virtual bool GetPropertyAsFunction(const std::wstring &name,JsCallBackFun **out);

    virtual JsParamType GetPropertyType(const std::wstring &name);
    virtual bool GetPropertyNames(std::vector<std::wstring> *out);

    virtual bool SetPropertyBool(const std::wstring& name,bool value);
    virtual bool SetPropertyInt(const std::wstring &name,int value);
    virtual bool SetPropertyDouble(const std::wstring& name,double value);
    virtual bool SetPropertyString(const std::wstring &name,
        const std::wstring &value);
    virtual bool SetPropertyArray(const std::wstring& name,
        JsArray* value);
    virtual bool SetPropertyObject(const std::wstring& name,
        JsObject* value);
    virtual bool SetPropertyFunction(const std::wstring& name,
        JsCallBackFun* value);
    virtual bool SetPropertyModule(const std::wstring& name,
        ModuleImplBaseClass* value);
    virtual bool SetPropertyNull(const std::wstring &name);
    virtual bool SetPropertyUndefined(const std::wstring &name);

    //virtual const JsScopedToken &token();

//     virtual bool GetProperty(const std::wstring &name,JsScopedToken *value);
//     virtual bool SetProperty(const std::wstring &name,const JsToken &value);
    virtual JsContextPtr js_context();

protected:
private:
};

#endif //WEBAPP_JS_OBJECT_H__