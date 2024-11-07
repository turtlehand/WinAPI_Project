#pragma once
#include "CObj.h"
#include "GFlipBookPlayer.h"

class GHitBox;

class GCreature :
	public CObj
{
	DefaultStatsInfo* m_StatInfo;
	GFlipBookPlayer* m_EffectAnim;

public:
	void SetStatInfo(DefaultStatsInfo* _StatInfo) { m_StatInfo = _StatInfo; }
	DefaultStatsInfo* GetStatInfo() { return m_StatInfo; }

	void RenderEffect() { m_EffectAnim->Render(); };

public:
	virtual void Tick() override;
	void StatusEffect();

public:
	void Interaction(GHitBox* _HitBox);

	void Damaged(int _Damage);
	void KnockBack();
	virtual void DropItem() {};

	void Dead();

public:
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

public:
	GCreature();
	virtual ~GCreature() override;
};
