#pragma once

class GSound;

class GSoundManager
{
	SINGLE(GSoundManager)
private:
	LPDIRECTSOUND8		m_SoundDevice;		// 사운드 카드 제어
	GSound*				m_pBGM;				// BGM Sound


public:
	int Init();
	LPDIRECTSOUND8 GetSoundDevice() { return m_SoundDevice; }
	void RegisterToBGM(GSound* _pSound);
};

