#include "baseclass.h"

ModuleImplBaseClass::ModuleImplBaseClass(const std::string &name): module_name_(name) 
{
}

ModuleImplBaseClass::~ModuleImplBaseClass() 
{
}

JsToken* ModuleImplBaseClass::GetWrapperToken() const
{
    if (js_wrapper_ == NULL)
    {
        return NULL;
    }

    return js_wrapper_->GetWrapperToken();
}

JsRunnerInterface* ModuleImplBaseClass::GetJsRunner() const
{
    if (app_run_env_ == NULL)
    {
        return NULL;
    }

    return app_run_env_->GetJsRunner();
}
bool ModuleImplBaseClass::InvokeCallback(const JsCallBackFun& callback, int argc,JsParamToSend *argv)
{
    JsRunnerInterface* js_runner = GetJsRunner();
    if (js_runner == NULL)
    {
        return false;
    }
    
    
    return true;
}


WebAppEnvironment_IE::WebAppEnvironment_IE(IUnknown *iunknown_site,
                     JsRunnerInterface *js_runner,
                     RUNAPPINFO* pRunAppInfo)
{
    m_JsRunner = js_runner;
    m_pRunAppInfo = pRunAppInfo;
    m_spUnknownSite = iunknown_site;
}

WebAppEnvironment_IE::~WebAppEnvironment_IE()
{
    if (m_JsRunner)
    {
        delete m_JsRunner;
        m_JsRunner = NULL;
    }

//     if (m_pRunAppInfo)
//     {
//         delete m_pRunAppInfo;
//         m_pRunAppInfo = NULL;
//     }
}

JsRunnerInterface* WebAppEnvironment_IE::GetJsRunner()const
{
    return m_JsRunner;
}

RUNAPPINFO* WebAppEnvironment_IE::GetRunAppInof()const
{
    return m_pRunAppInfo;
}