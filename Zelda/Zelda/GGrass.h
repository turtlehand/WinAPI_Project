#pragma once
#include "GCreature.h"

class GBoxCollider;
class GFlipBookPlayer;

class GGrass :
	public GCreature
{
	GFlipBookPlayer* m_FlipBookPlayer;

public:
	virtual void InteractionEffect(GHitBox* _HitBox) override;

public:
	virtual void Begin() override;			// ������ ���۵� ��
	//virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	GGrass();
	virtual ~GGrass() override;
};

