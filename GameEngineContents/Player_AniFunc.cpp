#include "PreCompile.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "Player_Main.h"
#include "ExtremOverkill.h"
#include "GoreCross.h"

bool Player_Main::CheckAttackKey()
{
	//평타
	if (GameEngineInput::GetInst()->IsPress("X") == true)
	{
		IsReadyNextAttack_ = true;
		if (IsFrenzy_ == false)
		{
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
		else
		{
			//아예 다른 공격
			if (CurAttackData_.AttackName != "Frenzy_AutoAttack")
			{
				NextAttackAni_ = PlayerAnimations::AutoAttack; //일단오토어택을 해서 AutoAttack State로 전이한다.
				return true;
			}
			//같은 공격인데 이미 공격횟수를 전부 했음
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

	if (GameEngineInput::GetInst()->IsDown("Z") == true)
	{
		return CheckCanUsingSkill("UpperSlash", PlayerAnimations::UpperSlash);
	}

	if (GameEngineInput::GetInst()->IsDown("A") == true)
	{
		return CheckCanUsingSkill("GoreCross", PlayerAnimations::GoreCross);
	}

	if (GameEngineInput::GetInst()->IsDown("S") == true)
	{
		return CheckCanUsingSkill("HopSmash", PlayerAnimations::HopSmash);
	}
	if (GameEngineInput::GetInst()->IsDown("D") == true)
	{
		return CheckCanUsingSkill("TripleSlash", PlayerAnimations::TripleSlash);
	}
	if (GameEngineInput::GetInst()->IsDown("F") == true)
	{
		return CheckCanUsingSkill("Frenzy", PlayerAnimations::Frenzy);
	}

	if (GameEngineInput::GetInst()->IsDown("E") == true)
	{
		return CheckCanUsingSkill("Fury", PlayerAnimations::Fury);
	}

	if (GameEngineInput::GetInst()->IsDown("R") == true)
	{
		return CheckCanUsingSkill("ExtremOverkill", PlayerAnimations::ExtremOverkill);
	}

	if (GameEngineInput::GetInst()->IsDown("W") == true)
	{
		return CheckCanUsingSkill("Outragebreak", PlayerAnimations::Outragebreak);
	}

	return false;
}

bool Player_Main::CheckCanUsingSkill(std::string _SkillName, PlayerAnimations _ChangeStateEnum)
{
	//같은 공격의 선입력을 받으면 무시한다.
	if (StateManager_.GetCurStateStateName() == _SkillName)
	{
		IsReadyNextAttack_ = false;
		return false;
	}

	//해당 스킬을 사용해서 쿨타임이 돌고있는 상태면 무시한다.
	if (SkillCoolTime_[_SkillName]->IsTimerOn() == true)
	{
		IsReadyNextAttack_ = false;
		GameEngineSound::SoundPlayOneShot("sm_cooltime.wav");
		return false;
	}

	//해당 스킬을 사용할 MP가 없다면 False
	if (CurMP_ < MPConsumption_[_SkillName])
	{
		IsReadyNextAttack_ = false;
		GameEngineSound::SoundPlayOneShot("sm_cooltime.wav");
		return false;
	}

	IsReadyNextAttack_ = true;
	NextAttackAni_ = _ChangeStateEnum;
	return true;
}

void Player_Main::InitAniFunc()
{
	//프렌지
	MainRenderer_->AnimationBindEnd("Frenzy",
		[&](const FrameAnimation_DESC& _Desc)
		{
			GameEngineSound::SoundPlayOneShot("sm_frenzy.wav");
			IsFrenzy_ = true;
		});
	//폭주
	MainRenderer_->AnimationBindFrame("Fury",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 1)
			{
				GameEngineSound::SoundPlayOneShot("sm_congestion.wav");
				ShakeCamera(12.5f, 0.55f);
				StartSuperArmor(8.0f);
			}
		});
	MainRenderer_->AnimationBindEnd("Fury",
		[&](const FrameAnimation_DESC& _Desc)
		{
			StateManager_.ChangeState("Idle");
		});

	TripleSlashAniFunc();

	AutoAttackAniFunc();

	Frenzy_AutoAttackAniFunc();

	UpperSlashAniFunc();

	GoreCrossAniFun();

	HopSmashAniFunc();

	OutragebreakAniFunc();

	ExtremOverkillAniFunc();
}

void Player_Main::TripleSlashAniFunc()
{
	//TripleSlash_0
	MainRenderer_->AnimationBindFrame("TripleSlash_0",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 2)
			{
				Force_.ForceX_ = TripleSlashForceX;
				//CheckAttackKey();
				TripleSlash_->On();
				TripleSlash_->ChangeFrameAnimation("TripleSlash_0");
				TripleSlash_Trail_->On();
				TripleSlash_Trail_->ChangeFrameAnimation("TripleSlash_0");

				GameEngineSound::SoundPlayControl("tslash_01.wav");
				GameEngineSound::SoundPlayControl("sm_triple1.wav");
			}

			if (_Desc.CurFrame == 3)
			{
				SetAttackCol(Value_.TripleSlashhPos, Value_.TripleSlashhScale);
				//Set Attack
				CurAttackData_.AttackSound = GetRandomSound("slessSwd_hit_0", 1, 2) + ".wav";

				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "TripleSlash";
				CurAttackData_.Att = CalAtt(Value_.GoreCrossAtt);
				CurAttackData_.XForce = FrenzyXForce;
				CurAttackData_.Stiffness = 0.07f;
				CurAttackData_.RStiffness = 0.05f;
				CurAttackData_.Bleeding = 17;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			//else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_0_End - 1)
			//{
			//	CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
			//	CurAttackData_.AttCount++;
			//	CurAttackData_.AttEffect = Effect::SlashSLeft;
			//}

			else if (_Desc.CurFrame == _Desc.Frames.size())
			{
				TripleSlash_->Off();
				TripleSlash_Trail_->Off();

				AttackCol_->Off();
				IsAttack_End_ = true;
			}
		});

	//AutoAttack_1
	MainRenderer_->AnimationBindFrame("TripleSlash_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 2)
			{
				Force_.ForceX_ = TripleSlashForceX;
				GameEngineSound::SoundPlayControl("tslash_02.wav");
				GameEngineSound::SoundPlayControl("sm_triple2.wav");
				TripleSlash_->On();
				TripleSlash_->ChangeFrameAnimation("TripleSlash_1");

				TripleSlash_Trail_->On();
				TripleSlash_Trail_->ChangeFrameAnimation("TripleSlash_1");
			}

			/*	if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_1_Start + 1)
				{
					AutoAttackSound();
				}*/

			if (_Desc.CurFrame == 3)
			{
				SetAttackCol(Value_.TripleSlashhPos, Value_.TripleSlashhScale);
				CurAttackData_.AttackSound = GetRandomSound("slessSwd_hit_0", 1, 2) + ".wav";

				//Set Attack
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "TripleSlash";
				CurAttackData_.Att = CalAtt(Value_.GoreCrossAtt);
				CurAttackData_.XForce = FrenzyXForce;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.05f;
				CurAttackData_.Bleeding = 17;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttCount++;

				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			//else if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_1_End - 1)
			//{
			//	CurAttackData_.Att = CalAtt(Value_.FrenzyAtt);
			//	CurAttackData_.AttCount++;
			//	CurAttackData_.AttEffect = Effect::SlashSHori;
			//}

			else if (_Desc.CurFrame == _Desc.Frames.size())
			{
				TripleSlash_Trail_->Off();
				TripleSlash_->Off();
				AttackCol_->Off();
				IsAttack_End_ = true;
			}
		});

	//AutoAttack_3
	MainRenderer_->AnimationBindFrame("TripleSlash_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 2)
			{
				Force_.ForceX_ = TripleSlashForceX;
				GameEngineSound::SoundPlayControl("tslash_03.wav");
				GameEngineSound::SoundPlayControl("sm_triple3.wav");
				TripleSlash_->On();
				TripleSlash_->ChangeFrameAnimation("TripleSlash_2");
				TripleSlash_Trail_->On();
				TripleSlash_Trail_->ChangeFrameAnimation("TripleSlash_2");
			}

			/*	if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_3_Start + 1)
				{
					AutoAttackSound();
				}*/
			if (_Desc.CurFrame == 3)
			{
				float4 Sclae = Value_.TripleSlashhScale;
				Sclae.x = Value_.TripleSlashhScale.x * 1.4f;
				SetAttackCol(Value_.TripleSlashhPos, Sclae);
				//Set Attack
				CurAttackData_.AttackSound = GetRandomSound("slessSwd_hit_0", 1, 2) + ".wav";

				CurAttackData_.AttackName = "TripleSlash";
				CurAttackData_.Att = CalAtt(Value_.GoreCrossAtt);
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.Bleeding = 17;

				CurAttackData_.YForce = 550.0f;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttCount++;
				CurAttackData_.AttEffect = Effect::SlashSHori;
			}

			else if (_Desc.CurFrame == _Desc.Frames.size())
			{
				TripleSlash_->Off();
				TripleSlash_Trail_->Off();

				AttackCol_->Off();
				IsAttack_End_ = true;
			}
		});
}

