#pragma once


enum class  PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	WHITE,
	GRAY,
	BLACK,

	END
};

enum class BRUSH_TYPE
{
	RED,
	GREEN,
	BLUE,

	HOLLOW,

	WHITE,
	GRAY,
	BLACK,

	END
};

enum class TASK_TYPE
{
	// Param0 : Object Address, Param1 : Layer Index
	CREATE_OBJECT,

	// Param0 : Object Address
	DELETE_OBJECT,

	// Param0 : Next Level
	CHANGE_LEVEL,
};

enum class LAYER_TYPE
{
	BACKGROUND,
	TILE,
	DEFAULT,
	PLAYER,
	PLAYER_OBJECT,
	MONSTER,
	MONSTER_OBJECT,

	UI = 31,
	END = 32
};

enum class COLLIDER_TYPE
{
	RECTANGLE,
	CIRCLE,
	EDGE,
	TILE,
};

enum class COMPONENT_TYPE
{
	COLLIDER,
	RIGIDBODY,
	FILPBOOKPLAYER,
	TILEMAP,
	FSM,
	SPRITERENDERER,
};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,
};

enum class ASSET_TYPE
{
	TEXTURE,	// 이미지
	SOUND,		// 소리	
	SPRITE,		// 특정 텍스쳐의 특정 부위
	FLIPBOOK,	// Sprite 의 집합체
};

enum class RIGIDBODY_TYPE
{
	DYNAMIC,
	STATIC,
	KINETIC
};

enum class LEVEL_TYPE
{
	EDITOR,
	START,
	STAGE0,
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	LAST,
	END,

};