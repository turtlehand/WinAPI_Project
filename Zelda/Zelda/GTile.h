#pragma once
#include "GAsset.h"

class GSprite;

class GTile :
    public GAsset
{
private:
	GSprite* m_Sprite;		// ��������Ʈ�� Ÿ������ ������ ��Ʋ�� �ؽ���
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