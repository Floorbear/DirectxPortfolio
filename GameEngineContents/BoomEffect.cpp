#include "PreCompile.h"
#include "BoomEffect.h"

#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"

BoomEffect::BoomEffect() :
	MainRenderer_(),
	YellowRenderer_(),
	RedTimer_(),
	YellowTimer_()
{
}

BoomEffect::~BoomEffect()
{
}

void BoomEffect::Start()
{
	//Boom 텍스처가 없으면 로드한다.
	if (GameEngineFolderTexture::Find("BoomRed") == nullptr)
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("SkillTexture");
			Dir.Move("Boom");
			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
	}

	//위치확인용 콜라이더
		//MiddleHit
	GameEngineCollision* HitAbove_ = CreateComponent<GameEngineCollision>("Middle");
	HitAbove_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
	HitAbove_->GetTransform().SetLocalScale({ 10,10 });
	HitAbove_->ChangeOrder(ColOrder::Debug);

	float Speed = 0.06f;
	//Red텍스처 로드
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->CreateFrameAnimationFolder("BoomRed", FrameAnimation_DESC("BoomRed", Speed, false));
	MainRenderer_->ChangeFrameAnimation("BoomRed");
	MainRenderer_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	MainRenderer_->SetScaleModeImage();
	MainRenderer_->GetTransform().SetLocalPosition({ 160,50,0 });//

	//Yellow텍스처 로드
	YellowRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	YellowRenderer_->CreateFrameAnimationFolder("BoomYellow", FrameAnimation_DESC("BoomYellow", Speed, false));
	YellowRenderer_->ChangeFrameAnimation("BoomYellow");
	YellowRenderer_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	YellowRenderer_->SetScaleModeImage();
	YellowRenderer_->GetTransform().SetLocalPosition({ 100,-40,0 });//DNFGlobalValue::Temp1

	//Yellow텍스처 로드

	Death(1.3f);
	//BleedingRenderer_->SetScaleRatio(Value_.BleedingScale.y);
	//BleedingRenderer_->Off();

	MainRenderer_->AnimationBindEnd("BoomRed", [&](const FrameAnimation_DESC _Desc)
		{
			RedTimer_.StartTimer(1.0f);
		});

	YellowRenderer_->AnimationBindEnd("BoomYellow", [&](const FrameAnimation_DESC _Desc)
		{
			YellowTimer_.StartTimer(1.0f);
		});
}

void BoomEffect::Update(float _DeltaTime)
{
	if (RedTimer_.IsTimerOn() == true)
	{
		RedTimer_.Update(_DeltaTime * 6.0f);
		MainRenderer_->GetPixelData().MulColor.a = *RedTimer_.GetIterTime();
	}

	if (YellowTimer_.IsTimerOn() == true)
	{
		YellowTimer_.Update(_DeltaTime * 6.0f);
		YellowRenderer_->GetPixelData().MulColor.a = *YellowTimer_.GetIterTime();
	}
}

void BoomEffect::End()
{
}