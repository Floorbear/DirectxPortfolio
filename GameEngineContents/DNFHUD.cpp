#include "PreCompile.h"
#include "DNFHUD.h"

#include "DNFContentsMinimal.h"
#include "DNFLevel.h"
#include "DNFRenderObject.h"
#include "Player_Main.h"
#include "GaugeRenderer.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

DNFHUD::DNFHUD() :
	PrevHp_(-1),
	LerpHp_(),
	GauageDelta_HP_(),
	PrevMP_(-1),
	LerpMP_(),
	GauageDelta_MP_(),
	SkillIconBackground_(),
	Value_()
{
	SkillIconBackground_.reserve(14);
	ShortCut_.reserve(14);
}

DNFHUD::~DNFHUD()
{
}

void DNFHUD::Start()
{
	GetTransform().SetLocalMove(float4(0, 0, -1000));
	//UI렌더러
	MainRenderer_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	MainRenderer_->SetTexture("hud_frame.png");
	MainRenderer_->ScaleToTexture();
	MainRenderer_->SetPivot(PIVOTMODE::BOT);
	MainRenderer_->GetTransform().SetLocalMove(float4(0, -360));

	//HP렌더러
	HPRenderer_ = CreateComponent<GaugeRenderer>(GetNameCopy());
	HPRenderer_->SetTexture("HP.png");
	HPRenderer_->GetTransform().SetLocalScale({ 56.0f,56.0f });
	HPRenderer_->GetTransform().SetLocalMove(float4(-146, -323));

	//MP렌더러
	MPRenderer_ = CreateComponent<GaugeRenderer>(GetNameCopy());
	MPRenderer_->SetTexture("MP.png");
	MPRenderer_->GetTransform().SetLocalScale({ 56.0f,56.0f });
	MPRenderer_->GetTransform().SetLocalMove(float4(146, -323));

	//스킬 아이콘 백그라운드
	Value_.SkillIconBackPos = { -100,-308 };
	for (size_t i = 0; i < 14; i++)
	{
		GameEngineUIRenderer* NewSkillIcon = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
		NewSkillIcon->SetTexture("SkillBack.png");
		NewSkillIcon->ScaleToTexture();
		NewSkillIcon->SetPivot(PIVOTMODE::CENTER);
		SkillIconBackground_.push_back(NewSkillIcon);
	}

	//스킬 아이콘
	Value_.SkillIconPos = { -100,-308 };
	SkillRendererInit();

	//스킬 숏컷 백그라운드
	Value_.ShortCutPos = { -100,-308 };
	for (size_t i = 0; i < 14; i++)
	{
		GameEngineUIRenderer* NewShortCutIcon = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
		NewShortCutIcon->SetFolderTextureToIndex("SkillShortCut", static_cast<UINT>(i));
		NewShortCutIcon->ScaleToTexture();
		NewShortCutIcon->SetPivot(PIVOTMODE::CENTER);
		ShortCut_.push_back(NewShortCutIcon);
	}
}

void DNFHUD::Update(float _DeltaTime)
{
	if (DNFGlobalValue::CurrentLevel == nullptr)
	{
		return;
	}

	IconPosUpdate(_DeltaTime);
	HPBarUpdate(_DeltaTime);
	MPBarUpdate(_DeltaTime);
	SkillIconUpdate(_DeltaTime);
}

void DNFHUD::HPBarUpdate(float _DeltaTime)
{
	Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
	float MaxHP = static_cast<float>(Player->GetMaxHP());
	float CurHP = static_cast<float>(Player->GetCurHP());

	//가장 최초 HP 셋팅
	if (PrevHp_ == -1)
	{
		PrevHp_ = Player->GetCurHP();
		LerpHp_ = CurHP;
	}

	//HP 변화 감지
	if (PrevHp_ != CurHP)
	{
		GauageDelta_HP_ += _DeltaTime;
		LerpHp_ = (GameEngineMath::LerpLimit(static_cast<float>(PrevHp_), CurHP, GauageDelta_HP_));
	}

	if (static_cast<int>(LerpHp_) == CurHP)
	{
		GauageDelta_HP_ = 0.f;
		PrevHp_ = Player->GetCurHP();
		LerpHp_ = CurHP;
	}

	float ratio = LerpHp_ / MaxHP;
	HPRenderer_->UpdateGauge(ratio);
}

