#include "PreCompile.h"
#include "VilmarkLevel.h"

#include <GameEngineCore/GEngine.h>
#include "VilmarkMap.h"
#include "Player_Main.h"
#include "DNFMonster.h"
#include "MonsterHP.h"

#include "Bloodlugaru.h"
#include "CrazyIvan.h"
#include "Ciel.h"
#include "BoomEffect.h"
VilmarkLevel::VilmarkLevel() :
	VilmarkMap_(),
	MonsterList_(),
	LevelChangeTimer_()
{
}

VilmarkLevel::~VilmarkLevel()
{
}

void VilmarkLevel::VilmarkStart()
{
	DNFStart();

	InitCamera({ 0,0,-2000 }, 0.6f);
	//�� ����
	CreateBackground<VilmarkMap>();
	VilmarkMap_ = reinterpret_cast<VilmarkMap*>(Background_);
	//���͹� ����
	MonsterHP_ = CreateActor<MonsterHP>();
}

void VilmarkLevel::VilmarkUpdate(float _DeltaTime)
{
	if (StageNumber_ == -1)
	{
		MsgBoxAssert("StageNumber�� �Ҵ���� �ʾҽ��ϴ�. �����ڿ� StageNumber�� �ʱ�ȭ���ּ���");
	}
	DNFUpdate();

	Update_Door(_DeltaTime);

	//���� ���� ������
	std::map<int, DNFMonster*>::iterator StartIter = MonsterList_.begin();
	std::map<int, DNFMonster*>::iterator EndIter = MonsterList_.end();

	for (; StartIter != EndIter;)
	{
		if (StartIter->second->IsDeath() == true)
		{
			StartIter = MonsterList_.erase(StartIter);
			continue;
		}
		StartIter++;
	}
}

void VilmarkLevel::Update_Door(float _DeltaTime)
{
	//�ʿ� ���Ͱ� ������ ���� ������
	if (MonsterList_.empty() == true)
	{
		VilmarkMap_->OnDoor();

		//�÷��̾ ������Door Order�� �浹�ϸ� ���� ������
		if (Player_->HitBelow_->IsCollision(CollisionType::CT_OBB2D,
			ColOrder::DoorRight, CollisionType::CT_OBB2D) == true)
		{
			if (LevelChangeTimer_.IsTimerOn() == false)
			{
				VilmarkMap_->StartFadeOut();
				LevelChangeTimer_.StartTimer(1.0f);
				Player_->IsLevelChanging_ = true;
			}
			else
			{
				LevelChangeTimer_.Update(_DeltaTime * 1.2f);
				if (LevelChangeTimer_.IsTimerOn() == false)
				{
					Player_->PrevMapPos_ = 0;
					std::string NextStageNumber = std::to_string(StageNumber_ + 1);
					GEngine::ChangeLevel("Vilmark_" + NextStageNumber);
				}
			}
		}

		//�÷��̾ ����Door Order�� �浹�ϸ� ���� ������
		if (Player_->HitBelow_->IsCollision(CollisionType::CT_OBB2D,
			ColOrder::DoorLeft, CollisionType::CT_OBB2D) == true)
		{
			if (LevelChangeTimer_.IsTimerOn() == false)
			{
				VilmarkMap_->StartFadeOut();
				Player_->IsLevelChanging_ = true;
				LevelChangeTimer_.StartTimer(1.0f);
			}
			else
			{
				LevelChangeTimer_.Update(_DeltaTime * 1.2f);
				if (LevelChangeTimer_.IsTimerOn() == false)
				{
					Player_->PrevMapPos_ = 1;
					std::string NextStageNumber = std::to_string(StageNumber_ - 1);
					GEngine::ChangeLevel("Vilmark_" + NextStageNumber);
				}
			}
		}
	}
}

void VilmarkLevel::VilmarkStartLevel()
{
	//�÷��̾� ��ġ����
	int PrevMapPos = Player_->PrevMapPos_;
	if (PrevMapPos == 0) //���� > �����ʸ� �̵��ϰ�� >>ĳ���� ���ʿ� ��ġ�ϰ� �ϰ� �;�
	{
		Player_->GetTransform().SetWorldPosition({ 149,-373 });
	}
	else if (PrevMapPos == 1)//������ > ���� �̵��ϰ��
	{
		Player_->GetTransform().SetWorldPosition({ 1150,-369 });
	}

	//���� HP�� ����
	DNFGlobalValue::CurrentMonsterHP = MonsterHP_;
	MonsterHP_->Off();

	//���̵��� ȿ��
	VilmarkMap_->StartFadeIn();

	//���� ��ȭ ����
	Player_->IsLevelChanging_ = false;
}