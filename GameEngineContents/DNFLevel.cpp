#include "PreCompile.h"
#include "DNFLevel.h"

DNFLevel::DNFLevel():
	Camera_(nullptr)
{
}

DNFLevel::~DNFLevel()
{
}




void DNFLevel::DNFStart()
{
	CreateCamera({ 0,0,-500 }, 1.0f);
}

void DNFLevel::DNFUpdate()
{
	ErrorCheck();
}

void DNFLevel::ErrorCheck()
{
	if (Camera_ == nullptr)
	{
		MsgBoxAssert("Level���� ī�޶� ������ �ʾҽ��ϴ�!");
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
