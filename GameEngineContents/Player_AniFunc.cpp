#include "PreCompile.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "Player_Main.h"

#include "GoreCross.h"

bool Player_Main::CheckAttackKey()
{
	//��Ÿ
	if (GameEngineInput::GetInst()->IsPress("X") == true)
	{
		IsReadyNextAttack_ = true;
		if (IsFrenzy_ == false)
		{
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
		else
		{
			//�ƿ� �ٸ� ����
			if (CurAttackData_.AttackName != "Frenzy_AutoAttack")
			{
				NextAttackAni_ = PlayerAnimations::AutoAttack; //�ϴܿ�������� �ؼ� AutoAttack State�� �����Ѵ�.
				return true;
			}
			//���� �����ε� �̹� ����Ƚ���� ���� ����
			if (CurAttackData_.AttCount >= 8)
			{
				IsReadyNextAttack_ = false;
				return false;
			}
			switch (CurAttackData_.AttCount)
			{
			case 1:
				NextAttackAni_ = PlayerAnimations::Frenzy_AutoAttack_1;
				break;
			case 2:
				NextAttackAni_ = PlayerAnimations::Frenzy_AutoAttack_1;
				break;
			case 3:
				NextAttackAni_ = PlayerAnimations::Frenzy_AutoAttack_2;
				break;
			case 4:
				NextAttackAni_ = PlayerAnimations::Frenzy_AutoAttack_2;
				break;
			case 5:
				NextAttackAni_ = PlayerAnimations::Frenzy_AutoAttack_3;
				break;
			case 6:
				NextAttackAni_ = PlayerAnimations::Frenzy_AutoAttack_3;
				break;
			default:
				break;
			}
			return true;
		}
	}

	if (GameEngineInput::GetInst()->IsPress("Z") == true)
	{
		return CheckCanUsingSkill("UpperSlash", PlayerAnimations::UpperSlash);
	}

	if (GameEngineInput::GetInst()->IsPress("A") == true)
	{
		return CheckCanUsingSkill("GoreCross", PlayerAnimations::GoreCross);
	}

	if (GameEngineInput::GetInst()->IsPress("S") == true)
	{
		return CheckCanUsingSkill("HopSmash", PlayerAnimations::HopSmash);
	}

	if (GameEngineInput::GetInst()->IsPress("F") == true)
	{
		return CheckCanUsingSkill("Frenzy", PlayerAnimations::Frenzy);
	}

	if (GameEngineInput::GetInst()->IsPress("E") == true)
	{
		return CheckCanUsingSkill("Fury", PlayerAnimations::Fury);
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

	//�ش� ��ų�� ����ؼ� ��Ÿ���� �����ִ� ���¸� �����Ѵ�.
	if (SkillCoolTime_[_SkillName]->IsTimerOn() == true)
	{
		IsReadyNextAttack_ = false;
		return false;
	}

	//�ش� ��ų�� ����� MP�� ���ٸ� False
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
	//������
	MainRenderer_->AnimationBindEnd("Frenzy",
		[&](const FrameAnimation_DESC& _Desc)
		{
			IsFrenzy_ = true;
		});
	//����
	MainRenderer_->AnimationBindFrame("Fury",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 1)
			{
				ShakeCamera(12.5f, 0.55f);
				StartSuperArmor(8.0f);
			}
		});
	MainRenderer_->AnimationBindEnd("Fury",
		[&](const FrameAnimation_DESC& _Desc)
		{
			StateManager_.ChangeState("Idle");
		});

	AutoAttackAniFunc();

	Frenzy_AutoAttackAniFunc();

	UpperSlashAniFunc();

	GoreCrossAniFun();

	HopSmashAniFunc();
}

