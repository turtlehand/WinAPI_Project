#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr);
private:
	CLevel* m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel* m_CurLevel;
	LEVEL_TYPE m_CurLevelType;
	LEVEL_TYPE m_PrevLevelType;

public:
	void Init();
	void Progress();
	void Render();
	
public:
	CLevel* GetCurrentLevel() { return m_CurLevel; }
	LEVEL_TYPE GetCurrentLevelType() { return m_CurLevelType; }
	LEVEL_TYPE GetPrevLevelType() { return m_PrevLevelType; }
	CLevel* GetLevel(LEVEL_TYPE _Level) { return m_arrLevel[(UINT)_Level]; }


private:
	friend class TaskManager;
	void ChangeLevel(LEVEL_TYPE _Level);
	void ReLoadLevel();
	

};

