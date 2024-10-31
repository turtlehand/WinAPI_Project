#pragma once

class GTexture;
class GSprite;
class GFlipBook;
class GSound;
class GTile;
class GTilePalette;

class GAssetManager
{
	SINGLE(GAssetManager);
private:
	map<wstring, GTexture*> m_mapTexture;
	map<wstring, GSprite*> m_mapSprite;
	map<wstring, GFlipBook*> m_mapFlipBook;
	map<wstring, GSound*> m_mapSound;
	map<wstring, GTile*> m_mapTile;
	map<wstring, GTilePalette*> m_mapTilePalette;
	

public:
	void Init();

	GTexture* FindTexture(const wstring& _Key);
	GTexture* LoadTexture(const wstring& _Key, const wstring& _RelativePath);
	GTexture* CreateTexture(const wstring& _Key, UINT _Width, UINT _Height);
	int DeleteTexture(const wstring& _Key);

	GSprite* FindSprite(const wstring& _Key);
	GSprite* LoadSprite(const wstring& _Key, const wstring& _RelativePath);
	void AddSprite(const wstring& _Key, GSprite* _Sprite);

	GFlipBook* FindFlipBook(const wstring& _Key);
	GFlipBook* LoadFlipBook(const wstring& _Key, const wstring& _RelativePath);
	void AddFlipBook(const wstring& _Key, GFlipBook* _FlipBook);

	GSound* FindSound(const wstring& _Key);
	GSound* LoadSound(const wstring& _Key, const wstring& _RelativePath);

	GTile* FindTile(const wstring& _Key);
	GTile* LoadTile(const wstring& _Key, const wstring& _RelativePath);
	GTile* CreateTile(const wstring& _Key, const wstring& _RelativePath, GSprite* _Sprite);
	//void AddTile(const wstring& _Key, GTile* _Tile);

	GTilePalette* FindTilePalette(const wstring& _Key);
	GTilePalette* LoadTilePalette(const wstring& _Key, const wstring& _RelativePath);
	//void CreateTilePalette(const wstring& _Key);
	
};
