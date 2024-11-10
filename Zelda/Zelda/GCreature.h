#pragma once
#include "CObj.h"
#include "GFlipBookPlayer.h"

class GHitBox;
class GBoxCollider;

class GCreature :
	public CObj
{
	DefaultStatsInfo*	m_StatInfo;			// �⺻ ���� ����
	GBoxCollider*		m_HitBox;			// �ǰ� �ڽ�

	GFlipBookPlayer*	m_EffectAnim;		// �����̻� �ִϸ��̼�
	GHitBox*			m_EffectAttackBox;	// �����̻� ���� �ڽ�

public:
	void SetStatInfo(DefaultStatsInfo* _StatInfo) { m_StatInfo = _StatInfo; }
	DefaultStatsInfo* GetStatInfo() { return m_StatInfo; }

protected:
	GBoxCollider* GetHitBox() { return m_HitBox; }
	void RenderEffect() { m_EffectAnim->Render(); };

public:
	virtual void Tick() override;
	
public:
	void StatusEffect();				// �����̻�
	virtual void BurnStatusEffect();		// ȭ�� �����̻�

public:
	void Interaction(GHitBox* _HitBox);			// ��ȣ�ۿ�

	void Damaged(int _Damage);					// ����
	void KnockBack();							// �з��� 
	virtual void InteractionEffect(GHitBox* _HitBox) {};		// ��ȣ�ۿ� �� ȿ��

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

public:
	GCreature();
	virtual ~GCreature() override;
};
