#pragma once
#include "DNFMonster.h"
class HyperMecaCow : public DNFMonster
{
public:
	HyperMecaCow();
	~HyperMecaCow();

	HyperMecaCow(const HyperMecaCow& _Other) = delete;
	HyperMecaCow(const HyperMecaCow&& _Other) noexcept = delete;
	HyperMecaCow& operator=(const HyperMecaCow& _Ohter) = delete;
	HyperMecaCow& operator=(const HyperMecaCow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void CheckCoolTime(float _DeltaTime);
	void End() override;

	void Attack_2_Start(const StateInfo _Info); //돌진 공격
	void Attack_2_Update(float _DeltaTime, const StateInfo _Info);
	void Attack_2_End(const StateInfo _Info);

	void UpperAttack_Start(const StateInfo _Info); //밥상 뒤집기
	void UpperAttack_Update(float _DeltaTime, const StateInfo _Info);
	void UpperAttack_End(const StateInfo _Info);

	void Breath_Start(const StateInfo _Info); //브레스공격
	void Breath_Update(float _DeltaTime, const StateInfo _Info);
	void Breath_End(const StateInfo _Info);

	void CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc) override;
	void ChangeDNFAnimation(const std::string& _Name) override;
	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;
	void InitAdditionalRenderer() override;

	std::string CheckAdditionalPattern(float _DeltaTime) override;

	GameEngineTextureRenderer* WeaponRenderer_;
	//추가 공격 검사 타이머
	Timer AdditonAttack_Timer_; //일단 이 시간이 지난후, 쿨타임이 다된 브레스, 밥상뒤집기, 돌진 등에서 한 패턴을 사용한다.

	//Attack_2 관련
	float Attack_2_CoolTime = 18.0f;
	Timer Attack_2_CoolTimer_ = 20.0f;
	Timer Attack_2_Wait_Timer_;
	Timer Attack_2_Change_Timer_;

	//밥상 뒤집기 패턴관련
	bool IsUpperAttackEnd = false;
	Timer UpperAttack_CoolTimer_ = 10.0f;

	//브레스 패턴 관련
	GameEngineTextureRenderer* BreathFront_;
	GameEngineTextureRenderer* BreathBack_;
	bool IsBreathEnd_ = false;
	float4 BreathPos_ = { 180.f,9.f ,0 };
	Timer Breath_CoolTimer = 2.0f;

	float4 Attack_2_Pos_ = { 0.0f,-38.0f,-500.0f };
};
