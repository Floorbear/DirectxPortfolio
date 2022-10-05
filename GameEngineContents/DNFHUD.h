#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"

class GaugeRenderer;
class DNFHUD : public GameEngineActor
{
public:
	DNFHUD();
	~DNFHUD();

	DNFHUD(const DNFHUD& _Other) = delete;
	DNFHUD(const DNFHUD&& _Other) noexcept = delete;
	DNFHUD& operator=(const DNFHUD& _Ohter) = delete;
	DNFHUD& operator=(const DNFHUD&& _Other) noexcept = delete;

	Timer EndingTimer_ = Timer();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void CutSceneUpdate(float _DeltaTime);

private:

	void HPBarUpdate(float _DeltaTime);
	void MPBarUpdate(float _DeltaTime);
	void IconPosUpdate(float _DeltaTime);
	void SkillRendererInit();
	void SkillIconUpdate(float _DeltaTime);
	GameEngineUIRenderer* MainRenderer_;
	GameEngineUIRenderer* EndingRenderer_ = nullptr;

	GaugeRenderer* HPRenderer_;
	GaugeRenderer* MPRenderer_;

	//��ų ��Ÿ�� ����
	std::vector<GameEngineUIRenderer*> SkillIconBackground_;
	std::vector<GaugeRenderer*> SkillIcon_; //13: ���� ������
	std::vector<GameEngineUIRenderer*> ShortCut_;
	std::list<GaugeRenderer*> FlashSkillIcon_; //��Ÿ���� �� ���� ��½�� �༮���� ����
	std::map<std::string, int> StringToInt_;

	//HP�� ����
	int PrevHp_;
	float LerpHp_;
	float GauageDelta_HP_;

	//MP�� ����
	int PrevMP_;
	float LerpMP_;
	float GauageDelta_MP_;

	//������ �ƽ�
	GameEngineUIRenderer* CutScene_ = nullptr;
	float CutSceneAccTime_ = 0.f;
	float4 RootPos_ = {};
	float4 DestPos_ = {};

	//���� ���
	GameEngineUIRenderer* Coin_ = nullptr;

	struct DefaultValue
	{
		float4 SkillIconBackPos;
		float4 ShortCutPos;
		float4 SkillIconPos;
	};
	DefaultValue Value_;
};
