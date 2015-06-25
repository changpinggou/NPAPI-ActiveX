#ifndef WEBAPP_BASE_CLASS_H__
#define WEBAPP_BASE_CLASS_H__
#include <string>
#include "jscallcontext.h"
#include "dispatchertemplate.h"
#include "third_party/scoped_ptr.h"

class DispatcherInterface;
class RUNAPPINFO;

class WebAppRunEnvBase
{
public:
    WebAppRunEnvBase(){}
    ~WebAppRunEnvBase(){}

public:
    virtual JsRunnerInterface* GetJsRunner()const=0;
    virtual RUNAPPINFO* GetRunAppInof()const=0;
};

class WebAppEnvironment_IE : public WebAppRunEnvBase
{
public:
    WebAppEnvironment_IE(IUnknown *iunknown_site,
        JsRunnerInterface *js_runner,
        RUNAPPINFO* pRunAppInfo);
    ~WebAppEnvironment_IE();

private:
    JsRunnerInterface *m_JsRunner;
    RUNAPPINFO* m_pRunAppInfo;
    CComPtr<IUnknown> m_spUnknownSite;
public:
    virtual JsRunnerInterface* GetJsRunner()const;
    virtual RUNAPPINFO* GetRunAppInof()const;
};

class WebAppEnvironment_CR : public WebAppRunEnvBase
{
public:
    JsRunnerInterface* GetJsRunner()const=0;
    RUNAPPINFO* GetRunAppInof()const=0;
};
class ExternalWrapperBaseClass 
{
public:
    virtual JsToken* GetWrapperToken() const = 0;
    virtual DispatcherInterface *GetDispatcher() const = 0;
    virtual ModuleImplBaseClass *GetModuleImplBaseClass() const = 0;
    virtual void Ref()=0;
    virtual void Unref()=0;
protected:
    // Don't allow direct deletion via this interface.
    virtual ~ExternalWrapperBaseClass() { }
};

class ModuleImplBaseClass 
{
public:
    explicit ModuleImplBaseClass(const std::string &name);
    virtual ~ModuleImplBaseClass();

    const std::string &get_module_name() const 
    {
        return module_name_;
    }

    std::wstring get_wide_module_name() const 
    {
        return std::wstring(L"");
    }

    void InitModuleEnvironment(WebAppRunEnvBase* run_env)
    {
        app_run_env_ = run_env;
    }

    WebAppRunEnvBase* GetAppRunEnvironment()
    {
        return app_run_env_;
    }


    //const SecurityOrigin& EnvPageSecurityOrigin() const;
    JsRunnerInterface *GetJsRunner() const;

    // Methods for dealing with the JavaScript wrapper interface.
    void SetJsWrapper(ExternalWrapperBaseClass *wrapper)
    { 
        js_wrapper_ = wrapper; 
    }

    ExternalWrapperBaseClass *GetWrapper() const 
    {
        //assert(js_wrapper_);
        return js_wrapper_;
    }

    void Ref();
    void Unref();

    // TODO(aa): Remove and replace call sites with GetWrapper()->GetToken().
    virtual JsToken* GetWrapperToken() const; 
    bool InvokeCallback(const JsCallBackFun& callback, int argc,JsParamToSend *argv);

    //void InvokeCallbackUnsafe(const ScopedJsCallback& callback, int argc,
        //JsParamToSend *argv);

private:
    std::string module_name_;
    ExternalWrapperBaseClass *js_wrapper_;

protected:
    WebAppRunEnvBase *app_run_env_;
};

class JsRunnerInterface {
public:
    virtual ~JsRunnerInterface() {};

    virtual bool Eval(const std::wstring &script) = 0;
    virtual void SetErrorHandler(void* error_handler)=0;
    virtual JsObject *NewObject(bool dump_on_error = false) = 0;
    virtual JsObject *NewError(const std::wstring &message,bool dump_on_error = false) = 0;
    virtual JsArray* NewArray() = 0;

    virtual bool InitializeModuleWrapper(ModuleImplBaseClass *module,
                                         DispatcherInterface *dispatcher,
                                         JsCallContextBase *context) = 0;

    virtual bool InvokeCallback(const JsCallBackFun* callback,
                                int argc, JsParamToSend *argv,
                                JsToken* retval,std::wstring* exception)=0;
};

template<class ModuleClass,class OutType>
bool CreateModule(WebAppRunEnvBase *module_environment,
                  JsCallContextBase *context,
                  OutType** module) 
{
    if (!module || !module_environment)
    {
        return false;
    }

    JsRunnerInterface* js_runner = module_environment->GetJsRunner();
    if (!js_runner)
    {
        return false; 
    }

    scoped_ptr<ModuleClass> impl(new ModuleClass());
    impl->InitModuleEnvironment(module_environment);
    scoped_ptr<Dispatcher<ModuleClass> > dispatcher(new Dispatcher<ModuleClass>(impl.get()));
    
    bool env_init =js_runner->InitializeModuleWrapper(impl.get(),dispatcher.release(),context);
    
    if (!env_init) 
    {
        return false;
    }

    *module = impl.release();
    return true;
}

#endif //WEBAPP_BASE_CLASS_H__