#pragma once
#include "DNFLevel.h"

class Elvenguard_Front : public DNFLevel
{
public:
	Elvenguard_Front();
	~Elvenguard_Front();


	Elvenguard_Front(const Elvenguard_Front& _Other) = delete;
	Elvenguard_Front(const Elvenguard_Front&& _Other) noexcept = delete;
	Elvenguard_Front& operator=(const Elvenguard_Front& _Ohter) = delete;
	Elvenguard_Front& operator=(const Elvenguard_Front&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;


};

