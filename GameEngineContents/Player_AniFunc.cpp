#include "PreCompile.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "Player_Main.h"

bool Player_Main::CheckAttackKey()
{
	if (GameEngineInput::GetInst()->IsPress("X") == true)
	{
		IsReadyNextAttack_ = true;
		//아예 다른 공격
		if (CurAttackData_.AttackName != "AutoAttack")
		{
			NextAttackAni_ = PlayerAnimations::AutoAttack;
			return true;
		}
		//같은 공격인데 이미 공격횟수를 전부 했음
		if (CurAttackData_.AttCount >= 3)
		{
			IsReadyNextAttack_ = false;
			return false;
		}
		switch (CurAttackData_.AttCount)
		{
		case 1:
			NextAttackAni_ = PlayerAnimations::AutoAttack_1;
			break;
		case 2:
			NextAttackAni_ = PlayerAnimations::AutoAttack_2;
			break;
		default:
			break;
		}
		return true;
	}

	if (GameEngineInput::GetInst()->IsPress("Z") == true)
	{
		if (CurAttackData_.AttackName == "UpperSlash")
		{
			IsReadyNextAttack_ = false;
			return false;
		}
		IsReadyNextAttack_ = true;
		NextAttackAni_ = PlayerAnimations::UpperSlash;
		return true;
	}
}

void Player_Main::InitAniFunc()
{
	//AutoAttack_0
	MainRenderer_->AnimationBindFrame("AutoAttack_0",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] >= AutoAttack_0_Start + 3)
			{
				CheckAttackKey();
			}

			if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_0_Start + 3)
			{
				AttackCol_->On();
				AttackCol_->GetTransform().SetLocalScale(float4(120, 70, 1));
				AttackCol_->GetTransform().SetLocalPosition(float4(50, -20, -500));
				CurAttackData_.AttackName = "AutoAttack";
				CurAttackData_.XForce = 70.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;

			}
			else if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_0_Start + 7)
			{
				AttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_0_End)
			{
				IsAttack_End_ = true;
			}
		});

	//AutoAttack_1
	MainRenderer_->AnimationBindFrame("AutoAttack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] >= AutoAttack_1_Start + 3)
			{
				CheckAttackKey();
			}

			if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_1_Start + 3)
			{
				AttackCol_->On();
				AttackCol_->GetTransform().SetLocalScale(float4(120, 70, 1));
				AttackCol_->GetTransform().SetLocalPosition(float4(50, -20, -500));
				CurAttackData_.XForce = 140.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttCount++;
				Force_.ForceX_ = 70.0f;
			}
			else if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_1_Start + 7)
			{
				AttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_1_End)
			{				
				IsAttack_End_ = true;
			}
		});

	//AutoAttack_2
	MainRenderer_->AnimationBindFrame("AutoAttack_2",
		[&](const FrameAnimation_DESC& _Desc)
		{

			if (_Desc.Frames[_Desc.CurFrame - 1] >= AutoAttack_2_Start + 3)
			{
				CheckAttackKey();
			}
			if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_Start + 3)
			{
				AttackCol_->On();
				AttackCol_->GetTransform().SetLocalScale(float4(120, 70, 1));
				AttackCol_->GetTransform().SetLocalPosition(float4(50, -20, -500));
				CurAttackData_.XForce = 140.0f;
				CurAttackData_.YForce = 400.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttCount++;
				Force_.ForceX_ = 70.0f;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_Start + 7)
			{
				AttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_End)
			{
				IsAttack_End_ = true;
			}
		});

	//Jump
	MainRenderer_->AnimationBindFrame("Jump_Start",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (Force_.ForceY_ < 0.0f)
			{
				AvatarManager_.ChangeMotion(PlayerAnimations::Jump_End);
			}
		});

	//UpperSlash
	MainRenderer_->AnimationBindFrame("UpperSlash",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_Start + 3)
			{
				AttackCol_->On();
				AttackCol_->GetTransform().SetLocalScale(float4(120, 70, 1));
				AttackCol_->GetTransform().SetLocalPosition(float4(50, -20, -500));
				CurAttackData_.AttackName = "UpperSlash";
				CurAttackData_.AttCount = 0;
				CurAttackData_.XForce = 140.0f;
				CurAttackData_.Stiffness = 1.15f;
				CurAttackData_.RStiffness = 1.0f;
				CurAttackData_.YForce = 550.0f;
				CurAttackData_.AttCount++;
				Force_.ForceX_ = 70.0f;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_Start + 7)
			{
				AttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_End)
			{
				IsReadyNextAttack_ = false;
				IsAttack_End_ = true;
			}
		});
}


