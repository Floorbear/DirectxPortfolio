#pragma once
#include "VilmarkLevel.h"
#include "DNFMath.h"

class Vilmark_0 : public VilmarkLevel
{
public:
	Vilmark_0();
	~Vilmark_0();

	Vilmark_0(const Vilmark_0& _Other) = delete;
	Vilmark_0(const Vilmark_0&& _Other) noexcept = delete;
	Vilmark_0& operator=(const Vilmark_0& _Ohter) = delete;
	Vilmark_0& operator=(const Vilmark_0&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() override;

	void DNFOnEvent() override;
};
