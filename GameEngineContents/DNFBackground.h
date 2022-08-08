#pragma once
#include <GameEngineCore/GameEngineActor.h>

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
protected:
	void InitBackground(const std::string& _FileName);

	GameEngineTextureRenderer* MainRenderer_;
	GameEngineTextureRenderer* ColRenderer;

private:
};

