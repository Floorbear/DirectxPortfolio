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
	BattleIdle,
	BattleMove,
	Move,
	Buff,
	Fury,
	Down,
	NoneAttack,
	QuickStanding,
	AutoAttack,
	AutoAttack_0,
	AutoAttack_1,
	AutoAttack_2,
	TripleSlash,
	TripleSlash_0,
	TripleSlash_1,
	TripleSlash_2,
	Frenzy,
	Frenzy_AutoAttack_0,
	Frenzy_AutoAttack_1,
	Frenzy_AutoAttack_2,
	Frenzy_AutoAttack_3,
	Jump_Start,
	Jump_End,
	UpperSlash,
	Hit,
	GoreCross,
	GoreCross_0,
	GoreCross_1,
	HopSmash,
	HopSmash_0,
	HopSmash_1,
	HopSmash_2,
	Outragebreak,
	Outragebreak_0,
	Outragebreak_1,
	Outragebreak_2,
	Outragebreak_3,
	ExtremOverkill,
	ExtremOverkill_0,
	ExtremOverkill_1,
	ExtremOverkill_2
};