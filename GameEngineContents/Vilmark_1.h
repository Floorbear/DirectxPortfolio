#pragma once
#include "VilmarkLevel.h"

class Vilmark_1 : public VilmarkLevel
{
public:
	Vilmark_1();
	~Vilmark_1();

	Vilmark_1(const Vilmark_1& _Other) = delete;
	Vilmark_1(const Vilmark_1&& _Other) noexcept = delete;
	Vilmark_1& operator=(const Vilmark_1& _Ohter) = delete;
	Vilmark_1& operator=(const Vilmark_1&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() override;

	void DNFOnEvent() override;
};
