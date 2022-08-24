#include "PreCompile.h"
#include "BloodLugaru.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineStateManager.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "DNFBackground.h"

#include "Player_Main.h"
//Player_Utilty를 만들까?

BloodLugaru::BloodLugaru() :
	AniSpeed_(0.12f),
	StateManager_(),
	Player_(),
	FindRange_(450.0f),
	AttackRangeCol_(),
	Attack_1_Scale_(),
	Attack_1_Pos_(),
	IsAttack_1_End_(false),
	BackMoveDir_(),
	IsIdleFirst_(true),
	HitAbove_(),
	HitBelow_(),
	Attack_1_Timer_(4.0f),
	Idle_Timer_(3.0f),
	Back_Timer_(3.0f),
	Chase_Timer_(5.0f),
	Hit_Timer_(1.0f),
	PrevHitData_()
{
	InitDefaultValue();
}

BloodLugaru::~BloodLugaru()
{
}

void BloodLugaru::Start()
{
	DNFStart();

	InitCol();

	InitAniNState();


	//Force
	Force_.SetTransfrom(&GetTransform());
	Force_.FrictionX_ = 700.0f;
	Force_.Gravity_ = 1000.0f;

	/*Value_.DownAboveColPos =
		Value_.DownAboveColScale
		Value_.DownBelowColPos =
		Value_.DownBelowColScale*/
	DNFDebugGUI::AddMutableValue("AbovePos", &Value_.DownAboveColPos);
	DNFDebugGUI::AddMutableValue("AboveScale", &Value_.DownAboveColScale);
	DNFDebugGUI::AddMutableValue("BelowPos", &Value_.DownBelowColPos);
	DNFDebugGUI::AddMutableValue("BelowScale", &Value_.DownBelowColScale);
}

void BloodLugaru::Update(float _DeltaTime)
{
	StiffnessUpdate(_DeltaTime);
	if(Stiffness_ <= 0.0f)
	{
		Force_.Update(_DeltaTime*(1+(AirborneTime_*AirborneTime_)*0.01f));
	}


	//공격 쿨타임 카운트
	if (Attack_1_Timer_.IsTimerOn() == true)
	{
		Attack_1_Timer_ -= _DeltaTime;
	}

	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		Player_ = DNFGlobalValue::CurrentLevel->GetPlayer();
		//Hit감지
		HitColCheck();

	}

	StateManager_.Update(_DeltaTime);

	//제한된 범위 밖을 나가지 못하게
	if (DNFGlobalValue::CurrentLevel != nullptr)
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
	DNFUpdate();

}

void BloodLugaru::End()
{
}

