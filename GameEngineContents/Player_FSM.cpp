#include "PreCompile.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "Player_Main.h"
#include "HopSmash.h"

void Player_Main::IdleStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	PrevHitData_ = {};
}

void Player_Main::IdleUpdate(float _DeltaTime, const StateInfo _Info)
{
	//����Ű ������ ���� �Ǹ�
	if (IsPressMoveKey() == true)
	{
		StateManager_.ChangeState("Move");
		return;
	}
	if (CheckAttackKey() == true)
	{
		StateManager_.ChangeState(AvatarManager_.EnumToString(NextAttackAni_));
		return;
	}

	if (GameEngineInput::GetInst()->IsDown("C") == true)
	{
		StateManager_.ChangeState("Jump");
		return;
	}
}

void Player_Main::MoveStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Move);
}

void Player_Main::MoveUpdate(float _DeltaTime, const StateInfo _Info)
{
	if (IsPressMoveKey() == false)
	{
		StateManager_.ChangeState("Idle");
		return;
	}

	//���� State ����
	if (CheckAttackKey() == true)
	{
		StateManager_.ChangeState(AvatarManager_.EnumToString(NextAttackAni_));
		return;
	}

	if (GameEngineInput::GetInst()->IsDown("C") == true)
	{
		StateManager_.ChangeState("Jump");
		return;
	}

	FlipX(GetMoveDir());
	GetTransform().SetLocalMove(GetMoveDir() * _DeltaTime * 200.0f);
	ShadowUpdate();
}

void Player_Main::JumpStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Jump_Start);
	Force_.ForceY_ = 400.0f;
	Force_.OnGravity();
	GroundYPos_ = GetTransform().GetWorldPosition().y;
	OnAir_ = true;

	//�켱 1������ ���� ������ > ���� ���� �ߵ����� �ʰ� �ϱ� ����
	Force_.Update(GameEngineTime::GetInst()->GetDeltaTime());
}

void Player_Main::JumpUpdate(float _DeltaTime, const StateInfo _Info)
{
	if (GetTransform().GetWorldPosition().y <= GroundYPos_)
	{
		StateManager_.ChangeState("Idle");
	}

	//������ �̵�
	FlipX(GetMoveDir());
	if (CanMove(float4(GetMoveDir().x, 0, 0) * _DeltaTime * 200.0f) == true)
	{
		GetTransform().SetLocalMove(float4(GetMoveDir().x, 0, 0) * _DeltaTime * 200.0f);
	}
}

void Player_Main::JumpEnd(const StateInfo _Info)
{
	JumpLogicEnd();
}

void Player_Main::JumpLogicEnd()
{
	Force_.OffGravity();
	float4 PlayerPos = GetTransform().GetWorldPosition();
	PlayerPos.y = GroundYPos_;
	GetTransform().SetWorldPosition(PlayerPos);
	OnAir_ = false;
}

void Player_Main::AirborneStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Hit);
	ResetDNFAnimation();
	//ChangeHitColTrans("Hit");
	//�÷��̾ ���ֺ��� �������� Flip
	//FlipX(-Player_->GetDirX());
	Force_.ForceX_ += -PrevHitData_.XForce;

	GetTransform().SetLocalMove(float4(0, Force_.ForceY_ * GameEngineTime::GetDeltaTime()));
	Force_.OnGravity();
	OnAir_ = true;
}

void Player_Main::AirborneUpdate(float _DeltaTime, const StateInfo _Info)
{
	//����
	//�߶�
	AirborneTime_ += _DeltaTime;
	float CurYPos = GetTransform().GetWorldPosition().y;

	if (CurYPos <= GroundYPos_)
	{
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		ShadowUpdate();
		//Down ���� Bounce
		OnAir_ = true;
		Force_.ForceY_ = 200.0f;
		Force_.ForceX_ += -140.0f;
		AirborneTime_ = 0.0f;
		Force_.OnGravity();
		PrevHitData_ = {};
		GodTime_.StartTimer(Value_.Down_God_Time);
		StateManager_.ChangeState("Down");
		return;
	}
}

