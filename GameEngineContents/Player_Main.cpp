#include "PreCompile.h"
#include "DNFDefineList.h"
#include "Player_Main.h"

#include <GameEngineCore/GameEngineLevel.h>

Player_Main::Player_Main():
	QToggle_(false),
	WToggle_(false),
	EToggle_(false)
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
	 
	//Key �ʱ�ȭ
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
	
	//�ٸ� �ƹ�Ÿ Animation
	//HairRenderer_->CreateFrameAnimationFolder("Idle_1", FrameAnimation_DESC("sm_hair0001a", 0, 10, 0.08f));
	//HairRenderer_->CreateFrameAnimationFolder("Attack_1", FrameAnimation_DESC("sm_hair0000a", 11, 20, 0.08f));
}

void Player_Main::Update(float _DeltaTime)
{
	DNFUpdate();
	//z�� ������ ��� �ƹ�Ÿ�� ������ �Ͼ
	if (GameEngineInput::GetInst()->IsDown("Q") == true)
	{
		if (QToggle_ == false)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Hair);
			QToggle_ = true;
		}
		else
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Hair);
			QToggle_ = false;
		}

	}
	//w�� ������ ���� �ƹ�Ÿ�� ������ �Ͼ
	if (GameEngineInput::GetInst()->IsDown("W") == true)
	{
		if (WToggle_ == false)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Pants);
			WToggle_ = true;
		}
		else
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Pants);
			WToggle_ = false;
		}

	}
	//e�� ������ ���� �ƹ�Ÿ�� ������ �Ͼ
	if (GameEngineInput::GetInst()->IsDown("E") == true)
	{
		if (EToggle_ == false)
		{
			AvatarManager_.ChangeAvatar(AvatarType::Job, AvatarParts::Weapon);
			EToggle_ = true;
		}
		else
		{
			AvatarManager_.ChangeAvatar(AvatarType::Default, AvatarParts::Weapon);
			EToggle_ = false;
		}

	}
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


	//�̵� flip�Ҷ� �̼��� ���������� �������� �̵��Ҷ� ī�޶� ���� ���� �ۼ��Ҷ� ��������
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
