#include "PreCompile.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "Player_Main.h"

#include "GoreCross.h"

bool Player_Main::CheckAttackKey()
{
	if (GameEngineInput::GetInst()->IsPress("X") == true)
	{
		IsReadyNextAttack_ = true;
		//�ƿ� �ٸ� ����
		if (CurAttackData_.AttackName != "AutoAttack")
		{
			NextAttackAni_ = PlayerAnimations::AutoAttack;
			return true;
		}
		//���� �����ε� �̹� ����Ƚ���� ���� ����
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
		return CheckCanUsingSkill("UpperSlash", PlayerAnimations::UpperSlash);
	}

	if (GameEngineInput::GetInst()->IsPress("A") == true)
	{
		return CheckCanUsingSkill("GoreCross", PlayerAnimations::GoreCross);
	}

	return false;
}

bool Player_Main::CheckCanUsingSkill(std::string _SkillName, PlayerAnimations _ChangeStateEnum)
{
	//���� ������ ���Է��� ������ �����Ѵ�.
	if (StateManager_.GetCurStateStateName() == _SkillName)
	{
		IsReadyNextAttack_ = false;
		return false;
	}

	//���۽������� ����ؼ� ��Ÿ���� �����ִ� ���¸� �����Ѵ�.
	if (SkillCoolTime_[_SkillName]->IsTimerOn() == true)
	{
		IsReadyNextAttack_ = false;
		return false;
	}

	//���� �������� ����� MP�� ���ٸ� False
	if (CurMP_ < MPConsumption_[_SkillName])
	{
		IsReadyNextAttack_ = false;
		return false;
	}

	IsReadyNextAttack_ = true;
	NextAttackAni_ = _ChangeStateEnum;
	return true;
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

			if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_0_Start + 3)
			{
				SetAttackCol(Value_.AutoAttackPos, Value_.AutoAttackScale);
				//Set Attack
				CurAttackData_.Type = AttackType::Above;
				CurAttackData_.AttackName = "AutoAttack";
				CurAttackData_.Att = CalAtt(Value_.AutoAttackAtt);
				CurAttackData_.XForce = 70.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttEffect = Effect::SlashSHori;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_0_Start + 7)
			{
				AttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_0_End)
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

			if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_1_Start + 3)
			{
				SetAttackCol(Value_.AutoAttackPos, Value_.AutoAttackScale);
				//Set Attack
				CurAttackData_.Att = CalAtt(Value_.AutoAttackAtt);
				CurAttackData_.Type = AttackType::Above;
				CurAttackData_.XForce = 140.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttCount++;
				Force_.ForceX_ = 70.0f;
				CurAttackData_.AttEffect = Effect::SlashSHori;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_1_Start + 7)
			{
				AttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_1_End)
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
				SetAttackCol(Value_.UpperSlashPos, Value_.UpeerSlashScale);
				//Set Attack
				CurAttackData_.Att = CalAtt(Value_.AutoAttackAtt);
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.XForce = 140.0f;
				CurAttackData_.YForce = 300.0f;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttCount++;
				Force_.ForceX_ = 70.0f;
				CurAttackData_.AttEffect = Effect::SlashSRight;
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
			if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_Start + 1)
			{
				SetAttackCol(Value_.UpperSlashPos, Value_.UpeerSlashScale);
				//Set Attack
				CurAttackData_.AttackName = "UpperSlash";
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.Att = CalAtt(Value_.UpperSlashAtt);
				CurAttackData_.AttCount = 0;
				CurAttackData_.XForce = 140.0f;
				CurAttackData_.Stiffness = 0.25f;
				CurAttackData_.RStiffness = 0.21f;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.YForce = 550.0f;
				CurAttackData_.AttCount++;
				CurAttackData_.AttEffect = Effect::SlashSRight;

				//���� ������ ���� ����
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

	//GoreCross_0
	MainRenderer_->AnimationBindFrame("GoreCross_0",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == GoreCross_0_Start + 1)
			{
				SetAttackCol(Value_.GoreCrossSpawnPos, Value_.GoreCrossScale);
				CurAttackData_.AttackName = "GoreCross";
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.Att = CalAtt(Value_.GoreCrossAtt);
				CurAttackData_.AttCount = 0;
				CurAttackData_.XForce = 140.0f;
				CurAttackData_.Stiffness = 0.19f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				//CurAttackData_.YForce = 550.0f;
				CurAttackData_.AttCount++;
				CurAttackData_.Bleeding = 20;
				CurAttackData_.AttEffect = Effect::SlashSHori;

				//���ũ�ν� ���� ����
				GoreCross* New = GetLevel()->CreateActor<GoreCross>();
				float4 SpawnPos = GetTransform().GetWorldPosition();
				float4 MovePos = Value_.GoreCrossSpawnPos;
				MovePos.x = GetDirX().x * MovePos.x;
				New->GetTransform().SetWorldPosition(SpawnPos + MovePos);
				New->GetTransform().SetLocalScale({ GetDirX().x,1,1 });
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == GoreCross_0_End - 4)
			{
				CurAttackData_.Att = CalAtt(Value_.GoreCrossAtt);
				CurAttackData_.AttCount++;
				CurAttackData_.AttEffect = Effect::SlashSRight;
				CurAttackData_.XForce = 70.0f;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == GoreCross_0_End)
			{
				AvatarManager_.ChangeMotion(PlayerAnimations::GoreCross_1);
			}
		});
	//GoreCross_1
	MainRenderer_->AnimationBindFrame("GoreCross_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == GoreCross_1_Start + 1)
			{
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == GoreCross_1_End)
			{
			}
		});
}

void Player_Main::SetAttackCol(const float4& _Pos, const float4& _Scale)
{
	AttackCol_->On();
	AttackCol_->GetTransform().SetLocalScale(_Scale);
	AttackCol_->GetTransform().SetLocalPosition(_Pos);
}