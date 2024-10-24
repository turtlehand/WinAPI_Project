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

	// �浹�� �ִ�.
	if (!IsDead && IsCollision_BoxBtwBox(_LeftCol, _RightCol))
	{
		// ������ �浹�� �� ����.
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
		
		// ������ �浹�Ͽ���.
		else if (iter->second == true)
		{
			_LeftCol->Overlap(_RightCol);
			_RightCol->Overlap(_LeftCol);
		}
	}
	// �浹���� �ʾҴ�.
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
