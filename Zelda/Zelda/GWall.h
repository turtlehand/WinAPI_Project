#pragma once
#include "CObj.h"

enum class CREATURE_ID;
class SpriteRenderer;

class GWall : public CObj
{
public:
	virtual void Awake() override;
	virtual void Tick() override {};
	virtual void Render() override ;

public:
	GWall(CREATURE_ID _CreatureID);
	virtual ~GWall() override;
};

