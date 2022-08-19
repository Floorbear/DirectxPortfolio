#pragma once
#include <GameEngineBase/GameEngineMath.h>

class DNFMath
{
public:
	DNFMath();
	~DNFMath();


	DNFMath(const DNFMath& _Other) = delete;
	DNFMath(const DNFMath&& _Other) noexcept = delete;
	DNFMath& operator=(const DNFMath& _Ohter) = delete;
	DNFMath& operator=(const DNFMath&& _Other) noexcept = delete;

	//x,y로만 계산함 
	static float Length(const float4& _Left, const float4& _Right)
	{

		float4 LengthVector = _Left - _Right;
		LengthVector.z = 0;

		float length = LengthVector.Length();
		return length;
	}
};

class Timer
{
public:
	Timer();
	~Timer();

	Timer(float _Value);

	Timer& operator=(float _Value)
	{
		Iter_Time_ = _Value;
		Default_Time_ = _Value;
		return *this;
	}

	Timer& operator-=(float _Value)
	{
		Iter_Time_ -= _Value;
		if (Iter_Time_ <= 0.0f)
		{
			Iter_Time_ = 0.0f;
			IsTimerOn_ = false;
		}
		return *this;

	}

	Timer& operator+=(float _Value)
	{
		Iter_Time_ += _Value;
		return *this;

	}

	bool IsTimerOn()
	{
		if (IsTimerOn_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void StartTimer()
	{
		On();
		Reset();
	}

	void StartTimer(float _Value)
	{
		On();
		Default_Time_ = _Value;
		Reset();
	}

	//타이머의 초기 시간
	float Default_Time_;

	private:
		//실제 시간
		float Iter_Time_;

		bool IsTimerOn_;

		void On()
		{
			IsTimerOn_ = true;
		}

		void Off()
		{
			IsTimerOn_ = false;
		}

		void Reset()
		{
			Iter_Time_ = Default_Time_;
		}

		void SetDefaultTime(float _Value)
		{
			if (_Value <= 0.0f)
			{
				MsgBoxAssert("잘못된 _Value!");
			}
			Default_Time_ = _Value;
		}

		bool IsTimeZero()
		{
			if (Iter_Time_ <= 0.0f)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		//DefaultTime이상이냐
		bool IsTimeOver()
		{
			if (Iter_Time_ >= Default_Time_)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
};

class Force
{
public:
	Force();
	~Force();

	void Update(float _DeltaTime);
	bool IsForceX()
	{
		if (abs(ForceX_) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsForceY()
	{
		if (IsGravityOn_ == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void OnGravity()
	{
		IsGravityOn_ = true;
	}
	void OffGravity()
	{
		IsGravityOn_ = false;
	}

	inline void SetTransfrom(GameEngineTransform* _Trans)
	{
		Transform_ = _Trans;
	}

	inline float4 GetDirX()
	{
		if (Transform_->GetLocalScale().x > 0)
		{
			return float4::RIGHT;
		}
		else if (Transform_->GetLocalScale().x < 0)
		{
			return float4::LEFT;
		}

		return float4::ZERO;
	}

	//Y축 가속도의 On Off는 내가 수동으로 해줘야 한다.

	float ForceX_;
	float ForceY_;

	float FrictionX_;
	float Gravity_;

private:
	GameEngineTransform* Transform_;

	bool IsGravityOn_;

};
