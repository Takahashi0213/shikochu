#pragma once
class Player_Status : public IGameObject
{
public:
	Player_Status();
	~Player_Status();

	bool Start();
	void Update();
	void PostRender(CRenderContext& rc);

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CSpriteRender*> m_spriteRenderHP;

private:
	CFont m_font;
	const CVector2 LifePivot = { 0.0f, 1.0f };//HP‚ÌŠî“_

};

