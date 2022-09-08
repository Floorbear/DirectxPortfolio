#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

struct GaugeData
{
	int GaugeType; // 0 : 플레이어 MP,HP , 1 : 스킬 쿨타임
	float Ratio; //게이지 비율
	float Ratio2; //하얗게 될 게이지 비율
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

	PixelData ColorData;
	GaugeData GaugeDataInst;

};

