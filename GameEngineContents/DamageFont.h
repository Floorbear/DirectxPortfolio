#pragma once
#include <GameEngineCore/GameEngineActor.h>

class DamageFont : public GameEngineActor
{
public:
	DamageFont();
	~DamageFont();

	DamageFont(const DamageFont& _Other) = delete;
	DamageFont(const DamageFont&& _Other) noexcept = delete;
	DamageFont& operator=(const DamageFont& _Ohter) = delete;
	DamageFont& operator=(const DamageFont&& _Other) noexcept = delete;

	DamageFont* SetDamageFont(int _Value, int _Type);

protected:
	void Start();
	void Update(float _DeltaTime);
	void End();

	float GetDeathTime();
private:
	std::vector<GameEngineTextureRenderer*> FontRenderer_;

	float Speed_;
	float AlphaValue_;

	bool IsPlayerHitFont_;
};
