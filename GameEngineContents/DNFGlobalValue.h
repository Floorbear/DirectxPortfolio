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


class DNFGlobalValue
{
public:
	//현재 레벨
	static DNFLevel* CurrentLevel;

};



