#pragma once
#include "VilmarkLevel.h"

class Vilmark_3 : public VilmarkLevel
{
public:
	Vilmark_3();
	~Vilmark_3();

	Vilmark_3(const Vilmark_3& _Other) = delete;
	Vilmark_3(const Vilmark_3&& _Other) noexcept = delete;
	Vilmark_3& operator=(const Vilmark_3& _Ohter) = delete;
	Vilmark_3& operator=(const Vilmark_3&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() override;

	void DNFOnEvent() override;
};
