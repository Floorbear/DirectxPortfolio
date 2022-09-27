#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "VilmarkLevel.h"
#include "DNFMonster.h"
#include "DNFLevel.h"

class DNFMonster;
class SummonCircle : public GameEngineActor
{
public:
	SummonCircle();
	~SummonCircle();

	SummonCircle(const SummonCircle& _Other) = delete;
	SummonCircle(const SummonCircle&& _Other) noexcept = delete;
	SummonCircle& operator=(const SummonCircle& _Ohter) = delete;
	SummonCircle& operator=(const SummonCircle&& _Other) noexcept = delete;

	template <typename MonsterType>
	void SummonMonster(float4 _MovePos = {})
	{
		MovePos_ = _MovePos;
		SpawnFunction_ = std::bind(&SummonCircle::Summon<MonsterType>, this, std::placeholders::_1);
	}

protected:
	template <typename MonsterType>
	void Summon(float4 _MovePos)
	{
		DNFMonster* NewMonster = dynamic_cast<VilmarkLevel*>(GetLevel())->CreateMonster<MonsterType>(GetTransform().GetWorldPosition() + _MovePos);
	}

	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* PivotTex_;
	GameEngineTextureRenderer* SummonFront_;
	GameEngineTextureRenderer* SummonBack_;

	std::function<void(float4)> SpawnFunction_;

	float4 MovePos_ = {};
};
