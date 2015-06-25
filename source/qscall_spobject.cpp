#include "qscall_spobject.h"
//#include "Common/Include/Log.h"
//#include "Common/Include/UtilCoreConvert.h"
#include "fakesite.h"
#include "Convert.h"
//#include <winbase.h>
//#include <winuser.h>

#define	LOGFILTER		L"QscallSPObject"
#define MAX_PARAM_NUM	20

QscallSPObject::QscallSPObject(NPP npp) : 
ScriptablePluginObjectBase(npp)
{
	m_IdDealTencentString	= NPN_GetStringIdentifier("DealTencentString");
	m_IdInitActiveX			= NPN_GetStringIdentifier("InitActiveX");
}

QscallSPObject::~QscallSPObject()
{

}

bool QscallSPObject::HasProperty(NPIdentifier name)
{	
	return PR_TRUE;
}

bool QscallSPObject::GetProperty(NPIdentifier name, NPVariant *result)
{
	VOID_TO_NPVARIANT(*result);
	return PR_TRUE;
}

bool QscallSPObject::HasMethod(NPIdentifier name)
{
	return PR_TRUE;
}

bool QscallSPObject::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	VOID_TO_NPVARIANT(*result);
	if ( name == m_IdDealTencentString )
	{
		return _DealTencentString(args, argCount, result);
	}
	else if ( name == m_IdInitActiveX )
	{
		return _InitActiveX(args, argCount, result);
	}

	//return true;
	//调用activex
	return _CallActiveX(name, args, argCount, result);
}

bool QscallSPObject::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	VOID_TO_NPVARIANT(*result);
	return PR_TRUE;
}

bool QscallSPObject::_DealTencentString(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	//TXLog2(LOGFILTER, L"%s", L"_DealTencentString");
	BOOLEAN_TO_NPVARIANT(false, *result);

	if ( argCount != 1 || !NPVARIANT_IS_STRING(args[0]) )
	{
		//TXLog2(LOGFILTER, L"%s", L"err: _DealTencentString argCount < 1 || !NPVARIANT_IS_STRING(args[0])");
		return PR_TRUE;		
	}
	
	NPString nsTencentString = NPVARIANT_TO_STRING(args[0]);
	CString strTencentString = _T("\"") + Util::Convert::Utf8ToWS(nsTencentString.utf8characters, nsTencentString.utf8length) + _T("\"");

	//ShellExecute()
	CRegKey keyTencent;
	if ( ERROR_SUCCESS == keyTencent.Create(HKEY_CLASSES_ROOT, L"Tencent", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ) )
	{
		TCHAR szPath[MAX_PATH] = {0};
		ULONG uPathSize = MAX_PATH;
		if ( ERROR_SUCCESS == keyTencent.QueryStringValue(_T("URL Protocol"), szPath, &uPathSize) )
		{
			if ( 32 < (UINT)ShellExecute(NULL, _T("open"), szPath, (LPCTSTR)strTencentString, NULL, SW_SHOWNORMAL) )
			{
				BOOLEAN_TO_NPVARIANT(true, *result);
			}
		}			
		keyTencent.Close();
	}	
	
	return PR_TRUE;
}

bool QscallSPObject::_InitActiveX(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	//TXLog2(LOGFILTER, L"%s", L"_InitActiveX");
	BOOLEAN_TO_NPVARIANT(false, *result);

	if ( argCount < 1 || !NPVARIANT_IS_STRING(args[0]) )
	{
		//TXLog2(LOGFILTER, L"%s", L"err: _InitActiveX argCount < 1 || !NPVARIANT_IS_STRING(args[0])");
		return PR_TRUE;		
	}

	NPString nsActiveXName = NPVARIANT_TO_STRING(args[0]);
	CString strActiveXName = Util::Convert::Utf8ToWS(nsActiveXName.utf8characters, nsActiveXName.utf8length);

	CLSID clsidActiveX;
	if ( SUCCEEDED( CLSIDFromProgID(strActiveXName, &clsidActiveX) ) )
	{
		CFakeSite *pFakeSite = new CComObjectNoLock<CFakeSite>;
		if ( pFakeSite != NULL )
		{
			CComPtr<IUnknown> pUnknown;
			pFakeSite->QueryInterface(IID_IUnknown, (void**)&pUnknown);
			CComPtr<IObjectWithSite> pSite = NULL;
			CoCreateInstance(clsidActiveX, NULL, CLSCTX_ALL, IID_IObjectWithSite, (void**)&pSite);
			if ( pSite != NULL )
			{
				if ( FAILED( pSite->SetSite(pUnknown) ) )
				{
					//TXLog2(LOGFILTER, L"err: _InitActiveX SetSite failed g_strLocationURL[%s]", (LPCTSTR)g_strLocationURL);
					return PR_TRUE;
				}
			}
		}

		m_pAxDispatch = NULL;
		HRESULT hr = CoCreateInstance(clsidActiveX, NULL, CLSCTX_ALL, IID_IDispatch, (void**)&m_pAxDispatch);
		//这里后续需要手动调用isite接口进行校验
		BOOLEAN_TO_NPVARIANT(m_pAxDispatch != NULL, *result);
	}
	
	return PR_TRUE;
}

