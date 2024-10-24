#pragma once
#include "GComponent.h"
#include "CObj.h"
class GCollider : public GComponent
{
	COLLIDER_TYPE m_Type;

	bool	m_Trigger;

	Vec2	m_Offset;
	Vec2	m_Scale;

	int		m_OverlapCount;

public:
	GCollider(COLLIDER_TYPE _Type);
	~GCollider();

public:
	virtual void FinalTick() = 0;

public:
	void SetTrigger(bool _Trigger) { m_Trigger = _Trigger; }
	bool GetTrigger() { return m_Trigger; }

	void SetPos(Vec2 _Offset) { m_Offset = _Offset; }
	Vec2 GetPos( ) const { return m_Offset; }

	Vec2 GetGlobalPos()  { return (GetOwner()->GetPos() + m_Offset); }

	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	Vec2 GetScale() const { return m_Scale; }

	bool GetCollision() const { return m_OverlapCount; }

	int GetOverlapCount() const { return m_OverlapCount; }

public:
	void EnterOverlap(GCollider* _Other);
	void Overlap(GCollider* _Other);
	void ExitOverlap(GCollider* _Other);

};

