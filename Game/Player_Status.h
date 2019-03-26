#pragma once
class Player_Status : public IGameObject
{
public:
	Player_Status();
	~Player_Status();

	bool Start();
	void Update();
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CSpriteRender*> m_spriteRenderHP;

private:
	prefab::CFontRender* m_fontRender;
	const CVector2 LifePivot = { 0.5f, 0.1f };//HPの基点
	const CVector2 ZankiPos = { -630.0f, 240.0f }; //残機数表示位置
	CVector4 LifeColor = { 1.0f,1.0f,1.0f,1.0f }; //HPバーの色
	float ZankiScale = 3.0f; //残機数表示サイズ



};