bool QscallSPObject::_CallActiveX(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	//TXLog2(LOGFILTER, L"%s", L"_CallActiveX");
	VOID_TO_NPVARIANT(*result);
	if ( NULL == m_pAxDispatch || argCount > MAX_PARAM_NUM )
	{
		//TXLog2(LOGFILTER, L"%s", L"err: _CallActiveX NULL == m_pAxDispatch || argCount > MAX_PARAM_NUM");
		return PR_TRUE;
	}

	if ( !NPN_IdentifierIsString(name) )
	{
		//TXLog2(LOGFILTER, L"%s", L"err: _CallActiveX name is not string");
		return PR_TRUE;
	}

	NPUTF8 * utf8Identrifier = NPN_UTF8FromIdentifier(name);
	CString strIdentrifier = Util::Convert::Utf8ToWS(utf8Identrifier, strlen(utf8Identrifier));
	
	{
		LPOLESTR rgwsz[1];
		rgwsz[0] = T2OLE((LPTSTR)strIdentrifier.GetString());
		DISPID id;
		if ( SUCCEEDED( m_pAxDispatch->GetIDsOfNames(IID_NULL, &rgwsz[0], 1, 0, &id) ) )
		{
			CComVariant varargs[MAX_PARAM_NUM];
			for (UINT i = 0; i < argCount; ++i)
			{
				VariantInit(&varargs[i]);
				_VarientFromNPVariant(&args[i], &varargs[i]);
			}

			CComVariant varResult;
			VariantInit(&varResult);

			DISPPARAMS dp = {varargs, NULL, argCount, 0};
			if ( SUCCEEDED( m_pAxDispatch->Invoke(id, IID_NULL, 0, DISPATCH_METHOD, &dp, &varResult, 0, 0) ) )
			{
				_NPVarientFromVarient(&varResult, result);
			}
		}
	}
	
	NPN_MemFree(utf8Identrifier);
	
	return PR_TRUE;
}

void QscallSPObject::_VarientFromNPVariant(const NPVariant *args, VARIANT *vars)
{
	//MessageBox( NULL, _T(__FUNCTION__), NULL, 0 );

	switch ( args->type )
	{
	case NPVariantType_Void:
		{
			vars->vt = VT_EMPTY;
		}
	case NPVariantType_Null:
		{
			vars->vt = VT_NULL;
		}
		break;
	case NPVariantType_Bool:
		{
			vars->vt = VT_BOOL;
			vars->boolVal = NPVARIANT_TO_BOOLEAN(*args);
		}
		break;
	case NPVariantType_Int32:
		{
			vars->vt = VT_I4;
			vars->intVal = NPVARIANT_TO_INT32(*args);
		}
		break;
	case NPVariantType_Double:
		{
			vars->vt = VT_R8;
			vars->dblVal = NPVARIANT_TO_DOUBLE(*args);
		}
		break;
	case NPVariantType_String:
		{
			NPString nsTemp = NPVARIANT_TO_STRING(*args);
			vars->vt = VT_BSTR;
			vars->bstrVal = Util::Convert::Utf8ToWS(nsTemp.utf8characters, nsTemp.utf8length).AllocSysString();
		}
		break;
	default:
		break;
	}
}

void QscallSPObject::_NPVarientFromVarient(const VARIANT *vars, NPVariant *args)
{
	switch ( vars->vt )
	{
	case VT_EMPTY:
	case VT_VOID:
		{
			VOID_TO_NPVARIANT(*args);
		}
	case VT_NULL:
		{
			NULL_TO_NPVARIANT(*args);
		}
		break;
	case VT_BOOL:
		{
			BOOLEAN_TO_NPVARIANT((vars->vt & VT_BYREF) ? *vars->pboolVal : vars->boolVal, *args);
		}
		break;
	case VT_I1:
		{
			INT32_TO_NPVARIANT((vars->vt & VT_BYREF) ? *vars->pcVal : vars->cVal, *args);
		}
		break;
	case VT_UI1:
		{
			INT32_TO_NPVARIANT((vars->vt & VT_BYREF) ? *vars->pbVal : vars->bVal, *args);
		}
		break;
	case VT_I2:
		{
			INT32_TO_NPVARIANT((vars->vt & VT_BYREF) ? *vars->piVal : vars->iVal, *args);
		}
		break;
	case VT_UI2:
		{
			INT32_TO_NPVARIANT((vars->vt & VT_BYREF) ? *vars->puiVal : vars->uiVal, *args);
		}
		break;
	case VT_I4:
	case VT_INT:
		{
			INT32_TO_NPVARIANT((vars->vt & VT_BYREF) ? *vars->plVal : vars->lVal, *args);
		}
		break;
	case VT_UI4:	
	case VT_UINT:
		{
			INT32_TO_NPVARIANT((vars->vt & VT_BYREF) ? *vars->pulVal : vars->ulVal, *args);
		}
		break;
	case VT_R4:
		{
			DOUBLE_TO_NPVARIANT((vars->vt & VT_BYREF) ? *vars->pfltVal : vars->fltVal, *args);
		}
		break;
	case VT_R8:
		{
			DOUBLE_TO_NPVARIANT((vars->vt & VT_BYREF) ? *vars->pdblVal : vars->dblVal, *args);
		}
		break;
	case VT_BSTR:
		{
			CComBSTR bsTemp = (vars->vt & VT_BYREF) ? *vars->pbstrVal : vars->bstrVal;
			CStringA strATemp = Util::Convert::Utf8FromWS( (BSTR)bsTemp, bsTemp.Length() );
			NPUTF8 * utf8Val = (NPUTF8 *)NPN_MemAlloc(strATemp.GetLength());
			strcpy_s(utf8Val, strATemp.GetLength(), strATemp.GetString());
			STRINGZ_TO_NPVARIANT(utf8Val, *args);
		}
		break;
	default:
		break;
	}
}