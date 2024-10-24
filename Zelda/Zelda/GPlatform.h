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
	virtual void Begin() override;			// 레벨이 시작될 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

public:
	GPlatform();
	virtual ~GPlatform() override;
};

