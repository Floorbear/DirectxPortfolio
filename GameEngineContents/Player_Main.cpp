#include "PreCompile.h"
#include "Player_Main.h"

Player_Main::Player_Main()
{
}

Player_Main::~Player_Main()
{
}

void Player_Main::Start()
{
	DNFStart();
	MainRenderer_->CreateFrameAnimationFolder("AllAni", FrameAnimation_DESC("sm_body0000",0.08f));
	MainRenderer_->ChangeFrameAnimation("AllAni");
	MainRenderer_->GetTransform().SetLocalScale({ 500,500 });

	//Hair
	HairRenderer_ = CreateComponent<GameEngineTextureRenderer>("HairRenderer_");
	HairRenderer_->CreateFrameAnimationFolder("AllAni", FrameAnimation_DESC("sm_hair0000a", 0.08f));
	HairRenderer_->ChangeFrameAnimation("AllAni");
	HairRenderer_->GetTransform().SetLocalScale({ 500,500 });

	//Weapon
	WeaponRenderer_b_ = CreateComponent<GameEngineTextureRenderer>("WeaponRenderer_b_");
	WeaponRenderer_b_->CreateFrameAnimationFolder("AllAni", FrameAnimation_DESC("lswd3400b", 0.08f));
	WeaponRenderer_b_->ChangeFrameAnimation("AllAni");
	WeaponRenderer_b_->GetTransform().SetLocalScale({ 500,500 });

	//Weapon 
	WeaponRenderer_c_ = CreateComponent<GameEngineTextureRenderer>("WeaponRenderer_c_");
	WeaponRenderer_c_->CreateFrameAnimationFolder("AllAni", FrameAnimation_DESC("lswd3400c", 0.08f));
	WeaponRenderer_c_->ChangeFrameAnimation("AllAni");
	WeaponRenderer_c_->GetTransform().SetLocalScale({ 500,500 });
}

void Player_Main::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Player_Main::End()
{
}
