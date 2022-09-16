#include "PreCompile.h"
#include "DNFMonster.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineStateManager.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "DNFBackground.h"
#include "MonsterHP.h"
#include "Player_Main.h"
#include "DieEffect.h"
//Player_Utilty를 만들까?

DNFMonster::DNFMonster() :
	AniSpeed_(0.12f),
	Player_(),
	FindRange_(450.0f),
	AttackRangeCol_(),
	Attack_1_Scale_(),
	Attack_1_Pos_(),
	IsAttack_1_End_(false),
	BackMoveDir_(),
	IsIdleFirst_(true),
	Attack_1_Timer_(4.0f),
	Idle_Timer_(3.0f),
	Back_Timer_(3.0f),
	Chase_Timer_(5.0f),
	Hit_Timer_(1.0f),
	AttackCol_(),
	ID_(0),
	DieAlpha_(1.0f),
	IsDieEffect_(false)
{
	InitDefaultValue();
	InitTransition();
}

DNFMonster::~DNFMonster()
{
}

void DNFMonster::InitMonster()
{
	DNFStart();

	InitCol();

	InitAniNState();

	//Force
	Force_.SetTransfrom(&GetTransform());
	Force_.FrictionX_ = 700.0f;
	Force_.Gravity_ = 1000.0f;
}

void DNFMonster::UpdateMonster(float _DeltaTime)
{
	StiffnessUpdate(_DeltaTime);
	if (Stiffness_ > 0.0f)
	{
		return;
	}
	if (ID_ == 0)
	{
		MsgBoxAssert("ID가 0입니다. ID를 세팅해주세요");
	}
	TimerCheck(_DeltaTime);
	Force_.Update(_DeltaTime * (1 + (AirborneTime_ * AirborneTime_) * 0.01f));

	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		Player_ = DNFGlobalValue::CurrentLevel->GetPlayer();
	}
	HitColCheck(ColOrder::PlayerAttack);
	StateManager_.Update(_DeltaTime);

	//제한된 범위 밖을 나가지 못하게
	CheckColMap();
	DNFUpdate();
}

