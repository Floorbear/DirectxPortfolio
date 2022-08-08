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
