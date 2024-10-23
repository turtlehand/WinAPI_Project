#include "pch.h"
#include "DeBugRenderManager.h"

#include "CSelectGDI.h"
#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "GCamera.h"

DeBugRenderManager::DeBugRenderManager() :
	m_Show(true)
{

}

DeBugRenderManager::~DeBugRenderManager()
{

}

void DeBugRenderManager::Progress()
{
	if (GETKEYDOWN(KEY::NUM9))
		m_Show ? m_Show = false : m_Show = true;
}

void DeBugRenderManager::Render()
{
	list<DeBugRenderInfo>::iterator iter = m_DeBugInfo.begin();

	for (iter; iter != m_DeBugInfo.end();)
	{
		if (m_Show)
		{
			SELECT_PEN((*iter).Color);
			SELECT_BRUSH(BRUSH_TYPE::HOLLOW);

			switch ((*iter).Type)
			{
			case DEBUG_SHAPE::RECT:
			{
				
				Vec2 rPos = GCamera::GetInst()->GetRenderPos((*iter).vParam0);
				Vec2 rScale = (*iter).vParam1;
				Rectangle(CEngine::GetInst()->GetSecondDC(),
					rPos.x - rScale.x / 2.f,
					rPos.y - rScale.y / 2.f,
					rPos.x + rScale.x / 2.f,
					rPos.y + rScale.y / 2.f);
			}
			break;
			case DEBUG_SHAPE::CIRCLE:
			{
				Vec2 rPos = GCamera::GetInst()->GetRenderPos((*iter).vParam0);
				Vec2 rScale = (*iter).vParam1;
				Ellipse(CEngine::GetInst()->GetSecondDC(),
					rPos.x - rScale.x,
					rPos.y - rScale.y,
					rPos.x + rScale.x,
					rPos.y + rScale.y);
			}
			break;
			case DEBUG_SHAPE::LINE:
			{
				Vec2 rPos0 = GCamera::GetInst()->GetRenderPos((*iter).vParam0);
				Vec2 rPos1 = GCamera::GetInst()->GetRenderPos((*iter).vParam1);
				MoveToEx(CEngine::GetInst()->GetSecondDC(), rPos0.x, rPos0.y, nullptr);
				LineTo(CEngine::GetInst()->GetSecondDC(), rPos1.x, rPos1.y);
			}
			break;
			}
		}
	
		(*iter).Time += DT;
		if ((*iter).Time >= (*iter).Duration)
			iter = m_DeBugInfo.erase(iter);
		else
			++iter;
	}
}
