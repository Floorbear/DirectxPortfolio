#include "PreCompile.h"
#include "MiniTau.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"

#include "MonsterHP.h"
#include "Player_Main.h"

MiniTau::MiniTau() :
	WeaponRenderer_(),
	Attack_2_Change_Timer_(),
	Attack_2_Wait_Timer_()
{
	AllDNFRenderer_.push_back(&WeaponRenderer_);

	AdditionRenderer_.push_back(&WeaponRenderer_);

	Value_.MonsterTextureSize_ = { 155.0f,155.0f,1.0f };
	Value_.IdleAboveColPos = { 0,-20 * 0.31f,-500.0f };
	Value_.IdleAboveColScale = { 120 * 0.31f,70 * 0.31f,1 };
	Value_.IdleBelowColPos = { 0,-50 * 0.31f,-500 };
	Value_.IdleBelowColScale = { 120 * 0.31f,70 * 0.31f,1 };
	Value_.HitAboveColPos = { 0,-20 * 0.31f,-500.0f };
	Value_.HitAboveColScale = { 120 * 0.31f,70 * 0.31f,1 };
	Value_.HitBelowColPos = { 0,-50 * 0.31f,-500 };
	Value_.HitBelowColScale = { 120 * 0.31f,70 * 0.31f,1 };
	Value_.DownAboveColPos = { -65 * 0.31f,-60 * 0.31f,-500 };
	Value_.DownAboveColScale = { 120 * 0.31f,20 * 0.31f,1 };
	Value_.DownBelowColPos = { -65 * 0.31f,-80 * 0.31f,-500 };
	Value_.DownBelowColScale = { 120 * 0.31f,20 * 0.31f,1 };

	//출혈
	Value_.BleedingPos = { -90 * 0.31f,120 * 0.31f };
	Value_.BleedingScale = { -0.6f,0.6f,0.6f };

	HitEffectMovePos_ = { 0,-20 * 0.31f,0 }; //Hit파티클이 생기는 위치

	Attack_1_Pos_ = { 40.0f * 0.31f,-38.0f * 0.31f,-500.0f };
	Attack_1_Scale_ = { 120.0f * 0.31f,50.0f * 0.31f,1.0f };
	ShadowPos_ = { -10.f * 0.31f,-28.f * 0.31f,500.f,1.f };
	ShadowAirAcc_ = 0.31f;
	//ShadowPos_ = { -10.f ,-28.f ,500.f,1.f };
	BotPos_ = { 0,-88.f * 0.31f,0 };

	Value_.Attack_1_CoolTime = 0.2f;

	Value_.Speed = 110.0f;

	Value_.Type = MonsterType::MiniTauM;
	Value_.DieParticleName = "DieParticleBrown";
	Value_.DieParticleSize = { 0.5f,0.5f,0.5f };
	MaxHP_ = 500000;
	CurHP_ = MaxHP_;
	FindRange_ = 550.0f;

	Value_.SuperArmorPos = { 0.0f,0.0f };
	Value_.SuperArmorScale = { 513.0f * 0.31f,506.0f * 0.31f }; //슈퍼아머 상태
	Value_.StartSuperArmorScale = { 690.f * 0.31f,690.f * 0.31f };
	Value_.SuperArmorSmallerSpeed = 400.0f;

	Value_.ChaseAccPos = { 0,-55.f,0 };
}

MiniTau::~MiniTau()
{
}

void MiniTau::Start()
{
	//미니 타우 텍스처 로드
	if (GameEngineFolderTexture::Find("minitau_body") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("minitau");
		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}
	InitMonster();

	StateManager_.CreateStateMember("Attack_2", std::bind(&MiniTau::Attack_2_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MiniTau::Attack_2_Start, this, std::placeholders::_1),
		std::bind(&MiniTau::Attack_2_End, this, std::placeholders::_1));
}

void MiniTau::Update(float _DeltaTime)
{
	UpdateMonster(_DeltaTime);
	if (Attack_2_CoolTimer_.IsTimerOn() == true)
	{
		Attack_2_CoolTimer_.Update(_DeltaTime);
	}
}

