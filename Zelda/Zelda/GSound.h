#pragma once
#include "GAsset.h"
class GSound :
    public GAsset
{
private:
    LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
    DSBUFFERDESC			m_tBuffInfo;
    int						m_iVolume;

public:
    virtual int Load(const wstring& _RelativePath);

private:
    bool LoadWaveSound(const wstring& _RelativePath);

public:
    // ���� ���
    void Play(bool _bLoop = false);

    // ����������� ���
    void PlayToBGM(bool _bLoop = false);

    // ����
    void Stop(bool _bReset = false);

    // ���� ����
    void SetVolume(float _fVolume);

    // ���� ��� ��ġ (0 ~100)
    void SetPosition(float _fPosition); // 0 ~ 100

    int GetDecibel(float _fVolume);

public:
    GSound();
    ~GSound();
    friend class GAssetManager;

};

