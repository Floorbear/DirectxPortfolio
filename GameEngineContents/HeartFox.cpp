#include "PreCompile.h"
#include "HeartFox.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"

#include "MonsterHP.h"
#include "Player_Main.h"

HeartFox::HeartFox() :
	Attack_2_Wait_Timer_(),
	Attack_2_TargetPos_(),
	LugaruValue()
{
	AllDNFRenderer_.push_back(&AvaRenderer_Angry_);
	AllDNFRenderer_.push_back(&AvaRenderer_);
	AllDNFRenderer_.push_back(&ClowRenderer_);

	AdditionRenderer_.push_back(&AvaRenderer_);
	AdditionRenderer_.push_back(&AvaRenderer_Angry_);
	AdditionRenderer_.push_back(&ClowRenderer_);

	Value_.Type = MonsterType::HeartFoxM;
	Value_.DieParticleName = "DieParticleBlue";
	Value_.DieParticleSize = { 0.7f,0.7f,0.7f };
	MaxHP_ = 1700000;
	CurHP_ = MaxHP_;
	FindRange_ = 550.0f;

	Value_.SuperArmorPos = { 0.0f,0.0f };
	Value_.SuperArmorScale = { 328.0f,321.0f }; //슈퍼아머 상태
	Value_.StartSuperArmorScale = { 420.f,420.f };
	Value_.SuperArmorSmallerSpeed = 430.0f;
}

HeartFox::~HeartFox()
{
}

