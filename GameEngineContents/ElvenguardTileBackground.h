#pragma once
#include "DNFRenderObject.h"

class ElvenguardTileBackground : public DNFRenderObject
{
public:
	ElvenguardTileBackground();
	~ElvenguardTileBackground();


	ElvenguardTileBackground(const ElvenguardTileBackground& _Other) = delete;
	ElvenguardTileBackground(const ElvenguardTileBackground&& _Other) noexcept = delete;
	ElvenguardTileBackground& operator=(const ElvenguardTileBackground& _Ohter) = delete;
	ElvenguardTileBackground& operator=(const ElvenguardTileBackground&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

