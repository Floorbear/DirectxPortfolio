#include "PreCompile.h"
#include "Player_Main.h"

#include "DNFDefineList.h"
#include "DNFGlobalValue.h"

#include "DNFLevel.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

Player_Main::Player_Main():
	Toggle1_(0),
	Toggle2_(0),
	Toggle3_(0),
	Toggle4_(0),
	Toggle5_(0),
	Toggle6_(0),
	UIRenderer_(nullptr)
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
	 



	//아바타생성
	AvatarManager_.LinkPlayerToAvatar(this);

	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	
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



	//카메라 제한 관련
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



	ChaseCamera();
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
	if (CurPos.x - 640 * Zoom < -MapScale.Half().x)
	{
		CameraPos.x = -MapScale.Half().x + 640 * Zoom;
	}
	//오른쪽
	if (CurPos.x + 640 * Zoom > MapScale.Half().x)
	{
		CameraPos.x = MapScale.Half().x - 640 * Zoom;
	}

	CameraPos.y = GetTransform().GetWorldPosition().y;
	//아래
	if (CurPos.y - 360 * Zoom < -MapScale.Half().y)
	{
		CameraPos.y = -MapScale.Half().y + 360 * Zoom;
	}
	//위
	if (CurPos.y + 360 * Zoom > MapScale.Half().y)
	{
		CameraPos.y = MapScale.Half().y - 360 * Zoom;
	}


	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(CameraPos);
}
