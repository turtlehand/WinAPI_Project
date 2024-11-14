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
	virtual void Awake() override;			// ������ ���۵� ��
	//virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

public:
	GTree();
	virtual ~GTree() override;
};

