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
	Transform_(),
	IsGravityOn_(false)
{
}

Force::~Force()
{
}

void Force::Update(float _DeltaTime)
{
	//ForceUpdae
	if (IsForceX() == true)
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


		Transform_->SetLocalMove(GetDirX() * ForceX_ * _DeltaTime);
	}

	if (IsForceY() == true)
	{
		ForceY_ -= _DeltaTime * Gravity_;

		Transform_->SetLocalMove(float4::UP * ForceY_ * _DeltaTime);
	}



}
