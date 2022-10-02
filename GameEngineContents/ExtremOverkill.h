#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"

class ExtremOverkill : public GameEngineActor
{
public:
	ExtremOverkill();
	~ExtremOverkill();

	ExtremOverkill(const ExtremOverkill& _Other) = delete;
	ExtremOverkill(const ExtremOverkill&& _Other) noexcept = delete;
	ExtremOverkill& operator=(const ExtremOverkill& _Ohter) = delete;
	ExtremOverkill& operator=(const ExtremOverkill&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	float ScaleRatio_ = 1.0f;

	int DebugInt = 0;

	int Phase_ = 0;

	//Phase 0
	Timer Blood_0_Alpha_ = 1.0f;
	//phase 1
	Timer Particle_SpawnIter_ = 0.2f;
	Timer Phase_1_Timer = 2.8f;
	Timer ShakeIter = 0.2f;

	//Phase 2
	Timer Blood_1_Alpha_ = 1.0f;
	bool IsParticleSpawn_ = false;
	bool IsBoomSpawn_0_ = false;
	bool IsBoomSpawn_1_ = false;
	bool IsBoomSpawn_2_ = false;

	void UpdateParticle(float _DeltaTime);

	GameEngineTextureRenderer* Impact_ = nullptr;
	GameEngineTextureRenderer* Floor_1_ = nullptr;
	GameEngineTextureRenderer* Floor_2_ = nullptr;
	GameEngineTextureRenderer* Smoke_ = nullptr;
	GameEngineTextureRenderer* Blood_0_ = nullptr;
	GameEngineTextureRenderer* Blood_1_ = nullptr;
	GameEngineTextureRenderer* Blood_2_ = nullptr;

	std::list<GameEngineTextureRenderer*> AllRenderer_;
};
