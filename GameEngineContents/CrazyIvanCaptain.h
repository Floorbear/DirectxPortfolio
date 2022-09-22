#pragma once
#include "DNFMonster.h"

class CrazyIvanCaptain : public DNFMonster
{
public:
	CrazyIvanCaptain();
	~CrazyIvanCaptain();

	CrazyIvanCaptain(const CrazyIvanCaptain& _Other) = delete;
	CrazyIvanCaptain(const CrazyIvanCaptain&& _Other) noexcept = delete;
	CrazyIvanCaptain& operator=(const CrazyIvanCaptain& _Ohter) = delete;
	CrazyIvanCaptain& operator=(const CrazyIvanCaptain&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void CheckIvanFury();
	void End() override;

	void SelfDestruct_Start(const StateInfo _Info);
	void SelfDestruct_Update(float _DeltaTime, const StateInfo _Info);

	void FuryChaseStart(const StateInfo _Info);
	void FuryChaseUpdate(float _DeltaTime, const StateInfo _Info);

	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;

	std::string CheckAdditionalPattern(float _DeltaTime) override;

	Timer Check_SelfDestruct_Timer_;
	Timer SelfDestructCol_Timer_;
	float4 SelfDestructTargetPos_;
	struct IvanValue
	{
		float4 SelfStructAttackPos = { 0,-10,0 };
		float4 SelfStructAttackScale = { 180.0f,100.0f };

		int SelfDstructAtt = 5000;
	};
	IvanValue IvanValue_;
};