void Player_Main::ExtremOverkillAniFunc()
{
	//ExtremOverkill_0 >> 검 소환 상태
	MainRenderer_->AnimationBindFrame("ExtremOverkill_0",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 1)
			{
				GodTime_.StartTimer(1.5f);
			}
			if (_Desc.CurFrame == 4)
			{
				GameEngineSound::SoundPlayOneShot("frenzy_cast.wav");
			}
			if (_Desc.CurFrame == _Desc.Frames.size() - 1)
			{
				AvatarManager_.ChangeMotion(PlayerAnimations::ExtremOverkill_1);
				EOKRenderer_->ChangeFrameAnimation("ExtremOverkill_1");
				EOKRenderer_Dodge_->ChangeFrameAnimation("ExtremOverkill_1");
			}
		});

	//ExtremOverkill_1 >> 검 내려찍기 직전 자세
	EOKRenderer_->AnimationBindFrame("ExtremOverkill_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 1)
			{
				StartSuperArmor(4.5f);
			}
			if (_Desc.CurFrame == _Desc.Frames.size() - 1)
			{
				AvatarManager_.ChangeMotion(PlayerAnimations::ExtremOverkill_2);
			}
		});

	//ExtremOverkill_2 >> 검 내려찍기
	MainRenderer_->AnimationBindFrame("ExtremOverkill_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 1)
			{
				ShakeCamera(16, 0.5f);

				EOKRenderer_->SetScaleRatio(2.0f);
				EOKRenderer_Dodge_->SetScaleRatio(2.0f);

				float4 EOKPos = { 130,70 };
				EOKPos.z = -20.f;
				EOKRenderer_Dodge_->GetTransform().SetLocalPosition(EOKPos);
				EOKRenderer_->GetTransform().SetLocalPosition(EOKPos);

				EOKRenderer_->ChangeFrameAnimation("ExtremOverkill_2");
				EOKRenderer_Dodge_->ChangeFrameAnimation("ExtremOverkill_2");
			}
			if (_Desc.CurFrame == 2)
			{
				GameEngineSound::SoundPlayOneShot("sm_blood_rave_atk.wav");
				GameEngineSoundPlayer Sound = GameEngineSound::SoundPlayControl("tslash_02.wav");
				//Sound.Volume(3.0f);
				CurAttackData_.AttackSound = CurAttackData_.AttackSound = GetRandomSound("slessSwd_hit_0", 1, 2) + ".wav";

				SetAttackCol(Value_.ExtremOverKillPos, Value_.ExtremOverKillScale);
				//Set Attack
				CurAttackData_.AttackName = "ExtremOverKill";
				CurAttackData_.Att = CalAtt(Value_.OutrageBreakAtt);
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.XForce = 20.0f;
				CurAttackData_.YForce = 750.0f;
				CurAttackData_.ZPos = 0;
				CurAttackData_.Stiffness = 0.22f;
				CurAttackData_.RStiffness = 0.21f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			if (_Desc.CurFrame == _Desc.Frames.size() - 1)
			{
			}
		});

	//검 다 내려찍고
	EOKRenderer_->AnimationBindFrame("ExtremOverkill_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			//색관련
			EOKRenderer_->GetPixelData().MulColor.a -= GameEngineTime::GetDeltaTime() * 8.0f;
			EOKRenderer_Dodge_->GetPixelData().MulColor -= GameEngineTime::GetDeltaTime() * 8.0f;

			if (EOKRenderer_->GetPixelData().MulColor.a <= 0)
			{
				EOKRenderer_->Off();
				EOKRenderer_Dodge_->Off();
			}
		});

	EOKRenderer_->AnimationBindEnd("ExtremOverkill_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			EOKRenderer_->Off();
			EOKRenderer_Dodge_->Off();
			float4 MovePos = { 290,-60,450 };
			MovePos.x = MovePos.x * GetDirX().x;
			float4 SpawnPos = GetTransform().GetWorldPosition() + MovePos;
			ExtremOverkill* Newkill = GetLevel()->CreateActor<ExtremOverkill>();
			Newkill->GetTransform().SetWorldPosition(SpawnPos);
		});
}

