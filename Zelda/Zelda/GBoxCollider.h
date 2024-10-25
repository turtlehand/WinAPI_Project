#pragma once
#include "GCollider.h"
class GBoxCollider :
    public GCollider
{
private:
    Vec2 m_Scale;

public:
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    Vec2 GetScale() const { return m_Scale; }

public:
    virtual void FinalTick();

public:
    GBoxCollider();
    ~GBoxCollider();
};

