#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"

//애니메이션의Pause기능을 임의로 사용할 수 없다.
//Why?? 경직,역경직에서 애니메이션의 Pause를 건들기 때문에
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

	bool IsCallPlayerEnd_; //PlayerEnd는 딱 한번만 호출되어야 한다. >> 그렇지 않으면 Player::IsAttackEnd가 계속 true상태로 고정됨
};
