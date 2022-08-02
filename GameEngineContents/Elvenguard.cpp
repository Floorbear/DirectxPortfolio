#include "PreCompile.h"
#include "Elvenguard.h"

#include "Elvenguard_Background.h"
#include "Player_Main.h"

Elvenguard::Elvenguard()
{
}

Elvenguard::~Elvenguard()
{
}

void Elvenguard::Start()
{
	DNFStart();
	Elvenguard_Background* TileBackground = CreateActor< Elvenguard_Background>();

}

void Elvenguard::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Elvenguard::End()
{
}
