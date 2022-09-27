#pragma once
#include <GameEngineCore/GameEngineActor.h>
class HopSmash : public GameEngineActor
{
public:
	HopSmash();
	~HopSmash();

	HopSmash(const HopSmash& _Other) = delete;
	HopSmash(const HopSmash&& _Other) noexcept = delete;
	HopSmash& operator=(const HopSmash& _Ohter) = delete;
	HopSmash& operator=(const HopSmash&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	GameEngineTextureRenderer* Renderer_1_d_;
	GameEngineTextureRenderer* Renderer_1_n_;
	GameEngineTextureRenderer* Renderer_2_d_;
	GameEngineTextureRenderer* Renderer_2_n_;

	std::vector<GameEngineTextureRenderer*> AllRenderer_;

	bool IsEffectEnd_ = false;
	float Alpha_ = 1.0f;
};
