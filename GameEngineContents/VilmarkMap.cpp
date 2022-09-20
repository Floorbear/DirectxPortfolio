#include "PreCompile.h"
#include "VilmarkMap.h"
#include "DNFLevel.h"

#include "DNFGlobalValue.h"
#include "DNFDebugGUI.h"

VilmarkMap::VilmarkMap()
{
}

VilmarkMap::~VilmarkMap()
{
}

void VilmarkMap::Start()
{
	GetTransform().SetLocalMove({ 0, 0, 1000 });
	InitBackground("Vilmark_Background_00");

	//부쉬
	BushRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	BushRenderer_->SetTexture("Bush.png");
	BushRenderer_->ScaleToTexture();
	BushRenderer_->SetPivot(PIVOTMODE::LEFTTOP);

	//멀리있는거
	FarRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	FarRenderer_->SetTexture("Vilmark_far.png");
	FarRenderer_->ScaleToTexture();
	FarRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	PrevCameraPos_ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
	FarRenderer_->GetTransform().SetWorldPosition({ -200.0f,FarRenderer_->GetTransform().GetWorldPosition().y,GetTransform().GetLocalPosition().z + 10 });

	//DNFDebugGUI::AddMutableValue("BackgroundBushPos", &DNFGlobalValue::Temp1);
}

void VilmarkMap::Update(float _DeltaTime)
{
	//Far
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
	//카메라의 움직임이 감지되면 이동연산이 시작
	if (PrevCameraPos_.CompareInt3D(CameraPos) == false)
	{
		float MoveValue = CameraPos.x - PrevCameraPos_.x;
		MoveValue *= FarSpeed_;
		FarRenderer_->GetTransform().SetLocalMove({ MoveValue,0,0 });
		//FarRenderer_->GetTransform().SetWorldPosition()
		PrevCameraPos_ = CameraPos;
	}
}

void VilmarkMap::End()
{
}