void DNFMonster::CheckColMap()
{
	float4 MapScale = GetDNFLevel()->GetMapScale();
	float4 PlayerPosBot = GetTransform().GetWorldPosition();
	PlayerPosBot.y = -PlayerPosBot.y - BotPos_.y;

	GameEngineTexture* ColMap = DNFGlobalValue::CurrentLevel->GetBackground()->GetColRenderer()->GetCurTexture();

	//픽셀충돌범위를 넘어가면 이전 위치로 고정시킨다.
	if (OnAir_ == false)
	{
		if (ColMap->GetPixelToFloat4(static_cast<int>(PlayerPosBot.x), static_cast<int>(PlayerPosBot.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			GetTransform().SetWorldPosition(PrevPos_);
		}
	}
	else
	{
		float4 DownPos = GetTransform().GetWorldPosition();
		DownPos.y = -GroundYPos_ - BotPos_.y;
		if (ColMap->GetPixelToFloat4(static_cast<int>(PlayerPosBot.x), static_cast<int>(DownPos.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			GetTransform().SetWorldPosition(PrevPos_);
		}
	}

	//이전위치와 차이가 있으면 PrevPos를 갱신한다.
	if (DNFMath::Length(PrevPos_, GetTransform().GetWorldPosition()) >= 0.5f)
	{
		PrevPos_ = GetTransform().GetWorldPosition();
	}
}

void DNFMonster::End()
{
}

void DNFMonster::InitAniNState()
{
	MainRenderer_->GetTransform().SetLocalScale(Value_.MonsterTextureSize_);
	ShadowRenderer_->GetTransform().SetLocalScale(Value_.MonsterTextureSize_);

	//애니메이션 추가
	CreateMonsterAni();

	//애니메이션 바인드
	CreateMonsterAniFunc();

	//State 추가
	StateManager_.CreateStateMember("Idle", std::bind(&DNFMonster::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&DNFMonster::IdleStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Chase", std::bind(&DNFMonster::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&DNFMonster::ChaseStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Back", std::bind(&DNFMonster::BackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&DNFMonster::BackStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Hit", std::bind(&DNFMonster::HitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&DNFMonster::HitStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Airborne", std::bind(&DNFMonster::AirborneUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&DNFMonster::AirborneStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Down", std::bind(&DNFMonster::DownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&DNFMonster::DownStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Die", std::bind(&DNFMonster::DieUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&DNFMonster::DieStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Attack_1", std::bind(&DNFMonster::Attack_1_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&DNFMonster::Attack_1_Start, this, std::placeholders::_1),
		std::bind(&DNFMonster::Attack_1_End, this, std::placeholders::_1));

	StateManager_.ChangeState("Idle");
}

void DNFMonster::InitCol()
{
	//콜라이더 추가
	AttackRangeCol_ = CreateComponent<GameEngineCollision>("Col");
	AttackRangeCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0, 0.0f, 1.0f, 0.2f));

	AttackRangeCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	AttackRangeCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
	AttackRangeCol_->ChangeOrder(ColOrder::MonsterRange);

	//AttackCol
	AttackCol_ = CreateComponent<GameEngineCollision>("Col");
	AttackCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0, 0.0f, 1.0f, 0.5f));
	AttackCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	AttackCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
	AttackCol_->ChangeOrder(ColOrder::MonsterAttack);
	AttackCol_->Off();

	//AboveHit
	HitAbove_ = CreateComponent<GameEngineCollision>("Middle");
	HitAbove_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
	HitAbove_->GetTransform().SetLocalPosition(Value_.HitAboveColPos);
	HitAbove_->GetTransform().SetLocalScale(Value_.HitAboveColScale);
	HitAbove_->ChangeOrder(ColOrder::MonsterHit);

	//BottomHit
	HitBelow_ = CreateComponent<GameEngineCollision>("Bottom");
	HitBelow_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0.0f, 1.0f, 0.0f, 0.5f));
	HitBelow_->GetTransform().SetLocalPosition(Value_.HitBelowColPos);
	HitBelow_->GetTransform().SetLocalScale(Value_.HitBelowColScale);
	HitBelow_->ChangeOrder(ColOrder::MonsterHit);
}

void DNFMonster::IdleStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Idle");
	ChangeHitColTrans("Idle");

	Idle_Timer_ = GameEngineRandom::MainRandom.RandomFloat(1.0f, 3.0f);
	Idle_Timer_.StartTimer();
}

void DNFMonster::IdleUpdate(float _DeltaTime, const StateInfo _Info)
{
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();

	float length = DNFMath::Length(PlayerPos, thisPos);

	if (length > FindRange_)
	{
		IsIdleFirst_ = true;
		return;
	}

	//FindRange에 접근하면 바로 상태 판단에 들어간다.
	if (IsIdleFirst_ == true)
	{
		IsIdleFirst_ = false;
		StateManager_.ChangeState(Transition_["Idle"].Decide());
	}

	//상태 판단

	//공격범위 내에 접근하면 바로 공격
	if (CanHitAttack1() == true)
	{
		StateManager_.ChangeState("Attack_1");
		return;
	}

	if (Idle_Timer_.IsTimerOn() == true)
	{
		Idle_Timer_ -= _DeltaTime;
	}
	else
	{
		StateManager_.ChangeState(Transition_["Idle"].Decide());
	}
}

void DNFMonster::ChaseStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Move");
	Chase_Timer_ = GameEngineRandom::MainRandom.RandomFloat(2.0f, 5.0f);
	Chase_Timer_.StartTimer();
}

void DNFMonster::ChaseUpdate(float _DeltaTime, const StateInfo _Info)
{
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();

	float length = DNFMath::Length(PlayerPos, thisPos);

	//공격범위 내에 접근하면 바로 공격
	if (CanHitAttack1() == true)
	{
		StateManager_.ChangeState("Attack_1");
		return;
	}

	//플레이어와 너무 가까우면 Idle
	if (length < 20.0f)
	{
		StateManager_.ChangeState("Idle");
		return;
	}

	//상태 판단
	if (Chase_Timer_.IsTimerOn() == true)
	{
		Chase_Timer_ -= _DeltaTime;
	}
	else
	{
		StateManager_.ChangeState(Transition_["Chase"].Decide());
	}

	//Flip
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
	GetTransform().SetWorldMove(MoveDir * 100.0f * _DeltaTime);
}

void DNFMonster::Attack_1_Start(const StateInfo _Info)
{
	ChangeDNFAnimation("Attack_1");
}

void DNFMonster::Attack_1_Update(float _DeltaTime, const StateInfo _Info)
{
	if (IsAttack_1_End_ == true)
	{
		StateManager_.ChangeState(Transition_["Attack_1"].Decide());
	}
}

void DNFMonster::Attack_1_End(const StateInfo _Info)
{
	IsAttack_1_End_ = false;
	Attack_1_Timer_.StartTimer();
	AttackCol_->Off();
	CurAttackData_ = {};
}

