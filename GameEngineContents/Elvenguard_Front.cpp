#include "PreCompile.h"
#include "Elvenguard_Front.h"

#include "Elvenguard_Front_Background.h"

Elvenguard_Front::Elvenguard_Front()
{
}

Elvenguard_Front::~Elvenguard_Front()
{
}

void Elvenguard_Front::Start()
{
	DNFStart();
	Elvenguard_Front_Background* Background = CreateActor<Elvenguard_Front_Background>();
}

void Elvenguard_Front::Update(float _DeltaTime)
{
	DNFUpdate();

}

void Elvenguard_Front::End()
{
}
