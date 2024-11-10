#pragma once
#include "CObj.h"
#include "GFlipBookPlayer.h"

class GHitBox;
class GBoxCollider;

class GCreature :
	public CObj
{
	DefaultStatsInfo*	m_StatInfo;			// 기본 스탯 정보
	GBoxCollider*		m_HitBox;			// 피격 박스

	GFlipBookPlayer*	m_EffectAnim;		// 상태이상 애니메이션
	GHitBox*			m_EffectAttackBox;	// 상태이상 공격 박스

public:
	void SetStatInfo(DefaultStatsInfo* _StatInfo) { m_StatInfo = _StatInfo; }
	DefaultStatsInfo* GetStatInfo() { return m_StatInfo; }

protected:
	GBoxCollider* GetHitBox() { return m_HitBox; }
	void RenderEffect() { m_EffectAnim->Render(); };

public:
	virtual void Tick() override;
	
public:
	void StatusEffect();				// 상태이상
	virtual void BurnStatusEffect();		// 화상 상태이상

public:
	void Interaction(GHitBox* _HitBox);			// 상호작용

	void Damaged(int _Damage);					// 피해
	void KnockBack();							// 밀려남 
	virtual void InteractionEffect(GHitBox* _HitBox) {};		// 상호작용 시 효과

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

public:
	GCreature();
	virtual ~GCreature() override;
};
