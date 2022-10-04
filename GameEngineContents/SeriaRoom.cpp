#include "PreCompile.h"
#include "SeriaRoom.h"

#include "DNFLevel.h"
#include "SeriaBackground.h"
#include "DNFContentsMinimal.h"
#include "Player_Main.h"
#include <GameEngineCore/GEngine.h>
SeriaRoom::SeriaRoom()
{
}

SeriaRoom::~SeriaRoom()
{
}

void SeriaRoom::Start()
{
	DNFStart();

	InitCamera({ 0,0,-2000 }, 0.7f);

	//맵 생성
	CreateBackground<SeriaBackground>();
	SeriaBackground_ = dynamic_cast<SeriaBackground*>(Background_);
	//VilmarkMap_ = dynamic_cast<SeriaBackground*>(Background_);
}

void SeriaRoom::Update(float _DeltaTime)
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
				GEngine::ChangeLevel("Elvenguard");
			}
		}
	}
}

void SeriaRoom::End()
{
}

void SeriaRoom::DNFOnEvent()
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
			Dir.Move("Seria");

			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
		SeriaBackground_->Init();
	}

	DNFGlobalValue::Bgm_.Stop();
	DNFGlobalValue::Bgm_ = GameEngineSound::SoundPlayControl("seria_gate.ogg", 999);

	//플레이어 위치설정
	Player_->GetTransform().SetWorldPosition({ 477,-408 });
	Player_->PrevPos_ = { 477,-408 };

	//페이드인 효과
	Background_->StartFadeIn();

	//레벨 변화 종료
	Player_->IsLevelChanging_ = false;
}