void Player_Main::DownStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Down);
	//ChangeHitColTrans("Down");
	Down_Timer_.StartTimer(Value_.Down_Time);
	Force_.ForceX_ += -PrevHitData_.XForce;

	GetTransform().SetLocalMove(float4(0, Force_.ForceY_ * GameEngineTime::GetDeltaTime()));
}

void Player_Main::DownUpdate(float _DeltaTime, const StateInfo _Info)
{
	AirborneTime_ += 5.0f * _DeltaTime;
	float CurYPos = GetTransform().GetWorldPosition().y;

	//����˻�
	//if (CurHP_ == 0)
	//{
	//	//StateManager_.ChangeState("Die");
	//	return;
	//}

	if (CurYPos <= GroundYPos_)
	{
		//GroundYPos �Ʒ��� �������� �ʰ� ������Ű��
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		ShadowUpdate();
		Down_Timer_ -= _DeltaTime * (1.f + AirborneTime_ * 0.1f);
		OnAir_ = false;
		Force_.OffGravity();

		//���˻�
		if (Down_Timer_.IsTimerOn() == false)
		{
			OnAir_ = false;
			Force_.ForceY_ = 0.0f;
			AirborneTime_ = 0.0f;
			Force_.OffGravity();
			GodTime_.StartTimer(Value_.Down_God_Time);
			PrevHitData_ = {};
			StateManager_.ChangeState("Idle");
			return;
		}
	}
}

void Player_Main::AutoAttackStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::AutoAttack_0);
}

void Player_Main::AutoAttackUpdate(float _DeltaTime, const StateInfo _Info)
{
	//��ҿ��� False
	if (IsAttack_End_ == true)
	{
		if (IsReadyNextAttack_ == true)
		{
			if (NextAttackAni_ == PlayerAnimations::AutoAttack_1 || NextAttackAni_ == PlayerAnimations::AutoAttack_2)
			{
				AvatarManager_.ChangeMotion(NextAttackAni_);
				IsAttack_End_ = false;
				IsReadyNextAttack_ = false;
				return;
			}
			StateManager_.ChangeState(AvatarManager_.EnumToString(NextAttackAni_));
			return;
		}

		if (IsPressMoveKey() == false)
		{
			StateManager_.ChangeState("Idle");
			return;
		}
		else
		{
			StateManager_.ChangeState("Move");
			return;
		}
	}
}

void Player_Main::AutoAttackEnd(const StateInfo _Info)
{
	AttackEnd();
}

void Player_Main::UpperSlashStart(const StateInfo _Info)
{
	IsAttack_End_ = false;
	AvatarManager_.ChangeMotion(PlayerAnimations::UpperSlash);
	//CoolTime Set
	SkillCoolTime_["UpperSlash"]->StartTimer();

	//���� �Ҹ�
	CurMP_ -= Value_.UpperSlash_MP;
}

void Player_Main::UpperSlashUpdate(float _DeltaTime, const StateInfo _Info)
{
	//��ҿ��� False
	if (IsAttack_End_ == true)
	{
		if (CheckAttackKey() == true)
		{
			IsAttack_End_ = false;
			IsReadyNextAttack_ = false;
			StateManager_.ChangeState(AvatarManager_.EnumToString(NextAttackAni_));
			return;
		}

		if (IsPressMoveKey() == false)
		{
			StateManager_.ChangeState("Idle");
			return;
		}
		else
		{
			StateManager_.ChangeState("Move");
			return;
		}
	}
}

void Player_Main::UpperSlashEnd(const StateInfo _Info)
{
	AttackEnd();
}

void Player_Main::HopSmashStart(const StateInfo _Info)
{
	IsAttack_End_ = false;
	SkillCoolTime_["HopSmash"]->StartTimer();
	CurMP_ -= Value_.HopSmash_MP;

	AvatarManager_.ChangeMotion(PlayerAnimations::HopSmash_0);

	Force_.ForceX_ = 300.f; //350.0f
	Force_.ForceY_ = 300.f; //390.0f
	Force_.OnGravity();
	GroundYPos_ = GetTransform().GetWorldPosition().y;
	OnAir_ = true;

	//�켱 1������ ���� ������ > ���� ���� �ߵ����� �ʰ� �ϱ� ����
	Force_.Update(GameEngineTime::GetInst()->GetDeltaTime());
}

