#include "PreCompile.h"
#include "DNFLevel.h"

#include "Player_Main.h"
DNFLevel::DNFLevel():
	Camera_(nullptr),
	IsStart_(false)
{
}

DNFLevel::~DNFLevel()
{
}




void DNFLevel::DNFStart()
{
	CreateCamera({ 0,0,-500 }, 0.7f);
	IsStart_ = true;
}

void DNFLevel::DNFUpdate()
{
	ErrorCheck();
}

void DNFLevel::ErrorCheck()
{
	if (Camera_ == nullptr)
	{
		MsgBoxAssert("Level에서 카메라를 만들지 않았습니다!");
	}
	if (IsStart_ == false)
	{
		MsgBoxAssert("DnfStart를 호출하지 않았습니다.");
	}
}

void DNFLevel::CreateCamera(float4 _Pos, float _ZoomRate)
{
	{
		Camera_ = CreateActor<GameEngineCameraActor>();
		Camera_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera_->GetTransform().SetLocalPosition(_Pos);
	}
}
