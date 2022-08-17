#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineBase/GameEngineMath.h>

class DNFAvatarGUI : public GameEngineGUIWindow
{
public:
	DNFAvatarGUI();
	~DNFAvatarGUI();


	DNFAvatarGUI(const DNFAvatarGUI& _Other) = delete;
	DNFAvatarGUI(const DNFAvatarGUI&& _Other) noexcept = delete;
	DNFAvatarGUI& operator=(const DNFAvatarGUI& _Ohter) = delete;
	DNFAvatarGUI& operator=(const DNFAvatarGUI&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
};

