#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"

class DieEffect : public GameEngineActor
{
public:
	DieEffect();
	~DieEffect();

	DieEffect(const DieEffect& _Other) = delete;
	DieEffect(const DieEffect&& _Other) noexcept = delete;
	DieEffect& operator=(const DieEffect& _Ohter) = delete;
	DieEffect& operator=(const DieEffect&& _Other) noexcept = delete;

	void Init(std::string _ParticleFolderName);
	void Option(bool _SpawnDieFlash, float _DieTimeAcc, float AccYPos = 0.f);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void UpdateParticle(float _DeltaTime);
	void DieFlashUpdate(float _DeltaTime);
	void End() override;

	float DieTimeAcc_ = 1.f;
private:
	float DieFlashAlpha_;
	float ScaleRatio_;
	GameEngineTextureRenderer* DieFlash_;
	std::string DieParticleColor_;
	std::vector<GameEngineTextureRenderer*> DieParticle_;
	Timer DieFlashTimer_;
	std::vector<Force> Force_;
	std::vector<float> RandomYSize_;
	std::vector<float> RandomRot_;
	float ParticleTime_;

	float OptionYPos_ = 0.f;

	struct DefaultValue
	{
		float SpawnSizeParticleX = 100.0f;
		float SpawnSizeParticleY = 100.0f;

		float ForceX = 120.0f;
		float ForceY = 600.0f;
		float Friction = 400.0f;
		float Gravity = 1940.0f;

		float RandomYSize = 50.0f;
	};

	DefaultValue Value;
};
