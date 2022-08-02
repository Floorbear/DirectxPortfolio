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
	//a : -8 ~ d: -5
	//아바타가 사라지면 여기서 offset 수정을 하자
	float Idle_Iter = 0.2f;
	float Attack_Iter = 0.08f;

	SkinRenderer_ = _Player->MainRenderer_; 
	SkinRenderer_->GetTransform().SetLocalScale({ 500,500,1 });
	SkinRenderer_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ });


	//Hair
	_Player->HairRenderer_a_ = _Player->CreateComponent<GameEngineTextureRenderer>("HairRenderer_a_");
	HairRenderer_a_ = _Player->HairRenderer_a_;
	HairRenderer_a_->GetTransform().SetLocalScale({ 500,500,1 });
	HairRenderer_a_->GetTransform().SetLocalMove({ 0,0,LayerOffset_-9 });


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

	//Shoes
	_Player->ShoesRenderer_a_ = _Player->CreateComponent<GameEngineTextureRenderer>("ShoesRenderer_a_");
	ShoesRenderer_a_ = _Player->ShoesRenderer_a_;
	ShoesRenderer_a_->GetTransform().SetLocalScale({ 500,500,1 });
	ShoesRenderer_a_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 8 });

	_Player->ShoesRenderer_b_ = _Player->CreateComponent<GameEngineTextureRenderer>("ShoesRenderer_b_");
	ShoesRenderer_b_ = _Player->ShoesRenderer_b_;
	ShoesRenderer_b_->GetTransform().SetLocalScale({ 500,500,1 });
	ShoesRenderer_b_->GetTransform().SetLocalMove({ 0,0,LayerOffset_ - 7 });

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

	CreateAvatar("sm_coat0000a", AvatarParts::Coat, AvatarType::Default, AvatarLayer::A);

	CreateAvatar("sm_coat14500b", AvatarParts::Coat, AvatarType::Job, AvatarLayer::B);

	CreateAvatar("sm_belt10700c", AvatarParts::Belt, AvatarType::Job, AvatarLayer::C);
	CreateAvatar("sm_belt10700d", AvatarParts::Belt, AvatarType::Job, AvatarLayer::D);

	CreateAvatar("lswd3400b", AvatarParts::Weapon, AvatarType::Job, AvatarLayer::B);
	CreateAvatar("lswd3400c", AvatarParts::Weapon, AvatarType::Job, AvatarLayer::C);
	CreateAvatar("club0000b", AvatarParts::Weapon, AvatarType::Default, AvatarLayer::B);
	CreateAvatar("club0000c", AvatarParts::Weapon, AvatarType::Default, AvatarLayer::C);


	//렌더 리스트에 넣어줌
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
	CurAvatar_.insert(std::make_pair(AvatarParts::Skin, AvatarType::None));
	CurAvatar_.insert(std::make_pair(AvatarParts::Hair, AvatarType::Default));
	CurAvatar_.insert(std::make_pair(AvatarParts::Pants, AvatarType::Default));
	CurAvatar_.insert(std::make_pair(AvatarParts::Coat, AvatarType::Default));
	CurAvatar_.insert(std::make_pair(AvatarParts::Shoes, AvatarType::Default));
	CurAvatar_.insert(std::make_pair(AvatarParts::Weapon, AvatarType::Default));


}

void AvatarManager::ChangeMotion(PlayerAnimations _Animation)
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
			StartIter->second->ChangeFrameAnimation(AniName+ PartName);
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

	//여기서 모자에 대한 예외처리


	//모든 렌더러를 꺼버리고 필요한 렌더러만 킴
	for (auto pair : CurAvatar_)
	{
		for (AvatarLayer i : GetRendererLayer(pair.first, pair.second))
		{
			GameEngineTextureRenderer* Renderer = GetRenderer(pair.first, i);
			RenderList_.insert(std::make_pair(pair.first, Renderer));
			Renderer->On();
		}
	}
	

	ChangeMotion(PlayerAnimations::Idle);
}

void AvatarManager::CreateAvatar(const std::string& _AvatarFolderName, AvatarParts _Parts, AvatarType _Type, AvatarLayer _Layer)
{
	//아바타를 생성할 렌더러 선택
	GameEngineTextureRenderer* CurRenderer;
	CurRenderer = GetRenderer(_Parts, _Layer);

	//아바타 이름 선택
	std::string Name = EnumToString(_Type);


	float Idle_Iter = 0.2f;
	float Attack_Iter = 0.08f;

	//아바타 애니메이션 생성
	CurRenderer->CreateFrameAnimationFolder("Idle"+Name, FrameAnimation_DESC(_AvatarFolderName, Idle_Start, Idle_End, Idle_Iter));
	CurRenderer->CreateFrameAnimationFolder("Move" + Name, FrameAnimation_DESC(_AvatarFolderName, Move_Start, Move_End, Attack_Iter));
	CurRenderer->CreateFrameAnimationFolder("AutoAttack_0"+ Name, FrameAnimation_DESC(_AvatarFolderName, AutoAttack_0_Start, AutoAttack_0_End, Attack_Iter));
	CurRenderer->CreateFrameAnimationFolder("Buff" + Name, FrameAnimation_DESC(_AvatarFolderName, BuffOn_Start, BuffOn_End, Attack_Iter,false));


}

std::string AvatarManager::EnumToString(PlayerAnimations _Ani)
{
	switch (_Ani)
	{
	case PlayerAnimations::Idle:
		return "Idle";
		break;
	case PlayerAnimations::Buff:
		return "Buff";
		break;
	case PlayerAnimations::Move:
		return "Move";
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

std::vector<AvatarLayer> AvatarManager::GetRendererLayer(AvatarParts _Parts, AvatarType _Type)
{
	std::vector<AvatarLayer> Vector = {};
	switch (_Parts)
	{
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

GameEngineTextureRenderer* AvatarManager::GetRenderer(AvatarParts _Parts, AvatarLayer _Layer)
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
		switch (_Layer)
		{
		case AvatarLayer::A:
			return CoatRenderer_a_;
			break;
		case AvatarLayer::B:
			return CoatRenderer_b_;
			break;
			break;
		case AvatarLayer::C:
			break;
		case AvatarLayer::D:
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
}
