#ifndef WEBAPP_JS_ARRAY_H__
#define WEBAPP_JS_ARRAY_H__

#include <string>

class ModuleImplBaseClass;
class JsObject;

class JsArray 
{
public:
    virtual ~JsArray() {};

    virtual bool GetLength(int *length) = 0;

    virtual bool GetElementAsBool(int index, bool *out) = 0;
    virtual bool GetElementAsInt(int index, int *out) = 0;
    virtual bool GetElementAsDouble(int index, double *out) = 0;
    virtual bool GetElementAsString(int index, std::wstring *out) = 0;
    virtual bool GetElementAsArray(int index, JsArray **out) = 0;
    virtual bool GetElementAsObject(int index, JsObject **out) = 0;
    virtual bool GetElementAsFunction(int index,JsCallBackFun **out) = 0;

    // Returns JSPARAM_UNDEFINED if the requested element does not exist.
    virtual JsParamType GetElementType(int index) = 0;

    virtual bool SetElementBool(int index, bool value) = 0;
    virtual bool SetElementInt(int index, int value) = 0;
    virtual bool SetElementDouble(int index, double value) = 0;
    virtual bool SetElementString(int index, const std::wstring &value) = 0;
    virtual bool SetElementArray(int index, JsArray *value) = 0;
    virtual bool SetElementObject(int index, JsObject *value) = 0;
    virtual bool SetElementFunction(int index, JsCallBackFun *value) = 0;
    virtual bool SetElementModule(int index, ModuleImplBaseClass *value) = 0;
    virtual bool SetElementNull(int index) = 0;
    virtual bool SetElementUndefined(int index) = 0;

//     // TODO(nigeltao): These two methods should really be private.
//     virtual bool GetElement(int index, JsScopedToken *out) const = 0;
//     virtual bool SetElement(int index, const JsScopedToken &value) = 0;
};


class JsArray_IE : public JsArray
{
public:
    JsArray_IE(VARIANT t)
    {
        array_.Attach(&t);
    }

    virtual ~JsArray_IE() {};

    virtual bool GetLength(int *length);

    virtual bool GetElementAsBool(int index, bool *out);
    virtual bool GetElementAsInt(int index, int *out);
    virtual bool GetElementAsDouble(int index, double *out);
    virtual bool GetElementAsString(int index, std::wstring *out);
    virtual bool GetElementAsArray(int index, JsArray **out);
    virtual bool GetElementAsObject(int index, JsObject **out);
    virtual bool GetElementAsFunction(int index,JsCallBackFun **out);

    // Returns JSPARAM_UNDEFINED if the requested element does not exist.
    virtual JsParamType GetElementType(int index);

    virtual bool SetElementBool(int index, bool value);
    virtual bool SetElementInt(int index, int value);
    virtual bool SetElementDouble(int index, double value);
    virtual bool SetElementString(int index, const std::wstring &value);
    virtual bool SetElementArray(int index, JsArray *value);
    virtual bool SetElementObject(int index, JsObject *value);
    virtual bool SetElementFunction(int index, JsCallBackFun *value);
    virtual bool SetElementModule(int index, ModuleImplBaseClass *value);
    virtual bool SetElementNull(int index);
    virtual bool SetElementUndefined(int index);

private:
    virtual bool GetElement(int index, CComVariant* out);
    virtual bool SetElement(int index, const CComVariant &token);

private:
    CComVariant array_;
};


class JsArray_CR : public JsArray
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
};

#endif //WEBAPP_JS_ARRAY_H__