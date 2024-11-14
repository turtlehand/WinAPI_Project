#pragma once
#include "GCreature.h"

class GBoxCollider;
class GSpriteRenderer;
class GRigidBody;

class GLog :
    public GCreature
{
	GRigidBody* m_RigidBody;
	GSpriteRenderer* m_Sprite;

public:
	virtual void DropItem();

public:
	virtual void Begin() override;			// ������ ���۵� ��
	//virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���


public:
	GLog();
	virtual ~GLog() override;
};

