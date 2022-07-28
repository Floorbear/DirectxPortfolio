#include "PreCompile.h"
#include "DNFDefineList.h"
#include "Player_Main.h"

Player_Main::Player_Main():
	OnAvator_(false)
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
	GameEngineInput::GetInst()->CreateKey("Z", 'Z');
	GameEngineInput::GetInst()->CreateKey("X", 'X');
	GameEngineInput::GetInst()->CreateKey("C", 'C');

	GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);

	//skin
	AvatarManager_.LinkPlayerToAvatar(this);

	
	//다른 아바타 Animation
	//HairRenderer_->CreateFrameAnimationFolder("Idle_1", FrameAnimation_DESC("sm_hair0001a", 0, 10, 0.08f));
	//HairRenderer_->CreateFrameAnimationFolder("Attack_1", FrameAnimation_DESC("sm_hair0000a", 11, 20, 0.08f));
}

void Player_Main::Update(float _DeltaTime)
{
	DNFUpdate();
	////z를 누르면 헤어 아바타의 변경이 일어남
	//if (GameEngineInput::GetInst()->IsDown("Z") == true)
	//{
	//	OnAvator_ = !OnAvator_;
	//}
	////x를 누르면 모션의 변경이 일어남
	//if (GameEngineInput::GetInst()->IsDown("X") == true)
	//{
	//	//AvatarManager_.ChangeMotion(PlayerAnimations::AutoAttack_0);
	///*	if (OnAvator_ == true)
	//	{
	//		HairRenderer_d_->On();
	//		HairRenderer_a_->ChangeFrameAnimation("AutoAttack_0_1");
	//		HairRenderer_d_->ChangeFrameAnimation("AutoAttack_0_1");
	//	}
	//	else
	//	{
	//		HairRenderer_a_->ChangeFrameAnimation("AutoAttack_0");
	//		HairRenderer_d_->Off();
	//	}

	//	WeaponRenderer_b_->ChangeFrameAnimation("AutoAttack_0");
	//	WeaponRenderer_c_->ChangeFrameAnimation("AutoAttack_0");
	//	MainRenderer_->ChangeFrameAnimation("AutoAttack_0");

	//	PantsRenderer_a_->ChangeFrameAnimation("AutoAttack_0");
	//	PantsRenderer_b_->ChangeFrameAnimation("AutoAttack_0");*/
	//}

	////C를 누르면 모션의 변경이 일어남
	//if (GameEngineInput::GetInst()->IsDown("C") == true)
	//{
	//	//AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	//	//if (OnAvator_ == true)
	//	//{
	//	//	HairRenderer_a_->ChangeFrameAnimation("Idle_1");
	//	//	HairRenderer_d_->ChangeFrameAnimation("Idle_1");
	//	//}
	//	//else
	//	//{
	//	//	HairRenderer_a_->ChangeFrameAnimation("Idle");
	//	//	HairRenderer_d_->Off();
	//	//}

	//	//WeaponRenderer_b_->ChangeFrameAnimation("Idle");
	//	//WeaponRenderer_c_->ChangeFrameAnimation("Idle");
	//	//MainRenderer_->ChangeFrameAnimation("Idle");

	//	//PantsRenderer_a_->ChangeFrameAnimation("Idle");
	//	//PantsRenderer_b_->ChangeFrameAnimation("Idle");
	//}

}

void Player_Main::End()
{
}
