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
	virtual void Begin() override;			// 레벨이 시작될 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

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

