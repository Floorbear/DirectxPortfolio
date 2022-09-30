#include "PreCompile.h"
#include "Outragebreak.h"
#include "DieEffect.h"
#include "DNFContentsMinimal.h"
#include "Player_Main.h"

#include <GameEngineBase/GameEngineRandom.h>
Outragebreak::Outragebreak()
{
}

Outragebreak::~Outragebreak()
{
	for (int i = 0; i < BloodStartTimer_.size(); i++)
	{
		if (BloodStartTimer_[i] != nullptr)
		{
			delete BloodStartTimer_[i];
			BloodStartTimer_[i] = nullptr;
		}
	}
}

void Outragebreak::Start()
{
	//Floor_0 ·»´õ·¯ Ãß°¡
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Floor_0", FrameAnimation_DESC("outragebreak_floor", 0, 0, 1.0f, false));
		Renderer->ChangeFrameAnimation("Floor_0");
		Renderer->SetScaleModeImage();
		Renderer->GetTransform().SetLocalPosition({ 0,0,55 });
		Renderer->GetPixelData().MulColor.a = 0.0f;
		float Alpha = 0.0f;
		AllAlpha_.insert(std::make_pair("Floor_0", Alpha));
		AllRenderer_.insert(std::make_pair("Floor_0", Renderer));
		FloorRenderer_.push_back(Renderer);
	}

	//Floor_1 ·»´õ·¯ Ãß°¡ (»ìÂ¦ º¸ÀÌ´Â Æ´)
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Floor_1", FrameAnimation_DESC("outragebreak_floor", 1, 1, 1.0f, false));
		Renderer->ChangeFrameAnimation("Floor_1");
		Renderer->SetScaleModeImage();
		Renderer->GetTransform().SetLocalPosition({ 0,0,55 });
		Renderer->Off();
		float Alpha = 1.0f;
		AllAlpha_.insert(std::make_pair("Floor_1", Alpha));
		AllRenderer_.insert(std::make_pair("Floor_1", Renderer));
		FloorRenderer_.push_back(Renderer);
	}

	//Floor_2 ·»´õ·¯ Ãß°¡ (»¡°³Áö´Â Æ´)
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Floor_2", FrameAnimation_DESC("outragebreak_floor", 7, 10, 0.1f, false));
		Renderer->ChangeFrameAnimation("Floor_2");
		Renderer->SetScaleModeImage();
		Renderer->GetTransform().SetLocalPosition({ 0,0,55 });
		Renderer->Off();
		float Alpha = 1.0f;
		AllAlpha_.insert(std::make_pair("Floor_2", Alpha));
		AllRenderer_.insert(std::make_pair("Floor_2", Renderer));
		FloorRenderer_.push_back(Renderer);

		//ÇÔ¼öÃß°¡
		AllRenderer_["Floor_2"]->AnimationBindEnd("Floor_2",
			[&](const FrameAnimation_DESC& _Desc)
			{
				AllRenderer_["Floor_1"]->On();
				Phase_ = 3;
				for (int i = 0; i < 5; i++)
				{
					BloodStartTimer_[i]->StartTimer();
					//
				}
			});
	}

	//Ç÷±â ·»´õ·¯Ãß°¡
	{
		for (int i = 0; i < 5; i++)
		{
			GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
			Renderer->CreateFrameAnimationFolder("Blood", FrameAnimation_DESC("outragebreak_bloodsexp_2_none", 0.05f, false));
			Renderer->ChangeFrameAnimation("Blood");
			Renderer->GetTransform().SetLocalScale({ 640 * 1.2f,400 * 1.7f,1 });
			Renderer->GetTransform().SetLocalPosition(BloodPos_[i]);
			Renderer->Off();
			float Alpha = 1.0f;
			AllAlpha_.insert(std::make_pair("Blood_" + std::to_string(i), Alpha));
			AllRenderer_.insert(std::make_pair("Blood_" + std::to_string(i), Renderer));
			BloodRenderer_.push_back(Renderer);
		}

		//Ç÷±â Å¸ÀÌ¸Ó Ãß°¡
		{
			{
				Timer* NewTimer = new Timer(0.3f);
				BloodStartTimer_.push_back(NewTimer);
			}
			{
				Timer* NewTimer = new Timer(0.4f);
				BloodStartTimer_.push_back(NewTimer);
			}
			{
				Timer* NewTimer = new Timer(0.2f);
				BloodStartTimer_.push_back(NewTimer);
			}
			{
				Timer* NewTimer = new Timer(0.6f);
				BloodStartTimer_.push_back(NewTimer);
			}
			{
				Timer* NewTimer = new Timer(0.5f);
				BloodStartTimer_.push_back(NewTimer);
			}
		}

		//ÇÔ¼öÃß°¡ >> Ç÷±â2¹ø ´ÙÆ¢±â¸é »ç¶óÁö°Ô
		BloodRenderer_[0]->AnimationBindEnd("Blood",
			[&](const FrameAnimation_DESC& _Desc)
			{
				int _Index = 0;
				BloodFunction(_Index);
			});
		BloodRenderer_[1]->AnimationBindEnd("Blood",
			[&](const FrameAnimation_DESC& _Desc)
			{
				int _Index = 1;
				BloodFunction(_Index);
			});
		BloodRenderer_[2]->AnimationBindEnd("Blood",
			[&](const FrameAnimation_DESC& _Desc)
			{
				int _Index = 2;
				BloodFunction(_Index);
			});
		BloodRenderer_[3]->AnimationBindEnd("Blood",
			[&](const FrameAnimation_DESC& _Desc)
			{
				//°¡Àå ´Ê°Ô ¹æÃâµÇ´Â Ç÷±â
				int _Index = 3;
				BloodFunction(_Index);
			});
		BloodRenderer_[4]->AnimationBindEnd("Blood",
			[&](const FrameAnimation_DESC& _Desc)
			{
				int _Index = 4;
				BloodFunction(_Index);
			});
	}
}

