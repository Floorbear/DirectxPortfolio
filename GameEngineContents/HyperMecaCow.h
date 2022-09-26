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

	void Attack_2_Start(const StateInfo _Info); //���� ����
	void Attack_2_Update(float _DeltaTime, const StateInfo _Info);
	void Attack_2_End(const StateInfo _Info);

	void UpperAttack_Start(const StateInfo _Info); //��� ������
	void UpperAttack_Update(float _DeltaTime, const StateInfo _Info);
	void UpperAttack_End(const StateInfo _Info);

	void Breath_Start(const StateInfo _Info); //�극������
	void Breath_Update(float _DeltaTime, const StateInfo _Info);
	void Breath_End(const StateInfo _Info);

	void CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc) override;
	void ChangeDNFAnimation(const std::string& _Name) override;
	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;
	void InitAdditionalRenderer() override;

	std::string CheckAdditionalPattern(float _DeltaTime) override;

	GameEngineTextureRenderer* WeaponRenderer_;
	//�߰� ���� �˻� Ÿ�̸�
	Timer AdditonAttack_Timer_; //�ϴ� �� �ð��� ������, ��Ÿ���� �ٵ� �극��, ��������, ���� ��� �� ������ ����Ѵ�.

	//Attack_2 ����
	float Attack_2_CoolTime = 18.0f;
	Timer Attack_2_CoolTimer_ = 20.0f;
	Timer Attack_2_Wait_Timer_;
	Timer Attack_2_Change_Timer_;

	//��� ������ ���ϰ���
	bool IsUpperAttackEnd = false;
	Timer UpperAttack_CoolTimer_ = 10.0f;

	//�극�� ���� ����
	GameEngineTextureRenderer* BreathFront_;
	GameEngineTextureRenderer* BreathBack_;
	bool IsBreathEnd_ = false;
	float4 BreathPos_ = { 180.f,9.f ,0 };
	Timer Breath_CoolTimer = 2.0f;

	float4 Attack_2_Pos_ = { 0.0f,-38.0f,-500.0f };
};
