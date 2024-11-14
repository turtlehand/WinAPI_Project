#pragma once
#include "CObj.h"
#include "GFlipBookPlayer.h"

class GHitBox;
class GCollider;
class GBoxCollider;

enum class CREATURE_ID
{
	NONE = 0,

	// 플레이어
	Player = 1000,

	// 몬스터
	Monster = 2000,

	Moblin,

	// 장애물
	Obstacle = 3000,

	Grass,
	Tree,
	Log,
	Rock,
	PullRock,

	// 아이템
	Item = 4000,

	// 소재
	MATERIALS = 4100,
	Fire_Wood,
	Flint,
	MonsterMaterial,

	// 음식
	FOOD = 4200,
	Fruit,
	Roast_Fruit,

	// 무기
	WEAPON = 4300,
	Wooden_Sword,
	Iron_Sword,
	Stone_Hammer,
	Iron_Hammer,
	Wooden_Spear,
	Iron_Spear,
	Korok_Leaf,

	// 도구
	TOOLS = 4400,
	Bow,
	Arrow,

	// 공격 박스
	HitBox = 5000,
	Fire,

	// 벽
	Wall = 6000,
};

class GCreature :
	public CObj
{
private:
	const CREATURE_ID m_CreatureID;
	DefaultStatsInfo*	m_StatInfo;			// 기본 스탯 정보
	GBoxCollider*		m_HitBox;			// 피격 박스 또는 공격 박스

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

	void Interaction_Attack(GHitBox* _HitBox);							// 공격 상호작용
	virtual void InteractionEffect_Attack(GHitBox* _HitBox) {};		// 상호작용 시 효과

	void Damaged(int _Damage);									// 피해
	void KnockBack();											// 밀려남 


	void Dead();
	virtual void DropItem() {};					// 죽었을 시 떨어트리는 오브젝트

protected:
	// 소재 - 공격 반응
	void Smash();
	void CutWood();
	void BeAttacked(int _Damage);

	// 소재 - 속성 반응
	void Burn();
	void Flow();
	void Shock();
	void Freeze();
	void Wet();

	// 속성 - 속성 반응
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

