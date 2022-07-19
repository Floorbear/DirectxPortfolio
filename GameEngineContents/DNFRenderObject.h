#pragma once
#include <GameEngineCore/GameEngineActor.h>

//렌더러를 가지는 액터들은 이 클래스를 상속 받는다.
//스프라이트 리소스를 좀 더 활용하기 용이하게 하기위한 클래스
class DNFRenderObject : public GameEngineActor
{
public:
	DNFRenderObject();
	~DNFRenderObject();


	DNFRenderObject(const DNFRenderObject& _Other) = delete;
	DNFRenderObject(const DNFRenderObject&& _Other) noexcept = delete;
	DNFRenderObject& operator=(const DNFRenderObject& _Ohter) = delete;
	DNFRenderObject& operator=(const DNFRenderObject&& _Other) noexcept = delete;

protected:
	GameEngineTextureRenderer* MainRenderer_;
	
	//세팅이 안된것을 체크 해 주는 함수
	void ErrorCheck();

	//하는 역할
	//1. 에러 체크
	void DNFUpdate();

	//하는 역할
	//1. MainRenderer 생성
	void DNFStart();

private:
	bool IsStart_; //DnfStart 호출했냐

};

