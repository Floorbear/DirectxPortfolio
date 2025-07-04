#pragma once
#include <GameEngineCore/GameEngineActor.h>

struct MonsterHPData //Cur , Per
{
	int ID; //인스턴스된 몬스터의 NUmber
	int CurHP;
	int PerHP;//HP바 한줄이 나타내는 HP의 양 ex현재 체력 1500 PerHP 1000 >> 화면에 나타나는것 2줄
	int MaxHP;
	MonsterType Type;
};

//최대 30줄까지 지원
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

	void SetHPBar(MonsterHPData _Data); //플레이어가 몬스터를 처음 때릴 때 HP바를 보여주기 위해 호출. 중복된 몬스터를 때릴 때 호출하면 X
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
	std::map<int, MonsterHPData> Data_; // 몬스터로부터 정보를 받아와야함
	std::vector<GameEngineUIRenderer*> HPFont_;
	std::vector<GaugeRenderer*> HPBar_;

	struct DefaultValue
	{
		float DeadHeadTime = 0.23f;
		float4 HPBarPos = { 490,-33,0 };
		float4 HPFontPos_0 = { 875,-20,0 };
		float4 HPFontPos_1 = { 897,-20,0 };
		float4 HPFontPos_2 = { 924,-20,0 };
		float4 MonsterHeadPos = { 2,-2, };
		float4 UIPos = { -625,230,-1000 };
		float4 CategoryPos = { 48,0 };
	};
	DefaultValue Value_;
};
