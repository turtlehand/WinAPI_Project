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
	virtual void Begin() override;			// 레벨이 시작될 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

	virtual void EnterOverlap(GCollider* _Collider);
	virtual void Overlap(GCollider* _Collider);

public:
	GRock();
	virtual ~GRock() override;
};

