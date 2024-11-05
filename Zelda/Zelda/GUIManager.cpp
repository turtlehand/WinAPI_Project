#include "pch.h"
#include "GUIManager.h"

#include "GUI.h"
#include "CLevel.h"
#include "CLevelMgr.h"

GUIManager::GUIManager() :
	m_FocuesdUI(nullptr),
	m_PriorityUI(nullptr)
{

}

GUIManager::~GUIManager()
{

}

// 부모 UI에서 가장 우선순위가 높고 호버중인 UI를 찾는다.
// 이때 호버중인 UI가 없다면 nullptr을 반환 시켜준다.
GUI* GUIManager::GetPriorityUI(GUI* _ParentUI)
{
	GUI* pPriorty = nullptr;

	static list<GUI*>  queue;
	queue.push_back(_ParentUI);

	while (!queue.empty())
	{
		GUI* pUI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pUI->m_vecChild.size(); ++i)
		{
			queue.push_back((GUI*)pUI->m_vecChild[i]);
		}

		if (pUI->IsMouseHover())
			pPriorty = pUI;
	}

	return pPriorty;
}

// 해당 UI에 자식을 포함 모든 UI를 LBtnDown을 해제시켜준다.
void GUIManager::ReleaseCheck(GUI* _UI)
{
	// Queue 역할을 함 List
	static list<GUI*> queue;
	queue.clear();

	// 최상위 부모 UI 입력
	queue.push_back(_UI);

	// Queue 가 비어있지 않다면 반복문 실행
	while (!queue.empty())
	{
		GUI* pUI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pUI->m_vecChild.size(); ++i)
		{
			queue.push_back((GUI*)pUI->m_vecChild[i]);
		}

		if (GETKEYUP(KEY::LBTN))
			pUI->m_LBtnDown = false;
	}
}

void GUIManager::Progress()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	vector<CObj*>& vecUI = pCurLevel->GetUI();

	// 마우스 왼쪽버튼이 눌린 상황 체크
	KEY_STATE LBtnState = CKeyMgr::GetInst()->GetKeyState(KEY::LBTN);

	vector<CObj*>::reverse_iterator rIter = vecUI.rbegin();

	for (; rIter != vecUI.rend(); ++rIter)
	{
		// UI 레이어에 있는 오브젝트가 진짜 UI 객체인지 확인 및 다운캐스팅
		GUI* pParentUI = dynamic_cast<GUI*>(*rIter);
		assert(pParentUI != nullptr);

		// 최상위 부모 UI 포함, 본인의 자식들 중 가장 우선순위가 높은 UI를 찾아서 반환한다.
		GUI* pPriortyUI = GetPriorityUI(pParentUI);
		if (pPriortyUI == nullptr)
		{
			ReleaseCheck(pParentUI);
			continue;
		}

		if (LBtnState == KEY_STATE::DOWN && pPriortyUI->IsMouseHover())
		{
			pPriortyUI->m_LBtnDown = true;
			pPriortyUI->MouseLBtnDown();

			vecUI.erase((rIter + 1).base());
			vecUI.push_back(pParentUI);
			break;
		}
		if (LBtnState == KEY_STATE::UP)
		{
			if (pPriortyUI->IsMouseHover())
			{
				if (pPriortyUI->m_LBtnDown)
					pPriortyUI->MouseLBtnClikced();
				else
					pPriortyUI->MouseReleased();
				ReleaseCheck(pParentUI);
				break;
			}
		}

	}
}
