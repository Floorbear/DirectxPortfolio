#include "PreCompile.h"
#include "DNFHUD.h"

#include "DNFLevel.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

DNFHUD::DNFHUD()
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
	HPRenderer_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	HPRenderer_->SetTexture("HP.png");
	HPRenderer_->ScaleToTexture();
	HPRenderer_->GetTransform().SetLocalMove(float4(-146,-323));

	//MP·»´õ·¯
	MPRenderer_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	MPRenderer_->SetTexture("MP.png");
	MPRenderer_->ScaleToTexture();
	MPRenderer_->GetTransform().SetLocalMove(float4(146, -323));
}

void DNFHUD::Update(float _DeltaTime)
{
}
