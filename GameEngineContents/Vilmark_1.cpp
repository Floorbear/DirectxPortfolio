#include "PreCompile.h"
#include "Vilmark_1.h"

#include "VilmarkMap.h"
#include "CrazyIvan.h"
#include "CrazyIvanCaptain.h"
#include "Generator.h"
#include "Barricade.h"

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
		NewGe->Init< CrazyIvan>(9, 2.5f);//3.5
		NewGe->GetTransform().SetWorldPosition({ 404,-439 ,-439 });
	}
	{
		Generator* NewGe = CreateActor<Generator>();
		NewGe->Init< CrazyIvan>(9, 2.5f);//3.5
		NewGe->GetTransform().SetWorldPosition({ 622,-502 ,-472 });
	}
	{
		Generator* NewGe = CreateActor<Generator>();
		NewGe->Init< CrazyIvan>(9, 2.5f);//3.5
		NewGe->GetTransform().SetWorldPosition({ 622,-406 ,-406 });
	}

	{
		float BariTime = 26.f;
		float BariXPos = 700.f;
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-370 ,-370 });
		}
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-420 ,-420 });
		}
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-470 ,-470 });
		}
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-520 ,-520 });
		}
	}
	{
		float BariTime = 26.f;
		float BariXPos = 800.f;
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-370 ,-370 });
		}
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-420 ,-420 });
		}
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-470 ,-470 });
		}
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-520 ,-520 });
		}
	}
	{
		float BariTime = 26.f;
		float BariXPos = 900.f;
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-370 ,-370 });
		}
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-420 ,-420 });
		}
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-470 ,-470 });
		}
		{
			Barricade* NewBari = CreateActor<Barricade>();
			NewBari->Init(BariTime);
			NewBari->GetTransform().SetWorldPosition({ BariXPos,-520 ,-520 });
		}
	}

	CrazyIvanCaptain* MonsterBoss = CreateMonster<CrazyIvanCaptain>({ 1200,-376 });
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