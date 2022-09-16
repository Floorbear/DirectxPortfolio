#include "PreCompile.h"
#include "Bloodlugaru.h"

#include <GameEngineCore/GameEngineCollision.h>
#include "DNFContentsMinimal.h"

#include "MonsterHP.h"

Bloodlugaru::Bloodlugaru()
{
	Value_.Type = MonsterType::BloodLugaruM;
	Value_.DieParticleName = "DieParticleRed";
	Value_.DieParticleSize = { 0.7f,0.7f,0.7f };
}

Bloodlugaru::~Bloodlugaru()
{
}

void Bloodlugaru::Start()
{
	InitMonster();
}

void Bloodlugaru::Update(float _DeltaTime)
{
	UpdateMonster(_DeltaTime);
}

void Bloodlugaru::End()
{
}

void Bloodlugaru::CreateMonsterAni()
{
	CreateDNFAnimation("Idle", FrameAnimation_DESC("bloodlugaru", Lugaru_Idle_Start, Lugaru_Idle_End, AniSpeed_));
	CreateDNFAnimation("Move", FrameAnimation_DESC("bloodlugaru", Lugaru_Move_Start, Lugaru_Move_End, AniSpeed_));
	CreateDNFAnimation("Attack_1", FrameAnimation_DESC("bloodlugaru", Lugaru_Attack_1_Start, Lugaru_Attack_1_End, AniSpeed_, false));
	CreateDNFAnimation("Hit", FrameAnimation_DESC("bloodlugaru", Lugaru_Hit_Start, Lugaru_Hit_End, AniSpeed_, false));
	CreateDNFAnimation("Down", FrameAnimation_DESC("bloodlugaru", Lugaru_Down_Start, Lugaru_Down_End, AniSpeed_, false));
	CreateDNFAnimation("Die", FrameAnimation_DESC("bloodlugaru", Lugaru_Down_Start, Lugaru_Down_Start, AniSpeed_, false));
}

void Bloodlugaru::CreateMonsterAniFunc()
{
	MainRenderer_->AnimationBindFrame("Attack_1",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_Start + 1)
			{
				//Set Attack
				CurAttackData_.Type = AttackType::Below;
				CurAttackData_.AttackName = "Attack_1";
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.Font = 2;
				CurAttackData_.XForce = 100.0f;
				//CurAttackData_.YForce = 300.0f;
				CurAttackData_.Stiffness = 0.15f;
				CurAttackData_.RStiffness = 0.11f;
				CurAttackData_.AttCount = 0;
				CurAttackData_.AttCount++;
				CurAttackData_.ZPos = static_cast<int>(GetTransform().GetWorldPosition().y) + BotPos_.y;
				CurAttackData_.AttEffect = Effect::SlashSHori;
				Force_.ForceX_ = 70.0f;
				AttackCol_->On();
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_Start + 3)
			{
				CurAttackData_.AttCount++;
				CurAttackData_.Att = CalAtt(Value_.Attack_1_Att);
				CurAttackData_.AttEffect = Effect::SlashSRight;
			}
			else if (_Desc.Frames[_Desc.CurFrame - 1] == Lugaru_Attack_1_End)
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
		}
	);
}