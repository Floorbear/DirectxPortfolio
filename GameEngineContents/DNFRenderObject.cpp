#include "PreCompile.h"
#include "DNFRenderObject.h"
#include "DNFLevel.h"

DNFRenderObject::DNFRenderObject():
	MainRenderer_(nullptr),
	IsStart_(false)
{
}

DNFRenderObject::~DNFRenderObject()
{
}

DNFLevel* DNFRenderObject::GetDNFLevel()
{
	return dynamic_cast<DNFLevel*>(GetLevel());
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
	ErrorCheck();
	ZSort();
}

void DNFRenderObject::DNFStart()
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	IsStart_ = true;
}

void DNFRenderObject::ZSort()
{
	float4 CurPos = GetTransform().GetWorldPosition();
	CurPos.z = CurPos.y;
	GetTransform().SetWorldPosition(CurPos);
}
