#include "pch.h"
#include "CollisionManager.h"

#include "CLevelMgr.h"

#include "CLevel.h"
#include "GCollider.h"

#include "GRigidBody.h"



CollisionManager::CollisionManager() :
	m_Matrix{}
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::CollisionCheck(LAYER_TYPE _Left, LAYER_TYPE _Right)
{
	// 입력으로 들어온 레이어 번호중에서 더 작은값을 Matrix의 행으로, 더 큰 값으로 열로 사용한다.
	UINT Row = (UINT)_Left;			// 열 가로
	UINT Col = (UINT)_Right;		// 행 세로

	if (Col < Row)
	{
		Row = (UINT)_Right;
		Col = (UINT)_Left;
	}

	// 이미 체크가 되어있다면
	if (m_Matrix[Row] & (1 << Col))		// Col번째 비트와 비교하여
	{
		// 비트를 뺀다.
		m_Matrix[Row] &= ~(1 << Col);
	}
	else
	{
		m_Matrix[Row] |= (1 << Col);
	}
}

// 실질적인 충돌 검사
void CollisionManager::CollisionBtwLayer(LAYER_TYPE _Left, LAYER_TYPE _Right)
{
	// 현재 레벨에 저장된 Collider를 가져온다.
	const vector<GCollider*>& vecLeft = CLevelMgr::GetInst()->GetCurrentLevel()->GetCollider(_Left);
	const vector<GCollider*>& vecRight = CLevelMgr::GetInst()->GetCurrentLevel()->GetCollider(_Right);

	// 서로 다른 레이어간의 충돌 검사
	if (_Left != _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				CollisionBtwCollider(vecLeft[i], vecRight[j]);
			}
		}
	}

	// 동일 레이어간의 충돌 검사
	else
	{
		// 중복 검사 or 자기자신과의 검사를 피하기 위해서 j는 i +1 부터 시작한다.
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = i + 1; j < vecRight.size(); ++j)
			{
				CollisionBtwCollider(vecLeft[i], vecRight[j]);
			}
		}
	}
}

void CollisionManager::CollisionBtwCollider(GCollider* _LeftCol, GCollider* _RightCol)
{
	COLLISION_ID ColID = {};
	ColID.Left = _LeftCol->GetID();
	ColID.Right = _RightCol->GetID();

	map<ULONGLONG, bool>::iterator iter = m_ColInfo.find(ColID.ID);

	// 두 충돌체 조합이 등록된 적이 없다.
	if (iter == m_ColInfo.end())
	{
		m_ColInfo.insert(make_pair(ColID.ID,false));
		iter = m_ColInfo.find(ColID.ID);
	}

	// 두 충돌체 중 1개라도 삭제 예정 오브젝트라면
	bool IsDead = _LeftCol->GetOwner()->IsDead() || _RightCol->GetOwner()->IsDead();

	// 충돌해 있다.
	if (!IsDead && IsCollision_BoxBtwBox(_LeftCol, _RightCol))
	{
		// 이전에 충돌한 적 없다.
		if (iter->second == false)
		{
			_LeftCol->EnterOverlap(_RightCol);
			_RightCol->EnterOverlap(_LeftCol);
			iter->second = true;

			/*
			if (!(_LeftCol->GetTrigger() || _RightCol->GetTrigger()))
			{
				GRigidBody* LeftRigid = _LeftCol->GetOwner()->GetComponent<GRigidBody>();
				GRigidBody* RightRigid = _RightCol->GetOwner()->GetComponent<GRigidBody>();

				Collision(LeftRigid, RightRigid);
			}
			*/
		}
		
		// 이전에 충돌하였다.
		else if (iter->second == true)
		{
			_LeftCol->Overlap(_RightCol);
			_RightCol->Overlap(_LeftCol);
		}
	}
	// 충돌하지 않았다.
	else
	{
		if (iter->second == true)
		{
			_LeftCol->ExitOverlap(_RightCol);
			_RightCol->ExitOverlap(_LeftCol);
			iter->second = false;
		}
	}

}

bool CollisionManager::IsCollision_BoxBtwBox(GCollider* _LeftCol, GCollider* _RightCol)
{
	Vec2 LPos = _LeftCol->GetGlobalPos();
	Vec2 LScale = _LeftCol->GetScale();

	Vec2 RPos = _RightCol->GetGlobalPos();
	Vec2 RScale = _RightCol->GetScale();

	Vec2 Distance = _RightCol->GetGlobalPos() - _LeftCol->GetGlobalPos();


	if (fabs(Distance.x) < (LScale.x + RScale.x ) / 2.f &&
		fabs(Distance.y) < (LScale.y + RScale.y ) / 2.f)
	{
		return true;
	}

	return false;
}

void CollisionManager::Collision(GRigidBody* _LeftRigid, GRigidBody* _RightRigid)
{
	if (_LeftRigid != nullptr && _RightRigid != nullptr)
	{
		float m1 = _LeftRigid->GetMass();  // 물체 1의 질량
		float m2 = _RightRigid->GetMass();  // 물체 2의 질량
		Vec2 u1 = _LeftRigid->GetVelocity();  // 물체 1의 충돌 전 속도
		Vec2 u2 = _RightRigid->GetVelocity();  // 물체 2의 충돌 전 속도 
		float e = 1.f; //(_LeftRigid->GetElasticity() + _RightRigid->GetElasticity()) / 2;

		// 충돌 후 속도 공식 사용
		float v1_x = ((e + 1) * m2 * u2.x + u1.x * (m1 - e * m2)) / (m1 + m2);  //물체 1의 충돌후 x방향 속도
		float v1_y = ((e + 1) * m2 * u2.y + u1.y * (m1 - e * m2)) / (m1 + m2);  //물체 1의 충돌후 y방향 속도
		float v2_x = ((e + 1) * m1 * u1.x + u2.x * (m2 - e * m1)) / (m1 + m2);  //물체 2의 충돌후 x방향 속도
		float v2_y = ((e + 1) * m1 * u1.y + u2.y * (m2 - e * m1)) / (m1 + m2);  //물체 2의 충돌후 y방향 속도

		// 물체 1,2에 새로운 속도 적용
		_LeftRigid->SetVelocity(Vec2(v1_x, v1_y));
		_RightRigid->SetVelocity(Vec2(v2_x, v2_y));
	}
}

void CollisionManager::Tick()
{
	for (UINT Row = 0; Row < (UINT)LAYER_TYPE::END; ++Row)
	{
		for (UINT Col = 0; Col < (UINT)LAYER_TYPE::END; ++Col)
		{
			// 체크가 되어있지 않다면 넘어간다
			if (!(m_Matrix[Row] & (1 << Col)))
				continue;
			CollisionBtwLayer((LAYER_TYPE)Row, (LAYER_TYPE)Col);
		}
	}
}
