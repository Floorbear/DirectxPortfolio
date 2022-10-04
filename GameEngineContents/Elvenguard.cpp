#include "PreCompile.h"
#include "Elvenguard.h"

#include "Elvenguard_Background.h"
#include "Player_Main.h"
#include <GameEngineCore/GEngine.h>
Elvenguard::Elvenguard()
{
}

Elvenguard::~Elvenguard()
{
}

void Elvenguard::Start()
{
	DNFStart();

	InitCamera({ 0,0,-2000 }, 0.7f);

	//�� ����
	CreateBackground<Elvenguard_Background>();
	Elvenguard_Background_ = dynamic_cast<Elvenguard_Background*>(Background_);

	//Elvenguard_Background* TileBackground = CreateActor< Elvenguard_Background>();
}

void Elvenguard::Update(float _DeltaTime)
{
	DNFUpdate();
	//���̵� �浹üũ
	if (Player_->HitBelow_->IsCollision(CollisionType::CT_OBB2D,
		ColOrder::DoorRight, CollisionType::CT_OBB2D) == true)
	{
		if (LevelChangeTimer_.IsTimerOn() == false)
		{
			Background_->StartFadeOut();
			LevelChangeTimer_.StartTimer(1.0f);
			Player_->IsLevelChanging_ = true;
		}
		else
		{
			LevelChangeTimer_.Update(_DeltaTime * Background_->FadeTimeAcc_);
			if (LevelChangeTimer_.IsTimerOn() == false)
			{
				Player_->PrevMapPos_ = 0;
				std::string NextStageNumber = "0";
				GEngine::ChangeLevel("SeriaRoom");
			}
		}
	}

	if (Player_->HitBelow_->IsCollision(CollisionType::CT_OBB2D,
		ColOrder::DoorLeft, CollisionType::CT_OBB2D) == true)
	{
		if (LevelChangeTimer_.IsTimerOn() == false)
		{
			Background_->StartFadeOut();
			LevelChangeTimer_.StartTimer(1.0f);
			Player_->IsLevelChanging_ = true;
		}
		else
		{
			LevelChangeTimer_.Update(_DeltaTime * Background_->FadeTimeAcc_);
			if (LevelChangeTimer_.IsTimerOn() == false)
			{
				Player_->PrevMapPos_ = 0;
				std::string NextStageNumber = "0";
				GEngine::ChangeLevel("Vilmark_0");
			}
		}
	}
}

void Elvenguard::End()
{
}

void Elvenguard::DNFOnEvent()
{
	if (IsFirstEntrance_ == true)
	{
		IsFirstEntrance_ = false;
		//�����Ʒ� ���ҽ� �ε�
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("MapTexture");
			Dir.Move("Elvenguard");

			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
		Elvenguard_Background_->Init();
	}

	DNFGlobalValue::Bgm_.Stop();
	DNFGlobalValue::Bgm_ = GameEngineSound::SoundPlayControl("forest_town.ogg", 999);

	//�÷��̾� ��ġ����
	Player_->GetTransform().SetWorldPosition({ 700,-360 });
	Player_->PrevPos_ = { 700,-360 };

	//���̵��� ȿ��
	Background_->StartFadeIn();

	//���� ��ȭ ����
	Player_->IsLevelChanging_ = false;
}