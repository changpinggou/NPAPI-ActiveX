#ifndef SCRIPTABLE_OBJ_BASE_h_
#define SCRIPTABLE_OBJ_BASE_h_

#include <map>
#include "npapi.h"
#include "npruntime.h"
#include "plugin.h"

#define DeclareHandlerMethod(name) void name##(const NPVariant *args, uint32_t argCount, NPVariant *result);
#define DeclareHandlerProperty(name) void name##(NPIdentifier name, NPVariant *result);

#define DECLARE_NPOBJECT_CLASS_WITH_BASE(_class, ctor)                \
  static NPClass s##_class##_NPClass = {                              \
  NP_CLASS_STRUCT_VERSION_CTOR,                                       \
  ctor,                                                               \
  Dispatcher<_class>::_Deallocate,                                    \
  Dispatcher<_class>::_Invalidate,                                    \
  Dispatcher<_class>::_HasMethod,                                     \
  Dispatcher<_class>::_Invoke,                                        \
  Dispatcher<_class>::_InvokeDefault,                                 \
  Dispatcher<_class>::_HasProperty,                                   \
  Dispatcher<_class>::_GetProperty,                                   \
  Dispatcher<_class>::_SetProperty,                                   \
  Dispatcher<_class>::_RemoveProperty,                                \
  Dispatcher<_class>::_Enumerate,                                     \
  Dispatcher<_class>::_Construct                                      \
}

#define GET_NPOBJECT_CLASS(_class) &s##_class##_NPClass

template<class T>
class ScriptablePluginObjectBase : public NPObject{
public:
  typedef T ImplClass;
  typedef void (ImplClass::*ImplCallback)(const NPVariant *args, uint32_t argCount, NPVariant *result);
  typedef void (ImplClass::*ImplPropCallback)(NPIdentifier name, NPVariant *result);
  typedef std::map<std::string,NPIdentifier> DispatcherNameList;
  typedef std::map<NPIdentifier, ImplCallback> DispatcherCallbackList;
  typedef std::map<NPIdentifier, ImplPropCallback> DispatcherCallbackPropList;
  static DispatcherNameList g_dispather_name_list_;
  static DispatcherCallbackList g_dispather_callback_list_;
  static DispatcherCallbackPropList g_dispather_property_callback_list_;
  static void RegisterMethod(const char *name, ImplCallback callback);
  static void RegisterProperty(const char *name, ImplPropCallback callback);

public:
  ScriptablePluginObjectBase(){
  }

  virtual ~ScriptablePluginObjectBase(){
  }

  // Virtual NPObject hooks called through this base class. Override
  // as you see fit.
  virtual void Invalidate();
  virtual bool HasMethod(NPIdentifier name);
  virtual bool Invoke(NPIdentifier name, const NPVariant *args,
                      uint32_t argCount, NPVariant *result);
  virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount,NPVariant *result);
  virtual bool HasProperty(NPIdentifier name);
  virtual bool GetProperty(NPIdentifier name, NPVariant *result);
  virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
  virtual bool RemoveProperty(NPIdentifier name);
  virtual bool Enumerate(NPIdentifier **identifier, uint32_t *count);
  virtual bool Construct(const NPVariant *args, uint32_t argCount,
                         NPVariant *result);
};

template<class T>
void ScriptablePluginObjectBase<T>::Invalidate(){
}

template<class T>
bool ScriptablePluginObjectBase<T>::HasMethod(NPIdentifier name){
  return false;
}

template<class T>
bool ScriptablePluginObjectBase<T>::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result){
  return false;
}

template<class T>
bool ScriptablePluginObjectBase<T>::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result){
  return false;
}

template<class T>
bool ScriptablePluginObjectBase<T>::HasProperty(NPIdentifier name){
  return false;
  //return (name == sBar_id || name == sPluginType_id);
}

template<class T>
bool ScriptablePluginObjectBase<T>::GetProperty(NPIdentifier name, NPVariant *result){
  VOID_TO_NPVARIANT(*result);
  return true;
}

