#pragma once
#include "CObj.h"
#include "Collider.h"

class Missile :
	public CObj
{
private:
	Vec2 m_Velocity;
	float m_VelocityScale;
	Collider* m_HitBox;

	float m_Mass;
	Vec2 m_Force;

public:
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void EnterOverlap(Collider* _Collider) override;


public:
	void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
	Vec2 GetVelocity() { return m_Velocity; }

	void SetVelocityScale(float _VelocityScale) { m_VelocityScale = _VelocityScale; }
	float GetVelocityScale() { return m_VelocityScale; }

	Collider* GetCollider() { return m_HitBox; }

	void SetMass(float _Mass) { m_Mass = _Mass; }
	float GetMass() { return m_Mass; }
	
	void SetForce(Vec2 _Force) { m_Force = _Force; }
	Vec2 GetForce() { return m_Force; }
	void AddForce(Vec2 _Force) { m_Force += _Force; }


public:
	Missile();
	virtual ~Missile() override;
};

