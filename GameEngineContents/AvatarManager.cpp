#include "PreCompile.h"
#include "AvatarManager.h"

#include "Player_Main.h"
#include "DNFDefineList.h"

AvatarManager::AvatarManager():
	LayerOffset_(-5.0f)
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
	//a : -4 ~ d: -1
	float Idle_Iter = 0.2f;
	float Attack_Iter = 0.08f;

	SkinRenderer_ = _Player->MainRenderer_; 
	SkinRenderer_->GetTransform().SetLocalScale({ 500,500,LayerOffset_ });


	//Hair
	_Player->HairRenderer_a_ = _Player->CreateComponent<GameEngineTextureRenderer>("HairRenderer_a_");
	HairRenderer_a_ = _Player->HairRenderer_a_;
	HairRenderer_a_->GetTransform().SetLocalScale({ 500,500,LayerOffset_-1 });


	_Player->HairRenderer_d_ = _Player->CreateComponent<GameEngineTextureRenderer>("HairRenderer_d_");
	HairRenderer_d_ = _Player->HairRenderer_d_;
	HairRenderer_d_->GetTransform().SetLocalScale({ 500,500,LayerOffset_ - 2 });
	HairRenderer_d_->Off();

	//Pants
	_Player->PantsRenderer_a_ = _Player->CreateComponent<GameEngineTextureRenderer>("PantsRenderer_a_");
	PantsRenderer_a_ = _Player->PantsRenderer_a_;
	PantsRenderer_a_->GetTransform().SetLocalScale({ 500,500,LayerOffset_ - 1 });


	_Player->PantsRenderer_b_ = _Player->CreateComponent<GameEngineTextureRenderer>("PantsRenderer_b_");
	PantsRenderer_b_ = _Player->PantsRenderer_b_;
	PantsRenderer_b_->GetTransform().SetLocalScale({ 500,500,LayerOffset_ - 2 });


	_Player->WeaponRenderer_b_ = _Player->CreateComponent<GameEngineTextureRenderer>("WeaponRenderer_b_");
	WeaponRenderer_b_ = _Player->WeaponRenderer_b_;
	WeaponRenderer_b_->GetTransform().SetLocalScale({ 500,500,LayerOffset_ - 10 });

	_Player->WeaponRenderer_c_ = _Player->CreateComponent<GameEngineTextureRenderer>("WeaponRenderer_c_");
	WeaponRenderer_c_ = _Player->WeaponRenderer_c_;
	WeaponRenderer_c_->GetTransform().SetLocalScale({ 500,500,LayerOffset_ - 11 });





	//
	CreateAvatar("sm_body0000", AvatarParts::Skin, AvatarType::None, AvatarLayer::A);
	CreateAvatar("sm_hair0000a", AvatarParts::Hair, AvatarType::Default, AvatarLayer::A);
	CreateAvatar("A_sm_pants0000", AvatarParts::Pants, AvatarType::Default, AvatarLayer::A);
	CreateAvatar("B_sm_pants0000", AvatarParts::Pants, AvatarType::Default, AvatarLayer::B);
	CreateAvatar("lswd3400b", AvatarParts::Weapon, AvatarType::None, AvatarLayer::B);
	CreateAvatar("lswd3400c", AvatarParts::Weapon, AvatarType::None, AvatarLayer::C);

	////렌더 리스트에 넣어줌
	//RenderList_.insert(std::make_pair(AvatarParts::Skin, SkinRenderer_));
	//RenderList_.insert(std::make_pair(AvatarParts::Hair, HairRenderer_a_));
	//RenderList_.insert(std::make_pair(AvatarParts::Pants, PantsRenderer_a_));
	//RenderList_.insert(std::make_pair(AvatarParts::Pants, PantsRenderer_b_));
	//RenderList_.insert(std::make_pair(AvatarParts::Weapon, WeaponRenderer_b_));
	//RenderList_.insert(std::make_pair(AvatarParts::Weapon, WeaponRenderer_c_));

	////현재 아바타로 세팅
	//CurAvatar_.insert(std::make_pair(AvatarParts::Skin, AvatarType::None));
	//CurAvatar_.insert(std::make_pair(AvatarParts::Hair, AvatarType::Default));
	//CurAvatar_.insert(std::make_pair(AvatarParts::Pants, AvatarType::Default));
	//CurAvatar_.insert(std::make_pair(AvatarParts::Weapon, AvatarType::None));




	//헤어

	//HairRenderer_a_->CreateFrameAnimationFolder("Idle_1", FrameAnimation_DESC("A_sm_hair13000", Idle_Start, Idle_End, Idle_Iter));
	//HairRenderer_a_->CreateFrameAnimationFolder("AutoAttack_0_1", FrameAnimation_DESC("A_sm_hair13000", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));

	/*HairRenderer_d_->CreateFrameAnimationFolder("Idle_1", FrameAnimation_DESC("D_sm_hair13000", Idle_Start, Idle_End, Idle_Iter));
	HairRenderer_d_->CreateFrameAnimationFolder("AutoAttack_0_1", FrameAnimation_DESC("D_sm_hair13000", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	HairRenderer_d_->ChangeFrameAnimation("Idle_1");
	HairRenderer_d_->Off();*/

	//팬츠
	//PantsRenderer_a_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("A_sm_pants0000", Idle_Start, Idle_End, Idle_Iter));
	//PantsRenderer_a_->CreateFrameAnimationFolder("AutoAttack_0", FrameAnimation_DESC("A_sm_pants0000", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	//PantsRenderer_a_->ChangeFrameAnimation("Idle");

	//PantsRenderer_b_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("B_sm_pants0000", Idle_Start, Idle_End, Idle_Iter));
	//PantsRenderer_b_->CreateFrameAnimationFolder("AutoAttack_0", FrameAnimation_DESC("B_sm_pants0000", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	//PantsRenderer_b_->ChangeFrameAnimation("Idle");


	//Weapon
	//WeaponRenderer_b_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("lswd3400b", Idle_Start, Idle_End, Idle_Iter));
	//WeaponRenderer_b_->CreateFrameAnimationFolder("AutoAttack_0", FrameAnimation_DESC("lswd3400b", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	//WeaponRenderer_b_->ChangeFrameAnimation("Idle");

	////Weapon 
	//WeaponRenderer_c_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("lswd3400c", Idle_Start, Idle_End, Idle_Iter));
	//WeaponRenderer_c_->CreateFrameAnimationFolder("AutoAttack_0", FrameAnimation_DESC("lswd3400c", AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	//WeaponRenderer_c_->ChangeFrameAnimation("Idle");


}

