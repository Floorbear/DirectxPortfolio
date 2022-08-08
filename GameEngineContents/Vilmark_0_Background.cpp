#include "PreCompile.h"
#include "Vilmark_0_Background.h"
#include "DNFLevel.h"

#include "DNFGlobalValue.h"
#include "DNFDebugGUI.h"

Vilmark_0_Background::Vilmark_0_Background():
	FarSpeed_(0.5f),
	PrevCameraPos_(),
	FarRenderer_(),
	ColRenderer_()
{
}

Vilmark_0_Background::~Vilmark_0_Background()
{
}

void Vilmark_0_Background::Start()
{
	InitBackground("Vilmark_Background_00");


	FarRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	FarRenderer_->SetTexture("Vilmark_far.png");
	FarRenderer_->ScaleToTexture();
	FarRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	PrevCameraPos_ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
	FarRenderer_->GetTransform().SetWorldPosition({ PrevCameraPos_.x,FarRenderer_->GetTransform().GetWorldPosition().y,10});
	//On�̺�Ʈ ���� ���� �Ǹ� OnEvent�� �����ؾ���
}

void Vilmark_0_Background::Update(float _DeltaTime)
{
	//Far 

	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
	//ī�޶��� �������� �����Ǹ� �̵������� ����
	if (PrevCameraPos_.CompareInt3D(CameraPos) == false)
	{
		float MoveValue = CameraPos.x - PrevCameraPos_.x;
		MoveValue*= FarSpeed_;
		FarRenderer_->GetTransform().SetLocalMove({MoveValue,0,0});
		//FarRenderer_->GetTransform().SetWorldPosition()
		PrevCameraPos_ = CameraPos;
	}

}

void Vilmark_0_Background::End()
{

}
