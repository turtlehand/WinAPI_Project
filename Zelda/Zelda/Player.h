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
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

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

