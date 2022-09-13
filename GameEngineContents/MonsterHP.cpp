#include "PreCompile.h"
#include "DNFContentsMinimal.h"
#include "MonsterHP.h"

#include "GaugeRenderer.h"
MonsterHP::MonsterHP():
	HPFrame_(),
	Data_(),
	Value_(),
	CurID_(0),
	PlusValue_(1.0f),
	LerpValue_(0.0f),
	UIWaitingTime_(1.0f)
{
	HPBar_.reserve(30);
	HPFont_.reserve(3);
}

MonsterHP::~MonsterHP()
{
}

void MonsterHP::SetHPBar(MonsterHPData _Data)
{
	CurID_ = _Data.ID;
	//HPBar
	if (Data_[CurID_].CurHP != _Data.CurHP) //HP변화를 감지하면 변화하기 전값을 PrevHP에 저장한다.
	{
		PrevHP_[CurID_] = static_cast<float>(Data_[CurID_].CurHP);
		PlusValue_ = 1.0f;
		PlusValue_ -= 0.003f;
		LerpValue_ = 0.0f;
		if (PrevHP_[CurID_] <= 0) //PrevHP가 세팅되지 않아 0으로 설정되있는 경우, 즉 최초에는 MaxHP를 넣어준다
		{
			PrevHP_[CurID_] = static_cast<float>(_Data.MaxHP);
		}
	}

	//데이타 복사
	Data_[_Data.ID] = _Data;

	//몬스터가 죽으면 UI가 꺼지는 시간을 초기화한다.
	UIWaitingTime_ = 1.0f;

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
	//몬스터가 죽으면 잠시후에 UI가 꺼진다.
	if (Data_[CurID_].CurHP == 0)
	{
		UIWaitingTime_ -= DeltaTime_;
		if (UIWaitingTime_ <= 0)
		{
			Off();
		}
	}
	//HP바 하얗게 됬다가 어두워 지는거 파라미터 부분
	if (PlusValue_ < 1.0f && PlusValue_> -1.7f)
	{
		PlusValue_ -= DeltaTime_ * 4.5f;
	}

	//어두워진 HP바 줄어들게 하기
	if (PlusValue_ < -1.7f && LerpValue_ < 1.0f)
	{
		LerpValue_ += DeltaTime_ * 1.5f;
		PrevHP_[CurID_] = GameEngineMath::LerpLimit(PrevHP_[CurID_], static_cast<float>(Data_[CurID_].CurHP), LerpValue_);
	}

	//HP바 업데이트
	int leftHP = Data_[CurID_].CurHP;
	int PrevHP = PrevHP_[CurID_];
	int HPBarCount = 0;
	for (; leftHP > 0; 
		leftHP -= Data_[CurID_].PerHP,
		PrevHP -= Data_[CurID_].PerHP
		)
	{
		float CurHPRatio = static_cast<float>(leftHP) / static_cast<float>(Data_[CurID_].PerHP);
		float PrevHPRatio = static_cast<float>(PrevHP) / static_cast<float>(Data_[CurID_].PerHP);
		if (CurHPRatio >= 1.0f)
		{
			CurHPRatio = 1.0f;
		}
		if (PrevHPRatio >= 1.0f)
		{
			PrevHPRatio = 1.0f;
		}

		//여기까지하면 현재 체력의 Ratio, 이전 체력의 Ratio를 알 수 있다.
		//HPBar의 갯수도 기록하고 있다.

		HPBar_[HPBarCount]->On();
		float AlphaValue = PlusValue_;
		if (AlphaValue <= -1.0f)
		{
			AlphaValue += 1.0f;
			AlphaValue = -AlphaValue;
			HPBar_[HPBarCount]->GetColorData().PlusColor = { -0.5f * AlphaValue,-0.5f * AlphaValue,-0.5f * AlphaValue,0.5f };
		}
		else
		{
			HPBar_[HPBarCount]->GetColorData().PlusColor = { 1.0,1.0,1.0,AlphaValue };
		}
		
		HPBar_[HPBarCount]->UpdateMonsterHP(CurHPRatio,PrevHPRatio);
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
