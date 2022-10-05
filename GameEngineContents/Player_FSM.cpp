#include "PreCompile.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "Player_Main.h"
#include "HopSmash.h"
#include "Outragebreak.h"

//렌더러추가
void Player_Main::AddRenderer_Init()
{
	//프렌지 텍스처가 없으면 로드한다.
	if (GameEngineFolderTexture::Find("sword_blood_upper") == nullptr)
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("SkillTexture");
			Dir.Move("Frenzy");
			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
	}

	//아웃레이지 브레이크 텍스처가 없으면 로드한다
	if (GameEngineFolderTexture::Find("outragebreak_bloodsword_none") == nullptr)
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("SkillTexture");
			Dir.Move("Outragebreak");
			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
	}

	//익오킬 텍스처가 없으면 로드한다
	if (GameEngineFolderTexture::Find("kaaa-d2") == nullptr)
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("SkillTexture");
			Dir.Move("ExtremOverkill");
			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
	}

	//스파크 텍스처가 없으면 로드한다
	if (GameEngineFolderTexture::Find("electric065_etc") == nullptr)
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("SkillTexture");
			Dir.Move("Electric");
			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
	}

	//트리플 어택 텍스처가 없으면 로드한다
	if (GameEngineFolderTexture::Find("Triple1") == nullptr)
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("SkillTexture");
			Dir.Move("TripleSlash");
			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
	}
	float Iter_2 = 0.027f;

	Frenzy_Upper_ = CreateComponent<GameEngineTextureRenderer>();
	Frenzy_Upper_->CreateFrameAnimationFolder("Frenzy_AutoAttack_0", FrameAnimation_DESC("sword_blood_upper", 0, 5, Iter_2 * 2.1f, false));
	Frenzy_Upper_->CreateFrameAnimationFolder("Frenzy_AutoAttack_1", FrameAnimation_DESC("sword_blood_upper", 6, 10, Iter_2 * 2.1f, false));
	Frenzy_Upper_->CreateFrameAnimationFolder("Frenzy_AutoAttack_2", FrameAnimation_DESC("sword_blood_upper", 11, 15, Iter_2 * 2.1f, false));
	Frenzy_Upper_->CreateFrameAnimationFolder("Frenzy_AutoAttack_3", FrameAnimation_DESC("sword_blood_upper", 16, 21, Iter_2 * 2.1f, false));
	Frenzy_Upper_->ChangeFrameAnimation("Frenzy_AutoAttack_0");
	Frenzy_Upper_->SetScaleModeImage();
	Frenzy_Upper_->Off();

	Frenzy_Under_ = CreateComponent<GameEngineTextureRenderer>();
	Frenzy_Under_->CreateFrameAnimationFolder("Frenzy_AutoAttack_0", FrameAnimation_DESC("sword_blood_under", 0, 5, Iter_2 * 2.1f, false));
	Frenzy_Under_->CreateFrameAnimationFolder("Frenzy_AutoAttack_1", FrameAnimation_DESC("sword_blood_under", 6, 10, Iter_2 * 2.1f, false));
	Frenzy_Under_->CreateFrameAnimationFolder("Frenzy_AutoAttack_2", FrameAnimation_DESC("sword_blood_under", 11, 15, Iter_2 * 2.1f, false));
	Frenzy_Under_->CreateFrameAnimationFolder("Frenzy_AutoAttack_3", FrameAnimation_DESC("sword_blood_under", 16, 21, Iter_2 * 2.1f, false));
	Frenzy_Under_->ChangeFrameAnimation("Frenzy_AutoAttack_0");
	Frenzy_Under_->SetScaleModeImage();
	Frenzy_Under_->Off();

	Frenzy_Trail_ = CreateComponent<GameEngineTextureRenderer>();
	Frenzy_Trail_->CreateFrameAnimationFolder("Frenzy_AutoAttack_0", FrameAnimation_DESC("blood-energy", 0, 5, Iter_2 * 2.1f, false));
	Frenzy_Trail_->CreateFrameAnimationFolder("Frenzy_AutoAttack_1", FrameAnimation_DESC("blood-energy", 6, 10, Iter_2 * 2.1f, false));
	Frenzy_Trail_->CreateFrameAnimationFolder("Frenzy_AutoAttack_3", FrameAnimation_DESC("blood-energy", 16, 21, Iter_2 * 2.1f, false));
	Frenzy_Trail_->CreateFrameAnimationFolder("Frenzy_AutoAttack_2", FrameAnimation_DESC("blood-energy", 11, 15, Iter_2 * 2.1f, false));
	Frenzy_Trail_->ChangeFrameAnimation("Frenzy_AutoAttack_0");
	Frenzy_Trail_->SetScaleModeImage();
	Frenzy_Trail_->GetTransform().SetLocalMove({ 0,0,-20 });
	Frenzy_Trail_->Off();

	Blood_Effect_ = CreateComponent<GameEngineTextureRenderer>();
	Blood_Effect_->CreateFrameAnimationFolder("Default", FrameAnimation_DESC("blood-spirits", 0.13f, true));
	Blood_Effect_->ChangeFrameAnimation("Default");
	Blood_Effect_->SetScaleModeImage();
	Blood_Effect_->GetTransform().SetLocalMove({ -20,-10,-20 });
	Blood_Effect_->GetPixelData().MulColor.a = 0.7f;
	Blood_Effect_->Off();

	Outragebreak_Sword_ = CreateComponent<GameEngineTextureRenderer>();
	Outragebreak_Sword_->CreateFrameAnimationFolder("Outragebreak_0", FrameAnimation_DESC("outragebreak_bloodsword_none", 0, 9, Iter_2 * 3.0f, false));
	Outragebreak_Sword_->CreateFrameAnimationFolder("Outragebreak_1", FrameAnimation_DESC("outragebreak_bloodsword_none", 10, 10, Iter_2 * 3.0f, false));
	Outragebreak_Sword_->CreateFrameAnimationFolder("Outragebreak_2", FrameAnimation_DESC("outragebreak_bloodsword_none", 11, 12, Iter_2 * 3.0f, false));
	Outragebreak_Sword_->CreateFrameAnimationFolder("Outragebreak_3", FrameAnimation_DESC("outragebreak_bloodsword_none", 13, 19, Iter_2 * 3.0f, false));
	Outragebreak_Sword_->ChangeFrameAnimation("Outragebreak_0");
	Outragebreak_Sword_->SetScaleModeImage();
	Outragebreak_Sword_->GetTransform().SetLocalMove({ 0,0,-20 });
	Outragebreak_Sword_->Off();

	float4 EOKPos = { -50,0,-20 };

	EOKRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	EOKRenderer_->CreateFrameAnimationFolder("ExtremOverkill_0", FrameAnimation_DESC("sword-normal", Iter_2 * 3.0f, false));
	EOKRenderer_->CreateFrameAnimationFolder("ExtremOverkill_1", FrameAnimation_DESC("change-n", Iter_2 * 4.5f, false));
	EOKRenderer_->CreateFrameAnimationFolder("ExtremOverkill_2", FrameAnimation_DESC("slash-n", Iter_2 * 3.0f, false));
	EOKRenderer_->ChangeFrameAnimation("ExtremOverkill_0");
	EOKRenderer_->SetScaleModeImage();
	EOKRenderer_->GetTransform().SetLocalMove(EOKPos);
	EOKRenderer_->Off();

	EOKRenderer_Dodge_ = CreateComponent<GameEngineTextureRenderer>();
	EOKRenderer_Dodge_->CreateFrameAnimationFolder("ExtremOverkill_0", FrameAnimation_DESC("sword-dodge", Iter_2 * 3.0f, false));
	EOKRenderer_Dodge_->CreateFrameAnimationFolder("ExtremOverkill_1", FrameAnimation_DESC("change-d", Iter_2 * 4.5f, false));
	EOKRenderer_Dodge_->CreateFrameAnimationFolder("ExtremOverkill_2", FrameAnimation_DESC("slash-d", Iter_2 * 3.0f, false));
	EOKRenderer_Dodge_->ChangeFrameAnimation("ExtremOverkill_0");
	EOKRenderer_Dodge_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	EOKRenderer_Dodge_->SetScaleModeImage();
	EOKRenderer_Dodge_->GetTransform().SetLocalMove(EOKPos);
	EOKRenderer_Dodge_->Off();

	Resurrection_ = CreateComponent<GameEngineTextureRenderer>();
	Resurrection_->CreateFrameAnimationFolder("Default", FrameAnimation_DESC("electric065_etc", Iter_2 * 3.0f, false));
	Resurrection_->ChangeFrameAnimation("Default");
	Resurrection_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	Resurrection_->SetScaleRatio(1.6f);
	Resurrection_->SetScaleModeImage();
	Resurrection_->GetTransform().SetLocalPosition({ -70,350,-500 });

	//Resurrection_->GetTransform().SetLocalMove(EOKPos);
	Resurrection_->Off();
	Resurrection_->AnimationBindEnd("Default", [&](const FrameAnimation_DESC _Desc)
		{
			Resurrection_->Off();
			AttackCol_->Off();
			CurAttackData_ = {};
		});

	float4 TriPos = { 0,0,-20 };
	TripleSlash_ = CreateComponent<GameEngineTextureRenderer>();
	TripleSlash_->CreateFrameAnimationFolder("TripleSlash_0", FrameAnimation_DESC("Triple1", Iter_2 * 1.3f, false));
	TripleSlash_->CreateFrameAnimationFolder("TripleSlash_1", FrameAnimation_DESC("Triple2", Iter_2 * 1.3f, false));
	TripleSlash_->CreateFrameAnimationFolder("TripleSlash_2", FrameAnimation_DESC("Triple3", Iter_2 * 1.3f, false));
	TripleSlash_->ChangeFrameAnimation("TripleSlash_0");
	TripleSlash_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	TripleSlash_->SetScaleModeImage();
	TripleSlash_->GetTransform().SetLocalMove(TriPos);
	TripleSlash_->Off();

	TripleSlash_Trail_ = CreateComponent<GameEngineTextureRenderer>();
	TripleSlash_Trail_->CreateFrameAnimationFolder("TripleSlash_0", FrameAnimation_DESC("TripleTrail", 0, 3, Iter_2 * 1.3f, false));
	TripleSlash_Trail_->CreateFrameAnimationFolder("TripleSlash_1", FrameAnimation_DESC("TripleTrail", 0, 3, Iter_2 * 1.3f, false));
	TripleSlash_Trail_->CreateFrameAnimationFolder("TripleSlash_2", FrameAnimation_DESC("TripleTrail", 4, 7, Iter_2 * 1.3f, false));
	TripleSlash_Trail_->ChangeFrameAnimation("TripleSlash_0");
	TripleSlash_Trail_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	TripleSlash_Trail_->SetScaleModeImage();
	TripleSlash_Trail_->GetTransform().SetLocalMove(TriPos);
	TripleSlash_Trail_->Off();
}

