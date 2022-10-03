#include "PreCompile.h"
#include "Bloodlugaru.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "DNFContentsMinimal.h"

#include "MonsterHP.h"
#include "Player_Main.h"

Bloodlugaru::Bloodlugaru() :
	Attack_2_Wait_Timer_(),
	Attack_2_TargetPos_(),
	LugaruValue()
{
	Value_.Type = MonsterType::BloodLugaruM;
	Value_.DieParticleName = "DieParticleRed";
	Value_.DieParticleSize = { 0.7f,0.7f,0.7f };
	FindRange_ = 550.0f;
}

Bloodlugaru::~Bloodlugaru()
{
}

void Bloodlugaru::Start()
{
	//�簡�� �ؽ�ó �ε�
	if (GameEngineFolderTexture::Find("bloodlugaru") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("MonsterTexture");
		Dir.Move("bloodlugaru");
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
	InitMonster();

	Value_.BleedingPos.y -= 50.0f;

	//���� �ʱ�ȭ
	SetHitSound("bloodgaru_dmg_0", 2, 1.5f);
	DieSound_ = "bloodgaru_slayer.wav";

	//���� �߰�
	{
		DNFTransition Attack_2;
		Attack_2.AddValue("Idle", -1);
		Transition_.insert(std::make_pair("Attack_2", Attack_2));
	}
	//State�߰�
	StateManager_.CreateStateMember("Attack_2", std::bind(&Bloodlugaru::Attack_2_Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Bloodlugaru::Attack_2_Start, this, std::placeholders::_1),
		std::bind(&Bloodlugaru::Attack_2_End, this, std::placeholders::_1));
}

void Bloodlugaru::Update(float _DeltaTime)
{
	UpdateMonster(_DeltaTime);
	if (Attack_2_Timer_.IsTimerOn() == true)
	{
		Attack_2_Timer_.Update(_DeltaTime);
	}
}

void Bloodlugaru::End()
{
}

void Bloodlugaru::Attack_2_Start(const StateInfo _Info)
{
	//Flip Check
	float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
	float4 thisPos = GetTransform().GetWorldPosition();
	float4 MoveDir = PlayerPos - thisPos;
	MoveDir.z = 0;
	MoveDir.Normalize();
	if (MoveDir.x > 0)
	{
		GetTransform().PixLocalPositiveX();
	}
	else
	{
		GetTransform().PixLocalNegativeX();
	}

	GameEngineSound::SoundPlayControl("clawA_01.wav");

	//TargetPos Set
	Attack_2_TargetPos_ = PlayerPos;
	GroundYPos_ = PlayerPos.y;

	ChangeDNFAnimation("Attack_2_Wait");
	Attack_2_Wait_Timer_.StartTimer(0.35f);
}

void Bloodlugaru::Attack_2_Update(float _DeltaTime, const StateInfo _Info)
{
	//���� ���� �� �غ���
	Attack_2_Wait_Timer_.Update(_DeltaTime);
	if (Attack_2_Wait_Timer_.IsTimerOn() == true)
	{
		return;
	}
	else
	{
		if (Attack_2_Wait_Timer_.IsSet == false) //�غ��ڼ��� ���ϰ� �����ϱ� ���� ����
		{
			Attack_2_Wait_Timer_.IsSet = true;

			//������ ���� ��
			float4 thisPos = GetTransform().GetWorldPosition();
			float ForceX = abs(Attack_2_TargetPos_.x - thisPos.x);
			Force_.ForceX_ = ForceX * LugaruValue.Attack_2_ForceXAcc;

			//������
			Force_.FrictionX_ = ForceX * LugaruValue.Attack_2_FrctionAcc;

			//���� �ϴ� ��
			Force_.ForceY_ = LugaruValue.Attack_2_ForceY;
			GroundYPos_ = Attack_2_TargetPos_.y;
			StartYForce();
			ChangeDNFAnimation("Attack_2");
			return;
		}
	}

	//���⼭ ���� �����Ϸ��� �پ������ ����
	float4 CurPos = GetTransform().GetWorldPosition();
	if (CurPos.y <= GroundYPos_)
	{
		if (Force_.ForceY_ >= 0) //���� ���� �������
		{
			return;
		}
		GetTransform().SetWorldPosition(float4(GetTransform().GetWorldPosition().x, GroundYPos_, GroundYPos_));
		OnAir_ = false;
		Force_.OffGravity();
		StateManager_.ChangeState(Transition_["Attack_2"].Decide());
		return;
	}
}

void Bloodlugaru::Attack_2_End(const StateInfo _Info)
{
	OnAir_ = false;
	Force_.OffGravity();
	Force_.FrictionX_ = Value_.Default_Frction;
	AttackCol_->Off();
	CurAttackData_ = {};
}

void Bloodlugaru::CreateMonsterAni()
{
	CreateDNFAnimation("Idle", FrameAnimation_DESC("bloodlugaru", Lugaru_Idle_Start, Lugaru_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("bloodlugaru", Lugaru_Move_Start, Lugaru_Move_End, AniSpeed_));
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("bloodlugaru", Lugaru_Attack_1_Start, Lugaru_Attack_1_End, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("bloodlugaru", Lugaru_Hit_Start, Lugaru_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("bloodlugaru", Lugaru_Down_Start, Lugaru_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("bloodlugaru", Lugaru_Down_Start, Lugaru_Down_Start, AniSpeed_, false));

	CreateDNFAnimation("Attack_2_Wait", FrameAnimation_DESC("bloodlugaru", Lugaru_Attack_2_Wait_Start, Lugaru_Attack_2_Wait_End, AniSpeed_, false));
	CreateDNFAnimation("Attack_2", FrameAnimation_DESC("bloodlugaru", Lugaru_Attack_2_Start, Lugaru_Attack_2_End, AniSpeed_, false));
}

void Bloodlugaru::CreateMonsterAniFunc()
{
	MainRenderer_->AnimationBindFrame("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_Start + 1)
			{
				GameEngineSound::SoundPlayControl("clawA_01.wav");
				//Set Attack
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "Attack_1";
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.Font = 2;
				CurAttackData_.XForce = 100.0f;
				//CurAttackData_.YForce = 300.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttackSound = "clawA_hit_01.wav";
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttEffect = Effect::SlashSHori;
				Force_.ForceX_ = 70.0f;
				AttackCol_->On();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_Start + 3)
			{
				GameEngineSound::SoundPlayControl("clawA_01.wav");
				CurAttackData_.AttCount++;
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_End)
			{
				//������ ���� ���� ����
				IsAttack_1_End_ = true;
				Attack_1_Timer_.StartTimer();
				AttackCol_->Off();
			}
		}
	);

	MainRenderer_->AnimationBindFrame("Attack_2",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_2_Start + 1)
			{
				//Set Attack
				CurAttackData_.Type = AttackType::Above;
				CurAttackData_.AttackName = "Attack_2";
				CurAttackData_.Att = CalAtt(LugaruValue.Attack_2_Att);
				CurAttackData_.Font = 2;
				CurAttackData_.XForce = 100.0f;
				//CurAttackData_.YForce = 300.0f;
				CurAttackData_.AttackSound = "clawA_hit_01.wav";
				CurAttackData_.Stiffness = 0.35f;
				CurAttackData_.RStiffness = 0.21f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = 0;
				CurAttackData_.AttEffect = Effect::SlashSLeft;
				Force_.ForceX_ = 70.0f;
				AttackCol_->On();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_2_Start + 3)
			{
				AttackCol_->Off();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_2_End)
			{
				//������ ���� ���� ����
				/*IsAttack_1_End_ = true;
				Attack_1_Timer_.StartTimer();*/
			}
		}
	);
}

std::string Bloodlugaru::CheckAdditionalPattern(float _DeltaTime)
{
	if (Attack_2_Timer_.IsTimerOn() == false)
	{
		Attack_2_Timer_.StartTimer(LugaruValue.Attack_2_CoolTime);

		//������ ���� ��
		float4 PlayerPos = Player_->GetTransform().GetWorldPosition();
		float4 thisPos = GetTransform().GetWorldPosition();

		float XLength = abs(PlayerPos.x - thisPos.x);
		float YLength = abs(PlayerPos.y - thisPos.y);

		if (XLength >= LugaruValue.Attack_2_StartRange.x || YLength >= LugaruValue.Attack_2_StartRange.y)
		{
			return "";
		}
		//�����Ÿ� ���� ��� ������ Ȯ�� 60����
		float RandomValue = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);
		if (RandomValue < 0.6f)
		{
			return "Attack_2";
		}
	}
	return "";
}