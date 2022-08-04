#pragma once
#include <GameEngineCore/GameEngineLevel.h>

//������ �������� �ʿ��� ���� ����� ����� Ŭ����
class GameEngineCameraActor;
class Player_Main;
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

protected:
	void DNFStart();
	void DNFUpdate();

	//�������� ���� üũ �Լ�
	void ErrorCheck();

	void InitCamera(float4 _Pos, float _ZoomRate);

	void OnEvent() override;

private:
	//���� üũ�� Bool �Լ�
	bool IsStart_;

	//������ �ִ� �÷��̾�
	Player_Main* Player_;

	//�� ������
	float4 MapScale_;

	//������ �� �ִ� ����
	float4 CanMovingScale_;

	//������ ZoomRate
	float Zoom_;
};

