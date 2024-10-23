#pragma once

class GSound;

class GSoundManager
{
	SINGLE(GSoundManager)
private:
	LPDIRECTSOUND8		m_SoundDevice;		// ���� ī�� ����
	GSound*				m_pBGM;				// BGM Sound


public:
	int Init();
	LPDIRECTSOUND8 GetSoundDevice() { return m_SoundDevice; }
	void RegisterToBGM(GSound* _pSound);
};