void DNFHUD::MPBarUpdate(float _DeltaTime)
{
	Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
	float MaxMP = static_cast<float>(Player->GetMaxMP());
	float CurMP = static_cast<float>(Player->GetCurMP());

	//가장 최초 HP 셋팅
	if (PrevMP_ == -1)
	{
		PrevMP_ = Player->GetCurMP();
		LerpMP_ = CurMP;
	}

	//HP 변화 감지
	if (PrevMP_ != CurMP)
	{
		GauageDelta_MP_ += _DeltaTime;
		LerpMP_ = (GameEngineMath::LerpLimit(static_cast<float>(PrevMP_), CurMP, GauageDelta_MP_));
	}

	if (static_cast<int>(LerpMP_) == CurMP)
	{
		GauageDelta_MP_ = 0.f;
		PrevMP_ = Player->GetCurMP();
		LerpMP_ = CurMP;
	}

	float ratio = LerpMP_ / MaxMP;
	MPRenderer_->UpdateGauge(ratio);
}

void DNFHUD::IconPosUpdate(float _DeltaTime)
{
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			float4 AddPos = float4(static_cast<float>(j) * 32, static_cast<float>(i) * -32, 0) + Value_.SkillIconBackPos;
			SkillIconBackground_[j + (i * 7)]->GetTransform().SetLocalPosition(AddPos);
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			float4 AddPos = float4(static_cast<float>(j) * 32, static_cast<float>(i) * -32, 0) + Value_.SkillIconPos;
			SkillIcon_[j + (i * 7)]->GetTransform().SetLocalPosition(AddPos);
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			float4 AddPos = float4(static_cast<float>(j) * 32, static_cast<float>(i) * -32, 0) + Value_.ShortCutPos;
			ShortCut_[j + (i * 7)]->GetTransform().SetLocalPosition(AddPos);
		}
	}
}

void DNFHUD::SkillRendererInit()
{
	for (size_t i = 0; i < 14; i++)
	{
		GaugeRenderer* NewSkillIcon = CreateComponent<GaugeRenderer>(GetNameCopy());
		NewSkillIcon->Off();
		NewSkillIcon->SetGauge(1);
		//NewSkillIcon->SetTexture("SkillBack.png");
		//NewSkillIcon->ScaleToTexture();
		//NewSkillIcon->SetPivot(PIVOTMODE::CENTER);
		SkillIcon_.push_back(NewSkillIcon);
	}

	SkillIcon_[13]->On();
	SkillIcon_[13]->SetTexture("UpperSlash.png");
	SkillIcon_[13]->GetTransform().SetLocalScale({ 28,28 });
}

void DNFHUD::SkillIconUpdate(float _DeltaTime)
{
	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();

		//어퍼슬래쉬
		std::map<std::string, Timer*> CoolTimeMap = Player->GetSkillCoolTimeList();
		if (CoolTimeMap["UpperSlash"]->IsTimerOn() == true) //쿨타임 도는 것을 보여준다.
		{
			SkillIcon_[13]->SetTexture("UpperSlashCool.png");
			float MaxTime = CoolTimeMap["UpperSlash"]->Default_Time_;
			float CurTime = *CoolTimeMap["UpperSlash"]->GetIterTime();
			float ratio = CurTime / MaxTime;
			float4 Black = { 0.f,0.f,0.f,1.0f };
			SkillIcon_[13]->UpdateGauegeColor(ratio, Black);
		}
		else
		{
			if (CoolTimeMap["UpperSlash"]->IsSet == true) //쿨타임이 다 돌면 스킬아이콘이 번쩍이게 한다.
			{
				SkillIcon_[13]->GetColorData().PlusColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
				FlashSkillIcon_.push_back(SkillIcon_[13]);
				CoolTimeMap["UpperSlash"]->IsSet = false;
			}
			SkillIcon_[13]->SetTexture("UpperSlash.png");
		}

		std::list<GaugeRenderer*>::iterator StartIter = FlashSkillIcon_.begin();
		for (; StartIter != FlashSkillIcon_.end(); StartIter++)
		{
			(*StartIter)->GetColorData().PlusColor -= _DeltaTime * 1.4f;
			(*StartIter)->GetColorData().PlusColor.a -= _DeltaTime * 1.4f;
			if ((*StartIter)->GetColorData().PlusColor.a < 0.02f)
			{
				(*StartIter)->GetColorData().PlusColor = float4::ZERO;
				FlashSkillIcon_.erase(StartIter);
				break;
			}
		}
	}
}