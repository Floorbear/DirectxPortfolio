#include "PreCompile.h"
#include "ExtremOverkill.h"

#include <GameEngineBase/GameEngineRandom.h>
#include "DNFContentsMinimal.h"
#include "OverkillParticle.h"

#include "DieEffect.h"
#include "BoomEffect.h"
#include "Player_Main.h"
ExtremOverkill::ExtremOverkill()
{
}

ExtremOverkill::~ExtremOverkill()
{
}

void ExtremOverkill::Start()
{
	//�Ϳ�ų �ؽ�ó�� ������ �ε��Ѵ�.
	if (GameEngineFolderTexture::Find("kaaa-d2") == nullptr)
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("SkillTexture");
			Dir.Move("ExtremOverkill");
			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
	}

	//�ٴ� �ؽ�ó �ε�
	{
		Floor_1_ = CreateComponent<GameEngineTextureRenderer>();
		Floor_1_->CreateFrameAnimationFolder("Floor_1", FrameAnimation_DESC("split-n1", 0, 3, 0.1f, false));
		Floor_1_->CreateFrameAnimationFolder("Floor_1_1", FrameAnimation_DESC("split-n1", 4, 4, 0.1f, false));

		Floor_1_->ChangeFrameAnimation("Floor_1");
		Floor_1_->SetScaleModeImage();
		Floor_1_->SetScaleRatio(ScaleRatio_);
		AllRenderer_.push_back(Floor_1_);
	}

	// �ٴ� 2 �ؽ�ó �ε�
	{
		Floor_2_ = CreateComponent<GameEngineTextureRenderer>();
		Floor_2_->CreateFrameAnimationFolder("Floor_2", FrameAnimation_DESC("split-n2", 0, 7, 0.1f, false));
		Floor_2_->ChangeFrameAnimation("Floor_2");
		Floor_2_->SetScaleModeImage();
		Floor_2_->SetScaleRatio(ScaleRatio_);
		Floor_2_->Off();
		Floor_2_->AnimationBindEnd("Floor_2", [&](const FrameAnimation_DESC _Desc)
			{
				Floor_2_->Off();
				Blood_0_->On();
				Player_Main* Player = DNFGlobalValue::CurrentPlayer_;
				Player->ShakeCamera(15.f, 0.3f);
			});
		AllRenderer_.push_back(Floor_2_);
	}

	//���� ���� ������
	{
		Blood_0_ = CreateComponent<GameEngineTextureRenderer>();
		Blood_0_->CreateFrameAnimationFolder("Blood_0", FrameAnimation_DESC("kaaa-d1", 0, 0, 0.1f, false));
		Blood_0_->ChangeFrameAnimation("Blood_0");
		Blood_0_->SetScaleModeImage();
		Blood_0_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
		Blood_0_->GetTransform().SetLocalPosition({ 0,210,0 });
		Blood_0_->SetScaleRatio(ScaleRatio_ * 1.8f);
		Blood_0_->Off();
		Blood_0_->AnimationBindEnd("Blood_0", [&](const FrameAnimation_DESC _Desc)
			{
				if (Blood_0_Alpha_.IsTimerOn() == false)
				{
					Blood_0_Alpha_.StartTimer();
				}
			});
		AllRenderer_.push_back(Blood_0_);
	}

	float ScaleRatio = 2.0f;
	//���� �Ѿƾ� ����
	{
		Blood_1_ = CreateComponent<GameEngineTextureRenderer>();
		Blood_1_->CreateFrameAnimationFolder("Blood_1_", FrameAnimation_DESC("kaaa-d2", 0, 2, 0.05f, true));
		Blood_1_->ChangeFrameAnimation("Blood_1_");
		Blood_1_->SetPivot(PIVOTMODE::RIGHTBOT);
		Blood_1_->GetTransform().SetLocalPosition({ 0,-180,0 });
		Blood_1_->GetTransform().SetLocalScale({ 158 * ScaleRatio,422 * ScaleRatio });
		Blood_1_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
		Blood_1_->Off();

		AllRenderer_.push_back(Blood_1_);
	}

	//���� �Ѿƾ� ������
	{
		Blood_2_ = CreateComponent<GameEngineTextureRenderer>();
		Blood_2_->CreateFrameAnimationFolder("Blood_2_", FrameAnimation_DESC("kaaa-d2", 0, 2, 0.05f, true));
		Blood_2_->ChangeFrameAnimation("Blood_2_");
		Blood_2_->SetPivot(PIVOTMODE::RIGHTBOT);
		Blood_2_->GetTransform().SetLocalPosition({ 0,-180,0 });
		Blood_2_->GetTransform().SetLocalScale({ -158 * ScaleRatio,422 * ScaleRatio });
		Blood_2_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
		Blood_2_->Off();

		AllRenderer_.push_back(Blood_2_);
	}

	//����
	{
		Smoke_ = CreateComponent<GameEngineTextureRenderer>();
		Smoke_->CreateFrameAnimationFolder("Smoke", FrameAnimation_DESC("kaaa-n", 2, 3, 0.12f, true));
		Smoke_->ChangeFrameAnimation("Smoke");
		Smoke_->GetTransform().SetLocalPosition({ 0,180,0 });
		Smoke_->GetTransform().SetLocalScale({ -180 * 3.f,212 * 3.f });
		Smoke_->Off();

		AllRenderer_.push_back(Smoke_);
	}

	//������� �ٷγ����� ����Ʈ �ε�
	{
		Impact_ = CreateComponent<GameEngineTextureRenderer>();
		Impact_->CreateFrameAnimationFolder("Impact", FrameAnimation_DESC("impact-d", 0, 3, 0.1f, false));
		Impact_->ChangeFrameAnimation("Impact");
		Impact_->SetScaleModeImage();
		Impact_->SetScaleRatio(ScaleRatio_);
		Impact_->AnimationBindEnd("Impact", [&](const FrameAnimation_DESC _Desc)
			{
				Impact_->Off();
				Floor_2_->On();
			});
		AllRenderer_.push_back(Impact_);
	}

	Death(6.0f);
}

