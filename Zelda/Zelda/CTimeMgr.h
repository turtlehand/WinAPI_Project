#pragma once
class CTimeMgr
{
private:
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_PrevCount;
	LARGE_INTEGER m_CurCount;

	UINT m_FPS;
	float m_DT;	// Delta TIme : 프레임 간격 시간, 1 프레임 동작하는데 걸리는 시간
	float m_Time;
	wchar_t m_Info[255];

public:
	void Init();
	void Progress();

	float DeltaTime() { return m_DT; }
	UINT FramePerSecond() { return m_FPS; }

	void PrintInfo();

	
};

