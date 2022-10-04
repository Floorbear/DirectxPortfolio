#include "PreCompile.h"
#include "AvatarManager.h"

#include "Player_Main.h"
#include "DNFDefineList.h"
#include "DNFDebugGUI.h"

AvatarManager::AvatarManager() :
	LayerOffset_(-5.0f),
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
	ShadowRenderer_(),
	SkinRenderer_()
{
}

AvatarManager::~AvatarManager()
{
}

void AvatarManager::LoadAvatar()
{
}

void AvatarManager::LinkPlayerToAvatar(Player_Main* _Player)
{
	//_Player에 아바타 렌더러를 생성한다.
	//a : -8 ~ d: -5
	//아바타가 사라지면 여기서 offset 수정을 하자
	float Idle_Iter = 0.2f;
	float Attack_Iter = 0.08f;

	//Shadow
	//_Player->ShadowRenderer_ = _Player->CreateComponent<GameEngineTextureRenderer>("ShadowRenderer_");
	ShadowRenderer_ = _Player->ShadowRenderer_;
	ShadowRenderer_->GetTransform().SetLocalScale({ 500,500,1 });
	//ShadowRenderer_->GetTransform().SetLocalPosition({-10,-45,150 });
	//ShadowRenderer_->GetTransform().SetLocalRotation({ -60,0,5 });
	//ShadowRenderer_->GetColorData().MulColor = float4(0, 0, 0,0.6f);
	//DNFDebugGUI::AddTransform("Shadow", &ShadowRenderer_->GetTransform());
	//skin
	SkinRenderer_ = _Player->MainRenderer_;
	SkinRenderer_->GetTransform().SetLocalScale({ 500,500,1 });
	SkinRenderer_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ });

	//Hair
	_Player->HairRenderer_a_ = _Player->CreateComponent<GameEngineTextureRenderer>("HairRenderer_a_");
	HairRenderer_a_ = _Player->HairRenderer_a_;
	HairRenderer_a_->GetTransform().SetLocalScale({ 500,500,1 });
	HairRenderer_a_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 9 });

	_Player->HairRenderer_d_ = _Player->CreateComponent<GameEngineTextureRenderer>("HairRenderer_d_");
	HairRenderer_d_ = _Player->HairRenderer_d_;
	HairRenderer_d_->GetTransform().SetLocalScale({ 500,500,1 });
	HairRenderer_d_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 5 });
	HairRenderer_d_->Off();

	//Pants
	_Player->PantsRenderer_a_ = _Player->CreateComponent<GameEngineTextureRenderer>("PantsRenderer_a_");
	PantsRenderer_a_ = _Player->PantsRenderer_a_;
	PantsRenderer_a_->GetTransform().SetLocalScale({ 500,500,1 });
	PantsRenderer_a_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 6 });

	_Player->PantsRenderer_b_ = _Player->CreateComponent<GameEngineTextureRenderer>("PantsRenderer_b_");
	PantsRenderer_b_ = _Player->PantsRenderer_b_;
	PantsRenderer_b_->GetTransform().SetLocalScale({ 500,500,1 });
	PantsRenderer_b_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 5 });

	_Player->PantsRenderer_d_ = _Player->CreateComponent<GameEngineTextureRenderer>("PantsRenderer_d_");
	PantsRenderer_d_ = _Player->PantsRenderer_d_;
	PantsRenderer_d_->GetTransform().SetLocalScale({ 500,500,1 });
	PantsRenderer_d_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 3 });
	PantsRenderer_d_->Off();

	//Coat
	_Player->CoatRenderer_a_ = _Player->CreateComponent<GameEngineTextureRenderer>("CoatRenderer_a_");
	CoatRenderer_a_ = _Player->CoatRenderer_a_;
	CoatRenderer_a_->GetTransform().SetLocalScale({ 500,500,1 });
	CoatRenderer_a_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 8 });

	_Player->CoatRenderer_b_ = _Player->CreateComponent<GameEngineTextureRenderer>("CoatRenderer_b_");
	CoatRenderer_b_ = _Player->CoatRenderer_b_;
	CoatRenderer_b_->GetTransform().SetLocalScale({ 500,500,1 });
	CoatRenderer_b_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 7 });
	CoatRenderer_b_->Off();

	_Player->CoatRenderer_c_ = _Player->CreateComponent<GameEngineTextureRenderer>("CoatRenderer_c_");
	CoatRenderer_c_ = _Player->CoatRenderer_c_;
	CoatRenderer_c_->GetTransform().SetLocalScale({ 500,500,1 });
	CoatRenderer_c_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 6 });
	CoatRenderer_c_->Off();

	_Player->CoatRenderer_d_ = _Player->CreateComponent<GameEngineTextureRenderer>("CoatRenderer_d_");
	CoatRenderer_d_ = _Player->CoatRenderer_d_;
	CoatRenderer_d_->GetTransform().SetLocalScale({ 500,500,1 });
	CoatRenderer_d_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 5 });
	CoatRenderer_d_->Off();

	//Shoes
	_Player->ShoesRenderer_a_ = _Player->CreateComponent<GameEngineTextureRenderer>("ShoesRenderer_a_");
	ShoesRenderer_a_ = _Player->ShoesRenderer_a_;
	ShoesRenderer_a_->GetTransform().SetLocalScale({ 500,500,1 });
	ShoesRenderer_a_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 4 });

	_Player->ShoesRenderer_b_ = _Player->CreateComponent<GameEngineTextureRenderer>("ShoesRenderer_b_");
	ShoesRenderer_b_ = _Player->ShoesRenderer_b_;
	ShoesRenderer_b_->GetTransform().SetLocalScale({ 500,500,1 });
	ShoesRenderer_b_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 3 });

	//벨트
	_Player->BeltRenderer_c_ = _Player->CreateComponent<GameEngineTextureRenderer>("BeltRenderer_c_");
	BeltRenderer_c_ = _Player->BeltRenderer_c_;
	BeltRenderer_c_->GetTransform().SetLocalScale({ 500,500,1 });
	BeltRenderer_c_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 6 });
	BeltRenderer_c_->Off();

	_Player->BeltRenderer_d_ = _Player->CreateComponent<GameEngineTextureRenderer>("BeltRenderer_d_");
	BeltRenderer_d_ = _Player->BeltRenderer_d_;
	BeltRenderer_d_->GetTransform().SetLocalScale({ 500,500,1 });
	BeltRenderer_d_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 5 });
	BeltRenderer_d_->Off();

	//모자
	_Player->CapRenderer_a_ = _Player->CreateComponent<GameEngineTextureRenderer>("CapRenderer_a_");
	CapRenderer_a_ = _Player->CapRenderer_a_;
	CapRenderer_a_->GetTransform().SetLocalScale({ 500,500,1 });
	CapRenderer_a_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 10 });
	CapRenderer_a_->Off();

	_Player->CapRenderer_b_ = _Player->CreateComponent<GameEngineTextureRenderer>("CapRenderer_b_");
	CapRenderer_b_ = _Player->CapRenderer_b_;
	CapRenderer_b_->GetTransform().SetLocalScale({ 500,500,1 });
	CapRenderer_b_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 9 });
	CapRenderer_b_->Off();

	_Player->CapRenderer_c_ = _Player->CreateComponent<GameEngineTextureRenderer>("CapRenderer_c_");
	CapRenderer_c_ = _Player->CapRenderer_c_;
	CapRenderer_c_->GetTransform().SetLocalScale({ 500,500,1 });
	CapRenderer_c_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 8 });
	CapRenderer_c_->Off();

	//무기
	_Player->WeaponRenderer_b_ = _Player->CreateComponent<GameEngineTextureRenderer>("WeaponRenderer_b_");
	WeaponRenderer_b_ = _Player->WeaponRenderer_b_;
	WeaponRenderer_b_->GetTransform().SetLocalScale({ 500,500,1 });
	WeaponRenderer_b_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 15 });

	_Player->WeaponRenderer_c_ = _Player->CreateComponent<GameEngineTextureRenderer>("WeaponRenderer_c_");
	WeaponRenderer_c_ = _Player->WeaponRenderer_c_;
	WeaponRenderer_c_->GetTransform().SetLocalScale({ 500,500,1 });
	WeaponRenderer_c_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 14 });

	//아바타 생성 부분

	CreateAvatar("sm_body0000", AvatarParts::Skin, AvatarType::None, AvatarLayer::A);
	CreateAvatar("sm_body0000", AvatarParts::Shadow, AvatarType::None, AvatarLayer::A);

	CreateAvatar("sm_hair0000a", AvatarParts::Hair, AvatarType::Default, AvatarLayer::A);

	CreateAvatar("A_sm_hair13000", AvatarParts::Hair, AvatarType::Job, AvatarLayer::A);
	CreateAvatar("D_sm_hair13000", AvatarParts::Hair, AvatarType::Job, AvatarLayer::D);

	CreateAvatar("A_sm_pants0000", AvatarParts::Pants, AvatarType::Default, AvatarLayer::A);
	CreateAvatar("B_sm_pants0000", AvatarParts::Pants, AvatarType::Default, AvatarLayer::B);

	CreateAvatar("sm_pants13600a", AvatarParts::Pants, AvatarType::Job, AvatarLayer::A);
	CreateAvatar("sm_pants13600b", AvatarParts::Pants, AvatarType::Job, AvatarLayer::B);
	CreateAvatar("sm_pants13600d", AvatarParts::Pants, AvatarType::Job, AvatarLayer::D);

	CreateAvatar("sm_shoes0000a", AvatarParts::Shoes, AvatarType::Default, AvatarLayer::A);
	CreateAvatar("sm_shoes0000b", AvatarParts::Shoes, AvatarType::Default, AvatarLayer::B);

	CreateAvatar("sm_shoes12800a", AvatarParts::Shoes, AvatarType::Job, AvatarLayer::A);
	CreateAvatar("sm_shoes12800b", AvatarParts::Shoes, AvatarType::Job, AvatarLayer::B);

	CreateAvatar("sm_shoes14500a", AvatarParts::Shoes, AvatarType::Dog, AvatarLayer::A);
	CreateAvatar("sm_shoes14500b", AvatarParts::Shoes, AvatarType::Dog, AvatarLayer::B);

	CreateAvatar("sm_coat0000a", AvatarParts::Coat, AvatarType::Default, AvatarLayer::A);

	CreateAvatar("sm_coat14500b", AvatarParts::Coat, AvatarType::Job, AvatarLayer::B);

	CreateAvatar("sm_coat16300a", AvatarParts::Coat, AvatarType::Dog, AvatarLayer::A);
	CreateAvatar("sm_coat16300c", AvatarParts::Coat, AvatarType::Dog, AvatarLayer::C);
	CreateAvatar("sm_coat16300d", AvatarParts::Coat, AvatarType::Dog, AvatarLayer::D);

	CreateAvatar("sm_belt12100c", AvatarParts::Belt, AvatarType::Dog, AvatarLayer::C);
	CreateAvatar("sm_belt12100d", AvatarParts::Belt, AvatarType::Dog, AvatarLayer::D);

	CreateAvatar("sm_belt10700c", AvatarParts::Belt, AvatarType::Job, AvatarLayer::C);
	CreateAvatar("sm_belt10700d", AvatarParts::Belt, AvatarType::Job, AvatarLayer::D);

	CreateAvatar("sm_cap1500a", AvatarParts::Cap, AvatarType::Danjin, AvatarLayer::A);

	CreateAvatar("sm_cap15100a", AvatarParts::Cap, AvatarType::Dog, AvatarLayer::A);
	CreateAvatar("sm_cap15100b", AvatarParts::Cap, AvatarType::Dog, AvatarLayer::B);
	CreateAvatar("sm_cap15100c", AvatarParts::Cap, AvatarType::Dog, AvatarLayer::C);

	CreateAvatar("lswd3400b", AvatarParts::Weapon, AvatarType::Job, AvatarLayer::B);
	CreateAvatar("lswd3400c", AvatarParts::Weapon, AvatarType::Job, AvatarLayer::C);
	CreateAvatar("club0000b", AvatarParts::Weapon, AvatarType::Default, AvatarLayer::B);
	CreateAvatar("club0000c", AvatarParts::Weapon, AvatarType::Default, AvatarLayer::C);

	//렌더 리스트에 넣어줌
	RenderList_.insert(std::make_pair(AvatarParts::Shadow, ShadowRenderer_));
	RenderList_.insert(std::make_pair(AvatarParts::Skin, SkinRenderer_));
	RenderList_.insert(std::make_pair(AvatarParts::Hair, HairRenderer_a_));
	RenderList_.insert(std::make_pair(AvatarParts::Pants, PantsRenderer_a_));
	RenderList_.insert(std::make_pair(AvatarParts::Pants, PantsRenderer_b_));
	RenderList_.insert(std::make_pair(AvatarParts::Coat, CoatRenderer_a_));
	RenderList_.insert(std::make_pair(AvatarParts::Shoes, ShoesRenderer_a_));
	RenderList_.insert(std::make_pair(AvatarParts::Shoes, ShoesRenderer_b_));
	RenderList_.insert(std::make_pair(AvatarParts::Weapon, WeaponRenderer_b_));
	RenderList_.insert(std::make_pair(AvatarParts::Weapon, WeaponRenderer_c_));

	//현재 아바타로 세팅
	CurAvatar_.insert(std::make_pair(AvatarParts::Shadow, AvatarType::None));
	CurAvatar_.insert(std::make_pair(AvatarParts::Skin, AvatarType::None));
	CurAvatar_.insert(std::make_pair(AvatarParts::Hair, AvatarType::Default));
	CurAvatar_.insert(std::make_pair(AvatarParts::Pants, AvatarType::Default));
	CurAvatar_.insert(std::make_pair(AvatarParts::Coat, AvatarType::Default));
	CurAvatar_.insert(std::make_pair(AvatarParts::Shoes, AvatarType::Default));
	CurAvatar_.insert(std::make_pair(AvatarParts::Weapon, AvatarType::Default));
}

