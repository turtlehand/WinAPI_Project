#pragma once
#include "GUI.h"
#include "GItem.h"

class GInventory :
	public GUI
{
private:
	map<CREATURE_ID, GItem*> m_Item;
	GSprite* m_CurImage;

public:
	void UseItem(CREATURE_ID _ItemID, GCreature* _User);
	const GItem* FindItem(CREATURE_ID _ItemID);

	void SetCurItme(CREATURE_ID _ItemID);

public:
	virtual void Awake() override;
	virtual void Tick_UI() override;
	virtual void Render_UI() override;

public:
	GInventory();
	virtual ~GInventory() override;
};

