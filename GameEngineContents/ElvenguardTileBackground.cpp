#include "PreCompile.h"
#include "ElvenguardTileBackground.h"

ElvenguardTileBackground::ElvenguardTileBackground()
{
}

ElvenguardTileBackground::~ElvenguardTileBackground()
{
}

void ElvenguardTileBackground::Start()
{
	DNFStart();
	MainRenderer_->SetTexture("ElvenGuard_Tile.png");
	MainRenderer_->ScaleToTexture();
}

void ElvenguardTileBackground::Update(float _DeltaTime)
{
	DNFUpdate();
}

void ElvenguardTileBackground::End()
{
}
