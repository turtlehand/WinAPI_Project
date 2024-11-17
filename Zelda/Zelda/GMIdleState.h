#pragma once
#include "GState.h"

class GMonster;

class GMIdleState :
    public GState
{
private:
    GMonster* m_Monster;
    MonsterInfo* m_MonsterInfo;
    float m_MoveTimer;

public:
    virtual void Begin() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GMIdleState();
    ~GMIdleState();
};

