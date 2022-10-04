#include "PreCompile.h"
#include "SeriaBackground.h"
#include "DNFContentsMinimal.h"

#include <GameEngineCore/GameEngineCollision.h>
SeriaBackground::SeriaBackground()
{
}

SeriaBackground::~SeriaBackground()
{
}

void SeriaBackground::Init()
{
	IsInit_ = true;
	Seria_ = CreateComponent<GameEngineTextureRenderer>();
	std::vector<unsigned int> Frame = { 0,1,2,3,4,5,6,7,8,9,9,9,9,9,9,9,9,9,9,9 };
	Seria_->CreateFrameAnimationFolder("Seria", FrameAnimation_DESC("quest_seria", Frame, 0.2f, true));
	Seria_->SetScaleModeImage();
	Seria_->ChangeFrameAnimation("Seria");
	Seria_->GetTransform().SetLocalPosition({ 830,-500 });

	Gate_ = CreateComponent<GameEngineTextureRenderer>();
	Gate_->CreateFrameAnimationFolder("Seria", FrameAnimation_DESC("gate", 0, 0, 0.2f, false));
	Gate_->SetPivot(PIVOTMODE::LEFTTOP);
	Gate_->SetScaleModeImage();
	Gate_->ChangeFrameAnimation("Seria");
	Gate_->GetTransform().SetLocalPosition({ 0,0,-1000 });

	//Gate_->GetTransform().SetLocalPosition({ 830,-500 });
}

void SeriaBackground::Start()
{
	GetTransform().SetLocalMove({ 0, 0, 1000 });
	InitBackground("SeriaBackground");

	//오른쪽문 충돌체
	{
		DoorCol_ = CreateComponent<GameEngineCollision>("Middle");
		DoorCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
		DoorCol_->GetTransform().SetLocalPosition({ 470,-540 });
		DoorCol_->GetTransform().SetLocalScale({ 140,40 });
		DoorCol_->ChangeOrder(ColOrder::DoorRight); //Enum태그때문에 그런건데 아랫문을 의미함
	}
}

void SeriaBackground::Update(float _DeltaTime)
{
	if (IsInit_ == false)
	{
		return;
	}
	//DoorCol_->GetTransform().SetLocalPosition(DNFGlobalValue::Temp1);

	BackgroundUpdate(_DeltaTime);
}