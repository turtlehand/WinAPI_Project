#pragma once
#include "CObj.h"

class GHitBox;

class GCreature :
    public CObj
{
    DefaultStatsInfo* m_StatInfo;

public:
    void SetStatInfo(DefaultStatsInfo* _StatInfo) { m_StatInfo = _StatInfo; }
    DefaultStatsInfo* GetStatInfo() { return m_StatInfo; }

public:
    void BeAttacked(GHitBox* _HitBox);

    void Damaged(int _Damage);

    void Dead();

public:
    void Smash();

public:
    void KnockBack();

public:
    GCreature();
    virtual ~GCreature() override;
};

