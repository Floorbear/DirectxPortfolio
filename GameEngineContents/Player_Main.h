#pragma once
#include "DNFRenderObject.h"
#include "AvatarManager.h"

class Player_Main : public DNFRenderObject
{
	friend AvatarManager;
public:
	Player_Main();
	~Player_Main();


	Player_Main(const Player_Main& _Other) = delete;
	Player_Main(const Player_Main&& _Other) noexcept = delete;
	Player_Main& operator=(const Player_Main& _Ohter) = delete;
	Player_Main& operator=(const Player_Main&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	AvatarManager AvatarManager_;

	GameEngineTextureRenderer* HairRenderer_a_;
	GameEngineTextureRenderer* HairRenderer_d_;
	GameEngineTextureRenderer* WeaponRenderer_b_;
	GameEngineTextureRenderer* WeaponRenderer_c_;

	GameEngineTextureRenderer* PantsRenderer_a_;
	GameEngineTextureRenderer* PantsRenderer_b_;
	GameEngineTextureRenderer* PantsRenderer_d_;

	//아바타 렌더러 추가하면 확인해야할 것
	//아바타매니저에 렌더러 추가
	//아바타 매니저 LinkPlayerToAvatar 에서 렌더러의 조치
	//ChangeMotion에서 해당 부위가 있는지 확인
	//GetRenderer, SelectRenderer에 해랑 렌더러 추가


	bool QToggle_;
	bool WToggle_;
};

