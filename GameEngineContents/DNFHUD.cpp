#include "PreCompile.h"
#include "DNFHUD.h"

#include "DNFContentsMinimal.h"
#include "DNFLevel.h"
#include "DNFRenderObject.h"
#include "Player_Main.h"
#include "GaugeRenderer.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

#define Outragebreak_Icon 1
#define Fury_Icon 2
#define ExtremOverkill_Icon 3
#define QuickStanding_Icon 6
#define GoreCross_Icon 7
#define HopSmash_Icon 8
#define TripleSlash_Icon 9
#define Frenzy_Icon 10
#define UpperSlash_Icon 13

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

	//SkillRendererInit 에도 추가 스킬 코드 작성해주세요
	StringToInt_.insert(std::make_pair("UpperSlash", UpperSlash_Icon));
	StringToInt_.insert(std::make_pair("GoreCross", GoreCross_Icon));
	StringToInt_.insert(std::make_pair("HopSmash", HopSmash_Icon));
	StringToInt_.insert(std::make_pair("QuickStanding", QuickStanding_Icon));

	StringToInt_.insert(std::make_pair("Frenzy", Frenzy_Icon));
	StringToInt_.insert(std::make_pair("Fury", Fury_Icon));
	StringToInt_.insert(std::make_pair("Outragebreak", Outragebreak_Icon));
	StringToInt_.insert(std::make_pair("ExtremOverkill", ExtremOverkill_Icon));
	StringToInt_.insert(std::make_pair("TripleSlash", TripleSlash_Icon));
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

	//빨간 글씨 백그라운드
	Value_.ShortCutPos = { -100,-308 };
	for (size_t i = 0; i < 14; i++)
	{
		GameEngineUIRenderer* NewShortCutIcon = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
		NewShortCutIcon->SetFolderTextureToIndex("SkillShortCut", static_cast<UINT>(i));
		NewShortCutIcon->ScaleToTexture();
		NewShortCutIcon->SetPivot(PIVOTMODE::CENTER);
		ShortCut_.push_back(NewShortCutIcon);
	}

	//컷신
	//윈도우 사이즈는 { 1280.0f, 720.0f }
	CutScene_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	CutScene_->SetTexture("CutScene.png");
	CutScene_->SetScaleRatio(1.2f);
	CutScene_->ScaleToTexture();
	CutScene_->SetPivot(PIVOTMODE::LEFTBOT);
	CutScene_->GetTransform().SetLocalMove(float4(-640.f - CutScene_->GetTransform().GetLocalScale().x, -360));
	CutScene_->Off();

	RootPos_ = CutScene_->GetTransform().GetLocalPosition();
	DestPos_ = RootPos_;
	DestPos_.x += CutScene_->GetTransform().GetLocalScale().x;

	//엔딩
	EndingRenderer_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	EndingRenderer_->SetTexture("Ending.png");
	EndingRenderer_->ScaleToTexture();
	EndingRenderer_->GetTransform().SetLocalMove({ 0,0,-1500 });
	EndingRenderer_->Off();

	//코인
	Coin_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	Coin_->SetTexture("Coin.png");
	Coin_->SetScaleRatio(1.4f);
	Coin_->ScaleToTexture();
	Coin_->GetTransform().SetLocalMove({ 0,0,-500 });
	Coin_->Off();
}

void DNFHUD::Update(float _DeltaTime)
{
	if (DNFGlobalValue::CurrentLevel == nullptr)
	{
		return;
	}
	if (EndingTimer_.IsTimerOn() == true)
	{
		EndingTimer_.Update(_DeltaTime);
		if (EndingTimer_.IsTimerOn() == false)
		{
			DNFGlobalValue::Bgm_.Stop();
			GameEngineSound::SoundPlayOneShot("result.ogg");
			EndingRenderer_->On();
		}
	}
	Player_Main* Player = DNFGlobalValue::CurrentPlayer_;
	if (Player->StateManager_.GetCurStateStateName() == "Die")
	{
		Coin_->On();
	}
	else
	{
		Coin_->Off();
	}
	CutSceneUpdate(_DeltaTime);
	IconPosUpdate(_DeltaTime);
	HPBarUpdate(_DeltaTime);
	MPBarUpdate(_DeltaTime);
	SkillIconUpdate(_DeltaTime);
}

