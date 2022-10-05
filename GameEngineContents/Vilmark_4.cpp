#include "PreCompile.h"
#include "Vilmark_4.h"

#include "CrazyIvan.h"
#include "Bloodlugaru.h"
#include "Ciel.h"
#include "CrazyIvanCaptain.h"
#include "Barricade.h"

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
	{
		float BariTime = 8.f;
		float BariXPos = 370.f;
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
		float BariTime = 8.f;
		float BariXPos = 470.f;
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
	float4 AccPos = { 150,0,0 };
	Bloodlugaru* Monster = CreateMonster<Bloodlugaru>(AccPos + float4(579, -352));
	Bloodlugaru* Monster1 = CreateMonster<Bloodlugaru>(AccPos + float4(697, -365));
	Bloodlugaru* Monster2 = CreateMonster<Bloodlugaru>(AccPos + float4(682, -418));
	Bloodlugaru* Monster3 = CreateMonster<Bloodlugaru>(AccPos + float4(669, -351));
	Bloodlugaru* Monster4 = CreateMonster<Bloodlugaru>(AccPos + float4(818, -379));
	Bloodlugaru* Monster7 = CreateMonster<Bloodlugaru>(AccPos + float4(828, -369));
	Bloodlugaru* Monster8 = CreateMonster<Bloodlugaru>(AccPos + float4(818, -375));

	Bloodlugaru* Monster5 = CreateMonster<Bloodlugaru>(AccPos + float4(714, -433));

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