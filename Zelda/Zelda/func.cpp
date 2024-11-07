#include "pch.h"
#include "func.h"

#include "CObj.h"
#include "TaskManager.h"
#include "DeBugRenderManager.h"

#include "GAsset.h"
#include "GAssetManager.h"

bool IsValid(CObj*& _Object)
{
	// 비어있거나 곧 삭제될 대상이라면 false
	if (nullptr == _Object)
		return false;
	else if (_Object->IsDead())
		return false;

	// 그 외에는 유효함
	return true;
}

void CreateGameObject(CObj* _NewObject, LAYER_TYPE _Layer)
{
	Task task = { TASK_TYPE::CREATE_OBJECT,(DWORD_PTR)_NewObject, (DWORD_PTR)_Layer };
	TaskManager::GetInst()->AddTask(task);
}

void DeleteGameObject(CObj* _DestroyObject)
{
	Task task = { TASK_TYPE::DELETE_OBJECT,(DWORD_PTR)_DestroyObject };
	TaskManager::GetInst()->AddTask(task);

	// 자식 오브젝트들을 삭제한다.
	for (size_t i = 0; i < _DestroyObject->GetChilds().size(); ++i)
	{
		DeleteGameObject(_DestroyObject->GetChilds()[i]);
	}
}

void ChangeLevel(LEVEL_TYPE _Level)
{
	Task task = { TASK_TYPE::CHANGE_LEVEL,(DWORD_PTR)_Level };
	TaskManager::GetInst()->AddTask(task);
}


void DrawDebugRect(PEN_TYPE _Color, time_t _Duration, Vec2 _Position, Vec2 _Scale)
{
	DeBugRenderInfo info;
	info.Color = _Color;
	info.Duration = _Duration;
	info.Time = 0.f;
	info.Type = DEBUG_SHAPE::RECT;
	info.vParam0 = _Position;
	info.vParam1 = _Scale;

	DeBugRenderManager::GetInst()->AddDeBugInfo(info);
}

void DrawDebugCircle(PEN_TYPE _Color, time_t _Duration, Vec2 _Position, float _Radius)
{
	DeBugRenderInfo info;
	info.Color = _Color;
	info.Duration = _Duration;
	info.Time = 0.f;
	info.Type = DEBUG_SHAPE::CIRCLE;
	info.vParam0 = _Position;
	info.vParam1 = Vec2(_Radius, _Radius);

	DeBugRenderManager::GetInst()->AddDeBugInfo(info);
}

void DrawDebugEllipse(PEN_TYPE _Color, time_t _Duration, Vec2 _Position, Vec2 _Scale)
{
	DeBugRenderInfo info;
	info.Color = _Color;
	info.Duration = _Duration;
	info.Time = 0.f;
	info.Type = DEBUG_SHAPE::CIRCLE;
	info.vParam0 = _Position;
	info.vParam1 = Vec2(_Scale.x, _Scale.y);

	DeBugRenderManager::GetInst()->AddDeBugInfo(info);
}

void DrawDebugLine(PEN_TYPE _Color, time_t _Duration, Vec2 _Position0, Vec2 _Position1)
{
	DeBugRenderInfo info;
	info.Color = _Color;
	info.Duration = _Duration;
	info.Time = 0.f;
	info.Type = DEBUG_SHAPE::LINE;
	info.vParam0 = _Position0;
	info.vParam1 = _Position1;

	DeBugRenderManager::GetInst()->AddDeBugInfo(info);
}

// _Dir은 현재 방향 벡터 _Angle은 라디안
Vec2 Rotate(Vec2 _Dir, float _Angle)
{
	_Dir = _Dir.Normalize();

	return Vec2(_Dir.x * cosf(_Angle) - _Dir.y * sinf(_Angle), _Dir.y * cosf(_Angle) + _Dir.x * sinf(_Angle));
}

float DotProduct(const Vec2& _Other1, const Vec2& _Other2)
{
	return _Other1.x * _Other2.x + _Other1.y * _Other2.y;
}

int CCW(const Vec2& _Other1, const Vec2& _Other2)
{
	float result = _Other1.x * _Other2.y - _Other2.x * _Other1.y;

	if (result > 0)
		return 1;
	else if (result < 0)
		return -1;

	return 0;
}

void SaveAssetRef(GAsset* _Asset, FILE* _File)
{
	int Asset = !!_Asset;
	fwrite(&Asset, sizeof(int), 1, _File);
	if (!Asset)
		return;

	ASSET_TYPE type = _Asset->GetAssetType();
	fwrite(&type, sizeof(ASSET_TYPE), 1, _File);

	// 저장하려는 Asset의 Key, Path를 가져온다.
	const wstring& Key = _Asset->GetKey();
	const wstring& Path = _Asset->GetRelativePath();

	// Asset의 Key, Path 문자열을 저장한다.
	size_t len = Key.size();
	fwrite(&len, sizeof(size_t), 1, _File);
	fwrite(Key.c_str(), sizeof(wchar_t), Key.size(), _File);

	
	len = Path.size();
	fwrite(&len, sizeof(size_t), 1, _File);
	fwrite(Path.c_str(), sizeof(wchar_t), Path.size(), _File);
}

GAsset* LoadAssetRef(FILE* _File)
{
	// 불러오려는 Asset의 유무를 확인
	int Asset;
	fread(&Asset, sizeof(int), 1, _File);
	if (!Asset)
		return nullptr;

	// 불러오는 Asset의 종류를 읽어드린다.
	ASSET_TYPE type;
	fread(&type, sizeof(ASSET_TYPE), 1, _File);

	// 불러올 Asset 의 키, Path 를 알아낸다.
	wstring Key;
	wstring Path;
	wchar_t buffer[255];

	size_t len;
	fread(&len, sizeof(size_t), 1, _File);
	fread(buffer, sizeof(wchar_t), len, _File);
	Key = buffer;

	wmemset(buffer, 0, 255);

	//len;
	//buffer;
	fread(&len, sizeof(size_t), 1, _File);
	fread(buffer, sizeof(wchar_t), len, _File);
	Path = buffer;
	

	GAsset* pAsset = nullptr;
	switch (type)
	{
	case ASSET_TYPE::SPRITE:
		pAsset = (GAsset*)GAssetManager::GetInst()->LoadSprite(Key, Path);
		break;
	case ASSET_TYPE::TEXTURE:
		pAsset = (GAsset*)GAssetManager::GetInst()->LoadTexture(Key, Path);
		break;
	case ASSET_TYPE::FLIPBOOK:
		pAsset = (GAsset*)GAssetManager::GetInst()->LoadFlipBook(Key, Path);
		break;
	/*
	case ASSET_TYPE::SOUND:
		pAsset = new GSprite;
		break;
	*/
	}

	return pAsset;
}

void CheckExt(const wstring& _Ext, wstring& _strFilePath)
{
	wchar_t szExt[50] = {};

	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 50);
	// 확장자가 올바르지 않다면
	if (wcscmp(szExt, _Ext.c_str()))
	{
		// 확장자가 세팅되어있지 않았다면
		if (!wcscmp(szExt, L""))
		{
			_strFilePath += _Ext;
		}
		else
		{
			_strFilePath = _strFilePath.substr(0, _strFilePath.find(szExt));
			_strFilePath += _Ext;
		}
	}
}

// 파일의 이름을 출력한다.
wstring PathKey(const wstring& _strFilePath)
{
	wchar_t szExt[50] = {};

	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, szExt, 50, nullptr, 0);

	wstring Key = szExt;
	return Key;
}