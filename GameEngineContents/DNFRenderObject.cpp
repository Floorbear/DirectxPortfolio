#include "PreCompile.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "GameEngineCore/GameEngineCollision.h"

#include "DNFContentsMinimal.h"
#include "DNFRenderObject.h"
#include "DNFLevel.h"
#include "DNFBackground.h"
#include "DNFMath.h"
#include "EffectActor.h"
#include "DamageFont.h"

#include "DNFDebugGUI.h"

DNFRenderObject::DNFRenderObject() :
	MainRenderer_(nullptr),
	ShadowRenderer_(),
	IsStart_(false),
	ShadowPos_({ -10,-45,500 }),
	ShadowRot_(),
	BotCol_(),
	BotPos_({ 0,-88.0f }),
	PrevPos_(),
	OnAir_(false),
	GroundYPos_(),
	CurAttackData_(),
	AirborneTime_(),
	GodTime_(),
	MaxHP_(),
	CurHP_(),
	StateManager_(),
	HitAbove_(),
	HitBelow_(),
	PrevHitData_(),
	IsSuperArmor_(false),
	SuperArmorTimer_(),
	HitEffectMovePos_(),
	DamageFontMovePos_()
{
	AllDNFRenderer_.push_back(&MainRenderer_);
	AllDNFRenderer_.push_back(&ShadowRenderer_);
}

DNFRenderObject::~DNFRenderObject()
{
}

DNFLevel* DNFRenderObject::GetDNFLevel()
{
	return dynamic_cast<DNFLevel*>(GetLevel());
}

void DNFRenderObject::GiveAndRecevieStiffness(AttackData& _Data, DNFRenderObject* _Other)
{
	Stiffness_ = _Data.Stiffness;
	_Other->Stiffness_ = _Data.RStiffness;
}

