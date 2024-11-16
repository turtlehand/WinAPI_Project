#pragma once
#include "GUI.h"
#include "GItem.h"

#define PRE 0
#define CUR 1
#define POST 2

class GInventory :
	public GUI
{
private:
	GSprite* m_CurImage[3];

public:
	void UseItem(CREATURE_ID _ItemID, GCreature* _User);

	void SetCurItme(CREATURE_ID _ItemID);

public:
	virtual void Awake() override;
	virtual void Tick_UI() override;
	virtual void Render_UI() override;

public:
	GInventory();
	virtual ~GInventory() override;
};

