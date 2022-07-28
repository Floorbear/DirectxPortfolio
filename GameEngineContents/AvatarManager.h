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
	void LinkPlayerToAvatar(Player_Main* _Player);

	//�ƹ�Ÿ ����� �����ϴ� �Լ�
	void ChangeMotion(PlayerAnimations _Animation);

protected:

private:

	//�ƹ�Ÿ�� �����ϴ� �Լ� > �������� �ִϸ��̼��� �߰����ִ� �Լ�
	//����! ���� �ִϸ��̼��� ���� ������ ����
	void CreateAvatar(const std::string& _AvatarFolderName, AvatarParts _Parts, AvatarType _Type, AvatarLayer _Layer);

	std::string EnumToString(PlayerAnimations _Ani);
	std::string EnumToString(AvatarType _Type);


	//�������� �����ϴ� �Լ�
	//����! ���� �б⸦ �������� ���� ����
	GameEngineTextureRenderer* SelectRenderer(AvatarParts _Parts, AvatarLayer _Layer);

	float LayerOffset_;
	GameEngineTextureRenderer* SkinRenderer_;
	GameEngineTextureRenderer* HairRenderer_a_;
	GameEngineTextureRenderer* HairRenderer_d_;
	GameEngineTextureRenderer* WeaponRenderer_b_;
	GameEngineTextureRenderer* WeaponRenderer_c_;

	GameEngineTextureRenderer* PantsRenderer_a_;
	GameEngineTextureRenderer* PantsRenderer_b_;

	//ȭ�鿡 ������ �Ǵ� ������
	std::multimap<AvatarParts, GameEngineTextureRenderer*> RenderList_;

	//���� �԰��ִ� �ƹ�Ÿ Ÿ��
	std::map<AvatarParts, AvatarType> CurAvatar_;
};

