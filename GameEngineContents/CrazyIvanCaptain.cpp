#include "PreCompile.h"
#include "CrazyIvanCaptain.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "DNFContentsMinimal.h"

#include "MonsterHP.h"
#include "BoomEffect.h"
#include "Player_Main.h"

CrazyIvanCaptain::CrazyIvanCaptain() :
	Check_SelfDestruct_Timer_(),
	SelfDestructTargetPos_(),
	SelfDestructCol_Timer_()
{
	MaxHP_ = 1000000;
	CurHP_ = MaxHP_;

	Value_.Type = MonsterType::CrazyIvanM;
	Value_.MonsterTextureSize_ = { 200.0f,200.0f,1.0f };
	Value_.DieParticleName = "DieParticleGreen";
	Value_.DieParticleSize = { 0.7f,0.7f,0.7f };
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

	Value_.Attack_1_CoolTime = 10.0f;
}

CrazyIvanCaptain::~CrazyIvanCaptain()
{
}

void CrazyIvanCaptain::Start()
{
	//크레이지 이반 텍스처 로드
	if (GameEngineFolderTexture::Find("crazyivancaptain") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("crazyivancaptain");
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
	InitMonster();
	//StartDebug();
	StartSuperArmor(9999999.0f);
	//State추가
	StateManager_.CreateStateMember("SelfDestruct", std::bind(&CrazyIvanCaptain::SelfDestruct_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&CrazyIvanCaptain::SelfDestruct_Start, this, std::placeholders::_1));

	StateManager_.CreateStateMember("FuryChase", std::bind(&CrazyIvanCaptain::FuryChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&CrazyIvanCaptain::FuryChaseStart, this, std::placeholders::_1));

	//Transition 수정
	{
		Transition_.erase("Idle");
		Transition_.erase("Chase");
		Transition_.erase("Attack_1");
		Transition_.erase("Back");

		DNFTransition Idle;
		Idle.AddValue("Back", 20);
		Idle.AddValue("Chase", 30);
		Idle.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Idle", Idle));
	}

	{
		DNFTransition Chase;
		Chase.AddValue("Back", 30);
		Chase.AddValue("Chase", 30);
		Chase.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Chase", Chase));
	}

	{
		DNFTransition Attack_1;
		Attack_1.AddValue("Back", 30);
		Attack_1.AddValue("Chase", 20);
		Attack_1.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Attack_1", Attack_1));
	}

	{
		DNFTransition Back;
		Back.AddValue("Chase", 20);
		Back.AddValue("Idle", 60);
		Back.AddValue("Back", -1);
		Transition_.insert(std::make_pair("Back", Back));
	}
}

void CrazyIvanCaptain::Update(float _DeltaTime)
{
	UpdateMonster(_DeltaTime);
	CheckIvanFury();

	//UpdateDebug();
}

void CrazyIvanCaptain::CheckIvanFury()
{
	if (StateManager_.GetCurStateStateName() == "SelfDestruct")
	{
		return;
	}
	float HPRatio = static_cast<float>(CurHP_) / static_cast<float>(MaxHP_);
	if (HPRatio < 0.7f/* && IsUnder70_ == false*/)
	{
		//IsUnder70_ = true;
		Value_.Speed = 195.0f;
		MainRenderer_->GetPixelData().PlusColor.r += 0.25f;
	}
	if (HPRatio < 0.35f /*&& IsUnder35_ == false*/)
	{
		//IsUnder35_ = true;
		Value_.Speed = 240.0f;
		MainRenderer_->GetPixelData().PlusColor.r += 0.25f;
	}
}

void CrazyIvanCaptain::End()
{
}

void CrazyIvanCaptain::SelfDestruct_Start(const StateInfo _Info)
{
	ShadowRenderer_->Off();
	SuperArmorRenderer_->Off();
	Force_.OffGravity();
	Force_.ForceX_ = 0;
	MainRenderer_->GetPixelData().PlusColor = { 1.0f,1.0f,1.0f,1.0f };
	GodTime_.StartTimer(1.0f);
	MainRenderer_->CurAnimationPauseOn();

	IsSuperArmor_ = false;
	CurHP_ = 0;
	HPBarUpdate();
	Death(1.5f);
}

void CrazyIvanCaptain::SelfDestruct_Update(float _DeltaTime, const StateInfo _Info)
{
	DieAlpha_ -= _DeltaTime * 1.0f;
	if (DieAlpha_ <= 0.0f)
		DieAlpha_ = 0;
	if (IsDieEffect_ == false && DieAlpha_ < 0.7f)
	{
		//여기서 죽여
		float4 AddPos = { 0,30,0 };
		BoomEffect* NewBoom2 = GetLevel()->CreateActor<BoomEffect>();
		NewBoom2->GetTransform().SetWorldPosition(AddPos + GetTransform().GetWorldPosition() + Value_.DieEffectAddPos + float4(-40, 30, 0));
		NewBoom2->GetTransform().SetLocalScale({ 0.5f,0.5f,0.5f });

		BoomEffect* NewBoom3 = GetLevel()->CreateActor<BoomEffect>();
		NewBoom3->GetTransform().SetWorldPosition(AddPos + GetTransform().GetWorldPosition() + Value_.DieEffectAddPos + float4(40, 30, 0));
		NewBoom3->GetTransform().SetLocalScale({ 0.5f,0.5f,0.5f });

		BoomEffect* NewBoom = GetLevel()->CreateActor<BoomEffect>();
		NewBoom->GetTransform().SetWorldPosition(AddPos + GetTransform().GetWorldPosition() + Value_.DieEffectAddPos);
		NewBoom->GetTransform().SetLocalScale({ 0.5f,0.5f,0.5f });

		//Set Attack
		CurAttackData_.Type = AttackType::Below;
		CurAttackData_.AttackName = "SelfDestruct";
		CurAttackData_.Att = CalAtt(IvanValue_.SelfDstructAtt);
		CurAttackData_.Font = 2;
		CurAttackData_.XForce = 100.0f;
		CurAttackData_.YForce = 500.0f;
		CurAttackData_.Stiffness = 0.10f;
		CurAttackData_.AttCount = 0;
		CurAttackData_.AttCount++;
		CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
		CurAttackData_.AttEffect = Effect::None;
		AttackCol_->GetTransform().SetLocalPosition(IvanValue_.SelfStructAttackPos);
		AttackCol_->GetTransform().SetLocalScale(IvanValue_.SelfStructAttackScale);
		AttackCol_->On();

		MainRenderer_->Off();
		DieAlpha_ = 0.0f;
		IsDieEffect_ = true;
		SelfDestructCol_Timer_.StartTimer(0.13f);
	}

	if (SelfDestructCol_Timer_.IsTimerOn() == true)
	{
		SelfDestructCol_Timer_.Update(_DeltaTime);
		if (SelfDestructCol_Timer_.IsTimerOn() == false)
		{
			AttackCol_->Off();
		}
	}
	MainRenderer_->GetPixelData().MulColor = { 1.0f,1.0f,1.0f,DieAlpha_ };
	MainRenderer_->GetPixelData().PlusColor = { 1.0f,1.0f,1.0f,DieAlpha_ };
}

void CrazyIvanCaptain::CreateMonsterAni()
{
	CreateDNFAnimation("Idle", FrameAnimation_DESC("crazyivancaptain", Ivan_Idle_Start, Ivan_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("crazyivancaptain", Ivan_Move_Start, Ivan_Move_End, AniSpeed_));
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("crazyivancaptain", Ivan_Attack_1_Start, Ivan_Attack_1_End, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("crazyivancaptain", Ivan_Hit_Start, Ivan_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("crazyivancaptain", Ivan_Down_Start, Ivan_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("crazyivancaptain", Ivan_Down_Start, Ivan_Down_Start, AniSpeed_, false));
}

void CrazyIvanCaptain::CreateMonsterAniFunc()
{
	MainRenderer_->AnimationBindFrame("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == Ivan_Attack_1_Start + 1)
			{
				//Set Attack
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "Attack_1";
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.Font = 2;
				CurAttackData_.XForce = 100.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttEffect = Effect::SlashSHori;
				Force_.ForceX_ = 70.0f;
				AttackCol_->On();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Ivan_Attack_1_End)
			{
				//공격이 끝난 직후 로직
				IsAttack_1_End_ = true;
				Attack_1_Timer_.StartTimer(Value_.Attack_1_CoolTime);
				AttackCol_->Off();
			}
		}
	);

	MainRenderer_->AnimationBindEnd("Attack_1",
		[&](const FrameAnimation_DESC&)
		{
			//공격이 끝난 직후 로직
			IsAttack_1_End_ = true;
			Attack_1_Timer_.StartTimer(Value_.Attack_1_CoolTime);
			AttackCol_->Off();
		}
	);
}
void CrazyIvanCaptain::FuryChaseStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Move");
	SelfDestructTargetPos_ = Player_->GetBotPos() + float4(0, 30, 0);
}

void CrazyIvanCaptain::FuryChaseUpdate(float _DeltaTime, const StateInfo _Info)
{
	float4 thisPos = GetTransform().GetWorldPosition();

	float length = DNFMath::Length(SelfDestructTargetPos_, thisPos);

	//목적지에 다다르면 자폭
	if (length < 1.0f)
	{
		StateManager_.ChangeState("SelfDestruct");
		return;
	}

	//Flip
	float4 MoveDir = SelfDestructTargetPos_ - thisPos;
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
	GetTransform().SetWorldMove(MoveDir * Value_.Speed * _DeltaTime);
}

std::string CrazyIvanCaptain::CheckAdditionalPattern(float _DeltaTime)
{
	if (Check_SelfDestruct_Timer_.IsTimerOn() == false) //최초의 타이머 Set
	{
		float RandomValue = GameEngineRandom::MainRandom.RandomFloat(4.5f, 6.3f);
		Check_SelfDestruct_Timer_.StartTimer(RandomValue);
	}
	else
	{
		Check_SelfDestruct_Timer_.Update(_DeltaTime);
		if (Check_SelfDestruct_Timer_.IsTimerOn() == false) //시간이 다되고 자폭하러갈지 판단
		{
			float HPRatio = static_cast<float>(CurHP_) / static_cast<float>(MaxHP_);
			float Value = 1.f - (HPRatio);
			float RandomValue = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
			if (Value > RandomValue)
			{
				return "FuryChase";
			}
		}
	}

	return "";
}