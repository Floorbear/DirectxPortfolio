#include "PreCompile.h"
#include "BloodLugaru.h"

#include <GameEngineCore/GameEngineStateManager.h>

#include "DNFContentsMinimal.h"

#include "Player_Main.h"
//Player_Utilty를 만들까?

BloodLugaru::BloodLugaru() :
	AniSpeed_(0.12f),
	StateManager_(),
	Player_()
{
}

BloodLugaru::~BloodLugaru()
{
}

void BloodLugaru::Start()
{
	DNFStart();
	MainRenderer_->GetTransform().SetLocalScale(float4(315, 315,1));
	MainRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("bloodlugaru",Lugaru_Idle_Start, Lugaru_Idle_End, AniSpeed_));
	MainRenderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("bloodlugaru", Lugaru_Move_Start, Lugaru_Move_End, AniSpeed_));
	MainRenderer_->ChangeFrameAnimation("Idle");


	StateManager_.CreateStateMember("Idle", std::bind(&BloodLugaru::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::IdleStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Chase", std::bind(&BloodLugaru::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::ChaseStart, this, std::placeholders::_1));

	StateManager_.ChangeState("Idle");
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

	if (length < 100.0f)
	{
		StateManager_.ChangeState("Chase");
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
	DNFDebugGUI::AddValue("Length", length);

	if (length > 200.0f)
	{
		StateManager_.ChangeState("Idle");
	}
}

