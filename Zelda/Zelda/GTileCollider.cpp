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

	// 우상좌하 순으로 타일이 있는지 확인한다.

	// 오른쪽에 타일이 있다면

	vector<CObj*> _Tile = CLevelMgr::GetInst()->GetCurrentLevel()->GetGameObject(GetOwner()->GetLayerType());

	for (int i = 0; i < _Tile.size(); ++i)
	{
		// 오른쪽에 타일이 있다면
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

	// 상하좌우에 존재하지 않는다.
	Vec2 Pos = GetOwner()->GetPos();
	if (!m_ExtendX && !m_ExtendY)
	{
		return;
	}

	// 최적화 완료
	m_IsOptimize = true;
	// 우,좌로 타일이 있다면 이 타일은 X축으로 뻗어나가게 한다.
	
	// 상,하로 타일이 있다면 이 타일은 Y축으로 뻗어나가게 한다.

	// 무한 반복문
	// X축일 때
	// GetOwner.x + (Scale.x / 합쳐진 개수 ) + 원래 크기 위치에 합쳐진 개수가 1인 타일이 있는지 확인한다.
	// 타일이 있다면 이 GetOwner의 위치를 GetOwner.x + 원래크기 / 2를 변경한다.
	// 그리고 타일의 크기를 원래 크기만큼 증가시키며
	// 찾은 타일은 삭제한다 또는 비활성화 한다.


}

