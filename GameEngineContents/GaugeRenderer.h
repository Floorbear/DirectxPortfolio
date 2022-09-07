#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

struct GaugeData
{
	int IsBottomGauge; // 0은 아래서 위로 게이지가 사라짐, 1은 위에서 아래로 게이지가 사라짐
	int IsColorGauge; // 0 : TexCoord를 건들이는 게이지 1: Color를 건드리는 게이지
	float Ratio; //게이지 비율
	int a1;
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

	inline void SetGauge(int IsBottomGauge, int IsColorGauge)
	{
		GaugeDataInst.IsBottomGauge = IsBottomGauge;
		GaugeDataInst.IsColorGauge = IsColorGauge;
	}

	void UpdateGauge(float _Ratio); //비율만큼 게이지를 TexCoord좌표를 조절하는 함수
	void UpdateGauegeColor(float _Ratio, float4 _Color); //게이지 위에 _Color을 덮어씌우고 그 Color을 비율만큼 게이지처럼 보여주는 함수

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

};

