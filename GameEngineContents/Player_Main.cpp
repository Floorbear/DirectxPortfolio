#include "PreCompile.h"
#include "DNFDefineList.h"
#include "Player_Main.h"

#include <GameEngineCore/GameEngineLevel.h>

Player_Main::Player_Main():
	Toggle1_(0),
	Toggle2_(0),
	Toggle3_(0),
	Toggle4_(0),
	Toggle5_(0),
	Toggle6_(0)
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
	 
	//Key 초기화
	GameEngineInput::GetInst()->CreateKey("1", 0x31);
	GameEngineInput::GetInst()->CreateKey("2", 0x32);
	GameEngineInput::GetInst()->CreateKey("3", 0x33);
	GameEngineInput::GetInst()->CreateKey("4", 0x34);
	GameEngineInput::GetInst()->CreateKey("5", 0x35);
	GameEngineInput::GetInst()->CreateKey("6", 0x36);



	GameEngineInput::GetInst()->CreateKey("Z", 'Z');
	GameEngineInput::GetInst()->CreateKey("X", 'X');
	GameEngineInput::GetInst()->CreateKey("C", 'C');
	GameEngineInput::GetInst()->CreateKey("Q", 'Q');
	GameEngineInput::GetInst()->CreateKey("W", 'W');
	GameEngineInput::GetInst()->CreateKey("E", 'E');



	GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);


	//skin
	AvatarManager_.LinkPlayerToAvatar(this);

	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	
	//다른 아바타 Animation
	//HairRenderer_->CreateFrameAnimationFolder("Idle_1", FrameAnimation_DESC("sm_hair0001a", 0, 10, 0.08f));
	//HairRenderer_->CreateFrameAnimationFolder("Attack_1", FrameAnimation_DESC("sm_hair0000a", 11, 20, 0.08f));
}

void Player_Main::Update(float _DeltaTime)
{
	DNFUpdate();
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


	//이동 flip할때 미세한 오차수정은 일정범위 이동할때 카메라 추적 로직 작성할때 같이하자
	//if (GameEngineInput::GetInst()->IsDown("Right") == true)
	//{
	//	GetTransform().PixLocalPositiveX();
	//	GetTransform().SetLocalMove(float4::RIGHT * 30);
	//}
	if (GameEngineInput::GetInst()->IsPress("Right") == true)
	{
		GetTransform().SetLocalMove(float4::RIGHT * _DeltaTime * 100.0f);
		AvatarManager_.ChangeMotion(PlayerAnimations::Move);
		GetTransform().PixLocalPositiveX();
	}
	//if (GameEngineInput::GetInst()->IsDown("Left") == true)
	//{
	//	GetTransform().PixLocalNegativeX();
	//	GetTransform().SetLocalMove(float4::LEFT * 30);
	//}
	if (GameEngineInput::GetInst()->IsPress("Left") == true)
	{
		GetTransform().SetLocalMove(float4::LEFT * _DeltaTime * 100.0f);
		AvatarManager_.ChangeMotion(PlayerAnimations::Move);
		GetTransform().PixLocalNegativeX();

	}
	if (GameEngineInput::GetInst()->IsUp("Left") == true || GameEngineInput::GetInst()->IsUp("Right") == true)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	}

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(GetTransform().GetWorldPosition());

}

void Player_Main::End()
{
}
