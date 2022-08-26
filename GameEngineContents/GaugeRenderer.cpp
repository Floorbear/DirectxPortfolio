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
	AtlasDataInst.FrameData.PosY = (1.f-_Ratio);
	AtlasDataInst.PivotPos.y = -(1.0f-_Ratio);
}

void GaugeRenderer::Start()
{
	GameEngineDefaultRenderer::Start();
	PushRendererToUICamera();
	SetTextureRendererSetting();
}

void GaugeRenderer::SetTextureRendererSetting()
{
	SetPipeLine("TextureAtlas");

	AtlasDataInst.FrameData.PosX = 0.0f;
	AtlasDataInst.FrameData.PosY = 0.0f;
	AtlasDataInst.FrameData.SizeX = 1.0f;
	AtlasDataInst.FrameData.SizeY = 1.0f;
	AtlasDataInst.PivotPos = float4::ZERO;

	ShaderResources.SetConstantBufferLink("AtlasData", AtlasDataInst);
	ShaderResources.SetConstantBufferLink("ColorData", ColorData);
}

void GaugeRenderer::Update(float _Delta)
{
}
