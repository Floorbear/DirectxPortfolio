#include "PreCompile.h"
#include "HopSmash.h"

#include "DNFContentsMinimal.h"

HopSmash::HopSmash() :
	Renderer_1_d_(),
	Renderer_1_n_(),
	Renderer_2_d_(),
	Renderer_2_n_()
{
}

HopSmash::~HopSmash()
{
}

void HopSmash::Start()
{
	//붕산격 텍스처 로딩
	if (GameEngineFolderTexture::Find("b_bottom_01_d") == nullptr)
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExitsChildDirectory("ContentsResources");
			Dir.Move("ContentsResources");
			Dir.Move("FolderTexture");
			Dir.Move("SkillTexture");
			Dir.Move("HopSmash");
			std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
			for (GameEngineDirectory Dir_i : Dirs)
			{
				GameEngineFolderTexture::Load(Dir_i.GetFullPath());
			}
		}
	}
	{
		Renderer_1_d_ = CreateComponent<GameEngineTextureRenderer>();
		Renderer_1_d_->CreateFrameAnimationFolder("Smash", FrameAnimation_DESC("b_bottom_01_d", GoreCrossIter, false));
		Renderer_1_d_->SetScaleModeImage();
		Renderer_1_d_->ChangeFrameAnimation("Smash");
		Renderer_1_d_->AnimationBindEnd("Smash", [&](const FrameAnimation_DESC _Desc)
			{
				IsEffectEnd_ = true;
			});
		AllRenderer_.push_back(Renderer_1_d_);
	}
	{
		Renderer_1_n_ = CreateComponent<GameEngineTextureRenderer>();
		Renderer_1_n_->CreateFrameAnimationFolder("Smash", FrameAnimation_DESC("b_bottom_01_n", GoreCrossIter, false));
		Renderer_1_n_->SetScaleModeImage();
		Renderer_1_n_->ChangeFrameAnimation("Smash");
		AllRenderer_.push_back(Renderer_1_n_);
	}
	{
		Renderer_2_d_ = CreateComponent<GameEngineTextureRenderer>();
		Renderer_2_d_->CreateFrameAnimationFolder("Smash", FrameAnimation_DESC("b_bottom_02_d", GoreCrossIter, false));
		Renderer_2_d_->SetScaleModeImage();
		Renderer_2_d_->ChangeFrameAnimation("Smash");
		AllRenderer_.push_back(Renderer_2_d_);
	}
	{
		Renderer_2_n_ = CreateComponent<GameEngineTextureRenderer>();
		Renderer_2_n_->CreateFrameAnimationFolder("Smash", FrameAnimation_DESC("b_bottom_02_n", GoreCrossIter, false));
		Renderer_2_n_->SetScaleModeImage();
		Renderer_2_n_->ChangeFrameAnimation("Smash");
		AllRenderer_.push_back(Renderer_2_n_);
	}
	Death(1.0f);
}

void HopSmash::Update(float _DeltaTime)
{
	if (IsEffectEnd_ == true)
	{
		Alpha_ -= _DeltaTime * 8.f;
		if (Alpha_ <= 0.f)
		{
			Alpha_ = 0.f;
		}
		for (auto i : AllRenderer_)
		{
			i->GetPixelData().MulColor.a = Alpha_;
		}
	}
}

void HopSmash::End()
{
}