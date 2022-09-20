#pragma once
#include "DNFLevel.h"

class VilmarkLevel : public DNFLevel
{
public:
	VilmarkLevel();
	~VilmarkLevel();

	VilmarkLevel(const VilmarkLevel& _Other) = delete;
	VilmarkLevel(const VilmarkLevel&& _Other) noexcept = delete;
	VilmarkLevel& operator=(const VilmarkLevel& _Ohter) = delete;
	VilmarkLevel& operator=(const VilmarkLevel&& _Other) noexcept = delete;

protected:
	void VilmarkStart();
	void VilmarkUpdate(float _DeltaTime);

	void VilmarkStartLevel();
};
