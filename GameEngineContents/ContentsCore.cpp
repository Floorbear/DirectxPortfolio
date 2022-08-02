#include "PreCompile.h"
#include "ContentsCore.h"

#include "GameEngineContents/SeriaRoom.h"
#include "GameEngineContents/Elvenguard.h"
#include "GameEngineContents/Elvenguard_Front.h"
#include "Bar.h"

#include "Vilmark_0.h"

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

	//Key 초기화
	GameEngineInput::GetInst()->CreateKey("1", 0x31);
	GameEngineInput::GetInst()->CreateKey("2", 0x32);
	GameEngineInput::GetInst()->CreateKey("3", 0x33);
	GameEngineInput::GetInst()->CreateKey("4", 0x34);
	GameEngineInput::GetInst()->CreateKey("5", 0x35);
	GameEngineInput::GetInst()->CreateKey("6", 0x36);



	GameEngineInput::GetInst()->CreateKey("Z", 'Z');
	GameEngineInput::GetInst()->CreateKey("X", 'X');
	GameEngineInput::GetInst()->CreateKey("C", 'C');
	GameEngineInput::GetInst()->CreateKey("Q", 'Q');
	GameEngineInput::GetInst()->CreateKey("W", 'W');
	GameEngineInput::GetInst()->CreateKey("E", 'E');



	GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);
	GameEngineInput::GetInst()->CreateKey("Up", VK_UP);
	GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);


	//노말 텍스처 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("NormalTexture");

		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			std::vector<GameEngineFile> Shaders = Dir_i.GetAllFile();

			for (size_t i = 0; i < Shaders.size(); i++)
			{
				GameEngineTexture::Load(Shaders[i].GetFullPath());
			}
		}
	}

	//폴더 텍스처 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("FolderTexture");

		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
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


	//CreateLevel<SeriaRoom>("SeriaRoom");
	//CreateLevel<Elvenguard>("Elvenguard");
	//CreateLevel<Elvenguard_Front>("Elvenguard_Front");
	//CreateLevel<Bar>("Bar");

	CreateLevel<Vilmark_0>("Vilmark_0");
	//CreateLevel<State0>("Title");
	//CreateLevel<State1>("Title");
	ChangeLevel("Vilmark_0");



	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
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
	if (GameEngineInput::GetInst()->IsDown("MoveVilmark") == true)
	{
		ChangeLevel("Vilmark_0");
	}
	if (GameEngineInput::GetInst()->IsDown("MoveBar") == true)
	{
		ChangeLevel("Bar");
	}

	
}

void ContentsCore::End()
{
	int a = 0;
}