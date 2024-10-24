#pragma once
#include "CObj.h"

class GTexture;

class GCollider;
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

	GCollider* m_HitBox;
	GRigidBody* m_RigidBody;
	GFSM* m_FSM;

public:
	virtual void Begin() override;			// 레벨이 시작될 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

	virtual void EnterOverlap(GCollider* _Collider) override;

public:
	
	MonsterInfo& GetInfo() { return m_MInfo; }

	void SetDir(Vec2 _Dir) { m_Dir = _Dir; }
	Vec2 GetDir() const { return m_Dir; }

public:
	Monster();
	virtual ~Monster() override;
};