void BloodLugaru::InitAniNState()
{
	//애니메이션 추가
	MainRenderer_->GetTransform().SetLocalScale(float4(315, 315, 1));
	ShadowRenderer_->GetTransform().SetLocalScale(float4(315, 315, 1));

	CreateDNFAnimation("Idle", FrameAnimation_DESC("bloodlugaru", Lugaru_Idle_Start, Lugaru_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("bloodlugaru", Lugaru_Move_Start, Lugaru_Move_End, AniSpeed_));
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("bloodlugaru", Lugaru_Attack_1_Start, Lugaru_Attack_1_End, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("bloodlugaru", Lugaru_Hit_Start, Lugaru_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("bloodlugaru", Lugaru_Down_Start, Lugaru_Down_End, AniSpeed_, false));


	//애니메이션 바인드
	MainRenderer_->AnimationBindEnd("Attack_1",
		[&](const FrameAnimation_DESC&)
		{
			//공격이 끝난 직후 로직
			IsAttack_1_End_ = true;
			Attack_1_Timer_.StartTimer();
		}
	);

	//State 추가
	StateManager_.CreateStateMember("Idle", std::bind(&BloodLugaru::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::IdleStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Chase", std::bind(&BloodLugaru::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::ChaseStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Back", std::bind(&BloodLugaru::BackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::BackStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Hit", std::bind(&BloodLugaru::HitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::HitStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Airborne", std::bind(&BloodLugaru::AirborneUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::AirborneStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Down", std::bind(&BloodLugaru::DownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::DownStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Attack_1", std::bind(&BloodLugaru::Attack_1_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::Attack_1_Start, this, std::placeholders::_1),
		std::bind(&BloodLugaru::Attack_1_End, this, std::placeholders::_1));

	StateManager_.ChangeState("Idle");
}

void BloodLugaru::InitCol()
{
	//콜라이더 추가
	AttackRangeCol_ = CreateComponent<GameEngineCollision>("Col");
	AttackRangeCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0, 0.0f, 1.0f, 0.5f));
	Attack_1_Scale_ = float4(120, 50, 1);
	Attack_1_Pos_ = float4(40, -45, -500);
	AttackRangeCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	AttackRangeCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
	AttackRangeCol_->ChangeOrder(ColOrder::Monster);

	//MiddleHit
	HitAbove_ = CreateComponent<GameEngineCollision>("Middle");
	HitAbove_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
	HitAbove_->GetTransform().SetLocalPosition({ 0,-30.0f,-500.0f });
	HitAbove_->GetTransform().SetLocalScale({ 100.0f,40.0f,1.0f });
	HitAbove_->ChangeOrder(ColOrder::MonsterHit);


	//BottomHit
	HitBelow_ = CreateComponent<GameEngineCollision>("Bottom");
	HitBelow_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0.0f, 1.0f, 0.0f, 0.5f));
	HitBelow_->GetTransform().SetLocalPosition({ 0,-70.0f,-500.0f });
	HitBelow_->GetTransform().SetLocalScale({ 100.0f,40.0f,1.0f });
	HitBelow_->ChangeOrder(ColOrder::MonsterHit);

}

void BloodLugaru::IdleStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Idle");
	ChangeHitColTrans("Idle");

	Idle_Timer_ = GameEngineRandom::MainRandom.RandomFloat(1.0f, 3.0f);
	Idle_Timer_.StartTimer();

}

void BloodLugaru::IdleUpdate(float _DeltaTime,const StateInfo _Info )
{
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();

	float length = DNFMath::Length(PlayerPos,thisPos);

	if (length > FindRange_)
	{		
		IsIdleFirst_ = true;
		return;
	}

	//FindRange에 접근하면 바로 상태 판단에 들어간다.
	if (IsIdleFirst_ == true)
	{
		IsIdleFirst_ = false;
		int Random = GameEngineRandom::MainRandom.RandomInt(0, 100);
		if (Random <= 70)
		{
			StateManager_.ChangeState("Chase");
			return;
		}
		else if (Random <= 90)
		{
			StateManager_.ChangeState("Back");
			return;
		}
		else
		{
			StateManager_.ChangeState("Idle");
			return;
		}
	}

	//상태 판단

	//공격범위 내에 접근하면 바로 공격
	if (AttackRangeCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::Player, CollisionType::CT_OBB2D)
		== true && Attack_1_Timer_.IsTimerOn() == false)
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
		int Random = GameEngineRandom::MainRandom.RandomInt(0, 100);
		if (Random <= 70)
		{
			StateManager_.ChangeState("Chase");
			return;
		}
		else if (Random <= 90)
		{
			StateManager_.ChangeState("Back");
			return;
		}
		else
		{
			StateManager_.ChangeState("Idle");
			return;
		}
	}
}

void BloodLugaru::ChaseStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Move");
	Chase_Timer_ = GameEngineRandom::MainRandom.RandomFloat(2.0f, 5.0f);
	Chase_Timer_.StartTimer();
}

void BloodLugaru::ChaseUpdate(float _DeltaTime, const StateInfo _Info)
{
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();

	float length = DNFMath::Length(PlayerPos, thisPos);


	//공격범위 내에 접근하면 바로 공격
	if (AttackRangeCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::Player, CollisionType::CT_OBB2D)
		== true && Attack_1_Timer_.IsTimerOn() == false)
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
		int Random = GameEngineRandom::MainRandom.RandomInt(0, 100);
		if (Random <= 60)
		{
			StateManager_.ChangeState("Chase");
			return;
		}
		else if (Random <= 80)
		{
			StateManager_.ChangeState("Back");
			return;
		}
		else
		{
			StateManager_.ChangeState("Idle");
			return;
		}
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

void BloodLugaru::Attack_1_Start(const StateInfo _Info)
{
	ChangeDNFAnimation("Attack_1");
}

