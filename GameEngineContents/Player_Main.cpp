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
	Toggle1_(0),
	Toggle2_(0),
	Toggle3_(0),
	Toggle4_(0),
	Toggle5_(0),
	Toggle6_(0),
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

}

Player_Main::~Player_Main()
{
}

void Player_Main::Start()
{
	DNFStart();
	float Idle_Iter = 0.2f;
	float Attack_Iter = 0.08f;
	BotPos_ = { 0,-88.0f };
	InitCol();


	//아바타생성
	AvatarManager_.LinkPlayerToAvatar(this);

	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	
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
	ChangeAvatar();
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



	if (GameEngineInput::GetInst()->IsPress("Right") == true)
	{
		GetTransform().SetLocalMove(float4::RIGHT * _DeltaTime * 200.0f);
		AvatarManager_.ChangeMotion(PlayerAnimations::Move);
		GetTransform().PixLocalPositiveX();
	}

	if (GameEngineInput::GetInst()->IsPress("Left") == true)
	{
		GetTransform().SetLocalMove(float4::LEFT * _DeltaTime * 200.0f);
		AvatarManager_.ChangeMotion(PlayerAnimations::Move);
		GetTransform().PixLocalNegativeX();
		ShadowUpdate();
	}
	if (GameEngineInput::GetInst()->IsPress("Up") == true)
	{
		GetTransform().SetLocalMove(float4::UP * _DeltaTime * 100.0f);
		AvatarManager_.ChangeMotion(PlayerAnimations::Move);
	}
	if (GameEngineInput::GetInst()->IsPress("Down") == true)
	{
		GetTransform().SetLocalMove(float4::DOWN * _DeltaTime * 100.0f);
		AvatarManager_.ChangeMotion(PlayerAnimations::Move);
	}

	if (GameEngineInput::GetInst()->IsUp("Left") == true || GameEngineInput::GetInst()->IsUp("Right") == true
		|| GameEngineInput::GetInst()->IsUp("Down") == true || GameEngineInput::GetInst()->IsUp("Up") == true)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
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

void Player_Main::ChangeAvatar()
{
	//1를 누르면 헤어 아바타의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("1") == true)
	{
		if (Toggle1_ < 1)
		{
			Toggle1_++;
		}
		else
		{
			Toggle1_ = 0;
		}

		if (Toggle1_ == 0)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Hair);

		}
		else if (Toggle1_ == 1)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Hair);
		}

	}
	//2를 누르면 바지 아바타의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("2") == true)
	{
		if (Toggle2_ < 1)
		{
			Toggle2_++;
		}
		else
		{
			Toggle2_ = 0;
		}

		if (Toggle2_ == 0)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Pants);

		}
		else if (Toggle2_ == 1)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Pants);
		}

	}
	//3를 누르면 코트 아바타의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("3") == true)
	{
		if (Toggle3_ < 2)
		{
			Toggle3_++;
		}
		else
		{
			Toggle3_ = 0;
		}

		if (Toggle3_ == 0)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Coat);

		}
		else if (Toggle3_ == 1)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Coat);
		}
		else if (Toggle3_ == 2)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Dog, AvatarParts::Coat);
		}
	}
	//4를 누르면 신발 아바타의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("4") == true)
	{
		if (Toggle4_ < 2)
		{
			Toggle4_++;
		}
		else
		{
			Toggle4_ = 0;
		}

		if (Toggle4_ == 0)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Shoes);

		}
		else if (Toggle4_ == 1)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Shoes);
		}
		else if (Toggle4_ == 2)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Dog, AvatarParts::Shoes);
		}
	}
	//5를 누르면 벨트 아바타의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("5") == true)
	{
		if (Toggle5_ < 2)
		{
			Toggle5_++;
		}
		else
		{
			Toggle5_ = 0;
		}

		if (Toggle5_ == 0)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Belt);

		}
		else if (Toggle5_ == 1)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Belt);
		}
		else if (Toggle5_ == 2)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Dog, AvatarParts::Belt);
		}
	}
	//6를 누르면 모자 아바타의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("6") == true)
	{
		if (Toggle6_ < 2)
		{
			Toggle6_++;
		}
		else
		{
			Toggle6_ = 0;
		}

		if (Toggle6_ == 0)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Cap);

		}
		else if (Toggle6_ == 1)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Danjin, AvatarParts::Cap);
		}
		else if (Toggle6_ == 2)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Dog, AvatarParts::Cap);
		}
	}
	//e를 누르면 무기 아바타의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("E") == true)
	{
		if (Toggle3_ == false)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Weapon);
			Toggle3_ = true;
		}
		else
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Weapon);
			Toggle3_ = false;
		}

	}
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
