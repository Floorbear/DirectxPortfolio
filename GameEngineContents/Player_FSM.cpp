#include "PreCompile.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DNFContentsMinimal.h"
#include "Player_Main.h"
#include "HopSmash.h"

void Player_Main::Frenzy_Init()
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
	float Iter_2 = 0.027f;

	Frenzy_Upper_ = CreateComponent<GameEngineTextureRenderer>();
	Frenzy_Upper_->CreateFrameAnimationFolder("Frenzy_AutoAttack_0", FrameAnimation_DESC("sword_blood_upper", 0, 5, Iter_2 * 2.3f, false));
	Frenzy_Upper_->CreateFrameAnimationFolder("Frenzy_AutoAttack_1", FrameAnimation_DESC("sword_blood_upper", 6, 10, Iter_2 * 2.3f, false));
	Frenzy_Upper_->CreateFrameAnimationFolder("Frenzy_AutoAttack_2", FrameAnimation_DESC("sword_blood_upper", 11, 15, Iter_2 * 2.3f, false));
	Frenzy_Upper_->CreateFrameAnimationFolder("Frenzy_AutoAttack_3", FrameAnimation_DESC("sword_blood_upper", 16, 21, Iter_2 * 2.3f, false));
	Frenzy_Upper_->ChangeFrameAnimation("Frenzy_AutoAttack_0");
	Frenzy_Upper_->SetScaleModeImage();
	Frenzy_Upper_->Off();

	Frenzy_Under_ = CreateComponent<GameEngineTextureRenderer>();
	Frenzy_Under_->CreateFrameAnimationFolder("Frenzy_AutoAttack_0", FrameAnimation_DESC("sword_blood_under", 0, 5, Iter_2 * 2.3f, false));
	Frenzy_Under_->CreateFrameAnimationFolder("Frenzy_AutoAttack_1", FrameAnimation_DESC("sword_blood_under", 6, 10, Iter_2 * 2.3f, false));
	Frenzy_Under_->CreateFrameAnimationFolder("Frenzy_AutoAttack_2", FrameAnimation_DESC("sword_blood_under", 11, 15, Iter_2 * 2.3f, false));
	Frenzy_Under_->CreateFrameAnimationFolder("Frenzy_AutoAttack_3", FrameAnimation_DESC("sword_blood_under", 16, 21, Iter_2 * 2.3f, false));
	Frenzy_Under_->ChangeFrameAnimation("Frenzy_AutoAttack_0");
	Frenzy_Under_->SetScaleModeImage();
	Frenzy_Under_->Off();

	Frenzy_Trail_ = CreateComponent<GameEngineTextureRenderer>();
	Frenzy_Trail_->CreateFrameAnimationFolder("Frenzy_AutoAttack_0", FrameAnimation_DESC("blood-energy", 0, 5, Iter_2 * 2.3f, false));
	Frenzy_Trail_->CreateFrameAnimationFolder("Frenzy_AutoAttack_1", FrameAnimation_DESC("blood-energy", 6, 10, Iter_2 * 2.3f, false));
	Frenzy_Trail_->CreateFrameAnimationFolder("Frenzy_AutoAttack_2", FrameAnimation_DESC("blood-energy", 11, 15, Iter_2 * 2.3f, false));
	Frenzy_Trail_->CreateFrameAnimationFolder("Frenzy_AutoAttack_3", FrameAnimation_DESC("blood-energy", 16, 21, Iter_2 * 2.3f, false));
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
}

void Player_Main::IdleStart(const StateInfo _Info)
{
	AvatarManager_.ChangeMotion(PlayerAnimations::Idle);
	PrevHitData_ = {};
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
	Down_Timer_.StartTimer(Value_.Down_Time);
	Force_.ForceX_ += -PrevHitData_.XForce;

	GetTransform().SetLocalMove(float4(0, Force_.ForceY_ * GameEngineTime::GetDeltaTime()));
}

void Player_Main::DownUpdate(float _DeltaTime, const StateInfo _Info)
{
	AirborneTime_ += 5.0f * _DeltaTime;
	float CurYPos = GetTransform().GetWorldPosition().y;

	//사망검사
	//if (CurHP_ == 0)
	//{
	//	//StateManager_.ChangeState("Die");
	//	return;
	//}

	if (CurYPos <= GroundYPos_)
	{
		//GroundYPos 아래로 떨어지지 않게 고정시키기
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		ShadowUpdate();
		Down_Timer_ -= _DeltaTime * (1.f + AirborneTime_ * 0.1f);
		OnAir_ = false;
		Force_.OffGravity();

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

		CurAttackData_.AttCount++;
		CurAttackData_.AttEffect = Effect::SlashSRight;
		CurAttackData_.Stiffness = 0.22f;
		CurAttackData_.RStiffness = 0.21f;
		CurAttackData_.YForce = 350.0f;
		CurAttackData_.Bleeding = 85;
		CurAttackData_.ZPos = 0;
		ShakeCamera(7.5f, 0.30f);
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

	//플레이어를 마주보는 방향으로 Flip
	//FlipX(-Player_->GetDirX());
	Force_.ForceX_ += -PrevHitData_.XForce;
}

void Player_Main::HitUpdate(float _DeltaTime, const StateInfo _Info)
{
	//사망검사
	//if (CurHP_ == 0)
	//{
	//	StateManager_.ChangeState("Die");
	//	return;
	//}
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