#include "PreCompile.h"
#include "VilmarkMap.h"
#include "DNFLevel.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFGlobalValue.h"
#include "DNFDebugGUI.h"

VilmarkMap::VilmarkMap() :
	RightDoor_Renderer_(),
	DoorEffect_Timer_(),
	LeftDoorCol_(),
	VilmarkLogo_()
{
	RightDoor_Renderer_.reserve(3);
	LeftDoor_Renderer_.reserve(3);
}

VilmarkMap::~VilmarkMap()
{
}

void VilmarkMap::OnDoor()
{
	if (RightDoor_Renderer_.empty() == false)
	{
		//�����ʹ� ���� Off
		RightDoor_Renderer_[1]->Off();
		//�����ʹ� ����Ʈ On
		RightDoor_Renderer_[2]->On();
	}

	if (LeftDoor_Renderer_.empty() == false)
	{
		//���ʹ� ���� Off
		LeftDoor_Renderer_[1]->Off();
		//���ʹ� ����Ʈ On
		LeftDoor_Renderer_[2]->On();
	}
}

void VilmarkMap::MakeLeftDoor()
{
	//���� �� ������
	{
		//��¦
		{
			GameEngineTextureRenderer* NewRenderer = CreateComponent<GameEngineTextureRenderer>();
			NewRenderer->SetTexture("Door0.png");
			NewRenderer->ScaleToTexture();
			NewRenderer->SetPivot(PIVOTMODE::LEFTTOP);
			NewRenderer->GetTransform().SetLocalPosition({ -40.f,-250.f,-5000.f });
			LeftDoor_Renderer_.push_back(NewRenderer);
		}
		//������
		{
			GameEngineTextureRenderer* NewRenderer = CreateComponent<GameEngineTextureRenderer>();
			NewRenderer->SetTexture("Door1.png");
			NewRenderer->ScaleToTexture();
			NewRenderer->SetPivot(PIVOTMODE::LEFTTOP);
			NewRenderer->GetTransform().SetLocalPosition({ -40.f,-250.f,-5000.f });
			LeftDoor_Renderer_.push_back(NewRenderer);
		}
		//����Ʈ
		{
			GameEngineTextureRenderer* NewRenderer = CreateComponent<GameEngineTextureRenderer>();
			NewRenderer->SetTexture("Door2.png");
			NewRenderer->ScaleToTexture();
			NewRenderer->SetPivot(PIVOTMODE::LEFTTOP);
			NewRenderer->GetTransform().SetLocalPosition({ -40.f,-250.f,-5000.f });
			NewRenderer->Off();
			LeftDoor_Renderer_.push_back(NewRenderer);
		}
	}
	//���ʹ� �浹ü
	{
		LeftDoorCol_ = CreateComponent<GameEngineCollision>("Middle");
		LeftDoorCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
		LeftDoorCol_->GetTransform().SetLocalPosition({ 38,-380 });
		LeftDoorCol_->GetTransform().SetLocalScale({ 50,100 });
		LeftDoorCol_->ChangeOrder(ColOrder::DoorLeft);
	}
}

void VilmarkMap::MakeRightDoor()
{
	//������ �� ������
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
	//�����ʹ� �浹ü
	{
		RightDoorCol_ = CreateComponent<GameEngineCollision>("Middle");
		RightDoorCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
		RightDoorCol_->GetTransform().SetLocalPosition({ 1300,-340 });
		RightDoorCol_->GetTransform().SetLocalScale({ 50,100 });
		RightDoorCol_->ChangeOrder(ColOrder::DoorRight);
	}
}

void VilmarkMap::MakeLogo()
{
	VilmarkLogo_ = CreateComponent<GameEngineUIRenderer>();
	VilmarkLogo_->CreateFrameAnimationFolder("Logo", FrameAnimation_DESC("VilmarkLogo", 0.05f, true));
	VilmarkLogo_->ChangeFrameAnimation("Logo");
	VilmarkLogo_->SetScaleRatio(1.3f);
	VilmarkLogo_->ScaleToTexture();
	VilmarkLogo_->SetPivot(PIVOTMODE::CENTER);
	VilmarkLogo_->GetTransform().SetLocalPosition({ 0,0,-10000 });

	VilmarkLogo_->AnimationBindEnd("Logo", [&](const FrameAnimation_DESC _Desc)
		{
			if (LogoLoopCount_ >= 3)
			{
				VilmarkLogo_->Off();
			}
			LogoLoopCount_++;
		});
}

void VilmarkMap::Start()
{
	GetTransform().SetLocalMove({ 0, 0, 1000 });
	InitBackground("Vilmark_Background_00");

	InitRenderer();

	//���ʹ��� ������ ���ʹ� ���� �Լ��� ȣ���ؼ� �����ϰ� ����
	//DNFDebugGUI::AddMutableValue("BackgroundBushPos", &DNFGlobalValue::Temp1);
}

void VilmarkMap::InitRenderer()
{
	//�ν�
	BushRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	BushRenderer_->SetTexture("Bush.png");
	BushRenderer_->GetTransform().SetLocalMove({ 0,0,-6000 });
	BushRenderer_->ScaleToTexture();
	BushRenderer_->SetPivot(PIVOTMODE::LEFTTOP);

	//�޹��
	FarRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	FarRenderer_->SetTexture("Vilmark_far.png");
	FarRenderer_->ScaleToTexture();
	FarRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	PrevCameraPos_ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
	FarRenderer_->GetTransform().SetWorldPosition({ -200.0f,FarRenderer_->GetTransform().GetWorldPosition().y,GetTransform().GetLocalPosition().z + 10 });
}

void VilmarkMap::Update(float _DeltaTime)
{
	//FadeIn & Out
	BackgroundUpdate(_DeltaTime);
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
	if (RightDoor_Renderer_.empty() == false) //������ ���� ���� ���� ȣ��
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

	if (LeftDoor_Renderer_.empty() == false) //���� ���� ���� ���� ȣ��
	{
		if (LeftDoor_Renderer_[2]->IsUpdate() == true)
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
			LeftDoor_Renderer_[2]->GetPixelData().MulColor.a = AlphaValue;
		}
	}
}

void VilmarkMap::End()
{
}