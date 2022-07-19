#include "PreCompile.h"
#include "Elvenguard_Front_Background.h"

Elvenguard_Front_Background::Elvenguard_Front_Background()
{
}

Elvenguard_Front_Background::~Elvenguard_Front_Background()
{
}

void Elvenguard_Front_Background::Start()
{
	DNFStart();
	MainRenderer_->SetTexture("ElvenGuardFront_Tile.png");
	MainRenderer_->ScaleToTexture();
}

void Elvenguard_Front_Background::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Elvenguard_Front_Background::End()
{
}