void AvatarManager::ChangeMotion(PlayerAnimations _Animation)
{
	NextMotion_ = std::bind(&AvatarManager::ChangeLastUpdateMotion, this, _Animation);
}

void AvatarManager::ChangeAvatar(AvatarType _Type, AvatarParts _Parts)
{
	//CurAvatar와 RenderList 초기화
	CurAvatar_[_Parts] = _Type;

	////RenderList의 모든 렌더러를 Off후, 렌더리스트에서 비우고 렌더러 다시 넣어주기
	//{
	//	std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(_Parts);
	//	std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(_Parts);
	//	for (; StartIter != EndIter; StartIter++)
	//	{
	//		StartIter->second->Off();
	//	}
	//}
	//RenderList_.erase(_Parts);

	//모든 렌더러 끄기
	for (auto i : RenderList_)
	{
		i.second->Off();
	}
	RenderList_.clear();

	//모든 렌더러를 꺼버리고 필요한 렌더러만 킴
	//피부, 그림자 등도 켜야하니 피부, 그림자에 더미 레이어를 추가해서 GetRendererLayer에 들어가게 하자
	for (auto pair : CurAvatar_)
	{
		for (AvatarLayer i : GetRendererLayer(pair.first, pair.second))
		{
			GameEngineTextureRenderer* Renderer = GetRenderer(pair.first, i);
			RenderList_.insert(std::make_pair(pair.first, Renderer));
			Renderer->On();
		}
	}

	//모자압이나 댕댕압같은 다른 렌더러를 꺼버리는 아바타의 예외처리
	for (auto pair : CurAvatar_)
	{
		//예외처리 렌더러가 있으면 꺼준다.
		for (GameEngineTextureRenderer* i : GetHideRendererList(pair.first, pair.second))
		{
			i->Off();
		}
	}

	ChangeMotion(PlayerAnimations::ChangeAvatar);
}

