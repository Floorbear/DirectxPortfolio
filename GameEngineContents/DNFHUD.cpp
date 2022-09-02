#include "PreCompile.h"
#include "DNFHUD.h"

#include "DNFContentsMinimal.h"
#include "DNFLevel.h"
#include "DNFRenderObject.h"
#include "Player_Main.h"
#include "GaugeRenderer.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

DNFHUD::DNFHUD() :
	PrevHp_(-1),
	LerpHp_(),
	GauageDelta_(),
	SkillIconBackground_(),
	Value_()
{
	SkillIconBackground_.reserve(14);
}

DNFHUD::~DNFHUD()
{
}

void DNFHUD::Start()
{
	GetTransform().SetLocalMove(float4(0, 0, -1000));
	//UI렌더러
	MainRenderer_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	MainRenderer_->SetTexture("hud_frame.png");
	MainRenderer_->ScaleToTexture();
	MainRenderer_->SetPivot(PIVOTMODE::BOT);
	MainRenderer_->GetTransform().SetLocalMove(float4(0, -360));

	//HP렌더러
	HPRenderer_ = CreateComponent<GaugeRenderer>(GetNameCopy());
	HPRenderer_->SetTexture("HP.png");
	HPRenderer_->GetTransform().SetLocalScale({ 56.0f,56.0f });
	HPRenderer_->GetTransform().SetLocalMove(float4(-146,-323));

	//MP렌더러
	MPRenderer_ = CreateComponent<GaugeRenderer>(GetNameCopy());
	MPRenderer_->SetTexture("MP.png");
	MPRenderer_->GetTransform().SetLocalScale({ 56.0f,56.0f });
	MPRenderer_->GetTransform().SetLocalMove(float4(146, -323));

	//스킬 아이콘 백그라운드
	Value_.SkillIconBackPos = { -100,-340 };
	for (size_t i = 0; i < 14; i++)
	{
		GameEngineUIRenderer* NewSkillIcon = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
		NewSkillIcon->SetTexture("SkillBack.png");
		NewSkillIcon->ScaleToTexture();
		NewSkillIcon->SetPivot(PIVOTMODE::CENTER);
		SkillIconBackground_.push_back(NewSkillIcon);
	}

}

void DNFHUD::Update(float _DeltaTime)
{
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			float4 AddPos = float4(static_cast<float>(j) * 32, static_cast<float>(i) * 32, 0) + Value_.SkillIconBackPos;
			SkillIconBackground_[j+(i*7)]->GetTransform().SetLocalPosition(AddPos);
		}
	}
	HPAndMPBarUpdate(_DeltaTime);
}

void DNFHUD::HPAndMPBarUpdate(float _DeltaTime)
{
	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
		float MaxHP = static_cast<float>(Player->GetMaxHP());
		float CurHP = static_cast<float>(Player->GetCurHP());

		//가장 최초 HP 셋팅
		if (PrevHp_ == -1)
		{
			PrevHp_ = Player->GetCurHP();
			LerpHp_ = CurHP;
		}

		//HP 변화 감지
		if (PrevHp_ != CurHP)
		{
			GauageDelta_ += _DeltaTime;
			LerpHp_ = (GameEngineMath::LerpLimit(static_cast<float>(PrevHp_), CurHP, GauageDelta_));
		}

		if (static_cast<int>(LerpHp_) == CurHP)
		{
			GauageDelta_ = 0.f;
			PrevHp_ = Player->GetCurHP();
			LerpHp_ = CurHP;
		}

		float ratio = LerpHp_ / MaxHP;
		DNFDebugGUI::AddValue("ratio", ratio);
		HPRenderer_->UpdateGauge(ratio);
	}
}
