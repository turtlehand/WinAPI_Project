#pragma once
#include "GState.h"

class GMonster;
class GSound;

class GMBeAttackedState :
    public GState
{
private:
    GMonster* m_Monster;
    float m_Timer;

    GSound* m_EnemyHurt;

public:
    virtual void Awake() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GMBeAttackedState();
    ~GMBeAttackedState();
};