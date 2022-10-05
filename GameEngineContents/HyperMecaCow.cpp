#include "PreCompile.h"
#include "HyperMecaCow.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"

#include "Runner.h"
#include "SummonCircle.h"
#include "MonsterHP.h"
#include "Player_Main.h"
#include "DNFHUD.h"
HyperMecaCow::HyperMecaCow() :
	WeaponRenderer_(),
	Attack_2_Change_Timer_(),
	Attack_2_Wait_Timer_(),
	AdditonAttack_Timer_()
{
	AllDNFRenderer_.push_back(&WeaponRenderer_);

	AdditionRenderer_.push_back(&WeaponRenderer_);

	Value_.MonsterTextureSize_ = { 750.0f,750.0f,1.0f };
	Value_.IdleAboveColPos = { -30,-60,-500.0f };
	Value_.IdleAboveColScale = { 150,70,1 };
	Value_.IdleBelowColPos = { -30,-90,-500 };
	Value_.IdleBelowColScale = { 150,70,1 };
	Value_.HitAboveColPos = Value_.IdleAboveColPos;
	Value_.HitAboveColScale = Value_.IdleAboveColScale;
	Value_.HitBelowColPos = Value_.IdleBelowColPos;
	Value_.HitBelowColScale = Value_.IdleBelowColScale;
	Value_.DownAboveColPos = { -95,-80,-500 };
	Value_.DownAboveColScale = { 240,20,1 };
	Value_.DownBelowColPos = { -95,-100,-500 };
	Value_.DownBelowColScale = { 240,20,1 };

	//출혈
	Value_.BleedingPos = { -100,150 };
	Value_.BleedingScale = { -1.6f,1.6f,1.6f };

	HitEffectMovePos_ = { 0,-20,0 }; //Hit파티클이 생기는 위치

	Attack_1_Pos_ = { 70.0f,-118.0f,-500.0f };
	Attack_1_Scale_ = { 280.0f,40.0f,1.0f };
	ShadowPos_ = { -10.f,-28.f,500.f,1.f };
	BotPos_ = { 0,-128.f,0 };

	Value_.Attack_1_CoolTime = 0.5f;

	Value_.Speed = 170.0f;

	Value_.Type = MonsterType::MecaTauM;
	Value_.DieParticleName = "DieParticleBrown";
	Value_.DieParticleSize = { 1.5f,1.5f,1.5f };
	MaxHP_ = 3000000; //3000000
	CurHP_ = MaxHP_;
	PerHP_ = 110000; //110000
	FindRange_ = 1250.0f;

	Value_.SuperArmorPos = { 0.0f,0.0f };
	Value_.SuperArmorScale = { 753.0f,756.0f }; //슈퍼아머 상태
	Value_.StartSuperArmorScale = { 850.f,850.f };
	Value_.SuperArmorSmallerSpeed = 430.0f;

	Value_.ChaseAccPos = { 0,20,0 };
}
HyperMecaCow::~HyperMecaCow()
{
}

