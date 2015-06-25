#ifndef WEBAPP_EXTERNAL_WRAPPER_H__
#define WEBAPP_EXTERNAL_WRAPPER_H__

#include <oaidl.h>
#include <atlbase.h>
#include <atlcom.h>
#include "dispatchertemplate.h"
#include "third_party/scoped_ptr.h"
#include "baseclass.h"
#include <string>

class ExternalWrapper_IE
    : public ExternalWrapperBaseClass,
      public IDispatch,
      public CComObjectRootEx<CComMultiThreadModel>,
      public CComCoClass<ExternalWrapper_IE>
{
public:
    BEGIN_COM_MAP(ExternalWrapper_IE)
        COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()

    DECLARE_NOT_AGGREGATABLE(ExternalWrapper_IE)
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    ExternalWrapper_IE() 
    {
        VariantInit(&token_);
        token_.vt = VT_DISPATCH;
        token_.pdispVal = const_cast<ExternalWrapper_IE *>(this);
    }
    
    ~ExternalWrapper_IE() {}

    // IDispatch: GetTypeInfoCount, GetTypeInfo, GetIDsOfNames, Invoke.
    STDMETHOD(GetTypeInfoCount)(unsigned int FAR* retval);
    STDMETHOD(GetTypeInfo)(unsigned int index, LCID lcid,
        ITypeInfo FAR* FAR* retval);
    STDMETHOD(GetIDsOfNames)(REFIID iid, OLECHAR FAR* FAR* names,
        unsigned int num_names, LCID lcid, 
        DISPID FAR* retval);
    STDMETHOD(Invoke)(DISPID member_id, REFIID iid, LCID lcid, WORD flags,
        DISPPARAMS FAR* params, VARIANT FAR* retval,
        EXCEPINFO FAR* exception,
        unsigned int FAR* arg_error_index);

    virtual JsToken* GetWrapperToken() const 
    {
        //return token_;
        JsToken *token =new JsTokenIE(token_);
        return token;
    }

    // Gets the Dispatcher for this module.
    virtual DispatcherInterface *GetDispatcher() const 
    {
        assert(dispatcher_.get());
        return dispatcher_.get();
    }

    virtual ModuleImplBaseClass *GetModuleImplBaseClass() const 
    {
        assert(impl_.get());
        return impl_.get();
    }

    virtual void Ref() 
    {
        AddRef();
    }

    virtual void Unref() 
    {
        Release();
    }

    void Init(ModuleImplBaseClass *impl, DispatcherInterface *dispatcher) 
    {
        assert(!impl_.get());
        assert(impl);
        impl_.reset(impl);

        assert(!dispatcher_.get());
        assert(dispatcher);
        dispatcher_.reset(dispatcher);
    }

private:
    scoped_ptr<ModuleImplBaseClass> impl_;
    scoped_ptr<DispatcherInterface> dispatcher_;
    VARIANT token_;
};

#endif //WEBAPP_BASE_CLASS_H__