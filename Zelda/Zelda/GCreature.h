#pragma once
#include "CObj.h"
#include "GFlipBookPlayer.h"

class GHitBox;
class GCollider;
class GBoxCollider;

enum class CREATURE_ID
{
	NONE = -1,

	// �÷��̾�
	Player,

	// ����
	Monster,

	Moblin,

	// ��ֹ�
	Obstacle,

	Grass,
	Tree,
	Log,
	Rock,
	PullRock,

	// ������
	Item,

	// ����
	MATERIALS,
	Fire_Wood,
	Flint,
	MonsterMaterial,

	// ����
	FOOD,
	Fruit,
	Roast_Fruit,

	// ����
	WEAPON,
	Wooden_Sword,
	Iron_Sword,
	Stone_Hammer,
	Iron_Hammer,
	Wooden_Spear,
	Iron_Spear,
	Korok_Leaf,

	// ����
	TOOLS,
	Bow,
	Arrow,

	ELEMENT,
	Fire,

	//��Ÿ
	ETC,

	// ���� �ڽ�
	HitBox,
	// ��
	Wall,

	END,
};

class GCreature :
	public CObj
{
private:
	const CREATURE_ID m_CreatureID;
	DefaultStatsInfo*	m_StatInfo;			// �⺻ ���� ����
	GBoxCollider*		m_HitBox;			// �ǰ� �ڽ� �Ǵ� ���� �ڽ�

	CObj* m_Element;

	bool m_ElementTick;						// ���� ƽ���� �Ӽ� ȿ���� �޾Ҵٸ� true
public:
	CREATURE_ID GetCreatureID() { return m_CreatureID; }

	void SetStatInfo(DefaultStatsInfo* _StatInfo) { m_StatInfo = _StatInfo; }
	DefaultStatsInfo* GetStatInfo() { return m_StatInfo; }

	CObj* GetElement() { return m_Element; }

protected:
	GBoxCollider* GetHitBox() { return m_HitBox; }

public:
	void StatusEffect();

public:
	virtual void Awake() override;
	virtual void Tick() override;

	virtual void OnTrigger(GCollider* _Collider) override;
	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:

	void Interaction_Element(GCreature* _Creature);
	virtual void InteractionEffect_Element(GCreature* _Creature) {};

	void Interaction_Attack(GHitBox* _HitBox);							// ���� ��ȣ�ۿ�
	virtual void InteractionEffect_Attack(GHitBox* _HitBox) {};		// ��ȣ�ۿ� �� ȿ��

	void Damaged(int _Damage);									// ����
	void KnockBack(GHitBox* _HitBox);											// �з��� 


	virtual void Dead();
	virtual void DropItem() {};					// �׾��� �� ����Ʈ���� ������Ʈ

protected:
	// ���� - ���� ����
	void Smash();
	void CutWood();
	void BeAttacked(GHitBox* _HitBox);

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

public:
	void Ignite();
	void InstantIgnite();

public:
	GCreature(CREATURE_ID _CreatrueID);
	virtual ~GCreature() override;
};

