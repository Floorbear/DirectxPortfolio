#include "PreCompile.h"
#include "DNFDebugGUI.h"

#include <GameEngineCore/GameEngineCamera.h>

#include "DNFGlobalValue.h"
#include "Player_Main.h"
#include "DNFBackground.h"

std::map<std::string, float> DNFDebugGUI::DebugValue_float_;
std::map<std::string, int> DNFDebugGUI::DebugValue_int_;
std::map<std::string, float4> DNFDebugGUI::DebugValue_float4_;
std::map<std::string, std::string> DNFDebugGUI::DebugValue_string_;
std::map<std::string, float*> DNFDebugGUI::MutableValue_float_;


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
		//Col맵 끄기 보기
		{
			if (ImGui::Button("On/Off ColMap") == true)
			{
				DNFGlobalValue::CurrentLevel->GetBackground()->GetColRenderer()->OnOffSwitch();
			}
		}
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
		if (ImGui::TreeNodeEx("MousePos", 0) == true)
		{
			ImGui::Text("MousePos");
			float4 Pos = DNFGlobalValue::CurrentLevel->GetMainCamera()->GetScreenPosition();
			std::string PosX = "X : " + std::to_string(Pos.x - 640);
			std::string PosY = "Y : " + std::to_string(-Pos.y + 360);
			ImGui::Text(PosX.c_str());
			ImGui::Text(PosY.c_str());
			ImGui::TreePop();
		}

		//DebugValue_int
		if (DebugValue_int_.empty() == false)
		{
			if (ImGui::TreeNodeEx("DebugValue int", 0) == true)
			{
				for (auto i : DebugValue_int_)
				{
					std::string Text = i.first + " : " + std::to_string((i.second));
					ImGui::Text(Text.c_str());

				}
				//업데이트를 위해서
				DebugValue_int_.clear();
				ImGui::TreePop();
			}
		}

		//DebugValue_float
		if (DebugValue_float_.empty() == false)
		{
			if (ImGui::TreeNodeEx("DebugValue Float", 0) == true)
			{
				for (auto i : DebugValue_float_)
				{
					std::string Text = i.first + " : " + std::to_string((i.second));
					ImGui::Text(Text.c_str());
					
				}
				//업데이트를 위해서
				DebugValue_float_.clear();
				ImGui::TreePop();
			}
		}

		//DebugValue_string
		if (DebugValue_string_.empty() == false)
		{
			if (ImGui::TreeNodeEx("DebugValue String", 0) == true)
			{
				for (auto i : DebugValue_string_)
				{
					std::string Text = i.first + " : " + (i.second);
					ImGui::Text(Text.c_str());
				}
				DebugValue_string_.clear();
				ImGui::TreePop();
			}
		}

		//DebugValue_float
		if (DebugValue_float4_.empty() == false)
		{
			if (ImGui::TreeNodeEx("DebugValue Float4", 0) == true)
			{
				for (auto i : DebugValue_float4_)
				{
					std::string Text = i.first + "\nX : " + std::to_string((i.second.x))+"\nY : " + std::to_string((i.second.y)) + "\nZ : " + std::to_string((i.second.z));
					ImGui::Text(Text.c_str());
					
					
				}
				//업데이트를 위해서
				DebugValue_float4_.clear();
				ImGui::TreePop();
			}
		}

		//MutableValue_float
		if (MutableValue_float_.empty() == false)
		{
			if (ImGui::TreeNodeEx("MutableValue_float_", 0) == true)
			{
				for (auto i : MutableValue_float_)
				{
					ImGui::InputFloat(i.first.c_str(), i.second);


				}
				ImGui::TreePop();
			}
		}

	}
}
