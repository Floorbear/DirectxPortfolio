#include "PreCompile.h"
#include "Vilmark_0.h"

#include "Vilmark_0_Background.h"
#include "Player_Main.h"
#include "BloodLugaru.h"

Vilmark_0::Vilmark_0()
{
}

Vilmark_0::~Vilmark_0()
{
}

void Vilmark_0::Start()
{
	DNFStart();
	Player_->GetTransform().SetWorldPosition({ 200,-400 });

	InitCamera({ 0,0,-2000 }, 0.6f);
	CreateBackground<Vilmark_0_Background>();
}

void Vilmark_0::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Vilmark_0::End()
{
}

void Vilmark_0::DNFOnEvent()
{
	//루가루 텍스처 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("MonsterTexture");
		Dir.Move("bloodlugaru");
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	BloodLugaru* Monster = CreateActor<BloodLugaru>();
	Monster->GetTransform().SetWorldPosition({ 600,-400 });
}
