#pragma once
#include "CObj.h"

class GTexture;

class Collider;
class GRigidBody;
class GFSM;

class Monster :
    public CObj
{
	friend class GMIdleState;
	friend class GMChaseState;

private:
	CObj* m_Target;

	MonsterInfo m_MInfo;

	Vec2 m_Dir;

	GTexture* m_Texture;

	Collider* m_HitBox;
	GRigidBody* m_RigidBody;
	GFSM* m_FSM;

public:
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void EnterOverlap(Collider* _Collider) override;

public:
	
	MonsterInfo& GetInfo() { return m_MInfo; }

	void SetDir(Vec2 _Dir) { m_Dir = _Dir; }
	Vec2 GetDir() const { return m_Dir; }

public:
	Monster();
	virtual ~Monster() override;
};

