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
	GauageDelta_()
{
}

DNFHUD::~DNFHUD()
{
}

void DNFHUD::Start()
{
	GetTransform().SetLocalMove(float4(0, 0, -1000));
	//UI·»´õ·¯
	MainRenderer_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	MainRenderer_->SetTexture("hud_frame.png");
	MainRenderer_->ScaleToTexture();
	MainRenderer_->SetPivot(PIVOTMODE::BOT);
	MainRenderer_->GetTransform().SetLocalMove(float4(0, -360));

	//HP·»´õ·¯
	HPRenderer_ = CreateComponent<GaugeRenderer>(GetNameCopy());
	HPRenderer_->SetTexture("HP.png");
	HPRenderer_->GetTransform().SetLocalScale({ 56.0f,56.0f });
	HPRenderer_->GetTransform().SetLocalMove(float4(-146,-323));

	//MP·»´õ·¯
	MPRenderer_ = CreateComponent<GaugeRenderer>(GetNameCopy());
	MPRenderer_->SetTexture("MP.png");
	MPRenderer_->GetTransform().SetLocalScale({ 56.0f,56.0f });
	MPRenderer_->GetTransform().SetLocalMove(float4(146, -323));

	//PrevHp Set

}

void DNFHUD::Update(float _DeltaTime)
{

	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
		float MaxHP = static_cast<float>(Player->GetMaxHP());
		float CurHP = static_cast<float>(Player -> GetCurHP());

		//°¡Àå ÃÖÃÊ HP ¼ÂÆÃ
		if (PrevHp_ == -1)
		{
			PrevHp_ = Player->GetCurHP();
			LerpHp_ = CurHP;
			AccTime_ = 1.f;
		}

		//HP º¯È­ °¨Áö
		if (PrevHp_ != CurHP)
		{
			GauageDelta_ += _DeltaTime *AccTime_ * 1.0f;
			LerpHp_ = (GameEngineMath::LerpLimit(static_cast<float>(PrevHp_), CurHP,GauageDelta_));
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
