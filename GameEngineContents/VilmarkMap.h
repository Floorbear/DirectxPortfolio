#pragma once
#include "DNFBackground.h"

class VilmarkMap : public DNFBackground
{
public:
	VilmarkMap();
	~VilmarkMap();

	VilmarkMap(const VilmarkMap& _Other) = delete;
	VilmarkMap(const VilmarkMap&& _Other) noexcept = delete;
	VilmarkMap& operator=(const VilmarkMap& _Ohter) = delete;
	VilmarkMap& operator=(const VilmarkMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
};
