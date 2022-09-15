#pragma once
#include <GameEngineCore/GameEngineActor.h>

struct MonsterHPData //Cur , Per
{
	int ID; //�ν��Ͻ��� ������ NUmber
	int CurHP;
	int PerHP;//HP�� ������ ��Ÿ���� HP�� �� ex���� ü�� 1500 PerHP 1000 >> ȭ�鿡 ��Ÿ���°� 2��
	int MaxHP;
	MonsterType Type;
};

//�ִ� 30�ٱ��� ����
class GaugeRenderer;
class MonsterHP : public GameEngineActor
{
public:
	MonsterHP();
	~MonsterHP();

	MonsterHP(const MonsterHP& _Other) = delete;
	MonsterHP(const MonsterHP&& _Other) noexcept = delete;
	MonsterHP& operator=(const MonsterHP& _Ohter) = delete;
	MonsterHP& operator=(const MonsterHP&& _Other) noexcept = delete;

	void SetHPBar(MonsterHPData _Data); //�÷��̾ ���͸� ó�� ���� �� HP�ٸ� �����ֱ� ���� ȣ��. �ߺ��� ���͸� ���� �� ȣ���ϸ� X
protected:
	void Start() override;
	void Update(float DeltaTime_) override;
	void End() override;

	void MonsterDeadCheck(float _DeltTime);
	void HPBarUpdate(float _DeltaTime);
	void ResetHP();
	void CheckType(MonsterType _Type);
	void SwitchDeadHead(float _DeltaTime);

private:
	float LerpValue_;
	float PlusValue_;
	float UIWaitingTime_;
	float DeadHeadTime_;
	int CurID_;
	GameEngineUIRenderer* HPFrame_;
	GameEngineUIRenderer* MonsterHead_;
	GameEngineUIRenderer* MonsterDead_;
	GameEngineUIRenderer* MonsterCategory_;
	std::map<int, float> PrevHP_;
	std::map<int, MonsterHPData> Data_; // ���ͷκ��� ������ �޾ƿ;���
	std::vector<GameEngineUIRenderer*> HPFont_;
	std::vector<GaugeRenderer*> HPBar_;

	struct DefaultValue
	{
		float DeadHeadTime = 0.23f;
		float4 HPBarPos = { 490,-33,0 };
		float4 HPFontPos_0 = { 875,-20,0 };
		float4 HPFontPos_1 = { 897,-20,0 };
		float4 HPFontPos_2 = { 924,-20,0 };
		float4 MonsterHeadPos = { 0,0, };
		float4 UIPos = { -625,230,-1000 };
		float4 CategoryPos = { 48,0 };
	};
	DefaultValue Value_;
};
