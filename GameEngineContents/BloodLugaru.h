#pragma once
#include "DNFMonster.h"

class Bloodlugaru : public DNFMonster
{
public:
	Bloodlugaru();
	~Bloodlugaru();

	Bloodlugaru(const Bloodlugaru& _Other) = delete;
	Bloodlugaru(const Bloodlugaru&& _Other) noexcept = delete;
	Bloodlugaru& operator=(const Bloodlugaru& _Ohter) = delete;
	Bloodlugaru& operator=(const Bloodlugaru&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;
};
