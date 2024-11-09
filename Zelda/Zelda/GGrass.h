#pragma once
#include "GCreature.h"

class GBoxCollider;
class GFlipBookPlayer;

class GGrass :
	public GCreature
{
	GBoxCollider* m_Collider;
	GFlipBookPlayer* m_FlipBookPlayer;

public:
	virtual void InteractionEffect();

public:
	virtual void Begin() override;			// 레벨이 시작될 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	GGrass();
	virtual ~GGrass() override;
};

