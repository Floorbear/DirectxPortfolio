#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"

class BoomEffect : public GameEngineActor
{
public:
	BoomEffect();
	~BoomEffect();

	BoomEffect(const BoomEffect& _Other) = delete;
	BoomEffect(const BoomEffect&& _Other) noexcept = delete;
	BoomEffect& operator=(const BoomEffect& _Ohter) = delete;
	BoomEffect& operator=(const BoomEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* MainRenderer_;
	GameEngineTextureRenderer* YellowRenderer_;

	Timer RedTimer_;
	Timer YellowTimer_;
};