void DNFMonster::BackStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Move");

	Back_Timer_ = GameEngineRandom::MainRandom.RandomFloat(1.0f, 3.0f);
	Back_Timer_.StartTimer();

	//후퇴 방향 정하기
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();
	BackMoveDir_ = PlayerPos - thisPos;
	BackMoveDir_.y += GameEngineRandom::MainRandom.RandomFloat(-80.0f, 80.0f);
	BackMoveDir_.z = 0;
	BackMoveDir_.Normalize();
	if (BackMoveDir_.x > 0)
	{
		GetTransform().PixLocalPositiveX();
	}
	else
	{
		GetTransform().PixLocalNegativeX();
	}

	BackMoveDir_.x = -BackMoveDir_.x;
	BackMoveDir_.y = -BackMoveDir_.y;
}

void DNFMonster::BackUpdate(float _DeltaTime, const StateInfo _Info)
{
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();

	float length = DNFMath::Length(PlayerPos, thisPos);

	if (length > FindRange_)
	{
		StateManager_.ChangeState("Idle");
		return;
	}

	//상태 판단
	//공격범위 내에 접근하면 바로 공격
	if (CanHitAttack1() == true)
	{
		StateManager_.ChangeState("Attack_1");
		return;
	}

	if (Back_Timer_.IsTimerOn() == true)
	{
		Back_Timer_ -= _DeltaTime;
	}
	else
	{
		StateManager_.ChangeState(Transition_["Back"].Decide());
	}

	GetTransform().SetWorldMove(BackMoveDir_ * 100.0f * _DeltaTime);
}

void DNFMonster::HitStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Hit");
	ResetDNFAnimation();
	ChangeHitColTrans("Hit");
	Hit_Timer_.StartTimer();

	//플레이어를 마주보는 방향으로 Flip
	FlipX(-Player_->GetDirX());
	Force_.ForceX_ += -PrevHitData_.XForce;
}

void DNFMonster::HitUpdate(float _DeltaTime, const StateInfo _Info)
{
	//사망검사
	if (CurHP_ == 0)
	{
		StateManager_.ChangeState("Die");
		return;
	}
	if (Hit_Timer_.IsTimerOn() == true)
	{
		Hit_Timer_ -= _DeltaTime;
	}
	else
	{
		StateManager_.ChangeState("Idle");
		PrevHitData_ = {};
		return;
	}
}

void DNFMonster::AirborneStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Hit");
	ResetDNFAnimation();
	ChangeHitColTrans("Hit");
	//플레이어를 마주보는 방향으로 Flip
	FlipX(-Player_->GetDirX());
	Force_.ForceX_ += -PrevHitData_.XForce;

	GetTransform().SetLocalMove(float4(0, Force_.ForceY_ * GameEngineTime::GetDeltaTime()));
	Force_.OnGravity();
	OnAir_ = true;
}

void DNFMonster::AirborneUpdate(float _DeltaTime, const StateInfo _Info)
{
	//경직
	//추락
	AirborneTime_ += _DeltaTime;
	float CurYPos = GetTransform().GetWorldPosition().y;

	if (CurYPos <= GroundYPos_)
	{
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		ShadowUpdate();
		//Down 상태 Bounce
		OnAir_ = true;
		Force_.ForceY_ = 200.0f;
		Force_.ForceX_ += -140.0f;
		AirborneTime_ = 0.0f;
		Force_.OnGravity();
		PrevHitData_ = {};
		GodTime_.StartTimer(Value_.Down_God_Time);
		StateManager_.ChangeState("Down");
		return;
	}
}

void DNFMonster::DownStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Down");
	ChangeHitColTrans("Down");
	Down_Timer_.StartTimer(Value_.Down_Time);
	Force_.ForceX_ += -PrevHitData_.XForce;

	GetTransform().SetLocalMove(float4(0, Force_.ForceY_ * GameEngineTime::GetDeltaTime()));
}

