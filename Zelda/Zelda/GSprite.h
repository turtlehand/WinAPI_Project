#pragma once
#include "GAsset.h"

class GTexture;

class GSprite : public GAsset
{
private:
	GTexture* m_Atlas;		// ��������Ʈ�� Ÿ������ ������ ��Ʋ�� �ؽ���
	Vec2 m_LeftTop;			// ��, ��� �ȼ� ��ġ
	Vec2 m_Slice;			// ���� ũ��
	Vec2 m_Offset;			// �߰� �����̵�

public:
	GTexture* const GetAtlas() { return m_Atlas; }
	Vec2 const GetLeftTop() { return m_LeftTop; }
	Vec2 const GetSlice() { return m_Slice; }
	Vec2 const GetOffset() { return m_Offset;}
	
	void SetLeftTop(Vec2 _LeftTop) { m_LeftTop = _LeftTop; }
	void SetSlice(Vec2 _Slice) { m_Slice = _Slice; }
	void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }

public:
	virtual int Save(const wstring& _RelativePath) override;
	virtual int Load(const wstring& _RelativePath) override;
	void Create(GTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice);

public:
	GSprite();
	virtual ~GSprite() override;

};

