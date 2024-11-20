#pragma once
#include "GCollider.h"
class GCircleCollider :
    public GCollider
{
private:
    float m_Radius;

public:
    void SetRadius(float _Radius) { m_Radius = _Radius; }
    virtual Vec2 GetScale() override { return Vec2(m_Radius,m_Radius); }

public:
    virtual void FinalTick();

public:
    GCircleCollider();
    ~GCircleCollider();
};

