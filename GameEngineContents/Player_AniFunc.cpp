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
			if (_Desc.Frames[_Desc.CurFrame] == AutoAttack_0_Start + 3)
			{
				MiddleAttackCol_->On();
				MiddleAttackCol_->GetTransform().SetLocalScale(float4(120, 70, 1));
				MiddleAttackCol_->GetTransform().SetLocalPosition(float4(50, -20, -500));
				AttackCount_++;
			}
			else if (_Desc.Frames[_Desc.CurFrame] == AutoAttack_0_Start + 7)
			{
				MiddleAttackCol_->Off();
				AttackCount_ = 0;
			}
			else if (_Desc.Frames[_Desc.CurFrame] == AutoAttack_0_End)
			{
				IsAutoAttack_0_End_ = true;
			}
		});
}
