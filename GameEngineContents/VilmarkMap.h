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

	std::vector<GameEngineTextureRenderer*> RightDoor_Renderer_;// 0 : ¹®Â¦ 1: ´ãÀå 2: ÀÌÆåÆ®
	GameEngineCollision* RightDoorCol_;
	Timer DoorEffect_Timer_;

	//Fade°ü·Ã
	GameEngineUIRenderer* FadeRenderer_;

private:
};
