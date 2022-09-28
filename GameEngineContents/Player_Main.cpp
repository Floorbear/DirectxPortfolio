#include "PreCompile.h"
#include "Player_Main.h"

#include "DNFDefineList.h"
#include "DNFGlobalValue.h"

#include "DNFLevel.h"
#include "DNFBackground.h"
#include "DNFDebugGUI.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Player_Main::Player_Main() :
	UIRenderer_(nullptr),
	WeaponRenderer_b_(),
	WeaponRenderer_c_(),
	CoatRenderer_a_(),
	CoatRenderer_b_(),
	CoatRenderer_c_(),
	CoatRenderer_d_(),
	PantsRenderer_a_(),
	PantsRenderer_b_(),
	PantsRenderer_d_(),
	CapRenderer_a_(),
	CapRenderer_b_(),
	CapRenderer_c_(),
	HairRenderer_a_(),
	HairRenderer_d_(),
	BeltRenderer_c_(),
	BeltRenderer_d_(),
	ShoesRenderer_a_(),
	ShoesRenderer_b_(),
	AttackCol_(),
	AttackCount_(),
	IsAttack_End_(false),
	IsReadyNextAttack_(false),
	NextAttackAni_(),
	BottomAttackCol_(),
	Value_(),
	SkillCoolTime_(),
	SuperArmorMulTime_(),
	PrevMapPos_(0)
{
	InitDefaultValue();

	AllDNFRenderer_.push_back(&WeaponRenderer_b_);
	AllDNFRenderer_.push_back(&WeaponRenderer_c_);
	AllDNFRenderer_.push_back(&CoatRenderer_a_);
	AllDNFRenderer_.push_back(&CoatRenderer_b_);
	AllDNFRenderer_.push_back(&CoatRenderer_c_);
	AllDNFRenderer_.push_back(&CoatRenderer_d_);
	AllDNFRenderer_.push_back(&PantsRenderer_a_);
	AllDNFRenderer_.push_back(&PantsRenderer_b_);
	AllDNFRenderer_.push_back(&PantsRenderer_d_);
	AllDNFRenderer_.push_back(&CapRenderer_a_);
	AllDNFRenderer_.push_back(&CapRenderer_b_);
	AllDNFRenderer_.push_back(&CapRenderer_c_);
	AllDNFRenderer_.push_back(&HairRenderer_a_);
	AllDNFRenderer_.push_back(&HairRenderer_d_);
	AllDNFRenderer_.push_back(&BeltRenderer_c_);
	AllDNFRenderer_.push_back(&BeltRenderer_d_);
	AllDNFRenderer_.push_back(&ShoesRenderer_a_);
	AllDNFRenderer_.push_back(&ShoesRenderer_b_);
	AllDNFRenderer_.push_back(&Frenzy_Upper_);
	AllDNFRenderer_.push_back(&Frenzy_Under_);
	AllDNFRenderer_.push_back(&Frenzy_Trail_);//Frenzy_Trail_

	AllCopyRenderer_.reserve(20);
}

void Player_Main::InitDefaultValue()
{
	//Scale
	Value_.HitAbovePos = { -20,-15.0f,-500.0f };
	Value_.HitAboveScale = { 50.0f,70.0f,1.0f };
	Value_.HitBelowPos = { -20,-55.0f,-500.0f };
	Value_.HitBelowScale = { 50.0f,70.0f,1.0f };

	Value_.AutoAttackPos = float4(50, 0, -500);
	Value_.AutoAttackScale = float4(120, 55, 1);
	Value_.UpperSlashPos = float4(75, -45, -500);
	Value_.UpeerSlashScale = float4(120, 100, 1);

	Value_.GoreCrossSpawnPos = float4(75, -45, -500);
	Value_.GoreCrossScale = float4(140, 120, 1);

	Value_.SuperArmorPos = { 1.0f,1.0f };
	Value_.SuperArmorScale = { 528.0f,513.0f };
	Value_.SuperArmorMul = 1000.0f;

	//공격력
	Value_.UpperSlashAtt = 15000;
	Value_.AutoAttackAtt = 7000;

	//스텟
	MaxHP_ = Value_.Default_HP;
	CurHP_ = MaxHP_;

	MaxMP_ = Value_.Default_MP;
	CurMP_ = MaxMP_;

	HitEffectMovePos_ = { 0,-30,0 };

	MPConsumption_.insert(std::make_pair("UpperSlash", Value_.UpperSlash_MP));
	MPConsumption_.insert(std::make_pair("GoreCross", Value_.GoreCross_MP));
	MPConsumption_.insert(std::make_pair("HopSmash", Value_.HopSmash_MP));
	MPConsumption_.insert(std::make_pair("Frenzy", 1));
	MPConsumption_.insert(std::make_pair("Fury", Value_.Fury_MP));
}

