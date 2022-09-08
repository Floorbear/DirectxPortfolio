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
	//���� ����
	static DNFLevel* CurrentLevel;

	static float4 Temp1;
};



