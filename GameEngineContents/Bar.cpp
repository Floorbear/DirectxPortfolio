#include "PreCompile.h"
#include "Bar.h"

#include "Bar_Background.h"

Bar::Bar()
{
}

Bar::~Bar()
{
}

void Bar::Start()
{
	DNFStart();
	Bar_Background* TileBackground = CreateActor< Bar_Background>();
}

void Bar::Update(float _DeltaTime)
{
	DNFUpdate();
}

void Bar::End()
{
}