void AvatarManager::ChangeMotion(PlayerAnimations _Animation)
{
	////애니메이션 이름 선택
	//std::string AniName = EnumToString(_Animation);

	////헤어
	//{
	//	std::string PartName = EnumToString(CurAvatar_[AvatarParts::Hair]);
	//	std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator StartIter = RenderList_.lower_bound(AvatarParts::Hair);
	//	std::multimap<AvatarParts, GameEngineTextureRenderer*>::iterator EndIter = RenderList_.upper_bound(AvatarParts::Hair);
	//	for (; StartIter != EndIter; StartIter)
	//	{
	//		StartIter->second->ChangeFrameAnimation(AniName+ PartName);
	//	}
	//}
		

}

void AvatarManager::CreateAvatar(const std::string& _AvatarFolderName, AvatarParts _Parts, AvatarType _Type, AvatarLayer _Layer)
{
	//아바타를 생성할 렌더러 선택
	GameEngineTextureRenderer* CurRenderer;
	CurRenderer = SelectRenderer(_Parts, _Layer);

	//아바타 이름 선택
	std::string Name = EnumToString(_Type);


	float Idle_Iter = 0.2f;
	float Attack_Iter = 0.08f;

	CurRenderer->CreateFrameAnimationFolder("Idle"+Name, FrameAnimation_DESC(_AvatarFolderName, Idle_Start, Idle_End, Idle_Iter));
	CurRenderer->CreateFrameAnimationFolder("AutoAttack_0"+ Name, FrameAnimation_DESC(_AvatarFolderName, AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));

	//이거 ChangeMotion에 바꿔야함
	CurRenderer->ChangeFrameAnimation("Idle"+Name);

}

std::string AvatarManager::EnumToString(PlayerAnimations _Ani)
{
	switch (_Ani)
	{
	case PlayerAnimations::Idle:
		return "Idle";
		break;
	case PlayerAnimations::AutoAttack_0:
		return "AutoAttack_0";
		break;
	default:
		break;
	}
	return "";
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

GameEngineTextureRenderer* AvatarManager::SelectRenderer(AvatarParts _Parts, AvatarLayer _Layer)
{
	switch (_Parts)
	{
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
		break;
	case AvatarParts::Face:
		break;
	case AvatarParts::Neck:
		break;
	case AvatarParts::Coat:
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
			break;
		default:
			break;
		}
		break;
	case AvatarParts::Belt:
		break;
	case AvatarParts::Shoes:
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
}
