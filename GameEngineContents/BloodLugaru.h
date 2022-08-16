#pragma once
#include "DNFRenderObject.h"
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

	//�÷��̾ �߰��ϴ� �Ÿ�
	float FindRange_;


	void IdleStart(const StateInfo _Info);
	void IdleUpdate(float _DeltaTime,const StateInfo _Info);

	void ChaseStart(const StateInfo _Info);
	void ChaseUpdate(float _DeltaTime, const StateInfo _Info);

	void Attack_1_Start(const StateInfo _Info);
	void Attack_1_Update(float _DeltaTime, const StateInfo _Info);
	void Attack_1_End(const StateInfo _Info);

	void BackStart(const StateInfo _Info);
	void BackUpdate(float _DeltaTime, const StateInfo _Info);

	bool AttackColCheck(GameEngineCollision* _this, GameEngineCollision* _Other);

	//Idle ���� ������
	bool IsIdleFirst_;

	//Attack_1 ���� ������
	float4 Attack_1_Scale_;
	float4	Attack_1_Pos_;
	bool IsAttack_1_End_;
	float Attack_1_Time_;

	//Back ���� ������
	float4 BackMoveDir_;

	//�ð����� �����̳�
	std::map<std::string, float> CurTime_; //������ DeltaTime�� �����ϴ� �����̳�
	std::map<std::string, float> DefaultTime_; //ó�� Set�� Time�� �����ϴ� �����̳� , �����Ǵ� Time�� Random�� �ִ� ����
	std::map<std::string, float> FloatValue_; //�̵��ӵ�, ��Ÿ� ���� ������ �����̳�


	//�ӽ� Value
	float Temp_;
};

