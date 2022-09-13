#include "PreCompile.h"
#include "DNFContentsMinimal.h"
#include "MonsterHP.h"

#include "GaugeRenderer.h"
MonsterHP::MonsterHP():
	HPFrame_(),
	Data_(),
	Value_(),
	CurID_(0)
{
	HPBar_.reserve(30);
	HPFont_.reserve(3);
}

MonsterHP::~MonsterHP()
{
}

void MonsterHP::SetHPBar(MonsterHPData _Data)
{
	Data_[_Data.ID] = _Data;
	CurID_ = _Data.ID;

	//여기서 HPBar을 전부 Reset해야 한다.
	ResetHP();

}

void MonsterHP::Start()
{
	GetTransform().SetLocalMove(Value_.UIPos);
	HPFrame_ = CreateComponent<GameEngineUIRenderer>();
	HPFrame_->SetFolderTextureToIndex("MonsterHP", 0);
	HPFrame_->SetScaleRatio(1.5f);
	HPFrame_->ScaleToTexture();
	HPFrame_->SetPivot(PIVOTMODE::LEFTTOP);
	HPFrame_->GetTransform().SetLocalMove(float4(0, 0));

	//HP바 생성
	for (int i = 0; i < 30; i++)
	{
		GaugeRenderer* NewHPBar = CreateComponent<GaugeRenderer>();
		int index = (i % 5) + 1;
		NewHPBar->SetFolderTextureToIndex("MonsterHP", index);
		NewHPBar->SetScaleRatio(1.5f);
		NewHPBar->ScaleToTexture();
		NewHPBar->GetTransform().SetLocalPosition(Value_.HPBarPos);
		NewHPBar->SetGauge(2);
		NewHPBar->Off();
		HPBar_.push_back(NewHPBar);
	}

	//HP 폰트 생성
	for (int i = 0; i < 3; i++)
	{
		GameEngineUIRenderer* NewFontImage = CreateComponent<GameEngineUIRenderer>();
		HPFont_.push_back(NewFontImage);
	}
	{
		HPFont_[0]->SetFolderTextureToIndex("MonsterHP", 16);
		HPFont_[0]->ScaleToTexture();
		HPFont_[0]->SetPivot(PIVOTMODE::RIGHTBOT);
		HPFont_[0]->GetTransform().SetLocalPosition(Value_.HPFontPos_0);

		HPFont_[1]->SetFolderTextureToIndex("MonsterHP", 6);
		HPFont_[1]->ScaleToTexture();
		HPFont_[1]->SetPivot(PIVOTMODE::RIGHTBOT);
		HPFont_[1]->GetTransform().SetLocalPosition(Value_.HPFontPos_1);

		HPFont_[2]->SetFolderTextureToIndex("MonsterHP", 6);
		HPFont_[2]->ScaleToTexture();
		HPFont_[2]->SetPivot(PIVOTMODE::RIGHTBOT);
		HPFont_[2]->GetTransform().SetLocalPosition(Value_.HPFontPos_2);

		for (int i = 0; i < 3; i++)
		{
			HPFont_[i]->Off();
		}
	}
	//DNFDebugGUI::AddMutableValue("HP",&Data_.CurHP);

}

void MonsterHP::Update(float DeltaTime_)
{
	float leftHP = Data_[CurID_].CurHP;
	//HP바 실시간 연동
	int HPBarCount = 0;
	for (; leftHP > 0; leftHP -= Data_[CurID_].PerHP)
	{
		float CurHPRatio = leftHP / Data_[CurID_].PerHP;
		if (CurHPRatio >= 1.0f)
		{
			CurHPRatio = 1.0f;
		}
		HPBar_[HPBarCount]->On();
		HPBar_[HPBarCount]->UpdateGauge(CurHPRatio);
		HPBarCount++;
	}
	HPBarCount--;

	//HP바 폰트 업데이트
	for (int j = 0; j < 3; j++)
	{
		HPFont_[j]->Off();
	}
	if (HPBarCount > 0)
	{
		HPFont_[0]->On();
		HPFont_[1]->On();
		if (HPBarCount >= 10)
		{
			HPFont_[2]->On();
			int DigitFront = (HPBarCount / 10);
			int DigitBack = (HPBarCount % 10);
			HPFont_[1]->SetFolderTextureToIndex("MonsterHP", (DigitFront % 10) + 6);
			HPFont_[2]->SetFolderTextureToIndex("MonsterHP", (DigitBack % 10) + 6);
		}
		else
		{
			HPFont_[1]->SetFolderTextureToIndex("MonsterHP", (HPBarCount % 10) + 6);
		}
	}

}

void MonsterHP::End()
{
}

void MonsterHP::ResetHP()
{
	for (int i = 0; i < 30; i++)
	{
		HPBar_[i]->Off();
	}

	for (auto i : HPFont_)
	{
		i->Off();
	}
}
