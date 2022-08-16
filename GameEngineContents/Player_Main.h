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

	float4 GetBotPos()
	{
		return GetTransform().GetWorldPosition() - float4(0, 250, 0, 0);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void ChangeAvatar();
	void ChaseCamera();

	//UI
	GameEngineUIRenderer* UIRenderer_;

	//아바타 관련 변수들
	AvatarManager AvatarManager_;

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







	//아바타 렌더러 추가하면 확인해야할 것
	// 
	//아바타매니저에 렌더러 추가
	//아바타 매니저 LinkPlayerToAvatar 에서 렌더러의 조치
	//ChangeMotion에서 해당 부위가 있는지 확인
	//GetRenderer, SelectRenderer에 해랑 렌더러 추가
	//디폴트 아바타일경우 렌더러 리스트랑 CurAvatar에 추가해주기


	int Toggle1_;
	int Toggle2_;
	int Toggle3_;
	int Toggle4_;
	int Toggle5_;
	int Toggle6_;

	float4 PrevPos_;
};

