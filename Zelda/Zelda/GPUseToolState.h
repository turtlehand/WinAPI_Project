#pragma once
#include "GState.h"
#include "GPlayer.h"

class GPlayer;
class GFlipBook;
class GHitBox;
class GSound;

class GPUseToolState :
    public GState
{
private:
    GPlayer* m_Player;
    PlayerInfo* m_PlayerInfo;
    GHitBox* m_AttackBox;
    GSound* m_ShotSound;

    PLAYER_ANIM_STATE m_PrevAnim;

public:
    virtual void Awake() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

private:
    void Bow();
public:
    GPUseToolState();
    ~GPUseToolState();
};

