#pragma once
#include "DNFRenderObject.h"
#include "DNFMath.h"
#include "DNFTransition.h"
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

	//추가 패턴
	virtual std::string CheckAdditionalPattern(float _DeltaTime) { return ""; }

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
	void StartYForce();
	void AirborneUpdate(float _DeltaTime, const StateInfo _Info);

	void DownStart(const StateInfo _Info);
	void DownUpdate(float _DeltaTime, const StateInfo _Info);

	void DieStart(const StateInfo _Info);
	void DieUpdate(float _DeltaTime, const StateInfo _Info);

	void ChangeHitColTrans(std::string _State);

	//슈퍼아머 관련
	GameEngineTextureRenderer* SuperArmorRenderer_;
	float4 SuperArmorScale_;
	float SuperArmorMulTime_;
	void StartSuperArmor(float _SuperArmorTime);
	void CopyRendererUpdate(float _DeltaTime);
	Timer SuperArmor_Hit_Timer_;
	std::string PrevHitName_;

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

	//출혈상태
	void UpdateBleeding(float _DeltaTime);
	void CheckBleeding(int _RandomValue) override;
	Timer Bleeding_Timer_;
	GameEngineTextureRenderer* BleedingRenderer_;
	float Bleed_Blink_Time_;

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

		float Default_Frction = 700.0f;

		//Att_1 관련
		float Attack_1_CoolTime = 4.0f;
		int Attack_1_Att = 1200;

		MonsterType Type;

		std::string DieParticleName;
		float4 DieParticleSize;

		//스피드
		float Speed = 135.0f;

		//슈퍼아머
		float4 SuperArmorPos = { 0.0f,0.0f };
		float4 SuperArmorScale = { 216.0f,206.0f }; //슈퍼아머 상태
		float4 StartSuperArmorScale = { 300.f,300.f };
		float SuperArmorMul = 1000.0f;

		//출혈
		float4 BleedingSpawnPos = { 20,35 };
		float4 BleedingPos = { 10.0f,60.0f,-1 };
		float4 BleedingScale = { -0.7f,0.7f,0.7f };
	};
	DefaultValue Value_;

	//디버그 관련
	void StartDebug();
	void UpdateDebug();

	//전이 관련
	std::map<std::string, DNFTransition> Transition_;
private:
	void InitTransition();
protected:
};
