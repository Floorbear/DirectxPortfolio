#pragma once
#include "DNFMonster.h"

class Ciel : public DNFMonster
{
public:
	Ciel();
	~Ciel();

	Ciel(const Ciel& _Other) = delete;
	Ciel(const Ciel&& _Other) noexcept = delete;
	Ciel& operator=(const Ciel& _Ohter) = delete;
	Ciel& operator=(const Ciel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void Attack_2_Start(const StateInfo _Info);
	void Attack_2_Update(float _DeltaTime, const StateInfo _Info);
	void Attack_2_End(const StateInfo _Info);

	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;

	std::string CheckAdditionalPattern(float _DeltaTime) override;

	//Attack_2 ฐüทร
	Timer Attack_2_Wait_Timer_;
	float4 Attack_2_TargetPos_;
	Timer Attack_2_Timer_;

	struct LugaruValue
	{
		float Attack_2_FrctionAcc = 0.0f;
		float Attack_2_ForceXAcc = 2.2f;
		float Attack_2_ForceY = 300.0f;
		float4 Attack_2_StartRange = { 200,40 };
		int Attack_2_Att = 1500;
		float Attack_2_CoolTime = 5.0f;
	};
	LugaruValue LugaruValue;
};
