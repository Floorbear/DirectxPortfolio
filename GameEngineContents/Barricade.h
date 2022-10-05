#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"

class Barricade : public GameEngineActor
{
public:
	Barricade();
	~Barricade();

	Barricade(const Barricade& _Other) = delete;
	Barricade(const Barricade&& _Other) noexcept = delete;
	Barricade& operator=(const Barricade& _Ohter) = delete;
	Barricade& operator=(const Barricade&& _Other) noexcept = delete;

	void Init(float _Time)
	{
		IsInit_ = true;
		DestroyTimer_.StartTimer(_Time);
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	Timer DestroyTimer_;
	bool IsInit_ = false;

private:
	GameEngineTextureRenderer* MainRenderer_ = nullptr;
	GameEngineCollision* ObjecCol_ = nullptr;
};
