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
	DieFlash_->SetTexture("DiebFlash22.png");
	DieFlash_->ScaleToTexture();
	DieFlash_->GetPixelData().MulColor = { 1,1,1,0.4f };

	Death(1.0f);
}

void DieEffect::Update(float _DeltaTime)
{
}

void DieEffect::End()
{
}