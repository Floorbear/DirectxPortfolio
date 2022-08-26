#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

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

	void UpdateGauge(float _Ratio); //������ŭ �������� ������Ʈ �ϴ� �Լ�

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
	AtlasData AtlasDataInst;

	void FrameDataReset();
};