template<class T>
bool ScriptablePluginObjectBase<T>::SetProperty(NPIdentifier name, const NPVariant *value){
  return false;
}

template<class T>
bool ScriptablePluginObjectBase<T>::RemoveProperty(NPIdentifier name){
  return false;
}

template<class T>
bool ScriptablePluginObjectBase<T>::Enumerate(NPIdentifier **identifier, uint32_t *count){
  return false;
}

template<class T>
bool ScriptablePluginObjectBase<T>::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result){
  return false;
}

template<class T>
void ScriptablePluginObjectBase<T>::RegisterMethod(const char *name, ImplCallback callback){
  if (!name){
    return;
  }
  NPIdentifier id = NPN_GetStringIdentifier(name);
  g_dispather_name_list_[std::string(name)] = id;
  g_dispather_callback_list_[id] = callback;
}

template<class T>
void ScriptablePluginObjectBase<T>::RegisterProperty(const char *name, ImplPropCallback callback){
  if (!name){
    return;
  }
  NPIdentifier id = NPN_GetStringIdentifier(name);
  g_dispather_property_callback_list_[id] = callback;
}

template<class T>
class Dispatcher{
public:
  typedef T ImplClass;
  static void _Deallocate(NPObject *npobj);
  static void _Invalidate(NPObject *npobj);
  static bool _HasMethod(NPObject *npobj, NPIdentifier name);
  static bool _Invoke(NPObject *npobj, NPIdentifier name,
    const NPVariant *args, uint32_t argCount,
    NPVariant *result);
  static bool _InvokeDefault(NPObject *npobj, const NPVariant *args,
    uint32_t argCount, NPVariant *result);
  static bool _HasProperty(NPObject * npobj, NPIdentifier name);
  static bool _GetProperty(NPObject *npobj, NPIdentifier name,
    NPVariant *result);
  static bool _SetProperty(NPObject *npobj, NPIdentifier name,
    const NPVariant *value);
  static bool _RemoveProperty(NPObject *npobj, NPIdentifier name);
  static bool _Enumerate(NPObject *npobj, NPIdentifier **identifier,
    uint32_t *count);
  static bool _Construct(NPObject *npobj, const NPVariant *args,
    uint32_t argCount, NPVariant *result);
private:
  ImplClass *impl_;
};


template<class T>
void Dispatcher<T>::_Deallocate(NPObject *npobj){
}

template<class T>
void Dispatcher<T>::_Invalidate(NPObject *npobj){
  return ((T*)npobj)->Invalidate();
}

template<class T>
bool Dispatcher<T>::_HasMethod(NPObject *npobj, NPIdentifier name){
  return ((T*)npobj)->HasMethod(name);
}

template<class T>
bool Dispatcher<T>::_Invoke(NPObject *npobj, NPIdentifier name,const NPVariant *args, uint32_t argCount, NPVariant *result){
  return ((T*)npobj)->Invoke(name, args, argCount, result);
}

template<class T>
bool Dispatcher<T>::_InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result){
  return ((T*)npobj)->InvokeDefault(args, argCount, result);
}

template<class T>
bool Dispatcher<T>::_HasProperty(NPObject * npobj, NPIdentifier name){
  return ((T*)npobj)->HasProperty(name);
}

template<class T>
bool Dispatcher<T>::_GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result){
  return ((T*)npobj)->HasProperty(name);
}

template<class T>
bool Dispatcher<T>::_SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value){
  return ((T*)npobj)->SetProperty(name, value);
}

template<class T>
bool Dispatcher<T>::_RemoveProperty(NPObject *npobj, NPIdentifier name){
  return ((T*)npobj)->RemoveProperty(name);
}

template<class T>
bool Dispatcher<T>::_Enumerate(NPObject *npobj, NPIdentifier **identifier,uint32_t *count){
  return ((T*)npobj)->Enumerate(identifier, count);
}

template<class T>
bool Dispatcher<T>::_Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result){
  return ((T*)npobj)->Construct(args, argCount, result);
}

#endif // pluginbase_h_
