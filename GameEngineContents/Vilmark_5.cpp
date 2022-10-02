#include "PreCompile.h"
#include "Vilmark_5.h"

#include "VilmarkMap.h"

#include "DNFDebugGUI.h"
#include "HyperMecaCow.h"
#include "ExtremOverkill.h"
Vilmark_5::Vilmark_5()
{
	StageNumber_ = 5;
}

Vilmark_5::~Vilmark_5()
{
}

void Vilmark_5::Start()
{
	VilmarkStart();
	VilmarkMap_->MakeLeftDoor();
	float4 AccPos = {};

	//HyperMecaCow* Boss = CreateMonster< HyperMecaCow>({ { 700,-420 } });
	DNFDebugGUI::AddMutableValue("DebugInt", &DebugInt);
}

void Vilmark_5::Update(float _DeltaTime)
{
	//디버깅용 구문
	if (DebugInt == 0)
	{
		DebugInt = 1;
		ExtremOverkill* Newkill = CreateActor<ExtremOverkill>();
		Newkill->GetTransform().SetWorldPosition({ 600,-400 });
	}
	VilmarkUpdate(_DeltaTime);
}

void Vilmark_5::End()
{
}

void Vilmark_5::DNFOnEvent()
{
	VilmarkStartLevel();
	if (IsFirstEntrance_ == true)
	{
		DNFGlobalValue::Bgm_.Stop();
		DNFGlobalValue::Bgm_ = GameEngineSound::SoundPlayControl("vilmark_boss.wav", 999);

		IsFirstEntrance_ = false;
	}
}