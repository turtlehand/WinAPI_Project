#pragma once
#include "CObj.h"
#include "GFlipBookPlayer.h"

class GHitBox;
class GCollider;
class GBoxCollider;

enum class CREATURE_ID
{
	NONE = 0,

	// �÷��̾�
	Player = 1000,

	// ����
	Monster = 2000,

	Moblin,

	// ��ֹ�
	Obstacle = 3000,

	Grass,
	Tree,
	Log,
	Rock,
	PullRock,

	// ������
	Item = 4000,

	// ����
	MATERIALS = 4100,
	Fire_Wood,
	Flint,
	MonsterMaterial,

	// ����
	FOOD = 4200,
	Fruit,
	Roast_Fruit,

	// ����
	WEAPON = 4300,
	Wooden_Sword,
	Iron_Sword,
	Stone_Hammer,
	Iron_Hammer,
	Wooden_Spear,
	Iron_Spear,
	Korok_Leaf,

	// ����
	TOOLS = 4400,
	Bow,
	Arrow,

	// ���� �ڽ�
	HitBox = 5000,
	Fire,

	// ��
	Wall = 6000,
};

class GCreature :
	public CObj
{
private:
	const CREATURE_ID m_CreatureID;
	DefaultStatsInfo*	m_StatInfo;			// �⺻ ���� ����
	GBoxCollider*		m_HitBox;			// �ǰ� �ڽ� �Ǵ� ���� �ڽ�

	CObj* m_Effect;

public:
	CREATURE_ID GetCreatureID() { return m_CreatureID; }

	void SetStatInfo(DefaultStatsInfo* _StatInfo) { m_StatInfo = _StatInfo; }
	DefaultStatsInfo* GetStatInfo() { return m_StatInfo; }

	CObj* GetEffectBox() { return m_Effect; }

protected:
	GBoxCollider* GetHitBox() { return m_HitBox; }

public:
	void StatusEffect();

public:
	virtual void Tick() override;

	virtual void OnTrigger(GCollider* _Collider) override;
	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:

	void Interaction_Element(GCreature* _Creature);
	virtual void InteractionEffect_Element(GCreature* _Creature) {};

	void Interaction_Attack(GHitBox* _HitBox);							// ���� ��ȣ�ۿ�
	virtual void InteractionEffect_Attack(GHitBox* _HitBox) {};		// ��ȣ�ۿ� �� ȿ��

	void Damaged(int _Damage);									// ����
	void KnockBack();											// �з��� 


	void Dead();
	virtual void DropItem() {};					// �׾��� �� ����Ʈ���� ������Ʈ

protected:
	// ���� - ���� ����
	void Smash();
	void CutWood();
	void BeAttacked(int _Damage);

	// ���� - �Ӽ� ����
	void Burn();
	void Flow();
	void Shock();
	void Freeze();
	void Wet();

	// �Ӽ� - �Ӽ� ����
	void Extinguish();
	void Melt();
	//void Freeze();
	//void Shock(); 

	void Ignite();
	void InstantIgnite();

public:
	GCreature(CREATURE_ID _CreatrueID);
	virtual ~GCreature() override;
};

