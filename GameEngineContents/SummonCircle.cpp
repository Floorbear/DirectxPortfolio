#include "Precompile.h"
#include "SummonCircle.h"

#include "DNFContentsMinimal.h"

SummonCircle::SummonCircle() :
	PivotTex_(),
	SummonFront_(),
	SummonBack_()
{
}

SummonCircle::~SummonCircle()
{
}

void SummonCircle::Start()
{
	//소환진 텍스처 로드
	if (GameEngineFolderTexture::Find("summons01") == nullptr)
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("SkillTexture");
		Dir.Move("Summon");
		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}

	SummonBack_ = CreateComponent<GameEngineTextureRenderer>();
	SummonBack_->SetScaleModeImage();
	SummonBack_->SetScaleRatio(0.7f);
	SummonBack_->CreateFrameAnimationFolder("Summon", FrameAnimation_DESC("summons02", 0.1f, false));
	SummonBack_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	SummonBack_->ChangeFrameAnimation("Summon");
	SummonBack_->GetTransform().SetLocalPosition({ 207, -87 });
	SummonBack_->Off();

	SummonFront_ = CreateComponent<GameEngineTextureRenderer>();
	SummonFront_->SetScaleModeImage();
	SummonFront_->SetScaleRatio(0.7f);
	SummonFront_->CreateFrameAnimationFolder("Summon", FrameAnimation_DESC("summons01", 0.1f, false));
	SummonFront_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	SummonFront_->ChangeFrameAnimation("Summon");
	SummonFront_->GetTransform().SetLocalPosition({ 207, -30 });

	SummonBack_->AnimationBindEnd("Summon",
		[&](const FrameAnimation_DESC& _Desc)
		{
			Death(0.5f);
		});
	SummonFront_->AnimationBindFrame("Summon",
		[&](const FrameAnimation_DESC& _Desc)
		{
			if (_Desc.CurFrame == 5)
			{
				SpawnFunction_(MovePos_);
				SummonBack_->On();
			}
		}
	);

	//SummonBack_ = CreateComponent<GameEngineTextureRenderer>();
}

void SummonCircle::Update(float _DeltaTime)
{
}

void SummonCircle::End()
{
}