void DNFMonster::DownUpdate(float _DeltaTime, const StateInfo _Info)
{
	AirborneTime_ += 5.0f * _DeltaTime;
	float CurYPos = GetTransform().GetWorldPosition().y;

	//사망검사
	if (CurHP_ == 0)
	{
		StateManager_.ChangeState("Die");
		return;
	}

	if (CurYPos <= GroundYPos_)
	{
		//GroundYPos 아래로 떨어지지 않게 고정시키기
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		ShadowUpdate();
		//이전에 받은 공격 데이터 초기화
		//PrevHitData_ = {};
		Down_Timer_ -= _DeltaTime * (1.f + AirborneTime_ * 0.1f);
		OnAir_ = false;
		Force_.OffGravity();

		//기상검사
		if (Down_Timer_.IsTimerOn() == false)
		{
			OnAir_ = false;
			Force_.ForceY_ = 0.0f;
			AirborneTime_ = 0.0f;
			Force_.OffGravity();
			GodTime_.StartTimer(Value_.Down_God_Time);
			PrevHitData_ = {};
			StateManager_.ChangeState("Idle");
			return;
		}
	}
}

void DNFMonster::DieStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Die");
	ShadowRenderer_->Off();
	Force_.OffGravity();
	Force_.ForceX_ = 0;
	MainRenderer_->GetPixelData().PlusColor = { 1.0f,1.0f,1.0f,1.0f };
	Death(1.5f);
}

void DNFMonster::DieUpdate(float _DeltaTime, const StateInfo _Info)
{
	DieAlpha_ -= _DeltaTime * 5.0f;
	if (DieAlpha_ <= 0.0f)
		DieAlpha_ = 0;
	if (IsDieEffect_ == false && DieAlpha_ < 0.2f)
	{
		//여기서 죽여
		DieEffect* NewDieEffect = GetLevel()->CreateActor<DieEffect>();
		NewDieEffect->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + Value_.DieEffectAddPos);
		NewDieEffect->GetTransform().SetLocalScale(Value_.DieParticleSize);
		NewDieEffect->Init(Value_.DieParticleName);
		IsDieEffect_ = true;
	}
	MainRenderer_->GetPixelData().MulColor = { 1.0f,1.0f,1.0f,DieAlpha_ };
	MainRenderer_->GetPixelData().PlusColor = { 1.0f,1.0f,1.0f,DieAlpha_ };
}
void DNFMonster::ChangeHitColTrans(std::string _State)
{
	if (_State == "Hit")
	{
		HitAbove_->GetTransform().SetLocalPosition(Value_.HitAboveColPos);
		HitAbove_->GetTransform().SetLocalScale(Value_.HitAboveColScale);
		HitBelow_->GetTransform().SetLocalPosition(Value_.HitBelowColPos);
		HitBelow_->GetTransform().SetLocalScale(Value_.HitBelowColScale);
		return;
	}
	else if (_State == "Idle")
	{
		HitAbove_->GetTransform().SetLocalPosition(Value_.IdleAboveColPos);
		HitAbove_->GetTransform().SetLocalScale(Value_.IdleAboveColScale);
		HitBelow_->GetTransform().SetLocalPosition(Value_.IdleBelowColPos);
		HitBelow_->GetTransform().SetLocalScale(Value_.IdleBelowColScale);
		return;
	}
	else if (_State == "Down")
	{
		HitAbove_->GetTransform().SetLocalPosition(Value_.DownAboveColPos);
		HitAbove_->GetTransform().SetLocalScale(Value_.DownAboveColScale);
		HitBelow_->GetTransform().SetLocalPosition(Value_.DownBelowColPos);
		HitBelow_->GetTransform().SetLocalScale(Value_.DownBelowColScale);
		return;
	}
	MsgBoxAssert("잘못된 _State");
}

bool DNFMonster::CanHitAttack1()
{
	if (AttackRangeCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::PlayerHit, CollisionType::CT_OBB2D)
		== true && Attack_1_Timer_.IsTimerOn() == false)
	{
		if (IsZPosHit(static_cast<int>(Player_->GetTransform().GetWorldPosition().y + BotPos_.y)) == true)
		{
			return true;
		}
	}
	return false;
}

int DNFMonster::CalAtt(int _Att)
{
	float Att = static_cast<float>(_Att);
	float RandomRange = Att * 0.5f;
	float CalDamge = GameEngineRandom::MainRandom.RandomFloat(Att - RandomRange, Att + RandomRange);
	return static_cast<int>(CalDamge);
}

void DNFMonster::HPBarUpdate()
{
	MonsterHPData Data;
	Data.CurHP = CurHP_;
	Data.PerHP = PerHP_;
	Data.ID = ID_;
	Data.MaxHP = MaxHP_;
	Data.Type = Value_.Type;
	DNFGlobalValue::CurrentMonsterHP->On();
	DNFGlobalValue::CurrentMonsterHP->SetHPBar(Data);
}

