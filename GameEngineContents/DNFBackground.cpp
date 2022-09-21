#include "PreCompile.h"
#include "DNFBackground.h"

#include "DNFLevel.h"
#include "DNFRenderObject.h"
#include "DNFGlobalValue.h"
DNFBackground::DNFBackground() :
	ColRenderer(),
	BushRenderer_(),
	MainRenderer_(),
	FarSpeed_(0.5f),
	FadeRenderer_(),
	FadeInTimer_()
{
}

DNFBackground::~DNFBackground()
{
}

void DNFBackground::InitBackground(const std::string& _FileName)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	std::string MapName = _FileName + ".png";
	MainRenderer_->SetTexture(MapName);
	MainRenderer_->ScaleToTexture();
	MainRenderer_->SetPivot(PIVOTMODE::LEFTTOP);

	dynamic_cast<DNFLevel*>(GetLevel())->SetMapScale(MainRenderer_->GetTransform().GetLocalScale());

	ColRenderer = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	std::string ColMapName = _FileName + "_col.png";
	ColRenderer->SetTexture(ColMapName);
	ColRenderer->ScaleToTexture();
	ColRenderer->SetPivot(PIVOTMODE::LEFTTOP);
	ColRenderer->Off();

	//페이드 인 아웃
	FadeRenderer_ = CreateComponent<GameEngineUIRenderer>(GetNameCopy());
	FadeRenderer_->SetTexture("Fade.png");
	FadeRenderer_->GetTransform().SetLocalScale({ 2000.0f,2000.0f });
	FadeRenderer_->GetTransform().SetLocalMove({ 0,0,-4000 });
	FadeRenderer_->GetPixelData().PlusColor = { -1,-1,-1,0 };
}