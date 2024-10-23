#pragma once

class GUI;

// ��� UI �� �߿��� � UI�� Focus �������� �˻�
// Focus ���� UI�� �̺�Ʈ ó���� �� �� �ֵ��� ��� UI �� ���� �� �˻��ϴ� ����
class GUIManager
{
	SINGLE(GUIManager);
private:
	GUI* m_FocuesdUI;		// ��Ŀ�� �Ǿ��ִ� UI
	GUI* m_PriorityUI;		// ��Ŀ�� �Ǿ��ִ� UI ������ �ٽ� ���� �켱������ ���� UI

private:
	GUI* GetPriorityUI(GUI* _ParentUI);
	void ReleaseCheck(GUI* _UI);


public:
	void Progress();
};

