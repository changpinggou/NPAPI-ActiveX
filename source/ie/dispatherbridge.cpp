#include <assert.h>

#include "dispatherbridge.h"
#include "..//jscallcontext.h"
#include "..//utilstring.h"
#include "..//dispatchertemplate.h"

HRESULT DispatcherGetTypeInfoCount(DispatcherInterface* dispatcher,unsigned int FAR* retval)
{
    return E_NOTIMPL;
}


HRESULT DispatcherGetTypeInfo(DispatcherInterface* dispatcher,
                              unsigned int index, LCID lcid,
                              ITypeInfo FAR* FAR* retval) 
{
    return E_NOTIMPL;
}


HRESULT DispatcherGetIDsOfNames(DispatcherInterface* dispatcher, REFIID iid,
                                OLECHAR FAR* FAR* names, unsigned int num_names, 
                                LCID lcid,DISPID FAR* retval) 
{
    assert(dispatcher);
    // JavaScript does not have named parameters.
    assert(num_names == 1);

    std::string member_name_utf8 = Util::String::UnicodetoUtf8(*names);

    DispatchId dispatch_id = dispatcher->GetDispatchId(member_name_utf8);
    if (dispatch_id == NULL) 
    {
        *retval = DISPID_UNKNOWN;
        return DISP_E_UNKNOWNNAME;
    } else {
        *retval = reinterpret_cast<DISPID>(dispatch_id);
        return S_OK;
    }
}


HRESULT DispatcherInvoke(DispatcherInterface* dispatcher, DISPID member_id,
                         REFIID iid, LCID lcid, WORD flags,
                         DISPPARAMS FAR* params, VARIANT FAR* retval,
                         EXCEPINFO FAR* exception,
                         unsigned int FAR* arg_error_index) 
{
     assert(dispatcher);
     JsCallContext_IE js_call_context(params, retval, exception);
     DispatchId dispatch_id = reinterpret_cast<DispatchId>(member_id);
     if (flags & DISPATCH_METHOD) 
     {
         if (!dispatcher->CallMethod(dispatch_id, &js_call_context)) 
         {
             return DISP_E_MEMBERNOTFOUND;
         }
     } else if (flags & DISPATCH_PROPERTYGET) {
         if (!dispatcher->GetProperty(dispatch_id, &js_call_context)) 
         {
             return DISP_E_MEMBERNOTFOUND;
         }
     } else if (flags & DISPATCH_PROPERTYPUT) {
         if (!dispatcher->SetProperty(dispatch_id, &js_call_context)) 
         {
             return DISP_E_MEMBERNOTFOUND;
         }
     } else {
         return DISP_E_MEMBERNOTFOUND;
     }

     if (js_call_context.IsExceptionSet())
     {
         return DISP_E_EXCEPTION;
     } else {
         return S_OK;
     }
}

