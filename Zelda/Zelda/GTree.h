#pragma once
#include "GCreature.h"

class GSpriteRenderer;

class GTree :
    public GCreature
{
	GSpriteRenderer* m_Sprite;

public:
	virtual void DropItem();

public:
	virtual void Begin() override;			// ������ ���۵� ��
	//virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	GTree();
	virtual ~GTree() override;
};

