#pragma once
#include "Component.h"
#include "CObj.h"
class Collider : public Component
{
	bool	m_Trigger;

	Vec2	m_Offset;
	Vec2	m_Scale;

	bool	m_Active;
	int		m_OverlapCount;

public:
	Collider();
	~Collider();

public:
	virtual void FinalTick();

public:
	void SetTrigger(bool _Trigger) { m_Trigger = _Trigger; }
	bool GetTrigger() { return m_Trigger; }

	void SetPos(Vec2 _Offset) { m_Offset = _Offset; }
	Vec2 GetPos( ) const { return m_Offset; }

	Vec2 GetGlobalPos()  { return (GetOwner()->GetPos() + m_Offset); }

	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	Vec2 GetScale() const { return m_Scale; }

	void SetActive(bool _Active) { m_Active = _Active; }
	bool GetActive() const { return m_Active; }

	bool GetCollision() const { return m_OverlapCount; }

public:
	void EnterOverlap(Collider* _Other);
	void Overlap(Collider* _Other);
	void ExitOverlap(Collider* _Other);

};