void Player_Main::IdleStart(const StateInfo _Info)
{
	if (IsBattleMode_ == false)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	}
	else
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::BattleIdle);
	}

	PrevHitData_ = {};
}

void Player_Main::IdleUpdate(float _DeltaTime, const StateInfo _Info)
{
	if (IsBattleMode_ == false)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	}
	else
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::BattleIdle);
	}

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
	if (IsBattleMode_ == false)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Move);
	}
	else
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::BattleMove);
	}
}

void Player_Main::MoveUpdate(float _DeltaTime, const StateInfo _Info)
{
	if (IsBattleMode_ == false)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Move);
	}
	else
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::BattleMove);
	}

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
	if (IsBattleMode_ == false)
	{
		GetTransform().SetLocalMove(GetMoveDir() * _DeltaTime * 200.0f);
	}
	else
	{
		GetTransform().SetLocalMove(GetMoveDir() * _DeltaTime * 300.0f);
	}

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
	if (IsBattleMode_ == false)
	{
		if (CanMove(float4(GetMoveDir().x, 0, 0) * _DeltaTime * 200.0f) == true)
		{
			GetTransform().SetLocalMove(float4(GetMoveDir().x, 0, 0) * _DeltaTime * 200.0f);
		}
	}
	else
	{
		if (CanMove(float4(GetMoveDir().x, 0, 0) * _DeltaTime * 300.0f) == true)
		{
			GetTransform().SetLocalMove(float4(GetMoveDir().x, 0, 0) * _DeltaTime * 300.0f);
		}
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
	GameEngineSound::SoundPlayOneShot(GetRandomSound("sm_dmg_0", 1, 3) + ".wav");
	//ChangeHitColTrans("Hit");
	//플레이어를 마주보는 방향으로 Flip
	//FlipX(-Player_->GetDirX());
	Force_.ForceX_ += -PrevHitData_.XForce;

	GetTransform().SetLocalMove(float4(0, Force_.ForceY_ * GameEngineTime::GetDeltaTime()));
	Force_.OnGravity();
	OnAir_ = true;
}

