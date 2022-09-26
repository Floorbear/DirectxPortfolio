#pragma once
#include "VilmarkLevel.h"
#include "DNFMath.h"

class Vilmark_4 : public VilmarkLevel
{
public:
	Vilmark_4();
	~Vilmark_4();

	Vilmark_4(const Vilmark_4& _Other) = delete;
	Vilmark_4(const Vilmark_4&& _Other) noexcept = delete;
	Vilmark_4& operator=(const Vilmark_4& _Ohter) = delete;
	Vilmark_4& operator=(const Vilmark_4&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() override;

	void DNFOnEvent() override;
};
