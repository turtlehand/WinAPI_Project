#pragma once
#include "GAsset.h"

class GTexture;

class GSprite : public GAsset
{
private:
	GTexture* m_Atlas;		// 스프라이트가 타겟으로 지정한 아틀라스 텍스쳐
	Vec2 m_LeftTop;			// 좌, 상단 픽셀 위치
	Vec2 m_Slice;			// 조각 크기
	Vec2 m_Offset;			// 추가 보정이동

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

