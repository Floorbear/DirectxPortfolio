#include "PreCompile.h"
#include "SeriaBackground.h"

SeriaBackground::SeriaBackground()
{
}

SeriaBackground::~SeriaBackground()
{
}

void SeriaBackground::Start()
{
	DNFStart();

	MainRenderer_->SetTexture("SeriaBackground.png");
	MainRenderer_->ScaleToTexture();
	MainRenderer_->GetTransform().SetLocalPosition({ 0,0,0 });
}

void SeriaBackground::Update(float _DeltaTime)
{
	DNFUpdate();
}

