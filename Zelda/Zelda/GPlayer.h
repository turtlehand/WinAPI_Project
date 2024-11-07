#pragma once
#include "CObj.h"
#include "GCreature.h"

class GBoxCollider;
class GFlipBookPlayer;
class GTexture;
class GRigidBody;
class GFSM;
class GHitBox;

class GPlayer :
    public GCreature
{
private:

	GFSM* m_FSM;
	GBoxCollider* m_Collider;
	GFlipBookPlayer* m_FlipBookPlayer;
	GRigidBody* m_RigidBody;

	GHitBox* m_AttackBox;

public:
	virtual void Begin() override;			// 레벨이 시작될 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

	virtual void EnterOverlap(GCollider* _Collider);

public:
	PlayerInfo* GetPlayerStatInfo() {	return (PlayerInfo*)GetStatInfo();	}
	const wstring& GetCurrentState();
	void CreateAnimator();

public:
	GPlayer();
	virtual ~GPlayer() override;

	friend class GPIdleState;
	friend class GPMoveState;
	friend class GPAttackState;
};

enum class PLAYER_ANIM_STATE
{
	UP,
	DOWN,
	RIGHT,

	ATTACK_UP,
	ATTACK_DOWN,
	ATTACK_RIGHT,
	NONE
};