/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM f:\xpcom-sample\src\IFileTransferProxy.idl
 */

#ifndef __gen_IFileTransferProxy_h__
#define __gen_IFileTransferProxy_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IFileTransferProxy */
#define IFILETRANSFERPROXY_IID_STR "bd180a22-3b8a-4210-b992-4426e24e6b31"

#define IFILETRANSFERPROXY_IID \
  {0xbd180a22, 0x3b8a, 0x4210, \
    { 0xb9, 0x92, 0x44, 0x26, 0xe2, 0x4e, 0x6b, 0x31 }}

class NS_NO_VTABLE NS_SCRIPTABLE IFileTransferProxy : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IFILETRANSFERPROXY_IID)

  /* void AddSendTask (in string strUin, in string strPeerUin, in string strFilePath, in string strKey, [retval] out string strSessionId); */
  NS_SCRIPTABLE NS_IMETHOD AddSendTask(const char *strUin, const char *strPeerUin, const char *strFilePath, const char *strKey, char **strSessionId) = 0;

  /* void AddRecvTask (in string strUin, in string strPeerUin, in string strRequestCodecBuffer, in string strKey, [retval] out string strTaskInfo); */
  NS_SCRIPTABLE NS_IMETHOD AddRecvTask(const char *strUin, const char *strPeerUin, const char *strRequestCodecBuffer, const char *strKey, char **strTaskInfo) = 0;

  /* void CancelTask (in string strSessionId); */
  NS_SCRIPTABLE NS_IMETHOD CancelTask(const char *strSessionId) = 0;

  /* void SetLoginInfo (in string strUin, in string strServerToldIP, in string strServerTime); */
  NS_SCRIPTABLE NS_IMETHOD SetLoginInfo(const char *strUin, const char *strServerToldIP, const char *strServerTime) = 0;

  /* void QueryCCSendTaskInfo ([retval] out string strCCSendTaskInfo); */
  NS_SCRIPTABLE NS_IMETHOD QueryCCSendTaskInfo(char **strCCSendTaskInfo) = 0;

  /* void SetCCSendTaskResult (in string strSessionId, in string strResult); */
  NS_SCRIPTABLE NS_IMETHOD SetCCSendTaskResult(const char *strSessionId, const char *strResult) = 0;

  /* void QueryTaskState (in string strSessionId, [retval] out string strTaskState); */
  NS_SCRIPTABLE NS_IMETHOD QueryTaskState(const char *strSessionId, char **strTaskState) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IFileTransferProxy, IFILETRANSFERPROXY_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IFILETRANSFERPROXY \
  NS_SCRIPTABLE NS_IMETHOD AddSendTask(const char *strUin, const char *strPeerUin, const char *strFilePath, const char *strKey, char **strSessionId); \
  NS_SCRIPTABLE NS_IMETHOD AddRecvTask(const char *strUin, const char *strPeerUin, const char *strRequestCodecBuffer, const char *strKey, char **strTaskInfo); \
  NS_SCRIPTABLE NS_IMETHOD CancelTask(const char *strSessionId); \
  NS_SCRIPTABLE NS_IMETHOD SetLoginInfo(const char *strUin, const char *strServerToldIP, const char *strServerTime); \
  NS_SCRIPTABLE NS_IMETHOD QueryCCSendTaskInfo(char **strCCSendTaskInfo); \
  NS_SCRIPTABLE NS_IMETHOD SetCCSendTaskResult(const char *strSessionId, const char *strResult); \
  NS_SCRIPTABLE NS_IMETHOD QueryTaskState(const char *strSessionId, char **strTaskState); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IFILETRANSFERPROXY(_to) \
  NS_SCRIPTABLE NS_IMETHOD AddSendTask(const char *strUin, const char *strPeerUin, const char *strFilePath, const char *strKey, char **strSessionId) { return _to AddSendTask(strUin, strPeerUin, strFilePath, strKey, strSessionId); } \
  NS_SCRIPTABLE NS_IMETHOD AddRecvTask(const char *strUin, const char *strPeerUin, const char *strRequestCodecBuffer, const char *strKey, char **strTaskInfo) { return _to AddRecvTask(strUin, strPeerUin, strRequestCodecBuffer, strKey, strTaskInfo); } \
  NS_SCRIPTABLE NS_IMETHOD CancelTask(const char *strSessionId) { return _to CancelTask(strSessionId); } \
  NS_SCRIPTABLE NS_IMETHOD SetLoginInfo(const char *strUin, const char *strServerToldIP, const char *strServerTime) { return _to SetLoginInfo(strUin, strServerToldIP, strServerTime); } \
  NS_SCRIPTABLE NS_IMETHOD QueryCCSendTaskInfo(char **strCCSendTaskInfo) { return _to QueryCCSendTaskInfo(strCCSendTaskInfo); } \
  NS_SCRIPTABLE NS_IMETHOD SetCCSendTaskResult(const char *strSessionId, const char *strResult) { return _to SetCCSendTaskResult(strSessionId, strResult); } \
  NS_SCRIPTABLE NS_IMETHOD QueryTaskState(const char *strSessionId, char **strTaskState) { return _to QueryTaskState(strSessionId, strTaskState); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IFILETRANSFERPROXY(_to) \
  NS_SCRIPTABLE NS_IMETHOD AddSendTask(const char *strUin, const char *strPeerUin, const char *strFilePath, const char *strKey, char **strSessionId) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddSendTask(strUin, strPeerUin, strFilePath, strKey, strSessionId); } \
  NS_SCRIPTABLE NS_IMETHOD AddRecvTask(const char *strUin, const char *strPeerUin, const char *strRequestCodecBuffer, const char *strKey, char **strTaskInfo) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddRecvTask(strUin, strPeerUin, strRequestCodecBuffer, strKey, strTaskInfo); } \
  NS_SCRIPTABLE NS_IMETHOD CancelTask(const char *strSessionId) { return !_to ? NS_ERROR_NULL_POINTER : _to->CancelTask(strSessionId); } \
  NS_SCRIPTABLE NS_IMETHOD SetLoginInfo(const char *strUin, const char *strServerToldIP, const char *strServerTime) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLoginInfo(strUin, strServerToldIP, strServerTime); } \
  NS_SCRIPTABLE NS_IMETHOD QueryCCSendTaskInfo(char **strCCSendTaskInfo) { return !_to ? NS_ERROR_NULL_POINTER : _to->QueryCCSendTaskInfo(strCCSendTaskInfo); } \
  NS_SCRIPTABLE NS_IMETHOD SetCCSendTaskResult(const char *strSessionId, const char *strResult) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCCSendTaskResult(strSessionId, strResult); } \
  NS_SCRIPTABLE NS_IMETHOD QueryTaskState(const char *strSessionId, char **strTaskState) { return !_to ? NS_ERROR_NULL_POINTER : _to->QueryTaskState(strSessionId, strTaskState); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IFileTransferProxy
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IFILETRANSFERPROXY

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IFileTransferProxy)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void AddSendTask (in string strUin, in string strPeerUin, in string strFilePath, in string strKey, [retval] out string strSessionId); */
NS_IMETHODIMP _MYCLASS_::AddSendTask(const char *strUin, const char *strPeerUin, const char *strFilePath, const char *strKey, char **strSessionId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddRecvTask (in string strUin, in string strPeerUin, in string strRequestCodecBuffer, in string strKey, [retval] out string strTaskInfo); */
NS_IMETHODIMP _MYCLASS_::AddRecvTask(const char *strUin, const char *strPeerUin, const char *strRequestCodecBuffer, const char *strKey, char **strTaskInfo)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void CancelTask (in string strSessionId); */
NS_IMETHODIMP _MYCLASS_::CancelTask(const char *strSessionId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetLoginInfo (in string strUin, in string strServerToldIP, in string strServerTime); */
NS_IMETHODIMP _MYCLASS_::SetLoginInfo(const char *strUin, const char *strServerToldIP, const char *strServerTime)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void QueryCCSendTaskInfo ([retval] out string strCCSendTaskInfo); */
NS_IMETHODIMP _MYCLASS_::QueryCCSendTaskInfo(char **strCCSendTaskInfo)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCCSendTaskResult (in string strSessionId, in string strResult); */
NS_IMETHODIMP _MYCLASS_::SetCCSendTaskResult(const char *strSessionId, const char *strResult)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void QueryTaskState (in string strSessionId, [retval] out string strTaskState); */
NS_IMETHODIMP _MYCLASS_::QueryTaskState(const char *strSessionId, char **strTaskState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IFileTransferProxy_h__ */
