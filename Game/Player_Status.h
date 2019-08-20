#pragma once

class Player_Status : public IGameObject
{
	static Player_Status* m_instance;
public:
	Player_Status();
	~Player_Status();

	bool Start();
	void Update();

	//インスタンスの取得
	static Player_Status* Player_Status::GetInstance() {
		return m_instance;
	}

private:

	void SkillSetUp();
	void SkillUpdate(); //スキル色々更新用

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CSpriteRender*> m_spriteRenderBar;
	prefab::CFontRender* m_fontRender; //残機用
	prefab::CFontRender* m_fontRender_bonus; //ボーナス文字用

	const CVector2 LifePivot = { 0.5f, 0.9f };//HPの基点
	const CVector2 LifePivot2 = { 0.5f, 0.1f };//HPの基点
	const CVector2 StarPivot = { 0.5f, 0.0f };//流星バーの基点

	bool StarMaxFlag = false; //マックスアイコン表示フラグ
	float StarMaxColor = 1.0f; //マックスアイコンの白さ
	bool StarMaxColorFlag = false; //マックスアイコンの色味が往復ループするので
	float StarMaxScale = 1.0f; //マックスアイコンの拡大率

	const CVector2 ZankiPos = { -565.0f, 300.0f }; //残機数表示位置
	const float ZankiPosXHosei = 0.0f; //残機が１桁の時X位置を補正
	CVector4 LifeColor = { 1.0f,1.0f,1.0f,1.0f }; //HPバーの色
	CVector4 StarColor = { 1.0f,1.0f,1.0f,1.0f }; //流星バーの色
	const float ZankiScale = 3.0f; //残機数表示サイズ
	float ZankiScaleNow = 3.0f; //残機数表示サイズ

	bool StarMaxSE = false; //流星ゲージマックス効果音フラグ
	bool StarMaxSE2 = false; //流星ゲージマックス効果音フラグ

	bool WhiteGage = false; //白くする時のウェイトフラグ
	int WhiteTimer = 0;
	const int WhiteLimit = 20;

	//残機が減ったとき一瞬大きくする用
	int BeforeZanki = 0;
	bool ZankiAnimeFlag = false;
	int ZankiAnimeTimer = 0;
	const int ZankiAnimeLimit = 12; //表示時間

	//キコウチュウ撃破時の演出用
	bool KikoFlag = false;
	int KikoTimer = 0;
	const int KikoLimit = 40; //表示時間
	const int KikoWait = 60;
	const float KikoMoveX = 6.0f; //1フレームの移動量
	float Kiko_Alpha = 0.0f;
	const float Kiko_AlphaSpeed = 0.05f; //1フレームの加減量

	//スキルバー
	const float SkillScale = 0.5f; //スキル枠の大きさ
	const float StarMAX = 286.0f; //スターゲージの大きさ
	const float StarPOS = -156.0f; //目印が一番下の時の高さ
	short SkillIconMAX_Timer = 0; //スキルアイコンマックスタイマ～

	//スキルデータ（最初に保管）
	int SkillNoY = -1;
	int SkillNoX = -1;

};

