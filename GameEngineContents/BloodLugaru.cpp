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
	Attack_1_Time_(0.0f),
	Temp_(),
	BackMoveDir_(),
	IsIdleFirst_(true)
{
	CurTime_.insert(std::make_pair("Attack_1", 0.0f));
	CurTime_.insert(std::make_pair("IdleIter", 0.0f));
	CurTime_.insert(std::make_pair("ChaseIter", 0.0f));
	CurTime_.insert(std::make_pair("BackIter", 0.0f));



	DefaultTime_.insert(std::make_pair("Attack_1", 4.0f));
	DefaultTime_.insert(std::make_pair("IdleIter", 3.0f));
	DefaultTime_.insert(std::make_pair("ChaseIter", 5.0f));
	DefaultTime_.insert(std::make_pair("BackIter", 3.0f));



	FloatValue_.insert(std::make_pair("MoveSpeed", 100.0f));
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

	//애니메이션 바인드
	MainRenderer_->AnimationBindEnd("Attack_1",
		[&](const FrameAnimation_DESC&) 
		{
			//공격이 끝난 직후 로직
			IsAttack_1_End_ = true;
			CurTime_["Attack_1"] = 4.0f;
		}
	);

	//State 추가
	StateManager_.CreateStateMember("Idle", std::bind(&BloodLugaru::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::IdleStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Chase", std::bind(&BloodLugaru::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::ChaseStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Back", std::bind(&BloodLugaru::BackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&BloodLugaru::BackStart, this, std::placeholders::_1));

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


}

void BloodLugaru::Update(float _DeltaTime)
{
	DNFUpdate();

	//공격 쿨타임 카운트
	if (CurTime_["Attack_1"] > 0.0f)
	{
		CurTime_["Attack_1"] -= _DeltaTime;
	}

	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		Player_ = DNFGlobalValue::CurrentLevel->GetPlayer();
	}
	StateManager_.Update(_DeltaTime);

	//제한된 범위 밖을 나가지 못하게
	if (DNFGlobalValue::CurrentLevel != nullptr)
	{

		float4 MapScale = GetDNFLevel()->GetMapScale();
		float4 MonsterBotPos = GetTransform().GetWorldPosition();
		MonsterBotPos.y = -MonsterBotPos.y - BotPos_.y;

		GameEngineTexture* ColMap = DNFGlobalValue::CurrentLevel->GetBackground()->GetColRenderer()->GetCurTexture();


		if (ColMap->GetPixelToFloat4(static_cast<int>(MonsterBotPos.x), static_cast<int>(MonsterBotPos.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			GetTransform().SetWorldPosition(PrevPos_);
		}

		PrevPos_ = GetTransform().GetWorldPosition();
		 
		//TemValue += _DeltaTime;
		//TemValue1 += _DeltaTime*2.0f;
	}

}

void BloodLugaru::End()
{
}

void BloodLugaru::IdleStart(const StateInfo _Info)
{
	ChangeDNFAnimation("Idle");

	CurTime_["IdleIter"] = GameEngineRandom::MainRandom.RandomFloat(DefaultTime_["IdleIter"]-2.0f, DefaultTime_["IdleIter"]);

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
	if (CurTime_["IdleIter"] > 0.0f)
	{
		CurTime_["IdleIter"] -= _DeltaTime;
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
	CurTime_["ChaseIter"] = GameEngineRandom::MainRandom.RandomFloat(DefaultTime_["ChaseIter"] - 3.0f, DefaultTime_["ChaseIter"]);
}

void BloodLugaru::ChaseUpdate(float _DeltaTime, const StateInfo _Info)
{
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();

	float length = DNFMath::Length(PlayerPos, thisPos);


	//공격범위 내에 접근하면 바로 공격
	if (AttackRangeCol_->IsCollision(CollisionType::CT_OBB2D, ColOrder::Player, CollisionType::CT_OBB2D)
		== true && CurTime_["Attack_1"] < 0.01f)
	{
		StateManager_.ChangeState("Attack_1");
		return;
	}

	//플레이어와 너무 가까우면 후퇴
	if (length < 20.0f)
	{
		StateManager_.ChangeState("Back");
		return;
	}

	//상태 판단
	if (CurTime_["ChaseIter"] > 0.0f)
	{
		CurTime_["ChaseIter"] -= _DeltaTime;
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
	GetTransform().SetWorldMove(MoveDir * FloatValue_["MoveSpeed"] * _DeltaTime);
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

	CurTime_["BackIter"] = GameEngineRandom::MainRandom.RandomFloat(DefaultTime_["BackIter"] - 2.0f, DefaultTime_["BackIter"]);

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
		== true && CurTime_["Attack_1"] < 0.01f)
	{
		StateManager_.ChangeState("Attack_1");
		return;
	}

	if (CurTime_["BackIter"] > 0.0f)
	{
		CurTime_["BackIter"] -= _DeltaTime;
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

	

	GetTransform().SetWorldMove(BackMoveDir_ * FloatValue_["MoveSpeed"] * _DeltaTime);
}

bool BloodLugaru::AttackColCheck(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	return true;
}

