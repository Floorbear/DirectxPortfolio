#pragma once
#include "DNFLevel.h"

class Vilmark_0 : public DNFLevel
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
	void Update(float _DeltaTime) override;
	void End() override;

};

