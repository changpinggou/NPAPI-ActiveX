#ifndef QQGAME_HALL_ASSIST_IE_H__
#define QQGAME_HALL_ASSIST_IE_H__

#include <objsafe.h>
#include <windows.h>
#include <string>
#include "QQGameAssistPlugin_i.h"

// A macro to disallow the evil copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
  TypeName(const TypeName&);                    \
  void operator=(const TypeName&)


// This is just a thin COM wrapper around a Dispatcher-backed
// GearsFactoryImpl instance.
class ATL_NO_VTABLE QQGameHallAssist
    : public CComObjectRootEx<CComMultiThreadModel>,
      public CComCoClass<QQGameHallAssist, &CLSID_QQGameHallAssist>,
      public IObjectWithSiteImpl<QQGameHallAssist>,
      public IObjectSafetyImpl<QQGameHallAssist,
                               INTERFACESAFE_FOR_UNTRUSTED_CALLER +
                               INTERFACESAFE_FOR_UNTRUSTED_DATA>,
      public IDispatch {
 public:
  BEGIN_COM_MAP(QQGameHallAssist)
    COM_INTERFACE_ENTRY(IObjectWithSite)
    COM_INTERFACE_ENTRY(IObjectSafety)
    COM_INTERFACE_ENTRY(IDispatch)
  END_COM_MAP()

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  DECLARE_REGISTRY_RESOURCEID(IDR_REGISTRY1)
  // End boilerplate code.

  QQGameHallAssist() {}

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

  // IObjectWithSite: SetSite.
  STDMETHOD(SetSite)(IUnknown *site);


private:
  DISALLOW_EVIL_CONSTRUCTORS(QQGameHallAssist);
};

OBJECT_ENTRY_AUTO(__uuidof(QQGameHallAssist), QQGameHallAssist)

#endif  //QQGAME_HALL_ASSIST_IE_H__
