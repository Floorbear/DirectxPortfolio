#pragma once

#include "DNFLevel.h"

enum class ColOrder
{
	None,
	Player,
	Monster,
	MonsterHitMiddle,
	PlayerAttackMiddle,
	Debug
};

class DNFGlobalValue
{
public:
	//���� ����
	static DNFLevel* CurrentLevel;
};



