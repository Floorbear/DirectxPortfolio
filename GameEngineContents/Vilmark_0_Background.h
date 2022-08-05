#pragma once
#include "DNFBackground.h"

class Vilmark_0_Background : public DNFBackground
{
public:
	Vilmark_0_Background();
	~Vilmark_0_Background();


	Vilmark_0_Background(const Vilmark_0_Background& _Other) = delete;
	Vilmark_0_Background(const Vilmark_0_Background&& _Other) noexcept = delete;
	Vilmark_0_Background& operator=(const Vilmark_0_Background& _Ohter) = delete;
	Vilmark_0_Background& operator=(const Vilmark_0_Background&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* ColRenderer_;
};

