#include "pch.h"
#include "GWall.h"

#include "GBoxCollider.h"
#include "GAssetManager.h"
#include "GSprite.h"
#include "GTexture.h"
#include "GSound.h"

#include "CLevel.h"
#include "CLevelMgr.h"

#include "GCreature.h"
#include "GBoxCollider.h"


void GWall::Awake()
{
	GBoxCollider* Collider = AddComponent<GBoxCollider>();
	Collider->SetScale(Vec2(64.f, 64.f));
	Collider->SetTrigger(false);
}

void GWall::Render()
{
	if (CLevelMgr::GetInst()->GetCurrentLevelType() == LEVEL_TYPE::EDITOR)
	{
		BitBlt(CEngine::GetInst()->GetSecondDC(),
			GetRenderPos().x - GetTitleSprite()->GetSlice().x / 2,
			GetRenderPos().y - GetTitleSprite()->GetSlice().y / 2,
			GetTitleSprite()->GetSlice().x,
			GetTitleSprite()->GetSlice().y,
			GetTitleSprite()->GetAtlas()->GetDC(),
			GetTitleSprite()->GetLeftTop().x,
			GetTitleSprite()->GetLeftTop().y, SRCCOPY);
	}
}

void GWall::OnCollisionEnter(GCollider* _Collider)
{
	if (m_CreatureID == CREATURE_ID::Water)
	{

		if (_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::OBJECT)
		{
			GCreature* Creature = dynamic_cast<GCreature*>(_Collider->GetOwner());

			if (Creature->GetCreatureID() == CREATURE_ID::Log)
			{
				GAssetManager::GetInst()->LoadSound(L"Secret", L"Sound\\Sound_Effects\\LOZ_Secret.wav")->Play();
				_Collider->GetOwner()->SetPos(GetPos());
				_Collider->SetEnabled(false);
				DeleteGameObject(this);
			}
			else if (Creature->GetCreatureID() == CREATURE_ID::PullRock)
			{
				//DeleteGameObject(this);
				DeleteGameObject(_Collider->GetOwner());
			}
		}
	}
}

GWall::GWall(CREATURE_ID _CreatureID)
{
	m_CreatureID = _CreatureID;
	if (_CreatureID == CREATURE_ID::Wall)
	{
		SetName(L"Wall");
		SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"WALL", L"Sprite\\Object_16\\WALL.sprite"));
	}
	else if(_CreatureID == CREATURE_ID::Water)
	{
		SetName(L"Water");
		SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"WATER", L"Sprite\\Object_16\\WATER.sprite"));
	}
}

GWall::~GWall()
{
}
