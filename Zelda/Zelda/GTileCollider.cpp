#include "pch.h"
#include "GTileCollider.h"

#include "CLevel.h"
#include "CLevelMgr.h"

GTileCollider::GTileCollider() :
	GBoxCollider(COLLIDER_TYPE::TILE),
	m_Num(1)
{
	
}

GTileCollider::~GTileCollider()
{

}

void GTileCollider::FinalTick()
{
	GBoxCollider::FinalTick();
	Optimize();
}

void GTileCollider::Optimize()
{
	if (m_IsOptimize)
		return;

	m_DefaultScale = GetScale();

	// ������� ������ Ÿ���� �ִ��� Ȯ���Ѵ�.

	// �����ʿ� Ÿ���� �ִٸ�

	vector<CObj*> _Tile = CLevelMgr::GetInst()->GetCurrentLevel()->GetGameObject(GetOwner()->GetLayerType());

	for (int i = 0; i < _Tile.size(); ++i)
	{
		// �����ʿ� Ÿ���� �ִٸ�
		if (_Tile[i]->GetPos().x == (GetOwner()->GetPos().x + m_DefaultScale.x))
		{
			m_ExtendX = true;
			break;
		}
		else if (_Tile[i]->GetPos().x == (GetOwner()->GetPos().x - m_DefaultScale.x))
		{
			m_ExtendX = true;
			break;
		}
		else if (_Tile[i]->GetPos().y == (GetOwner()->GetPos().y + m_DefaultScale.y))
		{
			m_ExtendY = true;
			break;
		}
		else if (_Tile[i]->GetPos().y == (GetOwner()->GetPos().y - m_DefaultScale.y))
		{
			m_ExtendY = true;
			break;
		}

	}

	// �����¿쿡 �������� �ʴ´�.
	Vec2 Pos = GetOwner()->GetPos();
	if (!m_ExtendX && !m_ExtendY)
	{
		return;
	}

	// ����ȭ �Ϸ�
	m_IsOptimize = true;
	// ��,�·� Ÿ���� �ִٸ� �� Ÿ���� X������ ������� �Ѵ�.
	
	// ��,�Ϸ� Ÿ���� �ִٸ� �� Ÿ���� Y������ ������� �Ѵ�.

	// ���� �ݺ���
	// X���� ��
	// GetOwner.x + (Scale.x / ������ ���� ) + ���� ũ�� ��ġ�� ������ ������ 1�� Ÿ���� �ִ��� Ȯ���Ѵ�.
	// Ÿ���� �ִٸ� �� GetOwner�� ��ġ�� GetOwner.x + ����ũ�� / 2�� �����Ѵ�.
	// �׸��� Ÿ���� ũ�⸦ ���� ũ�⸸ŭ ������Ű��
	// ã�� Ÿ���� �����Ѵ� �Ǵ� ��Ȱ��ȭ �Ѵ�.


}