void HyperMecaCow::Start()
{
	//메카타우 텍스처 로드
	if (GameEngineFolderTexture::Find("hypermecacow_body") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("hypermecacow");
		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}

	//브레스 텍스처 로드
	if (GameEngineFolderTexture::Find("fire_start") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("SkillTexture");
		Dir.Move("Breath");
		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}
	InitMonster();

	//Transition 수정 >> 좀더 호전적이게
	{
		Transition_.erase("Idle");
		Transition_.erase("Chase");
		Transition_.erase("Attack_1");
		Transition_.erase("Back");

		DNFTransition Idle;
		Idle.AddValue("Back", 5);
		Idle.AddValue("Chase", 70);
		Idle.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Idle", Idle));
	}

	{
		DNFTransition Chase;
		Chase.AddValue("Back", 10);
		Chase.AddValue("Chase", 70);
		Chase.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Chase", Chase));
	}

	{
		DNFTransition Attack_1;
		Attack_1.AddValue("Back", 10);
		Attack_1.AddValue("Chase", 60);
		Attack_1.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Attack_1", Attack_1));
	}

	{
		DNFTransition Back;
		Back.AddValue("Chase", 80);
		Back.AddValue("Idle", 10);
		Back.AddValue("Back", -1);
		Transition_.insert(std::make_pair("Back", Back));
	}

	//상태 추가
	Attack_2_CoolTimer_.StartTimer();
	Breath_CoolTimer.StartTimer();
	Runner_CoolTimer.StartTimer();
	StateManager_.CreateStateMember("Attack_2", std::bind(&HyperMecaCow::Attack_2_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HyperMecaCow::Attack_2_Start, this, std::placeholders::_1),
		std::bind(&HyperMecaCow::Attack_2_End, this, std::placeholders::_1));

	StateManager_.CreateStateMember("UpperAttack", std::bind(&HyperMecaCow::UpperAttack_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HyperMecaCow::UpperAttack_Start, this, std::placeholders::_1),
		std::bind(&HyperMecaCow::UpperAttack_End, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Breath", std::bind(&HyperMecaCow::Breath_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HyperMecaCow::Breath_Start, this, std::placeholders::_1),
		std::bind(&HyperMecaCow::Breath_End, this, std::placeholders::_1));
	StateManager_.CreateStateMember("SpawnRunner", std::bind(&HyperMecaCow::SpawnRunner_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HyperMecaCow::SpawnRunner_Start, this, std::placeholders::_1),
		std::bind(&HyperMecaCow::SpawnRunner_End, this, std::placeholders::_1));

	//사운드 초기화
	SetHitSound("hyper_tau_dmg_0", 4, 1.1f);
	DieSound_ = "boneCrusher_charge.wav";
}

void HyperMecaCow::Update(float _DeltaTime)
{
	if (StateManager_.GetCurStateStateName() == "Die" && StateManager_.GetCurStateTime() < 0.25f)
	{
		GameEngineTime::GetInst()->SetGlobalScale(0.1f);
	}
	else
	{
		GameEngineTime::GetInst()->SetGlobalScale(1.0f);
		if (StateManager_.GetCurStateStateName() == "Die" && IsDieFirst_ == true)
		{
			IsDieFirst_ = false;
			GameEngineSound::SoundPlayOneShot("hyper_tau_die_01.wav");
			DNFGlobalValue::CurrentHUD_->EndingTimer_.StartTimer(2.5f);
		}
	}
	UpdateMonster(_DeltaTime);
	CheckCoolTime(_DeltaTime);
}

void HyperMecaCow::CheckCoolTime(float _DeltaTime)
{
	if (Attack_2_CoolTimer_.IsTimerOn() == true)
	{
		Attack_2_CoolTimer_.Update(_DeltaTime);
	}
	if (UpperAttack_CoolTimer_.IsTimerOn() == true)
	{
		UpperAttack_CoolTimer_.Update(_DeltaTime);
	}
	if (Breath_CoolTimer.IsTimerOn() == true)
	{
		Breath_CoolTimer.Update(_DeltaTime);
	}
	if (Runner_CoolTimer.IsTimerOn() == true)
	{
		Runner_CoolTimer.Update(_DeltaTime);
	}
}

void HyperMecaCow::End()
{
}

void HyperMecaCow::Attack_2_Start(const StateInfo _Info)
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

void HyperMecaCow::Attack_2_Update(float _DeltaTime, const StateInfo _Info)
{
	//돌진 공격 전 준비동작
	if (Attack_2_Wait_Timer_.IsTimerOn() == true)
	{
		Attack_2_Wait_Timer_.Update(_DeltaTime);
		if (Attack_2_Wait_Timer_.IsTimerOn() == false) //준비자세를 취하고 돌진하기 직전 순간
		{
			//사운드
			CurAttackData_.AttackSound = "axe_hit_03.wav";
			//Set Attack
			CurAttackData_.Type = AttackType::Above;
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
			UpperAttackScale.x *= 0.25f;
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
			StateManager_.ChangeState("Chase");
			return;
		}
	}

	Force_.ForceX_ += Value_.Speed * 10.0f * _DeltaTime;
	//오브젝트에 박았어
	if (BotCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::Object, CollisionType::CT_OBB2D) == true)
	{
		GameEngineSound::SoundPlayControl("tau_crash.wav");
		Player_->ShakeCamera(11.5f, 0.35f);
		StateManager_.ChangeState("Hit");
		return;
	}

	//픽셀충돌 범위 밖에 도달했어
	if (CheckColMap() == false)
	{
		GameEngineSound::SoundPlayControl("tau_crash.wav");
		Player_->ShakeCamera(11.5f, 0.35f);
		StateManager_.ChangeState("Hit");
		return;
	}
}

