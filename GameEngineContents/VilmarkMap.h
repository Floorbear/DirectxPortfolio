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
	void MakeLeftDoor();//왼쪽 문이 없는 녀석들도 있기 때문에, 왼쪽 문을 만드는 함수를 호출하자
	void MakeRightDoor();

protected:
	void Start() override;
	void InitRenderer();
	void Update(float _DeltaTime) override;
	void ChaseFarBackground();
	void DoorEffect(float _DeltaTime);
	void End() override;

	std::vector<GameEngineTextureRenderer*> RightDoor_Renderer_;// 0 : 문짝 1: 담장 2: 이펙트
	std::vector<GameEngineTextureRenderer*> LeftDoor_Renderer_;// 0 : 문짝 1: 담장 2: 이펙트

	GameEngineCollision* RightDoorCol_;
	GameEngineCollision* LeftDoorCol_;
	Timer DoorEffect_Timer_;

private:
};
