#pragma once
#include "DNFRenderObject.h"

class Bar_Background : public DNFRenderObject
{
public:
	Bar_Background();
	~Bar_Background();


	Bar_Background(const Bar_Background& _Other) = delete;
	Bar_Background(const Bar_Background&& _Other) noexcept = delete;
	Bar_Background& operator=(const Bar_Background& _Ohter) = delete;
	Bar_Background& operator=(const Bar_Background&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

