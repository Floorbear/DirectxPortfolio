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

Force::Force():
	Transform_()
{
}

Force::~Force()
{
}

void Force::Update(float _DeltaTime)
{
	//ForceUpdae
	if (abs(ForceX_) > 0)
	{
		if (ForceX_ > 0.0f)
		{
			ForceX_ -= _DeltaTime * FrictionX_;
			if (ForceX_ <= 0.0f)
			{
				ForceX_ = 0.0f;
			}
		}
		else if (ForceX_ < 0.0f)
		{
			ForceX_ += _DeltaTime * FrictionX_;
			if (ForceX_ >= 0.0f)
			{
				ForceX_ = 0.0f;
			}
		}
	}

	if (IsForceX() == true)
	{
		Transform_->SetLocalMove(GetDirX() * ForceX_ * _DeltaTime);
	}
}
