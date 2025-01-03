#include "pch.h"
#include "CollisionManager.h"

#include "CLevelMgr.h"

#include "CLevel.h"
#include "GCollider.h"
#include "GBoxCollider.h"
#include "GCircleCollider.h"

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

	// 두 충돌체 중 모두 활성활 상태임
	bool IsActive = _LeftCol->GetOwner()->GetActive() && _RightCol->GetOwner()->GetActive();

	// 충돌해 있다.
	if (IsActive && !IsDead && IsCollision(_LeftCol, _RightCol))
	{
		// 이전에 충돌한 적 없다.
		if (iter->second == false)
		{
			// 하나라도 Trigger 상태
			if (_LeftCol->GetTrigger() || _RightCol->GetTrigger())
			{
				_LeftCol->OnTriggerEnter(_RightCol);
				_RightCol->OnTriggerEnter(_LeftCol);
			}
			else
			{
				_LeftCol->OnCollisionEnter(_RightCol);
				_RightCol->OnCollisionEnter(_LeftCol);
			}

			iter->second = true;
		}
		
		// 이전에 충돌하였다.
		else if (iter->second == true)
		{
			// 하나라도 Trigger 상태
			if (_LeftCol->GetTrigger() || _RightCol->GetTrigger())
			{
				_LeftCol->OnTrigger(_RightCol);
				_RightCol->OnTrigger(_LeftCol);
			}
			else
			{
				_LeftCol->OnCollision(_RightCol);
				_RightCol->OnCollision(_LeftCol);
			}
		}
	}
	// 충돌하지 않았다.
	else
	{
		if (iter->second == true)
		{
			// 하나라도 Trigger 상태
			if (_LeftCol->GetTrigger() || _RightCol->GetTrigger())
			{
				_LeftCol->OnTriggerExit(_RightCol);
				_RightCol->OnTriggerExit(_LeftCol);
			}
			else
			{
				_LeftCol->OnCollisionExit(_RightCol);
				_RightCol->OnCollisionExit(_LeftCol);
			}
			iter->second = false;
		}
	}

}

bool CollisionManager::IsCollision(GCollider* _LeftCol, GCollider* _RightCol)
{

	bool CollisionBool = false;

	if (_LeftCol->GetColliderType() == COLLIDER_TYPE::BOX)
	{
		if(_RightCol->GetColliderType() == COLLIDER_TYPE::BOX)
			CollisionBool = IsCollision_BoxBtwBox(_LeftCol, _RightCol);
		//else if (_RightCol->GetColliderType() == COLLIDER_TYPE::CIRCLE)
			//CollisionBool = IsCollision_BoxBtwCircle(_LeftCol, _RightCol);
	}
	/*
	else if (_LeftCol->GetColliderType() == COLLIDER_TYPE::CIRCLE)
	{
		if (_RightCol->GetColliderType() == COLLIDER_TYPE::BOX)
			CollisionBool = IsCollision_BoxBtwCircle(_RightCol, _LeftCol);
		else if (_RightCol->GetColliderType() == COLLIDER_TYPE::CIRCLE)
			CollisionBool = IsCollision_CircleBtwCircle(_LeftCol, _RightCol);
	}
	*/
	return CollisionBool;
}

