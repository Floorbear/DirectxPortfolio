#include "PreCompile.h"
#include "Vilmark_0.h"

#include "CrazyIvan.h"
#include "Bloodlugaru.h"

Vilmark_0::Vilmark_0()
{
}

Vilmark_0::~Vilmark_0()
{
}

void Vilmark_0::Start()
{
	VilmarkStart();

	Bloodlugaru* Monster = CreateActor<Bloodlugaru>();
	Monster->ID_ = 1;
	Monster->GetTransform().SetWorldPosition({ 700,-400 });

	Bloodlugaru* Monster2 = CreateActor<Bloodlugaru>();
	Monster2->ID_ = 2;
	Monster2->GetTransform().SetWorldPosition({ 800,-430 });
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