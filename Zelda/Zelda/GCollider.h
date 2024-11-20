#pragma once
#include "GComponent.h"
#include "CObj.h"

class GCollider : public GComponent
{
	friend class GRigidBody;

private:
	COLLIDER_TYPE m_ColliderType;

	bool	m_Trigger;

	Vec2	m_Offset;

	int		m_OverlapCount;

	bool	m_IsRigidBody;		// 해당 오브젝트가 리지드 바디를 보유하고 있는지

public:
	GCollider(COLLIDER_TYPE _Type);
	~GCollider();

public:
	virtual void Awake() override;
	virtual void FinalTick() = 0;

public:
	void SetTrigger(bool _Trigger) { m_Trigger = _Trigger; }
	bool GetTrigger() { return m_Trigger; }

	void SetPos(Vec2 _Offset) { m_Offset = _Offset; }
	Vec2 GetPos( ) const { return m_Offset; }

	virtual Vec2 GetScale() = 0;

	Vec2 GetGlobalPos()  { return (GetOwner()->GetGlobalPos() + m_Offset); }

	bool GetCollision() const { return m_OverlapCount; }

	COLLIDER_TYPE GetColliderType() const { return m_ColliderType; }

	bool IsRigidBody() { return m_IsRigidBody; }

public:
	void OnCollisionEnter(GCollider* _Other);
	void OnCollision(GCollider* _Other);
	void OnCollisionExit(GCollider* _Other);

	void OnTriggerEnter(GCollider* _Other);
	void OnTrigger(GCollider* _Other);
	void OnTriggerExit(GCollider* _Other);

};

