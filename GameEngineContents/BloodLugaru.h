#pragma once
#include "DNFRenderObject.h"

class BloodLugaru : public DNFRenderObject
{
public:
	BloodLugaru();
	~BloodLugaru();


	BloodLugaru(const BloodLugaru& _Other) = delete;
	BloodLugaru(const BloodLugaru&& _Other) noexcept = delete;
	BloodLugaru& operator=(const BloodLugaru& _Ohter) = delete;
	BloodLugaru& operator=(const BloodLugaru&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	float AniSpeed_;

};

