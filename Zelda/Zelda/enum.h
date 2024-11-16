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
	// Param0 : Object Address, Param1 : bool
	ACTIVE_OBJECT,
	
	// Param0 : Object Address, Param1 : Layer Index
	CREATE_OBJECT,

	// Param0 : Parent Object, Param1 : Child Object Address, Param2 : Layer Index
	CREATE_CHILDE_OBJECT,

	// Param0 : Object Address
	DELETE_OBJECT,

	// Param0 : Next Level
	CHANGE_LEVEL,
};

enum class LAYER_TYPE
{
	BACKGROUND,
	DEFAULT,
	ITEM,
	OBJECT,
	MONSTER_OBJECT,
	PLAYER_OBJECT,

	MONSTER,
	PLAYER,
	ELEMENT,

	UI = 31,
	END = 32
};

enum class COLLIDER_TYPE
{
	BOX,
	CIRCLE,
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
	TILE,
	TILEPALETTE,
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

enum class ATTACK_TYPE
{
	SLASH,
	STRIKE,
	THRUSHT,
	NONE,
};

enum class MATERIAL_TYPE
{
	WOOD,
	METAL,
	STONE,
	LIFE,
	FIRE,
	ICE,
	LIGHTNING,
	WATER,
	NONE,
};

enum class ELEMENT_TYPE
{
	FIRE,
	ICE,
	LIGHTNING,
	WATER,
	NONE
};
