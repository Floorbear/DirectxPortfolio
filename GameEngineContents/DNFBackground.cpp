#include "PreCompile.h"
#include "DNFBackground.h"

#include "DNFLevel.h"
#include "DNFRenderObject.h"
DNFBackground::DNFBackground()
{
}

DNFBackground::~DNFBackground()
{
}

void DNFBackground::InitBackground(const std::string& _FileName)
{
	IsStart_ = true;
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	std::string MapName = _FileName + ".png";
	MainRenderer_->SetTexture(MapName);
	MainRenderer_->ScaleToTexture();
	GetDNFLevel()->SetMapScale(MainRenderer_->GetTransform().GetLocalScale());

	ColRenderer = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	std::string ColMapName = _FileName + "_col.png";
	ColRenderer->SetTexture(ColMapName);
	ColRenderer->ScaleToTexture();
	GetDNFLevel()->SetMapScale(ColRenderer->GetTransform().GetLocalScale());
}
