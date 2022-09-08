#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFGlobalValue.h"

class EffectActor : public GameEngineActor
{
public:
	EffectActor();
	~EffectActor();


	EffectActor(const EffectActor& _Other) = delete;
	EffectActor(const EffectActor&& _Other) noexcept = delete;
	EffectActor& operator=(const EffectActor& _Ohter) = delete;
	EffectActor& operator=(const EffectActor&& _Other) noexcept = delete;

	void InitEffect(Effect _Effect);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* EffectRenderer_;
};

