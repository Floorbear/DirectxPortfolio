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

	GameEngineCameraActor* Camera_;

protected:
	void DNFStart();
	void DNFUpdate();

	//�������� ���� üũ �Լ�
	void ErrorCheck();

	void CreateCamera(float4 _Pos, float _ZoomRate);

};

