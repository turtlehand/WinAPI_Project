#pragma once
#include "GCreature.h"

class GBoxCollider;
class GSpriteRenderer;

class GRock :
    public GCreature
{
	GSpriteRenderer* m_Sprite;

public:
	virtual void Awake() override;			// ������ ���۵� ��
	//virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void OnTriggerEnter(GCollider* _Collider);

public:
	GRock();
	virtual ~GRock() override;
};

