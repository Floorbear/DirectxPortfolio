#pragma once
#include <GameEngineCore/GameEngineActor.h>

class DieEffect : public GameEngineActor
{
public:
	DieEffect();
	~DieEffect();

	DieEffect(const DieEffect& _Other) = delete;
	DieEffect(const DieEffect&& _Other) noexcept = delete;
	DieEffect& operator=(const DieEffect& _Ohter) = delete;
	DieEffect& operator=(const DieEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	float DieFlashAlpha_;
	GameEngineTextureRenderer* DieFlash_;
};
