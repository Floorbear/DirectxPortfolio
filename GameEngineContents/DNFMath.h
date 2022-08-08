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

