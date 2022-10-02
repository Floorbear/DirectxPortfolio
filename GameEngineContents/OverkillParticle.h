#pragma once
#include <GameEngineCore/GameEngineActor.h>
class OverkillParticle : public GameEngineActor
{
public:
	OverkillParticle();
	~OverkillParticle();

	OverkillParticle(const OverkillParticle& _Other) = delete;
	OverkillParticle(const OverkillParticle&& _Other) noexcept = delete;
	OverkillParticle& operator=(const OverkillParticle& _Ohter) = delete;
	OverkillParticle& operator=(const OverkillParticle&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Normal_ = nullptr;
	GameEngineTextureRenderer* Dodge_ = nullptr;
};
