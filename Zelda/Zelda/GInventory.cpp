#include "pch.h"
#include "GInventory.h"

#include "GCreature.h"
#include "GFireWood.h"
#include "GFlint.h"
#include "GFruit.h"
#include "GRoastFruit.h"
#include "GWeapon.h"
#include "GBow.h"

#include "GTexture.h"
#include "GSprite.h"

#include "GPrefabManager.h"

GInventory::GInventory() :
	m_CurImage{nullptr,nullptr,nullptr}
{

}

GInventory::~GInventory()
{

}

void GInventory::Awake()
{

}

void GInventory::UseItem(CREATURE_ID _ItemID, GCreature* _User)
{
	const CObj* Item = GPrefabManager::GetInst()->FindPrefab(_ItemID);
	assert(Item != nullptr);

	((GItem*)Item)->UseItem(_User);
}

void GInventory::SetCurItme(CREATURE_ID _ItemID)
{

	if (_ItemID == CREATURE_ID::END)
	{
		m_CurImage[CUR] = nullptr;
		return;
	}
		

	const CObj* Item = GPrefabManager::GetInst()->FindPrefab(_ItemID);
	assert(Item != nullptr);
	m_CurImage[CUR] = Item->GetTitleSprite();
}

void GInventory::Tick_UI()
{

}

void GInventory::Render_UI()
{
	if (m_CurImage[CUR] == nullptr)
		return;

	StretchBlt(CEngine::GetInst()->GetSecondDC(),
		CEngine::GetInst()->GetResolution().x - 100, 50,
		m_CurImage[CUR]->GetSlice().x * 4, m_CurImage[CUR]->GetSlice().y * 4,
		m_CurImage[CUR]->GetAtlas()->GetDC(), m_CurImage[CUR]->GetLeftTop().x, m_CurImage[CUR]->GetLeftTop().y,
		m_CurImage[CUR]->GetSlice().x, m_CurImage[CUR]->GetSlice().y, SRCCOPY);
}
