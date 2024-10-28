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

// 이렇게 되면 매크로는 각 영역에서 한번만 쓸 수 밖에 없지 않나?
// {} 괄호를 사용하면 지역 변수로 지역이 사라질 때 지역 변수도 사라지는 것을 활용
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