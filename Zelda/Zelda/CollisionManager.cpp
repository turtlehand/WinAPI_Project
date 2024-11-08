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
	// �Է����� ���� ���̾� ��ȣ�߿��� �� �������� Matrix�� ������, �� ū ������ ���� ����Ѵ�.
	UINT Row = (UINT)_Left;			// �� ����
	UINT Col = (UINT)_Right;		// �� ����

	if (Col < Row)
	{
		Row = (UINT)_Right;
		Col = (UINT)_Left;
	}

	// �̹� üũ�� �Ǿ��ִٸ�
	if (m_Matrix[Row] & (1 << Col))		// Col��° ��Ʈ�� ���Ͽ�
	{
		// ��Ʈ�� ����.
		m_Matrix[Row] &= ~(1 << Col);
	}
	else
	{
		m_Matrix[Row] |= (1 << Col);
	}
}

// �������� �浹 �˻�
void CollisionManager::CollisionBtwLayer(LAYER_TYPE _Left, LAYER_TYPE _Right)
{
	// ���� ������ ����� Collider�� �����´�.
	const vector<GCollider*>& vecLeft = CLevelMgr::GetInst()->GetCurrentLevel()->GetCollider(_Left);
	const vector<GCollider*>& vecRight = CLevelMgr::GetInst()->GetCurrentLevel()->GetCollider(_Right);

	// ���� �ٸ� ���̾�� �浹 �˻�
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

	// ���� ���̾�� �浹 �˻�
	else
	{
		// �ߺ� �˻� or �ڱ��ڽŰ��� �˻縦 ���ϱ� ���ؼ� j�� i +1 ���� �����Ѵ�.
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

	// �� �浹ü ������ ��ϵ� ���� ����.
	if (iter == m_ColInfo.end())
	{
		m_ColInfo.insert(make_pair(ColID.ID,false));
		iter = m_ColInfo.find(ColID.ID);
	}

	// �� �浹ü �� 1���� ���� ���� ������Ʈ���
	bool IsDead = _LeftCol->GetOwner()->IsDead() || _RightCol->GetOwner()->IsDead();

	// �� �浹ü �� ��� Ȱ��Ȱ ������
	bool IsActive = _LeftCol->GetOwner()->GetActive() && _RightCol->GetOwner()->GetActive();

	// �浹�� �ִ�.
	if (IsActive && !IsDead && IsCollision(_LeftCol, _RightCol))
	{
		// ������ �浹�� �� ����.
		if (iter->second == false)
		{
			// �ϳ��� Trigger ����
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
		
		// ������ �浹�Ͽ���.
		else if (iter->second == true)
		{
			// �ϳ��� Trigger ����
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
	// �浹���� �ʾҴ�.
	else
	{
		if (iter->second == true)
		{
			// �ϳ��� Trigger ����
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

	GRigidBody* _LeftRigid = _LeftBox->GetOwner()->GetComponent<GRigidBody>();
	GRigidBody* _RightRigid = _RightBox->GetOwner()->GetComponent<GRigidBody>();

	assert(_LeftBox != nullptr && _RightBox != nullptr);

	Vec2 LPos = _LeftBox->GetGlobalPos();
	Vec2 LScale = _LeftBox->GetScale();

	Vec2 RPos = _RightBox->GetGlobalPos();
	Vec2 RScale = _RightBox->GetScale();

	Vec2 Distance = _RightBox->GetGlobalPos() - _LeftBox->GetGlobalPos();


	if (fabs(Distance.x) < (LScale.x + RScale.x ) / 2.f &&
		fabs(Distance.y) < (LScale.y + RScale.y ) / 2.f)
	{
		// �ϳ��� Trigger ���°� �ƴ϶�� ���� �о��.
		if (!(_LeftCol->GetTrigger() || _RightCol->GetTrigger()))
		{
			Vec2 Pull;
			Pull.x = ((LScale.x + RScale.x) / 2.f - fabs(Distance.x)) / 2;
			Pull.y = ((LScale.y + RScale.y) / 2.f - fabs(Distance.y)) / 2;

			// ������ ������ ���� x���� ���� �δ�.
			if (Pull.x < Pull.y)
			{
				// ���� �ݶ��̴��� ���ʿ� �ְ� ������ �ݶ��̴��� �����ʿ� ���� ��
				if (LPos.x < RPos.x)
				{
					if(_LeftRigid != nullptr)
						_LeftCol->GetOwner()->AddPos(-Pull.x,0);
					if (_RightRigid != nullptr)
						_RightCol->GetOwner()->AddPos(Pull.x,0);
				}
				// ���� �ݶ��̴��� �����ʿ� �ְ� ������ �ݶ��̴��� ���ʿ� ���� ��
				else if (LPos.x > RPos.x)
				{
					if (_LeftRigid != nullptr)
						_LeftCol->GetOwner()->AddPos(Pull.x, 0);
					if (_RightRigid != nullptr)
						_RightCol->GetOwner()->AddPos(-Pull.x, 0);
				}
			}
			
			// ������ ������ ���� y���� ���� �δ�.
			else if (Pull.y < Pull.x)
			{
				// ���� �ݶ��̴��� �Ʒ��� �ְ� ������ �ݶ��̴��� ���� ���� ��
				if (LPos.y < RPos.y)
				{
					if (_LeftRigid != nullptr)
						_LeftCol->GetOwner()->AddPos(0, -Pull.y);
					if (_RightRigid != nullptr)
						_RightCol->GetOwner()->AddPos(0, Pull.y);
				}
				// ���� �ݶ��̴��� ���� �ְ� ������ �ݶ��̴��� �Ʒ��� ���� ��
				else if (LPos.y > RPos.y)
				{
					if (_LeftRigid != nullptr)
						_LeftCol->GetOwner()->AddPos(0, Pull.y);
					if (_RightRigid != nullptr)
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
		// �������� ��ǥ�� ���Ѵ�.
		Vec2 RT = LPos + Vec2(LScale.x, LScale.y) / 2;
		Vec2 RB = LPos + Vec2(LScale.x, -LScale.y) / 2;
		Vec2 LT = LPos + Vec2(-LScale.x, LScale.y) / 2;
		Vec2 LB = LPos + Vec2(-LScale.x, -LScale.y) / 2;

		// ���� �簢���� ������ ���� �ִ�.
		if ((RPos - RT).x > 0 && (RPos - RT).y > 0)
		{
			// ���ȿ� �簢���� �������� �ִ�.
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

void CollisionManager::Collision(GRigidBody* _LeftRigid, GRigidBody* _RightRigid)
{
	if (_LeftRigid != nullptr && _RightRigid != nullptr)
	{
		float m1 = _LeftRigid->GetMass();  // ��ü 1�� ����
		float m2 = _RightRigid->GetMass();  // ��ü 2�� ����
		Vec2 u1 = _LeftRigid->GetVelocity();  // ��ü 1�� �浹 �� �ӵ�
		Vec2 u2 = _RightRigid->GetVelocity();  // ��ü 2�� �浹 �� �ӵ� 
		float e = 1.f; //(_LeftRigid->GetElasticity() + _RightRigid->GetElasticity()) / 2;

		// �浹 �� �ӵ� ���� ���
		float v1_x = ((e + 1) * m2 * u2.x + u1.x * (m1 - e * m2)) / (m1 + m2);  //��ü 1�� �浹�� x���� �ӵ�
		float v1_y = ((e + 1) * m2 * u2.y + u1.y * (m1 - e * m2)) / (m1 + m2);  //��ü 1�� �浹�� y���� �ӵ�
		float v2_x = ((e + 1) * m1 * u1.x + u2.x * (m2 - e * m1)) / (m1 + m2);  //��ü 2�� �浹�� x���� �ӵ�
		float v2_y = ((e + 1) * m1 * u1.y + u2.y * (m2 - e * m1)) / (m1 + m2);  //��ü 2�� �浹�� y���� �ӵ�

		// ��ü 1,2�� ���ο� �ӵ� ����
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
			// üũ�� �Ǿ����� �ʴٸ� �Ѿ��
			if (!(m_Matrix[Row] & (1 << Col)))
				continue;
			CollisionBtwLayer((LAYER_TYPE)Row, (LAYER_TYPE)Col);
		}
	}
}
