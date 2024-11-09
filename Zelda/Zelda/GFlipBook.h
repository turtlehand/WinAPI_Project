#pragma once
#include "GAsset.h"

class GSprite;

class GFlipBook : public GAsset
{
private:
	vector<pair<GSprite*,RenderInfo>>    m_Sprites;

public:
	void AddSprite(GSprite* _Sprite, const RenderInfo& _RenderInfo) { m_Sprites.push_back(make_pair(_Sprite,_RenderInfo)); }
	GSprite* GetSprite(int _Idx) { return m_Sprites[_Idx].first; }
	RenderInfo& GetRenderInfo(int _Idx) { return m_Sprites[_Idx].second; }

	int GetMaxSpriteCount() { return m_Sprites.size(); }

public:
	virtual int Save(const wstring& _RelativePath) override;
	virtual int Load(const wstring & _RelativePath) override;

public:
	GFlipBook();
	~GFlipBook();
};


