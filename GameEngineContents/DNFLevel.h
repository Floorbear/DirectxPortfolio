#pragma once
#include <GameEngineCore/GameEngineLevel.h>

//던파의 레벨에서 필요한 공통 기능을 담당할 클래스
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

	//레벨단위 에러 체크 함수
	void ErrorCheck();

	void CreateCamera(float4 _Pos, float _ZoomRate);

};

