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


class GPlayer :
    public GCreature
{
private:

	GFSM* m_FSM;
	GFlipBookPlayer* m_FlipBookPlayer;
	GRigidBody* m_RigidBody;

	// ���� ����
	CREATURE_ID m_WeaponEquip;
	GHitBox* m_AttackBox;

	// ���� ����
	CREATURE_ID m_ToolEquip;

	// ������ ����
	GInventory* m_InventoryUI;
	int m_InvenIndex;
	vector<pair<CREATURE_ID, int>> m_Inventory;
	CObj* m_NearbyItem;

public:
	virtual void Awake() override;			// ���� �� ������ ���� ��
	virtual void Begin() override;			// ������ ������ ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void OnTrigger(GCollider* _Collider) override;
	virtual void OnTriggerExit(GCollider* _Collider) override;
	virtual void OnCollisionEnter(GCollider* _Collider) override;
	virtual void OnCollisionExit(GCollider* _Collider) override;

public:
	PlayerInfo* GetPlayerStatInfo() {	return (PlayerInfo*)GetStatInfo();	}
	const wstring& GetCurrentState();
	void CreateAnimator();

	void SetInvenUI(GInventory* _InvenUI) { m_InventoryUI = _InvenUI; }

	void SetAttackBox(CREATURE_ID _WeaponID, const WeaponInfo* _WeaponInfo, GSprite* _SpriteX, GSprite* _SpriteY);
	void SetTool(CREATURE_ID _ToolID, const DefaultStatsInfo* _ToolInfo);

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
	friend class GPUseToolState;
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

enum class ATTACK_ANIM_STATE
{
	WEAPON_X,
	WEAPON_Y,

	BOW_X,
	BOW_Y,
};