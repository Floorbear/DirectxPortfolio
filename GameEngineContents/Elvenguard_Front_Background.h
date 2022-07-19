#pragma once
#include "DNFRenderObject.h"

class Elvenguard_Front_Background : public DNFRenderObject
{
public:
	Elvenguard_Front_Background();
	~Elvenguard_Front_Background();


	Elvenguard_Front_Background(const Elvenguard_Front_Background& _Other) = delete;
	Elvenguard_Front_Background(const Elvenguard_Front_Background&& _Other) noexcept = delete;
	Elvenguard_Front_Background& operator=(const Elvenguard_Front_Background& _Ohter) = delete;
	Elvenguard_Front_Background& operator=(const Elvenguard_Front_Background&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