void Player_Main::AirborneUpdate(float _DeltaTime, const StateInfo _Info)
{
	//경직
	//추락
	AirborneTime_ += _DeltaTime;
	float CurYPos = GetTransform().GetWorldPosition().y;

	if (CurYPos <= GroundYPos_)
	{
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		ShadowUpdate();
		//Down 상태 Bounce
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

	GameEngineSound::SoundPlayOneShot("mon_fall_down_02.wav");
	Down_Timer_.StartTimer(Value_.Down_Time);
	Force_.ForceX_ += -PrevHitData_.XForce;

	GetTransform().SetLocalMove(float4(0, Force_.ForceY_ * GameEngineTime::GetDeltaTime()));
}

void Player_Main::DownUpdate(float _DeltaTime, const StateInfo _Info)
{
	AirborneTime_ += 5.0f * _DeltaTime;
	float CurYPos = GetTransform().GetWorldPosition().y;

	//사망검사
	if (CurHP_ == 0)
	{
		StateManager_.ChangeState("Die");
		return;
	}

	if (CurYPos <= GroundYPos_)
	{
		//GroundYPos 아래로 떨어지지 않게 고정시키기
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		ShadowUpdate();
		Down_Timer_ -= _DeltaTime * (1.f + AirborneTime_ * 0.1f);
		OnAir_ = false;
		Force_.OffGravity();

		//퀵스텐딩 검사
		{
			if (GameEngineInput::GetInst()->IsPress("C") == true)
			{
				//해당 스킬을 사용해서 쿨타임이 돌고있는 상태면 무시한다.
				if (SkillCoolTime_["QuickStanding"]->IsTimerOn() == false)
				{
					OnAir_ = false;
					Force_.ForceY_ = 0.0f;
					AirborneTime_ = 0.0f;
					Force_.OffGravity();
					GodTime_.StartTimer(Value_.Down_God_Time);
					PrevHitData_ = {};
					StateManager_.ChangeState("QuickStanding");
					return;
				}
			}
		}

		//기상검사
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

void Player_Main::QuickStandingStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::QuickStanding);
	GodTime_.StartTimer(2.5f);
}

void Player_Main::QuickStandingUpdate(float _DeltaTime, const StateInfo _Info)
{
	if (GameEngineInput::GetInst()->IsPress("C") == false && GodTime_.GetCurTime() < 2.0f)
	{
		StateManager_.ChangeState("Idle");
		return;
	}

	if (GodTime_.IsTimerOn() == false)
	{
		StateManager_.ChangeState("Idle");
		return;
	}
}

void Player_Main::QuickStandingEnd(const StateInfo _Info)
{
	SkillCoolTime_["QuickStanding"]->StartTimer();
	GodTime_.StartTimer(0.05f);
	StartSuperArmor(0.2f);
}

void Player_Main::AutoAttackStart(const StateInfo _Info)
{
	if (IsFrenzy_ == false)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::AutoAttack_0);
	}
	else
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Frenzy_AutoAttack_0);
		Frenzy_Upper_->CurAnimationReset();
		Frenzy_Under_->CurAnimationReset();
		Frenzy_Trail_->CurAnimationReset();

		Frenzy_Upper_->On();
		Frenzy_Under_->On();
		Frenzy_Trail_->On();
		Frenzy_Upper_->ChangeFrameAnimation("Frenzy_AutoAttack_0");
		Frenzy_Under_->ChangeFrameAnimation("Frenzy_AutoAttack_0");
		Frenzy_Trail_->ChangeFrameAnimation("Frenzy_AutoAttack_0");
	}
}

