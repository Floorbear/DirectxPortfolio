#pragma once
#include "DNFMonster.h"
#include "DNFMath.h"

class MiniTau : public DNFMonster
{
public:
	MiniTau();
	~MiniTau();

	MiniTau(const MiniTau& _Other) = delete;
	MiniTau(const MiniTau&& _Other) noexcept = delete;
	MiniTau& operator=(const MiniTau& _Ohter) = delete;
	MiniTau& operator=(const MiniTau&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void Attack_2_Start(const StateInfo _Info); //돌진공격
	void Attack_2_Update(float _DeltaTime, const StateInfo _Info);
	void Attack_2_End(const StateInfo _Info);

	void CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc) override;
	void ChangeDNFAnimation(const std::string& _Name) override;
	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;
	void InitAdditionalRenderer() override;

	std::string CheckAdditionalPattern(float _DeltaTime) override;

	GameEngineTextureRenderer* WeaponRenderer_;

	//Attack_2 관련
	float Attack_2_CoolTime = 15.0f;
	Timer Attack_2_CoolTimer_;
	Timer Attack_2_Wait_Timer_;
	Timer Attack_2_Change_Timer_;

	float4 Attack_2_Pos_ = { 0.0f,-38.0f * 0.31f,-500.0f };
};
