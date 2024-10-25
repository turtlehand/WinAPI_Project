#pragma once

class CObj;
class GAsset;

#pragma region Object

bool IsValid(CObj*& _Object);

void CreateGameObject(CObj* _NewObject, LAYER_TYPE _Layer = LAYER_TYPE::DEFAULT);

void DeleteGameObject(CObj* _DestroyObject);

#pragma endregion

void ChangeLevel(LEVEL_TYPE _Type);


#pragma region DrawDebug

void DrawDebugRect(PEN_TYPE _Color, time_t _Duration, Vec2 _Position, Vec2 _Scale);

void DrawDebugCircle(PEN_TYPE _Color, time_t _Duration, Vec2 _Position, float _Radius);

void DrawDebugEllipse(PEN_TYPE _Color, time_t _Duration, Vec2 _Position, Vec2 _Scale);

void DrawDebugLine(PEN_TYPE _Color, time_t _Duration, Vec2 _Position0, Vec2 _Position1);

#pragma endregion

#pragma region Vector

Vec2 Rotate(Vec2 _Dir, float _Angle);

float DotProduct(const Vec2& _Other1, const Vec2& _Other2);

int CCW(const Vec2& _Other1, const Vec2& _Other2);

#pragma endregion

#pragma region Asset

void SaveAssetRef(GAsset* _Asset, FILE* _File);
GAsset* LoadAssetRef(FILE* _File);
void CheckExt(const wstring& _Ext, wstring& _strFilePath);

#pragma endregion


