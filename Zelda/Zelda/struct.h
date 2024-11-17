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
		if (Length() == 0.f)
			return Vec2::zero();
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

	bool operator==(const Vec2& _Other)
	{
		if (this->x == _Other.x && this->y == _Other.y)
			return true;
		return false;
	}

	bool operator!=(const Vec2& _Other)
	{
		if (this->x == _Other.x && this->y == _Other.y)
			return false;
		return true;
	}

	Vec2 static right()
	{
		return Vec2(1, 0);
	}

	Vec2 static left()
	{
		return Vec2(-1, 0);
	}

	Vec2 static up()
	{
		return Vec2(0, 1);
	}

	Vec2 static down()
	{
		return Vec2(0, -1);
	}

	Vec2 static zero()
	{
		return Vec2(0, 0);
	}
};

struct Task
{
	float		Time;
	TASK_TYPE	Type;
	DWORD_PTR	Param0;
	DWORD_PTR	Param1;
	DWORD_PTR	Param2;
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

// 렌더 시 sprite를 조작할 정보
struct RenderInfo
{
	Vec2				Offset = Vec2::zero();
	Vec2				Scale = Vec2(1.f,1.f);
	int					Alpha = 255;
	COLORREF			DeleteColor = RGB(-1,-1,-1);

	bool				XFlip = false;
	bool				YFlip = false;
};


struct ElementalEffect
{
	ELEMENT_TYPE ElementType = ELEMENT_TYPE::NONE;
	float Duration = 0.f;
	float Time = 0.f;
};

struct DefaultStatsInfo
{
	MATERIAL_TYPE Material = MATERIAL_TYPE::NONE;
	ElementalEffect Effect;

	int MaxHP = 0;
	int HP = 0;

	float AttackPower = 0.f;
	float Speed = 0.f;

	bool IsDead = false;
};

struct WeaponInfo : public DefaultStatsInfo
{
	ATTACK_TYPE AttackType;
};

struct MonsterInfo : public DefaultStatsInfo
{
	float DetectRange;
	float DetectKeepRange;
	float AttackRange;
	Vec2 Direction;
};

struct PlayerInfo : public DefaultStatsInfo
{
	Vec2 Direction;		// 현재 바라보고 있는 방향
};

