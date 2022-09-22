#pragma once
#include "DNFMonster.h"

class TauCaptain : public DNFMonster
{
public:
	TauCaptain();
	~TauCaptain();

	TauCaptain(const TauCaptain& _Other) = delete;
	TauCaptain(const TauCaptain&& _Other) noexcept = delete;
	TauCaptain& operator=(const TauCaptain& _Ohter) = delete;
	TauCaptain& operator=(const TauCaptain&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc) override;
	void ChangeDNFAnimation(const std::string& _Name) override;
	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;
	void InitAdditionalRenderer() override;

	std::string CheckAdditionalPattern(float _DeltaTime) override;

	GameEngineTextureRenderer* WeaponRenderer_;
};
