#include "pch.h"
#include "GInventory.h"

#include "GSlot.h"

#include "GTexture.h"
#include "GSprite.h"

#include "GPrefabManager.h"

GInventory::GInventory(vector<pair<CREATURE_ID, int>>& _Inventory) :
	m_CurItem(-1),
	m_Inventory(_Inventory),
	m_ItemSlot{nullptr}
{
	SetName(L"Inventory");
}

GInventory::~GInventory()
{

}

void GInventory::Awake()
{
	for (int i = 0; i < 3; ++i)
	{
		m_ItemSlot[i] = new GSlot;
		m_ItemSlot[i]->Awake();
		AddChildUI(m_ItemSlot[i]);
		m_ItemSlot[i]->SetPos(Vec2(8 + 72.f * i, 8.f));
		m_ItemSlot[i]->SetScale(Vec2(64.f, 64.f));
	}
	
	m_ItemSlot[PRE]->SetPos(Vec2(8 + 16.f, 8.f + 16.f));
	m_ItemSlot[PRE]->SetScale(Vec2(32.f, 32.f));

	m_ItemSlot[POST]->SetPos(Vec2(8 + 72.f * 2 + 16.f, 8.f + 16.f));
	m_ItemSlot[POST]->SetScale(Vec2(32.f, 32.f));
}

void GInventory::DropItem(GCreature* _User)
{
	if (m_CurItem == -1)
		return;

	CObj* DropObj = GPrefabManager::GetInst()->CreatePrefab(m_Inventory[m_CurItem].first);

	if (DropObj != nullptr)
	{
		DropObj->SetPos(_User->GetPos().x, _User->GetPos().y);
		CreateGameObject(DropObj, LAYER_TYPE::ITEM);
	}

	// �ش� �κ��丮�� �������� ������ 1�̶�� ���Կ��� �����.
	// �׸��� ���� �������� ����Ű�� �Ѵ�.
	if (m_Inventory[m_CurItem].second == 1)
	{
		m_Inventory.erase(m_Inventory.begin() + m_CurItem);
		SetCurItem(PreItem());
	}
	else
		m_Inventory[m_CurItem].second -= 1;

	
}

void GInventory::UseItem(GCreature* _User)
{
	if (m_CurItem == -1)
		return;

	const CObj* Item = GPrefabManager::GetInst()->FindPrefab(m_Inventory[m_CurItem].first);
	assert(Item != nullptr);

	((GItem*)Item)->UseItem(_User);

	// ������ �� ������ ���ҽ�Ų��.
	if ((int)CREATURE_ID::FOOD < (int)m_Inventory[m_CurItem].first && (int)m_Inventory[m_CurItem].first < (int)CREATURE_ID::WEAPON)
	{
		// �ش� �κ��丮�� �������� ������ 1�̶�� ���Կ��� �����.
		if (m_Inventory[m_CurItem].second == 1)
		{
			m_Inventory.erase(m_Inventory.begin() + m_CurItem);
			SetCurItem(PreItem());
		}
		else
			m_Inventory[m_CurItem].second -= 1;
	}
}

GSprite* GInventory::GetCurItemSprite()
{
	return m_ItemSlot[1]->GetItemSprite();
}

void GInventory::SetCurItem(int _Index)
{
	// -1�� ����Ű�� �����Ѵ�.
	if (_Index == -1)
	{
		m_CurItem = -1;
	}
	else
	{
		// ���� �ȿ� ���� �����Ѵ�.
		assert(0 <= _Index && _Index < m_Inventory.size());
		m_CurItem = _Index;
	}

	m_ItemSlot[PRE]->SetItemSprite(m_Inventory.empty() ? nullptr : GPrefabManager::GetInst()->FindPrefab(m_Inventory[PreItem()].first)->GetTitleSprite());
	m_ItemSlot[CUR]->SetItemSprite(m_Inventory.empty() ? nullptr : GPrefabManager::GetInst()->FindPrefab(m_Inventory[m_CurItem].first)->GetTitleSprite());
	m_ItemSlot[POST]->SetItemSprite(m_Inventory.empty() ? nullptr : GPrefabManager::GetInst()->FindPrefab(m_Inventory[PostItem()].first)->GetTitleSprite());
}

int GInventory::FristItem()
{
	// �κ��丮�� �������� ����.
	if (m_Inventory.size() == 0)
	{
		return -1;
	}

	return 0;
}

int GInventory::LastItem()
{
	// �κ��丮�� �������� ����.
	if (m_Inventory.size() == 0)
	{
		return -1;
	}

	return m_Inventory.size() - 1;
}

int GInventory::PreItem()
{
	// �κ��丮�� �������� ����.
	if (m_Inventory.size() == 0)
	{
		return -1;
	}
	// ���� ��ġ�� 0�̴�
	// ������ �ε����� ����Ű�� �Ѵ�.
	if (m_CurItem == 0)
	{
		return m_Inventory.size() - 1;
	}
	// �ƹ��͵� ����Ű�� ���� ���� 0�� ����Ű�� �Ѵ�.
	else if (m_CurItem == -1)
	{
		return m_CurItem = 0;
	}

	return m_CurItem - 1;
}

int GInventory::PostItem()
{
	// �κ��丮�� �������� ����.
	if (m_Inventory.size() == 0)
	{
		return -1;
	}

	// ���� ��ġ�� �������̴�.
	// ó�� �ε����� ����Ű�� �Ѵ�.
	if (m_Inventory.size() - 1 == m_CurItem)
	{
		return 0;
	}	// �ƹ��͵� ����Ű�� ���� ���� 0�� ����Ű�� �Ѵ�.
	else if (m_CurItem == -1)
	{
		return m_CurItem = m_Inventory.size() - 1;
	}

	return m_CurItem + 1;
}

void GInventory::Tick_UI()
{
	GPanel::Tick_UI();

	// �κ��丮�� ������� �ʴٸ�
	if (m_Inventory.size() > 0)
	{
		if (GETKEYDOWN(KEY::A))
		{
			SetCurItem(PreItem());
		}
		else if (GETKEYDOWN(KEY::D))
		{
			SetCurItem(PostItem());
		}
	}
	else
	{
		SetCurItem(-1);
	}
}

void GInventory::Render_UI()
{
	//GPanel::Render_UI();

	if (m_CurItem == -1)
		return;
}