void HyperMecaCow::Attack_2_End(const StateInfo _Info)
{
	Attack_2_CoolTimer_.StartTimer();
	OnAir_ = false;
	Force_.OffGravity();
	Force_.ForceX_ = 0.f;
	Force_.FrictionX_ = Value_.Default_Frction;
	Attack_2_Change_Timer_.Off();
	AttackCol_->Off();
	OffSuperArmor();
	AttackCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	CurAttackData_ = {};
}

void HyperMecaCow::UpperAttack_Start(const StateInfo _Info)
{
	StartSuperArmor(1.5f);
	ChangeDNFAnimation("UpperAttack");
	WeaponRenderer_->Off();
	float4 UpperAttackScale = Attack_1_Scale_;
	UpperAttackScale.x *= 0.25f;
	AttackCol_->GetTransform().SetLocalScale(UpperAttackScale);
}

void HyperMecaCow::UpperAttack_Update(float _DeltaTime, const StateInfo _Info)
{
	if (IsUpperAttackEnd == true)
	{
		StateManager_.ChangeState("Chase");
	}
}

void HyperMecaCow::UpperAttack_End(const StateInfo _Info)
{
	WeaponRenderer_->On();
	//공격이 끝난 직후 로직
	IsUpperAttackEnd = false;
	UpperAttack_CoolTimer_.StartTimer();
	AttackCol_->Off();

	OnAir_ = false;
	Force_.OffGravity();
	Force_.ForceX_ = 0.f;
	Force_.FrictionX_ = Value_.Default_Frction;
	CurAttackData_ = {};

	AttackCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
}

void HyperMecaCow::SpawnRunner_Start(const StateInfo _Info)
{
	StartSuperArmor(2.9f);
	ChangeDNFAnimation("SpawnRunner");
	WeaponRenderer_->Off();
}
void HyperMecaCow::SpawnRunner_Update(float _DeltaTime, const StateInfo _Info)
{
	if (IsSpawnRunner_ == true)
	{
		StateManager_.ChangeState("Chase");
	}
}
void HyperMecaCow::SpawnRunner_End(const StateInfo _Info)
{
	WeaponRenderer_->On();
	//공격이 끝난 직후 로직
	IsSpawnRunner_ = false;
	Runner_CoolTimer.StartTimer();
}

void HyperMecaCow::Breath_Start(const StateInfo _Info)
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

	StartSuperArmor(2.9f);
	ChangeDNFAnimation("Breath");
	WeaponRenderer_->Off();
}

void HyperMecaCow::Breath_Update(float _DeltaTime, const StateInfo _Info)
{
	if (IsBreathEnd_ == true)
	{
		StateManager_.ChangeState("Chase");
	}
}

void HyperMecaCow::Breath_End(const StateInfo _Info)
{
	WeaponRenderer_->On();
	//공격이 끝난 직후 로직
	IsBreathEnd_ = false;
	Breath_CoolTimer.StartTimer();
	AttackCol_->Off();

	OnAir_ = false;
	Force_.OffGravity();
	Force_.ForceX_ = 0.f;
	Force_.FrictionX_ = Value_.Default_Frction;
	CurAttackData_ = {};
	BreathFront_->Off();
	BreathBack_->Off();

	AttackCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	AttackCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
}

