#pragma once
class GamePause : public IGameObject
{
	static GamePause* m_instance;
public:
	GamePause();
	~GamePause();
	bool Start();
	void Update();

	//インスタンスの取得
	static GamePause* GamePause::GetInstance() {
		return m_instance;
	}

private:

	void CursorUpdate();

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;

	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSoundSource* ss;

	int Timer = 0;
	bool CommandNow = false; //falseならBack、trueならリタイア

	//名前
	wchar_t StageName_hoge[255] = { L"" };	//モデル名保管用

	//一時用
	CVector3 position = CVector3::Zero;
	CVector3 scale = { 1.0f,0.0f,1.0f };
	CVector2 CV2_position = CVector2::Zero;
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//カーソル移動
	int CursorCount = 0;
	bool CursorFlag = false;

	//削除用
	bool DeleteFlag = false; //削除演出フラグ
	int DeleteTimer = 0;

	//定数
	const int SetWaitLimit = 60; //準備完了までの時間/操作できるようになる時間
	const int DeleteLimit = 30; //消去にかかる時間

	const float AccPos_Hosei = 300.0f; //上下枠の移動距離
	const float StagePos_Hosei = 500.0f; //ステージ枠の移動距離
};

