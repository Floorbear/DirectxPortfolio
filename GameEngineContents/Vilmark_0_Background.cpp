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

	//On�̺�Ʈ ���� ���� �Ǹ� OnEvent�� �����ؾ���
}

void Vilmark_0_Background::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Vilmark_0_Background::End()
{

}
