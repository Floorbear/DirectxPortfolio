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
	//���� ����
	static DNFLevel* CurrentLevel;

};



