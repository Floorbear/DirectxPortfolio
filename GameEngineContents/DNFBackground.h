#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"

class GameEngineActor;
class GameEngineTextureRenderer;
//Background�� �̸��� �߿��ϴ�! �� Map�̸��� Ȯ���� ���Ͱ� �����ϰ� ����
class DNFBackground : public GameEngineActor
{
public:
	DNFBackground();
	~DNFBackground();

	DNFBackground(const DNFBackground& _Other) = delete;
	DNFBackground(const DNFBackground&& _Other) noexcept = delete;
	DNFBackground& operator=(const DNFBackground& _Ohter) = delete;
	DNFBackground& operator=(const DNFBackground&& _Other) noexcept = delete;

	//void CreateColRenderer(std::string _Name);
	inline GameEngineTextureRenderer* GetColRenderer()
	{
		return ColRenderer;
	}

	void StartFadeIn()
	{
		FadeInTimer_.StartTimer(1.0f);
	}
	void StartFadeOut()
	{
		FadeOutTimer_.StartTimer(1.0f);
	}
protected:
	void InitBackground(const std::string& _FileName);

	GameEngineTextureRenderer* MainRenderer_;
	GameEngineTextureRenderer* BushRenderer_;
	GameEngineTextureRenderer* ColRenderer;
	GameEngineTextureRenderer* FarRenderer_;

	float FarSpeed_;
	float4 PrevCameraPos_;

	//Fade����
	GameEngineUIRenderer* FadeRenderer_;
	Timer FadeInTimer_;
	Timer FadeOutTimer_;

private:
};
