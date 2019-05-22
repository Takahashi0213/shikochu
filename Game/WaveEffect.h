#pragma once
class WaveEffect : public IGameObject
{
public:
	WaveEffect();
	~WaveEffect();
	bool Start();
	void Update();

private:

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;

	prefab::CSpriteRender* r;
	prefab::CFontRender* f;

	float ScaleY = 0.0f;

	int Timer = 0;
	int Wave = 0;
	int MaxWave = 0;
	
	CVector4 MulColor;

	float alf = 0.0f;
	float Accalf = 0.0f; //アクセサリー用Alpha値

	//アクセサリー用変数
	float AccX1 = 0.0f;
	float AccX2 = 1280.0f;
	float AccX3 = 0.0f;
	float AccX4 = -1280.0f;
	float AccX5 = 0.0f;
	float AccX6 = -1280.0f;
	float AccX7 = 0.0f;
	float AccX8 = 1280.0f;

	//定数
	const int DeleteTimer = 48;
	const float WaveScale = 2.0f;
	const float DefPositionX = 1000.0f;

	float positionX = DefPositionX;

};

