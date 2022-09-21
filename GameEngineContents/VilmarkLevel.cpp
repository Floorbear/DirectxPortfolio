#include "PreCompile.h"
#include "VilmarkLevel.h"

#include <GameEngineCore/GEngine.h>
#include "VilmarkMap.h"
#include "Player_Main.h"
#include "DNFMonster.h"
#include "MonsterHP.h"

#include "Bloodlugaru.h"
#include "CrazyIvan.h"
#include "BoomEffect.h"
VilmarkLevel::VilmarkLevel() :
	VilmarkMap_(),
	MonsterList_()
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

	//맵에 몬스터가 없으면 문이 열리게
	if (MonsterList_.empty() == true)
	{
		VilmarkMap_->OnDoor();
	}
	//플레이어가 오른쪽Door Order에 충돌하면 다음 맵으로
	if (Player_->HitBelow_->IsCollision(CollisionType::CT_OBB2D, ColOrder::DoorRight, CollisionType::CT_OBB2D) == true)
	{
		std::string NextStageNumber = std::to_string(StageNumber_ + 1);
		GEngine::ChangeLevel("Vilmark_" + NextStageNumber);
	}
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

void VilmarkLevel::VilmarkStartLevel()
{
	//플레이어 위치설정
	Player_->GetTransform().SetWorldPosition({ 200,-400 });

	//몬스터 HP바 설정
	DNFGlobalValue::CurrentMonsterHP = MonsterHP_;
	MonsterHP_->Off();
}