#pragma once
#include "DNFRenderObject.h"
#include "DNFMath.h"
#include <GameEngineCore/GameEngineStateManager.h>

class Player_Main;
class GameEngineCollision;
class DNFMonster : public DNFRenderObject
{
public:
	DNFMonster();
	~DNFMonster();

	DNFMonster(const DNFMonster& _Other) = delete;
	DNFMonster(const DNFMonster&& _Other) noexcept = delete;
	DNFMonster& operator=(const DNFMonster& _Ohter) = delete;
	DNFMonster& operator=(const DNFMonster&& _Other) noexcept = delete;

	int ID_;

protected:
	void InitMonster();
	void UpdateMonster(float _DeltaTime);
	void CheckColMap();
	void End() override;

	float AniSpeed_;

protected:
	GameEngineCollision* AttackRangeCol_;
	Player_Main* Player_;

	//플레이어를 발견하는 거리
	float FindRange_;

	void InitAniNState();
	virtual void CreateMonsterAni() {};
	virtual void CreateMonsterAniFunc() {};

	void InitCol();

	void IdleStart(const StateInfo _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo _Info);

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

	//Idle 관련 변수들
	bool IsIdleFirst_;

	//공격관련
	float4 Attack_1_Scale_;
	float4	Attack_1_Pos_;
	bool IsAttack_1_End_;
	GameEngineCollision* AttackCol_;
	bool CanHitAttack1();
	int CalAtt(int _Att);

	//Back 관련 변수들
	float4 BackMoveDir_;

	//체력관련
	int PerHP_;
	void HPBarUpdate() override;

	//타이머
	void TimerCheck(float _DeltaTime);
	Timer Attack_1_Timer_;
	Timer Idle_Timer_;
	Timer Back_Timer_;
	Timer Chase_Timer_;
	Timer Hit_Timer_;

	//사망
	float DieAlpha_;
	bool IsDieEffect_;

	//DefaultVales
	virtual void InitDefaultValue();
	struct DefaultValue
	{
		int HitZRange;

		float4 MonsterTextureSize_ = { 315,315,1 };
		float4 IdleAboveColPos;
		float4 IdleAboveColScale;
		float4 IdleBelowColPos;
		float4 IdleBelowColScale;
		float4 HitAboveColPos;
		float4 HitAboveColScale;
		float4 HitBelowColPos;
		float4 HitBelowColScale;
		float4 DownAboveColPos;
		float4 DownAboveColScale;
		float4 DownBelowColPos;
		float4 DownBelowColScale;
		float4 DieEffectAddPos = { 0,-40 };

		float Down_Time;
		float Down_God_Time;

		int Attack_1_Att = 1200;

		MonsterType Type;

		std::string DieParticleName;
		float4 DieParticleSize;
	};
	DefaultValue Value_;

	//디버그 관련
	void StartDebug();
	void UpdateDebug();
};
