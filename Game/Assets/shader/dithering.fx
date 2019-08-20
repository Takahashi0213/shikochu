
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};
struct PointLig {
	float2 pos;
	float attn;
};
Texture2D<float4> sceneTexture : register(t0);	//�V�[���e�N�X�`���B
StructuredBuffer<PointLig> pointLights : register(t1);
sampler Sampler : register(s0);

//�f�B�U�p�^�[��
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
	float2 playerPos;
	float ligRange;
	int numPointLig;
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
	//���̃s�N�Z���̍��W�ɃA�X�y�N�g�␳��������
	float asspect = 9.0f / 16.0f;
	float2 pos = In.uv;
	pos -= 0.5f;
	pos *= 2.0f;
	pos.y *= asspect;
	float t = 0.0f;
	//�|�C���g���C�g�Ƃ̌v�Z
	for (int i = 0; i < numPointLig; i++) {
		//�|�C���g���C�g�Ƃ̌������v�Z����B
		float2 ptPos = pointLights[i].pos;
		ptPos.y *= asspect;

		float len = length( pointLights[i].pos - pos );
		/*if (len < pointLights[i].attn) {
			t += 1.0f;
		}*/
		float litRate = max( 0.0f, len / pointLights[i].attn);
		litRate *= litRate;
		t += pow( max( 0.0f, 1.0f - litRate ), 10.0f) * 0.5f;
	}
	
	
	//���S��������B
	float2 playerPosHosei = playerPos;
	playerPosHosei.y *= -asspect;
	float b = max( 0.0f, ligRange - length( pos - playerPosHosei) ) / ligRange;
	t += pow( b, 4.0f);

	t = min(1.0f, t);
	float4 color = sceneTexture.Sample(Sampler, In.uv);
	return lerp( float4( 0.0f, 0.0f, 0.0f, 1.0f), color, t);
}