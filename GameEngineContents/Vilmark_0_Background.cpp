#include "PreCompile.h"
#include "Vilmark_0_Background.h"
#include "DNFLevel.h"

Vilmark_0_Background::Vilmark_0_Background()
{
}

Vilmark_0_Background::~Vilmark_0_Background()
{
}

void Vilmark_0_Background::Start()
{
	DNFStart();
	InitBackground("Vilmark_Background_00");

	//ColRenderer_ = CreateComponent<GameEngineTextureRenderer>(GetNameCopy());
	//ColRenderer_->SetTexture("Vilmark_Background_00_col.png");
	//ColRenderer_->ScaleToTexture();

	//On이벤트 버그 수정 되면 OnEvent로 변경해야함
}

void Vilmark_0_Background::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Vilmark_0_Background::End()
{

}