Player_Main::~Player_Main()
{
	for (auto i : SkillCoolTime_)
	{
		if (i.second != nullptr)
		{
			delete i.second;
		}
	}
}

void Player_Main::Start()
{
	DNFStart();

	InitCol();

	//아바타생성
	AvatarManager_.LinkPlayerToAvatar(this);
	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);

	//카피렌더러 생성
	for (size_t i = 0; i < 20; i++)
	{
		GameEngineTextureRenderer* NewRenderer = CreateComponent<GameEngineTextureRenderer>();
		NewRenderer->GetTransform().SetLocalScale({ 500,500,1 });
		NewRenderer->Off();
		AllCopyRenderer_.push_back(NewRenderer);
	}

	//스테이트 초기화
	InitState();
	StateManager_.ChangeState("Idle");

	InitAniFunc();

	InitSkillCoolTime();

	Frenzy_Init();

	Force_.FrictionX_ = Value_.DefaultFriction;
	Force_.Gravity_ = Value_.DefaultGravity;
	Force_.SetTransfrom(&GetTransform());

	DNFDebugGUI::AddMutableValue("Temp1", &DNFGlobalValue::Temp1);
}

void Player_Main::Update(float _DeltaTime)
{
	if (IsLevelChanging_ == true) //레벨이 변하고 있으면 하는일을 멈춘다.
	{
		return;
	}
	CopyRendererUpdate(_DeltaTime);
	CoolTimeUpdate(_DeltaTime);
	StiffnessUpdate(_DeltaTime);
	if (Stiffness_ > 0)
	{
		return;
	}
	UpdateShakeCamera(_DeltaTime);
	if (SuperArmorTimer_.IsTimerOn() == true)
	{
		SuperArmorTimer_.Update(_DeltaTime);
	}
	else
	{
		for (auto i : AllCopyRenderer_)
		{
			i->Off();
		}
		IsSuperArmor_ = false;
	}

	DNFUpdate();
	HitColCheck(ColOrder::MonsterAttack);
	StateManager_.Update(_DeltaTime);
	Force_.Update(_DeltaTime);

	//제한된 범위 밖으로 못나가는 카메라& 캐릭터
	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		CheckColMap();
		ChaseCamera(_DeltaTime);
	}
	AvatarManager_.UpdateMotion();
	ShadowUpdate();
}

void Player_Main::End()
{
}

void Player_Main::ChaseCamera(float _DeltaTime)
{
	//카메라 Pos관련
	float4 CurPos = GetTransform().GetWorldPosition();
	float4 MapScale = GetDNFLevel()->GetMapScale();
	float Zoom = DNFGlobalValue::CurrentLevel->GetZoom();
	float4 CameraPos;
	CameraPos.z = -500;

	CameraPos.x = GetTransform().GetWorldPosition().x;

	float4 ShakePos = ShakeData_;

	//왼쪽
	if (CurPos.x - 640 * Zoom < 0.0f)
	{
		CameraPos.x = 640 * Zoom;
		ShakePos.x = abs(ShakePos.x);
	}
	//오른쪽
	if (CurPos.x + 640 * Zoom > MapScale.x)
	{
		CameraPos.x = MapScale.x - 640 * Zoom;
		ShakePos.x = -abs(ShakePos.x);
	}

	CameraPos.y = GetTransform().GetWorldPosition().y;
	//아래
	if (CurPos.y - 360 * Zoom < -MapScale.y)
	{
		CameraPos.y = -MapScale.y + 360 * Zoom;
		ShakePos.y = abs(ShakePos.y);
	}
	//아래
	if ((CurPos.y - 360 * Zoom) + ShakePos.y < -MapScale.y)
	{
		ShakePos.y = abs(ShakePos.y);
	}
	//위
	if (CurPos.y + 360 * Zoom > 0.0f)
	{
		CameraPos.y = -360 * Zoom;
		ShakePos.y = -abs(ShakePos.y);
	}

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(CameraPos + ShakePos);
}

