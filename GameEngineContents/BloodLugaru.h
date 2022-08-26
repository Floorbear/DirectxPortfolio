#pragma once
#include "DNFRenderObject.h"
#include "DNFMath.h"
#include <GameEngineCore/GameEngineStateManager.h>

class Player_Main;
class GameEngineCollision;
class BloodLugaru : public DNFRenderObject
{
public:
	BloodLugaru();
	~BloodLugaru();


	BloodLugaru(const BloodLugaru& _Other) = delete;
	BloodLugaru(const BloodLugaru&& _Other) noexcept = delete;
	BloodLugaru& operator=(const BloodLugaru& _Ohter) = delete;
	BloodLugaru& operator=(const BloodLugaru&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	float AniSpeed_;

private:
	GameEngineCollision* AttackRangeCol_;
	Player_Main* Player_;

	//�÷��̾ �߰��ϴ� �Ÿ�
	float FindRange_;

	void InitAniNState();

	void InitCol();


	void IdleStart(const StateInfo _Info);
	void IdleUpdate(float _DeltaTime,const StateInfo _Info);

	void ChaseStart(const StateInfo _Info);
	void ChaseUpdate(float _DeltaTime, const StateInfo _Info);

	void Attack_1_Start(const StateInfo _Info);
	void Attack_1_Update(float _DeltaTime, const StateInfo _Info);
	void Attack_1_End(const StateInfo _Info);

	void BackStart(const StateInfo _Info);
	void BackUpdate(float _DeltaTime, const StateInfo _Info);

	void HitStart(const StateInfo _Info);
	void HitUpdate(float _DeltaTime, const StateInfo _Info);

	void AirborneStart(const StateInfo _Info);
	void AirborneUpdate(float _DeltaTime, const StateInfo _Info);

	void DownStart(const StateInfo _Info);
	void DownUpdate(float _DeltaTime, const StateInfo _Info);

	void DieStart(const StateInfo _Info);
	void DieUpdate(float _DeltaTime, const StateInfo _Info);



	void ChangeHitColTrans(std::string _State);



	
	//Idle ���� ������
	bool IsIdleFirst_;

	//���ݰ���
	float4 Attack_1_Scale_;
	float4	Attack_1_Pos_;
	bool IsAttack_1_End_;
	GameEngineCollision* AttackCol_;
	bool CanHitAttack1();

	//Back ���� ������
	float4 BackMoveDir_;





	//Ÿ�̸� 
	void TimerCheck(float _DeltaTime);
	Timer Attack_1_Timer_;
	Timer Idle_Timer_;
	Timer Back_Timer_;
	Timer Chase_Timer_;
	Timer Hit_Timer_;
	Timer Down_Timer_;


	//DefaultVales
	void InitDefaultValue();
	struct DefaultValue
	{
		int HitZRange;

		float4 HitAboveColPos;
		float4 HitAboveColScale;
		float4 HitBelowColPos;
		float4 HitBelowColScale;
		float4 DownAboveColPos;
		float4 DownAboveColScale;
		float4 DownBelowColPos;
		float4 DownBelowColScale;

		float Down_Time;
		float Down_God_Time;
	};
	DefaultValue Value_;

};

