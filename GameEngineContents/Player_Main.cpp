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
	 



	//�ƹ�Ÿ����
	AvatarManager_.LinkPlayerToAvatar(this);

	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	
}

void Player_Main::Update(float _DeltaTime)
{
	DNFUpdate();
	ChangeAvatar();
	//z�� ������ ����� ������ �Ͼ
	if (GameEngineInput::GetInst()->IsDown("Z") == true)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Buff);
	}
	//x�� ������ ����� ������ �Ͼ
	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::AutoAttack_0);
	}

	//C�� ������ ����� ������ �Ͼ
	if (GameEngineInput::GetInst()->IsDown("C") == true)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Idle);

	}



	//ī�޶� ���� ����
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
	//1�� ������ ��� �ƹ�Ÿ�� ������ �Ͼ
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
	//2�� ������ ���� �ƹ�Ÿ�� ������ �Ͼ
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
	//3�� ������ ��Ʈ �ƹ�Ÿ�� ������ �Ͼ
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
	//4�� ������ �Ź� �ƹ�Ÿ�� ������ �Ͼ
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
	//5�� ������ ��Ʈ �ƹ�Ÿ�� ������ �Ͼ
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
	//6�� ������ ���� �ƹ�Ÿ�� ������ �Ͼ
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
	//e�� ������ ���� �ƹ�Ÿ�� ������ �Ͼ
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
	//ī�޶� Pos����
	float4 CurPos = GetTransform().GetWorldPosition();
	float4 MapScale = GetDNFLevel()->GetMapScale();
	float Zoom = DNFGlobalValue::CurrentLevel->GetZoom();
	float4 CameraPos;
	CameraPos.z = -500;


	CameraPos.x = GetTransform().GetWorldPosition().x;
	//����
	if (CurPos.x - 640 * Zoom < -MapScale.Half().x)
	{
		CameraPos.x = -MapScale.Half().x + 640 * Zoom;
	}
	//������
	if (CurPos.x + 640 * Zoom > MapScale.Half().x)
	{
		CameraPos.x = MapScale.Half().x - 640 * Zoom;
	}

	CameraPos.y = GetTransform().GetWorldPosition().y;
	//�Ʒ�
	if (CurPos.y - 360 * Zoom < -MapScale.Half().y)
	{
		CameraPos.y = -MapScale.Half().y + 360 * Zoom;
	}
	//��
	if (CurPos.y + 360 * Zoom > MapScale.Half().y)
	{
		CameraPos.y = MapScale.Half().y - 360 * Zoom;
	}


	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(CameraPos);
}
