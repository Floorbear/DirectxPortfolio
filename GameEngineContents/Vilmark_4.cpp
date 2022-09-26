#include "PreCompile.h"
#include "Vilmark_4.h"

#include "CrazyIvan.h"
#include "Bloodlugaru.h"
#include "Ciel.h"
#include "CrazyIvanCaptain.h"

#include "VilmarkMap.h"

Vilmark_4::Vilmark_4()
{
	StageNumber_ = 4;
}

Vilmark_4::~Vilmark_4()
{
}

void Vilmark_4::Start()
{
	VilmarkStart();
	VilmarkMap_->MakeLeftDoor();
	VilmarkMap_->MakeRightDoor();
	float4 AccPos = {};
	Bloodlugaru* Monster = CreateMonster<Bloodlugaru>(AccPos + float4(579, -342));
	Bloodlugaru* Monster1 = CreateMonster<Bloodlugaru>(AccPos + float4(697, -365));
	Bloodlugaru* Monster2 = CreateMonster<Bloodlugaru>(AccPos + float4(782, -418));
	Bloodlugaru* Monster3 = CreateMonster<Bloodlugaru>(AccPos + float4(869, -340));
	Bloodlugaru* Monster4 = CreateMonster<Bloodlugaru>(AccPos + float4(918, -379));
	Bloodlugaru* Monster5 = CreateMonster<Bloodlugaru>(AccPos + float4(1014, -433));

	//Bloodlugaru* Monster2 = CreateMonster<Bloodlugaru>({ { 800,-430 } });
	//Bloodlugaru* Monster3 = CreateMonster<Bloodlugaru>({ { 750,-430 } });
}

void Vilmark_4::Update(float _DeltaTime)
{
	VilmarkUpdate(_DeltaTime);
}

void Vilmark_4::End()
{
}

void Vilmark_4::DNFOnEvent()
{
	VilmarkStartLevel();
}