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

// �θ� UI���� ���� �켱������ ���� ȣ������ UI�� ã�´�.
// �̶� ȣ������ UI�� ���ٸ� nullptr�� ��ȯ �����ش�.
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

// �ش� UI�� �ڽ��� ���� ��� UI�� LBtnDown�� ���������ش�.
void GUIManager::ReleaseCheck(GUI* _UI)
{
	// Queue ������ �� List
	static list<GUI*> queue;
	queue.clear();

	// �ֻ��� �θ� UI �Է�
	queue.push_back(_UI);

	// Queue �� ������� �ʴٸ� �ݺ��� ����
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

	// ���콺 ���ʹ�ư�� ���� ��Ȳ üũ
	KEY_STATE LBtnState = CKeyMgr::GetInst()->GetKeyState(KEY::LBTN);

	vector<CObj*>::reverse_iterator rIter = vecUI.rbegin();

	for (; rIter != vecUI.rend(); ++rIter)
	{
		// UI ���̾ �ִ� ������Ʈ�� ��¥ UI ��ü���� Ȯ�� �� �ٿ�ĳ����
		GUI* pParentUI = dynamic_cast<GUI*>(*rIter);
		assert(pParentUI != nullptr);

		// �ֻ��� �θ� UI ����, ������ �ڽĵ� �� ���� �켱������ ���� UI�� ã�Ƽ� ��ȯ�Ѵ�.
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
