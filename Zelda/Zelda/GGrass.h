#pragma once
#include "GCreature.h"

class GBoxCollider;
class GFlipBookPlayer;

class GGrass :
	public GCreature
{
	GBoxCollider* m_Collider;
	GFlipBookPlayer* m_FlipBookPlayer;

public:
	virtual void InteractionEffect();

public:
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	GGrass();
	virtual ~GGrass() override;
};

