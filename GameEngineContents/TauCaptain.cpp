#include "PreCompile.h"
#include "TauCaptain.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"

#include "MonsterHP.h"
#include "Player_Main.h"

TauCaptain::TauCaptain() :
	WeaponRenderer_()
{
	AllDNFRenderer_.push_back(&WeaponRenderer_);

	AdditionRenderer_.push_back(&WeaponRenderer_);

	Value_.MonsterTextureSize_ = { 500.0f,500.0f,1.0f };
	Value_.IdleAboveColPos = { 0,0,-500.0f };
	Value_.IdleAboveColScale = { 60,47,1 };
	Value_.IdleBelowColPos = { 0,-30,-500 };
	Value_.HitAboveColPos = { 0, 0, -500.0f };
	Value_.HitAboveColScale = { 60,47,1 };
	Value_.HitBelowColPos = { 0, -30, -500 };
	Value_.HitBelowColScale = { 60,47,1 };
	Value_.DownAboveColPos = { -25,-30,-500 };
	Value_.DownAboveColScale = { 80,20,1 };
	Value_.DownBelowColPos = { -25,-50,-500 };
	Value_.DownBelowColScale = { 80,20,1 };

	HitEffectMovePos_ = { 0,-20,0 }; //Hit파티클이 생기는 위치

	Attack_1_Pos_ = { 40.0f,-30.0f,-500.0f };
	Attack_1_Scale_ = { 120.0f,50.0f,1.0f };
	ShadowPos_ = { -10.f,-28.f,500.f,1.f };
	BotPos_ = { 0,-58.f,0 };

	Value_.Attack_1_CoolTime = 5.0f;

	Value_.Speed = 100.0f;

	Value_.Type = MonsterType::HeartFoxM;
	Value_.DieParticleName = "DieParticleRed";
	Value_.DieParticleSize = { 1.0f,1.0f,1.0f };
	MaxHP_ = 1700000;
	CurHP_ = MaxHP_;
	FindRange_ = 550.0f;

	Value_.SuperArmorPos = { 0.0f,0.0f };
	Value_.SuperArmorScale = { 328.0f,321.0f }; //슈퍼아머 상태
	Value_.StartSuperArmorScale = { 420.f,420.f };
	Value_.SuperArmorSmallerSpeed = 430.0f;
}

TauCaptain::~TauCaptain()
{
}

void TauCaptain::Start()
{
	//타우 캡틴 텍스처 로드
	if (GameEngineFolderTexture::Find("taucaptain_body") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("taucaptain");
		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}
	InitMonster();

	Value_.BleedingPos.y -= 50.0f;
}

void TauCaptain::Update(float _DeltaTime)
{
	UpdateMonster(_DeltaTime);
}

void TauCaptain::End()
{
}

void TauCaptain::CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc)
{
	MainRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
	ShadowRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
	FrameAnimation_DESC NewDesc = _Desc;
	NewDesc.TextureName = "taucaptain_weapon";
	WeaponRenderer_->CreateFrameAnimationFolder(_AnimationName, NewDesc);
}

void TauCaptain::ChangeDNFAnimation(const std::string& _Name)
{
	MainRenderer_->ChangeFrameAnimation(_Name);
	ShadowRenderer_->ChangeFrameAnimation(_Name);
	WeaponRenderer_->ChangeFrameAnimation(_Name);
}

void TauCaptain::CreateMonsterAni()
{
	CreateDNFAnimation("Idle", FrameAnimation_DESC("taucaptain_body", Tau_Idle_Start, Tau_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("taucaptain_body", Tau_Move_Start, Tau_Move_End, AniSpeed_));
	std::vector<unsigned int> AttackFrames = { 1,2,2,2,3,4,5,6,6,6 };
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("taucaptain_body", AttackFrames, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("taucaptain_body", Tau_Hit_Start, Tau_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("taucaptain_body", Tau_Down_Start, Tau_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("taucaptain_body", Tau_Down_Start, Tau_Down_Start, AniSpeed_, false));
}

void TauCaptain::CreateMonsterAniFunc()
{
	MainRenderer_->AnimationBindFrame("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == 3)
			{
				//Set Attack
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "Attack_1";
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.Font = 2;
				CurAttackData_.XForce = 100.0f;
				//CurAttackData_.YForce = 300.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttEffect = Effect::SlashSLeft;
				AttackCol_->On();
			}
		}
	);

	MainRenderer_->AnimationBindEnd("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			//공격이 끝난 직후 로직
			IsAttack_1_End_ = true;
			Attack_1_Timer_.StartTimer();
			AttackCol_->Off();
		}
	);
}

void TauCaptain::InitAdditionalRenderer()
{
	//추가 렌더러 생성
	{
		WeaponRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		WeaponRenderer_->SetScaleModeImage();
	}
}

std::string TauCaptain::CheckAdditionalPattern(float _DeltaTime)
{
	return "";
}