#include "PreCompile.h"
#include "Vilmark_2.h"

#include "VilmarkMap.h"

#include "Ciel.h"

Vilmark_2::Vilmark_2()
{
	StageNumber_ = 2;
}

Vilmark_2::~Vilmark_2()
{
}

void Vilmark_2::Start()
{
	VilmarkStart();
	VilmarkMap_->MakeLeftDoor();
	VilmarkMap_->MakeRightDoor();

	////몬스터 생성
	//float4 AccPos = {};
	//Ciel* Monster = CreateMonster<Ciel>(AccPos + float4(579, -342));
	//Ciel* Monster1 = CreateMonster<Ciel>(AccPos + float4(697, -365));
	//Ciel* Monster2 = CreateMonster<Ciel>(AccPos + float4(782, -418));
	//Ciel* Monster3 = CreateMonster<Ciel>(AccPos + float4(869, -340));
	//Ciel* Monster4 = CreateMonster<Ciel>(AccPos + float4(918, -379));
	//Ciel* Monster5 = CreateMonster<Ciel>(AccPos + float4(1014, -433));
}

void Vilmark_2::Update(float _DeltaTime)
{
	VilmarkUpdate(_DeltaTime);
}

void Vilmark_2::End()
{
}

void Vilmark_2::DNFOnEvent()
{
	VilmarkStartLevel();
}