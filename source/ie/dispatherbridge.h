#ifndef WEBAPP_IE_DISPATHER_BRIDGE_H__
#define WEBAPP_IE_DISPATHER_BRIDGE_H__

#include <windows.h>
class DispatcherInterface;

HRESULT DispatcherGetTypeInfoCount(DispatcherInterface* dispatcher,unsigned int FAR* retval);

HRESULT DispatcherGetTypeInfo(DispatcherInterface* dispatcher,
                              unsigned int index, LCID lcid,
                              ITypeInfo FAR* FAR* retval);

HRESULT DispatcherGetIDsOfNames(DispatcherInterface* dispatcher, REFIID iid,
                                OLECHAR FAR* FAR* names, 
                                unsigned int num_names, LCID lcid,
                                DISPID FAR* retval);

HRESULT DispatcherInvoke(DispatcherInterface* dispatcher, DISPID member_id,
                         REFIID iid, LCID lcid, WORD flags,
                         DISPPARAMS FAR* params, VARIANT FAR* retval,
                         EXCEPINFO FAR* exception,
                         unsigned int FAR* arg_error_index);

#endif //WEBAPP_IE_DISPATHER_BRIDGE_H__