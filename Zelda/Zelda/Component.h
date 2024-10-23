#pragma once
#include "CBase.h"
#include "CObj.h"

class Component : public CBase
{
private:
	CObj* m_Owner;
	const COMPONENT_TYPE m_Type;

public:
	COMPONENT_TYPE GetType() { return m_Type; }
	CObj* GetOwner() { return m_Owner; }

public:
	virtual void FinalTick() = 0;

public:
	Component(COMPONENT_TYPE _Type);
	~Component();

public:
	friend class CObj;
};

