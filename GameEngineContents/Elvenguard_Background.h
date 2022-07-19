#pragma once
#include "DNFRenderObject.h"

class Elvenguard_Background : public DNFRenderObject
{
public:
	Elvenguard_Background();
	~Elvenguard_Background();


	Elvenguard_Background(const Elvenguard_Background& _Other) = delete;
	Elvenguard_Background(const Elvenguard_Background&& _Other) noexcept = delete;
	Elvenguard_Background& operator=(const Elvenguard_Background& _Ohter) = delete;
	Elvenguard_Background& operator=(const Elvenguard_Background&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

