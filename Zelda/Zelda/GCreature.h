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

	void Damaged(int _Damage);					// ����
	void KnockBack();							// �з��� 
	virtual void InteractionEffect() {};		// ��ȣ�ۿ� �� ȿ��

	void Dead();
	virtual void DropItem() {};					// �׾��� �� ����Ʈ���� ������Ʈ

public:
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

public:
	GCreature();
	virtual ~GCreature() override;
};
