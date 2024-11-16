#include "pch.h"
#include "GWall.h"

#include "GBoxCollider.h"
#include "GAssetManager.h"
#include "GSprite.h"
#include "GTexture.h"

#include "CLevel.h"
#include "CLevelMgr.h"

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

GWall::GWall()
{
	SetName(L"Wall");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"WALL", L"Sprite\\Object_16\\WALL.sprite"));
}

GWall::~GWall()
{
}
