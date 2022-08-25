#include "PreCompile.h"
#include "Player_Main.h"

#include "DNFDefineList.h"
#include "DNFGlobalValue.h"

#include "DNFLevel.h"
#include "DNFBackground.h"
#include "DNFDebugGUI.h"

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
	Value_()
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
}


void Player_Main::InitDefaultValue()
{
	//, 
	Value_.AutoAttackPos = float4(50, 0, -500);
	Value_.AutoAttackScale = float4(120, 55, 1);
	Value_.UpperSlashPos = float4(75, -45, -500);
	Value_.UpeerSlashScale = float4(120,100, 1);

	//���ݷ�
	Value_.UpperSlashAtt = 2;
	Value_.AutoAttackAtt = 1;
}

Player_Main::~Player_Main()
{
}

void Player_Main::Start()
{
	DNFStart();

	InitCol();



	//�ƹ�Ÿ����
	AvatarManager_.LinkPlayerToAvatar(this);
	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);

	//������Ʈ �ʱ�ȭ
	InitState();
	StateManager_.ChangeState("Idle");

	InitAniFunc();


	Force_.FrictionX_ = 700.0f;
	Force_.Gravity_ = 700.0f;
	Force_.SetTransfrom(&GetTransform());

	DNFDebugGUI::AddMutableValue("UpperSlashPos_", &Value_.UpperSlashPos);
	DNFDebugGUI::AddMutableValue("UpeerSlashScale_", &Value_.UpeerSlashScale);
	DNFDebugGUI::AddMutableValue("AutoAttackPos", &Value_.AutoAttackPos);
	DNFDebugGUI::AddMutableValue("AutoAttackScale", &Value_.AutoAttackScale);

}

void Player_Main::Update(float _DeltaTime)
{
	StiffnessUpdate(_DeltaTime);
	if (Stiffness_ > 0)
	{
		return;
	}

	DNFUpdate();
	DNFDebugGUI::AddValue("PlayerState", StateManager_.GetCurStateStateName());
	StateManager_.Update(_DeltaTime);
	//ForceUpdae
	Force_.Update(_DeltaTime);

	//���ѵ� ���� ������ �������� ī�޶�& ĳ����
	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		CheckColMap();
		ChaseCamera();
	}
	ShadowUpdate();

}

void Player_Main::End()
{
}


void Player_Main::ChaseCamera()
{
	//ī�޶� Pos����
	float4 CurPos = GetTransform().GetWorldPosition();
	float4 MapScale = GetDNFLevel()->GetMapScale();
	float Zoom = DNFGlobalValue::CurrentLevel->GetZoom();
	float4 CameraPos;
	CameraPos.z = -500;


	CameraPos.x = GetTransform().GetWorldPosition().x;
	//����
	if (CurPos.x - 640 * Zoom < 0.0f)
	{
		CameraPos.x =  640 * Zoom;
	}
	//������
	if (CurPos.x + 640 * Zoom > MapScale.x)
	{
		CameraPos.x = MapScale.x - 640 * Zoom;
	}

	CameraPos.y = GetTransform().GetWorldPosition().y;
	//�Ʒ�
	if (CurPos.y - 360 * Zoom < -MapScale.y)
	{
		CameraPos.y = -MapScale.y + 360 * Zoom;
	}
	//��
	if (CurPos.y + 360 * Zoom > 0.0f)
	{
		CameraPos.y =  - 360 * Zoom;
	}


	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(CameraPos);
}

void Player_Main::CheckColMap()
{
	float4 MapScale = GetDNFLevel()->GetMapScale();
	float4 PlayerPosBot = GetTransform().GetWorldPosition();
	PlayerPosBot.y = -PlayerPosBot.y - BotPos_.y;

	GameEngineTexture* ColMap = DNFGlobalValue::CurrentLevel->GetBackground()->GetColRenderer()->GetCurTexture();

	//�ȼ��浹������ �Ѿ�� ���� ��ġ�� ������Ų��.
	if (OnAir_ == false)
	{
		if (ColMap->GetPixelToFloat4(static_cast<int>(PlayerPosBot.x), static_cast<int>(PlayerPosBot.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			GetTransform().SetWorldPosition(PrevPos_);
		}
	}
	else
	{
		float4 DownPos = GetTransform().GetWorldPosition();
		DownPos.y = -GroundYPos_ - BotPos_.y;
		if (ColMap->GetPixelToFloat4(static_cast<int>(PlayerPosBot.x), static_cast<int>(DownPos.y)).CompareInt3D(float4::MAGENTA) == false)
		{
			GetTransform().SetWorldPosition(PrevPos_);
		}
	}
	

	//������ġ�� ���̰� ������ PrevPos�� �����Ѵ�.
	if (DNFMath::Length(PrevPos_, GetTransform().GetWorldPosition()) >= 0.5f)
	{
		PrevPos_ = GetTransform().GetWorldPosition();
	}

}

void Player_Main::InitCol()
{
	//�׽�Ʈ�� �ݶ��̴�
	GameEngineCollision* Col = CreateComponent<GameEngineCollision>("Col");
	Col->SetDebugSetting(CollisionType::CT_OBB2D, float4(0, 1.0f, 0, 0.5f));
	Col->GetTransform().SetLocalScale(float4(100, 100, 1));
	Col->GetTransform().SetLocalMove(float4(0, 0, -500));
	Col->ChangeOrder(ColOrder::Player);

	//Attack �ݶ��̴�
	AttackCol_ = CreateComponent<GameEngineCollision>("Attack");
	AttackCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4(0, 1.0f, 0, 0.5f));
	AttackCol_->ChangeOrder(ColOrder::PlayerAttack);
	AttackCol_->Off();


}

void Player_Main::InitState()
{
	//������Ʈ �ʱ�ȭ
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
	return _Value;
}


