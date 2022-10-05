#include "PreCompile.h"
#include "ContentsCore.h"

#include "DNFDebugGUI.h"
#include "DNFAvatarGUI.h"

#include <GameEngineBase/GameEngineSound.h>
#include "GameEngineContents/SeriaRoom.h"
#include "GameEngineContents/Elvenguard.h"
#include "GameEngineContents/Elvenguard_Front.h"
#include "Bar.h"

#include "VilmarkLevel.h"

#include "Vilmark_0.h"
#include "Vilmark_1.h"
#include "Vilmark_2.h"
#include "Vilmark_3.h"
#include "Vilmark_4.h"
#include "Vilmark_5.h"

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

	GameEngineInput::GetInst()->CreateKey("A", 'A');
	GameEngineInput::GetInst()->CreateKey("S", 'S');
	GameEngineInput::GetInst()->CreateKey("D", 'D');
	GameEngineInput::GetInst()->CreateKey("F", 'F');

	GameEngineInput::GetInst()->CreateKey("Q", 'Q');
	GameEngineInput::GetInst()->CreateKey("W", 'W');
	GameEngineInput::GetInst()->CreateKey("E", 'E');
	GameEngineInput::GetInst()->CreateKey("R", 'R');

	GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);
	GameEngineInput::GetInst()->CreateKey("Up", VK_UP);
	GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
	GameEngineInput::GetInst()->CreateKey("Shift", VK_LSHIFT);

	//노말 텍스처 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
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

	//아바타 텍스처 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("AvatarTexture");

		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}

	//이펙트 텍스처 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("EffectTexture");
		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}

	//UI 텍스처 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("FolderTexture");
		Dir.Move("UITexture");
		std::vector<GameEngineDirectory> Dirs = Dir.GetRecursiveAllDirectory();
		for (GameEngineDirectory Dir_i : Dirs)
		{
			GameEngineFolderTexture::Load(Dir_i.GetFullPath());
		}
	}

	//BGM 사운드 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Sounds");
		Dir.Move("Bgm");

		std::vector<GameEngineFile> Sounds = Dir.GetAllFile();

		for (size_t i = 0; i < Sounds.size(); i++)
		{
			GameEngineSound::LoadRessource(Sounds[i].GetFullPath());
		}
	}

	//쉐이더 컴파일
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("ContentsShader");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile("hlsl");

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineShader::AutoCompile(Shaders[i].GetFullPath());
		}
	}

	//랜파생성
	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Gauge");
		NewPipe->SetVertexShader("Gauge.hlsl");
		NewPipe->SetPixelShader("Gauge.hlsl");
	}

	CreateLevel<SeriaRoom>("SeriaRoom");
	CreateLevel<Elvenguard>("Elvenguard");
	//CreateLevel<Elvenguard_Front>("Elvenguard_Front");
	//CreateLevel<Bar>("Bar");

	CreateLevel<Vilmark_0>("Vilmark_0");
	CreateLevel<Vilmark_1>("Vilmark_1");
	CreateLevel<Vilmark_2>("Vilmark_2");
	CreateLevel<Vilmark_3>("Vilmark_3");
	CreateLevel<Vilmark_4>("Vilmark_4");
	CreateLevel<Vilmark_5>("Vilmark_5");

	ChangeLevel("SeriaRoom");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
	GameEngineGUI::CreateGUIWindow<DNFDebugGUI>("DNFDebug", nullptr);
	GameEngineGUI::CreateGUIWindow<DNFAvatarGUI>("DNFAvatar", nullptr);
}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
	int a = 0;
}