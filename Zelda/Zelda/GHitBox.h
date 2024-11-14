#pragma once
#include "CObj.h"
#include "GCreature.h"

class GRigidBody;
class GSpriteRenderer;
class GFlipBookPlayer;
class GBoxCollider;

class GHitBox :
	public GCreature
{
	ATTACK_TYPE m_AttackType;

	bool m_IsProjectile;

	// 스프라이트
	GSpriteRenderer* m_SpriteRenderer;
	GFlipBookPlayer* m_FlipBookPlayer;

public:
	virtual void Awake() override;
	virtual void Tick() override;
	virtual void Render() override;

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	void SetAttackType(ATTACK_TYPE _AttackType) { m_AttackType = _AttackType; };
	ATTACK_TYPE GetAttackType() { return m_AttackType; };

	void SetMaterialType(MATERIAL_TYPE _MaterialType) { GetStatInfo()->Material = _MaterialType; }
	MATERIAL_TYPE GetMaterialType() { return GetStatInfo()->Material; }

	void SetDamage(int _Damage) { GetStatInfo()->AttackPower = _Damage; };
	int GetDamage() { return GetStatInfo()->AttackPower; };

	void SetIsProjectile(bool _IsProjectile) { m_IsProjectile = _IsProjectile; };
	bool GetIsProjectile() { return m_IsProjectile; };

	GSpriteRenderer* GetSpriteRenderer() { return m_SpriteRenderer; }
	GFlipBookPlayer* GetFlipBookPlayer() { return m_FlipBookPlayer; }

public:
	GHitBox(CREATURE_ID _CreatureID = CREATURE_ID::HitBox);
	virtual ~GHitBox() override;

	friend class GPAttackState;
	friend class GCreature;

};

