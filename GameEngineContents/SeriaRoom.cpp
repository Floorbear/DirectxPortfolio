#include "PreCompile.h"
#include "SeriaRoom.h"

#include "SeriaBackground.h"


SeriaRoom::SeriaRoom()
{
}

SeriaRoom::~SeriaRoom()
{
}

void SeriaRoom::Start()
{
	DNFStart();
	SeriaBackground* Background = CreateActor<SeriaBackground>();
}

void SeriaRoom::Update(float _DeltaTime)
{
	DNFUpdate();
}

void SeriaRoom::End()
{
}
