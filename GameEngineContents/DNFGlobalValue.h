#pragma once

#include "DNFLevel.h"
enum MonsterType
{
	BloodLugaruM,
	CrazyIvanM,
	CrazyIvanCapM,
	CielM,
	HeartFoxM,
	TauCaptainM,
	MiniTauM,
	MecaTauM,
	RunnerM
};

enum class ColOrder
{
	None,
	PlayerHit,
	MonsterAttack,
	MonsterHit,
	MonsterRange,
	PlayerAttack,
	DoorRight,
	DoorLeft,
	Object,
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
	//현재 레벨
	static DNFLevel* CurrentLevel;

	static MonsterHP* CurrentMonsterHP;

	static Player_Main* CurrentPlayer_;

	static DNFHUD* CurrentHUD_;

	static float4 Temp1;

	static GameEngineSoundPlayer Bgm_;
};
