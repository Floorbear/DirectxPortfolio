#include "PreCompile.h"
#include "GaugeRenderer.h"

GaugeRenderer::GaugeRenderer()
{
}

GaugeRenderer::~GaugeRenderer()
{
}

void GaugeRenderer::SetTexture(const std::string& _Name)
{
	CurTex = ShaderResources.SetTexture("Tex", _Name);
}

void GaugeRenderer::UpdateGauge(float _Ratio)
{
	GaugeDataInst.Ratio = _Ratio;
}

void GaugeRenderer::UpdateGauegeColor(float _Ratio, float4 _Color)
{
	GaugeDataInst.Ratio = _Ratio;
	ColorData.PlusColor = _Color;
}

void GaugeRenderer::Start()
{
	GameEngineDefaultRenderer::Start();
	PushRendererToUICamera();
	SetTextureRendererSetting();
}

void GaugeRenderer::SetTextureRendererSetting()
{
	SetPipeLine("Gauge");

	GaugeDataInst.GaugeType = 0;
	GaugeDataInst.Ratio = 1.0f;

	ShaderResources.SetConstantBufferLink("GaugeData", GaugeDataInst);
	ShaderResources.SetConstantBufferLink("ColorData", ColorData);
}

void GaugeRenderer::Update(float _Delta)
{
}
