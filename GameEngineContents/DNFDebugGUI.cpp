#include "PreCompile.h"
#include "DNFDebugGUI.h"

#include <GameEngineCore/GameEngineCamera.h>

#include "DNFGlobalValue.h"
#include "Player_Main.h"

DNFDebugGUI::DNFDebugGUI()
{
}

DNFDebugGUI::~DNFDebugGUI()
{
}

void DNFDebugGUI::Initialize(GameEngineLevel* _Level)
{
}

void DNFDebugGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::string CurrentLevel = "Current Level : " + DNFGlobalValue::CurrentLevel->GetNameCopy();
	ImGui::Text(CurrentLevel.c_str());
	
	if (DNFGlobalValue::CurrentLevel != nullptr)
	{
		//플레이어 위치 
		{
			ImGui::Text("PlayerPos");
			float4 Pos = DNFGlobalValue::CurrentLevel->GetPlayer()->GetTransform().GetWorldPosition();
			std::string PosX = "X : " + std::to_string(Pos.x);
			std::string PosY = "Y : " + std::to_string(Pos.y);
			std::string PosZ = "Z : " + std::to_string(Pos.z);
			ImGui::Text(PosX.c_str());
			ImGui::Text(PosY.c_str());
			ImGui::Text(PosZ.c_str());
		}
		
		//마우스 위치
		{
			ImGui::Text("MousePos");
			float4 Pos = DNFGlobalValue::CurrentLevel->GetMainCamera()->GetScreenPosition();
			std::string PosX = "X : " + std::to_string(Pos.x-640);
			std::string PosY = "Y : " + std::to_string(-Pos.y+360);
			ImGui::Text(PosX.c_str());
			ImGui::Text(PosY.c_str());

		}
		
	}
}
