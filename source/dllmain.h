// dllmain.h : 模块类的声明。
#include "resource.h"

class CQQGameAssistPluginModule : public CAtlDllModuleT< CQQGameAssistPluginModule >
{
public :
	//DECLARE_LIBID(LIBID_QQGameAssistPluginLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_REGISTRY1, "{AF076D87-D0E8-462D-8DC3-3493666DC2F6}")
};

extern class CQQGameAssistPluginModule _AtlModule;
