#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CTimeMgr::CTimeMgr() :
	m_Frequency{},
	m_PrevCount{},
	m_CurCount{},
	m_FPS(0),
	m_DT(0.f),
	m_Time(0.f),
	m_Info{}
{
}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	// 1c�ʿ� 1000 ī���� -> �ʴ� ī���� ���� �ʹ� ����
	// GetTIckCount();
	
	// �����Ӱ� ������ ������ �ð�
	QueryPerformanceFrequency(&m_Frequency);	// �ʴ� ī���� �� (õ��)
	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::Progress()
{
	// ���� ���� Count ��
	QueryPerformanceCounter(&m_CurCount);

	m_DT = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_Frequency.QuadPart;
	m_PrevCount = m_CurCount;

	++m_FPS;
	m_Time += m_DT;

	if (1.f <= m_Time)
	{
		wchar_t buff[255] = {};
		swprintf_s(buff, 255, L"FPS : %d, DeltaTime : %f", m_FPS, m_DT);
		SetWindowText(CEngine::GetInst()->GetMainWndHwnd(), buff);

		m_FPS = 0;
		m_Time -= 1.f;
	}
}

void CTimeMgr::PrintInfo()
{
	TextOut(CEngine::GetInst()->GetSecondDC(), 0, 0, m_Info, wcslen(m_Info));
}
