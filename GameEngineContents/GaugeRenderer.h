#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

struct GaugeData
{
	int IsBottomGauge; // 0�� �Ʒ��� ���� �������� �����, 1�� ������ �Ʒ��� �������� �����
	int IsColorGauge; // 0 : TexCoord�� �ǵ��̴� ������ 1: Color�� �ǵ帮�� ������
	float Ratio; //������ ����
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

	void UpdateGauge(float _Ratio); //������ŭ �������� TexCoord��ǥ�� �����ϴ� �Լ�
	void UpdateGauegeColor(float _Ratio, float4 _Color); //������ ���� _Color�� ������ �� Color�� ������ŭ ������ó�� �����ִ� �Լ�

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

