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

	//맵 생성
	CreateBackground<Elvenguard_Background>();
	Elvenguard_Background_ = dynamic_cast<Elvenguard_Background*>(Background_);

	//Elvenguard_Background* TileBackground = CreateActor< Elvenguard_Background>();
}

void Elvenguard::Update(float _DeltaTime)
{
	DNFUpdate();
	//맵이동 충돌체크
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
		//세리아룸 리소스 로드
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

	//플레이어 위치설정
	Player_->GetTransform().SetWorldPosition({ 700,-360 });
	Player_->PrevPos_ = { 700,-360 };

	//페이드인 효과
	Background_->StartFadeIn();

	//레벨 변화 종료
	Player_->IsLevelChanging_ = false;
}