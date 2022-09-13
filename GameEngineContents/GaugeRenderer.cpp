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

void GaugeRenderer::SetTexture(GameEngineTexture* _Texture)
{
	CurTex = _Texture;
	ShaderResources.SetTexture("Tex", _Texture);
}

void GaugeRenderer::SetFolderTextureToIndex(const std::string& _Text, UINT _Index)
{
	GameEngineFolderTexture* FolderTexture = GameEngineFolderTexture::Find(_Text);

	SetTexture(FolderTexture->GetTexture(_Index));
}

void GaugeRenderer::ScaleToTexture()
{
	float4 Scale = CurTex->GetScale();

	if (0 > GetTransform().GetLocalScale().x)
	{
		Scale.x = -Scale.x;
	}

	if (0 > GetTransform().GetLocalScale().y)
	{
		Scale.y = -Scale.y;
	}

	GetTransform().SetLocalScale(Scale * ScaleRatio);
}

void GaugeRenderer::UpdateGauge(float _Ratio)
{
	GaugeDataInst.Ratio = _Ratio;
}

void GaugeRenderer::UpdateMonsterHP(float _Ratio , float _PrevRatio)
{
	GaugeDataInst.Ratio = _Ratio;
	GaugeDataInst.Ratio2 = _PrevRatio;

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
