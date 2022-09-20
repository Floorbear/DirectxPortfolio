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
	//맵 생성
	CreateBackground<VilmarkMap>();
	//몬스터바 생성
	MonsterHP_ = CreateActor<MonsterHP>();
}

void VilmarkLevel::VilmarkUpdate(float _DeltaTime)
{
	DNFUpdate();
}

void VilmarkLevel::VilmarkStartLevel()
{
	//플레이어 위치설정
	Player_->GetTransform().SetWorldPosition({ 200,-400 });

	//몬스터 HP바 설정
	DNFGlobalValue::CurrentMonsterHP = MonsterHP_;
	MonsterHP_->Off();
}