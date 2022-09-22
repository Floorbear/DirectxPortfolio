#pragma once
#include "VilmarkLevel.h"
class Vilmark_2 : public VilmarkLevel
{
public:
	Vilmark_2();
	~Vilmark_2();

	Vilmark_2(const Vilmark_2& _Other) = delete;
	Vilmark_2(const Vilmark_2&& _Other) noexcept = delete;
	Vilmark_2& operator=(const Vilmark_2& _Ohter) = delete;
	Vilmark_2& operator=(const Vilmark_2&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() override;

	void DNFOnEvent() override;
};