void Outragebreak::BloodFunction(int _Index)
{
	LoopCount_[_Index]++;
	if (LoopCount_[_Index] >= 2)
	{
		BloodRenderer_[_Index]->Off();
		if (_Index == 3)
		{
			Phase_ = 4;
		}
	}
	else
	{
		BloodRenderer_[_Index]->CurAnimationReset();
	}
}

void Outragebreak::Update(float _DeltaTime)
{
	switch (Phase_)
	{
	case 0:
		AllAlpha_["Floor_0"] += _DeltaTime * 10.0f;
		if (AllAlpha_["Floor_0"] >= 1.0f)
		{
			DieEffect* NewDieEffect = GetLevel()->CreateActor<DieEffect>();
			float4 MovePos = { 120,-45,-500 };
			MovePos.x = GetDirX() * MovePos.x;
			NewDieEffect->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + MovePos);
			NewDieEffect->GetTransform().SetLocalScale({ 1.0f,1.0f,1.0f });
			NewDieEffect->Init("Outragebreak_part");
			NewDieEffect->Option(false, 2.5f);
			AllAlpha_["Floor_0"] = 1.0f;
			Phase1Timer_.StartTimer();
			Phase_ = 1;
		}
		AllRenderer_["Floor_0"]->GetPixelData().MulColor.a = AllAlpha_["Floor_0"];
		break;
	case 1:
		if (Phase1Timer_.IsTimerOn() == false)
		{
			Phase_ = 2;
			AllRenderer_["Floor_2"]->On();
		}
		else
		{
			Phase1Timer_.Update(_DeltaTime);
		}
		break;
	case 2:
		break;
	case 3: //Ç÷±â Æø¹ß
	{
		for (int i = 0; i < 5; i++)
		{
			if (BloodStartTimer_[i]->IsTimerOn() == true)
			{
				BloodStartTimer_[i]->Update(_DeltaTime);
				if (BloodStartTimer_[i]->IsTimerOn() == false)
				{
					BloodRenderer_[i]->On();
				}
			}
		}
		//Ä«¸Þ¶ó Shake
		Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
		if (BloodStartTimer_[2]->IsTimerOn() == true)
		{
			break;
		}
		if (ShakeTimer_.IsTimerOn() == false)
		{
			if (ShakeLoop_ < 4)
			{
				ShakeLoop_++;
				Player->ShakeCamera(8.0f, 0.17f);
				ShakeTimer_.StartTimer();
			}
		}
		else
		{
			ShakeTimer_.Update(_DeltaTime);
		}

		if (AttTimer_.IsTimerOn() == false)
		{
			if (AttLoop_ < 6)
			{
				AttLoop_++;
				AttTimer_.StartTimer();
				GameEngineSound::SoundPlayOneShot(Player->GetRandomSound("outrage_crash-0", 1, 3) + ".wav");

				Player->GetAttData().AttackSound = "";

				Player->GetAttData().AttackName = "Outragebreak";
				Player->GetAttData().Att = Player->CalAtt(Player->Value_.OutrageBreakAtt);
				Player->GetAttData().Type = AttackType::Below;
				Player->GetAttData().XForce = 00.0f;
				Player->GetAttData().AttCount++;
				int Random = GameEngineRandom::MainRandom.RandomInt(1, 3);
				Player->GetAttData().AttEffect = static_cast<Effect>(Random);
				Player->GetAttData().Stiffness = 0.01f;
				Player->GetAttData().RStiffness = 0.01f;
				Player->GetAttData().YForce = 120.0f;
				Player->GetAttData().Bleeding = 85;
				Player->GetAttData().ZPos = 0;
			}
		}
		else
		{
			AttTimer_.Update(_DeltaTime);
		}
	}

	break;
	case 4:
	{
		if (IsAttackEnd_ == false)
		{
			IsAttackEnd_ = true;
			Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
			Player->CurAttEnd();
		}
		AllAlpha_["Floor_0"] -= _DeltaTime * 3.0f;
		if (AllAlpha_["Floor_0"] <= 0.0f)
		{
			Death();
		}
		for (auto i : FloorRenderer_)
		{
			i->GetPixelData().MulColor.a = AllAlpha_["Floor_0"];
		}
	}
	break;
	default:
		break;
	}
}

void Outragebreak::StiffnessUpdate(float _DeltaTime)
{
}

void Outragebreak::End()
{
}

float Outragebreak::GetDirX()
{
	if (GetTransform().GetLocalScale().x > 0)
	{
		return 1.f;
	}

	return -1.f;
}