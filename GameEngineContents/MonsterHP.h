#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum MonsterType
{
	BloodLugaruM
};
struct MonsterHPData //Cur , Per
{
	int ID; //�ν��Ͻ��� ������ NUmber
	float CurHP;
	float PerHP;//HP�� ������ ��Ÿ���� HP�� �� ex���� ü�� 1500 PerHP 1000 >> ȭ�鿡 ��Ÿ���°� 2��
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

	void ResetHP();

private:
	GameEngineUIRenderer* HPFrame_;
	std::vector<GaugeRenderer*> HPBar_;
	std::vector<GameEngineUIRenderer*> HPFont_;
	
	std::map<int,MonsterHPData> Data_; // ���ͷκ��� ������ �޾ƿ;���
	int CurID_;

	struct DefaultValue
	{
		float4 UIPos = {-625,230,-1000};
		float4 HPBarPos = {490,-33,0 };
		float4 HPFontPos_0 = { 855,-20,0 };
		float4 HPFontPos_1 = { 877,-20,0 };
		float4 HPFontPos_2 = { 904,-20,0 };
	};
	DefaultValue Value_;
};

