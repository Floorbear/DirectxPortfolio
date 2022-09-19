#include "PreCompile.h"
#include "DNFContentsMinimal.h"
#include "GoreCross.h"
#include "Player_Main.h"

GoreCross::GoreCross() :
	Speed_(0.0f),
	IsEnd_(false),
	Stiffness_(),
	IsSlashEnd_(false),
	IsAttCountPlus_(false),
	IsCallPlayerEnd_(false)
{
}

GoreCross::~GoreCross()
{
}

void GoreCross::Start()
{
	//고어크로스 텍스처가 없으면 로드한다.
	if (GameEngineFolderTexture::Find("gorecross_cross") == nullptr)
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("SkillTexture");
			Dir.Move("GoreCross");
			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
	}

	//Slash 렌더러 추가
	{
		GameEngineTextureRenderer* Slash = CreateComponent<GameEngineTextureRenderer>();
		Slash->CreateFrameAnimationFolder("Slash", FrameAnimation_DESC("gorecross_slash", GoreCrossIter * 1.2f, false));
		Slash->ChangeFrameAnimation("Slash");
		Slash->SetScaleModeImage();

		Renderer_.insert(std::make_pair("Slash", Slash));
	}

	//Main 렌더러 추가
	{
		GameEngineTextureRenderer* Main = CreateComponent<GameEngineTextureRenderer>();
		Main->CreateFrameAnimationFolder("Main", FrameAnimation_DESC("gorecross_cross", GoreCrossIter, false));
		Main->ChangeFrameAnimation("Main");
		Main->SetScaleModeImage();

		Renderer_.insert(std::make_pair("Main", Main));
	}
	//ObjBack 렌더러 추가
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("ObjBack", FrameAnimation_DESC("gorecross_obj_cross_ldodge", GoreCrossIter * 1.7f, false));
		Renderer->ChangeFrameAnimation("ObjBack");
		Renderer->CurAnimationPauseOn();
		Renderer->SetScaleModeImage();
		Renderer->Off();
		Renderer_.insert(std::make_pair("ObjBack", Renderer));
	}
	//ObjFront 렌더러 추가
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("ObjFront", FrameAnimation_DESC("gorecross_obj_cross_none", GoreCrossIter * 1.7f, false));
		Renderer->ChangeFrameAnimation("ObjFront");
		Renderer->CurAnimationPauseOn();
		Renderer->SetScaleModeImage();
		Renderer->Off();
		Renderer_.insert(std::make_pair("ObjFront", Renderer));
	}
	//애니메이션 바인딩
	{
		Renderer_["Slash"]->AnimationBindEnd("Slash",
			[&](const FrameAnimation_DESC& _Desc)
			{
				IsSlashEnd_ = true;
			});

		Renderer_["ObjBack"]->AnimationBindEnd("ObjBack",
			[&](const FrameAnimation_DESC& _Desc)
			{
			});

		Renderer_["ObjFront"]->AnimationBindEnd("ObjFront",
			[&](const FrameAnimation_DESC& _Desc)
			{
			});

		Renderer_["Main"]->AnimationBindEnd("Main",
			[&](const FrameAnimation_DESC& _Desc)
			{
				Renderer_["Main"]->CurAnimationPauseOn();
				Renderer_["Main"]->Off();
				Renderer_["ObjFront"]->On();
				Renderer_["ObjBack"]->On();
				Speed_ = 400.0f;
				MoveTimer_.StartTimer(0.14f);
			});
	}
	//Death(2.0f);
}

void GoreCross::StiffnessUpdate(float _DeltaTime)
{
	if (Stiffness_ > 0.0f)
	{
		for (auto i : Renderer_)
		{
			if (i.second->IsUpdate() == true)
			{
				i.second->CurAnimationPauseOn();
			}
		}
	}

	if (Stiffness_ <= 0)
	{
		for (auto i : Renderer_)
		{
			if (i.second->IsUpdate() == true)
			{
				i.second->CurAnimationPauseOff();
			}
		}
	}
}

void GoreCross::Update(float _DeltaTime)
{
	//플레이어의 Striffniss로 업데이트
	if (DNFGlobalValue::CurrentLevel == nullptr)
	{
		return;
	}
	Stiffness_ = DNFGlobalValue::CurrentLevel->GetPlayer()->GetStiffness();
	StiffnessUpdate(_DeltaTime);
	if (Stiffness_ > 0.0f)
	{
		return;
	}
	//플레이어가 Hit상태면 삭제되게?

	if (MoveTimer_.IsTimerOn() == true)
	{
		MoveTimer_.Update(_DeltaTime);
		GetTransform().SetLocalMove(float4::RIGHT * GetDirX() * Speed_ * _DeltaTime);
		//도중에 공격 딱 한번 더하는거 추가
		if (*MoveTimer_.GetIterTime() < 0.02f && IsAttCountPlus_ == false)
		{
			Player_Main* Player = DNFGlobalValue::CurrentLevel->GetPlayer();
			Player->GetAttData().AttCount++;
			Player->GetAttData().XForce = 30.0f;
			Player->GetAttData().YForce = 170.0f;

			IsAttCountPlus_ = true;
		}
		if (MoveTimer_.IsTimerOn() == false)
		{
			IsEnd_ = true;
		}
	}

	//Slash
	if (IsSlashEnd_ == true)
	{
		if (Renderer_["Slash"]->GetPixelData().MulColor.a > 0)
		{
			Renderer_["Slash"]->GetPixelData().MulColor.a -= _DeltaTime * 9.0f;
		}
		else
		{
			Renderer_["Slash"]->GetPixelData().MulColor.a = 0.0f;
		}
	}

	//모든 이펙트가 끝난 후 후처리
	if (IsEnd_ == true)
	{
		if (IsCallPlayerEnd_ == false)
		{
			DNFGlobalValue::CurrentLevel->GetPlayer()->CurAttEnd();
			IsCallPlayerEnd_ = true;
		}
		if (Renderer_["ObjFront"]->GetPixelData().MulColor.a > 0)
		{
			Renderer_["ObjFront"]->GetPixelData().MulColor.a -= _DeltaTime * 6.0f;
		}
		else
		{
			Renderer_["ObjFront"]->GetPixelData().MulColor.a = 0.0f;
			Death();
			return;
		}

		if (Renderer_["ObjBack"]->GetPixelData().MulColor.a > 0)
		{
			Renderer_["ObjBack"]->GetPixelData().MulColor.a -= _DeltaTime * 12.0f;
		}
		else
		{
			Renderer_["ObjBack"]->GetPixelData().MulColor.a = 0.0f;
		}
	}
}

void GoreCross::End()
{
}

float GoreCross::GetDirX()
{
	if (GetTransform().GetLocalScale().x > 0)
	{
		return 1.f;
	}

	return -1.f;
}