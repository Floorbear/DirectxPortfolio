#pragma once
#include "DNFLevel.h"

class Elvenguard : public DNFLevel
{
public:
	Elvenguard();
	~Elvenguard();


	Elvenguard(const Elvenguard& _Other) = delete;
	Elvenguard(const Elvenguard&& _Other) noexcept = delete;
	Elvenguard& operator=(const Elvenguard& _Ohter) = delete;
	Elvenguard& operator=(const Elvenguard&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
};