bool CollisionManager::IsCollision_BoxBtwBox(GCollider* _LeftCol, GCollider* _RightCol)
{
	GBoxCollider* _LeftBox = dynamic_cast<GBoxCollider*>(_LeftCol);
	GBoxCollider* _RightBox = dynamic_cast<GBoxCollider*>(_RightCol);

	assert(_LeftBox != nullptr && _RightBox != nullptr);

	Vec2 LPos = _LeftBox->GetGlobalPos();
	Vec2 LScale = _LeftBox->GetScale();

	Vec2 RPos = _RightBox->GetGlobalPos();
	Vec2 RScale = _RightBox->GetScale();

	Vec2 Distance = _RightBox->GetGlobalPos() - _LeftBox->GetGlobalPos();

	if (fabs(Distance.x) < (LScale.x + RScale.x ) / 2.f &&
		fabs(Distance.y) < (LScale.y + RScale.y ) / 2.f)
	{
		// 하나라도 Trigger 상태가 아니라면 서로 밀어낸다.
		if (!(_LeftCol->GetTrigger() || _RightCol->GetTrigger()))
		{
			Vec2 Pull;
			Pull.x = ((LScale.x + RScale.x) / 2.f - fabs(Distance.x)) / 2;
			Pull.y = ((LScale.y + RScale.y) / 2.f - fabs(Distance.y)) / 2;

			// 접촉한 면적이 적은 x축을 서로 민다.
			if (Pull.x < Pull.y)
			{
				// 왼쪽 콜라이더가 왼쪽에 있고 오른쪽 콜라이더가 오른쪽에 있을 때
				if (LPos.x < RPos.x)
				{
					if(_LeftBox->IsRigidBody())
						_LeftCol->GetOwner()->AddPos(-Pull.x,0);
					if (_RightBox->IsRigidBody())
						_RightCol->GetOwner()->AddPos(Pull.x,0);
				}
				// 왼쪽 콜라이더가 오른쪽에 있고 오른쪽 콜라이더가 왼쪽에 있을 때
				else if (LPos.x > RPos.x)
				{
					if (_LeftBox->IsRigidBody())
						_LeftCol->GetOwner()->AddPos(Pull.x, 0);
					if (_RightBox->IsRigidBody())
						_RightCol->GetOwner()->AddPos(-Pull.x, 0);
				}
			}
			
			// 접촉한 면적이 적은 y축을 서로 민다.
			else if (Pull.y < Pull.x)
			{
				// 왼쪽 콜라이더가 아래에 있고 오른쪽 콜라이더가 위에 있을 때
				if (LPos.y < RPos.y)
				{
					if (_LeftBox->IsRigidBody())
						_LeftCol->GetOwner()->AddPos(0, -Pull.y);
					if (_RightBox->IsRigidBody())
						_RightCol->GetOwner()->AddPos(0, Pull.y);
				}
				// 왼쪽 콜라이더가 위에 있고 오른쪽 콜라이더가 아래에 있을 때
				else if (LPos.y > RPos.y)
				{
					if (_LeftBox->IsRigidBody())
						_LeftCol->GetOwner()->AddPos(0, Pull.y);
					if (_RightBox->IsRigidBody())
						_RightCol->GetOwner()->AddPos(0, -Pull.y);
				}
			}
			
		}

		return true;
	}

	return false;
}

/*
bool CollisionManager::IsCollision_BoxBtwCircle(GCollider* _LeftCol, GCollider* _RightCol)
{
	GBoxCollider* _LeftBox = dynamic_cast<GBoxCollider*>(_LeftCol);
	GCircleCollider* _RightCircle = dynamic_cast<GCircleCollider*>(_RightCol);

	assert(_LeftBox != nullptr && _RightCircle != nullptr);

	Vec2 LPos = _LeftBox->GetGlobalPos();
	Vec2 LScale = _LeftBox->GetScale();

	Vec2 RPos = _RightCircle->GetGlobalPos();
	float RRadius = _RightCircle->GetRadius();

	Vec2 Distance = _RightCircle->GetGlobalPos() - _LeftBox->GetGlobalPos();

	if (fabs(Distance.x) < (LScale.x / 2.f + RRadius)  &&
		fabs(Distance.y) < (LScale.y / 2.f + RRadius))
	{
		// 꼭짓점의 좌표를 구한다.
		Vec2 RT = LPos + Vec2(LScale.x, LScale.y) / 2;
		Vec2 RB = LPos + Vec2(LScale.x, -LScale.y) / 2;
		Vec2 LT = LPos + Vec2(-LScale.x, LScale.y) / 2;
		Vec2 LB = LPos + Vec2(-LScale.x, -LScale.y) / 2;

		// 원이 사각형의 오른쪽 위에 있다.
		if ((RPos - RT).x > 0 && (RPos - RT).y > 0)
		{
			// 원안에 사각형의 꼭짓점이 있다.
			if ((RPos - RT).Length() < RRadius)
			{
				return true;
			}
			return false;
		}
		else if ((RPos - RB).x > 0 && (RPos - RB).y < 0)
		{
			if ((RPos - RB).Length() < RRadius)
			{
				return true;
			}
			return false;
		}
		else if ((RPos - LT).x < 0 && (RPos - LT).y > 0)
		{
			if ((RPos - LT).Length() < RRadius)
			{
				return true;
			}
			return false;
		}
		else if ((RPos - LB).x < 0 && (RPos - LB).y < 0)
		{
			if ((RPos - LB).Length() < RRadius)
			{
				return true;
			}
			return false;
		}

		return true;
	}

	return false;
}

bool CollisionManager::IsCollision_CircleBtwCircle(GCollider* _LeftCol, GCollider* _RightCol)
{
	GCircleCollider* _LeftCircle = dynamic_cast<GCircleCollider*>(_LeftCol);
	GCircleCollider* _RightCircle = dynamic_cast<GCircleCollider*>(_RightCol);

	assert(_LeftCircle != nullptr && _RightCircle != nullptr);

	Vec2 LPos = _LeftCircle->GetGlobalPos();
	float LRadius = _LeftCircle->GetRadius();

	Vec2 RPos = _RightCircle->GetGlobalPos();
	float RRadius = _RightCircle->GetRadius();

	Vec2 Distance = _RightCircle->GetGlobalPos() - _LeftCircle->GetGlobalPos();


	if (Distance.Length() < LRadius + RRadius)
	{
		return true;
	}

	return false;
}
*/

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
