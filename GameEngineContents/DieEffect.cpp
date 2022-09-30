#include "PreCompile.h"
#include "DieEffect.h"

#include <GameEngineBase/GameEngineRandom.h>

DieEffect::DieEffect() :
	DieFlash_(),
	DieFlashAlpha_(0.23f),
	DieFlashTimer_(),
	DieParticleColor_(""),
	ScaleRatio_(1.0f)
{
	DieParticle_.reserve(10);
	Force_.reserve(10);
	RandomYSize_.reserve(10);
	RandomRot_.reserve(10);
	ParticleTime_ = 0.0f;
}

DieEffect::~DieEffect()
{
}

void DieEffect::Init(std::string _ParticleFolderName)
{
	DieParticleColor_ = _ParticleFolderName;

	//DieParticle 초기화
	for (size_t i = 0; i < 10; i++)
	{
		GameEngineTextureRenderer* NewParticle = CreateComponent<GameEngineTextureRenderer>();
		int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 3);
		NewParticle->SetFolderTextureToIndex(DieParticleColor_, RandomValue);
		NewParticle->ScaleToTexture();
		DieParticle_.push_back(NewParticle);
	}

	//DieParticle 랜덤 배치
	for (auto i : DieParticle_)
	{
		ScaleRatio_ = reinterpret_cast<GameEngineActor*>(i->GetParent())->GetTransform().GetLocalScale().x;
		float XPos = GameEngineRandom::MainRandom.RandomFloat(-Value.SpawnSizeParticleX * ScaleRatio_ / 2.f, Value.SpawnSizeParticleX * ScaleRatio_ / 2.f);
		float YPos = GameEngineRandom::MainRandom.RandomFloat(-Value.SpawnSizeParticleY * ScaleRatio_ / 2.f, Value.SpawnSizeParticleY * ScaleRatio_ / 2.f);

		i->GetTransform().SetLocalMove({ XPos,YPos,500 });
	}

	//DieParticle Force 초기화
	for (int i = 0; i < 10; i++)
	{
		//퍼지는 정도
		Force NewForce;
		NewForce.FrictionX_ = Value.Friction;
		float ForceX = Value.ForceX * (i - 5);
		if (ForceX >= 0)
		{
			ForceX = GameEngineRandom::MainRandom.RandomFloat(ForceX * 0.7f, ForceX * 1.3f);
		}
		else
		{
			ForceX = GameEngineRandom::MainRandom.RandomFloat(ForceX * 1.3f, ForceX * 0.7f);
		}
		NewForce.ForceX_ = ForceX;
		NewForce.ForceY_ = Value.ForceY;
		NewForce.Gravity_ = Value.Gravity;
		NewForce.OnGravity();
		NewForce.SetTransfrom(&DieParticle_[i]->GetTransform());
		Force_.push_back(NewForce);

		//회전하는 정도
		float RotValue = GameEngineRandom::MainRandom.RandomFloat(-90.0f, 90.0f);
		float Time = 0.0f;
		RandomRot_.push_back(RotValue);
	}

	//RandomValue 초기화
	for (int i = 0; i < 10; i++)
	{
		float RandomYPos = GameEngineRandom::MainRandom.RandomFloat(-Value.RandomYSize * ScaleRatio_, Value.RandomYSize * ScaleRatio_);
		RandomYSize_.push_back(RandomYPos);
	}
}

void DieEffect::Start()
{
	DieFlash_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	DieFlash_->SetTexture("DiebFlash22.png");
	DieFlash_->ScaleToTexture();
	DieFlash_->GetPixelData().MulColor = { 1,1,1,DieFlashAlpha_ };

	//Death(1.3f);
}

void DieEffect::Update(float _DeltaTime)
{
	if (DieParticleColor_ == "")
	{
		return;
	}
	UpdateParticle(_DeltaTime);
	DieFlashUpdate(_DeltaTime);
}

void DieEffect::UpdateParticle(float _DeltaTime)
{
	ParticleTime_ += _DeltaTime * DieTimeAcc_;
	for (int i = 0; i < 10; i++)
	{
		if (Force_[i].ForceY_ <= 0 && Force_[i].GetTransform()->GetLocalPosition().y <= RandomYSize_[i] - 20.0f)
		{
			continue;
		}
		Force_[i].Update(_DeltaTime);
		DieParticle_[i]->GetTransform().SetLocalRotate({ 0,0, RandomRot_[i] * _DeltaTime * 10.0f });
	}

	if (ParticleTime_ >= 2.5f)
	{
		float AlphaValue = 1.f - (ParticleTime_ - 2.5f);
		if (AlphaValue <= 0)
		{
			Death();
		}
		for (int i = 0; i < 10; i++)
		{
			DieParticle_[i]->GetPixelData().MulColor.a = AlphaValue;
		}
	}
}

void DieEffect::DieFlashUpdate(float _DeltaTime)
{
	DieFlashAlpha_ -= _DeltaTime * 2.0f;
	if (DieFlashAlpha_ <= 0.0f)
	{
		DieFlashAlpha_ = 0.0f;
	}
	DieFlash_->GetPixelData().MulColor = { 1,1,1,DieFlashAlpha_ };
}

void DieEffect::End()
{
}

void DieEffect::Option(bool _SpawnDieFlash, float _DieTimeAcc)
{
	if (_SpawnDieFlash == false)
	{
		DieFlash_->Off();
	}

	DieTimeAcc_ = _DieTimeAcc;
}