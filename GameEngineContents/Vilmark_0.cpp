#include "PreCompile.h"
#include "Vilmark_0.h"

#include "CrazyIvan.h"
#include "Bloodlugaru.h"
#include "Ciel.h"
#include "CrazyIvanCaptain.h"

#include "VilmarkMap.h"

Vilmark_0::Vilmark_0()
{
	StageNumber_ = 0;
}

Vilmark_0::~Vilmark_0()
{
}

void Vilmark_0::Start()
{
	VilmarkStart();
	VilmarkMap_->FadeTimeAcc_ = 0.25f;
	VilmarkMap_->MakeRightDoor();
	VilmarkMap_->MakeLogo();
	//CrazyIvanCaptain* Monster = CreateMonster<CrazyIvanCaptain>({ { 700,-400 } });
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

void Vilmark_0::Update(float _DeltaTime)
{
	VilmarkUpdate(_DeltaTime);
}

void Vilmark_0::End()
{
}

void Vilmark_0::DNFOnEvent()
{
	VilmarkStartLevel();
}