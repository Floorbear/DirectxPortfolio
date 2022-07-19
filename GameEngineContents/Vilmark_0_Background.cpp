#include "PreCompile.h"
#include "Vilmark_0_Background.h"

Vilmark_0_Background::Vilmark_0_Background()
{
}

Vilmark_0_Background::~Vilmark_0_Background()
{
}

void Vilmark_0_Background::Start()
{
	DNFStart();
	MainRenderer_->SetTexture("Vilmark_Background_00.png");
	MainRenderer_->ScaleToTexture();
}

void Vilmark_0_Background::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Vilmark_0_Background::End()
{
}