void Player_Main::CheckColMap()
{
	float4 MapScale = GetDNFLevel()->GetMapScale();
	float4 PlayerPosBot = GetTransform().GetWorldPosition();
	PlayerPosBot.y = -PlayerPosBot.y - BotPos_.y;

	GameEngineTexture* ColMap = DNFGlobalValue::CurrentLevel->GetBackground()->GetColRenderer()->GetCurTexture();

	//픽셀충돌범위를 넘어가면 이전 위치로 고정시킨다.
	if (OnAir_ == false)
	{
		if (ColMap->GetPixelToFloat4(static_cast<int>(PlayerPosBot.x), static_cast<int>(PlayerPosBot.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			GetTransform().SetWorldPosition(PrevPos_);
		}
	}
	else //체공중입니다
	{
		float4 DownPos = GetTransform().GetWorldPosition();
		DownPos.y = -GroundYPos_ - BotPos_.y;
		if (ColMap->GetPixelToFloat4(static_cast<int>(PlayerPosBot.x), static_cast<int>(DownPos.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			GetTransform().SetWorldPosition(PrevPos_);
			Force_.ForceX_ = 0.f;
		}
	}

	//이전위치와 차이가 있으면 PrevPos를 갱신한다.
	if (DNFMath::Length(PrevPos_, GetTransform().GetWorldPosition()) >= 0.5f)
	{
		PrevPos_ = GetTransform().GetWorldPosition();
	}
}

void Player_Main::InitCol()
{
	//MiddleHit
	HitAbove_ = CreateComponent<GameEngineCollision>("Middle");
	HitAbove_->SetDebugSetting(CollisionType::CT_OBB2D, float4(1.0f, 0.0f, 0.0f, 0.5f));
	HitAbove_->GetTransform().SetLocalPosition(Value_.HitAbovePos);
	HitAbove_->GetTransform().SetLocalScale(Value_.HitAboveScale);
	HitAbove_->ChangeOrder(ColOrder::PlayerHit);

	//BottomHit
	HitBelow_ = CreateComponent<GameEngineCollision>("Bottom");
	HitBelow_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0.0f, 1.0f, 0.0f, 0.5f));
	HitBelow_->GetTransform().SetLocalPosition(Value_.HitBelowPos);
	HitBelow_->GetTransform().SetLocalScale(Value_.HitBelowScale);
	HitBelow_->ChangeOrder(ColOrder::PlayerHit);

	//Attack 콜라이더
	AttackCol_ = CreateComponent<GameEngineCollision>("Attack");
	AttackCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0, 1.0f, 0, 0.5f));
	AttackCol_->ChangeOrder(ColOrder::PlayerAttack);
	AttackCol_->Off();
}

