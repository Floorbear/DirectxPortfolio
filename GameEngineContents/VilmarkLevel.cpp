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

	//�ʿ� ���Ͱ� ������ ���� ������
	if (MonsterList_.empty() == true)
	{
		VilmarkMap_->OnDoor();
	}
	//�÷��̾ ������Door Order�� �浹�ϸ� ���� ������
	if (Player_->HitBelow_->IsCollision(CollisionType::CT_OBB2D, ColOrder::DoorRight, CollisionType::CT_OBB2D) == true)
	{
		std::string NextStageNumber = std::to_string(StageNumber_ + 1);
		GEngine::ChangeLevel("Vilmark_" + NextStageNumber);
	}
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

void VilmarkLevel::VilmarkStartLevel()
{
	//�÷��̾� ��ġ����
	Player_->GetTransform().SetWorldPosition({ 200,-400 });

	//���� HP�� ����
	DNFGlobalValue::CurrentMonsterHP = MonsterHP_;
	MonsterHP_->Off();
}