#include "PreCompile.h"
#include "ContentsCore.h"

#include "GameEngineContents/SeriaRoom.h"
#include "GameEngineContents/Elvenguard.h"

#include "GameEngineContents/LoginLevel.h"
#include "GameEngineContents/PlayLevel.h"

#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore() 
	: GameEngineCore()
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{

	{
		//GameEngineDirectory Dir;
		//Dir.MoveParentToExitsChildDirectory("ConstantResources");
		//Dir.Move("ConstantResources");
		//Dir.Move("Texture");
		//Dir.Move("Login");

		//std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		//for (size_t i = 0; i < Shaders.size(); i++)
		//{
		//	GameEngineTexture::Load(Shaders[i].GetFullPath());
		//}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	//Dir.Move("BlackSet");
	//GameEngineFolderTexture::Load(Dir.GetFullPath());

	// 이걸 해줘야 합니다.
	// GameEngineTexture::Cut("Boss_Left.bmp", 5, 7);


	//키 생성
	GameEngineInput::GetInst()->CreateKey("MoveSeriaRoom", VK_NUMPAD1);
	GameEngineInput::GetInst()->CreateKey("MoveElvenguard", VK_NUMPAD2);
	GameEngineInput::GetInst()->CreateKey("MoveElvenguard_Front", VK_NUMPAD3);
	GameEngineInput::GetInst()->CreateKey("MoveVilmark", VK_NUMPAD4);
	GameEngineInput::GetInst()->CreateKey("MoveBar", VK_NUMPAD5);

	// 리소스를 로드하는데.

	// RTTI 런 타임 타입 인포메이션
	CreateLevel<SeriaRoom>("SeriaRoom");
	CreateLevel<Elvenguard>("Elvenguard");
	//CreateLevel<State0>("Title");
	//CreateLevel<State1>("Title");
	ChangeLevel("SeriaRoom");

	// 게임컨텐츠 정의
	// 이 게임에는 타이틀화면
	//            스테이지1
	//            스테이지2
}

void ContentsCore::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("MoveSeriaRoom") == true)
	{
		ChangeLevel("SeriaRoom");
	}
	if (GameEngineInput::GetInst()->IsDown("MoveElvenguard") == true)
	{
		ChangeLevel("Elvenguard");
	}
	if (GameEngineInput::GetInst()->IsDown("MoveElvenguard_Front") == true)
	{
		ChangeLevel("Elvenguard_Front");
	}

	
}

void ContentsCore::End()
{
	int a = 0;
}