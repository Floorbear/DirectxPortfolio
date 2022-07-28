#pragma once
#include <string>
#include <list>
#include "DNFEnums.h"

//아바타 인터페이스 함수
class GameEngineTextureRenderer;
class Player_Main;
class AvatarManager
{
public:
	AvatarManager();
	~AvatarManager();

	AvatarManager(const AvatarManager& _Other) = delete;
	AvatarManager(AvatarManager&& _Other) noexcept = delete;
	AvatarManager& operator=(const AvatarManager& _Other) = delete;
	AvatarManager& operator=(const AvatarManager&& _Other) = delete;

	//아바타 문자열 정보를 Load하는 함수
	void LoadAvatar();

	//캐릭터 렌더러와 아바타를 연결해주는 함수
	void LinkPlayerToAvatar(Player_Main* _Player);

	//아바타 모션을 변경하는 함수
	void ChangeMotion(PlayerAnimations _Animation);

protected:

private:

	//아바타를 생성하는 함수 > 렌더러에 애니메이션을 추가해주는 함수
	//주의! 아직 애니메이션을 전부 만들지 않음
	void CreateAvatar(const std::string& _AvatarFolderName, AvatarParts _Parts, AvatarType _Type, AvatarLayer _Layer);

	std::string EnumToString(PlayerAnimations _Ani);
	std::string EnumToString(AvatarType _Type);


	//렌더러를 선택하는 함수
	//주의! 아직 분기를 나눈것이 많지 않음
	GameEngineTextureRenderer* SelectRenderer(AvatarParts _Parts, AvatarLayer _Layer);

	float LayerOffset_;
	GameEngineTextureRenderer* SkinRenderer_;
	GameEngineTextureRenderer* HairRenderer_a_;
	GameEngineTextureRenderer* HairRenderer_d_;
	GameEngineTextureRenderer* WeaponRenderer_b_;
	GameEngineTextureRenderer* WeaponRenderer_c_;

	GameEngineTextureRenderer* PantsRenderer_a_;
	GameEngineTextureRenderer* PantsRenderer_b_;

	//화면에 렌더링 되는 렌더러
	std::multimap<AvatarParts, GameEngineTextureRenderer*> RenderList_;

	//현재 입고있는 아바타 타입
	std::map<AvatarParts, AvatarType> CurAvatar_;
};

