#pragma once
#include "DNFMonster.h"

class HeartFox : public DNFMonster
{
public:
	HeartFox();
	~HeartFox();

	HeartFox(const HeartFox& _Other) = delete;
	HeartFox(const HeartFox&& _Other) noexcept = delete;
	HeartFox& operator=(const HeartFox& _Ohter) = delete;
	HeartFox& operator=(const HeartFox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void InitAdditionalRenderer() override;
	void Update(float _DeltaTime) override;
	void End() override;

	virtual void CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc) override;
	virtual void ChangeDNFAnimation(const std::string& _Name) override;

	void Attack_2_Start(const StateInfo _Info);
	void Attack_2_Update(float _DeltaTime, const StateInfo _Info);
	void Attack_2_End(const StateInfo _Info);

	void Angry_Start(const StateInfo _Info);
	void Angry_Update(float _DeltaTime, const StateInfo _Info);

	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;

	std::string CheckAdditionalPattern(float _DeltaTime) override;

	GameEngineTextureRenderer* AvaRenderer_;
	GameEngineTextureRenderer* AvaRenderer_Angry_;
	GameEngineTextureRenderer* ClowRenderer_;

	//Attack_2 관련
	Timer Attack_2_Wait_Timer_;
	float4 Attack_2_TargetPos_;
	Timer Attack_2_Timer_;

	//화내는거 관련
	bool IsAngry_ = false;
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
