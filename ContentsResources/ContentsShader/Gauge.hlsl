// #include "myshader.hlsli"

// SV_POSITION �ø�ƽ
// �׷���ī�忡�� �̳༮�� �̷� �η��ϱ� �ϰ� �ڵ����� ó���ϴ� �༮�� ������ �ϰ�.

#include "TransformHeader.fx"
#include "RenderOption.fx"

// 0                                                                                                1 
// 0�������������������������������������������������������������������������������������������������1

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
};

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001


cbuffer GaugeData : register(b2)
{
    int IsBottomGauge; // 0�� �Ʒ��� ���� �������� �����, 1�� ������ �Ʒ��� �������� �����
    int IsSkillGauge;
    float Ratio; //������ ����
    int a1;
};


Output Gauge_VS(Input _Input)
{
    // -0.5, 0.5,     0.5 0.5
    // 0.5, 0.5,     0.5 0.5
    
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    // ���ؽ��� ���° ���ؽ� ���� �˼��� ����.
    // NewOutPut.Tex
    // 00    10
    
    //// 10    11
    
    //TextureFrameSize.x -= 0.5f;
    //TextureFrameSize.y -= 0.5f;
    //TextureFramePos.x -= 0.5f;
    //TextureFramePos.y -= 0.5f;
    
    NewOutPut.Tex.x = (_Input.Tex.x);

    NewOutPut.Tex.y = (_Input.Tex.y);
    
    return NewOutPut;
}

cbuffer ColorData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 Gauge_PS(Output _Input) : SV_Target0
{
    if (IsSkillGauge == 0)
    {
        if (IsBottomGauge == 1)
        {
            float ClipYPos = 1.0f - Ratio;
            if (_Input.Tex.y < ClipYPos)
            {
                clip(-1);
            }
        }
        return (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
    }
    else if (IsSkillGauge == 1)
    {
        float ClipYPos = 1.0f - Ratio;
        if (_Input.Tex.y > ClipYPos)
        {
            return (Tex.Sample(Smp, _Input.Tex.xy));
        }
        else
        {
            return (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
        }
    }


    return (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
}