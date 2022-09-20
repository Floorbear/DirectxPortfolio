#include "PreCompile.h"
#include "Vilmark_0.h"

#include "Vilmark_0_Background.h"
#include "Player_Main.h"
#include "DNFMonster.h"
#include "MonsterHP.h"

#include "Bloodlugaru.h"
#include "CrazyIvan.h"
#include "BoomEffect.h"
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
	//if (GameEngineInput::GetInst()->IsDown("Q") == true)
	//{
	//}
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

	//크레이지 이반 텍스처 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("crazyivan");
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

	//Bloodlugaru* Monster = CreateActor<Bloodlugaru>();
	//Monster->ID_ = 1;
	//Monster->GetTransform().SetWorldPosition({ 700,-400 });

	//Bloodlugaru* Monster2 = CreateActor<Bloodlugaru>();
	//Monster2->ID_ = 2;
	//Monster2->GetTransform().SetWorldPosition({ 800,-430 });

	CrazyIvan* Monster3 = CreateActor<CrazyIvan>();
	Monster3->ID_ = 3;
	Monster3->GetTransform().SetWorldPosition({ 700,-400 });//1000,-400

	CrazyIvan* Monster4 = CreateActor<CrazyIvan>();
	Monster4->ID_ = 4;
	Monster4->GetTransform().SetWorldPosition({ 1000,-400 });//1000,-400

	CrazyIvan* Monster5 = CreateActor<CrazyIvan>();
	Monster5->ID_ = 5;
	Monster5->GetTransform().SetWorldPosition({ 1100,-500 });//1000,-400

	CrazyIvan* Monster6 = CreateActor<CrazyIvan>();
	Monster6->ID_ = 6;
	Monster6->GetTransform().SetWorldPosition({ 1200,-400 });//1000,-400
}