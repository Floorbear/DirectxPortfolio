#include "PreCompile.h"
#include "Vilmark_0.h"

#include "CrazyIvan.h"
#include "Bloodlugaru.h"
#include "Ciel.h"

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
	VilmarkMap_->MakeRightDoor();
	Ciel* Monster = CreateMonster<Ciel>({ { 700,-400 } });
	//Bloodlugaru* Monster = CreateMonster<Bloodlugaru>({ { 700,-400 } });
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