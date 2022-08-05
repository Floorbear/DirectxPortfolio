#include "PreCompile.h"
#include "BloodLugaru.h"

#include "DNFDefineList.h"
#include "DNFDebugGUI.h"
BloodLugaru::BloodLugaru():
	AniSpeed_(0.12f)
{
}

BloodLugaru::~BloodLugaru()
{
}

void BloodLugaru::Start()
{
	DNFStart();
	MainRenderer_->GetTransform().SetLocalScale(float4(315, 315,1));
	MainRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("bloodlugaru",Lugaru_Idle_Start, Lugaru_Idle_End, AniSpeed_));
	MainRenderer_->ChangeFrameAnimation("Idle");
}

void BloodLugaru::Update(float _DeltaTime)
{
	DNFUpdate();
}

void BloodLugaru::End()
{
}
