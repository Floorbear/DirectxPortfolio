#include "PreCompile.h"
#include "DNFRenderObject.h"

DNFRenderObject::DNFRenderObject():
	MainRenderer_(nullptr),
	IsStart_(false)
{
}

DNFRenderObject::~DNFRenderObject()
{
}

void DNFRenderObject::ErrorCheck()
{
	if (IsStart_ == false)
	{
		MsgBoxAssert("DnfStart�� ȣ������ �ʾҽ��ϴ�.");
	}
	if (MainRenderer_ == nullptr)
	{
		MsgBoxAssert("MainRenderer_ ������ �ȉ���ϴ�.");
	}

	if (MainRenderer_->GetTransform().GetLocalScale().CompareInt3D(float4::ONE) == true)
	{
		MsgBoxAssert("MainRenderer_ Scale ������ ���߽��ϴ�.");
	}
}

void DNFRenderObject::DNFUpdate()
{
	ErrorCheck();
}

void DNFRenderObject::DNFStart()
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	IsStart_ = true;
}
