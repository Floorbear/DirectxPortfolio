#pragma once
#include "DNFRenderObject.h"
#include "DNFBackground.h"
class Elvenguard_Background : public DNFBackground
{
public:
	Elvenguard_Background();
	~Elvenguard_Background();

	Elvenguard_Background(const Elvenguard_Background& _Other) = delete;
	Elvenguard_Background(const Elvenguard_Background&& _Other) noexcept = delete;
	Elvenguard_Background& operator=(const Elvenguard_Background& _Ohter) = delete;
	Elvenguard_Background& operator=(const Elvenguard_Background&& _Other) noexcept = delete;

	void Init();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	bool IsInit_ = false;
	GameEngineTextureRenderer* NearRenderer_ = nullptr;
	GameEngineTextureRenderer* Linus_ = nullptr;

	GameEngineCollision* UpDoorCol_ = nullptr;
	GameEngineCollision* LeftDoorCol_ = nullptr;
};
