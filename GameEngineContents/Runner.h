#pragma once
#include "DNFMonster.h"

class Runner : public DNFMonster
{
public:
	Runner();
	~Runner();

	Runner(const Runner& _Other) = delete;
	Runner(const Runner&& _Other) noexcept = delete;
	Runner& operator=(const Runner& _Ohter) = delete;
	Runner& operator=(const Runner&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void SelfDestruct_Start(const StateInfo _Info);
	void SelfDestruct_Update(float _DeltaTime, const StateInfo _Info);

	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;

	Timer Check_SelfDestruct_Timer_;
	Timer SelfDestructCol_Timer_;
	struct IvanValue
	{
		float4 SelfStructAttackPos = { 0,-10,0 };
		float4 SelfStructAttackScale = { 180.0f,100.0f };

		int SelfDstructAtt = 5000;
	};
	IvanValue IvanValue_;
};
