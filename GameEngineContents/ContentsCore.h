#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>

// 설명 : 프로그램 자체를 시작하게 한다.
class ContentsCore : public GameEngineCore
{
public:
	// constrcuter destructer
	ContentsCore(); 
	~ContentsCore(); 
	
	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;


	std::string GetWindowTitle() override
	{
		return "DnF";
	}

	//윈도우 위치 초기화
	float4 StartWindowPosition() override
	{
		return { 0,0 };
	}


protected:
	void Start() override;

	// 이 프로그램이 어느 상황에서건 계속 Update하면서 체크할일이 있다면 여기서 한다.
	// 서버가 붙지 않으면 그럴일은 없다. 게임이 무슨 레벨이건 뭐건 무슨키를 누르면 종료한다.
	// 타이틀을 넘기거나 이런
	void Update(float _DeltaTime) override;

	void End() override;

private:

};

