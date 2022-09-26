#pragma once
#include "VilmarkLevel.h"

class Vilmark_5 : public VilmarkLevel
{
public:
	Vilmark_5();
	~Vilmark_5();

	Vilmark_5(const Vilmark_5& _Other) = delete;
	Vilmark_5(const Vilmark_5&& _Other) noexcept = delete;
	Vilmark_5& operator=(const Vilmark_5& _Ohter) = delete;
	Vilmark_5& operator=(const Vilmark_5&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() override;

	void DNFOnEvent() override;
};