void Player_Main::OutragebreakAniFunc()
{
	//OutRageBreak_0 >> 가드상태
	Outragebreak_Sword_->AnimationBindFrame("Outragebreak_0",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 1)
			{
				StartSuperArmor(3.43f);
				GameEngineSound::SoundPlayOneShot("sm_outrage_break_01.wav");
			}
			if (_Desc.CurFrame == _Desc.Frames.size() - 1)
			{
				AvatarManager_.ChangeMotion(PlayerAnimations::Outragebreak_1);
				Outragebreak_Sword_->ChangeFrameAnimation("Outragebreak_1");

				Force_.ForceX_ = 300.f; //350.0f
				Force_.ForceY_ = 700.f; //390.0f
				Force_.Gravity_ = 1300;
				Force_.OnGravity();
				GroundYPos_ = GetTransform().GetWorldPosition().y;
				OnAir_ = true;

				//우선 1프레임 위로 보낸다 > 착지 로직 발동하지 않게 하기 위에
				Force_.Update(GameEngineTime::GetInst()->GetDeltaTime());
			}
		});

	//OutRageBreak_1 >>
	Outragebreak_Sword_->AnimationBindFrame("Outragebreak_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 0)
			{
				Outragebreak_Sword_->GetTransform().SetLocalPosition({ 143,-10,-20 });
			}
		});

	//OutRageBreak_1 >> 점프해서 올라가는 상태
	MainRenderer_->AnimationBindFrame("Outragebreak_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 2)
			{
			}

			//내려찍기 전 모션취하기
			if (Force_.ForceY_ < 420.f)
			{
				Force_.ForceY_ -= 600.f;//200
				Outragebreak_Sword_->GetTransform().SetLocalPosition({ 133,-10,-20 });
				AvatarManager_.ChangeMotion(PlayerAnimations::Outragebreak_2);
				Outragebreak_Sword_->ChangeFrameAnimation("Outragebreak_2");
			}

			//내려찍는 모션 취하기
			/*if (_Desc.CurFrame == _Desc.Frames.size() - 1)
			{
				AvatarManager_.ChangeMotion(PlayerAnimations::HopSmash_2);
			}*/
		});
	//OutRageBreak_2 >> 추락하면서 내려가는 상태
	MainRenderer_->AnimationBindFrame("Outragebreak_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			//if (_Desc.CurFrame == 1)//첫번째 프레임
			//{
			//	GameEngineSound::SoundPlayOneShot("sm_boongsan.wav");
			//	GameEngineSoundPlayer Sound = GameEngineSound::SoundPlayControl(GetRandomSound("swdc_0", 1, 5) + ".wav");
			//	Sound.Volume(3.0f);
			//	CurAttackData_.AttackSound = CurAttackData_.AttackSound = GetRandomSound("slessSwd_hit_0", 1, 2) + ".wav";
			//	SetAttackCol(Value_.UpperSlashPos, Value_.UpeerSlashScale);
			//	//Set Attack
			//	CurAttackData_.AttackName = "HopSmash";
			//	CurAttackData_.Att = CalAtt(Value_.AutoAttackAtt);
			//	CurAttackData_.Type = AttackType::Below;
			//	CurAttackData_.XForce = 50.0f;
			//	CurAttackData_.ZPos = static_cast<int>(GetBotPos().y);
			//	CurAttackData_.Stiffness = 0.07f;
			//	CurAttackData_.RStiffness = 0.04f;
			//	CurAttackData_.AttCount++;
			//	Force_.ForceX_ = 70.0f;
			//	CurAttackData_.AttEffect = Effect::SlashSRight;
			//}
			//if (_Desc.CurFrame == 3)//마지막 프레임
			//{
			//	CurAttackData_.AttCount++;
			//	CurAttackData_.AttEffect = Effect::SlashSHori;
			//	ShakeCamera(7.5f, 0.45f);
			//}
		});
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
			if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_0_Start + 1)
			{
				AutoAttackSound();
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
			if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_1_Start + 1)
			{
				AutoAttackSound();
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
			if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_2_Start + 1)
			{
				AutoAttackSound();
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
			if (_Desc.Frames[_Desc.CurFrame - 1] == Frenzy_AutoAttack_3_Start + 1)
			{
				AutoAttackSound();
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
				AutoAttackSound();
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
				AutoAttackSound();
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
				AutoAttackSound();
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
			if (_Desc.CurFrame == 1)//첫번째 프레임
			{
				GameEngineSound::SoundPlayOneShot("sm_boongsan.wav");
				GameEngineSoundPlayer Sound = GameEngineSound::SoundPlayControl(GetRandomSound("swdc_0", 1, 5) + ".wav");
				Sound.Volume(3.0f);
				CurAttackData_.AttackSound = CurAttackData_.AttackSound = GetRandomSound("slessSwd_hit_0", 1, 2) + ".wav";
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
			if (_Desc.CurFrame == 3)//마지막 프레임
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
				//슈퍼아머 set
				StartSuperArmor(0.29f);
				GameEngineSound::SoundPlayOneShot("sm_upslash.wav");
				GameEngineSound::SoundPlayOneShot(GetRandomSound("upper_slash_0", 1, 2) + ".wav");
			}
			if (_Desc.Frames[_Desc.CurFrame - 1] == AutoAttack_2_Start + 1)
			{
				SetAttackCol(Value_.UpperSlashPos, Value_.UpeerSlashScale);
				//Set Attack
				CurAttackData_.AttackSound = CurAttackData_.AttackSound = GetRandomSound("slessSwd_hit_0", 1, 2) + ".wav";
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

				//내가 앞으로 가는 정도
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
				//사운드
				GameEngineSound::SoundPlayOneShot("sm_gorecross.wav");
				GameEngineSound::SoundPlayOneShot("upper_slash_01.wav");

				CurAttackData_.AttackSound = CurAttackData_.AttackSound = "gorecross_hit_01.wav";
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

				//고어크로스 액터 생성
				GoreCross* New = GetLevel()->CreateActor<GoreCross>();
				float4 SpawnPos = GetTransform().GetWorldPosition();
				float4 MovePos = Value_.GoreCrossSpawnPos;
				MovePos.x = GetDirX().x * MovePos.x;
				New->GetTransform().SetWorldPosition(SpawnPos + MovePos);
				New->GetTransform().SetLocalScale({ GetDirX().x,1,1 });
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == GoreCross_0_End - 4)
			{
				GameEngineSound::SoundPlayOneShot("upper_slash_02.wav");
				CurAttackData_.AttackSound = CurAttackData_.AttackSound = "gorecross_hit_02.wav";
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