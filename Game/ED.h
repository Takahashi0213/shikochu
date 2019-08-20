#pragma once
class ED
{
	static ED* m_instance;
public:
	ED();
	~ED();
	bool Start();
	void Update();

	//インスタンスの取得
	static ED* ED::GetInstance() {
		return m_instance;
	}

private:

	void BounderSet(int x);
	void Bounder();
	//
	void UpperSet(int x);
	void Upper();
	//
	void KamisibaiSet(int x);
	void Kamisibai();

	//EDシーン
	enum ed_Scene {
		Tobu,
		Utyu,
		Otiru,
		Saigo,
		END,
	};

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	ed_Scene ED_Scene = Tobu;		 //状態

	int Timer = 0;
	CVector3 pos = CVector3::Zero;
	CVector3 scl = CVector3::One;

	//バウンダー
	int BoundSet[5]{
		{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};
	int BoundTimer[5]{
		{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};

	//アッパー
	int UppSet[5]{
		{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};
	int UpperTimer[5]{
		{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};

	float BMG_V = 0.8f;

	//紙芝居
	int KamisibaiNo = -1;
	int KamisibaiTimer = -1;

	//くるりん用
	int KuruTimer = 0;

	//実行用
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//スキップ用
	int SkipTimer = -1; //普段は-1
	float SkipAlpha = 1.0f;

	//定数
	const float DEF_POS = 720.0f;//デフォ用加算定数

	const float TextScale = 1.3f;
	const float SetumeiScale = 1.0f; //スキップ説明文の大きさ

	const int Scene1_Limit = 180; //シーン1のタイムリミット

	const int SkipMoziLimit = 120; //スキップ説明文が消えるまでの時間
};

