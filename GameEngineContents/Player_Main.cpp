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

	//skin
	MainRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("sm_body0000",Idle_Start,Idle_End, Idle_Iter));
	MainRenderer_->CreateFrameAnimationFolder("AutoAttack_0", FrameAnimation_DESC("sm_body0000", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	MainRenderer_->ChangeFrameAnimation("Idle");
	MainRenderer_->GetTransform().SetLocalScale({ 500,500 });

	//Hair
	HairRenderer_a_ = CreateComponent<GameEngineTextureRenderer>("HairRenderer_a_");
	HairRenderer_a_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("sm_hair0000a", Idle_Start, Idle_End, Idle_Iter));

	HairRenderer_a_->CreateFrameAnimationFolder("AutoAttack_0", FrameAnimation_DESC("sm_hair0000a", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	HairRenderer_a_->ChangeFrameAnimation("Idle");
	HairRenderer_a_->GetTransform().SetLocalScale({ 500,500 });

	HairRenderer_a_->CreateFrameAnimationFolder("Idle_1", FrameAnimation_DESC("A_sm_hair13000", Idle_Start, Idle_End, Idle_Iter));
	HairRenderer_a_->CreateFrameAnimationFolder("AutoAttack_0_1", FrameAnimation_DESC("A_sm_hair13000", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));

	HairRenderer_d_ = CreateComponent<GameEngineTextureRenderer>("HairRenderer_d_");

	HairRenderer_d_->CreateFrameAnimationFolder("Idle_1", FrameAnimation_DESC("D_sm_hair13000", Idle_Start, Idle_End, Idle_Iter));
	HairRenderer_d_->CreateFrameAnimationFolder("AutoAttack_0_1", FrameAnimation_DESC("D_sm_hair13000", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));

	HairRenderer_d_->ChangeFrameAnimation("Idle_1");
	HairRenderer_d_->Off();
	HairRenderer_d_->GetTransform().SetLocalScale({ 500,500 });

	//Weapon
	WeaponRenderer_b_ = CreateComponent<GameEngineTextureRenderer>("WeaponRenderer_b_");
	WeaponRenderer_b_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("lswd3400b", Idle_Start, Idle_End, Idle_Iter));
	WeaponRenderer_b_->CreateFrameAnimationFolder("AutoAttack_0", FrameAnimation_DESC("lswd3400b", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	WeaponRenderer_b_->ChangeFrameAnimation("Idle");
	WeaponRenderer_b_->GetTransform().SetLocalScale({ 500,500 });

	//Weapon 
	WeaponRenderer_c_ = CreateComponent<GameEngineTextureRenderer>("WeaponRenderer_c_");
	WeaponRenderer_c_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("lswd3400c", Idle_Start, Idle_End, Idle_Iter));
	WeaponRenderer_c_->CreateFrameAnimationFolder("AutoAttack_0", FrameAnimation_DESC("lswd3400c", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	WeaponRenderer_c_->ChangeFrameAnimation("Idle");
	WeaponRenderer_c_->GetTransform().SetLocalScale({ 500,500 });

	//다른 아바타 Animation
	//HairRenderer_->CreateFrameAnimationFolder("Idle_1", FrameAnimation_DESC("sm_hair0001a", 0, 10, 0.08f));
	//HairRenderer_->CreateFrameAnimationFolder("Attack_1", FrameAnimation_DESC("sm_hair0000a", 11, 20, 0.08f));
}

void Player_Main::Update(float _DeltaTime)
{
	DNFUpdate();
	//z를 누르면 헤어 아바타의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("Z") == true)
	{
		OnAvator_ = !OnAvator_;
	}
	//x를 누르면 모션의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		if (OnAvator_ == true)
		{
			HairRenderer_d_->On();
			HairRenderer_a_->ChangeFrameAnimation("AutoAttack_0_1");
			HairRenderer_d_->ChangeFrameAnimation("AutoAttack_0_1");
		}
		else
		{
			HairRenderer_a_->ChangeFrameAnimation("AutoAttack_0");
			HairRenderer_d_->Off();
		}

		WeaponRenderer_b_->ChangeFrameAnimation("AutoAttack_0");
		WeaponRenderer_c_->ChangeFrameAnimation("AutoAttack_0");
		MainRenderer_->ChangeFrameAnimation("AutoAttack_0");
	}

	//C를 누르면 모션의 변경이 일어남
	if (GameEngineInput::GetInst()->IsDown("C") == true)
	{
		if (OnAvator_ == true)
		{
			HairRenderer_a_->ChangeFrameAnimation("Idle_1");
			HairRenderer_d_->ChangeFrameAnimation("Idle_1");
		}
		else
		{
			HairRenderer_a_->ChangeFrameAnimation("Idle");
			HairRenderer_d_->Off();
		}

		WeaponRenderer_b_->ChangeFrameAnimation("Idle");
		WeaponRenderer_c_->ChangeFrameAnimation("Idle");
		MainRenderer_->ChangeFrameAnimation("Idle");
	}

}

void Player_Main::End()
{
}
