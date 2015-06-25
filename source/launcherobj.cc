#include "StdAfx.h"
#include <io.h>
#include "launcherobj.h"
#include "string_util.h"

template<>
ScriptablePluginObjectBase<ScriptablePluginObject>::DispatcherNameList 
  ScriptablePluginObjectBase<ScriptablePluginObject>::g_dispather_name_list_;

template<>
ScriptablePluginObjectBase<ScriptablePluginObject>::DispatcherCallbackList 
  ScriptablePluginObjectBase<ScriptablePluginObject>::g_dispather_callback_list_;

template<>
ScriptablePluginObjectBase<ScriptablePluginObject>::DispatcherCallbackPropList ScriptablePluginObjectBase<ScriptablePluginObject>::g_dispather_property_callback_list_;

bool ScriptablePluginObject::HasMethod(NPIdentifier name)
{
  DispatcherCallbackList::iterator it = g_dispather_callback_list_.find(name);
  if (it != g_dispather_callback_list_.end()){
    return true;
  }

  return false;
}

bool ScriptablePluginObject::HasProperty(NPIdentifier name)
{
  DispatcherCallbackPropList::iterator it = g_dispather_property_callback_list_.find(name);
  if (it != g_dispather_property_callback_list_.end()){
    return true;
  }
  return false;
}

bool ScriptablePluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
  VOID_TO_NPVARIANT(*result);
  DispatcherCallbackPropList::iterator it = g_dispather_property_callback_list_.find(name);
  if (it == g_dispather_property_callback_list_.end()){
    return false;
  }
  ImplPropCallback callback = it->second;

  (this->*callback)(name, result);
  return true;
}

bool ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args, 
                                    uint32_t argCount, NPVariant *result){
	//::MessageBox(NULL, L"QQGameHallAssist::Invoke", L"QQGameHallAssist::Invoke", MB_OK);
  DispatcherCallbackList::iterator it = g_dispather_callback_list_.find(name);
  if (it == g_dispather_callback_list_.end()){
    return false;
  }
  ImplCallback callback = it->second;

  (this->*callback)(args, argCount, result);
  return true;
}

bool ScriptablePluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount,
                                           NPVariant *result)
{

  STRINGZ_TO_NPVARIANT(_strdup("default method return val"), *result);
  return true;
}

// class ConstructablePluginObject : public ScriptablePluginObjectBase<ConstructablePluginObject>
// {
// public:
//   ConstructablePluginObject(NPP npp) : npp_(npp){
// 
//   }
// 
//   virtual bool Construct(const NPVariant *args, uint32_t argCount,
//     NPVariant *result);
// protected:
//   NPP npp_;
// };
// 
// static NPObject *AllocateConstructablePluginObject(NPP npp, NPClass *aClass)
// {
//   return new ConstructablePluginObject(npp);
// }
// 
// DECLARE_NPOBJECT_CLASS_WITH_BASE(ConstructablePluginObject,AllocateConstructablePluginObject);
// 
// bool ConstructablePluginObject::Construct(const NPVariant *args, 
//   uint32_t argCount, NPVariant *result)
// {
//   //printf("Creating new ConstructablePluginObject!\n");
// 
//   NPObject *myobj =
//     NPN_CreateObject(npp_, GET_NPOBJECT_CLASS(ConstructablePluginObject));
//   if (!myobj)
//     return false;
// 
//   OBJECT_TO_NPVARIANT(myobj, *result);
// 
//   return true;
// }

void ScriptablePluginObject::GetPlugin(NPIdentifier name, NPVariant *result){
//   NPObject *myobj =
//     NPN_CreateObject(npp_, GET_NPOBJECT_CLASS(ScriptablePluginObject));
//   if (!myobj) {
//     return;
//   }
  if (!npp_){
    return;
  }
  CPlugin * plugin = (CPlugin *)npp_->pdata;
  if (!plugin){
    return;
  }

  OBJECT_TO_NPVARIANT(plugin->GetScriptableObject(), *result);
}

void ScriptablePluginObject::LaunchQQGameHall(const NPVariant *args, uint32_t argCount, NPVariant *result){
  if (!npp_){
    return;
  }
  CPlugin * plugin = (CPlugin *)npp_->pdata;
  if (!plugin){
    return;
  }

  NPString lvalue = NPVARIANT_TO_STRING(args[0]);
  std::string strCmdParam(lvalue.utf8characters);
  std::wstring wstrCmdParam = StringUtil::Utf8ToUnicode(strCmdParam.c_str());
  plugin->LaunchQQGameWithParam(wstrCmdParam);
}

void ScriptablePluginObject::GetQQGameHallVer(const NPVariant *args, uint32_t argCount, NPVariant *result){
  if (!npp_){
    return;
  }
  CPlugin * plugin = (CPlugin *)npp_->pdata;
  if (!plugin){
    return;
  }

  std::wstring strCurVer;
  plugin->GetQQGameHallVer(strCurVer);
  std::string strCurVerA = StringUtil::UnicodetoUtf8(strCurVer.c_str());


  int len = strCurVerA.length() + 1;
  NPUTF8  *utf8_chars = static_cast<NPUTF8 *>(NPN_MemAlloc(len)); 
  memset( utf8_chars, 0, len );
  strncpy_s( utf8_chars, len, strCurVerA.c_str(), len);

  if (result){
    STRINGZ_TO_NPVARIANT(utf8_chars, *result);
  }
}

void ScriptablePluginObject::GetPluginCurVer(const NPVariant *args, uint32_t argCount, NPVariant *result){
  if (!npp_){
    return;
  }
  CPlugin * plugin = (CPlugin *)npp_->pdata;
  if (!plugin){
    return;
  }

  std::wstring strCurVer;
  plugin->GetPluginVer(strCurVer);
  std::string strCurVerA = StringUtil::UnicodetoUtf8(strCurVer.c_str());


  int len = strCurVerA.length() + 1;
  NPUTF8  *utf8_chars = static_cast<NPUTF8 *>(NPN_MemAlloc(len)); 
  memset( utf8_chars, 0, len );
  strncpy_s( utf8_chars, len, strCurVerA.c_str(), len);

  if (result){
    STRINGZ_TO_NPVARIANT(utf8_chars, *result);
  }
}