void DNFRenderObject::StiffnessUpdate(float& _DeltaTime)
{
	if (Stiffness_ > 0.0f)
	{
		for (GameEngineTextureRenderer** i : AllDNFRenderer_)
		{
			if ((*i)->IsCurAnimation() == true)
			{
				(*i)->CurAnimationPauseOn();
			}
		}

		Stiffness_ -= _DeltaTime;
		_DeltaTime = 0.0f;
		if (Stiffness_ <= 0)
		{
			Stiffness_ = 0.0f;
			for (GameEngineTextureRenderer** i : AllDNFRenderer_)
			{
				if ((*i)->IsCurAnimation() == true)
				{
					(*i)->CurAnimationPauseOff();
				}
			}
		}
	}
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

void DNFRenderObject::ResetDNFAnimation()
{
	for (GameEngineTextureRenderer** i : AllDNFRenderer_)
	{
		if ((*i)->IsCurAnimation() == true)
		{
			(*i)->CurAnimationReset();
		}
	}
}

void DNFRenderObject::ShadowUpdate()
{
	//ShadowRenderer_->GetTransform().SetLocalPosition(ShadowPos_);
	//ShadowRenderer_->GetTransform().SetLocalRotation(ShadowRot_);
	//x�� �����
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

	//ü�����¸� �׸��ڰ���
	if (OnAir_ == true)
	{
		float4 GroundPos = GetTransform().GetWorldPosition();
		GroundPos += ShadowPos_;
		GroundPos.y = GroundYPos_ - 40.0f;
		ShadowRenderer_->GetTransform().SetWorldPosition(GroundPos);
	}
}

void DNFRenderObject::CalHP(int _Value)
{
	CurHP_ += _Value;
	if (CurHP_ <= 0)
	{
		CurHP_ = 0;
	}
	if (CurHP_ > MaxHP_)
	{
		CurHP_ = MaxHP_;
	}
}

int DNFRenderObject::ShakeDamage(int _Value, float _Seed)
{
	float Value = static_cast<float>(_Value) + _Seed;
	float Left = Value * 0.9f;
	float Right = Value * 1.1f;
	float CalDmg = GameEngineRandom::MainRandom.RandomFloat(Left, Right);
	return static_cast<int>(CalDmg);
}

void DNFRenderObject::SetDamageFont(int _Value, float4 _WorldPos, int _FontType)
{
	DamageFont* NewDamageFont = GetLevel()->CreateActor<DamageFont>();
	NewDamageFont->GetTransform().SetWorldPosition(_WorldPos);
	NewDamageFont->GetTransform().SetLocalMove({ 0,0,-1000 });

	NewDamageFont->SetDamageFont(_Value, _FontType);
}

void DNFRenderObject::HitColCheck(ColOrder _Order)
{
	if (GodTime_.IsTimerOn() == true)
	{
		return;
	}

	//if (CurHP_ == 0)
	//{
	//	return;
	//}

	if (StateManager_.GetCurStateStateName() == "Die")
	{
		return;
	}

	HitBelow_->IsCollision(CollisionType::CT_OBB2D, _Order, CollisionType::CT_OBB2D,
		std::bind(&DNFRenderObject::BelowHitCheck, this, std::placeholders::_1, std::placeholders::_2));

	HitAbove_->IsCollision(CollisionType::CT_OBB2D, _Order, CollisionType::CT_OBB2D,
		std::bind(&DNFRenderObject::AboveHitCheck, this, std::placeholders::_1, std::placeholders::_2));
}

bool DNFRenderObject::HitCheck(AttackType _Type, DNFRenderObject* _Other)
{
	AttackData Data = _Other->CurAttackData_;

	//�浹�� ������ Hitó������ �ʴ� ���
	if (IsHit(_Type, Data) == false)
	{
		return false;
	}

	//���� �Ʒ����� ������ ������ Ȯ��������.

	//���� ���� ������ ����
	PrevHitData_ = Data;

	int Damage = ShakeDamage(Data.Att, GetTransform().GetWorldPosition().x);
	CalHP(-Damage);

	GiveAndRecevieStiffness(PrevHitData_, _Other);

	HPBarUpdate();
	//�����Ϳ� ��������Ʈ�� ������ �����ض�
	if (PrevHitData_.AttEffect != Effect::None)
	{
		SetEffect(PrevHitData_.AttEffect, GetTransform().GetWorldPosition() + HitEffectMovePos_, _Other->GetDirX());
	}

	//������
	SetDamageFont(Damage, GetTransform().GetWorldPosition() + DamageFontMovePos_, Data.Font);

	if (IsSuperArmor_ == true)
	{
		return true;
	}

	FlipX(-_Other->GetDirX());

	//���߰����� �ƴ� ���
	if (OnAir_ == false && Data.YForce <= 0.0f)
	{
		if (StateManager_.GetCurStateStateName() == "Down")
		{
			ResetDNFAnimation();
			StateManager_.ChangeState("Down");
		}
		else
		{
			StateManager_.ChangeState("Hit");
		}
		return true;
	}

	//���⼭���� ä������

	//������ ���߿� �� ���� �϶�
	if (OnAir_ == false)
	{
		GroundYPos_ = GetTransform().GetWorldPosition().y;
		Force_.ForceY_ = PrevHitData_.YForce;

		//Down ���� �б�
		if (StateManager_.GetCurStateStateName() == "Down")
		{
			ResetDNFAnimation();
			Force_.ForceY_ = PrevHitData_.YForce * 0.5f;
			OnAir_ = true;
			Force_.OnGravity();
			StateManager_.ChangeState("Down");
		}
		else
		{
			AirborneTime_ = 0.0f; //Down ���¿����� �̰� ������, �ٿ�������� ���� �߷��� �ʱ�ȭ��
			StateManager_.ChangeState("Airborne");
		}
		return true;
	}
	else//������ �� ���¿��� ������ �������
	{
		Force_.ForceY_ = PrevHitData_.YForce;
		if (StateManager_.GetCurStateStateName() == "Down")
		{
			ResetDNFAnimation();
			Force_.ForceY_ = PrevHitData_.YForce * 0.5f;
			OnAir_ = true;
			StateManager_.ChangeState("Down");
		}
		else
		{
			StateManager_.ChangeState("Airborne");
		}
		return true;
	}
}

bool DNFRenderObject::AboveHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	DNFRenderObject* Other = dynamic_cast<DNFRenderObject*>(_Other->GetParent());
	return HitCheck(AttackType::Above, Other);
}

bool DNFRenderObject::BelowHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	DNFRenderObject* Other = dynamic_cast<DNFRenderObject*>(_Other->GetParent());
	return HitCheck(AttackType::Below, Other);
}

