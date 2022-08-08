#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineBase/GameEngineMath.h>

class DNFDebugGUI : public GameEngineGUIWindow
{
public:
	DNFDebugGUI();
	~DNFDebugGUI();


	DNFDebugGUI(const DNFDebugGUI& _Other) = delete;
	DNFDebugGUI(const DNFDebugGUI&& _Other) noexcept = delete;
	DNFDebugGUI& operator=(const DNFDebugGUI& _Ohter) = delete;
	DNFDebugGUI& operator=(const DNFDebugGUI&& _Other) noexcept = delete;

	static void AddValue(const std::string _Name, int _Value)
	{
		DebugValue_int_.insert(std::make_pair(_Name, _Value));
	}
	static void AddValue(const std::string _Name, float _Value)
	{
		DebugValue_float_.insert(std::make_pair(_Name, _Value));
	}
	static void AddValue(const std::string _Name, float4 _Value)
	{
		DebugValue_float4_.insert(std::make_pair(_Name, _Value));
	}
	static void AddValue(const std::string _Name, std::string _Value)
	{
		DebugValue_string_.insert(std::make_pair(_Name, _Value));
	}
	static void AddMutableValue(const std::string _Name,float* _Value)
	{
		MutableValue_float_.insert(std::make_pair(_Name, _Value));
	}
	static void AddMutableValue(const std::string _Name, float4* _Value)
	{
		MutableValue_float4_.insert(std::make_pair(_Name, _Value));
	}


private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	static std::map<std::string, int> DebugValue_int_;
	static std::map<std::string, float> DebugValue_float_;
	static std::map<std::string, float4> DebugValue_float4_;
	static std::map<std::string, std::string> DebugValue_string_;

	static std::map<std::string, float*> MutableValue_float_;
	static std::map<std::string, float4*> MutableValue_float4_;


};

