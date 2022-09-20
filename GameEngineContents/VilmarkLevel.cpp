#include "PreCompile.h"
#include "VilmarkLevel.h"

#include "VilmarkMap.h"
#include "Player_Main.h"
#include "DNFMonster.h"
#include "MonsterHP.h"

#include "Bloodlugaru.h"
#include "CrazyIvan.h"
#include "BoomEffect.h"
VilmarkLevel::VilmarkLevel()
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
	//���͹� ����
	MonsterHP_ = CreateActor<MonsterHP>();
}

void VilmarkLevel::VilmarkUpdate(float _DeltaTime)
{
	DNFUpdate();
}

void VilmarkLevel::VilmarkStartLevel()
{
	//�÷��̾� ��ġ����
	Player_->GetTransform().SetWorldPosition({ 200,-400 });

	//���� HP�� ����
	DNFGlobalValue::CurrentMonsterHP = MonsterHP_;
	MonsterHP_->Off();
}