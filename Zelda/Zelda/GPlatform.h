#pragma once
#include "CObj.h"

class GCollider;
class GRigidBody;

class GPlatform :
    public CObj
{
private:
	GCollider* m_Collider;
	GRigidBody* m_RigidBody;

public:
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

public:
	GPlatform();
	virtual ~GPlatform() override;
};

