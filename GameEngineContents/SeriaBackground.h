#pragma once
#include "DNFBackground.h"
#include "DNFMath.h"

class DNFBackground;
class SeriaBackground : public DNFBackground
{
public:
	SeriaBackground();
	~SeriaBackground();

	SeriaBackground(const SeriaBackground& _Other) = delete;
	SeriaBackground(const SeriaBackground&& _Other) noexcept = delete;
	SeriaBackground& operator=(const SeriaBackground& _Ohter) = delete;
	SeriaBackground& operator=(const SeriaBackground&& _Other) noexcept = delete;

	void Init();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsInit_ = false;
	GameEngineTextureRenderer* Seria_ = nullptr;

	//∞‘¿Ã∆Æ
	GameEngineTextureRenderer* Gate_ = nullptr;
	GameEngineTextureRenderer* Gate_Effect_ = nullptr;

	GameEngineCollision* DoorCol_ = nullptr;
};
