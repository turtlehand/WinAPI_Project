#pragma once
#include "GState.h"
#include "GPlayer.h";

class GPlayer;
class GFlipBook;
class GHitBox;

class GPAttackState :
    public GState
{
private:
    GPlayer* m_Player;
    PlayerInfo* m_PlayerInfo;
    GHitBox* m_AttackBox;

    PLAYER_ANIM_STATE m_PrevAnim;

public:
    virtual void Begin() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GPAttackState();
    ~GPAttackState();
};

