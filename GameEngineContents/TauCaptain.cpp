#include "PreCompile.h"
#include "TauCaptain.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"

#include "MonsterHP.h"
#include "Player_Main.h"

TauCaptain::TauCaptain() :
	WeaponRenderer_(),
	Attack_2_Change_Timer_(),
	Attack_2_Wait_Timer_()
{
	AllDNFRenderer_.push_back(&WeaponRenderer_);

	AdditionRenderer_.push_back(&WeaponRenderer_);

	Value_.MonsterTextureSize_ = { 500.0f,500.0f,1.0f };
	Value_.IdleAboveColPos = { 0,-20,-500.0f };
	Value_.IdleAboveColScale = { 120,70,1 };
	Value_.IdleBelowColPos = { 0,-50,-500 };
	Value_.IdleBelowColScale = { 120,70,1 };
	Value_.HitAboveColPos = { 0,-20,-500.0f };
	Value_.HitAboveColScale = { 120,70,1 };
	Value_.HitBelowColPos = { 0,-50,-500 };
	Value_.HitBelowColScale = { 120,70,1 };
	Value_.DownAboveColPos = { -65,-60,-500 };
	Value_.DownAboveColScale = { 120,20,1 };
	Value_.DownBelowColPos = { -65,-80,-500 };
	Value_.DownBelowColScale = { 120,20,1 };

	//출혈
	Value_.BleedingPos = { -90,120 };
	Value_.BleedingScale = { -1.3f,1.3f,1.3f };

	HitEffectMovePos_ = { 0,-20,0 }; //Hit파티클이 생기는 위치

	Attack_1_Pos_ = { 40.0f,-38.0f,-500.0f };
	Attack_1_Scale_ = { 120.0f,50.0f,1.0f };
	ShadowPos_ = { -10.f,-28.f,500.f,1.f };
	BotPos_ = { 0,-88.f,0 };

	Value_.Attack_1_CoolTime = 0.2f;

	Value_.Speed = 170.0f;

	Value_.Type = MonsterType::TauCaptainM;
	Value_.DieParticleName = "DieParticleRed";
	Value_.DieParticleSize = { 1.0f,1.0f,1.0f };
	MaxHP_ = 1700000;
	CurHP_ = MaxHP_;
	FindRange_ = 850.0f;

	Value_.SuperArmorPos = { 0.0f,0.0f };
	Value_.SuperArmorScale = { 513.0f,506.0f }; //슈퍼아머 상태
	Value_.StartSuperArmorScale = { 690.f,690.f };
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

	//추가 패턴의 확률 추가
	//Transition_
	Attack_2_CoolTimer_.StartTimer(Attack_2_CoolTime * 0.7f);

	StateManager_.CreateStateMember("Attack_2", std::bind(&TauCaptain::Attack_2_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&TauCaptain::Attack_2_Start, this, std::placeholders::_1),
		std::bind(&TauCaptain::Attack_2_End, this, std::placeholders::_1));
}

void TauCaptain::Update(float _DeltaTime)
{
	UpdateMonster(_DeltaTime);
	if (Attack_2_CoolTimer_.IsTimerOn() == true)
	{
		Attack_2_CoolTimer_.Update(_DeltaTime);
	}
}

void TauCaptain::End()
{
}

void TauCaptain::Attack_2_Start(const StateInfo _Info)
{
	//Flip Check
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();
	float4 MoveDir = PlayerPos - thisPos;
	MoveDir.z = 0;
	MoveDir.Normalize();
	if (MoveDir.x > 0)
	{
		GetTransform().PixLocalPositiveX();
	}
	else
	{
		GetTransform().PixLocalNegativeX();
	}

	ChangeDNFAnimation("Attack_2_Wait");
	StartSuperArmor(9999.0f);
	Attack_2_Wait_Timer_.StartTimer(0.35f);
}