void Player_Main::HopSmashUpdate(float _DeltaTime, const StateInfo _Info)
{
	if (GetTransform().GetWorldPosition().y <= GroundYPos_ && StateManager_.GetCurStateTime() >= 0.12f && IsAttack_End_ == false)
	{
		HopSmash* New = GetLevel()->CreateActor<HopSmash>();
		float4 SpawnPos = GetTransform().GetWorldPosition();
		float4 MovePos = { 60,-60 };
		MovePos.x = GetDirX().x * MovePos.x;
		New->GetTransform().SetWorldPosition(SpawnPos + MovePos);
		New->GetTransform().SetLocalScale({ GetDirX().x,1,1 });

		CurAttackData_.AttCount++;
		CurAttackData_.AttEffect = Effect::SlashSRight;
		CurAttackData_.Stiffness = 0.32f;
		CurAttackData_.RStiffness = 0.31f;
		CurAttackData_.YForce = 350.0f;
		CurAttackData_.Bleeding = 85;
		CurAttackData_.ZPos = 0;
		ShakeCamera(7.5f, 0.30f);
		IsReadyNextAttack_ = false;
		IsAttack_End_ = true;
		JumpLogicEnd();
		return;
	}
	//��ҿ��� False
	if (IsAttack_End_ == true)
	{
		if (CheckAttackKey() == true)
		{
			IsAttack_End_ = false;
			IsReadyNextAttack_ = false;
			StateManager_.ChangeState(AvatarManager_.EnumToString(NextAttackAni_));
			return;
		}

		if (IsPressMoveKey() == false)
		{
			StateManager_.ChangeState("Idle");
			return;
		}
		else
		{
			StateManager_.ChangeState("Move");
			return;
		}
	}
}

void Player_Main::HopSmashEnd(const StateInfo _Info)
{
	Force_.FrictionX_ = Value_.DefaultFriction;
	Force_.Gravity_ = Value_.DefaultGravity;
	AttackEnd();
	JumpLogicEnd();
}

void Player_Main::GoreCrossStart(const StateInfo _Info)
{
	IsAttack_End_ = false;
	AvatarManager_.ChangeMotion(PlayerAnimations::GoreCross_0);
	SkillCoolTime_["GoreCross"]->StartTimer();
	CurMP_ -= Value_.GoreCross_MP;
}

void Player_Main::GoreCrossUpdate(float _DeltaTime, const StateInfo _Info)
{
	//��ҿ��� False
	if (IsAttack_End_ == true)
	{
		if (CheckAttackKey() == true)
		{
			IsAttack_End_ = false;
			IsReadyNextAttack_ = false;
			StateManager_.ChangeState(AvatarManager_.EnumToString(NextAttackAni_));
			return;
		}

		if (IsPressMoveKey() == false)
		{
			StateManager_.ChangeState("Idle");
			return;
		}
		else
		{
			StateManager_.ChangeState("Move");
			return;
		}
	}
}

void Player_Main::GoreCrossEnd(const StateInfo _Info)
{
	AttackEnd();
}

void Player_Main::HitStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Hit);
	ResetDNFAnimation();
	//ChangeHitColTrans("Hit");
	Hit_Timer_ = 0.65f;
	Hit_Timer_.StartTimer();

	//�÷��̾ ���ֺ��� �������� Flip
	//FlipX(-Player_->GetDirX());
	Force_.ForceX_ += -PrevHitData_.XForce;
}

void Player_Main::HitUpdate(float _DeltaTime, const StateInfo _Info)
{
	//����˻�
	//if (CurHP_ == 0)
	//{
	//	StateManager_.ChangeState("Die");
	//	return;
	//}
	if (Hit_Timer_.IsTimerOn() == true)
	{
		Hit_Timer_ -= _DeltaTime;
	}
	else
	{
		StateManager_.ChangeState("Idle");
		PrevHitData_ = {};
		return;
	}
}