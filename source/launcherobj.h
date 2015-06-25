#ifndef SCRIPTABLE_PLAY_CTRL_OBJ_h__
#define SCRIPTABLE_PLAY_CTRL_OBJ_h__

#include <map>
#include "npapi.h"
#include "npruntime.h"
#include "plugin.h"
#include "scriptable_obj_base.h"
#include "qg_string_constants.h"

class ScriptablePluginObject : public ScriptablePluginObjectBase<ScriptablePluginObject>
{
public:
  DeclareHandlerMethod(LaunchQQGameHall)
  DeclareHandlerMethod(GetQQGameHallVer)
  DeclareHandlerMethod(GetPluginCurVer)
  DeclareHandlerProperty(GetPlugin)

public:
  ScriptablePluginObject(NPP npp) : m_bAllow(false), npp_(npp){
    RegisterMethod("launchQQGameHall", &ScriptablePluginObject::LaunchQQGameHall);
    RegisterMethod("getGameHallCurVer", &ScriptablePluginObject::GetQQGameHallVer);
    RegisterMethod("getPluginCurVer", &ScriptablePluginObject::GetPluginCurVer);
	  RegisterProperty("PluginType", &ScriptablePluginObject::GetPlugin);
  }

  virtual bool HasMethod(NPIdentifier name);
  virtual bool HasProperty(NPIdentifier name);
  virtual bool GetProperty(NPIdentifier name, NPVariant *result);
  virtual bool Invoke(NPIdentifier name, const NPVariant *args,
    uint32_t argCount, NPVariant *result);
  virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount,
    NPVariant *result);
  void SetAllow(bool bAllow){
    m_bAllow = bAllow;
  }
protected:
  bool m_bAllow;
  NPP npp_;
};

#endif // pluginbase_h_
