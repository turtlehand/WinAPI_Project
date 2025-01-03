#pragma once
#include "CObj.h"
#include "GCreature.h"
#include "GItem.h"

class GBoxCollider;
class GFlipBookPlayer;
class GSpriteRenderer;
class GTexture;
class GSprite;
class GRigidBody;
class GFSM;
class GHitBox;
class GInventory;
class GSlot;


class GPlayer :
    public GCreature
{
private:

	GFSM* m_FSM;
	GFlipBookPlayer* m_FlipBookPlayer;
	GRigidBody* m_RigidBody;

	// 공격 관련
	CREATURE_ID m_WeaponEquip;
	GHitBox* m_AttackBox;

	// 도구 관련
	CREATURE_ID m_ToolEquip;

	// 아이템 관련
	GInventory* m_InventoryUI;
	vector<pair<CREATURE_ID, int>> m_Inventory;

	// 현재 장착 장비
	GSlot* m_EquipUI;

	// 근처 장비
	CObj* m_NearbyItem;

public:
	virtual void Awake() override;			// 생성 후 레벨에 삽입 전
	virtual void Begin() override;			// 레벨에 삽입할 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

	virtual void OnTrigger(GCollider* _Collider) override;
	virtual void OnTriggerExit(GCollider* _Collider) override;
	virtual void OnCollisionEnter(GCollider* _Collider) override;
	virtual void OnCollisionExit(GCollider* _Collider) override;

public:
	PlayerInfo* GetPlayerStatInfo() {	return (PlayerInfo*)GetStatInfo();	}
	const wstring& GetCurrentState();
	void CreateAnimator();

	void SetAttackBox(CREATURE_ID _WeaponID);
	void SetTool(CREATURE_ID _ToolID);

	int SaveUserData();
	int LoadUserData();

public:
	virtual void Dead();

private:
	void PickUpItem();
	void DropInvenItem();
	void UseItem();

public:
	GPlayer();
	virtual ~GPlayer() override;

	friend class GPIdleState;
	friend class GPMoveState;
	friend class GPAttackState;
	friend class GPPickUpState;
	friend class GPUseToolState;
	friend class GPBeAttackedState;
	friend class GPDieState;
};

enum class PLAYER_ANIM_STATE
{
	DIE,

	UP,
	DOWN,
	RIGHT,

	ATTACK_UP,
	ATTACK_DOWN,
	ATTACK_RIGHT,

	PICK_UP,
	NONE
};

enum class ATTACK_ANIM_STATE
{
	WEAPON_X,
	WEAPON_Y,

	BOW_X,
	BOW_Y,
};