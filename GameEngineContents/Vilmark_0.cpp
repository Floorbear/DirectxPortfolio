#include "PreCompile.h"
#include "Vilmark_0.h"

#include "Vilmark_0_Background.h"

Vilmark_0::Vilmark_0()
{
}

Vilmark_0::~Vilmark_0()
{
}

void Vilmark_0::Start()
{
	DNFStart();
	Vilmark_0_Background* TileBackground = CreateActor< Vilmark_0_Background>();
}

void Vilmark_0::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Vilmark_0::End()
{
}
