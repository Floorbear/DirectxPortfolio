#include "PreCompile.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "Player_Main.h"



void Player_Main::IdleStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
}

void Player_Main::IdleUpdate(float _DeltaTime, const StateInfo _Info)
{
	//방향키 조작이 감지 되면
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

	//공격 State 전이
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

	//우선 1프레임 위로 보낸다 > 착지 로직 발동하지 않게 하기 위에
	Force_.Update(GameEngineTime::GetInst()->GetDeltaTime());
}

void Player_Main::JumpUpdate(float _DeltaTime, const StateInfo _Info)
{
	if (GetTransform().GetWorldPosition().y <= GroundYPos_)
	{
		StateManager_.ChangeState("Idle");
	}

	//점프중 이동
	FlipX(GetMoveDir());
	if (CanMove(float4(GetMoveDir().x, 0, 0) * _DeltaTime * 200.0f) == true)
	{
		GetTransform().SetLocalMove(float4(GetMoveDir().x, 0, 0) * _DeltaTime * 200.0f);
	}
}

void Player_Main::JumpEnd(const StateInfo _Info)
{
	Force_.OffGravity();
	float4 PlayerPos = GetTransform().GetWorldPosition();
	PlayerPos.y = GroundYPos_;
	GetTransform().SetWorldPosition(PlayerPos);
	OnAir_ = false;
}

void Player_Main::AutoAttackStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::AutoAttack_0);
}

void Player_Main::AutoAttackUpdate(float _DeltaTime, const StateInfo _Info)
{
	//평소에는 False
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
	AttackCol_->Off();
	CurAttackData_ = {};
	IsAttack_End_ = false;
	IsReadyNextAttack_ = false;
	Force_.ForceX_ = 0;
}

void Player_Main::UpperSlashStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::UpperSlash);
}

void Player_Main::UpperSlashUpdate(float _DeltaTime, const StateInfo _Info)
{
	//평소에는 False
	if (IsAttack_End_ == true)
	{
		if (IsReadyNextAttack_ == true)
		{
			AvatarManager_.ChangeMotion(NextAttackAni_);
			IsAttack_End_ = false;
			IsReadyNextAttack_ = false;
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
	AttackCol_->Off();
	AttackCount_ = 0;
	IsAttack_End_ = false;
	Force_.ForceX_ = 0;
	CurAttackData_ = {};
}

