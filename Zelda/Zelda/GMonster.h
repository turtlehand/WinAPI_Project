#pragma once
#include "CObj.h"
#include "GCreature.h"

class GFlipBookPlayer;
class GBoxCollider;
class GRigidBody;
class GFSM;
class GHitBox;

class GMonster :
    public GCreature
{
	friend class GMIdleState;
	friend class GMChaseState;

private:
	CObj* m_Target;

	GFSM* m_FSM;
	GBoxCollider* m_HitBox;
	GFlipBookPlayer* m_FlipBookPlayer;
	GRigidBody* m_RigidBody;

	GHitBox* m_AttackBox;

public:
	virtual void EnterOverlap(GCollider* _Collider) override;

public:
	MonsterInfo* GetMonsterStatInfo() { return (MonsterInfo*)GetStatInfo(); }
	const wstring& GetCurrentState();

	void SetTarget(CObj* _Target) { m_Target = _Target; }
	CObj* GetTarget() { return m_Target; }

	GFSM* GetFSM() { return m_FSM; }
	GBoxCollider* GetHitBox() { return m_HitBox; }
	GFlipBookPlayer* GetFlipBookPlayer() { return m_FlipBookPlayer; }
	GRigidBody* GetRigidBody() { return m_RigidBody; }
	GHitBox* GetAttackBox() { return m_AttackBox; }

protected:
	virtual void CreateAnimator() = 0;

public:
	GMonster();
	virtual ~GMonster() override;
};

enum class MOBLIN_ANIM_STATE
{
	UP,
	DOWN,
	RIGHT,
};
