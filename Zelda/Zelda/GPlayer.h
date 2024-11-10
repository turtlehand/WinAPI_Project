#pragma once
#include "CObj.h"
#include "GCreature.h"
#include "GItem.h"

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
	GFlipBookPlayer* m_FlipBookPlayer;
	GRigidBody* m_RigidBody;

	// ���� ����
	GHitBox* m_AttackBox;

	// ������ ����
	vector<pair<ITEM_ID, int>> m_Inventory;
	CObj* m_NearbyItem;

public:
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void OnTriggerEnter(GCollider* _Collider) override;
	virtual void OnTrigger(GCollider* _Collider) override;
	virtual void OnTriggerExit(GCollider* _Collider) override;
	virtual void OnCollisionEnter(GCollider* _Collider) override;
	virtual void OnCollisionExit(GCollider* _Collider) override;

public:
	PlayerInfo* GetPlayerStatInfo() {	return (PlayerInfo*)GetStatInfo();	}
	const wstring& GetCurrentState();
	void CreateAnimator();

private:
	void PickUpItem();
	void DropItem(int index);
	void UseItem(int index);

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