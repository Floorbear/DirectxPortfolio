#include "PreCompile.h"
#include "EffectActor.h"
#include <GameEngineBase/GameEngineRandom.h>
EffectActor::EffectActor():
	EffectRenderer_()
{
}

EffectActor::~EffectActor()
{
}

void EffectActor::InitEffect(Effect _Effect)
{
	std::string TextureName;
	int EndFrame = 2;

	//색 변경 관련
	float RandomColor = GameEngineRandom::MainRandom.RandomFloat(2.0f, 3.0f);
	float4 MulValue = { 3,RandomColor,1,0.8f };

	switch (_Effect)
	{
	case Effect::SlashSRight:
		TextureName = "SlashS1";
		break;
	case Effect::SlashSLeft:
		TextureName = "SlashS2";
		break;
	case Effect::SlashSHori:
		TextureName = "SlashS3";
		break;
	default:
		break;
	}

	//색 변경값이 존재하면 곱해준다.
	if (MulValue.Length() >= 0)
	{
		EffectRenderer_->GetPixelData().MulColor = MulValue;
	}

	//애니메이션 생성
	EffectRenderer_->CreateFrameAnimationFolder(TextureName, FrameAnimation_DESC(TextureName, 0, EndFrame,0.05f, false));
	EffectRenderer_->SetScaleModeImage();
	//EffectRenderer_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	EffectRenderer_->ChangeFrameAnimation(TextureName);
	EffectRenderer_->AnimationBindEnd(TextureName, [&](const FrameAnimation_DESC _Desc)
		{
			Death(0.05f);
		});

	EffectRenderer_->On();
}

void EffectActor::Start()
{
	EffectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	EffectRenderer_->Off();
}

void EffectActor::Update(float _DeltaTime)
{
	int a = 0;
}

void EffectActor::End()
{
}