bool DNFRenderObject::IsZPosHit(int _ZPos)
{
	//z�� ����(y��)�� ���� �浹 ����
	int ZLength = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y) - _ZPos;
	if (ZLength > 10 || ZLength < -40) //����� �����̻� �Ÿ����� ���� ������ �����Ѵ�.
	{
		if (_ZPos != 0 && Force_.IsGravity() == false) //ZPos ==0 : �� ������ z���� ������ ���� �ʴ´� && ���߿� �� ���¿����� z�� ���̸� ������� �ʴ´�.
		{
			return false;
		}
	}
	return true;
}

bool DNFRenderObject::IsHit(AttackType _Type, AttackData _Data)
{
	//Hit�浹ü�� ����Ÿ���� ����ġ�ϸ� ����
	if (_Type != _Data.Type)
	{
		return false;
	}

	//���� ���ݿ� ������ �浹 ����
	if (_Data.AttackName == PrevHitData_.AttackName && _Data.AttCount <= PrevHitData_.AttCount)
	{
		return false;
	}

	//z�� ����(y��)�� ���� �浹 ����
	if (IsZPosHit(_Data.ZPos) == false)
	{
		return false;
	}
	return true;
}

EffectActor* DNFRenderObject::SetEffect(Effect _Effect, float4 _WorldPos, float4 _Dir)
{
	EffectActor* NewEffect = GetLevel()->CreateActor<EffectActor>();
	NewEffect->GetTransform().SetWorldPosition(_WorldPos);
	NewEffect->GetTransform().SetLocalMove({ 0,0,-300 });

	//Dir������ ������ Dir�� �ٲ����
	if (_Dir.Length() > 0)
	{
		NewEffect->GetTransform().SetLocalScale({ _Dir.x, 1, 1 });
	}

	NewEffect->InitEffect(_Effect);
	return NewEffect;
}

bool DNFRenderObject::CanMove(const float4& _MoveValue)
{
	float4 MapScale = GetDNFLevel()->GetMapScale();
	float4 ActorPosBot = GetTransform().GetWorldPosition();
	ActorPosBot += _MoveValue;
	ActorPosBot.y = -ActorPosBot.y - BotPos_.y;

	GameEngineTexture* ColMap = DNFGlobalValue::CurrentLevel->GetBackground()->GetColRenderer()->GetCurTexture();

	//�ȼ��浹������ �Ѿ�� ���� ��ġ�� ������Ų��.
	if (OnAir_ == false)
	{
		if (ColMap->GetPixelToFloat4(static_cast<int>(ActorPosBot.x), static_cast<int>(ActorPosBot.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			return false;
		}
	}
	else
	{
		float4 DownPos;
		DownPos.y = -GroundYPos_ - BotPos_.y;
		if (ColMap->GetPixelToFloat4(static_cast<int>(ActorPosBot.x), static_cast<int>(DownPos.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			return false;
		}
	}

	return true;
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
	ShadowUpdate();
	ErrorCheck();
	ZSort();
	//BotCol ������Ʈ
	BotCol_->GetTransform().SetLocalPosition(float4(BotPos_.x, BotPos_.y, -500));
}

void DNFRenderObject::DNFStart()
{
	ShadowRenderer_ = CreateComponent<GameEngineTextureRenderer>("ShadowRenderer");
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());

	//BotCol
	BotCol_ = CreateComponent<GameEngineCollision>("Col");
	BotCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 1.0f, 0.5f));
	BotCol_->GetTransform().SetLocalScale(float4(5, 5, 1));
	BotCol_->GetTransform().SetLocalMove(float4(0, 0, -500));
	BotCol_->ChangeOrder(ColOrder::Debug);

	//���� ���� ��ġ
	PrevPos_ = GetTransform().GetWorldPosition();

	ShadowRenderer_->GetPixelData().MulColor = float4(0, 0, 0, 0.6f);
	ShadowRot_ = { -60,0,5 };
	IsStart_ = true;
}

void DNFRenderObject::ZSort()
{
	float4 CurPos = GetTransform().GetWorldPosition();
	CurPos.z = CurPos.y;
	GetTransform().SetWorldPosition(CurPos);
}