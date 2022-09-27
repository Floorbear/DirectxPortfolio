#include "PreCompile.h"
#include "Vilmark_1.h"

#include "VilmarkMap.h"
#include "CrazyIvan.h"
#include "CrazyIvanCaptain.h"

Vilmark_1::Vilmark_1()
{
	StageNumber_ = 1;
}

Vilmark_1::~Vilmark_1()
{
}

void Vilmark_1::Start()
{
	VilmarkStart();
	VilmarkMap_->MakeLeftDoor();
	VilmarkMap_->MakeRightDoor();

	//-320보다 작아야
	CrazyIvan* Monster = CreateMonster<CrazyIvan>({ 423,-351 });
	CrazyIvan* Monster1 = CreateMonster<CrazyIvan>({ 494,-359 });
	CrazyIvan* Monster2 = CreateMonster<CrazyIvan>({ 414,-442 });
	CrazyIvan* Monster3 = CreateMonster<CrazyIvan>({ 572,-376 });
	CrazyIvanCaptain* MonsterBoss = CreateMonster<CrazyIvanCaptain>({ 1040,-376 });
}

void Vilmark_1::Update(float _DeltaTime)
{
	VilmarkUpdate(_DeltaTime);
}

void Vilmark_1::End()
{
}

void Vilmark_1::DNFOnEvent()
{
	VilmarkStartLevel();
}