#pragma once

#include "scriptable_base.h"
#include "define.h"
//#include "Common/Include/TXString.h"

class QscallSPObject : public ScriptablePluginObjectBase
{
public:
	QscallSPObject(NPP npp);
	~QscallSPObject();

	virtual bool HasMethod(NPIdentifier name);
	virtual bool HasProperty(NPIdentifier name);
	virtual bool GetProperty(NPIdentifier name, NPVariant *result);
	virtual bool Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
	virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);

protected:
	bool _DealTencentString(const NPVariant *args, uint32_t argCount, NPVariant *result);
	bool _InitActiveX(const NPVariant *args, uint32_t argCount, NPVariant *result);
	bool _CallActiveX(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
	void _VarientFromNPVariant(const NPVariant *args, VARIANT *vars);
	void _NPVarientFromVarient(const VARIANT *vars, NPVariant *args);

protected:
	NPObject *m_pCallback;
	NPIdentifier m_IdDealTencentString;
	NPIdentifier m_IdInitActiveX;
	CComPtr<IDispatch> m_pAxDispatch;
};

static NPObject * AllocateQscallSPObject(NPP npp, NPClass *aClass)
{
	return new QscallSPObject(npp);
}

DECLARE_NPOBJECT_CLASS_WITH_BASE(QscallSPObject, AllocateQscallSPObject);