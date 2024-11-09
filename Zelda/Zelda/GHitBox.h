#pragma once
#include "CObj.h"

class GRigidBody;
class GSpriteRenderer;
class GFlipBookPlayer;
class GCollider;

class GHitBox :
    public CObj
{
    ATTACK_TYPE m_AttackType;
    MATERIAL_TYPE m_MaterialType;
    ElementalEffect m_Effect;

    int m_Damage;
    bool m_IsProjectile;

    GCollider* m_Collider;
    GSpriteRenderer* m_SpriteRenderer;
    GFlipBookPlayer* m_FlipBookPlayer;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

public:
    void SetAttackType(ATTACK_TYPE _AttackType) { m_AttackType = _AttackType; };
    ATTACK_TYPE GetAttackType() { return m_AttackType; };

    void SetMaterialType(MATERIAL_TYPE _MaterialType) { m_MaterialType = _MaterialType; };
    MATERIAL_TYPE GetMaterialType() { return m_MaterialType; };

    void SetEffect(ElementalEffect _Effect) { m_Effect = _Effect; };
    ElementalEffect GetEffect() { return m_Effect; };

    void SetDamage(int _Damage) { m_Damage = _Damage; };
    int GetDamage() { return m_Damage; };

    void SetIsProjectile(bool _IsProjectile) { m_IsProjectile = _IsProjectile; };
    bool GetIsProjectile() { return m_IsProjectile; };

    virtual void OnTriggerEnter(GCollider* _Collider) override;

    GSpriteRenderer* GetSpriteRenderer() { return m_SpriteRenderer; }
    GFlipBookPlayer* GetFlipBookPlayer() { return m_FlipBookPlayer; }

public:
    GHitBox();
    virtual ~GHitBox() override;

    friend class GPAttackState;

};

