#include "PreCompile.h"
#include "Elvenguard.h"

#include "ElvenguardTileBackground.h"

Elvenguard::Elvenguard()
{
}

Elvenguard::~Elvenguard()
{
}

void Elvenguard::Start()
{
	DNFStart();
	ElvenguardTileBackground* TileBackground = CreateActor< ElvenguardTileBackground>();

}

void Elvenguard::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Elvenguard::End()
{
}
