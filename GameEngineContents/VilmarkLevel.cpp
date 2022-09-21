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
	//맵 생성
	CreateBackground<VilmarkMap>();
	VilmarkMap_ = reinterpret_cast<VilmarkMap*>(Background_);
	//몬스터바 생성
	MonsterHP_ = CreateActor<MonsterHP>();
}

void VilmarkLevel::VilmarkUpdate(float _DeltaTime)
{
	if (StageNumber_ == -1)
	{
		MsgBoxAssert("StageNumber가 할당되지 않았습니다. 생성자에 StageNumber을 초기화해주세요");
	}
	DNFUpdate();

	Update_Door(_DeltaTime);

	//죽은 몬스터 릴리즈
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
	//맵에 몬스터가 없으면 문이 열리게
	if (MonsterList_.empty() == true)
	{
		VilmarkMap_->OnDoor();

		//플레이어가 오른쪽Door Order에 충돌하면 다음 맵으로
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

		//플레이어가 왼쪽Door Order에 충돌하면 다음 맵으로
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
	//플레이어 위치설정
	int PrevMapPos = Player_->PrevMapPos_;
	if (PrevMapPos == 0) //왼쪽 > 오른쪽맵 이동일경우 >>캐릭터 왼쪽에 위치하게 하고 싶어
	{
		Player_->GetTransform().SetWorldPosition({ 149,-373 });
	}
	else if (PrevMapPos == 1)//오른쪽 > 왼쪽 이동일경우
	{
		Player_->GetTransform().SetWorldPosition({ 1150,-369 });
	}

	//몬스터 HP바 설정
	DNFGlobalValue::CurrentMonsterHP = MonsterHP_;
	MonsterHP_->Off();

	//페이드인 효과
	VilmarkMap_->StartFadeIn();

	//레벨 변화 종료
	Player_->IsLevelChanging_ = false;
}