void TauCaptain::Attack_2_Update(float _DeltaTime, const StateInfo _Info)
{
	//돌진 공격 전 준비동작
	if (Attack_2_Wait_Timer_.IsTimerOn() == true)
	{
		Attack_2_Wait_Timer_.Update(_DeltaTime);
		if (Attack_2_Wait_Timer_.IsTimerOn() == false) //준비자세를 취하고 돌진하기 직전 순간
		{
			//Set Attack
			CurAttackData_.Type = AttackType::Below;
			CurAttackData_.AttackName = "Attack_2";
			CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
			CurAttackData_.Font = 2;
			CurAttackData_.XForce = 1100.0f;
			CurAttackData_.YForce = 350.0f;
			CurAttackData_.Stiffness = 0.85f;
			CurAttackData_.RStiffness = 0.84f;
			CurAttackData_.AttCount = 0;
			CurAttackData_.AttCount++;
			CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
			CurAttackData_.AttEffect = Effect::SlashSLeft;
			AttackCol_->GetTransform().SetLocalPosition(Attack_2_Pos_);
			float4 UpperAttackScale = Attack_1_Scale_;
			UpperAttackScale.x *= 0.5f;
			AttackCol_->GetTransform().SetLocalScale(UpperAttackScale);
			AttackCol_->On();
			ChangeDNFAnimation("Attack_2");
			Force_.ForceX_ += Value_.Speed;
			return;
		}
		return;
	}
	//플레이어를 박았어
	if (AttackCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::PlayerHit, CollisionType::CT_OBB2D) == true &&
		IsZPosHit(static_cast<int>(Player_->GetBotPos().y)) == true)
	{
		//O.2초뒤에 Idle상태로
		Player_->ShakeCamera(11.5f, 0.35f);
		Attack_2_Change_Timer_.StartTimer(0.2f);
	}

	if (Attack_2_Change_Timer_.IsTimerOn() == true) //플레이어를 박고 0.1초뒤 Idle상태로
	{
		Attack_2_Change_Timer_.Update(_DeltaTime);
		if (Attack_2_Change_Timer_.IsTimerOn() == false)
		{
			StateManager_.ChangeState("Idle");
			return;
		}
	}

	Force_.ForceX_ += Value_.Speed * 10.0f * _DeltaTime;
	//오브젝트에 박았어
	if (BotCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::Object, CollisionType::CT_OBB2D) == true)
	{
		Player_->ShakeCamera(11.5f, 0.35f);
		StateManager_.ChangeState("Hit");
		return;
	}

	//픽셀충돌 범위 밖에 도달했어
	if (CheckColMap() == false)
	{
		Player_->ShakeCamera(11.5f, 0.35f);
		StateManager_.ChangeState("Hit");
		return;
	}
}

void TauCaptain::Attack_2_End(const StateInfo _Info)
{
	Attack_2_CoolTimer_.StartTimer(Attack_2_CoolTime);
	OnAir_ = false;
	Force_.OffGravity();
	Force_.ForceX_ = 0.f;
	Force_.FrictionX_ = Value_.Default_Frction;
	Attack_2_Change_Timer_.Off();
	AttackCol_->Off();
	AttackCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	OffSuperArmor();
	CurAttackData_ = {};
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
	std::vector<unsigned int> AttackFrames = { 1,2,2,2,2,3,4,5,6,6,6 };
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("taucaptain_body", AttackFrames, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("taucaptain_body", Tau_Hit_Start, Tau_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("taucaptain_body", Tau_Down_Start, Tau_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("taucaptain_body", Tau_Down_Start, Tau_Down_Start, AniSpeed_, false));
	CreateDNFAnimation("Attack_2_Wait", FrameAnimation_DESC("taucaptain_body", Tau_Attack_2_Wait_Start, Tau_Attack_2_Wait_Start, AniSpeed_, false));
	CreateDNFAnimation("Attack_2", FrameAnimation_DESC("taucaptain_body", Tau_Attack_2_Start, Tau_Attack_2_End, AniSpeed_, true));
}

void TauCaptain::CreateMonsterAniFunc()
{
	MainRenderer_->AnimationBindFrame("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == 1)
			{
				StartSuperArmor(1.0f);
			}
			if (_Desc.Frames[_Desc.CurFrame - 1] == 3)
			{
				//Set Attack
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "Attack_1";
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.Font = 2;
				CurAttackData_.XForce = 300.0f;
				//CurAttackData_.YForce = 950.0f;
				CurAttackData_.Stiffness = 0.35f;
				CurAttackData_.RStiffness = 0.21f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttEffect = Effect::SlashSLeft;
				AttackCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
				AttackCol_->On();
			}
			if (_Desc.Frames[_Desc.CurFrame - 1] == 5)
			{
				AttackCol_->Off();
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
	if (Attack_2_CoolTimer_.IsTimerOn() == false)
	{
		//돌진하면 적이 맞을꺼 같냐
		if (IsZPosHit(static_cast<int>(Player_->GetBotPos().y)) == true &&
			abs(Player_->GetTransform().GetWorldPosition().x - GetTransform().GetWorldPosition().x) < FindRange_)
		{
			return "Attack_2";
		}
	}

	return "";
}