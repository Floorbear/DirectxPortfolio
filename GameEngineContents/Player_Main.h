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

	//내 공격카운트 << 몬스터가 같은 공격을 여러번 맞는 것을 방지
	int GetAttackCount()
	{
		return AttackCount_;
	}
	//아바타 관련 변수들
	AvatarManager AvatarManager_;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	//카메라 추적
	void ChaseCamera();
	//캐릭터의 충돌체 초기화
	void InitCol();

	//공격관련
	GameEngineCollision* MiddleAttackCol_;
	int AttackCount_;

	//UI
	GameEngineUIRenderer* UIRenderer_;


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


	//FSM
	// 아무키도 누르지 않으면 float4::zero리턴
	float4 GetMoveDir();
	GameEngineStateManager StateManager_;

	void IdleStart(const StateInfo _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo _Info);

	void MoveStart(const StateInfo _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo _Info);



};

