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
	Temp_(),
	BackMoveDir_(),
	IsIdleFirst_(true),
	HitMiddle_(),
	Attack_1_Timer_(4.0f),
	Idle_Timer_(3.0f),
	Back_Timer_(3.0f),
	Chase_Timer_(5.0f),
	Hit_Timer_(1.0f),
	PrevHitData_()
{
}

BloodLugaru::~BloodLugaru()
{
}

void BloodLugaru::Start()
{
	DNFStart();
	//애니메이션 추가
	MainRenderer_->GetTransform().SetLocalScale(float4(315, 315, 1));
	ShadowRenderer_->GetTransform().SetLocalScale(float4(315, 315, 1));

	CreateDNFAnimation("Idle", FrameAnimation_DESC("bloodlugaru", Lugaru_Idle_Start, Lugaru_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("bloodlugaru", Lugaru_Move_Start, Lugaru_Move_End, AniSpeed_));
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("bloodlugaru", Lugaru_Attack_1_Start, Lugaru_Attack_1_End, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("bloodlugaru", Lugaru_Hit_Start, Lugaru_Hit_End, AniSpeed_, false));


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

	StateManager_.CreateStateMember("Attack_1", std::bind(&BloodLugaru::Attack_1_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::Attack_1_Start, this, std::placeholders::_1),
		 std::bind(&BloodLugaru::Attack_1_End, this, std::placeholders::_1));

	StateManager_.ChangeState("Idle");



	//콜라이더 추가
	AttackRangeCol_ = CreateComponent<GameEngineCollision>("Col");
	AttackRangeCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0, 0.0f, 1.0f, 0.5f));
	Attack_1_Scale_ = float4(120, 50, 1);
	Attack_1_Pos_ = float4(40, -45, -500);
	AttackRangeCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	AttackRangeCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
	AttackRangeCol_->ChangeOrder(ColOrder::Monster);

	//MiddleHit
	HitMiddle_ = CreateComponent<GameEngineCollision>("Middle");
	HitMiddle_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
	HitMiddle_->GetTransform().SetLocalPosition({ 0,-50.0f,-500.0f });
	HitMiddle_->GetTransform().SetLocalScale({ 100.0f,30.0f,1.0f });
	HitMiddle_->ChangeOrder(ColOrder::MonsterHitMiddle);

	//Force
	Force_.SetTransfrom(&GetTransform());
	Force_.FrictionX_ = 700.0f;
	Force_.Gravity_ = 1000.0f;
	DNFDebugGUI::AddMutableValue("Gravity", &Force_.Gravity_);

}

void BloodLugaru::Update(float _DeltaTime)
{
	if (Stiffness_ > 0.0f)
	{
		Stiffness_ -= _DeltaTime;
		_DeltaTime = 0.0f;
		if (Stiffness_ <= 0)
		{
			Stiffness_ = 0.0f;
		}
	}
	else
	{
		Force_.Update(_DeltaTime);
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
		HitMiddle_->IsCollision(CollisionType::CT_OBB2D, ColOrder::PlayerAttack, CollisionType::CT_OBB2D,
			[&](GameEngineCollision* _This, GameEngineCollision* _Other)
			{
				Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
				AttackData Data = Player->CurAttackData_;

				//같은 공격에 여러번 충돌 방지
				if (Data.AttackName == PrevHitData_.AttackName && Data.AttCount <= PrevHitData_.AttCount)
				{
					return false;
				}

				PrevHitData_ = Data;

				if (OnAir_ == false && Data.YForce <= 0.0f)
				{
					//PrevData
					Stiffness_ += 0.1f;
					StateManager_.ChangeState("Hit");
					return true;
				}

				//여기서부터 채공상태

				//최초의 공중에 뜸 상태 일때
				if (OnAir_ == false)
				{
					GroundYPos_ = GetTransform().GetWorldPosition().y;
					Force_.ForceY_ = PrevHitData_.YForce;
					StateManager_.ChangeState("Airborne");
					return true;
				}
				else//공중의 뜸 상태에서 공격을 받은경우
				{
					Stiffness_ += 0.1f;
					Force_.ForceY_ = PrevHitData_.YForce;
					StateManager_.ChangeState("Airborne");
					return true;
				}

				



				
			});
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

void BloodLugaru::IdleStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Idle");

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
	float CurYPos = GetTransform().GetWorldPosition().y;
	if (CurYPos <= GroundYPos_)
	{
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		OnAir_ = false;
		Force_.ForceY_ = 0.0f;
		Force_.OffGravity();
		PrevHitData_ = {};
		StateManager_.ChangeState("Idle");
		return;
	}
}

bool BloodLugaru::AttackColCheck(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	return true;
}