void HyperMecaCow::SpawnRunner()
{
	std::vector<float4> SpawnPos;
	SpawnPos.reserve(3);
	float4 CurPos = GetTransform().GetWorldPosition();

	for (int i = 0; i < 3; i++)
	{
		float4 _SpawnWorldPos = {};
		//랜덤Pos를 구하고 Break
		float RandomPosX = GameEngineRandom::MainRandom.RandomFloat(CurPos.x - 300.0f, CurPos.x + 300.0f);
		if (RandomPosX > 1210)
		{
			RandomPosX = 1209.f;
		}
		if (RandomPosX < 150)
		{
			RandomPosX = 151.f;
		}
		float RandomPosY = GameEngineRandom::MainRandom.RandomFloat(-479.f, -349.f);
		_SpawnWorldPos.x = RandomPosX;
		_SpawnWorldPos.y = RandomPosY;
		SpawnPos.push_back(_SpawnWorldPos);
	}

	for (auto i : SpawnPos)
	{
		SummonCircle* NewCircle = GetLevel()->CreateActor< SummonCircle>();
		NewCircle->GetTransform().SetWorldPosition(i);
		NewCircle->SummonMonster<Runner>();
	}
}

void HyperMecaCow::CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc)
{
	MainRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
	ShadowRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
	FrameAnimation_DESC NewDesc = _Desc;
	NewDesc.TextureName = "hypermecacow_axe";
	WeaponRenderer_->CreateFrameAnimationFolder(_AnimationName, NewDesc);
}

void HyperMecaCow::ChangeDNFAnimation(const std::string& _Name)
{
	MainRenderer_->ChangeFrameAnimation(_Name);
	ShadowRenderer_->ChangeFrameAnimation(_Name);
	WeaponRenderer_->ChangeFrameAnimation(_Name);
}

