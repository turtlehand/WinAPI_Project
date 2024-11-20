#pragma once
#include "CBase.h"
#include "CObj.h"

class GComponent : public CBase
{
private:
	CObj* m_Owner;
	const COMPONENT_TYPE m_Type;

	bool m_PrevEnabled;
	bool m_Enabled;

public:
	COMPONENT_TYPE GetType() { return m_Type; }
	CObj* GetOwner() { return m_Owner; }
	void SetEnabled(bool _Enabled);

public:
	virtual void Awake() {};
	virtual void FinalTick() = 0;

public:
	GComponent(COMPONENT_TYPE _Type);
	~GComponent();

public:
	friend class CObj;
	friend class TaskManager;
};

