#pragma once
#include "GState.h"

class GPlayer;

class GPMoveState :
    public GState
{
private:
    GPlayer* m_Player;
    PlayerInfo* m_PlayerInfo;
    Vec2 m_PrevDir;

public:
    virtual void Begin() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GPMoveState();
    ~GPMoveState();

};

