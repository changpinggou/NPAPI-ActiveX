#include "stdafx.h"
#include "qqgame_assist_ie.h"
#include "common/jscallcontext.h"
#include "qqgame_util.h"
#include "qg_string_constants.h"
#include "string_util.h"


STDMETHODIMP QQGameHallAssist::SetSite(IUnknown *site) {
  HRESULT hr = IObjectWithSiteImpl<QQGameHallAssist>::SetSite(site);
  return hr;
}


HRESULT QQGameHallAssist::GetTypeInfoCount(unsigned int FAR* retval) {
  return E_FAIL;
}


HRESULT QQGameHallAssist::GetTypeInfo(unsigned int index, LCID lcid,
                                  ITypeInfo FAR* FAR* retval) {
  return E_FAIL;
}


HRESULT QQGameHallAssist::GetIDsOfNames(REFIID iid, OLECHAR FAR* FAR* names,
                                    unsigned int num_names, LCID lcid, 
                                    DISPID FAR* retval) {
    std::wstring name_as_string(static_cast<wchar_t *>(*names));
    if (QQGameHall::kApiLaunchQQGameHall == name_as_string) {
      *retval = reinterpret_cast<DISPID>(&QQGameHall::kApiLaunchQQGameHall);
      return S_OK;
    }else if (QQGameHall::kApiGetQQGameHallVer == name_as_string){
      *retval = reinterpret_cast<DISPID>(&QQGameHall::kApiGetQQGameHallVer);
      return S_OK;
    }else if (QQGameHall::kApiGetPluginCurVer == name_as_string){
      *retval = reinterpret_cast<DISPID>(&QQGameHall::kApiGetPluginCurVer);
      return S_OK;
    }
    return E_FAIL;

}


HRESULT QQGameHallAssist::Invoke(DISPID member_id, REFIID iid, LCID lcid,
                             WORD flags, DISPPARAMS FAR* params,
                             VARIANT FAR* retval, EXCEPINFO FAR* exception,
                             unsigned int FAR* arg_error_index) {
#ifdef _DEBUG
	  ::MessageBox(NULL, L"QQGameHallAssist::Invoke", L"QQGameHallAssist::Invoke", MB_OK);
#endif

    JsCallContext_IE js_call_context(params, retval, exception);
    if (member_id == reinterpret_cast<DISPID>(&QQGameHall::kApiLaunchQQGameHall)) {

      std::wstring cmdParam;
      const int argc = 1;
      JsArgument argv[argc] = {
        { JSPARAM_OPTIONAL, JSPARAM_STRING16, &cmdParam},
      };

      js_call_context.GetArguments(argc, argv);

      if (js_call_context.IsExceptionSet()) {
          return DISP_E_EXCEPTION;
      }

	  if (cmdParam.length() > QQGAME_MAX_PARAM_LENGTH){
		js_call_context.SetException(L"param exceed limit");
		return DISP_E_EXCEPTION;
	  }

	  std::wstring strFullPath;
	  if (!qqgame::GetQQGwpExePath(strFullPath)){
		  js_call_context.SetException(L"QQGameHall doesn't exist");
		  return DISP_E_EXCEPTION;
	  }

	  bool result = qqgame::LaunchQQGwpInternal(strFullPath, cmdParam);

	  return result ? S_OK : DISP_E_EXCEPTION;
    }else if (member_id == reinterpret_cast<DISPID>(&QQGameHall::kApiGetQQGameHallVer)){
      std::wstring strVerInfo;
      qqgame::GetQQGameCUVer(strVerInfo);
      js_call_context.SetReturnValue(JSPARAM_STRING16, &strVerInfo);
      return S_OK;
    }else if (member_id == reinterpret_cast<DISPID>(&QQGameHall::kApiGetPluginCurVer)){
      std::wstring strVerInfo;
      qqgame::GetPluginCUVer(strVerInfo);
      OutputDebugStr(L"QQGameHallAssist::Invoke::getPluginCurVer::begin");      
      js_call_context.SetReturnValue(JSPARAM_STRING16, &strVerInfo);
      OutputDebugStr(strVerInfo.c_str());
      OutputDebugStr(L"QQGameHallAssist::Invoke::getPluginCurVer::end");
      return S_OK;
    }else if(member_id == 0){
      return S_OK; // 兼容IE6,IE6产生异常会终止脚本执行
    }else{
      js_call_context.SetException(L"has not been implemented");
      return DISP_E_EXCEPTION;
    }

    return E_FAIL;
}
