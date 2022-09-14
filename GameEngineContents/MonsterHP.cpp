#include "PreCompile.h"
#include "DNFContentsMinimal.h"
#include "MonsterHP.h"

#include "GaugeRenderer.h"
MonsterHP::MonsterHP() :
	HPFrame_(),
	Data_(),
	Value_(),
	CurID_(0),
	PlusValue_(1.0f),
	LerpValue_(0.0f),
	UIWaitingTime_(1.8f),
	MonsterHead_(),
	MonsterDead_(),
	DeadHeadTime_(Value_.DeadHeadTime),
	MonsterCategory_()
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

	CheckType(_Data.Type);

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
	//폰트 이미지 Set
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

	//몬스터 초상화 & Dead 초상화 Set
	{
		MonsterHead_ = CreateComponent<GameEngineUIRenderer>();
		MonsterHead_->SetPivot(PIVOTMODE::LEFTTOP);
		MonsterHead_->GetTransform().SetLocalPosition(Value_.MonsterHeadPos);
		MonsterHead_->Off();

		MonsterDead_ = CreateComponent<GameEngineUIRenderer>();
		MonsterDead_->SetFolderTextureToIndex("MonsterHead", 0);
		MonsterDead_->ScaleToTexture();
		MonsterDead_->SetPivot(PIVOTMODE::LEFTTOP);
		MonsterDead_->GetTransform().SetLocalPosition(Value_.MonsterHeadPos);
		MonsterDead_->Off();
	}

	//몬스터 카테고리
	{
		MonsterCategory_ = CreateComponent<GameEngineUIRenderer>();
		MonsterCategory_->SetScaleRatio(1.5f);
		MonsterCategory_->SetPivot(PIVOTMODE::LEFTTOP);
		MonsterCategory_->GetTransform().SetLocalPosition(Value_.CategoryPos);
	}

	//DNFDebugGUI::AddMutableValue("Pos", &Value_.CategoryPos);
}
void MonsterHP::End()
{
}

void MonsterHP::Update(float DeltaTime_)
{
	MonsterDeadCheck(DeltaTime_);
	HPBarUpdate(DeltaTime_);
}
void MonsterHP::MonsterDeadCheck(float _DeltaTime)
{
	//몬스터가 죽으면 잠시후에 UI가 꺼진다.
	if (Data_[CurID_].CurHP == 0)
	{
		UIWaitingTime_ -= _DeltaTime;
		SwitchDeadHead(_DeltaTime);
		if (UIWaitingTime_ <= 0)
		{
			Off();
		}
	}
}
void MonsterHP::SwitchDeadHead(float _DeltaTime)
{
	DeadHeadTime_ -= _DeltaTime;
	if (DeadHeadTime_ < 0.0f)
	{
		MonsterDead_->OnOffSwitch();
		DeadHeadTime_ = Value_.DeadHeadTime;
	}
}

void MonsterHP::HPBarUpdate(float DeltaTime_)
{
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

		HPBar_[HPBarCount]->UpdateMonsterHP(CurHPRatio, PrevHPRatio);
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
void MonsterHP::ResetHP()
{
	//몬스터가 죽으면 UI가 꺼지는 시간을 초기화한다.
	UIWaitingTime_ = 1.8f;

	MonsterDead_->Off();
	DeadHeadTime_ = Value_.DeadHeadTime;

	for (int i = 0; i < 30; i++)
	{
		HPBar_[i]->Off();
	}

	for (auto i : HPFont_)
	{
		i->Off();
	}
}

void MonsterHP::CheckType(MonsterType _Type)
{
	switch (_Type)
	{
	case BloodLugaruM:
		MonsterHead_->SetFolderTextureToIndex("MonsterHead", 1);
		MonsterHead_->ScaleToTexture();
		MonsterHead_->On();

		MonsterCategory_->SetFolderTextureToIndex("Category", 1);
		MonsterCategory_->ScaleToTexture();
		break;
	default:
		break;
	}
}