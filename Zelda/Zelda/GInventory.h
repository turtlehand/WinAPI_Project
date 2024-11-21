#pragma once
#include "GPanel.h"
#include "GItem.h"

#define PRE 0
#define CUR 1
#define POST 2

class GSprite;
class GSlot;

class GInventory :
	public GPanel
{
private:
	int m_CurItem;
	vector<pair<CREATURE_ID, int>>& m_Inventory;
	GSlot* m_ItemSlot[3];

public:
	void SetCurItem(int _Index);
	int FristItem();
	int LastItem();
	int PreItem();					// 이전 아이템
	int CurItem() { return m_CurItem; };
	int PostItem();					// 다음 아이템

	//void PickUpItem();		
	void DropItem(GCreature* _User);
	void UseItem(GCreature* _User);
	
	GSprite* GetCurItemSprite();

public:
	virtual void Awake() override;
	virtual void Tick_UI() override;
	virtual void Render_UI() override;

public:
	GInventory(vector<pair<CREATURE_ID, int>>& _Inventory);
	virtual ~GInventory() override;
};

