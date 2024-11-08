#pragma once
#include "GComponent.h"
#include "CObj.h"
class GCollider : public GComponent
{
	COLLIDER_TYPE m_ColliderType;

	bool	m_Trigger;

	Vec2	m_Offset;

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

	Vec2 GetGlobalPos()  { return (GetOwner()->GetGlobalPos() + m_Offset); }

	bool GetCollision() const { return m_OverlapCount; }

	COLLIDER_TYPE GetColliderType() const { return m_ColliderType; }

public:
	void OnCollisionEnter(GCollider* _Other);
	void OnCollision(GCollider* _Other);
	void OnCollisionExit(GCollider* _Other);

	void OnTriggerEnter(GCollider* _Other);
	void OnTrigger(GCollider* _Other);
	void OnTriggerExit(GCollider* _Other);

};

