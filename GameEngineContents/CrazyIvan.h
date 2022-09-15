#pragma once
#include "DNFMonster.h"

class CrazyIvan : public DNFMonster
{
public:
	CrazyIvan();
	~CrazyIvan();

	CrazyIvan(const CrazyIvan& _Other) = delete;
	CrazyIvan(const CrazyIvan&& _Other) noexcept = delete;
	CrazyIvan& operator=(const CrazyIvan& _Ohter) = delete;
	CrazyIvan& operator=(const CrazyIvan&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void CreateMonsterAni() override;
	void CreateMonsterAniFunc() override;
};
