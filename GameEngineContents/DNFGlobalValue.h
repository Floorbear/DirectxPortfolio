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
	//���� ����
	static DNFLevel* CurrentLevel;
};



