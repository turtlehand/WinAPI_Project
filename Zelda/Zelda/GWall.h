#pragma once
#include "CObj.h"

enum class CREATURE_ID;
class SpriteRenderer;

class GWall : public CObj
{
private:
	CREATURE_ID m_CreatureID;

public:
	virtual void Awake() override;
	virtual void Tick() override {};
	virtual void Render() override;

	virtual void OnCollisionEnter(GCollider* _Collider) override;

public:
	GWall(CREATURE_ID _CreatureID);
	virtual ~GWall() override;
};

