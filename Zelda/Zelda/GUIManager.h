#pragma once

class GUI;

// 모든 UI 들 중에서 어떤 UI가 Focus 상태인지 검사
// Focus 중인 UI만 이벤트 처리가 될 수 있도록 모든 UI 툴 관리 및 검사하는 역할
class GUIManager
{
	SINGLE(GUIManager);
private:
	GUI* m_FocuesdUI;		// 포커싱 되어있는 UI
	GUI* m_PriorityUI;		// 포커싱 되어있는 UI 내에서 다시 가장 우선순위가 높은 UI

private:
	GUI* GetPriorityUI(GUI* _ParentUI);
	void ReleaseCheck(GUI* _UI);


public:
	void Progress();
};

