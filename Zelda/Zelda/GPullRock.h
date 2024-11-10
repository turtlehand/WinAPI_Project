#pragma once
#include "GCreature.h"

class GSpriteRenderer;
class GRigidBody;

class GPullRock :
	public GCreature
{
	GRigidBody* m_RigidBody;
	GSpriteRenderer* m_Sprite;

public:
	virtual void Begin() override;			// ������ ���۵� ��
	//virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void OnTriggerEnter(GCollider* _Collider);

public:
	GPullRock();
	virtual ~GPullRock() override;
};