void AvatarManager::CreateAvatar(const std::string& _AvatarFolderName, AvatarParts _Parts, AvatarType _Type, AvatarLayer _Layer)
{
	//아바타를 생성할 렌더러 선택
	GameEngineTextureRenderer* CurRenderer;
	CurRenderer = GetRenderer(_Parts, _Layer);

	//아바타 이름 선택
	std::string Name = EnumToString(_Type);

	float Iter_0 = 0.2f;
	float Iter_1 = 0.08f;
	float Iter_2 = 0.027f;

	//아바타 애니메이션 생성
	CurRenderer->CreateFrameAnimationFolder("Idle" + Name, FrameAnimation_DESC(_AvatarFolderName, Idle_Start, Idle_End, Iter_0));
	CurRenderer->CreateFrameAnimationFolder("ChangeAvatar" + Name, FrameAnimation_DESC(_AvatarFolderName, Idle_Start, Idle_End, Iter_0, false));
	//ChangeAvatar 애니상태면 다음프레임에 Idle로 이동한다.
	CurRenderer->AnimationBindFrame("ChangeAvatar" + Name, [&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame] == Idle_Start + 1)
			{
				ChangeMotion(PlayerAnimations::Idle);
			}
		});

	CurRenderer->CreateFrameAnimationFolder("Move" + Name, FrameAnimation_DESC(_AvatarFolderName, Move_Start, Move_End, Iter_1));

	CurRenderer->CreateFrameAnimationFolder("BattleIdle" + Name, FrameAnimation_DESC(_AvatarFolderName, BattleIdle_Start, BattleIdle_End, Iter_0));
	CurRenderer->CreateFrameAnimationFolder("BattleMove" + Name, FrameAnimation_DESC(_AvatarFolderName, BattleMove_Start, BattleMove_End, Iter_1));

	CurRenderer->CreateFrameAnimationFolder("AutoAttack_0" + Name, FrameAnimation_DESC(_AvatarFolderName, AutoAttack_0_Start, AutoAttack_0_End, Iter_2, false));
	CurRenderer->CreateFrameAnimationFolder("AutoAttack_1" + Name, FrameAnimation_DESC(_AvatarFolderName, AutoAttack_1_Start, AutoAttack_1_End, Iter_2, false));
	CurRenderer->CreateFrameAnimationFolder("AutoAttack_2" + Name, FrameAnimation_DESC(_AvatarFolderName, AutoAttack_2_Start, AutoAttack_2_End, Iter_2, false));
	CurRenderer->CreateFrameAnimationFolder("UpperSlash" + Name, FrameAnimation_DESC(_AvatarFolderName, AutoAttack_2_Start, AutoAttack_2_End, Iter_2, false));
	CurRenderer->CreateFrameAnimationFolder("Buff" + Name, FrameAnimation_DESC(_AvatarFolderName, BuffOn_Start, BuffOn_End, Iter_1, false));
	CurRenderer->CreateFrameAnimationFolder("Fury" + Name, FrameAnimation_DESC(_AvatarFolderName, BuffOn_Start, BuffOn_End, Iter_1 * 0.5f, false));
	CurRenderer->CreateFrameAnimationFolder("Hit" + Name, FrameAnimation_DESC(_AvatarFolderName, Hit_Start, Hit_End, 0.04f, false));
	CurRenderer->CreateFrameAnimationFolder("Down" + Name, FrameAnimation_DESC(_AvatarFolderName, Down_Start, Down_End, 0.04f, false));
	CurRenderer->CreateFrameAnimationFolder("Jump_Start" + Name, FrameAnimation_DESC(_AvatarFolderName, Jump_Motion_Start, Jump_Motion_Middle, 0.06f, false));
	CurRenderer->CreateFrameAnimationFolder("Jump_End" + Name, FrameAnimation_DESC(_AvatarFolderName, Jump_Motion_Middle + 1, Jump_Motion_End, 0.06f, false));

	CurRenderer->CreateFrameAnimationFolder("Frenzy" + Name, FrameAnimation_DESC(_AvatarFolderName, Frenzy_Start, Frenzy_End, Iter_1, false));
	CurRenderer->CreateFrameAnimationFolder("Frenzy_AutoAttack_0" + Name, FrameAnimation_DESC(_AvatarFolderName, Frenzy_AutoAttack_0_Start, Frenzy_AutoAttack_0_End, Iter_2 * 2.1f, false));
	CurRenderer->CreateFrameAnimationFolder("Frenzy_AutoAttack_1" + Name, FrameAnimation_DESC(_AvatarFolderName, Frenzy_AutoAttack_1_Start, Frenzy_AutoAttack_1_End, Iter_2 * 2.1f, false));
	CurRenderer->CreateFrameAnimationFolder("Frenzy_AutoAttack_2" + Name, FrameAnimation_DESC(_AvatarFolderName, Frenzy_AutoAttack_2_Start, Frenzy_AutoAttack_2_End, Iter_2 * 2.1f, false));
	CurRenderer->CreateFrameAnimationFolder("Frenzy_AutoAttack_3" + Name, FrameAnimation_DESC(_AvatarFolderName, Frenzy_AutoAttack_3_Start, Frenzy_AutoAttack_3_End, Iter_2 * 2.1f, false));

	CurRenderer->CreateFrameAnimationFolder("GoreCross_0" + Name, FrameAnimation_DESC(_AvatarFolderName, GoreCross_0_Start, GoreCross_0_End, GoreCrossIter, false));
	CurRenderer->CreateFrameAnimationFolder("GoreCross_1" + Name, FrameAnimation_DESC(_AvatarFolderName, GoreCross_1_Start, GoreCross_1_End, GoreCrossIter, false));

	CurRenderer->CreateFrameAnimationFolder("HopSmash_0" + Name, FrameAnimation_DESC(_AvatarFolderName, Jump_Motion_Start, Jump_Motion_Middle, 0.06f, false));
	CurRenderer->CreateFrameAnimationFolder("HopSmash_1" + Name, FrameAnimation_DESC(_AvatarFolderName, HopSmash_1_Start, HopSmash_1_End, Iter_2, false));
	CurRenderer->CreateFrameAnimationFolder("HopSmash_2" + Name, FrameAnimation_DESC(_AvatarFolderName, HopSmash_2_Start, HopSmash_2_End, Iter_2, false));

	CurRenderer->CreateFrameAnimationFolder("Outragebreak_0" + Name, FrameAnimation_DESC(_AvatarFolderName, Guard_Start, Guard_End, Iter_2, false));
	CurRenderer->CreateFrameAnimationFolder("Outragebreak_1" + Name, FrameAnimation_DESC(_AvatarFolderName, Jump_Motion_Start, Jump_Motion_Middle, 0.06f, false));
	CurRenderer->CreateFrameAnimationFolder("Outragebreak_2" + Name, FrameAnimation_DESC(_AvatarFolderName, HopSmash_1_Start, HopSmash_1_End, Iter_2, false));
	CurRenderer->CreateFrameAnimationFolder("Outragebreak_3" + Name, FrameAnimation_DESC(_AvatarFolderName, HopSmash_2_Start, HopSmash_2_End, Iter_2, false));

	CurRenderer->CreateFrameAnimationFolder("ExtremOverkill_0" + Name, FrameAnimation_DESC(_AvatarFolderName, BuffOn_Start, BuffOn_End, Iter_1 * 0.8f, false));
	CurRenderer->CreateFrameAnimationFolder("ExtremOverkill_1" + Name, FrameAnimation_DESC(_AvatarFolderName, ExtremOverkill_Start, ExtremOverkill_Start, Iter_2, false));
	CurRenderer->CreateFrameAnimationFolder("ExtremOverkill_2" + Name, FrameAnimation_DESC(_AvatarFolderName, ExtremOverkill_Start + 1, ExtremOverkill_End, Iter_2, false));
}