void Player_Main::InitState()
{
	//스테이트 초기화
	StateManager_.CreateStateMember("Idle", std::bind(&Player_Main::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::IdleStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Move", std::bind(&Player_Main::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::MoveStart, this, std::placeholders::_1));
	StateManager_.CreateStateMember("AutoAttack", std::bind(&Player_Main::AutoAttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::AutoAttackStart, this, std::placeholders::_1),
		std::bind(&Player_Main::AutoAttackEnd, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Jump", std::bind(&Player_Main::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::JumpStart, this, std::placeholders::_1),
		std::bind(&Player_Main::JumpEnd, this, std::placeholders::_1));

	StateManager_.CreateStateMember("UpperSlash", std::bind(&Player_Main::UpperSlashUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::UpperSlashStart, this, std::placeholders::_1),
		std::bind(&Player_Main::UpperSlashEnd, this, std::placeholders::_1));

	StateManager_.CreateStateMember("HopSmash", std::bind(&Player_Main::HopSmashUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::HopSmashStart, this, std::placeholders::_1),
		std::bind(&Player_Main::HopSmashEnd, this, std::placeholders::_1));

	StateManager_.CreateStateMember("GoreCross", std::bind(&Player_Main::GoreCrossUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::GoreCrossStart, this, std::placeholders::_1),
		std::bind(&Player_Main::GoreCrossEnd, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Hit", std::bind(&Player_Main::HitUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::HitStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Airborne", std::bind(&Player_Main::AirborneUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::AirborneStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Down", std::bind(&Player_Main::DownUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::DownStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Frenzy", std::bind(&Player_Main::FrenzyUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::FrenzyStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Fury", std::bind(&Player_Main::FuryUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player_Main::FuryStart, this, std::placeholders::_1));
}

void Player_Main::StartSuperArmor(float _SuperArmorTime)
{
	//Clear 해야함
	for (auto i : AllCopyRenderer_)
	{
		i->Off();
	}

	int count = 0;
	for (auto i : AvatarManager_.GetRenderList())
	{
		if (i.second->GetNameCopy() == "ShadowRenderer")
		{
			continue;
		}
		if (i.second->IsUpdate() == false)
		{
			continue;
		}
		AllCopyRenderer_[count]->On();
		float4 SetPos = i.second->GetTransform().GetLocalPosition();
		SetPos.z = i.second->GetTransform().GetLocalPosition().z + 20;
		//SetPos.x = i.second->GetTransform().GetLocalPosition().x + 20;
		AllCopyRenderer_[count]->GetTransform().SetLocalPosition(SetPos);

		//스케일
		SuperArmorScale_ = { 730,730 };
		AllCopyRenderer_[count]->GetTransform().SetLocalScale({ SuperArmorScale_ });
		AllCopyRenderer_[count]->SetTexture(i.second->GetCurTexture());
		count++;
	}

	for (auto i : AllCopyRenderer_)
	{
		i->GetPixelData().MulColor = float4(99999.f, 0, 0, 0.6f);
	}
	IsSuperArmor_ = true;
	if (SuperArmorTimer_.IsTimerOn() == true)
	{
		SuperArmorTimer_ += _SuperArmorTime;
	}
	else
	{
		SuperArmorTimer_.StartTimer(_SuperArmorTime);
	}
}

void Player_Main::CopyRendererUpdate(float _DeltaTime)
{
	int count = 0;
	for (auto i : AvatarManager_.GetRenderList())
	{
		if (i.second->IsUpdate() == false)
		{
			continue;
		}
		if (i.second->GetNameCopy() == "ShadowRenderer")
		{
			continue;
		}

		//크기 커졌다가 작아지는 것
		if (SuperArmorScale_.x > Value_.SuperArmorScale.x)
		{
			SuperArmorScale_.x -= _DeltaTime * 100.f;
		}
		else
		{
			SuperArmorScale_.x = Value_.SuperArmorScale.x;
		}
		if (SuperArmorScale_.y > Value_.SuperArmorScale.y)
		{
			SuperArmorScale_.y -= _DeltaTime * 100.f;
		}
		else
		{
			SuperArmorScale_.y = Value_.SuperArmorScale.y;
		}
		if (i.second->GetCurTexture() == nullptr)
		{
			continue;
		}
		AllCopyRenderer_[count]->SetTexture(i.second->GetCurTexture());
		AllCopyRenderer_[count]->GetTransform().SetLocalScale(SuperArmorScale_);

		//색깔
		if (SuperArmorMulTime_ < 5.0f)
		{
			SuperArmorMulTime_ += _DeltaTime;
			AllCopyRenderer_[count]->GetPixelData().MulColor = float4(0, 0, 0, 0.0f);
			AllCopyRenderer_[count]->GetPixelData().PlusColor = float4(1, SuperArmorMulTime_ / 5.0f, 0, 1.f);
		}
		else if (SuperArmorMulTime_ >= 5.0 && SuperArmorMulTime_ < 10.0)
		{
			SuperArmorMulTime_ += _DeltaTime;
			AllCopyRenderer_[count]->GetPixelData().MulColor = float4(0, 0, 0, 0.0f);
			AllCopyRenderer_[count]->GetPixelData().PlusColor = float4(1, 1 - (SuperArmorMulTime_ - 5.0f) / 5, 0, 1.f);
		}
		//else if (SuperArmorMulTime_ >= 10.0f && SuperArmorMulTime_ < 15.0f)
		//{
		//	SuperArmorMulTime_ += _DeltaTime;
		//	AllCopyRenderer_[count]->GetPixelData().MulColor = float4(100, 6.0f * (SuperArmorMulTime_-10.0f), 0, 0.5f);
		//}
		else
		{
			SuperArmorMulTime_ = 0.0f;
		}

		//Pos
		float4 SetPos = i.second->GetTransform().GetLocalPosition();
		SetPos.x = i.second->GetTransform().GetLocalPosition().x + Value_.SuperArmorPos.x;
		SetPos.y = i.second->GetTransform().GetLocalPosition().y + Value_.SuperArmorPos.y;
		SetPos.z = i.second->GetTransform().GetLocalPosition().z + 20;
		AllCopyRenderer_[count]->GetTransform().SetLocalPosition(SetPos);
		count++;
	}
}

float4 Player_Main::GetMoveDir()
{
	float4 MoveDir = float4::ZERO;

	if (GameEngineInput::GetInst()->IsPress("Right") == true)
	{
		MoveDir += float4::RIGHT;
	}

	if (GameEngineInput::GetInst()->IsPress("Left") == true)
	{
		MoveDir += float4::LEFT;
	}
	if (GameEngineInput::GetInst()->IsPress("Up") == true)
	{
		MoveDir += float4::UP;
	}
	if (GameEngineInput::GetInst()->IsPress("Down") == true)
	{
		MoveDir += float4::DOWN;
	}

	if (MoveDir.CompareInt3D(float4::ZERO) == true)
	{
		return MoveDir;
	}
	else
	{
		MoveDir.y *= 0.5f;
		MoveDir.Normalize();
		return MoveDir;
	}
}

bool Player_Main::IsDirXPositive()
{
	if (GetTransform().GetLocalScale().x > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player_Main::IsPressMoveKey()
{
	if (GetMoveDir().Length() > 0.01f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Player_Main::CalAtt(int _Value)
{
	float Value = static_cast<float>(_Value);
	//크리티컬 확률
	int IsCritical = GameEngineRandom::MainRandom.RandomInt(0, 1);
	CurAttackData_.Font = IsCritical;
	if (IsCritical >= 1)
	{
		Value = Value * 2.f;
	}
	float CalDam = GameEngineRandom::MainRandom.RandomFloat(Value * 0.7f, Value * 1.3f);
	return static_cast<int>(CalDam);
}

float4 Player_Main::UpdateShakeCamera(float _DeltaTime)
{
	if (ShakeDurationTimer_.IsTimerOn() == false)
	{
		ShakeData_ = {};
		return { 0,0,0 };
	}
	else
	{
		ShakeDurationTimer_.Update(_DeltaTime);
		if (ShakeIterTimer_.IsTimerOn() == false)
		{
			ShakeIterTimer_.StartTimer();
			ShakeData_.x = GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f) * ShakeSize_;
			ShakeData_.y = GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f) * ShakeSize_;

			ShakeSize_ = ShakeSize_ * 0.8f;
		}
		ShakeIterTimer_.Update(_DeltaTime);
		return ShakeData_;
	}
	return {};
}

Timer* Player_Main::CreateSkillCoolTime(std::string _Name, float Time_)
{
	Timer* NewCoolTime = new Timer(Time_);
	SkillCoolTime_.insert(std::make_pair(_Name, NewCoolTime));
	return NewCoolTime;
}

void Player_Main::InitSkillCoolTime()
{
	CreateSkillCoolTime("UpperSlash", 2.0f);
	CreateSkillCoolTime("GoreCross", 3.0f);
	CreateSkillCoolTime("HopSmash", 4.0f);
	CreateSkillCoolTime("Frenzy", 5.0f);
	CreateSkillCoolTime("Fury", 43.0f);
}

void Player_Main::CoolTimeUpdate(float _DeltaTime)
{
	if (GodTime_.IsTimerOn() == true)
	{
		GodTime_ -= _DeltaTime;
	}
	for (auto i : SkillCoolTime_)
	{
		Timer* CurTimer = i.second;
		if (CurTimer->IsTimerOn() == true)
		{
			CurTimer->Update(_DeltaTime);
			if (CurTimer->IsTimerOn() == false) // 타이머가 종료되면 딱 한번만 호출
			{
				CurTimer->IsSet = true;
			}
		}
	}
}

void Player_Main::AttackEnd()
{
	AttackCol_->Off();
	CurAttackData_ = {};
	IsAttack_End_ = false;
	IsReadyNextAttack_ = false;
}