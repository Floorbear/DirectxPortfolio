#include "PreCompile.h"
#include "GameEngineCore/GameEngineCollision.h"

#include "DNFContentsMinimal.h"
#include "DNFRenderObject.h"
#include "DNFLevel.h"
#include "DNFBackground.h"
#include "DNFMath.h"

#include "DNFDebugGUI.h"

DNFRenderObject::DNFRenderObject():
	MainRenderer_(nullptr),
	ShadowRenderer_(),
	IsStart_(false),
	ShadowPos_(),
	ShadowRot_(),
	BotCol_(),
	BotPos_({0,-88.0f}),
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
	PrevHitData_()
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


	//체공상태면 그림자고정
	if (OnAir_ == true)
	{
		float4 GroundPos = GetTransform().GetWorldPosition();
		GroundPos += ShadowPos_;
		GroundPos.y = GroundYPos_-40.0f;
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

void DNFRenderObject::HitColCheck(ColOrder _Order)
{
	if (GodTime_.IsTimerOn() == true)
	{
		return;
	}

	if (CurHP_ == 0)
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

	//Hit충돌체와 공격타입이 불일치하면 리턴
	if (_Type != Data.Type)
	{
		return false;
	}


	//같은 공격에 여러번 충돌 방지
	if (Data.AttackName == PrevHitData_.AttackName && Data.AttCount <= PrevHitData_.AttCount)
	{
		return false;
	}

	//z축 차이(y축)가 나면 충돌 방지
	if (IsZPosHit(Data.ZPos) == false)
	{
		return false;
	}

	//여기 아래부터 공격을 받은건 확실해진다.

	//현재 받은 공격을 저장
	PrevHitData_ = Data;

	CalHP(-Data.Att);

	FlipX(-_Other->GetDirX());


	//공중공격이 아닌 경우
	if (OnAir_ == false && Data.YForce <= 0.0f)
	{
		GiveAndRecevieStiffness(PrevHitData_, _Other);
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

	//여기서부터 채공상태

	//최초의 공중에 뜸 상태 일때
	if (OnAir_ == false)
	{
		GroundYPos_ = GetTransform().GetWorldPosition().y;
		Force_.ForceY_ = PrevHitData_.YForce;
		GiveAndRecevieStiffness(PrevHitData_, _Other);
		//Down 상태 분기
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
			AirborneTime_ = 0.0f; //Down 상태에서도 이걸 넣으면, 다운상태적을 띄우면 중력이 초기화됨
			StateManager_.ChangeState("Airborne");
		}
		return true;
	}
	else//공중의 뜸 상태에서 공격을 받은경우
	{
		GiveAndRecevieStiffness(PrevHitData_, _Other);
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
	//z축 차이(y축)가 나면 충돌 방지
	int ZLength = abs(static_cast<int>(GetTransform().GetWorldPosition().y) - _ZPos);
	if (ZLength > 15) //상대방과 15이상 거리차가 나면 공격을 무시한다.
	{
		if (_ZPos != 0 && Force_.IsGravity() == false) //ZPos ==0 : 이 공격은 z축의 영향을 받지 않는다 && 공중에 뜸 상태에서는 z축 차이를 계산하지 않는다.
		{
			return false;
		}
	}
	return true;
}



bool DNFRenderObject::CanMove(const float4& _MoveValue)
{
	float4 MapScale = GetDNFLevel()->GetMapScale();
	float4 ActorPosBot = GetTransform().GetWorldPosition();
	ActorPosBot += _MoveValue;
	ActorPosBot.y = -ActorPosBot.y - BotPos_.y;

	GameEngineTexture* ColMap = DNFGlobalValue::CurrentLevel->GetBackground()->GetColRenderer()->GetCurTexture();

	//픽셀충돌범위를 넘어가면 이전 위치로 고정시킨다.
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
