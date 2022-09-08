#include "PreCompile.h"
#include "DamageFont.h"

DamageFont::DamageFont()
{
}

DamageFont::~DamageFont()
{
}

DamageFont* DamageFont::SetDamageFont(int _Value, bool IsCriticalDamage)
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
	for (int i = static_cast<int>(DigitsR.size()) - 1; i >= 0;i--)
	{
		GameEngineTextureRenderer* NewFont = CreateComponent< GameEngineTextureRenderer>();
		int Digit = DigitsR[i];
		if (IsCriticalDamage == true)
		{
			NewFont->SetFolderTextureToIndex("CriticalDamage", Digit);

		}
		else
		{
			NewFont->SetFolderTextureToIndex("NomalDamage", Digit);
		}
		NewFont->ScaleToTexture();
		MovePosX += NewFont->GetTransform().GetLocalScale().x * 0.35f;
		NewFont->GetTransform().SetLocalMove({ MovePosX,0,0 });
		MovePosX += NewFont->GetTransform().GetLocalScale().x * 0.35f;
		FontRenderer_.push_back(NewFont);
		NewFont->Death(1.0f); //나중에 한번에 죽여
	}
	

	return this;
}

void DamageFont::Start()
{
}

void DamageFont::Update(float _DeltaTime)
{
}

void DamageFont::End()
{
}
