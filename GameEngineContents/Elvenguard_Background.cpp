#include "PreCompile.h"
#include "Elvenguard_Background.h"

Elvenguard_Background::Elvenguard_Background()
{
}

Elvenguard_Background::~Elvenguard_Background()
{
}

void Elvenguard_Background::Start()
{
	DNFStart();
	MainRenderer_->SetTexture("ElvenGuard_Tile.png");
	MainRenderer_->ScaleToTexture();
}

void Elvenguard_Background::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Elvenguard_Background::End()
{
}