void BloodLugaru::Attack_1_Update(float _DeltaTime, const StateInfo _Info)
{
	if (IsAttack_1_End_ == true)
	{
		int Random = GameEngineRandom::MainRandom.RandomInt(0, 100);
		if (Random <= 40)
		{
			StateManager_.ChangeState("Chase");
			return;
		}
		else if (Random <= 80)
		{
			StateManager_.ChangeState("Back");
			return;
		}
		else
		{
			StateManager_.ChangeState("Idle");
			return;
		}
	}
}

void BloodLugaru::Attack_1_End(const StateInfo _Info)
{
	IsAttack_1_End_ = false;
}

void BloodLugaru::BackStart(const StateInfo _Info)
{

	ChangeDNFAnimation("Move");

	Back_Timer_ = GameEngineRandom::MainRandom.RandomFloat(1.0f,3.0f);
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

void BloodLugaru::BackUpdate(float _DeltaTime, const StateInfo _Info)
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
	if (AttackRangeCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::Player, CollisionType::CT_OBB2D)
		== true && Attack_1_Timer_.IsTimerOn() == false)
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
		int Random = GameEngineRandom::MainRandom.RandomInt(0, 100);
		if (Random <= 60)
		{
			StateManager_.ChangeState("Chase");
			return;
		}
		else if (Random <= 90)
		{
			StateManager_.ChangeState("Idle");
			return;
		}
		else
		{
			StateManager_.ChangeState("Back");
			return;
		}
	}

	

	GetTransform().SetWorldMove(BackMoveDir_ * 100.0f * _DeltaTime);
}

void BloodLugaru::HitStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Hit");
	ChangeHitColTrans("Hit");
	Hit_Timer_.StartTimer();
	
	//플레이어를 마주보는 방향으로 Flip
	FlipX(-Player_->GetDirX());
	Force_.ForceX_ = -PrevHitData_.XForce;


}

void BloodLugaru::HitUpdate(float _DeltaTime, const StateInfo _Info)
{
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

void BloodLugaru::AirborneStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Hit");
	ChangeHitColTrans("Hit");
	//플레이어를 마주보는 방향으로 Flip
	FlipX(-Player_->GetDirX());
	Force_.ForceX_ = -PrevHitData_.XForce;
	

	GetTransform().SetLocalMove(float4(0, Force_.ForceY_ * GameEngineTime::GetDeltaTime()));
	Force_.OnGravity();
	OnAir_ = true;
}

void BloodLugaru::AirborneUpdate(float _DeltaTime, const StateInfo _Info)
{
	//경직
	//추락
	AirborneTime_ += _DeltaTime;
	float CurYPos = GetTransform().GetWorldPosition().y;
	if (CurYPos <= GroundYPos_)
	{
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		//Down 상태 Bounce
		OnAir_ = true;
		Force_.ForceY_ = 200.0f;
		AirborneTime_ = 0.0f;
		Force_.OnGravity();
		PrevHitData_ = {};
		StateManager_.ChangeState("Down");
		return;
	}
}

void BloodLugaru::DownStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Down");
	ChangeHitColTrans("Down");
	Down_Timer_.StartTimer(Value_.Down_Time);

	//플레이어를 마주보는 방향으로 Flip
	FlipX(-Player_->GetDirX());
	Force_.ForceX_ = -150.0f;

	GetTransform().SetLocalMove(float4(0, Force_.ForceY_ * GameEngineTime::GetDeltaTime()));

}

void BloodLugaru::DownUpdate(float _DeltaTime, const StateInfo _Info)
{
	AirborneTime_ += 5.0f * _DeltaTime;
	float CurYPos = GetTransform().GetWorldPosition().y;

	if (CurYPos <= GroundYPos_)
	{
		//GroundYPos 아래로 떨어지지 않게 고정시키기
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		//이전에 받은 공격 데이터 초기화
		PrevHitData_ = {};

		Down_Timer_ -= _DeltaTime;
		if (Down_Timer_.IsTimerOn() == false)
		{
			OnAir_ = false;
			Force_.ForceY_ = 0.0f;
			AirborneTime_ = 0.0f;
			Force_.OffGravity();
			PrevHitData_ = {};
			StateManager_.ChangeState("Idle");
			return;
		}
	}
}

