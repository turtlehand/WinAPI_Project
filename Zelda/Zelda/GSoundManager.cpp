#include "pch.h"
#include "GSoundManager.h"

#include "CEngine.h"

#include "GSound.h"

GSoundManager::GSoundManager() :
	m_SoundDevice(nullptr),
	m_pBGM(nullptr)
{}

GSoundManager::~GSoundManager()
{}

int GSoundManager::Init()
{
	// ���� ī�带 ���� �� m_SoundDeviece�� �ּҸ� �����Ѵ�.
	if (FAILED(DirectSoundCreate8(NULL, &m_SoundDevice, NULL)))
	{
		MessageBox(NULL, L"���� ����̽� ���� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� �������� ����
	HWND hWnd = CEngine::GetInst()->GetMainWndHwnd();
	if (FAILED(m_SoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"���� �Ŵ��� �ʱ�ȭ ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void GSoundManager::RegisterToBGM(GSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);
	m_pBGM = _pSound;
}
