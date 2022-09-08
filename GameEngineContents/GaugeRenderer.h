#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

struct GaugeData
{
	int GaugeType; // 0 : �÷��̾� MP,HP , 1 : ��ų ��Ÿ��
	float Ratio; //������ ����
	float Ratio2; //�Ͼ�� �� ������ ����
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


	PixelData& GetColorData()
	{
		return ColorData;
	}

	inline void SetGauge(int _Type)
	{
		GaugeDataInst.GaugeType = _Type;
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

	PixelData ColorData;
	GaugeData GaugeDataInst;

};

