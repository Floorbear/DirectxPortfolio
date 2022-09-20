#include "PreCompile.h"
#include "DNFGlobalValue.h"
#include "MonsterHP.h"

DNFLevel* DNFGlobalValue::CurrentLevel = nullptr;

MonsterHP* DNFGlobalValue::CurrentMonsterHP = nullptr;

Player_Main* DNFGlobalValue::CurrentPlayer_ = nullptr;

DNFHUD* DNFGlobalValue::CurrentHUD_ = nullptr;

float4 DNFGlobalValue::Temp1 = {};