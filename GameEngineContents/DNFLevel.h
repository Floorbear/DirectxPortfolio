#pragma once
#include <GameEngineCore/GameEngineLevel.h>

//������ �������� �ʿ��� ���� ����� ����� Ŭ����
class GameEngineCameraActor;
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

protected:
	void DNFStart();
	void DNFUpdate();

	//�������� ���� üũ �Լ�
	void ErrorCheck();

	void InitCamera(float4 _Pos, float _ZoomRate);

private:
	//���� üũ�� Bool �Լ�
	bool IsStart_;

	//�� ������
	float4 MapScale_;
	//������ �� �ִ� ����
	float4 CanMovingScale_;

};

