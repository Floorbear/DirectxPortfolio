#include "PreCompile.h"

#include "DNFContentsMinimal.h"
#include "Player_Main.h"

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
	DNFDebugGUI::AddValue("MoveDir", MoveDir);

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

void Player_Main::IdleStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
}

void Player_Main::IdleUpdate(float _DeltaTime, const StateInfo _Info)
{
	//방향키 조작이 감지 되면
	if (GetMoveDir().Length() > 0.0f)
	{
		StateManager_.ChangeState("Move");
		return;
	}
}

void Player_Main::MoveStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Move);
}

void Player_Main::MoveUpdate(float _DeltaTime, const StateInfo _Info)
{
	float4 MoveDir = GetMoveDir();

	if (MoveDir.Length() < 0.01f)
	{
		StateManager_.ChangeState("Idle");
		return;
	}

	if (MoveDir.x > 0.0f)
	{
		GetTransform().PixLocalPositiveX();
	}
	else
	{
		GetTransform().PixLocalNegativeX();
	}
	GetTransform().SetLocalMove(MoveDir * _DeltaTime * FloatValue_["MoveSpeed"]);
	ShadowUpdate();

}
