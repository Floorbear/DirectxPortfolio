#pragma once

#include "DNFLevel.h"

enum class ColOrder
{
	None,
	Player,
	Monster,
	Debug
};

class DNFGlobalValue
{
public:
	//���� ����
	static DNFLevel* CurrentLevel;
};