void HyperMecaCow::CreateMonsterAni()
{
	CreateDNFAnimation("Idle", FrameAnimation_DESC("hypermecacow_body", Tau_Idle_Start, Tau_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("hypermecacow_body", Tau_Move_Start, Tau_Move_End, AniSpeed_));
	std::vector<unsigned int> AttackFrames = { 1,2,2,2,3,4,5,6,6,6 };
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("hypermecacow_body", AttackFrames, AniSpeed_, false));
	std::vector<unsigned int> UpperAttackFrames = { 6,6,6,5,4,3,2,2,2 };
	CreateDNFAnimation("UpperAttack", FrameAnimation_DESC("hypermecacow_body", UpperAttackFrames, AniSpeed_, false));
	std::vector<unsigned int> ShoutFrames = { 28,29,30,31,29,30,31,29,30,31 ,29,30,31,29,30,31 }; //로봇소환, Breath 애니함수 별도 구현을 위해
	CreateDNFAnimation("Breath", FrameAnimation_DESC("hypermecacow_body", ShoutFrames, AniSpeed_, false));
	CreateDNFAnimation("SpawnRunner", FrameAnimation_DESC("hypermecacow_body", ShoutFrames, AniSpeed_, false));

	CreateDNFAnimation("Hit", FrameAnimation_DESC("hypermecacow_body", Tau_Hit_Start, Tau_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("hypermecacow_body", Tau_Down_Start, Tau_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("hypermecacow_body", Tau_Down_Start, Tau_Down_Start, AniSpeed_, false));
	CreateDNFAnimation("Attack_2_Wait", FrameAnimation_DESC("hypermecacow_body", Tau_Attack_2_Wait_Start, Tau_Attack_2_Wait_Start, AniSpeed_, false));
	CreateDNFAnimation("Attack_2", FrameAnimation_DESC("hypermecacow_body", Tau_Attack_2_Start, Tau_Attack_2_End, AniSpeed_, true));

	//브레스 애니메이션
	float BreathTime = 0.05f;
	BreathFront_->CreateFrameAnimationFolder("Breath_Start", FrameAnimation_DESC("fire_start", BreathTime, false));
	BreathFront_->CreateFrameAnimationFolder("Breath_Loop", FrameAnimation_DESC("fire_loop", BreathTime, true));
	BreathFront_->CreateFrameAnimationFolder("Breath_End", FrameAnimation_DESC("fire_end", BreathTime, false));
	BreathFront_->ChangeFrameAnimation("Breath_Start");

	BreathBack_->Off();
	BreathFront_->Off();
}

void HyperMecaCow::CreateMonsterAniFunc()
{
	MainRenderer_->AnimationBindFrame("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == 1)
			{
				StartSuperArmor(1.5f);
			}
			if (_Desc.Frames[_Desc.CurFrame - 1] == 3)
			{
				GameEngineSound::SoundPlayControl("tau_axeSwing.wav");
				CurAttackData_.AttackSound = "axe_hit_03.wav";
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
				Player_->ShakeCamera(11.5f, 0.35f);
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

	MainRenderer_->AnimationBindFrame("UpperAttack",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == 5)
			{
				GameEngineSound::SoundPlayControl("tau_axeSwing.wav");
				CurAttackData_.AttackSound = "axe_hit_03.wav";
				//Set Attack
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "UpperAttack";
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.Font = 2;
				CurAttackData_.XForce = 100.0f;
				CurAttackData_.YForce = 1450.0f;
				CurAttackData_.Stiffness = 0.85f;
				CurAttackData_.RStiffness = 0.71f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttEffect = Effect::SlashSLeft;
				AttackCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
				AttackCol_->On();
			}
			if (_Desc.Frames[_Desc.CurFrame - 1] == 3)
			{
				AttackCol_->Off();
			}
		}
	);

	MainRenderer_->AnimationBindEnd("UpperAttack",
		[&](const FrameAnimation_DESC& _Desc)
		{
			//공격이 끝난 직후 로직
			IsUpperAttackEnd = true;
			UpperAttack_CoolTimer_.StartTimer();
			AttackCol_->Off();
		}
	);

	//랜드러너
	MainRenderer_->AnimationBindFrame("SpawnRunner",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 4)
			{
				GameEngineSound::SoundPlayControl("summon_equipment.wav");
				GameEngineSound::SoundPlayControl(GetRandomSound("hyper_tau_atk_0", 1, 3));
				Player_->ShakeCamera(13.0f, 0.55f);
				SpawnRunner();
			}
		}
	);

	MainRenderer_->AnimationBindEnd("SpawnRunner",
		[&](const FrameAnimation_DESC& _Desc)
		{
			IsSpawnRunner_ = true;
		}
	);

	//브래스
	MainRenderer_->AnimationBindFrame("Breath",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 3)
			{
				GameEngineSound::SoundPlayControl(GetRandomSound("hyper_tau_atk_0", 1, 3));
				BreathFront_->On();
				BreathFront_->ChangeFrameAnimation("Breath_Start");
				BreathFront_->CurAnimationReset();
			}
		}
	);

	MainRenderer_->AnimationBindEnd("Breath",
		[&](const FrameAnimation_DESC& _Desc)
		{
			//공격이 끝난 직후 로직
			IsBreathEnd_ = true;
			//UpperAttack_CoolTimer_.StartTimer();
			AttackCol_->Off();
		}
	);

	//브레스 불길
	BreathFront_->AnimationBindEnd("Breath_Start",
		[&](const FrameAnimation_DESC& _Desc)
		{
			BreathFront_->ChangeFrameAnimation("Breath_Loop");
			CurAttackData_.AttCount = 0;
			CurAttackData_.Type = AttackType::Above;
			CurAttackData_.AttackName = "Breath";
			CurAttackData_.Att = CalAtt(static_cast<int>(Value_.Attack_1_Att * 0.3));
			CurAttackData_.Font = 2;
			CurAttackData_.XForce = 100.0f;
			//CurAttackData_.YForce = 1450.0f;
			CurAttackData_.Stiffness = 0.1f;
			CurAttackData_.RStiffness = 0.04f;
			CurAttackData_.AttCount++;
			CurAttackData_.ZPos = 0;
			//CurAttackData_.AttEffect = Effect::SlashSLeft;
			AttackCol_->GetTransform().SetLocalPosition(Attack_2_Pos_ + float4(170, 30));
			AttackCol_->On();
			float4 AttackSclae = Attack_1_Scale_;
			AttackSclae.y *= 1.5f;
			AttackCol_->GetTransform().SetLocalScale(AttackSclae);
		}
	);

	BreathFront_->AnimationBindStart("Breath_Loop",
		[&](const FrameAnimation_DESC& _Desc)
		{
			//Set Attack
			CurAttackData_.Type = AttackType::Above;
			CurAttackData_.AttackName = "Breath";
			CurAttackData_.Att = CalAtt(static_cast<int>(Value_.Attack_1_Att * 0.3));
			CurAttackData_.Font = 2;
			CurAttackData_.XForce = 100.0f;
			//CurAttackData_.YForce = 1450.0f;
			CurAttackData_.Stiffness = 0.1f;
			CurAttackData_.RStiffness = 0.04f;
			CurAttackData_.AttCount++;
			CurAttackData_.ZPos = 0;
			//CurAttackData_.AttEffect = Effect::SlashSLeft;
			AttackCol_->GetTransform().SetLocalPosition(Attack_2_Pos_ + float4(170, 30));
			float4 AttackSclae = Attack_1_Scale_;
			AttackSclae.y *= 1.5f;
			AttackCol_->GetTransform().SetLocalScale(AttackSclae);
		}
	);
}

