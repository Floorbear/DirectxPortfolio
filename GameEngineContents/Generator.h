#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "SummonCircle.h"
#include "DNFMath.h"
class Generator : public GameEngineActor
{
public:
	Generator();
	~Generator();

	Generator(const Generator& _Other) = delete;
	Generator(const Generator&& _Other) noexcept = delete;
	Generator& operator=(const Generator& _Ohter) = delete;
	Generator& operator=(const Generator&& _Other) noexcept = delete;

	template <typename MonsterType>
	void Init(int _SpawnCount, float _SpawnIter)
	{
		SpawnFunction_ = std::bind(&Generator::Spawn<MonsterType>, this);
		SpawnCount_ = _SpawnCount;
		SpawnTimer_ = _SpawnIter;
		SpawnTimer_.StartTimer();
	}

	template <typename MonsterType>
	void Spawn()
	{
		SummonCircle* NewCircle = GetLevel()->CreateActor< SummonCircle>();
		NewCircle->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4(-60, 30));
		NewCircle->SummonMonster<MonsterType>();
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	std::function<void()> SpawnFunction_ = nullptr;
	Timer SpawnTimer_;
	int SpawnCount_ = -1;

private:
	GameEngineTextureRenderer* MainRenderer_ = nullptr;
	GameEngineTextureRenderer* FloorRenderer_ = nullptr;

	GameEngineCollision* ObjecCol_ = nullptr;
};
