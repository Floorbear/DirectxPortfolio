#include "PreCompile.h"
#include "CrazyIvan.h"

#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"

#include "MonsterHP.h"

CrazyIvan::CrazyIvan()
{
	//MaxHP_ = 3000000;
	//CurHP_ = MaxHP_;
	//PerHP_ = 900000;

	Value_.Type = MonsterType::CrazyIvanM;
	Value_.MonsterTextureSize_ = { 200.0f,200.0f,1.0f };
	Value_.DieParticleName = "DieParticleGreen";
	Value_.DieParticleSize = { 0.7f,0.7f,0.7f };
	Value_.IdleAboveColPos = { 0,0,-500.0f };
	Value_.IdleAboveColScale = { 60,47,1 };
	Value_.IdleBelowColPos = { 0,-30,-500 };
	Value_.IdleBelowColScale = { 60,47,1 };
	Value_.HitAboveColPos = { 0, 0, -500.0f };
	Value_.HitAboveColScale = { 60,47,1 };
	Value_.HitBelowColPos = { 0, -30, -500 };
	Value_.HitBelowColScale = { 60,47,1 };
	Value_.DownAboveColPos = { -25,-30,-500 };
	Value_.DownAboveColScale = { 80,20,1 };
	Value_.DownBelowColPos = { -25,-50,-500 };
	Value_.DownBelowColScale = { 80,20,1 };

	HitEffectMovePos_ = { 0,-20,0 }; //Hit파티클이 생기는 위치

	Attack_1_Pos_ = { 40.0f,-30.0f,-500.0f };
	Attack_1_Scale_ = { 120.0f,50.0f,1.0f };
	ShadowPos_ = { -10.f,-28.f,500.f,1.f };
	BotPos_ = { 0,-58.f,0 };
}

CrazyIvan::~CrazyIvan()
{
}

void CrazyIvan::Start()
{
	InitMonster();
	//StartDebug();
	StartSuperArmor(9999999.0f);
	Bleeding_Timer_.StartTimer(20.0f);
}

void CrazyIvan::Update(float _DeltaTime)
{
	UpdateMonster(_DeltaTime);
	//UpdateDebug();
}

void CrazyIvan::End()
{
}

void CrazyIvan::CreateMonsterAni()
{
	CreateDNFAnimation("Idle", FrameAnimation_DESC("crazyivan", Ivan_Idle_Start, Ivan_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("crazyivan", Ivan_Move_Start, Ivan_Move_End, AniSpeed_));
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("crazyivan", Ivan_Attack_1_Start, Ivan_Attack_1_End, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("crazyivan", Ivan_Hit_Start, Ivan_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("crazyivan", Ivan_Down_Start, Ivan_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("crazyivan", Ivan_Down_Start, Ivan_Down_Start, AniSpeed_, false));
}

void CrazyIvan::CreateMonsterAniFunc()
{
	MainRenderer_->AnimationBindFrame("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == Ivan_Attack_1_Start + 1)
			{
				//Set Attack
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "Attack_1";
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.Font = 2;
				CurAttackData_.XForce = 100.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y + BotPos_.y);
				CurAttackData_.AttEffect = Effect::SlashSHori;
				Force_.ForceX_ = 70.0f;
				AttackCol_->On();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Ivan_Attack_1_End)
			{
				//공격이 끝난 직후 로직
				IsAttack_1_End_ = true;
				Attack_1_Timer_.StartTimer();
				AttackCol_->Off();
			}
		}
	);

	MainRenderer_->AnimationBindEnd("Attack_1",
		[&](const FrameAnimation_DESC&)
		{
			//공격이 끝난 직후 로직
			IsAttack_1_End_ = true;
			Attack_1_Timer_.StartTimer();
			AttackCol_->Off();
		}
	);
}