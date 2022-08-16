#include "PreCompile.h"
#include "GameEngineCore/GameEngineCollision.h"

#include "DNFContentsMinimal.h"
#include "DNFRenderObject.h"
#include "DNFLevel.h"

#include "DNFDebugGUI.h"

DNFRenderObject::DNFRenderObject():
	MainRenderer_(nullptr),
	ShadowRenderer_(),
	IsStart_(false),
	ShadowPos_(),
	ShadowRot_(),
	BotCol_(),
	BotPos_({0,-88.0f}),
	PrevPos_()
{
}

DNFRenderObject::~DNFRenderObject()
{
}

DNFLevel* DNFRenderObject::GetDNFLevel()
{
	return dynamic_cast<DNFLevel*>(GetLevel());
}

void DNFRenderObject::CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc)
{
	MainRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
	ShadowRenderer_->CreateFrameAnimationFolder(_AnimationName, _Desc);
}

void DNFRenderObject::ChangeDNFAnimation(const std::string& _Name)
{
	MainRenderer_->ChangeFrameAnimation(_Name);
	ShadowRenderer_->ChangeFrameAnimation(_Name);
}

void DNFRenderObject::ShadowUpdate()
{
	//ShadowRenderer_->GetTransform().SetLocalPosition(ShadowPos_);
	//ShadowRenderer_->GetTransform().SetLocalRotation(ShadowRot_);
	//x가 양수면
	if (ShadowRenderer_->GetTransform().GetWorldScale().x > 0)
	{
		ShadowRenderer_->GetTransform().SetLocalPosition(ShadowPos_);
		ShadowRenderer_->GetTransform().SetLocalRotation(ShadowRot_);
	}
	else
	{
		float4 ShadowPos = ShadowPos_;
		ShadowPos.x = -ShadowPos.x;
		float4 ShadowRot = ShadowRot_;
		ShadowRot.x = ShadowRot_.x;
		ShadowRot.z = -ShadowRot_.z;
		ShadowRenderer_->GetTransform().SetLocalPosition(ShadowPos);
		ShadowRenderer_->GetTransform().SetLocalRotation(ShadowRot);
	}
}

void DNFRenderObject::ErrorCheck()
{
	if (IsStart_ == false)
	{
		MsgBoxAssert("DnfStart를 호출하지 않았습니다.");
	}
	if (MainRenderer_ == nullptr)
	{
		MsgBoxAssert("MainRenderer_ 세팅이 안됬습니다.");
	}

	if (MainRenderer_->GetTransform().GetLocalScale().CompareInt3D(float4::ONE) == true)
	{
		MsgBoxAssert("MainRenderer_ Scale 세팅을 안했습니다.");
	}
}

void DNFRenderObject::DNFUpdate()
{
	ShadowUpdate();
	ErrorCheck();
	ZSort();
	//BotCol 업데이트
	BotCol_->GetTransform().SetLocalPosition(float4(BotPos_.x, BotPos_.y, -500));
}

void DNFRenderObject::DNFStart()
{
	ShadowRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());

	//BotCol
	BotCol_ = CreateComponent<GameEngineCollision>("Col");
	BotCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 1.0f, 0.5f));
	BotCol_->GetTransform().SetLocalScale(float4(5, 5, 1));
	BotCol_->GetTransform().SetLocalMove(float4(0, 0, -500));
	BotCol_->ChangeOrder(ColOrder::Debug);

	//이전 액터 위치
	PrevPos_ = GetTransform().GetWorldPosition();

	ShadowRenderer_->GetColorData().MulColor = float4(0, 0, 0, 0.6f);
	ShadowPos_ = { -10,-45,500};
	ShadowRot_ = { -60,0,5 };
	IsStart_ = true;
}

void DNFRenderObject::ZSort()
{
	float4 CurPos = GetTransform().GetWorldPosition();
	CurPos.z = CurPos.y;
	GetTransform().SetWorldPosition(CurPos);
}
