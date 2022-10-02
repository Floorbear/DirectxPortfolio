#include "PreCompile.h"
#include "OverkillParticle.h"

#include <GameEngineBase/GameEngineRandom.h>
#include "DNFContentsMinimal.h"

OverkillParticle::OverkillParticle()
{
}

OverkillParticle::~OverkillParticle()
{
}

void OverkillParticle::Start()
{
	int Random = GameEngineRandom::MainRandom.RandomInt(0, 5);

	//�븻 �ؽ�ó �ʱ�ȭ
	{
		Normal_ = CreateComponent < GameEngineTextureRenderer >();
		Normal_->SetFolderTextureToIndex("particle-n", Random);
		Normal_->ScaleToTexture();
	}

	//����
	{
		Dodge_ = CreateComponent < GameEngineTextureRenderer >();
		Dodge_->SetFolderTextureToIndex("particle-d", Random);
		Dodge_->ScaleToTexture();
		Dodge_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	}
	Death(1.5f);
}

void OverkillParticle::Update(float _DeltaTime)
{
	GetTransform().SetLocalMove(float4::UP * 1800.f * _DeltaTime);
}

void OverkillParticle::End()
{
}