void HeartFox::Start()
{
	//고집불통 하트넥 텍스처 로드
	if (GameEngineFolderTexture::Find("heart_body") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("HeartFox");
		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}
	InitMonster();

	Value_.BleedingPos.y -= 50.0f;

	//전이 추가
	{
		DNFTransition Attack_2;
		Attack_2.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Attack_2", Attack_2));
	}
	//State추가
	StateManager_.CreateStateMember("Attack_2", std::bind(&HeartFox::Attack_2_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeartFox::Attack_2_Start, this, std::placeholders::_1),
		std::bind(&HeartFox::Attack_2_End, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Angry", std::bind(&HeartFox::Angry_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeartFox::Angry_Start, this, std::placeholders::_1));
}

void HeartFox::InitAdditionalRenderer()
{
	//추가 렌더러 생성
	{
		AvaRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		//AvaRenderer_->GetTransform().SetWorldMove({ 0,0,-1 });
		AvaRenderer_->SetScaleModeImage();

		AvaRenderer_Angry_ = CreateComponent<GameEngineTextureRenderer>();
		AvaRenderer_Angry_->SetScaleModeImage();

		ClowRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		ClowRenderer_->SetScaleModeImage();
	}
}

void HeartFox::Update(float _DeltaTime)
{
	UpdateMonster(_DeltaTime);
	if (Attack_2_Timer_.IsTimerOn() == true)
	{
		Attack_2_Timer_.Update(_DeltaTime);
	}
}

void HeartFox::End()
{
}

void HeartFox::CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc)
{
	MainRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
	ShadowRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
	FrameAnimation_DESC NewDesc = _Desc;
	NewDesc.TextureName = "heart_fox_ava";
	AvaRenderer_->CreateFrameAnimationFolder(_AnimationName, NewDesc);
	NewDesc.TextureName = "heart_fox_ava2";
	AvaRenderer_Angry_->CreateFrameAnimationFolder(_AnimationName, NewDesc);
	AvaRenderer_Angry_->Off();
	NewDesc.TextureName = "heart_fox_ava2_clow";
	ClowRenderer_->CreateFrameAnimationFolder(_AnimationName, NewDesc);
	ClowRenderer_->Off();
}

void HeartFox::ChangeDNFAnimation(const std::string& _Name)
{
	MainRenderer_->ChangeFrameAnimation(_Name);
	ShadowRenderer_->ChangeFrameAnimation(_Name);
	if (IsAngry_ == true)
	{
		AvaRenderer_->Off();
		AvaRenderer_Angry_->On();
		ClowRenderer_->On();
	}
	AvaRenderer_->ChangeFrameAnimation(_Name);
	AvaRenderer_Angry_->ChangeFrameAnimation(_Name);
	ClowRenderer_->ChangeFrameAnimation(_Name);
}

void HeartFox::Attack_2_Start(const StateInfo _Info)
{
	if (IsAngry_ == true)
	{
		StartSuperArmor(1.5f);
	}
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

	//TargetPos Set
	Attack_2_TargetPos_ = PlayerPos;
	GroundYPos_ = PlayerPos.y;

	ChangeDNFAnimation("Attack_2_Wait");
	Attack_2_Wait_Timer_.StartTimer(0.35f);
}

void HeartFox::Attack_2_Update(float _DeltaTime, const StateInfo _Info)
{
	//점프 공격 전 준비동작
	Attack_2_Wait_Timer_.Update(_DeltaTime);
	if (Attack_2_Wait_Timer_.IsTimerOn() == true)
	{
		return;
	}
	else
	{
		if (Attack_2_Wait_Timer_.IsSet == false) //준비자세를 취하고 점프하기 직전 순간
		{
			Attack_2_Wait_Timer_.IsSet = true;

			//앞으로 가는 힘
			float4 thisPos = GetTransform().GetWorldPosition();
			float ForceX = abs(Attack_2_TargetPos_.x - thisPos.x);
			Force_.ForceX_ = ForceX * LugaruValue.Attack_2_ForceXAcc;

			//마찰력
			Force_.FrictionX_ = ForceX * LugaruValue.Attack_2_FrctionAcc;

			//점프 하는 힘
			Force_.ForceY_ = LugaruValue.Attack_2_ForceY;
			GroundYPos_ = Attack_2_TargetPos_.y;
			StartYForce();
			ChangeDNFAnimation("Attack_2");
			return;
		}
	}

	//여기서 부터 공격하려고 뛰어오르는 상태
	float4 CurPos = GetTransform().GetWorldPosition();
	if (CurPos.y <= GroundYPos_)
	{
		if (Force_.ForceY_ >= 0) //아직 위로 상승중임
		{
			return;
		}
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		OnAir_ = false;
		Force_.OffGravity();
		StateManager_.ChangeState(Transition_["Attack_2"].Decide());
		return;
	}
}

void HeartFox::Attack_2_End(const StateInfo _Info)
{
	OnAir_ = false;
	Force_.OffGravity();
	Force_.FrictionX_ = Value_.Default_Frction;
	AttackCol_->Off();
	CurAttackData_ = {};
}

void HeartFox::Angry_Start(const StateInfo _Info)
{
	StartSuperArmor(1.5f);
	LugaruValue.Attack_2_CoolTime = 3.0f;
	Value_.Attack_1_CoolTime = 2.5f;
	Value_.Speed = 200.0f;
	ChangeDNFAnimation("Angry");
}

void HeartFox::Angry_Update(float _DeltaTime, const StateInfo _Info)
{
}

void HeartFox::CreateMonsterAni()
{
	CreateDNFAnimation("Idle", FrameAnimation_DESC("heart_body", Lugaru_Idle_Start, Lugaru_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("heart_body", Lugaru_Move_Start, Lugaru_Move_End, AniSpeed_));
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("heart_body", Lugaru_Attack_1_Start, Lugaru_Attack_1_End, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("heart_body", Lugaru_Hit_Start, Lugaru_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("heart_body", Lugaru_Down_Start, Lugaru_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("heart_body", Lugaru_Down_Start, Lugaru_Down_Start, AniSpeed_, false));

	CreateDNFAnimation("Attack_2_Wait", FrameAnimation_DESC("heart_body", Lugaru_Attack_2_Wait_Start, Lugaru_Attack_2_Wait_End, AniSpeed_, false));
	CreateDNFAnimation("Attack_2", FrameAnimation_DESC("heart_body", Lugaru_Attack_2_Start, Lugaru_Attack_2_End, AniSpeed_, false));

	CreateDNFAnimation("Angry", FrameAnimation_DESC("heart_body", Lugaru_Angry_Start, Lugaru_Angry_End, AniSpeed_, false));
}

void HeartFox::CreateMonsterAniFunc()
{
	MainRenderer_->AnimationBindFrame("Angry",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Angry_End)
			{
				StateManager_.ChangeState("Chase");
			}
		});

	MainRenderer_->AnimationBindFrame("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_Start)
			{
				if (IsAngry_ == true)
				{
					StartSuperArmor(0.7f);
				}
			}
			if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_Start + 1)
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
				CurAttackData_.AttEffect = Effect::SlashSHori;
				Force_.ForceX_ = 70.0f;
				AttackCol_->On();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_Start + 3)
			{
				CurAttackData_.AttCount++;
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_End)
			{
				//공격이 끝난 직후 로직
				IsAttack_1_End_ = true;
				Attack_1_Timer_.StartTimer();
				AttackCol_->Off();
			}
		}
	);

	MainRenderer_->AnimationBindFrame("Attack_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_2_Start + 1)
			{
				//Set Attack
				CurAttackData_.Type = AttackType::Above;
				CurAttackData_.AttackName = "Attack_2";
				CurAttackData_.Att = CalAtt(LugaruValue.Attack_2_Att);
				CurAttackData_.Font = 2;
				CurAttackData_.XForce = 100.0f;
				//CurAttackData_.YForce = 300.0f;
				CurAttackData_.Stiffness = 0.35f;
				CurAttackData_.RStiffness = 0.21f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = 0;
				CurAttackData_.AttEffect = Effect::SlashSLeft;
				Force_.ForceX_ = 70.0f;
				AttackCol_->On();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_2_Start + 3)
			{
				AttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_2_End)
			{
				//공격이 끝난 직후 로직
				/*IsAttack_1_End_ = true;
				Attack_1_Timer_.StartTimer();*/
			}
		}
	);
}

std::string HeartFox::CheckAdditionalPattern(float _DeltaTime)
{
	//현재 체력이 55퍼 이하면 화냄
	float HPRatio = static_cast<float>(CurHP_) / static_cast<float>(MaxHP_);
	if (HPRatio <= 0.55f && IsAngry_ == false)
	{
		IsAngry_ = true;
		return "Angry";
	}
	if (Attack_2_Timer_.IsTimerOn() == false)
	{
		Attack_2_Timer_.StartTimer(LugaruValue.Attack_2_CoolTime);

		//앞으로 가는 힘
		float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
		float4 thisPos = GetTransform().GetWorldPosition();

		float XLength = abs(PlayerPos.x - thisPos.x);
		float YLength = abs(PlayerPos.y - thisPos.y);

		if (XLength >= LugaruValue.Attack_2_StartRange.x || YLength >= LugaruValue.Attack_2_StartRange.y)
		{
			return "";
		}
		//사정거리 내에 들면 공격할 확률 70프로
		float RandomValue = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);
		if (RandomValue < 0.7f)
		{
			return "Attack_2";
		}
	}
	return "";
}