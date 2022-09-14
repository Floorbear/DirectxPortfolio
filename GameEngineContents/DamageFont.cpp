#include "PreCompile.h"
#include "DamageFont.h"

DamageFont::DamageFont() :
	Speed_(0.0f),
	AlphaValue_(1.0f),
	IsPlayerHitFont_(false)
{
}

DamageFont::~DamageFont()
{
}

DamageFont* DamageFont::SetDamageFont(int _Value, int _Type)
{
	int Number = _Value;
	std::vector<int> DigitsR;
	for (; Number != 0;)
	{
		int Digit = Number % 10;
		Number = Number / 10;
		DigitsR.push_back(Digit);
	}

	float MovePosX = 0.f;
	for (int i = static_cast<int>(DigitsR.size()) - 1; i >= 0; i--)
	{
		GameEngineTextureRenderer* NewFont = CreateComponent< GameEngineTextureRenderer>();
		int Digit = DigitsR[i];
		if (_Type == 0)
		{
			NewFont->SetFolderTextureToIndex("NomalDamage", Digit);
		}
		else if (_Type == 1)
		{
			NewFont->SetFolderTextureToIndex("CriticalDamage", Digit);
		}
		else if (_Type == 2)
		{
			NewFont->SetFolderTextureToIndex("PlayerHitDamage", Digit);
			IsPlayerHitFont_ = true;
		}
		else
		{
			MsgBoxAssert("Àß¸øµÈ Font Type");
		}
		NewFont->ScaleToTexture();
		MovePosX += NewFont->GetTransform().GetLocalScale().x * 0.35f;
		NewFont->GetTransform().SetLocalMove({ MovePosX,0,0 });
		MovePosX += NewFont->GetTransform().GetLocalScale().x * 0.35f;
		FontRenderer_.push_back(NewFont);
	}
	GetTransform().SetLocalMove({ -MovePosX * 0.5f,0,0 });
	GetTransform().SetLocalScale({ 1.8f,1.8f,1 });

	return this;
}

void DamageFont::Start()
{
}

void DamageFont::Update(float _DeltaTime)
{
	//
	if (GetAccTime() > GetDeathTime())
	{
		Death();
	}
	float ScaleX = GetTransform().GetLocalScale().x;
	if (ScaleX > 1.0f)
	{
		ScaleX -= _DeltaTime * 5.0f;
		float ScaleY = ScaleX;
		GetTransform().SetLocalScale({ ScaleX,ScaleY,1 });
	}
	else
	{
		Speed_ += 1000.0f * _DeltaTime;
		for (auto i : FontRenderer_)
		{
			AlphaValue_ -= _DeltaTime * 0.5f;
			if (AlphaValue_ <= 0)
			{
				AlphaValue_ = 0.0f;
			}
			i->GetPixelData().MulColor = float4{ 1.f,1.f,1.f,AlphaValue_ };
		}
		GetTransform().SetLocalMove(float4::UP * Speed_ * _DeltaTime);
	}
}

void DamageFont::End()
{
}

float DamageFont::GetDeathTime()
{
	if (IsPlayerHitFont_ = true)
	{
		return 0.5f;
	}
	return 1.0f;
}