void Player_Main::Frenzy_AutoAttackAniFunc()
{
	//AutoAttack_0
	MainRenderer_->AnimationBindFrame("Frenzy_AutoAttack_0",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] >= Frenzy_AutoAttack_0_Start + 1)
			{
				CheckAttackKey();
			}

			if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_0_Start + 2)
			{
				SetAttackCol(Value_.AutoAttackPos, Value_.AutoAttackScale);
				//Set Attack
				CurAttackData_.Type = AttackType::Above;
				CurAttackData_.AttackName = "Frenzy_AutoAttack";
				CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
				CurAttackData_.XForce = FrenzyXForce;
				CurAttackData_.Stiffness = FrenzyStif;
				CurAttackData_.RStiffness = FrenzyRStif;
				CurAttackData_.Bleeding = 17;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_0_End - 1)
			{
				CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
				CurAttackData_.AttCount++;
				CurAttackData_.AttEffect = Effect::SlashSLeft;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_0_End)
			{
				AttackCol_->Off();
				IsAttack_End_ = true;
			}
		});

	//AutoAttack_1
	MainRenderer_->AnimationBindFrame("Frenzy_AutoAttack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] >= Frenzy_AutoAttack_1_Start + 1)
			{
				CheckAttackKey();
			}

			if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_1_Start + 2)
			{
				SetAttackCol(Value_.AutoAttackPos, Value_.AutoAttackScale);
				//Set Attack
				CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
				CurAttackData_.Type = AttackType::Above;
				CurAttackData_.AttackName = "Frenzy_AutoAttack";
				CurAttackData_.XForce = FrenzyXForce;
				CurAttackData_.Stiffness = FrenzyStif;
				CurAttackData_.Bleeding = 17;

				CurAttackData_.RStiffness = FrenzyRStif;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttCount++;
				Force_.ForceX_ = 70.0f;
				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_1_End - 1)
			{
				CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
				CurAttackData_.AttCount++;
				CurAttackData_.AttEffect = Effect::SlashSHori;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_1_End)
			{
				AttackCol_->Off();
				IsAttack_End_ = true;
			}
		});

	//AutoAttack_2
	MainRenderer_->AnimationBindFrame("Frenzy_AutoAttack_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] >= Frenzy_AutoAttack_2_Start + 1)
			{
				CheckAttackKey();
			}

			if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_2_Start + 2)
			{
				SetAttackCol(Value_.UpperSlashPos, Value_.UpeerSlashScale);
				//Set Attack
				CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "Frenzy_AutoAttack";
				CurAttackData_.XForce = FrenzyXForce;
				CurAttackData_.Stiffness = FrenzyStif;
				CurAttackData_.Bleeding = 17;

				CurAttackData_.YForce = 240.0f;

				CurAttackData_.RStiffness = FrenzyRStif;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttCount++;
				Force_.ForceX_ = 70.0f;
				CurAttackData_.AttEffect = Effect::SlashSLeft;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_2_End - 1)
			{
				CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
				CurAttackData_.AttCount++;
				CurAttackData_.AttEffect = Effect::SlashSHori;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_2_End)
			{
				AttackCol_->Off();
				IsAttack_End_ = true;
			}
		});

	//AutoAttack_3
	MainRenderer_->AnimationBindFrame("Frenzy_AutoAttack_3",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] >= Frenzy_AutoAttack_3_Start + 1)
			{
				CheckAttackKey();
			}
			if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_3_Start + 2)
			{
				SetAttackCol(Value_.UpperSlashPos, Value_.UpeerSlashScale);
				//Set Attack
				CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "Frenzy_AutoAttack";
				CurAttackData_.XForce = FrenzyXForce;
				CurAttackData_.Stiffness = FrenzyStif;
				CurAttackData_.Bleeding = 17;

				CurAttackData_.RStiffness = FrenzyRStif;
				CurAttackData_.YForce = 100.0f;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttCount++;
				Force_.ForceX_ = 70.0f;
				CurAttackData_.AttEffect = Effect::SlashSHori;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_3_End - 1)
			{
				CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
				CurAttackData_.AttCount++;
				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_3_End)
			{
				AttackCol_->Off();
				IsAttack_End_ = true;
			}
		});
}

void Player_Main::AutoAttackAniFunc()
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
}

void Player_Main::HopSmashAniFunc()
{
	//HopSmash_0
	MainRenderer_->AnimationBindFrame("HopSmash_0",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (Force_.ForceY_ < 120.f)
			{
				Force_.ForceY_ -= 150.f;//200
				StartSuperArmor(0.43f);
				AvatarManager_.ChangeMotion(PlayerAnimations::HopSmash_1);
			}
		});
	//HopSmash_1
	MainRenderer_->AnimationBindFrame("HopSmash_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == _Desc.Frames.size() - 1)
			{
				AvatarManager_.ChangeMotion(PlayerAnimations::HopSmash_2);
			}
		});
	//HopSmash_2
	MainRenderer_->AnimationBindFrame("HopSmash_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 1)//ù��° ������
			{
				SetAttackCol(Value_.UpperSlashPos, Value_.UpeerSlashScale);
				//Set Attack
				CurAttackData_.AttackName = "HopSmash";
				CurAttackData_.Att = CalAtt(Value_.AutoAttackAtt);
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.XForce = 50.0f;
				CurAttackData_.ZPos = static_cast<int>(GetBotPos().y);
				CurAttackData_.Stiffness = 0.07f;
				CurAttackData_.RStiffness = 0.04f;
				CurAttackData_.AttCount++;
				Force_.ForceX_ = 70.0f;
				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			if (_Desc.CurFrame == 3)//������ ������
			{
				CurAttackData_.AttCount++;
				CurAttackData_.AttEffect = Effect::SlashSHori;
				ShakeCamera(7.5f, 0.45f);
			}
		});
}

void Player_Main::UpperSlashAniFunc()
{
	//UpperSlash
	MainRenderer_->AnimationBindFrame("UpperSlash",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_Start)
			{
				//���۾Ƹ� set
				StartSuperArmor(0.29f);
			}
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
}

void Player_Main::GoreCrossAniFun()
{
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