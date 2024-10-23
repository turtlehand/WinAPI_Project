#pragma once
#include "GAsset.h"

class GSprite;

class GFlipBook : public GAsset
{
private:
	vector<GSprite*>    m_Sprites;

public:
	void AddSprite(GSprite* _Sprite) { m_Sprites.push_back(_Sprite); }
	GSprite* GetSprite(int _Idx) { return m_Sprites[_Idx]; }

	int GetMaxSpriteCount() { return m_Sprites.size(); }

public:
	virtual int Save(const wstring& _RelativePath) override;
	virtual int Load(const wstring & _RelativePath) override;

public:
	GFlipBook();
	~GFlipBook();
};


