#pragma once
#include "DNFMonster.h"

class CrazyIvan : public DNFMonster
{
public:
	CrazyIvan();
	~CrazyIvan();

	CrazyIvan(const CrazyIvan& _Other) = delete;
	CrazyIvan(const CrazyIvan&& _Other) noexcept = delete;
	CrazyIvan& operator=(const CrazyIvan& _Ohter) = delete;
	CrazyIvan& operator=(const CrazyIvan&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void CheckIvanFury();
	void End() override;

	void SelfDestruct_Start(const StateInfo _Info);
	void SelfDestruct_Update(float _DeltaTime, const StateInfo _Info);

	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;

	std::string CheckAdditionalPattern() override;

	Timer Check_SelfDestruct_Timer_;

	struct IvanValue
	{
		float4 SelfStructAttackPos = { 0,-10,0 };
		float4 SelfStructAttackScale = { 180.0f,100.0f };

		int SelfDstructAtt = 5000;
	};
	IvanValue IvanValue_;
};
