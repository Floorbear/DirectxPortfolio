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

	//�� ����
	CreateBackground<SeriaBackground>();
	SeriaBackground_ = dynamic_cast<SeriaBackground*>(Background_);
	//VilmarkMap_ = dynamic_cast<SeriaBackground*>(Background_);
}

void SeriaRoom::Update(float _DeltaTime)
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
		//�����Ʒ� ���ҽ� �ε�
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

	//�÷��̾� ��ġ����
	Player_->GetTransform().SetWorldPosition({ 477,-408 });
	Player_->PrevPos_ = { 477,-408 };

	//���̵��� ȿ��
	Background_->StartFadeIn();

	//���� ��ȭ ����
	Player_->IsLevelChanging_ = false;
}