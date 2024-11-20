#pragma once
#include "GCollider.h"

class GBoxCollider :
    public GCollider
{
private:
    Vec2 m_Scale;

public:
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    virtual Vec2 GetScale() override { return m_Scale; }

public:
    virtual void FinalTick();

public:
    GBoxCollider(COLLIDER_TYPE _ColliderType = COLLIDER_TYPE::BOX);
    virtual ~GBoxCollider() override;
};

