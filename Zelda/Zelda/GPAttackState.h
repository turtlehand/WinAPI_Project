#pragma once
#include "GState.h"

class Player;
class GFlipBook;

class GPAttackState :
    public GState
{
private:
    Player* m_Player;
    PlayerInfo* m_PlayerInfo;

    PLAYER_ANIM_STATE m_PrevAnim;


public:
    virtual void Awake() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GPAttackState();
    ~GPAttackState();
};

