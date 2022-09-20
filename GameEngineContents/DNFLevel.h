#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineMath.h>

//������ �������� �ʿ��� ���� ����� ����� Ŭ����
class GameEngineCameraActor;
class Player_Main;
class DNFBackground;
class MonsterHP;
class DNFHUD;
class DNFLevel : public GameEngineLevel
{
public:
	DNFLevel();
	~DNFLevel();

	DNFLevel(const DNFLevel& _Other) = delete;
	DNFLevel(const DNFLevel&& _Other) noexcept = delete;
	DNFLevel& operator=(const DNFLevel& _Ohter) = delete;
	DNFLevel& operator=(const DNFLevel&& _Other) noexcept = delete;

	GameEngineCameraActor* MainCamera_;

	void SetMapScale(const float4& _Scale);
	const float4& GetMapScale();

	inline Player_Main* GetPlayer()
	{
		return Player_;
	}

	inline float GetZoom()
	{
		return Zoom_;
	}

	inline DNFBackground* GetBackground()
	{
		return Background_;
	}

	template <typename BackgroundType>
	void CreateBackground()
	{
		Background_ = CreateActor<BackgroundType>();
	}

protected:
	void DNFStart();
	void DNFUpdate();

	//�������� ���� üũ �Լ�
	void ErrorCheck();

	void InitCamera(float4 _Pos, float _ZoomRate);

	void OnEvent() override;

	void LevelStartEvent() override;
	virtual void DNFOnEvent();
	Player_Main* Player_;
	DNFHUD* HUD_;
	MonsterHP* MonsterHP_;

private:
	//���� üũ�� Bool �Լ�
	bool IsStart_;

	//�� ������
	float4 MapScale_;

	//����HPBar

	DNFBackground* Background_;

	//������ ZoomRate
	float Zoom_;
};
