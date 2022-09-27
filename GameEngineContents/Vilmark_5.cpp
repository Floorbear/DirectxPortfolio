#include "PreCompile.h"
#include "Vilmark_5.h"

#include "VilmarkMap.h"

#include "HyperMecaCow.h"
#include "Runner.h"

Vilmark_5::Vilmark_5()
{
	StageNumber_ = 5;
}

Vilmark_5::~Vilmark_5()
{
}

void Vilmark_5::Start()
{
	VilmarkStart();
	VilmarkMap_->MakeLeftDoor();
	float4 AccPos = {};

	//Runner* Monster2 = CreateMonster<Runner>({ { 800,-430 } });
	//Runner* Monster3 = CreateMonster<Runner>({ { 750,-430 } });
	HyperMecaCow* Boss = CreateMonster< HyperMecaCow>({ { 700,-430 } });
}

void Vilmark_5::Update(float _DeltaTime)
{
	VilmarkUpdate(_DeltaTime);
}

void Vilmark_5::End()
{
}

void Vilmark_5::DNFOnEvent()
{
	VilmarkStartLevel();
}