std::string AvatarManager::EnumToString(PlayerAnimations _Ani)
{
	//스킬명이된다. Why > 이 이름으로 애니메이션이 만들어진다. > 스킬이 같은 모션을 공유할 수 있는데 만약 애니메이션을 공유하면 FrameAnimion 함수를 사용하기 힘들다.
	switch (_Ani)
	{
	case PlayerAnimations::ChangeAvatar:
		return "ChangeAvatar";
		break;
	case PlayerAnimations::Idle:
		return "Idle";
		break;
	case PlayerAnimations::BattleIdle:
		return "BattleIdle";
		break;
	case PlayerAnimations::Buff:
		return "Buff";
		break;
	case PlayerAnimations::Fury:
		return "Fury";
		break;
	case PlayerAnimations::Move:
		return "Move";
		break;
	case PlayerAnimations::BattleMove:
		return "BattleMove";
		break;
	case PlayerAnimations::AutoAttack: //Enum To String State전이용
		return "AutoAttack";
		break;
	case PlayerAnimations::AutoAttack_0:
		return "AutoAttack_0";
		break;
	case PlayerAnimations::AutoAttack_1:
		return "AutoAttack_1";
		break;
	case PlayerAnimations::AutoAttack_2:
		return "AutoAttack_2";
		break;
	case PlayerAnimations::Frenzy:
		return "Frenzy";
		break;
	case PlayerAnimations::Frenzy_AutoAttack_0:
		return "Frenzy_AutoAttack_0";
		break;
	case PlayerAnimations::Frenzy_AutoAttack_1:
		return "Frenzy_AutoAttack_1";
		break;
	case PlayerAnimations::Frenzy_AutoAttack_2:
		return "Frenzy_AutoAttack_2";
		break;
	case PlayerAnimations::Frenzy_AutoAttack_3:
		return "Frenzy_AutoAttack_3";
		break;
	case PlayerAnimations::Jump_Start:
		return "Jump_Start";
		break;
	case PlayerAnimations::Jump_End:
		return "Jump_End";
		break;
	case PlayerAnimations::UpperSlash:
		return "UpperSlash";
		break;
	case PlayerAnimations::Hit:
		return "Hit";
		break;
	case PlayerAnimations::Down:
		return "Down";
		break;
	case PlayerAnimations::GoreCross: //State 전이용
		return "GoreCross";
		break;
	case PlayerAnimations::GoreCross_0:
		return "GoreCross_0";
		break;
	case PlayerAnimations::GoreCross_1:
		return "GoreCross_1";
		break;
	case PlayerAnimations::HopSmash: //State 전이용
		return "HopSmash";
		break;
	case PlayerAnimations::HopSmash_0:
		return "HopSmash_0";
		break;
	case PlayerAnimations::HopSmash_1:
		return "HopSmash_1";
		break;
	case PlayerAnimations::HopSmash_2:
		return "HopSmash_2";
		break;
	case PlayerAnimations::Outragebreak: //State 전이용
		return "Outragebreak";
		break;
	case PlayerAnimations::Outragebreak_0:
		return "Outragebreak_0";
		break;
	case PlayerAnimations::Outragebreak_1:
		return "Outragebreak_1";
		break;
	case PlayerAnimations::Outragebreak_2:
		return "Outragebreak_2";
		break;
	case PlayerAnimations::Outragebreak_3:
		return "Outragebreak_3";
		break;
	case PlayerAnimations::ExtremOverkill: //State 전이용
		return "ExtremOverkill";
		break;
	case PlayerAnimations::ExtremOverkill_0:
		return "ExtremOverkill_0";
		break;
	case PlayerAnimations::ExtremOverkill_1:
		return "ExtremOverkill_1";
		break;
	case PlayerAnimations::ExtremOverkill_2:
		return "ExtremOverkill_2";
		break;
	default:
		break;
	}
	return "";
}

