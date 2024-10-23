#pragma once

class GTexture;
class GSprite;
class GFlipBook;
class GSound;

class GAssetManager
{
	SINGLE(GAssetManager);
private:
	map<wstring, GTexture*> m_mapTexture;
	map<wstring, GSprite*> m_mapSprite;
	map<wstring, GFlipBook*> m_mapFlipBook;
	map<wstring, GSound*> m_mapSound;
	

public:
	void Init();

	GTexture* FindTexture(const wstring& _Key);
	GTexture* LoadTexture(const wstring& _Key, const wstring& _RelativePath);
	GTexture* CreateTexture(const wstring& _Key, UINT _Width, UINT _Height);

	GSprite* FindSprite(const wstring& _Key);
	GSprite* LoadSprite(const wstring& _Key, const wstring& _RelativePath);
	void AddSprite(const wstring& _Key, GSprite* _Sprite);

	GFlipBook* FindFlipBook(const wstring& _Key);
	GFlipBook* LoadFlipBook(const wstring& _Key, const wstring& _RelativePath);
	void AddFlipBook(const wstring& _Key, GFlipBook* _FlipBook);

	GSound* FindSound(const wstring& _Key);
	GSound* LoadSound(const wstring& _Key, const wstring& _RelativePath);
	
};
