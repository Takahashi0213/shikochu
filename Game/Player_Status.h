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
	const CVector2 StarPivot = { 0.5f, 0.0f };//流星バーの基点

	bool StarMaxFlag = false; //マックスアイコン表示フラグ
	float StarMaxColor = 1.0f; //マックスアイコンの白さ
	bool StarMaxColorFlag = false; //マックスアイコンの色味が往復ループするので
	float StarMaxScale = 1.0f; //マックスアイコンの拡大率

	const CVector2 ZankiPos = { -645.0f, 255.0f }; //残機数表示位置
	const float ZankiPosXHosei = 40.0f; //残機が１桁の時X位置を補正
	CVector4 LifeColor = { 1.0f,1.0f,1.0f,1.0f }; //HPバーの色
	CVector4 StarColor = { 1.0f,1.0f,1.0f,1.0f }; //流星バーの色
	const float ZankiScale = 3.0f; //残機数表示サイズ

};