void BloodLugaru::HitColCheck()
{
	HitBelow_->IsCollision(CollisionType::CT_OBB2D, ColOrder::PlayerAttack, CollisionType::CT_OBB2D,
		std::bind(&BloodLugaru::BelowHitCheck, this, std::placeholders::_1, std::placeholders::_2));

	HitAbove_->IsCollision(CollisionType::CT_OBB2D, ColOrder::PlayerAttack, CollisionType::CT_OBB2D,
		std::bind(&BloodLugaru::AboveHitCheck, this, std::placeholders::_1, std::placeholders::_2));
}

bool BloodLugaru::HitCheck(AttackType _Type)
{
	Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
	AttackData Data = Player->CurAttackData_;

	//Hit충돌체와 공격타입이 불일치하면 리턴
	if (_Type != Data.Type)
	{
		return false;
	}


	//같은 공격에 여러번 충돌 방지
	if (Data.AttackName == PrevHitData_.AttackName && Data.AttCount <= PrevHitData_.AttCount)
	{
		return false;
	}

	//현재 받은 공격을 저장
	PrevHitData_ = Data;

	//공중공격이 아닌 경우
	if (OnAir_ == false && Data.YForce <= 0.0f)
	{
		GiveAndRecevieStiffness(PrevHitData_, Player);
		if (StateManager_.GetCurStateStateName() == "Down")
		{
			ResetDNFAnimation();
			StateManager_.ChangeState("Down");
		}
		else
		{
			StateManager_.ChangeState("Hit");
		}
		return true;
	}

	//여기서부터 채공상태

	//최초의 공중에 뜸 상태 일때
	if (OnAir_ == false)
	{
		GroundYPos_ = GetTransform().GetWorldPosition().y;
		Force_.ForceY_ = PrevHitData_.YForce;
		AirborneTime_ = 0.0f;
		GiveAndRecevieStiffness(PrevHitData_, Player);
		//Down 상태 분기
		if (StateManager_.GetCurStateStateName() == "Down")
		{
			ResetDNFAnimation();
			Force_.ForceY_ = PrevHitData_.YForce * 0.5f;
			StateManager_.ChangeState("Down");
		}
		else
		{
			StateManager_.ChangeState("Airborne");
		}
		return true;
	}
	else//공중의 뜸 상태에서 공격을 받은경우
	{
		GiveAndRecevieStiffness(PrevHitData_, Player);
		Force_.ForceY_ = PrevHitData_.YForce;
		if (StateManager_.GetCurStateStateName() == "Down")
		{
			ResetDNFAnimation();
			Force_.ForceY_ = PrevHitData_.YForce * 0.5f;
			StateManager_.ChangeState("Down");
		}
		else
		{
			StateManager_.ChangeState("Airborne");
		}
		return true;
	}
}

bool BloodLugaru::AboveHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	return HitCheck(AttackType::Above);
}

bool BloodLugaru::BelowHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	return HitCheck(AttackType::Below);
}

void BloodLugaru::ChangeHitColTrans(std::string _State)
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
		HitAbove_->GetTransform().SetLocalPosition({ 0,-30.0f,-500.0f });
		HitAbove_->GetTransform().SetLocalScale({ 100.0f,40.0f,1.0f });
		HitBelow_->GetTransform().SetLocalPosition({ 0,-70.0f,-500.0f });
		HitBelow_->GetTransform().SetLocalScale({ 100.0f,40.0f,1.0f });
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

void BloodLugaru::InitDefaultValue()
{
	Value_.HitAboveColPos = { 0,-40.0f,-500.0f };
	Value_.HitAboveColScale = { 80.0f,40.0f,1.0f };
	Value_.HitBelowColPos = { 0,-60.0f,-500.0f };
	Value_.HitBelowColScale = { 80.0f,40.0f,1.0f };

	Value_.DownAboveColPos = { 0,-60.0f,-500.0f };
	Value_.DownAboveColScale = { 80.0f,20.0f,1.0f };
	Value_.DownBelowColPos = { 0,-80.0f,-500.0f };
	Value_.DownBelowColScale = { 80.0f,20.0f,1.0f };

	Value_.Down_Time = 1.3f;
}

