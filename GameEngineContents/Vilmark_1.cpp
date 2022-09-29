#include "PreCompile.h"
#include "Vilmark_1.h"

#include "VilmarkMap.h"
#include "CrazyIvan.h"
#include "CrazyIvanCaptain.h"
#include "Generator.h"

Vilmark_1::Vilmark_1()
{
	StageNumber_ = 1;
}

Vilmark_1::~Vilmark_1()
{
}

void Vilmark_1::Start()
{
	VilmarkStart();
	VilmarkMap_->MakeLeftDoor();
	VilmarkMap_->MakeRightDoor();

	{
		Generator* NewGe = CreateActor<Generator>();
		NewGe->Init< CrazyIvan>(14, 2.5f);//3.5
		NewGe->GetTransform().SetWorldPosition({ 554,-439 ,-439 });
	}
	{
		Generator* NewGe = CreateActor<Generator>();
		NewGe->Init< CrazyIvan>(14, 2.5f);//3.5
		NewGe->GetTransform().SetWorldPosition({ 772,-502 ,-472 });
	}
	{
		Generator* NewGe = CreateActor<Generator>();
		NewGe->Init< CrazyIvan>(14, 2.5f);//3.5
		NewGe->GetTransform().SetWorldPosition({ 772,-406 ,-406 });
	}

	CrazyIvanCaptain* MonsterBoss = CreateMonster<CrazyIvanCaptain>({ 1040,-376 });
}

void Vilmark_1::Update(float _DeltaTime)
{
	VilmarkUpdate(_DeltaTime);
}

void Vilmark_1::End()
{
}

void Vilmark_1::DNFOnEvent()
{
	VilmarkStartLevel();
}