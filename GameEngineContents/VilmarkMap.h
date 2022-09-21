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

protected:
	void Start() override;
	void InitRenderer();
	void Update(float _DeltaTime) override;
	void ChaseFarBackground();
	void DoorEffect(float _DeltaTime);
	void End() override;

	std::vector<GameEngineTextureRenderer*> RightDoor_Renderer_;// 0 : ��¦ 1: ���� 2: ����Ʈ
	GameEngineCollision* RightDoorCol_;
	Timer DoorEffect_Timer_;

	//Fade����
	GameEngineUIRenderer* FadeRenderer_;

private:
};
