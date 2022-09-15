#pragma once

#include "DNFLevel.h"
enum MonsterType
{
	BloodLugaruM,
	CrazyIvanM
};

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

class MonsterHP;
class DNFGlobalValue
{
public:
	//���� ����
	static DNFLevel* CurrentLevel;

	static MonsterHP* CurrentMonsterHP;

	static float4 Temp1;
};
