#include "PreCompile.h"
#include "DNFBackground.h"

#include "DNFLevel.h"
#include "DNFRenderObject.h"
#include "DNFGlobalValue.h"
DNFBackground::DNFBackground()
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
}