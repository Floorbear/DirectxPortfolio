#include "PreCompile.h"
#include "Elvenguard_Background.h"

#include <GameEngineCore/GameEngineCollision.h>

Elvenguard_Background::Elvenguard_Background()
{
}

Elvenguard_Background::~Elvenguard_Background()
{
}

void Elvenguard_Background::Init()
{
	IsInit_ = true;

	std::vector<unsigned int> Frame = { 0,1,2,3,4,5,6,7,8,9,10,11,11,11,11,11,11,11,11,11,11,11 };
	Linus_ = CreateComponent<GameEngineTextureRenderer>();
	Linus_->CreateFrameAnimationFolder("Default", FrameAnimation_DESC("linus", Frame, 0.1f, true));
	Linus_->SetScaleModeImage();
	Linus_->ChangeFrameAnimation("Default");
	Linus_->SetPivot(PIVOTMODE::LEFTTOP);
	Linus_->GetTransform().SetLocalPosition({ 330,-210,-210 });

	//Sign_1_ = CreateComponent<GameEngineTextureRenderer>();
	//Sign_1_->SetTexture("Sign.png");
	//Sign_1_->ScaleToTexture();
	//Sign_1_->SetPivot(PIVOTMODE::LEFTBOT);
	//NearRenderer_->GetTransform().SetLocalPosition(MovePos);
}

void Elvenguard_Background::Start()
{
	GetTransform().SetLocalMove({ 0, 0, 1000 });
	InitBackground("ElvenGuard_Tile");

	NearRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	NearRenderer_->SetTexture("ElvenGuard_Near.png");
	NearRenderer_->ScaleToTexture();
	NearRenderer_->SetPivot(PIVOTMODE::LEFTBOT);
	float4 MovePos = { 0,0,-2000 };
	MovePos.y = -MainRenderer_->GetTransform().GetLocalScale().y;
	NearRenderer_->GetTransform().SetLocalPosition(MovePos);

	//윗쪽문 충돌체
	{
		UpDoorCol_ = CreateComponent<GameEngineCollision>("Middle");
		UpDoorCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
		UpDoorCol_->GetTransform().SetLocalPosition({ 1300,-340 });
		UpDoorCol_->GetTransform().SetLocalScale({ 50,100 });
		UpDoorCol_->ChangeOrder(ColOrder::DoorRight);
		UpDoorCol_->GetTransform().SetLocalPosition({ 740,-300 });
	}

	//왼쪽문 충돌체
	{
		LeftDoorCol_ = CreateComponent<GameEngineCollision>("Middle");
		LeftDoorCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
		LeftDoorCol_->GetTransform().SetLocalPosition({ 38,-380 });
		LeftDoorCol_->GetTransform().SetLocalScale({ 50,300 });
		LeftDoorCol_->ChangeOrder(ColOrder::DoorLeft);
		LeftDoorCol_->GetTransform().SetLocalPosition({ 40,-400 });
	}
}

void Elvenguard_Background::Update(float _DeltaTime)
{
	if (IsInit_ == false)
	{
		return;
	}
	//LeftDoorCol_->GetTransform().SetLocalPosition(DNFGlobalValue::Temp1);
	BackgroundUpdate(_DeltaTime);
}

void Elvenguard_Background::End()
{
}