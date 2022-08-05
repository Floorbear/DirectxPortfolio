#pragma once
#include "DNFRenderObject.h"

class DNFRenderObject;
class GameEngineTextureRenderer;
//Background의 이름은 중요하다! 꼭 Map이름에 확장자 뗀것과 동일하게 하자
class DNFBackground : public DNFRenderObject
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

	
	GameEngineTextureRenderer* ColRenderer;

private:
};

