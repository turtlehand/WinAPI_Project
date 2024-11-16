#pragma once
#include "GCreature.h"

#include "GSprite.h"


class GItem :
	public GCreature
{

public:
	virtual void UseItem(GCreature* _User) = 0;

public:
	GItem(CREATURE_ID _CreatureID);
	virtual ~GItem() override;
};

