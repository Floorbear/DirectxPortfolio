#include "PreCompile.h"
#include "Barricade.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"
#include "DieEffect.h"
#include "BoomEffect.h"

Barricade::Barricade()
{
}

Barricade::~Barricade()
{
}

void Barricade::Start()
{
	//바리케이드 텍스처 로드
	if (GameEngineFolderTexture::Find("Barricade") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("Barricade");
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->CreateFrameAnimationFolder("Barricade", FrameAnimation_DESC("Barricade", 0, 0, 0.2f, false));
	MainRenderer_->CreateFrameAnimationFolder("Fire", FrameAnimation_DESC("Barricade", 1, 6, 0.2f, false));
	MainRenderer_->ChangeFrameAnimation("Barricade");
	MainRenderer_->SetScaleModeImage();

	MainRenderer_->AnimationBindEnd("Fire", [&](const FrameAnimation_DESC _Desc)
		{
			BoomEffect* NewBoom = GetLevel()->CreateActor<BoomEffect>();
			NewBoom->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			NewBoom->GetTransform().SetLocalScale({ 0.8f,0.8f,0.8f });
			DieEffect* NewDieEffect = GetLevel()->CreateActor<DieEffect>();
			NewDieEffect->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			NewDieEffect->GetTransform().SetLocalScale({ 1.0f,1.0f,1.0f });
			NewDieEffect->Init("bunker_particle");
			//Sound
			GameEngineSound::SoundPlayControl("bomb_01.wav");

			Death();
		});
	//FloorRenderer_->GetTransform().SetLocalPosition({ -60,0,150 });

	ObjecCol_ = CreateComponent<GameEngineCollision>("Col");
	ObjecCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 1.0f, 0.5f));
	ObjecCol_->GetTransform().SetLocalScale({ 117,92 });
	ObjecCol_->GetTransform().SetLocalPosition(float4(0, 0, -500));
	ObjecCol_->ChangeOrder(ColOrder::Object);
}

void Barricade::Update(float _DeltaTime)
{
	if (IsInit_ == false)
	{
		return;
	}

	if (DestroyTimer_.IsTimerOn() == true)
	{
		DestroyTimer_.Update(_DeltaTime);
		if (DestroyTimer_.IsTimerOn() == false)
		{
			MainRenderer_->ChangeFrameAnimation("Fire");
		}
	}
}

void Barricade::End()
{
}