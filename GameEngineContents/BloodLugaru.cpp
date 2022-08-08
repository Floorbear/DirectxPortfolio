#include "PreCompile.h"
#include "BloodLugaru.h"

#include <GameEngineCore/GameEngineStateManager.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"

#include "Player_Main.h"
//Player_Utilty를 만들까?

BloodLugaru::BloodLugaru() :
	AniSpeed_(0.12f),
	StateManager_(),
	Player_(),
	FindRange_(270.0f),
	AttackRangeCol_(),
	Attack_1_Scale_(),
	Attack_1_Pos_()
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
	MainRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("bloodlugaru", Lugaru_Idle_Start, Lugaru_Idle_End, AniSpeed_));
	MainRenderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("bloodlugaru", Lugaru_Move_Start, Lugaru_Move_End, AniSpeed_));
	MainRenderer_->CreateFrameAnimationFolder("Attack_1", FrameAnimation_DESC("bloodlugaru", Lugaru_Attack_1_Start, Lugaru_Attack_1_End, AniSpeed_));
	MainRenderer_->ChangeFrameAnimation("Idle");




	//State 추가
	StateManager_.CreateStateMember("Idle", std::bind(&BloodLugaru::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::IdleStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Chase", std::bind(&BloodLugaru::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::ChaseStart, this, std::placeholders::_1));

	StateManager_.ChangeState("Idle");


	//콜라이더 추가
	AttackRangeCol_ = CreateComponent<GameEngineCollision>("Col");
	AttackRangeCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0, 0.0f, 1.0f, 0.5f));
	Attack_1_Scale_ = float4(120, 40, 1);
	Attack_1_Pos_ = float4(80, -40, -500);
	AttackRangeCol_->GetTransform().SetLocalScale(Attack_1_Scale_);
	AttackRangeCol_->GetTransform().SetLocalPosition(Attack_1_Pos_);
	AttackRangeCol_->ChangeOrder(ColOrder::Monster);
	DNFDebugGUI::AddMutableValue("Scale", &Attack_1_Scale_);
	DNFDebugGUI::AddMutableValue("Pos", &Attack_1_Pos_);
}

void BloodLugaru::Update(float _DeltaTime)
{
	DNFUpdate();
	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		Player_ = DNFGlobalValue::CurrentLevel->GetPlayer();
	}
	StateManager_.Update(_DeltaTime);

	

}

void BloodLugaru::End()
{
}

void BloodLugaru::IdleStart(const StateInfo _Info)
{
	MainRenderer_->ChangeFrameAnimation("Idle");

}

void BloodLugaru::IdleUpdate(float _DeltaTime,const StateInfo _Info )
{
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();

	float length = DNFMath::Length(PlayerPos,thisPos);
	DNFDebugGUI::AddValue("Length", length);

	if (length < FindRange_)
	{
		StateManager_.ChangeState("Chase");
		return;
	}

}

void BloodLugaru::ChaseStart(const StateInfo _Info)
{
	MainRenderer_->ChangeFrameAnimation("Move");
}

void BloodLugaru::ChaseUpdate(float _DeltaTime, const StateInfo _Info)
{
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();

	float length = DNFMath::Length(PlayerPos, thisPos);

	if (length > FindRange_)
	{
		StateManager_.ChangeState("Idle");
		return;
	}

	if (AttackRangeCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::Player, CollisionType::CT_OBB2D)
		== true)
	{
		MainRenderer_->ChangeFrameAnimation("Attack_1");
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

bool BloodLugaru::AttackColCheck(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	return true;
}

