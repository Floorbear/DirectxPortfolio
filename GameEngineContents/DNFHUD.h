#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	void HPBarUpdate(float _DeltaTime);
	void MPBarUpdate(float _DeltaTime);
	void IconPosUpdate(float _DeltaTime);
	void SkillRendererInit();
	void SkillIconUpdate(float _DeltaTime);
	GameEngineUIRenderer* MainRenderer_;

	GaugeRenderer* HPRenderer_;
	GaugeRenderer* MPRenderer_;

	//스킬 쿨타임 관련
	std::vector<GameEngineUIRenderer*> SkillIconBackground_;
	std::vector<GaugeRenderer*> SkillIcon_; //13: 어퍼 슬래쉬
	std::vector<GameEngineUIRenderer*> ShortCut_;
	std::list<GaugeRenderer*> FlashSkillIcon_; //쿨타임이 다 돌면 번쩍일 녀석들을 보관
	std::map<std::string, int> StringToInt_;

	//HP바 관련
	int PrevHp_;
	float LerpHp_;
	float GauageDelta_HP_;

	//MP바 관련
	int PrevMP_;
	float LerpMP_;
	float GauageDelta_MP_;

	struct DefaultValue
	{
		float4 SkillIconBackPos;
		float4 ShortCutPos;
		float4 SkillIconPos;
	};
	DefaultValue Value_;
};
