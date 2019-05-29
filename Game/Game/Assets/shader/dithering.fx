
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> sceneTexture : register(t0);	//シーンテクスチャ。
sampler Sampler : register(s0);

//ディザパターン
static const int pattern[] = {
    0, 32,  8, 40,  2, 34, 10, 42,   /* 8x8 Bayer ordered dithering  */
    48, 16, 56, 24, 50, 18, 58, 26,  /* pattern.  Each input pixel   */
    12, 44,  4, 36, 14, 46,  6, 38,  /* is scaled to the 0..63 range */
    60, 28, 52, 20, 62, 30, 54, 22,  /* before looking in this table */
    3, 35, 11, 43,  1, 33,  9, 41,   /* to determine the action.     */
    51, 19, 59, 27, 49, 17, 57, 25,
    15, 47,  7, 39, 13, 45,  5, 37,
    63, 31, 55, 23, 61, 29, 53, 21 
};

cbuffer cbParam : register( b0 )
{
	float ligRange;
};

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

float4 PSMain( PSInput In ) : SV_Target0
{
	float asspect = 9.0f / 16.0f;
	
	float2 pos = In.uv;
	pos -= 0.5f;
	pos *= 2.0f;
	pos.y *= asspect;
	float t = max( 0.0f, ligRange - length( pos ) ) / ligRange;
	t = pow( t, 4.0f);
	float4 color = sceneTexture.Sample(Sampler, In.uv);
	
	return lerp( float4( 0.0f, 0.0f, 0.0f, 1.0f), color, t);
}