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

	void HPAndMPBarUpdate(float _DeltaTime);
	void IconPosUpdate(float _DeltaTime);
	void SkillRendererInit();
	GameEngineUIRenderer* MainRenderer_;

	GaugeRenderer* HPRenderer_;
	GaugeRenderer* MPRenderer_;

	// 6 : 어퍼슬래쉬
	std::vector<GameEngineUIRenderer*> SkillIconBackground_;
	std::vector<GaugeRenderer*> SkillIcon_;
	std::vector<GameEngineUIRenderer*> ShortCut_;


	int PrevHp_;
	float LerpHp_;
	float GauageDelta_;

	struct DefaultValue
	{
		float4 SkillIconBackPos;
		float4 ShortCutPos;
		float4 SkillIconPos;
	};
	DefaultValue Value_;
};

