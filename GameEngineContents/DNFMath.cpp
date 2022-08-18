#include "PreCompile.h"
#include "DNFMath.h"

DNFMath::DNFMath()
{
}

DNFMath::~DNFMath()
{
}

Timer::Timer()
{
}

Timer::~Timer()
{
}

Timer::Timer(float _Value):
	Iter_Time_(_Value),
	Default_Time_(_Value),
	IsTimerOn_(false)
{
}
