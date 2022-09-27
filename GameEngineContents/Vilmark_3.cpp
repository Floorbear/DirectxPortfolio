#include "PreCompile.h"
#include "Vilmark_3.h"

#include "VilmarkMap.h"

#include "Ciel.h"
#include "HeartFox.h"
#include "TauCaptain.h"
#include "MiniTau.h"

Vilmark_3::Vilmark_3()
{
	StageNumber_ = 3;
}

Vilmark_3::~Vilmark_3()
{
}

void Vilmark_3::Start()
{
	VilmarkStart();
	VilmarkMap_->MakeLeftDoor();
	VilmarkMap_->MakeRightDoor();

	HeartFox* MonsterBoss = CreateMonster<HeartFox>(float4(1079, -352));
	////몬스터 생성
	float4 AccPos = {};
	Ciel* Monster = CreateMonster<Ciel>(AccPos + float4(573, -352));
	Ciel* Monster1 = CreateMonster<Ciel>(AccPos + float4(697, -365));
	Ciel* Monster2 = CreateMonster<Ciel>(AccPos + float4(782, -418));
	Ciel* Monster3 = CreateMonster<Ciel>(AccPos + float4(869, -351));
	Ciel* Monster4 = CreateMonster<Ciel>(AccPos + float4(918, -379));
	Ciel* Monster5 = CreateMonster<Ciel>(AccPos + float4(1014, -433));
}

void Vilmark_3::Update(float _DeltaTime)
{
	VilmarkUpdate(_DeltaTime);
}

void Vilmark_3::End()
{
}

void Vilmark_3::DNFOnEvent()
{
	VilmarkStartLevel();
}