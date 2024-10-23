#pragma once
#include "CBase.h"
#include "GFSM.h"
class GState :
    public CBase
{
private:
    GFSM* m_Owner;

public:
    GFSM* GetFSM() { return m_Owner; }
    CObj* GetOwnerObj() { return m_Owner->GetOwner(); }

public:
    virtual void Awake() {};
    virtual void Enter() = 0;
    virtual void FinalTick() = 0;
    virtual void Exit() = 0;

public:
    GState();
    virtual ~GState() override;

    friend class GFSM;
};

