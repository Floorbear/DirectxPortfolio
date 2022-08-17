#include "PreCompile.h"
#include "Player_Main.h"

#include "DNFDefineList.h"
#include "DNFGlobalValue.h"

#include "DNFLevel.h"
#include "DNFBackground.h"
#include "DNFDebugGUI.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


Player_Main::Player_Main() :
	UIRenderer_(nullptr),
	WeaponRenderer_b_(),
	WeaponRenderer_c_(),
	CoatRenderer_a_(),
	CoatRenderer_b_(),
	CoatRenderer_c_(),
	CoatRenderer_d_(),
	PantsRenderer_a_(),
	PantsRenderer_b_(),
	PantsRenderer_d_(),
	CapRenderer_a_(),
	CapRenderer_b_(),
	CapRenderer_c_(),
	HairRenderer_a_(),
	HairRenderer_d_(),
	BeltRenderer_c_(),
	BeltRenderer_d_(),
	ShoesRenderer_a_(),
	ShoesRenderer_b_(),
	MiddleAttackCol_(),
	AttackCount_()
{
	FloatValue_.insert(std::make_pair("MoveSpeed", 200.0f));
}

Player_Main::~Player_Main()
{
}

void Player_Main::Start()
{
	DNFStart();
	BotPos_ = { 0,-88.0f };
	

	InitCol();

	//아바타생성
	AvatarManager_.LinkPlayerToAvatar(this);
	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);

	//스테이트 초기화
	StateManager_.CreateStateMember("Idle", std::bind(&Player_Main::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::IdleStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Move", std::bind(&Player_Main::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::MoveStart, this, std::placeholders::_1));
	

	StateManager_.ChangeState("Idle");

	//애니메이션 함수 초기화
	MainRenderer_->AnimationBindFrame("AutoAttack_0", 
		[&](const FrameAnimation_DESC& _Desc) 
		{
			if (_Desc.CurFrame == AutoAttack_0_Start + 3)
			{
				MiddleAttackCol_->On();
				MiddleAttackCol_->GetTransform().SetLocalScale(float4(120, 70, 1));
				MiddleAttackCol_->GetTransform().SetLocalPosition(float4(50, -20, -500));
				AttackCount_++;
			}
			else if (_Desc.CurFrame == AutoAttack_0_Start + 7)
			{
				MiddleAttackCol_->Off();
				AttackCount_ = 0;
			}
		});
}

void Player_Main::Update(float _DeltaTime)
{
	DNFUpdate();
	DNFDebugGUI::AddValue("PlayerState", StateManager_.GetCurStateStateName());
	StateManager_.Update(_DeltaTime);
	//z를 누르면 모션의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("Z") == true)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Buff);
	}
	//x를 누르면 모션의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::AutoAttack_0);
	}

	//C를 누르면 모션의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("C") == true)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	}



	if (GameEngineInput::GetInst()->IsUp("Left") == true || GameEngineInput::GetInst()->IsUp("Right") == true
		|| GameEngineInput::GetInst()->IsUp("Down") == true || GameEngineInput::GetInst()->IsUp("Up") == true)
	{
		
	}

	//제한된 범위 밖을 나가지 못하게
	if (DNFGlobalValue::CurrentLevel != nullptr)
	{

		float4 MapScale = GetDNFLevel()->GetMapScale();
		float4 PlayerPosBot = GetTransform().GetWorldPosition();
		PlayerPosBot.y = -PlayerPosBot.y + 88.0f;

		GameEngineTexture* ColMap = DNFGlobalValue::CurrentLevel->GetBackground()->GetColRenderer()->GetCurTexture();
		
		
		if (ColMap->GetPixelToFloat4(static_cast<int>(PlayerPosBot.x), static_cast<int>(PlayerPosBot.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			GetTransform().SetWorldPosition(PrevPos_);
		}
		
		PrevPos_ = GetTransform().GetWorldPosition();


		ChaseCamera();
	}



	
}

void Player_Main::End()
{
}


void Player_Main::ChaseCamera()
{
	//카메라 Pos관련
	float4 CurPos = GetTransform().GetWorldPosition();
	float4 MapScale = GetDNFLevel()->GetMapScale();
	float Zoom = DNFGlobalValue::CurrentLevel->GetZoom();
	float4 CameraPos;
	CameraPos.z = -500;


	CameraPos.x = GetTransform().GetWorldPosition().x;
	//왼쪽
	if (CurPos.x - 640 * Zoom < 0.0f)
	{
		CameraPos.x =  640 * Zoom;
	}
	//오른쪽
	if (CurPos.x + 640 * Zoom > MapScale.x)
	{
		CameraPos.x = MapScale.x - 640 * Zoom;
	}

	CameraPos.y = GetTransform().GetWorldPosition().y;
	//아래
	if (CurPos.y - 360 * Zoom < -MapScale.y)
	{
		CameraPos.y = -MapScale.y + 360 * Zoom;
	}
	//위
	if (CurPos.y + 360 * Zoom > 0.0f)
	{
		CameraPos.y =  - 360 * Zoom;
	}


	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(CameraPos);
}

void Player_Main::InitCol()
{
	//테스트용 콜라이더
	GameEngineCollision* Col = CreateComponent<GameEngineCollision>("Col");
	Col->SetDebugSetting(CollisionType::CT_OBB2D, float4(0, 1.0f, 0, 0.5f));
	Col->GetTransform().SetLocalScale(float4(100, 100, 1));
	Col->GetTransform().SetLocalMove(float4(0, 0, -500));
	Col->ChangeOrder(ColOrder::Player);

	//MiddleAttack 콜라이더
	MiddleAttackCol_ = CreateComponent<GameEngineCollision>("MiddleAttack");
	MiddleAttackCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0, 1.0f, 0, 0.5f));
	MiddleAttackCol_->ChangeOrder(ColOrder::PlayerAttackMiddle);
	MiddleAttackCol_->Off();
}


