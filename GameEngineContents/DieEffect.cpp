#include "PreCompile.h"
#include "DieEffect.h"

DieEffect::DieEffect() :
	DieFlash_(),
	DieFlashAlpha_(1.0f)
{
}

DieEffect::~DieEffect()
{
}

void DieEffect::Start()
{
	DieFlash_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	DieFlash_->SetTexture("DieFlash.png");
	DieFlash_->ScaleToTexture();
	DieFlash_->GetPixelData().MulColor = { 1,1,1,0.4f };
}

void DieEffect::Update(float _DeltaTime)
{
	DieFlashAlpha_ -= _DeltaTime;
	DieFlash_->GetPixelData().MulColor = { 1,1,1,DieFlashAlpha_ };
}

void DieEffect::End()
{
}