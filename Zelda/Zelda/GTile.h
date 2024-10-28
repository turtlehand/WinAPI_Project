#pragma once
#include "GAsset.h"

class GSprite;

class GTile :
    public GAsset
{
private:
	GSprite* m_Sprite;		// 스프라이트가 타겟으로 지정한 아틀라스 텍스쳐
	bool m_Collider;

public:
	GSprite* GetSprite() const { return m_Sprite; }

public:
	virtual int Save(const wstring& _RelativePath) override;
	virtual int Load(const wstring& _RelativePath) override;
	void Create(GSprite* _Sprite, bool _Collider);

public:
	GTile();
	virtual ~GTile() override;

};