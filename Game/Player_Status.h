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
	const CVector2 LifePivot = { 0.5f, 0.1f };//HP�̊�_
	const CVector2 ZankiPos = { -630.0f, 240.0f }; //�c�@���\���ʒu
	CVector4 LifeColor = { 1.0f,1.0f,1.0f,1.0f }; //HP�o�[�̐F
	float ZankiScale = 3.0f; //�c�@���\���T�C�Y



};

