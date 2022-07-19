#pragma once
#include "DNFRenderObject.h"

class SeriaBackground : public DNFRenderObject
{
public:
	SeriaBackground();
	~SeriaBackground();


	SeriaBackground(const SeriaBackground& _Other) = delete;
	SeriaBackground(const SeriaBackground&& _Other) noexcept = delete;
	SeriaBackground& operator=(const SeriaBackground& _Ohter) = delete;
	SeriaBackground& operator=(const SeriaBackground&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

};