void ExtremOverkill::Update(float _DeltaTime)
{
	Player_Main* Player = DNFGlobalValue::CurrentPlayer_;
	switch (Phase_)
	{
	case 0:
	{
		if (Blood_0_Alpha_.IsTimerOn() == true)
		{
			Blood_0_Alpha_.Update(_DeltaTime * 12);
			Blood_0_->GetPixelData().MulColor.a = Blood_0_Alpha_.GetCurTime();
			if (Blood_0_Alpha_.IsTimerOn() == false)
			{
				ShakeIter.StartTimer();
				Floor_1_->ChangeFrameAnimation("Floor_1_1");
				Blood_0_->Off();
				Blood_1_->On();
				Blood_2_->On();
				Smoke_->On();
				Phase_1_Timer.StartTimer();
				Particle_SpawnIter_.StartTimer();
				Phase_ = 1;
			}
		}
	}
	break;
	case 1:
	{
		if (Phase_1_Timer.IsTimerOn() == true)
		{
			Phase_1_Timer.Update(_DeltaTime);
			if (Phase_1_Timer.IsTimerOn() == false)
			{
				Blood_1_Alpha_.StartTimer();
				Floor_1_->Off();
				Smoke_->Off();
				Phase_ = 2;
			}

			if (ShakeIter.IsTimerOn() == true)
			{
				ShakeIter.Update(_DeltaTime);
				if (ShakeIter.IsTimerOn() == false)
				{
					Player->ShakeCamera(7.f, 0.15f);
					ShakeIter.StartTimer();
				}
			}
		}
		UpdateParticle(_DeltaTime);
	}
	break;
	case 2:
	{
		//���� ����Ʈ ���
		if (Blood_1_Alpha_.IsTimerOn() == true)
		{
			Blood_1_Alpha_.Update(_DeltaTime * 4.f);
			Blood_1_->GetPixelData().MulColor = { Blood_1_Alpha_.GetCurTime() ,Blood_1_Alpha_.GetCurTime(),Blood_1_Alpha_.GetCurTime() };
			Blood_2_->GetPixelData().MulColor = { Blood_1_Alpha_.GetCurTime() ,Blood_1_Alpha_.GetCurTime(),Blood_1_Alpha_.GetCurTime() };

			//���߿� ������ƼŬ�̶� ���� ��ƼŬ�� ����
			if (IsBoomSpawn_0_ == false && Blood_1_Alpha_.GetCurTime() < 0.8f)
			{
				Player->ShakeCamera(15.f, 0.3f);
				IsBoomSpawn_0_ = true;
				float4 Acc = { 90,40 };
				{
					BoomEffect* NewParticle = GetLevel()->CreateActor<BoomEffect>();
					float4 SpawnPos = GetTransform().GetWorldPosition() + Acc;
					NewParticle->GetTransform().SetWorldPosition(SpawnPos);
					NewParticle->GetTransform().SetLocalScale({ 1.4f,1.4f,1.4f });
				}
			}

			if (IsBoomSpawn_1_ == false && Blood_1_Alpha_.GetCurTime() < 0.77f)
			{
				IsBoomSpawn_1_ = true;
				float4 Acc = { 90,40 };
				{
					BoomEffect* NewParticle = GetLevel()->CreateActor<BoomEffect>();
					Acc.x = -Acc.x;
					float4 SpawnPos = GetTransform().GetWorldPosition() + Acc;
					NewParticle->GetTransform().SetWorldPosition(SpawnPos);
					NewParticle->GetTransform().SetLocalScale({ 1.4f,1.4f,1.4f });
				}
			}

			if (IsBoomSpawn_2_ == false && Blood_1_Alpha_.GetCurTime() < 0.75f)
			{
				IsBoomSpawn_2_ = true;
				float4 Acc = { 90,40 };
				{
					BoomEffect* NewParticle = GetLevel()->CreateActor<BoomEffect>();
					float4 SpawnPos = GetTransform().GetWorldPosition();
					NewParticle->GetTransform().SetWorldPosition(SpawnPos);
					NewParticle->GetTransform().SetLocalScale({ 1.4f,1.4f,1.4f });
				}
			}

			if (IsParticleSpawn_ == false && Blood_1_Alpha_.GetCurTime() < 0.25f)
			{
				IsParticleSpawn_ = true;
				float4 Acc = { 0,190 };
				{
					DieEffect* NewParticle = GetLevel()->CreateActor<DieEffect>();
					float4 SpawnPos = GetTransform().GetWorldPosition() + Acc;
					NewParticle->GetTransform().SetWorldPosition(SpawnPos);
					NewParticle->GetTransform().SetLocalScale({ 1.0f,1.0f,1.0f });
					NewParticle->Init("exi-particle");
					NewParticle->Option(false, 3.0f, -200.f);
				}
			}

			if (Blood_1_Alpha_.IsTimerOn() == false)
			{
				Blood_1_->Off();
				Blood_2_->Off();
			}
		}
	}
	break;
	default:
		break;
	}
}

void ExtremOverkill::End()
{
}

void ExtremOverkill::UpdateParticle(float _DeltaTime)
{
	//����������� �Ѿ�� n�������� ������ �ƿ� �����.
	if (Phase_1_Timer.GetCurTime() < 0.04f)
	{
		return;
	}
	if (Particle_SpawnIter_.IsTimerOn() == true)
	{
		Particle_SpawnIter_.Update(_DeltaTime);
		if (Particle_SpawnIter_.IsTimerOn() == false)
		{
			OverkillParticle* NewParticle = GetLevel()->CreateActor<OverkillParticle>();
			float4 SpawnPos = GetTransform().GetWorldPosition();
			float RandomPos = GameEngineRandom::MainRandom.RandomFloat(-180.f, 180.f);
			SpawnPos.x += RandomPos;
			NewParticle->GetTransform().SetWorldPosition(SpawnPos);
			float RandomTime = GameEngineRandom::MainRandom.RandomFloat(0.08f, 0.12f);
			Particle_SpawnIter_.StartTimer(RandomTime);
		}
	}
	//RandomYPos
}