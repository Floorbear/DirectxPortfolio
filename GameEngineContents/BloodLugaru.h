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
	GameEngineStateManager StateManager_;
	GameEngineCollision* AttackRangeCol_;
	Player_Main* Player_;

	//플레이어를 발견하는 거리
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


	void HitColCheck();
	bool HitCheck(AttackType _Type);//파라미터 : 확인할 공격 타입
	bool AboveHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other);
	bool BelowHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other);

	void ChangeHitColTrans(std::string _State);




	//Idle 관련 변수들
	bool IsIdleFirst_;

	//Attack_1 관련 변수들
	float4 Attack_1_Scale_;
	float4	Attack_1_Pos_;
	bool IsAttack_1_End_;

	//Back 관련 변수들
	float4 BackMoveDir_;

	//Hit 관련 변수들
	GameEngineCollision* HitAbove_;
	GameEngineCollision* HitBelow_;
	AttackData PrevHitData_;


	//타이머 
	Timer Attack_1_Timer_;
	Timer Idle_Timer_;
	Timer Back_Timer_;
	Timer Chase_Timer_;
	Timer Hit_Timer_;
	Timer Down_Timer_;
	Force Force_;


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
	};
	DefaultValue Value_;

};

