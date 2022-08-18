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
	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		StateManager_.ChangeState("AutoAttack");
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
	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		StateManager_.ChangeState("AutoAttack");
		return;
	}

	FlipX(GetMoveDir());
	GetTransform().SetLocalMove(GetMoveDir() * _DeltaTime * 200.0f);
	ShadowUpdate();
}

void Player_Main::AutoAttackStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::AutoAttack_0);
}

void Player_Main::AutoAttackUpdate(float _DeltaTime, const StateInfo _Info)
{


	//평소에는 False
	if (IsAutoAttack_End_ == true)
	{
		if (IsReadyNextAttack_ == true)
		{
			AvatarManager_.ChangeMotion(NextAutoAttackAni_);
			IsAutoAttack_End_ = false;
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

void Player_Main::AutoAttackEnd(const StateInfo _Info)
{
	MiddleAttackCol_->Off();
	AttackCount_ = 0;
	IsAutoAttack_End_ = false;
}