void AvatarManager::UpdateMotion()
{
	if (NextMotion_ != nullptr)
	{
		NextMotion_();
		NextMotion_ = nullptr;
	}
}

void AvatarManager::ChangeLastUpdateMotion(PlayerAnimations _Animation)
{
	//애니메이션 이름 선택
	std::string AniName = EnumToString(_Animation);

	//헤어
	{
		std::string PartName = EnumToString(CurAvatar_[AvatarParts::Hair]);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Hair);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Hair);
		for (; StartIter != EndIter; StartIter++)
		{
			StartIter->second->ChangeFrameAnimation(AniName + PartName);
		}
	}
	//피부
	{
		std::string PartName = EnumToString(CurAvatar_[AvatarParts::Skin]);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Skin);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Skin);
		for (; StartIter != EndIter; StartIter++)
		{
			StartIter->second->ChangeFrameAnimation(AniName + PartName);
		}
	}
	//그림자
	{
		std::string PartName = EnumToString(CurAvatar_[AvatarParts::Shadow]);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Shadow);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Shadow);
		for (; StartIter != EndIter; StartIter++)
		{
			StartIter->second->ChangeFrameAnimation(AniName + PartName);
		}
	}
	//팬츠
	{
		std::string PartName = EnumToString(CurAvatar_[AvatarParts::Pants]);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Pants);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Pants);
		for (; StartIter != EndIter; StartIter++)
		{
			StartIter->second->ChangeFrameAnimation(AniName + PartName);
		}
	}
	//코트
	{
		std::string PartName = EnumToString(CurAvatar_[AvatarParts::Coat]);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Coat);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Coat);
		for (; StartIter != EndIter; StartIter++)
		{
			StartIter->second->ChangeFrameAnimation(AniName + PartName);
		}
	}
	//신발
	{
		std::string PartName = EnumToString(CurAvatar_[AvatarParts::Shoes]);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Shoes);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Shoes);
		for (; StartIter != EndIter; StartIter++)
		{
			StartIter->second->ChangeFrameAnimation(AniName + PartName);
		}
	}
	//벨트
	{
		std::string PartName = EnumToString(CurAvatar_[AvatarParts::Belt]);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Belt);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Belt);
		for (; StartIter != EndIter; StartIter++)
		{
			StartIter->second->ChangeFrameAnimation(AniName + PartName);
		}
	}
	//모자
	{
		std::string PartName = EnumToString(CurAvatar_[AvatarParts::Cap]);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Cap);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Cap);
		for (; StartIter != EndIter; StartIter++)
		{
			StartIter->second->ChangeFrameAnimation(AniName + PartName);
		}
	}
	//무기
	{
		std::string PartName = EnumToString(CurAvatar_[AvatarParts::Weapon]);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Weapon);
		std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Weapon);
		for (; StartIter != EndIter; StartIter++)
		{
			StartIter->second->ChangeFrameAnimation(AniName + PartName);
		}
	}
}