void Player_Main::AutoAttackUpdate(float _DeltaTime, const StateInfo _Info)
{
	//평소에는 False
	if (IsAttack_End_ == true)
	{
		if (IsReadyNextAttack_ == true)
		{
			if (IsFrenzy_ == false) //프렌지 상태가 아니면 평범한 평타
			{
				if (NextAttackAni_ == PlayerAnimations::AutoAttack_1 || NextAttackAni_ == PlayerAnimations::AutoAttack_2)
				{
					AvatarManager_.ChangeMotion(NextAttackAni_);
					IsAttack_End_ = false;
					IsReadyNextAttack_ = false;
					return;
				}
			}
			else //프렌지 상태면 특수한 평타
			{
				if (NextAttackAni_ == PlayerAnimations::Frenzy_AutoAttack_1 || NextAttackAni_ == PlayerAnimations::Frenzy_AutoAttack_2 || NextAttackAni_ == PlayerAnimations::Frenzy_AutoAttack_3)
				{
					AvatarManager_.ChangeMotion(NextAttackAni_);

					std::string AniName = AvatarManager_.EnumToString(NextAttackAni_);
					Frenzy_Upper_->ChangeFrameAnimation(AniName);
					Frenzy_Under_->ChangeFrameAnimation(AniName);
					Frenzy_Trail_->ChangeFrameAnimation(AniName);

					IsAttack_End_ = false;
					IsReadyNextAttack_ = false;
					return;
				}
			}
			//평타외 다른 스킬이 입력들어오면 그상태로 바꾼다.
			if (NextAttackAni_ != PlayerAnimations::AutoAttack) //이 조건은 평타 한번만 누른 상태 == AutoAttack이 되기 때문에 AutoAttack을 한번 더 들어오기 때문에 예외처리
			{
				StateManager_.ChangeState(AvatarManager_.EnumToString(NextAttackAni_));
				return;
			}
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

	//프렌지 종료
	Frenzy_Upper_->Off();
	Frenzy_Under_->Off();
	Frenzy_Trail_->Off();
}

void Player_Main::UpperSlashStart(const StateInfo _Info)
{
	IsAttack_End_ = false;
	AvatarManager_.ChangeMotion(PlayerAnimations::UpperSlash);
	//CoolTime Set
	SkillCoolTime_["UpperSlash"]->StartTimer();

	//마나 소모
	CurMP_ -= Value_.UpperSlash_MP;
}

void Player_Main::UpperSlashUpdate(float _DeltaTime, const StateInfo _Info)
{
	//평소에는 False
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

void Player_Main::TripleSlashStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::TripleSlash_0);
	TripleSlashTimer_.StartTimer(TripleSlashGetKeyTime_);

	TripleSlash_->CurAnimationReset();
	TripleSlash_Trail_->CurAnimationReset();

	//마나 소모
	CurMP_ -= Value_.HopSmash_MP;
}

void Player_Main::TripleSlashUpdate(float _DeltaTime, const StateInfo _Info)
{
	//공격중인 상태
	if (TripleSlashTimer_.IsTimerOn() == true)
	{
		TripleSlashTimer_.Update(_DeltaTime);
		//특정 시간까지 키 입력을 받는다.
		if (GameEngineInput::GetInst()->IsDown("D") == true)
		{
			IsReadyNextAttack_ = true;

			//같은 공격인데 이미 공격횟수를 전부 했음
			if (CurAttackData_.AttCount >= 3)
			{
				IsReadyNextAttack_ = false;
			}
			switch (CurAttackData_.AttCount)
			{
			case 1:
				NextAttackAni_ = PlayerAnimations::TripleSlash_1;
				break;
			case 2:
				NextAttackAni_ = PlayerAnimations::TripleSlash_2;
				break;
			default:
				break;
			}
			//특정시간에 키입력을 받으면 모션을 바로 바꾼다.
			if (TripleSlashTimer_.GetCurTime() < TripleSlashGetKeyTime_ * 0.5f)
			{
				TripleSlashTimer_.Off();
			}
		}
	}
	//공격이 끝났어 == 한사이클이 돌았어
	if (TripleSlashTimer_.IsTimerOn() == false)
	{
		if (IsReadyNextAttack_ == true)
		{
			if (NextAttackAni_ == PlayerAnimations::TripleSlash_1 || NextAttackAni_ == PlayerAnimations::TripleSlash_2)
			{
				FlipX(GetMoveDir());
				TripleSlashTimer_.StartTimer(TripleSlashGetKeyTime_);
				AvatarManager_.ChangeMotion(NextAttackAni_);
				IsAttack_End_ = false;
				IsReadyNextAttack_ = false;
				return;
			}
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

void Player_Main::TripleSlashEnd(const StateInfo _Info)
{
	//CoolTime Set
	SkillCoolTime_["TripleSlash"]->StartTimer();
	Force_.ForceX_ = 0.f;
	TripleSlash_->Off();
	TripleSlash_Trail_->Off();
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

	//우선 1프레임 위로 보낸다 > 착지 로직 발동하지 않게 하기 위에
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
		GameEngineSound::SoundPlayOneShot("boongsan_explo.wav");
		SetAttackCol(Value_.UpperSlashPos, Value_.HopSmashScale);
		CurAttackData_.AttCount++;
		CurAttackData_.AttEffect = Effect::SlashSRight;
		CurAttackData_.Stiffness = 0.22f;
		CurAttackData_.RStiffness = 0.21f;
		CurAttackData_.YForce = 350.0f;
		CurAttackData_.Bleeding = 85;
		CurAttackData_.ZPos = 0;
		IsReadyNextAttack_ = false;
		IsAttack_End_ = true;
		JumpLogicEnd();
		return;
	}
	//평소에는 False
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

//아웃뷁스타트
void Player_Main::OutragebreakStart(const StateInfo _Info)
{
	IsAttack_End_ = false;
	SkillCoolTime_["Outragebreak"]->StartTimer();
	CurMP_ -= Value_.Outragebreak_MP;

	WeaponRenderer_b_->Off();
	WeaponRenderer_c_->Off();

	Outragebreak_Sword_->CurAnimationReset();
	Outragebreak_Sword_->On();
	Outragebreak_Sword_->ChangeFrameAnimation("Outragebreak_0");
	Outragebreak_Sword_->GetTransform().SetLocalPosition({ 143,-10,-20 });

	AvatarManager_.ChangeMotion(PlayerAnimations::Outragebreak_0);
}

void Player_Main::OutragebreakUpdate(float _DeltaTime, const StateInfo _Info)
{
	//점프해서 바로 딱 착지한 상태임
	if (GetTransform().GetWorldPosition().y <= GroundYPos_ && StateManager_.GetCurStateTime() >= 0.92f && IsAttack_End_ == false && IsOutragebreak_first_ == true)
	{
		IsOutragebreak_first_ = false;
		AvatarManager_.ChangeMotion(PlayerAnimations::Outragebreak_3);
		Outragebreak_Sword_->ChangeFrameAnimation("Outragebreak_3");
		ShakeCamera(13.5f, 0.45f);

		Outragebreak* New = GetLevel()->CreateActor<Outragebreak>();
		float4 SpawnPos = GetTransform().GetWorldPosition();
		float4 MovePos = { 40,8, };
		MovePos.x = GetDirX().x * MovePos.x;
		New->GetTransform().SetWorldPosition(SpawnPos + MovePos);
		New->GetTransform().SetLocalScale(float4(GetDirX().x * 1.55f, 1 * 1.12f, 1) /** DNFGlobalValue::Temp1.w*/);

		GameEngineSound::SoundPlayOneShot("sm_outrage_break_02.wav");
		GameEngineSound::SoundPlayOneShot("outrage_swing.wav");
		//GameEngineSoundPlayer Sound = GameEngineSound::SoundPlayControl(GetRandomSound("swdc_0", 1, 5) + ".wav");
		//Sound.Volume(3.0f);
		//CurAttackData_.AttackSound = CurAttackData_.AttackSound = GetRandomSound("slessSwd_hit_0", 1, 2) + ".wav";

		//

			//Set Attack
		SetAttackCol(Value_.OutrageBreakPos, Value_.OutrageBreakScale);
		CurAttackData_.AttackName = "Outragebreak";
		CurAttackData_.Att = CalAtt(Value_.OutrageBreakAtt);
		CurAttackData_.Type = AttackType::Below;
		CurAttackData_.XForce = 50.0f;

		CurAttackData_.AttCount++;
		CurAttackData_.AttEffect = Effect::SlashSRight;
		CurAttackData_.Stiffness = 0.22f;
		CurAttackData_.RStiffness = 0.21f;
		CurAttackData_.YForce = 650.0f;
		CurAttackData_.Bleeding = 85;
		CurAttackData_.ZPos = 0;
		//IsReadyNextAttack_ = false;
		//IsAttack_End_ = true;
		JumpLogicEnd();
		return;
	}
	//평소에는 False
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

void Player_Main::OutragebreakEnd(const StateInfo _Info)
{
	IsOutragebreak_first_ = true;
	Force_.FrictionX_ = Value_.DefaultFriction;
	Force_.Gravity_ = Value_.DefaultGravity;
	AttackEnd();
	JumpLogicEnd();

	WeaponRenderer_b_->On();
	WeaponRenderer_c_->On();
	Outragebreak_Sword_->Off();
}

//익오킬스타트
void Player_Main::ExtremOverkillStart(const StateInfo _Info)
{
	IsAttack_End_ = false;
	SkillCoolTime_["ExtremOverkill"]->StartTimer();
	CurMP_ -= Value_.Outragebreak_MP * 3;

	WeaponRenderer_b_->Off();
	WeaponRenderer_c_->Off();

	float4 EOKPos = { -50,0,-20 };
	EOKRenderer_Dodge_->SetScaleRatio(1.0f);
	EOKRenderer_Dodge_->GetTransform().SetLocalPosition(EOKPos);
	EOKRenderer_Dodge_->CurAnimationReset();
	EOKRenderer_Dodge_->On();
	EOKRenderer_Dodge_->ChangeFrameAnimation("ExtremOverkill_0");
	EOKRenderer_Dodge_->GetPixelData().MulColor = { 1,1,1 };

	EOKRenderer_->SetScaleRatio(1.0f);
	EOKRenderer_->GetTransform().SetLocalPosition(EOKPos);
	EOKRenderer_->CurAnimationReset();
	EOKRenderer_->On();
	EOKRenderer_->ChangeFrameAnimation("ExtremOverkill_0");
	EOKRenderer_->GetPixelData().MulColor.a = 1.f;

	AvatarManager_.ChangeMotion(PlayerAnimations::ExtremOverkill_0);
}

void Player_Main::ExtremOverkillUpdate(float _DeltaTime, const StateInfo _Info)
{
	//평소에는 False
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

void Player_Main::ExtremOverkillEnd(const StateInfo _Info)
{
	WeaponRenderer_b_->On();
	WeaponRenderer_c_->On();
	EOKRenderer_->Off();
	EOKRenderer_Dodge_->Off();
	AttackEnd();
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
	//평소에는 False
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

void Player_Main::FrenzyStart(const StateInfo _Info)
{
	if (IsFrenzy_ == false)
	{
		AvatarManager_.ChangeMotion(PlayerAnimations::Frenzy);
	}
	SkillCoolTime_["Frenzy"]->StartTimer();
}

void Player_Main::FrenzyUpdate(float _DeltaTime, const StateInfo _Info)
{
	if (IsFrenzy_ == true && StateManager_.GetCurStateTime() < 0.1f) //끄는 경우
	{
		IsFrenzy_ = false;
		Blood_Effect_->Off();
		StateManager_.ChangeState("Idle");
		return;
	}

	if (IsFrenzy_ == true) //키는 경우
	{
		Blood_Effect_->On();
		StateManager_.ChangeState("Idle");
		return;
	}
}

void Player_Main::FuryStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Fury);
	SkillCoolTime_["Fury"]->StartTimer();
}

void Player_Main::FuryUpdate(float _DeltaTime, const StateInfo _Info)
{
}

void Player_Main::HitStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Hit);
	ResetDNFAnimation();
	//ChangeHitColTrans("Hit");
	Hit_Timer_ = 0.65f;
	Hit_Timer_.StartTimer();

	GameEngineSound::SoundPlayOneShot(GetRandomSound("sm_dmg_0", 1, 3) + ".wav");
	//플레이어를 마주보는 방향으로 Flip
	//FlipX(-Player_->GetDirX());
	Force_.ForceX_ += -PrevHitData_.XForce;
}

void Player_Main::HitUpdate(float _DeltaTime, const StateInfo _Info)
{
	//사망검사
	if (CurHP_ == 0)
	{
		StateManager_.ChangeState("Die");
		return;
	}
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

void Player_Main::DieStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Down);
	GodTime_.StartTimer(99999.f);
	Force_.OffGravity();
	Force_.ForceX_ = 0;
	GameEngineSoundPlayer Sound = GameEngineSound::SoundPlayControl("sm_die.wav");//revive_cast
	Sound.Volume(1.3f);
}

void Player_Main::DieUpdate(float _DeltaTime, const StateInfo _Info)
{
	if (GameEngineInput::GetInst()->IsDown("X") == true)
	{
		GodTime_.StartTimer(1.5f);
		GameEngineSoundPlayer Sound = GameEngineSound::SoundPlayControl("revive_cast.wav");//revive_cast
		Resurrection_->On();
		Resurrection_->CurAnimationReset();
		CurHP_ = MaxHP_;
		CurMP_ = MaxMP_;
		PrevHitData_ = {};
		IsFrenzy_ = false;
		Blood_Effect_->Off();
		*SuperArmorTimer_.GetIterTime() = 0.f;

		StateManager_.ChangeState("Idle");
		//공격 잠시만 키기
		SetAttackCol({ 0,0,-500 }, Value_.HopSmashScale);
		CurAttackData_.AttackName = "Resurrection";
		CurAttackData_.Att = CalAtt(100);
		CurAttackData_.Type = AttackType::Below;
		CurAttackData_.XForce = 250.0f;
		CurAttackData_.YForce = 150.0f;

		CurAttackData_.AttCount++;
		CurAttackData_.AttEffect = Effect::None;
		CurAttackData_.Stiffness = 0.02f;
		CurAttackData_.RStiffness = 0.01f;
		CurAttackData_.ZPos = 0;
	}
}