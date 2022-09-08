#pragma once

#include "DNFLevel.h"

enum class ColOrder
{
	None,
	PlayerHit,
	MonsterAttack,
	MonsterHit,
	MonsterRange,
	PlayerAttack,
	Debug
};

enum class Effect
{
	None,
	SlashSRight,
	SlashSLeft,
	SlashSHori
};


class DNFGlobalValue
{
public:
	//현재 레벨
	static DNFLevel* CurrentLevel;

	static float4 Temp1;
};



