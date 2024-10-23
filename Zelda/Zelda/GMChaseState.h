#pragma once
#include "GState.h"

class Monster;

class GMChaseState : public GState
{
private:
    Monster* m_Monster;

public:
    virtual void Awake() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GMChaseState();
    ~GMChaseState();
};

