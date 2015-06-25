#ifndef WEBAPP_COMMON_DISPATCHER_H__
#define WEBAPP_COMMON_DISPATCHER_H__

#include <map>
#include "jscallcontext.h"
#include "win32/threadlocals.h"


typedef void* DispatchId;

typedef std::map<std::string, DispatchId> DispatcherNameList;

class DispatcherInterface {
 public:
  virtual ~DispatcherInterface() {}
  virtual bool HasMethod(DispatchId method_id) = 0;
  virtual bool HasPropertyGetter(DispatchId property_id) = 0;
  virtual bool HasPropertySetter(DispatchId property_id) = 0;
  virtual bool CallMethod(DispatchId method_id, JsCallContextBase *context) = 0;
  virtual bool GetProperty(DispatchId property_id, JsCallContextBase *context) = 0;
  virtual bool SetProperty(DispatchId property_id, JsCallContextBase *context) = 0;
  virtual const DispatcherNameList &GetMemberNames() = 0;
  virtual DispatchId GetDispatchId(const std::string &member_name) = 0;
};

template<class T>
class Dispatcher : public DispatcherInterface {
 public:

  typedef T ImplClass;

  typedef void (ImplClass::*ImplCallback)(JsCallContextBase *);

  Dispatcher(ImplClass *impl);
  virtual ~Dispatcher() {}

  static void Init();

  // DispatcherInterface:
  virtual bool HasMethod(DispatchId method_id);
  virtual bool HasPropertyGetter(DispatchId property_id);
  virtual bool HasPropertySetter(DispatchId property_id);
  virtual bool CallMethod(DispatchId method_id, JsCallContextBase *context);
  virtual bool GetProperty(DispatchId property_id, JsCallContextBase *context);
  virtual bool SetProperty(DispatchId property_id, JsCallContextBase *context);
  virtual const DispatcherNameList &GetMemberNames();
  virtual DispatchId GetDispatchId(const std::string &member_name);

 protected:
  // Register JavaScript property/methods
  static void RegisterProperty(const char *name,
                               ImplCallback getter, ImplCallback setter);
  static void RegisterMethod(const char *name, ImplCallback callback);

  //delete dispatcherData registered in threadlocals
  static void DeleteDispatcherData(void *context);

 private:
  typedef std::map<DispatchId, ImplCallback> IDList;

  struct DispatcherData {
    bool did_init_class;
    IDList property_getters;
    IDList property_setters;
    IDList methods;
    DispatcherNameList members;
    DispatcherData() : did_init_class(false) {}
  };

  static DispatcherData &GetDispatcherData();

  static IDList& GetPropertyGetterList()
  {
      return GetDispatcherData().property_getters;
  }

  static IDList& GetPropertySetterList() 
  {
      return GetDispatcherData().property_setters;
  }
  static IDList& GetMethodList() 
  {
      return GetDispatcherData().methods;
  }

  //static DispatcherData* kDispatcherData;
  static const ThreadLocals::Slot kThreadLocalsKey;
  ImplClass *impl_;
};

// Used to set up the Dispatcher for the given class.
#define DECLARE_DISPATCHER(ImplClass) \
class ImplClass; \
    template <> \
    const ThreadLocals::Slot Dispatcher<ImplClass>::kThreadLocalsKey = \
    ThreadLocals::Alloc()

// Returns the DispatchId associated with the given string.  Used for looking
// up methods and properties.
inline DispatchId GetStringIdentifier(const char *str) 
{
    return reinterpret_cast<DispatchId>(const_cast<char *>(str));
}

template<class T>
Dispatcher<T>::Dispatcher(ImplClass *impl) : impl_(impl) 
{
  // Ensure that property and method mappings are initialized.
  DispatcherData &dispathData = GetDispatcherData();

  if (!dispathData.did_init_class)
  {
    dispathData.did_init_class = true;
    Init();
  }

}

template<class T>
bool Dispatcher<T>::HasMethod(DispatchId method_id) 
{
  const IDList &methods = GetMethodList();
  return methods.find(method_id) != methods.end();
}

template<class T>
bool Dispatcher<T>::HasPropertyGetter(DispatchId property_id)
{
    const IDList &properties = GetPropertyGetterList();
    return properties.find(property_id) != properties.end();
}

template<class T>
bool Dispatcher<T>::HasPropertySetter(DispatchId property_id)
{
    const IDList &properties = GetPropertySetterList();
    return properties.find(property_id) != properties.end();
}

template<class T>
bool Dispatcher<T>::CallMethod(DispatchId method_id, JsCallContextBase *context) 
{
    const IDList &methods = GetMethodList();
    typename IDList::const_iterator method = methods.find(method_id);
    if (method == methods.end())
    {
        return false;
    }
  
    ImplCallback callback = method->second;
    (impl_->*callback)(context);
    return true;
}

template<class T>
bool Dispatcher<T>::GetProperty(DispatchId property_id,
                                JsCallContextBase *context) 
{
  const IDList &properties = GetPropertyGetterList();
  typename IDList::const_iterator property = properties.find(property_id);
  if (property == properties.end())
    return false;
  ImplCallback callback = property->second;

  //assert(IsImplCallbackValid(callback));
  (impl_->*callback)(context);
  return true;
}

template<class T>
bool Dispatcher<T>::SetProperty(DispatchId property_id,
                                JsCallContextBase *context)
{
  const IDList &properties = GetPropertySetterList();
  
  typename IDList::const_iterator property = properties.find(property_id);
  
  if (property == properties.end())
  {
    return false;
  }

  ImplCallback callback = property->second;

  (impl_->*callback)(context);
  return true;
}

template<class T>
const DispatcherNameList &Dispatcher<T>::GetMemberNames()
{
  return GetDispatcherData().members;
}

template<class T>
DispatchId Dispatcher<T>::GetDispatchId(const std::string &member_name) 
{
  const DispatcherNameList &member_names = GetMemberNames();
  
  DispatcherNameList::const_iterator result = member_names.find(member_name);
  if (result != member_names.end()) 
  {
    return result->second;
  } else {
    return NULL;
  }
}

// static
template<class T>
void Dispatcher<T>::RegisterProperty(const char *name,
                                     ImplCallback getter, ImplCallback setter) 
{
  //assert(IsImplCallbackValid(getter));
  DispatchId id = GetStringIdentifier(name);
  GetPropertyGetterList()[id] = getter;
  GetPropertySetterList()[id] = setter;
  GetDispatcherData().members[name] = id;
}

// static
template<class T>
void Dispatcher<T>::RegisterMethod(const char *name, ImplCallback callback) 
{
  DispatchId id = GetStringIdentifier(name);
  GetMethodList()[id] = callback;
  GetDispatcherData().members[name] = id;
}

// static
template<class T>
void Dispatcher<T>::DeleteDispatcherData(void *context) 
{
    DispatcherData *disp_data =
        reinterpret_cast<DispatcherData*>(context);
    delete disp_data;
}

template<class T>
typename  Dispatcher<T>::DispatcherData &Dispatcher<T>::GetDispatcherData()
{
    const ThreadLocals::Slot &key = kThreadLocalsKey;
    DispatcherData *pData = reinterpret_cast<DispatcherData*>(ThreadLocals::GetValue(key));
    if (!pData) 
    {
        pData = new DispatcherData;
        ThreadLocals::SetValue(key, pData);
    }

    return *pData;
}

#endif // WEBAPP_COMMON_DISPATCHER_H__
