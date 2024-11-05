#pragma once
#include "GCreature.h"

class GBoxCollider;
class GSpriteRenderer;

class GRock :
    public GCreature
{
	GBoxCollider* m_Collider;
	GSpriteRenderer* m_Sprite;

public:
	virtual void Awake() override;
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void EnterOverlap(GCollider* _Collider);
	virtual void Overlap(GCollider* _Collider);

public:
	GRock();
	virtual ~GRock() override;
};

