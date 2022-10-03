#include "PreCompile.h"
#include "Generator.h"

#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"
#include "DieEffect.h"

Generator::Generator()
{
}

Generator::~Generator()
{
}

void Generator::Start()
{
	//생성기 텍스처 로드
	if (GameEngineFolderTexture::Find("generator") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("generator");
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
	FloorRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	FloorRenderer_->SetFolderTextureToIndex("generator", 1);
	FloorRenderer_->ScaleToTexture();
	FloorRenderer_->GetTransform().SetLocalPosition({ -60,0,150 });

	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetFolderTextureToIndex("generator", 0);
	MainRenderer_->ScaleToTexture();
	MainRenderer_->GetTransform().SetLocalPosition({ 0,35,0 });

	ObjecCol_ = CreateComponent<GameEngineCollision>("Col");
	ObjecCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 1.0f, 0.5f));
	ObjecCol_->GetTransform().SetLocalScale({ 30,30 });
	ObjecCol_->GetTransform().SetLocalPosition(float4(0, 0, -500));
	ObjecCol_->ChangeOrder(ColOrder::Object);
}

void Generator::Update(float _DeltaTime)
{
	if (SpawnCount_ == -1) //아직 초기화 되있지 않으면 Return;
	{
		return;
	}
	if (SpawnTimer_.IsTimerOn() == false)
	{
		if (SpawnCount_ <= 0)
		{
			DieEffect* NewDieEffect = GetLevel()->CreateActor<DieEffect>();
			NewDieEffect->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			NewDieEffect->GetTransform().SetLocalScale({ 1.0f,1.0f,1.0f });
			NewDieEffect->Init("DieParticleGenerator");
			Death();
			return;
		}
		GameEngineSound::SoundPlayControl("summon_equipment.wav");
		SpawnFunction_();
		SpawnCount_--;
		SpawnTimer_.StartTimer();
	}
	else
	{
		SpawnTimer_.Update(_DeltaTime);
	}
}

void Generator::End()
{
}