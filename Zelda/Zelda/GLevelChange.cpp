#include "pch.h"
#include "GLevelChange.h"

#include "GBoxCollider.h"
#include "GAssetManager.h"
#include "GSprite.h"
#include "GTexture.h"

#include "GPlayer.h"
#include "CLevel.h"
#include "CLevelMgr.h"

#include "GCreature.h"
#include "GBoxCollider.h"
#include "GSound.h"

GLevelChange::GLevelChange() :
	m_ChanageLevel(LEVEL_TYPE::EDITOR)
{
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"Stair", L"Sprite\\Object_16\\STAIR.sprite"));
}

GLevelChange::~GLevelChange()
{

}


void GLevelChange::Awake()
{
	GBoxCollider* Collider = AddComponent<GBoxCollider>();
	Collider->SetScale(Vec2(64.f, 64.f));
	Collider->SetTrigger(true);
}

void GLevelChange::Render()
{
}

void GLevelChange::OnTriggerEnter(GCollider* _Collider)
{
	if (_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::PLAYER)
	{
		GPlayer* Player = dynamic_cast<GPlayer*>(_Collider->GetOwner());
		assert(Player != nullptr);
		Player->SaveUserData();

		GAssetManager::GetInst()->LoadSound(L"Stair", L"Sound\\Sound_Effects\\LOZ_Stairs.wav")->Play();
		ChangeLevel(m_ChanageLevel);
	}
}