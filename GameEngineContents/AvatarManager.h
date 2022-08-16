#pragma once
#include <string>
#include <list>
#include "DNFEnums.h"

//�ƹ�Ÿ �������̽� �Լ�
class GameEngineTextureRenderer;
class Player_Main;
class AvatarManager
{
public:
	AvatarManager();
	~AvatarManager();

	AvatarManager(const AvatarManager& _Other) = delete;
	AvatarManager(AvatarManager&& _Other) noexcept = delete;
	AvatarManager& operator=(const AvatarManager& _Other) = delete;
	AvatarManager& operator=(const AvatarManager&& _Other) = delete;

	//�ƹ�Ÿ ���ڿ� ������ Load�ϴ� �Լ�
	void LoadAvatar();

	//ĳ���� �������� �ƹ�Ÿ�� �������ִ� �Լ�
	//�ϰ� �÷��̾ �����ϸ� Player::Start�� �� �Լ��� ������ ȣ������� ��
	void LinkPlayerToAvatar(Player_Main* _Player);

	//�ƹ�Ÿ ����� �����ϴ� �Լ�
	//RenderList�� �ִ� �������� �ִϸ��̼��� �����Ѵ�
	void ChangeMotion(PlayerAnimations _Animation);

	//�ƹ�Ÿ �ٲܶ��� RenderList�� CurAvatar�� �ش������ Clear�ϰ� �����ؾ���
	//���⼭ ����� �������� ������ �׿� �������� �����ϴ�.
	//CurAvatar�� RenderList�� ������ �Ͼ
	void ChangeAvatar(AvatarType _Type, AvatarParts _Parts);

protected:

private:

	//�ƹ�Ÿ�� �����ϴ� �Լ� > �������� �ִϸ��̼��� �߰����ִ� �Լ�
	//����! ���� �ִϸ��̼��� ���� ������ ����
	void CreateAvatar(const std::string& _AvatarFolderName, AvatarParts _Parts, AvatarType _Type, AvatarLayer _Layer);

	std::string EnumToString(PlayerAnimations _Ani);
	std::string EnumToString(AvatarType _Type);

	//� �ƹ�Ÿ�� ���� �������� ������ Ȯ���ϴ� �Լ�
	std::vector<AvatarLayer> GetRendererLayer(AvatarParts _Parts, AvatarType _Type);
	//� �ƹ�Ÿ�� ���� �������� ��������(�������) Ȯ���ϴ� �Լ�
	std::vector<GameEngineTextureRenderer*> GetHideRendererList(AvatarParts _Parts, AvatarType _Type);



	//�������� ��ȯ�ϴ� �Լ�
	//���� HairRenderer_a�� ��������� �̰� switch�б⹮���� �����ϱ⿡�� ���ؼ� �Լ��� ����
	//����! ���� �б⸦ �������� ���� ����
	GameEngineTextureRenderer* GetRenderer(AvatarParts _Parts, AvatarLayer _Layer);

	float LayerOffset_;

	//�ƹ�Ÿ ������ �߰��ϸ� Ȯ���ؾ��� ��
	// 
	//�ƹ�Ÿ�Ŵ����� ������ �߰�
	//�ƹ�Ÿ �Ŵ��� LinkPlayerToAvatar ���� �������� ��ġ
	//ChangeMotion���� �ش� ������ �ִ��� Ȯ��
	//GetRenderer, SelectRenderer�� �ض� ������ �߰�
	//����Ʈ �ƹ�Ÿ�ϰ�� ������ ����Ʈ�� CurAvatar�� �߰����ֱ�

	GameEngineTextureRenderer* SkinRenderer_;
	GameEngineTextureRenderer* HairRenderer_a_;
	GameEngineTextureRenderer* HairRenderer_d_;
	GameEngineTextureRenderer* WeaponRenderer_b_;
	GameEngineTextureRenderer* WeaponRenderer_c_;

	GameEngineTextureRenderer* PantsRenderer_a_;
	GameEngineTextureRenderer* PantsRenderer_b_;
	GameEngineTextureRenderer* PantsRenderer_d_;

	GameEngineTextureRenderer* CoatRenderer_a_;
	GameEngineTextureRenderer* CoatRenderer_b_;
	GameEngineTextureRenderer* CoatRenderer_c_;
	GameEngineTextureRenderer* CoatRenderer_d_;


	GameEngineTextureRenderer* ShoesRenderer_a_;
	GameEngineTextureRenderer* ShoesRenderer_b_;

	GameEngineTextureRenderer* BeltRenderer_c_;
	GameEngineTextureRenderer* BeltRenderer_d_;

	GameEngineTextureRenderer* CapRenderer_a_;
	GameEngineTextureRenderer* CapRenderer_b_;
	GameEngineTextureRenderer* CapRenderer_c_;

	GameEngineTextureRenderer* ShadowRenderer_;


	//�� �ƹ�Ÿ�� �� �������� ����մϴٸ� �����ϴ� �����̳�
	//���⿡ �־���� ȭ�鿡 ������ �ȴ�
	//Renderer_b���� �Ⱦ��� �ƹ�Ÿ ������ ������
	//�׷��� �ƹ�Ÿ�� ����ϴ� �������� RenderList�� ����ؼ� �װ͸� �����ϰ� ����� �Ѱž�
	std::multimap<AvatarParts, GameEngineTextureRenderer*> RenderList_;

	//���� �����ϰ� �ִ� �ƹ�Ÿ�� ����
	std::map<AvatarParts, AvatarType> CurAvatar_;
};