void MiniTau::End()
{
}

void MiniTau::Attack_2_Start(const StateInfo _Info)
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
	StartSuperArmor(2.0f);
	Attack_2_Wait_Timer_.StartTimer(0.35f);
}

void MiniTau::Attack_2_Update(float _DeltaTime, const StateInfo _Info)
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
			CurAttackData_.XForce = 500.0f;
			CurAttackData_.YForce = 250.0f;
			CurAttackData_.Stiffness = 0.35f;
			CurAttackData_.RStiffness = 0.34f;
			CurAttackData_.AttCount = 0;
			CurAttackData_.AttCount++;
			CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
			CurAttackData_.AttEffect = Effect::SlashSLeft;
			AttackCol_->GetTransform().SetLocalPosition(Attack_2_Pos_);
			AttackCol_->On();
			ChangeDNFAnimation("Attack_2");
			Force_.ForceX_ += Value_.Speed;
			Attack_2_Change_Timer_.StartTimer(0.9f); //0.9초뒤에 박기 종료
			return;
		}
		return;
	}
	//플레이어를 박았어
	if (AttackCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::PlayerHit, CollisionType::CT_OBB2D) == true &&
		IsZPosHit(static_cast<int>(Player_->GetBotPos().y)) == true)
	{
		Attack_2_Change_Timer_.StartTimer(0.1f);
		return;
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

	//픽셀충돌 범위 밖에 도달했어
	if (CheckColMap() == false)
	{
		StateManager_.ChangeState("Hit");
		return;
	}
}

void MiniTau::Attack_2_End(const StateInfo _Info)
{
	Attack_2_CoolTimer_.StartTimer(Attack_2_CoolTime);
	OnAir_ = false;
	Force_.OffGravity();
	Force_.ForceX_ = 0.f;
	Force_.FrictionX_ = Value_.Default_Frction;
	Attack_2_Change_Timer_.Off();
	AttackCol_->Off();
	OffSuperArmor();
	CurAttackData_ = {};
}

void MiniTau::CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc)
{
	MainRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
	ShadowRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
	FrameAnimation_DESC NewDesc = _Desc;
	NewDesc.TextureName = "minitau_weapon";
	WeaponRenderer_->CreateFrameAnimationFolder(_AnimationName, NewDesc);
}

void MiniTau::ChangeDNFAnimation(const std::string& _Name)
{
	MainRenderer_->ChangeFrameAnimation(_Name);
	ShadowRenderer_->ChangeFrameAnimation(_Name);
	WeaponRenderer_->ChangeFrameAnimation(_Name);
}

void MiniTau::CreateMonsterAni()
{
	CreateDNFAnimation("Idle", FrameAnimation_DESC("minitau_body", Tau_Idle_Start, Tau_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("minitau_body", Tau_Move_Start, Tau_Move_End, AniSpeed_));
	std::vector<unsigned int> AttackFrames = { 1,2,2,2,2,3,4,5,6,6,6 };
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("minitau_body", AttackFrames, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("minitau_body", Tau_Hit_Start, Tau_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("minitau_body", Tau_Down_Start, Tau_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("minitau_body", Tau_Down_Start, Tau_Down_Start, AniSpeed_, false));
	CreateDNFAnimation("Attack_2_Wait", FrameAnimation_DESC("minitau_body", Tau_Attack_2_Wait_Start, Tau_Attack_2_Wait_Start, AniSpeed_, false));
	CreateDNFAnimation("Attack_2", FrameAnimation_DESC("minitau_body", Tau_Attack_2_Start, Tau_Attack_2_End, AniSpeed_, true));
}

void MiniTau::CreateMonsterAniFunc()
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

void MiniTau::InitAdditionalRenderer()
{
	//추가 렌더러 생성
	{
		WeaponRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		WeaponRenderer_->SetScaleModeImage();
	}
}

std::string MiniTau::CheckAdditionalPattern(float _DeltaTime)
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