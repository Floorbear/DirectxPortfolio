// #include "myshader.hlsli"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.

#include "TransformHeader.fx"
#include "RenderOption.fx"

// 0                                                                                                1 
// 0□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□1

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
    int GaugeType; // 0 : 플레이어 체력, Mp바 , 1: 스킬 쿨타임, 2:몬스터 HP바
    float Ratio; //
    float Ratio2; //
    int a1;
};


Output Gauge_VS(Input _Input)
{
    // -0.5, 0.5,     0.5 0.5
    // 0.5, 0.5,     0.5 0.5
    
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    // 버텍스가 몇번째 버텍스 인지 알수가 없다.
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
    if (GaugeType == 0) // HP & MP 바
    {
        float ClipYPos = 1.0f - Ratio;
        if (_Input.Tex.y < ClipYPos)
        {
            clip(-1);
        }
        return (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
    }
    else if (GaugeType == 1) //스킬 쿨타임
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
    else if (GaugeType == 2) //몬스터 HP바
    {
        float ClipXPos = Ratio;
        if (_Input.Tex.x > Ratio2)
        {
            clip(-1);
        }
        if (_Input.Tex.x > ClipXPos && _Input.Tex.x<Ratio2)
        {
            return (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
        }
        else
        {
            return (Tex.Sample(Smp, _Input.Tex.xy));
        }
    }


    return (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
}
