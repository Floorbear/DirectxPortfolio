#include "PreCompile.h"
#include "Vilmark_2.h"

#include "VilmarkMap.h"

#include "TauCaptain.h"
#include "MiniTau.h"
#include "HeartFox.h"
#include "Generator.h"

Vilmark_2::Vilmark_2()
{
	StageNumber_ = 2;
}

Vilmark_2::~Vilmark_2()
{
}

void Vilmark_2::Start()
{
	VilmarkStart();
	VilmarkMap_->MakeLeftDoor();
	VilmarkMap_->MakeRightDoor();

	////빌마르크 방 3꺼

	TauCaptain* MonsterBoss = CreateMonster<TauCaptain>(float4(1079, -352));
	float Acc = 200.f;
	////몬스터 생성
	{
		Generator* NewGe = CreateActor<Generator>();
		NewGe->Init< MiniTau>(2, 6.f);//3.5
		NewGe->GetTransform().SetWorldPosition({ 554,-439 ,-439 });
	}
	{
		Generator* NewGe = CreateActor<Generator>();
		NewGe->Init< MiniTau>(3, 13.f);//3.5
		NewGe->GetTransform().SetWorldPosition({ Acc + 772,-502 ,-472 });
	}
	{
		Generator* NewGe = CreateActor<Generator>();
		NewGe->Init< MiniTau>(1, 21.f);//3.5
		NewGe->GetTransform().SetWorldPosition({ Acc + 772,-406 ,-406 });
	}
	float4 AccPos = { 0,-30.f };
	//MiniTau* Monster0 = CreateMonster<MiniTau>(AccPos + float4(573, -352));
	//MiniTau* Monster1 = CreateMonster<MiniTau>(AccPos + float4(697, -365));
	//MiniTau* Monster2 = CreateMonster<MiniTau>(AccPos + float4(782, -418));
	//MiniTau* Monster3 = CreateMonster<MiniTau>(AccPos + float4(869, -340));
	//MiniTau* Monster4 = CreateMonster<MiniTau>(AccPos + float4(918, -379));
	//MiniTau* Monster5 = CreateMonster<MiniTau>(AccPos + float4(1014, -400));
}

void Vilmark_2::Update(float _DeltaTime)
{
	VilmarkUpdate(_DeltaTime);
}

void Vilmark_2::End()
{
}

void Vilmark_2::DNFOnEvent()
{
	VilmarkStartLevel();
}