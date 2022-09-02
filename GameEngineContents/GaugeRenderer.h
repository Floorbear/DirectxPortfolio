#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

struct GaugeData
{
	int IsBottomGauge; // 0�� �Ʒ��� ���� �������� �����, 1�� ������ �Ʒ��� �������� �����
	float Ratio; //������ ����
	//����
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
	GaugeData GaugeDataInst;

	void FrameDataReset();
};

