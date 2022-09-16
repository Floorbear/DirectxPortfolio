#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"

class GoreCross : public GameEngineActor
{
public:
	GoreCross();
	~GoreCross();

	GoreCross(const GoreCross& _Other) = delete;
	GoreCross(const GoreCross&& _Other) noexcept = delete;
	GoreCross& operator=(const GoreCross& _Ohter) = delete;
	GoreCross& operator=(const GoreCross&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void StiffnessUpdate(float _DeltaTime);
	void End() override;

	float GetDirX();

private:
	std::map<std::string, GameEngineTextureRenderer*> Renderer_;

	struct Alpha
	{
		float Slash = 1.0f;
		float Main = 1.0f;
	};

	float Speed_;
	float Stiffness_;
	Timer MoveTimer_;
	bool IsEnd_;
	bool IsSlashEnd_;
	bool IsAttCountPlus_;
};
