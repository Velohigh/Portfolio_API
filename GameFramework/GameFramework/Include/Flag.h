#pragma once

enum class ETexture_Type
{
	Sprite,
	Frame
};

enum class ERender_Layer
{
	Back,
	LateBack,
	Tile,
	PreDefault,
	Default,
	Effect,
	UI,
	Max
};

enum class ECollision_Channel
{
	Default,
	Player,
	PlayerHitBox,
	PlayerBullet,
	Monster,
	MonsterHitBox,
	PlayerAttack,
	MonsterAttack,
	MonsterBullet,
	Mouse,
	Max
};

enum class ECollision_Interaction
{
	Ignore,
	Collision
};

enum class ECollider_Type
{
	Box,
	Circle
};

enum class EBrush_Type
{
	Red,
	Green,
	Black,
	Blue,
	Yellow,
	Max
};

enum class EEffect_Type
{
	Once,
	Duration,
	Loop
};

enum class EButton_State
{
	Normal,
	MouseHovered,
	Click,
	Disable,
	Max
};

enum class EButton_Sound_State
{
	MouseHovered,
	Click,
	Max
};

enum class ETile_Option
{
	Normal,
	ImpossibleToMove
};


