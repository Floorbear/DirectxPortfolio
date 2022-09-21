#include "PreCompile.h"
#include "Vilmark_1.h"

#include "VilmarkMap.h"
#include "CrazyIvan.h"

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
	//CrazyIvan* Monster = CreateMonster<CrazyIvan>({ { 700,-400 } });

	//CrazyIvan* Monster4 = CreateActor<CrazyIvan>();
	//Monster4->ID_ = 4;
	//Monster4->GetTransform().SetWorldPosition({ 1000,-400 });//1000,-400

	//CrazyIvan* Monster5 = CreateActor<CrazyIvan>();
	//Monster5->ID_ = 5;
	//Monster5->GetTransform().SetWorldPosition({ 1100,-500 });//1000,-400

	//CrazyIvan* Monster6 = CreateActor<CrazyIvan>();
	//Monster6->ID_ = 6;
	//Monster6->GetTransform().SetWorldPosition({ 1200,-400 });//1000,-400
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