#include "PreCompile.h"
#include "Bar_Background.h"

Bar_Background::Bar_Background()
{
}

Bar_Background::~Bar_Background()
{
}

void Bar_Background::Start()
{
	DNFStart();
	MainRenderer_->SetTexture("Bar_Background.png");
	MainRenderer_->ScaleToTexture();
}

void Bar_Background::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Bar_Background::End()
{
}
