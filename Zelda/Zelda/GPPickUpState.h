#pragma once
#include "GState.h"
#include "GPlayer.h"

class GPlayer;
class GSound;
class GPanel;
class GGameImage;

class GPPickUpState :
	public GState
{
private:
	GPlayer* m_Player;
	GGameImage* m_ItemImage;

	PLAYER_ANIM_STATE m_PrevAnim;
	GSound* m_PickUpSound;

public:
	virtual void Awake() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
public:
	GPPickUpState();
	~GPPickUpState();
};