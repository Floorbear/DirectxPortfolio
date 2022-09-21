#include "PreCompile.h"
#include "VilmarkMap.h"
#include "DNFLevel.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFGlobalValue.h"
#include "DNFDebugGUI.h"

VilmarkMap::VilmarkMap() :
	RightDoor_Renderer_(),
	DoorEffect_Timer_(),
	FadeRenderer_()
{
	RightDoor_Renderer_.reserve(3);
}

VilmarkMap::~VilmarkMap()
{
}

void VilmarkMap::OnDoor()
{
	//�����ʹ� ���� Off
	RightDoor_Renderer_[1]->Off();
	//�����ʹ� ����Ʈ On
	RightDoor_Renderer_[2]->On();
}

void VilmarkMap::Start()
{
	GetTransform().SetLocalMove({ 0, 0, 1000 });
	InitBackground("Vilmark_Background_00");

	InitRenderer();

	//�����ʹ� �浹ü
	{
		RightDoorCol_ = CreateComponent<GameEngineCollision>("Middle");
		RightDoorCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
		RightDoorCol_->GetTransform().SetLocalPosition({ 1300,-340 });
		RightDoorCol_->GetTransform().SetLocalScale({ 50,100 });
		RightDoorCol_->ChangeOrder(ColOrder::DoorRight);
	}
	//���ʹ��� ������ ���ʹ� ���� �Լ��� ȣ���ؼ� �����ϰ� ����
	//DNFDebugGUI::AddMutableValue("BackgroundBushPos", &DNFGlobalValue::Temp1);
}

void VilmarkMap::InitRenderer()
{
	//���̵� �� �ƿ�
	FadeRenderer_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	FadeRenderer_->GetTransform().SetLocalScale({ 2000.0f,2000.0f });
	FadeRenderer_->GetTransform().SetLocalMove({ 0,0,-4000 });
	FadeRenderer_->GetPixelData().PlusColor = { -1,-1,-1,0 };
	//�ν�
	BushRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	BushRenderer_->SetTexture("Bush.png");
	BushRenderer_->ScaleToTexture();
	BushRenderer_->SetPivot(PIVOTMODE::LEFTTOP);

	//�޹��
	FarRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	FarRenderer_->SetTexture("Vilmark_far.png");
	FarRenderer_->ScaleToTexture();
	FarRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	PrevCameraPos_ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
	FarRenderer_->GetTransform().SetWorldPosition({ -200.0f,FarRenderer_->GetTransform().GetWorldPosition().y,GetTransform().GetLocalPosition().z + 10 });

	//������ ��
	{
		//��¦
		{
			GameEngineTextureRenderer* NewRenderer = CreateComponent<GameEngineTextureRenderer>();
			NewRenderer->SetTexture("Door0.png");
			NewRenderer->ScaleToTexture();
			NewRenderer->SetPivot(PIVOTMODE::LEFTTOP);
			NewRenderer->GetTransform().SetLocalPosition({ 1228.f,-220.f });
			RightDoor_Renderer_.push_back(NewRenderer);
		}
		//������
		{
			GameEngineTextureRenderer* NewRenderer = CreateComponent<GameEngineTextureRenderer>();
			NewRenderer->SetTexture("Door1.png");
			NewRenderer->ScaleToTexture();
			NewRenderer->SetPivot(PIVOTMODE::LEFTTOP);
			NewRenderer->GetTransform().SetLocalPosition({ 1228.f,-220.f });
			RightDoor_Renderer_.push_back(NewRenderer);
		}
		//����Ʈ
		{
			GameEngineTextureRenderer* NewRenderer = CreateComponent<GameEngineTextureRenderer>();
			NewRenderer->SetTexture("Door2.png");
			NewRenderer->ScaleToTexture();
			NewRenderer->SetPivot(PIVOTMODE::LEFTTOP);
			NewRenderer->GetTransform().SetLocalPosition({ 1228.f,-220.f });
			NewRenderer->Off();
			RightDoor_Renderer_.push_back(NewRenderer);
		}
	}
}

void VilmarkMap::Update(float _DeltaTime)
{
	//DoorEffect �����Ÿ��°�
	DoorEffect(_DeltaTime);
	//Far
	ChaseFarBackground();
}

void VilmarkMap::ChaseFarBackground()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
	if (PrevCameraPos_.CompareInt3D(CameraPos) == false)	//ī�޶��� �������� �����Ǹ� �̵������� ����
	{
		float MoveValue = CameraPos.x - PrevCameraPos_.x;
		MoveValue *= FarSpeed_;
		FarRenderer_->GetTransform().SetLocalMove({ MoveValue,0,0 });
		//FarRenderer_->GetTransform().SetWorldPosition()
		PrevCameraPos_ = CameraPos;
	}
}

void VilmarkMap::DoorEffect(float _DeltaTime)
{
	if (RightDoor_Renderer_[2]->IsUpdate() == true)
	{
		if (DoorEffect_Timer_.IsTimerOn() == false)
		{
			DoorEffect_Timer_.StartTimer(1.5f);
		}
		DoorEffect_Timer_.Update(_DeltaTime * 2.0f);
		float AlphaValue = 1.5f - DoorEffect_Timer_.GetCurTime();
		if (AlphaValue >= 1.0f)
		{
			AlphaValue = 1.0f;
		}
		RightDoor_Renderer_[2]->GetPixelData().MulColor.a = AlphaValue;
	}
}

void VilmarkMap::End()
{
}