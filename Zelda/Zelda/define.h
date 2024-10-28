#pragma once

#define SINGLE(Type)	public:\
							static Type* GetInst()\
							{\
								static Type engine;\
								return &engine;\
							}\
						private:\
							Type();\
							Type(const Type& _Origin) = delete;\
							void operator =(const Type& _Origin) = delete;\
							~Type();

// �̷��� �Ǹ� ��ũ�δ� �� �������� �ѹ��� �� �� �ۿ� ���� �ʳ�?
// {} ��ȣ�� ����ϸ� ���� ������ ������ ����� �� ���� ������ ������� ���� Ȱ��
#define SELECT_PEN(Pen)		CSelectGDI SelectPen(CEngine::GetInst()->GetSecondDC(), CEngine::GetInst()->GetPen(Pen));
#define SELECT_BRUSH(Brush)	CSelectGDI SelectBrush(CEngine::GetInst()->GetSecondDC(), CEngine::GetInst()->GetBrush(Brush));

#define DT CTimeMgr::GetInst()->DeltaTime()
#define FPS CTimeMgr::GetInst()->FramePerSecond()

#define GETKEYDOWN(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::DOWN
#define GETKEYPRESSED(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::PRESSED
#define GETKEYUP(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::UP
#define GETKEYNONE(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::NONE

#define DELETEGAMEOBJECT(p) if(p != nullptr) {delete p; p = nullptr;}

#define PI 3.14159265

#define TILE_SIZE 16