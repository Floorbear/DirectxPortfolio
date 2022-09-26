#include "PreCompile.h"
#include "Runner.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "DNFContentsMinimal.h"

#include "MonsterHP.h"
#include "BoomEffect.h"
#include "Player_Main.h"

Runner::Runner() :
	Check_SelfDestruct_Timer_(),
	SelfDestructCol_Timer_()
{
	MaxHP_ = 120000;
	CurHP_ = MaxHP_;

	Value_.Type = MonsterType::CrazyIvanM;
	Value_.MonsterTextureSize_ = { 105.0f,94.0f,1.0f };
	Value_.DieParticleName = "DieParticleRobot";
	Value_.DieParticleSize = { 1.0f,1.0f,1.0f };
	Value_.IdleAboveColPos = { -20,0,-500.0f };
	Value_.IdleAboveColScale = { 40,30,1 };
	Value_.IdleBelowColPos = { -20,-30,-500 };
	Value_.IdleBelowColScale = { 40,40,1 };

	Value_.HitAboveColPos = Value_.IdleAboveColPos;
	Value_.HitAboveColScale = Value_.IdleAboveColScale;
	Value_.HitBelowColPos = Value_.IdleBelowColPos;
	Value_.HitBelowColScale = Value_.IdleBelowColScale;
	Value_.DownAboveColPos = { -25,-30,-500 };
	Value_.DownAboveColScale = { 80,20,1 };
	Value_.DownBelowColPos = { -25,-50,-500 };
	Value_.DownBelowColScale = { 80,20,1 };

	HitEffectMovePos_ = { 0,-20,0 }; //Hit파티클이 생기는 위치

	Attack_1_Pos_ = { 20.0f,-30.0f,-500.0f };
	Attack_1_Scale_ = { 80.0f,50.0f,1.0f };
	BotPos_ = { 0,-40.f,0 };

	Value_.Attack_1_CoolTime = 10.0f;

	Value_.Speed = 70.0f;

	Value_.ChaseAccPos = { 0,-55.f,0 };
	ShadowAirAcc_ = 0.31f;
	ShadowPos_ = { -10.f * 0.31f,-28.f * 0.31f,500.f,1.f };
}

Runner::~Runner()
{
}

void Runner::Start()
{
	//랜드러너  텍스처 로드
	if (GameEngineFolderTexture::Find("rx78") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("rx78");
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
	InitMonster();
	StartDebug();
	//State추가

	//Transition 수정
	{
		Transition_.erase("Idle");
		Transition_.erase("Chase");
		Transition_.erase("Attack_1");
		Transition_.erase("Back");

		DNFTransition Idle;
		Idle.AddValue("Back", 20);
		Idle.AddValue("Chase", 70);
		Idle.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Idle", Idle));
	}

	{
		DNFTransition Chase;
		Chase.AddValue("Back", 15);
		Chase.AddValue("Chase", 75);
		Chase.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Chase", Chase));
	}

	{
		DNFTransition Attack_1;
		Attack_1.AddValue("SelfDestruct", -1);
		//Attack_1.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Attack_1", Attack_1));
	}

	{
		DNFTransition Back;
		Back.AddValue("Chase", 80);
		Back.AddValue("Idle", 5);
		Back.AddValue("Back", -1);
		Transition_.insert(std::make_pair("Back", Back));
	}

	//State추가
	StateManager_.CreateStateMember("SelfDestruct", std::bind(&Runner::SelfDestruct_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Runner::SelfDestruct_Start, this, std::placeholders::_1));
}

void Runner::Update(float _DeltaTime)
{
	UpdateMonster(_DeltaTime);
	UpdateDebug();
}

void Runner::End()
{
}

void Runner::SelfDestruct_Start(const StateInfo _Info)
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

void Runner::SelfDestruct_Update(float _DeltaTime, const StateInfo _Info)
{
	DieAlpha_ -= _DeltaTime * 1.0f;
	if (DieAlpha_ <= 0.0f)
		DieAlpha_ = 0;
	if (IsDieEffect_ == false && DieAlpha_ < 0.95f)
	{
		//여기서 죽여
		float4 AddPos = { 0,30,0 };

		BoomEffect* NewBoom = GetLevel()->CreateActor<BoomEffect>();
		NewBoom->GetTransform().SetWorldPosition(AddPos + GetTransform().GetWorldPosition() + Value_.DieEffectAddPos);
		NewBoom->GetTransform().SetLocalScale({ 0.5f,0.5f,0.5f });

		//Set Attack
		CurAttackData_.Type = AttackType::Below;
		CurAttackData_.AttackName = "SelfDestruct";
		CurAttackData_.Att = CalAtt(IvanValue_.SelfDstructAtt);
		CurAttackData_.Font = 2;
		CurAttackData_.XForce = 100.0f;
		//CurAttackData_.YForce = 500.0f;
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
		Player_->ShakeCamera(13.0f, 0.35f);
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

void Runner::CreateMonsterAni()
{
	CreateDNFAnimation("Idle", FrameAnimation_DESC("rx78", Runner_Idle_Start, Runner_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("rx78", Runner_Move_Start, Runner_Move_End, AniSpeed_));
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("rx78", Runner_Attack_1_Start, Runner_Attack_1_End, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("rx78", Runner_Hit_Start, Runner_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("rx78", Runner_Down_Start, Runner_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("rx78", Runner_Down_Start, Runner_Down_Start, AniSpeed_, false));
}

void Runner::CreateMonsterAniFunc()
{
	MainRenderer_->AnimationBindFrame("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 0)
			{
				GodTime_.StartTimer(5.0f);
				//시작프레임에 갓모드
			}
		}
	);

	MainRenderer_->AnimationBindEnd("Attack_1",
		[&](const FrameAnimation_DESC&)
		{
			//공격이 끝난 직후 로직
			IsAttack_1_End_ = true;
			Attack_1_Timer_.StartTimer(Value_.Attack_1_CoolTime);
		}
	);
}