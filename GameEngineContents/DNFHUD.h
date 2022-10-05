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

	//각성기 컷신
	GameEngineUIRenderer* CutScene_ = nullptr;
	float CutSceneAccTime_ = 0.f;
	float4 RootPos_ = {};
	float4 DestPos_ = {};

	//코인 사용
	GameEngineUIRenderer* Coin_ = nullptr;

	struct DefaultValue
	{
		float4 SkillIconBackPos;
		float4 ShortCutPos;
		float4 SkillIconPos;
	};
	DefaultValue Value_;
};
