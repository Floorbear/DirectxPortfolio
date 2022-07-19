#pragma once
#include "DNFLevel.h"

class Bar : public DNFLevel
{
public:
	Bar();
	~Bar();


	Bar(const Bar& _Other) = delete;
	Bar(const Bar&& _Other) noexcept = delete;
	Bar& operator=(const Bar& _Ohter) = delete;
	Bar& operator=(const Bar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
};

