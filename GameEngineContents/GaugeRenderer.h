#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

struct GaugeData
{
	int IsBottomGauge; // 0은 아래서 위로 게이지가 사라짐, 1은 위에서 아래로 게이지가 사라짐
	float Ratio; //게이지 비율
	//더미
	int a1;
	int a2;
};
class GaugeRenderer : public GameEngineDefaultRenderer
{
public:
	GaugeRenderer();
	~GaugeRenderer();


	GaugeRenderer(const GaugeRenderer& _Other) = delete;
	GaugeRenderer(const GaugeRenderer&& _Other) noexcept = delete;
	GaugeRenderer& operator=(const GaugeRenderer& _Ohter) = delete;
	GaugeRenderer& operator=(const GaugeRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string& _Name);


	ColorData& GetColorData()
	{
		return ColorData;
	}

	void UpdateGauge(float _Ratio); //비율만큼 게이지를 업데이트 하는 함수

protected:
	void Start() override;

	void SetTextureRendererSetting();

	void Update(float _Delta) override;

private:
	PIVOTMODE PivotMode;
	SCALEMODE ScaleMode;
	float ScaleRatio;

	GameEngineTexture* CurTex;

	ColorData ColorData;
	GaugeData GaugeDataInst;

	void FrameDataReset();
};

