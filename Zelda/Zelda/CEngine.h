#pragma once

class CObj;
class CLevel;
class GTexture;

// ���α׷��� �ֻ��� ������
class CEngine
{
	SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;		// ���μ��� �ּ�
	HWND		m_hWnd;			// ���� ������ �ڵ�
	Vec2		m_Resolution;	// ���� ������ �ػ�
	HDC			m_hDC;			// Main DC(Device Context) �׸��� ���� ������, �׸��� ���� ����ü

	GTexture*	m_BackBuffer;

	HPEN		m_Pen[(UINT)PEN_TYPE::END];
	HBRUSH		m_Brush[(UINT)BRUSH_TYPE::END];

public:

	HWND GetMainWndHwnd() { return m_hWnd; }
	Vec2 GetResolution() { return m_Resolution; }
	HDC GetMainDC() { return m_hDC; }

	HDC GetSecondDC();

	HPEN GetPen(PEN_TYPE _Type) { return m_Pen[(UINT)_Type]; }
	HBRUSH GetBrush(BRUSH_TYPE _Type) { return m_Brush[(UINT)_Type]; }


public:
	int Init(HINSTANCE _Inst, POINT _Resolution);
	void Progress();

	void ChangeWindowSize(Vec2 _vResolution);

private:
	void CreateGDIObject();
	void CreateSecondBuffer();

};
