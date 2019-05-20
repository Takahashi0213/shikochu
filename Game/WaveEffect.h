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

	CVector4 MulColor;

	const float WaveScale = 2.0f;
	const float DefPositionX = 1000.0f;

	float alf = 0.0f;
	float positionX = DefPositionX;
};

