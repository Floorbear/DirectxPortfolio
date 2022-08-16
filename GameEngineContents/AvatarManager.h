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
	//니가 플레이어를 생성하면 Player::Start에 이 함수를 무조건 호출해줘야 해
	void LinkPlayerToAvatar(Player_Main* _Player);

	//아바타 모션을 변경하는 함수
	//RenderList에 있는 렌더러의 애니메이션을 변경한다
	void ChangeMotion(PlayerAnimations _Animation);

	//아바타 바꿀때는 RenderList와 CurAvatar의 해당부위를 Clear하고 진행해야함
	//여기서 사용할 렌더러가 켜지고 그외 렌더러가 꺼집니다.
	//CurAvatar와 RenderList의 변경이 일어남
	void ChangeAvatar(AvatarType _Type, AvatarParts _Parts);

protected:

private:

	//아바타를 생성하는 함수 > 렌더러에 애니메이션을 추가해주는 함수
	//주의! 아직 애니메이션을 전부 만들지 않음
	void CreateAvatar(const std::string& _AvatarFolderName, AvatarParts _Parts, AvatarType _Type, AvatarLayer _Layer);

	std::string EnumToString(PlayerAnimations _Ani);
	std::string EnumToString(AvatarType _Type);

	//어떤 아바타가 무슨 렌더러를 쓰는지 확인하는 함수
	std::vector<AvatarLayer> GetRendererLayer(AvatarParts _Parts, AvatarType _Type);
	//어떤 아바타가 무슨 렌더러를 가리는지(지우는지) 확인하는 함수
	std::vector<GameEngineTextureRenderer*> GetHideRendererList(AvatarParts _Parts, AvatarType _Type);



	//렌더러를 반환하는 함수
	//내가 HairRenderer_a를 쓰고싶은데 이걸 switch분기문으로 구현하기에는 빡쌔서 함수로 만듬
	//주의! 아직 분기를 나눈것이 많지 않음
	GameEngineTextureRenderer* GetRenderer(AvatarParts _Parts, AvatarLayer _Layer);

	float LayerOffset_;

	//아바타 렌더러 추가하면 확인해야할 것
	// 
	//아바타매니저에 렌더러 추가
	//아바타 매니저 LinkPlayerToAvatar 에서 렌더러의 조치
	//ChangeMotion에서 해당 부위가 있는지 확인
	//GetRenderer, SelectRenderer에 해랑 렌더러 추가
	//디폴트 아바타일경우 렌더러 리스트랑 CurAvatar에 추가해주기

	GameEngineTextureRenderer* SkinRenderer_;
	GameEngineTextureRenderer* HairRenderer_a_;
	GameEngineTextureRenderer* HairRenderer_d_;
	GameEngineTextureRenderer* WeaponRenderer_b_;
	GameEngineTextureRenderer* WeaponRenderer_c_;

	GameEngineTextureRenderer* PantsRenderer_a_;
	GameEngineTextureRenderer* PantsRenderer_b_;
	GameEngineTextureRenderer* PantsRenderer_d_;

	GameEngineTextureRenderer* CoatRenderer_a_;
	GameEngineTextureRenderer* CoatRenderer_b_;
	GameEngineTextureRenderer* CoatRenderer_c_;
	GameEngineTextureRenderer* CoatRenderer_d_;


	GameEngineTextureRenderer* ShoesRenderer_a_;
	GameEngineTextureRenderer* ShoesRenderer_b_;

	GameEngineTextureRenderer* BeltRenderer_c_;
	GameEngineTextureRenderer* BeltRenderer_d_;

	GameEngineTextureRenderer* CapRenderer_a_;
	GameEngineTextureRenderer* CapRenderer_b_;
	GameEngineTextureRenderer* CapRenderer_c_;

	GameEngineTextureRenderer* ShadowRenderer_;


	//이 아바타는 이 렌더러를 사용합니다를 보관하는 컨테이너
	//여기에 넣어줘야 화면에 랜더링 된다
	//Renderer_b등을 안쓰는 아바타 부위가 존재해
	//그래서 아바타가 사용하는 렌더러를 RenderList에 등록해서 그것만 렌더하게 만들려 한거야
	std::multimap<AvatarParts, GameEngineTextureRenderer*> RenderList_;

	//현재 장착하고 있는 아바타가 뭐냐
	std::map<AvatarParts, AvatarType> CurAvatar_;
};

