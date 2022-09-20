#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineMath.h>

//던파의 레벨에서 필요한 공통 기능을 담당할 클래스
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

	//레벨단위 에러 체크 함수
	void ErrorCheck();

	void InitCamera(float4 _Pos, float _ZoomRate);

	void OnEvent() override;

	void LevelStartEvent() override;
	virtual void DNFOnEvent();
	Player_Main* Player_;
	DNFHUD* HUD_;
	MonsterHP* MonsterHP_;

private:
	//에러 체크용 Bool 함수
	bool IsStart_;

	//맵 스케일
	float4 MapScale_;

	//몬스터HPBar

	DNFBackground* Background_;

	//레벨의 ZoomRate
	float Zoom_;
};