void DNFHUD::CutSceneUpdate(float _DeltaTime)
{
	//각성기 컷신 Update
	Player_Main* Player = DNFGlobalValue::CurrentPlayer_;
	if (Player->StateManager_.GetCurStateStateName() == "ExtremOverkill")
	{
		CutScene_->On();
		CutSceneAccTime_ += _DeltaTime;
		if (CutSceneAccTime_ < 1.0f)
		{
			float4 CutScenePos = float4::LerpLimit(RootPos_, DestPos_, CutSceneAccTime_ * 4.f);
			CutScene_->GetTransform().SetLocalPosition(CutScenePos);
		}
		else if (CutSceneAccTime_ >= 2.0f && CutSceneAccTime_ <= 3.0f)
		{
			float CurTime = CutSceneAccTime_ - 2.0f;
			float4 CutScenePos = float4::LerpLimit(DestPos_, RootPos_, CurTime * 4.f);
			CutScene_->GetTransform().SetLocalPosition(CutScenePos);
		}
	}
	else
	{
		CutScene_->Off();
		CutSceneAccTime_ = 0.f;
	}
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
	SkillIcon_[QuickStanding_Icon]->On();
	SkillIcon_[QuickStanding_Icon]->SetTexture("QuickStanding.png");
	SkillIcon_[QuickStanding_Icon]->GetTransform().SetLocalScale({ 28,28 });

	SkillIcon_[Outragebreak_Icon]->On();
	SkillIcon_[Outragebreak_Icon]->SetTexture("Outragebreak.png");
	SkillIcon_[Outragebreak_Icon]->GetTransform().SetLocalScale({ 28,28 });

	SkillIcon_[TripleSlash_Icon]->On();
	SkillIcon_[TripleSlash_Icon]->SetTexture("TripleSlash.png");
	SkillIcon_[TripleSlash_Icon]->GetTransform().SetLocalScale({ 28,28 });

	SkillIcon_[ExtremOverkill_Icon]->On();
	SkillIcon_[ExtremOverkill_Icon]->SetTexture("ExtremOverkill.png");
	SkillIcon_[ExtremOverkill_Icon]->GetTransform().SetLocalScale({ 28,28 });

	SkillIcon_[Fury_Icon]->On();
	SkillIcon_[Fury_Icon]->SetTexture("Fury.png");
	SkillIcon_[Fury_Icon]->GetTransform().SetLocalScale({ 28,28 });

	SkillIcon_[UpperSlash_Icon]->On();
	SkillIcon_[UpperSlash_Icon]->SetTexture("UpperSlash.png");
	SkillIcon_[UpperSlash_Icon]->GetTransform().SetLocalScale({ 28,28 });

	SkillIcon_[GoreCross_Icon]->On();
	SkillIcon_[GoreCross_Icon]->SetTexture("GoreCross.png");
	SkillIcon_[GoreCross_Icon]->GetTransform().SetLocalScale({ 28,28 });

	SkillIcon_[HopSmash_Icon]->On();
	SkillIcon_[HopSmash_Icon]->SetTexture("HopSmash.png");
	SkillIcon_[HopSmash_Icon]->GetTransform().SetLocalScale({ 28,28 });

	SkillIcon_[Frenzy_Icon]->On();
	SkillIcon_[Frenzy_Icon]->SetTexture("Frenzy.png");
	SkillIcon_[Frenzy_Icon]->GetTransform().SetLocalScale({ 28,28 });
}

void DNFHUD::SkillIconUpdate(float _DeltaTime)
{
	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();

		//어퍼슬래쉬
		std::map<std::string, Timer*> CoolTimeMap = Player->GetSkillCoolTimeList();
		for (auto i : CoolTimeMap)
		{
			if (CoolTimeMap[i.first]->IsTimerOn() == true) //쿨타임 도는 것을 보여준다.
			{
				SkillIcon_[StringToInt_[i.first]]->SetTexture(i.first + "Cool.png");
				float MaxTime = CoolTimeMap[i.first]->Default_Time_;
				float CurTime = *CoolTimeMap[i.first]->GetIterTime();
				float ratio = CurTime / MaxTime;
				float4 Black = { 0.f,0.f,0.f,1.0f };
				SkillIcon_[StringToInt_[i.first]]->UpdateGauegeColor(ratio, Black);
			}
			else
			{
				if (CoolTimeMap[i.first]->IsSet == true) //쿨타임이 다 돌면 스킬아이콘이 번쩍이게 한다.
				{
					SkillIcon_[StringToInt_[i.first]]->GetColorData().PlusColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
					FlashSkillIcon_.push_back(SkillIcon_[StringToInt_[i.first]]);
					CoolTimeMap[i.first]->IsSet = false;
				}
				SkillIcon_[StringToInt_[i.first]]->SetTexture(i.first + ".png");
			}
		}
		//if (CoolTimeMap["UpperSlash"]->IsTimerOn() == true) //쿨타임 도는 것을 보여준다.
		//{
		//	SkillIcon_[UpperSlash_Icon]->SetTexture("UpperSlashCool.png");
		//	float MaxTime = CoolTimeMap["UpperSlash"]->Default_Time_;
		//	float CurTime = *CoolTimeMap["UpperSlash"]->GetIterTime();
		//	float ratio = CurTime / MaxTime;
		//	float4 Black = { 0.f,0.f,0.f,1.0f };
		//	SkillIcon_[UpperSlash_Icon]->UpdateGauegeColor(ratio, Black);
		//}
		//else
		//{
		//	if (CoolTimeMap["UpperSlash"]->IsSet == true) //쿨타임이 다 돌면 스킬아이콘이 번쩍이게 한다.
		//	{
		//		SkillIcon_[UpperSlash_Icon]->GetColorData().PlusColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
		//		FlashSkillIcon_.push_back(SkillIcon_[13]);
		//		CoolTimeMap["UpperSlash"]->IsSet = false;
		//	}
		//	SkillIcon_[UpperSlash_Icon]->SetTexture("UpperSlash.png");
		//}

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