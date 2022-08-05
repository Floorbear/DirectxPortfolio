#include "PreCompile.h"
#include "DNFLevel.h"
#include "DNFGlobalValue.h"

#include "Player_Main.h"
#include "DNFHUD.h"

DNFLevel::DNFLevel():
	MainCamera_(nullptr),
	IsStart_(false),
	MapScale_(float4::ZERO),
	Player_()
{
}

DNFLevel::~DNFLevel()
{
}


void DNFLevel::SetMapScale(const float4& _Scale)
{
	MapScale_ = _Scale;
}


const float4& DNFLevel::GetMapScale()
{
	return MapScale_;
}


void DNFLevel::DNFStart()
{
	Player_ = CreateActor<Player_Main>();
	CreateActor<DNFHUD>();
	IsStart_ = true;
}

void DNFLevel::DNFUpdate()
{
	ErrorCheck();
}

void DNFLevel::ErrorCheck()
{
	if (MainCamera_ == nullptr)
	{
		MsgBoxAssert("Level에서 카메라를 만들지 않았습니다!");
	}
	if (IsStart_ == false)
	{
		MsgBoxAssert("DnfStart를 호출하지 않았습니다.");
	}
	if (MapScale_.CompareInt2D(float4::ZERO) == true)
	{
		MsgBoxAssert("MapScale을 세팅하지 않았습니다.");
	}
}

void DNFLevel::InitCamera(float4 _Pos, float _ZoomRate)
{
	{
		MainCamera_ = GetMainCameraActor();
		MainCamera_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		float4 Size = float4(1280,720) * _ZoomRate;
		Zoom_ = _ZoomRate;
		MainCamera_->GetCameraComponent()->SetProjectionSize(Size);
		MainCamera_->GetTransform().SetLocalPosition(_Pos);
	}
}

void DNFLevel::OnEvent()
{
	DNFGlobalValue::CurrentLevel = this;
	DNFOnEvent();
}

void DNFLevel::DNFOnEvent()
{
}
