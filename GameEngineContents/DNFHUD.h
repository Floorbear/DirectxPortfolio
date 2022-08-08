#pragma once
#include <GameEngineCore/GameEngineActor.h>
class DNFHUD : public GameEngineActor
{
public:
	DNFHUD();
	~DNFHUD();


	DNFHUD(const DNFHUD& _Other) = delete;
	DNFHUD(const DNFHUD&& _Other) noexcept = delete;
	DNFHUD& operator=(const DNFHUD& _Ohter) = delete;
	DNFHUD& operator=(const DNFHUD&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineUIRenderer* MainRenderer_;
	GameEngineUIRenderer* HPRenderer_;
	GameEngineUIRenderer* MPRenderer_;

};

