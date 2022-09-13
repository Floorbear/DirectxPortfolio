#include "PreCompile.h"
#include "Vilmark_0.h"

#include "Vilmark_0_Background.h"
#include "Player_Main.h"
#include "BloodLugaru.h"
#include "MonsterHP.h"

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
	MonsterHP_ = CreateActor<MonsterHP>();
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
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("bloodlugaru");
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	//이펙트 텍스처 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("EffectTexture");
		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}
	DNFGlobalValue::CurrentMonsterHP = MonsterHP_;
	MonsterHP_->Off();

	BloodLugaru* Monster = CreateActor<BloodLugaru>();
	Monster->ID_ = 1;
	Monster->GetTransform().SetWorldPosition({ 700,-400 });
}
