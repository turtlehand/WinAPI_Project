#pragma once

// 수학적 벡터 구조체
struct Vec2
{
public:
	float x;
	float y;
public:
	Vec2() :
		x(0.f),
		y(0.f)
	{}

	Vec2(float _x, float _y) :
		x(_x), 
		y(_y) 
	{}

	Vec2(int _x, int _y) :
		x((float)_x),
		y((float)_y)
	{}

	Vec2(POINT _pt) :
		x(_pt.x),
		y(_pt.y)
	{}

	~Vec2() {}

public:

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vec2 Normalize()
	{
		return Vec2(x / Length(), y / Length());
	}

	Vec2 operator+(const Vec2& _Other) const
	{
		return Vec2(x + _Other.x, y + _Other.y);
	}
	Vec2 operator+(const float& _Other) const
	{
		return Vec2(x + _Other, y + _Other);
	}
	Vec2& operator+=(const Vec2& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		return *this;
	}
	Vec2& operator+=(const float& _Other)
	{
		x += _Other;
		y += _Other;
		return *this;
	}

	Vec2 operator-(const Vec2& _Other) const
	{
		return Vec2(x - _Other.x, y - _Other.y);
	}
	Vec2 operator-(const float& _Other) const
	{
		return Vec2(x - _Other, y - _Other);
	}
	Vec2& operator-=(const Vec2& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		return *this;
	}
	Vec2& operator-=(const float& _Other)
	{
		x -= _Other;
		y -= _Other;
		return *this;
	}

	Vec2 operator*(const float& _Other) const
	{
		return Vec2(x * _Other, y * _Other);
	}
	Vec2& operator*=(const float& _Other)
	{
		x*= _Other; y*= _Other;
		return *this;
	}

	Vec2 operator/(const float& _Other) const
	{
		assert(_Other);
		return Vec2(x / _Other, y / _Other);
	}
	Vec2& operator/=(const float& _Other)
	{
		assert(_Other);
		x /= _Other;
		y /= _Other;
		return *this;
	}
};

struct Task
{
	TASK_TYPE	Type;
	DWORD_PTR	Param0;
	DWORD_PTR	Param1;
};

struct DeBugRenderInfo
{
	DEBUG_SHAPE Type;
	Vec2 vParam0;
	Vec2 vParam1;
	PEN_TYPE Color;
	float Duration;		// 표시 시간
	float Time;			// 진행 시간
};

struct MonsterInfo
{
	float MaxHP;
	float HP;

	float AttackPower;
	float Speed;

	float DetectRange;
	float AttackRange;
};