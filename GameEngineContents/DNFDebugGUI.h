#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class DNFDebugGUI : public GameEngineGUIWindow
{
public:
	DNFDebugGUI();
	~DNFDebugGUI();


	DNFDebugGUI(const DNFDebugGUI& _Other) = delete;
	DNFDebugGUI(const DNFDebugGUI&& _Other) noexcept = delete;
	DNFDebugGUI& operator=(const DNFDebugGUI& _Ohter) = delete;
	DNFDebugGUI& operator=(const DNFDebugGUI&& _Other) noexcept = delete;

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

};

