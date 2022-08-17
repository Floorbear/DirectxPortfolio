#pragma once

enum class AvatarParts
{
	Shadow,
	Skin,
	Hair,
	Cap,
	Face,
	Neck,
	Coat,
	Pants,
	Belt,
	Shoes,
	Weapon
};

enum class AvatarType
{
	None,
	Default,
	Job,
	Dog,
	Danjin
};

enum class AvatarLayer
{
	A,
	B,
	C,
	D
};

enum class PlayerAnimations
{
	ChangeAvatar,
	Idle,
	Move,
	Buff,
	AutoAttack_0,
};