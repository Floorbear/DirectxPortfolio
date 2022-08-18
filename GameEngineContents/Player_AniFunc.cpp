#include "PreCompile.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "Player_Main.h"

void Player_Main::InitAniFunc()
{
	//AutoAttack_0
	MainRenderer_->AnimationBindFrame("AutoAttack_0",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] >= AutoAttack_0_Start + 3)
			{
				if (GameEngineInput::GetInst()->IsPress("X") == true)
				{
					IsReadyNextAttack_ = true;
					NextAutoAttackAni_ = PlayerAnimations::AutoAttack_1;
				}
			}
			

			if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_0_Start + 3)
			{
				MiddleAttackCol_->On();
				MiddleAttackCol_->GetTransform().SetLocalScale(float4(120, 70, 1));
				MiddleAttackCol_->GetTransform().SetLocalPosition(float4(50, -20, -500));
				AttackCount_++;
			}
			else if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_0_Start + 7)
			{
				MiddleAttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_0_End)
			{
				IsAutoAttack_End_ = true;
			}
		});

	//AutoAttack_1
	MainRenderer_->AnimationBindFrame("AutoAttack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] >= AutoAttack_1_Start + 3)
			{
				if (GameEngineInput::GetInst()->IsPress("X") == true)
				{
					IsReadyNextAttack_ = true;
					NextAutoAttackAni_ = PlayerAnimations::AutoAttack_2;
				}
			}

			if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_1_Start + 3)
			{
				MiddleAttackCol_->On();
				MiddleAttackCol_->GetTransform().SetLocalScale(float4(120, 70, 1));
				MiddleAttackCol_->GetTransform().SetLocalPosition(float4(50, -20, -500));
				AttackCount_++;
				//AddForce
				Force_.ForceX_ = 200.0f;
			}
			else if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_1_Start + 7)
			{
				MiddleAttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame-1] == AutoAttack_1_End)
			{				
				IsAutoAttack_End_ = true;
			}
		});

	//AutoAttack_2
	MainRenderer_->AnimationBindFrame("AutoAttack_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_Start + 3)
			{
				MiddleAttackCol_->On();
				MiddleAttackCol_->GetTransform().SetLocalScale(float4(120, 70, 1));
				MiddleAttackCol_->GetTransform().SetLocalPosition(float4(50, -20, -500));
				AttackCount_++;
				//AddForce
				Force_.ForceX_ = 200.0f;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_Start + 7)
			{
				MiddleAttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_End)
			{
				IsReadyNextAttack_ = false;
				IsAutoAttack_End_ = true;
			}
		});
}
