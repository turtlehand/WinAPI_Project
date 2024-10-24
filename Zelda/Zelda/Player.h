#pragma once
#include "CObj.h"

class GCollider;
class GFlipBookPlayer;
class GTexture;
class GRigidBody;

class Player :
    public CObj
{
private:
	float m_MaxMoveSpeed;		// 최대 이동속도
	float m_InitForce;

	float   m_AttSpeed;			// 초당 발사 횟수
	float   m_AccTime;			// 시간 누적

	int m_JumpStack;
	float m_MaxJumpTime;
	float m_JumpTime;

	GCollider* m_Collider;
	GFlipBookPlayer* m_FlipBookPlayer;
	GRigidBody* m_RigidBody;

	GTexture* m_Texture;
public:
	virtual void Begin() override;			// 레벨이 시작될 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

public:
	virtual void EnterOverlap(GCollider* _Collider) override;

public:

	void SetInitForce(float _InitForce) { m_InitForce = _InitForce; }
	float GetInitForce() { return m_InitForce; }

	void SetMaxMoveSpeed(float _MaxMoveSpeed) { m_MaxMoveSpeed = _MaxMoveSpeed; }
	float GetMaxMoveSpeed() { return m_MaxMoveSpeed; }

	void SetAttSpeed(float _AttSpeed) { m_AttSpeed = _AttSpeed; }
	float GetAttSpeed() const { return m_AttSpeed; }

	//void SetAccTime(float _AccTime) { m_AccTime = _AccTime; }
	float GetAccTime() const { return m_AccTime; }

	void SetMaxJumpTime(float _MaxJumpTim) { m_MaxJumpTime = _MaxJumpTim; }
	float GetMaxJumpTime() const { return m_MaxJumpTime; }


private:

#pragma region Move

	void Move();
	void CalMaxMoveSpeed();
	void AddInitForce(Vec2 _Dir, float _Force);

#pragma endregion



	void Shot();
	void Jump();

	void CreatePlayerFlipBook();
	void CreateFlipBook(const wstring& _FlipBookName, GTexture* _Atlas, Vec2 _LftTop, Vec2 _Slice, int MaxFrame);

public:
	Player();
	virtual ~Player() override;
};

