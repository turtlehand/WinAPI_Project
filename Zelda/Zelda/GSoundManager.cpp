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
	// 사운드 카드를 생성 후 m_SoundDeviece에 주소를 저장한다.
	if (FAILED(DirectSoundCreate8(NULL, &m_SoundDevice, NULL)))
	{
		MessageBox(NULL, L"사운드 디바이스 생성 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 협조레벨 설정
	HWND hWnd = CEngine::GetInst()->GetMainWndHwnd();
	if (FAILED(m_SoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"사운드 매니저 초기화 실패", L"SYSTEM ERROR", MB_OK);
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
