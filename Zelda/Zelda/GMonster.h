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
	GFlipBookPlayer* m_FlipBookPlayer;
	GRigidBody* m_RigidBody;

	GHitBox* m_AttackBox;

public:
	MonsterInfo* GetMonsterStatInfo() { return (MonsterInfo*)GetStatInfo(); }
	const wstring& GetCurrentState();

	void SetTarget(CObj* _Target) { m_Target = _Target; }
	CObj* GetTarget() { return m_Target; }


	GFSM* GetFSM() { return m_FSM; }
	GFlipBookPlayer* GetFlipBookPlayer() { return m_FlipBookPlayer; }
	GRigidBody* GetRigidBody() { return m_RigidBody; }
	GHitBox* GetAttackBox() { return m_AttackBox; }

public:
	virtual void Awake() override;

protected:
	virtual void CreateAnimator() = 0;

public:
	GMonster(CREATURE_ID _CreatureID);
	virtual ~GMonster() override;
};

enum class MOBLIN_ANIM_STATE
{
	UP,
	DOWN,
	RIGHT,
};

