#pragma once
#include "CObj.h"

class GCircleCollider;
class GFlipBookPlayer;
class GTexture;
class GRigidBody;
class GFSM;

class Player :
    public CObj
{
private:

	GFSM* m_FSM;
	GCircleCollider* m_Collider;
	GFlipBookPlayer* m_FlipBookPlayer;
	GRigidBody* m_RigidBody;

	PlayerInfo m_PlayerInfo;

public:
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

public:
	PlayerInfo& GetInfo() {	return m_PlayerInfo;	}
	const wstring& GetCurrentState();
	void CreateAnimator();

public:
	Player();
	virtual ~Player() override;

	friend class GPIdleState;
	friend class GPMoveState;
	friend class GPAttackState;
};

