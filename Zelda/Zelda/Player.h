#pragma once
#include "CObj.h"
#include "GCreature.h"

class GCircleCollider;
class GFlipBookPlayer;
class GTexture;
class GRigidBody;
class GFSM;
class GHitBox;

class Player :
    public GCreature
{
private:

	GFSM* m_FSM;
	GCircleCollider* m_Collider;
	GFlipBookPlayer* m_FlipBookPlayer;
	GRigidBody* m_RigidBody;

	GHitBox* m_AttackBox;

public:
	virtual void Awake() override;
	virtual void Begin() override;			// 레벨이 시작될 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

	virtual void EnterOverlap(GCollider* _Collider);
	virtual void Overlap(GCollider* _Collider);

public:
	PlayerInfo* GetPlayerStatInfo() {	return (PlayerInfo*)GetStatInfo();	}
	const wstring& GetCurrentState();
	void CreateAnimator();

	void SetAttackBox(GHitBox* _AttackBox) { m_AttackBox = _AttackBox; }

public:
	Player();
	virtual ~Player() override;

	friend class GPIdleState;
	friend class GPMoveState;
	friend class GPAttackState;
};

