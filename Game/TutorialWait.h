#pragma once
class TutorialWait : public IGameObject
{
	static TutorialWait* m_instance;
public:
	TutorialWait();
	~TutorialWait();
	bool Start();
	void Update();

private:

	void SelectUp();

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;

	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSoundSource* ss;

	int Timer = 0;
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };
	float Sentaku_Y = 0.0f;

	bool SelectNow = true; //ƒ}ƒ‹ƒoƒc
	bool DeleteFlag = false;
	int DeleteTimer = 0;
};