std::string AvatarManager::EnumToString(AvatarType _Type)
{
	switch (_Type)
	{
	case AvatarType::None:
		return "";
		break;
	case AvatarType::Default:
		return "_Default";
		break;
	case AvatarType::Job:
		return "_Job";
		break;
	case AvatarType::Dog:
		return "_Dog";
		break;
	case AvatarType::Danjin:
		return "_Danjin";
		break;
	default:
		break;
	}

	return "";
}

std::vector<AvatarLayer> AvatarManager::GetRendererLayer(AvatarParts _Parts, AvatarType _Type)
{
	std::vector<AvatarLayer> Vector = {};
	switch (_Parts)
	{
	case AvatarParts::Shadow:
		//for에 들어가기 위해 더미 리턴
		Vector.push_back(AvatarLayer::A);
		return Vector;
		break;
	case AvatarParts::Skin:
		//for에 들어가기 위해 더미 리턴
		Vector.push_back(AvatarLayer::A);
		return Vector;
		break;

	case AvatarParts::Hair:
		switch (_Type)
		{
		case AvatarType::None:
			break;
		case AvatarType::Default:
			Vector.push_back(AvatarLayer::A);
			return Vector;
			break;
		case AvatarType::Job:
			Vector.push_back(AvatarLayer::A);
			Vector.push_back(AvatarLayer::D);
			return Vector;
			break;
		case AvatarType::Dog:
			break;
		case AvatarType::Danjin:
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Cap:
		switch (_Type)
		{
		case AvatarType::None:
			break;
		case AvatarType::Default:
			break;
		case AvatarType::Job:
			break;
		case AvatarType::Dog:
			Vector.push_back(AvatarLayer::A);
			Vector.push_back(AvatarLayer::B);
			Vector.push_back(AvatarLayer::C);
			return Vector;
			break;
		case AvatarType::Danjin:
			Vector.push_back(AvatarLayer::A);
			return Vector;
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Face:
		break;
	case AvatarParts::Neck:
		break;
	case AvatarParts::Coat:
		switch (_Type)
		{
		case AvatarType::None:
			break;
		case AvatarType::Default:
			Vector.push_back(AvatarLayer::A);
			return Vector;
			break;
		case AvatarType::Job:
			Vector.push_back(AvatarLayer::B);
			return Vector;
			break;
		case AvatarType::Dog:
			Vector.push_back(AvatarLayer::A);
			Vector.push_back(AvatarLayer::C);
			Vector.push_back(AvatarLayer::D);
			return Vector;
			break;
		case AvatarType::Danjin:
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Pants:
		switch (_Type)
		{
		case AvatarType::None:
			break;
		case AvatarType::Default:
			Vector.push_back(AvatarLayer::A);
			Vector.push_back(AvatarLayer::B);
			return Vector;
			break;
		case AvatarType::Job:
			Vector.push_back(AvatarLayer::A);
			Vector.push_back(AvatarLayer::B);
			Vector.push_back(AvatarLayer::D);
			return Vector;
			break;
		case AvatarType::Dog:
			break;
		case AvatarType::Danjin:
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Belt:
		switch (_Type)
		{
		case AvatarType::None:
			break;
		case AvatarType::Default:
			return Vector;
			break;
		case AvatarType::Job:
			Vector.push_back(AvatarLayer::C);
			Vector.push_back(AvatarLayer::D);
			return Vector;
			break;
		case AvatarType::Dog:
			Vector.push_back(AvatarLayer::C);
			Vector.push_back(AvatarLayer::D);
			return Vector;
			break;
		case AvatarType::Danjin:
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Shoes:
		switch (_Type)
		{
		case AvatarType::None:
			break;
		case AvatarType::Default:
			Vector.push_back(AvatarLayer::A);
			Vector.push_back(AvatarLayer::B);
			return Vector;
			break;
		case AvatarType::Job:
			Vector.push_back(AvatarLayer::A);
			Vector.push_back(AvatarLayer::B);
			return Vector;
			break;
		case AvatarType::Dog:
			Vector.push_back(AvatarLayer::A);
			Vector.push_back(AvatarLayer::B);
			return Vector;
			break;
		case AvatarType::Danjin:
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Weapon:
		Vector.push_back(AvatarLayer::B);
		Vector.push_back(AvatarLayer::C);
		return Vector;
		break;
	default:
		break;
	}
	return Vector;
}

std::vector<GameEngineTextureRenderer*> AvatarManager::GetHideRendererList(AvatarParts _Parts, AvatarType _Type)
{
	std::vector<GameEngineTextureRenderer*> Vector = {};
	switch (_Parts)
	{
	case AvatarParts::Skin:
		break;
	case AvatarParts::Hair:
		break;
	case AvatarParts::Cap:
		switch (_Type)
		{
		case AvatarType::None:
			break;
		case AvatarType::Default:
			break;
		case AvatarType::Job:
			break;
		case AvatarType::Dog:
			Vector.push_back(HairRenderer_a_);
			Vector.push_back(HairRenderer_d_);
			return Vector;
			break;
		case AvatarType::Danjin:
			Vector.push_back(HairRenderer_a_);
			Vector.push_back(HairRenderer_d_);
			return Vector;
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Face:
		break;
	case AvatarParts::Neck:
		break;
	case AvatarParts::Coat:
		switch (_Type)
		{
		case AvatarType::None:
			break;
		case AvatarType::Default:
			break;
		case AvatarType::Job:
			break;
		case AvatarType::Dog:
			Vector.push_back(PantsRenderer_a_);
			Vector.push_back(PantsRenderer_b_);
			Vector.push_back(PantsRenderer_d_);
			return Vector;
			break;
		case AvatarType::Danjin:
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Pants:
		break;
	case AvatarParts::Belt:
		break;
	case AvatarParts::Shoes:
		break;
	case AvatarParts::Weapon:
		break;
	default:
		break;
	}
	return Vector;
}

GameEngineTextureRenderer* AvatarManager::GetRenderer(AvatarParts _Parts, AvatarLayer _Layer)
{
	switch (_Parts)
	{
	case AvatarParts::Shadow:
		return ShadowRenderer_;
		break;
	case AvatarParts::Skin:
		return SkinRenderer_;
		break;

	case AvatarParts::Hair:
		switch (_Layer)
		{
		case AvatarLayer::A:
			return HairRenderer_a_;
			break;
		case AvatarLayer::B:
			break;
		case AvatarLayer::C:
			break;
		case AvatarLayer::D:
			return HairRenderer_d_;
			break;
		default:
			break;
		}
		break;

	case AvatarParts::Cap:
		switch (_Layer)
		{
		case AvatarLayer::A:
			return CapRenderer_a_;
			break;
		case AvatarLayer::B:
			return CapRenderer_b_;
			break;
		case AvatarLayer::C:
			return CapRenderer_c_;
			break;
		case AvatarLayer::D:
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Face:
		break;
	case AvatarParts::Neck:
		break;
	case AvatarParts::Coat:
		switch (_Layer)
		{
		case AvatarLayer::A:
			return CoatRenderer_a_;
			break;
		case AvatarLayer::B:
			return CoatRenderer_b_;
			break;
		case AvatarLayer::C:
			return CoatRenderer_c_;
			break;
		case AvatarLayer::D:
			return CoatRenderer_d_;
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Pants:
		switch (_Layer)
		{
		case AvatarLayer::A:
			return PantsRenderer_a_;
			break;
		case AvatarLayer::B:
			return PantsRenderer_b_;
			break;
		case AvatarLayer::C:
			break;
		case AvatarLayer::D:
			return PantsRenderer_d_;
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Belt:
		switch (_Layer)
		{
		case AvatarLayer::A:
			break;
		case AvatarLayer::B:
			break;
		case AvatarLayer::C:
			return BeltRenderer_c_;
			break;
		case AvatarLayer::D:
			return BeltRenderer_d_;

			break;
		default:
			break;
		}
		break;
	case AvatarParts::Shoes:
		switch (_Layer)
		{
		case AvatarLayer::A:
			return ShoesRenderer_a_;
			break;
		case AvatarLayer::B:
			return ShoesRenderer_b_;
			break;
		case AvatarLayer::C:
			break;
		case AvatarLayer::D:
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Weapon:
		switch (_Layer)
		{
		case AvatarLayer::A:
			break;
		case AvatarLayer::B:
			return WeaponRenderer_b_;
			break;
		case AvatarLayer::C:
			return WeaponRenderer_c_;
			break;
		case AvatarLayer::D:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	MsgBoxAssert("존재하지 않는 Renderer를 Get하려 했습니다.");
	return nullptr;
}