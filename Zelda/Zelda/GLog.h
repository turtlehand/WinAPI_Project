#pragma once
#include "GCreature.h"

class GBoxCollider;
class GSpriteRenderer;

class GLog :
    public GCreature
{
	GBoxCollider* m_Collider;
	GSpriteRenderer* m_Sprite;

public:
	virtual void DropItem();

public:
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void EnterOverlap(GCollider* _Collider);

public:
	GLog();
	virtual ~GLog() override;
};

