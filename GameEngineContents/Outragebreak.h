#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"

class Outragebreak : public GameEngineActor
{
public:
	Outragebreak();
	~Outragebreak();

	Outragebreak(const Outragebreak& _Other) = delete;
	Outragebreak(const Outragebreak&& _Other) noexcept = delete;
	Outragebreak& operator=(const Outragebreak& _Ohter) = delete;
	Outragebreak& operator=(const Outragebreak&& _Other) noexcept = delete;

protected:
	void Start() override;
	void BloodFunction(int _Index);
	void Update(float _DeltaTime) override;
	void StiffnessUpdate(float _DeltaTime);
	void End() override;

	float GetDirX();

private:
	std::map<std::string, GameEngineTextureRenderer*> AllRenderer_;
	std::list<GameEngineTextureRenderer*> FloorRenderer_;
	std::vector<GameEngineTextureRenderer*> BloodRenderer_;
	std::vector<float4> BloodPos_{ {-210,50,-20},{-160,0,-25} ,{-100,-20,-30},{-40,25,-25} ,{-10,70,-20} };
	std::vector<Timer*> BloodStartTimer_;
	std::vector<int> LoopCount_ = { 0,0,0,0,0 };

	std::map<std::string, float> AllAlpha_;

	Timer Phase1Timer_ = 0.6f;
	Timer ShakeTimer_ = 0.2f;
	Timer AttTimer_ = 0.2f;

	int ShakeLoop_ = 0;

	int AttLoop_ = 0;

	int Phase_ = 0;

	bool IsAttackEnd_ = false;
	//Phase 0 : ¹Ù´ÚÀÌ »ı±è
	// 1 : Àá½Ã ±â´Ù¸²
	// 2 : »¡°£ Æ´ÀÌ Á¡Á¡ºÓ¾îÁö°í, ³ë¶õ Æ´ÀÌ »ı±è
	// 3 : Ç÷±â°¡ ¹æÃâµÊ
	// 4: Ç÷±â ¹æÃâÀÌ ³¡³ª°í Floor°¡ Á¡Á¡ Èñ¹ÌÇØÁü
	//
};
