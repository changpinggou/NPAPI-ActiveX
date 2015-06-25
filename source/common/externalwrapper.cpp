#include "externalwrapper.h"
#include "ie/dispatherbridge.h"


STDMETHODIMP ExternalWrapper_IE::GetTypeInfoCount(unsigned int FAR* retval) 
{
    return DispatcherGetTypeInfoCount(dispatcher_.get(), retval);
}

STDMETHODIMP ExternalWrapper_IE::GetTypeInfo(unsigned int index, LCID lcid,
                                             ITypeInfo FAR* FAR* retval) 
{
    return DispatcherGetTypeInfo(dispatcher_.get(), index, lcid, retval);
}

STDMETHODIMP ExternalWrapper_IE::GetIDsOfNames(REFIID iid, OLECHAR FAR* FAR* names,
                                          unsigned int num_names, LCID lcid, DISPID FAR* retval) 
{
    return DispatcherGetIDsOfNames(dispatcher_.get(), iid, names, num_names, lcid, retval);
}

STDMETHODIMP ExternalWrapper_IE::Invoke(DISPID member_id, REFIID iid, LCID lcid,WORD flags,
                                        DISPPARAMS FAR* params,VARIANT FAR* retval,
                                        EXCEPINFO FAR* exception,unsigned int FAR* arg_error_index) 
{
    return DispatcherInvoke(dispatcher_.get(), member_id, iid, lcid, flags,params, retval, exception, arg_error_index);
}