void HyperMecaCow::InitAdditionalRenderer()
{
	//추가 렌더러 생성
	{
		WeaponRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		WeaponRenderer_->SetScaleModeImage();
		BreathFront_ = CreateComponent<GameEngineTextureRenderer>();
		BreathFront_->SetScaleModeImage();
		BreathBack_ = CreateComponent<GameEngineTextureRenderer>();
		BreathBack_->SetScaleModeImage();
		BreathFront_->GetTransform().SetLocalPosition(BreathPos_);
		BreathFront_->GetPixelData().MulColor.a = 0.7f;
	}
}

std::string HyperMecaCow::CheckAdditionalPattern(float _DeltaTime)
{
	if (Attack_2_CoolTimer_.IsTimerOn() == false)
	{
		//돌진하면 적이 맞을꺼 같냐
		if (IsZPosHit(static_cast<int>(Player_->GetBotPos().y + 10.0f)) == true &&
			abs(Player_->GetTransform().GetWorldPosition().x - GetTransform().GetWorldPosition().x) < FindRange_)
		{
			return "Attack_2";
		}
	}

	if (UpperAttack_CoolTimer_.IsTimerOn() == false)
	{
		//밥상 뒤집기 하면 적이 맞을꺼 같냐
		if (IsZPosHit(static_cast<int>(Player_->GetBotPos().y + 10.0f)) == true &&
			abs(Player_->GetTransform().GetWorldPosition().x - GetTransform().GetWorldPosition().x) < AttackCol_->GetTransform().GetLocalScale().Half().x)
		{
			return "UpperAttack";
		}
	}

	if (Breath_CoolTimer.IsTimerOn() == false)
	{
		//브래스 하면 적이 맞을꺼 같냐
		if (IsZPosHit(static_cast<int>(Player_->GetBotPos().y + 10.0f)) == true &&
			abs(Player_->GetTransform().GetWorldPosition().x - GetTransform().GetWorldPosition().x) < Attack_1_Scale_.x + 130.0f)
		{
			return "Breath";
		}
	}

	if (Runner_CoolTimer.IsTimerOn() == false)
	{
		return "SpawnRunner";
	}
	return "";
}