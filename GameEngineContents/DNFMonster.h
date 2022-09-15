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

	//�÷��̾ �߰��ϴ� �Ÿ�
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

	//Idle ���� ������
	bool IsIdleFirst_;

	//���ݰ���
	float4 Attack_1_Scale_;
	float4	Attack_1_Pos_;
	bool IsAttack_1_End_;
	GameEngineCollision* AttackCol_;
	bool CanHitAttack1();
	int CalAtt(int _Att);

	//Back ���� ������
	float4 BackMoveDir_;

	//ü�°���
	int PerHP_;
	void HPBarUpdate() override;

	//Ÿ�̸�
	void TimerCheck(float _DeltaTime);
	Timer Attack_1_Timer_;
	Timer Idle_Timer_;
	Timer Back_Timer_;
	Timer Chase_Timer_;
	Timer Hit_Timer_;

	//���
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

	//����� ����
	void StartDebug();
	void UpdateDebug();
};
