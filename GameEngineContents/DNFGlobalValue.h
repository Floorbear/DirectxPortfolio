#pragma once

#include "DNFLevel.h"

enum class ColOrder
{
	None,
	Player,
	Monster,
	MonsterHit,
	PlayerAttack,
	Debug
};


class DNFGlobalValue
{
public:
	//현재 레벨
	static DNFLevel* CurrentLevel;
};



