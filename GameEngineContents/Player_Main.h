#pragma once
#include "DNFRenderObject.h"
#include "AvatarManager.h"

class Player_Main : public DNFRenderObject
{
	friend AvatarManager;
public:
	Player_Main();
	~Player_Main();


	Player_Main(const Player_Main& _Other) = delete;
	Player_Main(const Player_Main&& _Other) noexcept = delete;
	Player_Main& operator=(const Player_Main& _Ohter) = delete;
	Player_Main& operator=(const Player_Main&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	AvatarManager AvatarManager_;

	GameEngineTextureRenderer* HairRenderer_a_;
	GameEngineTextureRenderer* HairRenderer_d_;
	GameEngineTextureRenderer* WeaponRenderer_b_;
	GameEngineTextureRenderer* WeaponRenderer_c_;

	GameEngineTextureRenderer* PantsRenderer_a_;
	GameEngineTextureRenderer* PantsRenderer_b_;
	GameEngineTextureRenderer* PantsRenderer_d_;

	//�ƹ�Ÿ ������ �߰��ϸ� Ȯ���ؾ��� ��
	//�ƹ�Ÿ�Ŵ����� ������ �߰�
	//�ƹ�Ÿ �Ŵ��� LinkPlayerToAvatar ���� �������� ��ġ
	//ChangeMotion���� �ش� ������ �ִ��� Ȯ��
	//GetRenderer, SelectRenderer�� �ض� ������ �߰�


	bool QToggle_;
	bool WToggle_;
};

