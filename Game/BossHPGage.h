#pragma once
class BossHPGage : public IGameObject
{
public:
	BossHPGage();
	~BossHPGage();
	bool Start();
	void Update();

private:
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CFontRender* m_fontRender;

};