void DNFMonster::TimerCheck(float _DeltaTime)
{
	if (GodTime_.IsTimerOn() == true)
	{
		GodTime_ -= _DeltaTime;
	}
	if (Attack_1_Timer_.IsTimerOn() == true)
	{
		Attack_1_Timer_ -= _DeltaTime;
	}
}

void DNFMonster::InitDefaultValue()
{
	Value_.HitZRange = 15;
	Value_.HitAboveColPos = { 0,-40.0f,-500.0f };
	Value_.HitAboveColScale = { 80.0f,40.0f,1.0f };
	Value_.HitBelowColPos = { 0,-60.0f,-500.0f };
	Value_.HitBelowColScale = { 80.0f,40.0f,1.0f };

	Value_.DownAboveColPos = { 0,-60.0f,-500.0f };
	Value_.DownAboveColScale = { 80.0f,20.0f,1.0f };
	Value_.DownBelowColPos = { 0,-80.0f,-500.0f };
	Value_.DownBelowColScale = { 80.0f,20.0f,1.0f };

	//
	Value_.IdleAboveColPos = { 0,-30.0f,-500.0f };
	Value_.IdleAboveColScale = { 100.0f,40.0f,1.0f };
	Value_.IdleBelowColPos = { 0,-70.0f,-500.0f };
	Value_.IdleBelowColScale = { 100.0f,40.0f,1.0f };

	Value_.Down_Time = 1.3f;
	Value_.Down_God_Time = 0.48f;

	MaxHP_ = 300000;
	PerHP_ = 70000;
	CurHP_ = MaxHP_;

	HitEffectMovePos_ = { 0,-50,0 };

	Attack_1_Scale_ = float4(120, 50, 1);
	Attack_1_Pos_ = float4(40, -45, -500);
}

void DNFMonster::StartDebug()
{
	DNFDebugGUI::AddMutableValue("ShadowPos", &ShadowPos_);
	DNFDebugGUI::AddMutableValue("BotPos", &BotPos_);

	DNFDebugGUI::AddMutableValue("Attack_1_Pos", &Attack_1_Pos_);
	DNFDebugGUI::AddMutableValue("Attack_1_Scale", &Attack_1_Scale_);

	DNFDebugGUI::AddMutableValue("IdleAboveColPos", &Value_.IdleAboveColPos);
	DNFDebugGUI::AddMutableValue("IdleAboveColScl", &Value_.IdleAboveColScale);
	DNFDebugGUI::AddMutableValue("IdleBelowColPos", &Value_.IdleBelowColPos);
	DNFDebugGUI::AddMutableValue("IdleBelowColscl", &Value_.IdleBelowColScale);

	DNFDebugGUI::AddMutableValue("HitAboveColPos", &Value_.HitAboveColPos);
	DNFDebugGUI::AddMutableValue("HitAboveColScl", &Value_.HitAboveColScale);
	DNFDebugGUI::AddMutableValue("HitBelowColPos", &Value_.HitBelowColPos);
	DNFDebugGUI::AddMutableValue("HitBelowColscl", &Value_.HitBelowColScale);

	DNFDebugGUI::AddMutableValue("DownAboveColPos", &Value_.DownAboveColPos);
	DNFDebugGUI::AddMutableValue("DownAboveColScl", &Value_.DownAboveColScale);
	DNFDebugGUI::AddMutableValue("DownBelowColPos", &Value_.DownBelowColPos);
	DNFDebugGUI::AddMutableValue("DownBelowColscl", &Value_.DownBelowColScale);

	DNFDebugGUI::AddMutableValue("HitEffectPos", &HitEffectMovePos_);
}

void DNFMonster::UpdateDebug()
{
	AttackRangeCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	AttackRangeCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
	AttackCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	AttackCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
}

void DNFMonster::InitTransition()
{
	{
		DNFTransition Idle;
		Idle.AddValue("Chase", 70);
		Idle.AddValue("Back", 20);
		Idle.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Idle", Idle));
	}

	{
		DNFTransition Chase;
		Chase.AddValue("Chase", 60);
		Chase.AddValue("Back", 20);
		Chase.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Chase", Chase));
	}

	{
		DNFTransition Attack_1;
		Attack_1.AddValue("Chase", 50);
		Attack_1.AddValue("Back", 30);
		Attack_1.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Attack_1", Attack_1));
	}

	{
		DNFTransition Back;
		Back.AddValue("Chase", 60);
		Back.AddValue("Idle", 30);
		Back.AddValue("Back", -1);
		Transition_.insert(std::make_pair("Back", Back));
	}
}