#pragma once
#include "DNFBackground.h"
#include "DNFMath.h"

class VilmarkMap : public DNFBackground
{
public:
	VilmarkMap();
	~VilmarkMap();

	VilmarkMap(const VilmarkMap& _Other) = delete;
	VilmarkMap(const VilmarkMap&& _Other) noexcept = delete;
	VilmarkMap& operator=(const VilmarkMap& _Ohter) = delete;
	VilmarkMap& operator=(const VilmarkMap&& _Other) noexcept = delete;

	void OnDoor();
	void MakeLeftDoor();//���� ���� ���� �༮�鵵 �ֱ� ������, ���� ���� ����� �Լ��� ȣ������
	void MakeRightDoor();
	void MakeLogo();

protected:
	void Start() override;
	void InitRenderer();
	void Update(float _DeltaTime) override;
	void ChaseFarBackground();
	void DoorEffect(float _DeltaTime);
	void End() override;

	int LogoLoopCount_ = 0;
	GameEngineUIRenderer* VilmarkLogo_;

	std::vector<GameEngineTextureRenderer*> RightDoor_Renderer_;// 0 : ��¦ 1: ���� 2: ����Ʈ
	std::vector<GameEngineTextureRenderer*> LeftDoor_Renderer_;// 0 : ��¦ 1: ���� 2: ����Ʈ

	GameEngineCollision* RightDoorCol_;
	GameEngineCollision* LeftDoorCol_;
	Timer DoorEffect_Timer_;

private:
};
