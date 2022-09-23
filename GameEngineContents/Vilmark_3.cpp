#include "PreCompile.h"
#include "Vilmark_3.h"

#include "VilmarkMap.h"

#include "TauCaptain.h"

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

	TauCaptain* MonsterTau = CreateMonster<TauCaptain>(float4(579, -342));
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